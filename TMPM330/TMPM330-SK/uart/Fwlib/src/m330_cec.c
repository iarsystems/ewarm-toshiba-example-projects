/*******************************************************************************
* File Name 		 : m330_cec.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : cec liblary source
********************************************************************************/


#include "m330_cec.h"


/*******************************************************************************
* Function Name  : API_CEC_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_Init(void)
{
	API_CEC_IP_Enable(ENABLE);
	API_CEC_SoftReset();
	API_CEC_IP_Enable(DISABLE);
}



/*******************************************************************************
* Function Name  : API_CEC_SoftReset
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_SoftReset(void)
{
	BITBAND_IP(CEC->IO_CECRESET.reg,BIT0) = 0x01;
}

/*******************************************************************************
* Function Name  : API_CEC_IP_Enable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_IP_Enable(IpFunctionState NewState)
{
//	assert_param(IP_FUNCTION_STATUS(NewState));


	BITBAND_IP(CEC->IO_CECEN.reg,BIT0) = (u_int8)NewState;

}

/*******************************************************************************
* Function Name  : API_CEC_Idle
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_Idle(IpFunctionState NewState)
{
//	assert_param(IP_FUNCTION_STATUS(NewState));

	BITBAND_IP(CEC->IO_CECEN.reg,BIT1) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_CEC_IntEnable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_IntEnable(void)
{
}

/*******************************************************************************
* Function Name  : API_CEC_RcvEnable
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_RcvEnable(IpFunctionState NewState)
{
//	assert_param(IP_FUNCTION_STATUS(NewState));

	BITBAND_IP(CEC->IO_CECREN.reg,BIT0) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_CEC_RcvStatus
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_CEC_RcvStatus(void)
{
	u_int8	rcv_status;
	
	rcv_status = BITBAND_IP(CEC->IO_CECREN.reg,BIT0);

	return rcv_status;
}

/*******************************************************************************
* Function Name  : API_CEC_RcvRegInit
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_RcvRegInit(void)
{
	CEC->IO_CECRCR1.reg = IO_CEC_CECRCR1_Init;
	CEC->IO_CECRCR2.reg = IO_CEC_CECRCR2_Init;
	CEC->IO_CECRCR3.reg = IO_CEC_CECRCR3_Init;
}

/*******************************************************************************
* Function Name  : API_CEC_SndRegInit
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_SndRegInit(void)
{
	CEC->IO_CECTCR.reg = IO_CEC_CECTCR_Init;
}

/*******************************************************************************
* Function Name  : API_CEC_RcvRegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_RcvRegSet(u_int32 cecrcr1,u_int16 cecrcr2,u_int32 cecrcr3)
{
	CEC->IO_CECRCR1.reg = cecrcr1;
	CEC->IO_CECRCR2.reg = cecrcr2;
	CEC->IO_CECRCR3.reg = cecrcr3;
}

/*******************************************************************************
* Function Name  : API_CEC_SndRegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_SndRegSet(u_int32 cectcr)
{
	CEC->IO_CECTCR.reg = cectcr;
}

/*******************************************************************************
* Function Name  : API_CEC_LogAdrSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_LogAdrSet(u_int16 LogAdr)
{
	CEC->IO_CECADD.reg = LogAdr;
}

/*******************************************************************************
* Function Name  : API_CEC_RcvDataRead
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int16 API_CEC_RcvDataRead(void)
{
	u_int16	receive_data;

	receive_data = CEC->IO_CECRBUF.reg;

	return receive_data;

}

/*******************************************************************************
* Function Name  : API_CEC_AckRespons
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_AckRespons(IpCEC_AckRespons AckRespons)
{
//	assert_param(IP_CEC_ACK_RESPONS(AckRespons));

	BITBAND_IP(CEC->IO_CECRCR1.reg,BIT24) = (u_int8)AckRespons;

}

/*******************************************************************************
* Function Name  : API_CEC_RcvErrIntHold
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_RcvErrIntHold(IpCEC_HoldState HoldState)
{
//	assert_param(IP_CEC_ERR_HOLD_STATUS(HoldState));

	BITBAND_IP(CEC->IO_CECRCR1.reg,BIT1) = (u_int8)HoldState;

}

/*******************************************************************************
* Function Name  : API_CEC_RcvSnoop
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_RcvSnoop(IpCEC_SnoopState SnoopState)
{
//	assert_param(IP_CEC_SNOOP_STATUS(SnoopState));

	BITBAND_IP(CEC->IO_CECRCR1.reg,BIT0) = (u_int8)SnoopState;
}

/*******************************************************************************
* Function Name  : API_CEC_WebErrDet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_WebErrDet(IpFunctionState NewState)
{
//	assert_param(IP_FUNCTION_STATUS(NewState));

	BITBAND_IP(CEC->IO_CECRCR3.reg,BIT0) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_CEC_SndStart
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_SndStart(IpFunctionState NewState)
{
//	assert_param(IP_FUNCTION_STATUS(NewState));

	BITBAND_IP(CEC->IO_CECTEN.reg,BIT0) = (u_int8)NewState;
}

/*******************************************************************************
* Function Name  : API_CEC_SndStatus
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_CEC_SndStatus(void)
{
	u_int8	send_status;
	
	send_status = BITBAND_IP(CEC->IO_CECTEN.reg,BIT0);

	return send_status;
}

/*******************************************************************************
* Function Name  : API_CEC_SndDataSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_SndDataSet(u_int16 SendData)
{
	CEC->IO_CECTBUF.reg = SendData;
}

/*******************************************************************************
* Function Name  : API_CEC_SndBroadcast
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_SndBroadcast(IpCEC_BroadcastState BroadcastState)
{
//	assert_param(IP_CEC_BROADCAST_STATUS(BroadcastState));

	BITBAND_IP(CEC->IO_CECTCR.reg,BIT4) = (u_int8)BroadcastState;
}

/*******************************************************************************
* Function Name  : API_CEC_BusFree
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CEC_BusFree(u_int8 BusFree)
{

	CEC->IO_CECTCR.reg &= IO_CEC_BUS_MASK;
	CEC->IO_CECTCR.byte[0] |= BusFree;
}

/*******************************************************************************
* Function Name  : API_CEC_RcvIntStatus
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_CEC_RcvIntStatus(void)
{
	u_int8	RcvIntStatus;
	
	RcvIntStatus = CEC->IO_CECRSTAT.reg;

	return RcvIntStatus;
}

/*******************************************************************************
* Function Name  : API_CEC_SndIntStatus
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_CEC_SndIntStatus(void)
{
	u_int8	SndIntStatus;
	
	SndIntStatus = CEC->IO_CECTSTAT.reg;

	return SndIntStatus;
}





