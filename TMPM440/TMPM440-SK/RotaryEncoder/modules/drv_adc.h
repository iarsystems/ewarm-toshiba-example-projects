/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : drv_adc.h
 *    Description : Toshiba TMPM440 ADC Control
 *
 *    History :
 *    1. Date        : 7.2013
 *       Author      : Santosh Pawar
 *       Description : initial revision
 *
 **************************************************************************/
#ifndef __ADC_H
#define __ADC_H
/** include files **/
#include <stdint.h>
/** definitions **/

#define CH_ADCA     0
#define CH_ADCB     1
#define CH_ADCC     2

#define CH_AINA(x)    ((CH_ADCA<<4) + ((x)&0xF))
#define CH_AINB(x)    ((CH_ADCB<<4) + ((x)&0xF))
#define CH_AINC(x)    ((CH_ADCC<<4) + ((x)&0xF))


/*ADC clk divider typedef */
typedef enum _adc_gear_t
{
  ADC_FC_2 = 1,   /* fc/2 */
  ADC_FC_4,       /* fc/4 */
  ADC_FC_8,       /* fc/8 */
  ADC_FC_16,      /* fc/16 */
} adc_gear_t;

/*ADC sample hold time typedef */
typedef enum _adc_holdtm_t
{
  ADC_HOLDTM_10 = 0,    /* ADCLK = 10 */
  ADC_HOLDTM_20,      /* ADCLK = 20 */
  ADC_HOLDTM_30,      /* ADCLK = 30 */
  ADC_HOLDTM_40,      /* ADCLK = 40 */
  ADC_HOLDTM_80,      /* ADCLK = 80 */
  ADC_HOLDTM_160,     /* ADCLK = 160 */
  ADC_HOLDTM_320,     /* ADCLK = 320 */
} adc_holdtm_t;


/* ADC init structure */
typedef struct _adc_init_t
{
  adc_holdtm_t    holdtime;
  adc_gear_t      adclk;
} adc_init_t;


/** public data **/

/** public functions **/
void ADC_Init( uint32_t port_num, const adc_init_t *initdata );
uint32_t ADC_Read( uint32_t ch_num );
void ADC_Start( uint32_t ch_num );


#endif  /* __ADC_H */
