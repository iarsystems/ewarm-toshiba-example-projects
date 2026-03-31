/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2010
 *
 *    File name   : led.h
 *    Description : Toshiba TMPM380-SK LEDs 
 *                  header file
 *    History :
 *    1. Date        : 15.3.2010 
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    $Revision: 41 $
 **************************************************************************/
#ifndef __LED_H
#define __LED_H
/** include files **/
#include "Toshiba/iotmpm380fxfg.h"

/** definitions **/
/*Port*/
#define LED_PORT    PADATA
#define LED_OUTEN   PACR

#define DIGIT_PORT  PGDATA
#define DIGIT_OUTEN PGCR
/*Enable*/
#define DIGIT0   (1<<4)
#define DIGIT1   (1<<5)
#define DIGIT2   (1<<6)
#define DIGIT3   (1<<7)

#define DigitON(digit)  DIGIT_PORT &= ~digit;
#define DigitOFF(digit) DIGIT_PORT |= digit;

/*Seven segment LED definitions*/
#define segA  (1<<0)
#define segB  (1<<1)
#define segC  (1<<2)
#define segD  (1<<3)
#define segE  (1<<4)
#define segF  (1<<5)
#define segG  (1<<6)
#define segDP (1<<7)

/*Seven segnent LED char codes*/
#define ch0   ~(segA | segB | segC | segD | segE | segF       )
#define ch1   ~(       segB | segC                            )
#define ch2   ~(segA | segB        | segD | segE        | segG)
#define ch3   ~(segA | segB | segC | segD               | segG)
#define ch4   ~(       segB | segC               | segF | segG)
#define ch5   ~(segA        | segC | segD        | segF | segG)
#define ch6   ~(segA        | segC | segD | segE | segF | segG)
#define ch7   ~(segA | segB | segC                            )
#define ch8   ~(segA | segB | segC | segD | segE | segF | segG)
#define ch9   ~(segA | segB | segC | segD        | segF | segG)
#define chA   ~(segA | segB | segC        | segE | segF | segG)
#define chb   ~(              segC | segD | segE | segF | segG)
#define chC   ~(segA               | segD | segE | segF       )
#define chd   ~(       segB | segC | segD | segE        | segG)
#define chE   ~(segA               | segD | segE | segF | segG)
#define chF   ~(segA                      | segE | segF | segG)
#define chSpace 0xFF

/*LEDs difinitions*/
#define LED4  (1<<0)
#define LED5  (1<<4)
#define LED6  (1<<1)
#define LED7  (1<<5)
#define LED8  (1<<2)
#define LED9  (1<<6)
#define LED10 (1<<3)
#define LED11 (1<<7)

#define LedON(led)  LED_PORT &= ~led;
#define LedOFF(led) LED_PORT |= led;

/** public data **/
/*seven segment led code table*/
extern char _7ledchar[];

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
void LED_Init(void);

/*************************************************************************
 * Function Name: LED_Control
 * Parameters:None
 *
 * Return:None  
 *
 * Description: Drive leds.
 *
 *************************************************************************/
void LED_Control(void);

/*************************************************************************
 * Function Name: LED_WriteBuffer
* Parameters:data to write, Buffer index: 0 - 3
 *
 * Return: None
 *
 * Description: Write to LED buffer
 *
 *************************************************************************/
void LED_WriteBuff(char data, char digit);

#endif  /* __LED_H */
