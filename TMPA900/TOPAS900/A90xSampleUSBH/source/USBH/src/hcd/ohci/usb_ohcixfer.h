/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohcixfer.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI 転送処理

*/

#ifndef USB_OHCI_XFER_H
#define USB_OHCI_XFER_H

#include "usb_ohcitypes.h"
#include "usb_usbd_class.h"


/* デバイスリクエスト発行 */
extern int16_t usb_OHCI_iDeviceRequest( usbd_xfer_t* ptXfer, int16_t* psError );


/* --- USBD が使用する関数 (関数アドレスをUSBDに渡す) --- */

/* Control 転送開始 */
extern usbd_status usb_OHCI_iCtrlStart( usbd_xfer_t* ptXfer );
/* Control 転送中断 */
extern void usb_OHCI_vCtrlAbort( usbd_xfer_t* ptXfer);
/* Control パイプクローズ */
extern void usb_OHCI_vCtrlClose( usbd_pipe_t* ptPipe );
/* Bulk 転送開始 */
extern usbd_status usb_OHCI_iBulkStart( usbd_xfer_t* ptXfer );
/* Bulk 転送中断 */
extern void usb_OHCI_vBulkAbort( usbd_xfer_t* ptXfer);
/* Bulk パイプクローズ */
extern void usb_OHCI_vBulkClose( usbd_pipe_t* ptPipe );
/* Interrupt 転送開始 */
extern usbd_status usb_OHCI_iIntrStart( usbd_xfer_t* ptXfer );
/* Interrupt 転送中断 */
extern void usb_OHCI_vIntrAbort( usbd_xfer_t* ptXfer);
/* Interrupt パイプクローズ */
extern void usb_OHCI_vIntrClose( usbd_pipe_t* ptPipe );
/* Toggle ビットクリア */
extern void usb_OHCI_vClearToggle( usbd_pipe_t* ptPipe );

#endif
