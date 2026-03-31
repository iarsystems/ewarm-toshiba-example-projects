/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : drv_hd44780_l.h
 *    Description : STM32 HD44780 low level I/O function driver
 *
 *    History :
 *    1. Date        : February 5, 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *    2. Date        : September 7, 2009
 *       Author      : Stoyan Choynev
 *       Description : Port for IAR-LPC1343-SK
 *    3. Date        : January 19, 2012
 *       Author      : Stanimir Bonev
 *       Description : Port for IAR-TMPM369-SK
 *
 *    $Revision: 41 $
 **************************************************************************/
#include "board.h"
#include "drv_hd44780_cnfg.h"

#ifndef  __DRV_HD44780_L_H
#define  __DRV_HD44780_L_H

#define LCD_RS                    (1UL << 5)  // PF5
#define LCD_RS_DIR                PFCR
#define LCD_RS_PORT               PFDATA

#define LCD_E                     (1UL << 4)  // PF4
#define LCD_E_DIR                 PFCR
#define LCD_E_PORT                PFDATA

#define LCD_RW                    (1UL << 3)  // PE3
#define LCD_RW_DIR                PECR
#define LCD_RW_PORT               PEDATA


#define LCD_DATA_MASK             0xFFUL
#define LDC_DATA_IN_E             PDIE
#define LDC_DATA_DIR              PDCR
#define LCD_DATA_PORT             PDDATA

#define LCD_E_HIGH()              LCD_E_PORT  |=  LCD_E
#define LCD_E_LOW()               LCD_E_PORT  &= ~LCD_E

#define LCD_RS_HIGH()             LCD_RS_PORT |=  LCD_RS
#define LCD_RS_LOW()              LCD_RS_PORT &= ~LCD_RS

#define LCD_RW_HIGH()             LCD_RW_PORT |=  LCD_RW
#define LCD_RW_LOW()              LCD_RW_PORT &= ~LCD_RW

/* Delay macro */
#define HD44780_BUS_DLY()         for(volatile int dly = 10;dly;--dly)

void HD44780_IO_Init (void);
void HD44780SetRS (Boolean Data);
void HD44780SetE (Boolean Data);
void HD44780WrIO (Int32U);
#if HD4780_WR > 0
void HD44780SetRW (Boolean Data);
Int8U HD44780RdIO (void);
#endif // HD4780_WR > 0


#endif  /* __DRV_HD44780_L_H */
