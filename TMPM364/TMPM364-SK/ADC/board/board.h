/***************************************************************************
 **
 **    This file defines the board specific definition
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 41 $
 **
 ***************************************************************************/
#include <intrinsics.h>
#include "arm_comm.h"

#ifndef __BOARD_H
#define __BOARD_H

#if defined(IAR_TMPM364_SK)
/*Clock Definitions*/
#define EHOSC   (12MHZ)
#define ELOSC   (32768)
/*LEDs*/
#define LED1        (1<<0)
#define LED2        (1<<1)
#define LED3        (1<<2)
#define LED4        (1<<3)
#define LED5        (1<<4)
#define LED6        (1<<5)
#define LED7        (1<<6)
#define LED8        (1<<7)

#define LED_MASK    (LED1 | LED2 | LED3 | LED4 | \
                     LED5 | LED6 | LED7 | LED8 )

#define LED_PORT    PMDATA

#define INIT_LEDS    {  PMFR1 &= ~LED_MASK; PMFR2 &= ~LED_MASK;PMFR3 &= ~LED_MASK; /* Port Function */ \
                        PMIE &= ~LED_MASK;   /*Disable input*/   \
                        PMCR |= LED_MASK;    /*Enable Output*/   \
                     }

#define LED_ON(led)   {LED_PORT |= led;}
#define LED_OFF(led)  {LED_PORT &= ~led;}

/*Buttons*/
#define PSW1        (1<<7)
#define PSW2        (1<<6)
#define PSW3        (1<<5)
#define PSW4        (1<<4)

#define BUTTON_MASK (PSW1 | PSW2 | PSW3 | PSW4)
#define BUTTON_PORT PJDATA

#define INIT_BUTTONS  { PJFR2 &= ~BUTTON_MASK;/* Port Function */ \
                        PJIE |= BUTTON_MASK;  /*Enable inputs*/   \
                      }

#define GET_BUTTON(butt)  (BUTTON_PORT & butt)

/*UART*/
#define UART_TX       (1<<4)
#define UART_RX       (1<<5)
#define UART_CTS      (1<<6)

#define UART_FR       PNFR1
#define UART_CR       PNCR
#define UART_IE       PNIE

/*TRIMER VR2*/
#define VR2           (1<<0)
#define VR2_IE        PJIE
/*ADC channels*/
#define VR2_CHANNEL   0

#else
#error define type of the board
#endif

#endif /* __BOARD_H */
