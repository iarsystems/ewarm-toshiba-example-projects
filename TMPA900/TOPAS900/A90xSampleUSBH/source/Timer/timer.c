/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : Timer Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file timer.c
	\brief Source Code of TIMER API Functions

	\author TOSHIBA CORPORATION

	\date 2008/08/11 New
	\date 2008/10/24 A910 Sample version 1.0
 */
/* ************************************************************************ */

/* ************************************************************************ */
/*
 * --------------------------------------------------------------------------
 *   Header Include Area
 * --------------------------------------------------------------------------
 */
#include "cmn_type.h"

#include "system_def.h"

#include "timer.h"

#include "usb_config.h"	/* for ctx	*/


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#if(MSYS_CLK == CSYS_CLK192M)
# define CFCLK_FREQ					192		/* FCLK frequency */
#elif(MSYS_CLK == CSYS_CLK048M)
# define CFCLK_FREQ					 48		/* FCLK frequency */
#else
# error
#endif

/* for TimerxLoad	*/
#define CFPCLK_FREQ			(CFCLK_FREQ/2)

#define CTIMCLK_FREQ 		((CFPCLK_FREQ/2)/16)	/* TIMCLK frequency */
#define CTimer0Load_1ms		((CTIMCLK_FREQ*1000)-1)
//#define CTimer0Load_1ms		(1000/(1/CTIMCLK_FREQ))

/*
 * --------------------------------------------------------------------------
 *   Style Define Area
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Variable Define
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Prototype Declaration Area
 * --------------------------------------------------------------------------
 */


/* ************************************************************************** */
/*! \addtogroup TIMER_Functions
 *  @{
 */

/*! \addtogroup TIMER_API_Functions
 *  @{
 */
/* ======================================================================== */
/*! 
	Initialize of Timer0
		Timer stop/start	(Timer0Control<7>=0/1)
		Periodic timer mode	(Timer0Control<6>=1)
		Enable Interrupt	(Timer0Control<5>=1)
		Prescaler 16		(Timer0Control<3,2>=01)
		16bit				(Timer0Control<1>=1)
		Wrapping mode		(Timer0Control<0>=0)

	\param  interrupt_func	interrupt function
	\retval -
 */
/* ------------------------------------------------------------------------ */
void timer0_init(void interrupt_func(void))
{
	UINT32_t reg_data;

	Timer0Control = CTimer0Control_init;	/* set Timer0 Control	*/
	reg_data = CTimer0Load_1ms;
    Timer0Load    = reg_data;		/* set 1ms */
//    Timer0Load    = CTimer0Load_1ms;		/* set 1ms */

	/* set interrupt */
   	reg_data = VICINTSELECT & ~CInterruptTimer01_MASK;
#if defined(USB_CTX_SWT)
#else
	reg_data		= (reg_data & CInterruptTimer01_MASK) | CInterruptTimer01_T; /*FIQ*/
#endif
	VICINTSELECT = reg_data;					/* Select IRQ interrupt		*/
	VICVECTADDR2 = (UINT32_t)interrupt_func; 	/* Set interrupt function	*/
	VICINTENABLE |= CInterruptTimer01_T;		/* Enable Interrupt Timer01 */
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	Clear Timer0 interrupt and start
		Timer start	(Timer0Control<7>=1)

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void timer0_start(void)
{
	UINT32_t reg_data;

	Timer0IntClr  =	CTimerxIntClr;			/* Clear interrupt	*/
	reg_data = Timer0Control & ~CTimerxControl_TIMxEN_MASK;
	reg_data |= CTimerxControl_TIMxEN_START;
	Timer0Control = reg_data;
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	stop timer0 and Clear Timer0 interrupt
		Timer stop	(Timer0Control<7>=0)

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void timer0_stop(void)
{
	UINT32_t reg_data;

	reg_data = Timer0Control & ~CTimerxControl_TIMxEN_MASK;
/*	reg_data |= CTimerxControl_TIMxEN_STOP; */
	Timer0Control = reg_data;
}
/* ======================================================================== */
/*! @}	*/ /* TIMER_API_Function */

/*! @}	*/ /* TIMER_Functions */
/* ************************************************************************ */
