/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_msc_core.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Mass Storage Class Driver Core Header

*/

#ifndef USB_MASS_STORAGE_CLASS_DRIVER_H
#define USB_MASS_STORAGE_CLASS_DRIVER_H

#include "usb_config.h"
#include "usb_classdrv.h"
#include "usb_msc.h"

/* ========== DEFINES ========== */

#define MSC_OK USB_MSC_OK
#define MSC_NG USB_MSC_NG

/* Mass Storage Class Code */
#define MSC_CLASS_CODE 0x08

/* Mass Storage Sub Class Code */
#define MSC_SUBCLASS_UFI      0x04
#define MSC_SUBCLASS_SFF8070I 0x05
#define MSC_SUBCLASS_SCSI     0x06

/* Mass Storage Class Transport Protocol */
#define MSC_PROTOCOL_CBI_CCI   0x00     /* CBI with CCI */
#define MSC_PROTOCOL_CBI_NOCCI 0x01     /* CBI */
#define MSC_PROTOCOL_BBB       0x50     /* Bulk-Only Transport */

/* ATAPI コマンドブロックサイズ */
#define MSC_ATAPI_CMD_SZ    12

/* 転送状態 */
enum {
  MSC_STAT_NO_DEVICE  = 0x00,   /* デバイス未接続 */
  MSC_STAT_READY      = 0x01,   /* 通信可能 */
  MSC_STAT_COMMAND    = 0x02,   /* コマンド送信中 */
  MSC_STAT_DATA       = 0x03,   /* データ転送中 */
  MSC_STAT_STATUS     = 0x04    /* ステータス受信中 */
};


/* コマンド完了ステータス */
enum {
  MSC_STATUS_COMMAND_PASSED  = 0x00,      /* コマンド成功 */
  MSC_STATUS_COMMAND_FAILED  = 0x01,      /* コマンド失敗 */
  MSC_STATUS_PHASE_ERROR     = 0x02,      /* フェイズエラー(内部エラー) */
  MSC_STATUS_PERSISTENT_FAILURE  = 0x03, /* Persistent Failure (CBI) */
  MSC_STATUS_IO_ERROR,                    /* 通信エラー */
  MSC_STATUS_TIMEOUT,                     /* 転送タイムアウト */
  MSC_STATUS_CANCELLED,                   /* 転送キャンセル */
  MSC_STATUS_FATAL_ERROR,                 /* デバイス異常 */
  MSC_STATUS_ILLEGAL_CSW,                 /* 異常な CSW */
  MSC_STATUS_DRIVER_ERROR,                /* ドライバの状態異常 */
  MSC_STATUS_REMOVE_DEVICE                /* デバイス解除 */
};

/* ========== TYPE_DEFS ========== */

/* 結果返却用構造体  7[byte] */
typedef struct MSC_tagResult {
  uint8_t*  pucBuffer;              /* コマンドに付随した転送データ */
  uint16_t  usSize;                 /* 実際に転送したデータ長 */
  uint8_t   ucSCSICmd;              /* 実行した SCSI コマンド種別 */
} MSC_typeResult;

/* ========== EXTERNS ========== */

/* Mass Storage デバイス使用開始 */
extern int16_t usb_MSC_CORE_iOpen( USBC_typeCallbacks* ptCallbacks, uint32_t* pulIdMsc, int16_t* psError );
/* Mass Storage デバイス使用終了 */
extern int16_t usb_MSC_CORE_iClose( uint32_t ulIdMsc, int16_t* psError );
/* Mass Storage リセット復旧 */
extern int16_t usb_MSC_CORE_iResetRecovery( uint32_t ulIdMsc, int16_t* psError );
/* SCSI Command 発行 */
extern int16_t usb_MSC_CORE_iSCSICommand( uint32_t ulIdMsc, usb_MSC_typeCommandBlock* ptCmdBlk, int16_t* psError );
/* SCSI Command キャンセル */
extern int16_t usb_MSC_CORE_iCancelCommand( uint32_t ulIdMsc, int16_t* psError );
/* 最大論理ユニット番号取得 */
extern int16_t usb_MSC_CORE_iGetMaxLUN( uint32_t ulIdMsc, unsigned char* pucMaxLun, int16_t* psError );
#endif
