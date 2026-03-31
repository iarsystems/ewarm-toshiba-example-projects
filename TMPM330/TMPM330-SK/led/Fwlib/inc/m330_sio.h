/*******************************************************************************
* File Name 		 : m330_sio.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SIO header
********************************************************************************/

/* avoid double definition  */
#ifndef __M330_SIO_H
#define __M330_SIO_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* SIO initial data */
#define IO_SIO_EN_INIT			(u_int8)0x00
#define IO_SIO_BUF_INIT			(u_int8)0x00
#define IO_SIO_CR_INIT			(u_int8)0x00
#define IO_SIO_MOD0_INIT		(u_int8)0x00
#define IO_SIO_BRCR_INIT		(u_int8)0x00
#define IO_SIO_BRADD_INIT		(u_int8)0x00
#define IO_SIO_MOD1_INIT		(u_int8)0x00
#define IO_SIO_MOD2_INIT		(u_int8)0x80
#define IO_SIO_RFC_INIT			(u_int8)0x00
#define IO_SIO_TFC_INIT			(u_int8)0x00
#define IO_SIO_RST_INIT			(u_int8)0x00
#define IO_SIO_TST_INIT			(u_int8)0x80
#define IO_SIO_FCNF_INIT		(u_int8)0x00


typedef enum { SIO_PARITY_ODD = 0, SIO_PARITY_EVEN = 1 }			IpSIO_ParityOddEven;		/* API_SIO_ParityOddEvenSet	*/
typedef enum { SIO_SCLK0_RISING = 0, SIO_SCLK0_FALLING = 1 }		IpSIO_ClkEdge;				/* API_SIO_ClkEdgeSel	*/
typedef enum { SIO_CLK_BAUDRATE = 0, SIO_CLK_SCLK0 = 1 }			IpSIO_ClkSel;				/* API_SIO_ClkSel	*/
typedef enum { SIO_SND_BIT0 = 0, SIO_SND_BIT1 = 1 }					IpSIO_SndDataBit8;			/* API_SIO_SndData_8_Set	*/
typedef enum { SIO_SBL_BIT1 = 0, SIO_SBL_BIT2 = 1 }					IpSIO_StopBitLen;			/* API_SIO_UartStopBit	*/
typedef enum { SIO_LSB_FIRST = 0, SIO_MSB_FIRST = 1 }				IpSIO_LsbMsbSel;			/* API_SIO_LsbMsbSet	*/
typedef enum { SIO_RCVFIFOBYTE_MAX = 0, SIO_RCVFIFOBYTE_FILL = 1 }	IpSIO_RcvFIFOByte;			/* API_SIO_RcvFIFO_ByteSet	*/



#define SIO_ERRFLAG_SHIFT			(u_int8)0x02
#define IO_SIO_UI8BIT2_0_MASK		(u_int8)0x07
#define IO_SIO_MODESET_MASK			(u_int8)0xF3
#define IO_SIO_CLKSET_MASK			(u_int8)0xFC
#define IO_SIO_TRANSMODE_MASK		(u_int8)0x9F
#define IO_SIO_INTERVAL_MASK		(u_int8)0xF1
#define IO_SIO_BRCLK_MASK			(u_int8)0xCF
#define IO_SIO_BRN_MASK				(u_int8)0xF0
#define IO_SIO_BR16K_MASK			(u_int8)0xF0
#define IO_SIO_RCVFFILL_MASK		(u_int8)0xFC
#define IO_SIO_SNDFFILL_MASK		(u_int8)0xFC


/* SIO Soft Reset */			/* API_SIO_SoftReaset */
#define IO_SIO_SOFTRESET_10			(u_int8)0x02
#define IO_SIO_SOFTRESET_01			(u_int8)0x01
/* SIO Receive FIFO_Clear */	/* API_SIO_RcvFIFO_Clear */
#define IO_SIO_RCVFIFO_CLEAR		(u_int8)0x80
/* SIO Send FIFO_Clear */	/* API_SIO_RcvFIFO_Clear */
#define IO_SIO_SNDFIFO_CLEAR		(u_int8)0x80




#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */

	/* SCxMOD0<SM1><SM0> */				/* API_SIO_IP_ModeSet */
#define IP_SIO_IO_MODE			0x00		/* I/O Interface Mode	*/
#define IP_SIO_UARTBIT7MODE		0x04		/* 7bit UART Mode		*/
#define IP_SIO_UARTBIT8MODE		0x08		/* 8bit UART Mode		*/
#define IP_SIO_UARTBIT9MODE		0x0C		/* 9bit UART Mode		*/
	/* SCxMOD0<SC1><SC0> */				/* API_SIO_IP_ClkSet */
#define IP_SIO_CLK_TB7OUT		0x00		/* Timer TB7OUT				*/
#define IP_SIO_CLK_BAUDRATE		0x01		/* Baudrate Generater		*/
#define IP_SIO_CLK_FSYS			0x02		/* Internal Clock(fsys)		*/
#define IP_SIO_CLK_SCLK0		0x04		/* External Clock(SCLK0)	*/
	/* SCxMOD1<FDPX1><FDPX0> */			/* API_SIO_TrnModeSet */
#define IP_SIO_TRS_ENABLE		0x00		/* Forwarding prohibition			*/
#define IP_SIO_HALFDOUBLE_RCV	0x20		/* Half duplex( receiving)		*/
#define IP_SIO_HALFDOUBLE_TRS	0x40		/* Half duplex(transmitting)		*/
#define IP_SIO_DOUBLE			0x60		/* Full duplex			*/
	/* SCxMOD1<SINT2-0> */				/* API_SIO_IntervalSet */
#define IP_SIO_INTVL_NOTING		0x00		/* none			*/
#define IP_SIO_INTVL_1SCLK		0x02		/* 1SCLK		*/
#define IP_SIO_INTVL_2SCLK		0x04		/* 2SCLK		*/
#define IP_SIO_INTVL_4SCLK		0x06		/* 4SCLK		*/
#define IP_SIO_INTVL_8SCLK		0x08		/* 8SCLK		*/
#define IP_SIO_INTVL_16SCLK		0x0A		/* 16SCLK		*/
#define IP_SIO_INTVL_32SCLK		0x0C		/* 32SCLK		*/
#define IP_SIO_INTVL_64SCLK		0x0E		/* 64SCLK		*/
	/* SCxBRCR<BRxCK1><BRxCK0> */		/* API_SIO_BR_ClkSet */
#define IP_SIO_BRCLK_T1			0x00		/* É”T1			*/
#define IP_SIO_BRCLK_T4			0x10		/* É”T4			*/
#define IP_SIO_BRCLK_T16		0x20		/* É”T16		*/
#define IP_SIO_BRCLK_T64		0x30		/* É”T64		*/
	/* SCxBRCR<BRxS3-0> */				/* API_SIO_BR_N_Set */
#define IP_SIO_BRN_16			0x00		/* 16		*/
#define IP_SIO_BRN_1			0x01		/*  1		*/
#define IP_SIO_BRN_2			0x02		/*  2		*/
#define IP_SIO_BRN_3			0x03		/*  3		*/
#define IP_SIO_BRN_4			0x04		/*  4		*/
#define IP_SIO_BRN_5			0x05		/*  5		*/
#define IP_SIO_BRN_6			0x06		/*  6		*/
#define IP_SIO_BRN_7			0x07		/*  7		*/
#define IP_SIO_BRN_8			0x08		/*  8		*/
#define IP_SIO_BRN_9			0x09		/*  9		*/
#define IP_SIO_BRN_10			0x0A		/* 10		*/
#define IP_SIO_BRN_11			0x0B		/* 11		*/
#define IP_SIO_BRN_12			0x0C		/* 12		*/
#define IP_SIO_BRN_13			0x0D		/* 13		*/
#define IP_SIO_BRN_14			0x0E		/* 14		*/
#define IP_SIO_BRN_15			0x0F		/* 15		*/
	/* SC0BRADD<BRxK3-0> */				/* API_SIO_BR16_K_Set */
#define IP_SIO_BR16K_ENABLE		0x00		/* setting is prohibited */
#define IP_SIO_BR16K_1			0x01		/* K=1		*/
#define IP_SIO_BR16K_2			0x02		/* K=2		*/
#define IP_SIO_BR16K_3			0x03		/* K=3		*/
#define IP_SIO_BR16K_4			0x04		/* K=4		*/
#define IP_SIO_BR16K_5			0x05		/* K=5		*/
#define IP_SIO_BR16K_6			0x06		/* K=6		*/
#define IP_SIO_BR16K_7			0x07		/* K=7		*/
#define IP_SIO_BR16K_8			0x08		/* K=8		*/
#define IP_SIO_BR16K_9			0x09		/* K=9		*/
#define IP_SIO_BR16K_10			0x0A		/* K=10		*/
#define IP_SIO_BR16K_11			0x0B		/* K=11		*/
#define IP_SIO_BR16K_12			0x0C		/* K=12		*/
#define IP_SIO_BR16K_13			0x0D		/* K=13		*/
#define IP_SIO_BR16K_14			0x0E		/* K=14		*/
#define IP_SIO_BR16K_15			0x0F		/* K=15		*/
	/* SCxRFC<RFIS> */					/* API_SIO_RcvIntFillSet */
#define IP_SIO_RFI_FILL			0x00		/* Reach fill level		*/
#define IP_SIO_RFI_FILL_OVER	0x01		/* When the fill level attainment and new data is read, the fill level is exceeded. 	*/
	/* SCxRFC<RIL1><RIL0> */			/* API_SIO_RcvIntFillSet */
#define IP_SIO_RFF_4BYTE		0x00		/* 4byte(in the case of full duplex 2byte)		*/
#define IP_SIO_RFF_1BYTE		0x01		/* 1byte	*/
#define IP_SIO_RFF_2BYTE		0x02		/* 2byte	*/
#define IP_SIO_RFF_3BYTE		0x03		/* 3byte	*/
	/* SCxTFC<TFIS> */					/* API_SIO_SndIntFillSet */
#define IP_SIO_SFI_FILL			0x00		/* Reach fill level	*/
#define IP_SIO_SFI_FILL_BELOW	0x01		/* When the fill level attainment and new data is read, it doesn't reach at the fill level.*/
	/* SCxTFC<TIL1><TIL0> */			/* API_SIO_SndIntFillSet */
#define IP_SIO_RFF_4BYTE		0x00		/* Empty	*/
#define IP_SIO_RFF_1BYTE		0x01		/* 1byte	*/
#define IP_SIO_RFF_2BYTE		0x02		/* 2byte	*/
#define IP_SIO_RFF_3BYTE		0x03		/* 3byte	*/



/**************************************************************/

void API_SIO_Init(SFR_SIOx_t * SioChSel);
void API_SIO_IP_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_SndDataSet(SFR_SIOx_t * SioChSel,u_int8 scbuf);
u_int8 API_SIO_RcvDataRead(SFR_SIOx_t * SioChSel);
void API_SIO_CR_Set(SFR_SIOx_t * SioChSel,u_int8 sccr);
void API_SIO_MOD0_Set(SFR_SIOx_t * SioChSel,u_int8 scmod0);
void API_SIO_MOD1_Set(SFR_SIOx_t * SioChSel,u_int8 scmod1);
void API_SIO_MOD2_Set(SFR_SIOx_t * SioChSel,u_int8 scmod2);
u_int8 API_SIO_MOD2_Read(SFR_SIOx_t * SioChSel);
void API_SIO_FCNF_Set(SFR_SIOx_t * SioChSel,u_int8 scfcnf);
void API_SIO_BR_Set(SFR_SIOx_t * SioChSel,u_int8 scbrcr,u_int8 scbradd);
u_int8 API_SIO_RcvData_8_Read(SFR_SIOx_t * SioChSel);
void API_SIO_ParityOddEvenSet(SFR_SIOx_t * SioChSel,IpSIO_ParityOddEven ParityOddEven);
void API_SIO_ParityEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
u_int8 API_SIO_ErrFlagReaf(SFR_SIOx_t * SioChSel);
void API_SIO_ClkEdgeSel(SFR_SIOx_t * SioChSel,IpSIO_ClkEdge ClkEdge);
void API_SIO_ClkSel(SFR_SIOx_t * SioChSel,IpSIO_ClkSel Clk);
void API_SIO_SndData_8_Set(SFR_SIOx_t * SioChSel,IpSIO_SndDataBit8 SndDataBit8);
void API_SIO_CTS_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_RcvEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_WupEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_IP_ModeSet(SFR_SIOx_t * SioChSel,u_int8 Siomode);
void API_SIO_IP_ClkSet(SFR_SIOx_t * SioChSel,u_int8 Sioclk);
void API_SIO_Idle(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_TrnModeSet(SFR_SIOx_t * SioChSel,u_int8 Transmode);
void API_SIO_SndEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_IntervalSet(SFR_SIOx_t * SioChSel,u_int8 Interval);
void API_SIO_UartStopBit(SFR_SIOx_t * SioChSel,IpSIO_StopBitLen StopBitLen);
void API_SIO_LsbMsbSet(SFR_SIOx_t * SioChSel,IpSIO_LsbMsbSel LsbMsbSel);
void API_SIO_W_BufEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_SoftReset(SFR_SIOx_t * SioChSel);
void API_SIO_BR16_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_BR_ClkSet(SFR_SIOx_t * SioChSel,u_int8 BR_Clk);
void API_SIO_BR_N_Set(SFR_SIOx_t * SioChSel,u_int8 BR_N);
void API_SIO_BR16_K_Set(SFR_SIOx_t * SioChSel,u_int8 BR16_K);
void API_SIO_RcvFIFO_ByteSet(SFR_SIOx_t * SioChSel,IpSIO_RcvFIFOByte RcvFIFOByte);
void API_SIO_SndFIFO_IntEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_RcvFIFO_IntEnable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_RXTX_CNT_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_FIFO_Enable(SFR_SIOx_t * SioChSel,IpFunctionState NewState);
void API_SIO_RcvFIFO_Clear(SFR_SIOx_t * SioChSel);
void API_SIO_RcvIntFillSet(SFR_SIOx_t * SioChSel,u_int8 RcvFIFOIntSel,u_int8 RcvFIFOFill);
void API_SIO_SndFIFO_Clear(SFR_SIOx_t * SioChSel);
void API_SIO_SndIntFillSet(SFR_SIOx_t * SioChSel,u_int8 SndFIFOIntSel,u_int8 SndFIFOFill);
u_int8 API_SIO_RcvFIFO_Status(SFR_SIOx_t * SioChSel);
u_int8 API_SIO_SndFIFO_Status(SFR_SIOx_t * SioChSel);
void API_SIO_UART_SET(SFR_SIOx_t * SioChSel,IpSIO_ParityOddEven ParityOddEven,IpFunctionState ParityEnable,IpFunctionState CTSEnable,IpSIO_StopBitLen StopBitLen);





#endif /* avoid double definition  */





