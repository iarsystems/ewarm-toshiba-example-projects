/******************** (c) Copyright IAR Systems 2009 ********************
* File Name          : hw_config.h
* Version            : V1.0
* Date               : 20/10/2008
* Description        : 
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
//typedef enum { DISABLE = 0, ENABLE  = !DISABLE} FunctionalState;

/* Private define ------------------------------------------------------------*/

// ADC_PORT:	PORTC,	PORTD
// AN0...3 --- PC0...3
#define ADC_PORT_1	PORTC
#define AN0					BIT0
#define AN1					BIT1
#define AN2					BIT2
#define AN3					BIT3

// AN4...7 --- PD0...3
#define ADC_PORT_2	PORTD
#define AN4					BIT0
#define AN5					BIT1
#define AN6					BIT2
#define AN7					BIT3

// LED_PORT:	PORTG, PORTJ
// LED1...4 --- PG0...3
#define LED_PORT_1	PORTG
#define LED1				BIT0
#define LED2				BIT1
#define LED3				BIT2
#define LED4				BIT3
// LED5...8 --- PJ0...3
#define LED_PORT_2	PORTJ
#define LED5				BIT0
#define LED6				BIT1
#define LED7				BIT2
#define LED8				BIT3

// LCD_PORT: PORTF, PORTH
// LCD DB4...7 --- PF4...7
#define LCD_PORT_DB	PORTF
#define LCD_DB			0xF0
#define DB4					BIT4
#define DB5					BIT5
#define DB6					BIT6
#define DB7					BIT7
// LCD CE, RW, RS --- PH1, PH2, PH3
#define LCD_PORT_RW	PORTH
#define LCD_E				BIT1
#define LCD_RW			BIT2
#define LCD_RS			BIT3
// LCD BL --- PF2
#define LCD_PORT_BL	PORTF
#define LCD_BL			BIT2

// USER BUTTON PORT: PORTB
// KEY4...1 --- PB4...7
#define KEY_PORT	PORTB
#define KEY4			BIT4
#define KEY3			BIT5
#define KEY2			BIT6
#define KEY1			BIT7

// USART PORT: PORTE, PORTF
// UART0 TX, RX --- PE0, PE1
#define UART0_PORT		PORTE
#define TXD0					0x01
#define RXD0					0x02
// UART1 TX, RX --- PE4, PE5
#define UART1_PORT		PORTE
#define TXD1					0x10
#define RXD1					0x20
// UART2 TX, RX --- PF0, PF1
#define UART2_PORT		PORTF
#define TXD2					0x01
#define RXD2					0x02

// Buzz port --- PI0
#define BUZZ_PORT			PORTI
#define BUZZ					BIT0

// Audio PWM port --- PI1
#define AUDIO_PORT		PORTI
#define AUDIO					0x02

// Micphone  port --- PD7
#define MIC_PORT		PORTD
#define MIC_PIN			BIT7
#define MIC_AIN			BIT11

// Potentiometer  port --- PC0
#define ADC_PORT		PORTC
#define ADC_IN			BIT0

// I2C2  port: PORTG
// I2C2  SDA2, SCL2 --- PG4, PG5
#define I2C2_PORT			PORTD
#define SDA2					0x10
#define SCL2					0x20

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
void Set_System(void);
void Set_System_Clock(void);
void Button_IO_Configuration(void);
void Buzz_IO_Configuration(void);
void Audio_IO_Configuration(void);
void LCD_IO_Configuration(void);
void LED_IO_Configuration(void);
void ADC_IO_Configuration(void);
void Uart_IO_Configuration(void);
void Buzz_Status(IpFunctionState status );
void LED_Rolling(void);
void Delay_ms(int ms);
#endif  /*__HW_CONFIG_H*/

/*************************** END OF FILE **************************************/






