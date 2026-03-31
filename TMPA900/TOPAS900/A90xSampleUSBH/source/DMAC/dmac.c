/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : DMAC Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file dmac.c
	\brief Source Code of DMAC API Functions

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

#include "system_def.h"

#include "dmac.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#define CDMAC_ADDRCheck_x2		0x00000001
#define CDMAC_ADDRCheck_x4		0x00000003
#define CDMAC_ADDRCheck_SUCCESS	0x00000000


/*
 * --------------------------------------------------------------------------
 *   Style Define Area
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Variable Define
 * --------------------------------------------------------------------------
 */
void (*gInterruptFunc_DMA_ch0)(void);/*!< DMAC ch0 interruput function pointer*/
void (*gInterruptFunc_DMA_ch1)(void);/*!< DMAC ch1 interruput function pointer*/
void (*gInterruptFunc_DMA_ch2)(void);/*!< DMAC ch2 interruput function pointer*/
void (*gInterruptFunc_DMA_ch3)(void);/*!< DMAC ch3 interruput function pointer*/
void (*gInterruptFunc_DMA_ch4)(void);/*!< DMAC ch4 interruput function pointer*/
void (*gInterruptFunc_DMA_ch5)(void);/*!< DMAC ch5 interruput function pointer*/
void (*gInterruptFunc_DMA_ch6)(void);/*!< DMAC ch6 interruput function pointer*/
void (*gInterruptFunc_DMA_ch7)(void);/*!< DMAC ch7 interruput function pointer*/

void (*gInterruptFunc_DMAError_ch0)(void);		/*!< DMAC ch0 interruput error function pointer	*/
void (*gInterruptFunc_DMAError_ch1)(void);		/*!< DMAC ch1 interruput error function pointer	*/
void (*gInterruptFunc_DMAError_ch2)(void);		/*!< DMAC ch2 interruput error function pointer	*/
void (*gInterruptFunc_DMAError_ch3)(void);		/*!< DMAC ch3 interruput error function pointer	*/
void (*gInterruptFunc_DMAError_ch4)(void);		/*!< DMAC ch4 interruput error function pointer	*/
void (*gInterruptFunc_DMAError_ch5)(void);		/*!< DMAC ch5 interruput error function pointer	*/
void (*gInterruptFunc_DMAError_ch6)(void);		/*!< DMAC ch6 interruput error function pointer	*/
void (*gInterruptFunc_DMAError_ch7)(void);		/*!< DMAC ch7 interruput error function pointer	*/

DMACCxControl_t 		gDMACC0Control;	/*!< work buffer of DMACC0Control	*/
DMACCxControl_t 		gDMACC1Control;	/*!< work buffer of DMACC1Control	*/
DMACCxControl_t 		gDMACC2Control;	/*!< work buffer of DMACC2Control	*/
DMACCxControl_t 		gDMACC3Control;	/*!< work buffer of DMACC3Control	*/
DMACCxControl_t 		gDMACC4Control;	/*!< work buffer of DMACC4Control	*/
DMACCxControl_t 		gDMACC5Control;	/*!< work buffer of DMACC5Control	*/
DMACCxControl_t 		gDMACC6Control;	/*!< work buffer of DMACC6Control	*/
DMACCxControl_t 		gDMACC7Control;	/*!< work buffer of DMACC7Control	*/

DMACCxConfiguration_t	gDMACC0Configuration;	/*!< work buffer of DMACC0Configuration	*/
DMACCxConfiguration_t	gDMACC1Configuration;	/*!< work buffer of DMACC1Configuration	*/
DMACCxConfiguration_t	gDMACC2Configuration;	/*!< work buffer of DMACC2Configuration	*/
DMACCxConfiguration_t	gDMACC3Configuration;	/*!< work buffer of DMACC3Configuration	*/
DMACCxConfiguration_t	gDMACC4Configuration;	/*!< work buffer of DMACC4Configuration	*/
DMACCxConfiguration_t	gDMACC5Configuration;	/*!< work buffer of DMACC5Configuration	*/
DMACCxConfiguration_t	gDMACC6Configuration;	/*!< work buffer of DMACC6Configuration	*/
DMACCxConfiguration_t	gDMACC7Configuration;	/*!< work buffer of DMACC7Configuration	*/

static const DMACChannelInfo_t gDMACInfo[CDMAC_CH_MAX] = {
	{
		&DMACC0SrcAddr, &DMACC0DestAddr, &DMACC0LLI,
		&DMACC0Control, &DMACC0Configuration,
		&gDMACC0Control, &gDMACC0Configuration,
	},
	{
		&DMACC1SrcAddr, &DMACC1DestAddr, &DMACC1LLI,
		&DMACC1Control, &DMACC1Configuration,
		&gDMACC1Control, &gDMACC1Configuration,
	},
	{
		&DMACC2SrcAddr, &DMACC2DestAddr, &DMACC2LLI,
		&DMACC2Control, &DMACC2Configuration,
		&gDMACC2Control, &gDMACC2Configuration,
	},
	{
		&DMACC3SrcAddr, &DMACC3DestAddr, &DMACC3LLI,
		&DMACC3Control, &DMACC3Configuration,
		&gDMACC3Control, &gDMACC3Configuration,
	},
	{
		&DMACC4SrcAddr, &DMACC4DestAddr, &DMACC4LLI,
		&DMACC4Control, &DMACC4Configuration,
		&gDMACC4Control, &gDMACC4Configuration,
	},
	{
		&DMACC5SrcAddr, &DMACC5DestAddr, &DMACC5LLI,
		&DMACC5Control, &DMACC5Configuration,
		&gDMACC5Control, &gDMACC5Configuration,
	},
	{
		&DMACC6SrcAddr, &DMACC6DestAddr, &DMACC6LLI,
		&DMACC6Control, &DMACC6Configuration,
		&gDMACC6Control, &gDMACC6Configuration,
	},
	{
		&DMACC7SrcAddr, &DMACC7DestAddr, &DMACC7LLI,
		&DMACC7Control, &DMACC7Configuration,
		&gDMACC7Control, &gDMACC7Configuration,
	},
};


/*
 * --------------------------------------------------------------------------
 *   Function
 * --------------------------------------------------------------------------
 */
static void Interrupt_DMACIntErrorStatus(void);
static DMACIntxxx_t dmac_get_channel_mask(DMAC_Channel_t ch);


/* ************************************************************************** */
/*! \addtogroup DMAC_Functions
 *  @{
 */

/*! \addtogroup DMAC_API_Functions
 *  @{
 */
/* ======================================================================== */
/*!
	Initialize of dmac
	Check DMACIntTCStatus(DMA End) and do each function.

	NOTES:	check "vectors.s"

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void dmac_init(void)
{
	UINT32_t reg_data;
	UINT32_t reg_data2;

	gInterruptFunc_DMA_ch0 = dmac_dummy_func;
	gInterruptFunc_DMA_ch1 = dmac_dummy_func;
	gInterruptFunc_DMA_ch2 = dmac_dummy_func;
	gInterruptFunc_DMA_ch3 = dmac_dummy_func;
	gInterruptFunc_DMA_ch4 = dmac_dummy_func;
	gInterruptFunc_DMA_ch5 = dmac_dummy_func;
	gInterruptFunc_DMA_ch6 = dmac_dummy_func;
	gInterruptFunc_DMA_ch7 = dmac_dummy_func;

	gInterruptFunc_DMAError_ch0 = dmac_dummy_func;
	gInterruptFunc_DMAError_ch1 = dmac_dummy_func;
	gInterruptFunc_DMAError_ch2 = dmac_dummy_func;
	gInterruptFunc_DMAError_ch3 = dmac_dummy_func;
	gInterruptFunc_DMAError_ch4 = dmac_dummy_func;
	gInterruptFunc_DMAError_ch5 = dmac_dummy_func;
	gInterruptFunc_DMAError_ch6 = dmac_dummy_func;
	gInterruptFunc_DMAError_ch7 = dmac_dummy_func;

	gDMACC0Control.data 		= CDMACC0Control_Init;
	gDMACC1Control.data 		= CDMACC1Control_Init;
	gDMACC2Control.data 		= CDMACC2Control_Init;
	gDMACC3Control.data 		= CDMACC3Control_Init;
	gDMACC4Control.data 		= CDMACC4Control_Init;
	gDMACC5Control.data 		= CDMACC5Control_Init;
	gDMACC6Control.data 		= CDMACC6Control_Init;
	gDMACC7Control.data 		= CDMACC7Control_Init;

	gDMACC0Configuration.data	= CDMACC0Configuration_Init;
	gDMACC1Configuration.data	= CDMACC1Configuration_Init;
	gDMACC2Configuration.data	= CDMACC2Configuration_Init;
	gDMACC3Configuration.data	= CDMACC3Configuration_Init;
	gDMACC4Configuration.data	= CDMACC4Configuration_Init;
	gDMACC5Configuration.data	= CDMACC5Configuration_Init;
	gDMACC6Configuration.data	= CDMACC6Configuration_Init;
	gDMACC7Configuration.data	= CDMACC7Configuration_Init;

	DMACConfiguration	= CDMACConfiguration_Init;	/* Enable DMAC Circuit	*/
	DMACIntTCClear		= CDMACIntTCClear_Init;		/* Clear All DMAC TC    */
	DMACIntErrClr		= CDMACIntErrClr_Init;		/* Clear All DMAC Error Interrupt	*/

	/* Set DMA interrupt function */
	/* Disable all interrupt 	*/
	reg_data2		= VICINTENABLE;
	VICINTENABLE	= CInterruptALL_F;
	/* set interrupt function	*/
	VICVECTADDR16 = (UINT32_t)Interrupt_DMACIntErrorStatus;
	VICVECTADDR17 = (UINT32_t)Interrupt_DMACIntTCStatus;
	/* Set FIQ interrupt for DMAEnd		*/
	reg_data		= VICINTSELECT;
// for timer	reg_data		= (reg_data & CInterruptDMAEnd_MASK) | CInterruptDMAEnd_T;
	reg_data		= (reg_data & CInterruptDMAEnd_MASK) | CInterruptDMAEnd_F;
	VICINTSELECT	= reg_data;
	/* Enable Interrupt DMAEnd	*/
	VICINTENABLE	= reg_data2 | (CInterruptDMAError_T | CInterruptDMAEnd_T);
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	dummy function

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void dmac_dummy_func(void)
{
	for(;;) {
		;	/* check entry	*/
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	Interrupt function of DMACIntTCStatus(FIQ)
	Check DMACIntTCStatus(DMA End) and do each function.

	NOTES:	check "vectors.s"

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void Interrupt_DMACIntTCStatus(void)
{
	UINT32_t reg_data;

	reg_data = DMACIntTCStatus;

	if ((reg_data & CDMAIntxxx_CH0_MASK) == CDMAIntxxx_CH0_T) {
		DMACIntTCClear = CDMAIntxxx_CH0_T;
		gInterruptFunc_DMA_ch0();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH1_MASK) == CDMAIntxxx_CH1_T) {
		DMACIntTCClear = CDMAIntxxx_CH1_T;
		gInterruptFunc_DMA_ch1();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH2_MASK) == CDMAIntxxx_CH2_T) {
		DMACIntTCClear = CDMAIntxxx_CH2_T;
		gInterruptFunc_DMA_ch2();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH3_MASK) == CDMAIntxxx_CH3_T) {
		DMACIntTCClear = CDMAIntxxx_CH3_T;
		gInterruptFunc_DMA_ch3();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH4_MASK) == CDMAIntxxx_CH4_T) {
		DMACIntTCClear = CDMAIntxxx_CH4_T;
		gInterruptFunc_DMA_ch4();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH5_MASK) == CDMAIntxxx_CH5_T) {
		DMACIntTCClear = CDMAIntxxx_CH5_T;
		gInterruptFunc_DMA_ch5();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH6_MASK) == CDMAIntxxx_CH6_T) {
		DMACIntTCClear = CDMAIntxxx_CH6_T;
		gInterruptFunc_DMA_ch6();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH7_MASK) == CDMAIntxxx_CH7_T) {
		DMACIntTCClear = CDMAIntxxx_CH7_T;
		gInterruptFunc_DMA_ch7();
	}
	else {
		;	/* do nothing	*/
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	Interrupt function of DMACIntErrorStatus(IRQ)
	Check DMACIntTCStatus(DMA End) and do each function.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void Interrupt_DMACIntErrorStatus(void)
{
	UINT32_t reg_data;

	reg_data = DMACIntErrorStatus;

	if ((reg_data & CDMAIntxxx_CH0_MASK) == CDMAIntxxx_CH0_T) {
		DMACIntErrClr = CDMAIntxxx_CH0_T;
		gInterruptFunc_DMAError_ch0();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH1_MASK) == CDMAIntxxx_CH1_T) {
		DMACIntErrClr = CDMAIntxxx_CH1_T;
		gInterruptFunc_DMAError_ch1();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH2_MASK) == CDMAIntxxx_CH2_T) {
		DMACIntErrClr = CDMAIntxxx_CH2_T;
		gInterruptFunc_DMAError_ch2();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH3_MASK) == CDMAIntxxx_CH3_T) {
		DMACIntErrClr = CDMAIntxxx_CH3_T;
		gInterruptFunc_DMAError_ch3();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH4_MASK) == CDMAIntxxx_CH4_T) {
		DMACIntErrClr = CDMAIntxxx_CH4_T;
		gInterruptFunc_DMAError_ch4();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH5_MASK) == CDMAIntxxx_CH5_T) {
		DMACIntErrClr = CDMAIntxxx_CH5_T;
		gInterruptFunc_DMAError_ch5();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH6_MASK) == CDMAIntxxx_CH6_T) {
		DMACIntErrClr = CDMAIntxxx_CH6_T;
		gInterruptFunc_DMAError_ch6();
	}
	else {
		;	/* do nothing	*/
	}

	if ((reg_data & CDMAIntxxx_CH7_MASK) == CDMAIntxxx_CH7_T) {
		DMACIntErrClr = CDMAIntxxx_CH7_T;
		gInterruptFunc_DMAError_ch7();
	}
	else {
		;	/* do nothing	*/
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	Initialize  DMAC ch
	SrcM(inc)toDstM(inc)

	\param  ch				: DMAC channel
	\param  *pSrc			: Src Buffer Address
	\param  *pDst			: Dst Buffer Address
	\param  size			: trans size(byte)
	\retval E_DMAC_TRUE		: success
	\retval E_DMAC_FALSE	: error
 */
/* ------------------------------------------------------------------------ */
UINT32_t dmac_ch_init(const DMAC_Channel_t ch,
					  const UINT32_t* const pSrc, UINT32_t *const pDst,
					  const UINT32_t size)
{
	UINT32_t work_size;
	UINT32_t rtn;

	/* check address	*/
	rtn = dmac_check_address(ch, pSrc, pDst);
	if(rtn == E_DMAC_FALSE) {
		return E_DMAC_FALSE;
	}
	else {
		;	/* do nothing	*/
	}

	/* check transfer size	*/
	work_size = size;
	rtn = dmac_check_transfer_size(ch, &work_size);
	if(rtn == E_DMAC_FALSE) {
		return E_DMAC_FALSE;
	}
	else {
		;	/* do nothing	*/
	}

	/* check dma enable	*/
	rtn = dmac_check_channel_enable(ch);
	if(rtn == E_DMAC_FALSE) {
		return E_DMAC_FALSE;
	}
	else {
		;	/* do nothing	*/
	}

	/* set transfersize	*/
	gDMACInfo[ch].control_work->b.transfersize	= work_size;

	/* disable ch		*/
	gDMACInfo[ch].configuration_work->b.e = CDMACCxConfiguration_B_E_F;
	
	/* set controller	*/
	*gDMACInfo[ch].srcaddr		= (UINT32_t)pSrc;
	*gDMACInfo[ch].dstaddr		= (UINT32_t)pDst;
	*gDMACInfo[ch].lli			= CDMACCxLLI_OFF;
	*gDMACInfo[ch].control		= gDMACInfo[ch].control_work->data;
	*gDMACInfo[ch].configuration = gDMACInfo[ch].configuration_work->data;

	return E_DMAC_TRUE;
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	init DMAC ch1

	\param  ch				: DMAC channel
	\param  *plli			: Dst Buffer Address
	\param  list_size		: lli list size
	\retval E_DMAC_TRUE		: success
	\retval E_DMAC_FALSE	: error
 */
/* ------------------------------------------------------------------------ */
UINT32_t dmac_ch_lli_init(const DMAC_Channel_t ch, const LLI_t* const plli,
						  const UINT32_t list_size)
{
	UINT32_t cnt;
	const LLI_t* work_lli;
	UINT32_t work_size;
	UINT32_t rtn;

	/* set interrupt function	*/
	gDMACInfo[ch].control_work->data = plli->dmaccxcontrol;

	/* check transfer size	*/
	work_lli = plli;
	for(cnt = 0; cnt < list_size; cnt++) {
		
		gDMACC1Control.data	= work_lli->dmaccxcontrol;
		work_size = work_lli->dmaccxcontrol & CDMACCxControl_Transfersize_MASK;

		/* check address	*/
		rtn = dmac_check_address(ch, work_lli->src_addr, work_lli->dst_addr);
		if(rtn == E_DMAC_FALSE) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}

		/* check transfer size	*/
		rtn = dmac_check_transfer_size(ch, &work_size);
		if(rtn == E_DMAC_FALSE) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}
		work_lli++;
	}

	/* check dma enable	*/
	rtn = dmac_check_channel_enable(ch);
	if(rtn == E_DMAC_FALSE) {
		return E_DMAC_FALSE;
	}
	else {
		;	/* do nothing	*/
	}

	/* restor controldata	*/
	gDMACInfo[ch].control_work->data = plli->dmaccxcontrol;

	/* disable ch		*/
	gDMACInfo[ch].configuration_work->b.e = CDMACCxConfiguration_B_E_F;

	/* set controller	*/
	*gDMACInfo[ch].srcaddr		= (UINT32_t)plli->src_addr;
	*gDMACInfo[ch].dstaddr		= (UINT32_t)plli->dst_addr;
	*gDMACInfo[ch].lli			= (UINT32_t)plli->next_lli;
	*gDMACInfo[ch].control		= gDMACInfo[ch].control_work->data;
	*gDMACInfo[ch].configuration = gDMACInfo[ch].configuration_work->data;

	return E_DMAC_TRUE;
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	start DMAC ch(enable ch)

	\param  ch			: DMAC channel
	\param  mode		: E_DMAC_TRUE  burst request at peripheral
						  E_DMAC_FALSE single request at peripheral
	\retval E_DMAC_TRUE		sucdess
	\retval E_DMAC_FALSE	failed
 */
/* ------------------------------------------------------------------------ */
UINT32_t dmac_ch_start(const DMAC_Channel_t ch, const UINT32_t mode)
{
	UINT32_t work_buf;
	DMACCxConfiguration_t work_configuration;
	DMACSoftBReq_t work_softreq;

	work_configuration.data = gDMACInfo[ch].configuration_work->data;
	*gDMACInfo[ch].configuration = (work_configuration.data |
									CDMACCxConfiguration_E_T);
	if(work_configuration.b.flowcontrl !=
	   CDMACCxConfiguration_B_FlowCntrl_MtoM){
		/* MtoP or PtoM or PtoP	*/
		if(work_configuration.b.flowcontrl ==
		   CDMACCxConfiguration_B_FlowCntrl_MtoP) {
			/* MtoP	*/
			work_buf = gDMACInfo[ch].configuration_work->b.destperipheral;
		}
		else {
			/* PtoM or PtoP 	*/
			work_buf = gDMACInfo[ch].configuration_work->b.srcperipheral;
		}

		work_softreq.data = 0;
		switch(work_buf) {
		case CDMACCxConfiguration_B_Peripheral_UART0_TX:
			work_softreq.b.uart0_tx	= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_UART0_RX:
			work_softreq.b.uart0_rx	= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_NANDC0:
			work_softreq.b.nand0	= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_CMSI:
			work_softreq.b.cmsi		= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_SDHC_CC_W:
			work_softreq.b.sdhc_cc_w= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_SDHC_CC_R:
			work_softreq.b.sdhc_cc_r= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_SDHC_SD_W:
			work_softreq.b.sdhc_sd_w= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_SDHC_SD_R:
			work_softreq.b.sdhc_sd_r= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_I2S0:
			work_softreq.b.i2s0		= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_I2S1:
			work_softreq.b.i2s1		= CDMACCSoftxReq_B_T;
			break;
		case CDMACCxConfiguration_B_Peripheral_LCDDA:
			work_softreq.b.lcdda	= CDMACCSoftxReq_B_T;
			break;
		default:
			return E_DMAC_FALSE;
		}
		if(mode == E_DMAC_TRUE) {
			/* burst request	*/
			DMACSoftBReq = work_softreq.data;
		}
		else {
			/* single request	*/
			work_softreq.data &= ~CDMACSoftSReq_Reserved_MASK;
			if(work_softreq.data != 0) {
				/* accept request	*/
				DMACSoftSReq = work_softreq.data;
			}
			else {
				return E_DMAC_FALSE;
			}
		}
	}
	else {
		/* M to M	*/
		;	/* do nothing	*/
	}
	return E_DMAC_TRUE;
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	stop DMAC ch(disable ch)

	\param  ch			: DMAC channel
	\retval -
 */
/* ------------------------------------------------------------------------ */
void dmac_ch_stop(const DMAC_Channel_t ch)
{
	gDMACInfo[ch].configuration_work->b.e = CDMACCxConfiguration_B_E_F;
	*gDMACInfo[ch].configuration = gDMACInfo[ch].configuration_work->data;
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	check Src,Dst address

	\param  ch			: DMAC channel
	\param  *pSrc		: Src Buffer Address
	\param  *pDst		: Dst Buffer Address
	\retval E_DMAC_TRUE		: success
	\retval E_DMAC_FALSE	: failed
 */
/* ------------------------------------------------------------------------ */
UINT32_t dmac_check_address(DMAC_Channel_t const ch,
							const UINT32_t* const pSrc,
							UINT32_t* const pDst)
{
	UINT32_t data;

	data = gDMACInfo[ch].control_work->data & CDMACCxControl_Swidth_MASK;
	if(data == CDMACCxControl_Swidth_16) {
		/* check 2*x or 2*x+1	*/
		if(((UINT32_t)pSrc & CDMAC_ADDRCheck_x2) != CDMAC_ADDRCheck_SUCCESS) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}
		if(((UINT32_t)pDst & CDMAC_ADDRCheck_x2) != CDMAC_ADDRCheck_SUCCESS) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}
	}
	else if(data == CDMACCxControl_Swidth_32) {
		/* check 4*x or 2*x+1,+2,+3	*/
		if(((UINT32_t)pSrc & CDMAC_ADDRCheck_x4) != CDMAC_ADDRCheck_SUCCESS) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}
		if(((UINT32_t)pDst & CDMAC_ADDRCheck_x4) != CDMAC_ADDRCheck_SUCCESS) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}
	}
	else /* (data == CDMACCxControl_Swidth_8) */ {
		;	/* do nothing	*/
	}

	/* Please check memory area if you need	*/
	return E_DMAC_TRUE;
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	check transfer size

	OUT		*size	: setting data of DMACCxControl transfer size

	\param  ch			: DMAC channel
	\param  size		: trans size(byte)
	\retval E_DMAC_TRUE		: success
	\retval E_DMAC_FALSE	: failed
 */
/* ------------------------------------------------------------------------ */
UINT32_t dmac_check_transfer_size(DMAC_Channel_t const ch, UINT32_t* const size)
{
	UINT32_t work_size;
	UINT32_t data;

	work_size = *size;
	data = gDMACInfo[ch].control_work->data & CDMACCxControl_Swidth_MASK;
	
	if(data == CDMACCxControl_Swidth_16) {
		/* check 2*x or 2*x+1	*/
		if((work_size & CDMAC_ADDRCheck_x2) != CDMAC_ADDRCheck_SUCCESS) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}
		work_size = work_size / CSIZEofUINT16_t;
	}
	else if(data == CDMACCxControl_Swidth_32) {
		/* check 4*x or 2*x+1,+2,+3	*/
		if((work_size & CDMAC_ADDRCheck_x4) != CDMAC_ADDRCheck_SUCCESS) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}
		work_size = work_size / CSIZEofUINT32_t;
	}
	else /* (data == CDMACCxControl_Swidth_8) */ {
		;	/* do nothing	*/
	}

	/* check size over	*/
	if(work_size > CDMACCxControl_Transfersize_MASK) {
		return E_DMAC_FALSE;
	}
	else if(work_size == 0) {
		return E_DMAC_FALSE;
	}
	else {
		;	/* do nothing	*/
	}

	*size = work_size;
	return E_DMAC_TRUE;
}
/* ======================================================================== */
/*! @}	*/ /* DMAC_API_Functions */

/*! \addtogroup DMAC_APILOCAL_Functions
 *  @{
 */
/* ======================================================================== */
/*!
	check dmac channel enable or not

	\param  ch			: DMAC channel
	\retval work.data	: dmac mask ch data
 */
/* ------------------------------------------------------------------------ */
static DMACIntxxx_t dmac_get_channel_mask(DMAC_Channel_t const ch)
{
	DMACIntxxx_t work;

	work.data = 0x00;
	switch(ch) {
	case CDMAC_CH0:
		work.b.ch0 = CDMAIntxxx_B_CHx_T;
		break;
	case CDMAC_CH1:
		work.b.ch1 = CDMAIntxxx_B_CHx_T;
		break;
	case CDMAC_CH2:
		work.b.ch2 = CDMAIntxxx_B_CHx_T;
		break;
	case CDMAC_CH3:
		work.b.ch3 = CDMAIntxxx_B_CHx_T;
		break;
	case CDMAC_CH4:
		work.b.ch4 = CDMAIntxxx_B_CHx_T;
		break;
	case CDMAC_CH5:
		work.b.ch5 = CDMAIntxxx_B_CHx_T;
		break;
	case CDMAC_CH6:
		work.b.ch6 = CDMAIntxxx_B_CHx_T;
		break;
	case CDMAC_CH7:
		work.b.ch7 = CDMAIntxxx_B_CHx_T;
		break;
	default:
		;	/* do nothing	*/
		break;
	}

	return work;
}
/* ======================================================================== */
/*! @}	*/ /* DMACAPI_LOCAL_Functions */

/*! \addtogroup DMAC_API_Functions
 *  @{
 */
/* ======================================================================== */
/*!
	check dmac channel enable or not

	\param  ch				: DMAC channel
	\retval E_DMAC_TRUE		: enable
	\retval E_DMAC_FALSE	: disable
 */
/* ------------------------------------------------------------------------ */
UINT32_t dmac_check_channel_enable(DMAC_Channel_t ch)
{
	DMACIntxxx_t work_buf;

	work_buf = dmac_get_channel_mask(ch);

	if(work_buf.data != 0) {
		/* check enable or not	*/
		if((DMACEnbldChns & work_buf.data) == work_buf.data) {
			return E_DMAC_FALSE;
		}
		else {
			;	/* do nothing	*/
		}
	}
	else {
		return E_DMAC_FALSE;
	}

	return E_DMAC_TRUE;
}
/* ======================================================================== */
/*! @}	*/ /* DMAC_API_Functions */

/*! @}	*/ /* DMAC_Functions */
/* ************************************************************************** */
