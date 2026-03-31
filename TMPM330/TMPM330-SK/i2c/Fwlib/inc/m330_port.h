/*******************************************************************************
* File Name 		 : m330_port.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : port header
********************************************************************************/

/* avoid double definition */
#ifndef __M330_PORT_H
#define __M330_PORT_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* PORT initial data */

#define IO_PORT_Px_Init			((u_int8)0x00)
/* PORTA */
#define IO_PORT_PACR_Init		((u_int8)0x01)
#define IO_PORT_PAFR1_Init		((u_int8)0x03)
#define IO_PORT_PAPUP_Init		((u_int8)0x01)
#define IO_PORT_PAPDN_Init		((u_int8)0x02)
#define IO_PORT_PAIE_Init		((u_int8)0x03)
/* PORTB */
#define IO_PORT_PBCR_Init		((u_int8)0x01)
#define IO_PORT_PBFR1_Init		((u_int8)0x07)
#define IO_PORT_PBPUP_Init		((u_int8)0x06)
#define IO_PORT_PBIE_Init		((u_int8)0x06)
/* PORTC */
#define IO_PORT_PCPUP_Init		((u_int8)0x00)
#define IO_PORT_PCIE_Init		((u_int8)0x06)
/* PORTD */
#define IO_PORT_PDFR1_Init		((u_int8)0x00)
#define IO_PORT_PDPUP_Init		((u_int8)0x00)
#define IO_PORT_PDIE_Init		((u_int8)0x00)
/* PORTE */
#define IO_PORT_PECR_Init		((u_int8)0x00)
#define IO_PORT_PEFR1_Init		((u_int8)0x00)
#define IO_PORT_PEFR2_Init		((u_int8)0x00)
#define IO_PORT_PEOD_Init		((u_int8)0x00)
#define IO_PORT_PEPUP_Init		((u_int8)0x00)
#define IO_PORT_PEIE_Init		((u_int8)0x00)
/* PORTF */
#define IO_PORT_PFCR_Init		((u_int8)0x00)
#define IO_PORT_PFFR1_Init		((u_int8)0x00)
#define IO_PORT_PFFR2_Init		((u_int8)0x00)
#define IO_PORT_PFOD_Init		((u_int8)0x00)
#define IO_PORT_PFPUP_Init		((u_int8)0x00)
#define IO_PORT_PFIE_Init		((u_int8)0x00)
/* PORTG */
#define IO_PORT_PGCR_Init		((u_int8)0x00)
#define IO_PORT_PGFR1_Init		((u_int8)0x00)
#define IO_PORT_PGOD_Init		((u_int8)0x00)
#define IO_PORT_PGPUP_Init		((u_int8)0x00)
#define IO_PORT_PGIE_Init		((u_int8)0x00)
/* PORTH */
#define IO_PORT_PHCR_Init		((u_int8)0x00)
#define IO_PORT_PHFR1_Init		((u_int8)0x00)
#define IO_PORT_PHPUP_Init		((u_int8)0x00)
#define IO_PORT_PHIE_Init		((u_int8)0x00)

/* PORTI */
#define IO_PORT_PICR_Init		((u_int8)0x00)
#define IO_PORT_PIFR1_Init		((u_int8)0x00)
#define IO_PORT_PIPUP_Init		((u_int8)0x00)
#define IO_PORT_PIIE_Init		((u_int8)0x00)
/* PORTJ */
#define IO_PORT_PJCR_Init		((u_int8)0x00)
#define IO_PORT_PJFR1_Init		((u_int8)0x00)
#define IO_PORT_PJPUP_Init		((u_int8)0x00)
#define IO_PORT_PJIE_Init		((u_int8)0x00)
/* PORTK */
#define IO_PORT_PHCR_Init		((u_int8)0x00)
#define IO_PORT_PHFR1_Init		((u_int8)0x00)
#define IO_PORT_PHPUP_Init		((u_int8)0x00)
#define IO_PORT_PHIE_Init		((u_int8)0x00)
/* PORTK */
#define IO_PORT_PKCR_Init		((u_int8)0x00)
#define IO_PORT_PKFR1_Init		((u_int8)0x00)
#define IO_PORT_PKFR2_Init		((u_int8)0x00)
#define IO_PORT_PKPUP_Init		((u_int8)0x00)
#define IO_PORT_PKIE_Init		((u_int8)0x00)


typedef enum { PORT_A = 0, 
			   PORT_B = 1,
			   PORT_C = 2,
			   PORT_D = 3,
			   PORT_E = 4,
			   PORT_F = 5,
			   PORT_G = 6,
			   PORT_H = 7,
			   PORT_I = 8,
			   PORT_J = 9,
			   PORT_K = 10
			 } IpPORT_ChSel;							/* PORT CH data */



#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */

	/* ‚È‚µ */



/**************************************************************/

void API_PORT_Init(SFR_PORTx_t * PortChSel);
void API_PORT_Out(SFR_PORTx_t * PortChSel,u_int8 px);
u_int8 API_PORT_Read(SFR_PORTx_t * PortChSel);
void API_PORT_CrRegSet(SFR_PORTx_t * PortChSel,u_int8 pxcr);
void API_PORT_Fr1RegSet(SFR_PORTx_t * PortChSel,u_int8 pxfr1);
void API_PORT_Fr2RegSet(SFR_PORTx_t * PortChSel,u_int8 pxfr2);
void API_PORT_OdRegSet(SFR_PORTx_t * PortChSel,u_int8 pxod);
void API_PORT_PupRegSet(SFR_PORTx_t * PortChSel,u_int8 pxpup);
void API_PORT_PdnRegSet(SFR_PORTx_t * PortChSel,u_int8 pxpdn);
void API_PORT_IeRegSet(SFR_PORTx_t * PortChSel,u_int8 pxie);
void API_PORT_BitFuncSet(SFR_PORTx_t * PortChSel,u_int8 bitnum,u_int8 cr,u_int8 fr1,u_int8 fr2,u_int8 od,u_int8 pup,u_int8 pdn,u_int8 ie);
void API_PORT_BitOut(SFR_PORTx_t * PortChSel,u_int8 bitnum,u_int8 bitdata);
u_int8 API_PORT_BitIn(SFR_PORTx_t * PortChSel,u_int8 bitnum);
void API_PORT_bitRev(SFR_PORTx_t * PortChSel,u_int8 bitnum);
void API_PORT_BitSet(SFR_PORTx_t * PortChSel,u_int8 bitnum);
void API_PORT_BitClr(SFR_PORTx_t * PortChSel,u_int8 bitnum);
void API_PORT_AndOut(SFR_PORTx_t * PortChSel,u_int8 anddata);
void API_PORT_OrOut(SFR_PORTx_t * PortChSel,u_int8 ordata);
void API_PORT_XorOut(SFR_PORTx_t * PortChSel,u_int8 xordata);







#endif /*  avoid double definition */





