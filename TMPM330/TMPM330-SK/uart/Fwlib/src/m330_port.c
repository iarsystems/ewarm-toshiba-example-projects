/*******************************************************************************
* File Name 		 : m330_port.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : port liblary source
********************************************************************************/


#include "m330_port.h"


/*******************************************************************************
* Function Name  : API_PORT_Init
* Description	 : SFR_PORTx_t * PortChSel = ch address?
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_Init(SFR_PORTx_t * PortChSel)
{
	PortChSel->IO_Px.reg = IO_PORT_Px_Init;
	switch((u_int32)PortChSel){
		case SFR_PORTA_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PACR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PAFR1_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PAPUP_Init;
			PortChSel->IO_PxPDN.reg = IO_PORT_PAPDN_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PAIE_Init;
			break;
		case SFR_PORTB_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PBCR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PBFR1_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PBPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PBIE_Init;
			break;
		case SFR_PORTC_ADR:		/*  ch address? */
			PortChSel->IO_PxPUP.reg = IO_PORT_PCPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PCIE_Init;
			break;
		case SFR_PORTD_ADR:		/*  ch address? */
			PortChSel->IO_PxFR1.reg = IO_PORT_PAFR1_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PAPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PAIE_Init;
			break;
		case SFR_PORTE_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PECR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PEFR1_Init;
			PortChSel->IO_PxFR2.reg = IO_PORT_PEFR2_Init;
			PortChSel->IO_PxOD.reg = IO_PORT_PEOD_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PEPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PEIE_Init;
			break;
		case SFR_PORTF_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PFCR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PFFR1_Init;
			PortChSel->IO_PxFR2.reg = IO_PORT_PFFR2_Init;
			PortChSel->IO_PxOD.reg = IO_PORT_PFOD_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PFPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PFIE_Init;
			break;
		case SFR_PORTG_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PGCR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PGFR1_Init;
			PortChSel->IO_PxOD.reg = IO_PORT_PGOD_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PGPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PGIE_Init;
			break;
		case SFR_PORTH_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PHCR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PHFR1_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PHPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PHIE_Init;
			break;
		case SFR_PORTI_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PICR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PIFR1_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PIPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PIIE_Init;
			break;
		case SFR_PORTJ_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PJCR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PJFR1_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PJPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PJIE_Init;
			break;
		case SFR_PORTK_ADR:		/*  ch address? */
			PortChSel->IO_PxCR.reg = IO_PORT_PKCR_Init;
			PortChSel->IO_PxFR1.reg = IO_PORT_PKFR1_Init;
			PortChSel->IO_PxFR2.reg = IO_PORT_PKFR2_Init;
			PortChSel->IO_PxPUP.reg = IO_PORT_PKPUP_Init;
			PortChSel->IO_PxIE.reg = IO_PORT_PKIE_Init;
			break;
		default:
			break;
	}
}

/*******************************************************************************
* Function Name  : API_PORT_Out
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_Out(SFR_PORTx_t * PortChSel,u_int8 px)
{
	PortChSel->IO_Px.reg = px;
}

/*******************************************************************************
* Function Name  : API_PORT_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_PORT_Read(SFR_PORTx_t * PortChSel)
{
	u_int8	Pxbuf;
	Pxbuf = PortChSel->IO_Px.reg;
	return Pxbuf;
}

/*******************************************************************************
* Function Name  : API_PORT_CrRegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_CrRegSet(SFR_PORTx_t * PortChSel,u_int8 pxcr)
{
	PortChSel->IO_PxCR.reg |= pxcr;
}

/*******************************************************************************
* Function Name  : API_PORT_Fr1regSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_Fr1RegSet(SFR_PORTx_t * PortChSel,u_int8 pxfr1)
{
	PortChSel->IO_PxFR1.reg |= pxfr1;
}

/*******************************************************************************
* Function Name  : API_PORT_Fr2RegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_Fr2RegSet(SFR_PORTx_t * PortChSel,u_int8 pxfr2)
{
	PortChSel->IO_PxFR2.reg |= pxfr2;
}

/*******************************************************************************
* Function Name  : API_PORT_OdRegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_OdRegSet(SFR_PORTx_t * PortChSel,u_int8 pxod)
{
	PortChSel->IO_PxOD.reg |= pxod;
}

/*******************************************************************************
* Function Name  : API_PORT_PupRegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_PupRegSet(SFR_PORTx_t * PortChSel,u_int8 pxpup)
{
	PortChSel->IO_PxPUP.reg |= pxpup;
}

/*******************************************************************************
* Function Name  : API_PORT_PdnRegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_PdnRegSet(SFR_PORTx_t * PortChSel,u_int8 pxpdn)
{
	PortChSel->IO_PxPDN.reg |= pxpdn;
}

/*******************************************************************************
* Function Name  : API_PORT_IeRegSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_IeRegSet(SFR_PORTx_t * PortChSel,u_int8 pxie)
{
	PortChSel->IO_PxIE.reg |= pxie;
}

/*******************************************************************************
* Function Name  : API_PORT_BitFuncSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_BitFuncSet(SFR_PORTx_t * PortChSel,u_int8 bitnum,u_int8 cr,
u_int8 fr1,u_int8 fr2,u_int8 od,u_int8 pup,u_int8 pdn,u_int8 ie)
{
	switch((u_int32)PortChSel){
		case SFR_PORTA_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxPDN.reg,bitnum) = (u_int8)pdn;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTB_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTC_ADR:
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTD_ADR:
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTE_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxFR2.reg,bitnum) = (u_int8)fr2;
			BITBAND_IP(PortChSel->IO_PxOD.reg,bitnum) = (u_int8)od;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTF_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxFR2.reg,bitnum) = (u_int8)fr2;
			BITBAND_IP(PortChSel->IO_PxOD.reg,bitnum) = (u_int8)od;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTG_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxOD.reg,bitnum) = (u_int8)od;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTH_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTI_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTJ_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		case SFR_PORTK_ADR:
			BITBAND_IP(PortChSel->IO_PxCR.reg,bitnum) = (u_int8)cr;
			BITBAND_IP(PortChSel->IO_PxFR1.reg,bitnum) = (u_int8)fr1;
			BITBAND_IP(PortChSel->IO_PxFR2.reg,bitnum) = (u_int8)fr2;
			BITBAND_IP(PortChSel->IO_PxPUP.reg,bitnum) = (u_int8)pup;
			BITBAND_IP(PortChSel->IO_PxIE.reg,bitnum) = (u_int8)ie;
			break;
		default:
			break;
	}
}

/*******************************************************************************
* Function Name  : API_PORT_BitOut
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_BitOut(SFR_PORTx_t * PortChSel,u_int8 bitnum,u_int8 bitdata)
{
	BITBAND_IP(PortChSel->IO_Px.reg,bitnum) = (u_int8)bitdata;
}

/*******************************************************************************
* Function Name  : API_PORT_BitIn
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_PORT_BitIn(SFR_PORTx_t * PortChSel,u_int8 bitnum)
{
	u_int8	Pxbitbuf;
	Pxbitbuf = BITBAND_IP(PortChSel->IO_Px.reg,bitnum);
	return Pxbitbuf;
}

/*******************************************************************************
* Function Name  : API_PORT_bitRev
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_bitRev(SFR_PORTx_t * PortChSel,u_int8 bitnum)
{
	BITBAND_IP(PortChSel->IO_Px.reg,bitnum) = (u_int8)(~(BITBAND_IP(PortChSel->IO_Px.reg,bitnum)));
}

/*******************************************************************************
* Function Name  : API_PORT_BitSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_BitSet(SFR_PORTx_t * PortChSel,u_int8 bitnum)
{
	BITBAND_IP(PortChSel->IO_Px.reg,bitnum) = 1;
}

/*******************************************************************************
* Function Name  : API_PORT_BitClr
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_BitClr(SFR_PORTx_t * PortChSel,u_int8 bitnum)
{
	BITBAND_IP(PortChSel->IO_Px.reg,bitnum) = 0;
}

/*******************************************************************************
* Function Name  : API_PORT_AndOut
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_AndOut(SFR_PORTx_t * PortChSel,u_int8 anddata)
{
	PortChSel->IO_Px.reg &= (u_int8)anddata;
}

/*******************************************************************************
* Function Name  : API_PORT_OrOut
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_OrOut(SFR_PORTx_t * PortChSel,u_int8 ordata)
{
	PortChSel->IO_Px.reg |= (u_int8)ordata;
}

/*******************************************************************************
* Function Name  : API_PORT_XorOut
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_XorOut(SFR_PORTx_t * PortChSel,u_int8 xordata)
{
	PortChSel->IO_Px.reg ^= (u_int8)xordata;
}



