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

/*! \file usb_intr_hw.c
	\brief Sample Code of USB Host MSC Wrapper
			This is a USB interrupt management.
			These functions are used by a USB driver.
			It is necessary to customize them when desiring the changes of interrupt levels
			and timer interrupt.

	\author TOSHIBA CORPORATION
	\date 2007/06/15 modify original file

 */
/* ************************************************************************** */

/*

  USB interrupt management

*/

/* ========== DEFINES & EXTERNS ========== */


//#if(MMCU_CORE == CTLCS900H1)
// # include "register.h"
// # include "sfr_def.h"
//# error
// #else
# include "system_def.h"
# include "timer.h"
//#endif
# include "usb_intr_hw.h"
# include "usb_usbd.h"
# include "usb_timer.h"

/* ========== global variables ========== */

/* ========== GLOBAL FUNCTIONS ========== */

/* ************************************************************************ */
/*! \addtogroup MSCWrapper
 *  @{
 */

/* ************************************************************************ */
/*! \addtogroup USBInterruptFunctions
 *  @{
 */

/* ======================================================================== */
/*! Set USB interrupt level
	It sets a USB interrupt level.
	Change it when desiring the change of an interrupt level.
	A USB driver uses this function.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void usb_INTR_vSetInterruptLevel(void)
{
//#if(MMCU_CORE == CTLCS900H1)
//	INTEUSB = ((INTEUSB & 0x70) | cINTEUSB_INIT);
//#else
	VICINTENABLE |= CInterruptUSBH_T;			/* Enable Interrupt 		*/
//#endif
}

/* ======================================================================== */

/* ======================================================================== */
/*! Clear USB Interrupt Level
	It clears (disables) a USB host interrupt level.
	A USB driver uses this function.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void usb_INTR_vClearInterruptLevel(void)
{
//#if(MMCU_CORE == CTLCS900H1)
//	INTEUSB = (INTEUSB & 0x70);
//#else
	VICINTENABLE &= ~CInterruptUSBH_MASK;		/* Disable Interrupt 		*/
//#endif
}
/* ======================================================================== */

/************************************************************************/
/* USB HOSTäÑÇËçûÇ›														*/
/************************************************************************/
void int_usbhost( void )
{
	UINT32_t reg_data;

	reg_data = GPIOBDATA & 0x0000000E;
	reg_data |= 0x00000001;
	GPIOBDATA = reg_data;

	usb_USBD_vIntr();

	reg_data &= 0x0000000E;
	GPIOBDATA = reg_data;
}

/*! @} */ /* USBInterruptFunctions */
/* ************************************************************************ */

/* ************************************************************************ */
/*! \addtogroup TimerInterruptFunctions
 *  @{
 */

/* ======================================================================== */
/*! Set 1msec timer and start
	It sets a timer interrupt of 1 ms.
	It currently uses Timer2 and Timer3.
	It is necessary to customize it when desiring to use other timer interrupts.
	A USB driver uses this function.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void usb_TIMER_vSetTimerInit(void)
{
//#if(MMCU_CORE == CTLCS900H1)
//	INTETA23 = cINTETA23_INIT;          /* INTA3 :          INTA2  :        */

	/* Terminate a timer */
//	TA23RUN = cTA23RUN_STOP;            // INTTA3 STOP

	/* Set a timer */
//	TA2REG  = cTA2REG_INIT;             // Lower (1ms)
//	TA3REG  = cTA3REG_INIT;             // Upper (1ms)
//	TA23MOD = cTA23MOD_INIT;            // 16bit timer, T1
//#else
	timer0_init(int_ta3);
//#endif

	/* Start a timer count */
	usb_TIMER_vStartTimer();           // INTTA3 START
}
/* ======================================================================== */

/* ======================================================================== */
/*! Start Timer
	It starts a timer count.
	A USB driver uses this function.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void usb_TIMER_vStartTimer(void)
{
//#if(MMCU_CORE == CTLCS900H1)
//	TA23RUN = cTA23RUN_START;           // INTTA3 START
//#else
	timer0_start();
// #endif
}
/* ======================================================================== */

/* ======================================================================== */
/*! Stop Timer
	It stops a timer count.
	A USB driver uses this function.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void usb_TIMER_vStopTimer(void)
{
//#if(MMCU_CORE == CTLCS900H1)
//	TA23RUN = cTA23RUN_STOP;
//#else
	timer0_stop();								/* Stop Timer0 */
// #endif
}
/* ======================================================================== */

/************************************************************************/
/* USB TIMERäÑÇËçûÇ›													*/
/************************************************************************/

void int_ta3( void )
{
	UINT32_t reg_data;

	reg_data = GPIOBDATA & 0x0000000D;
	reg_data |= 0x00000002;
	GPIOBDATA = reg_data;

	Timer0IntClr = CTimerxIntClr;		/* Clear interrupt	*/
	usb_TIMER_vIntr();

	reg_data &= 0x0000000D;
	GPIOBDATA = reg_data;
}
/*! @} */ /* TimerInterruptFunctions */
/* ************************************************************************ */

/*! @} */ /* MSCWrapper */
/* ************************************************************************ */

/* ************************************************************************ */
/* --- End of File --- */
