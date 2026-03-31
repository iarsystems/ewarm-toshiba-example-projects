/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : drv_cg.c
 *    Description : Toshiba TMPM369 Clock/Mode Control Drv
 *
 *    History :
 *    1. Date        : 1.2011
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *    2. Date        : January 18, 2012
 *       Author      : Stanimir Bonev
 *       Description : Port for TMPM369
 *
 *    $Revision: 41 $
 **************************************************************************/
/** include files **/
#include <stdint.h>
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
 * Function Name: CG_RegsProtect
 * Parameters: cg_enable_t wr_enable
 * Return: void
 *
 * Description: CG register write enable or disable
 *
 *
 *************************************************************************/
void CG_RegsProtect(cg_enable_t wr_enable)
{
  if(CG_ENABLE == wr_enable)
  {/*Register write enable*/
    CGPROTECT = 0xC1;
  }
  else
  {/*Register write disable*/
    CGPROTECT = ~0xC1;
  }
}
/*************************************************************************
 * Function Name: CG_ExtOscEnable
 * Parameters: cg_enable_t osc_enable
 *
 * Return: void
 *
 * Description: External Oscilator enable disable
 *
 *
 *************************************************************************/
void CG_ExtOscEnable(cg_enable_t osc_enable)
{
  if(CG_ENABLE == osc_enable)
  {/*Enable ext osc*/
    CGOSCCR_bit.XEN1 = 1;
  }
  else
  {/*Disable ext osc*/
    CGOSCCR_bit.XEN1 = 0;
  }
}

/*************************************************************************
 * Function Name: CG_ExtLP_OscEnable
 * Parameters: cg_enable_t osc_enable
 *
 * Return: void
 *
 * Description: External Low Power Oscilator enable disable
 *
 *
 *************************************************************************/
void CG_ExtLP_OscEnable(cg_enable_t osc_enable)
{
  if(CG_ENABLE == osc_enable)
  {/*Enable ext osc*/
    CGOSCCR_bit.XTEN = 1;
  }
  else
  {/*Disable ext osc*/
    CGOSCCR_bit.XTEN = 0;
  }
}

/*************************************************************************
 * Function Name: CG_IntOscEnable
 * Parameters: cg_enable_t osc_enable
 *
 * Return: void
 *
 * Description: Internal Oscilator 2 enable disable
 *
 *
 *************************************************************************/
void CG_IntOscEnable(cg_enable_t osc_enable)
{
  if(CG_ENABLE == osc_enable)
  {/*Enable internal osc*/
    CGOSCCR_bit.XEN2 = 1;
  }
  else
  {/*Disable internal osc*/
    CGOSCCR_bit.XEN2 = 0;
  }
}

/*************************************************************************
 * Function Name: CG_IntOscEnable
 * Parameters: cg_enable_t osc_enable
 *
 * Return: void
 *
 * Description: Internal Oscilator 3 enable disable
 *
 *
 *************************************************************************/
void CG_IntOsc3Enable(cg_enable_t osc_enable)
{
  if(CG_ENABLE == osc_enable)
  {/*Enable internal osc*/
    CGOSCCR_bit.XEN3 = 1;
  }
  else
  {/*Disable internal osc*/
    CGOSCCR_bit.XEN3 = 0;
  }
}

/*************************************************************************
 * Function Name: CG_SetFosc
 * Parameters: cg_foscsel_t fosc - selec internal osc, ext osc or ext clk
 *
 * Return: void
 *
 * Description: set fosc
 *
 *************************************************************************/
void CG_SetFosc(cg_foscsel_t fosc)
{
  if((CGOSCCR>>17 & 0x3) != fosc)
  {/*only if other source is selected*/
    if(FOSCSEL_INTOSC == fosc)
    {
       CGOSCCR_bit.XEN2 = 1;
       CGOSCCR_bit.EHOSCSEL = 0;
      /*Selects warm-up counter by internal oscillator*/
      CGOSCCR_bit.WUPSEL2 = 0;
    }
    else
    {
      if(FOSCSEL_EXTOSC == fosc)
      {/*external oscilator*/
        CGOSCCR_bit.XEN1 = 1;
        CGOSCCR_bit.EHOSCSEL = 1;
      }
      else
      {/*exnternal input clock*/
        CGOSCCR_bit.XEN1 = 0;
        CGOSCCR_bit.EHOSCSEL = 0;
      }
      /*Selects warm-up counter by external oscillator*/
      CGOSCCR_bit.WUPSEL2 = 1;
    }
    CGOSCCR_bit.WUPT = 256; /*wait some clocks from oscilatior*/
    while(256 != CGOSCCR_bit.WUPT);
    /*Start warm up*/
    CGOSCCR_bit.WUEON = 1;
    while(CGOSCCR_bit.WUEF);
    /*select fosc*/
    CGOSCCR_bit.OSCSEL = fosc&1;
  }
}
/*************************************************************************
 * Function Name: CG_SetSysClk
 * Parameters: cg_fcsel_t fcssel - select fc fosc or fpll/2
 *             cg_gear_t gear  - select fsys divider
 * Return: void
 *
 * Description: set fsys clock
 *
 *
 *************************************************************************/
void CG_SetSysClk(cg_fcsel_t fcssel,cg_gear_t gear)
{
  /*select oscilator fc clock*/
  CGPLLSEL_bit.PLLSEL = 0;
  /*set new gear*/
  CGSYSCR_bit.GEAR = gear;
  /*select fc*/
  CGPLLSEL_bit.PLLSEL = fcssel;
}
/*************************************************************************
 * Function Name: CG_SetPerifClk
 * Parameters: cg_fpsel_t pfsel - select fc or fsys
 *             cg_prck_t prck - select peripheral clock divider
 * Return: void
 *
 * Description: set peripheral clock
 *
 *
 *************************************************************************/
void CG_SetPerifClk(cg_fpsel_t pfsel, cg_prck_t prck)
{
  CGSYSCR_bit.FPSEL = pfsel;
  CGSYSCR_bit.PRCK = prck;
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
    CGPLLSEL_bit.PLLSET = pllmul;
    /*start PLL*/
    for(int i = 10000; i; --i); /*wait a little*/
    /*wait to lock 200us*/
    CGOSCCR_bit.PLLON = 1;
    /*PLL sould be use only with exernal clok or oscilator*/
    CGOSCCR_bit.WUPSEL2 = 1;
    CGOSCCR_bit.WUPT = 200*(EHOSC/1000000);
    while(200*(EHOSC/1000000) != CGOSCCR_bit.WUPT);
    /*Start warm up*/
    CGOSCCR_bit.WUEON = 1;
    while(CGOSCCR_bit.WUEF);
  }
}

/*************************************************************************
 * Function Name: CG_SetUSB_Pll
 * Parameters: cg_enable_t pllenalbe - enalbe or disable pll
 *             cg_usb_pllset_t pllmul  - set pll mul
 *
 * Return: void
 *
 * Description: set usb pll
 *
 *
 *************************************************************************/
void CG_SetUSB_Pll(cg_enable_t pllenable, cg_usb_pllset_t pllmul)
{
  USBPLLCR_bit.USBPLLON = 0;
  if(CG_ENABLE == pllenable)
  {
    /*set multiplying*/
    USBPLLSEL_bit.USBPLLSET = pllmul;
    CG_SelUSB_Clk(CLK_USBPLL);
    /*start PLL*/
    for(int i = 10000; i; --i); /*wait a little*/
    /*wait to lock 200us*/
    USBPLLCR_bit.USBPLLON = 1;

    /*PLL sould be use only with exernal clok or oscilator*/
    CGOSCCR_bit.WUPSEL2 = 1;
    CGOSCCR_bit.WUPT = 200*(EHOSC/1000000);
    while(200*(EHOSC/1000000) != CGOSCCR_bit.WUPT);
    /*Start warm up*/
    CGOSCCR_bit.WUEON = 1;
    while(CGOSCCR_bit.WUEF);
  }
}

/*************************************************************************
 * Function Name: CG_SelUSB_Clk
 * Parameters: cg_usb_clk_sel_t usbl_clk_sel - select USB clock source
 *              External 48MHz or USB PLL
 *
 * Return: none
 *
 * Description: Select UBS clock source
 *
 *
 *************************************************************************/
void CG_SelUSB_Clk(cg_usb_clk_sel_t usbl_clk_sel)
{
  if(CLK_USBCLK == usbl_clk_sel)
  {
    PKFR1_bit.PK2F1 = 1;
    PKIE_bit.PK2IE = 1;
  }
  USBPLLSEL_bit.USBPLLSEL = usbl_clk_sel;
}

/*************************************************************************
 * Function Name: CG_USB_Host_Enable
 * Parameters: cg_enable_t enable
 *
 * Return: void
 *
 * Description: USB Host controller clock enable/disable
 *
 *
 *************************************************************************/
void CG_USB_Host_Enable(cg_enable_t enable)
{
  if(CG_ENABLE == enable)
  {/*Enable internal osc*/
    USBPLLEN_bit.USBHEN = 1;
  }
  else
  {/*Disable internal osc*/
    USBPLLEN_bit.USBHEN = 0;
  }
}

/*************************************************************************
 * Function Name: CG_USB_Device_Enable
 * Parameters: cg_enable_t enable
 *
 * Return: void
 *
 * Description: USB Device controller clock enable/disable
 *
 *
 *************************************************************************/
void CG_USB_Device_Enable(cg_enable_t enable)
{
  if(CG_ENABLE == enable)
  {/*Enable internal osc*/
    USBPLLEN_bit.USBDEN = 1;
  }
  else
  {/*Disable internal osc*/
    USBPLLEN_bit.USBDEN = 0;
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
  case CLK_FOCS:            /*fosc clock*/
      if((CGOSCCR>>17 & 0x3) == FOSCSEL_INTOSC)
      {/*Internal osc*/
        freq =  IHOSC;
      }
      else
      {/*External osc*/
        freq =  EHOSC;
      }
    break ;
  case CLK_FPLL:            /*fpll clock*/
      if(CGOSCCR_bit.PLLON)
      {/*PLL is on*/
        if(PLLSET_8MHZ_48MHZ == CGPLLSEL_bit.PLLSET)
        {/*mul 8*/
          freq = 48 MHZ;
        }
        else if (PLLSET_8MHZ_80MHZ == CGPLLSEL_bit.PLLSET)
        {
          freq = 80 MHZ;
        }
        else if (PLLSET_10MHZ_80MHZ == CGPLLSEL_bit.PLLSET)
        {
          freq = 80 MHZ;
        }
        else if (PLLSET_12MHZ_48MHZ == CGPLLSEL_bit.PLLSET)
        {
          freq = 48 MHZ;
        }
        else if (PLLSET_12MHZ_72MHZ == CGPLLSEL_bit.PLLSET)
        {
          freq = 72 MHZ;
        }
        else if (PLLSET_16MHZ_48MHZ == CGPLLSEL_bit.PLLSET)
        {
          freq = 48 MHZ;
        }
        else if (PLLSET_16MHZ_80MHZ == CGPLLSEL_bit.PLLSET)
        {
          freq = 80 MHZ;
        }
        else
        {
          freq = 0;
        }
      }
    break;
  case CLK_FC:              /*fc clock*/
      if(FCSEL_FOSC == CGPLLSEL_bit.PLLSEL)
      {/*fosc is fc clock*/
        freq = CG_GetClock(CLK_FOCS);
      }
      else
      {/*fpll is fc clock*/
        freq = CG_GetClock(CLK_FPLL);
      }
    break;
  case CLK_FSYS:            /*fsys clock*/
      switch(CGSYSCR_bit.GEAR)
      {
      case GEAR_FC:         /*fc is fsys clock*/
        freq = CG_GetClock(CLK_FC);
        break;
      case GEAR_FC_2:       /*fc/2 is fsys clock*/
      case GEAR_FC_4:       /*fc/4 is fsys clock*/
      case GEAR_FC_8:       /*fc/8 is fsys clock*/
      case GEAR_FC_16:      /*fc/16 is fsys clock*/
        freq = CG_GetClock(CLK_FC)>>((CGSYSCR_bit.GEAR&0x3)+1);
        break;
      }
    break;
  case CLK_FPERIPH:         /*fperiph clock*/
      if(FPSEL_FGEAR == CGSYSCR_bit.FPSEL)
      {/*fgear as periph divider input*/
        freq = CG_GetClock(CLK_FSYS);
      }
      else
      {/*fc as periph divider input*/
        freq = CG_GetClock(CLK_FC);
      }
    break;
  case CLK_TO:
    freq = CG_GetClock(CLK_FPERIPH) >> CGSYSCR_bit.PRCK;
    break;
  }

  return freq;
}

/*
InitClock
*/
void InitClock(const cg_clkinit_t * clkinit)
{
  /*Enable CG registers write*/
  CG_RegsProtect(CG_ENABLE);
  /*Select fosc as sys clock*/
  CG_SetSysClk(FCSEL_FOSC, GEAR_FC);
  /*Set Fosc clock*/
  CG_SetFosc(clkinit->fosc);
  /*if external osc is selected*/
  if(FOSCSEL_INTOSC != clkinit->fosc)
  {/*init PLL*/
      CG_SetPll(clkinit->pll_enable,clkinit->pllmul);
  }
  else
  {/*disable PLL*/
      CG_SetPll(CG_DISABLE,PLLSET_16MHZ_48MHZ);
   }
  /*Set Peripheral clock*/
  CG_SetPerifClk(clkinit->pfsel,clkinit->prck);
  /*Set Sys clock*/
  CG_SetSysClk(clkinit->fcsel,clkinit->gear);
  /*Init USB clk*/
  /* If usb_pll select*/
  if(CLK_USBPLL == clkinit->usbl_clk_sel)
  {
    CG_SetUSB_Pll(clkinit->usbpll_enable,clkinit->usbpllmul);
  }
  else
  {
    CG_SelUSB_Clk(clkinit->usbl_clk_sel);
  }
  /* LP OSC set*/
  CG_ExtLP_OscEnable(clkinit->lposc);
}

