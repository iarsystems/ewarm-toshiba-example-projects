/***************************************************************************
 **
 **    This file defines the board specific definition
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2008
 **
 **    $Revision: 41 $
 **
 ***************************************************************************/
#include <Toshiba/iotmpa900cm.h>
#include "arm_comm.h"

#ifndef __BOARD_H
#define __BOARD_H

// OSCs [Hz]
#define MAIN_OSC_FREQ	       (24000000UL)
#define LF_OSC_FREQ		       (32768UL)

// Core clock frequency
#define FCLK                 (192MHZ)
// Memory controller clock frequency
#define PCLK                 (FCLK/2)

#endif /* __BOARD_H */
