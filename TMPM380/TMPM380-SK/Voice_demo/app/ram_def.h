/*******************************************************************************
* File Name          : ram_def.h
* Version            : V1.0
* Date				 : 2009/05/xx
* Description        : RAM Definition
*******************************************************************************/


#ifndef __RAM_DEF_H
#define __RAM_DEF_H


#include	"../typedef.h"

#ifdef DBG
#include	"..\mcu\m380_port.h"
#endif

#ifdef RAM_DEF_SET     
	#define EXTER
#else
	#define EXTER extern
#endif


/********************************************************************
 * Variable Definition
 ********************************************************************/
/*======= TIMER  ========*/
#define	cTIMER_1SEC			500	/* 1sec/2ms */
#define	cWAITTIMER_MAX		5000	/* 10sec/2ms */
#define	cLEDTIMER_MAX		500000	/* 1000sec/2ms */

EXTER	uint16_t	g_wait_timer;
EXTER	uint32_t	g_led_timer;
EXTER	uint32_t	g_led_timer_buf;

/*======= VOICE  ========*/
#ifdef SAMPLE_8K
extern const short voice_data_08k[];
#endif
#ifdef SAMPLE_16K
extern const short voice_data_16k[];
#endif

EXTER	uint32_t	g_pcm_size;		/* sizeof(.voice)/sizeof(short) */
EXTER	uint32_t	g_pcm_cnt;		/* max sizeof(.voice) */
EXTER	short		g_pcm_data;		/* section .voice data */
EXTER	uint16_t	g_ppg_data;		/* speaker out data */
EXTER	uint8_t		g_voice_flg;	/* 0:none 1:voice */

EXTER	uint8_t		sampling_cnt;	/* sampling count 8KHz(1samp/4time) 16KHz(1samp/2time) */

/*======= MODE  ========*/
EXTER	uint8_t		g_md_sts;
#define		STOP	0
#define		RUN		1
#define		WAIT	2
#define		HALT	3

/*======= SW  ========*/
#define		cCHATACNT1		100		/* SW chattering count */
#define		cCHATACNT2		2		/* SW chattering count */
#define		cCHATACNT3		2		/* SW chattering count */

EXTER	uint8_t		g_sw1_data;		/* TSW1 Port Data */
EXTER	uint8_t		g_sw1_data_buf;
EXTER	uint16_t	g_sw1_chata_cnt;
EXTER	uint8_t		g_sw1_flg;

EXTER	uint8_t		g_sw2_data;		/* TSW2 Port Data */
EXTER	uint8_t		g_sw2_data_buf;
EXTER	uint16_t	g_sw2_chata_cnt;
EXTER	uint8_t		g_sw2_flg;

EXTER	uint8_t		g_sw3_data;		/* TSW3 Port Data */
EXTER	uint8_t		g_sw3_data_buf;
EXTER	uint16_t	g_sw3_chata_cnt;
EXTER	uint8_t		g_sw3_flg;

/*======= LED  ========*/
EXTER	uint8_t	g_led_port[4];
EXTER	uint8_t g_digit_cnt;


/*======= PPG  ========*/
#define	cPPGDUDY50	0x0271		/* 625/1250 */
#define	cPPGDUDY100	0x04E2		/* 1250/1250 */
#define	cPPGADJUST	0x0001		/* 0<RG0<RG1<RG4<0xFFFF */

/*======= PORT  ========*/
#ifdef PORT_REFRESH
EXTER	uint8_t	port_data[15];
#endif





#endif  // __RAM_DEF_H

/*************************** END OF FILE **************************************/
