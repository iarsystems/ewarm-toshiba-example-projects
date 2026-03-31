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
#include "sd_spi.h"
#include "sd_spi_mode.h"

#define P_USB_COM		2
#define TEST_STARTBLOCK		0
#define TEST_ENDBLOCK		1000

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
__no_init uint8_t SDBuffer[512];

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
	uint8_t dbuf[40], cnt;
	DiskStatusCode_t StatusHold = (DiskStatusCode_t) -1;
	uint32_t Size,Tmp,Card_Size;
	Boolean card_in, test_flag;
	DiskStatusCode_t TestResult;
	uint32_t BlockNum, i, _Headcnt;

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
	SdDiskInit();				/* SD Card Interface initialization */

	__enable_interrupt();		/* Enable interrupt */

	UART_Send(P_USB_COM, (uint8_t *)Test_Str1);
	card_in = FALSE;
	test_flag = FALSE;

	/* SD Card detect program */
	while(1) {
		SdStatusUpdate();		/* Update SD card status */
		// Current state of MMC/SD show
		pDiskCtrlBlk_t pMMCDiskCtrlBlk = SdGetDiskCtrlBkl();

		if(StatusHold != pMMCDiskCtrlBlk->DiskStatus) {
			StatusHold = pMMCDiskCtrlBlk->DiskStatus;
			switch (pMMCDiskCtrlBlk->DiskStatus) {
			case DiskCommandPass:
				// Calculate MMC/SD size [MB]
				Size = (pMMCDiskCtrlBlk->BlockNumb * pMMCDiskCtrlBlk->BlockSize);
				Tmp  = Size/1000000;
				Tmp += ((Size%1000000)<1000000/2)?0:1;

				UART_Send(P_USB_COM, (uint8_t *)"Found SD Card in socket.\r\n");
				sprintf((char *)dbuf, "\tDisk Size = %d MB\r\n",Tmp);
				UART_Send(P_USB_COM, dbuf);
				sprintf((char *)dbuf, "\tBlock Count = %d\r\n",pMMCDiskCtrlBlk->BlockNumb);
				UART_Send(P_USB_COM, dbuf);
				sprintf((char *)dbuf, "\tBlock Size = %d\r\n",pMMCDiskCtrlBlk->BlockSize);
				UART_Send(P_USB_COM, dbuf);
				if (pMMCDiskCtrlBlk->DiskType == DiskSD_Spec1_x)
					UART_Send(P_USB_COM, "\tDisk Type = SD Class 1\r\n");
				else if (pMMCDiskCtrlBlk->DiskType == DiskSD_Spec2_0)
					UART_Send(P_USB_COM, "\tDisk Type = SD Class 2\r\n");
				if (pMMCDiskCtrlBlk->WriteProtect)
					UART_Send(P_USB_COM, "\tDisk Write Protection is ON\r\n");
				else
					UART_Send(P_USB_COM, "\tDisk Write Protection is OFF\r\n");

				UART_Send(P_USB_COM, "\r\nPress 'Y' to Write & Verify SD-Card Block Data");
				UART_Send(P_USB_COM, "\r\nPrecaution: SD-Card original data will get lost by this test\r\n");
				
				card_in = TRUE;
				Card_Size = Tmp;
				break;
			default:
				UART_Send(P_USB_COM, (uint8_t *)"Please insert SD Card !!\r\n");
				card_in = FALSE;
				test_flag = FALSE;
				Card_Size = 0;
				break;
			}
		}

		/* LED display update */
		Led_Data_Write(card_in?0x00:0xFF);
		Led_Digit_Write(cLedCom3);
		Led_Digit_Write(cALL_DIGIT_CLR);
		Led_Data_Write(g_Number2Port[Card_Size%10]);
		Led_Digit_Write(cLedCom2);
		Led_Digit_Write(cALL_DIGIT_CLR);
		Led_Data_Write(g_Number2Port[(Card_Size/10)%10]);
		Led_Digit_Write(cLedCom1);
		Led_Digit_Write(cALL_DIGIT_CLR);
		Led_Data_Write(g_Number2Port[(Card_Size/100)%10]);
		Led_Digit_Write(cLedCom0);
		Led_Digit_Write(cALL_DIGIT_CLR);

		if ((card_in) && (cnt = UART_Recv(P_USB_COM, dbuf))) {
			for (i=0; i < cnt; i++) {
				if ((dbuf[i] == 'y') || (dbuf[i] == 'Y')) {
					test_flag = TRUE;
					break;
				}
			}
		}
		
		if (test_flag == FALSE) {
			continue;
		}
		if (pMMCDiskCtrlBlk->WriteProtect) {
			UART_Send(P_USB_COM, "Disk Write Protection is ON\r\n");
			UART_Send(P_USB_COM, "Turn OFF the Protection and re-insert the Card\r\n");
			test_flag = FALSE;
			continue;
		}
		UART_Send(P_USB_COM, "\r\nPlease do NOT remove SD-Card during Test\r\nRunning..");
		BlockNum = TEST_STARTBLOCK;
		for (_Headcnt=0; BlockNum < pMMCDiskCtrlBlk->BlockNumb; BlockNum++, _Headcnt+= 3) {
			if (BlockNum >= TEST_ENDBLOCK) {
				continue;
			}
			for (i=0; i<pMMCDiskCtrlBlk->BlockSize; i++) {
				SDBuffer[i] = (uint8_t)(_Headcnt + i);
			}
			TestResult = SdDiskIO(SDBuffer, BlockNum, 1, DiskWrite);
			if (DiskCommandPass != TestResult) {
				break;
			}
			TestResult = SdDiskIO(SDBuffer, BlockNum, 1, DiskVerify);
			if (DiskCommandPass != TestResult) {
				UART_Send(P_USB_COM, "\r\nSD-Card Test Failed at ");
				sprintf((char *)dbuf, "Block = %d\r\n",BlockNum);
				UART_Send(P_USB_COM, dbuf);
				break;
			}
			if ((BlockNum%50)==0) {
				UART_Send(P_USB_COM, ".");
			}
			Led_Data_Write(BlockNum&1?0x00:0xFF);
			Led_Digit_Write(cLedCom3);
			Led_Digit_Write(cALL_DIGIT_CLR);
		}

		if (DiskCommandPass != TestResult) {
			UART_Send(P_USB_COM, "\r\nSD-Card Test Aborted !!\r\n");
		}
		else {
			UART_Send(P_USB_COM, "\r\nSD-Card Test Done Successfully\r\n");
		}
		test_flag = FALSE;

	}


}
