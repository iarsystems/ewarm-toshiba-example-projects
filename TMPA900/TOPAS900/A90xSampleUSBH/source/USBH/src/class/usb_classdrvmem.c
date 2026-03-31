/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_classdrvmem.c 41 2014-01-27 14:05:18Z danielru $ */


#include <string.h>
#include "usb_classdrvmem.h"
#include "usb_queue.h"

#if defined( USB_DEBUG ) && defined( PRINT_ON )
#include <stdio.h>
#endif

/* ========== DEFINES ========== */

/* ========== global variables ========== */
#pragma section = "HC_RAM_CLASSDRVMEM"
/* 各種空き構造体リスト */
static USBC_typeDevice*     ptDEVICE_FREE_HEAD @ "HC_RAM_CLASSDRVMEM";
static USBC_typeInterface*  ptINTERFACE_FREE_HEAD @ "HC_RAM_CLASSDRVMEM";

/* 各種構造体メモリ領域 */
static USBC_typeDevice      ptDEVICE_BUFFER[USB_MAX_CLASS_DRIVERS] @ "HC_RAM_CLASSDRVMEM";
static USBC_typeInterface   ptINTERFACE_BUFFER[USB_MAX_CLASS_IFACE_DRIVERS] @ "HC_RAM_CLASSDRVMEM";

/* ========== local functions ========== */

/* ========== GLOBAL FUNCTIONS ========== */

/*
  メモリ初期化
*/
void usb_USBC_vInitMemory( void )
{
  /* ヘッダ初期値 */
  ptDEVICE_FREE_HEAD = NULL;
  ptINTERFACE_FREE_HEAD = NULL;

  /* 各種構造体リスト作成 */
  USB_CREATE_LIST( ptDEVICE_FREE_HEAD, ptDEVICE_BUFFER, USB_MAX_CLASS_DRIVERS );
  USB_CREATE_LIST( ptINTERFACE_FREE_HEAD, ptINTERFACE_BUFFER, USB_MAX_CLASS_IFACE_DRIVERS );
}


/*
  デバイス管理用構造体メモリ領域取得
*/
USBC_typeDevice* usb_USBC_ptAllocDevice( void )
{
  USBC_typeDevice* ptDevice;

  /* Device リストから1つ取り出してリターン */
  USB_DEQUEUE_LIST( ptDEVICE_FREE_HEAD, ptDevice )

  /* 0 クリア */
  if( ptDevice != NULL )
    memset( ptDevice, 0, sizeof(USBC_typeDevice) );

  return( ptDevice );
}

/*
  デバイス管理用構造体解放
*/
void usb_USBC_vFreeDevice( USBC_typeDevice* ptDevice )
{
  /* Device リストに返却 */
  USB_ENQUEUE_LIST( ptDEVICE_FREE_HEAD, ptDevice );
}


/*
  インターフェース管理用構造体メモリ領域取得
*/
USBC_typeInterface* usb_USBC_ptAllocInterface( void )
{
  USBC_typeInterface* ptInterface;

  /* Device リストから1つ取り出してリターン */
  USB_DEQUEUE_LIST( ptINTERFACE_FREE_HEAD, ptInterface )

  /* 0 クリア */
  if( ptInterface != NULL )
    memset( ptInterface, 0, sizeof(USBC_typeInterface) );

  return( ptInterface );
}

/*
  インターフェース管理用構造体解放
*/
void usb_USBC_vFreeInterface( USBC_typeInterface* ptInterface )
{
  /* Interface リストに返却 */
  USB_ENQUEUE_LIST( ptINTERFACE_FREE_HEAD, ptInterface );
}


/*
  メモリ使用状態チェック
*/
#if defined( USB_DEBUG )
int16_t usb_USBC_iMemCheck( void )
{
  int16_t iDev, iIface, iRet = 0;

  /* デバイス管理用構造体 */
  USB_NUM_CHECK_LIST( ptDEVICE_FREE_HEAD, iDev );
  iRet += USB_MAX_CLASS_DRIVERS - iDev;

  /* インターフェース管理用構造体 */
  USB_NUM_CHECK_LIST( ptINTERFACE_FREE_HEAD, iIface );
  iRet += USB_MAX_CLASS_IFACE_DRIVERS - iIface;

#if defined( USB_DEBUG ) && defined( PRINT_ON )
  printf("class: device structure  total:%d, free:%d\n", USB_MAX_CLASS_DRIVERS, iDev );
  printf("class: interface structure  total:%d, free:%d\n", USB_MAX_CLASS_IFACE_DRIVERS, iIface );
#endif

  return( iRet );
}
#endif


/* --- End of File --- */
