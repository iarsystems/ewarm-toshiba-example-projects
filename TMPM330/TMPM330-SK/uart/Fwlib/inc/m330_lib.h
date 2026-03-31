/*******************************************************************************
* File Name 		 : m330_sfr.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : 
********************************************************************************/

/* avoid double definition */
#ifndef __M330_LIB_H
#define __M330_LIB_H



#include "m330_ip.h"


#ifdef _CEC
  #include "m330_cec.h"
#endif

#ifdef _RMC0
  #include "m330_rmc.h"
#endif

#ifdef _RMC1
  #include "m330_rmc.h"
#endif

#ifdef _PORTA
  #include "m330_port.h"
#endif

#ifdef _PORTB
  #include "m330_port.h"
#endif

#ifdef _PORTC
  #include "m330_port.h"
#endif

#ifdef _PORTD
  #include "m330_port.h"
#endif

#ifdef _PORTE
  #include "m330_port.h"
#endif

#ifdef _PORTF
  #include "m330_port.h"
#endif

#ifdef _PORTG
  #include "m330_port.h"
#endif

#ifdef _PORTH
  #include "m330_port.h"
#endif

#ifdef _PORTI
  #include "m330_port.h"
#endif

#ifdef _PORTJ
  #include "m330_port.h"
#endif

#ifdef _PORTK
  #include "m330_port.h"
#endif

#ifdef _CG
  #include "m330_cg.h"
#endif

#ifdef _TMRB0
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB1
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB2
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB3
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB4
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB5
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB6
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB7
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB8
  #include "m330_tmrb.h"
#endif

#ifdef _TMRB9
  #include "m330_tmrb.h"
#endif

#ifdef _NVIC
  #include "m330_int.h"
#endif


#ifdef _ADC
  #include "m330_adc.h"
#endif

#ifdef _SIO0
  #include "m330_sio.h"
#endif

#ifdef _SIO1
  #include "m330_sio.h"
#endif

#ifdef _SIO2
  #include "m330_sio.h"
#endif

#ifdef _SBI0
  #include "m330_sbi.h"
#endif

#ifdef _SBI1
  #include "m330_sbi.h"
#endif

#ifdef _SBI2
  #include "m330_sbi.h"
#endif

#ifdef _RTC
  #include "m330_rtc.h"
#endif

#ifdef _WDT
  #include "m330_wdt.h"
#endif

#ifdef _FLASH
  #include "m330_flash.h"
#endif



void debug(void);

#endif /* avoid double definition */
