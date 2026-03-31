/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_tmr.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Timer Header

*/

#ifndef USB_TIMER_H
#define USB_TIMER_H

#include "usb_config.h"
#include "usb_types.h"
#include "usb_queue.h"
#include "usb_timer.h"

/* ========== DEFINES ========== */

/* タイマ割り込み発生周期[ms] */
#define TIMER_INTR_CYCLE_MS 1

/* タイマハンドラ構造体用メモリサイズ */
/* 各種転送時タイムアウト、USBドライバ初期化時に使用 */
#define TIMER_HDR_MAX_NUM 2

#define TIMER_CARRY_FLAG  0x80000000UL

/* ========== TYPE_DEFS ========== */
/* 20[byte] */
typedef struct TIMER_tagHandler {
	usb_slist_entry_t	list;
	usb_TIMER_fnHdr vHdr;
	uint32_t		ulArg;
	uint32_t		ulCount;
} TIMER_typeHandler;

/* ========== EXTERNS ========== */

#if defined( USB_CTX_SWT )
/* コンテキストを切り替えての待ちが存在しているか否かをチェック */
extern bool usb_CTXSWT_blWaiting( void );
/* コンテキストを切り替えての待ちをキャンセル
    ホストドライバ終了時に usb_USBD_vFinalize() から呼び出す */
extern void usb_CTXSWT_vCancelWait( void );
#endif

#if defined( USB_DEBUG )
/* メモリチェック */
extern int16_t usb_TIMER_iMemCheck( void );
#endif

#endif
