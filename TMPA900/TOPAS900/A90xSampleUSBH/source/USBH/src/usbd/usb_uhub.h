/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 * \ingroup uhub
 */

/* $Id: usb_uhub.h 41 2014-01-27 14:05:18Z danielru $ */

#ifndef _USB_UHUB_H_SEEN_
#define _USB_UHUB_H_SEEN_


#include "usb_config.h"
#include "usb_usbd_class.h"
#include "usb_usbd_var.h"

/*!
 * \addtogroup uhub ハブクラス
 * @{
 */


/*!
 * \brief ハブクラスの Interrupt IN 転送で利用するバッファサイズを算出する。
 * \param numPorts ハブのポート数
 *
 * ハブの Interrupt IN 転送で転送される Hub_and_Port_Status_Change_Bitmap の
 * サイズ(バイト)を numPorts にから算出する。
 */
#define USB_STATUS_CHANGE_BITMAP_SIZE(numPorts)		(1 + (((numPorts)) >> 3))

/*!
 * \brief ステータス・チェンジ・ビットマップから指定ポートに対応する bit を取り出す
 * \param bitmap	Hub_and_Port_Status_Change_Bitmap で示されるビットマップ
 * \param portNo    ビットを取得するポート番号
 * \return ビットマップにおける portNo に対応するビットの値
 *
 * bitmap で指定する Interrupt IN で転送されるビットマップから、portNo で指定した
 * ポートに対応するビットの値を取得する。
 */
#define USB_STATUS_CHANGE_BITMAP_PORT(bitmap,portNo) \
		((*((uint8_t*)(bitmap) + ((portNo) >> 3)) >> ((portNo) & 0x7)) & 1)


/* ********************************************************* */
/*                     Type Definitions                      */
/* ********************************************************* */

/*!
 * ハブクラスの固有変数群構造体
 */
typedef struct uhub_softc {
    struct usbd_device*     ptHub;			/*!< ハブデバイスのデバイス構造体  */
    struct usbd_pipe*       ptIpipe;		/*!< InterruptIN 転送のパイプ */
    uint8_t                 pucStatus[USB_STATUS_CHANGE_BITMAP_SIZE(USB_MAX_HUB_PORTS)]; /*!< InterruptIN 転送のバッファ */
} uhub_softc_t;


#define USB_DEBOUNCE_STABLE     4
#define USB_DEBOUNCE_STEP      25
#define USB_DEBOUNCE_TIMEOUT  400

/* ********************************************************* */
/*                  Function Declarations                    */
/* ********************************************************* */
extern usbd_status			usb_iUHUBNewHub(usbd_device_t* ptDevice);
extern void					usb_vUHUBFreeHub(usbd_hub_t* ptHub);
extern usbd_status			usb_iUHUBExplore(usbd_device_t* ptDevice);
extern void					usb_vUHUBProcConnectStatusChange(usbd_device_t* ptDevice,
															 uint8_t ucPortNo,
															 usb_port_status_t* ptPortStatus);


/*!
 * @}
 */
#endif /* _USB_UHUB_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
