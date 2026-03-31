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

/*! \file usb_timer.h
	\brief Declaration of USB Host Driver Timer Function

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */

#ifndef USB_TIMER_PUBLIC_H
#define USB_TIMER_PUBLIC_H

#include "usb_types.h"

/* ========== TYPE_DEFS ========== */
typedef void (*usb_TIMER_fnHdr)( uint32_t ulArg );

/* ========== EXTERNS ========== */

/* タイマ初期化 */
extern void usb_TIMER_vInitialize( void );
/* タイマ終了処理 */
extern void usb_TIMER_vFinalize( void );
/* ミリ秒待ち */
extern void usb_TIMER_vWaiMsec( uint16_t usMs );
/* 現在時刻取得 */
extern int32_t usb_TIMER_lGetTime( void );
/* タイマハンドラセット */
extern int16_t usb_TIMER_iSetHandler( usb_TIMER_fnHdr vHdr, uint32_t ulArg, int16_t sTime, uint32_t* pulIdTimer );
/* タイマハンドラキャンセル */
extern void usb_TIMER_vCancelHandler( uint32_t ulIdTimer );

/* タイマ割り込み */
extern void usb_TIMER_vIntr( void );
/* タイマ割り込み禁止 */
extern void usb_TIMER_vDisIntr( void );
/* タイマ割り込み許可 */
extern void usb_TIMER_vEnaIntr( void );

#endif
