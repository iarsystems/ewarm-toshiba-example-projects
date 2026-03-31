/*******************************************************************************
* File Name 		 : m330_sbi.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SBI liblary source
********************************************************************************/


#include "m330_sbi.h"


/*******************************************************************************
* Function Name  : API_SBI_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBI_Init(SFR_SBIx_t * SbiChSel)
{
	API_SBI_IP_Enable(SbiChSel,ENABLE);			/* SBI Enable */

	/* SBI(I2C)mode initialize */
	SbiChSel->IO_SBIxCR0.reg = IO_SBI_CR0_INIT;
	SbiChSel->IO_SBIxCR1.reg = IO_SBI_CR1_I2C_INIT;
	SbiChSel->IO_SBIxDBR.reg = IO_SBI_DBR_I2C_INIT;
	SbiChSel->IO_SBIxI2CAR.reg = IO_SBI_I2CAR_INIT;
	SbiChSel->IO_SBIxCR2.reg = IO_SBI_CR2_I2C_INIT;
	SbiChSel->IO_SBIxBR0.reg = IO_SBI_BR0_I2C_INIT;

	API_SBI_IP_Enable(SbiChSel,DISABLE);		/* SBI Disable */
}

/*******************************************************************************
* Function Name  : API_SBI_IP_Enable
* Description	 : 
* Input 		 : SBIxCR0<SIBEN>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBI_IP_Enable(SFR_SBIx_t * SbiChSel,IpFunctionState NewState)
{
	BITBAND_IP(SbiChSel->IO_SBIxCR0.reg,BIT7) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SBI_SndDataSet
* Description	 : 
* Input 		 : SBIxDBR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBI_SndDataSet(SFR_SBIx_t * SbiChSel,u_int8 sbidbr)
{
	SbiChSel->IO_SBIxDBR.reg = sbidbr;
}

/*******************************************************************************
* Function Name  : API_SBI_RcvDataRead
* Description	 : 
* Input 		 : 
* Output		 : SBIxDBR
* Return		 : 
*******************************************************************************/
u_int8 API_SBI_RcvDataRead(SFR_SBIx_t * SbiChSel)
{
	u_int8	RcvDBRData;
	RcvDBRData = SbiChSel->IO_SBIxDBR.reg;
	return RcvDBRData;
}

/*******************************************************************************
* Function Name  : API_SBI_ModeSet
* Description	 : 
* Input 		 : SBIxCR2<SBIM1><SBIM0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBI_ModeSet(SFR_SBIx_t * SbiChSel,u_int8 Sbimode)
{
	SbiChSel->IO_SBIxCR2.reg &= IO_SBI_MODESET_MASK;
	SbiChSel->IO_SBIxCR2.reg |= Sbimode;
}

/*******************************************************************************
* Function Name  : API_SBI_Idle
* Description	 : 
* Input 		 : SBIxBR0<I2CSBI0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBI_Idle(SFR_SBIx_t * SbiChSel,IpFunctionState NewState)
{
	BITBAND_IP(SbiChSel->IO_SBIxBR0.reg,BIT6) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SBI_StatusRead
* Description	 : 
* Input 		 : 
* Output		 : readŽž SBIxSR(writeŽž SBIxCR2)
* Return		 : 
*******************************************************************************/
u_int8 API_SBI_StatusRead(SFR_SBIx_t * SbiChSel)
{
	u_int8	SbiStatus;
	SbiStatus = SbiChSel->IO_SBIxSR.reg;
	return SbiStatus;
}

/*******************************************************************************
* Function Name  : API_SBI_CR1_Set
* Description	 : 
* Input 		 : SBIxCR1
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBI_CR1_Set(SFR_SBIx_t * SbiChSel,u_int8 sbicr1)
{
	SbiChSel->IO_SBIxCR1.reg = sbicr1;
}

/*******************************************************************************
* Function Name  : API_SBI_CR2_Set
* Description	 : 
* Input 		 : writeŽž SBIxCR2(readŽž SBIxSR)
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBI_CR2_Set(SFR_SBIx_t * SbiChSel,u_int8 sbicr2)
{
	SbiChSel->IO_SBIxCR2.reg = sbicr2;
}

/*******************************************************************************
* Function Name  : API_SBIi_SoftResetStatusRead
* Description	 : I2CBUS Mode Only
* Input 		 : SBIxCR1<SWRMON>
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_SBIi_SoftResetStatusRead(SFR_SBIx_t * SbiChSel)
{
	u_int8	SoftResetStatus;
	SoftResetStatus = BITBAND_IP(SbiChSel->IO_SBIxCR1.reg,BIT0);
	return SoftResetStatus;
}

/*******************************************************************************
* Function Name  : API_SBIi_SlvAddressSet
* Description	 : I2CBUS Mode Only
* Input 		 : IO_SBIxI2CAR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBIi_SlvAddressSet(SFR_SBIx_t * SbiChSel,u_int8 sbii2car)
{
	SbiChSel->IO_SBIxI2CAR.reg = sbii2car;
}

/*******************************************************************************
* Function Name  : API_SBIs_TrnStartStop
* Description	 : SIO Mode Only
* Input 		 : SBIxCR1<SIOS>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBIs_TrnStartStop(SFR_SBIx_t * SbiChSel,IpFunctionState NewState)
{
	BITBAND_IP(SbiChSel->IO_SBIxCR1.reg,BIT7) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SBIs_ForceStop
* Description	 : SIO Mode Only
* Input 		 : SBIxCR1<SIOINH>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SBIs_ForceStop(SFR_SBIx_t * SbiChSel,IpFunctionState NewState)
{
	BITBAND_IP(SbiChSel->IO_SBIxCR1.reg,BIT6) = (u_int8)NewState;
}



