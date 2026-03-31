/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
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
 *    3. Date        : January 19, 2012
 *       Author      : Stanimir Bonev
 *       Description : Port for IAR-TMPM369-SK
 *
 *    $Revision: 41 $
**************************************************************************/
#include "drv_hd44780_l.h"

/*************************************************************************
 * Function Name: HD44780_IO_Init
 * Parameters: none
 * Return: none
 * Description: Init IO ports directions and level
 *
 *************************************************************************/
void HD44780_IO_Init (void)
{

  LCD_RS_DIR |= LCD_RS;
  LCD_E_DIR  |= LCD_E;

  LDC_DATA_DIR  |= LCD_DATA_MASK;
  LDC_DATA_IN_E |= LCD_DATA_MASK;

  // RS Output - Low
  LCD_RS_LOW();
  // E  Output - Low
  LCD_E_LOW();

  // RW line init
  LCD_RW_DIR |= LCD_RW;
  // WR Output - Low
  LCD_RW_LOW();
}

/*************************************************************************
 * Function Name: HD44780SetRS
 * Parameters: Boolean Data
 * Return: none
 * Description: Set RS signal
 *
 *************************************************************************/
void HD44780SetRS (Boolean Data)
{
  if(Data)
  {
    LCD_RS_HIGH();
  }
  else
  {
    LCD_RS_LOW();
  }
}

/*************************************************************************
 * Function Name: HD44780SetE
 * Parameters: Boolean Data
 * Return: none
 * Description: Set E signal
 *
 *************************************************************************/
void HD44780SetE (Boolean Data)
{
  if(Data)
  {
    LCD_E_HIGH();
  }
  else
  {
    LCD_E_LOW();
  }
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
  LDC_DATA_DIR |= LCD_DATA_MASK;
#endif

  LCD_E_HIGH();
  LCD_DATA_PORT = Data & LCD_DATA_MASK;
  HD44780_BUS_DLY();
  LCD_E_LOW();
}

#if HD4780_WR > 0
/*************************************************************************
 * Function Name: HD44780SetRW
 * Parameters: Boolean Data
 * Return: none
 * Description: Set R/W signal
 *
 *************************************************************************/
void HD44780SetRW (Boolean Data)
{
  if(Data)
  {
    LCD_RW_HIGH();
  }
  else
  {
    LCD_RW_LOW();
  }
}

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
  // Set Direction
  LDC_DATA_DIR &= ~LCD_DATA_MASK;

  LCD_RW_HIGH();
  // Read Data
  LCD_E_HIGH();
  HD44780_BUS_DLY();
  Data = LCD_DATA_PORT;
  LCD_E_LOW();
  return Data;
}
#endif
