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

#include "arm_comm.h"
#include "io_macros.h"

#ifndef __BOARD_H
#define __BOARD_H


/***************************************************************************
 **
 ** TMR0
 **
 ***************************************************************************/
__IO_REG32( TMR0_LOAD,            0x500C0000, __READ_WRITE );
__IO_REG32( TMR0_CNT,             0x500C0004, __READ_WRITE );
__IO_REG32( TMR0_CTRL,            0x500C0008, __READ_WRITE );
__IO_REG32( TMR0_ISR,             0x500C000C, __READ_WRITE );
__IO_REG32( CLK_CTRL_TMR0CLK,     0x5000DBFC, __READ_WRITE );
__IO_REG32( CG_OFF_TMR0,          0x5000D360, __READ_WRITE );
__IO_REG32( SWRST_OFF_TMR0,       0x5000D760, __READ_WRITE );

/***************************************************************************
 **
 ** GPIO1
 **
 ***************************************************************************/
__IO_REG32( GPIO1_ODATA,          0x500B9004, __READ_WRITE );
__IO_REG32( GPIO1_ODATASET,       0x500B9008, __READ_WRITE );
__IO_REG32( GPIO1_ODATACLR,       0x500B900C, __READ_WRITE );
__IO_REG32( GPIO1_DIR,            0x500B9010, __READ_WRITE );
__IO_REG32( GPIO1_DIROUT,         0x500B9014, __READ_WRITE );
__IO_REG32( GPIO1_DIRIN,          0x500B9018, __READ_WRITE );
__IO_REG32( CG_OFF_GPIO1,         0x5000D264, __READ_WRITE );
__IO_REG32( SWRST_OFF_GPIO1,      0x5000D664, __READ_WRITE );
__IO_REG32( IO_PIN_SEL3,          0x5002860C, __READ_WRITE );

/***************************************************************************
 **
 ** GPIO2
 **
 ***************************************************************************/
__IO_REG32( GPIO2_ODATA,          0x500BA004, __READ_WRITE );
__IO_REG32( GPIO2_ODATASET,       0x500BA008, __READ_WRITE );
__IO_REG32( GPIO2_ODATACLR,       0x500BA00C, __READ_WRITE );
__IO_REG32( GPIO2_DIR,            0x500BA010, __READ_WRITE );
__IO_REG32( GPIO2_DIROUT,         0x500BA014, __READ_WRITE );
__IO_REG32( GPIO2_DIRIN,          0x500BA018, __READ_WRITE );
__IO_REG32( CG_OFF_GPIO2,         0x5000D268, __READ_WRITE );
__IO_REG32( SWRST_OFF_GPIO2,      0x5000D668, __READ_WRITE );
__IO_REG32( IO_PIN_SEL4,          0x50028610, __READ_WRITE );

/***************************************************************************
 **
 ** GPIO3
 **
 ***************************************************************************/
__IO_REG32( GPIO3_ODATA,          0x500BB004, __READ_WRITE );
__IO_REG32( GPIO3_ODATASET,       0x500BB008, __READ_WRITE );
__IO_REG32( GPIO3_ODATACLR,       0x500BB00C, __READ_WRITE );
__IO_REG32( GPIO3_DIR,            0x500BB010, __READ_WRITE );
__IO_REG32( GPIO3_DIROUT,         0x500BB014, __READ_WRITE );
__IO_REG32( GPIO3_DIRIN,          0x500BB018, __READ_WRITE );
__IO_REG32( CG_OFF_GPIO3,         0x5000D26C, __READ_WRITE );
__IO_REG32( SWRST_OFF_GPIO3,      0x5000D66C, __READ_WRITE );
__IO_REG32( IO_PIN_SEL5,          0x50028614, __READ_WRITE );

/***************************************************************************
 **
 ** GIC-CPU
 **
 ***************************************************************************/
__IO_REG32( GIC_ICCICR,           0x50010000, __READ_WRITE );
__IO_REG32( GIC_ICCIAR,           0x5001000C, __READ       );
__IO_REG32( GIC_ICCPMR,           0x50010004, __READ_WRITE );
__IO_REG32( GIC_ICCBPR,           0x50010008, __READ_WRITE );
__IO_REG32( GIC_ICCEOIR,          0x50010010, __WRITE      );

/***************************************************************************
 **
 **  GIC-DISTRIBUTOR
 **
 ***************************************************************************/
/* Interrupt Controller Type Register, GIC_ICDICTR */
__IO_REG32( GIC_ICDDCR,           0x50011000, __READ_WRITE );
__IO_REG32( GIC_ICDISR0,          0x50011080, __READ_WRITE );
__IO_REG32( GIC_ICDISER0,         0x50011100, __READ_WRITE );
__IO_REG32( GIC_ICDICER0,         0x50011180, __READ_WRITE );
__IO_REG32( GIC_ICDISPR0,         0x50011200, __READ_WRITE );
__IO_REG8(  GIC_ICDIPR0,          0x50011400, __READ_WRITE );
__IO_REG32( GIC_ICDICTR,          0x50011004, __READ       );
__IO_REG8(  GIC_ICDIPR102,        0x50011466, __READ_WRITE );
__IO_REG32( GIC_ICDISER3,         0x5001110C, __READ_WRITE );

#define LED7											(1<<17)
#define LED8											(1<<26)
#define LED9											(1<<10)

#define LED_ALLBITS               (LED7|LED8|LED9)
#define INTNO_TMR0CNT0            102



#endif /* __BOARD_H */
