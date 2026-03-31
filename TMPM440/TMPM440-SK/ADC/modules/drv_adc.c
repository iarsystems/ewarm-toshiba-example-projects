/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : drv_adc.c
 *    Description : Toshiba TMPM440 ADC Control interface
 *
 *    History :
 *    1. Date        : 7.2013
 *       Author      : Santosh Pawar
 *       Description : initial revision
 *
 **************************************************************************/
/** include files **/
#include <stdint.h>
#include <intrinsics.h>
#include <Toshiba\iotmpm440FxXBG.h>
#include <assert.h>
#include "drv_adc.h"
#include "drv_cg.h"

/** local definitions **/

/** default settings **/

/** external functions **/

/** external data **/

/** internal functions **/
/*************************************************************************
 * Function Name:   ADCA_Init
 * Parameters:      initdata - setup data
 * Return:          none
 *
 * Description:     Setup ADC-A with specified data
 *
 *************************************************************************/
static void ADCA_Init( const adc_init_t *initdata )
{
  volatile int dmycnt;
  fclk_ena_adc( FCLK_ADC(0) );

  /* ADC software reset */
  ADAMOD6_bit.ADRST = 2;
  ADAMOD6_bit.ADRST = 1;
  for (dmycnt=0; dmycnt<1000; dmycnt++);  /* min 3us delay */

  ADACLK_bit.ADCLK = initdata->adclk;     /*ADCLOCK*/
  ADACLK_bit.ADSH = initdata->holdtime;   /*sample hold time*/
  ADAMOD1_bit.DACON = 1;    /*Enable Vref*/
  ADAMOD3_bit.SCAN = 0;     /*Fixed channel mode*/
  ADAMOD3_bit.REPEAT = 0;   /*Single conversion mode*/
}

/*************************************************************************
 * Function Name:   ADCB_Init
 * Parameters:      initdata - setup data
 * Return:          none
 *
 * Description:     Setup ADC-B with specified data
 *
 *************************************************************************/
static void ADCB_Init( const adc_init_t *initdata )
{
  volatile int dmycnt;
  fclk_ena_adc( FCLK_ADC(1) );

  /* ADC software reset */
  ADBMOD6_bit.ADRST = 2;
  ADBMOD6_bit.ADRST = 1;
  for (dmycnt=0; dmycnt<1000; dmycnt++);  /* min 3us delay */

  ADBCLK_bit.ADCLK = initdata->adclk;     /*ADCLOCK*/
  ADBCLK_bit.ADSH = initdata->holdtime;   /*sample hold time*/
  ADBMOD1_bit.DACON = 1;    /*Enable Vref*/
  ADBMOD3_bit.SCAN = 0;     /*Fixed channel mode*/
  ADBMOD3_bit.REPEAT = 0;   /*Single conversion mode*/
}

/*************************************************************************
 * Function Name:   ADCC_Init
 * Parameters:      initdata - setup data
 * Return:          none
 *
 * Description:     Setup ADC-C with specified data
 *
 *************************************************************************/
static void ADCC_Init( const adc_init_t *initdata )
{
  volatile int dmycnt;
  fclk_ena_adc( FCLK_ADC(2) );

  /* ADC software reset */
  ADCMOD6_bit.ADRST = 2;
  ADCMOD6_bit.ADRST = 1;
  for (dmycnt=0; dmycnt<1000; dmycnt++);  /* min 3us delay */

  ADCCLK_bit.ADCLK = initdata->adclk;     /*ADCLOCK*/
  ADCCLK_bit.ADSH = initdata->holdtime;   /*sample hold time*/
  ADCMOD1_bit.DACON = 1;    /*Enable Vref*/
  ADCMOD3_bit.SCAN = 0;     /*Fixed channel mode*/
  ADCMOD3_bit.REPEAT = 0;   /*Single conversion mode*/
}

/*************************************************************************
 * Function Name:   ADCA_Start
 * Parameters:      ch_num - ADC-A i/p channel number
 * Return:          none
 *
 * Description:     Start data conversion cycle for specified ADC-A channel
 *
 *************************************************************************/
static void ADCA_Start( uint32_t ch_num )
{
  ADAMOD2_bit.ADCH = ch_num;    /*Select Channel*/
  ADAMOD2_bit.HPADCH = ch_num;

  /*Start Conversion*/
  ADAMOD0_bit.ADS = 1;

}

/*************************************************************************
 * Function Name:   ADCB_Start
 * Parameters:      ch_num - ADC-B i/p channel number
 * Return:          none
 *
 * Description:     Start data conversion cycle for specified ADC-B channel
 *
 *************************************************************************/
static void ADCB_Start( uint32_t ch_num )
{
  ADBMOD2_bit.ADCH = ch_num;    /*Select Channel*/
  ADBMOD2_bit.HPADCH = ch_num;

  /*Start Conversion*/
  ADBMOD0_bit.ADS = 1;
}

/*************************************************************************
 * Function Name:   ADCC_Start
 * Parameters:      ch_num - ADC-C i/p channel number
 * Return:          none
 *
 * Description:     Start data conversion cycle for specified ADC-C channel
 *
 *************************************************************************/
static void ADCC_Start( uint32_t ch_num )
{
  ADCMOD2_bit.ADCH = ch_num;    /*Select Channel*/
  ADCMOD2_bit.HPADCH = ch_num;

  /*Start Conversion*/
  ADCMOD0_bit.ADS = 1;
}


/*************************************************************************
 * Function Name:   ADCA_Read
 * Parameters:      ch_num - ADC-A channel number
 * Return:          none
 *
 * Description:     Read converted data from specified ADC-A channel
 *
 *************************************************************************/
static uint32_t ADCA_Read( uint32_t ch_num )
{
  volatile uint32_t dmydat;
  volatile int dmycnt;

  /* clear status */
  dmydat = *((volatile uint32_t *)&ADAREG00 + ch_num);
  ADCA_Start(ch_num);	/* Start conversion */

  do {
	  for (dmycnt=0; dmycnt<50; dmycnt++);  /* small delay */
	  dmydat = *((volatile uint32_t *)&ADAREG00 + ch_num);
  } while (!(dmydat & (1UL<<12)));	/* while ADRF==0 */
  return dmydat&0xFFF;
}

/*************************************************************************
 * Function Name:   ADCB_Read
 * Parameters:      ch_num - ADC-B channel number
 * Return:          none
 *
 * Description:     Read converted data from specified ADC-B channel
 *
 *************************************************************************/
static uint32_t ADCB_Read( uint32_t ch_num )
{
  volatile uint32_t dmydat;
  volatile int dmycnt;

  /* clear status */
  dmydat = *((volatile uint32_t *)&ADBREG00 + ch_num);
  ADCB_Start(ch_num);	/* Start conversion */

  do {
	  for (dmycnt=0; dmycnt<50; dmycnt++);  /* small delay */
	  dmydat = *((volatile uint32_t *)&ADBREG00 + ch_num);
  } while (!(dmydat & (1UL<<12)));	/* while ADRF==0 */
  return dmydat&0xFFF;
}

/*************************************************************************
 * Function Name:   ADCC_Read
 * Parameters:      ch_num - ADC-C channel number
 * Return:          none
 *
 * Description:     Read converted data from specified ADC-C channel
 *
 *************************************************************************/
static uint32_t ADCC_Read( uint32_t ch_num )
{
  volatile uint32_t dmydat;
  volatile int dmycnt;

  /* clear status */
  dmydat = *((volatile uint32_t *)&ADCREG00 + ch_num);
  ADCC_Start(ch_num);	/* Start conversion */

  do {
	  for (dmycnt=0; dmycnt<50; dmycnt++);  /* small delay */
	  dmydat = *((volatile uint32_t *)&ADCREG00 + ch_num);
  } while (!(dmydat & (1UL<<12)));	/* while ADRF==0 */
  return dmydat&0xFFF;
}

/** public data **/

/** private data **/

/** public functions **/
/*************************************************************************
 * Function Name:   ADC_Init
 * Parameters:      port_num - channel number, initdata - setup data
 * Return:          none
 *
 * Description:     Setup ADC with specified data
 *
 *************************************************************************/
void ADC_Init( uint32_t port_num, const adc_init_t *initdata )
{
  if (CH_ADCA == port_num) {
    ADCA_Init( initdata );
  }
  else if (CH_ADCB == port_num) {
    ADCB_Init( initdata );
  }
  else if (CH_ADCC == port_num) {
    ADCC_Init( initdata );
  }
}

/*************************************************************************
 * Function Name:   ADC_Read
 * Parameters:      ch_num - ADC i/p channel number
 * Return:          ADC data
 *
 * Description:     Read converted data from specified ADC channel
 *
 *************************************************************************/
uint32_t ADC_Read( uint32_t ch_num )
{
  if (CH_ADCA == (ch_num>>4)) {
    return ADCA_Read( ch_num&0xF );
  }
  else if (CH_ADCB == (ch_num>>4)) {
    return ADCB_Read( ch_num&0xF );
  }
  else if (CH_ADCC == (ch_num>>4)) {
    return ADCC_Read( ch_num&0xF );
  }
  return 0;
}

/*************************************************************************
 * Function Name:   ADC_Start
 * Parameters:      ch_num - ADC i/p channel number
 * Return:          none
 *
 * Description:     Start data conversion cycle for specified ADC channel
 *
 *************************************************************************/
void ADC_Start( uint32_t ch_num )
{
  if (CH_ADCA == (ch_num>>4)) {
    ADCA_Start( ch_num&0xF );
  }
  else if (CH_ADCB == (ch_num>>4)) {
    ADCB_Start( ch_num&0xF );
  }
  else if (CH_ADCC == (ch_num>>4)) {
    ADCC_Start( ch_num&0xF );
  }
}

/** private functions **/
