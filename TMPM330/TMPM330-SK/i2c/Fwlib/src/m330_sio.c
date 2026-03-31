/*******************************************************************************
* File Name 		 : m330_sio.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SIO liblary source
********************************************************************************/


#include "m330_sio.h"


/*******************************************************************************
* Function Name  : API_SIO_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_Init(SFR_SIOx_t * SioChSel)
{
	API_SIO_IP_Enable(SioChSel,ENABLE);

	/* Notes */
	/* In the state of SCxMOD0.5= 0, SCxMOD0, SCxMOD1, and SCxMOD2 are set.  */
	/* < TUR > bit is cleared to "0" when writing it in buffer register (SCxBUF).  */

	/* SIO Reg initialize */
	SioChSel->IO_SCxEN.reg = IO_SIO_EN_INIT;
//		SioChSel->IO_SCxBUF.reg = IO_SIO_BUF_INIT;
	SioChSel->IO_SCxCR.reg = IO_SIO_EN_INIT;
	SioChSel->IO_SCxMOD0.reg = IO_SIO_MOD0_INIT;
	SioChSel->IO_SCxBRCR.reg = IO_SIO_BRCR_INIT;
	SioChSel->IO_SCxBRADD.reg = IO_SIO_BRADD_INIT;
	SioChSel->IO_SCxMOD1.reg = IO_SIO_MOD1_INIT;
	SioChSel->IO_SCxMOD2.reg = IO_SIO_MOD2_INIT;
	SioChSel->IO_SCxRFC.reg = IO_SIO_RFC_INIT;
	SioChSel->IO_SCxTFC.reg = IO_SIO_TFC_INIT;
	SioChSel->IO_SCxRST.reg = IO_SIO_RST_INIT;
	SioChSel->IO_SCxTST.reg = IO_SIO_TST_INIT;
	SioChSel->IO_SCxFCNF.reg = IO_SIO_FCNF_INIT;

	API_SIO_IP_Enable(SioChSel,DISABLE);
}


/*******************************************************************************
* Function Name  : API_SIO_IP_Enable
* Description	 : 
* Input 		 : SCxEn<SIOE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_IP_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxEN.reg,BIT0) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_SndDataSet
* Description	 : 
* Input 		 : SCxBUF
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndDataSet(SFR_SIOx_t * SioChSel,u_int8 scbuf)
{
	SioChSel->IO_SCxBUF.reg = scbuf;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvDataRead
* Description	 : 
* Input 		 : 
* Output		 : SCxBUF
* Return		 : 
*******************************************************************************/
u_int8 API_SIO_RcvDataRead(SFR_SIOx_t * SioChSel)
{
	u_int8	RcvData;
	RcvData = SioChSel->IO_SCxBUF.reg;
	return RcvData;
}

/*******************************************************************************
* Function Name  : API_SIO_CR_Set
* Description	 : 
* Input 		 : SCxCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_CR_Set(SFR_SIOx_t * SioChSel,u_int8 sccr)
{
	SioChSel->IO_SCxCR.reg = sccr;
}

/*******************************************************************************
* Function Name  : API_SIO_MOD0_Set
* Description	 : 
* Input 		 : SCxMOD0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_MOD0_Set(SFR_SIOx_t * SioChSel,u_int8 scmod0)
{
	SioChSel->IO_SCxMOD0.reg = scmod0;
}

/*******************************************************************************
* Function Name  : API_SIO_MOD1_Set
* Description	 : 
* Input 		 : SCxMOD1
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_MOD1_Set(SFR_SIOx_t * SioChSel,u_int8 scmod1)
{
	SioChSel->IO_SCxMOD1.reg = scmod1;
}

/*******************************************************************************
* Function Name  : API_SIO_MOD2_Set
* Description	 : 
* Input 		 : SCxMOD2
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_MOD2_Set(SFR_SIOx_t * SioChSel,u_int8 scmod2)
{
	SioChSel->IO_SCxMOD2.reg = scmod2;
}

/*******************************************************************************
* Function Name  : API_SIO_MOD2_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_SIO_MOD2_Read(SFR_SIOx_t * SioChSel)
{
	u_int8	ScMod2;
	//ScMod2 = SioChSel->IO_SCxBUF.reg;
	ScMod2 = SioChSel->IO_SCxMOD2.reg;
	return ScMod2;
}

/*******************************************************************************
* Function Name  : API_SIO_FCNF_Set
* Description	 : 
* Input 		 : SCxFCNF
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_FCNF_Set(SFR_SIOx_t * SioChSel,u_int8 scfcnf)
{
	SioChSel->IO_SCxFCNF.reg = scfcnf;
}

/*******************************************************************************
* Function Name  : API_SIO_BR_Set
* Description	 : 
* Input 		 : SCxBRCR,SCxBRADD
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR_Set(SFR_SIOx_t * SioChSel,u_int8 scbrcr,u_int8 scbradd)
{
	SioChSel->IO_SCxBRCR.reg = scbrcr;
	SioChSel->IO_SCxBRADD.reg = scbradd;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvData_8_Read
* Description	 : 
* Input 		 : 
* Output		 : SCxCR<RB8>
* Return		 : 
*******************************************************************************/
u_int8 API_SIO_RcvData_8_Read(SFR_SIOx_t * SioChSel)
{
	u_int8	RcvDataBit8;
	RcvDataBit8 = BITBAND_IP(SioChSel->IO_SCxCR.reg,BIT7);
	return RcvDataBit8;
}

/*******************************************************************************
* Function Name  : API_SIO_ParityOddEvenSet
* Description	 : 
* Input 		 : SCxCR<EVEN>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_ParityOddEvenSet(SFR_SIOx_t * SioChSel,IpSIO_ParityOddEven ParityOddEven)
{
	BITBAND_IP(SioChSel->IO_SCxCR.reg,BIT6) = (u_int8)ParityOddEven;
}

/*******************************************************************************
* Function Name  : API_SIO_ParityEnable
* Description	 : 
* Input 		 : SCxCR<PE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_ParityEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxCR.reg,BIT5) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_ErrFlagReaf
* Description	 : 
* Input 		 : 
* Output		 : SCxCR<OERR>,<PERR>,<FERR>
* Return		 : 
*******************************************************************************/
u_int8 API_SIO_ErrFlagReaf(SFR_SIOx_t * SioChSel)
{
	u_int8	ErrFlag;
	ErrFlag = SioChSel->IO_SCxCR.reg;
	ErrFlag >>= SIO_ERRFLAG_SHIFT;
	ErrFlag &= IO_SIO_UI8BIT2_0_MASK;
	return ErrFlag;
}

/*******************************************************************************
* Function Name  : API_SIO_ClkEdgeSel
* Description	 : 
* Input 		 : SCxCR<SCLKS>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_ClkEdgeSel(SFR_SIOx_t * SioChSel,IpSIO_ClkEdge ClkEdge)
{
	BITBAND_IP(SioChSel->IO_SCxCR.reg,BIT1) = (u_int8)ClkEdge;
}

/*******************************************************************************
* Function Name  : API_SIO_ClkSel
* Description	 : 
* Input 		 : SCxCR<IOC>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_ClkSel(SFR_SIOx_t * SioChSel,IpSIO_ClkSel Clk)
{
	BITBAND_IP(SioChSel->IO_SCxCR.reg,BIT0) = (u_int8)Clk;
}

/*******************************************************************************
* Function Name  : API_SIO_SndData_8_Set
* Description	 : 
* Input 		 : SCxMOD0<TB8>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndData_8_Set(SFR_SIOx_t * SioChSel,IpSIO_SndDataBit8 SndDataBit8)
{
	BITBAND_IP(SioChSel->IO_SCxMOD0.reg,BIT7) = (u_int8)SndDataBit8;
}

/*******************************************************************************
* Function Name  : API_SIO_CTS_Enable
* Description	 : 
* Input 		 : SCxMOD0<CTSE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_CTS_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxMOD0.reg,BIT6) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvEnable
* Description	 : 
* Input 		 : SCxMOD0<RXE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxMOD0.reg,BIT5) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_WupEnable
* Description	 : 
* Input 		 : SCxMOD0<WU>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_WupEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxMOD0.reg,BIT4) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_IP_ModeSet
* Description	 : 
* Input 		 : SCxMOD0<SM1><SM0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_IP_ModeSet(SFR_SIOx_t * SioChSel,u_int8 Siomode)
{
	SioChSel->IO_SCxMOD0.reg &= IO_SIO_MODESET_MASK;
	SioChSel->IO_SCxMOD0.reg |= Siomode;
}

/*******************************************************************************
* Function Name  : API_SIO_IP_ClkSet
* Description	 : 
* Input 		 : SCxMOD0<SC1><SC0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_IP_ClkSet(SFR_SIOx_t * SioChSel,u_int8 Sioclk)
{
	SioChSel->IO_SCxMOD0.reg &= IO_SIO_CLKSET_MASK;
	SioChSel->IO_SCxMOD0.reg |= Sioclk;
}

/*******************************************************************************
* Function Name  : API_SIO_Idle
* Description	 : 
* Input 		 : SCxMOD1<IDLE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_Idle(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxMOD1.reg,BIT7) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_TrnModeSet
* Description	 : 
* Input 		 : SCxMOD1<FDPX1><FDPX0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_TrnModeSet(SFR_SIOx_t * SioChSel,u_int8 Transmode)
{
	SioChSel->IO_SCxMOD1.reg &= IO_SIO_TRANSMODE_MASK;
	SioChSel->IO_SCxMOD1.reg |= Transmode;
}

/*******************************************************************************
* Function Name  : API_SIO_SndEnable
* Description	 : 
* Input 		 : SCxMOD1<TXE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxMOD1.reg,BIT4) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_IntervalSet
* Description	 : 
* Input 		 : SCxMOD1<SINT2-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_IntervalSet(SFR_SIOx_t * SioChSel,u_int8 Interval)
{
	SioChSel->IO_SCxMOD1.reg &= IO_SIO_INTERVAL_MASK;
	SioChSel->IO_SCxMOD1.reg |= Interval;
}

/*******************************************************************************
* Function Name  : API_SIO_UartStopBit
* Description	 : 
* Input 		 : SCxMOD2<SBLEN>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_UartStopBit(SFR_SIOx_t * SioChSel,IpSIO_StopBitLen StopBitLen)
{
	BITBAND_IP(SioChSel->IO_SCxMOD2.reg,BIT4) = (u_int8)StopBitLen;
}

/*******************************************************************************
* Function Name  : API_SIO_LsbMsbSet
* Description	 : 
* Input 		 : SCxMOD2<DRCHG>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_LsbMsbSet(SFR_SIOx_t * SioChSel,IpSIO_LsbMsbSel LsbMsbSel)
{
	BITBAND_IP(SioChSel->IO_SCxMOD2.reg,BIT3) = (u_int8)LsbMsbSel;
}

/*******************************************************************************
* Function Name  : API_SIO_W_BufEnable
* Description	 : 
* Input 		 : SCxMOD2<WBUF>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_W_BufEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxMOD2.reg,BIT2) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_SoftReset
* Description	 : 
* Input 		 : SCxMOD2<SWRST1><SWRST0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SoftReset(SFR_SIOx_t * SioChSel)
{
	/* SoftReset */	/* 0y******10 ¨ 0y******01 */
	SioChSel->IO_SCxMOD2.reg = IO_SIO_SOFTRESET_10;
	SioChSel->IO_SCxMOD2.reg = IO_SIO_SOFTRESET_01;
}

/*******************************************************************************
* Function Name  : API_SIO_BR16_Enable
* Description	 : 
* Input 		 : SCxBRCR<BRxADDE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR16_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxBRCR.reg,BIT6) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_BR_ClkSet
* Description	 : 
* Input 		 : SCxBRCR<BRxCK1><BRxCK0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR_ClkSet(SFR_SIOx_t * SioChSel,u_int8 BR_Clk)
{
	SioChSel->IO_SCxBRCR.reg &= IO_SIO_BRCLK_MASK;
	SioChSel->IO_SCxBRCR.reg |= BR_Clk;
}

/*******************************************************************************
* Function Name  : API_SIO_BR_N_Set
* Description	 : 
* Input 		 : SCxBRCR<BRxS3-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR_N_Set(SFR_SIOx_t * SioChSel,u_int8 BR_N)
{
	SioChSel->IO_SCxBRCR.reg &= IO_SIO_BRN_MASK;
	SioChSel->IO_SCxBRCR.reg |= BR_N;
}

/*******************************************************************************
* Function Name  : API_SIO_BR16_K_Set
* Description	 : 
* Input 		 : SC0BRADD<BRxK3-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR16_K_Set(SFR_SIOx_t * SioChSel,u_int8 BR16_K)
{
	SioChSel->IO_SCxBRADD.reg &= IO_SIO_BR16K_MASK;
	SioChSel->IO_SCxBRADD.reg |= BR16_K;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvFIFO_ByteSet
* Description	 : 
* Input 		 : SCxFCNF<RFST>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvFIFO_ByteSet(SFR_SIOx_t * SioChSel,IpSIO_RcvFIFOByte RcvFIFOByte)
{
	BITBAND_IP(SioChSel->IO_SCxFCNF.reg,BIT4) = (u_int8)RcvFIFOByte;
}

/*******************************************************************************
* Function Name  : API_SIO_SndFIFO_IntEnable
* Description	 : 
* Input 		 : SCxFCNF<TFIE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndFIFO_IntEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxFCNF.reg,BIT3) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvFIFO_IntEnable
* Description	 : 
* Input 		 : SCxFCNF<RFIE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvFIFO_IntEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxFCNF.reg,BIT2) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_RXTX_CNT_Enable
* Description	 : 
* Input 		 : SCxFCNF<RXTXCNT>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RXTX_CNT_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxFCNF.reg,BIT1) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_FIFO_Enable
* Description	 : 
* Input 		 : SCxFCNF<CNFG>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_FIFO_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->IO_SCxFCNF.reg,BIT0) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvFIFO_Clear
* Description	 : 
* Input 		 : SCxRFC<RFCS>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvFIFO_Clear(SFR_SIOx_t * SioChSel)
{
	SioChSel->IO_SCxRFC.reg |= IO_SIO_RCVFIFO_CLEAR;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvIntFillSet
* Description	 : 
* Input 		 : SCxRFC<RFIS><RIL1><RIL0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvIntFillSet(SFR_SIOx_t * SioChSel,u_int8 RcvFIFOIntSel,u_int8 RcvFIFOFill)
{
	/* Receive FIFO Int Sel */
	BITBAND_IP(SioChSel->IO_SCxRFC.reg,BIT6) = (u_int8)RcvFIFOIntSel;
	/* Receive FIFO Fill Level */
	SioChSel->IO_SCxRFC.reg &= IO_SIO_RCVFFILL_MASK;
	SioChSel->IO_SCxRFC.reg |= RcvFIFOFill;
}

/*******************************************************************************
* Function Name  : API_SIO_SndFIFO_Clear
* Description	 : 
* Input 		 : SCxTFC<TFCS>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndFIFO_Clear(SFR_SIOx_t * SioChSel)
{
	SioChSel->IO_SCxTFC.reg |= IO_SIO_SNDFIFO_CLEAR;
}

/*******************************************************************************
* Function Name  : API_SIO_SndIntFillSet
* Description	 : 
* Input 		 : SCxTFC<TFIS><TIL1><TIL0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndIntFillSet(SFR_SIOx_t * SioChSel,u_int8 SndFIFOIntSel,u_int8 SndFIFOFill)
{
	/* Send FIFO Int Sel */
	BITBAND_IP(SioChSel->IO_SCxTFC.reg,BIT6) = (u_int8)SndFIFOIntSel;
	/* Send FIFO Fill Level */
	SioChSel->IO_SCxTFC.reg &= IO_SIO_SNDFFILL_MASK;
	SioChSel->IO_SCxTFC.reg |= SndFIFOFill;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvFIFO_Status
* Description	 : 
* Input 		 : SCxRST<ROR><RLVL2-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_SIO_RcvFIFO_Status(SFR_SIOx_t * SioChSel)
{
	u_int8	RcvFIFOSt;
	RcvFIFOSt = SioChSel->IO_SCxRST.reg;
	return RcvFIFOSt;
}

/*******************************************************************************
* Function Name  : API_SIO_SndFIFO_Status
* Description	 : 
* Input 		 : SCxTST<TUR><TLVL2-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_SIO_SndFIFO_Status(SFR_SIOx_t * SioChSel)
{
	u_int8	SndFIFOSt;
	SndFIFOSt = SioChSel->IO_SCxTST.reg;
	return SndFIFOSt;
}

/*******************************************************************************
* Function Name  : API_SIO_UART_SET
* Description	 : 
* Input 		 : SCxCR<EVEN>,SCxCR<PE>,SCxMOD0<CTSE>,SCxMOD2<SBLEN>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_UART_SET(SFR_SIOx_t * SioChSel,IpSIO_ParityOddEven ParityOddEven,IpFunctionState ParityEnable,IpFunctionState CTSEnable,IpSIO_StopBitLen StopBitLen)
{
	/* SCxCR<EVEN>,SCxCR<PE> */
	BITBAND_IP(SioChSel->IO_SCxCR.reg,BIT6) = (u_int8)ParityOddEven;
	BITBAND_IP(SioChSel->IO_SCxCR.reg,BIT5) = (u_int8)ParityEnable;

	/*	Please ..<.. set < RXE>= "1" at the end after setting each mode 	*/
	/* register (SC0MOD0,SC0MOD1,SC0MOD2) in the state of RXE>= "0". 		*/

	API_SIO_RcvEnable(SioChSel,DISABLE);
	/* SCxMOD0<CTSE>,SCxMOD2<SBLEN> */
	BITBAND_IP(SioChSel->IO_SCxMOD0.reg,BIT6) = (u_int8)CTSEnable;
	BITBAND_IP(SioChSel->IO_SCxMOD2.reg,BIT4) = (u_int8)StopBitLen;
	API_SIO_RcvEnable(SioChSel,ENABLE);
}



