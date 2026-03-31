/******************** (c) Copyright IAR Systems 2009 ********************
* File Name          : lcd.h
* Version            : V1.0
* Date               : 20/10/2008
* Description        : 
*******************************************************************************/
#ifndef __LCD_H
#define __LCD_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ON  1
#define OFF 0

#define LCD_COMMAND    0
#define LCD_CHARACTER  1

#define   CLR_DISP      0x00000001
#define   DISP          0x00000008
#define   DISP_ON       0x0000000C
#define   DISP_CUR      0x0000000E
#define   DISP_BINK_CUR 0x0000000F
#define   DISP_OFF      DISP
#define   CUR_HOME      0x00000002
#define   SCUR_OFF      DISP_ON
#define		CUR_UNDER     DISP_CUR
#define   CUR_BLINK     DISP_BINK_CUR
#define   CUR_LEFT      0x00000010
#define   CUR_RIGHT     0x00000014
#define   FIRST_LINE    0x00000080
#define   SECOND_LINE   0x000000C0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void E_Pulse(void);
void Set_Data(unsigned char data);
void Send_To_LCD(unsigned char data, unsigned char type);
void Send_LCD_Text(char * str);
void LCD_Configuration(void);
void LCD_Light(unsigned char BLStatus);

#endif /* LCD_H */

/*********************************** END OF FILE ******************************/
