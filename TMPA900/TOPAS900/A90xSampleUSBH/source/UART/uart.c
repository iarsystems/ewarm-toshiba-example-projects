/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : UART Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file uart.c
	\brief Source Code of UART API Functions

	\author TOSHIBA CORPORATION

	\date 2008/08/11 New
	\date 2008/10/24 A910 Sample version 1.0
	\date 2008/11/04 init. mistake(gInterruptFunc_UART1RX)
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

#include "uart.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/* for UARTxFBRD	*/
#if(MSYS_CLK == CSYS_CLK192M)
# define CUART1IBRD_Init	0x00000034;	/* BAUDRATE 115200BPS for 192MHz	*/
# define CUART1FBRD_Init	0x00000005;	/* for 192MHz SYSTEM BOARD			*/
#elif(MSYS_CLK == CSYS_CLK048M)
# define CUART1IBRD_Init	0x0000000D;	/* BAUDRATE 115200BPS for  48MHz	*/
# define CUART1FBRD_Init	0x00000001;	/* for  48MHz SYSTEM BOARD			*/
#else
# error
#endif


/*
 * --------------------------------------------------------------------------
 *   Style Define Area
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Variable Define Area
 * --------------------------------------------------------------------------
 */
volatile UARTInfo_t gUART1TXInfo;
volatile UARTInfo_t gUART1RXInfo;

static void (*gInterruptFunc_UART1TX)(void);	/*!< UART1RIS_TX function	*/
static void (*gInterruptFunc_UART1RX)(void);	/*!< UART1RIS_RX function	*/


/*
 * --------------------------------------------------------------------------
 *   Prototype Declaration Area
 * --------------------------------------------------------------------------
 */
static void interrupt_uart1(void);
static void interrupt_uart1_tx_dummy(void);
static void interrupt_uart1_rx_dummy(void);


/* ************************************************************************** */
/*! \addtogroup UART_Functions
 *  @{
 */

/*! \addtogroup UART_API_Functions
 *  @{
 */

/* ======================================================================== */
/*! 
	Initialize of UART1

	Set Port Function	: GPIOTFR1
	Control of UART1	: UART1CR
	Baud rate			: UART1IBRD,UART1FBRD


	for CH0				FR1	FR2	IE	(DIR?)
	GPION<2>	U0CTSn	1	0	0	(0)
	GPION<1>	U0RXD	0	1	0	(1)
	GPION<0>	U0TXD	1	0	0	(0)

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void uart1_init(void)
{
	UINT32_t reg_data;

	/* port setup	*/
#if(MUART_CH == CUART_CH1)
	reg_data =  GPIOTFR1 & 0xFFFFFF8F;
	reg_data |= 0x00000070;
	GPIOTFR1 =  reg_data;
#elif (MUART_CH == CUART_CH0)
	reg_data =  GPIONDIR & 0xFFFFFFF8;
	reg_data |= 0x00000005;
	GPIONDIR =	reg_data;
	
	reg_data =  GPIONFR1 & 0xFFFFFFF8;
	reg_data |= 0x00000005;
	GPIONFR1 =  reg_data;

	reg_data =  GPIONFR2 & 0xFFFFFFF8;
	reg_data |= 0x00000002;
	GPIONFR2 =  reg_data;

	reg_data =  GPIONIE & 0xFFFFFFF8;
	GPIONIE  =  reg_data;
#else
# error
#endif

	/* ram init.	*/
	gInterruptFunc_UART1TX = interrupt_uart1_tx_dummy;
	gInterruptFunc_UART1RX = interrupt_uart1_rx_dummy;

	/* uart1 setup	*/
#if(MUART_CH == CUART_CH1)
	UART1CR 	= CUART1CR_Init;		/* disable UART			*/
	UART1IBRD 	= CUART1IBRD_Init;		/* set baud rate		*/
	UART1FBRD 	= CUART1FBRD_Init;
	UART1LCR_H 	= CUART1LCR_H_Init;		/* set operation mode	*/
	
	UART1IMSC 	= CUART1IMSC_Init;		/* set interrupt mask	*/
	UART1ICR    = CUART1ICR_Init;		/* clear interrupt flag	*/
#elif (MUART_CH == CUART_CH0)
	UART0CR 	= CUART1CR_Init;		/* disable UART			*/
	UART0IBRD 	= CUART1IBRD_Init;		/* set baud rate		*/
	UART0FBRD 	= CUART1FBRD_Init;
	UART0LCR_H 	= CUART1LCR_H_Init;		/* set operation mode	*/
	
	UART0IMSC 	= CUART1IMSC_Init;		/* set interrupt mask	*/
	UART0ICR    = CUART1ICR_Init;		/* clear interrupt flag	*/
#else
# error
#endif

	/* set interrupt */
#if(MUART_CH == CUART_CH1)
   	reg_data = VICINTSELECT & ~CInterruptUART1_MASK;
	VICINTSELECT = reg_data;					/* Select IRQ interrupt		*/
	VICVECTADDR11 = (UINT32_t)interrupt_uart1;	/* Set interrupt function	*/
	VICINTENABLE |= CInterruptUART1_T;			/* Enable Interrupt 		*/
#elif (MUART_CH == CUART_CH0)
   	reg_data = VICINTSELECT & ~CInterruptUART0_MASK;
	VICINTSELECT = reg_data;					/* Select IRQ interrupt		*/
	VICVECTADDR10 = (UINT32_t)interrupt_uart1;	/* Set interrupt function	*/
	VICINTENABLE |= CInterruptUART0_T;			/* Enable Interrupt 		*/
#else
# error
#endif
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	UART1 start tx

	\param  interrupt_func	tx function in interrupt
	\retval -
 */
/* ------------------------------------------------------------------------ */
void uart1_start_tx(void interrupt_func(void))
{
#if(MUART_TX_INTERRUPT_DEBUG == CUART_TX_INTERRUPT_DEBUG_TRUE)
	UINT32_t reg_data;
#else
	;	/* do nothing	*/
#endif

	/* check tx func	*/
	if(interrupt_func != NULL) {
		gInterruptFunc_UART1TX = interrupt_func;
	}
	else {
		gInterruptFunc_UART1TX = interrupt_uart1_tx_dummy;
	}

#if(MUART_TX_INTERRUPT_DEBUG == CUART_TX_INTERRUPT_DEBUG_TRUE)
	/* send data		*/
	reg_data = (UINT32_t)*gUART1TXInfo.paddr;
# if(MUART_CH == CUART_CH1)
	UART1DR = reg_data;
# elif(MUART_CH == CUART_CH0)
	UART0DR = reg_data;
# else
# endif
#else
	;	/* do nothing	*/
#endif
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	UART1 stop tx

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void uart1_stop_tx(void)
{
	gInterruptFunc_UART1TX = interrupt_uart1_tx_dummy;
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	Send charactor data(not used interrupt function)
	
	\param  data			: send data
	\retval E_UART_TRUE		: succeed to send data
	\retval E_UART_FALSE	: failed to send data
 */
/* ------------------------------------------------------------------------ */
UINT32_t send_char(const UINT8_t* const data)
{
	UINT32_t reg_data;

#if(MUART_CH == CUART_CH1)
	UART1DR = (UINT32_t)*data;
#elif (MUART_CH == CUART_CH0)
	UART0DR = (UINT32_t)*data;
#else
# error
#endif

#if(MUART_CH == CUART_CH1)
	do {
		reg_data = UART1RIS;
	}while((reg_data & CUARTxIxxx_TXxx_MASK) == CUARTxIxxx_TXxx_F);

	UART1ICR = CUART1ICR_ALL_CLEAR;
#elif (MUART_CH == CUART_CH0)
	do {
		reg_data = UART0RIS;
	}while((reg_data & CUARTxIxxx_TXxx_MASK) == CUARTxIxxx_TXxx_F);

	UART0ICR = CUART1ICR_ALL_CLEAR;
#else
# error
#endif
	
	if((reg_data & UARTxRIS_ERROR_MASK) == UARTxRIS_NOERROR) {
		return E_UART_TRUE;
	}
	else {
		return E_UART_FALSE;
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	UART1 start rx

	\param  interrupt_func	rx function in interrupt
	\retval -
 */
/* ------------------------------------------------------------------------ */
void uart1_start_rx(void interrupt_func(void))
{
	/* check rx func	*/
	if(interrupt_func != NULL) {
		gInterruptFunc_UART1RX = interrupt_func;
	}
	else {
		gInterruptFunc_UART1RX = interrupt_uart1_rx_dummy;
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	UART1 stop rx

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void uart1_stop_rx(void)
{
	gInterruptFunc_UART1RX = interrupt_uart1_rx_dummy;
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	Send charactor data(not used interrupt function)
	
	\param  data			: send data
	\retval E_UART_TRUE		: succeed to send data
	\retval E_UART_FALSE	: failed to send data
 */
/* ------------------------------------------------------------------------ */
UINT32_t get_char(UINT8_t *const data)
{
	UINT32_t reg_data;

#if (MUART_CH == CUART_CH1)
	reg_data = UART1DR;
#elif (MUART_CH == CUART_CH0)
	reg_data = UART0DR;
#else
# error
#endif

	if((reg_data & UARTxDR_ERROR_MASK) == UARTxDR_NOERROR) {
		*data = (UINT8_t)(reg_data & CUARTxDR_DATA_MASK);
		return E_UART_TRUE;
	}
	else {
		return E_UART_FALSE;
	}
}
/* ======================================================================== */
/*! @}	*/ /* UART_API_Functions */

/*! \addtogroup UART_APILocal_Functions
 *  @{
 */
/* ======================================================================== */
/*! 
	Interrupt function

	\param  -
 	\retval -
 */
/* ------------------------------------------------------------------------ */
static void interrupt_uart1(void)
{
	UINT32_t reg_data;

#if (MUART_CH == CUART_CH1)
	reg_data = UART1RIS;	/* get interrupt status		*/
	UART1ICR = reg_data;	/* clear interrupt status	*/
#elif (MUART_CH == CUART_CH0)
//	reg_data = UART0RIS;	/* get interrupt status		*/
	reg_data = UART0MIS;	/* get interrupt status		*/
	UART0ICR = reg_data;	/* clear interrupt status	*/
#else
# error
#endif

	if((reg_data & CUARTxIxxx_OExx_MASK) == CUARTxIxxx_OExx_T) {
		;	/* do nothing	*/
	}
	else {
		;	/* do nothing	*/
	}

	if((reg_data & CUARTxIxxx_BExx_MASK) == CUARTxIxxx_BExx_T) {
		;	/* do nothing	*/
	}
	else {
		;	/* do nothing	*/
	}

	if((reg_data & CUARTxIxxx_PExx_MASK) == CUARTxIxxx_PExx_T) {
		;	/* do nothing	*/
	}
	else {
		;	/* do nothing	*/
	}

	if((reg_data & CUARTxIxxx_FExx_MASK) == CUARTxIxxx_FExx_T) {
		;	/* do nothing	*/
	}
	else {
		;	/* do nothing	*/
	}

	if((reg_data & CUARTxIxxx_RTxx_MASK) == CUARTxIxxx_RTxx_T) {
		;	/* do nothing	*/
	}
	else {
		;	/* do nothing	*/
	}
	
	if((reg_data & CUARTxIxxx_RXxx_MASK) == CUARTxIxxx_RXxx_T) {
		gInterruptFunc_UART1RX();
	}
	else {
		;	/* do nothing	*/
	}

	if((reg_data & CUARTxIxxx_TXxx_MASK) == CUARTxIxxx_TXxx_T) {
		gInterruptFunc_UART1TX();
	}
	else {
		;	/* do nothing	*/
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	Interrupt TX dummy function

	\param  -
 	\retval -
 */
/* ------------------------------------------------------------------------ */
static void interrupt_uart1_tx_dummy(void)
{
}
/* ======================================================================== */

/* ======================================================================== */
/*! 
	Interrupt RX dummy function

	\param  -
 	\retval -
 */
/* ------------------------------------------------------------------------ */
static void interrupt_uart1_rx_dummy(void)
{
	UINT32_t reg_data;

#if(MUART_CH == CUART_CH1)
	reg_data = UART1DR;
#elif (MUART_CH == CUART_CH0)
	reg_data = UART0DR;
#else
# error
#endif
}
/* ======================================================================== */
/*! @}	*/ /* UART_APILocal_Functions */

/*! @}	*/ /* UART_Functions */
/* ************************************************************************** */
