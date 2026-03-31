/**
 *****************************************************************************
 * @file     system_TMPM471F10.h
 * @brief    CMSIS Cortex-M4 Device Peripheral Access Layer Header File for the
 *           TOSHIBA 'TMPM471' Device Series 
 * @version V1.0.0.0
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * Copyright(C) Toshiba Electronic Device Solutions Corporation 2024
 *****************************************************************************
 */



#ifndef __SYSTEM_TMPM471F10_H
#define __SYSTEM_TMPM471F10_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <stdint.h>

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock 
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif
