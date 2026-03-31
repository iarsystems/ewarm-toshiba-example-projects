/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : nvic.h
 *    Description : Toshiba TMPM366 Nested Vectored Interrup Controller
 *                  header file
 *    History :
 *    1. Date        : 1.2011 
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    $Revision: 4200 $
 **************************************************************************/
#ifndef __NVIC_H
#define __NVIC_H
/** include files **/
#include <stdint.h>
/** definitions **/

/** public data **/
extern uint32_t CriticalSecCntr;

/** public functions **/
/*************************************************************************
 * Function Name: NVIC_IntEnable
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description: Enable interrup at NVIC
 *
 *
 *************************************************************************/
extern void NVIC_IntEnable(uint32_t IntNumber);

/*************************************************************************
 * Function Name: NVIC_IntDisable
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description: Disables interrup at NVIC
 *
 *
 *************************************************************************/
void NVIC_IntDisable(uint32_t IntNumber);

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description:Clear pending interrupt at NVIC
 *
 *
 *************************************************************************/
void NVIC_ClrPend(uint32_t IntNumber);

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrup number, Interrupt Priority
 * Return: void
 *
 * Description:Sets Interrupt priority
 *
 *
 *************************************************************************/
void NVIC_IntPri(uint32_t IntNumber, uint8_t Priority);

#endif  /* __NVIC_H */
