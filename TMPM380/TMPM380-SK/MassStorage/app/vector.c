/********************************************************************************/
/* Notice																		*/
/********************************************************************************/
/*   The information contained herein has been carefully checked 				*/
/* and is believed to be reliable. However, no responsibility can be 			*/
/* assumed for inaccuracies that may not have been detected. The 				*/
/* information contained herein is subject to change without notice.			*/
/*   The information contained herein is presented only as a guide 				*/
/* for the application of our products. No responsibility is assumed 			*/
/* by TOSHIBA for any infringements of patents or other rights of 				*/
/* the third parties which may result from its use. No license is 				*/
/* granted by implication or otherwise under any patent or patent 				*/
/* rights of TOSHIBA or others.													*/
/* 																				*/
/********************************************************************************/
/* 	Copyright(C) TOSHIBA CORPORATION 2009 All rights reserved					*/
/********************************************************************************/
/*******************************************************************************
* File Name          : vector.c
* Version            : V1.0
* Date				 : 2010/01/XX
* Description        : TMPM380 vector table
*******************************************************************************/

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma segment="CSTACK"


void __iar_program_start(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void INT0_Handler(void);
void INT1_Handler(void);
void INT2_Handler(void);
void INT3_Handler(void);
void INT4_Handler(void);
void INT5_Handler(void);
void INTRX0_Handler(void);
void INTTX0_Handler(void);
void INTRX1_Handler(void);
void INTTX1_Handler(void);
void INTSSP0_Handler(void);
void INTSSP1_Handler(void);
void INTEMG0_Handler(void);
void INTEMG1_Handler(void);
void INTSBI0_Handler(void);
void INTSBI1_Handler(void);
void INTADPD0_Handler(void);
void INTRTC_Handler(void);
void INTADPD1_Handler(void);
void INTRMCRX_Handler(void);
void INTTB00_Handler(void);
void INTTB01_Handler(void);
void INTTB10_Handler(void);
void INTTB11_Handler(void);
void INTTB40_Handler(void);
void INTTB41_Handler(void);
void INTTB50_Handler(void);
void INTTB51_Handler(void);
void INTPMD0_Handler(void);
void INTPMD1_Handler(void);
void INTCAP00_Handler(void);
void INTCAP01_Handler(void);
void INTCAP10_Handler(void);
void INTCAP11_Handler(void);
void INTCAP40_Handler(void);
void INTCAP41_Handler(void);
void INTCAP50_Handler(void);
void INTCAP51_Handler(void);
void INT6_Handler(void);
void INT7_Handler(void);
void INTRX2_Handler(void);
void INTTX2_Handler(void);
void INTADCP0_Handler(void);
void INTADCP1_Handler(void);
void INTRX4_Handler(void);
void INTTX4_Handler(void);
void INTTB20_Handler(void);
void INTTB21_Handler(void);
void INTTB30_Handler(void);
void INTTB31_Handler(void);
void INTCAP20_Handler(void);
void INTCAP21_Handler(void);
void INTCAP30_Handler(void);
void INTCAP31_Handler(void);
void INTADSFT_Handler(void);
void INTADTMR_Handler(void);
void INT8_Handler(void);
void INT9_Handler(void);
void INTA_Handler(void);
void INTB_Handler(void);
void INTENC0_Handler(void);
void INTENC1_Handler(void);
void INTRX3_Handler(void);
void INTTX3_Handler(void);
void INTTB60_Handler(void);
void INTTB61_Handler(void);
void INTTB70_Handler(void);
void INTTB71_Handler(void);
void INTCAP60_Handler(void);
void INTCAP61_Handler(void);
void INTCAP70_Handler(void);
void INTCAP71_Handler(void);
void INTC_Handler(void);
void INTD_Handler(void);
void INTE_Handler(void);
void INTF_Handler(void);
void INTDMACERR_Handler(void);
void INTDMACTC_Handler(void);
void INTMTPTB00_Handler(void);
void INTMTTTB01_Handler(void);
void INTMTPTB10_Handler(void);
void INTMTTTB11_Handler(void);
void INTMTPTB20_Handler(void);
void INTMTTTB21_Handler(void);
void INTMTCAP00_Handler(void);
void INTMTCAP01_Handler(void);
void INTMTCAP10_Handler(void);
void INTMTCAP11_Handler(void);
void INTMTCAP20_Handler(void);
void INTMTCAP21_Handler(void);
void INTMTEMG0_Handler(void);
void INTMTEMG1_Handler(void);
void INTMTEMG2_Handler(void);


#pragma location = ".intvec"


const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_Handler,              /* NMI Handler */
  HardFault_Handler,        /* Hard Fault Handler */
  MemManage_Handler,        /* MPU Fault Handler */
  BusFault_Handler,         /* Bus Fault Handler */ 
  UsageFault_Handler,       /* Usage Fault Handler */
  0, 0, 0, 0,               /* Reserved */ 
  SVC_Handler,              /* SVCall Handler */
  DebugMon_Handler,         /* Debug Monitor Handler */
  0,                        /* Reserved */
  PendSV_Handler,           /* PendSV Handler */
  SysTick_Handler,          /* SysTick Handler */

/* External Interrupts */


INT0_Handler,		/*  0 */ /* Interrupt Pin INT0			              */  
INT1_Handler,		/*  1 */ /* Interrupt Pin INT1                        */
INT2_Handler,		/*  2 */ /* Interrupt Pin INT2                        */
INT3_Handler,		/*  3 */ /* Interrupt Pin INT3                        */
INT4_Handler,		/*  4 */ /* Interrupt Pin INT4                        */
INT5_Handler,		/*  5 */ /* Interrupt Pin INT5                        */
INTRX0_Handler,		/*  6 */ /* Serial Reception (Ch 0)                   */
INTTX0_Handler,		/*  7 */ /* Serial Transmit (Ch 0)                    */
INTRX1_Handler,		/*  8 */ /* Serial Reception (Ch 1)                   */
INTTX1_Handler,		/*  9 */ /* Serial Transmit (Ch 1)                    */
INTSSP0_Handler,	/* 10 */ /* Syncronous Serial Port 0 */
INTSSP1_Handler,	/* 11 */ /* Syncronous Serial Port 1 */
INTEMG0_Handler,	/* 12 */ /* EMG */
INTEMG1_Handler,	/* 13 */ /* EMG */
INTSBI0_Handler,	/* 14 */ /* Serial Bus Interface 0 interrupt */
INTSBI1_Handler,	/* 15 */ /* Serial Bus Interface 1 interrupt */
INTADPD0_Handler,	/* 16 */ /* ADC conversion triggered by PMD0 is finished */
INTRTC_Handler,		/* 17 */ /* Realtime clock interrupt */
INTADPD1_Handler,	/* 18 */ /* ADC conversion triggered by PMD1 is finished */
INTRMCRX_Handler,	/* 19 */ /* Remote Controller reception interrupt */
INTTB00_Handler,	/* 20 */ /* 16bit TMRB Match Detection 00             */
INTTB01_Handler,	/* 21 */ /* 16bit TMRB Match Detection 01             */
INTTB10_Handler,	/* 22 */ /* 16bit TMRB Match Detection 10             */
INTTB11_Handler,	/* 23 */ /* 16bit TMRB Match Detection 11             */
INTTB40_Handler,	/* 24 */ /* 16bit TMRB Match Detection 40             */
INTTB41_Handler,	/* 25 */ /* 16bit TMRB Match Detection 41             */
INTTB50_Handler,	/* 26 */ /* 16bit TMRB Match Detection 50             */
INTTB51_Handler,	/* 27 */ /* 16bit TMRB Match Detection 51             */
INTPMD0_Handler,	/* 28 */ /* PMD0 PWM */
INTPMD1_Handler,	/* 29 */ /* PMD1 PWM */
INTCAP00_Handler,	/* 30 */ /* 16bit TMRB Input Capture 00               */
INTCAP01_Handler,	/* 31 */ /* 16bit TMRB Input Capture 01               */
INTCAP10_Handler,	/* 32 */ /* 16bit TMRB Input Capture 10               */
INTCAP11_Handler,	/* 33 */ /* 16bit TMRB Input Capture 11               */
INTCAP40_Handler,	/* 34 */ /* 16bit TMRB Input Capture 40               */
INTCAP41_Handler,	/* 35 */ /* 16bit TMRB Input Capture 41               */
INTCAP50_Handler,	/* 36 */ /* 16bit TMRB Input Capture 50               */
INTCAP51_Handler,	/* 37 */ /* 16bit TMRB Input Capture 51               */
INT6_Handler,		/* 38 */ /* Interrupt Pin INT6                        */
INT7_Handler,		/* 39 */ /* Interrupt Pin INT7                        */
INTRX2_Handler,		/* 40 */ /* Serial Reception (Ch 2)                   */
INTTX2_Handler,		/* 41 */ /* Serial Transmit (Ch 2)                    */
INTADCP0_Handler,	/* 42 */ /* ADC conversion monitoring function interrupt 0 */
INTADCP1_Handler,	/* 43 */ /* ADC conversion monitoring function interrupt 1 */
INTRX4_Handler,		/* 44 */ /* Serial reception (Ch 4)  */
INTTX4_Handler,		/* 45 */ /* Serial transmit (Ch 4)   */
INTTB20_Handler,	/* 46 */ /* 16bit TMRB Match Detection 20             */
INTTB21_Handler,	/* 47 */ /* 16bit TMRB Match Detection 21             */
INTTB30_Handler,	/* 48 */ /* 16bit TMRB Match Detection 30             */
INTTB31_Handler,	/* 49 */ /* 16bit TMRB Match Detection 31             */
INTCAP20_Handler,	/* 50 */ /* 16bit TMRB Input Capture 20               */
INTCAP21_Handler,	/* 51 */ /* 16bit TMRB Input Capture 21               */
INTCAP30_Handler,	/* 52 */ /* 16bit TMRB Input Capture 30               */
INTCAP31_Handler,	/* 53 */ /* 16bit TMRB Input Capture 31               */
INTADSFT_Handler,	/* 54 */ /* ADC soft start ïœä∑èIóπ */
0,					/* 55 */ /* RESERVED		*/
INTADTMR_Handler,	/* 56 */ /* ADC timerìØä˙ïœä∑èIóπ */
0,					/* 57 */ /* RESERVED		*/
INT8_Handler,		/* 58 */ /* Interrupt Pin INT8                        */
INT9_Handler,		/* 59 */ /* Interrupt Pin INT9                        */
INTA_Handler,		/* 60 */ /* Interrupt Pin INTA                        */
INTB_Handler,		/* 61 */ /* Interrupt Pin INTB                        */
INTENC0_Handler,	/* 62 */ /* Encoder 0 input */
INTENC1_Handler,	/* 63 */ /* Encoder 1 input */
INTRX3_Handler,		/* 64 */ /* Serial Reception (Ch 3)                   */
INTTX3_Handler,		/* 65 */ /* Serial Transmit (Ch 3)                    */
INTTB60_Handler,	/* 66 */ /* 16bit TMRB Match Detection 60             */
INTTB61_Handler,	/* 67 */ /* 16bit TMRB Match Detection 61             */
INTTB70_Handler,	/* 68 */ /* 16bit TMRB Match Detection 70             */
INTTB71_Handler,	/* 69 */ /* 16bit TMRB Match Detection 71             */
INTCAP60_Handler,	/* 70 */ /* 16bit TMRB Input Capture 60               */
INTCAP61_Handler,	/* 71 */ /* 16bit TMRB Input Capture 61               */
INTCAP70_Handler,	/* 72 */ /* 16bit TMRB Input Capture 70               */
INTCAP71_Handler,	/* 73 */ /* 16bit TMRB Input Capture 71               */
INTC_Handler,		/* 74 */ /* Interrupt Pin INT8                        */
INTD_Handler,		/* 75 */ /* Interrupt Pin INT9                        */
INTE_Handler,		/* 76 */ /* Interrupt Pin INTA                        */
INTF_Handler,		/* 77 */ /* Interrupt Pin INTB                        */
INTDMACERR_Handler,	/* 78 */ /* DMA transfer error     */
INTDMACTC_Handler,	/* 79 */ /* DMA end of transfer     */
INTMTPTB00_Handler,	/* 80 */ /* 16-bit MPT0 IGBT period/ compare match detection 0 */
INTMTTTB01_Handler,	/* 81 */ /* 16-bit MPT0 IGBT trigger/ compare match detection 1 */
INTMTPTB10_Handler,	/* 82 */ /* 16-bit MPT1 IGBT period/ compare match detection 0 */
INTMTTTB11_Handler,	/* 83 */ /* 16-bit MPT1 IGBT trigger/ compare match detection 1 */
INTMTPTB20_Handler,	/* 84 */ /* 16-bit MPT2 IGBT period/ compare match detection 0 */
INTMTTTB21_Handler,	/* 85 */ /* 16-bit MPT2 IGBT trigger/ compare match detection 1 */
INTMTCAP00_Handler,	/* 86 */ /* 16-bit MPT0 input capture 0   */
INTMTCAP01_Handler,	/* 87 */ /* 16-bit MPT0 input capture 1   */
INTMTCAP10_Handler,	/* 88 */ /* 16-bit MPT1 input capture 0   */
INTMTCAP11_Handler,	/* 89 */ /* 16-bit MPT1 input capture 1   */
INTMTCAP20_Handler,	/* 80 */ /* 16-bit MPT2 input capture 0   */
INTMTCAP21_Handler,	/* 91 */ /* 16-bit MPT2 input capture 1   */
INTMTEMG0_Handler,		/* 92 */ /* 16-bit MPT0 IGBT EMG interrupt */
INTMTEMG1_Handler,		/* 93 */ /* 16-bit MPT1 IGBT EMG interrupt */
INTMTEMG2_Handler		/* 94 */ /* 16-bit MPT2 IGBT EMG interrupt */

};

/*************************** END OF FILE **************************************/
