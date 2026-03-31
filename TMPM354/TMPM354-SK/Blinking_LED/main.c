/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM354
 *    family microcontrollers. It is developed for TMPM354-SK Board.
 *     It uses the TIMER0 to toggle the LEDs.
 *
 *    History :
 *    1. Date        : 15.09.2011
 *       Author      : Stoyan Choynev
 *       Description : Initioal version TMPM354-SK
 *
 * Jumpers:
 *  JP9 - filled
 *  JP14 - filled
 *  JP10,JP11,JP13 - depend of power source
 *  E_JP8 - E_JP15 (LEDs) - filled
 *  J3P6 - 2-3
 *  J3P7 - 1-2
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

  assert((INTERR <= IntNumber) && (INTLVCLR >= IntNumber));
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

  assert((INTERR <= IntNumber) && (INTLVCLR >= IntNumber));
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

  assert((INTERR <= IntNumber) && (INTLVCLR >= IntNumber));
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

  assert((INTERR <= IntNumber) && (INTLVCLR >= IntNumber));
  IntNumber -= INTERR;
  pNVIC_IntPri += IntNumber;
  *pNVIC_IntPri = Priority;
}

void INTCMP00_IRQHandler (void)
{
  /*Toggle LEDs*/
  LED_TGL(LED1|LED2|LED3|LED4|
          LED5|LED6|LED7|LED8);
  NVIC_ClrPend(INTCMP00);
}


int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  /*LEDs init*/
  LED_INIT(LED1|LED2|LED3|LED4|
           LED5|LED6|LED7|LED8);
  /*ture on odd leds*/
  LED_ON(LED1|LED3|LED5|LED7);
  /*turn off even leds*/
  LED_OFF(LED2|LED4|LED6|LED8);
  /* Init Timer 0*/
  /*Stop and clear timer's counter*/
  TCMP0_TBTRUN = 0;
  /*div 1/2*/
  TCMP0_TBTCR_bit.DIVSEL = 1;
  /*Counter Clear Enable*/
  TCMP0_CMP0CR_bit.CNTCLEN = 1;
  /*Compare Enable*/
  TCMP0_CMP0CR_bit.CMPEN = 1;
  TCMP0_CMP0 = SYS_FREQ/(TICK_PER_SEC*2);
  /*Enable NVIC TMR0 Interrupt*/
  NVIC_IntEnable(INTCMP00);
  NVIC_IntPri(INTCMP00,16);
  TCMP0_TBTRUN_bit.DIVRUN = 1;
  TCMP0_TBTRUN_bit.TBRUN = 1;

  __enable_interrupt();

  while(1)
  {
  }
}
