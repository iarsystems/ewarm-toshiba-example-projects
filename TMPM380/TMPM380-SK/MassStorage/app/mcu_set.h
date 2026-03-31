/*******************************************************************************
* File Name          : mcu_set.h
* Version            : V1.0
* Date				 : 2010/01/XX
* Description        : 
*******************************************************************************/
#ifndef __MCU_SET_H
#define __MCU_SET_H

#include	"../typedef.h"

/********************************************************************
 * Constant Definition
 ********************************************************************/

/********************************************************************
 * Function Definition
 ********************************************************************/
void	Sys_Initialize(void);
void	Int_Initialize(void);
void	Port_Initialize(void);
void	Led_Data_Write(uint8_t data);
void	Led_Digit_Write(uint8_t data);

#endif /* __MCU_SET_H */

/*********************************** END OF FILE ******************************/
