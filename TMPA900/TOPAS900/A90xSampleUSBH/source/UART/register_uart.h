#ifndef _register_uart_h_
#define _register_uart_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : AD Driver
 *   Micon : TMPA910CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file register_uart.h
	\brief Header file of UART register's macro define

	\author TOSHIBA CORPORATION

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
/* for UARTxDR	*/
#define CUARTxDR_Reserved_MASK	0xFFFFF000	/*!< <31:12>				*/
# define CUARTxDR_Reserved		0x00000000
#define CUARTxDR_OE_MASK		0x00000800	/*!< <11>RO over run error	*/
# define CUARTxDR_OE_T			0x00000800	/* error					*/
# define CUARTxDR_OE_F			0x00000000	/* 							*/
#define CUARTxDR_BE_MASK		0x00000400	/*!< <10>RO break error		*/
# define CUARTxDR_BE_T			0x00000400	/* error					*/
# define CUARTxDR_BE_F			0x00000000	/* 				*/
#define CUARTxDR_PE_MASK		0x00000200	/*!< <9>RO parity error		*/
# define CUARTxDR_PE_T			0x00000200	/* error					*/
# define CUARTxDR_PE_F			0x00000000	/* 							*/
#define CUARTxDR_FE_MASK		0x00000100	/*!< <8>RO flaming error	*/
# define CUARTxDR_FE_T			0x00000100	/* error					*/
# define CUARTxDR_FE_F			0x00000000	/* 							*/
#define CUARTxDR_DATA_MASK		0x000000FF	/*!< <7:0>R:receive data
													  W:trans data
											 */

/* for UARTxSR	*/
#define CUARTxSR_Reserved_MASK	0xFFFFFFF0	/*!< <31:4>		*/
# define CUARTxSR_Reserved		0x00000000
#define CUARTxSR_OE_MASK		0x00000008	/*!< <3>RO over run error	*/
# define CUARTxSR_OE_T			0x00000008	/* error					*/
# define CUARTxSR_OE_F			0x00000000	/* 							*/
#define CUARTxSR_BE_MASK		0x00000004	/*!< <2>RO break error		*/
# define CUARTxSR_BE_T			0x00000004	/* error					*/
# define CUARTxSR_BE_F			0x00000000	/* 				*/
#define CUARTxSR_PE_MASK		0x00000002	/*!< <1>RO parity error		*/
# define CUARTxSR_PE_T			0x00000002	/* error					*/
# define CUARTxSR_PE_F			0x00000000	/* 							*/
#define CUARTxSR_FE_MASK		0x00000001	/*!< <0>RO flaming error	*/
# define CUARTxSR_FE_T			0x00000001	/* error					*/
# define CUARTxSR_FE_F			0x00000000	/* 							*/

/* for UARTxECR	same address as UARTxSR	*/
# define CUARTxECR_CLEAR		0x00000000	/*!< <31:0> clear error flag	*/

/* for UART0FR, UART1FR	*/
#define CUART0FR_Reserved_MASK	0xFFFFFE00	/*!< <31:9>						*/
# define CUART0FR_Reserved		0x00000000
#define CUART1FR_Reserved_MASK	0xFFFFFF06	/*!< <31:8>,<2:1>				*/
# define CUART1FR_Reserved		0x00000000
#define CUART0FR_RI_MASK		0x00000100	/*!< <8>RO 						*/
# define CUART0FR_RI_T			0x00000100	/* 								*/
# define CUART0FR_RI_F			0x00000000	/* 								*/
#define CUARTxFR_TXFE_MASK		0x00000080	/*!< <7>RO TX FIFO empty flag	*/
# define CUARTxFR_TXFE_T		0x00000080	/* empty						*/
# define CUARTxFR_TXFE_F		0x00000000	/* 								*/
#define CUARTxFR_RXFF_MASK		0x00000040	/*!< <6>RO RX FIFO full flag	*/
# define CUARTxFR_RXFF_T		0x00000040	/* full							*/
# define CUARTxFR_RXFF_F		0x00000000	/* 								*/
#define CUARTxFR_TXFF_MASK		0x00000020	/*!< <5>RO TX FIFO full flag	*/
# define CUARTxFR_TXFF_T		0x00000020	/* full							*/
# define CUARTxFR_TXFF_F		0x00000000	/* 								*/
#define CUARTxFR_RXFE_MASK		0x00000010	/*!< <4>RO RX FIFO empty flag	*/
# define CUARTxFR_RXFE_T		0x00000010	/* empty						*/
# define CUARTxFR_RXFE_F		0x00000000	/* 								*/
#define CUARTxFR_BUSY_MASK		0x00000008	/*!< <3>RO TX BUSY flag  		*/
# define CUARTxFR_BUSY_T		0x00000008	/* busy							*/
# define CUARTxFR_BUSY_F		0x00000000	/* 								*/
#define CUART0FR_DCD_MASK		0x00000004	/*!< <2>RO data carrier detect 	*/
# define CUART0FR_DCD_T			0x00000004	/* 								*/
# define CUART0FR_DCD_F			0x00000000	/* 								*/
#define CUART0FR_DSR_MASK		0x00000002	/*!< <1>RO data sete ready flag */
# define CUART0FR_DSR_T			0x00000002	/* 								*/
# define CUART0FR_DSR_F			0x00000000	/* 								*/
#define CUARTxFR_CTS_MASK		0x00000001	/*!< <0>RO ? 					*/
# define CUARTxFR_CTS_T			0x00000001	/* 								*/
# define CUARTxFR_CTS_F			0x00000000	/* 								*/

/* for UART0ILPR	*/
#define CUART0ILPR_Reserved_MASK	0xFFFFFF00	/*!< <31:8>		*/
# define CUART0ILPR_Reserved		0x00000000
#define CUART0ILPR_ILPDVSR_MASK		0x000000FF	/*!< <7:0> 		*/

/* for UARTxIBRD	*/
#define CUARTxIBRD_Reserved_MASK	0xFFFF0000	/*!< <31:16>	*/
# define CUARTxIBRD_Reserved		0x00000000
#define CUARTxIBRD_BAUD_DIVINT_MASK	0x0000FFFF	/*!< <15:8> 	*/

/* for UARTxFBRD	*/
#define CUARTxFBRD_Reserved_MASK	0xFFFFFF80	/*!< <31:6>		*/
# define CUARTxFBRD_Reserved		0x00000000
#define CUARTxFBRD_DAUDDIVFRAC_MASK	0x0000007E	/*!< <5:0> 		*/

/* for UARTxLCR_H	*/
#define CUARTxLCR_H_Reserved_MASK	0xFFFFFF00	/*!< <31:8>				*/
# define CUARTxLCR_H_Reserved		0x00000000
#define CUARTxLCR_H_SPS_MASK		0x00000080	/*!< <7> stick parity 	*/
# define CUARTxLCR_H_SPS_T			0x00000080	/* 						*/
# define CUARTxLCR_H_SPS_F			0x00000000	/* 						*/
#define CUARTxLCR_H_WLEN_MASK		0x00000060	/*!< <6:5> word length 	*/
# define CUARTxLCR_H_WLEN_5bit		0x00000000	/* 5bit					*/
# define CUARTxLCR_H_WLEN_6bit		0x00000020	/* 6bit					*/
# define CUARTxLCR_H_WLEN_7bit		0x00000040	/* 7bit					*/
# define CUARTxLCR_H_WLEN_8bit		0x00000060	/* 8bit					*/
#define CUARTxLCR_H_FEN_MASK		0x00000010	/*!< <4> FIFO control 	*/
# define CUARTxLCR_H_FEN_T			0x00000010	/* FIFO mode			*/
# define CUARTxLCR_H_FEN_F			0x00000000	/* character mode		*/
#define CUARTxLCR_H_STP2_MASK		0x00000008	/*!< <3> Stop bit 		*/
# define CUARTxLCR_H_STP2_T			0x00000008	/* 2 stop bit			*/
# define CUARTxLCR_H_STP2_F			0x00000000	/* 1 stop bit			*/
#define CUARTxLCR_H_EPS_MASK		0x00000004	/*!< <2> even parity 	*/
# define CUARTxLCR_H_EPS_T			0x00000004	/* even					*/
# define CUARTxLCR_H_EPS_F			0x00000000	/* odd					*/
#define CUARTxLCR_H_PEN_MASK		0x00000002	/*!< <1> parity control */
# define CUARTxLCR_H_PEN_T			0x00000002	/* enable				*/
# define CUARTxLCR_H_PEN_F			0x00000000	/* disable				*/
#define CUARTxLCR_H_BRK_MASK		0x00000001	/*!< <0> trans break 	*/
# define CUARTxLCR_H_BRK_T			0x00000001	/* trans break			*/
# define CUARTxLCR_H_BRK_F			0x00000000	/* -					*/

/* for UARTxCR	*/
#define CUART0CR_Reserved_MASK	0xFFFF30F8	/*!< <31:16>,<13:12>,<7:3>		*/
# define CUART0CR_Reserved		0x00000000
#define CUART1CR_Reserved_MASK	0xFFFF73FE	/*!< <31:16>,<14:10>,<7:1>		*/
# define CUART1CR_Reserved		0x00000000
#define CUARTxCR_CTSEn_MASK		0x00008000	/*!< <15> CTS HW control		*/
# define CUARTxCR_CTSEn_T		0x00008000	/* enable						*/
# define CUARTxCR_CTSEn_F		0x00000000	/* disable						*/
#define CUART0CR_RTSEn_MASK		0x00004000	/*!< <14> UART0 RTS HW control	*/
# define CUART0CR_RTSEn_T		0x00004000	/* enable						*/
# define CUART0CR_RTSEn_F		0x00000000	/* disable						*/
#define CUART0CR_RTS_MASK		0x00000800	/*!< <11> UART0 modem status 	*/
# define CUART0CR_RTS_T			0x00000800	/* 								*/
# define CUART0CR_RTS_F			0x00000000	/* 								*/
#define CUART0CR_DTR_MASK		0x00000400	/*!< <10> UART0 modem status 	*/
# define CUART0CR_DTR_T			0x00000400	/* 								*/
# define CUART0CR_DTR_F			0x00000000	/* 								*/
#define CUARTxCR_RXE_MASK		0x00000200	/*!< <9> RX enable				*/
# define CUARTxCR_RXE_T			0x00000200	/* enable						*/
# define CUARTxCR_RXE_F			0x00000000	/* disable						*/
#define CUARTxCR_TXE_MASK		0x00000100	/*!< <8> TX enable				*/
# define CUARTxCR_TXE_T			0x00000100	/* enable						*/
# define CUARTxCR_TXE_F			0x00000000	/* disable						*/
#define CUART0CR_SIRLP_MASK		0x00000004	/*!< <2> UART0 IrDA 			*/
# define CUART0CR_SIRLP_T		0x00000004	/* IrLPBaud16					*/
# define CUART0CR_SIRLP_F		0x00000000	/* 								*/
#define CUART0CR_SIREN_MASK		0x00000002	/*!< <1> UART0 SIR 				*/
# define CUART0CR_SIREN_T		0x00000002	/* enable						*/
# define CUART0CR_SIREN_F		0x00000000	/* disable						*/
#define CUARTxCR_UARTEN_MASK	0x00000001	/*!< <0> UART enable			*/
# define CUARTxCR_UARTEN_T		0x00000001	/* enable						*/
# define CUARTxCR_UARTEN_F		0x00000000	/* disable						*/

/* for UARTxIFLS	*/
#define CUARTxIFLS_Reserved_MASK	0xFFFFFFC0	/*!< <31:6>		*/
# define CUARTxIFLS_Reserved		0x00000000
#define CUARTxIFLS_RXIFLSEL_MASK	0x00000038	/*!< <5:3> RX interrupt
														 1word = 12bit
												 */
#define CUARTxIFLS_RXIFLSEL_3WORD	0x00000000	/* recieve 3word 	*/
#define CUARTxIFLS_RXIFLSEL_5WORD	0x00000008	/* recieve 5word 	*/
#define CUARTxIFLS_RXIFLSEL_9WORD	0x00000010	/* recieve 9word 	*/
#define CUARTxIFLS_RXIFLSEL_13WORD	0x00000018	/* recieve 13word 	*/
#define CUARTxIFLS_RXIFLSEL_15WORD	0x00000020	/* recieve 15word 	*/
#define CUARTxIFLS_TXIFLSEL_MASK	0x00000003	/*!< <2:0> TX interrupt
														1word = 8bit
												 */
#define CUARTxIFLS_TXIFLSEL_2WORD	0x00000000	/* remain 2word 	*/
#define CUARTxIFLS_TXIFLSEL_4WORD	0x00000001	/* remain 4word 	*/
#define CUARTxIFLS_TXIFLSEL_8WORD	0x00000002	/* remain 8word 	*/
#define CUARTxIFLS_TXIFLSEL_12WORD	0x00000003	/* remain 12word 	*/
#define CUARTxIFLS_TXIFLSEL_14WORD	0x00000004	/* remain 14word 	*/

/* for UARTxIMSC RW interrupt mask		1:set mask,	0:clear mask	*/
/* for UARTxRIS	 RO interrupt status	1:exist,	0:non			*/
/* for UARTxMIS  RO interrupt status	1:exist,	0:non			*/
/* for UARTxICR	 WO interrupt clear		1:clear,	0:non			*/
#define CUART0Ixxx_Reserved_MASK	0xFFFFF800	/*!< <31:12>,<11>			*/
# define CUART0Ixxx_Reserved		0x00000000
#define CUART1Ixxx_Reserved_MASK	0xFFFFF80D	/*!< <31:12>,<11>,<3:2>,<0>	*/
# define CUART1Ixxx_Reserved		0x00000000
#define CUARTxIxxx_OExx_MASK		0x00000400	/*!< <10> overrun error mask*/
# define CUARTxIxxx_OExx_T			0x00000400
# define CUARTxIxxx_OExx_F			0x00000000
#define CUARTxIxxx_BExx_MASK		0x00000200	/*!< <9> break error mask	*/
# define CUARTxIxxx_BExx_T			0x00000200
# define CUARTxIxxx_BExx_F			0x00000000
#define CUARTxIxxx_PExx_MASK		0x00000100	/*!< <8> parity error mask	*/
# define CUARTxIxxx_PExx_T			0x00000100
# define CUARTxIxxx_PExx_F			0x00000000
#define CUARTxIxxx_FExx_MASK		0x00000080	/*!< <7> flaming error mask	*/
# define CUARTxIxxx_FExx_T			0x00000080
# define CUARTxIxxx_FExx_F			0x00000000
#define CUARTxIxxx_RTxx_MASK		0x00000040	/*!< <6> RX timeout mask	*/
# define CUARTxIxxx_RTxx_T			0x00000040
# define CUARTxIxxx_RTxx_F			0x00000000
#define CUARTxIxxx_TXxx_MASK		0x00000020	/*!< <5> TX mask			*/
# define CUARTxIxxx_TXxx_T			0x00000020
# define CUARTxIxxx_TXxx_F			0x00000000
#define CUARTxIxxx_RXxx_MASK		0x00000010	/*!< <4> RX mask			*/
# define CUARTxIxxx_RXxx_T			0x00000010
# define CUARTxIxxx_RXxx_F			0x00000000
#define CUART0Ixxx_DSRMIM_MASK		0x00000008	/*!< <3> U0DSRn modem mask	*/
# define CUART0Ixxx_DSRMxx_T		0x00000008
# define CUART0Ixxx_DSRMxx_F		0x00000000
#define CUART0Ixxx_DCDMxx_MASK		0x00000004	/*!< <2> U0DCDn modem mask	*/
# define CUART0Ixxx_DCDMxx_T		0x00000004
# define CUART0Ixxx_DCDMxx_F		0x00000000
#define CUARTxIxxx_CTSMxx_MASK		0x00000002	/*!< <1> U0CTSn modem mask	*/
# define CUARTxIxxx_CTSMxx_T		0x00000002
# define CUARTxIxxx_CTSMxx_F		0x00000000
#define CUART0Ixxx_RIMxx_MASK		0x00000001	/*!< <0> U0RIn modem mask	*/
# define CUART0Ixxx_RIMxx_T			0x00000001
# define CUART0Ixxx_RIMxx_F			0x00000000

/* for UART0DMACR	*/
#define CUART0DMACR_Reserved_MASK	0xFFFFFFF8	/*!< <31:3>					*/
# define CUART0DMACR_Reserved		0x00000000
#define CUART0DMACR_DMAONERR_MASK	0x00000004	/*!< <2> DMA on error		*/
# define CUART0DMACR_DMAONERR_T		0x00000004	/* exist					*/
# define CUART0DMACR_DMAONERR_F		0x00000000	/* non						*/
#define CUART0DMACR_TXDMAE_MASK		0x00000002	/*!< <1> TX FIFO DMA enable	*/
# define CUART0DMACR_TXDMAE_T		0x00000002	/* enable					*/
# define CUART0DMACR_TXDMAE_F		0x00000000	/* disable					*/
#define CUART0DMACR_RXDMAE_MASK		0x00000001	/*!< <0> RX FIFO DMA enable	*/
# define CUART0DMACR_RXDMAE_T		0x00000001	/* enable					*/
# define CUART0DMACR_RXDMAE_F		0x00000000	/* disable					*/

/* ************************************************************************ */
#endif	/* _register_uart_h_ */
