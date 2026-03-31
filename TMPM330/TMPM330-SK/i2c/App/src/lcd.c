/******************** (c) Copyright IAR Systems 2009 ***************************
* File Name          : lcd.c
* Version            : V1.0
* Date               : 20/10/2008
* Description        : configuration LCD and communication with MCU
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
* Function Name  : E_Pulse
* Description    : Generation a pulse enable the LCD.
* Input          : None.
* Return         : None.
*******************************************************************************/
void E_Pulse(void)
{
  // set E high
	API_PORT_BitSet(LCD_PORT_RW, LCD_E);
  Delay_ms( 10 );	
  // set E low 
	API_PORT_BitClr(LCD_PORT_RW, LCD_E); 
}

/*******************************************************************************
* Function Name  : Set_Data
* Description    : transfer data to LCD
* Input          : data --- The data will transfer to LCD
* Return         : None.
*******************************************************************************/
void Set_Data( unsigned char data )
{
	u_int8 cTemp;
	cTemp = API_PORT_Read(LCD_PORT_DB) & 0x0F;
	data = (data << 4) | cTemp;
	API_PORT_Out(LCD_PORT_DB, data);
}

/*******************************************************************************
* Function Name  : Send_To_LCD
* Description    : send command or data to LCD
* Input          : data --- command or data
									 type --- LCD_COMMAND or LCD_CHARACTER
* Return         : None.
*******************************************************************************/
void Send_To_LCD( unsigned char data, unsigned char type )
{
  // enable write
	API_PORT_BitClr(LCD_PORT_RW, LCD_RW); 
  Delay_ms( 2 );
  // set high nibble of command 
  Set_Data( (data >> 4) );
  // set RS port to set command mode or data 
	if(type == LCD_COMMAND)
		API_PORT_BitClr(LCD_PORT_RW, LCD_RS);
	else
		API_PORT_BitSet(LCD_PORT_RW, LCD_RS);
  // pulse to set D4-D7 bits  
  E_Pulse();
  // set low nibble of command 
  Set_Data( (data & 0x0F) );
  // set RS port to set command mode or data 
	if(type == LCD_COMMAND)
		API_PORT_BitClr(LCD_PORT_RW, LCD_RS);
	else
		API_PORT_BitSet(LCD_PORT_RW, LCD_RS);
  // pulse to set D4-D7 bits 
  E_Pulse();
}

/*******************************************************************************
* Function Name  : Send_LCD_Text
* Description    : Send the string to LCD 
* Input          : str --- pointer of the string 
* Return         : None.
*******************************************************************************/
void Send_LCD_Text( char * str )
{
	unsigned char i;
	/* loop over string and send each character */
  for( i=0; i<strlen(str); i++)
    {
      Send_To_LCD(str[i], LCD_CHARACTER);
    }
	for(;i<16;i++)
		Send_To_LCD(' ', LCD_CHARACTER);
}

/*******************************************************************************
* Function Name  : LCD_Configuration
* Description    : Configures LCD
* Input          : None.
* Return         : None.
*******************************************************************************/
void LCD_Configuration(void)
{
  /* LCD initialization step by step */
  // clear "command" bits 
	API_PORT_BitClr(LCD_PORT_RW, LCD_RS);
	API_PORT_BitClr(LCD_PORT_RW, LCD_RW); 
	API_PORT_BitClr(LCD_PORT_RW, LCD_E);
  Delay_ms( 10 );
  // set D4 and D5 high 	
	API_PORT_BitSet(LCD_PORT_DB, DB4); 
	API_PORT_BitSet(LCD_PORT_DB, DB5);	
  E_Pulse();
  Delay_ms( 10 );
  // set D4 and D5 high 	
	API_PORT_BitSet(LCD_PORT_DB, DB4); 
	API_PORT_BitSet(LCD_PORT_DB, DB5);
  E_Pulse();
  Delay_ms( 10 );
  // set D4 and D5 high
	API_PORT_BitSet(LCD_PORT_DB, DB4); 
	API_PORT_BitSet(LCD_PORT_DB, DB5);	
  E_Pulse();
  Delay_ms( 10 );
  //  set D4 to low and D5 to high  	
	API_PORT_BitClr(LCD_PORT_DB, DB4); 
	API_PORT_BitSet(LCD_PORT_DB, DB5);	
  E_Pulse();
  // enable display 
  Send_To_LCD(DISP_ON, LCD_COMMAND);
  // clear display 
  Send_To_LCD(CLR_DISP, LCD_COMMAND);
}

/*******************************************************************************
* Function Name  : LCD_Light
* Description    : Turn on or off the back light of LCD
* Input          : BLStatus --- ON or OFF
* Return         : None.
*******************************************************************************/
void LCD_Light( unsigned char BLStatus )
{
	if(BLStatus == ON)
		API_PORT_BitSet(LCD_PORT_BL, LCD_BL);
	else
		API_PORT_BitClr(LCD_PORT_BL, LCD_BL);
}

/*********************************** END OF FILE ******************************/

