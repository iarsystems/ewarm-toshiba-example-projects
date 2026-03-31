/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ctxswt.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Host Driver 簡易コンテキストスイッチ (TLCS900)

*/

#ifndef USB_CONTEXT_SWITCH_H
#define USB_CONTEXT_SWITCH_H

#include "usb_config.h"

#if defined( USB_CTX_SWT )

#include "usb_types.h"

/* ========== DEFINES ========== */

/* USB 割り込みスタックサイズ[byte] */
//#define USB_INTR_STACK_SZ 1024
#define USB_INTR_STACK_SZ (1024*2)

/* ========== EXTERNS ========== */
/* 簡易コンテキストスイッチ初期化 */
extern void usb_CTXSWT_vInitialize( void );
/* 簡易コンテキストスイッチ終了 */
extern void usb_CTXSWT_vFinalize( void );
/* USB 割込みコンテキスト切り替え */
extern void usb_CTXSWT_vChgIntrCtx( void (*fvUsbIntr)( void ) );
/* 復帰されるまで、割り込み処理を中断する */
extern void usb_CTXSWT_vSlpIntrCtx( void );
/* 現在のコンテキストが割り込みか否かを調べる */
extern bool usb_CTXSWT_blIntrCtx( void );

#endif
#endif
