/***************************************************************************
 **
 **    This file defines the board specific definition
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2014
 **
 **    $Revision: 41 $
 **
 ***************************************************************************/
#include <intrinsics.h>
#include <Toshiba\iotmpm358fdtfg.h>
#include "arm_comm.h"

#ifndef __BOARD_H
#define __BOARD_H

#define MAIN_OSC_FREQ   (8000000ul)
#define SYS_FREQ   	(40000000ul)

#define LED1				(1ul<<0)
#define LED2				(1ul<<1)
#define LED3				(1ul<<2)
#define LED4				(1ul<<3)
#define LED5				(1ul<<4)
#define LED6				(1ul<<5)
#define LED7				(1ul<<6)
#define LED8				(1ul<<7)

#define LED_INIT(led)     { OENB |= (led); }
#define LED_DEINIT(led)   { OENB &= ~(led); }

#define LED_ON(led)       { OUTB |= (led); }

#define LED_OFF(led)      { OUTB &= ~(led); }

#define LED_TGL(led)      { OUTB ^= (led); }

#endif /* __BOARD_H */
