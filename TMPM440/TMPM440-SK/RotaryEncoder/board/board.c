/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : board.c
 *    Description : Toshiba TMPM440-SK Board specific functional interface
 *
 *    History :
 *    1. Date        : 7.2013
 *       Author      : Santohs Pawar
 *       Description : initial revision
 *
 **************************************************************************/
/** include files **/
#include <stdint.h>
#include <Toshiba\iotmpm440FxXBG.h>
#include <assert.h>
#include "drv_gpio.h"
#include "board.h"

/** local definitions **/

/** default settings **/

/** external functions **/

/** external data **/

/** internal functions **/

/** public data **/
const gpio_init_t led_initdata = {
    .mode =     PMODE_OUTPUT,
    .pull =     PIN_PUP,
};

const gpio_init_t psw_initport = {
    .mode =     PMODE_INPUT,
    .pull =     PIN_PUP,
};

const gpio_init_t psw_initfr3 = {
    .mode =     PMODE_FR3,
    .pull =     PIN_PUP,
};

const gpio_init_t *psw_initdata[] = { &psw_initport, &psw_initfr3 };

/** private data **/

/** public functions **/
/*************************************************************************
 * Function Name:   LED_INIT
 * Parameters:      none
 * Return:          none
 *
 * Description:     Setup LED Port
 *
 *************************************************************************/
void LED_INIT( void )
{
  fclk_ena_port( FCLK_PORTAD );
  GPIO_SetMode( PIN_LED1, &led_initdata );
  GPIO_SetMode( PIN_LED2, &led_initdata );
  GPIO_SetMode( PIN_LED3, &led_initdata );
  GPIO_SetMode( PIN_LED4, &led_initdata );
  GPIO_SetMode( PIN_LED5, &led_initdata );
  GPIO_SetMode( PIN_LED6, &led_initdata );
  GPIO_SetMode( PIN_LED7, &led_initdata );
  GPIO_SetMode( PIN_LED8, &led_initdata );
}

/*************************************************************************
 * Function Name:   LED_ON
 * Parameters:      led_mask
 * Return:          none
 *
 * Description:     Turn ON one or more leds defined with led_mask pattern
 *
 *************************************************************************/
void LED_ON( uint8_t led_mask )
{
  if (LED1 & led_mask)  GPIO_ClearData( PIN_LED1 );
  if (LED2 & led_mask)  GPIO_ClearData( PIN_LED2 );
  if (LED3 & led_mask)  GPIO_ClearData( PIN_LED3 );
  if (LED4 & led_mask)  GPIO_ClearData( PIN_LED4 );
  if (LED5 & led_mask)  GPIO_ClearData( PIN_LED5 );
  if (LED6 & led_mask)  GPIO_ClearData( PIN_LED6 );
  if (LED7 & led_mask)  GPIO_ClearData( PIN_LED7 );
  if (LED8 & led_mask)  GPIO_ClearData( PIN_LED8 );
}

/*************************************************************************
 * Function Name:   LED_OFF
 * Parameters:      led_mask
 * Return:          none
 *
 * Description:     Turn OFF one or more leds defined with led_mask pattern
 *
 *************************************************************************/
void LED_OFF( uint8_t led_mask )
{
  if (LED1 & led_mask)  GPIO_SetData( PIN_LED1 );
  if (LED2 & led_mask)  GPIO_SetData( PIN_LED2 );
  if (LED3 & led_mask)  GPIO_SetData( PIN_LED3 );
  if (LED4 & led_mask)  GPIO_SetData( PIN_LED4 );
  if (LED5 & led_mask)  GPIO_SetData( PIN_LED5 );
  if (LED6 & led_mask)  GPIO_SetData( PIN_LED6 );
  if (LED7 & led_mask)  GPIO_SetData( PIN_LED7 );
  if (LED8 & led_mask)  GPIO_SetData( PIN_LED8 );
}

/*************************************************************************
 * Function Name:   LED_GETSTS
 * Parameters:      led_mask
 * Return:          LED Port data status
 *
 * Description:     Reads status of leds defined with led_mask pattern
 *
 *************************************************************************/
uint8_t LED_GETSTS( uint8_t led_mask )
{
  uint8_t pdata = 0;
  pdata |= (GPIO_ReadData( PIN_LED1 )? 0: LED1);
  pdata |= (GPIO_ReadData( PIN_LED2 )? 0: LED2);
  pdata |= (GPIO_ReadData( PIN_LED3 )? 0: LED3);
  pdata |= (GPIO_ReadData( PIN_LED4 )? 0: LED4);
  pdata |= (GPIO_ReadData( PIN_LED5 )? 0: LED5);
  pdata |= (GPIO_ReadData( PIN_LED6 )? 0: LED6);
  pdata |= (GPIO_ReadData( PIN_LED7 )? 0: LED7);
  pdata |= (GPIO_ReadData( PIN_LED8 )? 0: LED8);
  return pdata;
}


/*************************************************************************
 * Function Name:   PSW_INIT
 * Parameters:      irq_mode - interrupt mode
 * Return:          none
 *
 * Description:     Setup Switch Port
 *
 *************************************************************************/
void PSW_INIT( uint8_t irq_mode )
{
  fclk_ena_port( FCLK_PORTC );
  if (irq_mode>0) irq_mode=1;
  GPIO_SetMode( PIN_PSW1, psw_initdata[irq_mode] );
  GPIO_SetMode( PIN_PSW2, psw_initdata[irq_mode] );
  GPIO_SetMode( PIN_PSW3, psw_initdata[irq_mode] );
  GPIO_SetMode( PIN_PSW4, psw_initdata[irq_mode] );
  GPIO_SetMode( PIN_PSW5, psw_initdata[irq_mode] );
  GPIO_SetMode( PIN_PSW6, psw_initdata[irq_mode] );
  GPIO_SetMode( PIN_PSW7, psw_initdata[irq_mode] );
  GPIO_SetMode( PIN_PSW8, psw_initdata[irq_mode] );
}

/*************************************************************************
 * Function Name:   PSW_GETSTS
 * Parameters:      sw_mask
 * Return:          Switch Port data status
 *
 * Description:     Reads status of switches defined with sw_mask pattern
 *
 *************************************************************************/
uint8_t PSW_GETSTS( uint8_t sw_mask )
{
  uint8_t pdata = 0;
  pdata |= (GPIO_ReadData( PIN_PSW1 )? 0: PSW1);
  pdata |= (GPIO_ReadData( PIN_PSW2 )? 0: PSW2);
  pdata |= (GPIO_ReadData( PIN_PSW3 )? 0: PSW3);
  pdata |= (GPIO_ReadData( PIN_PSW4 )? 0: PSW4);
  pdata |= (GPIO_ReadData( PIN_PSW5 )? 0: PSW5);
  pdata |= (GPIO_ReadData( PIN_PSW6 )? 0: PSW6);
  pdata |= (GPIO_ReadData( PIN_PSW7 )? 0: PSW7);
  pdata |= (GPIO_ReadData( PIN_PSW8 )? 0: PSW8);
  return pdata;
}

/** private functions **/
