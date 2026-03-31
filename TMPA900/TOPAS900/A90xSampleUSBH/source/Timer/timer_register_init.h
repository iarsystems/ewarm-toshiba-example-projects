#ifndef _timer_register_init_h_
#define _timer_register_init_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : Timer Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file timer_register_init.h
	\brief Header file of TIMER register's macro define

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
#include "register_timer.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/* for TimerxValue	*/

/* for TimerxControl	*/
#define	CTimer0Control_init	\
	( \
	  CTimerxControl_Reserved			| \
	  CTimerxControl_TIMxEN_STOP		| \
	  CTimerxControl_TIMxMOD_Periodic 	| \
	  CTimerxControl_TIMxINTE_ENABLE	| \
	  CTimerxControl_TIMxPRS_16			| \
	  CTimerxControl_TIMxSIZE_16bit		| \
	  CTimerxControl_TIMxOSCTL_Wrapping \
	  )

/* for TimerxIntClr	*/

/* for TimerxRIS	*/
/* for TimerxMIS	*/
/* for TimerxBGLoad	*/
/* for TimerxMode	*/
/* for TimerxCompare	*/
/* for TimerxCmpIntClr1	*/
/* for TimerxCmpEn	*/
/* for TimerxCmpRIS	*/
/* for TimerxCmpMIS	*/
/* for TimerxBGCmp	*/

/* ************************************************************************ */
#endif	/* _timer_register_init_h_ */
