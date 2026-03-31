/*******************************************************************************
* File Name 		 : m380_wdt.c
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : WDT liblary source
********************************************************************************/
#include "..\typedef.h"
#include "TMPM380_SYS.h"


#include "m380_wdt.h"


/*******************************************************************************
* Function Name  : API_WDT_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_WDT_Init(void)
{

/*
	WDT.WDMOD = cWDT_MOD_INIT;
	WDT.WDCR = cWDT_CR_INIT;
*/
	WDT.WDMOD = cWDT_MOD_DISABLE;
	WDT.WDCR = IP_WDT_DISABLECODE;



}

/*******************************************************************************
* Function Name  : API_WDT_Set_WdtMode
* Description	 : 
* Input 		 : WDMOD
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_WDT_Set_WdtMode(uint8_t wdmod)
{
	WDT.WDMOD = wdmod;
}

/*******************************************************************************
* Function Name  : API_WDT_Set_WdtCtrl
* Description	 : 
* Input 		 : WDCR
* Output		 : wdcr(setting data)
* Return		 : 
*******************************************************************************/
void API_WDT_Set_WdtCtrl(uint8_t wdcr)
{
	WDT.WDCR = wdcr;
}

