/***************************************************************************
 **
 **    This file defines the board specific definition
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2014
 **
 **    $Revision: 317 $
 **
 ***************************************************************************/
#include <Toshiba/iotz2000XBG.h>
#include "arm_comm.h"

#ifndef __BOARD_H
#define __BOARD_H

/* Timer Ticks per second*/
#define LED1                (1UL<<9)
#define LED2                (1UL<<8)

#define LED_MASK            (LED1 | LED2)
#define LED_PORT_OUT        GP1_ODR
#define LED_DIR             GP1_CR

#define LED1_ON()           (LED_PORT_OUT |=  LED1 )
#define LED1_OFF()          (LED_PORT_OUT &= ~LED1 )
#define LED1_TOGGLE()       (LED_PORT_OUT ^=  LED1 )

#define LED2_ON()           (LED_PORT_OUT |=  LED2 )
#define LED2_OFF()          (LED_PORT_OUT &= ~LED2 )
#define LED2_TOGGLE()       (LED_PORT_OUT ^=  LED2 )

#endif /* __BOARD_H */
