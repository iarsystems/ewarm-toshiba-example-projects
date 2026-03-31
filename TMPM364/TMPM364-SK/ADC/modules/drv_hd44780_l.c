/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2009
 *
 *    File name   : drv_hd44780_l.c
 *    Description : I/O function
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
 *************************************************************************/
#include "drv_hd44780_l.h"
#include "drv_hd44780_cnfg.h"

/*************************************************************************
 * Function Name: HD44780_IO_Init
 * Parameters: none
 * Return: none
 * Description: Init IO ports directions and level
 *
 *************************************************************************/
void HD44780_IO_Init (void)
{

  /*Select CPIO function*/
  LCD_RS_FR1 &= ~LCD_RS;
  LCD_RS_FR2 &= ~LCD_RS;
  /*Make pin output*/
  LCD_RS_IE &= ~LCD_RS;
  LCD_RS_CR |= LCD_RS;
  /*Select CPIO function*/
  LCD_E_FR1 &= ~LCD_E;
  LCD_E_FR2 &= ~LCD_E;
  /*Make pin output*/
  LCD_E_IE &= ~LCD_E;
  LCD_E_CR |= LCD_E;

  /*Select CPIO function*/
  LCD_DATA_FR1 &= ~LCD_DATA_MASK;
  /*Make pins outputs*/
  LCD_DATA_IE &= ~LCD_DATA_MASK;
  LCD_DATA_CR |= LCD_DATA_MASK;

#if HD4780_WR > 0
  /*Select CPIO function*/
  LCD_RW_FR1 &= ~LCD_RW;
  /*Make pin output*/
  LCD_RW_IE &= ~LCD_RW;
  LCD_RW_CR |= LCD_RW;
  LCD_RW_LOW();
#endif // HD4780_WR > 0

  HD44780SetPD();
}

/*************************************************************************
 * Function Name: HD44780SetPD
 * Parameters: none
 * Return: none
 * Description: Set power down
 *
 *************************************************************************/
void HD44780SetPD (void)
{
  // RS Output - Low
  LCD_RS_LOW();
  // E  Output - Low
  LCD_E_LOW();
  // Data lines High
  LCD_DATA_DATA |= LCD_DATA_MASK;
#if HD4780_WR > 0
  // WR Output - Low
  LCD_RW_LOW();
#endif // HD4780_WR > 0
}

/*************************************************************************
 * Function Name: HD44780SetPU
 * Parameters: none
 * Return: none
 * Description: Set power up
 *
 *************************************************************************/
void HD44780SetPU (void)
{
  HD44780_BUS_DLY();
  // RS Output - Low
  LCD_RS_LOW();
  // E  Output - Low
  LCD_E_LOW();
#if HD4780_WR > 0
  // WR Output - Low
  LCD_RW_HIGH();
#endif // HD4780_WR > 0
}

/*************************************************************************
 * Function Name: HD44780WrIO
 * Parameters: Int32U Data
 * Return: none
 * Description: Write to HD44780 I/O
 *
 *************************************************************************/
void HD44780WrIO (Int32U Data)
{
  // Write Data
#if HD4780_WR > 0
  LCD_RW_LOW();

  /*Make pins outputs*/
  LCD_DATA_IE &= ~LCD_DATA_MASK;
  LCD_DATA_CR |= LCD_DATA_MASK;

#endif
  LCD_E_HIGH();
  
  LCD_DATA_DATA  = Data & 0xFF;

  HD44780_BUS_DLY();
  LCD_E_LOW();
}

#if HD4780_WR > 0
/*************************************************************************
 * Function Name: HD44780RdIO
 * Parameters: none
 * Return: Int8U
 * Description: Read from HD44780 I/O
 *
 *************************************************************************/
Int8U HD44780RdIO (void)
{
Int8U Data;

 /*Make pins inputs*/
  LCD_DATA_CR &= ~LCD_DATA_MASK;
  LCD_DATA_IE |= LCD_DATA_MASK;

  LCD_RW_HIGH();
  // Read Data
  LCD_E_HIGH();
  HD44780_BUS_DLY();
  Data = LCD_DATA_DATA & LCD_DATA_MASK;
  LCD_E_LOW();
  return Data;
}
#endif
