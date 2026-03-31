/******************** (c) Copyright IAR Systems 2009 ********************
* File Name          : hw_config.c
* Version            : V1.0
* Date               : 20/10/2008
* Description        : Description of the hardware base on the pcb
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/*******************************************************************************
* Function Name  : Set_System
* Description    : Configures Main system clocks & power
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_System(void)
{
	Set_System_Clock();
	
	API_WDT_Set_WdtMode(0);
	API_WDT_Set_WdtCtrl(IP_WDT_DISABLECODE);
	
//	Buzz_IO_Configuration();
	Button_IO_Configuration();
//	LED_IO_Configuration();
	LCD_IO_Configuration();
//	ADC_IO_Configuration();
	Uart_IO_Configuration();
}


/*******************************************************************************
* Function Name  : Set_System_Clock
* Description    : Configures Main system clocks
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_System_Clock(void)
{
	// fc= fgear= fsys= fperiph= 10M
	API_CG_Init();
	API_CG_PLL_Sel(CG_PLL);
	//API_CG_IO_ClkSel(0x04);
}

/*******************************************************************************
* Function Name  : Button_IO_Configuration
* Description    : Configures Button IO port
* Input          : None.
* Return         : None.
*******************************************************************************/
void Button_IO_Configuration(void)
{
	// USER BUTTON PORT: PORTB
	// BUTTON1...4 --- PB4...7
	//API_PORT_CrRegSet( BUTTON_PORT, 0x01 );
	API_PORT_PupRegSet( KEY_PORT, 0xF6 );
	API_PORT_IeRegSet( KEY_PORT, 0xF6 );
}

/*******************************************************************************
* Function Name  : Buzz_IO_Configuration
* Description    : Configures Buzz IO port
* Input          : None.
* Return         : None.
*******************************************************************************/
void Buzz_IO_Configuration(void)
{
	// Buzz port --- PI0
	API_PORT_CrRegSet( BUZZ_PORT, 0x01 );
	API_PORT_PupRegSet( BUZZ_PORT, 0x01 );
}

/*******************************************************************************
* Function Name  : ADC_IO_Configuration
* Description    : Configures Buzz IO port
* Input          : None.
* Return         : None.
*******************************************************************************/
void ADC_IO_Configuration(void)
{
	// Potentiometer  port --- PC, PD
	//API_PORT_IeRegSet( MIC_PORT, MIC_PIN );
}


/*******************************************************************************
* Function Name  : LCD_IO_Configuration
* Description    : Configures LCD IO port
* Input          : None.
* Return         : None.
*******************************************************************************/
void LCD_IO_Configuration(void)
{
// LCD_PORT: PORTF, PORTH
// LCD DB4...7 --- PF4...7
// LCD CE, RW, RS --- PH1, PH2, PH3
// LCD BL --- PF2
	//API_PORT_CrRegSet( PORTF, LCD_DB | LCD_BL );
	//API_PORT_PupRegSet( PORTF, LCD_DB | LCD_BL );
	
	//API_PORT_CrRegSet( PORTH, LCD_E | LCD_RW | LCD_RS ); 
	//API_PORT_PupRegSet( PORTH, LCD_E | LCD_RW | LCD_RS  );
	
	API_PORT_CrRegSet( PORTF, 0xF4 );
	API_PORT_PupRegSet( PORTF, 0xF4 );
	
	API_PORT_CrRegSet( PORTH, 0x0E );
	API_PORT_PupRegSet( PORTH, 0x0E );
}

/*******************************************************************************
* Function Name  : LED_IO_Configuration
* Description    : Configures LED IO port
* Input          : None.
* Return         : None.
*******************************************************************************/
void LED_IO_Configuration(void)
{
// LCD_PORT: PORTF, PORTH
// LCD DB4...7 --- PF4...7
// LCD CE, RW, RS --- PH1, PH2, PH3
// LCD BL --- PF2
	//API_PORT_CrRegSet( LED_PORT_1, LED1 | LED2 | LED3 | LED4 );
	//API_PORT_PupRegSet( LED_PORT_1, LED1 | LED2 | LED3 | LED4 );
	
	//API_PORT_CrRegSet( LED_PORT_2, LED5 | LED6 | LED7 | LED8 ); 
	//API_PORT_PupRegSet( LED_PORT_2, LED5 | LED6 | LED7 | LED8 );
			
	API_PORT_CrRegSet( LED_PORT_1, 0x0F );
	API_PORT_PupRegSet( LED_PORT_1, 0x0F );
	
	API_PORT_CrRegSet( LED_PORT_2, 0x0F );
	API_PORT_PupRegSet( LED_PORT_2, 0x0F );
}

/*******************************************************************************
* Function Name  : Uart_IO_Configuration
* Description    : Configures uart IO port
* Input          : None.
* Return         : None.
*******************************************************************************/
void Uart_IO_Configuration(void)
{
// USART PORT: PORTE, PORTF
// UART0 TX, RX --- PE0, PE1
// UART1 TX, RX --- PE4, PE5
// API_PORT_Fr1RegSet(UART0_PORT, RXD1 | TXD1 | RXD0 | TXD0 );
// UART2 TX, RX --- PF0, PF1
// API_PORT_Fr1RegSet(UART2_PORT, RXD2 | TXD2 );
	
	API_PORT_Fr1RegSet( UART0_PORT,0x33 );
	API_PORT_Fr1RegSet( UART2_PORT,0x03 );
	
	API_PORT_CrRegSet( UART0_PORT, 0x11 );
	API_PORT_CrRegSet( UART2_PORT, 0x01 );
	
	API_PORT_IeRegSet( UART0_PORT, 0x22 );
	API_PORT_IeRegSet( UART2_PORT, 0x02 );
}

/*******************************************************************************
* Function Name  : Audio_IO_Configuration
* Description    : Configures audio IO port
* Input          : None.
* Return         : None.
*******************************************************************************/
void Audio_IO_Configuration(void)
{
	// Audio port --- PORTI
	// Audio pwm output pin --- PI1
	// API_PORT_CrRegSet( AUDIO_PORT, AUDIO ); 
	// API_PORT_Fr1RegSet( AUDIO_PORT, AUDIO );
	// Enable PI1 as output pin
	API_PORT_CrRegSet( AUDIO_PORT, 0x02 );
	// Enable PI1 as TB1OUT
	API_PORT_PupRegSet( AUDIO_PORT, 0x02 );
	
}
/*******************************************************************************
* Function Name  : Buzz_Status
* Description    : Enable or disable the buzz
* Input          : status --- ENABLE or DISABLE.
* Return         : None.
*******************************************************************************/
void Buzz_Status(IpFunctionState status )
{
	if(status == ENABLE)
		API_PORT_BitSet(BUZZ_PORT, BUZZ);
	else
		API_PORT_BitClr(BUZZ_PORT, BUZZ);		
}
/*******************************************************************************
* Function Name  : LED_Rolling
* Description    : rolling show the eight leds
* Input          : None.
* Return         : None.
*******************************************************************************/
void LED_Rolling(void)
{
	API_PORT_BitSet(LED_PORT_1, LED1);
	Delay_ms(100);
	API_PORT_BitClr(LED_PORT_1, LED1);
	API_PORT_BitSet(LED_PORT_1, LED2);
	Delay_ms(100);
	API_PORT_BitClr(LED_PORT_1, LED2);
	API_PORT_BitSet(LED_PORT_1, LED3);
	Delay_ms(100);
	API_PORT_BitClr(LED_PORT_1, LED3);
	API_PORT_BitSet(LED_PORT_1, LED4);
	Delay_ms(100);
	API_PORT_BitClr(LED_PORT_1, LED4);
	
	API_PORT_BitSet(LED_PORT_2, LED5);
	Delay_ms(100);
	API_PORT_BitClr(LED_PORT_2, LED5);
	API_PORT_BitSet(LED_PORT_2, LED6);
	Delay_ms(100);
	API_PORT_BitClr(LED_PORT_2, LED6);
	API_PORT_BitSet(LED_PORT_2, LED7);
	Delay_ms(100);
	API_PORT_BitClr(LED_PORT_2, LED7);
	API_PORT_BitSet(LED_PORT_2, LED8);
	Delay_ms(100);
	API_PORT_BitClr(LED_PORT_2, LED8);
}

/*******************************************************************************
* Function Name  : Delay_ms
* Description    : delay for some time in ms unit(accurate)
* Input          : How many ms of time to delay
* Return         : None.
*******************************************************************************/
void Delay_ms(int ms)
{
  for( int i=0; i<(ms*300); ++i );
}


/*********************************** END OF FILE ******************************/
