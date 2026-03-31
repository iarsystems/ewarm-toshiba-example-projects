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

#if defined(IAR_TMPM366_SK)
/*Clock Definitions*/
#define EHOSC   (12MHZ)
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

#define LED_PORT    PADATA

#define INIT_LEDS    {  PAFR1 &= ~LED_MASK;  /* Port Function */ \
                        PAIE &= ~LED_MASK;   /*Disable input*/   \
                        PACR |= LED_MASK;    /*Enable Output*/   \
                     }

#define LED_ON(led)   {LED_PORT |= led;}
#define LED_OFF(led)  {LED_PORT &= ~led;}

/*Buttons*/
#define PSW1        (1<<1)
#define PSW2        (1<<0)

#define BUTTON_MASK (PSW1 | PSW2)
#define BUTTON_PORT PDDATA

#define INIT_BUTTONS  { PDFR2 &= ~BUTTON_MASK; PDFR3 &= ~BUTTON_MASK; /* Port Function */ \
                        PDCR &= ~BUTTON_MASK; /*Disable outputs*/ \
                        PDIE |= BUTTON_MASK;  /*Enable inputs*/   \
                      }

#define GET_BUTTON(butt)  (BUTTON_PORT & butt)

/*UART*/
#define UART_TX       (1<<0)
#define UART_RX       (1<<1)
#define UART_CTS      (1<<2)
#define UART_RTS      (1<<4)

#define UART_FR       PGFR4
#define UART_CR       PGCR
#define UART_IE       PGIE
/*USB Host*/
#define USBPON        (1<<5)
#define USBPON_FR     PGFR4
#define USBPON_IE     PGIE
#define USBPON_PORT   PGDATA

#define USBPULLUP     (1<<4)
#define USBPULLUP_CR     PECR
#define USBPULLUP_PORT   PEDATA
#define USBPULLUP_ON  {USBPULLUP_PORT &= ~USBPULLUP;}
#define USBPULLUP_OFF {USBPULLUP_PORT |= USBPULLUP;}

/*SD Card*/
#define SD_CS         (1<<7)
#define SD_CP         (1<<2)
#define SD_WP         (1<<3)
#define SD_OUT        (1<<4)
#define SD_IN         (1<<5)
#define SD_CLK        (1<<6)

#define SD_FR         PDFR2
#define SD_CR         PDCR
#define SD_IE         PDIE
#define SD_PORT       PDDATA
/*PWM*/
#define PWM_OUT       (1<<2)
#define PWM_FR        PCFR3
#define PWM_CR        PCCR
#define PWM_PORT      PCDATA
/*TRIMER VR1*/
#define VR1           (1<<3)
#define VR1_IE        PKIE
/*ADC channels*/
#define VR1_CHANNEL   11

#else
#error define type of the board
#endif

#endif /* __BOARD_H */
