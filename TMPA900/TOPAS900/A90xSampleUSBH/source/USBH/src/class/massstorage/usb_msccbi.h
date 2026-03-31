/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_msccbi.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Mass Storage Class Control/Bulk/Interrupt Transport Driver

*/

#ifndef USB_MSC_CBI_DRIVER_H
#define USB_MSC_CBI_DRIVER_H

#include "usb_msc_core.h"

/* ========== DEFINES ========== */

/* デバイスリセット時待ち時間[ms] */
#define MSC_CBI_RESET_RECOVERY_WAIT 100

/* リトライ回数 */
#define MSC_CBI_CSW_MAX_RETRY   1

/* エンドポイント番号 */
#define MSC_CBI_BI 0
#define MSC_CBI_BO 1
#define MSC_CBI_IN 2
#define MSC_CBI_EP_NUM 3   /* 総数 */

#if (USBC_MAX_ED_NUM < MSC_CBI_EP_NUM)
#error not enough max endpoints
#endif

/* Class Request */
#define MSC_CBI_REQUEST_ADSC   0x00


/* ========== TYPE_DEFS ========== */

/* Interrupt Data Block  2[byte] */
typedef struct MSC_CBI_tagIntDataBlock {
  uint8_t bType;
  uint8_t bValue;
} MSC_CBI_typeIntDataBlock;

/* CBI 用転送ブロック構造体  27～30[byte] */
typedef struct MSC_CBI_tagBlock {
  usb_MSC_typeCommandBlock      tCmdBlk;
  MSC_CBI_typeIntDataBlock  tStatBlk;
} MSC_CBI_typeBlock;


/* ========== EXTERNS ========== */

/* デバイス接続時初期化処理 */
extern int16_t usb_MSC_CBI_iInitialize( USBC_typeInterface* ptIface, int16_t* psError );
/* デバイス解除時終了処理 */
extern int16_t usb_MSC_CBI_iFinalize( USBC_typeInterface* ptIface, int16_t* psError );
/* デバイスリセット */
extern int16_t usb_MSC_CBI_iReset( USBC_typeInterface* ptIface, int16_t* psError );
/* SCSI コマンド実行 */
extern int16_t usb_MSC_CBI_iSCSICommand( USBC_typeInterface* ptIface, usb_MSC_typeCommandBlock* ptCmdBlk, int16_t* psError );

#endif
