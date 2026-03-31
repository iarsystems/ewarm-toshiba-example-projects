/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_classdrvmem.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Class Driver メモリ管理

*/

#ifndef USB_CLASS_MEMORY_MANAGER_H
#define USB_CLASS_MEMORY_MANAGER_H

#include "usb_config.h"
#include "usb_classdrv.h"
#include "usb_usbd_mem.h"

/* ========== DEFINES ========== */

#define usb_USBC_ptAllocDeviceRequest() usb_USBDAllocDeviceRequest()
#define usb_USBC_vFreeDeviceRequest( req ) usb_USBDDeallocDeviceRequest( (req) )


/* ========== EXTERNS ========== */

/* USBクラスドライバ用メモリ初期化 */
extern void usb_USBC_vInitMemory( void );
/* デバイス管理用構造体メモリ領域取得 */
extern USBC_typeDevice* usb_USBC_ptAllocDevice( void );
/* デバイス管理用構造体解放 */
extern void usb_USBC_vFreeDevice( USBC_typeDevice* ptDevice );
/* インターフェース管理用構造体メモリ領域取得 */
extern USBC_typeInterface* usb_USBC_ptAllocInterface( void );
/* インターフェース管理用構造体解放 */
extern void usb_USBC_vFreeInterface( USBC_typeInterface* ptInterface );
/* メモリ使用状態チェック */
extern int16_t usb_USBC_iMemCheck( void );

#endif
