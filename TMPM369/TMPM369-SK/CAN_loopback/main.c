/***********************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *   (c) Copyright IAR Systems 2012
 *
 *   File name   : main.c
 *
 **********************************************************************/

#include <intrinsics.h>
#include "board.h"
#include "drv_cg.h"
#include "can.h"

#pragma section=".intvec"

#define CAN_CODE_LED1	0x12
#define CAN_CODE_LED2	0x34
#define CAN_CODE_LED3	0x56
#define CAN_CODE_LED4	0x78
#define CAN_CODE_LED5	0x9A

const cg_clkinit_t CG_clkinit = {
  .gear = GEAR_FC,
  .fcsel = FCSEL_FPLL,
  .pfsel = FPSEL_FC,
  .prck = PRCK_1,
  .fosc = FOSCSEL_EXTOSC,
  .pll_enable = CG_ENABLE,
  .pllmul = PLLSET_16MHZ_48MHZ,
  .lposc = CG_ENABLE,
  .usbl_clk_sel = CLK_USBPLL,
  .usbpll_enable = CG_ENABLE,
  .usbpllmul = PLLSET_16MHZ,
};

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

	InitClock(&CG_clkinit);		/* Setup clock controller */

  /* LEDs init */
  INIT_LEDS();
  LED_ON(LED1);
  LED_ON(LED2);
  LED_ON(LED3);
  LED_ON(LED4);

  /* Joystick init */
  JS_INIT();

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
			if (RecvMsg.data[0] == CAN_CODE_LED1)
			{
        if(RecvMsg.data[1]==0)
        {
          LED_OFF(LED1);
        }
        else
        {
          LED_ON(LED1);
        }
			}
			if (RecvMsg.data[2] == CAN_CODE_LED2)
			{
        if(RecvMsg.data[3]==0)
        {
          LED_OFF(LED2);
        }
        else
        {
          LED_ON(LED2);
        }
			}
		}

		/* Send CAN message to Mailbox ch1 */
		SendMsg.atr = MbxAtr_Ch1;
		SendMsg.data[0] = CAN_CODE_LED1;
		SendMsg.data[1] = (JS_LEFT_PORT & JS_LEFT)?1:0;
		SendMsg.data[2] = CAN_CODE_LED2;
		SendMsg.data[3] = (JS_RIGHT_PORT & JS_RIGHT)?1:0;
		SendMsg.dlen = 4;
		CAN_SendMsg(1, &SendMsg);

		/* Receive CAN message at Mailbox ch4 */
		rtn = CAN_RecvMsg(4, &RecvMsg);
		if (rtn == 0)
		{
			if (RecvMsg.data[0] == CAN_CODE_LED3)
			{
        if(RecvMsg.data[1]==0)
        {
          LED_OFF(LED3);
        }
        else
        {
          LED_ON(LED3);
        }
			}
			if (RecvMsg.data[2] == CAN_CODE_LED4)
			{
        if(RecvMsg.data[3]==0)
        {
          LED_OFF(LED4);
        }
        else
        {
          LED_ON(LED4);
        }
			}
		}
		
		/* Send CAN message to Mailbox ch5 */
		SendMsg.atr = MbxAtr_Ch5;
		SendMsg.data[0] = CAN_CODE_LED3;
		SendMsg.data[1] = (JS_UP_PORT & JS_UP)?1:0;
		SendMsg.data[2] = CAN_CODE_LED4;
		SendMsg.data[3] = (JS_DOWN_PORT & JS_DOWN)?1:0;
		SendMsg.dlen = 4;
		CAN_SendMsg(5, &SendMsg);
	}
}
