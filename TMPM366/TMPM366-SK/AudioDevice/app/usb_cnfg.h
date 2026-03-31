/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : usb_cfg.h
 *    Description : 
 *
 *    History :
 *    1. Date        : January, 2011
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

#define SpkEp         	                ENP2_OUT
#define SpkEpMaxSize   			(SampRerFrame * SubFrameSize)
#define SpkDDInd                        0

/* Class defenitions*/
#define USB_CTRL_INTERFACE              0
#define USB_SPK_INTERFACE               1

#define SubFrameSize                    2
#define SampRerFrame                    24
#define SampFreq                        (SampRerFrame KHZ)


/* Other defenitions */

#endif //__USB_CNFG_H

