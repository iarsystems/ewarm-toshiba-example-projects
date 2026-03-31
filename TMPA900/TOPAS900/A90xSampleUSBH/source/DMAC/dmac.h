#ifndef _dmac_h_
#define _dmac_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : DMAC Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file dmac.h
	\brief Header file of all dmac.c

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

#include "register_dmac.h"
#include "register_dmac_typedefs.h"
#include "dmac_register_init.h"


/*
 * --------------------------------------------------------------------------
 *   Style Define Area
 * --------------------------------------------------------------------------
 */
typedef enum {
	CDMAC_CH0,
	CDMAC_CH1,
	CDMAC_CH2,
	CDMAC_CH3,
	CDMAC_CH4,
	CDMAC_CH5,
	CDMAC_CH6,
	CDMAC_CH7,
} DMAC_Channel_t;

typedef struct {
	volatile UINT32_t *srcaddr;				/* DMACCxSrcAddr		*/
	volatile UINT32_t *dstaddr;				/* DMACCxDstAddr		*/
	volatile UINT32_t *lli;					/* DMACCxLLI			*/
	volatile UINT32_t *control;				/* DMACCxControl		*/
	volatile UINT32_t *configuration;		/* DMACCxConfiguration	*/

	DMACCxControl_t			*control_work;
	DMACCxConfiguration_t	*configuration_work;
} DMACChannelInfo_t;

typedef struct {
	const UINT32_t *src_addr;
	UINT32_t *dst_addr;
	UINT32_t *next_lli;
	UINT32_t dmaccxcontrol;
} LLI_t;

/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#define E_DMAC_FALSE		FALSE		/* failed of DMAC process	*/
#define E_DMAC_TRUE			TRUE		/* succeed of DMAC process	*/

#define CDMAC_CH_MAX		8

#define CLLI_END			0x00000000

/*
 * --------------------------------------------------------------------------
 *   Variable Define
 * --------------------------------------------------------------------------
 */
extern void (*gInterruptFunc_DMA_ch0)(void);
extern void (*gInterruptFunc_DMA_ch1)(void);
extern void (*gInterruptFunc_DMA_ch2)(void);
extern void (*gInterruptFunc_DMA_ch3)(void);
extern void (*gInterruptFunc_DMA_ch4)(void);
extern void (*gInterruptFunc_DMA_ch5)(void);
extern void (*gInterruptFunc_DMA_ch6)(void);
extern void (*gInterruptFunc_DMA_ch7)(void);

extern void (*gInterruptFunc_DMAError_ch0)(void);
extern void (*gInterruptFunc_DMAError_ch1)(void);
extern void (*gInterruptFunc_DMAError_ch2)(void);
extern void (*gInterruptFunc_DMAError_ch3)(void);
extern void (*gInterruptFunc_DMAError_ch4)(void);
extern void (*gInterruptFunc_DMAError_ch5)(void);
extern void (*gInterruptFunc_DMAError_ch6)(void);
extern void (*gInterruptFunc_DMAError_ch7)(void);

extern DMACCxControl_t 			gDMACC0Control;
extern DMACCxControl_t 			gDMACC1Control;
extern DMACCxControl_t 			gDMACC2Control;
extern DMACCxControl_t 			gDMACC3Control;
extern DMACCxControl_t 			gDMACC4Control;
extern DMACCxControl_t 			gDMACC5Control;
extern DMACCxControl_t 			gDMACC6Control;
extern DMACCxControl_t 			gDMACC7Control;

extern DMACCxConfiguration_t	gDMACC0Configuration;
extern DMACCxConfiguration_t	gDMACC1Configuration;
extern DMACCxConfiguration_t	gDMACC2Configuration;
extern DMACCxConfiguration_t	gDMACC3Configuration;
extern DMACCxConfiguration_t	gDMACC4Configuration;
extern DMACCxConfiguration_t	gDMACC5Configuration;
extern DMACCxConfiguration_t	gDMACC6Configuration;
extern DMACCxConfiguration_t	gDMACC7Configuration;


/*
 * --------------------------------------------------------------------------
 *   Function
 * --------------------------------------------------------------------------
 */
extern void Interrupt_DMACIntTCStatus(void);

extern void dmac_init(void);
extern UINT32_t dmac_ch_init(const DMAC_Channel_t ch,
							 const UINT32_t* const pSrc,
							 UINT32_t* const pDst,
							 const UINT32_t size);
extern UINT32_t dmac_ch_lli_init(const DMAC_Channel_t ch,
								 const LLI_t* const plli,
								 const UINT32_t list_size);
extern UINT32_t dmac_ch_start(const DMAC_Channel_t ch, const UINT32_t mode);
extern void dmac_ch_stop(const DMAC_Channel_t ch);

extern UINT32_t dmac_check_address(const DMAC_Channel_t ch,
								   const UINT32_t* const pSrc,
								   UINT32_t* const pDst);
extern UINT32_t dmac_check_transfer_size(const DMAC_Channel_t ch,
										 UINT32_t* const size);
extern UINT32_t dmac_check_channel_enable(const DMAC_Channel_t ch);
extern void dmac_dummy_func(void);


/* ************************************************************************ */
#endif	/* _dmac_h_ */
