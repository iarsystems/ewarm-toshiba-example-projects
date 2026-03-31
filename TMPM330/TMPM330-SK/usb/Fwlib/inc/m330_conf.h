/*******************************************************************************
* File Name 		 : m330_type.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : IP define
********************************************************************************/

/* avoid double definition */
#ifndef __M330_CONF_H
#define __M330_CONF_H


#include "m330_type.h"


#define _PORTA
#define _PORTB
#define _PORTC
#define _PORTD
#define _PORTE
#define _PORTF
#define _PORTG
#define _PORTH
#define _PORTI
#define _PORTJ
#define _PORTK

#define _TMRB0
#define _TMRB1
#define _TMRB2
#define _TMRB3
#define _TMRB4
#define _TMRB5
#define _TMRB6
#define _TMRB7
#define _TMRB8
#define _TMRB9

#define _SBI0
#define _SBI1
#define _SBI2

#define _SIO0
#define _SIO1
#define _SIO2

#define _ADC
#define _WDT
#define _RTC
#define _CG
#define _CEC
#define _RMC0
#define _RMC1
#define _FLASH
#define _NVIC



#ifdef  DEBUG
/*******************************************************************************
* Macro Name     : assert_param
* Description    : 
* Input          : exp:
* Return         : None
*******************************************************************************/ 
  #define assert_param(exp) ((exp) ? (void)0 : assert_failed((u_int8 *)__FILE__, __LINE__))
  void assert_failed(u_int8* file, u_int32 line);
#else
  #define assert_param(exp) ((void)0)
#endif /* DEBUG */


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    :
* Input          :
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u_int8* file, u_int32 line)
{ 
  while (1)
  {
  }
}
#endif /* DEBUG */


#endif /* avoid double definition */
