/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 * @ingroup	usbd_mem
 */

/* $Id: usb_usbd_mem.c 41 2014-01-27 14:05:18Z danielru $ */

#include "usb_config.h"
#include <string.h>	/* memset() */
#include <usb.h>
#include <usb_queue.h>
#include "usb_usbd_mem.h"
#include "usb_uhub.h"
#include "util/usb_dbg.h"


/* ========================================================= */
/*                        Constants                          */
/* ========================================================= */
#define	USBD_MAX_IFACES			(USB_MAX_IFACES)			/* max interfaces per device */
#define USBD_MAX_ENDPOINTS		(USB_MAX_ENDPOINTS)			/* max endpoints per device */
#define USBD_MAX_HUBS			((USB_MAX_HUBS) + 1)		/* 1 is root hub */
#define USBD_MAX_PORTS			(USB_MAX_HUB_PORTS)			/* max ports per hub */
#define USBD_MAX_NEST_REQ		(4)	/* max number of nesting device requests */

#define USBD_MAX_TINYS			(4 * ((USB_MAX_HUBS) + 1))	/* num of tiny buffers */

#define USBD_MAX_CLASS_DRIVERS	(USB_MAX_CLASS_DRIVERS)


#define	USBD_MEM_CDESC_MAX_SIZE		(sizeof(usb_config_descriptor_t) + \
									 (sizeof(usb_interface_descriptor_t) + \
									 (sizeof(usb_endpoint_descriptor_t) * (USBD_MAX_ENDPOINTS))) \
									 * (USBD_MAX_IFACES))
#define USBD_MEM_HUB_MAX_SIZE		(sizeof(usbd_hub_t) + (sizeof(usbd_port_t) * (USBD_MAX_PORTS - 1)))


#define __FUNCTION__		"" /* dummy */


/* ========================================================= */
/*                     Type Definitions                      */
/* ========================================================= */

/* --------------------------------------------------------- */
/*!
 * デバイス関連のバッファ
 */
struct usbd_mem_device {
	usb_slist_entry_t		ent;								/*!< リンクリスト用エントリ */
	usbd_device_t			tDevice;							/*!< usbd_device_t 型のバッファ */
	int8_t					pcCdesc[USBD_MEM_CDESC_MAX_SIZE];	/*!< cdesc用のバッファ */
	usbd_interface_t		ptIfaces[USBD_MAX_IFACES];			/*!< インターフェイス用のバッファ */
	usbd_endpoint_t			ptEndpoints[USBD_MAX_ENDPOINTS];	/*!< エンドポイント用のバッファ */
	uint8_t					ucUse;								/*!< 各バッファの使用状態フラグ */
#define CDESC_IN_USE		(uint8_t)(1 << 0)
#define IFACE_IN_USE		(uint8_t)(1 << 1)
#define ENDPT_IN_USE		(uint8_t)(1 << 2)
};

/*!
 * \brief usbd_device_t 型からの usbd_mem_device のアドレスを取得
 * \param d		usbd_device_t 型のポインタ
 * \return		引数 d の usbd_device_t 型が含まれる管理ノード usbd_mem_device 型のアドレス
 *
 * usbd_device_t 型のポインタより、このバッファを管理/格納しているノード(コンテナ)
 * のアドレスを算出する。
 */
#define DEV2ENT(d)		((struct usbd_mem_device*)((uint8_t*)(d) - sizeof(usb_slist_entry_t)))

/* --------------------------------------------------------- */
/*!
 * デバイスリクエストのバッファノード
 */
struct usbd_mem_devreq {
	usb_slist_entry_t		ent;							/*!< リンクリスト用エントリ */
	usb_device_request_t	tReq;							/*!< デバイスリクエスト用バッファ */
};

/*!
 * \brief usb_device_request_t 型からの usbd_mem_devreq のアドレスを取得
 * \param d		usb_device_request_t 型のポインタ
 * \return		引数 d の usb_device_request_t 型が含まれる管理ノード usbd_mem_devreq 型のアドレス
 *
 * usb_device_request_t 型のポインタより、このバッファを管理/格納しているノード(コンテナ)
 * のアドレスを算出する。
 */
#define REQ2ENT(d)		((struct usbd_mem_devreq*)((uint8_t*)(d) - sizeof(usb_slist_entry_t)))

/* --------------------------------------------------------- */
/*!
 * ハブ構造体のバッファノード
 */
struct usbd_mem_hub {
	usb_slist_entry_t		ent;							/*!< リンクリスト用のエントリ */
	int8_t					pcHub[USBD_MEM_HUB_MAX_SIZE];	/*!< usbd_hub_t型のバッファ */
};

/*!
 * \brief usbd_hub_t 型からの usbd_mem_hub のアドレスを取得
 * \param h		usbd_hub_t 型のポインタ
 * \return		引数 h の usbd_device_t 型が含まれる管理ノード usbd_mem_hub 型のアドレス
 *
 * usbd_hub_t 型(int8_t)のポインタより、このバッファを管理/格納しているノード(コンテナ)
 * のアドレスを算出する。
 */
#define HUB2ENT(h)		((struct usbd_mem_hub*)((uint8_t*)(h) - sizeof(usb_slist_entry_t)))

/* --------------------------------------------------------- */
/*!
 * ハブドライバ用変数のバッファノード
 */
struct usbd_mem_hubsoftc {
	usb_slist_entry_t		ent;						/*!< リンクリスト用のエントリ */
	uhub_softc_t			tHubsoftc;					/*!< ハブドライバ用変数のバッファ */
};

/*!
 * \brief uhub_softc_t 型からの usbd_mem_hubsoftc のアドレスを取得
 * \param s		uhub_softc_t 型のポインタ
 * \return		引数 s の uhub_softc_t 型が含まれる管理ノード usbd_mem_hubsoftc 型のアドレス
 *
 * uhub_softc_t 型のポインタより、このバッファを管理/格納しているノード(コンテナ)
 * のアドレスを算出する。
 */
#define HSC2ENT(s)		((struct usbd_mem_hub*)((uint8_t*)(s) - sizeof(usb_slist_entry_t)))

/* --------------------------------------------------------- */
/*!
 * ハブデスクリプタのバッファノード
 */
struct usbd_mem_hubdesc {
	usb_slist_entry_t		ent;						/*!< リンクリスト用のエントリ */
	usb_hub_descriptor_t	tHubdesc;					/*!< ハブデスクリプタのバッファ */
};

/*!
 * \brief usb_hub_descriptor_t 型からの usbd_mem_hubdesc のアドレスを取得
 * \param s		usb_hub_descriptor_t 型のポインタ
 * \return		引数 s の usb_hubdescriptor_t 型が含まれる管理ノード usbd_mem_hubdesc 型のアドレス
 *
 * usb_hub_descriptor_t 型のポインタより、このバッファを管理/格納しているノード(コンテナ)
 * のアドレスを算出する。
 */
#define HDESC2ENT(s)	((struct usbd_mem_hubdesc*)((uint8_t*)(s) - sizeof(usb_slist_entry_t)))

/* --------------------------------------------------------- */
/*!
 * usb_status_t, usb_port_status_t 型のバッファノード
 */
struct usbd_mem_tiny {
	usb_slist_entry_t		ent;						/*!< リンクリスト用のエントリ */
	union {
		uint32_t			ulValue;
		usb_status_t		tStatus;
		usb_port_status_t	tPortStatus;
	} tBufs;											/*!< バッファ */
};

/* --------------------------------------------------------- */
/*!
 * USBD_typeClassDriver 型のバッファノード
 */
struct usbd_mem_class_driver {
	usb_slist_entry_t		ent;						/*!< リンクリスト用のエントリ */
	USBD_typeClassDriver	tDrv;						/*!< USBD_typeClassDriverのバッファ */
};

/*!
 * \brief USBD_typeClassDriver 型からの usb_mem_class_driver のアドレスを取得
 * \param s		USBD_typeClassDriver 型のポインタ
 * \return		引数 s の USBD_typeClassDriver 型が含まれる管理ノード
 *				usbd_mem_class_driver 型のアドレス
 *
 * USBD_typeClassDriver 型のポインタより、このバッファを管理/格納しているノード(コンテナ)
 * のアドレスを算出する。
 */
#define DRV2ENT(d)		((struct usbd_mem_class_driver*)((uint8_t*)(d) - sizeof(usb_slist_entry_t)))


/* --------------------------------------------------------- */
#if defined(USBD_UTIL)
/*
 * メモリ管理機構の診断用
 */
struct usbd_mem_diagnose {
	uint16_t	usLeakCnt;	/* 総合リークポインタ数 */
	uint8_t		ucDev;
	uint8_t		ucCdesc;
	uint8_t		ucIface;
	uint8_t		ucEd;
	uint8_t		ucHub;
	uint8_t		ucHubsoftc;
	uint8_t		ucHubdesc;
	uint8_t		ucTinyBuf;
	uint8_t		ucDevreq;
	uint8_t		ucClsdrv;
};
#endif

/* --------------------------------------------------------- */
/*!
 * USBバス・ドライバで利用する各種バッファ
 */
struct usbd_mems {
	/* device */
	struct usbd_mem_device		ptMemDevice[USBD_MAX_DEVICES];	/*!< デバイス関連 */
	
	/* hub */
	struct usbd_mem_hub			ptMemHub[USBD_MAX_HUBS];		/*!< ハブ管理構造 */
	struct usbd_mem_hubsoftc	ptMemHubsoftc[USBD_MAX_HUBS];	/*!< ハブ・クラスドライバ */
	
	/* bus */
	usbd_bus_t					tMemBus;						/*!< バス管理構造 */
	
	/* usbd softc */
	usb_softc_t					tMemSoftc;						/*!< バス・ドライバ */

	struct usbd_mem_devreq		ptMemDevreq[USBD_MAX_NEST_REQ];	/*!< デバイス・リクエスト */
	struct usbd_mem_hubdesc		ptMemHubdesc[USBD_MAX_HUBS];	/*!< ハブ・デスクリプタ */
	struct usbd_mem_tiny		ptMemTiny[USBD_MAX_TINYS];		/*!< その他テンポラリ */
	
	/* class driver */
	struct usbd_mem_class_driver	ptMemDrv[USBD_MAX_CLASS_DRIVERS];	/*!< クラス・ドライバ */
	
	usb_string_descriptor_t		tMemSdesc;						/*!< 文字列デスクリプタ */

#if defined(USBD_UTIL)
	struct usbd_mem_diagnose	tMemDiag;						/*!< 診断用 */
#endif
};

/*!
 * USBバス・ドライバで利用する各種バッファの管理構造
 */
struct usbd_mem_ctrl {
	usb_slist_head_t			device;			/*!< デバイス関連 */
	usb_slist_head_t			hub;			/*!< ハブ管理構造 */
	usb_slist_head_t			hubsoftc;		/*!< ハブ・クラスドライバ */
	
	usbd_bus_t*					ptBus;			/*!< バス管理構造 */
	usb_softc_t*				ptSoftc;		/*!< バス・ドライバ */

	usb_slist_head_t			devreq;			/*!< デバイス・リクエスト */
	usb_slist_head_t			hubdesc;		/*!< ハブ・デスクリプタ */
	usb_slist_head_t			tiny;			/*!< その他テンポラリ */
	
	usb_slist_head_t			drv;			/*!< クラス・ドライバ */
	
	usb_string_descriptor_t*	ptSdesc;		/*!< 文字列デスクリプタ */
};


/* ========================================================= */
/*                     Local Variables                       */
/* ========================================================= */
#pragma section = "HC_RAM_USBDMEM"

/*!
 * USBドライバで利用する各種バッファ群
 */
static struct usbd_mems		tBuf @ "HC_RAM_USBDMEM";

/*!
 * USBドライバで利用する各種バッファの管理用変数群
 */
static struct usbd_mem_ctrl	tMemCtl @ "HC_RAM_USBDMEM";


/* ========================================================= */
/*                  Function Definitions                     */
/* ========================================================= */
/*!
 * \brief バッファを０クリアする
 * \param b		クリアするバッファのアドレス
 * \param len	クリアするバイト数
 */
static __inline void
bzero(void* b, size_t len)
{
	memset(b, 0, len);
}


/*!
 * \brief メモリ管理機能の初期化
 * \retval	0	正常に初期化が完了
 * \retval	!0	初期化に失敗(configパラメータが不正)
 *
 * USBドライバで利用するメモリの管理機構の初期化を行なう。
 * 初期化において行なうメモリの確保量は、コンフィグレーション値に依存する。
 *
 * \todo コンフィグレーション値とバッファ量の関係は別途ドキュメントを作成する。
 */
int16_t
usb_USBDMemInit(void)
{
	int16_t i;

	/* initialize buffers */
	memset(&tBuf, 0, sizeof(tBuf));
	memset(&tMemCtl, 0, sizeof(tMemCtl));

	/* initialize empty node queues */
	for(i = 0; i < USBD_MAX_DEVICES; i++) {
		SLIST_INSERT_TAIL(&tMemCtl.device, &tBuf.ptMemDevice[i]);
	}
	for(i = 0; i < USBD_MAX_HUBS; i++) {
		SLIST_INSERT_TAIL(&tMemCtl.hub, &tBuf.ptMemHub[i]);
		SLIST_INSERT_TAIL(&tMemCtl.hubsoftc, &tBuf.ptMemHubsoftc[i]);
	}
	tMemCtl.ptBus = &tBuf.tMemBus;		/* singleton */
	tMemCtl.ptSoftc = &tBuf.tMemSoftc;	/* singleton */

	for(i = 0; i < USBD_MAX_NEST_REQ; i++) {
		SLIST_INSERT_TAIL(&tMemCtl.devreq, &tBuf.ptMemDevreq[i]);
	}
	for(i = 0; i < USBD_MAX_HUBS; i++) {
		SLIST_INSERT_TAIL(&tMemCtl.hubdesc, &tBuf.ptMemHubdesc[i]);
	}
	for(i = 0; i < USBD_MAX_TINYS; i++) {
		SLIST_INSERT_TAIL(&tMemCtl.tiny, &tBuf.ptMemTiny[i]);
	}
	for(i = 0; i < USBD_MAX_CLASS_DRIVERS; i++) {
		SLIST_INSERT_TAIL(&tMemCtl.drv, &tBuf.ptMemDrv[i]);
	}
	tMemCtl.ptSdesc = &tBuf.tMemSdesc;

	return 0;
}

/*!
 * \brief usbd_device_t 型バッファを取得する
 * \return usbd_device_t 型のバッファアドレス。取得できなかった場合には NULL を返却する。
 *
 * メモリ管理機構から、usbd_device_t 構造体のバッファを取得し返却する。
 * 取得できなかった場合には、NULL を返却する。
 */
usbd_device_t*
usb_USBDAllocDevice(void)
{
	usb_slist_entry_t* ptEntry;
	usbd_device_t* ptDev;
	
	ptEntry = SLIST_REMOVE_HEAD(&tMemCtl.device);
	if(!ptEntry) {
		DEBUG_ERROR_CALL( 0, "failed to alloc DEVICE\n", NULL);
	}
	ptDev = ptEntry ? &((struct usbd_mem_device*)ptEntry)->tDevice : NULL;
	if(ptDev) {
		bzero(ptDev, sizeof(*ptDev));
	}
	return ptDev;
}

/*!
 * \brief usbd_device_t 型バッファを解放解放する
 * \param ptDev		usbd_device_t 型バッファのアドレス
 *
 * ptDev で指定した usbd_device_t 型のバッファをメモリ管理機構に解放する。
 */
void
usb_USBDDeallocDevice(usbd_device_t* ptDev)
{
	usb_slist_entry_t* ptEntry;
	usb_slist_entry_t* ptNode;
	uint8_t i;

	if(!ptDev)
		goto bad;
	ptEntry = (usb_slist_entry_t*)DEV2ENT(ptDev);
	SLIST_FOREACH(ptNode, usb_slist_entry_t, &tMemCtl.device) {
		if(ptNode == ptEntry) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptDev);
#endif
			DEBUG_ERROR_CALL( 3, "double free DEVICE\n", NULL);
			goto bad;
		}
	}

	/* 解放アドレスの正当性チェック */
	for(i = 0; i < USBD_MAX_DEVICES; i++) {
		if(&tBuf.ptMemDevice[i] == (struct usbd_mem_device*)ptEntry)
			goto ok;
	}
	DEBUG_ERROR_CALL( 3, "DEVICE free invalid address\n", NULL);
	goto bad;

  ok:
#if defined(USBD_UTIL)
	/* USBD_UTIL メモリのリークチェック用 */
	{
		struct usbd_mem_device* ptMemDev = (struct usbd_mem_device*)ptEntry;
		
		if(ptMemDev->ucUse & CDESC_IN_USE) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: cdesc is used, but device is dealloced.\n", __FUNCTION__);
#endif
			DEBUG_ERROR_CALL( 3, "CDESC is not dealloced\n", NULL);
			tBuf.tMemDiag.usLeakCnt++;
			tBuf.tMemDiag.ucCdesc++;
		}
		if(ptMemDev->ucUse & IFACE_IN_USE) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: iface is used, but device is dealloced.\n", __FUNCTION__);
#endif
			DEBUG_ERROR_CALL( 3, "IFACE is not dealloced\n", NULL);
			tBuf.tMemDiag.usLeakCnt++;
			tBuf.tMemDiag.ucIface++;
		}
		if(ptMemDev->ucUse & ENDPT_IN_USE) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: endpoint is used, but device is dealloced.\n", __FUNCTION__);
#endif
			DEBUG_ERROR_CALL( 3, "ED is not dealloced\n", NULL);
			tBuf.tMemDiag.usLeakCnt++;
			tBuf.tMemDiag.ucEd++;
		}
	}
#endif

	SLIST_INSERT_TAIL(&tMemCtl.device, ptEntry);
  bad:
	return;
}

/*!
 * \brief コンフィグ・デスクリプタ用バッファを取得する
 * \param	ptDev		コンフィグ・デスクリプタ・バッファを取得するデバイス
 * \param	size		取得するコンフィグ・デスクリプタ・バッファのサイズ
 * \return 要求されたコンフィグ・デスクリプタ用のバッファ。取得できなかった場合には NULL を返す。
 *
 * メモリ管理機構から、ptDev で指定したデバイス用に、size バイト分のコンフィグレーション・
 * デスクリプタ用バッファを取得して返却する。取得できなかった場合は NULL を返す。
 * コンフィグレーション・デスクリプタの取得可能な数は、ptDev で指定したデバイスに対して１つのみ,
 * 取得可能な最大サイズは USBD_MEM_CDESC_MAX_SIZE で指定されたサイズとなる。
 *
 * \note コンフィグ・デスクリプタには、１つ以上のインターフェイス・デスクリプタが
 *       後続しているので、USBD_MEM_CDESC_MAX_SIZE は、それを考慮したサイズでなければいけない。
 */
usb_config_descriptor_t*
usb_USBDAllocCDesc(usbd_device_t* ptDev, size_t size)
{
	struct usbd_mem_device* ptMemDev;
	usb_config_descriptor_t* ptCdesc = NULL;

	if(!ptDev) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: invalid param\n", __FUNCTION__);
#endif
		goto end;
	}
	if(size <= USBD_MEM_CDESC_MAX_SIZE) {
		ptMemDev = DEV2ENT(ptDev);
		if(!(ptMemDev->ucUse & CDESC_IN_USE)) {
			ptMemDev->ucUse |= CDESC_IN_USE;
			ptCdesc = (usb_config_descriptor_t*)ptMemDev->pcCdesc;
			goto end;
		}
		else {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: no memory\n", __FUNCTION__);
#endif
			goto end;
		}
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("%s: too large size\n", __FUNCTION__);
#endif
	
  end:
	if(!ptCdesc) {
		DEBUG_ERROR_CALL( 0, "failed to alloc CDESC\n", NULL);
	}
	else {
		bzero(ptCdesc, USBD_MEM_CDESC_MAX_SIZE);
	}
	return ptCdesc;
}

/*!
 * \brief コンフィグ・デスクリプタ・バッファを解放する
 * \param	ptDev		コンフィグ・デスクリプタ・バッファを返却するデバイス
 * \param	ptCdesc		返却するコンフィグ・デスクリプタ・バッファ
 *
 * メモリ管理機構に、ptDev で指定したデバイスがもつ、ptCdesc で指定するコンフィグ
 * レーション・デスクリプタのバッファを返却する。
 */
void
usb_USBDDeallocCDesc(usbd_device_t* ptDev, usb_config_descriptor_t* ptCdesc)
{
	struct usbd_mem_device* ptMemDev;
	usb_slist_entry_t* ptEntry;

	if(!ptDev || !ptCdesc)
		goto end;
	ptMemDev = DEV2ENT(ptDev);
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.device) {
		if(ptEntry == (usb_slist_entry_t*)ptMemDev) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: no parent.\n", __FUNCTION__);
#endif
			DEBUG_ERROR_CALL( 3, "no parent of CDESC\n", NULL);
			goto end; /* device already free */
		}
	}
	
	if(ptMemDev->pcCdesc != (int8_t*)ptCdesc) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: invalid address\n", __FUNCTION__);
#endif
		DEBUG_ERROR_CALL( 3, "invalid address\n", NULL);
		goto end;
	}
	if(ptMemDev->ucUse & CDESC_IN_USE) {
		ptMemDev->ucUse ^= CDESC_IN_USE;
		goto end;
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptCdesc);
#endif
	DEBUG_ERROR_CALL( 3, "double free CDESC\n", NULL);
	
  end:
	return;
}

/*!
 * \brief インターフェイス管理構造バッファを取得する
 * \param ptDev	インターフェイス管理構造バッファを取得するデバイス
 * \param sNumIfaces 取得するインターフェイスの数
 * \return 取得したインターフェイス管理構造バッファのアドレス。取得できない場合には NULL を返す。
 *
 * メモリ管理機構から、ptDev で指定するデバイスに対して、sNumIfaces 個分のインター
 * フェイス管理構造用バッファを配列として取得して返す。取得できない場合には NULL を返す。
 */
usbd_interface_t*
usb_USBDAllocIfaces(usbd_device_t* ptDev, int16_t sNumIfaces)
{
	struct usbd_mem_device* ptMemDev;
	usbd_interface_t* ptIface = NULL;

	if(!ptDev) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: invalid param\n", __FUNCTION__);
#endif
		goto end;
	}
	if(sNumIfaces <= USBD_MAX_IFACES) {
		ptMemDev = DEV2ENT(ptDev);
		if(!(ptMemDev->ucUse & IFACE_IN_USE)) {
			ptMemDev->ucUse |= IFACE_IN_USE;
			ptIface = ptMemDev->ptIfaces;
			goto end;
		}
		else {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: no memory\n", __FUNCTION__);
#endif
			goto end;
		}
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("%s: too large size\n", __FUNCTION__);
#endif

  end:
	if(!ptIface) {
		DEBUG_ERROR_CALL( 0, "failed to alloc IFACE\n", NULL);
	}
	else {
		bzero(ptIface, sizeof(*ptIface) * USBD_MAX_IFACES);
	}
	return ptIface;
}

/*!
 * \brief インターフェイス管理構造バッファを解放する
 * \param ptDev		インターフェイス管理構造バッファを解放するデバイス
 * \param ptIfaces	解放するインターフェイス管理構造バッファ
 *
 * メモリ管理機構に、ptDev で指定したデバイスの ptIfaces で指定するインターフェイス管理
 * 構造バッファを解放する。
 */
void
usb_USBDDeallocIfaces(usbd_device_t* ptDev, usbd_interface_t* ptIface)
{
	struct usbd_mem_device* ptMemDev;
	usb_slist_entry_t* ptEntry;

	if(!ptDev || !ptIface)
		goto end;
	ptMemDev = DEV2ENT(ptDev);
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.device) {
		if(ptEntry == (usb_slist_entry_t*)ptMemDev) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: no parent.\n", __FUNCTION__);
#endif
			DEBUG_ERROR_CALL( 3, "no parent of IFACE\n", NULL);
			goto end; /* device already free */
		}
	}

	if(ptMemDev->ptIfaces != ptIface) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: invalid address\n", __FUNCTION__);
#endif
		DEBUG_ERROR_CALL( 3, "invalid address\n", NULL);
		goto end;
	}
	if(ptMemDev->ucUse & IFACE_IN_USE) {
		ptMemDev->ucUse ^= IFACE_IN_USE;
		goto end;
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptIface);
#endif
	DEBUG_ERROR_CALL( 3, "double free IFACE\n", NULL);

  end:
	return;
}

/*!
 * \brief エンドポイント管理構造バッファを取得する
 * \param ptDev		エンドポイント管理構造バッファを取得するデバイス
 * \param sNumEds	取得するエンドポイント管理構造数
 * \return 取得したエンドポイント管理構造バッファのアドレス。
 *		   取得できなかった場合には NULL を返す。
 *
 * メモリ管理機構から、ptDev で指定したデバイスに、sNumEds 個分のエンドポイント
 * 管理構造バッファの配列を取得する。取得できなかった場合には、NULL を返す。
 */
usbd_endpoint_t*
usb_USBDAllocEndpoints(usbd_device_t* ptDev, int16_t sNumEds)
{
	struct usbd_mem_device* ptMemDev;
	usbd_endpoint_t* ptEd = NULL;

	if(!ptDev) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: illegal param\n", __FUNCTION__);
#endif
		goto end;
	}
	if(0 < sNumEds && sNumEds <= USBD_MAX_ENDPOINTS) {
		ptMemDev = DEV2ENT(ptDev);
		if(!(ptMemDev->ucUse & ENDPT_IN_USE)) {
			ptMemDev->ucUse |= ENDPT_IN_USE;
			ptEd = ptMemDev->ptEndpoints;
			goto end;
		}
		else {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: no memory\n", __FUNCTION__);
#endif
			goto end;
		}
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("%s: too large size\n", __FUNCTION__);
#endif

  end:
	if(!ptEd) {
		DEBUG_ERROR_CALL( 0, "failed to alloc ED\n", NULL);
	}
	else {
		bzero(ptEd, sizeof(*ptEd) * sNumEds);
	}
	return ptEd;
}

/*!
 * \brief エンドポイント管理構造バッファを解放する
 * \param ptDev		エンドポイント管理構造バッファを解放するデバイス
 * \param ptEd		解放するエンドポイント管理構造バッファ
 *
 * メモリ管理機構に、ptDev で指定したデバイスのエンドポイント管理構造バッファ ptEd を解放する。
 */
void
usb_USBDDeallocEndpoints(usbd_device_t*ptDev, usbd_endpoint_t* ptEd)
{
	struct usbd_mem_device* ptMemDev;
	usb_slist_entry_t* ptEntry;

	if(!ptDev || !ptEd)
		goto end;
	ptMemDev = DEV2ENT(ptDev);
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.device) {
		if(ptEntry == (usb_slist_entry_t*)ptMemDev) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: no parent.\n", __FUNCTION__);
#endif
			DEBUG_ERROR_CALL( 3, "no parent of ED\n", NULL);
			goto end; /* device already free */
		}
	}
	
	if(ptMemDev->ptEndpoints != ptEd) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: invalid address\n", __FUNCTION__);
#endif
		DEBUG_ERROR_CALL( 3, "invalid address\n", NULL);
		goto end;
	}
	if(ptMemDev->ucUse & ENDPT_IN_USE) {
		ptMemDev->ucUse ^= ENDPT_IN_USE;
		goto end;
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptEd);
#endif
	DEBUG_ERROR_CALL( 3, "double free ED\n", NULL);

  end:
	return;
}


/*!
 * \brief ハブ管理構造バッファを取得する
 * \param size		取得するハブ管理構造バッファのサイズ
 * \return 取得したハブ管理構造バッファのアドレス。取得できなかった場合には NULL を返す。
 *
 * メモリ管理機構から、ハブ管理構造バッファを size バイト分取得して返す。
 * 取得できなかった場合には、NULL を返却する。
 */
usbd_hub_t*
usb_USBDAllocHub(size_t size)
{
	usb_slist_entry_t* ptEntry;
	usbd_hub_t* ptHub = NULL;

	if(0 < size && size <= USBD_MEM_HUB_MAX_SIZE) {
		ptEntry = SLIST_REMOVE_HEAD(&tMemCtl.hub);
		if(!ptEntry) {
			DEBUG_ERROR_CALL( 0, "failed to alloc HUB\n", NULL);
		}
		ptHub = (usbd_hub_t*)(ptEntry ? ((struct usbd_mem_hub*)ptEntry)->pcHub : NULL);
		goto end;
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("%s: too large size\n", __FUNCTION__);
#endif
	
  end:
	if(ptHub) {
		bzero(ptHub, USBD_MEM_HUB_MAX_SIZE);
	}
	return ptHub;
}

/*!
 * \brief ハブ管理構造バッファを解放する
 * \param ptHub		解放するハブ管理構造バッファ
 *
 * ptHub で指定するハブ管理構造バッファをメモリ管理機構に解放する。
 */
void
usb_USBDDeallocHub(usbd_hub_t* ptHub)
{
	usb_slist_entry_t* ptEntry;
	usb_slist_entry_t* ptNode;
	uint8_t i;
	
	if(!ptHub)
		goto bad;
	ptEntry = (usb_slist_entry_t*)HUB2ENT(ptHub);
	SLIST_FOREACH(ptNode, usb_slist_entry_t, &tMemCtl.hub) {
		if(ptNode == ptEntry) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptHub);
#endif
			DEBUG_ERROR_CALL( 3, "double free HUB\n", NULL);
			goto bad;
		}
	}
	
	/* 解放アドレスの正当性チェック */
	for(i = 0; i < USBD_MAX_HUBS; i++) {
		if(&tBuf.ptMemHub[i] == (struct usbd_mem_hub*)ptEntry)
			goto ok;
	}
	DEBUG_ERROR_CALL( 3, "HUB free invalid address\n", NULL);
	goto bad;

  ok:
	SLIST_INSERT_TAIL(&tMemCtl.hub, ptEntry);
  bad:
	return;
}

/*!
 * \brief ハブ・クラスドライバ管理構造バッファを取得する
 * \return 取得したハブ・クラスドライバ管理構造バッファのアドレス。
 *		   取得できなかった場合には NULL を返却する。
 *
 * ハブ・クラスドライバ管理構造のバッファをメモリ管理機構より取得して返却する。
 * 取得できなかった場合には NULL を返却する。
 */
uhub_softc_t*
usb_USBDAllocHubsoftc(void)
{
	usb_slist_entry_t* ptEntry;
	uhub_softc_t* ptSc;

	ptEntry = SLIST_REMOVE_HEAD(&tMemCtl.hubsoftc);
	if(!ptEntry) {
		DEBUG_ERROR_CALL( 0, "failed to alloc HUBSOFTC\n", NULL);
	}
	ptSc = (uhub_softc_t*)(ptEntry ? &((struct usbd_mem_hubsoftc*)ptEntry)->tHubsoftc : NULL);
	if(ptSc) {
		bzero(ptSc, sizeof(*ptSc));
	}
	return ptSc;
}

/*!
 * \brief ハブ・クラスドライバ管理構造バッファを解放する
 * \param ptHubsoftc		解放するハブ・クラスドライバ管理構造バッファ
 *
 * ptHubsoftc で示す、ハブ・クラスドライバ管理構造のバッファをメモリ
 * 管理機構に解放(返却)する。
 */
void
usb_USBDDeallocHubsoftc(uhub_softc_t* ptHubsoftc)
{
	usb_slist_entry_t* ptEntry;
	usb_slist_entry_t* ptNode;
	uint8_t i;

	if(!ptHubsoftc)
		goto bad;
	ptEntry = (usb_slist_entry_t*)HSC2ENT(ptHubsoftc);
	SLIST_FOREACH(ptNode, usb_slist_entry_t, &tMemCtl.hubsoftc) {
		if(ptNode == ptEntry) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptHubsoftc);
#endif
			DEBUG_ERROR_CALL( 3, "double free HUBSOFTC\n", NULL);
			goto bad;
		}
	}
	
	/* 解放アドレスの正当性チェック */
	for(i = 0; i < USBD_MAX_HUBS; i++) {
		if(&tBuf.ptMemHubsoftc[i] == (struct usbd_mem_hubsoftc*)ptEntry)
			goto ok;
	}
	DEBUG_ERROR_CALL( 3, "HUBSOFTC free invalid address\n", NULL);
	goto bad;
	
  ok:
	SLIST_INSERT_TAIL(&tMemCtl.hubsoftc, ptEntry);
  bad:
	return;
}

/*!
 * \brief デバイス・リクエスト用バッファを取得する
 * \return 取得したデバイス・リクエスト用バッファ。取得できない場合には NULL を返す。
 *
 * メモリ管理機構より、デバイス・リクエスト用バッファを取得する。
 * 取得できなかった場合には NULL を返却する。
 */
usb_device_request_t*
usb_USBDAllocDeviceRequest(void)
{
	usb_slist_entry_t* ptEntry;
	usb_device_request_t* ptReq;

	ptEntry = SLIST_REMOVE_HEAD(&tMemCtl.devreq);
	if(!ptEntry) {
		DEBUG_ERROR_CALL( 0, "failed to alloc DEVICE-REQUEST\n", NULL);
	}
	ptReq = (usb_device_request_t*)(ptEntry ? &((struct usbd_mem_devreq*)ptEntry)->tReq : NULL);
	if(ptReq) {
		bzero(ptReq, sizeof(*ptReq));
	}
	return ptReq;
}

/*!
 * \brief デバイス・リクエスト用バッファを解放する
 * \param ptReq		解放するデバイス・リクエスト用バッファ
 *
 * ptReq で示すデバイス・リクエスト用バッファをメモリ管理機構に返却する。
 */
void
usb_USBDDeallocDeviceRequest(usb_device_request_t* ptReq)
{
	usb_slist_entry_t* ptEntry;
	usb_slist_entry_t* ptNode;
	uint8_t i;
	
	if(!ptReq)
		goto bad;
	ptEntry = (usb_slist_entry_t*)REQ2ENT(ptReq);
	SLIST_FOREACH(ptNode, usb_slist_entry_t, &tMemCtl.devreq) {
		if(ptNode == ptEntry) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptReq);
#endif
			DEBUG_ERROR_CALL( 3, "double free DEVICE-REQUEST\n", NULL);
			goto bad;
		}
	}
	
	/* 解放アドレスの正当性チェック */
	for(i = 0; i < USBD_MAX_NEST_REQ; i++) {
		if(&tBuf.ptMemDevreq[i] == (struct usbd_mem_devreq*)ptEntry)
			goto ok;
	}
	DEBUG_ERROR_CALL( 3, "DEVICE-REQUEST free invalid address\n", NULL);
	goto bad;

  ok:
	SLIST_INSERT_TAIL(&tMemCtl.devreq, ptEntry);
  bad:
	return;
}

/*!
 * \brief ハブ・デスクリプタのバッファを取得する
 * \return 取得したハブ・デスクリプタのバッファ。取得できないときには NULL を返す。
 *
 * ptHubsoftc で指定されるハブ で利用する、ハブ・デスクリプタのバッファを取得する。
 * 取得できない場合には NULL を返す。
 */
usb_hub_descriptor_t*
usb_USBDAllocHubDesc(void)
{
	usb_slist_entry_t* ptEntry;
	usb_hub_descriptor_t* ptHdesc;

	ptEntry = SLIST_REMOVE_HEAD(&tMemCtl.hubdesc);
	if(!ptEntry) {
		DEBUG_ERROR_CALL( 0, "failed to alloc HUBDESC\n", NULL);
	}
	ptHdesc = (usb_hub_descriptor_t*)(ptEntry ? &((struct usbd_mem_hubdesc*)ptEntry)->tHubdesc : NULL);
	if(ptHdesc) {
		bzero(ptHdesc, sizeof(*ptHdesc));
	}
	return ptHdesc;
}

/*!
 * \brief ハブ・デスクリプタのバッファを解放する
 * \param ptHubdesc		解放するハブ・デスクリプタのバッファ
 *
 * ptHubdesc で示すハブ・デスクリプタ用バッファをメモリ管理機構に返却する。
 */
void
usb_USBDDeallocHubDesc(usb_hub_descriptor_t* ptHubdesc)
{
	usb_slist_entry_t* ptEntry;
	usb_slist_entry_t* ptNode;
	uint8_t i;
	
	if(!ptHubdesc)
		goto bad;
	ptEntry = (usb_slist_entry_t*)HDESC2ENT(ptHubdesc);
	SLIST_FOREACH(ptNode, usb_slist_entry_t, &tMemCtl.hubdesc) {
		if(ptNode == ptEntry) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptHubdesc);
#endif
			DEBUG_ERROR_CALL( 3, "double free HDESC\n", NULL);
			goto bad;
		}
	}
	
	/* 解放アドレスの正当性チェック */
	for(i = 0; i < USBD_MAX_HUBS; i++) {
		if(&tBuf.ptMemHubdesc[i] == (struct usbd_mem_hubdesc*)ptEntry)
			goto ok;
	}
	DEBUG_ERROR_CALL( 3, "HDESC free invalid address\n", NULL);
	goto bad;

  ok:
	SLIST_INSERT_TAIL(&tMemCtl.hubdesc, ptEntry);
  bad:
	return;
}

/*!
 * \brief 汎用バッファを取得する
 * \param size		取得するバッファのバイト数
 * \return 取得した汎用バッファ。取得できない場合には NULL を返却する。
 *
 * size バイト分の汎用バッファをメモリ管理機構から取得する。
 * バッファの取得ができない場合には NULL を返却する。
 */
void*
usb_USBDAllocTinyBuffer(size_t size)
{
	usb_slist_entry_t* ptEntry;
	void* p = NULL;

	if(size <= sizeof(((struct usbd_mem_tiny*)ptEntry)->tBufs)) {
		ptEntry = SLIST_REMOVE_HEAD(&tMemCtl.tiny);
		if(!ptEntry) {
			DEBUG_ERROR_CALL( 0, "failed to alloc TINY\n", NULL);
		}
		p = (void*)(ptEntry ? &((struct usbd_mem_tiny*)ptEntry)->tBufs.ulValue : NULL);
		goto end;
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("%s: over size\n", __FUNCTION__);
#endif
	
  end:
	if(p) {
		bzero(p, size);
	}
	return p;
}

/*!
 * \brief 汎用バッファを解放する
 * \param pvPtr		解放するバッファ
 *
 * pvPtr で指定するバッファを、メモリ管理機構の汎用バッファに返却する。
 */
void
usb_USBDDeallocTinyBuffer(void* pvPtr)
{
	usb_slist_entry_t* ptEntry;
	usb_slist_entry_t* ptNode;
	uint8_t i;

	if(!pvPtr)
		goto bad;
	ptEntry = (usb_slist_entry_t*)(((char*)pvPtr) - sizeof(usb_slist_entry_t));
	SLIST_FOREACH(ptNode, usb_slist_entry_t, &tMemCtl.tiny) {
		if(ptNode == ptEntry) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)pvPtr);
#endif
			DEBUG_ERROR_CALL( 3, "double free\n", NULL);
			goto bad;
		}
	}
	
	/* 解放アドレスの正当性チェック */
	for(i = 0; i < USBD_MAX_TINYS; i++) {
		if(&tBuf.ptMemTiny[i] == (struct usbd_mem_tiny*)ptEntry)
			goto ok;
	}
	DEBUG_ERROR_CALL( 3, "TINY free invalid address\n", NULL);
	goto bad;

  ok:
	SLIST_INSERT_TAIL(&tMemCtl.tiny, ptEntry);
  bad:
	return;
}

/* --------------------------------------------------------- */
/*!
 * \brief バス管理構造のバッファを取得する
 * \return 取得したバス管理構造のバッファ。取得できない場合には NULL を返す。
 *
 * メモリ管理機構より、バス管理構造のバッファを取得する。取得できない場合には
 * NULL を返却する。
 */
usbd_bus_t*
usb_USBDAllocBus(void)
{
	usbd_bus_t* ptBus = tMemCtl.ptBus;
	
	if(ptBus) {
		tMemCtl.ptBus = NULL;
		bzero(ptBus, sizeof(*ptBus));
	}
	return ptBus;
}

/*!
 * \brief バス管理構造用バッファの解放
 * \param ptBus		解放するバス管理構造のバッファ
 *
 * ptBus で指定するバス管理構造用バッファを、メモリ管理機構に返却する。
 */
void
usb_USBDDeallocBus(usbd_bus_t* ptBus)
{
	if(!ptBus)
		return;
	if(&tBuf.tMemBus != ptBus) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: illegal dealloc address %#08x\n", __FUNCTION__, (uint32_t)ptBus);
#else
		;
#endif
		goto end;
	}
	
	if(!tMemCtl.ptBus) {
		tMemCtl.ptBus = &tBuf.tMemBus;
	}
	else {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptBus);
#else
		;
#endif
	}
  end:
	;
}

/*!
 * \brief バス・ドライバ管理構造用バッファの取得
 * \return 取得したバス・ドライバ管理構造用のバッファ。取得できない場合には、
 *		   NULL を返す。
 *
 * バス・ドライバ管理構造用のバッファを、メモリ管理機構より取得して返す。
 * 取得できない場合には NULL を返す。
 */
usb_softc_t*
usb_USBDAllocSoftc(void)
{
	usb_softc_t* ptSc = tMemCtl.ptSoftc;
	
	if(ptSc) {
		tMemCtl.ptSoftc = NULL;
		bzero(ptSc, sizeof(*ptSc));
	}
	return ptSc;
}

/*!
 * \brief バス・ドライバ管理構造用のバッファを返却する
 * \param ptSc		返却するバス・ドライバ管理構造用バッファ
 *
 * ptSc で指定するバス・ドライバ管理構造用のバッファを、メモリ管理機構に
 * 返却する。
 */
void
usb_USBDDeallocSoftc(usb_softc_t* ptSc)
{
	if(!ptSc)
		return;
	if(&tBuf.tMemSoftc != ptSc) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: illegal dealloc address %#08x\n", __FUNCTION__, (uint32_t)ptSc);
#else
		;
#endif
		goto end;
	}
	
	if(!tMemCtl.ptSoftc) {
		tMemCtl.ptSoftc = &tBuf.tMemSoftc;
	}
	else {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptSc);
#else
		;
#endif
	}
  end:
	;
}

/*!
 * \brief クラス・ドライバ管理構造用バッファを取得する
 * \return 取得したクラス・ドライバ管理構造用バッファ。取得できない場合には NULL
 *		   を返す。
 *
 * クラス・ドライバ管理構造用バッファを、メモリ管理機構より取得して返却する。
 * 取得できない場合には NULL を返却する。
 */
USBD_typeClassDriver*
usb_USBDAllocClassDriver(void)
{
	usb_slist_entry_t* ptEntry;
	USBD_typeClassDriver* ptDrv;

	ptEntry = SLIST_REMOVE_HEAD(&tMemCtl.drv);
	if(!ptEntry) {
		DEBUG_ERROR_CALL( 0, "failed to alloc CLASS-DRIVER\n", NULL);
	}
	ptDrv = ptEntry ? &((struct usbd_mem_class_driver*)ptEntry)->tDrv : NULL;
	if(ptDrv) {
		bzero(ptDrv, sizeof(*ptDrv));
	}
	return ptDrv;
}

/*!
 * \brief クラス・ドライバ管理構造用バッファを解放する
 * \param ptDrv		解放するクラス・ドライバ管理構造のバッファ
 *
 * ptDrv で指定するクラス・ドライバ管理構造バッファをメモリ管理機構に返却する。
 */
void
usb_USBDDeallocClassDriver(USBD_typeClassDriver* ptDrv)
{
	usb_slist_entry_t* ptEntry;
	usb_slist_entry_t* ptNode;
	uint8_t i;

	if(!ptDrv)
		goto bad;
	ptEntry = (usb_slist_entry_t*)DRV2ENT(ptDrv);
	SLIST_FOREACH(ptNode, usb_slist_entry_t, &tMemCtl.drv) {
		if(ptNode == ptEntry) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptDrv);
#endif
			DEBUG_ERROR_CALL( 3, "double free CLASS-DRIVER\n", NULL);
			goto bad;
		}
	}

	/* 解放アドレスの正当性チェック */
	for(i = 0; i < USBD_MAX_CLASS_DRIVERS; i++) {
		if(&tBuf.ptMemDrv[i] == (struct usbd_mem_class_driver*)ptEntry)
			goto ok;
	}
	DEBUG_ERROR_CALL( 3, "CLASS-DRIVER free invalid address\n", NULL);
	goto bad;

  ok:
	SLIST_INSERT_TAIL(&tMemCtl.drv, ptEntry);
  bad:
	return;
}


/*!
 * \brief ストリングデスクリプタの確保
 * \return 確保したストリングデスクリプタのアドレス。確保失敗は NULL
 *
 * ストリング・デスクリプタを確保してあるバッファから取り出し、返却する。
 * 使用可能なバッファがない場合には、NULL を返却する。
 */
usb_string_descriptor_t*
usb_USBDAllocSDesc(void)
{
	usb_string_descriptor_t* ptSdesc = tMemCtl.ptSdesc;

	if(ptSdesc) {
		tMemCtl.ptSdesc = NULL;
		bzero(ptSdesc, sizeof(*ptSdesc));
	}
	
	return ptSdesc;
}

/*!
 * \brief ストリングデスクリプタの返却
 * \param ptSdesc	返却するストリングデスクリプタ
 *
 * ストリング・デスクリプタを管理バッファに返却する。
 */
void
usb_USBDDeallocSDesc(usb_string_descriptor_t* ptSdesc)
{
	if(!ptSdesc)
		return;
	if(&tBuf.tMemSdesc != ptSdesc) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: illegal dealloc address %#08x\n", __FUNCTION__, (uint32_t)ptSdesc);
#else
		;
#endif
		goto end;
	}
	if(!tMemCtl.ptSdesc) {
		tMemCtl.ptSdesc = &tBuf.tMemSdesc;
	}
	else {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("%s: double free %#08x\n", __FUNCTION__, (uint32_t)ptSdesc);
#else
		;
#endif
	}
  end:
	;
}


/* --------------------------------------------------------- */
#if defined(USBD_UTIL)
/*!
 * \brief メモリ管理状態を取得する
 * \return 未解放バッファ数を返却する。
 *
 * メモリ管理機構において、現在返却されていないのバッファ数をカウントして、
 * 戻値に返却する。
 */
uint16_t
usb_USBDMemDiagnose(void)
{
	usb_slist_entry_t* ptEntry;
	int16_t i;
	int16_t ret = 0;

	/* devices */
	i = 0;
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.device) {
		i++;
	}
	if(i != USBD_MAX_DEVICES) {
		tBuf.tMemDiag.ucDev = (uint8_t)(USBD_MAX_DEVICES - i);
		tBuf.tMemDiag.usLeakCnt += tBuf.tMemDiag.ucDev;
	}

	/* hub */
	i = 0;
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.hub) {
		i++;
	}
	if(i != USBD_MAX_HUBS) {
		tBuf.tMemDiag.ucHub = (uint8_t)(USBD_MAX_HUBS - i);
		tBuf.tMemDiag.usLeakCnt += tBuf.tMemDiag.ucHub;
	}

	/* hubsoftc */
	i = 0;
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.hubsoftc) {
		i++;
	}
	if(i != USBD_MAX_HUBS) {
		tBuf.tMemDiag.ucHubsoftc = (uint8_t)(USBD_MAX_HUBS - i);
		tBuf.tMemDiag.usLeakCnt += tBuf.tMemDiag.ucHubsoftc;
	}

	if(tMemCtl.ptBus != &tBuf.tMemBus) {
		tBuf.tMemDiag.usLeakCnt++;
	}
	if(tMemCtl.ptSoftc != &tBuf.tMemSoftc) {
		tBuf.tMemDiag.usLeakCnt++;
	}

	/* hubdesc */
	i = 0;
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.hubdesc) {
		i++;
	}
	if(i != USBD_MAX_HUBS) {
		tBuf.tMemDiag.ucHubdesc = (uint8_t)(USBD_MAX_HUBS - i);
		tBuf.tMemDiag.usLeakCnt += tBuf.tMemDiag.ucHubdesc;
	}

	/* tiny */
	i = 0;
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.tiny) {
		i++;
	}
	if(i != USBD_MAX_TINYS) {
		tBuf.tMemDiag.ucTinyBuf = (uint8_t)(USBD_MAX_TINYS - i);
		tBuf.tMemDiag.usLeakCnt += tBuf.tMemDiag.ucTinyBuf;
	}

	/* device request */
	i = 0;
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.devreq) {
		i++;
	}
	if(i != USBD_MAX_NEST_REQ) {
		tBuf.tMemDiag.ucDevreq = (uint8_t)(USBD_MAX_NEST_REQ - i);
		tBuf.tMemDiag.usLeakCnt += tBuf.tMemDiag.ucDevreq;
	}

	/* class driver */
	i = 0;
	SLIST_FOREACH(ptEntry, usb_slist_entry_t, &tMemCtl.drv) {
		i++;
	}
	if(i != USBD_MAX_CLASS_DRIVERS) {
		tBuf.tMemDiag.ucClsdrv = (uint8_t)(USBD_MAX_CLASS_DRIVERS - i);
		tBuf.tMemDiag.usLeakCnt += tBuf.tMemDiag.ucClsdrv;
	}

	/* sdesc */
	if(!tMemCtl.ptSdesc) {
		tBuf.tMemDiag.usLeakCnt++;
	}
	
	return tBuf.tMemDiag.usLeakCnt;
}
#endif /* defined(USBD_UTIL) */

/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
