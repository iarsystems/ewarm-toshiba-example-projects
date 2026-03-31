#ifndef _register_dmac_typedefs_h_
#define _register_dmac_typedefs_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : DMAC Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file register_dmac_typedefs.h
	\brief Header file of DMAC register's type define

	\author TOSHIBA CORPORATION

	\date 2008/08/11 New
	\date 2008/10/24 A910 Sample version 1.0
 */
/* ************************************************************************ */

/* ************************************************************************ */

/*
 * --------------------------------------------------------------------------
 *   Header Include Area
 * --------------------------------------------------------------------------
 */
#include "cmn_type.h"


/*
 * --------------------------------------------------------------------------
 *   Type Define
 * --------------------------------------------------------------------------
 */
/*! for DMACIntStatus:RO	*/
typedef union {
	UINT32_t	data;
	UINT16_t	s_data[CSIZEofUINT32_t/CSIZEofUINT16_t];
	UINT8_t		c_data[CSIZEofUINT32_t/CSIZEofUINT8_t];
	struct {
		UINT32_t	ch0		:1;		/*!< <0> 			*/
		UINT32_t	ch1		:1;		/*!< <1> 			*/
		UINT32_t	ch2		:1;		/*!< <2> 			*/
		UINT32_t	ch3		:1;		/*!< <3> 			*/
		UINT32_t	ch4		:1;		/*!< <4> 			*/
		UINT32_t	ch5		:1;		/*!< <5> 			*/
		UINT32_t	ch6		:1;		/*!< <6> 			*/
		UINT32_t	ch7		:1;		/*!< <7> 			*/
		UINT32_t	rsv		:24;	/*!< <31:8>			*/
	}b;
}DMACIntxxx_t;
#define DMACIntStatus_t			DMACIntxxx_t	/*!< DMACIntTCStatus	:RO	*/
#define DMACIntTCStatus_t		DMACIntxxx_t	/*!< DMACIntTCStatus	:RO	*/
#define DMACIntTCClear_t		DMACIntxxx_t	/*!< DMACIntTCClear 	:WO	*/
#define DMACIntErrorStatus_t	DMACIntxxx_t	/*!< DMACIntErrorStatus	:RO	*/
#define DMACIntErrClr_t			DMACIntxxx_t	/*!< DMACIntErrClr		:WO	*/
#define DMACRawIntTCStatus_t	DMACIntxxx_t	/*!< DMACRawIntTCStatus	:RO	*/
#define DMACRawIntErrorStatus_t	DMACIntxxx_t	/*!< DMACRawIntErrorStatus:RO	*/
#define DMACEnbldChns_t			DMACIntxxx_t	/*!< DMACEnbldChns		:RO	*/

/*! for DMACSoftBReq	*/
typedef union {
	UINT32_t	data;
	UINT16_t	s_data[CSIZEofUINT32_t/CSIZEofUINT16_t];
	UINT8_t		c_data[CSIZEofUINT32_t/CSIZEofUINT8_t];
	struct {
		UINT32_t	uart0_tx	:1;		/*!< <0> SoftBReq0		*/
		UINT32_t	uart0_rx	:1;		/*!< <1> SoftBReq1		*/
		UINT32_t	rsv3		:2;		/*!< <3:2> 				*/
		UINT32_t	nand0		:1;		/*!< <4> SoftBReq4		*/
		UINT32_t	cmsi		:1;		/*!< <5> SoftBReq5		*/
		UINT32_t	sdhc_cc_w	:1;		/*!< <6> SoftBReq6		*/
		UINT32_t	sdhc_cc_r	:1;		/*!< <7> SoftBReq7		*/
		UINT32_t	sdhc_sd_w	:1;		/*!< <8> SoftBReq8		*/
		UINT32_t	sdhc_sd_r	:1;		/*!< <9> SoftBReq9		*/
		UINT32_t	i2s0		:1;		/*!< <10> SoftBReq10	*/
		UINT32_t	i2s1		:1;		/*!< <11> SoftBReq11	*/
		UINT32_t	rsv2		:2;		/*!< <13:12> 			*/
		UINT32_t	lcdda		:1;		/*!< <14> SoftBReq14	*/
		UINT32_t	rsv1		:17;	/*!< <31:15> 			*/
	}b;
}DMACSoftBReq_t;

/*! for DMACSoftSReq	*/
typedef union {
	UINT32_t	data;
	UINT16_t	s_data[CSIZEofUINT32_t/CSIZEofUINT16_t];
	UINT8_t		c_data[CSIZEofUINT32_t/CSIZEofUINT8_t];
	struct {
		UINT32_t	uart0_tx	:1;		/*!< <0> SoftSReq0		*/
		UINT32_t	uart0_rx	:1;		/*!< <1> SoftSReq1		*/
		UINT32_t	rsv4		:2;		/*!< <3:2> 				*/
		UINT32_t	rsv3		:8;		/*!< <11:4> 			*/
		UINT32_t	rsv2		:2;		/*!< <13:12> 			*/
		UINT32_t	lcdda		:1;		/*!< <14> SoftSReq14	*/
		UINT32_t	rsv1		:17;	/*!< <31:15> 			*/
	}b;
}DMACSoftSReq_t;

/*! for DMACConfiguration	*/
typedef union {
	UINT32_t	data;
	UINT16_t	s_data[CSIZEofUINT32_t/CSIZEofUINT16_t];
	UINT8_t		c_data[CSIZEofUINT32_t/CSIZEofUINT8_t];
	struct {
		UINT32_t	e		:1;		/*!< <0> 			*/
		UINT32_t	m1		:1;		/*!< <1> 			*/
		UINT32_t	m2		:1;		/*!< <2> 			*/
		UINT32_t	rsv		:29;	/*!< <31:3> 		*/
	}b;
}DMACConfiguration_t;

/*! for DMACCxSrcAddr	*/
typedef union {
	UINT32_t	data;
	UINT16_t	s_data[CSIZEofUINT32_t/CSIZEofUINT16_t];
	UINT8_t		c_data[CSIZEofUINT32_t/CSIZEofUINT8_t];
	struct {
		UINT32_t	addr;			/*!< <31:0> 		*/
	}b;
}DMACCxSrcAddr_t;
#define DMACCxDestAddr_t	DMACCxSrcAddr_t

/*! for DMACCxLLI	*/
typedef union {
	UINT32_t	data;
	UINT16_t	s_data[CSIZEofUINT32_t/CSIZEofUINT16_t];
	UINT8_t		c_data[CSIZEofUINT32_t/CSIZEofUINT8_t];
	struct {
		UINT32_t	lm	:1;			/*!< <0> 		*/
		UINT32_t	rsv	:1;			/*!< <1> 		*/
		UINT32_t	lli	:30;		/*!< <31:2> 	*/
	}b;
}DMACCxLLI_t;

/*! for DMACCxControl	*/
typedef union {
	UINT32_t	data;
	UINT16_t	s_data[CSIZEofUINT32_t/CSIZEofUINT16_t];
	UINT8_t		c_data[CSIZEofUINT32_t/CSIZEofUINT8_t];
	struct {
		UINT32_t	transfersize	:12;	/*!< <0:11> 			*/
		UINT32_t	sbsize	:3;				/*!< <12:14> 			*/
		UINT32_t	dbsize	:3;				/*!< <15:17> 			*/
		UINT32_t	swidth	:3;				/*!< <18:20> 			*/
		UINT32_t	dwidth	:3;				/*!< <21:23> 			*/
		UINT32_t	s		:1;				/*!< <24> 				*/
		UINT32_t	d		:1;				/*!< <25> 				*/
		UINT32_t	si		:1;				/*!< <26> 				*/
		UINT32_t	di		:1;				/*!< <27> 				*/
		UINT32_t	prot1	:1;				/*!< <28> 				*/
		UINT32_t	prot2	:1;				/*!< <29> 				*/
		UINT32_t	prot3	:1;				/*!< <30> 				*/
		UINT32_t	i		:1;				/*!< <31> 				*/
	}b;
}DMACCxControl_t;

/*! for DMACCxConfiguration	*/
typedef union {
	UINT32_t	data;
	UINT16_t	s_data[CSIZEofUINT32_t/CSIZEofUINT16_t];
	UINT8_t		c_data[CSIZEofUINT32_t/CSIZEofUINT8_t];
	struct {
		UINT32_t	e				:1;		/*!< <0> 				*/
		UINT32_t	srcperipheral	:4;		/*!< <4:1> 				*/
		UINT32_t	rsv3			:1;		/*!< <5> 				*/
		UINT32_t	destperipheral	:4;		/*!< <9:6> 				*/
		UINT32_t	rsv2			:1;		/*!< <10> 				*/
		UINT32_t	flowcontrl		:3;		/*!< <13:11> 				*/
		UINT32_t	ie				:1;		/*!< <14> 				*/
		UINT32_t	itc				:1;		/*!< <15> 				*/
		UINT32_t	lock			:1;		/*!< <16> 				*/
		UINT32_t	active			:1;		/*!< <17> 				*/
		UINT32_t	halt			:1;		/*!< <18> 				*/
		UINT32_t	rsv1	:13;	/*!< <31:19> 				*/
	}b;
}DMACCxConfiguration_t;


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/*
	for DMAC Interrupt register
	DMACIntStatus			RO	1: exist interrupt		0: no interrupt
	DMACIntTCStatus			RO	1: exist interrupt		0: no interrupt
	DMACIntTCClear			WO	1: clear interrupt		0: don't care
	DMACIntErrorStatus		RO	1: exist interrupt		0: no interrupt
	DMACIntErrClr			WO	1: clear interrupt		0: don't care
	DMACRawIntTCStatus		RO	1: exist interrupt		0: no interrupt
	DMACRawIntErrorStatus	RO	1: exist interrupt		0: no interrupt
	DMACEnbldChns			RO	1: Enable DMA			0: Disable DMA
 */
# define CDMAIntxxx_B_CHx_T			CBIT_TRUE
# define CDMAIntxxx_B_CHx_F			CBIT_FALSE

/* for DMACSoftBReq, DMACSoftSReq	*/
# define CDMACCSoftxReq_B_T			CBIT_TRUE		/*!< request DMA	*/
# define CDMACCSoftxReq_B_F			CBIT_FALSE		/*!< -				*/

/* for DMACConfiguration	*/
# define CDMACConfiguration_B_E_T	CBIT_TRUE		/*!< active DMAC	*/
# define CDMACConfiguration_B_E_F	CBIT_FALSE		/*!< stop DMAC		*/
# define CDMACConfiguration_B_M1_T	CBIT_TRUE		/*!< -				*/
# define CDMACConfiguration_B_M1_F	CBIT_FALSE		/*!< little endian	*/
# define CDMACConfiguration_B_M2_T	CBIT_TRUE		/*!< -				*/
# define CDMACConfiguration_B_M2_F	CBIT_FALSE		/*!< little endian	*/

/* for DMACCxLLI	*/
# define DMACCxLLI_B_LM_T			CBIT_TRUE		/*!< AHB Master DMA2	*/
# define DMACCxLLI_B_LM_F			CBIT_FALSE		/*!< AHB Master DMA1	*/

/* for DMACCxControl	*/
# define CDMACCxControl_B_Burst_1		0x0			/*!< burst size 1		*/
# define CDMACCxControl_B_Burst_4		0x1			/*!< burst size 4		*/
# define CDMACCxControl_B_Burst_8		0x2			/*!< burst size 8		*/
# define CDMACCxControl_B_Burst_16		0x3			/*!< burst size 16		*/
# define CDMACCxControl_B_Burst_32		0x4			/*!< burst size 32		*/
# define CDMACCxControl_B_Burst_64		0x5			/*!< burst size 64		*/
# define CDMACCxControl_B_Burst_128		0x6			/*!< burst size 128		*/
# define CDMACCxControl_B_Burst_256		0x7			/*!< burst size 256		*/
# define CDMACCxControl_B_width_1BYTE	0x0			/*!< transfer size 1byte*/
# define CDMACCxControl_B_width_2BYTE	0x1			/*!< transfer size 2byte*/
# define CDMACCxControl_B_width_4BYTE	0x2			/*!< transfer size 4byte*/
# define CDMACCxControl_B_S_T			CBIT_TRUE	/*!< Src DMA2			*/
# define CDMACCxControl_B_S_F			CBIT_FALSE	/*!< Src DMA1			*/
# define CDMACCxControl_B_D_T			CBIT_TRUE	/*!< Dst DMA2			*/
# define CDMACCxControl_B_D_F			CBIT_FALSE	/*!< Dst DMA1			*/
# define CDMACCxControl_B_SI_T			CBIT_TRUE	/*!< Src address fix	*/
# define CDMACCxControl_B_SI_F			CBIT_FALSE	/*!< Src address inc	*/
# define CDMACCxControl_B_DI_T			CBIT_TRUE	/*!< Dst address fix	*/
# define CDMACCxControl_B_DI_F			CBIT_FALSE	/*!< Dst address inc	*/
# define CDMACCxControl_B_Prot1_T		CBIT_TRUE	/*!< privilege			*/
# define CDMACCxControl_B_Prot1_F		CBIT_FALSE	/*!< user				*/
# define CDMACCxControl_B_Prot2_T		CBIT_TRUE	/*!< enable buffer		*/
# define CDMACCxControl_B_Prot2_F		CBIT_FALSE	/*!< disable buffer		*/
# define CDMACCxControl_B_Prot3_T		CBIT_TRUE	/*!< enable cache		*/
# define CDMACCxControl_B_Prot3_F		CBIT_FALSE	/*!< disable cache		*/
# define CDMACCxControl_B_I_T			CBIT_TRUE	/*!< enable scatter		*/
# define CDMACCxControl_B_I_F			CBIT_FALSE	/*!< disable scatter	*/

/* for DMACCxConfiguration	*/
# define CDMACCxConfiguration_B_E_T						CBIT_TRUE	/*!< enable ch		*/
# define CDMACCxConfiguration_B_E_F						CBIT_FALSE	/*!< disable ch		*/
# define CDMACCxConfiguration_B_Peripheral_UART0_TX		0x0			/*!< uart tx			*/
# define CDMACCxConfiguration_B_Peripheral_UART0_RX		0x1			/*!< uart rx			*/
# define CDMACCxConfiguration_B_Peripheral_NANDC0		0x4			/*!< nand controler	*/
# define CDMACCxConfiguration_B_Peripheral_CMSI			0x5			/*!< cmsi				*/
# define CDMACCxConfiguration_B_Peripheral_SDHC_CC_W	0x6			/*!< sdhc cc write	*/
# define CDMACCxConfiguration_B_Peripheral_SDHC_CC_R	0x7			/*!< sdhc cc read		*/
# define CDMACCxConfiguration_B_Peripheral_SDHC_SD_W	0x8			/*!< sdhc sd write	*/
# define CDMACCxConfiguration_B_Peripheral_SDHC_SD_R	0x9			/*!< sdhc sd read		*/
# define CDMACCxConfiguration_B_Peripheral_I2S0			0xA			/*!< i2s0				*/
# define CDMACCxConfiguration_B_Peripheral_I2S1			0xB			/*!< i2s1				*/
# define CDMACCxConfiguration_B_Peripheral_LCDDA		0xE			/*!< lcdda			*/
# define CDMACCxConfiguration_B_FlowCntrl_MtoM			0x0			/*!< Memory to Memory			*/
# define CDMACCxConfiguration_B_FlowCntrl_MtoP			0x1			/*!< Memory to Peripheral		*/
# define CDMACCxConfiguration_B_FlowCntrl_PtoM			0x2			/*!< Peripheral to Memory		*/
# define CDMACCxConfiguration_B_FlowCntrl_PtoP			0x3			/*!< Peripheral to Peripheral	*/
# define CDMACCxConfiguration_B_IE_T					CBIT_TRUE	/*!< enable interrupt		*/
# define CDMACCxConfiguration_B_IE_F					CBIT_FALSE	/*!< disable interrupt	*/
# define CDMACCxConfiguration_B_ITC_T					CBIT_TRUE	/*!< enable interrupt		*/
# define CDMACCxConfiguration_B_ITC_F					CBIT_FALSE	/*!< disable interrupt	*/
# define CDMACCxConfiguration_B_Lock_T					CBIT_TRUE	/*!< enable				*/
# define CDMACCxConfiguration_B_Lock_F					CBIT_FALSE	/*!< disable				*/
# define CDMACCxConfiguration_B_Active_T				CBIT_TRUE	/*!< exist FIFO			*/
# define CDMACCxConfiguration_B_Active_F				CBIT_FALSE	/*!< no FIFO				*/
# define CDMACCxConfiguration_B_Halt_T					CBIT_TRUE	/*!< accept DMA request	*/
# define CDMACCxConfiguration_B_Halt_F					CBIT_FALSE	/*!< ignore DMA request	*/


/* ************************************************************************ */
#endif	/* _register_dmac_typedefs_h_	*/
