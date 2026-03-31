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
 *    1. Date        : 25, March 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 41 $
 **************************************************************************/
#include "buttons.h"

#define _JS_RIGHT()        (0 == GPIOADATA_bit.PA1)
#define _JS_LEFT_MASK()    (0 == GPIOADATA_bit.PA2)
#define _JS_UP_MASK()      (0 == GPIOADATA_bit.PA0)
#define _JS_DOWN_MASK()    (0 == GPIOADATA_bit.PA3)
#define _JS_CENTER_MASK()  (0 == GPIOADATA_bit.PA4)


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
  if(_JS_RIGHT())
  {
    Buttons.JsRight = 1;
  }
  if(_JS_LEFT_MASK())
  {
    Buttons.JsLeft = 1;
  }
  if(_JS_UP_MASK())
  {
    Buttons.JsUp = 1;
  }
  if(_JS_DOWN_MASK())
  {
    Buttons.JsDown = 1;
  }
  if(_JS_CENTER_MASK())
  {
    Buttons.JsCenter = 1;
  }
  return(Buttons);
}
