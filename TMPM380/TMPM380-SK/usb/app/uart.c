/*******************************************************************************
* File Name 		 : uart.c
* Version			 : V1.0
* Date				 : 2010/03/xx
* Description		 : UART driver source
********************************************************************************/

#include "m380_sio.h"
#include "m380_port.h"
#include "uart.h"

/*******************************************************************************
* Function Name  : UART_Init
* Description    : Initialize the uart
* Input          : None.
* Return         : None.
*******************************************************************************/
void UART_Init(uint8_t ch, uint32_t baud)
{
	volatile PORTM *port;
	SIOM *SioCh;
	volatile uint32_t dlycnt;

	switch (ch) {
	case 4:
		port = &PORT.cnl[PORT_C];
		port->IO_PxFR4	|= 0xC0;
		port->IO_PxCR	|= 0x40;
		port->IO_PxIE	|= 0x80;
		port->IO_PxPUP	|= 0x80;
		break;
	case 3:
		port = &PORT.cnl[PORT_F];
		port->IO_PxFR2	|= 0x18;
		port->IO_PxCR	|= 0x08;
		port->IO_PxIE	|= 0x10;
		port->IO_PxPUP	|= 0x10;
		break;
	case 2:
		port = &PORT.cnl[PORT_D];
		port->IO_PxFR1	|= 0x60;
		port->IO_PxCR	|= 0x20;
		port->IO_PxIE	|= 0x40;
		port->IO_PxPUP	|= 0x40;
		break;
	case 1:
		port = &PORT.cnl[PORT_A];
		port->IO_PxFR1	|= 0x60;
		port->IO_PxCR	|= 0x20;
		port->IO_PxIE	|= 0x40;
		port->IO_PxPUP	|= 0x40;
		break;
	case 0:
		port = &PORT.cnl[PORT_E];
		port->IO_PxFR1	|= 0x3;
		port->IO_PxCR	|= 0x1;
		port->IO_PxIE	|= 0x2;
		port->IO_PxPUP	|= 0x2;
		break;
	default:
		return;
	}

	SioCh = (SIOM *)&SIO.cnl[ch];
	API_SIO_Init(SioCh);
	
	// enable uart
	API_SIO_IP_Enable(SioCh, ENABLE);
	// no parity bit
	API_SIO_CR_Set(SioCh,0x00);
	// no handshake, 8-bit data, clock by baud rate generator
	API_SIO_MOD0_Set(SioCh,0x09);
	// Half duplex(TX)
	API_SIO_MOD1_Set(SioCh,0xC0);
	// 1-bit stop, LSB,  W-buff enable
	API_SIO_MOD2_Set(SioCh,0x04);	
	// Disable all fifo
	API_SIO_FCNF_Set(SioCh,0x00);
	
	// baud rate = 10M/16/baud
	API_SIO_BR_ClkSet(SioCh,0x10);
	switch(baud) {
	case 9600:
		API_SIO_BR_N_Set(SioCh,0);
		API_SIO_BR16_K_Set(SioCh,12);
		API_SIO_BR16_Enable(SioCh,ENABLE);
		break;
	case 14400:
		API_SIO_BR_N_Set(SioCh,10);
		API_SIO_BR16_K_Set(SioCh,2);
		API_SIO_BR16_Enable(SioCh,ENABLE);
		break;
	case 19200:
		API_SIO_BR_N_Set(SioCh,8);
		API_SIO_BR16_K_Set(SioCh,14);
		API_SIO_BR16_Enable(SioCh,ENABLE);
		break;
	case 38400:
		API_SIO_BR_N_Set(SioCh,4);
		break;
	case 57600:
		API_SIO_BR_N_Set(SioCh,2);
		API_SIO_BR16_K_Set(SioCh,5);
		API_SIO_BR16_Enable(SioCh,ENABLE);
		break;
	default:
		return;
	}
	/* Baud rate settling delay */
	for (dlycnt=0; dlycnt<65536; dlycnt++);
	
	API_SIO_FIFO_Enable(SioCh,ENABLE);
	API_SIO_SndEnable(SioCh,ENABLE);
	API_SIO_RcvEnable(SioCh,ENABLE);
	while(API_SIO_MOD2_Read(SioCh)&0x40) {
		API_SIO_RcvDataRead(SioCh);
	}
}

/*******************************************************************************
* Function Name  : UART_Send
* Description    : Send data through uart
* Input          : ch: Channel number (0-4)
*                  Txbuff: Transmitter buffer pointer
* Return         : None.
*******************************************************************************/
uint8_t UART_Send(uint8_t ch, uint8_t *Txbuff)
{
	SIOM *SioCh;
	uint8_t cnt = 0;

	SioCh = (SIOM *)&SIO.cnl[ch];

	while(*Txbuff != 0x00)
	{
		API_SIO_SndDataSet(SioCh, *Txbuff++);
		cnt++;
		while(!(API_SIO_MOD2_Read(SioCh)&0x80));
	}
	return cnt;
}

/*******************************************************************************
* Function Name  : UART_Recv
* Description    : Receive the data through uart
* Input          : ch: Channel number (0-4)
*                  Rxbuff: receiver buffer pointer
* Return         : the data count received.
*******************************************************************************/
uint8_t UART_Recv(uint8_t ch, uint8_t *Rxbuff)
{
	SIOM *SioCh;
	uint8_t rxdat, cnt = 0;

	SioCh = (SIOM *)&SIO.cnl[ch];

	while(API_SIO_MOD2_Read(SioCh)&0x40) {
		rxdat = API_SIO_RcvDataRead(SioCh);
		*Rxbuff++ = rxdat;
		if (rxdat == '\r') {
			*Rxbuff++ = '\n';
			cnt++;
		}
		cnt++;
	}
	return cnt;
}
