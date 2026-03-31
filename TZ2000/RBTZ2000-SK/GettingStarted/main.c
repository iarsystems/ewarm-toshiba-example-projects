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
 * DESCRIPTION
 * ===========
 * This example project shows how to use the IAR Embedded Workbench for ARM
 * to develop code for the Toshiba RBTZ2000-SK.
 * It shows basic use of I/O, timers, GIC and some core initializations.
 * The two onboard leds start to blink with different frequencies.
 * At this stage the onboard certified SPI_Flash_ROM makes initializations to the system
 * (clock domains init, ddr init etc.).
 *
 * COMPATIBILITY
 * =============
 *   The example project is compatible with Toshiba RBTZ2000-SK board.
 *  By default, the project is configured to use the J-Link JTAG interface.
 *
 * CONFIGURATIONS
 * ==============
 *
 * SRAM Debug:
 *   This configuration is intended for debugging in the internal SRAM non-main memory.
 *
 *   Set DSW1 to: on-off-off-off (boot from SPI)
 *   Set SW1 to:  position 2-3 and 5-6 (boot from SPI_Flash_ROM, CPU_CS0 wired to FLASH_CS1)
 *
 * DDR Debug:
 *   This configuration is intended for debugging in the external DDR3 main memory.
 *
 *   Set DSW1 to: on-off-off-off (boot from SPI)
 *   Set SW1 to:  position 2-3 and 5-6 (boot from SPI_Flash_ROM, CPU_CS0 wired to FLASH_CS1)
 *
 * GETTING STARTED
 * ===============
 *
 * 1) Power-up the board and set JP2 to position 1-2 (non-reset state)
 *
 * 2) Build and download the example.
 *
 * 3) Run the program.
 *
 *
 *    $Revision: 4200 $
 **************************************************************************/

#include "Toshiba/iotz2000XBG.h"
#include <intrinsics.h>
#include <stdint.h>
#include "board.h"
#include "arm_comm.h"
#include "armv7a_cp15_drv.h"

#define MAX_INTS 256

#pragma section = ".intvec"
static void (*INT_Handlers_Table[MAX_INTS])(void);

static uint16_t int_num;

static volatile uint8_t flag0 = 0;
static volatile uint8_t flag1 = 0;

#if 0
/*************************************************************************
 * Function Name: __low_level_init
 * Parameters: none
 *
 * Return: 1 - continue with data initialization
 *         0 - skip data initialization and go to main
 *
 * Description: Low-level initialization.
 *
 *************************************************************************/
int __low_level_init(void)
{
  PMU_ClockGatingOff_telomereSS_0 = 0x00030111;
  PMU_SoftResetOff_telomereSS_0 = 0x00010100;
  return 1;
}
#endif

/*************************************************************************
 * Function Name: NoInterrupt_Handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Empty/Dummy interrupt handler for unused interrupts
 *
 *************************************************************************/
void NoInterrupt_Handler(void){}

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
  flag0 = 1;
  /* Clear TMR0 interrupt bit */
  TMR0_INTSTAT_bit.TIIS = 0;
}

/*************************************************************************
 * Function Name: TMR1_Handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: TMR1 interval interrupt handler
 *
 *************************************************************************/
void TMR1_Handler(void)
{
  flag1 = 1;
  /* Clear TMR1 interrupt bit */
  TMR1_INTSTAT_bit.TIIS = 0;
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
  if((int_id < int_num) && (int_id < MAX_INTS))
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
  int_num = (GIC_ICDICTR_bit.ITLINESNUMBER + 1) * 32;

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

  /* Configure TMR0 */
  TMR0_CTR_bit.CCDE = 1;
  TMR0_CTR_bit.CRE = 1;
  TMR0_CTR_bit.TCE = 0;
  TMR0_COMPA = 0x01000000;
  TMR0_INTM_bit.TIIE = 1;
  TMR0_INTM_bit.TZCE = 1;
  TMR0_CTR_bit.TCE = 1;

  /* Configure TMR1 */
  TMR1_CTR_bit.CCDE = 1;
  TMR1_CTR_bit.CRE = 1;
  TMR1_CTR_bit.TCE = 0;
  TMR1_COMPA = 0x02000000;
  TMR1_INTM_bit.TIIE = 1;
  TMR1_INTM_bit.TZCE = 1;
  TMR1_CTR_bit.TCE = 1;

  /* Configure TMR0 interrupt in GIC */
  INT_Handlers_Table[INT_TMR0] = TMR0_Handler;
  GIC_ICDISER3_bit.INTERRUPT100 = 1;
  GIC_ICDIPR100 = 0x70;

  /* Configure TMR1 interrupt in GIC */
  INT_Handlers_Table[INT_TMR1] = TMR1_Handler;
  GIC_ICDISER3_bit.INTERRUPT101 = 1;
  GIC_ICDIPR101 = 0x70;

  __enable_interrupt();

  /* Configure GPIO LED pins direction */
  LED_DIR = LED_MASK;

  /* Set initial state */
  LED1_OFF();
  LED2_OFF();

  /* Blink LEDS */
  while(1)
  {
    /* Toggle LEDs when flags are set by interrupt handlers */
    if (flag0)
    {
      LED1_TOGGLE();
      flag0 = 0;
    }
    if (flag1)
    {
      LED2_TOGGLE();
      flag1 = 0;
    }
  }
}
