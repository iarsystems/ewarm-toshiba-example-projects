/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 * @ingroup		usbd_interface
 */

/* $Id: usb_usbd.c 41 2014-01-27 14:05:18Z danielru $ */

#include "usb_config.h"
#include <string.h>	/* memset() */
#include "usb_usbd_class.h"
#include "usb_uhub.h"
#include "usb_usbd_var.h"
#include "usb_usbd_subr.h"
#include "usb_usbd_mem.h"

#include "class/usb_classdrv.h"
#include "hcd/ohci/usb_ohci.h"
#include "hcd/ohci/usb_ohcireg.h"

#include "util/usb_trace.h"
#include "util/usb_dbg.h"
#include "util/usb_intr.h"
#include "util/usb_ctxswt.h"
#include "util/usb_tmr.h"
#if defined(USBD_UTIL)
#include "usb_usbd_util.h"
#endif

/*!
 * \param list  確認するリストの head
 * \retval 0    リストは空でない
 * \retval !0   リストは空である
 *
 * 双方向リンクリストが空であるか判定するマクロ
 */
#define DLIST_IS_EMPTY(list)	((list)->first == NULL)


/*!
 * \brief USBバスドライバで確保する広域変数群への参照用ポインタ
 *
 * USBドライバが初期化されると、USBドライバの広域変数を集めた
 * 構造体 usb_softc_t のアドレスが設定される。USBドライバの
 * 終了に伴い、NULL に戻る。
 */
#pragma section = "HC_RAM_USBDMEM"

static usb_softc_t*		usb_ptSOFTC @ "HC_RAM_USBDMEM"= NULL;


/************************** DECLARATIONS *************************/
static void			userTransferCompleted(usbd_xfer_t* ptXfer, usbd_status iStatus);


/************************ IMPLEMENTATIONS ************************/

/* ========================================================= */
/*							APIs							 */
/* ========================================================= */

/* --------------------------------------------------------- */
/*                  クラスドライバの登録                     */
/* --------------------------------------------------------- */
/*!
 * \brief クラスドライバ管理用構造体の新規生成
 * \return 新規生成したクラスドライバ管理用構造体。生成できない場合には NULL を返す。
 *
 * クラスドライバが usbd にコールバックを登録するための構造体を
 * 用意し返す。メモリの確保ができない場合には NULL を返す。
 */
USBD_typeClassDriver*
usb_USBD_ptAllocClassDriver(void)
{
	USBD_typeClassDriver* ptDriver = NULL;
	const usb_softc_t* ptSc = usb_ptSOFTC;
	
	USB_TRACE_ENTER1(0, usb_USBD_ptAllocClassDriver, 0);
	if(!ptSc) {
		DEBUG_ERROR_LOG(("usb_USBD_ptAllocClassDriver: USBD not initialized\n"));
		goto end;
	}
	ptDriver = usb_USBDAllocClassDriver();
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_ptAllocClassDriver, ptDriver);
	return ptDriver;
}

/*!
 * \brief クラスドライバ管理用構造体の解放
 * \param ptClassDriver 解放するクラスドライバ管理用構造体
 *
 * クラスドライバ管理用構造体を解放する。
 */
void
usb_USBD_vFreeClassDriver(USBD_typeClassDriver* ptClassDriver)
{
	const usb_softc_t* ptSc = usb_ptSOFTC;
	
	USB_TRACE_ENTER1(0, usb_USBD_vFreeClassDriver, ptClassDriver);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptSc) {
		DEBUG_ERROR_LOG(("usb_USBD_vFreeClassDriver: USBD not initialized\n"));
		goto end;
	}

	/* クラスドライバを登録解除(Remove)せずに free した場合、強制登録解除 */
	(void)usb_USBD_iRemoveClassDriver(ptClassDriver, NULL);
	
	usb_USBDDeallocClassDriver(ptClassDriver);
  end:
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_vFreeClassDriver, 0);
}

/*!
 * \brief クラスドライバの登録
 * \param ptClassDriver	登録するクラスドライバの情報をもった構造体
 * \param psOutError	エラーの出力先。NULL の指定で出力の省略が可能。
 * \retval USB_OK		登録成功
 * \retval USB_NG		登録失敗
 * \note ptClassDriver は USB_ptAllocClassDriver(void) で生成したものを使う。
 * \todo デバイスドライバが後からインストールされても、アタッチできるようにすることは可能？
 *		 (登録時に roothub に対して explore すればいいだけ？
 *		  現在ドライバ未割り当てのデバイスはポートをディスエーブルにしてある)
 *
 * ptClassDriver で指定したクラスドライバを登録する。
 * 登録が成功した場合には USB_OK, 失敗した場合には USB_NG を返す。
 * エラーコードは psOutError に出力される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iRegistClassDriver(USBD_typeClassDriver* ptClassDriver, int16_t* psOutError)
{
	usbd_status err;
	const usb_softc_t* ptSc = usb_ptSOFTC;

	USB_TRACE_ENTER1(0, usb_USBD_iRegistClassDriver, ptClassDriver);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptClassDriver) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptSc) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBD_iRegistClassDriver: USBD not initialized\n"));
		goto end;
	}
	SLIST_ENTRY_INIT(ptClassDriver);
	ptClassDriver->ulDeviceId = 0;
	
	SLIST_INSERT_TAIL(&ptSc->drvs, ptClassDriver);
	err = USBD_NORMAL_COMPLETION;
	
  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iRegistClassDriver, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief クラスドライバの登録解除
 * \param ptClassDriver	登録解除するクラスドライバの情報をもった構造体
 * \param psOutError	エラーの出力先。NULL の指定で出力の省略が可能。
 * \retval USB_OK		登録解除成功
 * \retval USB_NG		登録解除失敗
 * \note ptClassDriver は USB_ptAllocClassDriver(void) で生成したものを使う。
 *
 * ptClassDriver で指定したクラスドライバを登録解除する。
 * 登録解除が成功した場合には USB_OK, 失敗した場合には USB_NG を返す。
 * エラーコードは psOutError に出力される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iRemoveClassDriver(USBD_typeClassDriver* ptClassDriver, int16_t* psOutError)
{
	usbd_status err;
	USBD_typeClassDriver* ptDrv;
	const usb_softc_t* ptSc = usb_ptSOFTC;

	USB_TRACE_ENTER1(0, usb_USBD_iRemoveClassDriver, ptClassDriver);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptClassDriver) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptSc) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBD_iRemoveClassDriver: USBD not initialized\n"));
		goto end;
	}
	
	SLIST_FOREACH(ptDrv, USBD_typeClassDriver, &ptSc->drvs) {
		if(ptDrv == ptClassDriver) {
			SLIST_REMOVE(&ptSc->drvs, ptDrv);
			((usbd_device_t*)ptDrv->ulDeviceId)->ptDrv = NULL;
			ptDrv->ulDeviceId = 0;
			err = USBD_NORMAL_COMPLETION;
			goto end;
		}
	}
	err = USBD_INVAL;
  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iRemoveClassDriver, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}


/* --------------------------------------------------------- */
/*                   デバイス状態の通知                      */
/* --------------------------------------------------------- */
/*!
 * \brief デバイス状態通知を登録する
 * \param ptNotifications	登録する通知コールバック構造体
 * \param psOutError		エラーコードの出力先。NULL の指定で出力の省略が可能。
 * \retval USB_OK			成功
 * \retval USB_NG			失敗(USBドライバが初期化されていない)
 *
 * デバイス状態通知用のコールバック関数を登録する。
 * 登録用構造体に、通知をうけたい種別に対するコールバック関数を設定する。
 * それ以外のメンバには NULL を設定する。構造体はコピーされて格納される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iSetNotifications(USBD_typeNotification* ptNotifications, int16_t* psOutError)
{
	usbd_status err = USBD_NORMAL_COMPLETION;
	usb_softc_t* ptSc = usb_ptSOFTC;

	USB_TRACE_ENTER(0, usb_USBD_iSetNotifications);
	if(!ptNotifications) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptSc) {
		err = USBD_INVAL; /* usb-driver is not initialised */
		DEBUG_ERROR_LOG(("usb_USBD_iSetNotifications: USBD not initialized\n"));
		goto end;
	}
	ptSc->tNotifications = *ptNotifications;

  end:
	if(psOutError)
		*psOutError = err;
	USB_TRACE_LEAVE1(0, usb_USBD_iSetNotifications, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイス通知を受けたデバイスの接続されたポート番号を取得する
 * \param ulNotifyId	デバイス通知ID
 * \param pcOutPortNo	通知されたポート番号
 * \retval USB_OK		正常終了
 * \retval USB_NG		エラー終了
 * \attention この関数は、状態通知コールバックが呼び出されてから、他のUSB割り込みを
 *            契機とする処理が行なわれない区間で使用すること。つまり状態通知コール
 *            バック関数のスタック内で使用する。そうでないと、通知コールバックの後に
 *            再度イナミュレーションが行なわれ、それにより当該ポートが喪失する可能性がある。
 *
 * ulNotifyId で通知を受けたデバイスの、ハブに挿入されたポート番号を pcOutPortNo に取得する。
 */
int16_t
usb_USBD_Notify_iGetPortNumber(uint32_t ulNotifyId, uint8_t* pucOutPortNo)
{
	usbd_status err;
	const usbd_port_t* ptPort = (const usbd_port_t*)ulNotifyId;

	USB_TRACE_ENTER1(0, usb_USBD_Notify_iGetPortNumber, ulNotifyId);
	if(!ulNotifyId || !pucOutPortNo) {
		err = USBD_INVAL;
		goto end;
	}
	
	if(ptPort->tPortStage >= kPortConnected) {
		*pucOutPortNo = ptPort->ucPortNo;
		err = USBD_NORMAL_COMPLETION;
	}
	else {
		err = USBD_INVAL;
	}
	
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_Notify_iGetPortNumber, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイス通知を受けたデバイスのスピードを取得する
 * \param ulNotifyId	デバイス通知ID
 * \param pcOutSpeed	デバイスの通信スピード(USBD_FULL_SPEED, USBD_LOW_SPEED)
 * \retval USB_OK		正常終了
 * \retval USB_NG		エラー終了
 * \attention この関数は、状態通知コールバックが呼び出されてから、他のUSB割り込みを
 *            契機とする処理が行なわれない区間で使用すること。つまり状態通知コール
 *            バック関数のスタック内で使用する。そうでないと、通知コールバックの後に
 *            再度イナミュレーションが行なわれ、それにより当該ポートが喪失する可能性がある。
 *
 * ulNotifyId で通知を受けたデバイスの、デバイス通信速度を pcOutSpeed に取得する。
 * 取得した値は、USBD_FULL_SPEEDがフルスピード, USBD_LOW_SPEEDがロースピードを意味する。
 * connected, ignored の通知では、スピードを取得することはできない(エラー)。
 * ignored されたデバイスの disconnect でも、値の取得をすることはできない(エラー)。
 */
int16_t
usb_USBD_Notify_iGetSpeed(uint32_t ulNotifyId, int8_t* pcOutSpeed)
{
	usbd_status err;
	const usbd_port_t* ptPort = (const usbd_port_t*)ulNotifyId;

	USB_TRACE_ENTER1(0, usb_USBD_Notify_iGetSpeed, ulNotifyId);
	if(!ulNotifyId || !pcOutSpeed) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptPort->ptDevice) {
		err = USBD_IOERROR;
		goto end;
	}
	
	if(ptPort->tPortStage >= kPortIdentified && ptPort->tPortStage < kPortIgnored) {
		*pcOutSpeed = ptPort->ptDevice->cLowSpeed ? USBD_LOW_SPEED : USBD_FULL_SPEED;
		err = USBD_NORMAL_COMPLETION;
	}
	else {
		err = USBD_INVAL;
	}
	
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_Notify_iGetSpeed, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイス通知を受けたデバイスのデバイスアドレスを取得する
 * \param ulNotifyId		デバイス通知ID
 * \param pucOutAddress		デバイスアドレス
 * \retval USB_OK			正常終了
 * \retval USB_NG			エラー終了
 * \attention この関数は、状態通知コールバックが呼び出されてから、他のUSB割り込みを
 *            契機とする処理が行なわれない区間で使用すること。つまり状態通知コール
 *            バック関数のスタック内で使用する。そうでないと、通知コールバックの後に
 *            再度イナミュレーションが行なわれ、それにより当該ポートが喪失する可能性がある。
 *
 * ulNotifyId で通知を受けたデバイスの、デバイスアドレスを pucOutAddress に取得する。
 * デバイスアドレスは、USBポートに接続されたデバイスにUSBドライバが一意に割り当てたアドレス。
 * connected, ignored の通知では、取得することはできない(エラー)。
 * ignored されたデバイスの disconnect でも、値の取得をすることはできない(エラー)。
 */
int16_t
usb_USBD_Notify_iGetDeviceAddress(uint32_t ulNotifyId, uint8_t* pucOutAddress)
{
	usbd_status err;
	const usbd_port_t* ptPort = (const usbd_port_t*)ulNotifyId;

	USB_TRACE_ENTER1(0, usb_USBD_Notify_iGetDeviceAddress, ulNotifyId);
	if(!ulNotifyId || !pucOutAddress) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptPort->ptDevice) {
		err = USBD_IOERROR;
		goto end;
	}
	
	if(ptPort->tPortStage >= kPortIdentified && ptPort->tPortStage < kPortIgnored) {
		*pucOutAddress = ptPort->ptDevice->ucAddress;
		err = USBD_NORMAL_COMPLETION;
	}
	else {
		err = USBD_INVAL;
	}
	
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_Notify_iGetDeviceAddress, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイス通知を受けたデバイスのデバイス・デスクリプタを取得する
 * \param ulNotifyId	デバイス通知ID
 * \param pptOutDdesc	デバイス・デスクリプタ
 * \retval USB_OK		正常終了
 * \retval USB_NG		エラー終了
 * \attention この関数は、状態通知コールバックが呼び出されてから、他のUSB割り込みを
 *            契機とする処理が行なわれない区間で使用すること。つまり状態通知コール
 *            バック関数のスタック内で使用する。そうでないと、通知コールバックの後に
 *            再度イナミュレーションが行なわれ、それにより当該ポートが喪失する可能性がある。
 *
 * ulNotifyId で通知を受けたデバイスの、デバイス・デスクリプタを pptOutDdesc に取得する。
 * connected, ignored の通知では、取得することはできない(エラー)。
 * ignored されたデバイスの disconnect でも、値の取得をすることはできない(エラー)。
 */
int16_t
usb_USBD_Notify_iGetDeviceDesc(uint32_t ulNotifyId,
							   const usb_device_descriptor_t** pptOutDdesc)
{
	usbd_status err;
	const usbd_port_t* ptPort = (const usbd_port_t*)ulNotifyId;

	USB_TRACE_ENTER1(0, usb_USBD_Notify_iGetDeviceDesc, ulNotifyId);
	if(!ulNotifyId || !pptOutDdesc) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptPort->ptDevice) {
		err = USBD_IOERROR;
		goto end;
	}
	
	if(ptPort->tPortStage >= kPortIdentified && ptPort->tPortStage < kPortIgnored) {
		*pptOutDdesc = &ptPort->ptDevice->tDdesc;
		err = USBD_NORMAL_COMPLETION;
	}
	else {
		err = USBD_INVAL;
	}
	
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_Notify_iGetDeviceDesc, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイス通知を受けたデバイスのプロダクト名を取得する
 * \param ulNotifyId		デバイス通知ID
 * \param ppcOutProdName	プロダクト名
 * \retval USB_OK			正常終了
 * \retval USB_NG			エラー終了
 * \attention この関数は、状態通知コールバックが呼び出されてから、他のUSB割り込みを
 *            契機とする処理が行なわれない区間で使用すること。つまり状態通知コール
 *            バック関数のスタック内で使用する。そうでないと、通知コールバックの後に
 *            再度イナミュレーションが行なわれ、それにより当該ポートが喪失する可能性がある。
 *
 * ulNotifyId で通知を受けたデバイスの、プロダクト名(C文字列)を ppcOutProdName に取得する。
 * connected, ignored の通知では、取得することはできない(エラー)。
 * ignored されたデバイスの disconnect でも、値の取得をすることはできない(エラー)。
 */
int16_t
usb_USBD_Notify_iGetProductName(uint32_t ulNotifyId, const int8_t** ppcOutProdName)
{
	usbd_status err;
	const usbd_port_t* ptPort = (const usbd_port_t*)ulNotifyId;

	USB_TRACE_ENTER1(0, usb_USBD_Notify_iGetProductName, ulNotifyId);
	if(!ulNotifyId || !ppcOutProdName) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptPort->ptDevice) {
		err = USBD_IOERROR;
		goto end;
	}
	
	if(ptPort->tPortStage >= kPortIdentified && ptPort->tPortStage < kPortIgnored) {
		*ppcOutProdName = ptPort->ptDevice->pcProdName;
		err = USBD_NORMAL_COMPLETION;
	}
	else {
		err = USBD_INVAL;
	}
	
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_Notify_iGetProductName, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイス通知を受けたデバイスのマニュファクチャラー名を取得する
 * \param ulNotifyId		デバイス通知ID
 * \param ppcOutManuName	マニュファクチャラー名
 * \retval USB_OK			正常終了
 * \retval USB_NG			エラー終了
 * \attention この関数は、状態通知コールバックが呼び出されてから、他のUSB割り込みを
 *            契機とする処理が行なわれない区間で使用すること。つまり状態通知コール
 *            バック関数のスタック内で使用する。そうでないと、通知コールバックの後に
 *            再度イナミュレーションが行なわれ、それにより当該ポートが喪失する可能性がある。
 *
 * ulNotifyId で通知を受けたデバイスの、マニュファクチャラー名(C文字列)を
 * ppcOutManuName に取得する。
 * connected, ignored の通知では、取得することはできない(エラー)。
 * ignored されたデバイスの disconnect でも、値の取得をすることはできない(エラー)。
 */
int16_t
usb_USBD_Notify_iGetManufacturerName(uint32_t ulNotifyId, const int8_t** ppcOutManuName)
{
	usbd_status err;
	const usbd_port_t* ptPort = (const usbd_port_t*)ulNotifyId;

	USB_TRACE_ENTER1(0, usb_USBD_Notify_iGetManufacturerName, ulNotifyId);
	if(!ulNotifyId || !ppcOutManuName) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptPort->ptDevice) {
		err = USBD_IOERROR;
		goto end;
	}
	
	if(ptPort->tPortStage >= kPortIdentified && ptPort->tPortStage < kPortIgnored) {
		*ppcOutManuName = ptPort->ptDevice->pcManuName;
		err = USBD_NORMAL_COMPLETION;
	}
	else {
		err = USBD_INVAL;
	}
	
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_Notify_iGetManufacturerName, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイス通知を受けたデバイスのパワータイプの取得
 * \param ulNotifyId		デバイス通知ID
 * \param pcOutPowerType	デバイスのパワータイプ
 * \retval USB_OK			正常終了
 * \retval USB_NG			エラー終了
 * \attention この関数は、状態通知コールバックが呼び出されてから、他のUSB割り込みを
 *            契機とする処理が行なわれない区間で使用すること。つまり状態通知コール
 *            バック関数のスタック内で使用する。そうでないと、通知コールバックの後に
 *            再度イナミュレーションが行なわれ、それにより当該ポートが喪失する可能性がある。
 *
 * ulNotifyId で通知を受けたデバイスの、パワータイプを pcOutPowerType に取得する。
 * バスパワーなら USBD_BUS_POWERED, セルフパワーなら USBD_SELF_POWERED が pcOutPowerType
 * に返される。
 * connected, ignored の通知では、取得することはできない(エラー)。
 * ignored されたデバイスの disconnect でも、値の取得をすることはできない(エラー)。
 */
int16_t
usb_USBD_Notify_iGetPowerType(uint32_t ulNotifyId, int8_t* pcOutPowerType)
{
	usbd_status err;
	const usbd_port_t* ptPort = (const usbd_port_t*)ulNotifyId;

	USB_TRACE_ENTER1(0, usb_USBD_Notify_iGetPowerType, ulNotifyId);
	if(!ulNotifyId || !pcOutPowerType) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptPort->ptDevice) {
		err = USBD_IOERROR;
		goto end;
	}
	
	if(ptPort->tPortStage >= kPortIdentified && ptPort->tPortStage < kPortIgnored) {
		*pcOutPowerType = ptPort->ptDevice->cSelfPowered ? USBD_SELF_POWERED : USBD_BUS_POWERED;
		err = USBD_NORMAL_COMPLETION;
	}
	else {
		err = USBD_INVAL;
	}
	
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_Notify_iGetPowerType, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイス通知を受けたデバイスの電流量を取得する
 * \param ulNotifyId		デバイス通知ID
 * \param pusOutMaxPower	電流量(mA)
 * \retval USB_OK			正常終了
 * \retval USB_NG			エラー終了
 * \attention この関数は、状態通知コールバックが呼び出されてから、他のUSB割り込みを
 *            契機とする処理が行なわれない区間で使用すること。つまり状態通知コール
 *            バック関数のスタック内で使用する。そうでないと、通知コールバックの後に
 *            再度イナミュレーションが行なわれ、それにより当該ポートが喪失する可能性がある。
 *
 * ulNotifyId で通知を受けたデバイスの、最大要求電流量(mA)を pusOutMaxPower に取得する。
 * connected, ignored の通知では、取得することはできない(エラー)。
 * ignored されたデバイスの disconnect でも、値の取得をすることはできない(エラー)。
 */
int16_t
usb_USBD_Notify_iGetMaxPower(uint32_t ulNotifyId, uint16_t* pusOutMaxPower)
{
	usbd_status err;
	const usbd_port_t* ptPort = (const usbd_port_t*)ulNotifyId;

	USB_TRACE_ENTER1(0, usb_USBD_Notify_iGetMaxPower, ulNotifyId);
	if(!ulNotifyId || !pusOutMaxPower) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptPort->ptDevice) {
		err = USBD_IOERROR;
		goto end;
	}
	
	if(ptPort->tPortStage >= kPortIdentified && ptPort->tPortStage < kPortIgnored) {
		*pusOutMaxPower = ptPort->ptDevice->usPower;
		err = USBD_NORMAL_COMPLETION;
	}
	else {
		err = USBD_INVAL;
	}
	
  end:
	USB_TRACE_LEAVE1(0, usb_USBD_Notify_iGetMaxPower, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}




/* --------------------------------------------------------- */
/*                    ハンドルの取得                         */
/* --------------------------------------------------------- */
/*!
 * \brief デバイスをオープンする
 * \param ulDeviceId	オープンするデバイス
 * \param psOutError	エラーコード。NULL の指定で出力の省略が可能。
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * ulDeviceId で指定されたデバイスをオープンする。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iOpenDevice(uint32_t ulDeviceId, int16_t* psOutError)
{
	usbd_status err;
	const usbd_bus_t* ptBus;
	int16_t i;

	USB_TRACE_ENTER1(0, usb_USBD_iOpenDevice, ulDeviceId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ulDeviceId) {
		err = USBD_INVAL;
		goto end;
	}
	ptBus = ((usbd_device_t*)ulDeviceId)->ptBus;
	
	for(i = 0; i < USBD_MAX_DEVICES; i++) {
		if(ptBus->pptDevices[i] == (usbd_device_t*)ulDeviceId) {
			err = USBD_NORMAL_COMPLETION;
			goto end;
		}
	}
	err = USBD_INVAL;
  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iOpenDevice, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイスをクローズする
 * \param ulDeviceId	クローズするデバイスID
 * \param psOutError	エラーコード。NULL の指定で出力の省略が可能。
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * ulDeviceId で指定されたデバイスをクローズする。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iCloseDevice(uint32_t ulDeviceId, int16_t* psOutError)
{
	int16_t err = USBD_NORMAL_COMPLETION;

	USB_TRACE_ENTER1(0, usb_USBD_iCloseDevice, ulDeviceId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ulDeviceId) {
		err = USBD_INVAL;
		goto end;
	}
	(void)usb_USBD_iCancelIoDevice(ulDeviceId, &err);

  end:
	if(psOutError)
		*psOutError = err;

	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iCloseDevice, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief インターフェイスをオープンする
 * \param ulDeviceId	インターフェイスをオープンするデバイスのデバイスID
 * \param ucIfaceNo		取得するインターフェイスの番号
 * \param pulOutIfaceId	取得するインターフェイスIDの出力先
 * \param psOutError	エラーコード。NULL の指定で出力の省略が可能。
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * ulDeviceId で指定したデバイスの ucIfaceNo 番目のインターフェイスをオープンする。
 * インターフェイスの数や種別の特定には、usb_USBD_iSetConfigurationIndex() により、
 * コンフィグ・デスクリプタの取得を行なう必要がある。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iOpenInterface(uint32_t ulDeviceId,
						uint8_t ucIfaceNo,
						uint32_t* pulOutIfaceId,
						int16_t* psOutError)
{
	usbd_status err;
	usbd_interface_t* ptIface = NULL;
	usbd_device_t* ptDev = (usbd_device_t*)ulDeviceId;

	USB_TRACE_ENTER1(0, usb_USBD_iOpenInterface, ulDeviceId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ulDeviceId || !pulOutIfaceId) {
		err = USBD_INVAL;
		goto end;
	}
	/* USBD 内部管理から指定のインターフェイスを取得する */
	err = usb_USBDDeviceToInterface(ptDev, (uint8_t)ucIfaceNo, &ptIface);
	if(err) {
		goto end;
	}
	*(usbd_interface_t**)pulOutIfaceId = ptIface;
	
  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iOpenInterface, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief インターフェイスをクローズする
 * \param ulIfaceId		クローズするインターフェイスID
 * \param psOutError	エラーコード。NULL の指定で出力の省略が可能。
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * ifaceId で指定したインターフェイスをクローズする。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iCloseInterface(uint32_t ulIfaceId, int16_t* psOutError)
{
	int16_t err = USBD_NORMAL_COMPLETION;

	USB_TRACE_ENTER1(0, usb_USBD_iCloseInterface, ulIfaceId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ulIfaceId) {
		err = USBD_INVAL;
		goto end;
	}
	(void)usb_USBD_iCancelIoInterface(ulIfaceId, &err);

  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iCloseInterface, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief パイプをオープンする
 * \param ulIfaceId		パイプをオープンするインターフェイスのID
 * \param ptEdesc		パイプを選択するためのエンドポイントデスクリプタ
 * \param fpFinished	通信完了のコールバック
 * \param ulArg			コールバックに渡す引数
 * \param pulOutPipeId	オープンしたパイプIDの出力先
 * \param psOutError	エラーコード。NULL の指定で出力の省略が可能。
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 * \todo Interrupt のパイプは別のインターフェイスを用意するほうがいい？
 *       周期転送時のInterruptのオープンに使うintervalの指定ができない。(ptPipe->ucInterval)
 *
 * ulIfaceId で指定したインターフェイスの ptEdesc で指定されたエンドポイントをもつ
 * パイプをオープンし、そのパイプへのハンドルを pulOutPipeId に渡す。
 * 同時に、オープンしたパイプの転送完了を通知するコールバックの登録も行なう。
 * 以後、このパイプに関する転送完了は、 fpFinished で指定した関数に、ulArg で指定した
 * 引数を用いて呼び出される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iOpenPipe(uint32_t ulIfaceId,
				   usb_endpoint_descriptor_t* ptEdesc,
				   USBD_typeCommFinished fpFinished,
				   uint32_t ulArg,
				   uint32_t* pulOutPipeId,
				   int16_t* psOutError)
{
	usbd_status err;
	usbd_pipe_t* ptPipe = NULL;

	USB_TRACE_ENTER1(0, usb_USBD_iOpenPipe, ulIfaceId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ulIfaceId || !ptEdesc || !pulOutPipeId) {
		err = USBD_INVAL;
		goto end;
	}
	
	err = usb_USBDOpenPipe((usbd_interface_t*)ulIfaceId,
						   ptEdesc->bEndpointAddress,
						   &ptPipe);
	if(err) {
		goto end;
	}
	if(!ptPipe) {
		DEBUG_ERROR_LOG(("usb_USBD_iOpenPipe: pipe not found\n"));
		err = USBD_INVAL;
		goto end;
	}
	/* register callback */
	ptPipe->tCallback.fpCallback = fpFinished;
	ptPipe->tCallback.ulArg = ulArg;
	
	*pulOutPipeId = (uint32_t)ptPipe;
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("usb_USBD_iOpenPipe: pipe = %#08x\n", *pulOutPipeId);
#endif

  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iOpenPipe, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief パイプをクローズする
 * \param ulPipeId		クローズするパイプのID
 * \param psOutError	エラーコード
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * pipeId で示されたパイプをクローズする。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iClosePipe(uint32_t ulPipeId, int16_t* psOutError)
{
	usbd_status err;
	usbd_pipe_t* ptPipe = (usbd_pipe_t*)ulPipeId;

	USB_TRACE_ENTER1(0, usb_USBD_iClosePipe, ulPipeId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptPipe) {
		err = USBD_INVAL;
		goto end;
	}
	/* TODO XXX closePipe のような処理にすべきか？ */
	if(!ptPipe->cRefcnt) {
		err = USBD_INVAL;
		goto end;
	}
	usb_USBDKillPipe(ptPipe);
	err = USBD_NORMAL_COMPLETION;

  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iClosePipe, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}


/* --------------------------------------------------------- */
/*                         転送                              */
/* --------------------------------------------------------- */
/*!
 * \brief パイプに対する送受信を行なう
 * \param ulPipeId		送受信を行なうパイプのID
 * \param pvBuffer		送受信するバッファ
 * \param usLength		送受信するバッファ長
 * \param usFlags		転送フラグ
 * \param psOutError	エラーコード
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * ulPipeId で指定したパイプに対して pvBuffer と usLength で示されるデータの
 * 送信(または受信)を行なう。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 *
 * \note 送信/受信の方向は、pipe によって既に決定している。
 */
int16_t
usb_USBD_iIoPipe(uint32_t ulPipeId,
				 void* pvBuffer,
				 uint16_t usLength,
				 uint16_t usFlags,
				 int16_t* psOutError)
{
	usbd_status err = USBD_NORMAL_COMPLETION;
	usbd_pipe_t* ptPipe = (usbd_pipe_t*)ulPipeId;
	usbd_xfer_t* ptXfer;
	const usbd_endpoint_t* ptEd;
	usbd_device_t* ptDev;

	USB_TRACE_ENTER1(0, usb_USBD_iIoPipe, ulPipeId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptPipe || !pvBuffer) {
		err = USBD_INVAL;
		goto end;
	}
	ptEd = ptPipe->ptEndpoint;
	ptDev = ptPipe->ptDevice;

#if 0 /* TODO usb_USBD_iClosePipe() での cRefcnt の処理に関連して */
	if(!ptPipe->cRefcnt) {
		err = USBD_IOERROR;
		goto end;
	}
#endif
	/* check length */
	if(UE_GET_XFERTYPE(ptEd->ptEdesc->bmAttributes) == UE_INTERRUPT) {
		if(usLength == 0 || ptDev->tDdesc.bMaxPacketSize < usLength) {
			err = USBD_INVAL;
			goto end;
		}
	}
	else if(UE_GET_XFERTYPE(ptEd->ptEdesc->bmAttributes) == UE_BULK) {
		/* XXX is the max size of bulk specified? */
		if(usLength == 0) {
			err = USBD_INVAL;
			goto end;
		}
	}
	
	/* setup and start xfer */
	if(ptPipe->ptXfer) {
		err = USBD_IN_USE;
		goto end;
	}
	ptXfer = usb_USBDAllocXfer(ptDev);
	if(!ptXfer) {
		err = USBD_NOMEM;
		goto end;
	}
	usb_USBDInitXfer(ptXfer, ptPipe, pvBuffer,
					 usLength, USBD_DEFAULT_TIMEOUT, userTransferCompleted);
	ptXfer->usFlags = usFlags;
	err = usb_USBDStartTransfer(ptXfer);
	
  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iIoPipe, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}


/*!
 * \brief デバイス単位の通信キャンセル
 * \param ulDevId		デバイスID
 * \param psOutError	エラーコード
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * デバイスID ulDevId で指定したデバイスの, すべてのパイプの通信をキャンセルする。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iCancelIoDevice( uint32_t ulDevId, int16_t* psOutError )
{
	int16_t err = USBD_NORMAL_COMPLETION;
	usbd_device_t* ptDev = (usbd_device_t*)ulDevId;

	USB_TRACE_ENTER1(0, usb_USBD_iCancelIoDevice, ulDevId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptDev) {
		err = USBD_INVAL;
		goto end;
	}
	
	(void)usb_USBD_iCancelIoInterface((uint32_t)ptDev->ptIfaces, &err);

  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iCancelIoDevice, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief インターフェース単位の通信キャンセル
 * \param ulIfaceId		インターフェイスID
 * \param psOutError	エラーコード
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * インターフェイスID ifaceId で指定したインターフェイスの,
 * すべてのパイプの通信をキャンセルする。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iCancelIoInterface( uint32_t ulIfaceId, int16_t* psOutError )
{
	usbd_pipe_t* ptPipe = NULL;
	int16_t er = USBD_NORMAL_COMPLETION;
	usbd_status err = USBD_NORMAL_COMPLETION;
	const usbd_interface_t* ptIface = (usbd_interface_t*)ulIfaceId;

	USB_TRACE_ENTER1(0, usb_USBD_iCancelIoInterface, ulIfaceId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptIface) {
		err = USBD_INVAL;
		goto end;
	}
	
	DLIST_FOREACH( ptPipe, usbd_pipe_t, &ptIface->pipes ) {
		(void)usb_USBD_iCancelIoPipe( (uint32_t)ptPipe, &er );
		if(er) {
			err = er;
		}
	}

  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iCancelIoInterface, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief パイプに対する送受信を中止する
 * \param ulPipeId		送受信を中止するパイプのID
 * \param psOutError	エラーコード
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * ulPipeId で指定されたパイプの送受信を中断する。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iCancelIoPipe(uint32_t ulPipeId, int16_t* psOutError)
{
	usbd_status err;
	usbd_pipe_t* ptPipe = (usbd_pipe_t*)ulPipeId;

	USB_TRACE_ENTER1(0, usb_USBD_iCancelIoPipe, ulPipeId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptPipe) {
		err = USBD_INVAL;
		goto end;
	}
	
	err = usb_USBDAbortPipe(ptPipe);

  end:
	if(psOutError)
		*psOutError = err;
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iCancelIoPipe, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief デバイスリクエストを発行する
 * \param ulDeviceId	デバイスリクエストを発行するデバイスのID
 * \param ptRequest		発行するデバイスリクエスト
 * \param pvInOutBuf	デバイスリクエストの送受信バッファ
 * \param psOutError	エラーコード
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * ulDeviceId で指定したデバイスに ptRequest で指定したデバイスリクエストを発行する。
 * デバイスリクエストに伴う入出力バッファがある場合には、pvInOutBuf にバッファを指定
 * する。動作はポーリングで、転送が完了するまで関数から復帰しない。
 * エラーは psOutError に代入され返される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 *
 * \todo アプリケーションのコンテキストから呼び出される場合には、ポーリングになる
 *       ため、アプリケーションに処理が戻らない。アプリからは、非同期で使わせる
 *       ようにすべきである(現状MSCではBBBを使っているのでアプリからは使われる
 *       ことはない)。非同期型デバイスリクエスト発行の別関数を用意するのが良い。
 */
int16_t
usb_USBD_iDeviceRequest(uint32_t ulDeviceId,
						usb_device_request_t* ptRequest,
						void* pvInOutBuf,
						int16_t* psOutError)
{
	usbd_status err;
	usbd_device_t* ptDevice = (usbd_device_t*)ulDeviceId;

	USB_TRACE_ENTER1(0, usb_USBD_iDeviceRequest, ulDeviceId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptDevice || !ptRequest) {
		err = USBD_INVAL;
		goto end;
	}
	
	err = usb_USBDDeviceRequest(ptDevice, ptRequest, pvInOutBuf, 0,
							 USBD_DEFAULT_TIMEOUT, (usbd_callback)0);
	
  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iDeviceRequest, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief パイプのHALTをクリアする
 * \param ulPipeId		HALTを解除するエンドポイントのパイプ
 * \param psOutError	エラーコード[out]
 * \retval	USB_OK		成功
 * \retval	USB_NG		失敗
 *
 * pipeId で指定したパイプのエンドポイントの HALT を
 * デバイスリクエスト ClearFeature(EndpointHalt) を発行して、クリアする。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iClearFeatureEndpoint(uint32_t ulPipeId, int16_t* psOutError)
{
	usbd_status err;
	usbd_device_t* ptDevice;
	usb_device_request_t* ptRequest = NULL;
	usbd_pipe_t* ptPipe = (usbd_pipe_t*)ulPipeId;

	USB_TRACE_ENTER1(0, usb_USBD_iClearFeatureEndpoint, ulPipeId);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptPipe) {
		err = USBD_INVAL;
		goto end;
	}
	ptDevice = ptPipe->ptDevice;
	
	ptRequest = usb_USBDAllocDeviceRequest();
	if(!ptRequest) {
		err = USBD_NOMEM;
		goto end;
	}
	ptRequest->bmRequestType = UT_WRITE_ENDPOINT;
	ptRequest->bRequest = UR_CLEAR_FEATURE;
	USB_SETW(ptRequest->wValue, UF_ENDPOINT_HALT);
	USB_SETW(ptRequest->wIndex, ptPipe->ptEndpoint->ptEdesc->bEndpointAddress);
	USB_SETW(ptRequest->wLength, 0);
	err = usb_USBDDeviceRequest(ptDevice, ptRequest, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
	if(err) {
		goto end;
	}
	/* TODO GetStatus(Endpoint) の発行をしてそのステータスをエラーコードに返す？ */

  /* トグルクリア */
	if(ptPipe->tMethods.fpClearToggle)
		ptPipe->tMethods.fpClearToggle(ptPipe);
	
  end:
	if(ptRequest)
		usb_USBDDeallocDeviceRequest(ptRequest);
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iClearFeatureEndpoint, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}


/* --------------------------------------------------------- */
/*                 ポートの切断/再接続                       */
/* --------------------------------------------------------- */
/*!
 * \brief デバイスが接続されているハブのデバイスID と ポート番号を取得する
 * \param ulIdDevice		対象デバイスのID
 * \param pulOutIdPort		デバイスが接続されているハブのポートID
 * \param pusOutError		エラーコード。NULL 指定で省略可能。
 * \retval USB_OK			正常終了
 * \retval USB_NG			エラー終了
 *
 * ulIdDevice のデバイスが接続されている、ハブのポート管理情報へのID を
 * pulOutIdPort に取得する。
 * pusOutError にはエラーコードが usbd_status の値で返却される。
 * 取得したポートIDは、usb_USBD_iDisconnectPort(), usb_USBD_iConnectPort()
 * で切断/再接続するポートを指定するために使用する。
 * psOutError に NULL を指定した場合、エラーコードの取得を省略することができる。
 */
int16_t
usb_USBD_iGetPortId(uint32_t ulIdDevice,
					uint32_t* pulOutIdPort,
					int16_t* psOutError)
{
	uint8_t i;
	const usbd_bus_t* ptBus;
	usbd_status err = USBD_NORMAL_COMPLETION;
	const usbd_device_t* ptDev = (usbd_device_t*)ulIdDevice;

	USB_TRACE_ENTER1(0, usb_USBD_iGetPortId, ulIdDevice);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptDev || !pulOutIdPort) {
		err = USBD_INVAL;
		goto end;
	}
	ptBus = ptDev->ptBus;
	
	/* check device's existence */
	for(i = 0; i < USBD_MAX_DEVICES; i++) {
		if(ptBus->pptDevices[i] == ptDev) {
			goto found;
		}
	}
	err = USBD_IOERROR;
	goto end;

  found: /* device exists on the bus */
	*pulOutIdPort = (uint32_t)ptDev->ptPowerSrc; /* hubport or 0(roothub's upstream port) */
	err = USBD_NORMAL_COMPLETION;
	
  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iGetPortId, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}


/*!
 * \brief ptPort で指定されるポートが実在していることを確認する。
 * \param ptPort   実在の確認をするポート
 * \param ptBus    ポートの存在しているバス
 * \retval USBD_NORMAL_COMPLETION  ポートは存在している
 * \retval USBD_IOERROR            ポートは存在していないまたは引数エラー
 * \attention 正しくポートの存在を確認するため、ポートの存在確認と
 *            ポートを利用する関数呼び出しは、１つのUSB割り込み禁止区間から呼び出すこと。
 *
 * ptPort で指定するポートが ptBus 上に存在しているか確認する。
 * 指定ポートを持つハブデバイスが取り除かれ、バス・イナミュレーションが
 * 発生することでポートが存在していない可能性があるため、安全にこれを確認する。
 * ポートの存在が確認できた場合には USBD_NORMAL_COMPLETION を, そうでない場合
 * には USBD_IOERROR を返す。
 */
static usbd_status
doesPortExist(usbd_port_t* ptPort, usbd_bus_t* ptBus)
{
	uint16_t i, j;
	usbd_hub_t* ptHub;
	int16_t iRet = USBD_IOERROR;
	
	if(!ptPort || !ptBus) {
		goto end;
	}
	if(!ptBus->pptDevices) {
		goto end;
	}
	for(i = 0; i < USBD_MAX_DEVICES; i++) {
		if(ptBus->pptDevices[i] && ptBus->pptDevices[i]->ptHub) {
			ptHub = ptBus->pptDevices[i]->ptHub;
			for(j = 0; j < ptHub->tHubDesc.bNbrPorts; j++) {
				if(ptPort == &ptHub->ptPorts[j]) {
					iRet = USBD_NORMAL_COMPLETION;
					goto end;
				}
			}
		}
	}
	
  end:
	return iRet;
}

/*!
 * \brief ポートを切断する
 * \param ulIdPort		ポート切断するポートのポートID
 * \param pusOutError	エラーコード (NULL指定により省略可能)
 * \retval USB_OK		正常終了
 * \retval USB_NG		エラー終了
 *
 * ulIdPort で指定されるポートをバスドライバにより切断処理をさせる。
 * 接続状態にあるポートをソフトウェア的に切断する。
 * psOutError に NULL を指定した場合、エラーコードの取得を省略することができる。
 */
int16_t
usb_USBD_iDisconnectPort(uint32_t ulIdPort, int16_t* psOutError)
{
	usbd_status err;
	usb_port_status_t tPortStatus = { 0, 0 };
	usbd_port_t* ptPort = (usbd_port_t*)ulIdPort;

	USB_TRACE_ENTER1(0, usb_USBD_iDisconnectPort, ulIdPort);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptPort) {
		err = USBD_INVAL;
		goto end;
	}

	/* ポートの存在確認 */
	if(!usb_ptSOFTC || !usb_ptSOFTC->ptBus) {
		err =USBD_INVAL;
		goto end;
	}
	err = doesPortExist(ptPort, usb_ptSOFTC->ptBus);
	if(err != USBD_NORMAL_COMPLETION) {
		goto end;
	}

	/* ソフトウェアで切断された時のポートステータスをつくり出し、ハブクラスに処理させる */
	USB_SETW(tPortStatus.wPortStatus, UPS_PORT_ENABLED | UPS_PORT_POWER);
	USB_SETW(tPortStatus.wPortChange, UPS_C_CONNECT_STATUS);
	usb_vUHUBProcConnectStatusChange(ptPort->ptParent, ptPort->ucPortNo, &tPortStatus);
	err = USBD_NORMAL_COMPLETION;

 end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iDisconnectPort, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief ポートを接続する
 * \param ulIdPort		電力供給を開始するポートのポートID
 * \param pusOutError	エラーコード (NULL指定により省略可能)
 * \retval USB_OK		正常終了
 * \retval USB_NG		エラー終了
 *
 * ulIdPort で指定したポートのデバイスを再度イナミュレーションを行ない、
 * バスドライバにより接続処理をする。
 * デバイスが接続状態にあるポートや、デバイスが接続されているがソフトウェア的に
 * 切断状態にあるポート(usb_USBD_iDisconnectPort() による)をソフトウェア的に
 * 再度接続を行なう。
 * psOutError に NULL を指定した場合、エラーコードの取得を省略することができる。
 */
int16_t
usb_USBD_iConnectPort(uint32_t ulIdPort, int16_t* psOutError)
{
	usbd_status err;
	usb_port_status_t tPortStatus = { 0, 0 };
	usbd_port_t* ptPort = (usbd_port_t*)ulIdPort;

	USB_TRACE_ENTER1(0, usb_USBD_iConnectPort, ulIdPort);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptPort) {
		err = USBD_INVAL;
		goto end;
	}

	/* ポートの存在確認 */
	if(!usb_ptSOFTC || !usb_ptSOFTC->ptBus) {
		err =USBD_INVAL;
		goto end;
	}
	err = doesPortExist(ptPort, usb_ptSOFTC->ptBus);
	if(err != USBD_NORMAL_COMPLETION) {
		goto end;
	}

	/* ソフトウェアで接続された時のポートステータスをつくり出し、ハブクラスに処理させる */
	USB_SETW(tPortStatus.wPortStatus, UPS_CURRENT_CONNECT_STATUS | UPS_PORT_POWER |
									  UPS_PORT_ENABLED);
	USB_SETW(tPortStatus.wPortChange, UPS_C_CONNECT_STATUS);
	usb_vUHUBProcConnectStatusChange(ptPort->ptParent, ptPort->ucPortNo, &tPortStatus);
	err = USBD_NORMAL_COMPLETION;
	
 end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iConnectPort, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}



/* --------------------------------------------------------- */
/*                 デスクリプタの取得                        */
/* --------------------------------------------------------- */
/*!
 * \brief デバイスデスクリプタの取得
 * \param ulIdDev		デスクリプタを取得するデバイスのID
 * \param pptOutDdesc	デスクリプタの出力先(out)
 * \param psOutError	エラーコード(out)
 * \retval	USB_OK		取得成功
 * \retval	USB_NG		取得失敗
 *
 * ulIdDev で指定したデバイスのデバイスデスクリプタを pptOutDdesc に出力する。
 * 取得に成功した場合には、psOutError に USBD_NORMAL_COMPLETION が返却される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iGetDeviceDescriptor(uint32_t ulIdDev,
							  const usb_device_descriptor_t** pptOutDdesc,
							  int16_t* psOutError)
{
	usbd_status err = USBD_NORMAL_COMPLETION;
	usbd_device_t* ptDev = (usbd_device_t*)ulIdDev;

	USB_TRACE_ENTER1(0, usb_USBD_iGetDeviceDescriptor, ulIdDev);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptDev || !pptOutDdesc) {
		err = USBD_INVAL;
		goto end;
	}
	
	*pptOutDdesc = &ptDev->tDdesc;

  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iGetDeviceDescriptor, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief コンフィグデスクリプタの取得
 * \param ulIdDev		デスクリプタを取得するデバイスのID
 * \param sCfgIndex		コンフィグレーションインデックス番号
 * \param pptCfgDesc	デスクリプタの出力先(out)
 * \param psOutError	エラーコード(out)
 * \retval	USB_OK		取得成功
 * \retval	USB_NG		取得失敗
 *
 * ulIdDev で指定したデバイスの ucCfgIndex をインデックスにもつ
 * コンフィグデスクリプタを pptCfgDesc に出力する。
 * 取得に成功した場合には、psOutError に USBD_NORMAL_COMPLETION が返却される。
 * ucCfgNo が範囲外の場合には USB_INVAL が返却される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 *
 * \note インデックス番号は、コンフィグ・デスクリプタのインデックス
 *       (0,1,2,...ddesc->bNumConfigurations)であり、コンフィグ・デスク
 *       リプタにあるコンフィグレーション番号(cdesc->bConfigurationValue)
 *       のことではない。
 */
int16_t
usb_USBD_iGetConfigDescriptor(uint32_t ulIdDev,
							  int16_t sCfgIndex,
							  const usb_config_descriptor_t** pptCfgDesc,
							  int16_t* psOutError)
{
	usbd_status err = USBD_NORMAL_COMPLETION;
	usbd_device_t* ptDev = (usbd_device_t*)ulIdDev;

	USB_TRACE_ENTER1(0, usb_USBD_iGetConfigDescriptor, ulIdDev);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptDev || !pptCfgDesc) {
		err = USBD_INVAL;
		goto end;
	}
	
	err = usb_USBDSetConfigIndex(ptDev, sCfgIndex);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBD_iGetConfigDescriptor: failed to set config index(=%u)\n", sCfgIndex));
		goto end;
	}
	if((sCfgIndex != USB_UNCONFIG_INDEX && !ptDev->ptCdesc) ||
	   (sCfgIndex == USB_UNCONFIG_INDEX && ptDev->ptCdesc)) {
		err = USBD_INVAL;
		goto end;
	}
	*pptCfgDesc = ptDev->ptCdesc;
	
  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iGetConfigDescriptor, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief インターフェイスデスクリプタの取得
 * \param ulIdDev		デスクリプタを取得するデバイスのID
 * \param ucIfaceNo		インターフェイス番号
 * \param pptOutIdesc	デスクリプタの出力先(out)
 * \param psOutError	エラーコード(out)
 * \retval	USB_OK		取得成功
 * \retval	USB_NG		取得失敗
 *
 * ulIdDev で指定したデバイスの ucIfaceNo をインターフェイス番号にもつ
 * インターフェイスデスクリプタを pptOutIdesc に出力する。
 * 取得に成功した場合には、psOutError に USBD_NORMAL_COMPLETION が返却される。
 * ucIfaceNo が範囲外の場合には USB_INVAL が、デバイスにコンフィギュレーション
 * 設定がされていなかった場合(UNCONFIG)には USBD_NOT_CONFIGURED が
 * 返却される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iGetInterfaceDescriptor(uint32_t ulIdDev,
								 uint8_t ucIfaceNo,
								 const usb_interface_descriptor_t** pptOutIdesc,
								 int16_t* psOutError)
{
	usbd_status err;
	usbd_interface_t* ptIface = NULL;
	usbd_device_t* ptDev = (usbd_device_t*)ulIdDev;

	USB_TRACE_ENTER1(0, usb_USBD_iGetInterfaceDescriptor, ulIdDev);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ulIdDev || !pptOutIdesc) {
		err = USBD_INVAL;
		goto end;
	}
	
	err = usb_USBDDeviceToInterface(ptDev, ucIfaceNo, &ptIface);
	if(err) {
		goto end;
	}
	if(!ptIface) {
		err = USBD_INVAL;	/* which case ? */
		goto end;
	}
	*pptOutIdesc = ptIface->ptIdesc;
	
  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iGetInterfaceDescriptor, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief エンドポイントデスクリプタの取得
 * \param ulIdIface		デスクリプタを取得するインターフェイスのID
 * \param ucEndptNo		デスクリプタを取得するエンドポイントのエンドポイント番号
 * \param pptOutEdesc	デスクリプタの出力先(out)
 * \param psOutError	エラーコード(out)
 * \retval	USB_OK		取得成功
 * \retval	USB_NG		取得失敗
 *
 * ulIdIface で指定したインターフェイスの ucEndptNo 番目のエンドポイントデスクリプタ
 * を pptOutEdesc に出力する。ucEndptNo は 0からidesc.bNumEndpointsまでの値。
 * 取得に成功した場合には、psOutError に USBD_NORMAL_COMPLETION が返却される。
 * ucEndptNo が不正だった場合には USBD_INVAL が返却される。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iGetEndpointDescriptor(uint32_t ulIdIface,
								uint8_t ucEndptNo,
								const usb_endpoint_descriptor_t** pptOutEdesc,
								int16_t* psOutError)
{
	usb_endpoint_descriptor_t* ptEd;
	usbd_status err = USBD_NORMAL_COMPLETION;

	USB_TRACE_ENTER1(0, usb_USBD_iGetEndpointDescriptor, ulIdIface);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ulIdIface || !pptOutEdesc) {
		err = USBD_INVAL;
		goto end;
	}
	
	ptEd = usb_USBDInterfaceToEndpointDesc((usbd_interface_t*)ulIdIface, ucEndptNo);
	if(!ptEd) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBD_iGetEndpointDescriptor: invalid endpoint number(%u).\n",
						 ucEndptNo));
		goto end;
	}
	*pptOutEdesc = ptEd;
	
  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE1(0, usb_USBD_iGetEndpointDescriptor, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}


/* --------------------------------------------------------- */
/*                 ドライバの起動/終了                       */
/* --------------------------------------------------------- */
/*!
 * \brief USBドライバの初期化
 * \param psOutError	エラーコードとして usbd_status の値を返却する
 * \retval USB_OK		正常終了
 * \retval USB_NG		エラー終了
 * \attention クラスドライバを登録する前に呼び出す必要がある。
 *
 * USBドライバが使用するメモリの初期化や構造体の準備などを行なう。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iInitialize(int16_t* psOutError)
{
	usbd_status err;
	usb_softc_t* ptSc;
	usbd_bus_t* ptBus;
	
	USB_TRACE_ENTER(0, usb_USBD_iInitialize);
	
//	/* USB 割り込み初期化 */
//	usb_INTR_vInitialize();
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();

	/* USB 割り込み初期化 */
	usb_INTR_vInitialize();	//add090602
	
	/* クラスドライバ管理層初期化  todo いずれUSBDに含める予定 */
	usb_USBC_vInitialize();
	
	/* initialize memory manager */
	err = usb_USBDMemInit();
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBD_iInitialize: failed to initialize memory manager.\n"));
		err = USBD_NOMEM;
		goto end;
	}

	/* initialize bus control data structures */
	ptSc = usb_USBDAllocSoftc();
	ptBus = usb_USBDAllocBus();
	if(ptSc && ptBus) {
		memset(ptSc, 0, sizeof(*ptSc));
		ptSc->ptBus = ptBus;
		ptBus->ptSoftc = ptSc;
		usb_ptSOFTC = ptSc; /* static variable is a reference of softc */
	}
	else {
		err = USBD_NOMEM;
		if(ptSc) {
			usb_USBDDeallocSoftc(ptSc);
		}
		if(ptBus) {
			usb_USBDDeallocBus(ptBus);
		}
		goto end;
	}
	
	/* initialize class driver registry */
	SLIST_INIT(&ptSc->drvs);
	
#if defined(USBD_UTIL)
	usb_USBDCountInit();
#endif
	
	err = USBD_NORMAL_COMPLETION;
	
  end:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();
	
	USB_TRACE_LEAVE(0, usb_USBD_iInitialize);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief USBドライバの開始
 * \param psOutError	エラーコードとして usbd_status の値を返却する
 * \retval USB_OK		正常終了
 * \retval USB_NG		エラー終了
 * \attention usb_USBD_iStart() を呼び出す前に、利用するクラスドライバを登録しておく必要がある。
 *
 * USBドライバの処理を開始する。
 * OHCI ドライバの初期化を行ない、ルートハブデバイスの登録を行なう。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iStart(int16_t* psOutError)
{
	usbd_status err;
	usbd_bus_t* ptBus;
	usb_softc_t* ptSc = usb_ptSOFTC;

	USB_TRACE_ENTER(0, usb_USBD_iStart);
	
	/* USB割り込み禁止 */
	USB_DIS_INTR();
	
	if(!ptSc) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBD_iStart: USBD not initialized\n"));
		goto bad;
	}
	ptBus = ptSc->ptBus;
	
	err = usb_OHCI_iInitialize();
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBD_iStart: failed to initialize OHCI driver.\n"));
		goto bad;
	}

	/* 二重起動を防ぐ */
	if(ptSc->tPort.ptDevice) {
		DEBUG_ERROR_LOG(("usb_USBD_iStart: Bus driver already started!\n"));
		goto bad;
	}
	
	/* Root Hub のデバイス登録 */
	/* TODO XXX ptSc->tPort->usPower に値を設定しておく必要はない？
	   (roothubのsetConfigIndexのため) */
	err = usb_USBDNewDevice(ptBus, 0, USB_SPEED_FULL, &ptSc->tPort, 0);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBD_iStart: failed to add root-hub device.\n"));
		goto bad;
	}
	if(!ptSc->tPort.ptDevice->ptHub) {
		DEBUG_ERROR_LOG(("usb_USBD_iStart: root hub not found.\n"));
		err = USBD_INVAL;
		goto bad;
	}
	ptBus->ptRootHub = ptSc->tPort.ptDevice;
	goto good;
	
  bad:
	/* 資源解放 */
	usb_USBD_vFinalize();
	
  good:
	if(psOutError) {
		*psOutError = err;
	}
	
	/* USB割り込み許可 */
	USB_ENA_INTR();

	USB_TRACE_LEAVE1(0, usb_USBD_iStart, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief USBドライバを終了する
 *
 * USBドライバの利用している資源を解放し、終了する。
 *
 * \todo usb_USBD_iDisconnectPort() を利用することで、より簡単にデバイス開放することが
 *       できないだろうか。
 */
void
usb_USBD_vFinalize()
{
	usbd_bus_t* ptBus;
	usbd_device_t* ptDevice;
	usb_softc_t* ptSc = usb_ptSOFTC;
	
	USB_TRACE_ENTER(0, usb_USBD_vFinalize);

#if defined( USB_CTX_SWT )
	usb_INTR_vDisable();

	/* 待ちに入っている割り込み処理の中断 */
	usb_CTXSWT_vCancelWait();
#endif

	if(!ptSc) {
		goto end;
	}
	ptBus = ptSc->ptBus;
	
	/* 資源解放 */
	{
		uint8_t i, j;
		uint8_t ucNumIface;
		usbd_status err;
		usbd_interface_t* ptIface = NULL;
		usbd_pipe_t *ptPipe, *ptNextPipe;
		usbd_xfer_t* ptXfer;
		USBD_typeClassDriver *ptDriver, *ptNextDriver;
		
		/* free class drivers */
		for(ptDriver = (USBD_typeClassDriver*)(&ptSc->drvs)->first;
			ptDriver;
			ptDriver = ptNextDriver) {
			ptNextDriver = (USBD_typeClassDriver*)((usb_slist_entry_t*)ptDriver)->next;
			usb_USBD_vFreeClassDriver(ptDriver);
		}
		
		/* free devices on bus */
		for(i = 0; i < USBD_MAX_DEVICES; i++) {
			ptDevice = ptBus->pptDevices[i];
			if(ptDevice) {
				
				/* kill all pipes */
				ucNumIface = 0; /* 0 for NOT_CONFIGURED */
				err = usb_USBDGetInterfaceNumber(ptDevice, &ucNumIface);
				/* each interface (oftenly have only an interface) */
				for(j = 0; j < ucNumIface; j++) {
					err = usb_USBDDeviceToInterface(ptDevice, j, &ptIface);
					if(err) {
						DEBUG_ERROR_LOG(("usb_USBD_vFinalize: failed to get interface for index %u\n", j));
						continue;
					}
					if(!ptIface) {
						DEBUG_ERROR_LOG(("usb_USBD_vFinalize: huhh? iface #%u lost?\n", j));
						continue;
					}
					for(ptPipe = (usbd_pipe_t*)ptIface->pipes.first;
						ptPipe;
						ptPipe = ptNextPipe) {
						ptNextPipe = (usbd_pipe_t*)ptPipe->pipes.next;
						usb_USBDKillPipe(ptPipe);
					}
				}
				
				/* free device */
				usb_USBDFreeDevice(ptDevice);
				usb_USBDDeallocDevice(ptDevice);
				ptBus->pptDevices[i] = NULL;
			}
		}
		
		/* free bus */
		ptBus->ptRootHub = NULL;
		ptBus->ptSoftc = NULL;
		usb_USBDDeallocBus(ptBus);
	}
	usb_USBDDeallocSoftc(ptSc);
	usb_ptSOFTC = NULL;
	
	/* hcd の終了 */
	usb_OHCI_vFinalize();
	
	/* USB割り込み終了 */
	usb_INTR_vFinalize();

  end:
	USB_TRACE_LEAVE(0, usb_USBD_vFinalize);
}

/*!
 * \brief 回避不能エラー通知コールバックを登録
 * \param fpCallback	回避不能エラーの通知用コールバック関数
 * \param psOutError	エラーコードとして usbd_status の値を返却する
 * \retval USB_OK		正常終了
 * \retval USB_NG		エラー終了
 * \attention			USBDの初期化後でなければ、登録することはできない。
 *
 * USBドライバによる転送中にホスト・コントローラで回避不能エラーが発生した場合に
 * 呼び出される、通知コールバック関数を登録する。
 * USBD が未初期化(usb_USBD_iInitialized 呼び出し前)の場合にはエラーとなる。
 * psOutError に NULL を指定することにより、エラーコードの取得を省略可能。
 */
int16_t
usb_USBD_iRegisterUnrecovErrorCallback(USBD_typeCaughtUnrecovError fpCallback,
									   int16_t* psOutError)
{
	usbd_status err;
	usb_softc_t* const ptSoftc = usb_ptSOFTC;
	
	USB_TRACE_ENTER1(0, usb_USBD_iRegisterUnrecovErrorCallback, fpCallback);
	if(!ptSoftc) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBD_iRegisterUnrecovErrorCallback: USBD not initialized.\n"));
		goto end;
	}
	ptSoftc->fpUnrecovError = fpCallback;
	err = USBD_NORMAL_COMPLETION;

  end:
	if(psOutError) {
		*psOutError = err;
	}
	USB_TRACE_LEAVE1(0, usb_USBD_iRegisterUnrecovErrorCallback, err);
	return err == USBD_NORMAL_COMPLETION ? USB_OK : USB_NG;
}

/*!
 * \brief USB 関連の割り込みの確認を行なう
 *
 * USB関係の割り込みを確認する(ポーリング用)。
 * 割り込みが発見できた場合には、その処理が内部で呼び出される。
 */
void
usb_USBD_vIntr(void)
{
	const usb_softc_t* ptSc = usb_ptSOFTC;
	usbd_status err = USBD_NORMAL_COMPLETION;
	
	USB_TRACE_ENTER(0, usb_USBD_vIntr);
	if(!(ptSc && ptSc->ptBus->ptRootHub)) {
		/* 割り込みを処理できないときは、要因クリア */
		OHCI_WRITE( OHCI_INTERRUPT_STATUS, OHCI_INTR_MASK_ALL );
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBD_vIntr: USBD not started\n"));
		goto end;
	}

#if defined( USB_CTX_SWT )
	/* コンテキストスイッチ切り替え OHCI 割り込み */
	usb_CTXSWT_vChgIntrCtx( usb_OHCI_vIntr );
#else
#if(0) /* check without ctxswt */
#error usb_USBD_vIntr() does not work without the context-switching.
#else
	usb_OHCI_vIntr();
#endif
#endif

  end:
	USB_TRACE_LEAVE(0, usb_USBD_vIntr);
}


/* --------------------------------------------------------- */
/*                   HCD インターフェイス                    */
/* --------------------------------------------------------- */
/*!
 * \brief 転送完了のコールバック
 * \param ptXfer		完了した転送の xfer
 * \note HCD に対して公開されている関数。
 *
 * OHCI での転送が完了したときに HCD から呼び出される関数。
 * ptXfer には、転送の完了(正常終了, エラー終了)した転送を示す xfer が
 * 渡される。
 */
void
usb_USBD_vTransferDone(usbd_xfer_t* ptXfer)
{
	USB_TRACE_ENTER1(3, usb_USBD_vTransferDone, ptXfer);
	if(!ptXfer) {
		goto end;
	}
	usb_USBDTransferDone(ptXfer);

  end:
	USB_TRACE_LEAVE1(3, usb_USBD_vTransferDone, 0);
}

/*!
 * \brief Unrecoverable Error の通知
 *
 * ホスト・コントローラにより回避不能なエラー(Unrecoverable Error)が発生した
 * 場合にユーザ・アプリケーションへと通知するために呼び出す、HCD用USBDインタ
 * ーフェイス。
 * 通知されたアプリケーションは、再びUSBバス・ドライバの再初期化からやり直さ
 * なければならない。
 */
void
usb_USBD_vRaiseUnrecoverableError(void)
{
	const usb_softc_t* const ptSc = usb_ptSOFTC;

	USB_TRACE_ENTER(3, usb_USBD_vRaiseUnrecoverableError);
	/* 回避不能エラーの通知 */
	if(ptSc && ptSc->fpUnrecovError) {
		(*ptSc->fpUnrecovError)();
	}
	USB_TRACE_LEAVE(3, usb_USBD_vRaiseUnrecoverableError);
}


/* --------------------------------------------------------- */
/*!
 * \brief ユーザの転送完了コールバック
 * \param ptXfer		転送完了した xfer
 * \param status	完了した転送の状態
 *
 * USB_iIoPipe() での転送管理に利用しているコールバック。
 * ユーザに登録されているコールバック関数を呼び出す。
 */
static void
userTransferCompleted(usbd_xfer_t* ptXfer, usbd_status iStatus)
{
	usbd_pipe_t* ptPipe;
	void* pvBuffer;
	uint16_t usActLen;

	USB_TRACE_ENTER1(5, userTransferCompleted, ptXfer);
	if(!ptXfer) {
		goto end;
	}
	ptPipe = ptXfer->ptPipe;
	pvBuffer = ptXfer->pvBuffer;
	usActLen = ptXfer->usActLen;
	
	usb_USBDFreeXfer(ptXfer);
	/* ユーザのパイプ転送コールバックの呼び出し */
	if(ptPipe->tCallback.fpCallback) {
		ptPipe->tCallback.fpCallback(ptPipe->tCallback.ulArg, pvBuffer, usActLen, iStatus);
	}
	else {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("userTransferCompleted: ASSERT: internal error! no user callback\n");
#else
		;
#endif
	}
	
  end:
	USB_TRACE_LEAVE1(5, userTransferCompleted, iStatus);
}

/* --------------------------------------------------------- */
/*
 * Trace Level について
 *
 * 0   ユーザインターフェイス関数まで
 * 1   usbd 内の主要関数まで
 * 2   usbd 内の子細関数まで
 * 3   xfer による基本的な転送開始/完了まで
 * 4
 * 5   xfer による転送の子細なレベル
 */

/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
