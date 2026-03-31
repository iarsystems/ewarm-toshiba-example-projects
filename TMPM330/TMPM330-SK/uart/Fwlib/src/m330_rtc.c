/*******************************************************************************
* File Name 		 : m330_rtc.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : RTC liblary source
********************************************************************************/


#include "m330_rtc.h"


/*******************************************************************************
* Function Name  : API_RTC_Init
* Description	 : 
* Input 		 : RESTR
* Output		 : IO_RTC_INIT(CLOCK,TIMER Reg Initialize)
* Return		 : 
*******************************************************************************/
void API_RTC_Init(void)
{
	RTC->IO_RESTR.reg = IO_RTC_INIT;	/* CLOCK,TIMER Reg Initialize */
}

/*******************************************************************************
* Function Name  : API_RTC_Set_ClkHMS
* Description	 : PAGE0(Clock) Select
* Input 		 : SECR,MINR,HOURR
* Output		 : secr,minr,hourr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_ClkHMS(u_int8 hourr,u_int8 minr,u_int8 secr)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
	RTC->IO_HOURR.reg = hourr;
	RTC->IO_MINR.reg = minr;
	RTC->IO_SECR.reg = secr;
}

/*******************************************************************************
* Function Name  : API_RTC_Set_AlmHM
* Description	 : PAGE1(Alarm) Select
* Input 		 : MINR,HOURR
* Output		 : minr,hourr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_AlmHM(u_int8 hourr,u_int8 minr)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE1);		/* PAGE1(Alarm) Select */
	RTC->IO_HOURR.reg = hourr;
	RTC->IO_MINR.reg = minr;
}

/*******************************************************************************
* Function Name  : API_RTC_Read_ClkHMS
* Description	 : PAGE0(Clock) Select
* Input 		 : 
* Output		 : SECR,MINR,HOURR
* Return		 : 
*******************************************************************************/
u_int32 API_RTC_Read_ClkHMS(void)
{
	u_int32		hourr;
	u_int32		minr;
	u_int32		secr;
	u_int32		HMSReadData = 0x00000000;

	API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
	hourr = (u_int32)(RTC->IO_HOURR.reg);
	minr = (u_int32)(RTC->IO_MINR.reg);
	secr = (u_int32)(RTC->IO_SECR.reg);
	HMSReadData = (u_int32)((hourr << 16) + (minr << 8) + secr);		/* clock minutes seconds */
	return HMSReadData;
}

/*******************************************************************************
* Function Name  : API_RTC_Read_AlmHM
* Description	 : PAGE1(Alarm) Select
* Input 		 : 
* Output		 : MINR,HOURR
* Return		 : 
*******************************************************************************/
u_int16 API_RTC_Read_AlmHM(void)
{
	u_int16		hourr;
	u_int16		minr;
	u_int16		AlmHMReadData = 0x0000;

	API_RTC_Set_PageSel(IP_RTC_PAGE1);		/* PAGE1(Alarm) Select */
	hourr = (u_int16)(RTC->IO_HOURR.reg);
	minr = (u_int16)(RTC->IO_MINR.reg);
	AlmHMReadData = (u_int16)((hourr << 8) + minr);			/* clock minutes  */
	return AlmHMReadData;
}

/*******************************************************************************
* Function Name  : API_RTC_Set_Sec
* Description	 : PAGE0(Clock) Select
* Input 		 : SECR
* Output		 : secr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_Sec(u_int8 secr)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
	RTC->IO_SECR.reg = secr;
}

/*******************************************************************************
* Function Name  : API_RTC_Set_Min
* Description	 : Page0/1 Select
* Input 		 : MINR
* Output		 : page,minr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_Min(u_int8 page,u_int8 minr)
{
	API_RTC_Set_PageSel(page);		/* PAGE0/1 Select */
	RTC->IO_MINR.reg = minr;
}

/*******************************************************************************
* Function Name  : API_RTC_Set_Hour
* Description	 : Page0/1 Select
* Input 		 : HOURR
* Output		 : page,hourr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_Hour(u_int8 page,u_int8 hourr)
{
	/* Set Hour */
	API_RTC_Set_PageSel(page);		/* PAGE0/1 Select */
	RTC->IO_HOURR.reg = hourr;
}

/*******************************************************************************
* Function Name  : API_RTC_Set_ClkYMDW
* Description	 : PAGE0(Clock) Select
* Input 		 : DAYR,DATER,MONTHR,YEARR
* Output		 : yearr,monthr,dater,dayr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_ClkYMDW(u_int8 yearr,u_int8 monthr,u_int8 dater,u_int8 dayr)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
	RTC->IO_YEARR.reg = yearr;			/* year	*/
	RTC->IO_MONTHR.reg = monthr;		/* month	*/
	RTC->IO_DATER.reg = dater;			/* day 	*/
	RTC->IO_DAYR.reg = dayr;			/* day of week	*/
}

/*******************************************************************************
* Function Name  : API_RTC_Set_AlmDW
* Description	 : PAGE1(Alarm) Select
* Input 		 : DAYR,DATER
* Output		 : dater,dayr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_AlmDW(u_int8 dater,u_int8 dayr)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE1);		/* PAGE1(Alarm) Select */
	RTC->IO_DATER.reg = dater;			/* day	*/
	RTC->IO_DAYR.reg = dayr;			/* day of week	*/
}

/*******************************************************************************
* Function Name  : API_RTC_Read_ClkYMDW
* Description	 : PAGE0(Clock) Select
* Input 		 : yearr,monthr,dater,dayr
* Output		 : DAYR,DATER,MONTHR,YEARR
* Return		 : 
*******************************************************************************/
u_int32 API_RTC_Read_ClkYMDW(void)
{
	u_int32		yearr;		/* year	*/
	u_int32		monthr;		/* month	*/
	u_int32		dater;		/* day 	*/
	u_int32		dayr;		/* day of week	*/
	u_int32		YMDWReadData = 0x00000000;

	API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
	yearr = (u_int32)(RTC->IO_YEARR.reg);
	monthr = (u_int32)(RTC->IO_MONTHR.reg);
	dater = (u_int32)(RTC->IO_DATER.reg);
	dayr = (u_int32)(RTC->IO_DAYR.reg);
	YMDWReadData = (u_int32)((yearr << 24) + (monthr << 16) + (dater << 8) + dayr);	/* year month day,day of week */
	return YMDWReadData;
}

/*******************************************************************************
* Function Name  : API_RTC_Read_AlmDW
* Description	 : PAGE1(Alarm) Select
* Input 		 : dater,dayr
* Output		 : DAYR,DATER
* Return		 : 
*******************************************************************************/
u_int16 API_RTC_Read_AlmDW(void)
{
	u_int16		dater;		/* day	*/
	u_int16		dayr;		/* day of week	*/
	u_int16		AlmDWReadData = 0x0000;

	API_RTC_Set_PageSel(IP_RTC_PAGE1);		/* PAGE1(Alarm) Select */
	dater = (u_int16)(RTC->IO_DATER.reg);
	dayr = (u_int16)(RTC->IO_DAYR.reg);
	AlmDWReadData = (u_int16)((dater << 8) + dayr);			/* day,day of week */
	return AlmDWReadData;
}

/*******************************************************************************
* Function Name  : API_RTC_Set_Week
* Description	 : PAGE0/1 Select
* Input 		 : DAYR
* Output		 : dayr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_Week(u_int8 page,u_int8 dayr)
{
	API_RTC_Set_PageSel(page);		/* PAGE0/1 Select */
	RTC->IO_DAYR.reg = dayr;			/* day of week	*/
}

/*******************************************************************************
* Function Name  : API_RTC_Set_Day
* Description	 : PAGE0/1 Select
* Input 		 : DATER
* Output		 : dater(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_Day(u_int8 page,u_int8 dater)
{
	API_RTC_Set_PageSel(page);		/* PAGE0/1 Select */
	RTC->IO_DATER.reg = dater;			/* day	*/
}

/*******************************************************************************
* Function Name  : API_RTC_Set_Month
* Description	 : PAGE0(Clock) Select
* Input 		 : MONTHR
* Output		 : monthr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_Month(u_int8 monthr)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
	RTC->IO_MONTHR.reg = monthr;		/* month	*/
}

/*******************************************************************************
* Function Name  : API_RTC_Set_Year
* Description	 : PAGE0(Clock) Select
* Input 		 : YEARR
* Output		 : yearr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_Year(u_int8 yearr)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
	RTC->IO_YEARR.reg = yearr;			/* year	*/
}

/*******************************************************************************
* Function Name  : API_RTC_Set_24_12_mode
* Description	 : PAGE1(Alarm) Select
* Input 		 : MONTHR<MO0>
* Output		 : hourmode(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_24_12_mode(u_int8 hourmode)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE1);		/* PAGE1(Alarm) Select */
	BITBAND_IP(RTC->IO_MONTHR.reg,BIT0) = hourmode;		/* 24/12 hours clock  */
}

/*******************************************************************************
* Function Name  : API_RTC_Set_LeapYear
* Description	 : PAGE1(Alarm) Select
* Input 		 : YEARR
* Output		 : leapyear(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_LeapYear(u_int8 leapyear)
{
	API_RTC_Set_PageSel(IP_RTC_PAGE1);		/* PAGE1(Alarm) Select */
	RTC->IO_YEARR.reg = leapyear;			/* Leap year */
}

/*******************************************************************************
* Function Name  : API_RTC_Set_PAGER
* Description	 : PAGE0/1
* Input 		 : PAGER
* Output		 : pager(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_PAGER(u_int8 pager)
{
	RTC->IO_PAGER.reg = pager;
}

/*******************************************************************************
* Function Name  : API_RTC_Set_IntRTC
* Description	 : PAGE0/1
* Input 		 : PAGER.7<INTENA>
* Output		 : IntRtc(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_IntRTC(u_int8 IntRtc)
{
	u_int8		pager_buff;	
	pager_buff = RTC->IO_PAGER.reg;
	pager_buff |= IntRtc;
	RTC->IO_PAGER.reg = pager_buff;
}

//	void API_RTC_Set_IntRTC(IpFunctionState NewState)
//	{
//		BITBAND_IP(RTC->IO_PAGER.reg,BIT7) = (u_int8)NewState;
//	}

/*******************************************************************************
* Function Name  : API_RTC_Set_SecAdjust
* Description	 : PAGE0(Clock) Select
* Input 		 : PAGER.4<ADJUST>
* Output		 : SecAdjust(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_SecAdjust(void)
{
	u_int8		pager_buff;	
	API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
	pager_buff = RTC->IO_PAGER.reg;
	pager_buff |= IP_RTC_SECADJUST;
	RTC->IO_PAGER.reg = pager_buff;
}

//	void API_RTC_Set_SecAdjust(void)
//	{
//		API_RTC_Set_PageSel(IP_RTC_PAGE0);		/* PAGE0(Clock) Select */
//		RTC->IO_PAGER.reg |= IP_RTC_SECADJUST;
//	}

/*******************************************************************************
* Function Name  : API_RTC_Set_ClkEnaDis
* Description	 : Page0/1
* Input 		 : PAGER.3<ENATMR>
* Output		 : ClkEnable(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_ClkEnaDis(u_int8 ClkEnable)
{
	u_int8		pager_buff;	
	pager_buff = RTC->IO_PAGER.reg;
	pager_buff |= ClkEnable;
	RTC->IO_PAGER.reg = pager_buff;
}

//	void API_RTC_Set_ClkEnaDis(IpFunctionState NewState)
//	{
//		BITBAND_IP(RTC->IO_PAGER.reg,BIT3) = (u_int8)NewState;
//	}

/*******************************************************************************
* Function Name  : API_RTC_Set_AlmEnaDis
* Description	 : Page0/1
* Input 		 : PAGER.2<ENAALM>
* Output		 : AlmEnable(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_AlmEnaDis(u_int8 AlmEnable)
{
	u_int8		pager_buff;	
	pager_buff = RTC->IO_PAGER.reg;
	pager_buff |= AlmEnable;
	RTC->IO_PAGER.reg = pager_buff;
}

//	void API_RTC_Set_AlmEnaDis(IpFunctionState NewState)
//	{
//		BITBAND_IP(RTC->IO_PAGER.reg,BIT2) = (u_int8)NewState;
//	}
/*******************************************************************************
* Function Name  : API_RTC_Set_PageSel
* Description	 : Page0/1
* Input 		 : PAGER.0<PAGE>
* Output		 : Page(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_PageSel(u_int8 Page)
{
	u_int8		pager_buff;	
	pager_buff = RTC->IO_PAGER.reg;
	pager_buff |= Page;
	RTC->IO_PAGER.reg = pager_buff;
}

//	void API_RTC_Set_PageSel(u_int8 page)
//	{
//		BITBAND_IP(RTC->IO_PAGER.reg,BIT0) = page;
//	}
/*******************************************************************************
* Function Name  : API_RTC_Set_RESTR
* Description	 : Page0/1
* Input 		 : RESTR
* Output		 : restr(setting data)
* Return		 : 
*******************************************************************************/
void API_RTC_Set_RESTR(u_int8 restr)
{
	RTC->IO_RESTR.reg = restr;
}

