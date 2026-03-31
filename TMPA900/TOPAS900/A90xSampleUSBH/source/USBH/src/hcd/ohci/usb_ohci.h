/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohci.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI Header

*/

#ifndef USB_OPEN_HOST_CONTROLLER_INTERFACE_H
#define USB_OPEN_HOST_CONTROLLER_INTERFACE_H

#include "usb_ohcitypes.h"

/* ========== Externs ========== */

/* Pipe 確保 */
extern usbd_pipe_t* usb_OHCI_ptAllocPipe( void );
/* Pipe 解放 */
extern void usb_OHCI_vFreePipe( usbd_pipe_t* ptPipe );
/* Xfer 確保 */
extern usbd_xfer_t* usb_OHCI_ptAllocXfer( void );
/* Xfer 解放 */
extern void usb_OHCI_vFreeXfer( usbd_xfer_t* ptXfer );

/* OHCI 初期化 */
extern usbd_status usb_OHCI_iInitialize( void );
/* OHCI 終了処理 */
extern void usb_OHCI_vFinalize( void );
/* パイプオープン */
extern usbd_status usb_OHCI_iOpen( usbd_pipe_t* ptPipe );
/* 割り込み処理 */
extern void usb_OHCI_vIntr( void );

#if defined( USB_DEBUG )
/* TD スキャン */
extern int16_t usb_OHCI_sScanTds( void );
#endif

#if defined( USB_CHECK_COMM_QUALITY )
/* 通信品質記録リセット　*/
extern void usb_OHCI_vResetCommQualityLog( void );
/* トランザクション単位での通信品質チェック */
extern void usb_OHCI_vCheckCommQuality( uint32_t* pulTrsCnt, uint32_t* pulTrsErrCnt, uint32_t* pulPktErrCnt );
#endif

#endif
