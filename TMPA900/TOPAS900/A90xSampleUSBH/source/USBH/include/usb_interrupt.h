/* ************************************************************************** */
/*
 * --------------------------------------------------------------------------
 *	Application			: USB Host Driver
 *	Micon				: TMP92xx28
 *	Development Tool	: -
 * 	Complie Option		: -
 *  Copyright(C) TOSHIBA CORPORATION 2007 All rights reserved
 * --------------------------------------------------------------------------
 */

/*! \file usb_interrupt.h
	\brief Declaration of USB Host Driver Interrupt Function

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */

#ifndef USB_INTERRUPT_PUBLIC_H
#define USB_INTERRUPT_PUBLIC_H

#include "usb_types.h"

/* ========== EXTERNS ========== */

/*! USB 割り込み許可 */
extern void usb_INTR_vEnable( void );
/*! USB 割り込み禁止 */
extern void usb_INTR_vDisable( void );

/*! USB/タイマ同時割り込み禁止 */
extern void usb_vDisableAllIntr( void );
/*! USB/タイマ同時割り込み許可 */
extern void usb_vEnableAllIntr( void );

#endif
