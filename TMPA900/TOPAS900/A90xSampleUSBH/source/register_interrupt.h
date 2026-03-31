#ifndef	_register_interrupt_h_
#define	_register_interrupt_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : -
 *   Micon : TMPA900CMAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2009 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file register_interrupt.h
	\brief Header file of interrupt register's macro define

	\author TOSHIBA CORPORATION

	\date 2008/08/11 New
	\date 2008/10/24 A910 Sample version 1.0
	\date 2008/11/04 add comment(VICINTENABLE)
	\date 2009/03/23 A900 Sample version 1.0
 */
/* ************************************************************************ */

/* ************************************************************************ */

/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/*
  interrupt factor for
	VICIRQSTATUS(IRQ Status)					1: exist inerrupt
	VICFIQSTATUS(FIQ Status)					1: exist inerrupt
	VICRAWINTR(Raw Interrupt Status)			1: exist inerrupt
	VICINTSELECT(Interrupt Select)				1: FIQ(only 1 function)
												0: IRQ
	VICINTENABLE(Interrupt Enable)				R: 1: Enable	0: Disable
												W: 1: Enable	0: -
	VICINTENCLEAR(Interrupt Enable Clear)		1: Disable interrupt
												0: do nothing
	VICSOFTINT(Software Interrupt)				1: Software interrupt
												0: do nothing
	VICSOFTINTCLEAR(Software Interrupt Clear)	1: Disable interrupt
												0: do nothing
 */
#define CInterruptWDT_MASK			0x00000001	/*  0:	*/
#define CInterruptRTC_MASK			0x00000002	/*  1:	*/
#define CInterruptTimer01_MASK		0x00000004	/*  2:	*/
#define CInterruptTimer23_MASK		0x00000008	/*  3:	*/
#define CInterruptTimer45_MASK		0x00000010	/*  4:	*/
#define CInterruptTSI_MASK			0x00000020	/*  5: GPIOD:INTA(TSI),INTB	*/
#define CInterruptI2C0_MASK			0x00000040	/*  6:	*/
#define CInterruptI2C1_MASK			0x00000080	/*  7:	*/
#define CInterruptADC_MASK			0x00000100	/*  8:	*/
#define CInterruptUART2_MASK		0x00000200	/*  9:	*/
#define CInterruptUART0_MASK		0x00000400	/* 10:	*/
#define CInterruptUART1_MASK		0x00000800	/* 11:	*/
#define CInterruptSSP0_MASK			0x00001000	/* 12:	*/
#define CInterruptSSP1_MASK			0x00002000	/* 13:	*/
#define CInterruptNDFC_MASK			0x00004000	/* 14:	*/
#define CInterruptCMSIF_MASK		0x00008000	/* 15:	*/
#define CInterruptDMAError_MASK		0x00010000	/* 16:	*/
#define CInterruptDMAEnd_MASK		0x00020000	/* 17:	*/
#define CInterruptLCDC_MASK			0x00040000	/* 18:	*/
#define CInterruptReserved1_MASK	0x00080000	/* 19: reserved1	*/
#define CInterruptLCDDA_MASK		0x00100000	/* 20:	*/
#define CInterruptUSB_MASK			0x00200000	/* 21:	*/
#define CInterruptSDHC_MASK			0x00400000	/* 22:	*/
#define CInterruptI2S_MASK			0x00800000	/* 23:	*/
#define CInterruptReserved2_MASK	0x01000000	/* 24: reserved2	*/
#define CInterruptReserved3_MASK	0x02000000	/* 25: reserved3	*/
#define CInterruptGPIOR_MASK		0x04000000	/* 26: GPIOR(INTH)	*/
#define CInterruptUSBH_MASK			0x08000000	/* 27: USB Host	*/
#define CInterruptGPION_MASK		0x10000000	/* 28: GPION(INTD-INTG)	*/
#define CInterruptGPIOF_MASK		0x20000000	/* 29: GPIOF(INTC)	*/
#define CInterruptGPIOC_MASK		0x40000000	/* 30: GPIOC(INT8,INT9)	*/
#define CInterruptGPIOA_MASK		0x80000000	/* 31: GPIOA(KI0-KI7)	*/

#define CInterruptWDT_T				0x00000001	/*  0:	*/
#define CInterruptRTC_T				0x00000002	/*  1:	*/
#define CInterruptTimer01_T			0x00000004	/*  2:	*/
#define CInterruptTimer23_T			0x00000008	/*  3:	*/
#define CInterruptTimer45_T			0x00000010	/*  4:	*/
#define CInterruptTSI_T				0x00000020	/*  5: GPIOD:INTA(TSI),INTB	*/
#define CInterruptI2C0_T			0x00000040	/*  6:	*/
#define CInterruptI2C1_T			0x00000080	/*  7:	*/
#define CInterruptADC_T				0x00000100	/*  8:	*/
#define CInterruptUART2_T			0x00000200	/*  9:	*/
#define CInterruptUART0_T			0x00000400	/* 10:	*/
#define CInterruptUART1_T			0x00000800	/* 11:	*/
#define CInterruptSSP0_T			0x00001000	/* 12:	*/
#define CInterruptSSP1_T			0x00002000	/* 13:	*/
#define CInterruptNDFC_T			0x00004000	/* 14:	*/
#define CInterruptCMSIF_T			0x00008000	/* 15:	*/
#define CInterruptDMAError_T		0x00010000	/* 16:	*/
#define CInterruptDMAEnd_T			0x00020000	/* 17:	*/
#define CInterruptLCDC_T			0x00040000	/* 18:	*/
#define CInterruptReserved1_T		0x00080000	/* 19: reserved1	*/
#define CInterruptLCDDA_T			0x00100000	/* 20:	*/
#define CInterruptUSB_T				0x00200000	/* 21:	*/
#define CInterruptSDHC_T			0x00400000	/* 22:	*/
#define CInterruptI2S_T				0x00800000	/* 23:	*/
#define CInterruptReserved2_T		0x01000000	/* 24: reserved2	*/
#define CInterruptReserved3_T		0x02000000	/* 25: reserved3	*/
#define CInterruptGPIOR_T			0x04000000	/* 26: GPIOR(INTH)	*/
#define CInterruptUSBH_T			0x08000000	/* 27: USB Host		*/
#define CInterruptGPION_T			0x10000000	/* 28: GPION(INTD-INTG)	*/
#define CInterruptGPIOF_T			0x20000000	/* 29: GPIOF(INTC)	*/
#define CInterruptGPIOC_T			0x40000000	/* 30: GPIOC(INT8,INT9)	*/
#define CInterruptGPIOA_T			0x80000000	/* 31: GPIOA(KI0-KI7)	*/

#define CInterruptWDT_F				0x00000000	/*  0:	*/
#define CInterruptRTC_F				0x00000000	/*  1:	*/
#define CInterruptTimer01_F			0x00000000	/*  2:	*/
#define CInterruptTimer23_F			0x00000000	/*  3:	*/
#define CInterruptTimer45_F			0x00000000	/*  4:	*/
#define CInterruptTSI_F				0x00000000	/*  5: GPIOD:INTA(TSI),INTB	*/
#define CInterruptI2C0_F			0x00000000	/*  6:	*/
#define CInterruptI2C1_F			0x00000000	/*  7:	*/
#define CInterruptADC_F				0x00000000	/*  8:	*/
#define CInterruptUART3_F			0x00000000	/*  9:	*/
#define CInterruptUART0_F			0x00000000	/* 10:	*/
#define CInterruptUART1_F			0x00000000	/* 11:	*/
#define CInterruptSSP0_F			0x00000000	/* 12:	*/
#define CInterruptSSP1_F			0x00000000	/* 13:	*/
#define CInterruptNDFC_F			0x00000000	/* 14:	*/
#define CInterruptCMSIF_F			0x00000000	/* 15:	*/
#define CInterruptDMAError_F		0x00000000	/* 16:	*/
#define CInterruptDMAEnd_F			0x00000000	/* 17:	*/
#define CInterruptLCDC_F			0x00000000	/* 18:	*/
#define CInterruptReserved1_F		0x00000000	/* 19: reserved1	*/
#define CInterruptLCDDA_F			0x00000000	/* 20:	*/
#define CInterruptUSB_F				0x00000000	/* 21:	*/
#define CInterruptSDHC_F			0x00000000	/* 22:	*/
#define CInterruptI2S_F				0x00000000	/* 23:	*/
#define CInterruptReserved2_F		0x00000000	/* 24: reserved2	*/
#define CInterruptReserved3_F		0x00000000	/* 25: reserved3	*/
#define CInterruptGPIOR_F			0x00000000	/* 26: GPIOR(INTH)	*/
#define CInterruptUSBH_F			0x00000000	/* 27: USB Host		*/
#define CInterruptGPION_F			0x00000000	/* 28: GPION(INTD-INTG)	*/
#define CInterruptGPIOF_F			0x00000000	/* 29: GPIOF(INTC)	*/
#define CInterruptGPIOC_F			0x00000000	/* 30: GPIOC(INT8,INT9)	*/
#define CInterruptGPIOA_F			0x00000000	/* 31: GPIOA(KI0-KI7)	*/

#define CInterruptALL_F				0x00000000	/* disable all interrupt	*/

/* for VICVECTADDRxx	*/
#define CVICVECTADDRxx_Default		0x00000000


/* **************************************************************** */
#endif	/* _register_interrupt_h_ */
