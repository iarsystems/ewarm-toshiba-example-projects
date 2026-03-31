/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : drv_adc.h
 *    Description : Toshiba TMPM440 GPIO Control
 *
 *    History :
 *    1. Date        : 7.2013
 *       Author      : Santosh Pawar
 *       Description : initial revision
 *
 **************************************************************************/
#ifndef __GPIO_H
#define __GPIO_H
/** include files **/
#include <stdint.h>
#include "io_macros.h"
/** definitions **/


/* PORT definitions */
#define CH_PORTA      0
#define CH_PORTB      1
#define CH_PORTC      2
#define CH_PORTD      3
#define CH_PORTE      4
#define CH_PORTF      5
#define CH_PORTG      6
#define CH_PORTH      7
#define CH_PORTJ      8
#define CH_PORTK      9
#define CH_PORTL      10
#define CH_PORTM      11
#define CH_PORTN      12
#define CH_PORTP      13
#define CH_PORTR      14
#define CH_PORTT      15
#define CH_PORTU      16
#define CH_PORTV      17
#define CH_PORTW      18
#define CH_PORTY      19
#define CH_PORTAA     20
#define CH_PORTAB     21
#define CH_PORTAC     22
#define CH_PORTAD     23
#define CH_PORTAE     24
#define CH_PORTAF     25
#define CH_PORTAG     26
#define CH_PORTAH     27
#define CH_PORTAJ     28

/* PORT bit definitions */
#define CH_PA(x)      ((CH_PORTA<<4) + ((x)&0xF))
#define CH_PB(x)      ((CH_PORTB<<4) + ((x)&0xF))
#define CH_PC(x)      ((CH_PORTC<<4) + ((x)&0xF))
#define CH_PD(x)      ((CH_PORTD<<4) + ((x)&0xF))
#define CH_PE(x)      ((CH_PORTE<<4) + ((x)&0xF))
#define CH_PF(x)      ((CH_PORTF<<4) + ((x)&0xF))
#define CH_PG(x)      ((CH_PORTG<<4) + ((x)&0xF))
#define CH_PH(x)      ((CH_PORTH<<4) + ((x)&0xF))
#define CH_PJ(x)      ((CH_PORTJ<<4) + ((x)&0xF))
#define CH_PK(x)      ((CH_PORTK<<4) + ((x)&0xF))
#define CH_PL(x)      ((CH_PORTL<<4) + ((x)&0xF))
#define CH_PM(x)      ((CH_PORTM<<4) + ((x)&0xF))
#define CH_PN(x)      ((CH_PORTN<<4) + ((x)&0xF))
#define CH_PP(x)      ((CH_PORTP<<4) + ((x)&0xF))
#define CH_PR(x)      ((CH_PORTR<<4) + ((x)&0xF))
#define CH_PT(x)      ((CH_PORTT<<4) + ((x)&0xF))
#define CH_PU(x)      ((CH_PORTU<<4) + ((x)&0xF))
#define CH_PV(x)      ((CH_PORTV<<4) + ((x)&0xF))
#define CH_PW(x)      ((CH_PORTW<<4) + ((x)&0xF))
#define CH_PY(x)      ((CH_PORTY<<4) + ((x)&0xF))
#define CH_PAA(x)     ((CH_PORTAA<<4) + ((x)&0xF))
#define CH_PAB(x)     ((CH_PORTAB<<4) + ((x)&0xF))
#define CH_PAC(x)     ((CH_PORTAC<<4) + ((x)&0xF))
#define CH_PAD(x)     ((CH_PORTAD<<4) + ((x)&0xF))
#define CH_PAE(x)     ((CH_PORTAE<<4) + ((x)&0xF))
#define CH_PAF(x)     ((CH_PORTAF<<4) + ((x)&0xF))
#define CH_PAG(x)     ((CH_PORTAG<<4) + ((x)&0xF))
#define CH_PAH(x)     ((CH_PORTAH<<4) + ((x)&0xF))
#define CH_PAJ(x)     ((CH_PORTAJ<<4) + ((x)&0xF))

/*GPIO pin mode typedef */
typedef enum _gpio_mode_t
{
  PMODE_INPUT = 0,    /* Input mode */
  PMODE_OUTPUT,       /* Output mode */
  PMODE_FR1,          /* FR1 mode */
  PMODE_FR2,          /* FR2 mode */
  PMODE_FR3,          /* FR3 mode */
} gpio_mode_t;

/*GPIO pin pull up/down mode typedef */
typedef enum _gpio_pull_t
{
  PIN_OPEN = 0,   /* Open */
  PIN_OD,         /* Open drain */
  PIN_PUP,        /* pull up mode */
  PIN_PDOWN,      /* pull down mode */
} gpio_pull_t;


/* GPIO mode init structure */
typedef struct _gpio_init_t
{
  gpio_mode_t     mode;
  gpio_pull_t     pull;
} gpio_init_t;


/** public data **/

/** public functions **/
void GPIO_SetMode( uint32_t port_num, const gpio_init_t *initdata );
void GPIO_SetData( uint32_t port_num );
void GPIO_ClearData( uint32_t port_num );
uint8_t GPIO_ReadData( uint32_t port_num );


#endif  /* __GPIO_H */
