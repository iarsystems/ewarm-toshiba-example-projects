/*******************************************************************************
* File Name 		 : m330_adc.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : ADC header
********************************************************************************/

/* avoid double definition */
#ifndef __M330_ADC_H
#define __M330_ADC_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* ADC initial data */
#define IO_ADC_CLK_INIT				((u_int8)0x80)
#define IO_ADC_MOD0_INIT			((u_int8)0x00)
#define IO_ADC_MOD1_INIT			((u_int8)0x00)
#define IO_ADC_MOD2_INIT			((u_int8)0x00)
#define IO_ADC_MOD3_INIT			((u_int8)0x00)
#define IO_ADC_MOD4_INIT			((u_int8)0x00)
#define IO_ADC_MOD5_INIT			((u_int8)0x00)
#define IO_ADC_REG08_INIT			((u_int16)0x003C)
#define IO_ADC_REG19_INIT			((u_int16)0x003C)
#define IO_ADC_REG2A_INIT			((u_int16)0x003C)
#define IO_ADC_REG3B_INIT			((u_int16)0x003C)
#define IO_ADC_REG4C_INIT			((u_int16)0x003C)
#define IO_ADC_REG5D_INIT			((u_int16)0x003C)
#define IO_ADC_REG6E_INIT			((u_int16)0x003C)
#define IO_ADC_REG7F_INIT			((u_int16)0x003C)
#define IO_ADC_REGSP_INIT			((u_int16)0x003C)
#define IO_ADC_CMPREG0_INIT			((u_int16)0x0000)
#define IO_ADC_CMPREG1_INIT			((u_int16)0x0000)


#define IO_ADC_INTRPTMODE_MASK		((u_int8)0xE7)		/* ADC INT Repeat Mode mask */
#define IO_ADC_CHSET_MASK			((u_int8)0xF0)		/* ADC Ch Set mask */
#define IO_ADC_HPCHSET_MASK			((u_int8)0xF0)		/* ADC HP Ch Set mask */
#define IO_ADC_OBSVREG_MASK			((u_int8)0xE1)		/* ADC Obsv Reg0 mask, ADC Obsv Reg1 mask */
#define IO_ADC_TSH_MASK				((u_int8)0x0F)		/* ADC Sample Hold Time mask */
#define IO_ADC_CLK_MASK				((u_int8)0xF8)		/* ADC Clock mask */

typedef enum { ADC_SINGLE_MODE = 0, ADC_REPEAT_MODE = 1 }			IpADC_RptMode;		/* API_ADC_RptmodeSet	*/
typedef enum { ADC_CHSTATIC_MODE = 0, ADC_CHSCAN_MODE = 1 }			IpADC_ScnMode;		/* API_ADC_ScnmodeSet	*/
typedef enum { ADC_SCAN4CH = 0, ADC_SCAN8CH = 1 }					IpADC_ChScnmode;	/* API_ADC_ChScnmodeSet	*/
typedef enum { ADC_OBINT0_REG_LOW = 0, ADC_OBINT0_REG_HIGH = 1 }	IpADC_ObsvInt0;		/* API_ADC_ObsvInt0_Set	*/
typedef enum { ADC_OBINT1_REG_LOW = 0, ADC_OBINT1_REG_HIGH = 1 }	IpADC_ObsvInt1;		/* API_ADC_ObsvInt1_Set	*/

/* ADC START */						/* API_ADC_Start_Set */
#define IO_ADC_START			((u_int8)0x01)
#define IO_ADC_WAIT3US			(u_int8)120			// (120us[@0.025us]) External Clock 40MHz
/* ADC Start of top priority conversion */			/* API_ADC_hpEnable */
#define IO_ADC_HPADC_ENABLE		((u_int8)0x20)
/* ADC Soft Reset */			/* API_ADC_SoftReset */
#define IO_ADC_SOFTRESET_10		((u_int8)0x02)
#define IO_ADC_SOFTRESET_01		((u_int8)0x01)


/* ADC REG  */	/* API_ADC_DataRead */
#define _ADCREG08	(u_int8 *)(&(ADC->IO_ADREG08.byte[1])),(u_int8 *)(&(ADC->IO_ADREG08.byte[0]))
#define _ADCREG19	(u_int8 *)(&(ADC->IO_ADREG19.byte[1])),(u_int8 *)(&(ADC->IO_ADREG19.byte[0]))
#define _ADCREG2A	(u_int8 *)(&(ADC->IO_ADREG2A.byte[1])),(u_int8 *)(&(ADC->IO_ADREG2A.byte[0]))
#define _ADCREG3B	(u_int8 *)(&(ADC->IO_ADREG3B.byte[1])),(u_int8 *)(&(ADC->IO_ADREG3B.byte[0]))
#define _ADCREG4C	(u_int8 *)(&(ADC->IO_ADREG4C.byte[1])),(u_int8 *)(&(ADC->IO_ADREG4C.byte[0]))
#define _ADCREG5D	(u_int8 *)(&(ADC->IO_ADREG5D.byte[1])),(u_int8 *)(&(ADC->IO_ADREG5D.byte[0]))
#define _ADCREG6E	(u_int8 *)(&(ADC->IO_ADREG6E.byte[1])),(u_int8 *)(&(ADC->IO_ADREG6E.byte[0]))
#define _ADCREG7F	(u_int8 *)(&(ADC->IO_ADREG7F.byte[1])),(u_int8 *)(&(ADC->IO_ADREG7F.byte[0]))
#define _ADCREGSP	(u_int8 *)(&(ADC->IO_ADREGSP.byte[1])),(u_int8 *)(&(ADC->IO_ADREGSP.byte[0]))

//	#define _ADCREG08	(u_int8 *)(&(ADC->IO_ADREG08.byte[1]))
//	#define _ADCREG19	(u_int8 *)(&(ADC->IO_ADREG19.byte[1]))
//	#define _ADCREG2A	(u_int8 *)(&(ADC->IO_ADREG2A.byte[1]))
//	#define _ADCREG3B	(u_int8 *)(&(ADC->IO_ADREG3B.byte[1]))
//	#define _ADCREG4C	(u_int8 *)(&(ADC->IO_ADREG4C.byte[1]))
//	#define _ADCREG5D	(u_int8 *)(&(ADC->IO_ADREG5D.byte[1]))
//	#define _ADCREG6E	(u_int8 *)(&(ADC->IO_ADREG6E.byte[1]))
//	#define _ADCREG7F	(u_int8 *)(&(ADC->IO_ADREG7F.byte[1]))
//	#define _ADCREGSP	(u_int8 *)(&(ADC->IO_ADREGSP.byte[1]))


#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */

	/* ADMOD0<D4-D3>/<ITM1><ITM0> */			/* API_ADC_IrptmodeSet */
#define IO_ADC_INTRPTMODE_CNV1		0x00		/* Interrupt generation whenever converting it 1 time */
#define IO_ADC_INTRPTMODE_CNV4		0x08		/* Interrupt generation whenever converting it 4 times */
#define IO_ADC_INTRPTMODE_CNV8		0x10		/* Interrupt generation whenever converting it 8 times */

	/* ADMOD1<D3-D0>/<ADCH3-ADCH0> */			/* API_ADC_ChSet */
	/* Channel fixation mode				ADMOD0.1<SCAN> = 0 */
#define IO_ADC_AN0		0x00				/* AN0		 */
#define IO_ADC_AN1		0x01				/* AN1		 */
#define IO_ADC_AN2		0x02				/* AN2		 */
#define IO_ADC_AN3		0x03				/* AN3		 */
#define IO_ADC_AN4		0x04				/* AN4		 */
#define IO_ADC_AN5		0x05				/* AN5		 */
#define IO_ADC_AN6		0x06				/* AN6		 */
#define IO_ADC_AN7		0x07				/* AN7		 */
#define IO_ADC_AN8		0x08				/* AN8		 */
#define IO_ADC_AN9		0x09				/* AN9		 */
#define IO_ADC_AN10		0x0A				/* AN10		 */
#define IO_ADC_AN11		0x0B				/* AN11		 */
	/* Channel scanning mode(4ch)		ADMOD0.1<SCAN>,ADMOD1.5<ADSCN> = 1,0 */
#define IO_ADC_AN0		0x00				/* AN0		 */
#define IO_ADC_AN0_1	0x01				/* AN0-AN1	 */
#define IO_ADC_AN0_2	0x02				/* AN0-AN2	 */
#define IO_ADC_AN0_3	0x03				/* AN0-AN3	 */
#define IO_ADC_AN4		0x04				/* AN4		 */
#define IO_ADC_AN4_5	0x05				/* AN4-AN5	 */
#define IO_ADC_AN4_6	0x06				/* AN4-AN6	 */
#define IO_ADC_AN4_7	0x07				/* AN4-AN7	 */
#define IO_ADC_AN8		0x08				/* AN8		 */
#define IO_ADC_AN8_9	0x09				/* AN8-AN9	 */
#define IO_ADC_AN8_10	0x0A				/* AN8-AN10	 */
#define IO_ADC_AN8_11	0x0B				/* AN8-AN11	 */
	/* Channel scanning mode(8ch)		ADMOD0.1<SCAN>,ADMOD1.5<ADSCN> = 1,1 */
#define IO_ADC_AN0		0x00				/* AN0		 */
#define IO_ADC_AN0_1	0x01				/* AN0-AN1	 */
#define IO_ADC_AN0_2	0x02				/* AN0-AN2	 */
#define IO_ADC_AN0_3	0x03				/* AN0-AN3	 */
#define IO_ADC_AN0_4	0x04				/* AN0-AN4	 */
#define IO_ADC_AN0_5	0x05				/* AN0-AN5	 */
#define IO_ADC_AN0_6	0x06				/* AN0-AN6	 */
#define IO_ADC_AN0_7	0x07				/* AN0-AN7	 */
#define IO_ADC_AN8		0x08				/* AN8		 */
#define IO_ADC_AN8_9	0x09				/* AN8-AN9	 */
#define IO_ADC_AN8_10	0x0A				/* AN8-AN10	 */
#define IO_ADC_AN8_11	0x0B				/* AN8-AN11	 */

	/* ADMOD2<D3-D0>/<HPADCH3-HPADCH0> */			/* API_ADC_ChhpSet */
	/* Analog input channel when top priority converting it		*/
#define IO_ADC_HP_AN0	0x00				/* HP AN0	 */
#define IO_ADC_HP_AN1	0x01				/* HP AN1	 */
#define IO_ADC_HP_AN2	0x02				/* HP AN2	 */
#define IO_ADC_HP_AN3	0x03				/* HP AN3	 */
#define IO_ADC_HP_AN4	0x04				/* HP AN4	 */
#define IO_ADC_HP_AN5	0x05				/* HP AN5	 */
#define IO_ADC_HP_AN6	0x06				/* HP AN6	 */
#define IO_ADC_HP_AN7	0x07				/* HP AN7	 */
#define IO_ADC_HP_AN8	0x08				/* HP AN8	 */
#define IO_ADC_HP_AN9	0x09				/* HP AN9	 */
#define IO_ADC_HP_AN10	0x0A				/* HP AN10	 */
#define IO_ADC_HP_AN11	0x0B				/* HP AN11	 */

	/* ADMOD3<D4-D1>/<REGS3-REGS0> */			/* API_ADC_ObsvRegi0_Sel */
	/* ADMOD5<D4-D1>/<REGS3-REGS0> */			/* API_ADC_ObsvRegi1_Sel */
	/* Compared analog to digital translation storage registers */
#define IO_ADC_REG_ADREG08		0x00		/* ADREG08	 */
#define IO_ADC_REG_ADREG19		0x02		/* ADREG19	 */
#define IO_ADC_REG_ADREG2A		0x04		/* ADREG2A	 */
#define IO_ADC_REG_ADREG3B		0x06		/* ADREG3B	 */
#define IO_ADC_REG_ADREG4C		0x08		/* ADREG4C	 */
#define IO_ADC_REG_ADREG5D		0x0A		/* ADREG5D	 */
#define IO_ADC_REG_ADREG6E		0x0C		/* ADREG6E	 */
#define IO_ADC_REG_ADREG7F		0x0E		/* ADREG7F	 */
#define IO_ADC_REG_ADREGSP		0x10		/* ADREGSP	 */

	/* ADCLK<D7-D4>/<TSH3-TSH0> */			/* API_ADC_TSH_Set */
	/* Selection at AD sample holding time */
#define IO_ADC_TSH_8		0x80			/* 8 Conversion Clock	 */
#define IO_ADC_TSH_16		0x90			/* 16 Conversion Clock	 */
#define IO_ADC_TSH_24		0xA0			/* 24 Conversion Clock	 */
#define IO_ADC_TSH_32		0xB0			/* 32 Conversion Clock	 */
#define IO_ADC_TSH_64		0x30			/* 64 Conversion Clock	 */
#define IO_ADC_TSH_128		0xC0			/* 128 Conversion Clock	 */
#define IO_ADC_TSH_512		0xD0			/* 512 Conversion Clock	 */

	/* ADCLK<D2-D0>/<ADCLK2-ADCLK0> */		/* API_ADC_ADCLK_Set */
	/* [AD Purisuke-ra] output selection */
#define IO_ADC_FC			0x00			/* fc		*/
#define IO_ADC_FC_2			0x01			/* fc/2	 	*/
#define IO_ADC_FC_4			0x02			/* fc/4	 	*/
#define IO_ADC_FC_8			0x03			/* fc/8	 	*/
#define IO_ADC_FC_16		0x04			/* fc/16	*/



/**************************************************************/

void API_ADC_Init(void);
u_int8 API_ADC_MOD0_Read(void);
void API_ADC_MOD0_Set(u_int8 admod0);
void API_ADC_IrptmodeSet(u_int8 IntRptMode);
void API_ADC_RptmodeSet(IpADC_RptMode RptMode);
void API_ADC_ScnmodeSet(IpADC_ScnMode ScnMode);
void API_ADC_Start_Set(void);
//	void API_ADC_Start(void);
void API_ADC_MOD1_Set(u_int8 admod1);
void API_ADC_VrefSet(IpFunctionState NewState);
void API_ADC_Idle(IpFunctionState NewState);
void API_ADC_ChScnmodeSet(IpADC_ChScnmode ChScnmode);
void API_ADC_ChSet(u_int8 ADCh);
u_int8 API_ADC_MOD2_Read(void);
void API_ADC_MOD2_Set(u_int8 admod2);
void API_ADC_hpEnable(void);
void API_ADC_ChhpSet(u_int8 ADHPCh);
void API_ADC_MOD3_Set(u_int8 admod3);
void API_ADC_ObsvInt0_Set(IpADC_ObsvInt0 ObsvInt0);
void API_ADC_ObsvRegi0_Sel(u_int8 ObsvReg0Sel);
void API_ADC_ObsvInt0_Enable(IpFunctionState NewState);
void API_ADC_MOD4_Set(u_int8 admod4);
void API_ADC_HWshpEnable(IpFunctionState NewState);
void API_ADC_HWsnorEnable(IpFunctionState NewState);
void API_ADC_SoftReset(void);
void API_ADC_ObsvInt1_Set(IpADC_ObsvInt1 ObsvInt1);
void API_ADC_ObsvRegi1_Sel(u_int8 ObsvReg1Sel);
void API_ADC_ObsvInt1_Enable(IpFunctionState NewState);
//	u_int16 API_ADC_DataRead(u_int8 * addr);
u_int16 API_ADC_DataRead(u_int8 * addrh, u_int8 * addrl);
void API_ADC_CMP0_Set(u_int16 adcmp0);
void API_ADC_CMP1_Set(u_int16 adcmp1);
void API_ADC_CLK_Set(u_int8 adclk);
void API_ADC_TSH_Set(u_int8 SmpHldTm);
void API_ADC_ADCLK_Set(u_int8 AdClk);

#endif /* avoid double definition */





