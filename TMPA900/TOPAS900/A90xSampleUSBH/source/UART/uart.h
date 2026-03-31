#ifndef _uart1_h_
#define _uart1_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : UART Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file uart.h
	\brief Header file of uart.c

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

#include "register_uart.h"
#include "uart_register_init.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#define MUART_CH	CUART_CH0
//#define MUART_CH	CUART_CH1
#define MUART	CUART_CH1
# define CUART_CH0	0
# define CUART_CH1	1

#define MUART_TX_INTERRUPT_DEBUG	CUART_TX_INTERRUPT_DEBUG_TRUE	/* NG	*/
//#define MUART_TX_INTERRUPT_DEBUG	CUART_TX_INTERRUPT_DEBUG_FALSE
# define CUART_TX_INTERRUPT_DEBUG_TRUE		TRUE
# define CUART_TX_INTERRUPT_DEBUG_FALSE		FALSE

#define UARTxDR_ERROR_MASK \
	( \
	  CUARTxDR_OE_MASK | \
	  CUARTxDR_BE_MASK | \
	  CUARTxDR_PE_MASK | \
	  CUARTxDR_FE_MASK \
	  )

#define UARTxDR_NOERROR \
	( \
	  CUARTxDR_OE_F | \
	  CUARTxDR_BE_F | \
	  CUARTxDR_PE_F | \
	  CUARTxDR_FE_F \
	  )

#define E_UART_FALSE	FALSE		/* failed of uart process	*/
#define E_UART_TRUE		TRUE		/* succeed of uart process	*/


/*
 * --------------------------------------------------------------------------
 *   Style Define Area
 * --------------------------------------------------------------------------
 */
typedef struct {
	UINT8_t	 	*paddr;	/*!< buffer start address		*/
	UINT32_t	size;	/*!< transfer/receive size		*/
	UINT32_t	cnt;	/*!< counter used in interrupt	*/
}UARTInfo_t;


/*
 * --------------------------------------------------------------------------
 *   Variable Define
 * --------------------------------------------------------------------------
 */
extern volatile UARTInfo_t gUART1TXInfo;
extern volatile UARTInfo_t gUART1RXInfo;



/*
 * --------------------------------------------------------------------------
 *   Function
 * --------------------------------------------------------------------------
 */
extern void uart1_init(void);
extern void uart1_start_tx(void interrupt_func(void));
extern void uart1_stop_tx(void);
extern void uart1_start_rx(void interrupt_func(void));
extern void uart1_stop_rx(void);

extern UINT32_t send_char(const UINT8_t *const data);
extern UINT32_t get_char(UINT8_t *const data);


/* ************************************************************************ */
#endif	/* _uart1_h_ */
