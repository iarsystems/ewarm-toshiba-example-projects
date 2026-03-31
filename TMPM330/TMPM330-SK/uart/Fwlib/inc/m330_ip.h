/*******************************************************************************
* File Name 		 : m330_sfr.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SFR define
********************************************************************************/

/* avoid double definition */
#ifndef __M330_IP_H
#define __M330_IP_H


#ifndef EXTERN
#define EXTERN extern
#endif

#include "m330_conf.h"



/* Exported types ------------------------------------------------------------*/
/******************************************************************************/
/*						   SFR define										  */
/******************************************************************************/

/*------------------------ PORTx -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_Px;
			u_int8						RESERVE1;
			u_int16						RESERVE2;
	volatile IO_SFR8_u		IO_PxCR;
			u_int8						RESERVE3;
			u_int16						RESERVE4;
	volatile IO_SFR8_u		IO_PxFR1;
			u_int8						RESERVE5;
			u_int16						RESERVE6;
	volatile IO_SFR8_u		IO_PxFR2;
			u_int8						RESERVE7;
			u_int16						RESERVE8;

			u_int32						RESERVE_1[6];
	volatile IO_SFR8_u		IO_PxOD;
			u_int8						RESERVE9;
			u_int16						RESERVE10;
	volatile IO_SFR8_u		IO_PxPUP;
			u_int8						RESERVE11;
			u_int16						RESERVE12;
	volatile IO_SFR8_u		IO_PxPDN;
			u_int8						RESERVE13;
			u_int16						RESERVE14;

			u_int32						RESERVE_7;
	volatile IO_SFR8_u		IO_PxIE;
			u_int8						RESERVE15;
			u_int16						RESERVE16;

			u_int32						RESERVE_2;
} SFR_PORTx_t;


/*------------------------ TMRBx -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_TBxEN;
			u_int8						RESERVE0;
			u_int16						RESERVE1;
	volatile IO_SFR8_u		IO_TBxRUN;
			u_int8						RESERVE2;
			u_int16						RESERVE3;
	volatile IO_SFR8_u		IO_TBxCR;
			u_int8						RESERVE4;
			u_int16						RESERVE5;
	volatile IO_SFR8_u		IO_TBxMOD;
			u_int8						RESERVE6;
			u_int16						RESERVE7;
	volatile IO_SFR8_u		IO_TBxFFCR;
			u_int8						RESERVE8;
			u_int16						RESERVE9;
	volatile IO_SFR8_u		IO_TBxST;
			u_int8						RESERVE10;
			u_int16						RESERVE11;
	volatile IO_SFR8_u		IO_TBxIM;
			u_int8						RESERVE12;
			u_int16						RESERVE13;
	volatile IO_SFR16_u		IO_TBxUC0;
			u_int16						RESERVE14;
	volatile IO_SFR16_u		IO_TBxRG0;
			u_int16						RESERVE15;
	volatile IO_SFR16_u		IO_TBxRG1;
			u_int16						RESERVE16;
	volatile IO_SFR16_u		IO_TBxCP0;
			u_int16						RESERVE17;
	volatile IO_SFR16_u		IO_TBxCP1;
			u_int16						RESERVE18;
} SFR_TMRBx_t;


/*------------------------ SBIx -----------------------*/
typedef struct {

	volatile IO_SFR8_u		IO_SBIxCR0;
			u_int8						RESERVE0;
			u_int16						RESERVE1;
	volatile IO_SFR8_u		IO_SBIxCR1;
			u_int8						RESERVE2;
			u_int16						RESERVE3;
	volatile IO_SFR8_u		IO_SBIxDBR;
			u_int8						RESERVE4;
			u_int16						RESERVE5;
	volatile IO_SFR8_u		IO_SBIxI2CAR;
			u_int8						RESERVE6;
			u_int16						RESERVE7;
	volatile IO_SFR8_u		IO_SBIxCR2;
			u_int8						RESERVE8;
			u_int16						RESERVE9;
//	SBIxSR = SBIxCR2 read (address common)
//		volatile IO_SFR8_u		IO_SBIxSR;
//				u_int8						RESERVE10;
//				u_int16						RESERVE11;
	volatile IO_SFR8_u		IO_SBIxBR0;
			u_int8						RESERVE12;
			u_int16						RESERVE13;
} SFR_SBIx_t;

#define IO_SBIxSR	IO_SBIxCR2


/*------------------------ SIOx -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_SCxEN;
			u_int8						RESERVE0;
			u_int16						RESERVE1;
	volatile IO_SFR8_u		IO_SCxBUF;
			u_int8						RESERVE2;
			u_int16						RESERVE3;
	volatile IO_SFR8_u		IO_SCxCR;
			u_int8						RESERVE4;
			u_int16						RESERVE5;
	volatile IO_SFR8_u		IO_SCxMOD0;
			u_int8						RESERVE6;
			u_int16						RESERVE7;
	volatile IO_SFR8_u		IO_SCxBRCR;
			u_int8						RESERVE8;
			u_int16						RESERVE9;
	volatile IO_SFR8_u		IO_SCxBRADD;
			u_int8						RESERVE10;
			u_int16						RESERVE11;
	volatile IO_SFR8_u		IO_SCxMOD1;
			u_int8						RESERVE12;
			u_int16						RESERVE13;
	volatile IO_SFR8_u		IO_SCxMOD2;
			u_int8						RESERVE14;
			u_int16						RESERVE15;
	volatile IO_SFR8_u		IO_SCxRFC;
			u_int8						RESERVE16;
			u_int16						RESERVE17;
	volatile IO_SFR8_u		IO_SCxTFC;
			u_int8						RESERVE18;
			u_int16						RESERVE19;
	volatile IO_SFR8_u		IO_SCxRST;
			u_int8						RESERVE20;
			u_int16						RESERVE21;
	volatile IO_SFR8_u		IO_SCxTST;
			u_int8						RESERVE22;
			u_int16						RESERVE23;
	volatile IO_SFR8_u		IO_SCxFCNF;
			u_int8						RESERVE24;
			u_int16						RESERVE25;
} SFR_SIOx_t;


/*------------------------ ADC -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_ADCLK;
			u_int8						RESERVE0;
			u_int16						RESERVE1;
	volatile IO_SFR8_u		IO_ADMOD0;
			u_int8						RESERVE2;
			u_int16						RESERVE3;
	volatile IO_SFR8_u		IO_ADMOD1;
			u_int8						RESERVE4;
			u_int16						RESERVE5;
	volatile IO_SFR8_u		IO_ADMOD2;
			u_int8						RESERVE6;
			u_int16						RESERVE7;
	volatile IO_SFR8_u		IO_ADMOD3;
			u_int8						RESERVE8;
			u_int16						RESERVE9;
	volatile IO_SFR8_u		IO_ADMOD4;
			u_int8						RESERVE10;
			u_int16						RESERVE11;
	volatile IO_SFR8_u		IO_ADMOD5;
			u_int8						RESERVE12;
			u_int16						RESERVE13;

			u_int32						RESERVE_1[5];

	volatile IO_SFR16_u		IO_ADREG08;
			u_int16						RESERVE14;
	volatile IO_SFR16_u		IO_ADREG19;
			u_int16						RESERVE15;
	volatile IO_SFR16_u		IO_ADREG2A;
			u_int16						RESERVE16;
	volatile IO_SFR16_u		IO_ADREG3B;
			u_int16						RESERVE17;
	volatile IO_SFR16_u		IO_ADREG4C;
			u_int16						RESERVE18;
	volatile IO_SFR16_u		IO_ADREG5D;
			u_int16						RESERVE19;
	volatile IO_SFR16_u		IO_ADREG6E;
			u_int16						RESERVE20;
	volatile IO_SFR16_u		IO_ADREG7F;
			u_int16						RESERVE21;
	volatile IO_SFR16_u		IO_ADREGSP;
			u_int16						RESERVE22;
	volatile IO_SFR16_u		IO_ADCMPREG0;
			u_int16						RESERVE23;
	volatile IO_SFR16_u		IO_ADCMPREG1;
			u_int16						RESERVE24;
} SFR_ADC_t;

/*------------------------ WDT -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_WDMOD;
			u_int8						RESERVE1;
			u_int16						RESERVE2;
	volatile IO_SFR8_u		IO_WDCR;
			u_int8						RESERVE3;
			u_int16						RESERVE4;
} SFR_WDT_t;


/*------------------------ RTC -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_SECR;
	volatile IO_SFR8_u		IO_MINR;
	volatile IO_SFR8_u		IO_HOURR;
			u_int8						RESERVE1;
	volatile IO_SFR8_u		IO_DAYR;
	volatile IO_SFR8_u		IO_DATER;
	volatile IO_SFR8_u		IO_MONTHR;
	volatile IO_SFR8_u		IO_YEARR;
	volatile IO_SFR8_u		IO_PAGER;
			u_int8						RESERVE2;
			u_int16						RESERVE3;
	volatile IO_SFR8_u		IO_RESTR;
			u_int8						RESERVE4;
			u_int16						RESERVE5;
} SFR_RTC_t;


/*------------------------ CG -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_SYSCR0;
	volatile IO_SFR8_u		IO_SYSCR1;
	volatile IO_SFR8_u		IO_SYSCR2;
			u_int8						RESERVE1;
	volatile IO_SFR8_u		IO_OSCCR0;
	volatile IO_SFR8_u		IO_OSCCR1;
			u_int16						RESERVE2;
	volatile IO_SFR8_u		IO_STBYCR0;
	volatile IO_SFR8_u		IO_STBYCR1;
	volatile IO_SFR8_u		IO_STBYCR2;
			u_int8						RESERVE3;
	volatile IO_SFR8_u		IO_PLLSEL;
			u_int8						RESERVE4;
			u_int16						RESERVE5;

	volatile IO_SFR8_u		IO_CKSEL;
			u_int8						RESERVE6;
			u_int16						RESERVE7;
	volatile IO_SFR8_u		IO_ICRCG;
			u_int8						RESERVE8;
			u_int16						RESERVE9;
	volatile IO_SFR8_u		IO_NMIFLG;
			u_int8						RESERVE10;
			u_int16						RESERVE11;
	volatile IO_SFR8_u		IO_RSTFLG;
			u_int8						RESERVE12;
			u_int16						RESERVE13;
	volatile IO_SFR32_u		IO_IMCGA;
	volatile IO_SFR32_u		IO_IMCGB;
	volatile IO_SFR32_u		IO_IMCGC;
	volatile IO_SFR8_u		IO_IMCGD;
			u_int8						RESERVE14;
			u_int16						RESERVE15;
} SFR_CG_t;


/*------------------------ CEC -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_CECEN;
			u_int8						RESERVE0;
			u_int16						RESERVE1;
	volatile IO_SFR16_u		IO_CECADD;
			u_int16						RESERVE2;
	volatile IO_SFR8_u		IO_CECRESET;
			u_int8						RESERVE3;
			u_int16						RESERVE4;
	volatile IO_SFR8_u		IO_CECREN;
			u_int8						RESERVE5;
			u_int16						RESERVE6;
	volatile IO_SFR16_u		IO_CECRBUF;
			u_int16						RESERVE7;
	volatile IO_SFR32_u		IO_CECRCR1;
	volatile IO_SFR16_u		IO_CECRCR2;
			u_int16						RESERVE8;
	volatile IO_SFR32_u		IO_CECRCR3;
	volatile IO_SFR8_u		IO_CECTEN;
			u_int8						RESERVE9;
			u_int16						RESERVE10;
	volatile IO_SFR16_u		IO_CECTBUF;
			u_int16						RESERVE11;
	volatile IO_SFR32_u		IO_CECTCR;
	volatile IO_SFR8_u		IO_CECRSTAT;
			u_int8						RESERVE12;
			u_int16						RESERVE13;
	volatile IO_SFR8_u		IO_CECTSTAT;
			u_int8						RESERVE14;
			u_int16						RESERVE15;
} SFR_CEC_t;


/*------------------------ RMCx -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_RMCxEN;
			u_int8						RESERVE0;
			u_int16						RESERVE1;
	volatile IO_SFR8_u		IO_RMCxREN;
			u_int8						RESERVE2;
			u_int16						RESERVE3;
	volatile IO_SFR32_u		IO_RMCxRBUF1;
	volatile IO_SFR32_u		IO_RMCxRBUF2;
	volatile IO_SFR8_u		IO_RMCxRBUF3;
			u_int8						RESERVE4;
			u_int16						RESERVE5;
	volatile IO_SFR32_u		IO_RMCxRCR1;
	volatile IO_SFR32_u		IO_RMCxRCR2;
	volatile IO_SFR16_u		IO_RMCxRCR3;
			u_int16						RESERVE6;
	volatile IO_SFR8_u		IO_RMCxRCR4;
			u_int8						RESERVE7;
			u_int16						RESERVE8;
	volatile IO_SFR16_u		IO_RMCxRSTAT;
			u_int16						RESERVE9;
} SFR_RMCx_t;


/*------------------------ FLASH -----------------------*/
typedef struct {
	volatile IO_SFR8_u		IO_SECBIT;
			u_int8						RESERVE0;
			u_int16						RESERVE1;

			u_int32						RESERVE_1[7];

	volatile IO_SFR32_u		IO_FLCS;
} SFR_FLASH_t;


/*------------------------ NVIC -----------------------*/

	/*	ICTR	*/
typedef struct {
	volatile IO_SFR32_u		IO_ICTR_ICTR;			/* Interrupt Control Type Register */
} SFR_ICTR_t;

	/*	SysTick	*/
typedef struct {
	volatile IO_SFR32_u		IO_NVIC_CTL;
	volatile IO_SFR32_u		IO_NVIC_RVR;
	volatile IO_SFR32_u		IO_NVIC_CVR;
	volatile IO_SFR32_u		IO_NVIC_CAL;
} SFR_SYSTICK_t;


typedef struct {
	volatile IO_SFR32_u		IO_NVIC_ISER00_31;		/* Set-Enable Reg Irq0Å`31			*/
	volatile IO_SFR32_u		IO_NVIC_ISER32_63;		/* Set-Enable Reg Irq32Å`63			*/
	volatile IO_SFR32_u		IO_NVIC_ISER64_95;		/* Set-Enable Reg Irq64Å`95			*/
	volatile IO_SFR32_u		IO_NVIC_ISER96_127;		/* Set-Enable Reg Irq96Å`127		*/
	volatile IO_SFR32_u		IO_NVIC_ISER128_159;	/* Set-Enable Reg Irq128Å`159		*/
	volatile IO_SFR32_u		IO_NVIC_ISER160_191;	/* Set-Enable Reg Irq160Å`191		*/
	volatile IO_SFR32_u		IO_NVIC_ISER192_223;	/* Set-Enable Reg Irq192Å`223		*/
	volatile IO_SFR32_u		IO_NVIC_ISER224_239;	/* Set-Enable Reg Irq224Å`239		*/

			u_int8						RESERVE1[96];

	volatile IO_SFR32_u		IO_NVIC_ICER00_31;		/* Clear-Enable Reg Irq0Å`31		*/
	volatile IO_SFR32_u		IO_NVIC_ICER32_63;		/* Clear-Enable Reg Irq32Å`63		*/
	volatile IO_SFR32_u		IO_NVIC_ICER64_95;		/* Clear-Enable Reg Irq64Å`95		*/
	volatile IO_SFR32_u		IO_NVIC_ICER96_127;		/* Clear-Enable Reg Irq96Å`127		*/
	volatile IO_SFR32_u		IO_NVIC_ICER128_159;	/* Clear-Enable Reg Irq128Å`159		*/
	volatile IO_SFR32_u		IO_NVIC_ICER160_191;	/* Clear-Enable Reg Irq160Å`191		*/
	volatile IO_SFR32_u		IO_NVIC_ICER192_223;	/* Clear-Enable Reg Irq192Å`223		*/
	volatile IO_SFR32_u		IO_NVIC_ICER224_239;	/* Clear-Enable Reg Irq224Å`239		*/

			u_int8						RESERVE2[96];

	volatile IO_SFR32_u		IO_NVIC_ISPR00_31;		/* Set-Pending Reg Irq0Å`31			*/
	volatile IO_SFR32_u		IO_NVIC_ISPR32_63;		/* Set-Pending Reg Irq32Å`63		*/
	volatile IO_SFR32_u		IO_NVIC_ISPR64_95;		/* Set-Pending Reg Irq64Å`95		*/
	volatile IO_SFR32_u		IO_NVIC_ISPR96_127;		/* Set-Pending Reg Irq96Å`127		*/
	volatile IO_SFR32_u		IO_NVIC_ISPR128_159;	/* Set-Pending Reg Irq128Å`159		*/
	volatile IO_SFR32_u		IO_NVIC_ISPR160_191;	/* Set-Pending Reg Irq160Å`191		*/
	volatile IO_SFR32_u		IO_NVIC_ISPR192_223;	/* Set-Pending Reg Irq192Å`223		*/
	volatile IO_SFR32_u		IO_NVIC_ISPR224_239;	/* Set-Pending Reg Irq224Å`239		*/

			u_int8						RESERVE3[96];

	volatile IO_SFR32_u		IO_NVIC_ICPR00_31;		/* Clear-Pending Reg Irq0Å`31		*/
	volatile IO_SFR32_u		IO_NVIC_ICPR32_63;		/* Clear-Pending Reg Irq32Å`63		*/
	volatile IO_SFR32_u		IO_NVIC_ICPR64_95;		/* Clear-Pending Reg Irq64Å`95		*/
	volatile IO_SFR32_u		IO_NVIC_ICPR96_127;		/* Clear-Pending Reg Irq96Å`127		*/
	volatile IO_SFR32_u		IO_NVIC_ICPR128_159;	/* Clear-Pending Reg Irq128Å`159	*/
	volatile IO_SFR32_u		IO_NVIC_ICPR160_191;	/* Clear-Pending Reg Irq160Å`191	*/
	volatile IO_SFR32_u		IO_NVIC_ICPR192_223;	/* Clear-Pending Reg Irq192Å`223	*/
	volatile IO_SFR32_u		IO_NVIC_ICPR224_239;	/* Clear-Pending Reg Irq224Å`239	*/

			u_int8						RESERVE4[96];

	volatile IO_SFR32_u		IO_NVIC_ABR00_31;		/* Active-Bit Reg Irq0Å`31		*/
	volatile IO_SFR32_u		IO_NVIC_ABR32_63;		/* Active-Bit Reg Irq32Å`63		*/
	volatile IO_SFR32_u		IO_NVIC_ABR64_95;		/* Active-Bit Reg Irq64Å`95		*/
	volatile IO_SFR32_u		IO_NVIC_ABR96_127;		/* Active-Bit Reg Irq96Å`127		*/
	volatile IO_SFR32_u		IO_NVIC_ABR128_159;		/* Active-Bit Reg Irq128Å`159	*/
	volatile IO_SFR32_u		IO_NVIC_ABR160_191;		/* Active-Bit Reg Irq160Å`191	*/
	volatile IO_SFR32_u		IO_NVIC_ABR192_223;		/* Active-Bit Reg Irq192Å`223	*/
	volatile IO_SFR32_u		IO_NVIC_ABR224_239;		/* Active-Bit Reg Irq224Å`239	*/

			u_int8						RESERVE5[224];

	volatile IO_SFR8_u		IO_NVIC_INTPR[240];		/* Priority Register Irq0Å`239		*/
} SFR_NVIC_t;

	/*	CPU	*/
typedef struct {
	volatile IO_SFR32_u		IO_CPU_CPUID_BR;		/* CPUID Base register */
	volatile IO_SFR32_u		IO_CPU_ICSR;
	volatile IO_SFR32_u		IO_CPU_VTOR;
	volatile IO_SFR32_u		IO_CPU_AIRCR;
	volatile IO_SFR32_u		IO_CPU_SCR;
	volatile IO_SFR32_u		IO_CPU_CCR;
	volatile IO_SFR32_u		IO_CPU_SHPR4_7;
	volatile IO_SFR32_u		IO_CPU_SHPR8_11;
	volatile IO_SFR32_u		IO_CPU_SHPR12_15;
	volatile IO_SFR32_u		IO_CPU_SHCSR;
	volatile IO_SFR32_u		IO_CPU_CFSR;
	volatile IO_SFR32_u		IO_CPU_HFSR;
	volatile IO_SFR32_u		IO_CPU_DFSR;
	volatile IO_SFR32_u		IO_CPU_MMAR;
	volatile IO_SFR32_u		IO_CPU_BFAR;
	volatile IO_SFR32_u		IO_CPU_AFSR;
	volatile IO_SFR32_u		IO_CPU_PFR0;
	volatile IO_SFR32_u		IO_CPU_PFR1;
	volatile IO_SFR32_u		IO_CPU_AFR0;
	volatile IO_SFR32_u		IO_CPU_MMFR0;
	volatile IO_SFR32_u		IO_CPU_MMFR1;
	volatile IO_SFR32_u		IO_CPU_MMFR2;
	volatile IO_SFR32_u		IO_CPU_MMFR3;
	volatile IO_SFR32_u		IO_CPU_ISAR0;
	volatile IO_SFR32_u		IO_CPU_ISAR1;
	volatile IO_SFR32_u		IO_CPU_ISAR2;
	volatile IO_SFR32_u		IO_CPU_ISAR3;
	volatile IO_SFR32_u		IO_CPU_ISAR4;
} SFR_CPU_t;

	/*	STIR	*/
typedef struct {
	volatile IO_SFR32_u		IO_STIR_BR;		/* Software Trigger Interrupt Register */
} SFR_STIR_t;

	/*	Peripheral	*/
typedef struct {
	volatile IO_SFR32_u		IO_PERIPH_PID4;
	volatile IO_SFR32_u		IO_PERIPH_PID5;
	volatile IO_SFR32_u		IO_PERIPH_PID6;
	volatile IO_SFR32_u		IO_PERIPH_PID7;
	volatile IO_SFR32_u		IO_PERIPH_PID0;
	volatile IO_SFR32_u		IO_PERIPH_PID1;
	volatile IO_SFR32_u		IO_PERIPH_PID2;
	volatile IO_SFR32_u		IO_PERIPH_PID3;
	volatile IO_SFR32_u		IO_PERIPH_CID0;
	volatile IO_SFR32_u		IO_PERIPH_CID1;
	volatile IO_SFR32_u		IO_PERIPH_CID2;
	volatile IO_SFR32_u		IO_PERIPH_CID3;
} SFR_PERIPF_t;



/******************************************************************************/
/*						   SFR base address									  */
/******************************************************************************/
/* SFR base address */
#define SFR_BASE_ADDRESS	((u_int32)0x40000000)

/* SFR address define */
#define SFR_PORTA_ADR 		(SFR_BASE_ADDRESS + 0x00000)
#define SFR_PORTB_ADR 		(SFR_BASE_ADDRESS + 0x00040)
#define SFR_PORTC_ADR 		(SFR_BASE_ADDRESS + 0x00080)
#define SFR_PORTD_ADR 		(SFR_BASE_ADDRESS + 0x000C0)
#define SFR_PORTE_ADR 		(SFR_BASE_ADDRESS + 0x00100)
#define SFR_PORTF_ADR 		(SFR_BASE_ADDRESS + 0x00140)
#define SFR_PORTG_ADR 		(SFR_BASE_ADDRESS + 0x00180)
#define SFR_PORTH_ADR 		(SFR_BASE_ADDRESS + 0x001C0)
#define SFR_PORTI_ADR 		(SFR_BASE_ADDRESS + 0x00200)
#define SFR_PORTJ_ADR 		(SFR_BASE_ADDRESS + 0x00240)
#define SFR_PORTK_ADR 		(SFR_BASE_ADDRESS + 0x00280)

#define SFR_TMRB0_ADR 		(SFR_BASE_ADDRESS + 0x10000)
#define SFR_TMRB1_ADR 		(SFR_BASE_ADDRESS + 0x10040)
#define SFR_TMRB2_ADR 		(SFR_BASE_ADDRESS + 0x10080)
#define SFR_TMRB3_ADR 		(SFR_BASE_ADDRESS + 0x100C0)
#define SFR_TMRB4_ADR 		(SFR_BASE_ADDRESS + 0x10100)
#define SFR_TMRB5_ADR 		(SFR_BASE_ADDRESS + 0x10140)
#define SFR_TMRB6_ADR 		(SFR_BASE_ADDRESS + 0x10180)
#define SFR_TMRB7_ADR 		(SFR_BASE_ADDRESS + 0x101C0)
#define SFR_TMRB8_ADR 		(SFR_BASE_ADDRESS + 0x10200)
#define SFR_TMRB9_ADR 		(SFR_BASE_ADDRESS + 0x10240)

#define SFR_SBI0_ADR 		(SFR_BASE_ADDRESS + 0x20000)
#define SFR_SBI1_ADR 		(SFR_BASE_ADDRESS + 0x20020)
#define SFR_SBI2_ADR 		(SFR_BASE_ADDRESS + 0x20040)

#define SFR_SIO0_ADR 		(SFR_BASE_ADDRESS + 0x20080)
#define SFR_SIO1_ADR 		(SFR_BASE_ADDRESS + 0x200C0)
#define SFR_SIO2_ADR 		(SFR_BASE_ADDRESS + 0x20100)

#define SFR_ADC_ADR 		(SFR_BASE_ADDRESS + 0x30000)

#define SFR_WDT_ADR 		(SFR_BASE_ADDRESS + 0x40000)

#define SFR_RTC_ADR 		(SFR_BASE_ADDRESS + 0x40100)

#define SFR_CG_ADR	 		(SFR_BASE_ADDRESS + 0x40200)

#define SFR_CEC_ADR 		(SFR_BASE_ADDRESS + 0x40300)

#define SFR_RMC0_ADR 		(SFR_BASE_ADDRESS + 0x40400)
#define SFR_RMC1_ADR 		(SFR_BASE_ADDRESS + 0x40440)

#define SFR_FLASH_ADR 		(SFR_BASE_ADDRESS + 0x40500)

#define SFR_ICTR_ADR 		(0xE000E004)
#define SFR_SYSTICK_ADR		(0xE000E010)
#define SFR_NVIC_ADR 		(0xE000E100)
#define SFR_CPU_ADR 		(0xE000ED00)
#define SFR_STIR_ADR 		(0xE000EF00)
#define SFR_PERIPH_ADR 		(0xE000EFD0)



/******************************************************************************/
/*						   SFR declaration									  */
/******************************************************************************/

/*------------------------ No Debug Mode ------------------------------------*/
#ifndef DEBUG

				/* PORT */
#ifdef _PORTA
  #define PORTA				((SFR_PORTx_t *) SFR_PORTA_ADR)
#endif

#ifdef _PORTB
  #define PORTB				((SFR_PORTx_t *) SFR_PORTB_ADR)
#endif

#ifdef _PORTC
  #define PORTC				((SFR_PORTx_t *) SFR_PORTC_ADR)
#endif

#ifdef _PORTD
  #define PORTD				((SFR_PORTx_t *) SFR_PORTD_ADR)
#endif

#ifdef _PORTE
  #define PORTE				((SFR_PORTx_t *) SFR_PORTE_ADR)
#endif

#ifdef _PORTF
  #define PORTF				((SFR_PORTx_t *) SFR_PORTF_ADR)
#endif

#ifdef _PORTG
  #define PORTG				((SFR_PORTx_t *) SFR_PORTG_ADR)
#endif

#ifdef _PORTH
  #define PORTH				((SFR_PORTx_t *) SFR_PORTH_ADR)
#endif

#ifdef _PORTI
  #define PORTI				((SFR_PORTx_t *) SFR_PORTI_ADR)
#endif

#ifdef _PORTJ
  #define PORTJ				((SFR_PORTx_t *) SFR_PORTJ_ADR)
#endif

#ifdef _PORTK
  #define PORTK				((SFR_PORTx_t *) SFR_PORTK_ADR)
#endif

				/* TIMER */
#ifdef _TMRB0
  #define TMRB0				((SFR_TMRBx_t *) SFR_TMRB0_ADR)
#endif

#ifdef _TMRB1
  #define TMRB1				((SFR_TMRBx_t *) SFR_TMRB1_ADR)
#endif

#ifdef _TMRB2
  #define TMRB2				((SFR_TMRBx_t *) SFR_TMRB2_ADR)
#endif

#ifdef _TMRB3
  #define TMRB3				((SFR_TMRBx_t *) SFR_TMRB3_ADR)
#endif

#ifdef _TMRB4
  #define TMRB4				((SFR_TMRBx_t *) SFR_TMRB4_ADR)
#endif

#ifdef _TMRB5
  #define TMRB5				((SFR_TMRBx_t *) SFR_TMRB5_ADR)
#endif

#ifdef _TMRB6
  #define TMRB6				((SFR_TMRBx_t *) SFR_TMRB6_ADR)
#endif

#ifdef _TMRB7
  #define TMRB7				((SFR_TMRBx_t *) SFR_TMRB7_ADR)
#endif

#ifdef _TMRB8
  #define TMRB8				((SFR_TMRBx_t *) SFR_TMRB8_ADR)
#endif

#ifdef _TMRB9
  #define TMRB9				((SFR_TMRBx_t *) SFR_TMRB9_ADR)
#endif


				/* SBI */

#ifdef _SBI0
  #define SBI0				((SFR_SBIx_t *) SFR_SBI0_ADR)
#endif

#ifdef _SBI1
  #define SBI1				((SFR_SBIx_t *) SFR_SBI1_ADR)
#endif

#ifdef _SBI2
  #define SBI2				((SFR_SBIx_t *) SFR_SBI2_ADR)
#endif

				/* SIO */
#ifdef _SIO0
  #define SIO0				((SFR_SIOx_t *) SFR_SIO0_ADR)
#endif

#ifdef _SIO1
  #define SIO1				((SFR_SIOx_t *) SFR_SIO1_ADR)
#endif
#ifdef _SIO2
  #define SIO2				((SFR_SIOx_t *) SFR_SIO2_ADR)
#endif

				/* ADC */
#ifdef _ADC
  #define ADC				((SFR_ADC_t *) SFR_ADC_ADR)
#endif

				/* WDT */
#ifdef _WDT
#define WDT					((SFR_WDT_t *) SFR_WDT_ADR)
#endif

				/* RTC */
#ifdef _RTC
#define RTC					((SFR_RTC_t *) SFR_RTC_ADR)
#endif

				/* CG */
#ifdef _CG
#define CG					((SFR_CG_t *) SFR_CG_ADR)
#endif

				/* CEC */
#ifdef _CEC
  #define CEC				((SFR_CEC_t *) SFR_CEC_ADR)
#endif

				/* RMC */
#ifdef _RMC0
  #define RMC0				((SFR_RMCx_t *) SFR_RMC0_ADR)
#endif

#ifdef _RMC1
  #define RMC1				((SFR_RMCx_t *) SFR_RMC1_ADR)
#endif
				/* FLASH */
#ifdef _FLASH
  #define FLASH				((SFR_FLASH_t *) SFR_FLASH_ADR)
#endif

				/* NVIC */
#ifdef _NVIC
#define ICTR				((SFR_ICTR_t *) SFR_ICTR_ADR)
#define SYSTICK				((SFR_SYSTICK_t *) SFR_SYSTICK_ADR)
#define NVIC				((SFR_NVIC_t *) SFR_NVIC_ADR)
#define CPU					((SFR_CPU_t *) SFR_CPU_ADR)
#define STIR				((SFR_STIR_t *) SFR_STIR_ADR)
#define PERIPH				((SFR_PERIPF_t *) SFR_PERIPH_ADR)
#endif




/*------------------------ Debug Mode ----------------------------------------*/
#else	/* DEBUG */

				/* PORT */
#ifdef _PORTA
  EXTERN SFR_PORTx_t				*PORTA;
#endif

#ifdef _PORTB
  EXTERN SFR_PORTx_t				*PORTB;
#endif

#ifdef _PORTC
  EXTERN SFR_PORTx_t				*PORTC;
#endif

#ifdef _PORTD
  EXTERN SFR_PORTx_t				*PORTD;
#endif

#ifdef _PORTE
  EXTERN SFR_PORTx_t				*PORTE;
#endif

#ifdef _PORTF
  EXTERN SFR_PORTx_t				*PORTF;
#endif

#ifdef _PORTG
  EXTERN SFR_PORTx_t				*PORTG;
#endif

#ifdef _PORTH
  EXTERN SFR_PORTx_t				*PORTH;
#endif

#ifdef _PORTI
  EXTERN SFR_PORTx_t				*PORTI;
#endif

#ifdef _PORTJ
  EXTERN SFR_PORTx_t				*PORTJ;
#endif

#ifdef _PORTK
  EXTERN SFR_PORTx_t				*PORTK;
#endif


				/* TMRB */
#ifdef _TMRB0
  EXTERN SFR_TMRBx_t				*TMRB0;
#endif

#ifdef _TMRB1
  EXTERN SFR_TMRBx_t				*TMRB1;
#endif

#ifdef _TMRB2
  EXTERN SFR_TMRBx_t				*TMRB2;
#endif

#ifdef _TMRB3
  EXTERN SFR_TMRBx_t				*TMRB3;
#endif

#ifdef _TMRB4
  EXTERN SFR_TMRBx_t				*TMRB4;
#endif

#ifdef _TMRB5
  EXTERN SFR_TMRBx_t				*TMRB5;
#endif

#ifdef _TMRB6
  EXTERN SFR_TMRBx_t				*TMRB6;
#endif

#ifdef _TMRB7
  EXTERN SFR_TMRBx_t				*TMRB7;
#endif

#ifdef _TMRB8
  EXTERN SFR_TMRBx_t				*TMRB8;
#endif

#ifdef _TMRB9
  EXTERN SFR_TMRBx_t				*TMRB9;
#endif


				/* SBI */
#ifdef _SBI0
  EXTERN SFR_SBIx_t					*SBI0;
#endif

#ifdef _SBI1
  EXTERN SFR_SBIx_t					*SBI1;
#endif

#ifdef _SBI2
  EXTERN SFR_SBIx_t					*SBI2;
#endif


				/* SIO */
#ifdef _SIO0
  EXTERN SFR_SIOx_t					*SIO0;
#endif

#ifdef _SIO1
  EXTERN SFR_SIOx_t					*SIO1;
#endif

#ifdef _SIO2
  EXTERN SFR_SIOx_t					*SIO2;
#endif


				/* ADC */
#ifdef _ADC
  EXTERN SFR_ADC_t					*ADC;
#endif

				/* WDT */
#ifdef _WDT
  EXTERN SFR_WDT_t					*WDT;
#endif

				/* RTC */
#ifdef _RTC
  EXTERN SFR_RTC_t					*RTC;
#endif

				/* CG */
#ifdef _CG
  EXTERN SFR_CG_t					*CG;
#endif

				/* CEC */
#ifdef _CEC
  EXTERN SFR_CEC_t					*CEC;
#endif

				/* RMC */
#ifdef _RMC0
  EXTERN SFR_RMCx_t					*RMC0;
#endif

#ifdef _RMC1
  EXTERN SFR_RMCx_t					*RMC1;
#endif

				/* FLASH */
#ifdef _FLASH
  EXTERN SFR_FLASH_t				*FLASH;
#endif

				/* NVIC */
#ifdef _NVIC
  EXTERN SFR_NVIC_t					*NVIC;
#endif


#endif /* DEBUG */

#endif /* avoid double definition */
