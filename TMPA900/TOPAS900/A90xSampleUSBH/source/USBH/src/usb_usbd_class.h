/* ************************************************************************** */
/*
 * --------------------------------------------------------------------------
 *	Application			: USB Host Driver
 *	Micon				: TMP92xD28
 *	Development Tool	: -
 * 	Complie Option		: -
 *  Copyright(C) TOSHIBA CORPORATION 2007 All rights reserved
 * --------------------------------------------------------------------------
 */

/*! \file usb_usbd_class.h
	\brief Declaration of USB Host Driver USB BUS Driver Function

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */

#ifndef _USB_USBD_USBD_H_SEEN_CLASS_
#define _USB_USBD_USBD_H_SEEN_CLASS_

#include <usb_types.h>
#include <usb.h>
#include <usb_queue.h>
#include "usb_usbd.h"


/* ********************************************************* */
/*              Type Definitions & Constants                 */
/* ********************************************************* */
/*!
 * バス・ドライバのインターフェイスが正常動作したときの戻り値
 */
#define USB_OK  0

/*!
 * バス・ドライバのインターフェイスがエラー動作した時の戻り値
 */
#define USB_NG  (-1)


/* ---------- pipe 転送のフラグ ---------- */
#define USBD_SYNCHRONOUS			0x02 /* wait for completion */
#define USBD_SHORT_XFER_OK			0x04 /* allow short reads */
#define USBD_FORCE_SHORT_XFER		0x08 /* force last short packet on write */

/* ---------- その他の定数 --------------- */
/* usb_USBD_Notify_iGetPowerType() の出力値 */
#define USBD_BUS_POWERED			  0  /*!< バスパワー */
#define USBD_SELF_POWERED			  1  /*!< セルフパワー */

/* usb_USBD_Notify_iGetSpeed() の出力値 */
#define USBD_LOW_SPEED				0	/*!< ロースピード */
#define USBD_FULL_SPEED				1	/*!< フルスピード */


/*!
 * \brief クラスドライバ管理用構造体
 *
 * クラスドライバ管理を行なう構造体。
 * blAttachDeviceFn には、デバイスが接続されたときに呼び出される関数を、
 * blDetachDeviceFn には、デバイスが抜かれたときに呼び出されるの関数を、
 * それぞれコールバック関数として登録する。
 * ulArg には、それぞれのコールバック関数が呼び出されるとき、コールバックの
 * 引数に渡される値を指定する。
 * queue メンバ, ulDeviceId メンバは、USBドライバ内部で使用するため、
 * クラスドライバ側で変更してはならない。
 */
typedef struct USBD_tagClassDriver {
	usb_slist_entry_t	queue; /*!< USB_tagClassDriverキューのエントリ */
	uint32_t			ulDeviceId; /*!< クラスドライバに割り当てられたデバイスID */
	uint32_t			ulArg; /*!< コールバック関数に渡される引数 */
	bool			(*blAttachDeviceFn)(uint32_t ulIdDev, uint32_t ulArg);	/* デバイス接続時コールバック関数 */
	void			(*vDetachDeviceFn)(uint32_t ulArg);						/* デバイス解除時コールバック関数 */
} USBD_typeClassDriver;

/*!
 * \brief ユーザ通信終了コールバック関数型
 *
 * usb_USBD_IoPipe() によるユーザ通信が終了した時に呼び出される、
 * コールバック関数の型定義。
 * ulArg はパイプのオープン時に指定した引数、pvBuf は転送バッファ、
 * ulLen は実際の転送長、sStatus は usbd_status の値で転送エラーコードが
 * それぞれ渡される。
 */
typedef void (*USBD_typeCommFinished)(uint32_t ulArg, void* pvBuf, uint16_t usLen, int16_t sStatus);

/*!
 * \brief 回避不能エラーの通知コールバック関数型
 *
 * USBドライバ動作中、ホスト・コントローラにおいて、回避不能エラーが
 * 発生した場合に呼び出される、回避不能エラーを通知するコールバック関数
 * の型定義。
 */
typedef void (*USBD_typeCaughtUnrecovError)(void);



/* ********************************************************* */
/*                ユーザインターフェイス関数                 */
/* ********************************************************* */

/* ---------- クラスドライバ ---------- */
USB_EXPORT USBD_typeClassDriver*	usb_USBD_ptAllocClassDriver(void);
USB_EXPORT void			usb_USBD_vFreeClassDriver(USBD_typeClassDriver* ptClsDrv);

USB_EXPORT int16_t		usb_USBD_iRegistClassDriver(USBD_typeClassDriver* ptClsDrv,
													int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iRemoveClassDriver(USBD_typeClassDriver* ptClsDrv,
													int16_t* psOutError);


/* ---------- デバイスなどのオープン/クローズ ---------- */
USB_EXPORT int16_t		usb_USBD_iOpenDevice(uint32_t ulDeviceId, int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iCloseDevice(uint32_t ulDeviceId, int16_t* psOutError);

USB_EXPORT int16_t		usb_USBD_iOpenInterface(uint32_t ulDeviceId,
												uint8_t ucIfaceNo,
												uint32_t* pulOutIfaceId,
												int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iCloseInterface(uint32_t ulIfaceId, int16_t* psOutError);

USB_EXPORT int16_t		usb_USBD_iOpenPipe(uint32_t ulIfaceId,
										   usb_endpoint_descriptor_t* ptEdesc,
										   USBD_typeCommFinished fpFinished,
										   uint32_t ulArg,
										   uint32_t* pulOutPipeId,
										   int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iClosePipe(uint32_t ulPipeId, int16_t* psOutError);

/* ---------- 通信 ---------- */
USB_EXPORT int16_t		usb_USBD_iIoPipe(uint32_t ulPipeId,
										 void* pvBuffer,
										 uint16_t usLen,
										 uint16_t usFlags,
										 int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iCancelIoDevice(uint32_t ulDeviceId, int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iCancelIoInterface(uint32_t ulIfaceId, int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iCancelIoPipe(uint32_t ulPipeId, int16_t* psOutError);

USB_EXPORT int16_t		usb_USBD_iDeviceRequest(uint32_t ulDeviceId,
												usb_device_request_t* ptRequest, 
												void* pvInOutBuf,
												int16_t* psOutError);

USB_EXPORT int16_t		usb_USBD_iClearFeatureEndpoint(uint32_t ulPipeId, int16_t* psOutError);

/* ---------- デバイスの切断/再接続 ---------- */
/* 以下 ポートの再接続を試みるためのインターフェイス (試作状態) */
USB_EXPORT int16_t		usb_USBD_iGetPortId(uint32_t ulIdDevice,
											uint32_t* pulOutIdPort,
											int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iDisconnectPort(uint32_t ulIdPort, int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iConnectPort(uint32_t ulIdPort, int16_t* psOutError);

/* ---------- デスクリプタの取得 ---------- */
USB_EXPORT int16_t		usb_USBD_iGetDeviceDescriptor(uint32_t ulIdDev,
													  const usb_device_descriptor_t** pptOutDdesc,
													  int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iGetConfigDescriptor(uint32_t ulIdDev,
													  int16_t sCfgIndex,
													  const usb_config_descriptor_t** pptCfgDesc,
													  int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iGetInterfaceDescriptor(uint32_t ulIdDev,
														 uint8_t ucIfaceNo,
														 const usb_interface_descriptor_t** pptOutIdesc,
														 int16_t* psOutError);
USB_EXPORT int16_t		usb_USBD_iGetEndpointDescriptor(uint32_t ulIdIface,
														uint8_t ucEndptNo,
														const usb_endpoint_descriptor_t** pptOutEdesc,
														int16_t* psOutError);

#endif /* _USB_USBD_USBD_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
