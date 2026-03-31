/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 */

/* $Id: usb_usbd_util.h 41 2014-01-27 14:05:18Z danielru $ */

#ifndef _USB_USBD_UTIL_H_SEEN_
#define _USB_USBD_UTIL_H_SEEN_

#include "usb_config.h"
#include <usb_types.h>


/*!
 * \page usbd_debug_util USBバス・ドライバ デバッグ・ユーティリティ
 *
 * このモジュールは USBバス・ドライバのデバッグ用ルーチン集です。
 *
 * \section error_check 発生エラーの確認
 *  USBバス・ドライバで発生したエラーを確認するための機能です。
 *
 * \section watch_xfer xferの監視
 *  バス・ドライバを使った転送で使われる xfer を監視します。
 */

/* ========================================================= */
/*                    発生エラーの確認                       */
/* ========================================================= */

typedef struct usbd_retry_count {
	uint32_t	device_request;
	uint32_t	port_restart;
} usbd_retry_count_t;


typedef struct usbd_error_count {
	uint32_t		device_vanished;
	uint32_t		illegal_port_change;
	uint32_t		port_error;
	uint32_t		ignore_port;
	uint32_t		device_request;
} usbd_error_count_t;


#if defined(USBD_UTIL)

extern usbd_retry_count_t* usb_ptUSBD_RETRY_COUNT;
extern usbd_error_count_t* usb_ptUSBD_ERROR_COUNT;


extern void				usb_USBDCountInit(void);


#define USBD_COUNT_RETRY(kind)		usb_ptUSBD_RETRY_COUNT->kind++
#define USBD_COUNT_ERROR(kind)		usb_ptUSBD_ERROR_COUNT->kind++

#else /* !defined(USBD_UTIL) */

#define usb_USBDCountInit()			/* empty */
#define USBD_COUNT_RETRY()			/* empty */
#define USBD_COUNT_ERROR()			/* empty */

#endif /* defined(USBD_UTIL) */



/* ========================================================= */
/*                       xfer の監視                         */
/* ========================================================= */
#include "usb_usbd_var.h"

#if defined(USBD_UTIL)
extern void				usb_USBDWatchXfer_RegisterTransferingXfer(usbd_xfer_t* xfer);
extern void				usb_USBDWatchXfer_RegisterTransferedXfer(usbd_xfer_t* xfer);
extern int16_t			usb_USBDWatchXfer_CheckXfer(usbd_xfer_t* xfer);
#endif


#endif /* _USB_USBD_UTIL_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
