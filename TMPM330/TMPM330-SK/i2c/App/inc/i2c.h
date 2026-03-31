/******************** (c) Copyright IAR Systems 2009 ********************
* File Name          : i2c.h
* Version            : V1.0
* Date               : 20/10/2008
* Description        : 
*******************************************************************************/
#ifndef __I2C_H
#define __I2C_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* EEPROM Addresses defines */
#define EEPROM_ADDRESS 0xA0   /* E2 = 0 */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void I2C_Init(void);
void I2C_ByteWrite(u_int8* pBuffer, u_int8 WriteAddr);
void I2C_PageWrite(u_int8* pBuffer, u_int8 WriteAddr, u_int8 NumByteToWrite);
#endif /* I2C_H */

/*********************************** END OF FILE ******************************/
