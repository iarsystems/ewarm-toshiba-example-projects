/*******************************************************************************
* File Name          : led_ctrl.c
* Version            : V1.0
* Date				 : 2010/01/XX
* Description        : LED Contorl
*******************************************************************************/
#include	"ram_def.h"

#include	"..\mcu\m380_tmrb.h"
#include	"..\mcu\m380_int.h"

#include	"led_ctrl.h"
#include	"mcu_set.h"

/********************************************************************
 * Extern Definition
 ********************************************************************/

/********************************************************************
 * Variable Definition
 ********************************************************************/

/********************************************************************
 * Constant Definition
 ********************************************************************/
/*======= TIMER =======*/
#define	cTimer100	100
#define	cTimer10	10
#define	cTimer1		1

/*======= VOICE LVL DATA  ========*/
#define	cLvlPeriod	50
#define	cPPG_MAX	1025
#define	cPPG_MID	625
#define	cPPG_MIN	225

#define	cVcLvl0		0xFF	/* 0b11111111 */
#define	cVcLvl1		0x7F	/* 0b01111111 */
#define	cVcLvl2		0x3F	/* 0b00111111 */
#define	cVcLvl3		0x1F	/* 0b00011111 */
#define	cVcLvl4		0x0F	/* 0b00001111 */
#define	cVcLvl5		0x07	/* 0b00000111 */
#define	cVcLvl6		0x03	/* 0b00000011 */
#define	cVcLvl7		0x01	/* 0b00000001 */
#define	cVcLvl8		0x00	/* 0b00000000 */
const uint8_t	g_Level2Port[] = {
	cVcLvl0, cVcLvl1, cVcLvl2, cVcLvl3, cVcLvl4,
	cVcLvl5, cVcLvl6, cVcLvl7, cVcLvl8
};

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
const uint8_t	g_Number2Port[] = {
	cLedDat0, cLedDat1, cLedDat2, cLedDat3, cLedDat4,
	cLedDat5, cLedDat6, cLedDat7, cLedDat8, cLedDat9
};

/*======= LED DIGIT  ========*/
#define	cALL_DIGIT_CLR	0xF0

#define	cLedCom0	0x70
#define	cLedCom1	0xB0
#define	cLedCom2	0xD0
#define	cLedCom3	0xE0
const uint8_t	g_digit_port[] = {cLedCom0, cLedCom1, cLedCom2, cLedCom3};

/********************************************************************
 * Function Definition
 ********************************************************************/
/* static function */
void Count2Disp(uint32_t data);
void Data2Level(uint16_t data);

/****************************************************************************************
 * Module   : Led_Data
 *---------------------------------------------------------------------------------------
 * Function : Led_Data
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
/*
---------------------------------------------------------
PA(activ 'L')  | PG7 | PG6|PG5 |PG4 | PG3 |PA2 |PA1 |PA0 | 
---------------------------------------------------------
LLE1-3(7SEG+DP)| dp  | g  | f  | e  |  d  | c  | b  | a |
---------------------------------------------------------
LED4-11        |LED11|LED9|LDE7|LED5|LED10|LED8|LED6|LED4|
---------------------------------------------------------
------------------------------------------------------
(Left)         |LED1|LED2|LDE3|LED4-11| --   | (Right)
------------------------------------------------------
g_led_port[]   | 0  | 1  | 2  | 3     | --   |
------------------------------------------------------
*/

void Led_Data(void)
{

	/* LED1-3 (7SEG_LED) */
	switch(g_md_sts){
		case STOP:				/* "000" */
			g_led_port[0] = cLedDat0;
			g_led_port[1] = cLedDat0;
			g_led_port[2] = cLedDat0;
			break;
		case RUN:				/* timer count */
			Count2Disp(g_led_timer);
			break;
		case WAIT:			/* no action */
			break;
		case HALT:			/* no action */
			break;
		default:
			break;
	}

	/* LED4-11 */
	switch(g_md_sts){
		case STOP:				/* ALL ON */
			g_led_port[3] = cVcLvl8;
			break;
		case RUN:				/* voice level meter */
			Data2Level(g_ppg_data);
			break;
		case WAIT:			/* no action */
			break;
		case HALT:			/* no action */
			break;
		default:
			break;
	}


}


/****************************************************************************************
 * Module   : Led_Ctrl
 *---------------------------------------------------------------------------------------
 * Function : Led_Ctrl
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
/*
------------------------------------------------------
PG(activ 'L')  |PG7 |PG6 |PG5 |PG4    |PG3-0 | 
------------------------------------------------------
(Left)         |LED1|LED2|LDE3|LED4-11| --   |
------------------------------------------------------
cLedCom        |Com0|Com1|Com2|Com3   | --   |
------------------------------------------------------
g_led_digit_cnt| 0  | 1  | 2  | 3     | --   |
------------------------------------------------------
g_digit_port[] | 0  | 1  | 2  | 3     | --   |
------------------------------------------------------
g_led_port[]   | 0  | 1  | 2  | 3     | --   |
------------------------------------------------------
*/

void Led_Ctrl(void)
{

	uint8_t ledcom;
	uint8_t leddat;

	ledcom = g_digit_port[g_digit_cnt];
	leddat = g_led_port[g_digit_cnt];
	g_digit_cnt++;
	if(g_digit_cnt >3){
		g_digit_cnt = 0;
	}

	Led_Digit_Write(cALL_DIGIT_CLR);	/* all digit clear */
	Led_Data_Write(leddat);				/* set data */
	Led_Digit_Write(ledcom);			/* set digit */

}


/****************************************************************************************
 * Module   : Count2Disp
 *---------------------------------------------------------------------------------------
 * Function : Count2Disp
 * Input    : data: timer count
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void Count2Disp(uint32_t data) {

	uint16_t	databuf;
	uint8_t	data100;
	uint8_t	data10;
	uint8_t	data1;
	
	databuf = (uint16_t)(data/cTIMER_1SEC);
	
	data10 = (uint8_t)(databuf % cTimer100);
	data1 = data10 % cTimer10;
	g_led_port[2] = g_Number2Port[data1];

	data10 = data10/cTimer10;
	g_led_port[1] = g_Number2Port[data10];

	data100 = (uint8_t)(databuf/cTimer100);
	g_led_port[0] = g_Number2Port[data100];

}
/****************************************************************************************
 * Module   : Data2Level
 *---------------------------------------------------------------------------------------
 * Function : Data2Level
 * Input    : data : PPG data
 * Output   : none
 * Note     : 
 ****************************************************************************************/

void Data2Level(uint16_t data) {

	uint8_t	lvl;
	
	if(data > cPPG_MID){
		if(data > cPPG_MAX){
			g_led_port[3] = cVcLvl8;
		}
		else{
			lvl = (uint8_t)((data - cPPG_MID)/cLvlPeriod);
			g_led_port[3] = g_Level2Port[lvl+1];
		}
	}
	else if(data == cPPG_MID){
		g_led_port[3] = g_Level2Port[0];
	}
	else{
		if(data < cPPG_MIN){
			g_led_port[3] = cVcLvl8;
		}
		else{
			lvl = (uint8_t)((cPPG_MID - data)/cLvlPeriod);
			g_led_port[3] = g_Level2Port[lvl+1];
		}
	}
}

/*********************************** END OF FILE ******************************/
