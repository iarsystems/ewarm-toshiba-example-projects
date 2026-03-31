/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2014
 *
 *    File name   : main.c
 *    Description : main module
 *
 *    History :
 *    1. Date        : 03.02.2014
 *       Author      : Atanas Uzunov
 *       Description : initial version
 *
 *    2. Date        : 2015/Mar/05
 *       Author      : Santosh Pawar
 *       Description : Updated for RBTZ2100-2MA-A2 Board
 *
 * DESCRIPTION
 * ===========
 * This example project shows how to use the IAR Embedded Workbench for ARM
 * to develop code for the Toshiba RBTZ2100-2MA-A2.
 * TMR0 interrupt is used to display LED7 at interval of 250ms.
 *
 *    $Revision: 379 $
 **************************************************************************/

#include <intrinsics.h>
#include <stdint.h>
#include "board.h"
#include "arm_comm.h"
#include "armv7a_cp15_drv.h"
#include "io_macros.h"

#pragma section = ".intvec"


static void (*INT_Handlers_Table[256])(void);
static uint16_t int_num;

/*************************************************************************
 * Function Name: NoInterrupt_Handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Empty/Dummy interrupt handler for unused interrupts
 *
 *************************************************************************/
void NoInterrupt_Handler(){}

/*************************************************************************
 * Function Name: TMR0_Handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: TMR0 interval interrupt handler
 *
 *************************************************************************/
void TMR0_Handler(void)
{
  static char ledcnt=0;
  
  if(ledcnt&1) {
    GPIO1_ODATACLR = LED7;
  }
  else {
    GPIO1_ODATASET = LED7;
  }
  ledcnt++;
  /* Clear TMR0 interrupt bit */
  TMR0_ISR = 0x1;
}


/*************************************************************************
 * Function Name: IRQ_Handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: IRQ nested interrupt handler
 *
 *************************************************************************/
__arm __nested __irq void IRQ_Handler(void)
{
/* Read/save active interrupt id */
uint32_t iarreg = GIC_ICCIAR;
uint16_t int_id = iarreg & 0x000003FF;

  /* If not spirious interrupt */
  if(int_id < int_num)
  {
    /* Enable interrupt nesting */
    __enable_irq();

    /* Call corresponding interrupt handler function */
    INT_Handlers_Table[int_id]();

    /* Disable interrupt nesting */
    __disable_irq();
  }

  /* End of interrupt */
  GIC_ICCEOIR = iarreg;
}

/*************************************************************************
 * Function Name: GIC_Init();
 * Parameters: none
 *
 * Return: none
 *
 * Description: Interrupt Controller init
 *
 *************************************************************************/
void GIC_Init()
{
uint16_t i;

  /* Get max number of valid interrupts */
  int_num = ((GIC_ICDICTR & 0x1F) + 1) * 32;

  /* Initialize Interrupt Security Registers (set all interrupts to be secured) */
  for(i=0;i<8;i++) *((volatile uint32_t*)&GIC_ICDISR0+i) = 0x00000000;

  /* Initialize Interrupt Clear Enable Registers */
  for(i=0;i<8;i++) *((volatile uint32_t*)&GIC_ICDICER0+i) = 0xFFFFFFFF;

  /* Initialize Interrupt Priority Registers (the 5 upper bits used per byte)*/
  for(i=0;i<64;i++) *((volatile uint32_t*)&GIC_ICDIPR0+i) = 0xF8F8F8F8;

  /* CPU Interface: Priority Mask Register (bits 7:3 are valid) */
  /* CPU will be notified for any interrupt with priority level higher than 31 */
  GIC_ICCPMR = 0xF8;

  /* CPU Interface: Binary Point Register */
  /* Separation point for the fractional part of the priority value field */
  /* 3-bits for group priority, 2-bits for subpriotity, preemption enabled */
  GIC_ICCBPR = 4;

  /* CPU Interface Control Register, Enable security interrupts */
  GIC_ICCICR = 1;

  /* Distributor Control Register: Enable = 1 */
  GIC_ICDDCR = 1;

  /* Init interrupt handlers table */
  for(i=0;i<256;i++) INT_Handlers_Table[i] = NoInterrupt_Handler;
}

/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description:
 *
 *************************************************************************/
void main()
{
  /* Disable MMU, enable ICache */
  CP15_Mmu(FALSE);
  CP15_ICache(TRUE);
  CP15_SetVectorBase((uint32_t)__section_begin(".intvec"));

  /* Set Low vectors mode in CP15 Control Register */
  CP15_SetHighVectors(FALSE);

  /* Configure GIC */
  GIC_Init();

  /* Configure LED port GPIO1 */
  CG_OFF_GPIO1 = 0x1;
  SWRST_OFF_GPIO1 = 0x1;
  IO_PIN_SEL3 |= LED_ALLBITS;
  GPIO1_ODATACLR = LED_ALLBITS;
  GPIO1_DIROUT = LED_ALLBITS;

  /* Configure TMR0 */
  CG_OFF_TMR0 = 0x1;
  SWRST_OFF_TMR0 = 0x11;
  CLK_CTRL_TMR0CLK = (1<<16)|(23<<0);
  TMR0_CTRL = 0;
  TMR0_LOAD = 250000uL-1;   /* periodic timer for 250ms */
  TMR0_ISR = 0x1;
  TMR0_CTRL = 0x7;

  /* Configure TMR0 interrupt in GIC */
  INT_Handlers_Table[INTNO_TMR0CNT0] = TMR0_Handler;
  GIC_ICDISER3 |= (1<<(INTNO_TMR0CNT0-96));
  GIC_ICDIPR102 = 0x70;

  __enable_interrupt();

  /* Blink LEDS */
  while(1)
  {
  }
}
