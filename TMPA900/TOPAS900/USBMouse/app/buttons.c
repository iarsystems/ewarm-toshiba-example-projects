/*************************************************************************
 *
 *    Used with ARM IAR C/C++ Compiler
 *
 *    (c) Copyright IAR Systems 2009
 *
 *    File name      : buttons.c
 *    Description    : Buttons module
 *
 *    History :
 *    1. Date        : 2, September 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 41 $
 **************************************************************************/
#include "buttons.h"

/*************************************************************************
 * Function Name: ButtonsInit
 * Parameters: none
 * Return: none
 * Description: Init buttons
 *
 *************************************************************************/
void ButtonsInit (void)
{
}

/*************************************************************************
 * Function Name: GetButtons
 * Parameters: none
 * Return: Buttons_t
 * Description: Return current buttons states
 *
 *************************************************************************/
Buttons_t GetButtons (void)
{
Buttons_t Buttons = {0};
  switch(0xF & GPIOADATA)
  {
  case 0:
    Buttons.JsLeft = 1;
    break;
  case 1:
    Buttons.JsDown = 1;
    break;
  case 2:
    Buttons.JsUp = 1;
    break;
  case 3:
    Buttons.JsRight = 1;
    break;
  case 4:
    Buttons.JsCenter = 1;
    break;
  }
  return(Buttons);
}
