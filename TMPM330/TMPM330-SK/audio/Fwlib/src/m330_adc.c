/*******************************************************************************
* File Name 		 : m330_adc.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : ADC liblary source
********************************************************************************/


#include "m330_adc.h"


/*******************************************************************************
* Function Name  : API_ADC_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_Init(void)
{
	/* ADC Reg Initialize */
	ADC->IO_ADCLK.reg = IO_ADC_CLK_INIT;
	ADC->IO_ADMOD0.reg = IO_ADC_MOD0_INIT;
	ADC->IO_ADMOD1.reg = IO_ADC_MOD1_INIT;
	ADC->IO_ADMOD2.reg = IO_ADC_MOD2_INIT;
	ADC->IO_ADMOD3.reg = IO_ADC_MOD3_INIT;
	ADC->IO_ADMOD4.reg = IO_ADC_MOD4_INIT;
	ADC->IO_ADMOD5.reg = IO_ADC_MOD5_INIT;
	ADC->IO_ADREG08.reg = IO_ADC_REG08_INIT;
	ADC->IO_ADREG19.reg = IO_ADC_REG19_INIT;
	ADC->IO_ADREG2A.reg = IO_ADC_REG2A_INIT;
	ADC->IO_ADREG3B.reg = IO_ADC_REG3B_INIT;
	ADC->IO_ADREG4C.reg = IO_ADC_REG4C_INIT;
	ADC->IO_ADREG5D.reg = IO_ADC_REG5D_INIT;
	ADC->IO_ADREG6E.reg = IO_ADC_REG6E_INIT;
	ADC->IO_ADREG7F.reg = IO_ADC_REG7F_INIT;
	ADC->IO_ADREGSP.reg = IO_ADC_REGSP_INIT;
	ADC->IO_ADCMPREG0.reg = IO_ADC_CMPREG0_INIT;
	ADC->IO_ADCMPREG1.reg = IO_ADC_CMPREG1_INIT;

	/* Isn't there problem though it corresponds with SoftReset? */
//		API_ADC_SoftReset();

}

/*******************************************************************************
* Function Name  : API_ADC_MOD0_Read
* Description	 : 
* Input 		 : 
* Output		 : ADMOD0
* Return		 : 
*******************************************************************************/
u_int8 API_ADC_MOD0_Read(void)
{
	u_int8	ADMode0;
	ADMode0 = ADC->IO_ADMOD0.reg;
	return ADMode0;
}

/*******************************************************************************
* Function Name  : API_ADC_MOD0_Set
* Description	 : 
* Input 		 : ADMOD0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_MOD0_Set(u_int8 admod0)
{
	ADC->IO_ADMOD0.reg = admod0;
}

/*******************************************************************************
* Function Name  : API_ADC_IrptmodeSet
* Description	 : 
* Input 		 : ADMOD0<D4-D3>/<ITM1><ITM0>
* Output		 : IntRptMode(setting data)
* Return		 : 
*******************************************************************************/
void API_ADC_IrptmodeSet(u_int8 IntRptMode)
{
	ADC->IO_ADMOD0.reg &= IO_ADC_INTRPTMODE_MASK;
	ADC->IO_ADMOD0.reg |= IntRptMode;
}

/*******************************************************************************
* Function Name  : API_ADC_RptmodeSet
* Description	 : 
* Input 		 : ADMOD0<D2>/<REPEAT>
* Output		 : RptMode(setting data)
* Return		 : 
*******************************************************************************/
void API_ADC_RptmodeSet(IpADC_RptMode RptMode)
{
	BITBAND_IP(ADC->IO_ADMOD0.reg,BIT2) = (u_int8)RptMode;
}

/*******************************************************************************
* Function Name  : API_ADC_ScnmodeSet
* Description	 : 
* Input 		 : ADMOD0<D1>/<SCAN>
* Output		 : ScnMode(setting data)
* Return		 : 
*******************************************************************************/
void API_ADC_ScnmodeSet(IpADC_ScnMode ScnMode)
{
	BITBAND_IP(ADC->IO_ADMOD0.reg,BIT1) = (u_int8)ScnMode;
}

/*******************************************************************************
* Function Name  : API_ADC_Start_Set
* Description	 : Please write "1" in ADMOD0<ADS > bit after waiting for 3É s of
*				 :  an internal standard voltage steady after writing "1" in 
*				 :  without fail < VREFON>bit when you start the analog to digi
*				 :  tal translation. 
* Input 		 : ADMOD0<D0>/<ADS>
* Output		 : IO_ADC_START(setting data)
* Return		 : 
*******************************************************************************/
void API_ADC_Start_Set(void)
{
	ADC->IO_ADMOD0.reg |= IO_ADC_START;
}

/*******************************************************************************
* Function Name  : API_ADC_Start
* Description	 : 
* Input 		 : ADMOD0<D0>/<ADS>,ADMOD1<D7>/<VREFON>
* Output		 : 
* Return		 : 
*******************************************************************************/
//	***	To correspond with API_ADC_VrefSet, API_ADC_Start_Set this API is deleted. ***//
//	void API_ADC_Start(void)
//	{
//		u_int8	i;
//		BITBAND_IP(ADC->IO_ADMOD1.reg,BIT7) = ENABLE;
//		/* An internal standard voltage is necessary when using it and 3us waiting until stabilizing is necessary. */
//		for(i = IO_ADC_WAIT3US; i != 0; --i);			/* 3us WAIT */
//		ADC->IO_ADMOD0.reg |= IO_ADC_START;
//	}

/*******************************************************************************
* Function Name  : API_ADC_MOD1_Set
* Description	 : 
* Input 		 : ADMOD1
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_MOD1_Set(u_int8 admod1)
{
	ADC->IO_ADMOD1.reg = admod1;
}

/*******************************************************************************
* Function Name  : API_ADC_VrefSet
* Description	 : Please write "1" in ADMOD0<ADS > bit after waiting for 3É s 
*				 : of an internal standard voltage steady after writing "1" in 
*				 : without fail < VREFON>bit when you start the analog to digital 
*				 : translation. 
* Input 		 : ADMOD1<D7>/<VREFON>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_VrefSet(IpFunctionState NewState)
{
	BITBAND_IP(ADC->IO_ADMOD1.reg,BIT7) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_ADC_Idle
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_Idle(IpFunctionState NewState)
{
	BITBAND_IP(ADC->IO_ADMOD1.reg,BIT6) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_ADC_ChScnmodeSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_ChScnmodeSet(IpADC_ChScnmode ChScnmode)
{
	BITBAND_IP(ADC->IO_ADMOD1.reg,BIT5) = (u_int8)ChScnmode;
}

/*******************************************************************************
* Function Name  : API_ADC_ChSet
* Description	 : 
* Input 		 : ADMOD1<D3-D0>/<ADCH3-ADCH0>
* Output		 : ADCh(setting data)
* Return		 : 
*******************************************************************************/
void API_ADC_ChSet(u_int8 ADCh)
{
	ADC->IO_ADMOD1.reg &= IO_ADC_CHSET_MASK;
	ADC->IO_ADMOD1.reg |= ADCh;
}

/*******************************************************************************
* Function Name  : API_ADC_MOD2_Read
* Description	 : 
* Input 		 : 
* Output		 : ADMOD2
* Return		 : 
*******************************************************************************/
u_int8 API_ADC_MOD2_Read(void)
{
	u_int8	ADMode2;
	ADMode2 = ADC->IO_ADMOD2.reg;
	return ADMode2;
}

/*******************************************************************************
* Function Name  : API_ADC_MOD2_Set
* Description	 : 
* Input 		 : ADMOD2
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_MOD2_Set(u_int8 admod2)
{
	ADC->IO_ADMOD2.reg = admod2;
}

/*******************************************************************************
* Function Name  : API_ADC_hpEnable
* Description	 : 
* Input 		 : ADMOD2<D5>/<HPADCE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_hpEnable(void)
{
	ADC->IO_ADMOD2.reg |= IO_ADC_HPADC_ENABLE;
}

/*******************************************************************************
* Function Name  : API_ADC_ChhpSet
* Description	 : 
* Input 		 : ADMOD2<D3-D0>/<HPADCH3-HPADCH0>
* Output		 : ADHPCh(setting data)
* Return		 : 
*******************************************************************************/
void API_ADC_ChhpSet(u_int8 ADHPCh)
{
	ADC->IO_ADMOD2.reg &= IO_ADC_HPCHSET_MASK;
	ADC->IO_ADMOD2.reg |= ADHPCh;
}

/*******************************************************************************
* Function Name  : API_ADC_MOD3_Set
* Description	 : 
* Input 		 : ADMOD3
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_MOD3_Set(u_int8 admod3)
{
	ADC->IO_ADMOD3.reg = admod3;
}

/*******************************************************************************
* Function Name  : API_ADC_ObsvInt0_Set
* Description	 : 
* Input 		 : ADMOD3<D5>/<ADOBIC>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_ObsvInt0_Set(IpADC_ObsvInt0 ObsvInt0)
{
	BITBAND_IP(ADC->IO_ADMOD3.reg,BIT5) = (u_int8)ObsvInt0;
}

/*******************************************************************************
* Function Name  : API_ADC_ObsvRegi0_Sel
* Description	 : 
* Input 		 : ADMOD3<D4-D1>/<REGS3-REGS0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_ObsvRegi0_Sel(u_int8 ObsvReg0Sel)
{
	ADC->IO_ADMOD3.reg &= IO_ADC_OBSVREG_MASK;
	ADC->IO_ADMOD3.reg |= ObsvReg0Sel;
}

/*******************************************************************************
* Function Name  : API_ADC_ObsvInt0_Enable
* Description	 : 
* Input 		 : ADMOD3<D0>/<ADOBSV>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_ObsvInt0_Enable(IpFunctionState NewState)
{
	BITBAND_IP(ADC->IO_ADMOD3.reg,BIT0) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_ADC_MOD4_Set
* Description	 : 
* Input 		 : ADMOD4
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_MOD4_Set(u_int8 admod4)
{
	ADC->IO_ADMOD4.reg = admod4;
}

/*******************************************************************************
* Function Name  : API_ADC_HWshpEnable
* Description	 : 
* Input 		 : ADMOD4<D6>/<HADHTG>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_HWshpEnable(IpFunctionState NewState)
{
	BITBAND_IP(ADC->IO_ADMOD4.reg,BIT6) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_ADC_HWsnorEnable
* Description	 : 
* Input 		 : ADMOD4<D4>/<ADHTG>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_HWsnorEnable(IpFunctionState NewState)
{
	BITBAND_IP(ADC->IO_ADMOD4.reg,BIT4) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_ADC_SoftReset
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_SoftReset(void)
{
	/* SoftReset */	/* 0y******10 Å® 0y******01 */
	ADC->IO_ADMOD4.reg = IO_ADC_SOFTRESET_10;
	ADC->IO_ADMOD4.reg = IO_ADC_SOFTRESET_01;
}

/*******************************************************************************
* Function Name  : API_ADC_ObsvInt1_Set
* Description	 : 
* Input 		 : ADMOD5<D5>/<ADOBIC>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_ObsvInt1_Set(IpADC_ObsvInt1 ObsvInt1)
{
	BITBAND_IP(ADC->IO_ADMOD5.reg,BIT5) = (u_int8)ObsvInt1;
}

/*******************************************************************************
* Function Name  : API_ADC_ObsvRegi1_Sel
* Description	 : 
* Input 		 : ADMOD5<D4-D1>/<REGS3-REGS0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_ObsvRegi1_Sel(u_int8 ObsvReg1Sel)
{
	ADC->IO_ADMOD5.reg &= IO_ADC_OBSVREG_MASK;
	ADC->IO_ADMOD5.reg |= ObsvReg1Sel;
}

/*******************************************************************************
* Function Name  : API_ADC_ObsvInt1_Enable
* Description	 : 
* Input 		 : ADMOD5<D0>/<ADOBSV>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_ObsvInt1_Enable(IpFunctionState NewState)
{
	BITBAND_IP(ADC->IO_ADMOD5.reg,BIT0) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_ADC_DataRead
* Description	 : 
* Input 		 : addr(ADC REG)
* Output		 : ADREG08,ADREG19,ADREG2A,ADREG3B,ADREG4C,
* 				 : ADREG5D,ADREG6E,ADREG7F,ADREGSP
* Return		 : 
*******************************************************************************/
u_int16 API_ADC_DataRead(u_int8 * addrh, u_int8 * addrl)
{
	u_int16		ADData0 = 0;
	u_int16		ADData1 = 0;
	u_int16		ADData;
	/* Please previously read the high rank, and, next, read the subordinate position to the conversion result register.  */
	ADData1 = (u_int16)(* addrh);			/* ADC->IO_ADREG**.byte[1] */
	ADData0 = (u_int16)(* addrl);			/* ADC->IO_ADREG**.byte[0] */
	if(ADData0 & 0x0001)
	{
		ADData = (u_int16)( (ADData0 >>6) | (ADData1 << 2) );
		return ADData;
	}
	else 
		return 0;
}

//	u_int16 API_ADC_DataRead(u_int8 * addr)
//	{
//		u_int16		ADData0 = 0;
//		u_int16		ADData1 = 0;
//		u_int16		ADData;
//		/* Please previously read the high rank, and, next, read the subordinate position to the conversion result register.  */
//		ADData1 = (u_int16)(* addr);				/* ADC->IO_ADREG**.byte[1] */
//		ADData0 = (u_int16)(* (addr--));			/* ADC->IO_ADREG**.byte[0] */
//		ADData = (u_int16)( ADData0 || ADData1 << 8 );
//		return ADData;
//	}

/*******************************************************************************
* Function Name  : API_ADC_CMP0_Set
* Description	 : 
* Input 		 : ADCMP0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_CMP0_Set(u_int16 adcmp0)
{
	ADC->IO_ADCMPREG0.reg = adcmp0;
}

/*******************************************************************************
* Function Name  : API_ADC_CMP1_Set
* Description	 : 
* Input 		 : ADCMP1
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_CMP1_Set(u_int16 adcmp1)
{
	ADC->IO_ADCMPREG1.reg = adcmp1;
}

/*******************************************************************************
* Function Name  : API_ADC_CLK_Set
* Description	 : 
* Input 		 : ADCLK
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_ADC_CLK_Set(u_int8 adclk)
{
	ADC->IO_ADCLK.reg = adclk;
}

/*******************************************************************************
* Function Name  : API_ADC_TSH_Set
* Description	 : 
* Input 		 : ADCLK<D7-D4>/<TSH3-TSH0>
* Output		 : SmpHldTm(setting data)
* Return		 : 
*******************************************************************************/
void API_ADC_TSH_Set(u_int8 SmpHldTm)
{
	ADC->IO_ADCLK.reg &= IO_ADC_TSH_MASK;
	ADC->IO_ADCLK.reg |= SmpHldTm;
}

/*******************************************************************************
* Function Name  : API_ADC_ADCLK_Set
* Description	 : 
* Input 		 : ADCLK<D2-D0>/<ADCLK2-ADCLK0>
* Output		 : AdClk(setting data)
* Return		 : 
*******************************************************************************/
void API_ADC_ADCLK_Set(u_int8 AdClk)
{
	ADC->IO_ADCLK.reg &= IO_ADC_CLK_MASK;
	ADC->IO_ADCLK.reg |= AdClk;
}



