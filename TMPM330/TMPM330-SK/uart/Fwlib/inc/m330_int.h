/*******************************************************************************
* File Name 		 : m330_int.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : INTERRUPT header
********************************************************************************/

/*  avoid double definition  */
#ifndef __M330_INT_H
#define __M330_INT_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* PORT initial data */

#define IO_INT_REGFIELD_0			(u_int8)0x00
#define IO_INT_REGFIELD_1			(u_int8)0x01
#define IO_INT_PRIFIELDMAX			240

/* INT Interrupt Request Clear mask */
	#define IO_INT_REQCLR_MASK			((u_int8)0x1F)

/* INT Enable mask */
#define IO_INT_ENABLE_MASK32		((u_int32)0x01010101)
#define IO_INT_ENABLE_MASK08		((u_int8)0x01)

typedef enum { INT0 = 		0, 
			   INT1 = 		1,
			   INT2 = 		2,
			   INT3 = 		3,
			   INT4 = 		4,
			   INT5 = 		5,
			   INTCECRX = 	6,
			   INTRMCRX0 = 	7,
			   INTRTC = 	8,
			   INT6 = 		9,
			   INT7 = 		10,
			   INTRMCRX1 = 	11,
			   INTCECTX = 	12
			 } IpINT_ChSel;							/* INT CH data */



	/* Batch setting symbol */

	/* ICRCG */			/* API_INT_ReqClr */
#define IP_INT_CLR_INT0			0x00		/* INT0 ReqClr			 */
#define IP_INT_CLR_INT1			0x01		/* INT1 ReqClr			 */
#define IP_INT_CLR_INT2			0x02		/* INT2 ReqClr			 */
#define IP_INT_CLR_INT3			0x03		/* INT3 ReqClr			 */
#define IP_INT_CLR_INT4			0x04		/* INT4 ReqClr			 */
#define IP_INT_CLR_INT5			0x05		/* INT5 ReqClr			 */
#define IP_INT_CLR_INTCECRX		0x06		/* INTCEC ReqClr		 */
#define IP_INT_CLR_INTRMCRX0	0x07		/* INTRMCRX0 ReqClr		 */
#define IP_INT_CLR_INTRTC		0x08		/* INTRTC ReqClr		 */
#define IP_INT_CLR_INT6			0x09		/* INT6 ReqClr			 */
#define IP_INT_CLR_INT7			0x0A		/* INT7 ReqClr			 */
#define IP_INT_CLR_INTRMCRX1	0x0B		/* INTRMCRX1 ReqClr		 */

	/* IMCGA,IMCGB,IMCGC,IMCGD */			/* API_INT_ActSt_Set */
#define IP_INT_ACTST_L			0x00		/* Standby Active State "L"	 */
#define IP_INT_ACTST_H			0x10		/* Standby Active State "H"	 */
#define IP_INT_ACTST_FALLING	0x20		/* Standby Active State "FALLING"	 */
#define IP_INT_ACTST_RISING		0x30		/* Standby Active State "RISING"	 */
#define IP_INT_ACTST_BOTH		0x40		/* Standby Active State "BOTH(FALLING,RISING)"	 */
	/* IMCGA,IMCGB,IMCGC,IMCGD */			/* API_INT_Enable */
#define IP_INT_DIS			0x00		/* Interrupt Disable	 */
#define IP_INT_ENA			0x01		/* Interrupt Enable	 */



/*--------------------- MCU(M330) INTERRUPT ---------------------*/

/* MCU(M330) INTERRUPT initial data */
#define IO_CG_ICRCG_Init		((u_int8)0x00)
#define IO_CG_NMIFLG_Init		((u_int8)0x00)
#define IO_CG_RSTFLG_Init		((u_int8)0x00)
#define IO_CG_IMCGA_Init		((u_int32)0x20202020)
#define IO_CG_IMCGB_Init		((u_int32)0x20202020)
#define IO_CG_IMCGC_Init		((u_int32)0x20202020)
#define IO_CG_IMCGD_Init		((u_int8)0x20)

/* Interrupt Standby Active State MASK bit */
#define CG_STS_MASK (u_int8)0x8F
#define CG_STS_SHIFT (u_int8)0x04

#define CG_UI8BIT2_0_MASK (u_int8)0x07

/* Interrupt Standby Active State */	/* API_INT_ActSt_Set */
#define _INT0_STS		(u_int8 *)(&(CG->IO_IMCGA.byte[0]))
#define _INT1_STS		(u_int8 *)(&(CG->IO_IMCGA.byte[1]))
#define _INT2_STS		(u_int8 *)(&(CG->IO_IMCGA.byte[2]))
#define _INT3_STS		(u_int8 *)(&(CG->IO_IMCGA.byte[3]))
#define _INT4_STS		(u_int8 *)(&(CG->IO_IMCGB.byte[0]))
#define _INT5_STS		(u_int8 *)(&(CG->IO_IMCGB.byte[1]))
#define _INTCECRX_STS	(u_int8 *)(&(CG->IO_IMCGB.byte[2]))
#define _INTRMCRX0_STS	(u_int8 *)(&(CG->IO_IMCGB.byte[3]))
#define _INTRTC_STS		(u_int8 *)(&(CG->IO_IMCGC.byte[0]))
#define _INT6_STS		(u_int8 *)(&(CG->IO_IMCGC.byte[1]))
#define _INT7_STS		(u_int8 *)(&(CG->IO_IMCGC.byte[2]))
#define _INTRMCRX1_STS	(u_int8 *)(&(CG->IO_IMCGC.byte[3]))
#define _INTCECTX_STS	(u_int8 *)(&(CG->IO_IMCGD.byte[0]))

/* Interrupt Enable MASK bit */
#define CG_INTEN_MASK (u_int8)0xFE

/* Interrupt Enable */	/* API_INT_Enable */
#define _INT0_EN		(u_int8 *)(&(CG->IO_IMCGA.byte[0]))
#define _INT1_EN		(u_int8 *)(&(CG->IO_IMCGA.byte[1]))
#define _INT2_EN		(u_int8 *)(&(CG->IO_IMCGA.byte[2]))
#define _INT3_EN		(u_int8 *)(&(CG->IO_IMCGA.byte[3]))
#define _INT4_EN		(u_int8 *)(&(CG->IO_IMCGB.byte[0]))
#define _INT5_EN		(u_int8 *)(&(CG->IO_IMCGB.byte[1]))
#define _INTCECRX_EN	(u_int8 *)(&(CG->IO_IMCGB.byte[2]))
#define _INTRMCRX0_EN	(u_int8 *)(&(CG->IO_IMCGB.byte[3]))
#define _INTRTC_EN		(u_int8 *)(&(CG->IO_IMCGC.byte[0]))
#define _INT6_EN		(u_int8 *)(&(CG->IO_IMCGC.byte[1]))
#define _INT7_EN		(u_int8 *)(&(CG->IO_IMCGC.byte[2]))
#define _INTRMCRX1_EN	(u_int8 *)(&(CG->IO_IMCGC.byte[3]))
#define _INTCECTX_EN	(u_int8 *)(&(CG->IO_IMCGD.byte[0]))


/*------------------------ Cortex-M3 NVIC -----------------------*/

/* Cortex-M3 NVIC initial data */
/* Set-Enable Reg */
/* Clear-Enable Reg */
/* Set-Pending Reg */
/* Clear-Pending Reg */
/* Active-Bit Reg */

/* Priority Register */
#define IO_NVIC_INTPR_Init		((u_int8)0x00)
/* CPUID Base register */
/* Interrupt Control State register */
#define IO_CPU_ICSR_Init		((u_int32)0x00000000)
/* Vector Table Offset Register */
#define IO_CPU_VTOR_Init		((u_int32)0x00000000)
/* System Handler Priority Register */
#define IO_CPU_SHPR_Init		((u_int32)0x00000000)
/* System Handler Control Register */
#define IO_CPU_SHCSR_Init		((u_int32)0x00000000)
/* Systick Control Type Register */
#define IO_SYSTICK_CTL_Init		((u_int32)0x00000000)
/* Systick Reload Value Register */
/* Systick Current Value Register */


/* Enable Set/Clear set MASK bit  */
#define INT_UI32BIT0_MASK (u_int32)0x00000001

/* Enable Set/Clear set bit */
#define INT_BIT00 (u_int32)0x00000001
#define INT_BIT01 (u_int32)0x00000002
#define INT_BIT02 (u_int32)0x00000004
#define INT_BIT03 (u_int32)0x00000008
#define INT_BIT04 (u_int32)0x00000010
#define INT_BIT05 (u_int32)0x00000020
#define INT_BIT06 (u_int32)0x00000040
#define INT_BIT07 (u_int32)0x00000080
#define INT_BIT08 (u_int32)0x00000100
#define INT_BIT09 (u_int32)0x00000200
#define INT_BIT10 (u_int32)0x00000400
#define INT_BIT11 (u_int32)0x00000800
#define INT_BIT12 (u_int32)0x00001000
#define INT_BIT13 (u_int32)0x00002000
#define INT_BIT14 (u_int32)0x00004000
#define INT_BIT15 (u_int32)0x00008000
#define INT_BIT16 (u_int32)0x00010000
#define INT_BIT17 (u_int32)0x00020000
#define INT_BIT18 (u_int32)0x00040000
#define INT_BIT19 (u_int32)0x00080000
#define INT_BIT20 (u_int32)0x00100000
#define INT_BIT21 (u_int32)0x00200000
#define INT_BIT22 (u_int32)0x00400000
#define INT_BIT23 (u_int32)0x00800000
#define INT_BIT24 (u_int32)0x01000000
#define INT_BIT25 (u_int32)0x02000000
#define INT_BIT26 (u_int32)0x04000000
#define INT_BIT27 (u_int32)0x08000000
#define INT_BIT28 (u_int32)0x10000000
#define INT_BIT29 (u_int32)0x20000000
#define INT_BIT30 (u_int32)0x40000000
#define INT_BIT31 (u_int32)0x80000000

/* Enable Set Reg individually set */	/* API_INT_SER_Set */
#define _INTSER00 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT00
#define _INTSER01 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT01
#define _INTSER02 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT02
#define _INTSER03 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT03
#define _INTSER04 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT04
#define _INTSER05 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT05
#define _INTSER06 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT06
#define _INTSER07 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT07
#define _INTSER08 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT08
#define _INTSER09 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT09
#define _INTSER10 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT10
#define _INTSER11 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT11
#define _INTSER12 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT12
#define _INTSER13 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT13
#define _INTSER14 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT14
#define _INTSER15 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT15
#define _INTSER16 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT16
#define _INTSER17 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT17
#define _INTSER18 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT18
#define _INTSER19 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT19
#define _INTSER20 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT20
#define _INTSER21 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT21
#define _INTSER22 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT22
#define _INTSER23 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT23
#define _INTSER24 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT24
#define _INTSER25 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT25
#define _INTSER26 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT26
#define _INTSER27 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT27
#define _INTSER28 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT28
#define _INTSER29 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT29
#define _INTSER30 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT30
#define _INTSER31 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),INT_BIT31

#define _INTSER32 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT00
#define _INTSER33 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT01
#define _INTSER34 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT02
#define _INTSER35 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT03
#define _INTSER36 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT04
#define _INTSER37 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT05
#define _INTSER38 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT06
#define _INTSER39 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT07
#define _INTSER40 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT08
#define _INTSER41 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT09
#define _INTSER42 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT10
#define _INTSER43 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT11
#define _INTSER44 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT12
#define _INTSER45 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT13
#define _INTSER46 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT14
#define _INTSER47 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT15
#define _INTSER48 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT16
#define _INTSER49 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT17
#define _INTSER50 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT18
#define _INTSER51 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT19
#define _INTSER52 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT20
#define _INTSER53 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT21
#define _INTSER54 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT22
#define _INTSER55 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT23
#define _INTSER56 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT24
#define _INTSER57 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT25
#define _INTSER58 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT26
#define _INTSER59 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT27
#define _INTSER60 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT28
#define _INTSER61 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT29
#define _INTSER62 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT30
#define _INTSER63 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),INT_BIT31

/* Enable Clear Reg individually set */		/* API_INT_CER_Set */
#define _INTCER00 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT00
#define _INTCER01 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT01
#define _INTCER02 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT02
#define _INTCER03 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT03
#define _INTCER04 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT04
#define _INTCER05 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT05
#define _INTCER06 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT06
#define _INTCER07 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT07
#define _INTCER08 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT08
#define _INTCER09 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT09
#define _INTCER10 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT10
#define _INTCER11 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT11
#define _INTCER12 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT12
#define _INTCER13 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT13
#define _INTCER14 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT14
#define _INTCER15 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT15
#define _INTCER16 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT16
#define _INTCER17 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT17
#define _INTCER18 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT18
#define _INTCER19 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT19
#define _INTCER20 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT20
#define _INTCER21 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT21
#define _INTCER22 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT22
#define _INTCER23 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT23
#define _INTCER24 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT24
#define _INTCER25 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT25
#define _INTCER26 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT26
#define _INTCER27 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT27
#define _INTCER28 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT28
#define _INTCER29 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT29
#define _INTCER30 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT30
#define _INTCER31 (u_int32 *)(&(NVIC->IO_NVIC_ICER00_31.reg)),INT_BIT31

#define _INTCER32 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT00
#define _INTCER33 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT01
#define _INTCER34 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT02
#define _INTCER35 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT03
#define _INTCER36 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT04
#define _INTCER37 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT05
#define _INTCER38 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT06
#define _INTCER39 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT07
#define _INTCER40 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT08
#define _INTCER41 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT09
#define _INTCER42 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT10
#define _INTCER43 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT11
#define _INTCER44 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT12
#define _INTCER45 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT13
#define _INTCER46 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT14
#define _INTCER47 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT15
#define _INTCER48 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT16
#define _INTCER49 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT17
#define _INTCER50 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT18
#define _INTCER51 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT19
#define _INTCER52 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT20
#define _INTCER53 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT21
#define _INTCER54 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT22
#define _INTCER55 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT23
#define _INTCER56 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT24
#define _INTCER57 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT25
#define _INTCER58 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT26
#define _INTCER59 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT27
#define _INTCER60 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT28
#define _INTCER61 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT29
#define _INTCER62 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT30
#define _INTCER63 (u_int32 *)(&(NVIC->IO_NVIC_ICER32_63.reg)),INT_BIT31

/* Set Pending Reg individually set */		/* API_INT_SPR_Set */
#define _INTSPR00 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT00
#define _INTSPR01 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT01
#define _INTSPR02 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT02
#define _INTSPR03 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT03
#define _INTSPR04 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT04
#define _INTSPR05 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT05
#define _INTSPR06 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT06
#define _INTSPR07 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT07
#define _INTSPR08 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT08
#define _INTSPR09 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT09
#define _INTSPR10 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT10
#define _INTSPR11 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT11
#define _INTSPR12 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT12
#define _INTSPR13 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT13
#define _INTSPR14 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT14
#define _INTSPR15 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT15
#define _INTSPR16 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT16
#define _INTSPR17 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT17
#define _INTSPR18 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT18
#define _INTSPR19 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT19
#define _INTSPR20 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT20
#define _INTSPR21 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT21
#define _INTSPR22 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT22
#define _INTSPR23 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT23
#define _INTSPR24 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT24
#define _INTSPR25 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT25
#define _INTSPR26 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT26
#define _INTSPR27 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT27
#define _INTSPR28 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT28
#define _INTSPR29 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT29
#define _INTSPR30 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT30
#define _INTSPR31 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),INT_BIT31

#define _INTSPR32 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT00
#define _INTSPR33 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT01
#define _INTSPR34 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT02
#define _INTSPR35 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT03
#define _INTSPR36 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT04
#define _INTSPR37 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT05
#define _INTSPR38 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT06
#define _INTSPR39 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT07
#define _INTSPR40 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT08
#define _INTSPR41 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT09
#define _INTSPR42 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT10
#define _INTSPR43 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT11
#define _INTSPR44 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT12
#define _INTSPR45 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT13
#define _INTSPR46 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT14
#define _INTSPR47 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT15
#define _INTSPR48 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT16
#define _INTSPR49 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT17
#define _INTSPR50 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT18
#define _INTSPR51 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT19
#define _INTSPR52 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT20
#define _INTSPR53 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT21
#define _INTSPR54 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT22
#define _INTSPR55 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT23
#define _INTSPR56 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT24
#define _INTSPR57 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT25
#define _INTSPR58 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT26
#define _INTSPR59 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT27
#define _INTSPR60 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT28
#define _INTSPR61 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT29
#define _INTSPR62 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT30
#define _INTSPR63 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),INT_BIT31

/* Clear Pending Reg individually set */		/* API_INT_CPR_Set */
#define _INTCPR00 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT00
#define _INTCPR01 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT01
#define _INTCPR02 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT02
#define _INTCPR03 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT03
#define _INTCPR04 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT04
#define _INTCPR05 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT05
#define _INTCPR06 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT06
#define _INTCPR07 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT07
#define _INTCPR08 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT08
#define _INTCPR09 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT09
#define _INTCPR10 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT10
#define _INTCPR11 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT11
#define _INTCPR12 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT12
#define _INTCPR13 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT13
#define _INTCPR14 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT14
#define _INTCPR15 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT15
#define _INTCPR16 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT16
#define _INTCPR17 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT17
#define _INTCPR18 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT18
#define _INTCPR19 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT19
#define _INTCPR20 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT20
#define _INTCPR21 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT21
#define _INTCPR22 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT22
#define _INTCPR23 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT23
#define _INTCPR24 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT24
#define _INTCPR25 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT25
#define _INTCPR26 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT26
#define _INTCPR27 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT27
#define _INTCPR28 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT28
#define _INTCPR29 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT29
#define _INTCPR30 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT30
#define _INTCPR31 (u_int32 *)(&(NVIC->IO_NVIC_ICPR00_31.reg)),INT_BIT31

#define _INTCPR32 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT00
#define _INTCPR33 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT01
#define _INTCPR34 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT02
#define _INTCPR35 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT03
#define _INTCPR36 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT04
#define _INTCPR37 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT05
#define _INTCPR38 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT06
#define _INTCPR39 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT07
#define _INTCPR40 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT08
#define _INTCPR41 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT09
#define _INTCPR42 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT10
#define _INTCPR43 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT11
#define _INTCPR44 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT12
#define _INTCPR45 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT13
#define _INTCPR46 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT14
#define _INTCPR47 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT15
#define _INTCPR48 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT16
#define _INTCPR49 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT17
#define _INTCPR50 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT18
#define _INTCPR51 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT19
#define _INTCPR52 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT20
#define _INTCPR53 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT21
#define _INTCPR54 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT22
#define _INTCPR55 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT23
#define _INTCPR56 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT24
#define _INTCPR57 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT25
#define _INTCPR58 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT26
#define _INTCPR59 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT27
#define _INTCPR60 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT28
#define _INTCPR61 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT29
#define _INTCPR62 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT30
#define _INTCPR63 (u_int32 *)(&(NVIC->IO_NVIC_ICPR32_63.reg)),INT_BIT31


/* Enable Set Reg individually Read */	/* API_INT_SER_Read */
#define _INTSER_R00 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT0
#define _INTSER_R01 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT1
#define _INTSER_R02 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT2
#define _INTSER_R03 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT3
#define _INTSER_R04 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT4
#define _INTSER_R05 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT5
#define _INTSER_R06 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT6
#define _INTSER_R07 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT7
#define _INTSER_R08 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT8
#define _INTSER_R09 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT9
#define _INTSER_R10 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT10
#define _INTSER_R11 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT11
#define _INTSER_R12 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT12
#define _INTSER_R13 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT13
#define _INTSER_R14 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT14
#define _INTSER_R15 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT15
#define _INTSER_R16 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT16
#define _INTSER_R17 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT17
#define _INTSER_R18 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT18
#define _INTSER_R19 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT19
#define _INTSER_R20 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT20
#define _INTSER_R21 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT21
#define _INTSER_R22 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT22
#define _INTSER_R23 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT23
#define _INTSER_R24 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT24
#define _INTSER_R25 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT25
#define _INTSER_R26 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT26
#define _INTSER_R27 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT27
#define _INTSER_R28 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT28
#define _INTSER_R29 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT29
#define _INTSER_R30 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT30
#define _INTSER_R31 (u_int32 *)(&(NVIC->IO_NVIC_ISER00_31.reg)),BIT31

#define _INTSER_R32 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT0
#define _INTSER_R33 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT1
#define _INTSER_R34 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT2
#define _INTSER_R35 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT3
#define _INTSER_R36 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT4
#define _INTSER_R37 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT5
#define _INTSER_R38 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT6
#define _INTSER_R39 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT7
#define _INTSER_R40 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT8
#define _INTSER_R41 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT9
#define _INTSER_R42 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT10
#define _INTSER_R43 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT11
#define _INTSER_R44 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT12
#define _INTSER_R45 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT13
#define _INTSER_R46 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT14
#define _INTSER_R47 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT15
#define _INTSER_R48 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT16
#define _INTSER_R49 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT17
#define _INTSER_R50 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT18
#define _INTSER_R51 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT19
#define _INTSER_R52 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT20
#define _INTSER_R53 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT21
#define _INTSER_R54 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT22
#define _INTSER_R55 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT23
#define _INTSER_R56 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT24
#define _INTSER_R57 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT25
#define _INTSER_R58 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT26
#define _INTSER_R59 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT27
#define _INTSER_R60 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT28
#define _INTSER_R61 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT29
#define _INTSER_R62 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT30
#define _INTSER_R63 (u_int32 *)(&(NVIC->IO_NVIC_ISER32_63.reg)),BIT31

/* Pending Set Reg individually read */	/* API_INT_SPR_Read */
#define _INTSPR_R00 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT0
#define _INTSPR_R01 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT1
#define _INTSPR_R02 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT2
#define _INTSPR_R03 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT3
#define _INTSPR_R04 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT4
#define _INTSPR_R05 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT5
#define _INTSPR_R06 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT6
#define _INTSPR_R07 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT7
#define _INTSPR_R08 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT8
#define _INTSPR_R09 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT9
#define _INTSPR_R10 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT10
#define _INTSPR_R11 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT11
#define _INTSPR_R12 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT12
#define _INTSPR_R13 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT13
#define _INTSPR_R14 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT14
#define _INTSPR_R15 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT15
#define _INTSPR_R16 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT16
#define _INTSPR_R17 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT17
#define _INTSPR_R18 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT18
#define _INTSPR_R19 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT19
#define _INTSPR_R20 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT20
#define _INTSPR_R21 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT21
#define _INTSPR_R22 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT22
#define _INTSPR_R23 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT23
#define _INTSPR_R24 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT24
#define _INTSPR_R25 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT25
#define _INTSPR_R26 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT26
#define _INTSPR_R27 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT27
#define _INTSPR_R28 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT28
#define _INTSPR_R29 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT29
#define _INTSPR_R30 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT30
#define _INTSPR_R31 (u_int32 *)(&(NVIC->IO_NVIC_ISPR00_31.reg)),BIT31

#define _INTSPR_R32 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT0
#define _INTSPR_R33 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT1
#define _INTSPR_R34 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT2
#define _INTSPR_R35 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT3
#define _INTSPR_R36 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT4
#define _INTSPR_R37 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT5
#define _INTSPR_R38 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT6
#define _INTSPR_R39 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT7
#define _INTSPR_R40 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT8
#define _INTSPR_R41 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT9
#define _INTSPR_R42 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT10
#define _INTSPR_R43 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT11
#define _INTSPR_R44 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT12
#define _INTSPR_R45 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT13
#define _INTSPR_R46 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT14
#define _INTSPR_R47 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT15
#define _INTSPR_R48 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT16
#define _INTSPR_R49 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT17
#define _INTSPR_R50 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT18
#define _INTSPR_R51 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT19
#define _INTSPR_R52 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT20
#define _INTSPR_R53 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT21
#define _INTSPR_R54 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT22
#define _INTSPR_R55 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT23
#define _INTSPR_R56 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT24
#define _INTSPR_R57 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT25
#define _INTSPR_R58 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT26
#define _INTSPR_R59 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT27
#define _INTSPR_R60 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT28
#define _INTSPR_R61 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT29
#define _INTSPR_R62 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT30
#define _INTSPR_R63 (u_int32 *)(&(NVIC->IO_NVIC_ISPR32_63.reg)),BIT31

/* Pending Set Reg individually read */	/* API_INT_ABR_Read */
#define _INTABR_R00 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT0
#define _INTABR_R01 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT1
#define _INTABR_R02 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT2
#define _INTABR_R03 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT3
#define _INTABR_R04 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT4
#define _INTABR_R05 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT5
#define _INTABR_R06 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT6
#define _INTABR_R07 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT7
#define _INTABR_R08 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT8
#define _INTABR_R09 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT9
#define _INTABR_R10 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT10
#define _INTABR_R11 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT11
#define _INTABR_R12 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT12
#define _INTABR_R13 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT13
#define _INTABR_R14 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT14
#define _INTABR_R15 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT15
#define _INTABR_R16 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT16
#define _INTABR_R17 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT17
#define _INTABR_R18 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT18
#define _INTABR_R19 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT19
#define _INTABR_R20 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT20
#define _INTABR_R21 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT21
#define _INTABR_R22 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT22
#define _INTABR_R23 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT23
#define _INTABR_R24 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT24
#define _INTABR_R25 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT25
#define _INTABR_R26 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT26
#define _INTABR_R27 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT27
#define _INTABR_R28 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT28
#define _INTABR_R29 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT29
#define _INTABR_R30 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT30
#define _INTABR_R31 (u_int32 *)(&(NVIC->IO_NVIC_ABR00_31.reg)),BIT31

#define _INTABR_R32 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT0
#define _INTABR_R33 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT1
#define _INTABR_R34 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT2
#define _INTABR_R35 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT3
#define _INTABR_R36 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT4
#define _INTABR_R37 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT5
#define _INTABR_R38 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT6
#define _INTABR_R39 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT7
#define _INTABR_R40 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT8
#define _INTABR_R41 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT9
#define _INTABR_R42 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT10
#define _INTABR_R43 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT11
#define _INTABR_R44 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT12
#define _INTABR_R45 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT13
#define _INTABR_R46 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT14
#define _INTABR_R47 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT15
#define _INTABR_R48 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT16
#define _INTABR_R49 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT17
#define _INTABR_R50 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT18
#define _INTABR_R51 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT19
#define _INTABR_R52 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT20
#define _INTABR_R53 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT21
#define _INTABR_R54 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT22
#define _INTABR_R55 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT23
#define _INTABR_R56 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT24
#define _INTABR_R57 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT25
#define _INTABR_R58 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT26
#define _INTABR_R59 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT27
#define _INTABR_R60 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT28
#define _INTABR_R61 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT29
#define _INTABR_R62 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT30
#define _INTABR_R63 (u_int32 *)(&(NVIC->IO_NVIC_ABR32_63.reg)),BIT31

/* System Handler Priority Reg Set */	/* API_INT_SHPR_Set */
/* System Handler Priority Reg Read */	/* API_INT_SHPR_Read */
#define _CPUSHPR_04 (u_int8 *)(&(CG->IO_CPU_SHPR4_7.byte[0]))
#define _CPUSHPR_05 (u_int8 *)(&(CG->IO_CPU_SHPR4_7.byte[1]))
#define _CPUSHPR_06 (u_int8 *)(&(CG->IO_CPU_SHPR4_7.byte[2]))
#define _CPUSHPR_07 (u_int8 *)(&(CG->IO_CPU_SHPR4_7.byte[3]))
#define _CPUSHPR_08 (u_int8 *)(&(CG->IO_CPU_SHPR8_11.byte[0]))
#define _CPUSHPR_09 (u_int8 *)(&(CG->IO_CPU_SHPR8_11.byte[1]))
#define _CPUSHPR_10 (u_int8 *)(&(CG->IO_CPU_SHPR8_11.byte[2]))
#define _CPUSHPR_11 (u_int8 *)(&(CG->IO_CPU_SHPR8_11.byte[3]))
#define _CPUSHPR_12 (u_int8 *)(&(CG->IO_CPU_SHPR12_15.byte[0]))
#define _CPUSHPR_13 (u_int8 *)(&(CG->IO_CPU_SHPR12_15.byte[1]))
#define _CPUSHPR_14 (u_int8 *)(&(CG->IO_CPU_SHPR12_15.byte[2]))
#define _CPUSHPR_15 (u_int8 *)(&(CG->IO_CPU_SHPR12_15.byte[3]))



#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */




/**************************************************************/

/*---------------------- MCU(M330) INTERRUPT --------------------*/
void API_INT_Init(void);
void API_INT_ReqClr(u_int8 IntReqClr);
u_int8 API_INT_NMIRead(void);
void API_INT_RstflgClear(void);
u_int8 API_INT_RstflgRead(void);
void API_INT_ActSt_Set(u_int8 * addr,u_int8 stbyactst);
u_int8 API_INT_ActSt_Read(u_int8 * addr);
void API_INT_Enable(u_int8 * addr,u_int8 inten);

/*------------------------ Cortex-M3 NVIC -----------------------*/
void API_INT_SER_0_31_Set(u_int32 enaset0);
void API_INT_SER_32_63_Set(u_int32 enaset1);
void API_INT_SER_Set(u_int32 * addr,u_int32 bit);
void API_INT_CER_0_31_Set(u_int32 enaclr0);
void API_INT_CER_32_63_Set(u_int32 enaclr1);
void API_INT_CER_Set(u_int32 * addr,u_int32 bit);
u_int32 API_INT_SER_0_31_Read(void);
u_int32 API_INT_SER_32_63_Read(void);
u_int32 API_INT_SER_Read(u_int32 * addr,u_int32 bit);	//API_INT_SER_Read
void API_INT_SPR_0_31_Set(u_int32 pendset0);
void API_INT_SPR_32_63_Set(u_int32 pendset1);
void API_INT_SPR_Set(u_int32 * addr,u_int32 bit);
void API_INT_CPR_0_31_Set(u_int32 pendclr0);
void API_INT_CPR_32_63_Set(u_int32 pendclr1);
void API_INT_CPR_Set(u_int32 * addr,u_int32 bit);
u_int32 API_INT_SPR_0_31_Read(void);
u_int32 API_INT_SPR_32_63_Read(void);
u_int32 API_INT_SPR_Read(u_int32 * addr,u_int8 bit);	//API_INT_SPR_Read
u_int32 API_INT_ABR_0_31_Read(void);
u_int32 API_INT_ABR_32_63_Read(void);
u_int32 API_INT_ABR_Read(u_int32 * addr,u_int8 bit);		//API_INT_ABR_Read
void API_INT_PR4_Set(u_int8 fieldnum,u_int8 pri0,u_int8 pri1,u_int8 pri2,u_int8 pri3);
void API_INT_PR_Set(u_int8 intnum,u_int8 pri);
u_int32 API_INT_ID_Read(void);
void API_INT_ICSR_Set(u_int32 intctrlst);
u_int32 API_INT_ICSR_Read(void);
void API_INT_VTOR_Set(u_int32 vctoffset);
void API_INT_SHPR_Set(u_int8 * addr,u_int8 shpr);		//API_INT_SHPR_Set
u_int8 API_INT_SHPR_Read(u_int8 * addr);				//API_INT_SHPR_Read
void API_INT_SHC_Set(u_int32 syshandcntl);
u_int32 API_INT_SHC_Read(void);
void API_INT_PR_AllSet(u_int8 pri);	//API_INT_PR_AllSet
void API_INT_StsTickSet(u_int32 systickcntl);
u_int32 API_INT_SysTickRead(void);
void API_INT_SysTickR_Set(u_int32 systickrld);
u_int32 API_INT_SysTickR_Read(void);
void API_INT_SysTickC_Set(u_int32 systickcrt);
u_int32 API_INT_SysTickC_Read(void);
u_int32 API_INT_SysTickCVR_Read(void);


#endif /* avoid double definition */





