/******************** (c) Copyright IAR Systems 2009 ********************
* File Name          : uart.h
* Version            : V1.0
* Date               : 20/10/2008
* Description        : 
*******************************************************************************/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void UART_Init(void);
void UART_Send(SFR_SIOx_t * SioChSel, u_int8 *Txbuff);
u_int8 * USART_Receive(SFR_SIOx_t * SioChSel, u_int8 NmbRxbuff);

#endif

