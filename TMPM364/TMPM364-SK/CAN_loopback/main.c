/***********************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *   (c) Copyright IAR Systems 2011
 *
 *   File name   : main.c
 *
 **********************************************************************/

#include <Toshiba\iotmpm364F10FG.h>
#include <intrinsics.h>
#include "can.h"

#pragma section=".intvec"

#define XTAL_CLOCK		(12000000UL)
#define CAN_CODE_LED0	0x12
#define CAN_CODE_LED1	0x34
#define CAN_CODE_LED2	0x56
#define CAN_CODE_LED3	0x78

/***********************************************************************
 * Function:	Clock_Init
 * Description:	PLL setup
 * Parameters:	none
 * Return:		none
 **********************************************************************/
void Clock_Init(void)
{
	/*External oscilator enable*/
	CGOSCCR_bit.XTEN = 1;
	CGOSCCR_bit.XEN = 1;
	/*Selects warm-up counter by external oscillator*/
	CGOSCCR_bit.WUPSEL = 1;
	CGOSCCR_bit.WUPT = 256; /*wait some clocks from external oscilatior*/
	/*Start warm up*/
	CGOSCCR_bit.WUEON = 1;
	while(CGOSCCR_bit.WUEF)
	{}
	/*Disable PLL*/
	CGOSCCR_bit.PLLON = 0;
	CGPLLSEL_bit.PLLSEL = 0;
	/*Setup PLL*/
	CGPLLSEL_bit.ND = 3;
	CGPLLSEL_bit.C2S = 0;
	CGPLLSEL_bit.IS = 1;
	CGPLLSEL_bit.RS = 7;

	/*start PLL*/
	CGOSCCR_bit.PLLON = 1;
	/*wait to lock 200us*/
	CGOSCCR_bit.WUPT = 200*XTAL_CLOCK/1000000;
	CGOSCCR_bit.WUPSEL = 0;
	/*Start warm up*/
	CGOSCCR_bit.WUEON = 1;
	while(CGOSCCR_bit.WUEF)
	{}
	/*Set Prescalers*/
	CGSYSCR_bit.GEAR = 0;
	CGSYSCR_bit.PRCK = 0;
	CGSYSCR_bit.FPSEL = 1;
	/*selecet PLL as clock*/
	CGPLLSEL_bit.PLLSEL = 1;
}

/***********************************************************************
 * Function:	main
 * Description:	application main function
 * Parameters:	none
 * Return:		none
 **********************************************************************/
void main(void)
{
	volatile unsigned char i=0;
	volatile int j;
	int rtn;
	sCANSetup can_setpar;
	sCANMsgType MbxAtr_Ch0 = {111, 0, 0};	/* ch0: Rx Id=111 (Standard) */
	sCANMsgType MbxAtr_Ch4 = {133, 1, 0};	/* ch4: Rx Id=133 (Extended) */

	sCANMsgType MbxAtr_Ch1 = {111, 0, 0};	/* ch1: Tx Id=111 (Standard) */
	sCANMsgType MbxAtr_Ch5 = {133, 1, 0};	/* ch5: Tx Id=133 (Extended) */
	sCANMsg SendMsg, RecvMsg;

	__disable_interrupt();
	VTOR  = (unsigned int)__segment_begin(".intvec");

	WDMOD = 0x00;
	WDCR = 0xB1;		/* Disable WatchDog control */

	Clock_Init();		/* Setup clock controller */

	PMFR1 = 0x00;		/* LED Port Function */
	PMIE = 0;			/* Disable input */
	PMCR = 0xFF;		/* Enable LED Output */

	PJFR2 &= 0x0F;		/* Key Pins as GPIO port */
	PJDATA &= 0x0F;
	PJIE |= 0xF0;		/* Key posrt pins as input */
	PJPUP &= 0x0F;

	can_setpar.loopback = 1;		/* Loopback mode */
	can_setpar.baudrate = 200000;	/* 200kbps baudrate */
	CAN_Init(&can_setpar);
	CAN_SetMbx_Rx(0, &MbxAtr_Ch0);	/* ch0: Rx Id=111 (Standard) */
	CAN_SetMbx_Rx(4, &MbxAtr_Ch4);	/* ch4: Rx Id=133 (Extended) */
	CAN_SetMbx_Tx(1, &MbxAtr_Ch1);	/* ch1: Tx Id=111 (Standard) */
	CAN_SetMbx_Tx(5, &MbxAtr_Ch5);	/* ch5: Tx Id=133 (Extended) */
	__enable_interrupt();

	while(1)
	{	/* Receive CAN message at Mailbox ch0 */
		rtn = CAN_RecvMsg(0, &RecvMsg);
		if (rtn == 0)
		{
			if (RecvMsg.data[0] == CAN_CODE_LED0)
			{
				PMDATA_bit.PM0 = ((RecvMsg.data[1]==0)?1:0);
			}
			if (RecvMsg.data[2] == CAN_CODE_LED1)
			{
				PMDATA_bit.PM1 = ((RecvMsg.data[3]==0)?1:0);
			}
		}

		/* Send CAN message to Mailbox ch1 */
		SendMsg.atr = MbxAtr_Ch1;
		SendMsg.data[0] = CAN_CODE_LED0;
		SendMsg.data[1] = ((PJDATA_bit.PJ7==0)?1:0);
		SendMsg.data[2] = CAN_CODE_LED1;
		SendMsg.data[3] = ((PJDATA_bit.PJ6==0)?1:0);
		SendMsg.dlen = 4;
		CAN_SendMsg(1, &SendMsg);

		/* Receive CAN message at Mailbox ch4 */
		rtn = CAN_RecvMsg(4, &RecvMsg);
		if (rtn == 0)
		{
			if (RecvMsg.data[0] == CAN_CODE_LED2)
			{
				PMDATA_bit.PM2 = ((RecvMsg.data[1]==0)?1:0);
			}
			if (RecvMsg.data[2] == CAN_CODE_LED3)
			{
				PMDATA_bit.PM3 = ((RecvMsg.data[3]==0)?1:0);
			}
		}
		
		/* Send CAN message to Mailbox ch5 */
		SendMsg.atr = MbxAtr_Ch5;
		SendMsg.data[0] = CAN_CODE_LED2;
		SendMsg.data[1] = ((PJDATA_bit.PJ5==0)?1:0);
		SendMsg.data[2] = CAN_CODE_LED3;
		SendMsg.data[3] = ((PJDATA_bit.PJ4==0)?1:0);
		SendMsg.dlen = 4;
		CAN_SendMsg(5, &SendMsg);
	}
}
