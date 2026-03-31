/**
 *******************************************************************************
 * @file    TMPM4Gx.h
 * @brief   CMSIS Cortex-M4 Core Peripheral Access Layer Header File for the
 *          TOSHIBA 'TMPM4Gx' Group
 * @version V0.0.0.0
 * $Date:: 2017-06-23 #$
 * 
 * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
 * 
 * (C)Copyright TOSHIBA MICROELECTRONICS CORPORATION 2017 All rights reserved
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
  
/** @addtogroup TMPM4Gx TMPM4Gx
  * @{
  */

#if !defined(TMPM4G9) && !defined(TMPM4G8) && !defined(TMPM4G7) && \
    !defined(TMPM4G6)

/**
  * @brief Remove a comment of target device.
  */
   #define TMPM4G9      /*!< TMPM4G9 device */
/* #define TMPM4G8 */   /*!< TMPM4G8 device */
/* #define TMPM4G7 */   /*!< TMPM4G7 device */
/* #define TMPM4G6 */   /*!< TMPM4G6 device */
#endif

/** @defgroup Device_Included Device Included
  * @{
  */

#if defined(TMPM4G9)
   #include "TMPM4G9.h"
#elif defined(TMPM4G8)
   #include "TMPM4G8.h"
#elif defined(TMPM4G7)
   #include "TMPM4G7.h"
#elif defined(TMPM4G6)
   #include "TMPM4G6.h"
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
