/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2010
 *
 *    File name   : nvic.c
 *    Description : Toshiba TMPM380-SK led driver
 *
 *    History :
 *    1. Date        : 15.3.2010 
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdint.h>
#include "led.h"
/** local definitions **/

/** default settings **/

/** external functions **/

/** external data **/

/** internal functions **/

/** public data **/
char _7ledchar[] = {
ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, chA, chb, chC, chd, chE, chF
};

/** private data **/
static int LedState;
static char ledbuff[4];
/** public functions **/
/*************************************************************************
 * Function Name: LED_Init
 * Parameters:None
 *
 * Return:None  
 *
 * Description: Init LED ports
 *
 *************************************************************************/
void LED_Init(void)
{
   /*switch all leds off*/
  LedOFF( LED4 | LED5 | LED6 | LED7 |
          LED8 | LED9 | LED10| LED11);
  /*enable led outputs*/ 
  LED_OUTEN = LED4 | LED5 | LED6 | LED7 |
              LED8 | LED9 | LED10| LED11;
  /*switch all digits off*/
  DigitOFF(DIGIT0 | DIGIT1 | 
           DIGIT2 | DIGIT3);
  /*enable digit outputs*/
  DIGIT_OUTEN = DIGIT0 | DIGIT1 | 
                DIGIT2 | DIGIT3;
  /*digit 1 on*/
  //DigitON(DIGIT1);
  
  ledbuff[0] = chSpace;
  ledbuff[1] = ch0;
  ledbuff[2] = ch0;
  ledbuff[3] = ch0;
}
/*************************************************************************
 * Function Name: LED_Control
 * Parameters:None
 *
 * Return:None  
 *
 * Description: Drive leds.
 *
 *************************************************************************/
void LED_Control(void)
{
  /*switch all digits off*/
  DigitOFF(DIGIT0 | DIGIT1 | 
           DIGIT2 | DIGIT3);
  switch(LedState)
  {
  case 0:
    /*Copy buffer to port*/
    LED_PORT = ledbuff[0];
    /*digit 0 on*/
    DigitON(DIGIT0); 
    break;
  case 1:
    /*Copy buffer to port*/
    LED_PORT = ledbuff[1];
    /*digit 1 on*/
    DigitON(DIGIT1); 
    break;
  case 2:
    /*Copy buffer to port*/
    LED_PORT = ledbuff[2];
    /*digit 2 on*/
    DigitON(DIGIT2); 
    break;
  case 3:
    /*Copy buffer to port*/
    LED_PORT = ledbuff[3];
    /*digit 3 on*/
    DigitON(DIGIT3); 
    break;
  }
  
  if(3 < ++LedState) LedState = 0;
}
/*************************************************************************
 * Function Name: LED_WriteBuffer
* Parameters: data to write, Buffer index : 0 - 3
 *
 * Return: None
 *
 * Description: Write to LED buffer
 *
 *************************************************************************/
void LED_WriteBuff(char data, char digit)
{
  ledbuff[digit] = data;
}
/** private functions **/
