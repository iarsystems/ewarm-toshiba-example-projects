/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2010
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the 
 *    IAR Embedded Workbench for ARM to develop code for Toshiba TMPM341 
 *    family microcontrollers. 
 *     It is developed for IAR-TMPM341-SK Board.
 *     For properly operation of SWO printf set CPU clock frequency to 
 *    10MHz (internal OSC)
 *
 *    It uses the WDT to toggle the port PE2 (LED2).
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 19.07.2010
 *       Author      : Santosh Pawar
 *       Description : Adapted for IAR-TMPM341-SK
 *
 *
 *    $Revision: 12822 $
 **************************************************************************/

/** include files **/
#include <stdio.h>
#include <Toshiba\iotmpm341fdxbg.h>

#pragma section=".intvec"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
  VTOR  = (unsigned int)__segment_begin(".intvec");

  //Port Function
  PEFR3_bit.PE2F3 = 0;

  //Disable input
  PEIE_bit.PE2IE = 0;

  //Enable Output
  PECR_bit.PE2C = 1;

  WDMOD = 0xA0;
  WDCR  = 0x4E;

  while(1)
  {
	;
  }
}

void NMI_ISR(void)
{
static unsigned char i;
  PEDATA_bit.PE2 = 0 != (i & 1);
  printf("LED toggle (Cnt:%d)\n", i);
  ++i;
}

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

#pragma language=extended
#pragma segment="CSTACK"

void __iar_program_start( void );

#pragma location = ".intvec"	/* Need aligned to 128 Bytes */
/* TMPM341 Vector Table entries */
const intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
  __iar_program_start,
  NMI_ISR,
};
