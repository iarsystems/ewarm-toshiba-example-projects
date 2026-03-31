/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : low_level_init.c
 *    Description : low level system initialization. 
 *
 *    $Revision: 41 $
 **************************************************************************/

/** include files **/
#include <stdint.h>
#include "Toshiba\iotmpm350fdtfg.h"
/** external data **/
extern uint16_t RAM_START[];
extern uint16_t RAM_END[];
extern uint16_t SRRAM_START[];
extern uint16_t SRRAM_END[];

/** public functions **/
#pragma section="app_img"
/*************************************************************************
 * Function Name: __low_level_init
 * Parameters: void
 * Return: 0 - do not init data section
 *         1 - init data section
 * Description: Low level system init ( WDT Disable
 *              and Ram init with zero for correct ECC)
 *
 *************************************************************************/
int __low_level_init (void)
{
register uint16_t * dest;

  /*Disable WDT*/
  WDTCTL = 1;
  WDTCMD = 0x5354;

 /*Ram Init*/
  dest = RAM_START;
 
  for(/*empty*/; dest < RAM_END; dest++)
  {
    *dest = 0 ;
  }

#if defined(RAM_DEBUG)
 dest = __section_end("app_img");
#else
 dest = SRRAM_START;
#endif
  for(/*empty*/; dest < SRRAM_END; dest++)
  {
    *dest = 0 ;
  }

  return 1;
}


/** private functions **/
