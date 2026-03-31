/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM350
 *    family microcontrollers. It is developed for TMPM350-SK Board.
 *     It uses the TIMER0 to toggle the port PD0 (LED1).
 *
 *    History :
 *    1. Date        : 09.06.2011
 *       Author      : Stanimir Bonev
 *       Description : Initioal version TMPM350-SK
 *
* Jumpers:
 *  J3P1 - 2-3
 *  J3P2 - 1-2
 *  JP1  - filled
 *  JP7  - filled
 *  JP8  - filled
 *  JP9  - filled
 *  JP10 - filled
 *  JP2,JP3,JP4,JP6 - depend of power source
 *
 * Note: Use only core reset strategy!
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <assert.h>
#include "board.h"

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
#define TICK_PER_SEC  10

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*************************************************************************
 * Function Name: NVIC_IntEnable
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description: Enable interrup at NVIC
 *
 *
 *************************************************************************/
void NVIC_IntEnable(Int32U IntNumber)
{
volatile unsigned long * pNVIC_SetEn = &SETENA0;

  assert((INTERR <= IntNumber) && (INTEXC >= IntNumber));
  IntNumber -= INTERR;

  pNVIC_SetEn += IntNumber/32;
  *pNVIC_SetEn = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_IntDisable
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description: Disables interrup at NVIC
 *
 *
 *************************************************************************/
void NVIC_IntDisable(Int32U IntNumber)
{
volatile unsigned long * pNVIC_ClrEn = &CLRENA0;

  assert((INTERR <= IntNumber) && (INTEXC >= IntNumber));
  IntNumber -= INTERR;

  pNVIC_ClrEn += IntNumber/32;
  *pNVIC_ClrEn = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrup number
 * Return: void
 *
 * Description:Clear pending interrupt at NVIC
 *
 *
 *************************************************************************/
void NVIC_ClrPend(Int32U IntNumber)
{
volatile unsigned long * pNVIC_ClrPend = &CLRPEND0;

  assert((INTERR <= IntNumber) && (INTEXC >= IntNumber));
  IntNumber -= INTERR;

  pNVIC_ClrPend += IntNumber/32;
  *pNVIC_ClrPend = (1UL<<(IntNumber%32));

}

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrup number, Interrupt Priority
 * Return: void
 *
 * Description:Sets Interrupt priority
 *
 *
 *************************************************************************/
void NVIC_IntPri(Int32U IntNumber, Int8U Priority)
{
volatile Int8U * pNVIC_IntPri = (Int8U *)&IP0;

  assert((INTERR <= IntNumber) && (INTEXC >= IntNumber));
  IntNumber -= INTERR;
  pNVIC_IntPri += IntNumber;
  *pNVIC_IntPri = Priority;
}

void INTCMP00_IRQHandler (void)
{
  LED_PORT ^= LED1_MASK;
  NVIC_ClrPend(INTCMP00);
}


int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  // Port Function
  FNCSELD_bit.FS0 = 0;
  // Enable Output
  LED_PORT_DIR |= LED1_MASK;
  // LED1 off
  LED_PORT     &=~LED1_MASK;
  // Init Timer 0
  // Stop and clear timer's counter
  TB00TRUN = 0;
  // div 1/2
  TB00TCR_bit.DIVSEL = 1;
  // Counter Clear Enable
  TB00CMP0CR_bit.CNTCLEN = 1;
  // Compare Enable
  TB00CMP0CR_bit.CPMEN = 1;
  TB00CMP0 = SYS_FREQ/(TICK_PER_SEC*2);
  // Enable NVIC TMR0 Interrupt
  NVIC_IntEnable(INTCMP00);
  NVIC_IntPri(INTCMP00,16);
  TB00TRUN_bit.DIVRUN = 1;
  TB00TRUN_bit.TBRUN = 1;

  __enable_interrupt();

  while(1)
  {
  }
}
