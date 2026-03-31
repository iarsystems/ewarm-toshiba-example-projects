/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : drv_adc.c
 *    Description : Toshiba TMPM440 GPIO Control interface
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
#include "drv_gpio.h"

/** local definitions **/

/** default settings **/

/** external functions **/

/** external data **/

/** internal functions **/


/** public data **/

/** private data **/

/** public functions **/
/*************************************************************************
 * Function Name:   GPIO_SetMode
 * Parameters:      port_num - port pin number, initdata - setup data
 * Return:          none
 *
 * Description:     Setup port pin interface with specified mode dat
 *
 *************************************************************************/
void GPIO_SetMode( uint32_t port_num, const gpio_init_t *initdata )
{
  uint8_t pin = (uint8_t)(port_num&0xF);

  switch (port_num>>4) {
  case CH_PORTA:    /*******************************/
    if (initdata->pull == PIN_PUP) { PAPUP |= (1U<<pin); }
    else  { PAPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PACR &= ~(1U<<pin);
      PAFR1 &= ~(1U<<pin);
      PAFR3 &= ~(1U<<pin);
      PAIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PAIE &= ~(1U<<pin);
      PAFR1 &= ~(1U<<pin);
      PAFR3 &= ~(1U<<pin);
      PACR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PACR &= ~(1U<<pin);
      PAIE &= ~(1U<<pin);
      PAFR3 &= ~(1U<<pin);
      PAFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PACR &= ~(1U<<pin);
      PAIE &= ~(1U<<pin);
      PAFR1 &= ~(1U<<pin);
      PAFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTB:    /*******************************/
    if (initdata->pull == PIN_PUP) { PBPUP |= (1U<<pin); }
    else  { PBPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PBCR &= ~(1U<<pin);
      PBFR1 &= ~(1U<<pin);
      PBFR3 &= ~(1U<<pin);
      PBIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PBIE &= ~(1U<<pin);
      PBFR1 &= ~(1U<<pin);
      PBFR3 &= ~(1U<<pin);
      PBCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PBCR &= ~(1U<<pin);
      PBIE &= ~(1U<<pin);
      PBFR3 &= ~(1U<<pin);
      PBFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PBCR &= ~(1U<<pin);
      PBIE &= ~(1U<<pin);
      PBFR1 &= ~(1U<<pin);
      PBFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTC:    /*******************************/
    if (initdata->pull == PIN_PUP) { PCPUP |= (1U<<pin); }
    else  { PCPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PCCR &= ~(1U<<pin);
      PCFR1 &= ~(1U<<pin);
      PCFR2 &= ~(1U<<pin);
      PCFR3 &= ~(1U<<pin);
      PCIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PCIE &= ~(1U<<pin);
      PCFR1 &= ~(1U<<pin);
      PCFR2 &= ~(1U<<pin);
      PCFR3 &= ~(1U<<pin);
      PCCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PCCR &= ~(1U<<pin);
      PCIE &= ~(1U<<pin);
      PCFR2 &= ~(1U<<pin);
      PCFR3 &= ~(1U<<pin);
      PCFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PCCR &= ~(1U<<pin);
      PCIE &= ~(1U<<pin);
      PCFR1 &= ~(1U<<pin);
      PCFR3 &= ~(1U<<pin);
      PCFR2 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PCCR &= ~(1U<<pin);
      PCIE |= (1U<<pin);   // Set INT as input
      PCFR1 &= ~(1U<<pin);
      PCFR2 &= ~(1U<<pin);
      PCFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTD:    /*******************************/
    if (initdata->pull == PIN_PUP) { PDPUP |= (1U<<pin); }
    else  { PDPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PDCR &= ~(1U<<pin);
      PDFR1 &= ~(1U<<pin);
      PDFR2 &= ~(1U<<pin);
      PDIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PDIE &= ~(1U<<pin);
      PDFR1 &= ~(1U<<pin);
      PDFR2 &= ~(1U<<pin);
      PDCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PDCR &= ~(1U<<pin);
      PDIE &= ~(1U<<pin);
      PDFR2 &= ~(1U<<pin);
      PDFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PDCR &= ~(1U<<pin);
      PDIE &= ~(1U<<pin);
      PDFR1 &= ~(1U<<pin);
      PDFR2 |= (1U<<pin);
    }
    break;

  case CH_PORTE:    /*******************************/
    if (initdata->pull == PIN_PUP) {
      if ((pin>=4)&&(pin<=6))   PEOD &= ~(1U<<(pin-1));
      else if (pin<=2)          PEOD &= ~(1U<<pin);
      PEPUP |= (1U<<pin);
    }
    else if (initdata->pull == PIN_OD) {
      PEPUP &= ~(1U<<pin);
      if ((pin>=4)&&(pin<=6))   PEOD |= (1U<<(pin-1));
      else if (pin<=2)          PEOD |= (1U<<pin);
    }
    else  {
      PEPUP &= ~(1U<<pin);
      if ((pin>=4)&&(pin<=6))   PEOD &= ~(1U<<(pin-1));
      else if (pin<=2)          PEOD &= ~(1U<<pin);
    }
    if (initdata->mode == PMODE_INPUT) {
      PECR &= ~(1U<<pin);
      PEFR1 &= ~(1U<<pin);
      PEFR2 &= ~(1U<<pin);
      PEFR3 &= ~(1U<<pin);
      PEIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PEIE &= ~(1U<<pin);
      PEFR1 &= ~(1U<<pin);
      PEFR2 &= ~(1U<<pin);
      PEFR3 &= ~(1U<<pin);
      PECR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PECR &= ~(1U<<pin);
      PEIE &= ~(1U<<pin);
      PEFR2 &= ~(1U<<pin);
      PEFR3 &= ~(1U<<pin);
      PEFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PECR &= ~(1U<<pin);
      PEIE &= ~(1U<<pin);
      PEFR1 &= ~(1U<<pin);
      PEFR3 &= ~(1U<<pin);
      PEFR2 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PECR &= ~(1U<<pin);
      PEIE &= ~(1U<<pin);
      PEFR1 &= ~(1U<<pin);
      PEFR2 &= ~(1U<<pin);
      PEFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTF:    /*******************************/
    if (initdata->pull == PIN_PUP) { PFPUP |= (1U<<pin); }
    else  { PFPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PFCR &= ~(1U<<pin);
      PFFR1 &= ~(1U<<pin);
      PFFR2 &= ~(1U<<pin);
      PFFR3 &= ~(1U<<pin);
      PFIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PFIE &= ~(1U<<pin);
      PFFR1 &= ~(1U<<pin);
      PFFR2 &= ~(1U<<pin);
      PFFR3 &= ~(1U<<pin);
      PFCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PFCR &= ~(1U<<pin);
      PFIE &= ~(1U<<pin);
      PFFR2 &= ~(1U<<pin);
      PFFR3 &= ~(1U<<pin);
      PFFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PFCR &= ~(1U<<pin);
      PFIE &= ~(1U<<pin);
      PFFR1 &= ~(1U<<pin);
      PFFR3 &= ~(1U<<pin);
      PFFR2 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PFCR &= ~(1U<<pin);
      PFIE &= ~(1U<<pin);
      PFFR1 &= ~(1U<<pin);
      PFFR2 &= ~(1U<<pin);
      PFFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTG:    /*******************************/
    if (initdata->pull == PIN_PUP) {
      PGPDN &= ~(1U<<pin);
      PGPUP |= (1U<<pin);
    }
    else if (initdata->pull == PIN_PDOWN) {
      PGPUP &= ~(1U<<pin);
      PGPDN |= (1U<<pin);
    }
    else  {
      PGPUP &= ~(1U<<pin);
      PGPDN &= ~(1U<<pin);
    }
    if (initdata->mode == PMODE_INPUT) {
      PGCR &= ~(1U<<pin);
      PGFR1 &= ~(1U<<pin);
      PGIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PGIE &= ~(1U<<pin);
      PGFR1 &= ~(1U<<pin);
      PGCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PGCR &= ~(1U<<pin);
      PGIE &= ~(1U<<pin);
      PGFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTH:    /*******************************/
    if (initdata->pull == PIN_PUP) {
      if ((pin==4)||(pin==5))   PHOD1 &= ~(4U<<pin);
      else if (pin==6)          PHOD2 &= ~(1U<<pin);
      PHPUP |= (1U<<pin);
    }
    else if (initdata->pull == PIN_OD) {
      PHPUP &= ~(1U<<pin);
      if ((pin==4)||(pin==5))   PHOD1 |= (4U<<pin);
      else if (pin==6)          PHOD2 |= (1U<<pin);
    }
    else  {
      PHPUP &= ~(1U<<pin);
      if ((pin==4)||(pin==5))   PHOD1 &= ~(4U<<pin);
      else if (pin==6)          PHOD2 &= ~(1U<<pin);
    }
    if (initdata->mode == PMODE_INPUT) {
      PHCR &= ~(1U<<pin);
      PHFR1 &= ~(1U<<pin);
      PHFR2 &= ~(1U<<pin);
      PHIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PHIE &= ~(1U<<pin);
      PHFR1 &= ~(1U<<pin);
      PHFR2 &= ~(1U<<pin);
      PHCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PHCR &= ~(1U<<pin);
      PHIE &= ~(1U<<pin);
      PHFR2 &= ~(1U<<pin);
      PHFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PHCR &= ~(1U<<pin);
      PHIE &= ~(1U<<pin);
      PHFR1 &= ~(1U<<pin);
      PHFR2 |= (1U<<pin);
    }
    break;

  case CH_PORTJ:    /*******************************/
    if (initdata->pull == PIN_PUP) { PJPUP |= (1U<<pin); }
    else  { PJPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PJCR &= ~(1U<<pin);
      PJFR1 &= ~(1U<<pin);
      PJIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PJIE &= ~(1U<<pin);
      PJFR1 &= ~(1U<<pin);
      PJCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PJCR &= ~(1U<<pin);
      PJIE &= ~(1U<<pin);
      PJFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTK:    /*******************************/
    if (initdata->pull == PIN_PUP) {
      if ((pin>=4)&&(pin<=7))   PKOD &= ~(1U<<(pin-4));
      PKPUP |= (1U<<pin);
    }
    else if (initdata->pull == PIN_OD) {
      PKPUP &= ~(1U<<pin);
      if ((pin>=4)&&(pin<=7))   PKOD |= (1U<<(pin-4));
    }
    else  {
      PKPUP &= ~(1U<<pin);
      if ((pin>=4)&&(pin<=7))   PKOD &= ~(1U<<(pin-4));
    }
    if (initdata->mode == PMODE_INPUT) {
      PKCR &= ~(1U<<pin);
      PKFR1 &= ~(1U<<pin);
      PKFR2 &= ~(1U<<pin);
      PKFR3 &= ~(1U<<pin);
      PKIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PKIE &= ~(1U<<pin);
      PKFR1 &= ~(1U<<pin);
      PKFR2 &= ~(1U<<pin);
      PKFR3 &= ~(1U<<pin);
      PKCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PKCR &= ~(1U<<pin);
      PKIE &= ~(1U<<pin);
      PKFR2 &= ~(1U<<pin);
      PKFR3 &= ~(1U<<pin);
      PKFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PKCR &= ~(1U<<pin);
      PKIE &= ~(1U<<pin);
      PKFR1 &= ~(1U<<pin);
      PKFR3 &= ~(1U<<pin);
      PKFR2 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PKCR &= ~(1U<<pin);
      if ((pin==3)||(pin==7))   PKIE |= (1U<<pin);
      else    PKIE &= ~(1U<<pin);
      PKFR1 &= ~(1U<<pin);
      PKFR2 &= ~(1U<<pin);
      PKFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTL:    /*******************************/
    if (initdata->pull == PIN_PUP) { PLPUP |= (1U<<pin); }
    else  { PLPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PLCR &= ~(1U<<pin);
      PLFR1 &= ~(1U<<pin);
      PLIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PLIE &= ~(1U<<pin);
      PLFR1 &= ~(1U<<pin);
      PLCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PLCR &= ~(1U<<pin);
      PLIE &= ~(1U<<pin);
      PLFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTM:    /*******************************/
    if (initdata->pull == PIN_PUP) {
      if ((pin>=4)&&(pin<=7))   PMOD &= ~(1U<<(pin-4));
      PMPUP |= (1U<<pin);
    }
    else if (initdata->pull == PIN_OD) {
      PMPUP &= ~(1U<<pin);
      if ((pin>=4)&&(pin<=7))   PMOD |= (1U<<(pin-4));
    }
    else  {
      PMPUP &= ~(1U<<pin);
      if ((pin>=4)&&(pin<=7))   PMOD &= ~(1U<<(pin-4));
    }
    if (initdata->mode == PMODE_INPUT) {
      PMCR &= ~(1U<<pin);
      PMFR1 &= ~(1U<<pin);
      PMFR2 &= ~(1U<<pin);
      PMFR3 &= ~(1U<<pin);
      PMIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PMIE &= ~(1U<<pin);
      PMFR1 &= ~(1U<<pin);
      PMFR2 &= ~(1U<<pin);
      PMFR3 &= ~(1U<<pin);
      PMCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PMCR &= ~(1U<<pin);
      PMIE &= ~(1U<<pin);
      PMFR2 &= ~(1U<<pin);
      PMFR3 &= ~(1U<<pin);
      PMFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PMCR &= ~(1U<<pin);
      PMIE &= ~(1U<<pin);
      PMFR1 &= ~(1U<<pin);
      PMFR3 &= ~(1U<<pin);
      PMFR2 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PMCR &= ~(1U<<pin);
      if ((pin==3)||(pin==7))   PMIE |= (1U<<pin);
      else    PMIE &= ~(1U<<pin);
      PMFR1 &= ~(1U<<pin);
      PMFR2 &= ~(1U<<pin);
      PMFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTN:    /*******************************/
    if (initdata->pull == PIN_PUP) { PNPUP |= (1U<<pin); }
    else  { PNPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PNCR &= ~(1U<<pin);
      PNFR1 &= ~(1U<<pin);
      PNFR3 &= ~(1U<<pin);
      PNIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PNIE &= ~(1U<<pin);
      PNFR1 &= ~(1U<<pin);
      PNFR3 &= ~(1U<<pin);
      PNCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PNCR &= ~(1U<<pin);
      PNIE &= ~(1U<<pin);
      PNFR3 &= ~(1U<<pin);
      PNFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PNCR &= ~(1U<<pin);
      if ((pin==3)||(pin==7))   PNIE |= (1U<<pin);
      else    PNIE &= ~(1U<<pin);
      PNFR1 &= ~(1U<<pin);
      PNFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTP:    /*******************************/
    if (initdata->pull == PIN_PUP) { PPPUP |= (1U<<pin); }
    else  { PPPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PPCR &= ~(1U<<pin);
      PPFR1 &= ~(1U<<pin);
      PPFR2 &= ~(1U<<pin);
      PPFR3 &= ~(1U<<pin);
      PPIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PPIE &= ~(1U<<pin);
      PPFR1 &= ~(1U<<pin);
      PPFR2 &= ~(1U<<pin);
      PPFR3 &= ~(1U<<pin);
      PPCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PPCR &= ~(1U<<pin);
      PPIE &= ~(1U<<pin);
      PPFR2 &= ~(1U<<pin);
      PPFR3 &= ~(1U<<pin);
      PPFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PPCR &= ~(1U<<pin);
      PPIE &= ~(1U<<pin);
      PPFR1 &= ~(1U<<pin);
      PPFR3 &= ~(1U<<pin);
      PPFR2 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PPCR &= ~(1U<<pin);
      if ((pin==2)||(pin==3)||(pin==7))   PPIE |= (1U<<pin);
      else    PPIE &= ~(1U<<pin);
      PPFR1 &= ~(1U<<pin);
      PPFR2 &= ~(1U<<pin);
      PPFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTR:    /*******************************/
    if (initdata->pull == PIN_PUP) {
      PROD &= ~(1U<<pin);
      PRPUP |= (1U<<pin);
    }
    else if (initdata->pull == PIN_OD) {
      PRPUP &= ~(1U<<pin);
      PROD |= (1U<<pin);
    }
    else  {
      PRPUP &= ~(1U<<pin);
      PROD &= ~(1U<<pin);
    }
    if (initdata->mode == PMODE_INPUT) {
      PRCR &= ~(1U<<pin);
      PRFR1 &= ~(1U<<pin);
      PRFR2 &= ~(1U<<pin);
      PRFR3 &= ~(1U<<pin);
      PRIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PRIE &= ~(1U<<pin);
      PRFR1 &= ~(1U<<pin);
      PRFR2 &= ~(1U<<pin);
      PRFR3 &= ~(1U<<pin);
      PRCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PRCR &= ~(1U<<pin);
      PRIE &= ~(1U<<pin);
      PRFR2 &= ~(1U<<pin);
      PRFR3 &= ~(1U<<pin);
      PRFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PRCR &= ~(1U<<pin);
      PRIE &= ~(1U<<pin);
      PRFR1 &= ~(1U<<pin);
      PRFR3 &= ~(1U<<pin);
      PRFR2 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR3) {
      PRCR &= ~(1U<<pin);
      if ((pin==2)||(pin==3)||(pin==6)||(pin==7)) PRIE |= (1U<<pin);
      else    PRIE &= ~(1U<<pin);
      PRFR1 &= ~(1U<<pin);
      PRFR2 &= ~(1U<<pin);
      PRFR3 |= (1U<<pin);
    }
    break;

  case CH_PORTT:    /*******************************/
    if (initdata->pull == PIN_PUP) { PTPUP |= (1U<<pin); }
    else  { PTPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PTCR &= ~(1U<<pin);
      PTFR1 &= ~(1U<<pin);
      PTIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PTIE &= ~(1U<<pin);
      PTFR1 &= ~(1U<<pin);
      PTCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PTCR &= ~(1U<<pin);
      PTIE &= ~(1U<<pin);
      PTFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTU:    /*******************************/
    if (initdata->pull == PIN_PUP) { PUPUP |= (1U<<pin); }
    else  { PUPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PUCR &= ~(1U<<pin);
      PUFR1 &= ~(1U<<pin);
      PUIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PUIE &= ~(1U<<pin);
      PUFR1 &= ~(1U<<pin);
      PUCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PUCR &= ~(1U<<pin);
      if (pin>=4)   PUIE |= (1U<<pin);
      else    PUIE &= ~(1U<<pin);
      PUFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTV:    /*******************************/
    if (initdata->pull == PIN_PUP) { PVPUP |= (1U<<pin); }
    else  { PVPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PVCR &= ~(1U<<pin);
      PVFR1 &= ~(1U<<pin);
      PVIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PVIE &= ~(1U<<pin);
      PVFR1 &= ~(1U<<pin);
      PVCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PVCR &= ~(1U<<pin);
      PVIE &= ~(1U<<pin);
      PVFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTW:    /*******************************/
    if (initdata->pull == PIN_PUP) {
      PWOD &= ~(1U<<pin);
      PWPUP |= (1U<<pin);
    }
    else if (initdata->pull == PIN_OD) {
      PWPUP &= ~(1U<<pin);
      PWOD |= (1U<<pin);
    }
    else  {
      PWPUP &= ~(1U<<pin);
      PWOD &= ~(1U<<pin);
    }
    if (initdata->mode == PMODE_INPUT) {
      PWCR &= ~(1U<<pin);
      PWFR1 &= ~(1U<<pin);
      PWIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PWIE &= ~(1U<<pin);
      PWFR1 &= ~(1U<<pin);
      PWCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PWCR &= ~(1U<<pin);
      PWIE &= ~(1U<<pin);
      PWFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTY:    /*******************************/
    if (initdata->pull == PIN_PUP) { PYPUP |= (1U<<pin); }
    else  { PYPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PYCR &= ~(1U<<pin);
      PYFR1 &= ~(1U<<pin);
      PYIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PYIE &= ~(1U<<pin);
      PYFR1 &= ~(1U<<pin);
      PYCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PYCR &= ~(1U<<pin);
      PYIE &= ~(1U<<pin);
      PYFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTAA:   /*******************************/
    if (initdata->pull == PIN_PUP) { PAAPUP |= (1U<<pin); }
    else  { PAAPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PAAIE |= (1U<<pin);
    }
    break;

  case CH_PORTAB:   /*******************************/
    if (initdata->mode == PMODE_INPUT) {
      PABIE |= (1U<<pin);
    }
    break;

  case CH_PORTAC:   /*******************************/
    if (initdata->pull == PIN_PUP) { PACPUP |= (1U<<pin); }
    else  { PACPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PACIE |= (1U<<pin);
    }
    break;

  case CH_PORTAD:   /*******************************/
    if (initdata->pull == PIN_PUP) { PADPUP |= (1U<<pin); }
    else  { PADPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PADCR &= ~(1U<<pin);
      PADFR1 &= ~(1U<<pin);
      PADIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PADIE &= ~(1U<<pin);
      PADFR1 &= ~(1U<<pin);
      PADCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PADCR &= ~(1U<<pin);
      PADIE &= ~(1U<<pin);
      PADFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTAE:   /*******************************/
    if (initdata->pull == PIN_PUP) { PAEPUP |= (1U<<pin); }
    else  { PAEPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PAECR &= ~(1U<<pin);
      PAEFR1 &= ~(1U<<pin);
      PAEIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PAEIE &= ~(1U<<pin);
      PAEFR1 &= ~(1U<<pin);
      PAECR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PAECR &= ~(1U<<pin);
      PAEIE &= ~(1U<<pin);
      PAEFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTAF:   /*******************************/
    if (initdata->pull == PIN_PUP) { PAFPUP |= (1U<<pin); }
    else  { PAFPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PAFCR &= ~(1U<<pin);
      PAFFR1 &= ~(1U<<pin);
      PAFIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PAFIE &= ~(1U<<pin);
      PAFFR1 &= ~(1U<<pin);
      PAFCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PAFCR &= ~(1U<<pin);
      PAFIE &= ~(1U<<pin);
      PAFFR1 |= (1U<<pin);
    }
    break;

  case CH_PORTAG:   /*******************************/
    if (initdata->pull == PIN_PUP) { PAGPUP |= (1U<<pin); }
    else  { PAGPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PAGCR &= ~(1U<<pin);
      PAGFR1 &= ~(1U<<pin);
      PAGFR2 &= ~(1U<<pin);
      PAGIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PAGIE &= ~(1U<<pin);
      PAGFR1 &= ~(1U<<pin);
      PAGFR2 &= ~(1U<<pin);
      PAGCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PAGCR &= ~(1U<<pin);
      PAGIE &= ~(1U<<pin);
      PAGFR2 &= ~(1U<<pin);
      PAGFR1 |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR2) {
      PAGCR &= ~(1U<<pin);
      PAGIE &= ~(1U<<pin);
      PAGFR1 &= ~(1U<<pin);
      PAGFR2 |= (1U<<pin);
    }
    break;

  case CH_PORTAH:   /*******************************/
    if (initdata->pull == PIN_PUP) { PAHPUP |= (1U<<pin); }
    else  { PAHPUP &= ~(1U<<pin); }
    if (initdata->mode == PMODE_INPUT) {
      PAHCR &= ~(1U<<pin);
      PAHIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PAHIE &= ~(1U<<pin);
      PAHCR |= (1U<<pin);
    }
    break;

  case CH_PORTAJ:   /*******************************/
    if (initdata->pull == PIN_PUP) {
      PAJOD &= ~(1U<<pin);
      PAJPUP |= (1U<<pin);
    }
    else if (initdata->pull == PIN_OD) {
      PAJPUP &= ~(1U<<pin);
      PAJOD |= (1U<<pin);
    }
    else  {
      PAJPUP &= ~(1U<<pin);
      PAJOD &= ~(1U<<pin);
    }
    if (initdata->mode == PMODE_INPUT) {
      PAJCR &= ~(1U<<pin);
      PAJFR1 &= ~(1U<<pin);
      PAJIE |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_OUTPUT) {
      PAJIE &= ~(1U<<pin);
      PAJFR1 &= ~(1U<<pin);
      PAJCR |= (1U<<pin);
    }
    else if (initdata->mode == PMODE_FR1) {
      PAJCR &= ~(1U<<pin);
      PAJIE &= ~(1U<<pin);
      PAJFR1 |= (1U<<pin);
    }
    break;

  default:
    break;
  }

}

/*************************************************************************
 * Function Name:   GPIO_SetData
 * Parameters:      port_num - port pin number
 * Return:          none
 *
 * Description:     Set 1 to specified GPIO output pin
 *
 *************************************************************************/
void GPIO_SetData( uint32_t port_num )
{
  uint8_t pin = (uint8_t)(port_num&0xF);

  switch (port_num>>4) {
  case CH_PORTA:    /*******************************/
    PADATA |= (1U<<pin);
    break;

  case CH_PORTB:    /*******************************/
    PBDATA |= (1U<<pin);
    break;

  case CH_PORTC:    /*******************************/
    PCDATA |= (1U<<pin);
    break;

  case CH_PORTD:    /*******************************/
    PDDATA |= (1U<<pin);
    break;

  case CH_PORTE:    /*******************************/
    PEDATA |= (1U<<pin);
    break;

  case CH_PORTF:    /*******************************/
    PFDATA |= (1U<<pin);
    break;

  case CH_PORTG:    /*******************************/
    PGDATA |= (1U<<pin);
    break;

  case CH_PORTH:    /*******************************/
    PHDATA |= (1U<<pin);
    break;

  case CH_PORTJ:    /*******************************/
    PJDATA |= (1U<<pin);
    break;

  case CH_PORTK:    /*******************************/
    PKDATA |= (1U<<pin);
    break;

  case CH_PORTL:    /*******************************/
    PLDATA |= (1U<<pin);
    break;

  case CH_PORTM:    /*******************************/
    PMDATA |= (1U<<pin);
    break;

  case CH_PORTN:    /*******************************/
    PNDATA |= (1U<<pin);
    break;

  case CH_PORTP:    /*******************************/
    PPDATA |= (1U<<pin);
    break;

  case CH_PORTR:    /*******************************/
    PRDATA |= (1U<<pin);
    break;

  case CH_PORTT:    /*******************************/
    PTDATA |= (1U<<pin);
    break;

  case CH_PORTU:    /*******************************/
    PUDATA |= (1U<<pin);
    break;

  case CH_PORTV:    /*******************************/
    PVDATA |= (1U<<pin);
    break;

  case CH_PORTW:    /*******************************/
    PWDATA |= (1U<<pin);
    break;

  case CH_PORTY:    /*******************************/
    PYDATA |= (1U<<pin);
    break;

  case CH_PORTAA:   /*******************************/
    PAADATA |= (1U<<pin);
    break;

  case CH_PORTAB:   /*******************************/
    PABDATA |= (1U<<pin);
    break;

  case CH_PORTAC:   /*******************************/
    PACDATA |= (1U<<pin);
    break;

  case CH_PORTAD:   /*******************************/
    PADDATA |= (1U<<pin);
    break;

  case CH_PORTAE:   /*******************************/
    PAEDATA |= (1U<<pin);
    break;

  case CH_PORTAF:   /*******************************/
    PAFDATA |= (1U<<pin);
    break;

  case CH_PORTAG:   /*******************************/
    PAGDATA |= (1U<<pin);
    break;

  case CH_PORTAH:   /*******************************/
    PAHDATA |= (1U<<pin);
    break;

  case CH_PORTAJ:   /*******************************/
    PAJDATA |= (1U<<pin);
    break;

  default:
    break;
  }
}

/*************************************************************************
 * Function Name:   GPIO_ClearData
 * Parameters:      port_num - port pin number
 * Return:          none
 *
 * Description:     Set 0 to specified GPIO output pin
 *
 *************************************************************************/
void GPIO_ClearData( uint32_t port_num )
{
  uint8_t pin = (uint8_t)(port_num&0xF);

  switch (port_num>>4) {
  case CH_PORTA:    /*******************************/
    PADATA &= ~(1U<<pin);
    break;

  case CH_PORTB:    /*******************************/
    PBDATA &= ~(1U<<pin);
    break;

  case CH_PORTC:    /*******************************/
    PCDATA &= ~(1U<<pin);
    break;

  case CH_PORTD:    /*******************************/
    PDDATA &= ~(1U<<pin);
    break;

  case CH_PORTE:    /*******************************/
    PEDATA &= ~(1U<<pin);
    break;

  case CH_PORTF:    /*******************************/
    PFDATA &= ~(1U<<pin);
    break;

  case CH_PORTG:    /*******************************/
    PGDATA &= ~(1U<<pin);
    break;

  case CH_PORTH:    /*******************************/
    PHDATA &= ~(1U<<pin);
    break;

  case CH_PORTJ:    /*******************************/
    PJDATA &= ~(1U<<pin);
    break;

  case CH_PORTK:    /*******************************/
    PKDATA &= ~(1U<<pin);
    break;

  case CH_PORTL:    /*******************************/
    PLDATA &= ~(1U<<pin);
    break;

  case CH_PORTM:    /*******************************/
    PMDATA &= ~(1U<<pin);
    break;

  case CH_PORTN:    /*******************************/
    PNDATA &= ~(1U<<pin);
    break;

  case CH_PORTP:    /*******************************/
    PPDATA &= ~(1U<<pin);
    break;

  case CH_PORTR:    /*******************************/
    PRDATA &= ~(1U<<pin);
    break;

  case CH_PORTT:    /*******************************/
    PTDATA &= ~(1U<<pin);
    break;

  case CH_PORTU:    /*******************************/
    PUDATA &= ~(1U<<pin);
    break;

  case CH_PORTV:    /*******************************/
    PVDATA &= ~(1U<<pin);
    break;

  case CH_PORTW:    /*******************************/
    PWDATA &= ~(1U<<pin);
    break;

  case CH_PORTY:    /*******************************/
    PYDATA &= ~(1U<<pin);
    break;

  case CH_PORTAA:   /*******************************/
    PAADATA &= ~(1U<<pin);
    break;

  case CH_PORTAB:   /*******************************/
    PABDATA &= ~(1U<<pin);
    break;

  case CH_PORTAC:   /*******************************/
    PACDATA &= ~(1U<<pin);
    break;

  case CH_PORTAD:   /*******************************/
    PADDATA &= ~(1U<<pin);
    break;

  case CH_PORTAE:   /*******************************/
    PAEDATA &= ~(1U<<pin);
    break;

  case CH_PORTAF:   /*******************************/
    PAFDATA &= ~(1U<<pin);
    break;

  case CH_PORTAG:   /*******************************/
    PAGDATA &= ~(1U<<pin);
    break;

  case CH_PORTAH:   /*******************************/
    PAHDATA &= ~(1U<<pin);
    break;

  case CH_PORTAJ:   /*******************************/
    PAJDATA &= ~(1U<<pin);
    break;

  default:
    break;
  }
}

/*************************************************************************
 * Function Name:   GPIO_ReadData
 * Parameters:      port_num - port pin number
 * Return:          port data (0/1)
 *
 * Description:     Read data from specified GPIO input pin
 *
 *************************************************************************/
uint8_t GPIO_ReadData( uint32_t port_num )
{
  uint8_t pdata = 0;
  uint8_t pin = (uint8_t)(port_num&0xF);

  switch (port_num>>4) {
  case CH_PORTA:    /*******************************/
    pdata = (PADATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTB:    /*******************************/
    pdata = (PBDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTC:    /*******************************/
    pdata = (PCDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTD:    /*******************************/
    pdata = (PDDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTE:    /*******************************/
    pdata = (PEDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTF:    /*******************************/
    pdata = (PFDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTG:    /*******************************/
    pdata = (PGDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTH:    /*******************************/
    pdata = (PHDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTJ:    /*******************************/
    pdata = (PJDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTK:    /*******************************/
    pdata = (PKDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTL:    /*******************************/
    pdata = (PLDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTM:    /*******************************/
    pdata = (PMDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTN:    /*******************************/
    pdata = (PNDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTP:    /*******************************/
    pdata = (PPDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTR:    /*******************************/
    pdata = (PRDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTT:    /*******************************/
    pdata = (PTDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTU:    /*******************************/
    pdata = (PUDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTV:    /*******************************/
    pdata = (PVDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTW:    /*******************************/
    pdata = (PWDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTY:    /*******************************/
    pdata = (PYDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAA:   /*******************************/
    pdata = (PAADATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAB:   /*******************************/
    pdata = (PABDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAC:   /*******************************/
    pdata = (PACDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAD:   /*******************************/
    pdata = (PADDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAE:   /*******************************/
    pdata = (PAEDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAF:   /*******************************/
    pdata = (PAFDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAG:   /*******************************/
    pdata = (PAGDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAH:   /*******************************/
    pdata = (PAHDATA & (1U<<pin)? 1:0);
    break;

  case CH_PORTAJ:   /*******************************/
    pdata = (PAJDATA & (1U<<pin)? 1:0);
    break;

  default:
    break;
  }

  return pdata;
}


/** private functions **/
