/*******************************************************************************
* File Name 		 : m370_port.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : port header
********************************************************************************/

#ifndef __M370_PORT_H
#define __M370_PORT_H

#include "..\typedef.h"

/* PORT initial data */

/* Port A */
#define		PORT_PA_INIT		BIT8(1,1,1,1,1,1,1,1)
#define		PORT_PACR_INIT		BIT8(1,1,1,1,1,1,1,1)
#define		PORT_PAFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PAFR2_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PAOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PAPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PAPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PAIE_INIT		BIT8(0,0,0,0,0,0,0,0)
/*								     | | | | | | | +-------; 7SEG LED a/LED4
								     | | | | | | +---------; 7SEG LED b/LED5
								     | | | | | +-----------; 7SEG LED c/LED6
								     | | | | +-------------; 7SEG LED d/LED7
								     | | | +---------------; 7SEG LED e/LED8
								     | | +-----------------; 7SEG LED f/LED9
								     | +-------------------; 7SEG LED g/LED10
								     +---------------------; 7SEG LED dp/LED11
*/

/* Port B */
#define		PORT_PB_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PBCR_INIT		BIT8(0,0,1,0,1,0,0,0)
#define		PORT_PBFR1_INIT		BIT8(1,1,1,1,1,0,0,0)
#define		PORT_PBOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PBPUP_INIT		BIT8(1,1,0,0,1,0,0,0)
#define		PORT_PBPDN_INIT		BIT8(0,0,0,1,0,0,0,0)
#define		PORT_PBIE_INIT		BIT8(1,1,0,1,1,0,0,0)
/*								     | | | | | | | +-------; 
								     | | | | | | +---------; 
								     | | | | | +-----------; 
								     | | | | +-------------; TMS/SWDIO
								     | | | +---------------; TCK/SWCLK
								     | | +-----------------; TDO/SWV
								     | + ------------------; TDI
								     + --------------------; TRST
*/

/* Port C */
#define		PORT_PC_INIT		BIT8(0,0,0,0,0,0,0,0)
#if DBG
#define		PORT_PCCR_INIT		BIT8(0,0,0,1,0,0,0,1)
#else
#define		PORT_PCCR_INIT		BIT8(0,0,0,1,0,0,0,0)
#endif
#define		PORT_PCFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PCFR2_INIT		BIT8(0,0,0,1,0,0,0,0)
#define		PORT_PCFR3_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PCFR4_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PCFR5_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PCPOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PCPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PCPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PCIE_INIT		BIT8(0,0,0,0,0,0,0,0)
/*								     | | | | | | | +-------; DEBUG PORT
								     | | | | | | +---------; 
								     | | | | | +-----------; 
								     | | | | +-------------; 
								     | | | +---------------; W0(PWM)
								     | | +-----------------; 
								     | +-------------------; 
								     +---------------------; 
*/

/* Port D */
#define		PORT_PD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PDCR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PDFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PDFR2_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PDFR3_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PDOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PDPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PDPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PDIE_INIT		BIT8(0,0,0,0,0,1,1,1)
/*								     | | | | | | | +-------; TSW1
								     | | | | | | +---------; TSW2
								     | | | | | +-----------; TSW3
								     | | | | +-------------;
								     | | | +---------------;
								     | | +-----------------;
								     | +-------------------;
								     +---------------------;
*/

/* Port E */
#define		PORT_PE_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PECR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PEFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PEFR2_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PEOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PEPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PEPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PEIE_INIT		BIT8(0,0,0,0,0,0,0,0)

/* Port F */
#define		PORT_PF_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PFCR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PFFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PFFR2_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PFFR3_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PFOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PFPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PFPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PFIE_INIT		BIT8(0,0,0,0,0,0,0,0)


/* Port G */
#define		PORT_PG_INIT		BIT8(1,1,1,1,0,0,0,0)
#define		PORT_PGCR_INIT		BIT8(1,1,1,1,0,0,0,0)
#define		PORT_PGFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PGFR2_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PGFR3_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PGOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PGPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PGPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PGIE_INIT		BIT8(0,0,0,0,0,0,0,0)
/*								     | | | | | | | +-------; 
								     | | | | | | +---------; 
								     | | | | | +-----------; 
								     | | | | +-------------; 
								     | | | +---------------; LED4-11
								     | | +-----------------; 7SEG LED3
								     | +-------------------; 7SEG LED2
								     +---------------------; 7SEG LED1
*/


/* Port H */
#define		PORT_PH_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PHCR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PHFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PHOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PHPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PHPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PHIE_INIT		BIT8(0,0,0,0,0,0,0,0)


/* Port I */
#define		PORT_PI_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PICR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PIOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PIPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PIPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PIIE_INIT		BIT8(0,0,0,0,0,0,0,0)


/* Port J */
#define		PORT_PJ_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PJCR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PJFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PJOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PJPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PJPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PJIE_INIT		BIT8(0,0,0,0,0,0,0,0)


/* Port K */
/* #define		PORT_PK_INIT		BIT8(0,0,0,0,0,0,0,0) */
/* #define		PORT_PKCR_INIT		BIT8(0,0,0,0,0,0,0,0) */
/* #define		PORT_PKFR1_INIT		BIT8(0,0,0,0,0,0,0,0) */
/* #define		PORT_PKOD_INIT		BIT8(0,0,0,0,0,0,0,0) */
/* #define		PORT_PKPUP_INIT		BIT8(0,0,0,0,0,0,0,0) */
/* #define		PORT_PKPDN_INIT		BIT8(0,0,0,0,0,0,0,0) */
/* #define		PORT_PKIE_INIT		BIT8(0,0,0,0,0,0,0,0) */

/* Port L */
#define		PORT_PL_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PLCR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PLFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PLOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PLPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PLPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PLIE_INIT		BIT8(0,0,0,0,0,0,0,0)

/* Port M */
#define		PORT_PM_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PMCR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PMFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PMOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PMPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PMPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PMIE_INIT		BIT8(0,0,0,0,0,0,0,0)

/* Port N */
#define		PORT_PN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PNCR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PNFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PNOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PNPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PNPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PNIE_INIT		BIT8(0,0,0,0,0,0,0,0)

/* Port P */
#define		PORT_PP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PPCR_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PPFR1_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PPOD_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PPPUP_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PPPDN_INIT		BIT8(0,0,0,0,0,0,0,0)
#define		PORT_PPIE_INIT		BIT8(0,0,0,0,0,0,0,0)

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
			   PORT_K = 10,
			   PORT_L = 11,
			   PORT_M = 12,
			   PORT_N = 13,
			   PORT_P = 14
			 } IpPORT_ChSel;							/* PORT CH data */

typedef enum { PORT_A0 = PORT_A*10, PORT_A1, PORT_A2, PORT_A3, PORT_A4, PORT_A5, PORT_A6, PORT_A7,
			   PORT_B0 = PORT_B*10, PORT_B1, PORT_B2, PORT_B3, PORT_B4, PORT_B5, PORT_B6, PORT_B7,
			   PORT_C0 = PORT_C*10, PORT_C1, PORT_C2, PORT_C3, PORT_C4, PORT_C5, PORT_C6, PORT_C7,
			   PORT_D0 = PORT_D*10, PORT_D1, PORT_D2, PORT_D3, PORT_D4, PORT_D5, PORT_D6, PORT_D7,
			   PORT_E0 = PORT_E*10, PORT_E1, PORT_E2, PORT_E3, PORT_E4, PORT_E5, PORT_E6, PORT_E7,
			   PORT_F0 = PORT_F*10, PORT_F1, PORT_F2, PORT_F3, PORT_F4, PORT_F5, PORT_F6, PORT_F7,
			   PORT_G0 = PORT_G*10, PORT_G1, PORT_G2, PORT_G3, PORT_G4, PORT_G5, PORT_G6, PORT_G7,
			   PORT_H0 = PORT_H*10, PORT_H1, PORT_H2, PORT_H3, PORT_H4, PORT_H5, PORT_H6, PORT_H7,
			   PORT_I0 = PORT_I*10, PORT_I1, PORT_I2, PORT_I3, PORT_I4, PORT_I5, PORT_I6, PORT_I7,
			   PORT_J0 = PORT_J*10, PORT_J1, PORT_J2, PORT_J3, PORT_J4, PORT_J5, PORT_J6, PORT_J7,
			   PORT_K0 = PORT_K*10, PORT_K1, PORT_K2, PORT_K3, PORT_K4, PORT_K5, PORT_K6, PORT_K7,
			   PORT_L0 = PORT_L*10, PORT_L1, PORT_L2, PORT_L3, PORT_L4, PORT_L5, PORT_L6, PORT_L7,
			   PORT_M0 = PORT_M*10, PORT_M1, PORT_M2, PORT_M3, PORT_M4, PORT_M5, PORT_M6, PORT_M7,
			   PORT_N0 = PORT_N*10, PORT_N1, PORT_N2, PORT_N3, PORT_N4, PORT_N5, PORT_N6, PORT_N7,
			   PORT_P0 = PORT_P*10, PORT_P1, PORT_P2, PORT_P3, PORT_P4, PORT_P5, PORT_P6, PORT_P7
			 } IpPORT_BitSel;							/* PORT BIT data */


#define STOP		0
#define ACTIVE		1




/**************************************************************/

void API_PORT_Init(void);
void API_PORT_Out(IpPORT_ChSel portChSel, uint8_t px);
uint8_t API_PORT_Read(IpPORT_ChSel portChSel);
uint8_t API_PORT_BitIn(IpPORT_BitSel portBitSel);
void API_PORT_BitSet(IpPORT_BitSel portBitSel);
void API_PORT_BitClr(IpPORT_BitSel portBitSel);


#endif

