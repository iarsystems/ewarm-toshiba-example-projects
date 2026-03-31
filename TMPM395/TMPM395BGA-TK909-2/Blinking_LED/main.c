/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2010
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded Workbench
 *    for ARM to develop code for Toshiba TMPM395 family microcontrollers. It is
 *    developed for Toshiba TMPM395BGA-TK909-2 Eval Board.
 *
 *    It uses the WDT to toggle the port PJ0.
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 21.01.2010
 *       Author      : Stanimir Bonev
 *       Description : Adapted for TMPM395BGA-TK909-2
 *
 *  Jumpers:
 *    JP31 - Filled
 *    Connect J24.2 (PJ0) to J14.1
 *
 *  Note: Please set correct SWO CPU clock (9MHz) in J-Link->SWO Settings...
 *  for correct operation of SWO features
 *
 *
 *    $Revision: 4200 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <Toshiba\iotmpm395fwbxbg.h>

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
  WDCR  = 0xB1;

  //Port Function
  PJFR1_bit.PJ0F1 = 0;

  //Disable input
  PJIE_bit.PJ0IE = 0;

  //Enable Output
  PJCR_bit.PJ0C = 1;

  while(1)
  {
  }
}

void NMI_ISR(void)
{
static unsigned char i;
  PJDATA_bit.PJ0 = 0 != (i & 1);
  ++i;
  printf("LED toggle\n");
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
