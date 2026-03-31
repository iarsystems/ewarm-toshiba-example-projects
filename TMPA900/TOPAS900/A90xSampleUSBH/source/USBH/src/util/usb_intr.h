/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_intr.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  割り込み管理

*/

#ifndef USB_INTERRUPT_H
#define USB_INTERRUPT_H

#include "usb_config.h"
#include "usb_types.h"
#include "usb_interrupt.h"

#define USB_ENA_INTR() usb_INTR_vEnable()    /* 割り込み許可 */
#define USB_DIS_INTR() usb_INTR_vDisable()    /* 割り込み禁止 */

/* USB 割り込み初期化 */
extern void usb_INTR_vInitialize( void );
/* USB 割り込み終了 */
extern void usb_INTR_vFinalize( void );
/* USB 割り込み判別 */
extern bool usb_INTR_blDisable( void );

/* タイマ割り込み開始 */
extern void usb_TIMER_vStartIntr( void );
/* タイマ割り込み終了 */
extern void usb_TIMER_vEndIntr( void );

extern void usb_INTR_vEnable( void );
extern void usb_INTR_vDisable( void );
#endif
