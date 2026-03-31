/***************************************************************************
 **
 **    This file defines the board specific definition
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2013
 **
 **    $Revision: 41 $
 **
 ***************************************************************************/
#include <intrinsics.h>
#include <Toshiba\iotmpm440FxXBG.h>
#include "drv_adc.h"
#include "drv_cg.h"
#include "drv_gpio.h"

#ifndef __BOARD_H
#define __BOARD_H

#ifndef MHZ
#define MHZ           *1000000UL
#endif
#ifndef KHZ
#define KHZ           *1000UL
#endif
#ifndef MSEC
#define MSEC          *1000UL
#endif


/* Clock Definition */
#define EHOSC       (10MHZ)


/* Buttons on Port C */
#define PSW1        (1UL<<0)
#define PSW2        (1UL<<1)
#define PSW3        (1UL<<2)
#define PSW4        (1UL<<3)
#define PSW5        (1UL<<4)
#define PSW6        (1UL<<5)
#define PSW7        (1UL<<6)
#define PSW8        (1UL<<7)

#define PSW_MASK    (PSW1 | PSW2 | PSW3 | PSW4 | \
                     PSW5 | PSW6 | PSW7 | PSW8 )

/* PSW Port pin mapping */
#define PIN_PSW1		CH_PC(0)
#define PIN_PSW2		CH_PC(1)
#define PIN_PSW3		CH_PC(2)
#define PIN_PSW4		CH_PC(3)
#define PIN_PSW5		CH_PC(4)
#define PIN_PSW6		CH_PC(5)
#define PIN_PSW7		CH_PC(6)
#define PIN_PSW8		CH_PC(7)

/* PSW Interrupt line mapping */
#define INT_PSW1		INT_5
#define INT_PSW2		INT_6
#define INT_PSW3		INT_7
#define INT_PSW4		INT_8
#define INT_PSW5		INT_9
#define INT_PSW6		INT_A
#define INT_PSW7		INT_B
#define INT_PSW8		INT_C

/* LED Port Definitions */
#define LED1        (1UL<<0)
#define LED2        (1UL<<1)
#define LED3        (1UL<<2)
#define LED4        (1UL<<3)
#define LED5        (1UL<<4)
#define LED6        (1UL<<5)
#define LED7        (1UL<<6)
#define LED8        (1UL<<7)

#define LED_MASK    (LED1 | LED2 | LED3 | LED4 | \
                     LED5 | LED6 | LED7 | LED8 )

/* LED Port pin mapping */
#define PIN_LED1		CH_PAD(0)
#define PIN_LED2		CH_PAD(1)
#define PIN_LED3		CH_PAD(2)
#define PIN_LED4		CH_PAD(3)
#define PIN_LED5		CH_PAD(4)
#define PIN_LED6		CH_PAD(5)
#define PIN_LED7		CH_PAD(6)
#define PIN_LED8		CH_PAD(7)

/* VR1, VR2 setting */
#define VR1_CHNUM   CH_AINA(0)      /* AINA0 */
#define VR2_CHNUM   CH_AINA(1)      /* AINA1 */

/** public data **/

/** public functions **/
/* Board Access API */
void LED_INIT( void );
void PSW_INIT( uint8_t irq_mode );
void LED_ON( uint8_t led_mask );
void LED_OFF( uint8_t led_mask );
uint8_t LED_GETSTS( uint8_t led_mask );
uint8_t PSW_GETSTS( uint8_t sw_mask );



#endif /* __BOARD_H */
