/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_mscapi.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  Mass Storage Class Driver USER API

*/

#ifndef USB_MSC_USER_API_H
#define USB_MSC_USER_API_H

#include "usb_types.h"
#include "usb_msc_core.h"
#include "usb_msc.h"

/* ========== DEFINES ========== */

/* 最大論理ユニット数 (1 ～ 16) */
#define MSC_MAX_NUM_LUS  16

/* SCSI コマンドリトライ回数  */
#define MSC_MAX_RETRY_SCSICMD 3

/* MSC クラスライブラリ状態 */
enum {
  MSC_APP_STAT_NO_DEVICE = 0,
  MSC_APP_STAT_IDLE,
  MSC_APP_STAT_ACTIVE
};

/* 状態検査種別マクロ */
enum {
  MSC_CHECK_RW,
  MSC_CHECK_COMM,
  MSC_CHECK_READY
};

/* ========== TYPE_DEFS ========== */


/* シナリオリスト構造体 */
typedef struct MSC_tagScenario {
  struct MSC_tagScenario* next;
  uint8_t ucScenNo;
} MSC_typeScenario;


/* MSC 管理用構造体 */
typedef struct MSC_tagMsc {
  uint32_t  ulIdMsc;                /* Mass Storage Class ID */
  uint32_t  pulNumBlks[MSC_MAX_NUM_LUS];     /* デバイスのブロック数 */
  uint16_t  pusBytePerBlk[MSC_MAX_NUM_LUS];  /* ブロック当たりのバイト数 */

  uint8_t   ucMaxLun;               /* 最大論理ユニット番号 */
  uint8_t   ucLun;                  /* 現在処理中の論理ユニット番号 */
  uint16_t  usLuState;              /* 論理ユニット状態 (ビットで表現) */

  MSC_typeScenario* ptScenarioList; /* シナリオリストヘッダ */

  void*     pvBuffer;               /* 転送時一時使用バッファ */

  uint32_t  ulTransBufSz;           /* 転送済みバッファサイズ */

  usb_MSC_typeCallbacks  tCallbacks;    /* コールバック関数群 */

  uint8_t   ucSenseKey;             /* SENSE KEY (REQUEST SENSE の結果) */
  uint8_t   ucState;                /* クラスの状態 */
  uint8_t   ucRetry;                /* リトライ回数 */
} MSC_typeMsc;


#endif
