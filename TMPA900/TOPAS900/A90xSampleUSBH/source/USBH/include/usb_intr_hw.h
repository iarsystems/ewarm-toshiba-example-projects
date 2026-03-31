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

/*! \file usb_intr_hw.h
	\brief 

	\author TOSHIBA CORPORATION
	\date 2007/06/15 modify original file

 */
/* ************************************************************************** */

/*

  USB äÑÇËçûÇ›ä«óù

*/


/* ========== DEFINES & EXTERNS ========== */

/* ========== global variables ========== */

/* ========== GLOBAL FUNCTIONS ========== */

/* --- USB Interrupt --- */
void usb_INTR_vSetInterruptLevel(void);
void usb_INTR_vClearInterruptLevel(void);
void int_usbhost(void);

/* --- TIMER Interrupt --- */
void usb_TIMER_vSetTimerInit(void);
void usb_TIMER_vStartTimer(void);
void usb_TIMER_vStopTimer(void);
void int_ta3(void);


/* --- End of File --- */
