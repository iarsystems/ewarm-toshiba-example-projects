/**
 *******************************************************************************
 * @file    TMPM4Gx.h
 * @brief   CMSIS Cortex-M4 Core Peripheral Access Layer Header File for the
 *          TOSHIBA 'TMPM4Gx' Group
 * @version V1.0.0
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * Copyright(C) Toshiba Electronic Device Solutions Corporation 2020
 *******************************************************************************
 */
#ifndef __TMPM4Gx_H__
#define __TMPM4Gx_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup TOSHIBA_TXZ_MICROCONTROLLER TOSHIBA TXZ MICROCONTROLLER
  * @{
  */
  
/** @addtogroup TMPM4GR TMPM4GQ TMPM4GN
  * @{
  */

#if !defined(TMPM4GR) && !defined(TMPM4GQ)&& !defined(TMPM4GN)

/**
  * @brief Remove a comment of target device.
  */
   #define TMPM4GR      /*!< TMPM4GR device */
 /*#define TMPM4GQ*/    /*!< TMPM4GQ device */
 /*#define TMPM4GN*/    /*!< TMPM4GN device */
#endif

/** @defgroup Device_Included Device Included
  * @{
  */

#if defined(TMPM4GR)
   #include "TMPM4GR.h"
#elif defined(TMPM4GQ)
   #include "TMPM4GQ.h"
#elif defined(TMPM4GN)
   #include "TMPM4GN.h"
#else
   #error "target device is non-select."
#endif

/**
  * @}
  */ /* End of group Device_Included */

#ifdef __cplusplus
}
#endif

#endif  /* __TMPM4Gx_H__ */

/**
  * @}
  */ /* End of group TMPM4Gx */

/**
  * @}
  */ /* End of group TOSHIBA_TXZ_MICROCONTROLLER */
