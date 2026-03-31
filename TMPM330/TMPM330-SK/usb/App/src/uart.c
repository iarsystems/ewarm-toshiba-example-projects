/******************** (c) Copyright IAR Systems 2009 ********************
* File Name          : uart.c
* Version            : V1.0
* Date               : 20/10/2008
* Description        : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "uart.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
* Function Name  : UART_Init
* Description    : Initialize the uart
* Input          : None.
* Return         : None.
*******************************************************************************/
void UART_Init(void)
{
	API_SIO_Init(SIO0);
	API_SIO_Init(SIO1);
	API_SIO_Init(SIO2);
	
		// enable uart0
	API_SIO_IP_Enable(SIO0, ENABLE);
	// no parity bit
	API_SIO_CR_Set(SIO0,0x00);
	// no handshake, 8-bit data, clock by baud rate generator
	API_SIO_MOD0_Set(SIO0,0x09);
	// Half duplex(TX)
	API_SIO_MOD1_Set(SIO0,0xC0);
	// 1-bit stop, LSB,  W-buff enable
	API_SIO_MOD2_Set(SIO0,0x04);	
	// Disable all fifo
	API_SIO_FCNF_Set(SIO0,0x00);
	// baut rate = 10M/2/8/16 = 19200
	API_SIO_BR_N_Set(SIO0,0x08);
	
	API_SIO_SndEnable(SIO0,ENABLE);
	
	// enable uart1
	API_SIO_IP_Enable(SIO1, ENABLE);
	// no parity bit
	API_SIO_CR_Set(SIO1,0x00);
	// no handshake, 8-bit data, clock by baud rate generator
	API_SIO_MOD0_Set(SIO1,0x09);
	// Half duplex(TX)
	API_SIO_MOD1_Set(SIO1,0xC0);
	// 1-bit stop, LSB,  W-buff enable
	API_SIO_MOD2_Set(SIO1,0x04);	
	// Disable all fifo
	API_SIO_FCNF_Set(SIO1,0x00);
	// baut rate = 10M/2/8/16 = 19200
	API_SIO_BR_N_Set(SIO1,0x08);
	
	API_SIO_SndEnable(SIO1,ENABLE);
	
		// enable uart2
	API_SIO_IP_Enable(SIO2, ENABLE);
	// no parity bit
	API_SIO_CR_Set(SIO2,0x00);
	// no handshake, 8-bit data, clock by baud rate generator
	API_SIO_MOD0_Set(SIO2,0x09);
	// Half duplex(RX)
	API_SIO_MOD1_Set(SIO2,0x20);
	// 1-bit stop, LSB,  W-buff enable
	API_SIO_MOD2_Set(SIO2,0x04);	
	// Disable all fifo
	API_SIO_FCNF_Set(SIO2,0x00);
	// baut rate = 10M/2/8/16 = 19200
	//API_SIO_BR_ClkSet(SIO1,0x06);
	API_SIO_BR_N_Set(SIO2,0x08);
	
	API_SIO_RcvEnable(SIO2,ENABLE);
}

/*******************************************************************************
* Function Name  : UART_Send
* Description    : Send data through uart
* Input          : SioChSel: SIO0,SIO1,SIO2
									 Txbuff: the data will be sent
* Return         : None.
*******************************************************************************/
void UART_Send(SFR_SIOx_t* SioChSel, u_int8* Txbuff)
{
	// u_int8 API_SIO_MOD2_Read(SFR_SIOx_t * SioChSel);

	while(*Txbuff != 0x00)
	{
		API_SIO_SndDataSet(SioChSel, *(Txbuff++));
		while(!(API_SIO_MOD2_Read(SioChSel)&0x80));
	}
}

/*******************************************************************************
* Function Name  : UART_Receive
* Description    : Receive the data through uart
* Input          : SioChSel: SIO0,SIO1,SIO2
									 NmbRxbuff: the number of data will be received
* Return         : the data received.
*******************************************************************************/
u_int8 * UART_Receive(SFR_SIOx_t * SioChSel, u_int8 NmbRxbuff)
{
	u_int8 i=0;
	u_int8 *Rxbuff;
	while(i < NmbRxbuff)
	{
		while(!(API_SIO_MOD2_Read(SioChSel)&0x40));
		*(Rxbuff++) = API_SIO_RcvDataRead(SioChSel);
		i++;
	}
	return(Rxbuff);
}
