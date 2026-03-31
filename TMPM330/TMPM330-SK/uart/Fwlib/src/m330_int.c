/*******************************************************************************
* File Name 		 : m330_int.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : INTERRUPT liblary source
********************************************************************************/


#include "m330_int.h"


/*------------------------ MCU(M330) INTERRUPT -----------------------*/


/*******************************************************************************
* Function Name  : API_INT_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_Init(void)
{
/*----- MCU(M330) INTERRUPT INITIALIZE -----*/
	CG->IO_ICRCG.reg = IO_CG_ICRCG_Init;
	CG->IO_NMIFLG.reg = IO_CG_NMIFLG_Init;
	CG->IO_RSTFLG.reg = IO_CG_RSTFLG_Init;
	CG->IO_IMCGA.reg = IO_CG_IMCGA_Init;
	CG->IO_IMCGB.reg = IO_CG_IMCGB_Init;
	CG->IO_IMCGC.reg = IO_CG_IMCGC_Init;
	CG->IO_IMCGD.reg = IO_CG_IMCGD_Init;

/*----- Cortex-M3 NVIC INITIALIZE -----*/
/* Set-Enable Reg */
/* Clear-Enable Reg */
/* Set-Pending Reg */
/* Clear-Pending Reg */
/* Active-Bit Reg */

/* Priority Register */
	API_INT_PR_AllSet(IO_NVIC_INTPR_Init);	/* Priority Register ALL INITIALIZE */
/* CPUID Base register */
/* Interrupt Control State register */
	CPU->IO_CPU_ICSR.reg = IO_CPU_ICSR_Init;
/* Vector Table Offset Register */
	CPU->IO_CPU_VTOR.reg = IO_CPU_VTOR_Init;
/* System Handler Priority Register */
	CPU->IO_CPU_SHPR4_7.reg = IO_CPU_SHPR_Init;
	CPU->IO_CPU_SHPR8_11.reg = IO_CPU_SHPR_Init;
	CPU->IO_CPU_SHPR12_15.reg = IO_CPU_SHPR_Init;
/* System Handler Control Register */
	CPU->IO_CPU_SHCSR.reg = IO_CPU_SHCSR_Init;
/* Systick Control Type Register */
	SYSTICK->IO_NVIC_CTL.reg = IO_SYSTICK_CTL_Init;
/* Systick Reload Value Register */
/* Systick Current Value Register */
}

/*******************************************************************************
* Function Name  : API_INT_ReqClr
* Description	 : 
* Input 		 : ICRCG.4-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_ReqClr(u_int8 IntReqClr)
{
	IntReqClr &= IO_INT_REQCLR_MASK;
	CG->IO_ICRCG.byte[0] = IntReqClr;
}

/*******************************************************************************
* Function Name  : API_INT_NMIRead
* Description	 : 
* Input 		 : 
* Output		 : NMIFLG.1-0
* Return		 : 
*******************************************************************************/
u_int8 API_INT_NMIRead(void)
{
	u_int8	NMIFlg;
	NMIFlg = CG->IO_NMIFLG.reg;
	return NMIFlg;
}

/*******************************************************************************
* Function Name  : API_INT_RstflgClear
* Description	 : 
* Input 		 : RSTFLG.4,2-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_RstflgClear(void)
{
	CG->IO_RSTFLG.reg = 0x00;
}

/*******************************************************************************
* Function Name  : API_INT_RstflgRead
* Description	 : 
* Input 		 : 
* Output		 : RSTFLG.4,2-0
* Return		 : 
*******************************************************************************/
u_int8 API_INT_RstflgRead(void)
{
	u_int8	RstFlg;
	RstFlg = CG->IO_RSTFLG.reg;
	return RstFlg;
}

/*******************************************************************************
* Function Name  : API_INT_ActSt_Set
* Description	 : _INT**_STS
* Input 		 : Interrupt Standby Active State set data
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_ActSt_Set(u_int8 * addr,u_int8 stbyactst)
{
	(* addr) = (u_int8)stbyactst;
}

/*******************************************************************************
* Function Name  : API_INT_ActSt_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_INT_ActSt_Read(u_int8 * addr)
{
	u_int8	StbyActSt;
	StbyActSt = (u_int8)(* addr);
	StbyActSt >>= CG_STS_SHIFT;
	StbyActSt &= CG_UI8BIT2_0_MASK;
	return StbyActSt;
}

/*******************************************************************************
* Function Name  : API_INT_Enable
* Description	 : 
* Input 		 : _INT**_EN
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_Enable(u_int8 * addr,u_int8 inten)
{
	(* addr) &= CG_INTEN_MASK;
	(* addr) |= (u_int8)inten;
}



/*------------------------ Cortex-M3 NVIC -----------------------*/



/*******************************************************************************
* Function Name  : API_INT_SER_0_31_Set
* Description	 : 
* Input 		 : Enable Set Reg0-31
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SER_0_31_Set(u_int32 enaset0)
{
	NVIC->IO_NVIC_ISER00_31.reg = enaset0;
}

/*******************************************************************************
* Function Name  : API_INT_SER_32_63_Set
* Description	 : 
* Input 		 : Enable Set Reg32-63
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SER_32_63_Set(u_int32 enaset1)
{
	NVIC->IO_NVIC_ISER32_63.reg = enaset1;
}

/*******************************************************************************
* Function Name  : API_INT_SER_Set
* Description	 : Enable Set Reg individually set
* Input 		 : _INTSER**
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SER_Set(u_int32 * addr,u_int32 bit)
{
	*addr = bit;
}

/*******************************************************************************
* Function Name  : API_INT_CER_0_31_Set
* Description	 : 
* Input 		 : Enable Clear Reg0-31
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_CER_0_31_Set(u_int32 enaclr0)
{
	NVIC->IO_NVIC_ICER00_31.reg = enaclr0;
}

/*******************************************************************************
* Function Name  : API_INT_CER_32_63_Set
* Description	 : 
* Input 		 : Enable Clear Reg32-63
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_CER_32_63_Set(u_int32 enaclr1)
{
	NVIC->IO_NVIC_ICER32_63.reg = enaclr1;
}

/*******************************************************************************
* Function Name  : API_INT_CER_Set
* Description	 : Enable Clear Reg individually set
* Input 		 : _INTCER**
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_CER_Set(u_int32 * addr,u_int32 bit)
{
	*addr = bit;
}

/*******************************************************************************
* Function Name  : API_INT_SER_0_31_Read
* Description	 : 
* Input 		 : 
* Output		 : Enable Set Reg0-31
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SER_0_31_Read(void)
{
	u_int32	EnaSet0;
	EnaSet0 = NVIC->IO_NVIC_ISER00_31.reg;
	return EnaSet0;
}

/*******************************************************************************
* Function Name  : API_INT_SER_32_63_Read
* Description	 : 
* Input 		 : 
* Output		 : Enable Set Reg32-63
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SER_32_63_Read(void)
{
	u_int32	EnaSet1;
	EnaSet1 = NVIC->IO_NVIC_ISER32_63.reg;
	return EnaSet1;
}

/*******************************************************************************
* Function Name  : API_INT_SER_Read
* Description	 : Enable Set Reg individually read
* Input 		 : _INTSER_R**
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SER_Read(u_int32 * addr,u_int32 bit)
{
	u_int32	EnaSet;
	EnaSet = (* addr);
	EnaSet >>= bit;
	EnaSet &= INT_UI32BIT0_MASK;
	return EnaSet;
}

/*******************************************************************************
* Function Name  : API_INT_SPR_0_31_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SPR_0_31_Set(u_int32 pendset0)
{
	NVIC->IO_NVIC_ISPR00_31.reg = pendset0;
}

/*******************************************************************************
* Function Name  : API_INT_SPR_32_63_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SPR_32_63_Set(u_int32 pendset1)
{
	NVIC->IO_NVIC_ISPR32_63.reg = pendset1;
}

/*******************************************************************************
* Function Name  : API_INT_SPR_Set
* Description	 : individually
* Input 		 : _INTSPR**
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SPR_Set(u_int32 * addr,u_int32 bit)
{
	*addr = bit;
}

/*******************************************************************************
* Function Name  : API_INT_CPR_0_31_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_CPR_0_31_Set(u_int32 pendclr0)
{
	NVIC->IO_NVIC_ICPR00_31.reg = pendclr0;
}

/*******************************************************************************
* Function Name  : API_INT_CPR_32_63_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_CPR_32_63_Set(u_int32 pendclr1)
{
	NVIC->IO_NVIC_ICPR32_63.reg = pendclr1;
}

/*******************************************************************************
* Function Name  : API_INT_CPR_Set
* Description	 : individually
* Input 		 : _INTCPR**
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_CPR_Set(u_int32 * addr,u_int32 bit)
{
	*addr = bit;
}

/*******************************************************************************
* Function Name  : API_INT_SPR_0_31_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SPR_0_31_Read(void)
{
	u_int32	PendSet0;
	PendSet0 = NVIC->IO_NVIC_ISPR00_31.reg;
	return PendSet0;
}

/*******************************************************************************
* Function Name  : API_INT_SPR_32_63_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SPR_32_63_Read(void)
{
	u_int32	PendSet1;
	PendSet1 = NVIC->IO_NVIC_ISPR32_63.reg;
	return PendSet1;
}

/*******************************************************************************
* Function Name  : API_INT_SPR_Read
* Description	 : Pending Set Reg individually read
* Input 		 : _INTSPR_R**
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SPR_Read(u_int32 * addr,u_int8 bit)
{
	u_int32	PendSet;
	PendSet = (* addr);
	PendSet >>= bit;
	PendSet &= INT_UI32BIT0_MASK;
	return PendSet;
}

/*******************************************************************************
* Function Name  : API_INT_ABR_0_31_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_ABR_0_31_Read(void)
{
	u_int32	ActiveBit0;
	ActiveBit0 = NVIC->IO_NVIC_ABR00_31.reg;
	return ActiveBit0;
}

/*******************************************************************************
* Function Name  : API_INT_ABR_32_63_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_ABR_32_63_Read(void)
{
	u_int32	ActiveBit1;
	ActiveBit1 = NVIC->IO_NVIC_ABR32_63.reg;
	return ActiveBit1;
}

/*******************************************************************************
* Function Name  : API_INT_ABR_Read
* Description	 : Active Bit Reg individually read
* Input 		 : _INTABR_R**
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_ABR_Read(u_int32 * addr,u_int8 bit)
{
	u_int32	ActiveBit;
	ActiveBit = (* addr);
	ActiveBit >>= bit;
	ActiveBit &= INT_UI32BIT0_MASK;
	return ActiveBit;
}

/*******************************************************************************
* Function Name  : API_INT_PR4_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_PR4_Set(u_int8 fieldnum,u_int8 pri0,u_int8 pri1,u_int8 pri2,u_int8 pri3)
{
	u_int8	i;
	i = (u_int8)(4 * fieldnum);
	NVIC->IO_NVIC_INTPR[i].reg = pri0;
	NVIC->IO_NVIC_INTPR[i+1].reg = pri1;
	NVIC->IO_NVIC_INTPR[i+2].reg = pri2;
	NVIC->IO_NVIC_INTPR[i+3].reg = pri3;
}

/*******************************************************************************
* Function Name  : API_INT_PR_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_PR_Set(u_int8 intnum,u_int8 pri)
{
	NVIC->IO_NVIC_INTPR[intnum].reg = pri;
}

/*******************************************************************************
* Function Name  : API_INT_ID_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_ID_Read(void)
{
	u_int32	CPUID;
	CPUID = CPU->IO_CPU_CPUID_BR.reg;
	return CPUID;
}

/*******************************************************************************
* Function Name  : API_INT_ICSR_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_ICSR_Set(u_int32 intctrlst)
{
	CPU->IO_CPU_ICSR.reg = intctrlst;
}

/*******************************************************************************
* Function Name  : API_INT_ICSR_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_ICSR_Read(void)
{
	u_int32	IntCntlSt;
	IntCntlSt = CPU->IO_CPU_ICSR.reg;
	return IntCntlSt;
}

/*******************************************************************************
* Function Name  : API_INT_VTOR_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_VTOR_Set(u_int32 vctoffset)
{
	CPU->IO_CPU_VTOR.reg = vctoffset;
}

/*******************************************************************************
* Function Name  : API_INT_SHPR_Set
* Description	 : individually
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SHPR_Set(u_int8 * addr,u_int8 shpr)
{
	*addr = shpr;
}

/*******************************************************************************
* Function Name  : API_INT_SHPR_Read
* Description	 : individually
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_INT_SHPR_Read(u_int8 * addr)
{
	u_int8	Shpr;
	Shpr = (u_int8)(* addr);
	return Shpr;
}

/*******************************************************************************
* Function Name  : API_INT_SHC_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SHC_Set(u_int32 syshandcntl)
{
	CPU->IO_CPU_SHCSR.reg = syshandcntl;
}

/*******************************************************************************
* Function Name  : API_INT_SHC_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SHC_Read(void)
{
	u_int32	SysHandCntl;
	SysHandCntl = CPU->IO_CPU_SHCSR.reg;
	return SysHandCntl;
}

/*******************************************************************************
* Function Name  : API_INT_PR_AllSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_PR_AllSet(u_int8 pri)
{
	u_int8	i;
	for(i = 0; i < IO_INT_PRIFIELDMAX; ++i){
		NVIC->IO_NVIC_INTPR[i].reg = pri;
	}
}

/*******************************************************************************
* Function Name  : API_INT_StsTickSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_StsTickSet(u_int32 systickcntl)
{
	SYSTICK->IO_NVIC_CTL.reg = systickcntl;
}

/*******************************************************************************
* Function Name  : API_INT_SysTickRead
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SysTickRead(void)
{
	u_int32	SysTickCntl;
	SysTickCntl = SYSTICK->IO_NVIC_CTL.reg;
	return SysTickCntl;
}

/*******************************************************************************
* Function Name  : API_INT_SysTickR_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SysTickR_Set(u_int32 systickrld)
{
	SYSTICK->IO_NVIC_RVR.reg = systickrld;
}

/*******************************************************************************
* Function Name  : API_INT_SysTickR_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SysTickR_Read(void)
{
	u_int32	SysTickRld;
	SysTickRld = SYSTICK->IO_NVIC_RVR.reg;
	return SysTickRld;
}

/*******************************************************************************
* Function Name  : API_INT_SysTickC_Set
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SysTickC_Set(u_int32 systickcrt)
{
	SYSTICK->IO_NVIC_CVR.reg = systickcrt;
}

/*******************************************************************************
* Function Name  : API_INT_SysTickC_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SysTickC_Read(void)
{
	u_int32	SysTickCrt;
	SysTickCrt = SYSTICK->IO_NVIC_CVR.reg;
	return SysTickCrt;
}

/*******************************************************************************
* Function Name  : API_INT_SysTickCVR_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int32 API_INT_SysTickCVR_Read(void)
{
	u_int32	SysTickCal;
	SysTickCal = SYSTICK->IO_NVIC_CAL.reg;
	return SysTickCal;
}

