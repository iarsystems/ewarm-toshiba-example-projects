/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohcilib.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI Utility

*/

#ifndef USB_OHCI_LIBRARY_H
#define USB_OHCI_LIBRARY_H

#include "usb_ohcitypes.h"
#include "usb_tmr.h"
#include "usb_dbg.h"

/* ========== DEFINES ========== */

#define ERROR_IF(is, jump)	{ if( is )	goto jump; }
#define ERROR_IF_WITHCODE(is, jump, perr, code) { if( is ){ if( perr ) *perr = code; goto jump; }}

#define MSEC_WAIT( time )  usb_TIMER_vWaiMsec( time )
#define GET_TIME()			usb_TIMER_lGetTime()

/* ========== Externs ========== */

/* Endpoint Descriptor リスト追加 */
extern void usb_OHCI_vAddEd( OHCI_typeSoftEd* ptSed, OHCI_typeSoftEd* ptHead );
/* Endpoint Descriptor リスト除去 */
extern void usb_OHCI_vRemoveEd( OHCI_typeSoftEd* ptSed, OHCI_typeSoftEd* ptHead );
/* ハッシュ TD 追加 */
extern void usb_OHCI_vHashAddTd( OHCI_typeOhci* ptOhci, OHCI_typeSoftTd* ptStd );
/* ハッシュ TD 除去 */
extern void usb_OHCI_vHashRemoveTd( OHCI_typeOhci* ptOhci, OHCI_typeSoftTd* ptStd );
/* ハッシュ TD 検索 */
extern OHCI_typeSoftTd* usb_OHCI_ptHashFindTd( OHCI_typeOhci* ptOhci, uint32_t ulHeadP );
/* 指定した xfer に属する未転送 TD の削除 */
extern void usb_OHCI_vDeleteTdsInXfer( OHCI_typeOhci* ptOhci, usbd_xfer_t* ptXfer );

#endif
