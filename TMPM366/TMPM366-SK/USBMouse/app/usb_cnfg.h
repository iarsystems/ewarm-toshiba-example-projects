/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2007
 *
 *    File name   : lpc23xx_usb_cfg.h
 *    Description : Define main module
 *
 *    History :
 *    1. Date        : January 7, 2007
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 41 $
**************************************************************************/

#include "includes.h"

#ifndef __USB_CNFG_H
#define __USB_CNFG_H

/* Debug */
#define TRACE_EN                        0

/* USB High Speed support*/
#define USB_HIGH_SPEED                  0

/* USB interrupt priority */
#define USB_INTR_PRIORITY               0

/* USB Events */
#define USB_SOF_EVENT                   0
#define USB_SOF_FRAME_NUMB              0   // disable frame number

//DMA Settings

/* USB Clock source select */
#define USB_EXT_CLK_SEL                 0   // 

/* Device power atrb  */
#define USB_SELF_POWERED                1
#define USB_REMOTE_WAKEUP               0

/* Max Interfaces number*/
#define USB_MAX_INTERFACE               1

/* Endpoint definitions */
#if USB_HIGH_SPEED > 0
#define Ep0MaxSize                      64
#else
#define Ep0MaxSize                      8
#endif

#define ReportEpHid                     ENP3_IN
#define ReportEpMaxSize                 3
#define ReportEpPollingPeriod           2   // resolution 1ms

/* Class defenitions*/
#define HID_INTERFACE_0                 0
#define HID_BOOT_DEVICE                 1
#define HID_IDLE_SUPP                   1
#define HID_ID_NUMB                     0

#define HID_MOUSE_ID                    0

/* Other defenitions */

#endif //__USB_CNFG_H

