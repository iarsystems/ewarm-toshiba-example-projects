/**
 *******************************************************************************
 * @file    TMPM4Nx.h
 * @brief   CMSIS Cortex-M4 Core Peripheral Access Layer Header File for the
 *          TOSHIBA 'TMPM4Nx' Group
 * @version V1.0.0
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
 * 
 * Copyright(C) Toshiba Electronic Device Solutions Corporation 2019
 *******************************************************************************
 */
#ifndef __TMPM4Nx_H__
#define __TMPM4Nx_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup TOSHIBA_TXZ_MICROCONTROLLER TOSHIBA TXZ MICROCONTROLLER
  * @{
  */
  
/** @addtogroup TMPM4NR TMPM4NQ TMPM4NN
  * @{
  */

#if !defined(TMPM4NR) && !defined(TMPM4NQ)&& !defined(TMPM4NN)

/**
  * @brief Remove a comment of target device.
  */
   #define TMPM4NR      /*!< TMPM4NR device */
 //#define TMPM4NQ      /*!< TMPM4NQ device */
 //#define TMPM4NN      /*!< TMPM4NN device */
#endif

/** @defgroup Device_Included Device Included
  * @{
  */

#if defined(TMPM4NR)
   #include "TMPM4NR.h"
#elif defined(TMPM4NQ)
   #include "TMPM4NQ.h"
#elif defined(TMPM4NN)
   #include "TMPM4NN.h"
#else
   #error "target device is non-select."
#endif

/**
  * @}
  */ /* End of group Device_Included */

#ifdef __cplusplus
}
#endif

#endif  /* __TMPM4Nx_H__ */

/**
  * @}
  */ /* End of group TMPM4Nx */

/**
  * @}
  */ /* End of group TOSHIBA_TXZ_MICROCONTROLLER */
