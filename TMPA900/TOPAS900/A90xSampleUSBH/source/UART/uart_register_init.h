#ifndef _uart_register_init_h_
#define _uart_register_init_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : AD Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file uart_register_init.h
	\brief Header file of UART register's macro define

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
#include "register_uart.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/* for UARTxDR	*/

/* for UARTxSR	*/

/* for UARTxECR	same address as UARTxSR	*/

/* for UART0FR, UART1FR	*/

/* for UART0ILPR	*/

/* for UARTxIBRD	*/

/* for UARTxLCR_H	*/
#define CUART1LCR_H_Init	\
	( \
	  CUARTxLCR_H_Reserved	/* 							*/ | \
	  CUARTxLCR_H_WLEN_8bit	/* 8bit						*/ | \
	  CUARTxLCR_H_FEN_F		/* character mode			*/ | \
	  CUARTxLCR_H_STP2_F	/* stop bit 1				*/ | \
	  CUARTxLCR_H_EPS_F		/* odd parity				*/ | \
	  CUARTxLCR_H_PEN_F		/* disable parity control	*/ | \
	  CUARTxLCR_H_BRK_F		/* no break					*/ \
	  )

/* for UARTxCR	*/
#define CUART1CR_Init	\
	( \
	  CUART1CR_Reserved	/* 							*/ | \
	  CUARTxCR_RXE_T	/* RX enable				*/ | \
	  CUARTxCR_TXE_T	/* TX enable				*/ | \
	  CUARTxCR_UARTEN_T	/* UART enable				*/ \
	  )

/* for UARTxIFLS	*/

/* for UARTxIMSC RW interrupt mask		1:set mask,	0:clear mask	*/
#define CUART1IMSC_Init	\
	( \
	  CUART1Ixxx_Reserved	/* 				*/ | \
	  CUARTxIxxx_OExx_F		/* set mask		*/ | \
	  CUARTxIxxx_BExx_F		/* set mask		*/ | \
	  CUARTxIxxx_PExx_F		/* set mask		*/ | \
	  CUARTxIxxx_FExx_F		/* set mask		*/ | \
	  CUARTxIxxx_RTxx_F		/* set mask		*/ | \
	  CUARTxIxxx_TXxx_F		/* clear mask	*/ | \
	  CUARTxIxxx_RXxx_T		/* clear mask	*/ | \
	  CUARTxIxxx_CTSMxx_F	/* set mask		*/ \
	  )

/* for UARTxRIS	 RO interrupt status	1:exist,	0:non			*/
#define UARTxRIS_ERROR_MASK	\
	( \
	  CUARTxIxxx_OExx_MASK /* over run error mask	*/ | \
	  CUARTxIxxx_BExx_MASK /* break error mask		*/ | \
	  CUARTxIxxx_PExx_MASK /* parity error mask		*/ | \
	  CUARTxIxxx_FExx_MASK /* flaming error mask	*/ | \
	  CUARTxIxxx_RTxx_MASK /* RX timeout mask		*/ \
	  )

#define UARTxRIS_NOERROR	\
	( \
	  CUARTxIxxx_OExx_F /* non over run error	*/ | \
	  CUARTxIxxx_BExx_F /* non break error		*/ | \
	  CUARTxIxxx_PExx_F /* non parity error		*/ | \
	  CUARTxIxxx_FExx_F /* non flaming error	*/ | \
	  CUARTxIxxx_RTxx_F /* non RX timeout		*/ \
	  )

/* for UARTxMIS  RO interrupt status	1:exist,	0:non			*/
/* for UARTxICR	 WO interrupt clear		1:clear,	0:non			*/
#define CUART1ICR_Init	CUART1ICR_ALL_CLEAR
#define CUART1ICR_ALL_CLEAR	\
	( \
	  CUART1Ixxx_Reserved	/* 				*/ | \
	  CUARTxIxxx_OExx_T		/* clear flag	*/ | \
	  CUARTxIxxx_BExx_T		/* clear flag	*/ | \
	  CUARTxIxxx_PExx_T		/* clear flag	*/ | \
	  CUARTxIxxx_FExx_T		/* clear flag	*/ | \
	  CUARTxIxxx_RTxx_T		/* clear flag	*/ | \
	  CUARTxIxxx_TXxx_T		/* clear flag	*/ | \
	  CUARTxIxxx_RXxx_T		/* clear flag	*/ | \
	  CUARTxIxxx_CTSMxx_T	/* clear flag	*/ \
	  )

/* for UART0DMACR	*/


/* ************************************************************************ */
#endif	/* _uart_register_init_h_ */
