/******************** (c) Copyright IAR Systems 2009 ***************************
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
	Set_System();
  LCD_Configuration();
//	Audio_IO_Configuration();	
	LCD_Light(ON);
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("Buzz To Speaker ");
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);
	Send_LCD_Text("Please Press K1 ");
	
	Buzz_Status(ENABLE);
	Delay_ms(300);
	Buzz_Status(DISABLE);
	
	while(API_PORT_BitIn(KEY_PORT, KEY1));
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("To Stop Speaker ");
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);
	Send_LCD_Text("Please Press K2 ");
	while(API_PORT_BitIn(KEY_PORT, KEY2))
	{
		API_PORT_BitClr(AUDIO_PORT, 0x01);
		Delay_ms(1);
		API_PORT_BitSet(AUDIO_PORT, 0x01);
		Delay_ms(1);
	}		
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("   TMPM330-SK   ");
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);
	Send_LCD_Text("   WWW.IAR.COM  ");
	//Audio_Out();

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
