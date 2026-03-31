/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : drv_ioexp.c
 *    Description : Toshiba M374-STK IO Expander drv
 *
 *    History :
 *    1. Date        : 09.2011
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    $Revision: 41 $
 **************************************************************************/
/** include files **/
#include <Toshiba\iotmpm374fwug.h>
#include "drv_cg.h"
#include "drv_ioexp.h"
/** local definitions **/
#define BAUD_RATE 10000000  /*Boud Rate 10MHz*/
/** default settings **/

/** external functions **/

/** external data **/

/** internal functions **/

/** public data **/

/** private data **/
static uint8_t ioexp_data;
/** public functions **/
/*************************************************************************
 * Function Name: IOExp_Init
 * Parameters: none
 *             
 * Return: void
 *
 * Description: IO Expander initialization
 *
 *
 *************************************************************************/
int IOExp_Init(void)
{
uint32_t clock;
uint32_t flclkset = 0;
  /*Enable SIO1*/
  SC1EN_bit.SIOE = 1;
  
  SC1CR = (0<<1) |    /*Data transmit/receive at rising edges of SCLK0*/
          (0<<0);     /*baud rate generator selected*/
  
  SC1MOD0 = (0<<2);   /*I/O interface mode*/
  SC1MOD1 = (2<<5) |  /*Half duplex(TX)*/
            (0<<1);   /*interval time of continuous transmission None*/
  SC1MOD2 = (1<<3) |  /*MSB first*/
            (0<<2);   /*W-buffer Disabled*/  
            
  SC1FCNF = (0<<0);   /*FIFO Disabled*/

  /*Set boud rate*/
  clock = CG_GetClock(CLK_TO);
  for(uint8_t sel_inclk = 0;  3 >= sel_inclk ; sel_inclk++)
  {
    for(uint8_t div_clk = 1;   16 >= div_clk ; div_clk++)
    {
      if((BAUD_RATE >= ((clock>>(2*sel_inclk+2))/div_clk)) && !flclkset)
      {
        SC1BRCR =  (sel_inclk<<4) |(div_clk & 0xF);
        flclkset = 1;
      }
    }
  }
  
  if(!flclkset)
  {/*error*/
    return -1;
  }
  
  /*IO Set*/
  PAFR2 &= ~((1<<5) |   /*disable TB6OUT function PA5*/
            (1<<4));    /*disable CTS function PA4*/
  PAFR1 |= (1<<5) |     /*enable MOSI function PA5*/
           (1<<4);      /*enable SCLK function PA4*/
          
  PACR |=  (1<<5) |     /*enable PA5 output*/
           (1<<4);      /*enable PA4 output*/
  
  PFFR1 &= ~(1<<0);     /*disable TB7IN function PF0*/
  PFCR |= (1<<0);       /*enable PF0 output*/    
  PFDATA |= (1<<0);     /*set PF0*/    
  /*Enable Transmition*/
  SC1MOD1 |= (1<<4);
  /*Clear All*/
  IOExp_Update(0);
  /*set ioexp data*/
  ioexp_data = 0;
  
  return 0;
}
/*************************************************************************
 * Function Name: IOExp_Update
 * Parameters: uint8_t
 *             
 * Return: void
 *
 * Description: Updates IO Expander data
 *
 *************************************************************************/
void IOExp_Update(uint8_t data)
{
  /*Clear PF0*/
  PFDATA &= ~(1<<0);    
  /*Send data*/
  SC1BUF = ioexp_data = data;
  /*wait until data is sent*/
  while( SC1MOD2_bit.TXRUN || !SC1MOD2_bit.TBEMP);
  /*Update data*/
  PFDATA |= (1<<0);      
}

/*************************************************************************
 * Function Name: IOExp_Get
 * Parameters: void
 *             
 * Return: uint8_t
 *
 * Description: return current IO Expander data
 *
 *************************************************************************/
uint8_t IOExp_Get()
{
  /*return ioexp_data*/
  return ioexp_data;
}

/** private functions **/
