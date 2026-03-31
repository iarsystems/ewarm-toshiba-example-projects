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

#if defined(TOSHIBA_M374_STK)
/*Clock Definitions*/
#define EHOSC   (10MHZ)
/*LEDs*/
#define LED2        (1<<4)
#define LED3        (1<<5)
#define LED4        (1<<6)
#define LED5        (1<<7)

#define LED_MASK    (LED2|LED3|LED4|LED5)

#define LED_INIT    IOExp_Init()

#define LED_ON(led)   IOExp_Update((led)|IOExp_Get())
#define LED_OFF(led)  IOExp_Update((~(led))&IOExp_Get())
#define LED_TGL(led)  IOExp_Update((led)^IOExp_Get())

#else
#error define type of the board
#endif

#endif /* __BOARD_H */
