/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : cstartup_M.c
 *    Description : Toshiba TMPM440 interrupt vector entry table
 *
 *    History :
 *    1. Date        : 7.2013
 *       Author      : Santosh Pawar
 *       Description : initial revision
 *
 **************************************************************************/

#pragma section=".intvec"

extern void __iar_program_start( void );

__weak void Default_Handler( void ) {  }

// Processor specific Interrupt handlers
__weak void NMI_Handler( void ) { Default_Handler(); }
__weak void HardFault_Handler( void ) { Default_Handler(); }
__weak void MemManage_Handler( void ) { Default_Handler(); }
__weak void BusFault_Handler( void ) { Default_Handler(); }
__weak void UsageFault_Handler( void ) { Default_Handler(); }
__weak void SVC_Handler( void ) { Default_Handler(); }
__weak void DebugMon_Handler( void ) { Default_Handler(); }
__weak void PendSV_Handler( void ) { Default_Handler(); }
__weak void SysTick_Handler( void ) { Default_Handler(); }


// Device specific Interrupt handlers
__weak void INT_0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_2_IRQHandler( void ) { Default_Handler(); }
__weak void INT_3_IRQHandler( void ) { Default_Handler(); }
__weak void INT_4_IRQHandler( void ) { Default_Handler(); }
__weak void INT_5_IRQHandler( void ) { Default_Handler(); }
__weak void INT_6_IRQHandler( void ) { Default_Handler(); }
__weak void INT_7_IRQHandler( void ) { Default_Handler(); }
__weak void INT_8_IRQHandler( void ) { Default_Handler(); }
__weak void INT_9_IRQHandler( void ) { Default_Handler(); }
__weak void INT_A_IRQHandler( void ) { Default_Handler(); }
__weak void INT_B_IRQHandler( void ) { Default_Handler(); }
__weak void INT_C_IRQHandler( void ) { Default_Handler(); }
__weak void INT_D_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E_IRQHandler( void ) { Default_Handler(); }
__weak void INT_F_IRQHandler( void ) { Default_Handler(); }
__weak void INT_10_IRQHandler( void ) { Default_Handler(); }
__weak void INT_11_IRQHandler( void ) { Default_Handler(); }
__weak void INT_12_IRQHandler( void ) { Default_Handler(); }
__weak void INT_13_IRQHandler( void ) { Default_Handler(); }
__weak void INT_14_IRQHandler( void ) { Default_Handler(); }
__weak void INT_15_IRQHandler( void ) { Default_Handler(); }
__weak void INT_KWUP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_KWUP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_KSCAN_IRQHandler( void ) { Default_Handler(); }
__weak void INT_RTC_IRQHandler( void ) { Default_Handler(); }
__weak void INT_16_IRQHandler( void ) { Default_Handler(); }
__weak void INT_17_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PSCSTOP_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PSCBRK_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PSCSTEP_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PSCII_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PSCIA_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E0RX_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E0TX_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E0ERR_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E1RX_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E1TX_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E1ERR_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E2RX_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E2TX_IRQHandler( void ) { Default_Handler(); }
__weak void INT_E2ERR_IRQHandler( void ) { Default_Handler(); }
__weak void INT_RX0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TX0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_RX1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TX1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_RX2_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TX2_IRQHandler( void ) { Default_Handler(); }
__weak void INT_RX3_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TX3_IRQHandler( void ) { Default_Handler(); }
__weak void INT_RX4_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TX4_IRQHandler( void ) { Default_Handler(); }
__weak void INT_RX5_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TX5_IRQHandler( void ) { Default_Handler(); }
__weak void INT_UART0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_UART1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_I2C_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADA_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADB_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADC_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB00_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB01_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB02_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB03_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB04_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB05_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB06_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB07_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB08_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB09_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB10_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB11_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB12_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB13_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB14_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB15_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB16_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB17_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB18_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB19_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCMP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCMP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCMP2_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCMP3_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCMP4_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCMP5_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCMP6_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCMP7_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCAP2_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCCAP3_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHC00_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHC01_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHC0EVRY_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHC10_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHC11_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHC1EVRY_IRQHandler( void ) { Default_Handler(); }
__weak void INT_EPHC_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHCPOVF_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHCPPHE_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHCPCY0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHCPCY1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHCPCY2_IRQHandler( void ) { Default_Handler(); }
__weak void INT_PHCPCY3_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD0CMP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD0CMP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD0CMP2_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD0CMP3_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD0CMP4_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD1CMP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD1CMP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD1CMP2_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD1CMP3_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TD1CMP4_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADAHP_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADBHP_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADCHP_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB07CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB07CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB08CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB08CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB09CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB09CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB10CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB10CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB11CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB11CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB12CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB12CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB13CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB13CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB14CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB14CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB15CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB15CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB16CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB16CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB17CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB17CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB18CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB18CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB19CAP0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TB19CAP1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADAM0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADAM1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADBM0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADBM1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADCM0_IRQHandler( void ) { Default_Handler(); }
__weak void INT_ADCM1_IRQHandler( void ) { Default_Handler(); }
__weak void INT_DMACATC_IRQHandler( void ) { Default_Handler(); }
__weak void INT_DMACAERR_IRQHandler( void ) { Default_Handler(); }
__weak void INT_DMACBTC_IRQHandler( void ) { Default_Handler(); }
__weak void INT_DMACBERR_IRQHandler( void ) { Default_Handler(); }
__weak void INT_DMACCTC_IRQHandler( void ) { Default_Handler(); }
__weak void INT_DMACCERR_IRQHandler( void ) { Default_Handler(); }
__weak void INT_TCTBT_IRQHandler( void ) { Default_Handler(); }




typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

// Vector Table Setup
#pragma location = ".intvec"
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
  INT_0_IRQHandler,			/* External Interrupt 0 		*/
  INT_1_IRQHandler,			/* External Interrupt 1 		*/
  INT_2_IRQHandler,			/* External Interrupt 2 		*/
  INT_3_IRQHandler,			/* External Interrupt 3 		*/
  INT_4_IRQHandler,			/* External Interrupt 4 		*/
  INT_5_IRQHandler,			/* External Interrupt 5 		*/
  INT_6_IRQHandler,			/* External Interrupt 6 		*/
  INT_7_IRQHandler,			/* External Interrupt 7 		*/
  INT_8_IRQHandler,			/* External Interrupt 8 		*/
  INT_9_IRQHandler,			/* External Interrupt 9 		*/
  INT_A_IRQHandler,			/* External Interrupt 10		*/
  INT_B_IRQHandler,			/* External Interrupt 11		*/
  INT_C_IRQHandler,			/* External Interrupt 12		*/
  INT_D_IRQHandler,			/* External Interrupt 13		*/
  INT_E_IRQHandler,			/* External Interrupt 14		*/
  INT_F_IRQHandler,			/* External Interrupt 15		*/
  INT_10_IRQHandler,			/* External Interrupt 16		*/
  INT_11_IRQHandler,			/* External Interrupt 17		*/
  INT_12_IRQHandler,			/* External Interrupt 18		*/
  INT_13_IRQHandler,			/* External Interrupt 19		*/
  INT_14_IRQHandler,			/* External Interrupt 20		*/
  INT_15_IRQHandler,			/* External Interrupt 21		*/
  INT_KWUP0_IRQHandler,
  INT_KWUP1_IRQHandler,
  INT_KSCAN_IRQHandler,
  INT_RTC_IRQHandler,
  INT_16_IRQHandler,			/* External Interrupt 22		*/
  INT_17_IRQHandler,			/* External Interrupt 23		*/
  INT_PSCSTOP_IRQHandler,
  INT_PSCBRK_IRQHandler,
  INT_PSCSTEP_IRQHandler,
  INT_PSCII_IRQHandler,
  INT_PSCIA_IRQHandler,
  INT_E0RX_IRQHandler,
  INT_E0TX_IRQHandler,
  INT_E0ERR_IRQHandler,
  INT_E1RX_IRQHandler,
  INT_E1TX_IRQHandler,
  INT_E1ERR_IRQHandler,
  INT_E2RX_IRQHandler,
  INT_E2TX_IRQHandler,
  INT_E2ERR_IRQHandler,
  INT_RX0_IRQHandler,
  INT_TX0_IRQHandler,
  INT_RX1_IRQHandler,
  INT_TX1_IRQHandler,
  INT_RX2_IRQHandler,
  INT_TX2_IRQHandler,
  INT_RX3_IRQHandler,
  INT_TX3_IRQHandler,
  INT_RX4_IRQHandler,
  INT_TX4_IRQHandler,
  INT_RX5_IRQHandler,
  INT_TX5_IRQHandler,
  INT_UART0_IRQHandler,
  INT_UART1_IRQHandler,
  INT_I2C_IRQHandler,
  INT_ADA_IRQHandler,
  INT_ADB_IRQHandler,
  INT_ADC_IRQHandler,
  INT_TB00_IRQHandler,
  INT_TB01_IRQHandler,
  INT_TB02_IRQHandler,
  INT_TB03_IRQHandler,
  INT_TB04_IRQHandler,
  INT_TB05_IRQHandler,
  INT_TB06_IRQHandler,
  INT_TB07_IRQHandler,
  INT_TB08_IRQHandler,
  INT_TB09_IRQHandler,
  INT_TB10_IRQHandler,
  INT_TB11_IRQHandler,
  INT_TB12_IRQHandler,
  INT_TB13_IRQHandler,
  INT_TB14_IRQHandler,
  INT_TB15_IRQHandler,
  INT_TB16_IRQHandler,
  INT_TB17_IRQHandler,
  INT_TB18_IRQHandler,
  INT_TB19_IRQHandler,
  INT_TCCMP0_IRQHandler,
  INT_TCCMP1_IRQHandler,
  INT_TCCMP2_IRQHandler,
  INT_TCCMP3_IRQHandler,
  INT_TCCMP4_IRQHandler,
  INT_TCCMP5_IRQHandler,
  INT_TCCMP6_IRQHandler,
  INT_TCCMP7_IRQHandler,
  INT_TCCAP0_IRQHandler,
  INT_TCCAP1_IRQHandler,
  INT_TCCAP2_IRQHandler,
  INT_TCCAP3_IRQHandler,
  INT_PHC00_IRQHandler,
  INT_PHC01_IRQHandler,
  INT_PHC0EVRY_IRQHandler,
  INT_PHC10_IRQHandler,
  INT_PHC11_IRQHandler,
  INT_PHC1EVRY_IRQHandler,
  INT_EPHC_IRQHandler,
  INT_PHCPOVF_IRQHandler,
  INT_PHCPPHE_IRQHandler,
  INT_PHCPCY0_IRQHandler,
  INT_PHCPCY1_IRQHandler,
  INT_PHCPCY2_IRQHandler,
  INT_PHCPCY3_IRQHandler,
  INT_TD0CMP0_IRQHandler,
  INT_TD0CMP1_IRQHandler,
  INT_TD0CMP2_IRQHandler,
  INT_TD0CMP3_IRQHandler,
  INT_TD0CMP4_IRQHandler,
  INT_TD1CMP0_IRQHandler,
  INT_TD1CMP1_IRQHandler,
  INT_TD1CMP2_IRQHandler,
  INT_TD1CMP3_IRQHandler,
  INT_TD1CMP4_IRQHandler,
  INT_ADAHP_IRQHandler,
  INT_ADBHP_IRQHandler,
  INT_ADCHP_IRQHandler,
  INT_TB07CAP0_IRQHandler,
  INT_TB07CAP1_IRQHandler,
  INT_TB08CAP0_IRQHandler,
  INT_TB08CAP1_IRQHandler,
  INT_TB09CAP0_IRQHandler,
  INT_TB09CAP1_IRQHandler,
  INT_TB10CAP0_IRQHandler,
  INT_TB10CAP1_IRQHandler,
  INT_TB11CAP0_IRQHandler,
  INT_TB11CAP1_IRQHandler,
  INT_TB12CAP0_IRQHandler,
  INT_TB12CAP1_IRQHandler,
  INT_TB13CAP0_IRQHandler,
  INT_TB13CAP1_IRQHandler,
  INT_TB14CAP0_IRQHandler,
  INT_TB14CAP1_IRQHandler,
  INT_TB15CAP0_IRQHandler,
  INT_TB15CAP1_IRQHandler,
  INT_TB16CAP0_IRQHandler,
  INT_TB16CAP1_IRQHandler,
  INT_TB17CAP0_IRQHandler,
  INT_TB17CAP1_IRQHandler,
  INT_TB18CAP0_IRQHandler,
  INT_TB18CAP1_IRQHandler,
  INT_TB19CAP0_IRQHandler,
  INT_TB19CAP1_IRQHandler,
  INT_ADAM0_IRQHandler,
  INT_ADAM1_IRQHandler,
  INT_ADBM0_IRQHandler,
  INT_ADBM1_IRQHandler,
  INT_ADCM0_IRQHandler,
  INT_ADCM1_IRQHandler,
  INT_DMACATC_IRQHandler,
  INT_DMACAERR_IRQHandler,
  INT_DMACBTC_IRQHandler,
  INT_DMACBERR_IRQHandler,
  INT_DMACCTC_IRQHandler,
  INT_DMACCERR_IRQHandler,
  INT_TCTBT_IRQHandler,
};

