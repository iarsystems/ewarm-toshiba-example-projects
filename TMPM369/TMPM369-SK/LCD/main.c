/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded
 *    Workbench for ARM to develop code for Toshiba TMPM369 family
 *    microcontrollers. It is developed for IAR TMPM369-SK Eval Board.
 *
 *    This example shows how to use driver for character LCD.
 *
 *    History :
 *    1. Date        : 19.01.2012
 *       Author      : Stanimir Bonev
 *       Description : Initial Revision
 *
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "arm_comm.h"
#include "board.h"
#include "drv_nvic.h"
#include "drv_cg.h"
#include "drv_hd44780_l.h"
#include "drv_hd44780.h"

/* Private define ------------------------------------------------------------*/
/* ADC PJ7/AINB11 */
#define ADC_CHANNEL     11
#define ADC_PIN_MASK    (1UL<<7)
#define ADC_IE          PJIE
#define ADC_CR          PJCR
#define ADC_DATA        ADBREG11_bit.ADR

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile int Tick;

const cg_clkinit_t CG_clkinit = {
  .gear = GEAR_FC,
  .fcsel = FCSEL_FPLL,
  .pfsel = FPSEL_FC,
  .prck = PRCK_1,
  .fosc = FOSCSEL_EXTOSC,
  .pll_enable = CG_ENABLE,
  .pllmul = PLLSET_16MHZ_80MHZ,
  .lposc = CG_ENABLE,
  .usbl_clk_sel = CLK_USBPLL,
  .usbpll_enable = CG_ENABLE,
  .usbpllmul = PLLSET_16MHZ,
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
	int result;
	char buffer[HD44780_HORIZONTAL_SIZE + 1];
  /*Watch dog timer disable*/
  WDMOD = 0x00;
  WDCR = 0xB1;
  InitClock(&CG_clkinit);

  /*
  ADC init
  */
  CGSYSCR_bit.FCSTOP = 0; /*Enable ADC Clock*/
  ADBCLK_bit.ADCLK = 1;   /*ADCLOCK = Fc/2*/
  ADBCLK_bit.ADSH = 4;    /*sample hold time = conversion clock * 80*/
  ADBMOD1 = (1<<7);       /*Enable Vref*/
  ADBMOD3_bit.SCAN = 0;   /*Fixed channel mode*/
  ADBMOD3_bit.REPEAT = 0; /*Single conversion mode*/
  ADBMOD2_bit.ADCH = ADC_CHANNEL;  /*Select Channel*/
  /* Pin init as Analog input*/
  ADC_IE &= ~ADC_PIN_MASK;
  ADC_CR &= ~ADC_PIN_MASK;
  /*Start Conversion*/
  ADBMOD0_bit.ADS = 1;

  /* LCD Init */
  HD44780_PowerUpInit();

  /* Show message on the LCD */
  HD44780_StrShow(1, 1,  "  IAR Systems   ");
  HD44780_StrShow(1, 2,  "   TMPM369-SK   ");

	/* dalay 5 sec*/
	DelayResolution100us(50000);
	
  /*Main loop*/
  while(1)
  {
    if(ADBMOD5_bit.EOCF)
    {
      result = ADC_DATA * 3300/4095;
      ADBMOD0_bit.ADS = 1;
      /* resul will hold string lenght */
      result = sprintf(buffer,"ADCB11 %4d mV",result);
      /* clear rest of line */
      memset(buffer + result,' ',sizeof(buffer)-1-result);
      buffer[sizeof(buffer)-1] = '\0';
      /* show adc volatge on LCD line 2 */
	  	HD44780_StrShow(1, 2, (Int8S*)buffer);
			DelayResolution100us(2000);	/* 0.2 sec */
    }
  }
}

/*************************************************************************
 * Function Name: DelayResolution100us
 * Parameters: Int32U Dly
 *
 * Return: none
 *
 * Description: Delay ~ (arg * 100us)
 *
 *************************************************************************/
void DelayResolution100us(Int32U Dly)
{
  for(; Dly; Dly--)
  {
    for(volatile Int32U j = DLY_100US; j; j--)
    {
    }
  }
}
