/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2009
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded Workbench for ARM
 *    to develop code for Toshiba TMPM370 family microcontrollers. It is developed for
 *    IAR TMPM370-SK Eval Board.
 *
 *    It uses the WDT to toggle the port C.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 18.09.2008
 *       Author      : Stanimir Bonev
 *       Description : Adapted for TMPM370-SK
 *
 *  Jumpers:
 *   JP19 - filled
 *   JP20 - filled
 *   JP21 - filled
 *  non isolated JTAG
 *   JP24 - Filled
 *  isolated JTAG
 *   JP24 - no filled
 *   JP14 - filled
 *   JP15 - filled
 *   JP16 - filled
 *
 *
 *    $Revision: 4200 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm370fxfg.h>

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
  PCCR_bit.PC0C = 1;
  PCCR_bit.PC2C = 1;
  PCCR_bit.PC4C = 1;

  while(1)
  {
  }
}

void NMI_ISR(void)
{
static unsigned char i;
  PCDATA_bit.PC0 = 0 != (i & 1);
  PCDATA_bit.PC2 = 0 != (i & 2);
  PCDATA_bit.PC4 = 0 != (i & 4);
  ++i;
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
