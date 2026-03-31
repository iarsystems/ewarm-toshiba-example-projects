#ifndef _register_dmac_h_
#define _register_dmac_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : DMAC Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file register_dmac.h

	\author TOSHIBA CORPORATION
	\brief Header file of DMAC register's macro define

	\date 2008/08/11 New
	\date 2008/10/24 A910 Sample version 1.0
 */
/* ************************************************************************ */

/* ************************************************************************ */

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
#define CDMAIntxxx_Reserved_MASK	0xFFFFFF00		/* DMAIntxxx<31:8>	*/
# define CDMAIntxxx_Reserved		0x00000000
#define CDMAIntxxx_CH7_MASK			0x00000080
# define CDMAIntxxx_CH7_T			0x00000080
# define CDMAIntxxx_CH7_F			0x00000000
#define CDMAIntxxx_CH6_MASK			0x00000040
# define CDMAIntxxx_CH6_T			0x00000040
# define CDMAIntxxx_CH6_F			0x00000000
#define CDMAIntxxx_CH5_MASK			0x00000020
# define CDMAIntxxx_CH5_T			0x00000020
# define CDMAIntxxx_CH5_F			0x00000000
#define CDMAIntxxx_CH4_MASK			0x00000010
# define CDMAIntxxx_CH4_T			0x00000010
# define CDMAIntxxx_CH4_F			0x00000000
#define CDMAIntxxx_CH3_MASK			0x00000008
# define CDMAIntxxx_CH3_T			0x00000008
# define CDMAIntxxx_CH3_F			0x00000000
#define CDMAIntxxx_CH2_MASK			0x00000004
# define CDMAIntxxx_CH2_T			0x00000004
# define CDMAIntxxx_CH2_F			0x00000000
#define CDMAIntxxx_CH1_MASK			0x00000002
# define CDMAIntxxx_CH1_T			0x00000002
# define CDMAIntxxx_CH1_F			0x00000000
#define CDMAIntxxx_CH0_MASK			0x00000001
# define CDMAIntxxx_CH0_T			0x00000001
# define CDMAIntxxx_CH0_F			0x00000000

/* for DMACSoftBReq	*/
#define CDMACSoftBReq_Reserved_MASK		0xFFFFB00C	/* <31:15>,<13:12>,<3:2>	*/
#define CDMACSoftBReq_Reserved			0x00000000
#define CDMACSoftBReq_LCDDA_MASK		0x00004000	/* <14>	*/
# define CDMACSoftBReq_LCDDA_T			0x00004000	/* request	*/
# define CDMACSoftBReq_LCDDA_F			0x00000000	/* don't care	*/
#define CDMACSoftBReq_I2S1_MASK			0x00000800	/* <11>	*/
# define CDMACSoftBReq_I2S1_T			0x00000800	/* request	*/
# define CDMACSoftBReq_I2S1_F			0x00000000	/* don't care	*/
#define CDMACSoftBReq_I2S0_MASK			0x00000400	/* <10>	*/
# define CDMACSoftBReq_I2S0_T			0x00000400	/* request	*/
# define CDMACSoftBReq_I2S0_F			0x00000000	/* don't care	*/
#define CDMACSoftBReq_SDHC_SD_R_MASK	0x00000200	/* <9>	*/
# define CDMACSoftBReq_SDHC_SD_R_T		0x00000200	/* request	*/
# define CDMACSoftBReq_SDHC_SD_R_F		0x00000000	/* don't care	*/
#define CDMACSoftBReq_SDHC_SD_W_MASK	0x00000100	/* <8>	*/
# define CDMACSoftBReq_SDHC_SD_W_T		0x00000100	/* request	*/
# define CDMACSoftBReq_SDHC_SD_W_F		0x00000000	/* don't care	*/
#define CDMACSoftBReq_SDHC_CC_R_MASK	0x00000080	/* <7>	*/
# define CDMACSoftBReq_SDHC_CC_R_T		0x00000080	/* request	*/
# define CDMACSoftBReq_SDHC_CC_R_F		0x00000000	/* don't care	*/
#define CDMACSoftBReq_SDHC_CC_W_MASK	0x00000040	/* <6>	*/
# define CDMACSoftBReq_SDHC_CC_W_T		0x00000040	/* request	*/
# define CDMACSoftBReq_SDHC_CC_W_F		0x00000000	/* don't care	*/
#define CDMACSoftBReq_CMSI_MASK			0x00000020	/* <5>	*/
# define CDMACSoftBReq_CMSI_T			0x00000020	/* request	*/
# define CDMACSoftBReq_CMSI_F			0x00000000	/* don't care	*/
#define CDMACSoftBReq_NANDC0_MASK		0x00000010	/* <4>	*/
# define CDMACSoftBReq_NANDC0_T			0x00000010	/* request	*/
# define CDMACSoftBReq_NANDC0_F			0x00000000	/* don't care	*/
#define CDMACSoftBReq_UART0RX_MASK		0x00000002	/* <1>	*/
# define CDMACSoftBReq_UART0RX_T		0x00000002	/* request	*/
# define CDMACSoftBReq_UART0RX_F		0x00000000	/* don't care	*/
#define CDMACSoftBReq_UART0TX_MASK		0x00000001	/* <0>	*/
# define CDMACSoftBReq_UART0TX_T		0x00000001	/* request	*/
# define CDMACSoftBReq_UART0TX_F		0x00000000	/* don't care	*/

/* for DMACSoftSReq	*/
#define CDMACSoftSReq_Reserved_MASK		0xFFFFBFFC	/* <31:15>,<13:2>	*/
#define CDMACSoftSReq_Reserved			0x00000000	/* don't care	*/
#define CDMACSoftSReq_LCDDA_MASK		0x00004000	/* <14>	*/
# define CDMACSoftSReq_LCDDA_T			0x00004000	/* request	*/
# define CDMACSoftSReq_LCDDA_F			0x00000000	/* don't care	*/
#define CDMACSoftSReq_UART0RX_MASK		0x00000002	/* <1>	*/
# define CDMACSoftSReq_UART0RX_T		0x00000002	/* request	*/
# define CDMACSoftSReq_UART0RX_F		0x00000000	/* don't care	*/
#define CDMACSoftSReq_UART0TX_MASK		0x00000001	/* <0>	*/
# define CDMACSoftSReq_UART0TX_T		0x00000001	/* request	*/
# define CDMACSoftSReq_UART0TX_F		0x00000000	/* don't care	*/

/* for DMACConfiguration	*/
#define CDMACConfiguration_Reserved_MASK	0xFFFFFFF8	/* <31:3>	*/
# define CDMACConfiguration_Reserved		0x00000000
#define CDMACConfiguration_M2_MASK		0x00000004	/* <2>	*/
# define CDMACConfiguration_M2_T		0x00000004	/* reserved	*/
# define CDMACConfiguration_M2_F		0x00000000	/* DMA2:little endian	*/
#define CDMACConfiguration_M1_MASK		0x00000002	/* <1>	*/
# define CDMACConfiguration_M1_T		0x00000002	/* reserved	*/
# define CDMACConfiguration_M1_F		0x00000000	/* DMA1:little endian	*/
#define CDMACConfiguration_E_MASK		0x00000001	/* <0>	*/
# define CDMACConfiguration_E_T			0x00000001	/* active	*/
# define CDMACConfiguration_E_F			0x00000000	/* stop	*/

/* for DMACCxSrcAddr	*/
/* for DMACCxDestAddr	*/

/* for DMACCxLLI	*/
#define CDMACCxLLI_Reserved_MASK			0x00000002	/* DMACCxLLI<1>	*/
# define CDMACCxLLI_Reserved				0x00000000
#define CDMACCxLLI_LLI_MASK					0xFFFFFFFC	/* DMACCxLLI<31:2>	*/
# define CDMACCxLLI_OFF						0x00000000	/* LLI off	*/
#define CDMACCxLLI_LM_MASK					0x00000001	/* DMACCxLLI<0>	*/
# define CDMACCxLLI_LM_T					0x00000001	/* DMA2	*/
# define CDMACCxLLI_LM_F					0x00000000	/* DMA1	*/

/* for DMACCxControl	*/
#define CDMACCxControl_I_MASK			0x80000000	/* <31>				*/
# define CDMACCxControl_I_T				0x80000000	/* Enable interrupt */
# define CDMACCxControl_I_F				0x00000000	/* Disable interupt	*/
#define CDMACCxControl_Port3_MASK		0x40000000	/* <30>				*/
# define CDMACCxControl_Port3_T			0x40000000	/* Enable cache		*/
# define CDMACCxControl_Port3_F			0x00000000	/* Disable cache	*/
#define CDMACCxControl_Port2_MASK		0x20000000	/* <29>				*/
# define CDMACCxControl_Port2_T			0x20000000	/* Enable cache		*/
# define CDMACCxControl_Port2_F			0x00000000	/* Disable cache	*/
#define CDMACCxControl_Port1_MASK		0x10000000	/* <28>				*/
# define CDMACCxControl_Port1_T			0x10000000	/* user				*/
# define CDMACCxControl_Port1_F			0x00000000	/* special? 		*/
#define CDMACCxControl_DI_MASK			0x08000000	/* <27>				*/
# define CDMACCxControl_DI_T			0x08000000	/* Des inc			*/
# define CDMACCxControl_DI_F			0x00000000	/* Des fix			*/
#define CDMACCxControl_SI_MASK			0x04000000	/* <26>				*/
# define CDMACCxControl_SI_T			0x04000000	/* Src inc			*/
# define CDMACCxControl_SI_F			0x00000000	/* Src fix			*/
#define CDMACCxControl_D_MASK			0x02000000	/* <25>				*/
# define CDMACCxControl_D_T				0x02000000	/* Dst select DMA2	*/
# define CDMACCxControl_D_F				0x00000000	/* Dst select DMA1	*/
#define CDMACCxControl_S_MASK			0x01000000	/* <24>				*/
# define CDMACCxControl_S_T				0x01000000	/* Src select DMA2	*/
# define CDMACCxControl_S_F				0x00000000	/* Src select DMA1	*/
#define CDMACCxControl_Dwidth_MASK		0x00E00000	/* <23:21>			*/
# define CDMACCxControl_Dwidth_8		0x00000000	/* 8bit 			*/
# define CDMACCxControl_Dwidth_16		0x00200000	/* 16bit			*/
# define CDMACCxControl_Dwidth_32		0x00400000	/* 32bit			*/
#define CDMACCxControl_Swidth_MASK		0x001C0000	/* <20:18>			*/
# define CDMACCxControl_Swidth_8		0x00000000	/* 8bit 			*/
# define CDMACCxControl_Swidth_16		0x00040000	/* 16bit			*/
# define CDMACCxControl_Swidth_32		0x00080000	/* 32bit			*/
#define CDMACCxControl_DBSize_MASK		0x00038000	/* <17:15>			*/
# define CDMACCxControl_DBSize_1		0x00000000	/* 	*/
# define CDMACCxControl_DBSize_4		0x00008000	/* 	*/
# define CDMACCxControl_DBSize_8		0x00010000	/* 	*/
# define CDMACCxControl_DBSize_16		0x00018000	/* 	*/
# define CDMACCxControl_DBSize_32		0x00020000	/* 	*/
# define CDMACCxControl_DBSize_64		0x00028000	/* 	*/
# define CDMACCxControl_DBSize_128		0x00030000	/* 	*/
# define CDMACCxControl_DBSize_256		0x00038000	/* 	*/
#define CDMACCxControl_SBSize_MASK		0x00007000	/* <14:12>			*/
# define CDMACCxControl_SBSize_1		0x00000000	/* 	*/
# define CDMACCxControl_SBSize_4		0x00001000	/* 	*/
# define CDMACCxControl_SBSize_8		0x00002000	/* 	*/
# define CDMACCxControl_SBSize_16		0x00003000	/* 	*/
# define CDMACCxControl_SBSize_32		0x00004000	/* 	*/
# define CDMACCxControl_SBSize_64		0x00005000	/* 	*/
# define CDMACCxControl_SBSize_128		0x00006000	/* 	*/
# define CDMACCxControl_SBSize_256		0x00007000	/* 	*/
#define CDMACCxControl_Transfersize_MASK	0x00000FFF	/* <11:0>		*/

/* for DMACCxConfiguration	*/
#define CDMACCxConfiguration_Reserved_MASK		0xFFF80420	/* <31:19>,<10>,<5> */
#define CDMACCxConfiguration_Reserved			0x00000000
#define CDMACCxConfiguration_Halt_MASK			0x00040000	/* <18> 		*/
# define CDMACCxConfiguration_Halt_T			0x00040000	/* ignore DMA request	*/
# define CDMACCxConfiguration_Halt_F			0x00000000	/* accept DMA request	*/
#define CDMACCxConfiguration_Active_MASK		0x00020000	/* <17> 		*/
# define CDMACCxConfiguration_Active_T			0x00020000	/* exist data in FIFO	*/
# define CDMACCxConfiguration_Active_F			0x00000000	/* no data in FIFO	*/
#define CDMACCxConfiguration_Lock_MASK			0x00010000	/* <16> 		*/
# define CDMACCxConfiguration_Lock_T			0x00010000	/* Enable lock trans	*/
# define CDMACCxConfiguration_Lock_F			0x00000000	/* Disable lock trans	*/
#define CDMACCxConfiguration_ITC_MASK			0x00008000	/* <15> 		*/
# define CDMACCxConfiguration_ITC_T				0x00008000	/* Enable interrupt TCEnd	*/
# define CDMACCxConfiguration_ITC_F				0x00000000	/* Disable interrupt TCEnd	*/
#define CDMACCxConfiguration_IE_MASK			0x00004000	/* <14> 		*/
# define CDMACCxConfiguration_IE_T				0x00004000	/* Enable interrupt Error	*/
# define CDMACCxConfiguration_IE_F				0x00000000	/* Disable interrupt Error	*/
#define CDMACCxConfiguration_FlowCntrl_MASK		0x00003800	/* <13:11> 		*/
# define CDMACCxConfiguration_FlowCntrl_MtoM	0x00000000	/* Memory to Memory			*/
# define CDMACCxConfiguration_FlowCntrl_MtoP	0x00000800	/* Memory to Peripheral		*/
# define CDMACCxConfiguration_FlowCntrl_PtoM	0x00001000	/* Peripheral to Memory		*/
# define CDMACCxConfiguration_FlowCntrl_PtoP	0x00001800	/* Peripheral to Peripheral	*/
#define CDMACCxConfiguration_DestP_MASK			0x000003C0	/* <9:6> 		*/
# define CDMACCxConfiguration_DestP_UART0_TX	0x00000000
# define CDMACCxConfiguration_DestP_UART0_RX	0x00000040
# define CDMACCxConfiguration_DestP_rsv1		0x00000080
# define CDMACCxConfiguration_DestP_rsv2		0x000000C0
# define CDMACCxConfiguration_DestP_NANDC0		0x00000100
# define CDMACCxConfiguration_DestP_CMSI		0x00000140
# define CDMACCxConfiguration_DestP_SDHC_CC_IN	0x00000180
# define CDMACCxConfiguration_DestP_SDHC_CC_OUT	0x000001C0
# define CDMACCxConfiguration_DestP_SDHC_BUF_W	0x00000200
# define CDMACCxConfiguration_DestP_SDHC_BUF_R	0x00000240
# define CDMACCxConfiguration_DestP_IS20		0x00000280
# define CDMACCxConfiguration_DestP_IS21		0x000002C0
# define CDMACCxConfiguration_DestP_rsv3		0x00000300
# define CDMACCxConfiguration_DestP_rsv4		0x00000340
# define CDMACCxConfiguration_DestP_LCDDA		0x00000380
# define CDMACCxConfiguration_DestP_rsv5		0x000003C0
#define CDMACCxConfiguration_SrcP_MASK			0x0000001E	/* <4:1> 		*/
# define CDMACCxConfiguration_SrcP_UART0_TX		0x00000000
# define CDMACCxConfiguration_SrcP_UART0_RX		0x00000002
# define CDMACCxConfiguration_SrcP_rsv1			0x00000004
# define CDMACCxConfiguration_SrcP_rsv2			0x00000006
# define CDMACCxConfiguration_SrcP_NANDC0		0x00000008
# define CDMACCxConfiguration_SrcP_CMSI			0x0000000A
# define CDMACCxConfiguration_SrcP_SDHC_CC_IN	0x0000000C
# define CDMACCxConfiguration_SrcP_SDHC_CC_OUT	0x0000000E
# define CDMACCxConfiguration_SrcP_SDHC_BUF_W	0x00000010
# define CDMACCxConfiguration_SrcP_SDHC_BUF_R	0x00000012
# define CDMACCxConfiguration_SrcP_IS20			0x00000014
# define CDMACCxConfiguration_SrcP_IS21			0x00000016
# define CDMACCxConfiguration_SrcP_rsv3			0x00000018
# define CDMACCxConfiguration_SrcP_rsv4			0x0000001A
# define CDMACCxConfiguration_SrcP_LCDDA		0x0000001C
# define CDMACCxConfiguration_SrcP_rsv5			0x0000001E
#define CDMACCxConfiguration_E_MASK				0x00000001	/* <0> 			*/
# define CDMACCxConfiguration_E_T				0x00000001	/* Enable channel	*/
# define CDMACCxConfiguration_E_F				0x00000000	/* Disable channel	*/

/* ************************************************************************ */
#endif /* _register_dmac_h_ */
