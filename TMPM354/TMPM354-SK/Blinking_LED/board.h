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
#include <Toshiba\iotmpm354f10tfg.h>
#include "arm_comm.h"

#ifndef __BOARD_H
#define __BOARD_H

#define MAIN_OSC_FREQ   (10000000ul)
#define SYS_FREQ   	(80000000ul)

#define LED1				(1ul<<7)
#define LED2				(1ul<<6)
#define LED3				(1ul<<5)
#define LED4				(1ul<<4)
#define LED5				(1ul<<3)
#define LED6				(1ul<<2)
#define LED7				(1ul<<1)
#define LED8				(1ul<<0)

#define LED_INIT(led)     { OENA |= (led & (LED1|LED2)); \
                            OENH |= (led & (LED3|LED4|LED5|LED6|LED7|LED8));}
#define LED_DEINIT(led)   { OENA &= ~(led & (LED1|LED2)); \
                            OENH &= ~(led & (LED3|LED4|LED5|LED6|LED7|LED8));}

#define LED_ON(led)       { OUTA |= (led & (LED1|LED2)); \
                            OUTH |= (led & (LED3|LED4|LED5|LED6|LED7|LED8));}

#define LED_OFF(led)      { OUTA &= ~(led & (LED1|LED2)); \
                            OUTH &= ~(led & (LED3|LED4|LED5|LED6|LED7|LED8));}

#define LED_TGL(led)      { OUTA ^= (led & (LED1|LED2)); \
                            OUTH ^= (led & (LED3|LED4|LED5|LED6|LED7|LED8));}

#endif /* __BOARD_H */
