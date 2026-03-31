/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM440
 *    family microcontrollers.
 *    It is developed for IAR TMPM440-SK Evaluation Board.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 15.08.2012
 *       Author      : Santosh Pawar
 *       Description : Adapted for TMPM440-SK
 *
 *
 *    $Revision: 2824 $
 **************************************************************************/
/*
 *  GPIO Demo program
 *  Opretaion mode = Interrupt or polling mode
 *    GPIO_INTERRUPT_MODE = 1 --> Interrupt mode demo
 *    GPIO_INTERRUPT_MODE = 0 --> Polling mode demo
 *  Push Swich to turn ON LED.
 *    Switch =  PSW8 - PSW7 - PSW6 - PSW5 - PSW4 - PSW3 - PSW2 - PSW1
 *    LED    =  LED8 - LED7 - LED6 - LED5 - LED4 - LED3 - LED2 - LED1
 *
 *  LED is ON until switch is pressed.
 *  LED is OFF on switch release
 *
 * Power Save mode:
 *    USE_WFI = 0   : Power save mode disabled in debug operation
 *    USE_WFI = 1   : Power save mode enabled. System tick timer used to
 *                    wakeup CPU for polling operation.
 *                    Tick time defined with TICK_TIME macro.
 */
/** include files **/
#include <stdio.h>
#include <stdint.h>
#include <Toshiba/iotmpm440FxXBG.h>
#include "drv_nvic.h"
#include "drv_cg.h"
#include "drv_gpio.h"
#include "board.h"

/* Private macro -------------------------------------------------------------*/
#define GPIO_INTERRUPT_MODE   1
#define TICK_TIME             (10MSEC)
#ifndef USE_WFI
#define USE_WFI               0 // 1: Power save mode, set to 0 when using ICE
#endif

/* Private define ------------------------------------------------------------*/

#if (GPIO_INTERRUPT_MODE==1)
//#define SW_ON_TRGMODE     (TRIG_RISING)
//#define SW_OFF_TRGMODE    (TRIG_FALLING)
#define SW_ON_TRGMODE     (TRIG_LOW)
#define SW_OFF_TRGMODE    (TRIG_HIGH)
#endif

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

#if (GPIO_INTERRUPT_MODE==1)
/*************************************************************************
 * Function Name:   INT_5_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PSW1 interrupt handler
 *
 *************************************************************************/
void INT_5_IRQHandler(void)
{
  static uint8_t psw1_trgsts = 0;
  NVIC_ClearTrigIRQ( INT_PSW1 );
  if (psw1_trgsts) {
    LED_OFF( LED1 );
    NVIC_SetTrigMode( INT_PSW1,  SW_ON_TRGMODE );
  }
  else {
    LED_ON( LED1 );
    NVIC_SetTrigMode( INT_PSW1,  SW_OFF_TRGMODE );
  }
  psw1_trgsts = !psw1_trgsts;
}

/*************************************************************************
 * Function Name:   INT_6_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PSW2 interrupt handler
 *
 *************************************************************************/
void INT_6_IRQHandler(void)
{
  static uint8_t psw2_trgsts = 0;
  NVIC_ClearTrigIRQ( INT_PSW2 );
  if (psw2_trgsts) {
    LED_OFF( LED2 );
    NVIC_SetTrigMode( INT_PSW2,  SW_ON_TRGMODE );
  }
  else {
    LED_ON( LED2 );
    NVIC_SetTrigMode( INT_PSW2,  SW_OFF_TRGMODE );
  }
  psw2_trgsts = !psw2_trgsts;
}

/*************************************************************************
 * Function Name:   INT_7_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PSW3 interrupt handler
 *
 *************************************************************************/
void INT_7_IRQHandler(void)
{
  static uint8_t psw3_trgsts = 0;
  NVIC_ClearTrigIRQ( INT_PSW3 );
  if (psw3_trgsts) {
    LED_OFF( LED3 );
    NVIC_SetTrigMode( INT_PSW3,  SW_ON_TRGMODE );
  }
  else {
    LED_ON( LED3 );
    NVIC_SetTrigMode( INT_PSW3,  SW_OFF_TRGMODE );
  }
  psw3_trgsts = !psw3_trgsts;
}

/*************************************************************************
 * Function Name:   INT_8_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PSW4 interrupt handler
 *
 *************************************************************************/
void INT_8_IRQHandler(void)
{
  static uint8_t psw4_trgsts = 0;
  NVIC_ClearTrigIRQ( INT_PSW4 );
  if (psw4_trgsts) {
    LED_OFF( LED4 );
    NVIC_SetTrigMode( INT_PSW4,  SW_ON_TRGMODE );
  }
  else {
    LED_ON( LED4 );
    NVIC_SetTrigMode( INT_PSW4,  SW_OFF_TRGMODE );
  }
  psw4_trgsts = !psw4_trgsts;
}

/*************************************************************************
 * Function Name:   INT_9_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PSW5 interrupt handler
 *
 *************************************************************************/
void INT_9_IRQHandler(void)
{
  static uint8_t psw5_trgsts = 0;
  NVIC_ClearTrigIRQ( INT_PSW5 );
  if (psw5_trgsts) {
    LED_OFF( LED5 );
    NVIC_SetTrigMode( INT_PSW5,  SW_ON_TRGMODE );
  }
  else {
    LED_ON( LED5 );
    NVIC_SetTrigMode( INT_PSW5,  SW_OFF_TRGMODE );
  }
  psw5_trgsts = !psw5_trgsts;
}

/*************************************************************************
 * Function Name:   INT_A_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PSW6 interrupt handler
 *
 *************************************************************************/
void INT_A_IRQHandler(void)
{
  static uint8_t psw6_trgsts = 0;
  NVIC_ClearTrigIRQ( INT_PSW6 );
  if (psw6_trgsts) {
    LED_OFF( LED6 );
    NVIC_SetTrigMode( INT_PSW6,  SW_ON_TRGMODE );
  }
  else {
    LED_ON( LED6 );
    NVIC_SetTrigMode( INT_PSW6,  SW_OFF_TRGMODE );
  }
  psw6_trgsts = !psw6_trgsts;
}

/*************************************************************************
 * Function Name:   INT_B_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PSW7 interrupt handler
 *
 *************************************************************************/
void INT_B_IRQHandler(void)
{
  static uint8_t psw7_trgsts = 0;
  NVIC_ClearTrigIRQ( INT_PSW7 );
  if (psw7_trgsts) {
    LED_OFF( LED7 );
    NVIC_SetTrigMode( INT_PSW7,  SW_ON_TRGMODE );
  }
  else {
    LED_ON( LED7 );
    NVIC_SetTrigMode( INT_PSW7,  SW_OFF_TRGMODE );
  }
  psw7_trgsts = !psw7_trgsts;
}

/*************************************************************************
 * Function Name:   INT_C_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PSW8 interrupt handler
 *
 *************************************************************************/
void INT_C_IRQHandler(void)
{
  static uint8_t psw8_trgsts = 0;
  NVIC_ClearTrigIRQ( INT_PSW8 );
  if (psw8_trgsts) {
    LED_OFF( LED8 );
    NVIC_SetTrigMode( INT_PSW8,  SW_ON_TRGMODE );
  }
  else {
    LED_ON( LED8 );
    NVIC_SetTrigMode( INT_PSW8,  SW_OFF_TRGMODE );
  }
  psw8_trgsts = !psw8_trgsts;
}


#else /* Polling mode */
#if (USE_WFI==1)
/*************************************************************************
 * Function Name:   setup_ticktimer
 * Parameters:      none
 * Return:          none
 *
 * Description:     Setup Tick Timer
 *
 *************************************************************************/
static void setup_ticktimer(void)
{
  uint32_t syscount = CG_GetClock( CLK_FSYS )/TICK_TIME;
  SYSTICKCSR_bit.ENABLE = 0;
  SYSTICKCSR_bit.CLKSOURCE = 1;
  SYSTICKRVR_bit.RELOAD = syscount;
  SYSTICKCVR_bit.CURRENT = syscount;
  SYSTICKCSR_bit.TICKINT = 1;
  SYSTICKCSR_bit.ENABLE = 1;
}
#endif  /* (USE_WFI==1) */
#endif

/*************************************************************************
 * Function Name:   main
 * Parameters:      none
 * Return:          none
 *
 * Description:     GPIO Demo sample program main handler
 *
 *************************************************************************/
int main(void)
{

  __disable_interrupt();
  WDMOD = 0;
  WDCR  = 0xB1;
  NVIC_Init();

  // Setup PLL controller
  const cg_clkinit_t sClkSet = {
        .fosc =     FOSCSEL_EXTOSC, /* External Oscillator */
        .pll0 =     CG_ENABLE,      /* PLL0 Enable */
        .pll1 =     CG_ENABLE,      /* PLL1 Enable */
        .pll0mul =  PLLMUL_10,      /* PLL0 mul = 10 */
        .pll1mul =  PLLMUL_10,      /* PLL1 mul = 10 */
        .pfsel =    FPSEL_FGEAR,    /* select fgear as periph divider */
        .gear =     GEAR_FC,      /* gear = fc */
        .prck =     PRCK_2,       /* peripheral gear = fc/2 */
        .scock =    STOP_SCO,     /* SCO clock disable */
  };
  InitClock( &sClkSet );

  // Setup LED Port
  LED_INIT();
  LED_OFF( LED_MASK );

#if (GPIO_INTERRUPT_MODE==1)
  // Setup Switch Port in interrupt mode
  PSW_INIT(1);

  // Interrupt handler setting
  NVIC_SetPriority( INT_PSW1,  2<<5 );
  NVIC_SetPriority( INT_PSW2,  2<<5 );
  NVIC_SetPriority( INT_PSW3,  2<<5 );
  NVIC_SetPriority( INT_PSW4,  2<<5 );
  NVIC_SetPriority( INT_PSW5,  2<<5 );
  NVIC_SetPriority( INT_PSW6,  2<<5 );
  NVIC_SetPriority( INT_PSW7,  2<<5 );
  NVIC_SetPriority( INT_PSW8,  2<<5 );

  // Set to Low Trigger mode
  NVIC_SetTrigMode( INT_PSW1,  SW_ON_TRGMODE );
  NVIC_SetTrigMode( INT_PSW2,  SW_ON_TRGMODE );
  NVIC_SetTrigMode( INT_PSW3,  SW_ON_TRGMODE );
  NVIC_SetTrigMode( INT_PSW4,  SW_ON_TRGMODE );
  NVIC_SetTrigMode( INT_PSW5,  SW_ON_TRGMODE );
  NVIC_SetTrigMode( INT_PSW6,  SW_ON_TRGMODE );
  NVIC_SetTrigMode( INT_PSW7,  SW_ON_TRGMODE );
  NVIC_SetTrigMode( INT_PSW8,  SW_ON_TRGMODE );

  // Clear the interrupt status
  NVIC_ClearPendingIRQ( INT_PSW1 );
  NVIC_ClearPendingIRQ( INT_PSW2 );
  NVIC_ClearPendingIRQ( INT_PSW3 );
  NVIC_ClearPendingIRQ( INT_PSW4 );
  NVIC_ClearPendingIRQ( INT_PSW5 );
  NVIC_ClearPendingIRQ( INT_PSW6 );
  NVIC_ClearPendingIRQ( INT_PSW7 );
  NVIC_ClearPendingIRQ( INT_PSW8 );

  NVIC_EnableIRQ( INT_PSW1 );
  NVIC_EnableIRQ( INT_PSW2 );
  NVIC_EnableIRQ( INT_PSW3 );
  NVIC_EnableIRQ( INT_PSW4 );
  NVIC_EnableIRQ( INT_PSW5 );
  NVIC_EnableIRQ( INT_PSW6 );
  NVIC_EnableIRQ( INT_PSW7 );
  NVIC_EnableIRQ( INT_PSW8 );

  __enable_interrupt();
  while(1)
  {
#if (USE_WFI==1)
    /* Enter power save mode */
    __WFI();
#endif
  }
#else
  // Setup Switch Port
  PSW_INIT(0);

#if (USE_WFI==1)
  /* setup system tick timer */
  setup_ticktimer();
#endif

  /* GPIO demo program in polling mode */
  while(1) {
    uint8_t sw_sts;
    sw_sts = PSW_GETSTS( PSW_MASK );
    LED_OFF( ~sw_sts );
    LED_ON(  sw_sts );
#if (USE_WFI==1)
    /* Enter power save mode */
    __WFI();
#endif
  }
#endif
}

