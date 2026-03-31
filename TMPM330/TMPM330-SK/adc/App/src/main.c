/******************** (c) Copyright IAR Systems 2009 *************************
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
	u_int8 i,Volume=0;
	u_int16 AdcValue;
	Set_System();
	
  LCD_Configuration();
	LCD_Light(ON);
	
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("Press K1 to ADC  ");
	Send_To_LCD(SECOND_LINE, LCD_COMMAND);
	Send_LCD_Text(" then K2 to MIC ");
	while(API_PORT_BitIn(KEY_PORT, KEY1));
	
	ADC_Init();
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("ADC-Value:      ");
	while(API_PORT_BitIn(KEY_PORT, KEY2))
	{
		Send_To_LCD(SECOND_LINE, LCD_COMMAND);
		for(i=0; i<(ADC_Get_Value()/100); ++i)
			Send_To_LCD('*', LCD_CHARACTER);
		for(;i<16;i++)
			Send_To_LCD(' ', LCD_CHARACTER);
  }
	
	MIC_Init();
	Send_To_LCD(FIRST_LINE, LCD_COMMAND);
	Send_LCD_Text("MIC-Value:      ");
		while(1)
	{
		Send_To_LCD(SECOND_LINE, LCD_COMMAND);
		AdcValue = ADC_Get_Value();
		if(AdcValue >= 470)
			Volume = (AdcValue - 470)/10;
		else
			Volume = (470 - AdcValue)/10;
		if(Volume >= 16)
		{
			for(i=0; i<16; i++)
				Send_To_LCD('*', LCD_CHARACTER);
		}
		else
		{
			for(i=0; i<Volume; i++)
				Send_To_LCD('*', LCD_CHARACTER);
			for(;i<16;i++)
				Send_To_LCD(' ', LCD_CHARACTER);
  }
	}

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
