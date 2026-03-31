/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2009
 *
 *    File name   : drv_hd44780_l.h
 *    Description : HD44780 low level I/O function driver
 *
 *    History :
 *    1. Date        : February 5, 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *    2. Date        : September 7, 2009
 *       Author      : Stoyan Choynev
 *       Description : Port for IAR-LPC1343-SK
 *    3. Date        : November 27, 2009
 *       Author      : Stanimir Bonev
 *       Description : Port for IAR-LPC1114-SK
 *    4. Date        : November 27, 2010
 *       Author      : Stoyan Choynev
 *       Description : Port for MB9BF506R-SK
 *
 *    $Revision: 41 $
 **************************************************************************/
#include <Toshiba\iotmpm364f10fg.h>
#include "arm_comm.h"

#ifndef  __DRV_HD44780_L_H
#define  __DRV_HD44780_L_H

#define LCD_RS                    (1 << 0)
#define LCD_RS_IE                 PPIE
#define LCD_RS_CR                 PPCR
#define LCD_RS_FR1                PPFR1
#define LCD_RS_FR2                PPFR2
#define LCD_RS_DATA               PPDATA

#define LCD_E                     (1 << 1)
#define LCD_E_IE                  PPIE
#define LCD_E_CR                  PPCR
#define LCD_E_FR1                 PPFR1
#define LCD_E_FR2                 PPFR2
#define LCD_E_DATA                PPDATA

#define LCD_RW                    (1 << 6)
#define LCD_RW_IE                 PPIE
#define LCD_RW_CR                 PPCR
#define LCD_RW_FR1                PPFR1
#define LCD_RW_FR2                PPFR2
#define LCD_RW_DATA               PPDATA

#define LCD_DATA_MASK             0xFF
#define LCD_DATA_IE               PBIE
#define LCD_DATA_CR               PBCR
#define LCD_DATA_FR1              PBFR1
#define LCD_DATA_DATA             PBDATA

#define LCD_E_HIGH()              LCD_E_DATA  |=  LCD_E
#define LCD_E_LOW()               LCD_E_DATA  &= ~LCD_E

#define LCD_RS_HIGH()             LCD_RS_DATA |=  LCD_RS
#define LCD_RS_LOW()              LCD_RS_DATA &= ~LCD_RS

#define LCD_RW_HIGH()             LCD_RW_DATA |=  LCD_RW
#define LCD_RW_LOW()              LCD_RW_DATA &= ~LCD_RW

/* Delay macro */
#define HD44780_BUS_DLY()         for(volatile int dly = 10;dly;--dly)

void HD44780_IO_Init (void);
void HD44780SetPD (void);
void HD44780SetPU (void);
void HD44780WrIO (Int32U);
#if HD4780_WR > 0
Int8U HD44780RdIO (void);
#endif // HD4780_WR > 0

#endif  /* __DRV_HD44780_L_H */
