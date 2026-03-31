/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_classdrvblock.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  Class Driver 共有 コマンド/ステータス転送用ブロック

*/

#ifndef USB_CLASS_DRIVER_UNION_BLOCK_H
#define USB_CLASS_DRIVER_UNION_BLOCK_H

#include "usb.h"
#include "usb_config.h"
#include "usb_mscbbb.h"
#include "usb_msccbi.h"

/* ========== TYPE_DEFS ========== */

/* コマンド転送用共有ブロック  44[byte] */
typedef union USBC_tagUnionBlock {
  /* Mass Storage Class Bulk-Only Transport */
  MSC_BBB_typeBlock tBbb;
  /* Mass Storage Class Control/Bulk/Interrupt Transport */
  MSC_CBI_typeBlock tCbi;
  /* 汎用 (デバイスリクエストに使用) */
  uint8_t pucBuf[1];
} USBC_typeUnionBlock;


/* ========== EXTERNS ========== */
/* 共有ブロック初期化 */
extern void usb_USBC_vInitUnionBlock( void );

/* 共有ブロック確保 */
extern void* usb_USBC_ptAllocUnionBlock( void );

/* 共有ブロック解放 */
extern void usb_USBC_vFreeUnionBlock( void* ptUniBlk );

#endif
