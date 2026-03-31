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
 *  Rotary Encoder Demo program
 *  Opretaion mode = Interrupt or polling mode
 *    GPIO_MODE = 1 --> GPIO Polling mode demo
 *    GPIO_MODE = 0 --> Interrupt mode demo
 *
 *  JP6    JP7    -> Encoder mode
 * -------------------------------------
 * (1-2)  (1-2)     ROTENC_MODE_PU45 = 1 (GPIO or PHCNT)
 * (2-3)  (2-3)     ROTENC_MODE_PU45 = 0 (GPIO or Interrupt mode)
 * -------------------------------------
 *
 * Rotary Encoder data reading is noise-free and accurate with PHCNT mode.
 *
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
#define GPIO_MODE             0
#define TICK_TIME         (10MSEC)
#define ROTENC_MODE_PU45      1
#ifndef USE_WFI
#define USE_WFI               0 // 1: Power save mode, set to 0 when using ICE
#endif

/* Private define ------------------------------------------------------------*/
#if (ROTENC_MODE_PU45 == 1)
#define PIN_ROTENC_IN_A     CH_PU(4)
#define PIN_ROTENC_IN_B     CH_PU(5)
#else
#define PIN_ROTENC_IN_A     CH_PR(6)
#define PIN_ROTENC_IN_B     CH_PR(7)
#endif

#define ROTENC_POS(a,b)     ((((a)<<1)|(b))&3)


/* Private variables ---------------------------------------------------------*/
uint32_t up_count = 0;
uint32_t down_count = 0;
uint8_t last_pos;
uint8_t led_pos = 0;

#if ((GPIO_MODE==0)&&(ROTENC_MODE_PU45 == 0))
uint8_t inA_sts;
uint8_t inB_sts;
#endif

const uint8_t encdef_tbl[4] = { /* up  down */
              0x12,             /* 1    2   */
              0x30,             /* 3    0   */
              0x03,             /* 0    3   */
              0x21              /* 2    1   */
  };
const uint8_t led_mask_tbl[] = { LED4, LED3, LED2, LED1, LED8, LED7, LED6, LED5 };


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*************************************************************************
 * Function Name:   upcnt_handler
 * Parameters:      none
 * Return:          none
 *
 * Description:     Handle Rotary Encoder Up Count event
 *
 *************************************************************************/
void upcnt_handler(void)
{
  LED_OFF( led_mask_tbl[led_pos] );
  led_pos = (led_pos+1)%8;
  LED_ON( led_mask_tbl[led_pos] );


}

/*************************************************************************
 * Function Name:   downcnt_handler
 * Parameters:      none
 * Return:          none
 *
 * Description:     Handle Rotary Encoder Down Count event
 *
 *************************************************************************/
void downcnt_handler(void)
{
  LED_OFF( led_mask_tbl[led_pos] );
  led_pos = (led_pos==0? 7:(led_pos-1)%8);
  LED_ON( led_mask_tbl[led_pos] );

}

/*************************************************************************
 * Function Name:   rotencoder_handler
 * Parameters:      pos - new position
 * Return:          none
 *
 * Description:     Handle Rotary Encoder event
 *
 *************************************************************************/
void rotencoder_handler(uint8_t pos)
{
  if (last_pos == ((encdef_tbl[pos]>>4)&0xF)) {
    if (!((++up_count)%4)) {
      upcnt_handler();
    }
  }
  else if (last_pos == (encdef_tbl[pos]&0xF)) {
    if (!((++down_count)%4)) {
      downcnt_handler();
    }
  }
  last_pos = pos;
}


#if (GPIO_MODE==0)
#if (ROTENC_MODE_PU45 == 0)
/*************************************************************************
 * Function Name:   INT_3_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     CH_PR(6) INT3 interrupt handler
 *
 *************************************************************************/
void INT_3_IRQHandler(void)
{
  NVIC_ClearTrigIRQ( INT_3 );
  if (inA_sts) {
    NVIC_SetTrigMode( INT_3,  TRIG_RISING );
  }
  else {
    NVIC_SetTrigMode( INT_3,  TRIG_FALLING );
  }
  inA_sts = !inA_sts&1;
  rotencoder_handler( ROTENC_POS(inA_sts,inB_sts) );
}

/*************************************************************************
 * Function Name:   INT_4_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     CH_PR(7) INT4 interrupt handler
 *
 *************************************************************************/
void INT_4_IRQHandler(void)
{
  NVIC_ClearTrigIRQ( INT_4 );
  if (inB_sts) {
    NVIC_SetTrigMode( INT_4,  TRIG_RISING );
  }
  else {
    NVIC_SetTrigMode( INT_4,  TRIG_FALLING );
  }
  inB_sts = !inB_sts&1;
  rotencoder_handler( ROTENC_POS(inA_sts,inB_sts) );
}

#else /* #if (ROTENC_MODE_PU45 == 0) */

/*************************************************************************
 * Function Name:   INT_PHC0EVRY_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     PHCNT0 interrupt handler
 *
 *************************************************************************/
void INT_PHC0EVRY_IRQHandler(void)
{
  static uint32_t last_cnt = 0x8000/4;
  uint32_t now_cnt;
  NVIC_ClearTrigIRQ( INT_PHC0EVRY );
  if (PHC0FLG_bit.OVF || PHC0FLG_bit.UDF) {
    PHC0RUN_bit.PHCRUN = 0;
    last_cnt = 0x8000;
    PHC0RUN_bit.PHCRUN = 1;
  }
  now_cnt = (0xFFFFUL-PHC0CNT_bit.PHCCNT)/4;
  if (now_cnt > last_cnt) {
    upcnt_handler();
  }
  else if (now_cnt < last_cnt) {
    downcnt_handler();
  }
  last_cnt = now_cnt;
}
#endif
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
 * Description:     Rotary Encoder Demo sample program main handler
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
  LED_OFF( LED_MASK & ~LED4 );
  LED_ON( LED4 );   /* center LED turned ON */

  // Setup Switch Port
  PSW_INIT(0);

#if (GPIO_MODE==0)
  last_pos = 3;

#if (ROTENC_MODE_PU45 == 1)
  const gpio_init_t initport = {
      .mode =     PMODE_FR1,
      .pull =     PIN_PUP,
  };
  GPIO_SetMode( PIN_ROTENC_IN_A, &initport );
  GPIO_SetMode( PIN_ROTENC_IN_B, &initport );

  // Setup PHCNT0
  PHC0EN_bit.PHCEN = 1;
  PHC0RUN = 0;
  PHC0CR_bit.PHCMD = 1;
  PHC0CR_bit.NFOFF = 0;
  PHC0CR_bit.EVRYINT = 1;

  // Interrupt handler setting
  NVIC_SetPriority( INT_PHC0EVRY,  2<<5 );
  // Set to Low Trigger mode
  NVIC_SetTrigMode( INT_PHC0EVRY,  TRIG_FALLING );
  // Clear the interrupt status
  NVIC_ClearPendingIRQ( INT_PHC0EVRY );
  NVIC_EnableIRQ( INT_PHC0EVRY );

  PHC0RUN_bit.PHCRUN = 1;


#else /* (ROTENC_MODE_PU45 == 1) */
  inA_sts = 1;
  inB_sts = 1;

  const gpio_init_t initport = {
      .mode =     PMODE_FR3,
      .pull =     PIN_PUP,
  };
  GPIO_SetMode( PIN_ROTENC_IN_A, &initport );
  GPIO_SetMode( PIN_ROTENC_IN_B, &initport );

  // Interrupt handler setting
  NVIC_SetPriority( INT_3,  3<<5 );
  NVIC_SetPriority( INT_4,  2<<5 );

  // Set to Low Trigger mode
  NVIC_SetTrigMode( INT_3,  TRIG_FALLING );
  NVIC_SetTrigMode( INT_4,  TRIG_FALLING );

  // Clear the interrupt status
  NVIC_ClearPendingIRQ( INT_3 );
  NVIC_ClearPendingIRQ( INT_4 );
  NVIC_ClearTrigIRQ( INT_3 );
  NVIC_ClearTrigIRQ( INT_4 );

  NVIC_EnableIRQ( INT_3 );
  NVIC_EnableIRQ( INT_4 );

#endif  /* (ROTENC_MODE_PU45 == 1) */

  __enable_interrupt();
  while(1)
  {
#if (USE_WFI==1)
    /* Enter power save mode */
    __WFI();
#endif
  }
#else   /* #if (GPIO_MODE==0) */
  const gpio_init_t initport = {
      .mode =     PMODE_INPUT,
      .pull =     PIN_PUP,
  };
  GPIO_SetMode( PIN_ROTENC_IN_A, &initport );
  GPIO_SetMode( PIN_ROTENC_IN_B, &initport );

#if (USE_WFI==1)
  /* setup system tick timer */
  setup_ticktimer();
#endif

  last_pos = ROTENC_POS( GPIO_ReadData(PIN_ROTENC_IN_A),
                        GPIO_ReadData(PIN_ROTENC_IN_B) );

  /* Rotary Encoder demo program in polling mode */
  uint8_t new_pos1, new_pos;
  volatile int dmy;
  while(1) {
    new_pos1 = ROTENC_POS( GPIO_ReadData(PIN_ROTENC_IN_A),
                          GPIO_ReadData(PIN_ROTENC_IN_B) );
    // small delay and recheck for noise filtering
    for (dmy=0; dmy<100; dmy++);
    new_pos = ROTENC_POS( GPIO_ReadData(PIN_ROTENC_IN_A),
                          GPIO_ReadData(PIN_ROTENC_IN_B) );
    if (new_pos != new_pos1) {
      continue;   /* false signal or noise */
    }
    if (new_pos != last_pos) {
      rotencoder_handler(new_pos);
    }

#if (USE_WFI==1)
    /* Enter power save mode */
    __WFI();
#endif
  }
#endif
}

