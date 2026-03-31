/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : drv_cg.c
 *    Description : Toshiba TMPM364 Clock/Mode Control Drv
 *
 *    History :
 *    1. Date        : 1.2011
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    $Revision: 41 $
 **************************************************************************/
/** include files **/
#include <stdint.h>
#include <Toshiba\iotmpm364f10fg.h>
#include "drv_cg.h"
#include "board.h"
/** local definitions **/

/** default settings **/

/** external functions **/

/** external data **/

/** internal functions **/

/** public data **/

/** private data **/

/** public functions **/

/*************************************************************************
 * Function Name: CG_ExtOscEnable
 * Parameters: cg_enable_t osc_enable, cg_osc_t osc
 *             
 * Return: void
 *
 * Description: External Oscilators enable disable
 *
 *
 *************************************************************************/
void CG_ExtOscEnable(cg_enable_t osc_enable, cg_osc_t osc)
{
  if(CG_ENABLE == osc_enable)
  {
    if( OSC_EH == osc)
    {/*Enable ext high osc*/
      CGOSCCR_bit.XEN = 1;
      CGOSCCR_bit.WUPSEL = 0;   /*sel ext high speed for warm up clock*/ 
      CGOSCCR_bit.WUPT = 1500;   /*wait some clocks from oscilatior*/ 
    }
    else 
    {
      if( OSC_EL == osc)
      {/*Enable ext low speed osc*/
        CGOSCCR_bit.XTEN = 1;
        CGOSCCR_bit.WUPSEL = 1; /*sel ext low speed for warm up clock*/ 
        CGOSCCR_bit.WUPT = 1;   /*wait some clocks from oscilatior*/ 
      }        
    }
    CGOSCCR;                  /*Dummy read*/
    /*Start warm up*/
    CGOSCCR_bit.WUEON = 1;
    while(CGOSCCR_bit.WUEF)
    {}
  }
  else
  { 
    if( OSC_EH == osc)
    {/*Disable ext high osc*/
      CGOSCCR_bit.XEN = 0;
    }
    else 
    {
      if( OSC_EL == osc)
      {/*Disable ext low speed osc*/
        CGOSCCR_bit.XTEN = 0;
      }        
    }
  }
}

/*************************************************************************
 * Function Name: CG_SetFcClk
 * Parameters: cg_fcsel_t fcssel - select fc fosc or fpll
 *             
 * Return: void
 *
 * Description: set fc clock
 *
 *
 *************************************************************************/
void CG_SetFcClk(cg_fcsel_t fcssel)
{
  /*select fc clock*/
  CGPLLSEL_bit.PLLSEL = fcssel;
}
/*************************************************************************
 * Function Name: CG_SetFgearClk
 * Parameters: cg_fgearsel_t fgearsel - select fgear
 *             
 * Return: void
 *
 * Description: set Fgear clock
 *
 *
 *************************************************************************/
void CG_SetFgearClk(cg_gear_t gear)
{
  /*set new gear*/
  CGSYSCR_bit.GEAR = gear;
}
/*************************************************************************
 * Function Name: CG_SetPerifClk
 * Parameters: cg_fpsel_t pfsel - select fc or fsys
 *             
 * Return: void
 *
 * Description: set peripheral clock
 *
 *
 *************************************************************************/
void CG_SetPerifClk(cg_fpsel_t pfsel)
{
  if(FPSEL_FGEAR == pfsel)
  {
    CGSYSCR_bit.FPSEL &= ~(1<<0);
  }
  else
  {
    CGSYSCR_bit.FPSEL |= (1<<0);
  }
}

/*************************************************************************
 * Function Name: CG_SetPerifClk
 * Parameters: cg_fsyssel_t fsyssel - select fsys clock
 *            
 * Return: void
 *
 * Description: set sys clock gear of fs
 *
 *
 *************************************************************************/
void CG_SetFsysClk(cg_fsyssel_t fsyssel)
{
  CGCKSEL_bit.SYSCK = fsyssel;
}

/*************************************************************************
 * Function Name: CG_SetT0Clk
 * Parameters: cg_ft0sel_t ft0sel - select ft0 clock
 *            
 * Return: void
 *
 * Description: set ft0 clock
 *
 *
 *************************************************************************/
void CG_SetT0Clk(cg_ft0sel_t ft0sel)
{
  if(FT0SEL_FC == ft0sel)
  {
    CGSYSCR_bit.FPSEL |= 1<<1;  
  }
  else
  {
    CGSYSCR_bit.PRCK = ft0sel;
    CGSYSCR_bit.FPSEL &= ~(1<<1);  
  }
}

/*************************************************************************
 * Function Name: CG_SetPll
 * Parameters: cg_enable_t pllenalbe - enalbe or disable pll
 *             cg_pllset_t pllmul  - set pll mul
 *
 * Return: void
 *
 * Description: set pll 
 *
 *
 *************************************************************************/
void CG_SetPll(cg_enable_t pllenable, cg_pllset_t pllmul)
{
  
  CGOSCCR_bit.PLLON = 0;
  if(CG_ENABLE == pllenable)
  {
    /*set multiplying*/
    CGPLLSEL = pllmul;
    CGOSCCR_bit.WUPSEL = 0;                       /*sel ext high speed for warm up clock*/ 
    CGOSCCR_bit.WUPT = (250*(EHOSC/1000000))/16;  /*wait 250us */ 
    /*Start warm up*/
    CGOSCCR_bit.WUEON = 1;
    while(CGOSCCR_bit.WUEF)  
    /*start PLL*/
    CGOSCCR_bit.PLLON = 1;
    /*Start warm up*/
    CGOSCCR_bit.WUEON = 1;
    while(CGOSCCR_bit.WUEF)  
    {}
  }
}

/*************************************************************************
 * Function Name: CG_SetPll
 * Parameters: cg_clk_t clock - clock to get
 *
 * Return: int clock frequency in Hz 
 *
 * Description: get clock frequency
 *
 *
 *************************************************************************/
int CG_GetClock(cg_clk_t clock)
{
int freq = 0;
  switch(clock)
  {
  case CLK_FOSC:            /*fosc clock*/
    /*External high speed osc*/
      freq =  EHOSC;
    break ;
  case CLK_FS:            /*fs clock*/
    /*External low speed osc*/
      freq =  ELOSC;
    break ;
  case CLK_FPLL:            /*fpll clock*/
      if(CGOSCCR_bit.PLLON)
      {/*PLL is on*/
        if(PLLSET_MUL_8 == (CGPLLSEL & ~(0x1)))
        {/*mul 8*/
          freq = EHOSC*8;
        }
        else
        {/*mul 4*/
          if(PLLSET_MUL_4 ==(CGPLLSEL & ~(0x1)))
          {
            freq = EHOSC*4;
          }
        }
      }
    break;
  case CLK_FC:              /*fc clock*/
      if(FCSEL_FOSC == CGPLLSEL_bit.PLLSEL)
      {/*fosc is fc clock*/
        freq = CG_GetClock(CLK_FOSC);
      }
      else
      {/*fpll is fc clock*/
        freq = CG_GetClock(CLK_FPLL);
      }
    break;
  case CLK_FGEAR:            /*fgear clock*/
      switch(CGSYSCR_bit.GEAR)
      {
      case GEAR_FC:         /*fc is fsys clock*/
        freq = CG_GetClock(CLK_FC);
        break;
      case GEAR_FC_2:       /*fc/2 is fsys clock*/
      case GEAR_FC_4:       /*fc/4 is fsys clock*/
      case GEAR_FC_8:       /*fc/8 is fsys clock*/
        freq = CG_GetClock(CLK_FC)>>((CGSYSCR_bit.GEAR&0x3)+1);
        break;
      }
    break;
  case CLK_FSYS:            /*fsys clock*/
     if(FSYSSEL_FGEAR == CGCKSEL_bit.SYSCK)
     {
       freq = CG_GetClock(CLK_FGEAR);
     }
     else
     {
       freq = CG_GetClock(CLK_FS);
     }
    break;
  case CLK_FPERIPH:         /*fperiph clock*/
      if(FPSEL_FGEAR == (CGSYSCR_bit.FPSEL & 0x1))
      {/*fgear as periph divider input*/
        freq = CG_GetClock(CLK_FGEAR);
      }
      else
      {/*fc as periph divider input*/
        freq = CG_GetClock(CLK_FC);
      }
    break;
  case CLK_FT0:
      if((CGSYSCR_bit.FPSEL & 0x2))
      {/*ft0 clock fs*/
        freq = CG_GetClock(CLK_FC);
      }
      else
      {/*fpeary as periph divider input*/
        freq = CG_GetClock(CLK_FPERIPH)>>CGSYSCR_bit.PRCK;
      }
    break;
  }
  
  return freq;
}

/*
InitClock
*/
void InitClock(cg_clkinit_t * clkinit)
{
  /*Enable ext HS osc*/
  CG_ExtOscEnable(CG_ENABLE, OSC_EH);
  /*Enable ext LS osc*/
  CG_ExtOscEnable(CG_ENABLE, OSC_EL);
  /*Fc set to Fosc*/
  CG_SetFcClk(FCSEL_FOSC);
  /*Set T0 Clock*/
  CG_SetT0Clk(clkinit->ft0sel);
  /*Set Periph Clock*/
  CG_SetPerifClk(clkinit->pfsel);
  /*Set Fsys Clock*/
  CG_SetFsysClk(clkinit->fsyssel);
  /*Set fgear Clock*/
  CG_SetFgearClk(clkinit->gear);
  /*Set Fosc clock*/
  CG_SetPll(clkinit->pll_enable,clkinit->pllmul);
  /*Set Peripheral clock*/
  CG_SetFcClk(clkinit->fcsel);
}

