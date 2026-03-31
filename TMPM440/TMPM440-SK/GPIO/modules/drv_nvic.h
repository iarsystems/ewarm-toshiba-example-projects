/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : drv_nvic.h
 *    Description : Toshiba TMPM440 Nested Vectored Interrupt Control
 *
 *    History :
 *    1. Date        : June 2011
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    2. Date        : 7.2013
 *       Author      : Santosh Pawar
 *       Description : Ported to Toshiba TMPM440
 *
 *    $Revision: 4200 $
 **************************************************************************/
#ifndef __NVIC_H
#define __NVIC_H
/** include files **/
#include <stdint.h>
/** definitions **/

/* Interrupt line trigger mode init structure */
typedef enum _int_trg_mode_t
{
	TRIG_LOW = 0, 		/* Low level trigger */
	TRIG_HIGH, 				/* High level trigger */
	TRIG_RISING,			/* Rising Edge trigger */
	TRIG_FALLING,			/* Falling Edge trigger */
	TRIG_BOTH_EDGE,		/* Rising & Falling Edge trigger */
} int_trg_mode_t;



/** public data **/

/** public functions **/
void NVIC_EnableIRQ(uint32_t IntNumber);
void NVIC_DisableIRQ(uint32_t IntNumber);
void NVIC_ClearPendingIRQ(uint32_t IntNumber);
void NVIC_SetPriority(uint32_t IntNumber, uint8_t Priority);
void NVIC_SetTrigMode(uint32_t IntNumber, int_trg_mode_t mode);
void NVIC_ClearTrigIRQ(uint32_t IntNumber);
void EntrCritSection(void);
void ExtCritSection(void);
void NVIC_Init(void);

#define ENTR_CRT_SECTION() EntrCritSection()
#define EXT_CRT_SECTION()  ExtCritSection()

#endif  /* __NVIC_H */
