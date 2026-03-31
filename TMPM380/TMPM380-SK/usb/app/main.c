/*******************************************************************************
* File Name          : main.c
* Version            : V1.0
* Date				 : 2010/03/XX
* Description        : USB-UART Bridge demo application (main)
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stddef.h>
#include "intrinsics.h"

#include "typedef.h"
#include "TMPM380_SYS.h"
#include "m380_port.h"
#include "mcu_set.h"
#include "uart.h"

#define P_USB_COM		2

/********************************************************************
 * External Definition
 ********************************************************************/

/********************************************************************
 * Variable Definition
 ********************************************************************/
 
/*======= 7SEG DATA  ========*/
#define	c7SEG_OFF		0x7F
#define	c7SEG_ON		0x80

#define	cDOT_OFF		0x80
#define	cDOT_ON			0x00

#define	cLedDat0	0xC0	/* 0b11000000 */
#define	cLedDat1	0xF9	/* 0b11111001 */
#define	cLedDat2	0xA4	/* 0b10100100 */
#define	cLedDat3	0xB0	/* 0b10110000 */
#define	cLedDat4	0x99	/* 0b10011001 */
#define	cLedDat5	0x92	/* 0b10010010 */
#define	cLedDat6	0x82	/* 0b10000010 */
#define	cLedDat7	0xD8	/* 0b11011000 */
#define	cLedDat8	0x80	/* 0b10000000 */
#define	cLedDat9	0x90	/* 0b10010000 */

/*======= LED DIGIT  ========*/
#define	cALL_DIGIT_CLR	0xF0

#define	cLedCom0	0x70
#define	cLedCom1	0xB0
#define	cLedCom2	0xD0
#define	cLedCom3	0xE0

uint8_t	g_led_port[4];
uint8_t g_digit_cnt;

/********************************************************************
 * Constant Definition
 ********************************************************************/
const uint8_t	g_Number2Port[] = {
	cLedDat0, cLedDat1, cLedDat2, cLedDat3, cLedDat4,
	cLedDat5, cLedDat6, cLedDat7, cLedDat8, cLedDat9
};
const uint8_t	g_digit_port[] = {cLedCom0, cLedCom1, cLedCom2, cLedCom3};
const uint8_t Test_Str1[] = "\r\nHello!! \r\nThis program is running with TMPM380\r\n";

/********************************************************************
 * Function Definition
 ********************************************************************/

/****************************************************************************************
 * Module   : main
 *---------------------------------------------------------------------------------------
 * Function : main loop
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void main(void) 
{
	uint8_t rcvbuf[16], cnt;
	uint16_t rxdatcnt = 0;
	uint8_t leddata = 0x55;

	g_led_port[0] = cLedDat0;
	g_led_port[1] = cLedDat0;
	g_led_port[2] = cLedDat0;
	g_led_port[3] = 0x00;

	/* Initialize System */
	Sys_Initialize();			/* Initialize System */
	Port_Initialize();			/* Initialize Port */
	Int_Initialize();			/* Initialize Interrupt */

	Led_Data_Write(cLedDat0);
	Led_Digit_Write(cLedCom0);
	Led_Digit_Write(cLedCom1);
	Led_Digit_Write(cLedCom2);

	UART_Init(P_USB_COM, 57600);
	
	__enable_interrupt();		/* Enable interrupt */

	UART_Send(P_USB_COM, (uint8_t *)Test_Str1);

	/* Echo back program */
	while(1) {
		cnt = UART_Recv(P_USB_COM, rcvbuf);
		if (cnt) {
			rxdatcnt += cnt;
			rcvbuf[cnt] = 0;
			UART_Send(P_USB_COM, rcvbuf);

			leddata = ~leddata;
		}

		/* LED display update */
		Led_Data_Write(leddata);
		Led_Digit_Write(cLedCom3);
		Led_Digit_Write(cALL_DIGIT_CLR);
		Led_Data_Write(g_Number2Port[rxdatcnt%10]);
		Led_Digit_Write(cLedCom2);
		Led_Digit_Write(cALL_DIGIT_CLR);
		Led_Data_Write(g_Number2Port[(rxdatcnt/10)%10]);
		Led_Digit_Write(cLedCom1);
		Led_Digit_Write(cALL_DIGIT_CLR);
		Led_Data_Write(g_Number2Port[(rxdatcnt/100)%10]);
		Led_Digit_Write(cLedCom0);
		Led_Digit_Write(cALL_DIGIT_CLR);
	}


}
