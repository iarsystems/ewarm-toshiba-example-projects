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
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u_int8 TxBuffer[13]="Hello world!";
u_int8 TxCounter = 0;
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
  Set_System();
	
  LCD_Configuration();
	LCD_Light(ON);
	
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("Connect USB cab-");
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);
	Send_LCD_Text("le and press K1");
	while(API_PORT_BitIn(KEY_PORT, KEY1));
	Uart_IO_Configuration();
	UART_Init();
	
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("Hyper-terminal: ");
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);
	Send_LCD_Text("Hello world!");
	
	//while(1)
		UART_Send(SIO1,TxBuffer);

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
