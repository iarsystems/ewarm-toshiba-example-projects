/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohcimem.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI メモリ管理

*/

#ifndef OHCI_MEMORY_MANAGER_H
#define OHCI_MEMORY_MANAGER_H

#include "usb_ohcitypes.h"

/* 物理アドレス変換 */
/* ホストコントローラがアクセスする範囲は 0x0000～0x7fff であるが、
   RAM の先頭を参照するときにアドレスが 0 になると不都合が生じるため、
   そのままのアドレスを使用する */
#define DMAADDR( addr )	  ( (uint32_t)(addr) /*& 0x00007fffUL*/ )

/* 仮想アドレス変換 */
# define CPUADDR( addr )	  ((uint32_t)(addr) )

/* ページ */
#define OHCI_PAGE_SIZE				0x1000					/* ページサイズ */
#define OHCI_PAGE_HEADER( x )		( (x) & ~0xfff )		/* ページ先頭 */
#define OHCI_PAGE_FRACTION( x )		( (x) & 0xfff )			/* ページからの端数 */


extern void				usb_OHCI_vInitMemory( void );
extern OHCI_typeSoftEd* usb_OHCI_ptAllocSed( void );					/* SoftED 確保 */
extern void				usb_OHCI_vFreeSed( OHCI_typeSoftEd* ptSed );	/* SoftED 解放 */
extern OHCI_typeSoftTd* usb_OHCI_ptAllocStd( void );					/* SoftTD 確保 */
extern void				usb_OHCI_vFreeStd( OHCI_typeSoftTd* ptStd );	/* SoftTD 解放 */
extern OHCI_typeHcca*	usb_OHCI_ptAllocHcca( void );					/* HCCA 確保 */
extern void				usb_OHCI_vFreeHcca( OHCI_typeHcca* ptHcca );	/* HCCA 解放 */
#if defined( USB_DEBUG )
extern int16_t			usb_OHCI_iMemCheck( void );						/* メモリ使用状態チェック */
#endif
#endif
