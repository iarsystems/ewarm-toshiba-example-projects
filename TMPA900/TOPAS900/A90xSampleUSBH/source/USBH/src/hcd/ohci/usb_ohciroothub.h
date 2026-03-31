/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohciroothub.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI Root Hub 処理

*/

#ifndef USB_OHCI_ROOT_HUB_H
#define USB_OHCI_ROOT_HUB_H

#include "usb_ohcitypes.h"
#include "usb_usbd_class.h"

/* Root Hub Status Change 割り込み許可/禁止 */
extern void usb_OHCI_vRhscAble( OHCI_typeOhci* ptOhci, bool blAble );
/* Root Hub Status Change 割り込み処理 */
extern void usb_OHCI_vRhsc( OHCI_typeOhci* ptOhci, usbd_xfer_t* ptXfer );

/* Control 転送開始 */
extern usbd_status usb_OHCI_iRootCtrlStart( usbd_xfer_t* ptXfer );
/* Control 転送中断 */
extern void usb_OHCI_vRootCtrlAbort( usbd_xfer_t* ptXfer);
/* Control パイプクローズ */
extern void usb_OHCI_vRootCtrlClose( usbd_pipe_t* ptPipe );
/* Interrupt 転送開始 */
extern usbd_status usb_OHCI_iRootIntrStart( usbd_xfer_t* ptXfer );
/* Interrupt 転送中断 */
extern void usb_OHCI_vRootIntrAbort( usbd_xfer_t* ptXfer);
/* Interrupt パイプクローズ */
extern void usb_OHCI_vRootIntrClose( usbd_pipe_t* ptPipe );

#endif
