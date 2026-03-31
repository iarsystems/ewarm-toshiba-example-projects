/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2006
 *
 *    File name   : uart.c
 *    Description : UART module
 *
 *    History :
 *    1. Date        : January, 2011
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *
 *    $Revision: 41 $
 **************************************************************************/
/** include files **/
#define UART_GLOBAL
#include "uart.h"
/** local definitions **/
#define UART_INT_PRIO 128
/** default settings **/

/** external functions **/
extern void NVIC_IntEnable(Int32U IntNumber);
extern void NVIC_IntDisable(Int32U IntNumber);
extern void NVIC_ClrPend(Int32U IntNumber);
extern void NVIC_IntPri(Int32U IntNumber, Int8U Priority);
/** external data **/

/** internal functions **/

/** public data **/
pUartFifo_t pUartRxFifo; // Pointer to a FIFO Buffer of the UART0 Receive
pUartFifo_t pUartTxFifo; // Pointer to a FIFO Buffer of the UART0 Transmit
// Hold UART0 Evens (PE, BI, FE, OE)
UartLineEvents_t UartLineEvents;

#if UART_MODEM_STAT_ENA > 0
// Hold the Modem Lines States of UART1
// ( Delta CTS, Delta DSR, Delta RI, Delta DCD,
//  CTS, DSR, RI and DCD )
UartModemEvents_t UartModemEvents;
#endif // UART1_MODEM_STAT_ENA > 0
/** private data **/

/** public functions **/


/*************************************************************************
 * Function Name: FifoPush
 * Parameters: pUartFifo_t Fifo, Int8U Data
 *
 * Return: Boolean
 *
 * Description: Push a char in a FIFO. Return TRUE when push is successful
 *  or FALSE when the FIFO is full.
 *
 *************************************************************************/
static Boolean FifoPush(pUartFifo_t Fifo, Int8U Data)
{
Int32U IndxTmp;

  // calculate next push index
  IndxTmp = Fifo->PushIndx + 1;
  IndxTmp = IndxTmp % UART_FIFO_SIZE;

  // Check FIFO state
  if (IndxTmp == Fifo->PopIndx)
  {
    // The FIFO is full
   return(FALSE);
  }
  
  // Push the data
  Fifo->Buffer[Fifo->PushIndx] = Data;
  // Updating the push's index
  Fifo->PushIndx = IndxTmp;
  return(TRUE);
}

/*************************************************************************
 * Function Name: FifoPop
 * Parameters: pUartFifo_t Fifo, Int8U Data
 *
 * Return: Boolean
 *
 * Description: Pop a char from a FIFO. Return TRUE when pop is successful
 *  or FALSE when the FIFO is empty.
 *
 *************************************************************************/
static Boolean FifoPop(pUartFifo_t Fifo, pInt8U pData)
{
Int32U IndxTmp;

  // Check FIFO state
  if (Fifo->PushIndx == Fifo->PopIndx)
  {
    // The FIFO is empty
    return(FALSE);
  }
  // Calculate the next pop index
  IndxTmp = Fifo->PopIndx + 1;
  IndxTmp = IndxTmp % UART_FIFO_SIZE;
  // Pop the data
  *pData = Fifo->Buffer[Fifo->PopIndx];
  // Updating of the pop's index
  Fifo->PopIndx = IndxTmp;
  return(TRUE);
}

/*************************************************************************
 * Function Name: UartInit
 * Parameters: UartNum_t Uart, Int32U IrqSlot, UartMode_t UartMode
 *
 * Return: Boolean
 *
 * Description: Init UART
 *
 *************************************************************************/
Boolean UartInit(void)
{
  
  /*Function select*/
  UART_FR |= UART_TX | UART_RX | UART_CTS | UART_RTS ;
  /*OUTPUT Enable*/
  UART_CR |= UART_TX | UART_RTS;
  /*INPUT Enable*/
  UART_IE |= UART_RX | UART_CTS;

 /**/
  UARTCR    = (0<<14) |        /*Disable hardware flow control*/
              (0<<9) |         /*Disable RX*/
              (0<<8) |         /*Disable TX*/
              (0<<1) |         /*Disable IrDA */
              (0<<0) ;         /*Disable UART */

  UARTLCR_H = (3<<5) |         /*8-bits*/
              (0<<4) |         /*Fifo disable*/
              (0<<3) |         /*One stop bit*/
              (0<<2) |         /**/
              (0<<1) ;         /*No Parity*/
    
  /*alloc software RX fifo*/
  pUartRxFifo = (pUartFifo_t)malloc(sizeof(UartFifo_t));
  if(pUartRxFifo == NULL)
  {
    return(FALSE);
  }
  /*alloc software TX fifo*/
  pUartTxFifo = (pUartFifo_t)malloc(sizeof(UartFifo_t));
  if(pUartTxFifo == NULL)
  {
    free(pUartRxFifo);
    return(FALSE);
  }
  /* Init receive and transmit FIFOs*/
  pUartRxFifo->PopIndx = pUartRxFifo->PushIndx = \
  pUartTxFifo->PopIndx = pUartTxFifo->PushIndx = 0;
  /*Enable interrupts in NVIC*/
  NVIC_IntPri(INT_UART,UART_INT_PRIO);
  NVIC_IntEnable(INT_UART);
  
  UARTICR = 0x7F;             /*Clear interrupts*/

  UARTIMSC = (1<<4) ;         /*RX Interrupt enable*/
#if UART_MODEM_STAT_ENA > 0
  UARTIMSC |= (1<<1) ;         /*CTS Interrupt enable*/
#endif
  UARTCR   |= (1<<9) |         /*Enable RX*/
              (1<<8) |         /*Enable TX*/
              (1<<0) ;
  return(TRUE);
}

void INTUART_IRQHandler(void)
{
Int8U Data;

  if(UARTMIS & (1<<4))
  { 
    UARTICR |= (1<<4);
    // Push a new data into the receiver buffer
    if(!FifoPush(pUartRxFifo,(Int8U)UARTDR))
    {// the FIFO is full
      UartLineEvents.bOE = TRUE;
      /*Disable RX interrupt*/
      UARTIMSC &= ~((1<<4));
    }
    UartLineEvents.Data |= UARTRSR;
    UARTECR = 0xF;
  }

  if(UARTMIS & (1<<5))
  {
    UARTICR |= (1<<5);
    if(FifoPop(pUartTxFifo, &Data))
    {
      UARTDR = Data;
    }
    else
    {
      /*Disable TX FIFO interrupt*/
      UARTIMSC &= ~(1<<5); 
    }
  }

#if UART_MODEM_STAT_ENA > 0
  if(UARTMIS & (1<<1))
  {
    UARTICR |= (1<<1);
    UartModemEvents.bCTS = 1;
  }
#endif // UART1_MODEM_STAT_ENA > 0
}

/*************************************************************************
 * Function Name: UartSetLineCoding
 * Parameters:  UartNum_t Uart,UartLineCoding_t pUartCoding
 *
 * Return: None
 *
 * Description: Init UART Baud rate, Word width, Stop bits, Parity type
 *
 *************************************************************************/
void UartSetLineCoding(UartLineCoding_t UartCoding)
{
Int32U Div;
Int32U PCLK = CG_GetClock(CLK_FPERIPH)/16;

  /*Check parameters*/
  if ((UartCoding.dwDTERate == 0) || (UartCoding.dwDTERate > UART_MAX_BAUD_RATE))
  {
    return;
  }

  UARTCR  &= ~((1<<9) | (1<<8) | (1<<0));                 /*Disable TX and RX*/

  /**/
  Div = (PCLK*64 + (UartCoding.dwDTERate/2))/UartCoding.dwDTERate;
  /**/
  UARTFBRD = Div & 0x3F;
  UARTIBRD = (Div>>6) & 0xFFFF;

  UARTLCR_H &=  ~(1<<3);                           /**/
  UARTLCR_H |= (UartCoding.bStopBitsFormat);    /*Set stop bit*/ 

  UARTLCR_H &= ~(3<<5);                           /*Set Data bits*/
  UARTLCR_H |= (UartCoding.bDataBits);            /*Set Data bits*/
  /**/
  UARTLCR_H &= ~((1<<7)|(1<<2)|(1<<1));        /*Set parity*/
  UARTLCR_H |= (UartCoding.bParityType);       /*Set parity*/
  
  UARTCR  |= ((1<<9) | (1<<8) | (1<<0));       /*Enable TX and RX*/
}

/*************************************************************************
 * Function Name: UartRead
 * Parameters:  UartNum_t Uart, pInt8U pBuffer, Int32U BufferSize
 *
 * Return: Int32U
 *
 * Description: Read received data from UART.
 *              Return number of readied characters
 *
 *************************************************************************/
Int32U UartRead(pInt8U pBuffer, Int32U BufferSize)
{
Int32U Count;
  for (Count = 0; Count < BufferSize; ++Count)
  {
    if(!FifoPop(pUartRxFifo,pBuffer+Count))
    {
      /*Enable RX Interrupt*/
      UARTIMSC |= (1<<4);
      break;
    }
    /*Enable RX Interrupt*/
    UARTIMSC |= (1<<4);
  }
  
  return(Count);

}

/*************************************************************************
 * Function Name: UartWrite
 * Parameters:  UartNum_t Uart, pInt8U pBuffer, Int32U BufferSize
 *
 * Return: Int32U
 *
 * Description: Write a data to UART. Return number of successful
 *  transmitted bytes
 *
 *************************************************************************/
Int32U UartWrite(pInt8U pBuffer, Int32U BufferSize)
{
Int32U Count;

  for (Count = 0; Count < BufferSize; ++Count)
  {
    if(!FifoPush(pUartTxFifo,*(pBuffer+Count)))
    {
      break;
    }
    if(UARTFR_bit.TXFE)
    {
      FifoPop(pUartTxFifo, (pInt8U)&UARTDR);
    }
    /*Enable FIFO Interrupt*/
    UARTIMSC |= (1<<5);
  }
  return(Count);
}

/*************************************************************************
 * Function Name: UartGetUartEvents
 * Parameters:  UartNum_t Uart
 *
 * Return: UartLineEvents_t
 *
 * Description: Get Uart Line events (PE,OE, FE, BI)
 *
 *************************************************************************/
UartLineEvents_t UartGetUartLineEvents (void)

{
UartLineEvents_t  LineEvents;
  LineEvents.Data = 0;

  AtomicExchange(LineEvents.Data,&UartLineEvents.Data);
  return(LineEvents);
}


/*************************************************************************
 * Function Name: UartSetUartLineState
 * Parameters:   Boolean Break
 *
 * Return: none
 *
 * Description: Set Uart Break Event
 *
 *************************************************************************/
void UartSetUartLineState (Boolean Break)
{
      UARTLCR_H_bit.BRK = Break;
}

 #if UART_MODEM_STAT_ENA > 0
/*************************************************************************
 * Function Name: Uart1SetModemLineState
 * Parameters:  UartModemLineState_t UartModemLineState
 *
 * Return: none
 *
 * Description: Init UART1 Modem lines state (RTS, DTR)
 *
 *************************************************************************/
void UartSetModemLineState(UartModemLineState_t UartModemLineState)
{
  UARTCR_bit.RTS = UartModemLineState.bRTS;
}

/*************************************************************************
 * Function Name: Uart1GetUartModemEvents
 * Parameters:  none
 *
 * Return: UartModemEvents_t
 *
 * Description: Get Uart1 Modem lines events (DCD,DSR,CTS,RI)
 *
 *************************************************************************/
UartModemEvents_t UartGetUartModemEvents (void)
{
UartModemEvents_t  ModemEvents;
  ModemEvents.Data = 0;
  ModemEvents.Data = AtomicExchange(ModemEvents.Data,(pInt32U)&UartModemEvents);
  return(ModemEvents);
}
#endif // UART1_MODEM_STAT_ENA > 0
