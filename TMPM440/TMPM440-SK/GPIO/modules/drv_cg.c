/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : drv_cg.c
 *    Description : Toshiba TMPM440 Clock/Mode Control Driver
 *
 *    History :
 *    1. Date        : 7.2013
 *       Author      : Santosh Pawar
 *       Description : initial revision
 *
 **************************************************************************/
/** include files **/
#include <stdint.h>
#include <Toshiba\iotmpm440FxXBG.h>
#include <assert.h>
#include "drv_cg.h"
#include "board.h"

/** local definitions **/
#define PLL0SET_IN8M_OUT40M       0x7426
#define PLL0SET_IN8M_OUT48M       0x782E
#define PLL0SET_IN8M_OUT64M       0x78BE
#define PLL0SET_IN8M_OUT80M       0x704D
#define PLL0SET_IN10M_OUT50M      0x7426
#define PLL0SET_IN10M_OUT60M      0x782E
#define PLL0SET_IN10M_OUT80M      0x603D
#define PLL0SET_IN10M_OUT100M     0x704D

#define PLL1SETH_IN8M_OUT64M      0x0C
#define PLL1SETH_IN8M_OUT80M      0x0E
#define PLL1SETH_IN10M_OUT80M     0x0C
#define PLL1SETH_IN10M_OUT100M    0x0E

#define PLL1SETL_IN8M_OUT64M      0x01E
#define PLL1SETL_IN8M_OUT80M      0x026
#define PLL1SETL_IN10M_OUT80M     0x01E
#define PLL1SETL_IN10M_OUT100M    0x026



/** default settings **/

/** external functions **/

/** external data **/

/** internal functions **/

/** public data **/

/** private data **/

/** public functions **/
/*************************************************************************
 * Function Name: InitClock
 * Parameters:    clkinit - setup parameters
 * Return:      none
 *
 * Description:   Setup Clock controller as per specified parameters
 *
 *************************************************************************/
void InitClock(const cg_clkinit_t * clkinit)
{
  /*Enable CG registers write*/
  CGPROTECT = 0xC1;

  /*Stop PLL0, PLL1*/
  CGPLLSEL_bit.PLL0SEL = 0;
  CGOSCCR_bit.PLL0ON = 0;
  CGPLLSEL_bit.PLL1SEL = 0;
  CGOSCCR_bit.PLL1ON = 0;

  if (clkinit->fosc == FOSCSEL_INTOSC) {
    CGOSCCR_bit.OSCSEL = 0;
    /* PLL is not set for internal oscillator */
  }
  else { /* External oscillator */
    /*External oscilator enable*/
    CGOSCCR_bit.EHOSCSEL = 1;
    CGOSCCR_bit.XEN1 = 1;
    /*Selects warm-up counter by external oscillator*/
    CGOSCCR_bit.WUPT = 256; /*wait some clocks from external oscilatior*/
    /*Start warm up*/
    CGOSCCR_bit.WUEON = 1;
    while(CGOSCCR_bit.WUEF)
    {}
    /*select external oscilator as clock*/
    CGOSCCR_bit.OSCSEL = 1;

    if (clkinit->pll0 == CG_ENABLE) {
      /*Disable PLL*/
      CGPLLSEL_bit.PLL0SEL = 0;
      CGOSCCR_bit.PLL0ON = 0;
      /* setup multiplier */
      switch (clkinit->pll0mul) {
      case PLLMUL_10:
        if (EHOSC==(10MHZ))
          CGPLLSEL_bit.PLL0SET = PLL0SET_IN10M_OUT100M;
        else
          CGPLLSEL_bit.PLL0SET = PLL0SET_IN8M_OUT80M;
        break;
      case PLLMUL_8:
        if (EHOSC==(10MHZ))
          CGPLLSEL_bit.PLL0SET = PLL0SET_IN10M_OUT80M;
        else
          CGPLLSEL_bit.PLL0SET = PLL0SET_IN8M_OUT64M;
        break;
      case PLLMUL_6:
        if (EHOSC==(10MHZ))
          CGPLLSEL_bit.PLL0SET = PLL0SET_IN10M_OUT60M;
        else
          CGPLLSEL_bit.PLL0SET = PLL0SET_IN8M_OUT48M;
        break;
      default:
        if (EHOSC==(10MHZ))
          CGPLLSEL_bit.PLL0SET = PLL0SET_IN10M_OUT50M;
        else
          CGPLLSEL_bit.PLL0SET = PLL0SET_IN8M_OUT40M;
        break;
      }
    }

    if (clkinit->pll1 == CG_ENABLE) {
      /*Disable PLL1*/
      CGPLLSEL_bit.PLL1SEL = 0;
      CGOSCCR_bit.PLL1ON = 0;
      /* setup multiplier */
      switch (clkinit->pll1mul) {
      case PLLMUL_10:
        if (EHOSC==(10MHZ)) {
          CGPLLSEL_bit.PLL1SETH = PLL1SETH_IN10M_OUT100M;
          CGPLLSEL_bit.PLL1SETL = PLL1SETL_IN10M_OUT100M;
        }
        else {
          CGPLLSEL_bit.PLL1SETH = PLL1SETH_IN8M_OUT80M;
          CGPLLSEL_bit.PLL1SETL = PLL1SETL_IN8M_OUT80M;
        }
        break;
      default:
        if (EHOSC==(10MHZ)) {
          CGPLLSEL_bit.PLL1SETH = PLL1SETH_IN10M_OUT80M;
          CGPLLSEL_bit.PLL1SETL = PLL1SETL_IN10M_OUT80M;
        }
        else {
          CGPLLSEL_bit.PLL1SETH = PLL1SETH_IN8M_OUT64M;
          CGPLLSEL_bit.PLL1SETL = PLL1SETL_IN8M_OUT64M;
        }
        break;
      }
    }

    if ((clkinit->pll0 == CG_ENABLE) ||
        (clkinit->pll1 == CG_ENABLE)) {
      /*wait to lock 100us*/
      CGOSCCR_bit.WUPT = 100*EHOSC/1000000;
      /*Start warm up*/
      CGOSCCR_bit.WUEON = 1;
      while(CGOSCCR_bit.WUEF)
      {}
    }

    if (clkinit->pll0 == CG_ENABLE) {
      /*start PLL*/
      CGOSCCR_bit.PLL0ON = 1;
    }
    if (clkinit->pll1 == CG_ENABLE) {
      /*start PLL1*/
      CGOSCCR_bit.PLL1ON = 1;
    }

    if ((clkinit->pll0 == CG_ENABLE) ||
        (clkinit->pll1 == CG_ENABLE)) {
      /*wait to lock 100us*/
      CGOSCCR_bit.WUPT = 100*EHOSC/1000000;
      /*Start warm up*/
      CGOSCCR_bit.WUEON = 1;
      while(CGOSCCR_bit.WUEF)
      {}
    }
  }

  /*Set Prescalers*/
  CGSYSCR_bit.GEAR = clkinit->gear;
  CGSYSCR_bit.PRCK = clkinit->prck;
  CGSYSCR_bit.FPSEL0 = clkinit->pfsel;
  CGSYSCR_bit.PSCSTOP = 0;
  CGSYSCR_bit.FCSTOP0 = 0;
  CGSYSCR_bit.FCSTOP1 = 0;
  CGSYSCR_bit.FCSTOP2 = 0;
  CGSYSCR_bit.SCOSEL = clkinit->scock;

  if (clkinit->fosc == FOSCSEL_EXTOSC) {
    if (clkinit->pll0 == CG_ENABLE) {
      /*select PLL0*/
      CGPLLSEL_bit.PLL0SEL = 1;
    }
    if (clkinit->pll1 == CG_ENABLE) {
      /*select PLL1*/
      CGPLLSEL_bit.PLL1SEL = 1;
    }
  }
}

/*************************************************************************
 * Function Name:   CG_GetClock
 * Parameters:    cg_clk_t clock - clock to get
 *
 * Return: int clock frequency in Hz
 *
 * Description:   get clock frequency
 *
 *
 *************************************************************************/
int CG_GetClock(cg_clk_t clock)
{
  int freq = 0;
  switch (clock) {
  case CLK_FOCS:      /*fosc clock*/
    if(CGOSCCR_bit.OSCSEL) { /*External osc*/
      freq =  EHOSC;
    }
    else {/*Internal osc*/
      freq =  IHOSC;
    }
    break ;

  case CLK_FPLL0:     /*fpll0 clock*/
    if(CGOSCCR_bit.PLL0ON) {  /*PLL0 is on*/
      if ((PLL0SET_IN8M_OUT40M == CGPLLSEL_bit.PLL0SET)||
          (PLL0SET_IN10M_OUT50M == CGPLLSEL_bit.PLL0SET)) { /* mul 5 */
        freq = 5*EHOSC;
      }
      else if ((PLL0SET_IN8M_OUT48M == CGPLLSEL_bit.PLL0SET)||
               (PLL0SET_IN10M_OUT60M == CGPLLSEL_bit.PLL0SET)) { /* mul 6 */
        freq = 6*EHOSC;
      }
      else if ((PLL0SET_IN8M_OUT64M == CGPLLSEL_bit.PLL0SET)||
               (PLL0SET_IN10M_OUT80M == CGPLLSEL_bit.PLL0SET)) { /* mul 8 */
        freq = 8*EHOSC;
      }
      else if ((PLL0SET_IN8M_OUT80M == CGPLLSEL_bit.PLL0SET)||
               (PLL0SET_IN10M_OUT100M == CGPLLSEL_bit.PLL0SET)) { /* mul 10 */
        freq = 10*EHOSC;
      }
    }
    break;

  case CLK_FPLL1:     /*fpll1 clock*/
    if(CGOSCCR_bit.PLL1ON) {  /*PLL1 is on*/
      if ((PLL1SETL_IN8M_OUT64M == CGPLLSEL_bit.PLL1SETL)||
          (PLL1SETL_IN10M_OUT80M == CGPLLSEL_bit.PLL1SETL)) { /* mul 8 */
        freq = 8*EHOSC;
      }
      else if ((PLL1SETL_IN8M_OUT80M == CGPLLSEL_bit.PLL1SETL)||
               (PLL1SETL_IN10M_OUT100M == CGPLLSEL_bit.PLL1SETL)) { /* mul 10 */
        freq = 10*EHOSC;
      }
    }
    break;

  case CLK_FC:        /*fc clock*/
    if (CGPLLSEL_bit.PLL0SEL) {/*fpll is fc clock*/
      freq = CG_GetClock(CLK_FPLL0);
    }
    else {/*fosc is fc clock*/
      freq = CG_GetClock(CLK_FOCS);
    }
    break;

  case CLK_FSYS:      /*fsys clock*/
    switch(CGSYSCR_bit.GEAR) {
    case GEAR_FC:     /*fc is fsys clock*/
      freq = CG_GetClock(CLK_FC);
      break;
      case GEAR_FC_2:   /*fc/2 is fsys clock*/
      case GEAR_FC_4:   /*fc/4 is fsys clock*/
      case GEAR_FC_8:   /*fc/8 is fsys clock*/
      case GEAR_FC_16:  /*fc/16 is fsys clock*/
        freq = CG_GetClock(CLK_FC)>>((CGSYSCR_bit.GEAR&0x3)+1);
        break;
    }
    break;

  case CLK_FPERIPH:     /*fperiph clock*/
    if (CGSYSCR_bit.FPSEL0) { /*fc as periph divider input*/
      freq = CG_GetClock(CLK_FC);
    }
    else {  /*fgear as periph divider input*/
      freq = CG_GetClock(CLK_FSYS);
    }
    break;

  case CLK_TO:
    freq = CG_GetClock(CLK_FPERIPH) >> CGSYSCR_bit.PRCK;
    break;

  case CLK_TMRD:
    freq = CG_GetClock(CLK_FC) >> CGPWMGEAR_bit.TMRDGEAR;
    break;
  }

  return freq;
}

/*************************************************************************
 * Function Name: fclk_ena_tmrd
 * Parameters:    gear  - setup parameters
 * Return:      none
 *
 * Description:   Setup TMRD Clock control as per specified parameters
 *
 *************************************************************************/
void fclk_ena_tmrd(const tmrd_gear_t gear)
{
  CGFCMSKA_bit.TMRD = 1;
  CGPWMGEAR_bit.TMRDCLKEN = 0;
  CGPWMGEAR_bit.TMRDGEAR = gear;
  CGPWMGEAR_bit.TMRDCLKEN = 1;
  CGFCMSKA_bit.TMRD = 0;
}

/*************************************************************************
 * Function Name: fclk_dis_tmrd
 * Parameters:    none
 * Return:      none
 *
 * Description:   Disable clock to TMRD
 *
 *************************************************************************/
void fclk_dis_tmrd(void)
{
  CGFCMSKA_bit.TMRD = 1;
  CGPWMGEAR_bit.TMRDCLKEN = 0;
}

/*************************************************************************
 * Function Name: fclk_ena_tmrb
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Enable clock to TMRB of specified channel
 *
 *************************************************************************/
void fclk_ena_tmrb(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_TMRB(0)) {
    CGFCMSKA_bit.TMRB00 = 0;
  }
  if (portnum_msk & FCLK_TMRB(0)) {
    CGFCMSKA_bit.TMRB01 = 0;
  }
  if (portnum_msk & FCLK_TMRB(2)) {
    CGFCMSKA_bit.TMRB02 = 0;
  }
  if (portnum_msk & FCLK_TMRB(3)) {
    CGFCMSKA_bit.TMRB03 = 0;
  }
  if (portnum_msk & FCLK_TMRB(4)) {
    CGFCMSKA_bit.TMRB04 = 0;
  }
  if (portnum_msk & FCLK_TMRB(5)) {
    CGFCMSKA_bit.TMRB05 = 0;
  }
  if (portnum_msk & FCLK_TMRB(6)) {
    CGFCMSKA_bit.TMRB06 = 0;
  }
  if (portnum_msk & FCLK_TMRB(7)) {
    CGFCMSKA_bit.TMRB07 = 0;
  }
  if (portnum_msk & FCLK_TMRB(8)) {
    CGFCMSKA_bit.TMRB08 = 0;
  }
  if (portnum_msk & FCLK_TMRB(9)) {
    CGFCMSKA_bit.TMRB09 = 0;
  }
  if (portnum_msk & FCLK_TMRB(10)) {
    CGFCLKMSKA_bit.TMRB10 = 0;
  }
  if (portnum_msk & FCLK_TMRB(11)) {
    CGFCLKMSKA_bit.TMRB11 = 0;
  }
  if (portnum_msk & FCLK_TMRB(12)) {
    CGFCLKMSKA_bit.TMRB12 = 0;
  }
  if (portnum_msk & FCLK_TMRB(13)) {
    CGFCLKMSKA_bit.TMRB13 = 0;
  }
  if (portnum_msk & FCLK_TMRB(14)) {
    CGFCLKMSKA_bit.TMRB14 = 0;
  }
  if (portnum_msk & FCLK_TMRB(15)) {
    CGFCLKMSKA_bit.TMRB15 = 0;
  }
  if (portnum_msk & FCLK_TMRB(16)) {
    CGFCLKMSKA_bit.TMRB16 = 0;
  }
  if (portnum_msk & FCLK_TMRB(17)) {
    CGFCLKMSKA_bit.TMRB17 = 0;
  }
  if (portnum_msk & FCLK_TMRB(18)) {
    CGFCLKMSKA_bit.TMRB18 = 0;
  }
  if (portnum_msk & FCLK_TMRB(19)) {
    CGFCLKMSKA_bit.TMRB19 = 0;
  }
}

/*************************************************************************
 * Function Name: fclk_dis_tmrb
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Disable clock to TMRB of specified channel
 *
 *************************************************************************/
void fclk_dis_tmrb(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_TMRB(0)) {
    CGFCMSKA_bit.TMRB00 = 1;
  }
  if (portnum_msk & FCLK_TMRB(1)) {
    CGFCMSKA_bit.TMRB01 = 1;
  }
  if (portnum_msk & FCLK_TMRB(2)) {
    CGFCMSKA_bit.TMRB02 = 1;
  }
  if (portnum_msk & FCLK_TMRB(3)) {
    CGFCMSKA_bit.TMRB03 = 1;
  }
  if (portnum_msk & FCLK_TMRB(4)) {
    CGFCMSKA_bit.TMRB04 = 1;
  }
  if (portnum_msk & FCLK_TMRB(5)) {
    CGFCMSKA_bit.TMRB05 = 1;
  }
  if (portnum_msk & FCLK_TMRB(6)) {
    CGFCMSKA_bit.TMRB06 = 1;
  }
  if (portnum_msk & FCLK_TMRB(7)) {
    CGFCMSKA_bit.TMRB07 = 1;
  }
  if (portnum_msk & FCLK_TMRB(8)) {
    CGFCMSKA_bit.TMRB08 = 1;
  }
  if (portnum_msk & FCLK_TMRB(9)) {
    CGFCMSKA_bit.TMRB09 = 1;
  }
  if (portnum_msk & FCLK_TMRB(10)) {
    CGFCLKMSKA_bit.TMRB10 = 1;
  }
  if (portnum_msk & FCLK_TMRB(11)) {
    CGFCLKMSKA_bit.TMRB11 = 1;
  }
  if (portnum_msk & FCLK_TMRB(12)) {
    CGFCLKMSKA_bit.TMRB12 = 1;
  }
  if (portnum_msk & FCLK_TMRB(13)) {
    CGFCLKMSKA_bit.TMRB13 = 1;
  }
  if (portnum_msk & FCLK_TMRB(14)) {
    CGFCLKMSKA_bit.TMRB14 = 1;
  }
  if (portnum_msk & FCLK_TMRB(15)) {
    CGFCLKMSKA_bit.TMRB15 = 1;
  }
  if (portnum_msk & FCLK_TMRB(16)) {
    CGFCLKMSKA_bit.TMRB16 = 1;
  }
  if (portnum_msk & FCLK_TMRB(17)) {
    CGFCLKMSKA_bit.TMRB17 = 1;
  }
  if (portnum_msk & FCLK_TMRB(18)) {
    CGFCLKMSKA_bit.TMRB18 = 1;
  }
  if (portnum_msk & FCLK_TMRB(19)) {
    CGFCLKMSKA_bit.TMRB19 = 1;
  }
}

/*************************************************************************
 * Function Name: fclk_ena_tmrc
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Enable clock to TMRC of specified channel
 *
 *************************************************************************/
void fclk_ena_tmrc(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_TMRC(0)) {
    CGFCMSKA_bit.TMRCCAP0 = 0;
    CGFCMSKA_bit.TMRCCMP0 = 0;
  }
  if (portnum_msk & FCLK_TMRC(0)) {
    CGFCMSKA_bit.TMRCCAP1 = 0;
    CGFCMSKA_bit.TMRCCMP1 = 0;
  }
  if (portnum_msk & FCLK_TMRC(2)) {
    CGFCMSKA_bit.TMRCCAP2 = 0;
    CGFCMSKA_bit.TMRCCMP2 = 0;
  }
  if (portnum_msk & FCLK_TMRC(3)) {
    CGFCMSKA_bit.TMRCCAP3 = 0;
    CGFCMSKA_bit.TMRCCMP3 = 0;
  }
  if (portnum_msk & FCLK_TMRC(4)) {
    CGFCMSKA_bit.TMRCCMP4 = 0;
  }
  if (portnum_msk & FCLK_TMRC(5)) {
    CGFCMSKA_bit.TMRCCMP5 = 0;
  }
  if (portnum_msk & FCLK_TMRC(6)) {
    CGFCMSKA_bit.TMRCCMP6 = 0;
  }
  if (portnum_msk & FCLK_TMRC(7)) {
    CGFCMSKA_bit.TMRCCMP7 = 0;
  }
  if (portnum_msk & FCLK_TMRCTBT) {
    CGFCMSKB_bit.TMRCTBT = 0;
  }
}



/*************************************************************************
 * Function Name: fclk_dis_tmrc
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Disable clock to TMRC of specified channel
 *
 *************************************************************************/
void fclk_dis_tmrc(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_TMRC(0)) {
    CGFCMSKA_bit.TMRCCAP0 = 1;
    CGFCMSKA_bit.TMRCCMP0 = 1;
  }
  if (portnum_msk & FCLK_TMRC(1)) {
    CGFCMSKA_bit.TMRCCAP1 = 1;
    CGFCMSKA_bit.TMRCCMP1 = 1;
  }
  if (portnum_msk & FCLK_TMRC(2)) {
    CGFCMSKA_bit.TMRCCAP2 = 1;
    CGFCMSKA_bit.TMRCCMP2 = 1;
  }
  if (portnum_msk & FCLK_TMRC(3)) {
    CGFCMSKA_bit.TMRCCAP3 = 1;
    CGFCMSKA_bit.TMRCCMP3 = 1;
  }
  if (portnum_msk & FCLK_TMRC(4)) {
    CGFCMSKA_bit.TMRCCMP4 = 1;
  }
  if (portnum_msk & FCLK_TMRC(5)) {
    CGFCMSKA_bit.TMRCCMP5 = 1;
  }
  if (portnum_msk & FCLK_TMRC(6)) {
    CGFCMSKA_bit.TMRCCMP6 = 1;
  }
  if (portnum_msk & FCLK_TMRC(7)) {
    CGFCMSKA_bit.TMRCCMP7 = 1;
  }
  if (portnum_msk & FCLK_TMRCTBT) {
    CGFCMSKB_bit.TMRCTBT = 1;
  }
}

/*************************************************************************
 * Function Name: fclk_ena_dac
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Enable clock to DAC of specified channel
 *
 *************************************************************************/
void fclk_ena_dac(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_DAC(0)) {
    CGFCLKMSKA_bit.DAC0 = 0;
  }
  if (portnum_msk & FCLK_DAC(1)) {
    CGFCLKMSKA_bit.DAC1 = 0;
  }
}

/*************************************************************************
 * Function Name: fclk_dis_dac
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Disable clock to DAC of specified channel
 *
 *************************************************************************/
void fclk_dis_dac(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_DAC(0)) {
    CGFCLKMSKA_bit.DAC0 = 1;
  }
  if (portnum_msk & FCLK_DAC(1)) {
    CGFCLKMSKA_bit.DAC1 = 1;
  }
}

/*************************************************************************
 * Function Name: fclk_ena_adc
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Enable clock to ADC of specified channel
 *
 *************************************************************************/
void fclk_ena_adc(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_ADC(0)) {
    CGFCLKMSKB_bit.ADCA = 0;
    CGSYSCR_bit.FCSTOP0 = 0;
  }
  if (portnum_msk & FCLK_ADC(1)) {
    CGFCLKMSKB_bit.ADCB = 0;
    CGSYSCR_bit.FCSTOP1 = 0;
  }
  if (portnum_msk & FCLK_ADC(2)) {
    CGFCLKMSKB_bit.ADCC = 0;
    CGSYSCR_bit.FCSTOP2 = 0;
  }
}

/*************************************************************************
 * Function Name: fclk_dis_adc
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Disable clock to ADC of specified channel
 *
 *************************************************************************/
void fclk_dis_adc(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_ADC(0)) {
    CGFCLKMSKB_bit.ADCA = 1;
    CGSYSCR_bit.FCSTOP0 = 1;
  }
  if (portnum_msk & FCLK_ADC(1)) {
    CGFCLKMSKB_bit.ADCB = 1;
    CGSYSCR_bit.FCSTOP1 = 1;
  }
  if (portnum_msk & FCLK_ADC(2)) {
    CGFCLKMSKB_bit.ADCC = 1;
    CGSYSCR_bit.FCSTOP2 = 1;
  }
}

/*************************************************************************
 * Function Name: fclk_ena_dmac
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Enable clock to DMAC of specified channel
 *
 *************************************************************************/
void fclk_ena_dmac(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_DMAC(0)) {
    CGFCLKMSKA_bit.DMACA = 0;
  }
  if (portnum_msk & FCLK_DMAC(1)) {
    CGFCLKMSKA_bit.DMACB = 0;
  }
  if (portnum_msk & FCLK_DMAC(2)) {
    CGFCLKMSKA_bit.DMACC = 0;
  }
}

/*************************************************************************
 * Function Name: fclk_dis_dmac
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Disable clock to DMAC of specified channel
 *
 *************************************************************************/
void fclk_dis_dmac(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_DMAC(0)) {
    CGFCLKMSKA_bit.DMACA = 1;
  }
  if (portnum_msk & FCLK_DMAC(1)) {
    CGFCLKMSKA_bit.DMACB = 1;
  }
  if (portnum_msk & FCLK_DMAC(2)) {
    CGFCLKMSKA_bit.DMACC = 1;
  }
}

/*************************************************************************
 * Function Name: fclk_ena_port
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Enable clock to specifed Port
 *
 *************************************************************************/
void fclk_ena_port(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_PORTA) {
    CGFCLKMSKA_bit.PORTA = 0;
  }
  if (portnum_msk & FCLK_PORTB) {
    CGFCLKMSKA_bit.PORTB = 0;
  }
  if (portnum_msk & FCLK_PORTC) {
    CGFCLKMSKA_bit.PORTC = 0;
  }
  if (portnum_msk & FCLK_PORTD) {
    CGFCLKMSKA_bit.PORTD = 0;
  }
  if (portnum_msk & FCLK_PORTE) {
    CGFCLKMSKA_bit.PORTE = 0;
  }
  if (portnum_msk & FCLK_PORTF) {
    CGFCLKMSKA_bit.PORTF = 0;
  }
  if (portnum_msk & FCLK_PORTG) {
    CGFCLKMSKA_bit.PORTG = 0;
  }
  if (portnum_msk & FCLK_PORTH) {
    CGFCLKMSKA_bit.PORTH = 0;
  }
  if (portnum_msk & FCLK_PORTJ) {
    CGFCLKMSKA_bit.PORTJ = 0;
  }
  if (portnum_msk & FCLK_PORTK) {
    CGFCLKMSKA_bit.PORTK = 0;
  }
  if (portnum_msk & FCLK_PORTL) {
    CGFCLKMSKA_bit.PORTL = 0;
  }
  if (portnum_msk & FCLK_PORTM) {
    CGFCLKMSKA_bit.PORTM = 0;
  }
  if (portnum_msk & FCLK_PORTN) {
    CGFCLKMSKA_bit.PORTN = 0;
  }
  if (portnum_msk & FCLK_PORTP) {
    CGFCLKMSKB_bit.PORTP = 0;
  }
  if (portnum_msk & FCLK_PORTR) {
    CGFCLKMSKB_bit.PORTR = 0;
  }
  if (portnum_msk & FCLK_PORTT) {
    CGFCLKMSKB_bit.PORTT = 0;
  }
  if (portnum_msk & FCLK_PORTU) {
    CGFCLKMSKB_bit.PORTU = 0;
  }
  if (portnum_msk & FCLK_PORTV) {
    CGFCLKMSKB_bit.PORTV = 0;
  }
  if (portnum_msk & FCLK_PORTW) {
    CGFCLKMSKB_bit.PORTW = 0;
  }
  if (portnum_msk & FCLK_PORTY) {
    CGFCLKMSKB_bit.PORTY = 0;
  }
  if (portnum_msk & FCLK_PORTAA) {
    CGFCLKMSKB_bit.PORTAA = 0;
  }
  if (portnum_msk & FCLK_PORTAB) {
    CGFCLKMSKB_bit.PORTAB = 0;
  }
  if (portnum_msk & FCLK_PORTAC) {
    CGFCLKMSKB_bit.PORTAC = 0;
  }
  if (portnum_msk & FCLK_PORTAD) {
    CGFCLKMSKB_bit.PORTAD = 0;
  }
  if (portnum_msk & FCLK_PORTAE) {
    CGFCLKMSKB_bit.PORTAE = 0;
  }
  if (portnum_msk & FCLK_PORTAF) {
    CGFCLKMSKB_bit.PORTAF = 0;
  }
  if (portnum_msk & FCLK_PORTAG) {
    CGFCLKMSKB_bit.PORTAG = 0;
  }
  if (portnum_msk & FCLK_PORTAH) {
    CGFCLKMSKB_bit.PORTAH = 0;
  }
  if (portnum_msk & FCLK_PORTAJ) {
    CGFCLKMSKB_bit.PORTAJ = 0;
  }
}

/*************************************************************************
 * Function Name: fclk_dis_port
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Disable clock to specifed Port
 *
 *************************************************************************/
void fclk_dis_port(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_PORTA) {
    CGFCLKMSKA_bit.PORTA = 1;
  }
  if (portnum_msk & FCLK_PORTB) {
    CGFCLKMSKA_bit.PORTB = 1;
  }
  if (portnum_msk & FCLK_PORTC) {
    CGFCLKMSKA_bit.PORTC = 1;
  }
  if (portnum_msk & FCLK_PORTD) {
    CGFCLKMSKA_bit.PORTD = 1;
  }
  if (portnum_msk & FCLK_PORTE) {
    CGFCLKMSKA_bit.PORTE = 1;
  }
  if (portnum_msk & FCLK_PORTF) {
    CGFCLKMSKA_bit.PORTF = 1;
  }
  if (portnum_msk & FCLK_PORTG) {
    CGFCLKMSKA_bit.PORTG = 1;
  }
  if (portnum_msk & FCLK_PORTH) {
    CGFCLKMSKA_bit.PORTH = 1;
  }
  if (portnum_msk & FCLK_PORTJ) {
    CGFCLKMSKA_bit.PORTJ = 1;
  }
  if (portnum_msk & FCLK_PORTK) {
    CGFCLKMSKA_bit.PORTK = 1;
  }
  if (portnum_msk & FCLK_PORTL) {
    CGFCLKMSKA_bit.PORTL = 1;
  }
  if (portnum_msk & FCLK_PORTM) {
    CGFCLKMSKA_bit.PORTM = 1;
  }
  if (portnum_msk & FCLK_PORTN) {
    CGFCLKMSKA_bit.PORTN = 1;
  }
  if (portnum_msk & FCLK_PORTP) {
    CGFCLKMSKB_bit.PORTP = 1;
  }
  if (portnum_msk & FCLK_PORTR) {
    CGFCLKMSKB_bit.PORTR = 1;
  }
  if (portnum_msk & FCLK_PORTT) {
    CGFCLKMSKB_bit.PORTT = 1;
  }
  if (portnum_msk & FCLK_PORTU) {
    CGFCLKMSKB_bit.PORTU = 1;
  }
  if (portnum_msk & FCLK_PORTV) {
    CGFCLKMSKB_bit.PORTV = 1;
  }
  if (portnum_msk & FCLK_PORTW) {
    CGFCLKMSKB_bit.PORTW = 1;
  }
  if (portnum_msk & FCLK_PORTY) {
    CGFCLKMSKB_bit.PORTY = 1;
  }
  if (portnum_msk & FCLK_PORTAA) {
    CGFCLKMSKB_bit.PORTAA = 1;
  }
  if (portnum_msk & FCLK_PORTAB) {
    CGFCLKMSKB_bit.PORTAB = 1;
  }
  if (portnum_msk & FCLK_PORTAC) {
    CGFCLKMSKB_bit.PORTAC = 1;
  }
  if (portnum_msk & FCLK_PORTAD) {
    CGFCLKMSKB_bit.PORTAD = 1;
  }
  if (portnum_msk & FCLK_PORTAE) {
    CGFCLKMSKB_bit.PORTAE = 1;
  }
  if (portnum_msk & FCLK_PORTAF) {
    CGFCLKMSKB_bit.PORTAF = 1;
  }
  if (portnum_msk & FCLK_PORTAG) {
    CGFCLKMSKB_bit.PORTAG = 1;
  }
  if (portnum_msk & FCLK_PORTAH) {
    CGFCLKMSKB_bit.PORTAH = 1;
  }
  if (portnum_msk & FCLK_PORTAJ) {
    CGFCLKMSKB_bit.PORTAJ = 1;
  }
}

/*************************************************************************
 * Function Name: fclk_ena_esio
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Enable clock to ESIO of specified channel
 *
 *************************************************************************/
void fclk_ena_esio(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_ESIO(0)) {
    CGFCMSKA_bit.ESIO0 = 0;
  }
  if (portnum_msk & FCLK_ESIO(1)) {
    CGFCMSKA_bit.ESIO1 = 0;
  }
  if (portnum_msk & FCLK_ESIO(2)) {
    CGFCMSKA_bit.ESIO2 = 0;
  }
}

/*************************************************************************
 * Function Name: fclk_dis_esio
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Disable clock to ESIO of specified channel
 *
 *************************************************************************/
void fclk_dis_esio(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_ESIO(0)) {
    CGFCMSKA_bit.ESIO0 = 1;
  }
  if (portnum_msk & FCLK_ESIO(1)) {
    CGFCMSKA_bit.ESIO1 = 1;
  }
  if (portnum_msk & FCLK_ESIO(2)) {
    CGFCMSKA_bit.ESIO2 = 1;
  }
}

/*************************************************************************
 * Function Name: fclk_ena_sio
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Enable clock to SIO of specified channel
 *
 *************************************************************************/
void fclk_ena_sio(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_SIO(0)) {
    CGFCMSKA_bit.UARTSIO0 = 0;
  }
  if (portnum_msk & FCLK_SIO(1)) {
    CGFCMSKA_bit.UARTSIO1 = 0;
  }
  if (portnum_msk & FCLK_SIO(2)) {
    CGFCMSKA_bit.UARTSIO2 = 0;
  }
  if (portnum_msk & FCLK_SIO(3)) {
    CGFCMSKA_bit.UARTSIO3 = 0;
  }
  if (portnum_msk & FCLK_SIO(4)) {
    CGFCMSKA_bit.UARTSIO4 = 0;
  }
  if (portnum_msk & FCLK_SIO(5)) {
    CGFCMSKA_bit.UARTSIO5 = 0;
  }
}

/*************************************************************************
 * Function Name: fclk_dis_sio
 * Parameters:    portnum_msk - channel number
 * Return:      none
 *
 * Description:   Disable clock to SIO of specified channel
 *
 *************************************************************************/
void fclk_dis_sio(uint32_t portnum_msk)
{
  if (portnum_msk & FCLK_SIO(0)) {
    CGFCMSKA_bit.UARTSIO0 = 1;
  }
  if (portnum_msk & FCLK_SIO(1)) {
    CGFCMSKA_bit.UARTSIO1 = 1;
  }
  if (portnum_msk & FCLK_SIO(2)) {
    CGFCMSKA_bit.UARTSIO2 = 1;
  }
  if (portnum_msk & FCLK_SIO(3)) {
    CGFCMSKA_bit.UARTSIO3 = 1;
  }
  if (portnum_msk & FCLK_SIO(4)) {
    CGFCMSKA_bit.UARTSIO4 = 1;
  }
  if (portnum_msk & FCLK_SIO(5)) {
    CGFCMSKA_bit.UARTSIO5 = 1;
  }
}

/*************************************************************************
 * Function Name: fclk_ena_ebif
 * Parameters:    none
 * Return:      none
 *
 * Description:   Enable clock to EBIF
 *
 *************************************************************************/
void fclk_ena_ebif(void)
{
  CGFCLKMSKA_bit.EBIF = 0;
}

/*************************************************************************
 * Function Name: fclk_dis_ebif
 * Parameters:    none
 * Return:      none
 *
 * Description:   Disable clock to EBIF
 *
 *************************************************************************/
void fclk_dis_ebif(void)
{
  CGFCLKMSKA_bit.EBIF = 1;
}

/*************************************************************************
 * Function Name: fclk_ena_ephc
 * Parameters:    none
 * Return:      none
 *
 * Description:   Enable clock to EPHC
 *
 *************************************************************************/
void fclk_ena_ephc(void)
{
  CGFCLKMSKB_bit.EPHC = 0;
}

/*************************************************************************
 * Function Name: fclk_dis_ephc
 * Parameters:    none
 * Return:      none
 *
 * Description:   Disable clock to EPHC
 *
 *************************************************************************/
void fclk_dis_ephc(void)
{
  CGFCLKMSKB_bit.EPHC = 1;
}

/*************************************************************************
 * Function Name: fclk_ena_sbi
 * Parameters:    none
 * Return:      none
 *
 * Description:   Enable clock to SBI
 *
 *************************************************************************/
void fclk_ena_sbi(void)
{
  CGFCLKMSKB_bit.SBI = 0;
}

/*************************************************************************
 * Function Name: fclk_dis_sbi
 * Parameters:    none
 * Return:      none
 *
 * Description:   Disable clock to SBI
 *
 *************************************************************************/
void fclk_dis_sbi(void)
{
  CGFCLKMSKB_bit.SBI = 1;
}

/*************************************************************************
 * Function Name: fclk_ena_wdt
 * Parameters:    none
 * Return:      none
 *
 * Description:   Enable clock to WDT
 *
 *************************************************************************/
void fclk_ena_wdt(void)
{
  CGFCLKMSKB_bit.WDT = 0;
}

/*************************************************************************
 * Function Name: fclk_dis_wdt
 * Parameters:    none
 * Return:      none
 *
 * Description:   Disable clock to WDT
 *
 *************************************************************************/
void fclk_dis_wdt(void)
{
  CGFCLKMSKB_bit.WDT = 1;
}

/** private functions **/
