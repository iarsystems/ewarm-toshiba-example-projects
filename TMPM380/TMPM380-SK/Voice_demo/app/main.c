/*******************************************************************************
* File Name          : main.c
* Version            : V1.0
* Date				 : 2010/01/XX
* Description        : Voice application (main)
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stddef.h>
#include "intrinsics.h"

#include	"../typedef.h"

#define RAM_DEF_SET
#include	"ram_def.h"
#undef RAM_DEF_SET

#include	"..\mcu\m380_wdt.h"

#include	"mcu_set.h"
#include	"mode_ctrl.h"
#include	"tmr_ctrl.h"
#include	"led_ctrl.h"

#ifdef SAMPLE_8K
//#include	"..\data\voice_data_08k.h"
extern const short voice_data_08k[];
extern unsigned long sizeof_voice_data_08k;
#endif
#ifdef SAMPLE_16K
//#include	"..\data\voice_data_16k.h"
extern const short voice_data_16k[];
extern unsigned long sizeof_voice_data_16k;
#endif

#include	"spiflash.h"

//#define SPIFLASH_SELFTEST

/********************************************************************
 * External Definition
 ********************************************************************/

/********************************************************************
 * Variable Definition
 ********************************************************************/
#ifdef SPIFLASH_SELFTEST
uint8_t pagebuf[PAGE_SIZE];
uint8_t pagebuf_rx[PAGE_SIZE];
#endif

/********************************************************************
 * Constant Definition
 ********************************************************************/

/********************************************************************
 * Function Definition
 ********************************************************************/
void User_Init(void);
void Ram_Init(void);

/****************************************************************************************
 * Module   : main
 *---------------------------------------------------------------------------------------
 * Function : main loop
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void main(void) {

#ifdef SPIFLASH_SELFTEST
	uint32_t dlen, i;
	volatile uint32_t faddr;
	volatile uint32_t errcnt;
#endif

	__disable_interrupt();			/* Disable interrupt */
	
	/* Initialize System */
	Sys_Initialize();			/* Initialize System */
	Port_Initialize();			/* Initialize Port */
	Int_Initialize();			/* Initialize Interrupt */
	Timer4_Start();				/* Initialize & Start TMBR4 */

	__enable_interrupt();		/* Enable interrupt */
	
	User_Init();					/* Initialize User mode */
	Timer4_Stop();			/* Stop TMBR4 */

	__disable_interrupt();			/* Disable interrupt */

	MPTimer_Initialize();		/* Initialize Multi-purpose Timers Control Register */
	Timer_Initialize();			/* Initialize Timer Control Register */

	spiflash_init();			/* SPI Flash device interface setup */

	Ram_Init();					/* Initialize User data */

#ifdef SPIFLASH_SELFTEST
	for (faddr=0, errcnt=0;;) {
		if ((faddr % BLOCK_SIZE) == 0) {
			spiflash_erase(faddr, BLOCK_SIZE);
			for (dlen=0; dlen < BLOCK_SIZE; dlen += PAGE_SIZE) {
				spiflash_read(faddr+dlen, pagebuf, PAGE_SIZE);
				for (i=0; i<PAGE_SIZE; i++) {
					if (pagebuf[i] != 0xFF) {
						errcnt++;
					}
				}
			}
		}

		for (i=0; i<PAGE_SIZE; i++) {
			pagebuf[i] = (uint8_t)(i+(faddr>>8));
		}
		spiflash_write(faddr, pagebuf, PAGE_SIZE);
		faddr += spiflash_read(faddr, pagebuf_rx, PAGE_SIZE);
		for (i=0; i<PAGE_SIZE; i++) {
			if (pagebuf[i] != pagebuf_rx[i]) {
				errcnt++;
			}
		}
		if (faddr > FLASH_SIZE)	break;
	}

	if (errcnt) {
		printf("\nError: Flash data Verification error");
	}
	else {
    	printf("\nFlash data Verified without error");
    }
#endif

	__enable_interrupt();		/* Enable interrupt */


	while(1) {
		WDT_CODE_CLEAR;			/* CLEAR WDT */
		Mode_ctrl();
		Led_Data();
#ifdef PORT_REFRESH
		Port_Refresh();
#endif
	}

}

/****************************************************************************************
 * Module   : Ram_Init
 *---------------------------------------------------------------------------------------
 * Function : Ram Initialize
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void Ram_Init(void) {

#ifdef SAMPLE_8K
//	g_pcm_size = sizeof(voice_data_08k)/sizeof(short);
	g_pcm_size = sizeof_voice_data_08k;
#endif
#ifdef SAMPLE_16K
//	g_pcm_size = sizeof(voice_data_16k)/sizeof(short);
	g_pcm_size = sizeof_voice_data_16k;
#endif

}

/****************************************************************************************
 * Module   : User_Init
 *---------------------------------------------------------------------------------------
 * Function : Initialize User mode
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/

void User_Init(void)
{

	while(1){
		WDT_CODE_CLEAR;			/* CLEAR WDT */
		if((g_sw3_flg==1) && (g_sw2_flg==1)){
			break;
		}
	}

}



