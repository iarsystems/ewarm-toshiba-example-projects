/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2015
 *
 *    File name   : low_level_init.c
 *    Description : Low level device initialization
 *
 *    History :
 *    1. Date        : December 2015
 *       Author      : Atanas Uzunov
 *       Description : Create
 *
 *    $Revision: 1 $
 **************************************************************************/
#include "Toshiba\TZ10xx.h"


/*************************************************************************
 * Function Name: __low_level_init
 * Parameters: none
 *
 * Return: none
 *
 * Description: Low Level Initialization function. Clocks to peripherals are:
 *              MPIER: 48MHz, PPIER0: 12MHz.
 *************************************************************************/
int __low_level_init()
{
  /* Turn off POWER_EFUSE */
  pmulv->ISO_EFUSE_b.INISOEN_EFUSE = 1;
  pmulv->ISO_EFUSE_b.OUTISOEN_EFUSE = 1;
  pmulv->PSW_EFUSE_b.PSW_EFUSE_VDDCS = 0;
  pmulv->PSW_EFUSE_b.PSW_EFUSE_VDDCW = 0;

  /* Enable dynamic clock gating */
  pmulv->DCG_POWERDOMAIN = 0xfbfu;

  /* Workaround for eratta E25 */
  pmulv->DCG_PM_2_b.DCG_ppier0clk_gconf_pclk = 0;

  /* Select prescale values 1/1 for MPIER, 1/1 SPIC, 1/4 PPIER0 */
  pmulv->PRESCAL_MAIN_b.PSSEL_CD_MPIER = 1;
  pmulv->PRESCAL_MAIN_b.PSSEL_CD_SPIC = 1;
  pmulv->PRESCAL_MAIN_b.PSSEL_CD_PPIER0 = 4;

  /* Enable gconf */
  pmulv->CG_OFF_PM_2_b.CG_ppier0clk_gconf_pclk = 1;
  pmulv->SRST_OFF_PM_2_b.SRST_asyncrst_gconf_prstn = 1;

  /* Trim clock sources */
  /* OSC32K */
  if (0 == pmulv->CONFIG_OSC32K_b.OSC32K_BOOST_DISABLE) {
    pmulv->SELECT_EFUSE_b.SEL_EFUSE_OSC32K = 0;
    pmulv->OVERRIDE_EFUSE_OSC32K           = 1;
  }
  /* SIOSC32K */
  if (0 == pmulv->CONFIG_SiOSC32K_b.SiOSC32K_EN) {
    pmulv->SELECT_EFUSE_b.SEL_EFUSE_SiOSC32K = 0;
    pmulv->OVERRIDE_EFUSE_SiOSC32K           = 1;
  }
  /* SIOSC4M */
  pmulv->SELECT_EFUSE_b.SEL_EFUSE_SiOSC4M = 1;
  pmulv->CONFIG_SiOSC4M_b.SiOSC4M_CTRIM_LAT = 1;

  /* Configure Voltage mode */
  switch (pmulv->MOVE_VOLTAGE_START_b.VMSTATUS) {
  case 0:
    pmulv->OVERRIDE_EFUSE_SiOSC4M_b.OVERRIDE_EFUSE_SiOSC4M_CTRIM = pmulv->EFUSE_SiOSC4M_b.EFUSE_SiOSC4M_CTRIM_MODEA;
    break;
  case 1:
    pmulv->OVERRIDE_EFUSE_SiOSC4M_b.OVERRIDE_EFUSE_SiOSC4M_CTRIM = pmulv->EFUSE_SiOSC4M_b.EFUSE_SiOSC4M_CTRIM_MODEB;
    break;
  case 2:
    pmulv->OVERRIDE_EFUSE_SiOSC4M_b.OVERRIDE_EFUSE_SiOSC4M_CTRIM = pmulv->EFUSE_SiOSC4M_b.EFUSE_SiOSC4M_CTRIM_MODEC;
    break;
  case 3:
  default:
    pmulv->OVERRIDE_EFUSE_SiOSC4M_b.OVERRIDE_EFUSE_SiOSC4M_CTRIM = pmulv->EFUSE_SiOSC4M_b.EFUSE_SiOSC4M_CTRIM_MODED;
    break;
  }
  pmulv->CONFIG_SiOSC4M_b.SiOSC4M_CTRIM_LAT = 0;

  /* Read and clear reset factor */
  pmulv->STATUS_LVRST = 0xffffffff;

  /* Set DCDC_EXTCLKMODE and DCDC_SSFAST */
  pmulv->CONFIG_DCDC_LVREG_1 |= (1u << 31) | (1u << 18);

  /* Set WAITTIME_PSW_PWON and WAITTIME_PSW_PWOFF */
  pmulv->WAITTIME_PSW         = 0x00090009;
  pmulv->WAITTIME_DVSCTL_b.WAITTIME_CHGTIME = 0;

  /* Initialize DATA sections */
  return 1;
}
