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

#if defined(IAR_TMPM369_SK)
#include  <Toshiba\iotmpm369FxFG.h>

//#define REV_A_BOARD

/*Clock Definitions*/
#define EHOSC   (16MHZ)
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

#define LED_PORT    PCDATA

#define INIT_LEDS() {  PCFR1 &= ~LED_MASK;  /* Port Function */ \
                        PCIE  &= ~LED_MASK;   /*Disable input*/   \
                        PCCR  |= LED_MASK;    /*Enable Output*/   \
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
#define UART_TX         (1<<2)
#define UART_RX         (1<<1)

#define UART_FR         PEFR1
#define UART_CR         PECR
#define UART_IE         PEIE

/*UART4*/
#define UART4_TX        (1<<1)
#define UART4_RX        (1<<2)
#define UART4_CTS       (1<<0)
#define UART4_RTS       (1<<3)

#define UART4_FR        PFFR3
#define UART4_CR        PFCR
#define UART4_IE        PFIE

/*USB Device*/
#define USBDPON          (1<<0)
#define USBDPON_FR       PKFR1
#define USBDPON_IE       PKIE
#define USBDPON_PORT     PKDATA

#define USBDPULLUP       (1<<0)
#define USBDPULLUP_CR    PECR
#define USBDPULLUP_PORT  PEDATA

#if defined(REV_A_BOARD)
#define USBDPULLUP_ON    {USBDPULLUP_PORT &= ~USBDPULLUP;}
#define USBDPULLUP_OFF   {USBDPULLUP_PORT |=  USBDPULLUP;}
#else
#define USBDPULLUP_ON    {USBDPULLUP_PORT |=  USBDPULLUP;}
#define USBDPULLUP_OFF   {USBDPULLUP_PORT &= ~USBDPULLUP;}
#endif

/*USB Host*/
#define USBHPON          (1<<3)
#define USBHPON_FR       PKFR1
#define USBHPON_IE       PKIE
#define USBHPON_PORT     PKDATA

#define USBHPOC          (1<<1)
#define USBHPOC_FR       PKFR1
#define USBHPOC_IE       PKIE
#define USBHPOC_PORT     PKDATA

/*SD Card*/
#define SD_CS           (1<<7)  // PG7
#define SD_CP           (1<<7)  // PE7
#define SD_WP           (1<<4)  // PE4
#define SD_OUT          (1<<5)  // PG5
#define SD_IN           (1<<6)  // PG6
#define SD_CLK          (1<<4)  // PG4

#define SD_FR           PGFR3
#define SD_CR           PGCR
#define SD_IE           PGIE
#define SD_PORT         PGDATA

#define SD_CP_PORT      PEDATA
#define SD_CP_IE        PEIE
#define SD_WP_PORT      PEDATA
#define SD_WP_IE        PEIE

#else
#error define type of the board
#endif

#endif /* __BOARD_H */
