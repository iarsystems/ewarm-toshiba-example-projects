/*******************************************************************************
* File Name 		 : m380_wdt.h
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : WDT header
********************************************************************************/

#ifndef __M380_WDT_H
#define __M380_WDT_H

#include "..\typedef.h"


/* WDT initial data */
#define		cWDT_MOD_DISABLE		BIT8(0,1,0,1,0,0,1,0)
#define		cWDT_MOD_ENABLE			BIT8(1,1,0,1,0,0,1,0)
/*									     | | | | | | | +------; 		Write "0".
									     | | | | | | +--------; RESCR	Watchdog timer out control
									     | | | | | |          ;			{ 0:Generates NMI interrupt, 1:Connects WDT out to reset }
									     | | | | | +----------; I2WDT	IDLE
									     | | | | |            ;			{ 0:Stop, 1:Start}
									     | | | | +------------;			"0" is read.
									     | +-+-+--------------; WDTP	Selects WDT detection time
									     |                    ;			{ 000: 2^16/fsys, 001: 2^18/fsys, 010: 2^20/fsys, 011: 2^22/fsys
									     |                    ;			  100: 2^24/fsys, 101: 2^26/fsys, 110: Setting prohibited, 111: Setting prohibited }
									     +--------------------; WDTE	Enable/disable control of the watchdog timer
									                                    { 0:Disable, 1:Enable }
*/


#define IP_WDT_DISABLECODE	0xB1
#define IP_WDT_CLEARCODE	0x4E


#define		WDT_CODE_CLEAR		API_WDT_Set_WdtCtrl(IP_WDT_CLEARCODE)

/**************************************************************/
void API_WDT_Init(void);
void API_WDT_Set_WdtMode(uint8_t wdmod);
void API_WDT_Set_WdtCtrl(uint8_t wdcr);


#endif /* __M380_WDT_H */ 





