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
 *  ADC Demo program
 *  Opretaion mode = Interrupt or polling mode
 *    ADC_INTERRUPT_MODE = 1 --> Interrupt mode demo
 *    ADC_INTERRUPT_MODE = 0 --> Polling mode demo
 *  VR1 pot position =  0% --> 20% --> 40% --> 60% --> 80% --> 100%
 *    led display =    All OFF ++ LED8 +++ LED7 ++ LED6 ++ LED5
 *
 *  VR2 pot position =  0% --> 20% --> 40% --> 60% --> 80% --> 100%
 *    led display =    All OFF ++ LED4 +++ LED3 ++ LED2 ++ LED1
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
#include "drv_adc.h"
#include "board.h"

/* Private define ------------------------------------------------------------*/
#define ADC_MAXDATA   0xFFE
#define ADC_MINDATA   0x001

/* Private macro -------------------------------------------------------------*/
#define ADC_INTERRUPT_MODE    1
#define TICK_TIME             (10MSEC)
#ifndef USE_WFI
#define USE_WFI               0 // 1: Power save mode, set to 0 when using ICE
#endif

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*************************************************************************
 * Function Name:   disp_vr1_led
 * Parameters:      adc_data - VR1 datafrom ADC
 * Return:          none
 *
 * Description:     Display VR1 data on LED port
 *
 *************************************************************************/
static void disp_vr1_led(uint32_t adc_data)
{
  if (adc_data >= ADC_MAXDATA) adc_data = ADC_MAXDATA;
  if (adc_data < ADC_MINDATA) adc_data = ADC_MINDATA;
  adc_data = (adc_data*100UL)/ADC_MAXDATA;
  if (adc_data >= 20UL)   LED_ON(  LED8 );
  else                    LED_OFF( LED8 );
  if (adc_data >= 40UL)   LED_ON(  LED7 );
  else                    LED_OFF( LED7 );
  if (adc_data >= 60UL)   LED_ON(  LED6 );
  else                    LED_OFF( LED6 );
  if (adc_data >= 80UL)   LED_ON(  LED5 );
  else                    LED_OFF( LED5 );
}

/*************************************************************************
 * Function Name:   disp_vr2_led
 * Parameters:      adc_data - VR2 datafrom ADC
 * Return:          none
 *
 * Description:     Display VR2 data on LED port
 *
 *************************************************************************/
static void disp_vr2_led(uint32_t adc_data)
{
  if (adc_data >= ADC_MAXDATA) adc_data = ADC_MAXDATA;
  if (adc_data < ADC_MINDATA) adc_data = ADC_MINDATA;
  adc_data = (adc_data*100UL)/ADC_MAXDATA;
  if (adc_data >= 20UL)   LED_ON(  LED4 );
  else                    LED_OFF( LED4 );
  if (adc_data >= 40UL)   LED_ON(  LED3 );
  else                    LED_OFF( LED3 );
  if (adc_data >= 60UL)   LED_ON(  LED2 );
  else                    LED_OFF( LED2 );
  if (adc_data >= 80UL)   LED_ON(  LED1 );
  else                    LED_OFF( LED1 );
}

/*************************************************************************
 * Function Name:   INT_ADA_IRQHandler
 * Parameters:      none
 * Return:          none
 *
 * Description:     ADC-A interrupt handler
 *
 *************************************************************************/
#if (ADC_INTERRUPT_MODE==1)
void INT_ADA_IRQHandler(void)
{
  uint32_t vr1_dat, vr2_dat;

  vr1_dat = *((volatile uint32_t *)&ADAREG00 + (VR1_CHNUM&0xF));
  if (vr1_dat & (1UL<<12)) {  /* ADRF==1 */
    vr1_dat = vr1_dat & 0xFFF;
    /* display result on LED port */
    disp_vr1_led(vr1_dat);
    ADC_Start( VR2_CHNUM );   /* Start Next ADC conversion for VR2 */
  }

  vr2_dat = *((volatile uint32_t *)&ADAREG00 + (VR2_CHNUM&0xF));
  if (vr2_dat & (1UL<<12)) {  /* ADRF==1 */
    vr2_dat = vr2_dat & 0xFFF;
    /* display result on LED port */
    disp_vr2_led(vr2_dat);
    ADC_Start( VR1_CHNUM );   /* Start Next ADC conversion for VR1 */
  }
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
 * Description:     ADC Demo sample program main handler
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

  // Setup ADC
  const adc_init_t sAdcSet = {
        .holdtime = ADC_HOLDTM_80,  /* Holdtime = 80 HCLK */
        .adclk =    ADC_FC_4,       /* fc/4 */
  };
  ADC_Init( CH_ADCA, &sAdcSet );

  // Setup LED Port
  LED_INIT();
  LED_OFF( LED_MASK );

  // Setup Switch Port
  PSW_INIT(0);

#if (ADC_INTERRUPT_MODE==1)
  // Interrupt handler setting
  NVIC_SetPriority( INT_ADA,  1<<5 );
  NVIC_ClearPendingIRQ( INT_ADA );
  NVIC_EnableIRQ( INT_ADA );
  __enable_interrupt();
  ADC_Start( VR1_CHNUM );   /* Start VR1 I/P ADC conversion */
  while(1)
  {
#if (USE_WFI==1)
    /* Enter power save mode */
    __WFI();
#endif
  }
#else
#if (USE_WFI==1)
  /* setup system tick timer */
  setup_ticktimer();
#endif

  /* ADC demo program in polling mode */
  while(1) {
    uint32_t vr1_dat, vr2_dat;
    vr1_dat = ADC_Read( VR1_CHNUM );
    vr2_dat = ADC_Read( VR2_CHNUM );
    /* display result on LED port */
    disp_vr1_led(vr1_dat);
    disp_vr2_led(vr2_dat);

#if (USE_WFI==1)
    /* Enter power save mode */
    __WFI();
#endif
  }
#endif
}

