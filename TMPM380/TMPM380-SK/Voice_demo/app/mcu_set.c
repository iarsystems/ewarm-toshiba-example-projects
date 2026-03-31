/*******************************************************************************
* File Name          : mce_set.c
* Version            : V1.0
* Date				 : 2009/05/xx
* Description        : mcu setting
*******************************************************************************/
#ifdef PORT_REFRESH
#include "intrinsics.h"
#endif

#include	"ram_def.h"

#include	"..\mcu\m380_port.h"
#include	"..\mcu\m380_tmrb.h"
#include	"..\mcu\m380_mpt.h"
#include	"..\mcu\m380_wdt.h"
#include	"..\mcu\m380_cg.h"
#include	"..\mcu\m380_int.h"

/********************************************************************
 * Extern Definition
 ********************************************************************/

/********************************************************************
 * Variable Definition
 ********************************************************************/

/********************************************************************
 * Constant Definition
 ********************************************************************/

/********************************************************************
 * Function Definition
 ********************************************************************/

/****************************************************************************************
 * Module   : Sys_Initialize
 *---------------------------------------------------------------------------------------
 * Function : Initialize System
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	Sys_Initialize(void)
{
	/* Initialize Watchdog Timer */
	API_WDT_Init();								/* WDT disable */
//	API_WDT_Set_WdtMode(cWDT_MOD_ENABLE);		/* WDT enable */

	/* Initialize Clock Generator (CG) Registers */
	API_CG_Init();
}


/****************************************************************************************
 * Module   : Int_Initialize
 *---------------------------------------------------------------------------------------
 * Function : Initialize interrupt
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	Int_Initialize(void)
{
	/*-----MCU INTERRUPT INITIALIZE -----*/
	API_INT_Init();

	API_INT_SPR_ALL_Set();		/* ALL PEND Clear */
}


/****************************************************************************************
 * Module   : Timer_Initialize
 *---------------------------------------------------------------------------------------
 * Function : Initialize Timer Control Register
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
/*
-------------------------
SW            |TSW3|TSW2|
-------------------------
LED disable   | 1  | *  |
-------------------------
LED 500us Out | 0  | 1  |
-------------------------
LED 5ms Out   | 0  | 0  |
-------------------------
*/
void	Timer_Initialize(void)
{

	/* INTTB1 500us LED outé¸ä˙äÑçûÇ›ê›íË */
	if((g_sw3_data == 0) && (g_sw2_data == 1)){ 
		API_TMRB_Init(TMRB_1);								/* Initialize,TBEn=1 */
	
		API_TMRB_CRSet(TMRB_1, BIT8(0,0,0,0,0,0,0,0));

		API_TMRB_ModSet(TMRB_1, BIT8(0,0,1,0,0,1,0,1));		/* Clear enable / clk= T4(0.05us@40MHz)) */
		API_TMRB_IntMaskSet(TMRB_1, BIT8(0,0,0,0,0,1,0,1));	/* TBIMOF=1, TBIM1=0, TBIM0=1 */
		API_TMRB_REG1_Write(TMRB_1, 10000);					/* 10000*0.05us = 500us */

		API_INT_PR_Set(EXT_INTTB11,0x40);					/* Set interrupt priority level */
		API_INT_SER_Set(EXT_INTTB11);						/* Enable INTTB11 */
	
		API_TMRB_RunSet(TMRB_1, BIT8(0,0,0,0,0,1,0,1));		/* Start Timer */
	}

	/* Set INTTB2 2ms cyclic interrupt */
	API_TMRB_Init(TMRB_2);									/* Initialize,TBEn=1 */
	
	API_TMRB_CRSet(TMRB_2, BIT8(0,0,0,0,0,0,0,0));

	API_TMRB_ModSet(TMRB_2, BIT8(0,0,1,0,0,1,1,0));			/* Clear enable / clk= T4(0.2us@40MHz)) */
	API_TMRB_IntMaskSet(TMRB_2, BIT8(0,0,0,0,0,1,0,1));		/* TBIMOF=1, TBIM1=0, TBIM0=1 */
	API_TMRB_REG1_Write(TMRB_2, 10000);						/* 10000*0.2us = 2ms */

	API_INT_PR_Set(EXT_INTTB21,0x60);						/* Set interrupt priority */
	API_INT_SER_Set(EXT_INTTB21);							/* Enable INTTB21 */
	
	API_TMRB_RunSet(TMRB_2, BIT8(0,0,0,0,0,1,0,1));			/* Start Timer */

	/* INTTB3 5ms LED out Cyclic interrupt set */
	if((g_sw3_data == 0) && (g_sw2_data == 0)){  
		API_TMRB_Init(TMRB_3);								/* Initialize,TBEn=1 */
	
		API_TMRB_CRSet(TMRB_3, BIT8(0,0,0,0,0,0,0,0));

		API_TMRB_ModSet(TMRB_3, BIT8(0,0,1,0,0,1,1,0));		/* Clear enable / clk= T4(0.2us@40MHz)) */
		API_TMRB_IntMaskSet(TMRB_3, BIT8(0,0,0,0,0,1,0,1));	/* TBIMOF=1, TBIM1=0, TBIM0=1 */
		API_TMRB_REG1_Write(TMRB_3, 25000);					/* 10000*0.2us = 5ms */

		API_INT_PR_Set(EXT_INTTB31,0x80);					/* Set interrupt priority level */
		API_INT_SER_Set(EXT_INTTB31);						/* INTTB31 ãñâ¬ */
	
		API_TMRB_RunSet(TMRB_3, BIT8(0,0,0,0,0,1,0,1));		/* Start Timer */
	}

}

/****************************************************************************************
 * Module   : MPTimer_Initialize
 *---------------------------------------------------------------------------------------
 * Function : IGBT mode
 * Input    : none
 * Output   : none
 * Note     : PPG output with a period specified with MTIG0RG4 (MT0OUT0 H start)
 ****************************************************************************************/
void	MPTimer_Initialize(void)
{
	/* 31.25usé¸ä˙äÑçûÇ›ê›íË */
	API_MPT_Init(MPT_0);									/* Initialize,MTEn=1 */
	API_MPT_ModSet(MPT_0, MPT_IGBT),						/* MTMODE=IGBT */

	API_MTIG_CRSet(MPT_0, 0x0000);							/* */
	API_MTIG_ICRSet(MPT_0, BIT8(0,0,0,0,0,0,0,0));			/* */
	API_MTIG_OCRSet(MPT_0, BIT8(0,0,0,1,0,0,0,1));			/* TB0OUT0 (active H) */

	/* MTTB0OUT0 output */
	API_MTTB_REG0_Write(MPT_0, cPPGADJUST);						/* 0*0.025us duty0% */
	API_MTTB_REG1_Write(MPT_0, cPPGDUDY50+cPPGADJUST);			/* 625*0.025us duty50% */

	/* MTTB0OUT0 output */
//	API_MTIG_REG2_Write(MPT_0, 0x0000);						/* no operation */
//	API_MTIG_REG3_Write(MPT_0, 0x0000);						/* no operation */

	/* IGBT period */
	API_MTIG_REG4_Write(MPT_0, cPPGDUDY100);			/* 1250*0.025us = 31.25us */

	API_INT_PR_Set(EXT_INTMTPTB00,0x20);					/* Set interrupt priority level */
	API_INT_SER_Set(EXT_INTMTPTB00);						/* enable INTMTPTB00 */

	API_MPT_RunSet(MPT_0, BIT8(0,0,0,0,0,1,0,1));			/* Start Timer */
}


/****************************************************************************************
 * Module   : Port_Initialize
 *---------------------------------------------------------------------------------------
 * Function : Initialize PortSetting
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	Port_Initialize(void)
{
	API_PORT_Init();

#ifdef PORT_REFRESH
	port_data[PORT_A] = PORT_PA_INIT;
	port_data[PORT_B] = PORT_PB_INIT;
	port_data[PORT_C] = PORT_PC_INIT;
	port_data[PORT_D] = PORT_PD_INIT;
	port_data[PORT_E] = PORT_PE_INIT;
	port_data[PORT_F] = PORT_PF_INIT;
	port_data[PORT_G] = PORT_PG_INIT;
	port_data[PORT_H] = PORT_PH_INIT;
	port_data[PORT_I] = PORT_PI_INIT;
	port_data[PORT_J] = PORT_PJ_INIT;
//	port_data[PORT_K] = PORT_PK_INIT;
	port_data[PORT_L] = PORT_PL_INIT;
	port_data[PORT_M] = PORT_PM_INIT;
	port_data[PORT_N] = PORT_PN_INIT;
	port_data[PORT_P] = PORT_PP_INIT;
#endif
}

#ifdef PORT_REFRESH
/****************************************************************************************
 * Module   : Port_Refresh
 *---------------------------------------------------------------------------------------
 * Function : Refresh Port
 * Input    : none
 * Output   : none
 * Note     : Set to Disable interrupt
 ****************************************************************************************/
void    Port_Refresh(void)
{
	volatile PORTM *port;

	__disable_interrupt();			/* Disable interrupt */

/* Port A */
	port = &PORT.cnl[PORT_A];
	port->IO_Px		= port_data[PORT_A];
/* Port B */
/* Input */
/*	port = &PORT.cnl[PORT_B];*/
/*	port->IO_Px		= port_data[PORT_B];*/
/* Port C */
	port = &PORT.cnl[PORT_C];
	port->IO_Px		= port_data[PORT_C];
/* Port D */
/* Input */
/*	port = &PORT.cnl[PORT_D];*/
/*	port->IO_Px		= port_data[PORT_D];*/
/* Port E */
	port = &PORT.cnl[PORT_E];
	port->IO_Px		= port_data[PORT_E];
/* Port F */
	port = &PORT.cnl[PORT_F];
	port->IO_Px		= port_data[PORT_F];
/* Port G */
	port = &PORT.cnl[PORT_G];
	port->IO_Px		= port_data[PORT_G];
/* Port H */
	port = &PORT.cnl[PORT_H];
	port->IO_Px		= port_data[PORT_H];
/* Port I */
	port = &PORT.cnl[PORT_I];
	port->IO_Px		= port_data[PORT_I];
/* Port J */
	port = &PORT.cnl[PORT_J];
	port->IO_Px		= port_data[PORT_J];
/* Port K */
//	port = &PORT.cnl[PORT_L];
//	port->IO_Px		= port_data[PORT_K];
/* Port L */
	port = &PORT.cnl[PORT_A];
	port->IO_Px		= port_data[PORT_L];
/* Port M */
	port = &PORT.cnl[PORT_M];
	port->IO_Px		= port_data[PORT_M];
/* Port N */
	port = &PORT.cnl[PORT_N];
	port->IO_Px		= port_data[PORT_N];
/* Port P */
	port = &PORT.cnl[PORT_P];
	port->IO_Px		= port_data[PORT_P];


	__enable_interrupt();			/* Enable interrupt */
}
#endif

/****************************************************************************************
 * Module   : SW1_Input
 *---------------------------------------------------------------------------------------
 * Function : SW1_Input(TSW1)
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	SW1_Input(void)
{
	uint8_t	portbuf;

	portbuf = API_PORT_BitIn(PORT_D0);			/* Read SW */

	if (portbuf == g_sw1_data_buf){				/* Same as last data */
		if (g_sw1_chata_cnt < cCHATACNT1){				/* Stable? */
			if (++g_sw1_chata_cnt >= cCHATACNT1){		/* Stable? */
				g_sw1_data = g_sw1_data_buf;		/* Settled */
			}
		}
	} else {
		g_sw1_data_buf = portbuf;					/* update "last data"  */
		g_sw1_chata_cnt = 0;							/* reset chattering counter */
	}

}

/****************************************************************************************
 * Module   : SW2_Input
 *---------------------------------------------------------------------------------------
 * Function : SW2_Input(TSW2)
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	SW2_Input(void)
{
	uint8_t	portbuf;

	portbuf = API_PORT_BitIn(PORT_D1);			/* Read SW */

	if (portbuf == g_sw2_data_buf){				/* Same as last data */
		if (g_sw2_chata_cnt < cCHATACNT2){				/* Stable? */
			if (++g_sw2_chata_cnt >= cCHATACNT2){		/* Stable? */
				g_sw2_data = g_sw2_data_buf;		/* Settled */
				g_sw2_flg = 1;
			}
		}
	} else {
		g_sw2_data_buf = portbuf;					/* update "last data" */
		g_sw2_chata_cnt = 0;							/* reset chattering counter */
	}

}

/****************************************************************************************
 * Module   : SW3_Input
 *---------------------------------------------------------------------------------------
 * Function : SW3_Input(TSW3)
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	SW3_Input(void)
{
	uint8_t	portbuf;

	portbuf = API_PORT_BitIn(PORT_D2);			/* Read SW */

	if (portbuf == g_sw3_data_buf){				/* Same as last data  */
		if (g_sw3_chata_cnt < cCHATACNT3){				/* Stable? */
			if (++g_sw3_chata_cnt >= cCHATACNT3){		/* Stable? */
				g_sw3_data = g_sw3_data_buf;		/* Settled */
				g_sw3_flg = 1;
			}
		}
	} else {
		g_sw3_data_buf = portbuf;					/* update "last data" */
		g_sw3_chata_cnt = 0;							/* reset chattering counter */
	}

}

/****************************************************************************************
 * Module   : Led_Data_Write
 *---------------------------------------------------------------------------------------
 * Function : Led_Data_Write
 * Input    : uint8_t data
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	Led_Data_Write(uint8_t data)
{
	volatile PORTM *port;

#ifdef PORT_REFRESH
	port_data[PORT_A] = data;
	port = &PORT.cnl[PORT_A];
	port->IO_Px = port_data[PORT_A];
#else
	port = &PORT.cnl[PORT_A];
	port->IO_Px = data;
#endif

}

/****************************************************************************************
 * Module   : Led_Digit_Write
 *---------------------------------------------------------------------------------------
 * Function : Led_Digit_Write
 * Input    : uint8_t data
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	Led_Digit_Write(uint8_t data)
{
	volatile PORTM *port;

#ifdef PORT_REFRESH
	port_data[PORT_G] = data;
	port = &PORT.cnl[PORT_G];
	port->IO_Px = port_data[PORT_G];
#else
	port = &PORT.cnl[PORT_G];
	port->IO_Px = data;
#endif

}

/****************************************************************************************
 * Module   : Timer4_Start
 *---------------------------------------------------------------------------------------
 * Function : Initialize & Start TMBR4
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	Timer4_Start(void)
{

	/* INTTB4 10msé¸ä˙äÑçûÇ›ê›íË */
	API_TMRB_Init(TMRB_4);									/* Initialize,TBEn=1 */
	
	API_TMRB_CRSet(TMRB_4, BIT8(0,0,0,0,0,0,0,0));

	API_TMRB_ModSet(TMRB_4, BIT8(0,0,1,0,0,1,1,1));			/* Clear enable / clk=É”T16(0.8us@40MHz)) */
	API_TMRB_IntMaskSet(TMRB_4, BIT8(0,0,0,0,0,1,0,1));		/* TBIMOF=1, TBIM1=0, TBIM0=1 */
	API_TMRB_REG1_Write(TMRB_4, 12500);						/* 12500*0.8us = 10ms */

	API_INT_PR_Set(EXT_INTTB41,0x80);						/* Interrupt priority level set */
	API_INT_SER_Set(EXT_INTTB41);							/* enable INTTB41 */
	
	API_TMRB_RunSet(TMRB_4, BIT8(0,0,0,0,0,1,0,1));			/* Start Timer */

}

/****************************************************************************************
 * Module   : Timer4_Stop
 *---------------------------------------------------------------------------------------
 * Function : Stop TMBR4
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void	Timer4_Stop(void)
{

	API_TMRB_Run(TMRB_4, TMRB_STOP);			/* TMBR4 Timer Stop */
	API_INT_PR_Set(EXT_INTTB41,0x00);			/* Clear interrupt priority level */
	API_INT_CER_Set(EXT_INTTB41);				/* Disable INTTB41 */

}

/*********************************** END OF FILE ******************************/
