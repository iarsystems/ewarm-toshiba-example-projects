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
#include <Toshiba\iotmpm350fdtfg.h>
#include "arm_comm.h"

#ifndef __BOARD_H
#define __BOARD_H

#define MAIN_OSC_FREQ   (16000000ul)
#define SYS_FREQ   			(88000000ul)

#define LED1_MASK				(1ul<<0)
#define LED2_MASK				(1ul<<1)
#define LED3_MASK				(1ul<<2)
#define LED4_MASK				(1ul<<3)
#define LED5_MASK				(1ul<<4)
#define LED6_MASK				(1ul<<5)
#define LED7_MASK				(1ul<<6)
#define LED8_MASK				(1ul<<7)

#define LED_PORT_DIR  	OEND
#define LED_PORT				OUTD


#endif /* __BOARD_H */
