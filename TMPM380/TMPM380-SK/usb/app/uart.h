/*******************************************************************************
* File Name 		 : uart.h
* Version			 : V1.0
* Date				 : 2010/03/xx
* Description		 : UART driver header
********************************************************************************/

#ifndef __UART_H
#define __UART_H

#include "..\typedef.h"


/**************************************************************/
void UART_Init(uint8_t ch, uint32_t baud);
uint8_t UART_Send(uint8_t ch, uint8_t *Txbuff);
uint8_t UART_Recv(uint8_t ch, uint8_t *Rxbuff);

#endif /* __UART_H */ 
