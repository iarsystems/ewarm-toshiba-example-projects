#ifndef _dmac_register_init_h_
#define _dmac_register_init_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : LCDDA Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file dmac_register_init.h
	\brief Header file of DMAC register's initialize macro define

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
#include "register_dmac.h"


/*
 * --------------------------------------------------------------------------
 *   type Define
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Function
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/* for DMACConfiguration	*/
#define CDMACConfiguration_Init	\
	( \
	  CDMACConfiguration_Reserved	| \
	  CDMACConfiguration_M2_F		/* little endian	*/ | \
	  CDMACConfiguration_M1_F		/* little endian	*/ | \
	  CDMACConfiguration_E_T 		/* active			*/ \
	  )

/* for DMACIntTCClear	*/
#define CDMACIntTCClear_Init		\
	( \
	  CDMAIntxxx_Reserved | \
	  CDMAIntxxx_CH7_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH6_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH5_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH4_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH3_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH2_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH1_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH0_T /* clear interrupt	*/ \
	  )

/* for DMACIntErrClr	*/
#define CDMACIntErrClr_Init	\
	( \
	  CDMAIntxxx_Reserved | \
	  CDMAIntxxx_CH7_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH6_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH5_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH4_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH3_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH2_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH1_T /* clear interrupt	*/ | \
	  CDMAIntxxx_CH0_T /* clear interrupt	*/ \
	  )

/* ------------------------------------------------------------------------ */
/* for DMACCxControl						*/
/* Src 32bit Inc, Dst 32bit Inc 			*/
#define CDMACCxControl_S32Inc_D32Inc_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_T			/* dst inc			*/ | \
	  CDMACCxControl_SI_T			/* src inc			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_32		/* 32bit			*/ | \
	  CDMACCxControl_Swidth_32		/* 32bit			*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 32bit Fix, Dst 32bit Inc				*/
#define CDMACCxControl_S32Fix_D32Inc_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_T			/* dst inc			*/ | \
	  CDMACCxControl_SI_F			/* src fix			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_32		/* 32bit			*/ | \
	  CDMACCxControl_Swidth_32		/* 32bit			*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 32bit Inc, Dst 32bit Fix				*/
#define CDMACCxControl_S32Inc_D32Fix_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_F			/* dst fix			*/ | \
	  CDMACCxControl_SI_T			/* src inc			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_32		/* 32bit			*/ | \
	  CDMACCxControl_Swidth_32		/* 32bit			*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 32bit Fix, Dst 32bit Fix				*/
#define CDMACCxControl_S32Fix_D32Fix_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_F			/* dst fix			*/ | \
	  CDMACCxControl_SI_F			/* src fix			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_32		/* 32bit			*/ | \
	  CDMACCxControl_Swidth_32		/* 32bit			*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )

/* Src 16bit Inc, Dst 16bit Inc 			*/
#define CDMACCxControl_S16Inc_D16Inc_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_T			/* dst inc			*/ | \
	  CDMACCxControl_SI_T			/* src inc			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_16		/* 16bit			*/ | \
	  CDMACCxControl_Swidth_16		/* 16bit			*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 16bit Fix, Dst 16bit Inc				*/
#define CDMACCxControl_S16Fix_D16Inc_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_T			/* dst inc			*/ | \
	  CDMACCxControl_SI_F			/* src fix			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_16		/* 16bit			*/ | \
	  CDMACCxControl_Swidth_16		/* 16bit			*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 16bit Inc, Dst 16bit Fix				*/
#define CDMACCxControl_S16Inc_D16Fix_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_F			/* dst fix			*/ | \
	  CDMACCxControl_SI_T			/* src inc			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_16		/* 16bit			*/ | \
	  CDMACCxControl_Swidth_16		/* 16bit			*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 16bit Fix, Dst 16bit Fix				*/
#define CDMACCxControl_S16Fix_D16Fix_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_F			/* dst fix			*/ | \
	  CDMACCxControl_SI_F			/* src fix			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_16		/* 16bit			*/ | \
	  CDMACCxControl_Swidth_16		/* 16bit			*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )

/* Src 8bit Inc, Dst 8bit Inc 			*/
#define CDMACCxControl_S8Inc_D8Inc_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_T			/* dst inc			*/ | \
	  CDMACCxControl_SI_T			/* src inc			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_8		/* 8bit				*/ | \
	  CDMACCxControl_Swidth_8		/* 8bit				*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 8bit Fix, Dst 8bit Inc				*/
#define CDMACCxControl_S8Fix_D8Inc_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_T			/* dst inc			*/ | \
	  CDMACCxControl_SI_F			/* src fix			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_8		/* 8bit				*/ | \
	  CDMACCxControl_Swidth_8		/* 8bit				*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 8bit Inc, Dst 8bit Fix				*/
#define CDMACCxControl_S8Inc_D8Fix_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_F			/* dst fix			*/ | \
	  CDMACCxControl_SI_T			/* src inc			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_8		/* 8bit				*/ | \
	  CDMACCxControl_Swidth_8		/* 8bit				*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* Src 8bit Fix, Dst 8bit Fix				*/
#define CDMACCxControl_S8Fix_D8Fix_Init	\
	( \
	  CDMACCxControl_I_T 			/* enable interrupt	*/ | \
	  CDMACCxControl_Port3_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port2_F 		/* disable cache	*/ | \
	  CDMACCxControl_Port1_F 		/* disable cache	*/ | \
	  CDMACCxControl_DI_F			/* dst fix			*/ | \
	  CDMACCxControl_SI_F			/* src fix			*/ | \
	  CDMACCxControl_D_F			/* Dst Master DMA1	*/ | \
	  CDMACCxControl_S_T			/* Src Master DMA2	*/ | \
	  CDMACCxControl_Dwidth_8		/* 8bit				*/ | \
	  CDMACCxControl_Swidth_8		/* 8bit				*/ | \
	  CDMACCxControl_DBSize_32		/* burst32			*/ | \
	  CDMACCxControl_SBSize_32		/* burst32			*/ | \
	  0								/* input size		*/ \
	  )
/* ------------------------------------------------------------------------ */
/* for CDMACxConfiguration						*/
/* Memory to Memory								*/
#define CDMACCxConfiguration_MtoM_Init	\
	( \
	  CDMACCxConfiguration_Reserved | \
	  CDMACCxConfiguration_Halt_F	/* accept DMA		*/ | \
	  CDMACCxConfiguration_Active_F	/* -				*/ | \
	  CDMACCxConfiguration_Lock_F	/* disable			*/ | \
	  CDMACCxConfiguration_ITC_T	/* enable interrupt	*/ | \
	  CDMACCxConfiguration_IE_T		/* enable interrupt	*/ | \
	  0x00 << 6						/* Dst Peripheral	*/ | \
	  0x00 << 1						/* Src Peripheral	*/ | \
	  CDMACCxConfiguration_FlowCntrl_MtoM /* M to M		*/ | \
	  CDMACCxConfiguration_E_F 		/* disable ch		*/ \
	  )
/* Memory to Peripheral							*/
#define CDMACCxConfiguration_MtoP_Init	\
	( \
	  CDMACCxConfiguration_Reserved | \
	  CDMACCxConfiguration_Halt_F	/* accept DMA		*/ | \
	  CDMACCxConfiguration_Active_F	/* -				*/ | \
	  CDMACCxConfiguration_Lock_F	/* disable			*/ | \
	  CDMACCxConfiguration_ITC_T	/* enable interrupt	*/ | \
	  CDMACCxConfiguration_IE_T		/* enable interrupt	*/ | \
	  0x00 << 6						/* Dst Peripheral	*/ | \
	  0x00 << 1						/* Src Peripheral	*/ | \
	  CDMACCxConfiguration_FlowCntrl_MtoP /* M to P		*/ | \
	  CDMACCxConfiguration_E_F 		/* disable ch		*/ \
	  )
/* Peripheral to Memory							*/
#define CDMACCxConfiguration_PtoM_Init	\
	( \
	  CDMACCxConfiguration_Reserved | \
	  CDMACCxConfiguration_Halt_F	/* accept DMA		*/ | \
	  CDMACCxConfiguration_Active_F	/* -				*/ | \
	  CDMACCxConfiguration_Lock_F	/* disable			*/ | \
	  CDMACCxConfiguration_ITC_T	/* enable interrupt	*/ | \
	  CDMACCxConfiguration_IE_T		/* enable interrupt	*/ | \
	  0x00 << 6						/* Dst Peripheral	*/ | \
	  0x00 << 1						/* Src Peripheral	*/ | \
	  CDMACCxConfiguration_FlowCntrl_PtoM /* P to M		*/ | \
	  CDMACCxConfiguration_E_F 		/* disable ch		*/ \
	  )
/* Peripheral to Peripheral						*/
#define CDMACCxConfiguration_PtoP_Init	\
	( \
	  CDMACCxConfiguration_Reserved | \
	  CDMACCxConfiguration_Halt_F	/* accept DMA		*/ | \
	  CDMACCxConfiguration_Active_F	/* -				*/ | \
	  CDMACCxConfiguration_Lock_F	/* disable			*/ | \
	  CDMACCxConfiguration_ITC_T	/* enable interrupt	*/ | \
	  CDMACCxConfiguration_IE_T		/* enable interrupt	*/ | \
	  0x00 << 6						/* Dst Peripheral	*/ | \
	  0x00 << 1						/* Src Peripheral	*/ | \
	  CDMACCxConfiguration_FlowCntrl_PtoP /* P to P		*/ | \
	  CDMACCxConfiguration_E_F 		/* disable ch		*/ \
	  )
/* ------------------------------------------------------------------------ */

/* DMAC ch0	SrcM(inc)toDstM(inc) 32bit	*/
#define CDMACC0Control_Init			CDMACCxControl_S32Inc_D32Inc_Init
#define CDMACC0Configuration_Init	CDMACCxConfiguration_MtoM_Init

/* DMAC ch1	SrcM(inc)toDstM(inc) 32bit LLI	*/
#define CDMACC1Control_Init			CDMACCxControl_S32Inc_D32Inc_Init
#define CDMACC1Configuration_Init	CDMACCxConfiguration_MtoM_Init

/* DMAC ch2	SrcM(fix)toDstM(inc) 32bit	*/
#define CDMACC2Control_Init			CDMACCxControl_S32Fix_D32Inc_Init
#define CDMACC2Configuration_Init	CDMACCxConfiguration_MtoM_Init

/* DMAC ch3	SrcM(inc)toDstM(fix) 32bit	*/
#define CDMACC3Control_Init			CDMACCxControl_S32Inc_D32Fix_Init
#define CDMACC3Configuration_Init	CDMACCxConfiguration_MtoM_Init


/* DMAC ch4	SrcM(inc)toDstP(fix) 32bit	*/
#define CDMACC4Control_Init			CDMACCxControl_S32Inc_D32Fix_Init
#define CDMACC4Configuration_Init	CDMACCxConfiguration_MtoP_Init

/* DMAC ch5	SrcP(fix)toDstM(inc) 32bit	*/
#define CDMACC5Control_Init			CDMACCxControl_S32Fix_D32Inc_Init
#define CDMACC5Configuration_Init	CDMACCxConfiguration_PtoM_Init

/* DMAC ch6	SrcP(fix)toDstP(fix) 32bit	*/
#define CDMACC6Control_Init			CDMACCxControl_S32Fix_D32Fix_Init
#define CDMACC6Configuration_Init	CDMACCxConfiguration_PtoP_Init

/* DMAC ch7	DstM(inc)toSrcM(inc) 16bit	*/
#define CDMACC7Control_Init			CDMACCxControl_S16Inc_D16Inc_Init
#define CDMACC7Configuration_Init	CDMACCxConfiguration_MtoM_Init


/* ************************************************************************ */
#endif	/* _dmac_register_init_h_ */
