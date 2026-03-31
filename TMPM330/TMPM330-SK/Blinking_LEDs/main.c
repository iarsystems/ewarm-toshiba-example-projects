/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded Workbench for ARM
 *    to develop code for Toshiba TMPM330 family microcontrollers. It is developed for
 *    Toshiba TMPM330 Eval Board.
 *
 *    It uses the WDT to toggle the port G.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *
 *    $Revision: 4208 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm330fxfg.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  WDMOD = 0xA0;

  //WDCR = 0xB1;
  //Port Function
  PGFR1_bit.PG0F1 = 0;
  PGFR1_bit.PG1F1 = 0;
  PGFR1_bit.PG2F1 = 0;
  PGFR1_bit.PG3F1 = 0;

  //Disable input
  PGIE_bit.PG0IE = 0;
  PGIE_bit.PG1IE = 0;
  PGIE_bit.PG2IE = 0;
  PGIE_bit.PG3IE = 0;

  //Enable Output
  PGCR_bit.PG0C = 1;
  PGCR_bit.PG1C = 1;
  PGCR_bit.PG2C = 1;
  PGCR_bit.PG3C = 1;

  while(1)
  {
  }
}

void NMI_ISR(void)
{
  PGDATA++;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"
/* TMPM330 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
