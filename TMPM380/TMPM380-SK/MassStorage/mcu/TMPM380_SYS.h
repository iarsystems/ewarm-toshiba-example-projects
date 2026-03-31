/*******************************************************************************
* File Name          : tmpm380_sys.h
* Version            : V1.0
* Date				 : 2010/01/xx
* Description        : TMPM380 定義ファイル
*******************************************************************************/


#ifndef __TMPM380_SYS_H
#define __TMPM380_SYS_H


#ifdef	_SFR_DEFINE
#define EXTERN
#else
#define EXTERN extern
#endif


#if __CC_ARM == 1
/********* KEIL ***********/
#include <absacc.h>
#define __IO_REG(NAME, ADDRESS, TYPE)\
                       EXTERN volatile TYPE NAME __at(ADDRESS)
#endif


#if __ICCARM__ == 1
/******** IAR *************/
#define __IO_REG(NAME, ADDRESS, TYPE)\
                       volatile __no_init TYPE NAME @ ADDRESS
#endif


#if 0
/******** TOSHIBA *********/
#define __IO_REG(NAME, ADDRESS, TYPE)\
                       EXTERN __io(ADDRESS) TYPE NAME

/******** defult **********/
#define __IO_REG(NAME, ADDRESS, TYPE)\
                       #define  NAME  (*(volatile TYPE *)(ADDRESS))

#endif


#include "CortexM3_SYS.h"

/********************/
/* 共通使用			*/
/********************/


/* Memory Map */
#define IO_BASE         0x40000000


/* Port I/O I/O M330/M370/M380 */
/* M330 PA/PB/PC/PD/PE/PF/PG/PH/PI/PJ/PK */
/* M370 PA/PB/PC/PD/PE/PF/PG/PH/PI/PJ/PK/PL */
/* M380 PA/PB/PC/PD/PE/PF/PG/PH/PI/PJ/PL/PM/PN/PP */
#define PORT_BASE       (IO_BASE + 0x00000)

typedef struct {
	volatile	unsigned char			IO_Px;
	volatile	unsigned char			RESERVE1;
	volatile	unsigned char			RESERVE2;
	volatile	unsigned char			RESERVE3;
	volatile	unsigned char			IO_PxCR;
	volatile	unsigned char			RESERVE4;
	volatile	unsigned char			RESERVE5;
	volatile	unsigned char			RESERVE6;
	volatile	unsigned char			IO_PxFR1;
	volatile	unsigned char			RESERVE7;
	volatile	unsigned char			RESERVE8;
	volatile	unsigned char			RESERVE9;
	volatile	unsigned char			IO_PxFR2;
	volatile	unsigned char			RESERVE10;
	volatile	unsigned char			RESERVE11;
	volatile	unsigned char			RESERVE12;
	volatile	unsigned char			IO_PxFR3;
	volatile	unsigned char			RESERVE13;
	volatile	unsigned char			RESERVE14;
	volatile	unsigned char			RESERVE15;
	volatile	unsigned char			IO_PxFR4;
	volatile	unsigned char			RESERVE16;
	volatile	unsigned char			RESERVE17;
	volatile	unsigned char			RESERVE18;
	volatile	unsigned char			IO_PxFR5;
	volatile	unsigned char			RESERVE19;
	volatile	unsigned char			RESERVE20;
	volatile	unsigned char			RESERVE21;

	volatile	unsigned long			RESERVE22[3];
	volatile	unsigned char			IO_PxOD;
	volatile	unsigned char			RESERVE23;
	volatile	unsigned char			RESERVE24;
	volatile	unsigned char			RESERVE25;
	volatile	unsigned char			IO_PxPUP;
	volatile	unsigned char			RESERVE26;
	volatile	unsigned char			RESERVE27;
	volatile	unsigned char			RESERVE28;
	volatile	unsigned char			IO_PxPDN;
	volatile	unsigned char			RESERVE29;
	volatile	unsigned char			RESERVE30;
	volatile	unsigned char			RESERVE31;

	volatile	unsigned long			RESERVE32;
	volatile	unsigned char			IO_PxIE;
	volatile	unsigned char			RESERVE33;
	volatile	unsigned char			RESERVE34;
	volatile	unsigned char			RESERVE35;

	volatile	unsigned long			RESERVE36;
} PORTM;

typedef struct{
	PORTM cnl[15];
}PORT_GR;

	__IO_REG(PORT,	(PORT_BASE), PORT_GR);


/* 16-bit Timer/Event Counter (TMRB) M330/M370/M380 */
/* M330(10ch)/M370(8ch)/M380(8ch) */
#define TMR_BASE        (IO_BASE + 0x10000)

typedef struct {
	volatile unsigned char	TBnEN;
	volatile unsigned char	dummy1;
	volatile unsigned char	dummy2;
	volatile unsigned char	dummy3;
	volatile unsigned char	TBnRUN;
	volatile unsigned char	dummy4;
	volatile unsigned char	dummy5;
	volatile unsigned char	dummy6;
	volatile unsigned char	TBnCR;
	volatile unsigned char	dummy7;
	volatile unsigned char	dummy8;
	volatile unsigned char	dummy9;
	volatile unsigned char	TBnMOD;
	volatile unsigned char	dummy10;
	volatile unsigned char	dummy11;
	volatile unsigned char	dummy12;
	volatile unsigned char	TBnFFCR;
	volatile unsigned char	dummy13;
	volatile unsigned char	dummy14;
	volatile unsigned char	dummy15;
	volatile unsigned char	TBnST;
	volatile unsigned char	dummy16;
	volatile unsigned char	dummy17;
	volatile unsigned char	dummy18;
	volatile unsigned char	TBnIM;
	volatile unsigned char	dummy19;
	volatile unsigned char	dummy20;
	volatile unsigned char	dummy21;
	volatile unsigned short	TBnUC;
	volatile unsigned short	dummy22;
	volatile unsigned short	TBnRG0;
	volatile unsigned short	dummy23;
	volatile unsigned short	TBnRG1;
	volatile unsigned short	dummy24;
	volatile unsigned short	TBnCP0;
	volatile unsigned short	dummy25;
	volatile unsigned short	TBnCP1;
	volatile unsigned short	dummy26;
	volatile unsigned long	dummy27;
	volatile unsigned long	dummy28;
	volatile unsigned long	dummy29;
	volatile unsigned long	dummy30;
}TMR_16M;

typedef struct{
	TMR_16M cnl[10];
}TMR16_GR;

	__IO_REG(TMR16,	(TMR_BASE), TMR16_GR);


/* Encoder (ENC0) M370/M380 */
#define ENC0_BASE        (IO_BASE + 0x10400)

typedef struct{
	volatile unsigned long	EN0TNCR;
	volatile unsigned short	EN0RELOAD;
	volatile unsigned char	dummy1;
	volatile unsigned char	dummy2;
	volatile unsigned long	EN0INT;
	volatile unsigned long	EN0CNT;
}ENC0REG;

	__IO_REG(ENC0,	(ENC0_BASE), ENC0REG);

/* Encoder (ENC1) M370/M380 */
#define ENC1_BASE        (IO_BASE + 0x10500)

typedef struct{
	volatile unsigned long	EN1TNCR;
	volatile unsigned short	EN1RELOAD;
	volatile unsigned char	dummy1;
	volatile unsigned char	dummy2;
	volatile unsigned long	EN1INT;
	volatile unsigned long	EN1CNT;
}ENC1REG;

	__IO_REG(ENC1,	(ENC1_BASE), ENC1REG);


/* Serial Bus Interface (SBI) M330/M380 */
/* M330(3ch)/M380(2ch) */
#define SBI_BASE        (IO_BASE + 0x20000)

typedef struct{
	volatile unsigned char	SBInCR0;
	volatile unsigned char	dummy1;
	volatile unsigned char	dummy2;
	volatile unsigned char	dummy3;
	volatile unsigned char	SBInCR1;
	volatile unsigned char	dummy4;
	volatile unsigned char	dummy5;
	volatile unsigned char	dummy6;
	volatile unsigned char	SBInDBR;
	volatile unsigned char	dummy7;
	volatile unsigned char	dummy8;
	volatile unsigned char	dummy9;
	volatile unsigned char	SBInI2CAR;
	volatile unsigned char	dummy10;
	volatile unsigned char	dummy11;
	volatile unsigned char	dummy12;
	volatile unsigned char	SBInCR2;
	volatile unsigned char	dummy13;
	volatile unsigned char	dummy14;
	volatile unsigned char	dummy15;
	volatile unsigned char	SBInBR0;
	volatile unsigned char	dummy16;
	volatile unsigned char	dummy17;
	volatile unsigned char	dummy18;
	volatile unsigned long	dummy19;
	volatile unsigned long	dummy20;

/* SBIのレジスタに"SBInSRレジスタ(reading)"
   "SBInCR2レジスタ(writing)"と同じアドレス */

}SBIM;

typedef struct{
	SBIM cnl[3];
}SBI_GR;

	__IO_REG(SBI,	(SBI_BASE), SBI_GR);

#define SBInSR	SBInCR2



/* Serial Interface (SIO/UART) M330/M370/M380 */
/* M330(3ch)/M370(4ch)/M380(5ch) */
#define SIO_BASE        (IO_BASE + 0x20080)

typedef struct{
	volatile unsigned char	SCnEN;
	volatile unsigned char	dummy1;
	volatile unsigned char	dummy2;
	volatile unsigned char	dummy3;
	volatile unsigned char	SCnBUF;
	volatile unsigned char	dummy4;
	volatile unsigned char	dummy5;
	volatile unsigned char	dummy6;
	volatile unsigned char	SCnCR;
	volatile unsigned char	dummy7;
	volatile unsigned char	dummy8;
	volatile unsigned char	dummy9;
	volatile unsigned char	SCnMOD0;
	volatile unsigned char	dummy10;
	volatile unsigned char	dummy11;
	volatile unsigned char	dummy12;
	volatile unsigned char	SCnBRCR;
	volatile unsigned char	dummy13;
	volatile unsigned char	dummy14;
	volatile unsigned char	dummy15;
	volatile unsigned char	SCnBRADD;
	volatile unsigned char	dummy16;
	volatile unsigned char	dummy17;
	volatile unsigned char	dummy18;
	volatile unsigned char	SCnMOD1;
	volatile unsigned char	dummy19;
	volatile unsigned char	dummy20;
	volatile unsigned char	dummy21;
	volatile unsigned char	SCnMOD2;
	volatile unsigned char	dummy22;
	volatile unsigned char	dummy23;
	volatile unsigned char	dummy24;
	volatile unsigned char	SCnRFC;
	volatile unsigned char	dummy25;
	volatile unsigned char	dummy26;
	volatile unsigned char	dummy27;
	volatile unsigned char	SCnTFC;
	volatile unsigned char	dummy28;
	volatile unsigned char	dummy29;
	volatile unsigned char	dummy30;
	volatile unsigned char	SCnRST;
	volatile unsigned char	dummy31;
	volatile unsigned char	dummy32;
	volatile unsigned char	dummy33;
	volatile unsigned char	SCnTST;
	volatile unsigned char	dummy34;
	volatile unsigned char	dummy35;
	volatile unsigned char	dummy36;
	volatile unsigned char	SCnFCNF;
	volatile unsigned char	dummy37;
	volatile unsigned char	dummy38;
	volatile unsigned char	dummy39;
	volatile unsigned long	dummy40;
	volatile unsigned long	dummy41;
	volatile unsigned long	dummy42;
}SIOM;

typedef struct{
	SIOM cnl[5];
}SIO_GR;


	__IO_REG(SIO,	(SIO_BASE), SIO_GR);


/* A/D Converter A (ADC-A) M370/M380 */
/* M380 12/10bit(Selectable)ADC 18ch */

#define ADA_BASE        (IO_BASE + 0x30000)

typedef struct{
	volatile unsigned short	ADREG;
	volatile unsigned short	dummy1;
}ADREG_T;

typedef struct{
	volatile unsigned char	ADPSEL;
	volatile unsigned char	dummy2;
	volatile unsigned short	dummy3;
}ADPSEL_T;

typedef struct{
	volatile unsigned char	ADPINTS;
	volatile unsigned char	dummy4;
	volatile unsigned short	dummy5;
}ADPINTS_T;

typedef struct{
	volatile unsigned char	ADPSET_REG[4];
}ADPSET_T;

typedef struct{
	volatile unsigned char	ADTSET_REG;
}ADTSET_T;

typedef struct{
	volatile unsigned char	ADSSET_REG;
}ADSSET_T;

typedef struct{
	volatile unsigned char	ADASET_REG;
}ADASET_T;

typedef struct{
	volatile unsigned short	ADCMP;
	volatile unsigned short	dummy6;
}ADCMP_T;

typedef struct{
	volatile unsigned short	ADCMPCR;
	volatile unsigned short	dummy7;
}ADCMPCR_T;

typedef struct{
	volatile unsigned char	ADCLK;
	volatile unsigned char	dummy8;
	volatile unsigned short	dummy9;
	
	volatile unsigned char	ADMOD0;
	volatile unsigned char	dummy10;
	volatile unsigned short	dummy11;
	
	volatile unsigned char	ADMOD1;
	volatile unsigned char	dummy12;
	volatile unsigned short	dummy13;
	
	volatile unsigned char	ADMOD2;
	volatile unsigned char	dummy14;
	volatile unsigned short	dummy15;
	
	volatile ADCMPCR_T		ADCMPCR_M[2];
	volatile ADCMP_T		ADCMP_M[2];
	volatile ADREG_T		ADREG_M[12];
	volatile ADPSEL_T		ADPSEL_M[12];
	volatile ADPINTS_T		ADPINTS_M[6];
	volatile ADPSET_T	ADPSET_M[6];
	volatile ADTSET_T	ADTSET_M[12];
	volatile ADSSET_T	ADSSET_M[12];
	volatile ADASET_T	ADASET_M[12];

/*	volatile unsigned short	ADHWCR; */
	volatile unsigned short	ADMOD3;
	volatile unsigned short	dummy16;

/* M380の場合
   "ADAPSELレジスタ"は4個 残り8個(32byte)は
   dummy(無効)となります */

/* ADCのレジスタに"ADPSELレジスタ"
   レジスタ一覧のアドレスが正しいのか、それとも
   詳細説明のアドレスが正しいのか？ */

/* ADCのレジスタに"ADHWCRレジスタ"というのがあるのですが、
   "ADMOD3レジスタ"と同じアドレス どういうことだろうか */

}ADC_REG;

	__IO_REG(ADCA,	(ADA_BASE), ADC_REG);


/* Watchdog Timer (WDT) */
#define WDT_BASE        (IO_BASE + 0x40000)
typedef struct{
	volatile unsigned char	WDMOD;
	volatile unsigned char	dummy1;
	volatile unsigned short	dummy2;
	volatile unsigned char	WDCR;
	volatile unsigned char	dummy3;
	volatile unsigned short	dummy4;
}WDTREG;

	__IO_REG(WDT,	(WDT_BASE), WDTREG);


/* Real Time Clock (RTC) */
#define RTC_BASE        (IO_BASE + 0x40100)
typedef struct{
	volatile unsigned char	SECR;
	volatile unsigned char	MINR;
	volatile unsigned char	HOURR;
	volatile unsigned char	dummy1;
	volatile unsigned char	DAYR;
	volatile unsigned char	DATER;
	volatile unsigned char	MONTHR;
	volatile unsigned char	YEARR;
	volatile unsigned char	PAGER;
	volatile unsigned char	dummy2;
	volatile unsigned short	dummy3;
	volatile unsigned char	RESTR;
	volatile unsigned char	dummy4;
	volatile unsigned short	dummy5;
}RTCREG;

	__IO_REG(RTC,	(RTC_BASE), RTCREG);


/* Clock Generator (CG) M370/M380 */
#define CG_BASE         (IO_BASE + 0x40200)

typedef struct{
	volatile unsigned char	SYSCR0;
	volatile unsigned char	SYSCR1;
	volatile unsigned char	SYSCR2;
	volatile unsigned char	dummy1;
	volatile unsigned char	OSCCR0;
	volatile unsigned char	OSCCR1;
	volatile unsigned char	OSCCR2;
	volatile unsigned char	OSCCR3;
	volatile unsigned char	STBYCR0;
	volatile unsigned char	STBYCR1;
	volatile unsigned char	STBYCR2;
	volatile unsigned char	dummy2;
	volatile unsigned short	PLLSEL;
	volatile unsigned short	dummy3;
	volatile unsigned char	CKSEL;
	volatile unsigned char	dummy4;
	volatile unsigned short	dummy5;
	volatile unsigned char	ICRCG;
	volatile unsigned char	dummy6;
	volatile unsigned short	dummy7;
	volatile unsigned char	NMIFLG;
	volatile unsigned char	dummy8;
	volatile unsigned short	dummy9;
	volatile unsigned char	RSTFLG;
	volatile unsigned char	dummy10;
	volatile unsigned short	dummy11;
	volatile unsigned char	IMCG[32];

/* M380の場合
   "CGIMCnレジスタ"はCGIMCGA-CGIMCGEまでしか使用しないようだが、
   SFRレジスタマップ(P580)を参照するとCGIMCGA-CGIMCGHまで領域を確保
   しているので確保した */

}CG_T;

	__IO_REG(CG,	(CG_BASE), CG_T);


/* CEC M330 */
#define CEC_BASE        (IO_BASE + 0x40300)
typedef struct{
	volatile unsigned char	CECEN;
	volatile unsigned char	dummy1;
	volatile unsigned short	dummy2;
	volatile unsigned char	CECADD;
	volatile unsigned char	dummy3;
	volatile unsigned short	dummy4;
	volatile unsigned char	CECRESET;
	volatile unsigned char	dummy5;
	volatile unsigned short	dummy6;
	volatile unsigned char	CECREN;
	volatile unsigned char	dummy7;
	volatile unsigned short	dummy8;
	volatile unsigned char	CECRBUF;
	volatile unsigned char	dummy9;
	volatile unsigned short	dummy10;
	volatile unsigned char	CECRCR1;
	volatile unsigned char	dummy11;
	volatile unsigned short	dummy12;
	volatile unsigned char	CECRCR2;
	volatile unsigned char	dummy13;
	volatile unsigned short	dummy14;
	volatile unsigned char	CECTEN;
	volatile unsigned char	dummy15;
	volatile unsigned short	dummy16;
	volatile unsigned char	CECTBUF;
	volatile unsigned char	dummy17;
	volatile unsigned short	dummy18;
	volatile unsigned char	CECTCR;
	volatile unsigned char	dummy19;
	volatile unsigned short	dummy20;
	volatile unsigned char	CECRSTAT;
	volatile unsigned char	dummy21;
	volatile unsigned short	dummy22;
	volatile unsigned char	CECTSTAT;
	volatile unsigned char	dummy23;
	volatile unsigned short	dummy24;
}CEC_T;

	__IO_REG(CEC,	(CEC_BASE), CEC_T);



/* Remote Control Signal Preprocessor (RMC) M330/M380 */
/* M330(2ch) */
/* M380(1ch) */
#define RMC_BASE        (IO_BASE + 0x40400)

typedef struct{
	volatile unsigned char	RMCnEN;
	volatile unsigned char	dummy1;
	volatile unsigned short	dummy2;
	volatile unsigned char	RMCnREN;
	volatile unsigned char	dummy3;
	volatile unsigned short	dummy4;
	volatile unsigned long	RMCnRBUF1;
	volatile unsigned long	RMCnRBUF2;
	volatile unsigned long	RMCnRBUF3;
	volatile unsigned long	RMCnRCR1;
	volatile unsigned long	RMCnRCR2;
	volatile unsigned long	RMCnRCR3;
	volatile unsigned long	RMCnRCR4;
	volatile unsigned short	RMCRSTAT;
	volatile unsigned short	dummy5;
}RMCM;

typedef struct{
	RMCM cnl[2];
}RMC_GR;

	__IO_REG(RMC,	(RMC_BASE), RMC_GR);


/*  OFD (OFD) M380 */
/* M370と動作仕様が異なるため共通して使えない */
#define OFD_BASE        (IO_BASE + 0x40800)

typedef struct{
	volatile unsigned char	OFDCR1;
	volatile unsigned char	dummy1;
	volatile unsigned short	dummy2;
	volatile unsigned char	OFDCR2;
	volatile unsigned char	dummy3;
	volatile unsigned short	dummy4;
	volatile unsigned char	OFDMN;
	volatile unsigned char	dummy5;
	volatile unsigned short	dummy6;
	volatile unsigned long	dummy7;
	volatile unsigned char	OFDMX;
	volatile unsigned char	dummy8;
	volatile unsigned short	dummy9;
	volatile unsigned long	dummy10;
	volatile unsigned char	OFDRST;
	volatile unsigned char	dummy11;
	volatile unsigned short	dummy12;
	volatile unsigned char	OFDSTAT;
	volatile unsigned char	dummy13;
	volatile unsigned short	dummy14;
	}OFDREG;

	__IO_REG(OFD,	(OFD_BASE), OFDREG);

/*  POR/LVTD (LTD) M370/M380 */
#define LVD_BASE        (IO_BASE + 0x40900)

typedef struct{
	volatile unsigned char	VDCR;
	volatile unsigned char	dummy1;
	volatile unsigned short	dummy2;
	volatile unsigned char	VDSR;
	volatile unsigned char	dummy3;
	volatile unsigned short	dummy4;
}LVDREG;

	__IO_REG(LVD,	(LVD_BASE), LVDREG);


/* PMD (PMD-0) M370/M380 */
#define PMD0_BASE        (IO_BASE + 0x50400)
typedef struct {
	volatile unsigned char	MDEN;
	volatile unsigned char	dummy1;
	volatile unsigned short	dummy2;
	volatile unsigned char	PORTMD;
	volatile unsigned char	dummy3;
	volatile unsigned short	dummy4;
	volatile unsigned char	MDCR;
	volatile unsigned char	dummy5;
	volatile unsigned short	dummy6;
	volatile unsigned char	CNTSTA;
	volatile unsigned char	dummy7;
	volatile unsigned short	dummy8;
	volatile unsigned short	MDCNT;
	volatile unsigned short	dummy9;
	volatile unsigned short	MDPRD;
	volatile unsigned short	dummy10;
	volatile unsigned short	CMPU;
	volatile unsigned short	dummy11;
	volatile unsigned short	CMPV;
	volatile unsigned short	dummy12;
	volatile unsigned short	CMPW;
	volatile unsigned short	dummy13;
	volatile unsigned char	MODESEL;
	volatile unsigned char	dummy14;
	volatile unsigned short	dummy15;
	volatile unsigned short	MDOUT;
	volatile unsigned short	dummy16;
	volatile unsigned char	MDPOT;
	volatile unsigned char	dummy17;
	volatile unsigned short	dummy18;
	volatile unsigned char	EMGREL;
	volatile unsigned char	dummy19;
	volatile unsigned short	dummy20;
	volatile unsigned short	EMGCR;
	volatile unsigned short	dummy21;
	volatile unsigned char	EMGSTA;
	volatile unsigned char	dummy22;
	volatile unsigned short	dummy23;
	volatile unsigned short	OVVCR;
	volatile unsigned short	dummy24;
	volatile unsigned char	OVVSTA;
	volatile unsigned char	dummy25;
	volatile unsigned short	dummy26;
	volatile unsigned char	DTR;
	volatile unsigned char	dummy27;
	volatile unsigned short	dummy28;
	volatile unsigned short	TRGCMP0;
	volatile unsigned short	dummy29;
	volatile unsigned short	TRGCMP1;
	volatile unsigned short	dummy30;
	volatile unsigned short	TRGCMP2;
	volatile unsigned short	dummy31;
	volatile unsigned short	TRGCMP3;
	volatile unsigned short	dummy32;
	volatile unsigned short	TRGCR;
	volatile unsigned short	dummy33;
	volatile unsigned char	TRGMD;
	volatile unsigned char	dummy34;
	volatile unsigned short	dummy35;
	volatile unsigned char	TRGSEL;
	volatile unsigned char	dummy36;
	volatile unsigned short	dummy37;

/* M380の場合
   "OVVCR0レジスタ""OVVSTA0レジスタ"はdummy(無効)となります */
}PMD_REG;

	__IO_REG(PMD0,	(PMD0_BASE), PMD_REG);

/* PMD (PMD-1) M370/M380 */
#define PMD1_BASE        (IO_BASE + 0x50480)

	__IO_REG(PMD1,	(PMD1_BASE), PMD_REG);


/* 16bit Multi purpose timer(MPT) (TMR/IGBT) M380 */
/* M380(3ch) */
#define MPT_BASE        (IO_BASE + 0x50800)

typedef struct{
	volatile unsigned char	MTnEN;
	volatile unsigned char	dummy1;
	volatile unsigned short	dummy2;
	volatile unsigned char	MTnRUN;
	volatile unsigned char	dummy3;
	volatile unsigned short	dummy4;
	volatile unsigned char	MTTBnCR;
	volatile unsigned char	dummy5;
	volatile unsigned short	dummy6;
	volatile unsigned char	MTTBnMOD;
	volatile unsigned char	dummy7;
	volatile unsigned short	dummy8;
	volatile unsigned char	MTTBnFFCR;
	volatile unsigned char	dummy9;
	volatile unsigned short	dummy10;
	volatile unsigned char	MTTBnST;
	volatile unsigned char	dummy11;
	volatile unsigned short	dummy12;
	volatile unsigned char	MTTBnIM;
	volatile unsigned char	dummy13;
	volatile unsigned short	dummy14;
	volatile unsigned short	MTTBnUC;
	volatile unsigned short	dummy15;
	volatile unsigned short	MTTBnRG0;
	volatile unsigned short	dummy16;
	volatile unsigned short	MTTBnRG1;
	volatile unsigned short	dummy17;
	volatile unsigned short	MTTBnCP0;
	volatile unsigned short	dummy18;
	volatile unsigned short	MTTBnCP1;
	volatile unsigned short	dummy19;
	volatile unsigned short	MTIGnCR;
	volatile unsigned short	dummy20;
	volatile unsigned char	MTIGnRESTA;
	volatile unsigned char	dummy21;
	volatile unsigned short	dummy22;
	volatile unsigned char	MTIGnST;
	volatile unsigned char	dummy23;
	volatile unsigned short	dummy24;
	volatile unsigned char	MTIGnICR;
	volatile unsigned char	dummy25;
	volatile unsigned short	dummy26;
	volatile unsigned char	MTIGnOCR;
	volatile unsigned char	dummy27;
	volatile unsigned short	dummy28;
	volatile unsigned short	MTIGnRG2;
	volatile unsigned short	dummy29;
	volatile unsigned short	MTIGnRG3;
	volatile unsigned short	dummy30;
	volatile unsigned short	MTIGnRG4;
	volatile unsigned short	dummy31;
	volatile unsigned char	MTIGnEMGCR;
	volatile unsigned char	dummy32;
	volatile unsigned short	dummy33;
	volatile unsigned char	MTIGnEMGST;
	volatile unsigned char	dummy34;
	volatile unsigned short	dummy35;
	volatile unsigned long	dummy36;
	volatile unsigned long	dummy37;
	volatile unsigned long	dummy38;
	volatile unsigned long	dummy39;
	volatile unsigned long	dummy40;
	volatile unsigned long	dummy41;
	volatile unsigned long	dummy42;
	volatile unsigned long	dummy43;
	volatile unsigned long	dummy44;
	volatile unsigned long	dummy45;
}MPT_M;

typedef struct{
	MPT_M cnl[3];
}MPT_GR;


	__IO_REG(MPT,	(MPT_BASE), MPT_GR);


/* DMA M380 */
#define DMA_BASE        (IO_BASE + 0x80000)
typedef struct{
	volatile unsigned char	INTSTS;
	volatile unsigned char	dummy1;
	volatile unsigned short	dummy2;
	volatile unsigned char	INTTCSTS;
	volatile unsigned char	dummy3;
	volatile unsigned short	dummy4;
	volatile unsigned char	INTTCCLR;
	volatile unsigned char	dummy5;
	volatile unsigned short	dummy6;
	volatile unsigned char	INTERRSTS;
	volatile unsigned char	dummy7;
	volatile unsigned short	dummy8;
	volatile unsigned char	INTERRCLR;
	volatile unsigned char	dummy9;
	volatile unsigned short	dummy10;
	volatile unsigned char	RAWINTTCSTS;
	volatile unsigned char	dummy11;
	volatile unsigned short	dummy12;
	volatile unsigned char	RAWINTERRSTS;
	volatile unsigned char	dummy13;
	volatile unsigned short	dummy14;
	volatile unsigned char	ENBLDCHNS;
	volatile unsigned char	dummy15;
	volatile unsigned short	dummy16;
	volatile unsigned short	SOFTBREQ;
	volatile unsigned short	dummy17;
	volatile unsigned short	SOFTSREQ;
	volatile unsigned short	dummy18;
	volatile unsigned char	CFG;
	volatile unsigned char	dummy19;
	volatile unsigned short	dummy20;
	volatile unsigned long	C0SRCADR;
	volatile unsigned long	C0DESADR;
	volatile unsigned long	C0LLI;
	volatile unsigned long	C0CTRL;
	volatile unsigned long	C0CFG;
	volatile unsigned long	dummy21;
	volatile unsigned long	dummy22;
	volatile unsigned long	dummy23;
	volatile unsigned long	C1SRCADR;
	volatile unsigned long	C1DESADR;
	volatile unsigned long	C1LLI;
	volatile unsigned long	C1CTRL;
	volatile unsigned long	C1CFG;
}DMAREG;

	__IO_REG(DMA,	(DMA_BASE), DMAREG);


/* Synchronous serial Port(SSP-0) M380 */
#define SSP0_BASE        (IO_BASE + 0xC0000)

typedef struct{
	volatile unsigned short	SSPCR0;
	volatile unsigned short	dummy1;
	volatile unsigned char	SSPCR1;
	volatile unsigned char	dummy2;
	volatile unsigned short	dummy3;
	volatile unsigned short	SSPDR;
	volatile unsigned short	dummy4;
	volatile unsigned char	SSPSR;
	volatile unsigned char	dummy5;
	volatile unsigned short	dummy6;
	volatile unsigned char	SSPCPSR;
	volatile unsigned char	dummy7;
	volatile unsigned short	dummy8;
	volatile unsigned char	SSPIMSC;
	volatile unsigned char	dummy9;
	volatile unsigned short	dummy10;
	volatile unsigned char	SSPRIS;
	volatile unsigned char	dummy11;
	volatile unsigned short	dummy12;
	volatile unsigned char	SSPMIS;
	volatile unsigned char	dummy13;
	volatile unsigned short	dummy14;
	volatile unsigned char	SSPICR;
	volatile unsigned char	dummy15;
	volatile unsigned short	dummy16;
	volatile unsigned char	SSPDMACR;
	volatile unsigned char	dummy17;
	volatile unsigned short	dummy18;
}SSP_REG;

	__IO_REG(SSP0,	(SSP0_BASE), SSP_REG);


/* Synchronous serial Port(SSP-1) M380 */
#define SSP1_BASE        (IO_BASE + 0xC1000)

	__IO_REG(SSP1,	(SSP1_BASE), SSP_REG);


/* Flash Controller M380 */
#define FLASH_BASE      (IO_BASE + 0x1FFF000)

	__IO_REG(PRID0     ,(FLASH_BASE + 0x0)	    , unsigned long);
	__IO_REG(PRID1     ,(FLASH_BASE + 0x4)	    , unsigned long);
	__IO_REG(FCSECBIT  ,(FLASH_BASE + 0x10)	, unsigned char);
	__IO_REG(SECSTATUS ,(FLASH_BASE + 0x14)	, unsigned long);
	__IO_REG(FCFLCS    ,(FLASH_BASE + 0x20)	, unsigned long);
	__IO_REG(WLDEND    ,(FLASH_BASE + 0x24)	, unsigned long);
	__IO_REG(WCLKWAIT  ,(FLASH_BASE + 0x28)	, unsigned long);

/* "FCSECBITレジスタ""FCFLCSレジスタ"以外は
    TDに説明が載っていない(reserved?) */


/* Chip ID  M380 */
#define ID_BASE         (IO_BASE + 0x1FFF000)

	__IO_REG(CHIPID0   ,(ID_BASE + 0x40)	, unsigned char);
	__IO_REG(CHIPID1   ,(ID_BASE + 0x44)	, unsigned char);
	__IO_REG(STCALIBV  ,(ID_BASE + 0x50)	, unsigned char);
	__IO_REG(BOOTIDAD  ,(ID_BASE + 0x60)	, unsigned long);
	__IO_REG(BOOTPRDC1 ,(ID_BASE + 0x64)	, unsigned char);
	__IO_REG(BOOTPRDC2 ,(ID_BASE + 0x68)	, unsigned char);
	__IO_REG(BOOTPRDC3 ,(ID_BASE + 0x6C)	, unsigned char);
	__IO_REG(BOOTRABG  ,(ID_BASE + 0x70)	, unsigned long);
	__IO_REG(BOOTRAEN  ,(ID_BASE + 0x74)	, unsigned long);
	__IO_REG(BOOTFLBG  ,(ID_BASE + 0x78)	, unsigned long);
	__IO_REG(BOOTFLEN  ,(ID_BASE + 0x7C)	, unsigned long);
	__IO_REG(BOOTBLNM  ,(ID_BASE + 0x80)	, unsigned long);
	__IO_REG(BOOT16BG  ,(ID_BASE + 0x84)	, unsigned long);
	__IO_REG(BOOT32BG  ,(ID_BASE + 0x88)	, unsigned long);
	__IO_REG(BOOT64BG  ,(ID_BASE + 0x8C)	, unsigned long);
	__IO_REG(BOOT12BG  ,(ID_BASE + 0x90)	, unsigned long);

/* TDにレジスタの説明が載っていない(reserved?) */

#endif  // __TMPM380_SYS_H

/*************************** END OF FILE **************************************/
