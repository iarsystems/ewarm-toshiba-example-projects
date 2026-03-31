/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2009
 *
 *    File name   : main.c
 *    Description : This example project shows how to use the IAR Embedded Workbench for ARM
 *    to develop code for Toshiba TMPM362 family microcontrollers. It is developed for
 *    Toshiba TMPM360-TK906-1 Board.
 *
 *    It uses the WDT to toggle the port C.
 *
 *    Connect PC0, PC1 and PC2 to some of LEDs ports
 *
 *    History :
 *    1. Date        : 08.2008
 *       Author      : Stoyan Choynev
 *       Description : Initial Revision
 *    2. Date        : 18.03.2010
 *       Author      : Stanimir Bonev
 *       Description : Adapted for TMPM362-SK
 *
 *  Jumpers:
 *
 *    $Revision: 4208 $
 **************************************************************************/

/** include files **/
#include <Toshiba\iotmpm362f10fg.h>

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
  PCFR1_bit.PC0F1 = 0;
  PCFR1_bit.PC1F1 = 0;
  PCFR1_bit.PC2F1 = 0;

  //Disable input
  PCIE_bit.PC0IE = 0;
  PCIE_bit.PC1IE = 0;
  PCIE_bit.PC2IE = 0;

  //Enable Output
  PCCR_bit.PC0C = 1;
  PCCR_bit.PC1C = 1;
  PCCR_bit.PC2C = 1;

  while(1)
  {
  }
}

void NMI_ISR(void)
{
static unsigned char i;
  PCDATA_bit.PC0 = 0 != (i & 1);
  PCDATA_bit.PC1 = 0 != (i & 2);
  PCDATA_bit.PC2 = 0 != (i & 4);
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
