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
void	Timer_Initialize(void);
void	MPTimer_Initialize(void);
void	Port_Initialize(void);
void	Port_Refresh(void);
void	SW1_Input(void);
void	SW2_Input(void);
void	SW3_Input(void);
void	Led_Data_Write(uint8_t data);
void	Led_Digit_Write(uint8_t data);
void	Timer4_Start(void);
void	Timer4_Stop(void);

#endif /* __MCU_SET_H */

/*********************************** END OF FILE ******************************/
