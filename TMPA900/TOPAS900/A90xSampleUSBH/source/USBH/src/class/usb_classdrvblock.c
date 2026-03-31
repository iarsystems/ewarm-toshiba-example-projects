/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_classdrvblock.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  Class Driver 共通 コマンド/ステータス転送用ブロック

    ブロックは1つのみ存在し、従って同時に転送できるデータは1つだけである

*/

#include "usb_classdrvblock.h"

/* ========== static variables ========== */

#pragma section = "HC_RAM_CLASSDRVMEM"
static USBC_typeUnionBlock tU_BLOCK @ "HC_RAM_CLASSDRVMEM";
static bool blBLK_IN_USE @ "HC_RAM_CLASSDRVMEM";

/* ========== GLOBAL FUNCTIONS ========== */

/*
  共有ブロック初期化
*/
void usb_USBC_vInitUnionBlock( void )
{
  blBLK_IN_USE = false;
}


/*
  共有ブロック確保
*/
void* usb_USBC_ptAllocUnionBlock( void )
{
  if( blBLK_IN_USE != false )
    return( NULL );

  blBLK_IN_USE = true;
  return( &tU_BLOCK );
}

/*
  共有ブロック解放
*/
void usb_USBC_vFreeUnionBlock( void* ptUniBlk )
{
  if( ptUniBlk == &tU_BLOCK )
    blBLK_IN_USE = false;
}

/* --- End of File --- */
