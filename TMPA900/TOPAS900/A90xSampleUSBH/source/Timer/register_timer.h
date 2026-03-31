#ifndef _register_timer_h_
#define _register_timer_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : Timer Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file register_timer.h
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


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/* for TimerxLoad	*/
#define CTimerxLoad_Reserved_MASK			0xFFFFFF00
# define CTimerxLoad_Reserved				0x00000000
#define CTimerxLoad_TIMxSD_MASK				0x000000FF	/* Don't set 0x00	*/

/* for TimerxValue	*/
#define CTimerxVale_Reserved_MASK			0xFFFFFF00
# define CTimerxVale_Reserved				0x00000000

/* for TimerxControl	*/
#define CTimerxControl_Reserved_MASK		0xFFFFFF10
# define CTimerxControl_Reserved			0x00000000
#define CTimerxControl_TIMxEN_MASK			0x00000080
# define CTimerxControl_TIMxEN_START		0x00000080	/*!< start timer	*/
# define CTimerxControl_TIMxEN_STOP			0x00000000	/*!< stop timer		*/

#define CTimerxControl_TIMxMOD_MASK			0x00000040
# define CTimerxControl_TIMxMOD_Periodic	0x00000040	/*!< Periodic mode	*/
# define CTimerxControl_TIMxMOD_FreeRun		0x00000000	/*!< Free Run mode	*/

#define CTimerxControl_TIMxINTE_MASK		0x00000020
# define CTimerxControl_TIMxINTE_ENABLE		0x00000020	/*!< enable interrupt */
# define CTimerxControl_TIMxINTE_DISABLE	0x00000000	/*!< disable interrupt*/

#define CTimerxControl_TIMxPRS_MASK			0x0000000C
# define CTimerxControl_TIMxPRS_1			0x00000000
# define CTimerxControl_TIMxPRS_16			0x00000004
# define CTimerxControl_TIMxPRS_256			0x00000008
# define CTimerxControl_TIMxPRS_DISABLE		#error

#define CTimerxControl_TIMxSIZE_MASK		0x00000002
# define CTimerxControl_TIMxSIZE_16bit		0x00000002	/*!< 16bit timer	*/
# define CTimerxControl_TIMxSIZE_8bit		0x00000000	/*!< 8bit timer		*/

#define CTimerxControl_TIMxOSCTL_MASK		0x00000001
# define CTimerxControl_TIMxOSCTL_OneShot	0x00000001
# define CTimerxControl_TIMxOSCTL_Wrapping	0x00000000

/* for TimerxIntClr	*/
#define CTimerxIntClr	0xFFFFFFFF

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
#endif	/* _register_timer_h_ */
