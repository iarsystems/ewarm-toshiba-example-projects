/*******************************************************************************
* File Name 		 : m380_mpt.c
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : MPT liblary source
********************************************************************************/

#include "..\typedef.h"
#include "TMPM380_SYS.h"

#include "m380_mpt.h"

#define SET_MPTPTR      volatile MPT_M *mpt;                  \
                         mpt = &MPT.cnl[mptChSel]

/*******************************************************************************
* Function Name  : API_MPT_Init
* Description	 : Multi purpose Initialize
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MPT_Init(IpMPT_ChSel mptChSel)
{
	SET_MPTPTR;

	mpt->MTnEN   = 0x80;
	
	mpt->MTnRUN  = 0x00;
	mpt->MTTBnCR   = 0x00;
	mpt->MTTBnMOD  = 0x20;
	mpt->MTTBnFFCR = 0xC0;
	mpt->MTTBnIM   = 0x00;
	
	
	mpt->MTTBnRG0 = 0x0000;
	mpt->MTTBnRG1 = 0x0000;
	
	mpt->MTIGnCR   = 0x0000;
	mpt->MTIGnRESTA = 0x00;
	mpt->MTIGnICR = 0x00;
	mpt->MTIGnOCR = 0x00;
	mpt->MTIGnOCR = 0x00;
	mpt->MTIGnRG2 = 0x0000;
	mpt->MTIGnRG3 = 0x0000;
	mpt->MTIGnRG4 = 0x0000;
	mpt->MTIGnEMGCR = 0x00;
	
}

/*******************************************************************************
* Function Name  : API_MPT_ModSet
* Description	 : Multi purpose Timer Mode (Timer or IGBT)
* Input 		 : MTxEN,0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MPT_ModSet(IpMPT_ChSel mptChSel, IpMPT_Mode mptmode)
{
	SET_MPTPTR;
	
	BITBAND_IP(mpt->MTnEN, cBIT0) = (uint8_t)mptmode;
}

/*******************************************************************************
* Function Name  : API_MPT_Run
* Description	 : Multi purpose Timer Start, Stop
* Input 		 : MPTxRUN
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MPT_Run(IpMPT_ChSel mptChSel, IpMPT_Run mptrun)
{
	SET_MPTPTR;
	if (mptrun == MPT_RUN) {
		mpt->MTnRUN = BIT8(0,0,0,0,0,1,0,1);
	}
	else {
		mpt->MTnRUN = BIT8(0,0,0,0,0,0,0,0);
	}


}

/*******************************************************************************
* Function Name  : API_MPT_RunSet
* Description	 : Multi purpose Timer MTnRUN
* Input 		 : MPTxRUN
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MPT_RunSet(IpMPT_ChSel mptChSel, uint8_t mptxrun)
{
	SET_MPTPTR;
	mpt->MTnRUN = mptxrun;
}

/*******************************************************************************
* Function Name  : API_MTTB_ModSet
* Description	 : 16bit Timer MTTBnMOD
* Input 		 : MTTBxMOD
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTTB_ModSet(IpMPT_ChSel mptChSel, uint8_t tbxmod)
{
	SET_MPTPTR;
	mpt->MTTBnMOD = tbxmod;
}

/*******************************************************************************
* Function Name  : API_MTTB_CRSet
* Description	 : 16bit Timer MTTBnCR
* Input 		 : MTTBnCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTTB_CRSet(IpMPT_ChSel mptChSel, uint8_t tbxcr)
{
	SET_MPTPTR;
	mpt->MTTBnCR = tbxcr;
}

/*******************************************************************************
* Function Name  : API_MTTB_FFSet
* Description	 : 16bit Timer MTTBnFF
* Input 		 : MTTBnFFCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTTB_FFSet(IpMPT_ChSel mptChSel, uint8_t tbxff)
{
	SET_MPTPTR;
	mpt->MTTBnFFCR = tbxff;
}

/*******************************************************************************
* Function Name  : API_MTTB_REG0_Write
* Description	 : 16bit Timer REG0
* Input 		 : MTTBxRG0.15-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTTB_REG0_Write(IpMPT_ChSel mptChSel, uint16_t tbxreg0)
{
	SET_MPTPTR;
	mpt->MTTBnRG0= tbxreg0;
}

/*******************************************************************************
* Function Name  : API_MTTB_REG1_Write
* Description	 : 16bit Timer REG1
* Input 		 : MTTBxRG1.15-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTTB_REG1_Write(IpMPT_ChSel mptChSel, uint16_t tbxreg1)
{
	SET_MPTPTR;
	mpt->MTTBnRG1= tbxreg1;
}

/*******************************************************************************
* Function Name  : API_MTTB_IntMaskSet
* Description	 : 16bit Timer Interrupt Mask
* Input 		 : MTTBxIM.2-0
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTTB_IntMaskSet(IpMPT_ChSel mptChSel, uint8_t tbxim)
{
	SET_MPTPTR;
	mpt->MTTBnIM= tbxim;
}

/*******************************************************************************
* Function Name  : API_MTIG_CRSet
* Description	 : IGBT MTIGnCR
* Input 		 : MTIGxCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTIG_CRSet(IpMPT_ChSel mptChSel, uint16_t igxcr)
{
	SET_MPTPTR;
	mpt->MTIGnCR= igxcr;
}

/*******************************************************************************
* Function Name  : API_MTIG_Restart
* Description	 : IBGT Restart REG
* Input 		 : MTIGxRESTA,0
* Return		 : 
*******************************************************************************/
void API_MTIG_Restart(IpMPT_ChSel mptChSel, uint8_t igxrestart)
{
	SET_MPTPTR;
	mpt->MTIGnRESTA= igxrestart;
}

/*******************************************************************************
* Function Name  : API_MTIG_ICRSet
* Description	 : IGBT Input Control REG
* Input 		 : MTIGxICR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTIG_ICRSet(IpMPT_ChSel mptChSel, uint8_t igxicr)
{
	SET_MPTPTR;
	mpt->MTIGnICR= igxicr;
}

/*******************************************************************************
* Function Name  : API_MTIG_OCRSet
* Description	 : IGBT Output Control REG
* Input 		 : MTIGxOCR
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTIG_OCRSet(IpMPT_ChSel mptChSel, uint8_t igxocr)
{
	SET_MPTPTR;
	mpt->MTIGnOCR= igxocr;
}

/*******************************************************************************
* Function Name  : API_MTIG_REG2_Write
* Description	 : IGBT Timer REG2
* Input 		 : MTIGxRG2
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTIG_REG2_Write(IpMPT_ChSel mptChSel, uint16_t igxreg2)
{
	SET_MPTPTR;
	mpt->MTIGnRG2= igxreg2;
}

/*******************************************************************************
* Function Name  : API_MTIG_REG3_Write
* Description	 : IGBT Timer REG3
* Input 		 : MTIGxRG3
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTIG_REG3_Write(IpMPT_ChSel mptChSel, uint16_t igxreg3)
{
	SET_MPTPTR;
	mpt->MTIGnRG3= igxreg3;
}

/*******************************************************************************
* Function Name  : API_MTIG_REG4_Write
* Description	 : IGBT Timer REG4
* Input 		 : MTIGxRG4
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_MTIG_REG4_Write(IpMPT_ChSel mptChSel, uint16_t igxreg4)
{
	SET_MPTPTR;
	mpt->MTIGnRG4= igxreg4;
}

/*********************************** END OF FILE ******************************/
