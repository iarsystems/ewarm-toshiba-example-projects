/*******************************************************************************
* File Name 		 : m380_sio.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SIO library source
********************************************************************************/


#include "m380_sio.h"


/*******************************************************************************
* Function Name  : API_SIO_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_Init(SIOM * SioChSel)
{
	API_SIO_IP_Enable(SioChSel,ENABLE);

	/* Notes */
	/* In the state of SCxMOD0.5= 0, SCxMOD0, SCxMOD1, and SCxMOD2 are set.  */
	/* < TUR > bit is cleared to "0" when writing it in buffer register (SCxBUF).  */

	/* SIO Reg initialize */
	SioChSel->SCnEN = IO_SIO_EN_INIT;
//		SioChSel->SCnBUF = IO_SIO_BUF_INIT;
	SioChSel->SCnCR = IO_SIO_EN_INIT;
	SioChSel->SCnMOD0 = IO_SIO_MOD0_INIT;
	SioChSel->SCnBRCR = IO_SIO_BRCR_INIT;
	SioChSel->SCnBRADD = IO_SIO_BRADD_INIT;
	SioChSel->SCnMOD1 = IO_SIO_MOD1_INIT;
	SioChSel->SCnMOD2 = IO_SIO_MOD2_INIT;
	SioChSel->SCnRFC = IO_SIO_RFC_INIT;
	SioChSel->SCnTFC = IO_SIO_TFC_INIT;
	SioChSel->SCnRST = IO_SIO_RST_INIT;
	SioChSel->SCnTST = IO_SIO_TST_INIT;
	SioChSel->SCnFCNF = IO_SIO_FCNF_INIT;

	API_SIO_IP_Enable(SioChSel,DISABLE);
}


/*******************************************************************************
* Function Name  : API_SIO_IP_Enable
* Description	 : 
* Input 		 : SCxEn<SIOE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_IP_Enable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnEN,cBIT0) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_SndDataSet
* Description	 : 
* Input 		 : SCxBUF
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndDataSet(SIOM * SioChSel,uint8_t scbuf)
{
	SioChSel->SCnBUF = scbuf;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvDataRead
* Description	 : 
* Input 		 : 
* Output		 : SCxBUF
* Return		 : 
*******************************************************************************/
uint8_t API_SIO_RcvDataRead(SIOM * SioChSel)
{
	uint8_t	RcvData;
	RcvData = SioChSel->SCnBUF;
	return RcvData;
}

/*******************************************************************************
* Function Name  : API_SIO_CR_Set
* Description	 : 
* Input 		 : SCxCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_CR_Set(SIOM * SioChSel,uint8_t sccr)
{
	SioChSel->SCnCR = sccr;
}

/*******************************************************************************
* Function Name  : API_SIO_MOD0_Set
* Description	 : 
* Input 		 : SCxMOD0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_MOD0_Set(SIOM * SioChSel,uint8_t scmod0)
{
	SioChSel->SCnMOD0 = scmod0;
}

/*******************************************************************************
* Function Name  : API_SIO_MOD1_Set
* Description	 : 
* Input 		 : SCxMOD1
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_MOD1_Set(SIOM * SioChSel,uint8_t scmod1)
{
	SioChSel->SCnMOD1 = scmod1;
}

/*******************************************************************************
* Function Name  : API_SIO_MOD2_Set
* Description	 : 
* Input 		 : SCxMOD2
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_MOD2_Set(SIOM * SioChSel,uint8_t scmod2)
{
	SioChSel->SCnMOD2 = scmod2;
}

/*******************************************************************************
* Function Name  : API_SIO_MOD2_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
uint8_t API_SIO_MOD2_Read(SIOM * SioChSel)
{
	uint8_t	ScMod2;
	//ScMod2 = SioChSel->SCnBUF;
	ScMod2 = SioChSel->SCnMOD2;
	return ScMod2;
}

/*******************************************************************************
* Function Name  : API_SIO_FCNF_Set
* Description	 : 
* Input 		 : SCxFCNF
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_FCNF_Set(SIOM * SioChSel,uint8_t scfcnf)
{
	SioChSel->SCnFCNF = scfcnf;
}

/*******************************************************************************
* Function Name  : API_SIO_BR_Set
* Description	 : 
* Input 		 : SCxBRCR,SCxBRADD
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR_Set(SIOM * SioChSel,uint8_t scbrcr,uint8_t scbradd)
{
	SioChSel->SCnBRCR = scbrcr;
	SioChSel->SCnBRADD = scbradd;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvData_8_Read
* Description	 : 
* Input 		 : 
* Output		 : SCxCR<RB8>
* Return		 : 
*******************************************************************************/
uint8_t API_SIO_RcvData_8_Read(SIOM * SioChSel)
{
	uint8_t	RcvDataBit8;
	RcvDataBit8 = BITBAND_IP(SioChSel->SCnCR,cBIT7);
	return RcvDataBit8;
}

/*******************************************************************************
* Function Name  : API_SIO_ParityOddEvenSet
* Description	 : 
* Input 		 : SCxCR<EVEN>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_ParityOddEvenSet(SIOM * SioChSel,IpSIO_ParityOddEven ParityOddEven)
{
	BITBAND_IP(SioChSel->SCnCR,cBIT6) = (uint8_t)ParityOddEven;
}

/*******************************************************************************
* Function Name  : API_SIO_ParityEnable
* Description	 : 
* Input 		 : SCxCR<PE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_ParityEnable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnCR,cBIT5) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_ErrFlagReaf
* Description	 : 
* Input 		 : 
* Output		 : SCxCR<OERR>,<PERR>,<FERR>
* Return		 : 
*******************************************************************************/
uint8_t API_SIO_ErrFlagReaf(SIOM * SioChSel)
{
	uint8_t	ErrFlag;
	ErrFlag = SioChSel->SCnCR;
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
void API_SIO_ClkEdgeSel(SIOM * SioChSel,IpSIO_ClkEdge ClkEdge)
{
	BITBAND_IP(SioChSel->SCnCR,cBIT1) = (uint8_t)ClkEdge;
}

/*******************************************************************************
* Function Name  : API_SIO_ClkSel
* Description	 : 
* Input 		 : SCxCR<IOC>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_ClkSel(SIOM * SioChSel,IpSIO_ClkSel Clk)
{
	BITBAND_IP(SioChSel->SCnCR,cBIT0) = (uint8_t)Clk;
}

/*******************************************************************************
* Function Name  : API_SIO_SndData_8_Set
* Description	 : 
* Input 		 : SCxMOD0<TB8>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndData_8_Set(SIOM * SioChSel,IpSIO_SndDataBit8 SndDataBit8)
{
	BITBAND_IP(SioChSel->SCnMOD0,cBIT7) = (uint8_t)SndDataBit8;
}

/*******************************************************************************
* Function Name  : API_SIO_CTS_Enable
* Description	 : 
* Input 		 : SCxMOD0<CTSE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_CTS_Enable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnMOD0,cBIT6) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvEnable
* Description	 : 
* Input 		 : SCxMOD0<RXE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvEnable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnMOD0,cBIT5) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_WupEnable
* Description	 : 
* Input 		 : SCxMOD0<WU>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_WupEnable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnMOD0,cBIT4) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_IP_ModeSet
* Description	 : 
* Input 		 : SCxMOD0<SM1><SM0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_IP_ModeSet(SIOM * SioChSel,uint8_t Siomode)
{
	SioChSel->SCnMOD0 &= IO_SIO_MODESET_MASK;
	SioChSel->SCnMOD0 |= Siomode;
}

/*******************************************************************************
* Function Name  : API_SIO_IP_ClkSet
* Description	 : 
* Input 		 : SCxMOD0<SC1><SC0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_IP_ClkSet(SIOM * SioChSel,uint8_t Sioclk)
{
	SioChSel->SCnMOD0 &= IO_SIO_CLKSET_MASK;
	SioChSel->SCnMOD0 |= Sioclk;
}

/*******************************************************************************
* Function Name  : API_SIO_Idle
* Description	 : 
* Input 		 : SCxMOD1<IDLE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_Idle(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnMOD1,cBIT7) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_TrnModeSet
* Description	 : 
* Input 		 : SCxMOD1<FDPX1><FDPX0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_TrnModeSet(SIOM * SioChSel,uint8_t Transmode)
{
	SioChSel->SCnMOD1 &= IO_SIO_TRANSMODE_MASK;
	SioChSel->SCnMOD1 |= Transmode;
}

/*******************************************************************************
* Function Name  : API_SIO_SndEnable
* Description	 : 
* Input 		 : SCxMOD1<TXE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndEnable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnMOD1,cBIT4) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_IntervalSet
* Description	 : 
* Input 		 : SCxMOD1<SINT2-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_IntervalSet(SIOM * SioChSel,uint8_t Interval)
{
	SioChSel->SCnMOD1 &= IO_SIO_INTERVAL_MASK;
	SioChSel->SCnMOD1 |= Interval;
}

/*******************************************************************************
* Function Name  : API_SIO_UartStopBit
* Description	 : 
* Input 		 : SCxMOD2<SBLEN>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_UartStopBit(SIOM * SioChSel,IpSIO_StopBitLen StopBitLen)
{
	BITBAND_IP(SioChSel->SCnMOD2,cBIT4) = (uint8_t)StopBitLen;
}

/*******************************************************************************
* Function Name  : API_SIO_LsbMsbSet
* Description	 : 
* Input 		 : SCxMOD2<DRCHG>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_LsbMsbSet(SIOM * SioChSel,IpSIO_LsbMsbSel LsbMsbSel)
{
	BITBAND_IP(SioChSel->SCnMOD2,cBIT3) = (uint8_t)LsbMsbSel;
}

/*******************************************************************************
* Function Name  : API_SIO_W_BufEnable
* Description	 : 
* Input 		 : SCxMOD2<WBUF>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_W_BufEnable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnMOD2,cBIT2) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_SoftReset
* Description	 : 
* Input 		 : SCxMOD2<SWRST1><SWRST0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SoftReset(SIOM * SioChSel)
{
	/* SoftReset */	/* 0y******10 ¨ 0y******01 */
	SioChSel->SCnMOD2 = IO_SIO_SOFTRESET_10;
	SioChSel->SCnMOD2 = IO_SIO_SOFTRESET_01;
}

/*******************************************************************************
* Function Name  : API_SIO_BR16_Enable
* Description	 : 
* Input 		 : SCxBRCR<BRxADDE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR16_Enable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnBRCR,cBIT6) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_BR_ClkSet
* Description	 : 
* Input 		 : SCxBRCR<BRxCK1><BRxCK0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR_ClkSet(SIOM * SioChSel,uint8_t BR_Clk)
{
	SioChSel->SCnBRCR &= IO_SIO_BRCLK_MASK;
	SioChSel->SCnBRCR |= BR_Clk;
}

/*******************************************************************************
* Function Name  : API_SIO_BR_N_Set
* Description	 : 
* Input 		 : SCxBRCR<BRxS3-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR_N_Set(SIOM * SioChSel,uint8_t BR_N)
{
	SioChSel->SCnBRCR &= IO_SIO_BRN_MASK;
	SioChSel->SCnBRCR |= BR_N;
}

/*******************************************************************************
* Function Name  : API_SIO_BR16_K_Set
* Description	 : 
* Input 		 : SC0BRADD<BRxK3-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_BR16_K_Set(SIOM * SioChSel,uint8_t BR16_K)
{
	SioChSel->SCnBRADD &= IO_SIO_BR16K_MASK;
	SioChSel->SCnBRADD |= BR16_K;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvFIFO_ByteSet
* Description	 : 
* Input 		 : SCxFCNF<RFST>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvFIFO_ByteSet(SIOM * SioChSel,IpSIO_RcvFIFOByte RcvFIFOByte)
{
	BITBAND_IP(SioChSel->SCnFCNF,cBIT4) = (uint8_t)RcvFIFOByte;
}

/*******************************************************************************
* Function Name  : API_SIO_SndFIFO_IntEnable
* Description	 : 
* Input 		 : SCxFCNF<TFIE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndFIFO_IntEnable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnFCNF,cBIT3) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvFIFO_IntEnable
* Description	 : 
* Input 		 : SCxFCNF<RFIE>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvFIFO_IntEnable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnFCNF,cBIT2) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_RXTX_CNT_Enable
* Description	 : 
* Input 		 : SCxFCNF<RXTXCNT>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RXTX_CNT_Enable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnFCNF,cBIT1) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_FIFO_Enable
* Description	 : 
* Input 		 : SCxFCNF<CNFG>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_FIFO_Enable(SIOM * SioChSel,IpFunctionState NewState)
{
	BITBAND_IP(SioChSel->SCnFCNF,cBIT0) = (uint8_t)NewState;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvFIFO_Clear
* Description	 : 
* Input 		 : SCxRFC<RFCS>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvFIFO_Clear(SIOM * SioChSel)
{
	SioChSel->SCnRFC |= IO_SIO_RCVFIFO_CLEAR;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvIntFillSet
* Description	 : 
* Input 		 : SCxRFC<RFIS><RIL1><RIL0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_RcvIntFillSet(SIOM * SioChSel,uint8_t RcvFIFOIntSel,uint8_t RcvFIFOFill)
{
	/* Receive FIFO Int Sel */
	BITBAND_IP(SioChSel->SCnRFC,cBIT6) = (uint8_t)RcvFIFOIntSel;
	/* Receive FIFO Fill Level */
	SioChSel->SCnRFC &= IO_SIO_RCVFFILL_MASK;
	SioChSel->SCnRFC |= RcvFIFOFill;
}

/*******************************************************************************
* Function Name  : API_SIO_SndFIFO_Clear
* Description	 : 
* Input 		 : SCxTFC<TFCS>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndFIFO_Clear(SIOM * SioChSel)
{
	SioChSel->SCnTFC |= IO_SIO_SNDFIFO_CLEAR;
}

/*******************************************************************************
* Function Name  : API_SIO_SndIntFillSet
* Description	 : 
* Input 		 : SCxTFC<TFIS><TIL1><TIL0>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_SndIntFillSet(SIOM * SioChSel,uint8_t SndFIFOIntSel,uint8_t SndFIFOFill)
{
	/* Send FIFO Int Sel */
	BITBAND_IP(SioChSel->SCnTFC,cBIT6) = (uint8_t)SndFIFOIntSel;
	/* Send FIFO Fill Level */
	SioChSel->SCnTFC &= IO_SIO_SNDFFILL_MASK;
	SioChSel->SCnTFC |= SndFIFOFill;
}

/*******************************************************************************
* Function Name  : API_SIO_RcvFIFO_Status
* Description	 : 
* Input 		 : SCxRST<ROR><RLVL2-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
uint8_t API_SIO_RcvFIFO_Status(SIOM * SioChSel)
{
	uint8_t	RcvFIFOSt;
	RcvFIFOSt = SioChSel->SCnRST;
	return RcvFIFOSt;
}

/*******************************************************************************
* Function Name  : API_SIO_SndFIFO_Status
* Description	 : 
* Input 		 : SCxTST<TUR><TLVL2-0>
* Output		 : 
* Return		 : 
*******************************************************************************/
uint8_t API_SIO_SndFIFO_Status(SIOM * SioChSel)
{
	uint8_t	SndFIFOSt;
	SndFIFOSt = SioChSel->SCnTST;
	return SndFIFOSt;
}

/*******************************************************************************
* Function Name  : API_SIO_UART_SET
* Description	 : 
* Input 		 : SCxCR<EVEN>,SCxCR<PE>,SCxMOD0<CTSE>,SCxMOD2<SBLEN>
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_SIO_UART_SET(SIOM * SioChSel,IpSIO_ParityOddEven ParityOddEven,IpFunctionState ParityEnable,IpFunctionState CTSEnable,IpSIO_StopBitLen StopBitLen)
{
	/* SCxCR<EVEN>,SCxCR<PE> */
	BITBAND_IP(SioChSel->SCnCR,cBIT6) = (uint8_t)ParityOddEven;
	BITBAND_IP(SioChSel->SCnCR,cBIT5) = (uint8_t)ParityEnable;

	/*	Please ..<.. set < RXE>= "1" at the end after setting each mode 	*/
	/* register (SC0MOD0,SC0MOD1,SC0MOD2) in the state of RXE>= "0". 		*/

	API_SIO_RcvEnable(SioChSel,DISABLE);
	/* SCxMOD0<CTSE>,SCxMOD2<SBLEN> */
	BITBAND_IP(SioChSel->SCnMOD0,cBIT6) = (uint8_t)CTSEnable;
	BITBAND_IP(SioChSel->SCnMOD2,cBIT4) = (uint8_t)StopBitLen;
	API_SIO_RcvEnable(SioChSel,ENABLE);
}



