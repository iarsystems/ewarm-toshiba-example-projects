/*******************************************************************************
* File Name 		 : m380_port.c
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : port liblary source (M380 STK)
********************************************************************************/
#include "..\typedef.h"
#include "TMPM380_SYS.h"


#include "m380_port.h"

#define SET_PORTPTR      volatile PORTM *port;                  \
                         port = &PORT.cnl[portChSel]

#define SET_BITPTR       volatile PORTM *port;                  \
                         uint8_t bitsel;                        \
                         port = &PORT.cnl[portBitSel/10];       \
                         bitsel = portBitSel%10


/*******************************************************************************
* Function Name  : API_PORT_Init
* Description	 : SFR_PORTx_t * PortChSel = ch address?
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_Init(void)
{
	volatile PORTM *port;
	
/* Port A */
	port = &PORT.cnl[PORT_A];
	port->IO_Px		= PORT_PA_INIT;
	port->IO_PxCR	= PORT_PACR_INIT;
	port->IO_PxFR1	= PORT_PAFR1_INIT;
	port->IO_PxFR2	= PORT_PAFR2_INIT;
	port->IO_PxOD	= PORT_PAOD_INIT;
	port->IO_PxPUP	= PORT_PAPUP_INIT;
	port->IO_PxPDN	= PORT_PAPDN_INIT;
	port->IO_PxIE	= PORT_PAIE_INIT;

/* Port B */
	port = &PORT.cnl[PORT_B];
	port->IO_Px		= PORT_PB_INIT;
	port->IO_PxCR	= PORT_PBCR_INIT;
	port->IO_PxFR1	= PORT_PBFR1_INIT;
	port->IO_PxOD	= PORT_PBOD_INIT;
	port->IO_PxPUP	= PORT_PBPUP_INIT;
	port->IO_PxPDN	= PORT_PBPDN_INIT;
	port->IO_PxIE	= PORT_PBIE_INIT;

/* Port C */
	port = &PORT.cnl[PORT_C];
	port->IO_Px		= PORT_PC_INIT;
	port->IO_PxCR	= PORT_PCCR_INIT;
	port->IO_PxFR1	= PORT_PCFR1_INIT;
	port->IO_PxFR2	= PORT_PCFR2_INIT;
	port->IO_PxFR3	= PORT_PCFR3_INIT;
	port->IO_PxFR4	= PORT_PCFR4_INIT;
	port->IO_PxFR5	= PORT_PCFR5_INIT;
	port->IO_PxOD	= PORT_PCPOD_INIT;
	port->IO_PxPUP	= PORT_PCPUP_INIT;
	port->IO_PxPDN	= PORT_PCPDN_INIT;
	port->IO_PxIE	= PORT_PCIE_INIT;

/* Port D */
	port = &PORT.cnl[PORT_D];
	port->IO_Px		= PORT_PD_INIT;
	port->IO_PxCR	= PORT_PDCR_INIT;
	port->IO_PxFR1	= PORT_PDFR1_INIT;
	port->IO_PxFR2	= PORT_PDFR2_INIT;
	port->IO_PxFR3	= PORT_PDFR3_INIT;
	port->IO_PxOD	= PORT_PDOD_INIT;
	port->IO_PxPUP	= PORT_PDPUP_INIT;
	port->IO_PxPDN	= PORT_PDPDN_INIT;
	port->IO_PxIE	= PORT_PDIE_INIT;

/* Port E */
	port = &PORT.cnl[PORT_E];
	port->IO_Px		= PORT_PE_INIT;
	port->IO_PxCR	= PORT_PECR_INIT;
	port->IO_PxFR1	= PORT_PEFR1_INIT;
	port->IO_PxFR2	= PORT_PEFR2_INIT;
	port->IO_PxOD	= PORT_PEOD_INIT;
	port->IO_PxPUP	= PORT_PEPUP_INIT;
	port->IO_PxPDN	= PORT_PEPDN_INIT;
	port->IO_PxIE	= PORT_PEIE_INIT;

/* Port F */
	port = &PORT.cnl[PORT_F];
	port->IO_Px		= PORT_PF_INIT;
	port->IO_PxCR	= PORT_PFCR_INIT;
	port->IO_PxFR1	= PORT_PFFR1_INIT;
	port->IO_PxFR2	= PORT_PFFR2_INIT;
	port->IO_PxFR3	= PORT_PFFR3_INIT;
	port->IO_PxOD	= PORT_PFOD_INIT;
	port->IO_PxPUP	= PORT_PFPUP_INIT;
	port->IO_PxPDN	= PORT_PFPDN_INIT;
	port->IO_PxIE	= PORT_PFIE_INIT;

/* Port G */
	port = &PORT.cnl[PORT_G];
	port->IO_Px		= PORT_PG_INIT;
	port->IO_PxCR	= PORT_PGCR_INIT;
	port->IO_PxFR1	= PORT_PGFR1_INIT;
	port->IO_PxFR2	= PORT_PGFR2_INIT;
	port->IO_PxFR3	= PORT_PGFR3_INIT;
	port->IO_PxOD	= PORT_PGOD_INIT;
	port->IO_PxPUP	= PORT_PGPUP_INIT;
	port->IO_PxPDN	= PORT_PGPDN_INIT;
	port->IO_PxIE	= PORT_PGIE_INIT;

/* Port H */
	port = &PORT.cnl[PORT_H];
	port->IO_Px		= PORT_PH_INIT;
	port->IO_PxCR	= PORT_PHCR_INIT;
	port->IO_PxFR1	= PORT_PHFR1_INIT;
	port->IO_PxOD	= PORT_PHOD_INIT;
	port->IO_PxPUP	= PORT_PHPUP_INIT;
	port->IO_PxPDN	= PORT_PHPDN_INIT;
	port->IO_PxIE	= PORT_PHIE_INIT;

/* Port I */
	port = &PORT.cnl[PORT_I];
	port->IO_Px		= PORT_PI_INIT;
	port->IO_PxCR	= PORT_PICR_INIT;
	port->IO_PxOD	= PORT_PIOD_INIT;
	port->IO_PxPUP	= PORT_PIPUP_INIT;
	port->IO_PxPDN	= PORT_PIPDN_INIT;
	port->IO_PxIE	= PORT_PIIE_INIT;

/* Port J */
	port = &PORT.cnl[PORT_J];
	port->IO_Px		= PORT_PJ_INIT;
	port->IO_PxCR	= PORT_PJCR_INIT;
	port->IO_PxFR1	= PORT_PJFR1_INIT;
	port->IO_PxOD	= PORT_PJOD_INIT;
	port->IO_PxPUP	= PORT_PJPUP_INIT;
	port->IO_PxPDN	= PORT_PJPDN_INIT;
	port->IO_PxIE	= PORT_PJIE_INIT;

/* Port K */

/* Port L */
	port = &PORT.cnl[PORT_L];
	port->IO_Px		= PORT_PL_INIT;
	port->IO_PxCR	= PORT_PLCR_INIT;
	port->IO_PxFR1	= PORT_PLFR1_INIT;
	port->IO_PxOD	= PORT_PLOD_INIT;
	port->IO_PxPUP	= PORT_PLPUP_INIT;
	port->IO_PxPDN	= PORT_PLPDN_INIT;
	port->IO_PxIE	= PORT_PLIE_INIT;

/* Port M */
	port = &PORT.cnl[PORT_M];
	port->IO_Px		= PORT_PM_INIT;
	port->IO_PxCR	= PORT_PMCR_INIT;
	port->IO_PxFR1	= PORT_PMFR1_INIT;
	port->IO_PxOD	= PORT_PMOD_INIT;
	port->IO_PxPUP	= PORT_PMPUP_INIT;
	port->IO_PxPDN	= PORT_PMPDN_INIT;
	port->IO_PxIE	= PORT_PMIE_INIT;

/* Port N */
	port = &PORT.cnl[PORT_N];
	port->IO_Px		= PORT_PN_INIT;
	port->IO_PxCR	= PORT_PNCR_INIT;
	port->IO_PxFR1	= PORT_PNFR1_INIT;
	port->IO_PxOD	= PORT_PNOD_INIT;
	port->IO_PxPUP	= PORT_PNPUP_INIT;
	port->IO_PxPDN	= PORT_PNPDN_INIT;
	port->IO_PxIE	= PORT_PNIE_INIT;

/* Port P */
	port = &PORT.cnl[PORT_P];
	port->IO_Px		= PORT_PP_INIT;
	port->IO_PxCR	= PORT_PPCR_INIT;
	port->IO_PxFR1	= PORT_PPFR1_INIT;
	port->IO_PxOD	= PORT_PPOD_INIT;
	port->IO_PxPUP	= PORT_PPPUP_INIT;
	port->IO_PxPDN	= PORT_PPPDN_INIT;
	port->IO_PxIE	= PORT_PPIE_INIT;

}

/*******************************************************************************
* Function Name  : API_PORT_Out
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_Out(IpPORT_ChSel portChSel, uint8_t px)
{
	SET_PORTPTR;
	port->IO_Px = px;
}

/*******************************************************************************
* Function Name  : API_PORT_Read
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
uint8_t API_PORT_Read(IpPORT_ChSel portChSel)
{
	SET_PORTPTR;
	return (port->IO_Px);
}

/*******************************************************************************
* Function Name  : API_PORT_BitIn
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
uint8_t API_PORT_BitIn(IpPORT_BitSel portBitSel)
{
	SET_BITPTR;
	return (BITBAND_IP(port->IO_Px, bitsel));
}


/*******************************************************************************
* Function Name  : API_PORT_BitSet
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_BitSet(IpPORT_BitSel portBitSel)
{
	SET_BITPTR;
	BITBAND_IP(port->IO_Px, bitsel) = 1;
}

/*******************************************************************************
* Function Name  : API_PORT_BitClr
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_PORT_BitClr(IpPORT_BitSel portBitSel)
{
	SET_BITPTR;
	BITBAND_IP(port->IO_Px, bitsel) = 0;
}

