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

/*! \file usb_usbd_application.h
	\brief Declaration of USB Host Driver USB BUS Driver Function

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */

#ifndef _USB_USBD_USBD_H_SEEN_APPLICATION_
#define _USB_USBD_USBD_H_SEEN_APPLICATION_

#include "usb_types.h"
#include "usb.h"


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
 * \brief USBD のエラーコード
 *
 * ホスト・コントローラ・ドライバとバス・ドライバ間の xfer に関するエラーや、
 * バス・ドライバ内部およびインターフェイスに利用される。
 */
typedef enum {
	USBD_NORMAL_COMPLETION = 0,		/*!< 正常終了 */
	/* errors */
	USBD_PENDING_REQUESTS,
	USBD_NOT_STARTED,				/*!< 転送が始まっていない */
	USBD_INVAL,						/*!< 不正なパラメータなど */
	USBD_NOMEM,						/*!< メモリ確保の失敗 */
	USBD_CANCELLED,					/*!< 転送のキャンセル */
	USBD_BAD_ADDRESS,				/*!< 不正なエンドポイントアドレス */
	USBD_IN_USE,					/*!< 既に利用されている */
	USBD_NO_ADDR,					/*!< 割り当てられるアドレスが存在しない */
	USBD_SET_ADDR_FAILED,			/*!< アドレスの割り当てに失敗 */
	USBD_NO_POWER,					/*!< 電源が供給されていない */
	USBD_TOO_DEEP,					/*!< ハブのネスト数が深すぎる */
	USBD_IOERROR,					/*!< 入出力エラー */
	USBD_NOT_CONFIGURED,			/*!< デバイスが usbd によってコンフィギュアされていない */
	USBD_TIMEOUT,					/*!< タイムアウト */
	USBD_SHORT_XFER,				/*!< SHORT XFER */
	USBD_STALLED,					/*!< ストール */
	USBD_INTERRUPTED,				/*!< */
	USBD_NO_CLASS_DRIVER			/*!< デバイスにアタッチできるクラスドライバが存在しない */
} usbd_status;

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

/*!
 * \brief USBデバイス接続通知コールバック登録構造体
 *
 * USBデバイスの接続状態を通知するコールバック関数を登録するための構造体。
 * 通知が必要ない場合には NULL を設定しておく。
 *
 * fpConnected は USBハブでポートが接続状態として認識されたことを通知する。
 * fpDisconnected は USBハブでポートが接続解除として認識されたことを通知する。
 * fpIdentified はUSBドライバにより、SET_ADDRESS～SET_CONFIGまでのデバイス・
 * イナミュレーションが完了したことを通知する。
 * blAttached は USBドライバからクラスドライバが割り当てられ、クラスドライバに
 * よる初期化が成功したことを通知する。
 * これらの関数の引数には通知IDが渡される。このIDを使う専用のインターフェイス
 * を呼び出すことで情報を取得することができる。
 *
 * fpIgnored は デバイスが接続されてから、デバイス・イナミュレーション～クラス
 * ドライバのアタッチの間で、USBドライバがそのデバイスを扱わずに無視することを
 * 通知する。
 * 引数には通知IDと、無視された理由となるエラーコードが渡される。
 *
 * \attention fpIgnored されたポートをもつハブ, あるいはさらに上流のハブごと
 *            デバイスの取り外しがおきた場合には、この fpIgnored されたデバイス
 *            の fpDisconnect は通知する術がないため、通知されない。
 * \attention fpIdentified は、バス・イナミュレーションの途中にある通知のため、
 *            バスドライバによるイナミュレーションのリトライにより、複数回よび
 *            だされる場合がある。
 */
typedef struct USBD_tagNotification {
	void	(*fpConnected)(uint32_t);				/*!< デバイス挿入の通知 */
	void	(*fpIdentified)(uint32_t);				/*!< デバイス識別成功の通知 */
	void	(*fpAttached)(uint32_t);				/*!< クラスドライバに登録成功の通知 */
	void	(*fpDisconnected)(uint32_t);			/*!< デバイス取外しの通知 */
	void	(*fpIgnored)(uint32_t, usbd_status);	/*!< デバイスを扱わない旨の通知 */
} USBD_typeNotification;




/* ********************************************************* */
/*                ユーザインターフェイス関数                 */
/* ********************************************************* */

/* ---------- 状態の通知 ---------- */
/* デバイス通知コールバックの登録 */
USB_EXPORT int16_t		usb_USBD_iSetNotifications(USBD_typeNotification* ptNotifications,
												   int16_t* psOutError);

/* 通知の詳細情報の取得 */
USB_EXPORT int16_t		usb_USBD_Notify_iGetPortNumber(uint32_t ulNotifyId, uint8_t* pucOutPortNo);
USB_EXPORT int16_t		usb_USBD_Notify_iGetSpeed(uint32_t ulNotifyId, int8_t* pcOutSpeed);
USB_EXPORT int16_t		usb_USBD_Notify_iGetDeviceAddress(uint32_t ulNotifyId,
														  uint8_t* pucOutAddress);
USB_EXPORT int16_t		usb_USBD_Notify_iGetDeviceDesc(uint32_t ulNotifyId,
													   const usb_device_descriptor_t** pptOutDdesc);
USB_EXPORT int16_t		usb_USBD_Notify_iGetProductName(uint32_t ulNotifyId,
														const int8_t** ppcOutProdName);
USB_EXPORT int16_t		usb_USBD_Notify_iGetManufacturerName(uint32_t ulNotifyId,
															 const int8_t** ppcOutManuName);
USB_EXPORT int16_t		usb_USBD_Notify_iGetPowerType(uint32_t ulNotifyId, int8_t* pcOutPowerType);
USB_EXPORT int16_t		usb_USBD_Notify_iGetMaxPower(uint32_t ulNotifyId, uint16_t* pcOutMaxPower);

/* ---------- その他 ---------- */
USB_EXPORT int16_t		usb_USBD_iInitialize(int16_t* psOutError);

/* USBドライバの開始 */
USB_EXPORT int16_t		usb_USBD_iStart(int16_t* psOutError);

/* USBドライバの終了 */
USB_EXPORT void			usb_USBD_vFinalize(void);

/* 回避不能エラー通知コールバックの登録 */
USB_EXPORT int16_t		usb_USBD_iRegisterUnrecovErrorCallback(USBD_typeCaughtUnrecovError fpCallback,
															   int16_t* psOutError);

/* USB割り込みの検知 */
USB_EXPORT void			usb_USBD_vIntr(void);


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
