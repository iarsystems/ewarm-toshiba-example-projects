/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_mscbbb.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Mass Storage Class Bulk-Only Transport Driver

*/

#ifndef USB_MSC_BBB_DRIVER_H
#define USB_MSC_BBB_DRIVER_H

#include "usb_msc_core.h"

/* ========== DEFINES ========== */

/* デバイスリセット時待ち時間[ms] */
#define MSC_BBB_RESET_RECOVERY_WAIT 100

/* リトライ回数 */
#define MSC_BBB_CBW_MAX_RETRY   2
#define MSC_BBB_CSW_MAX_RETRY   1

/* シグネチャ */
#define MSC_BBB_CBW_SIGNATURE 0x43425355
#define MSC_BBB_CSW_SIGNATURE 0x53425355

/* エンドポイント番号 */
#define MSC_BBB_BI 0
#define MSC_BBB_BO 1
#define MSC_BBB_EP_NUM 2  /* 総数 */

#if (USBC_MAX_ED_NUM < MSC_BBB_EP_NUM)
#error not enough max endpoints
#endif

/* bmCBWFlags */
#define MSC_BBB_DIR_OUT   0x00
#define MSC_BBB_DIR_IN    0x80

/* Class Request */
#define MSC_BBB_REQUEST_RESET   0xff
#define MSC_BBB_GET_MAX_LUN     0xfe

/* ブロックサイズ */
#define MSC_BBB_CBW_SIZE  31
#define MSC_BBB_CSW_SIZE  13

/* ========== TYPE_DEFS ========== */

/* Command Block Wrapper  31[byte] */
typedef struct MSC_BBB_tagCBW {
  uint32_t dCBWSignature;
  uint32_t dCBWTag;
  uint32_t dCBWDataTransferLength;
  uint8_t  bmCBWFlags;
  uint8_t  bCBWLUN;
  uint8_t  bCBWCBLength;
  uint8_t  CBWCB[16];
} MSC_BBB_typeCBW;

/* Command Status Wrapper  13[byte] */
typedef struct MSC_BBB_tagCSW {
  uint32_t dCSWSignature;
  uint32_t dCSWTag;
  uint32_t dCSWDataResidue;
  uint8_t  bCSWStatus;
} MSC_BBB_typeCSW;

/* BBB 用転送ブロック構造体  44[byte] */
typedef struct MSC_BBB_tagBlock {
  MSC_BBB_typeCBW tCbw;
  MSC_BBB_typeCSW tCsw;
} MSC_BBB_typeBlock;

/* ========== EXTERNS ========== */

/* デバイス接続時初期化処理 */
extern int16_t usb_MSC_BBB_iInitialize( USBC_typeInterface* ptIface, int16_t* psError );
/* デバイス解除時終了処理 */
extern int16_t usb_MSC_BBB_iFinalize( USBC_typeInterface* ptIface, int16_t* psError );
/* デバイスリセット */
extern int16_t usb_MSC_BBB_iReset( USBC_typeInterface* ptIface, int16_t* psError );
/* SCSI コマンド実行 */
extern int16_t usb_MSC_BBB_iSCSICommand( USBC_typeInterface* ptIface, usb_MSC_typeCommandBlock* ptCmdBlk, int16_t* psError );
/* Class Request GetMaxLUN */
extern int16_t usb_MSC_BBB_iGetMaxLUN( USBC_typeInterface* ptIface, uint8_t* pucLun, int16_t* psError );

#endif
