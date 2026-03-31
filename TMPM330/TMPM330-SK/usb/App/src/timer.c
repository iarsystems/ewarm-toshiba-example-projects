/******************** (c) Copyright IAR Systems 2009 ********************
* File Name          : uart.c
* Version            : V1.0
* Date               : 20/10/2008
* Description        : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "timer.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
* Function Name  : Timer_Init
* Description    : Initialize the timer
* Input          : None.
* Return         : None.
*******************************************************************************/
void Timer_Init(void)
{
	API_TMRB_Init(TMRB1);
	// Starts the TMRB1 module
	API_TMRB_IP_Enable(TMRB1, ENABLE);
	//API_TMRB_Idle(TMRB1, ENABLE);
	// enable the prescale
	// Stops the TMRB1 module
	API_TMRB_PreRun(TMRB1, TMRB_STOP);
	API_TMRB_CountRun(TMRB1, TMRB_STOP);
	// ...
	//...
}

/*******************************************************************************
* Function Name  : Audio_Out
* Description    : output the audio signal
* Input          : None.
* Return         : None.
*******************************************************************************/
void Audio_Out(void)
{
	Timer_Init();
		// Specifies a duty
	API_TMRB_RG0_Write(TMRB1, 2000);
	//Specifies a cycle
	API_TMRB_RG1_Write(TMRB1, 4000);
	// Enables the TB1RG0 double buffering
	API_TMRB_W_Buffer(TMRB1, ENABLE);
	// Specifies to trigger TB0FF0 to reverse
	//API_TMRB_Ff_RevTiming(TMRB1, DISABLE, DISABLE, ENABLE, ENABLE);
	//API_TMRB_FF_Ctl(TMRB1, 0x02);
	API_TMRB_FFCrSet(TMRB1, 0xCE);
	
	// T16 as the input clock, disables the capture function, uc0 enable	
	API_TMRB_UpCntClearEnable(TMRB1, ENABLE);
	API_TMRB_ClkSel(TMRB1, 0x03);
	// disable all interrupr
	API_TMRB_IntMaskSet(TMRB1, ENABLE, ENABLE, ENABLE);
	// Starts TMRB1
	API_TMRB_PreRun(TMRB1, TMRB_RUN);
	API_TMRB_CountRun(TMRB1, TMRB_RUN);
	//while(1);
}

