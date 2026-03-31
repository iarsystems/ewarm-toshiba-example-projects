/******************** (c) Copyright IAR Systems 2009 ********************
* File Name          : main.c
* Version            : V1.0
* Date               : 20/10/2008
* Description        : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TxBufferSize   (countof(TxBuffer))
/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
/* Private variables ---------------------------------------------------------*/
u_int8 TxBuffer[]="Hello world!";
u_int8 RxBuffer[TxBufferSize];
u_int8 TxCounter = 0, RxCounter = 0;
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
	debug();
#endif
	u_int8 i;
  Set_System();
	
  LCD_Configuration();
	LCD_Light(ON);
	
	Uart_IO_Configuration();
	UART_Init();	
	
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("Plug UART cable");	
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);
	Send_LCD_Text("and press K1");
	
	while(API_PORT_BitIn(KEY_PORT, KEY1));
	
	
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("UART0 to UART2: ");	
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);	
	for(i=0;i<16;i++)
			Send_To_LCD(' ', LCD_CHARACTER);
	
	while(TxCounter < TxBufferSize)
  {
		API_SIO_SndDataSet(SIO0, TxBuffer[TxCounter++]);
		while(!(API_SIO_MOD2_Read(SIO0)&0x80));
		while(!(API_SIO_MOD2_Read(SIO2)&0x40));
		RxBuffer[RxCounter++] = API_SIO_RcvDataRead(SIO2);
	}
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);
	for(i=0; i<RxCounter-1; ++i)
			Send_To_LCD(RxBuffer[i], LCD_CHARACTER);
	for(;i<16;i++)
			Send_To_LCD(' ', LCD_CHARACTER);
	
//USART_Send(SIO1,TxBuffer);
	///////////////////////////////////////////////////////////////
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/*********************************** END OF FILE ******************************/
