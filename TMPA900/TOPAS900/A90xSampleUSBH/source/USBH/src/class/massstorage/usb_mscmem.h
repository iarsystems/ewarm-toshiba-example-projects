/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_mscmem.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Mass Storage Class Driver メモリ管理

*/

#ifndef USB_MSC_MEMORY_MANAGER_H
#define USB_MSC_MEMORY_MANAGER_H

#include "usb_mscapi.h"
#include "usb_scsi_util.h"

/* ========== DEFINES ========== */

#define MSC_MAX_NUM USB_MAX_CLASS_IFACE_DRIVERS  /* MSC 管理用構造体数 */
#define MSC_MAX_NUM_SECENARIOS 5    /* シナリオ構造体数 (～255) */

/* ========== TYPE_DEFS ========== */

/* 読み書きパラメータ保存用構造体  12[byte] */
typedef struct MSC_tagReadWriteParameter {
  uint8_t*  pucBuffer;                /* 次転送バッファポインタ */
  uint32_t  ulStartBlk;               /* 次転送開始ブロック番号 */
  uint16_t  usNumBlks;                /* 次転送ブロック数 */
  uint16_t  usRemainBlks;             /* 残余ブロック数 */
} MSC_typeReadWriteParameter;


/* 転送時使用バッファ  36[byte] */
typedef union MSC_tagBuffer {
  uint8_t   pucBuffer[1];
  uint8_t   pucInquiry[SCSI_INQUIRY_BUF_SZ];
  uint8_t   pucReadCapacity[SCSI_READ_CAPACITY_BUF_SZ];
  uint8_t   pucReadSense[SCSI_REQUEST_SENSE_BUF_SZ];
  usb_MSC_typeCommandBlock  tCmdBlk;        /* SCSI Command 保存用 */
  MSC_typeReadWriteParameter  tRwPar;   /* 読み書きパラメータ */
} MSC_typeBuffer;

/* ========== EXTERNS ========== */

/* MSC メモリ初期化 */
extern void usb_MSC_vInitMemory( void );

/* MSC 管理用構造体確保 */
extern MSC_typeMsc* usb_MSC_ptAllocMsc( void );
/* MSC 管理用構造体解放 */
extern void usb_MSC_vFreeMsc( MSC_typeMsc* ptMsc );

/* MSC シナリオリスト用構造体確保 */
extern MSC_typeScenario* usb_MSC_ptAllocScenario( void );
/* MSC シナリオリスト用構造体解放 */
extern void usb_MSC_vFreeScenario( MSC_typeScenario* ptScen );
/* シナリオ削除 */
extern void usb_MSC_vDeleteScenarioList( MSC_typeScenario* ptScenHead );
/* シナリオ作成 */
extern MSC_typeScenario* usb_MSC_ptCreateScenarioList( uint8_t* pucScen, uint8_t ucLen );
/* 先頭にシナリオ追加 */
extern MSC_typeScenario* usb_MSC_ptAddHeadScenario( MSC_typeScenario** pptHead, uint8_t ucScenNo );
/* 次シナリオ取り出し */
extern MSC_typeScenario* usb_MSC_ptJumpNextScenario( MSC_typeScenario** pptHead );

/* 転送時使用バッファ確保 */
extern void* usb_MSC_pvAllocTransferBuffer( void );
/* 転送時使用バッファ解放 */
extern void usb_MSC_vFreeTransferBuffer( void* pvBuf );

/* スタック軽減用メモリ確保 */
extern void* usb_MSC_pvAllocTempMemory( void );
/* スタック軽減用メモリ解放 */
extern void usb_MSC_vFreeTempMemory( void* pvBuf );

#if defined( USB_DEBUG ) 
/* メモリ使用状態チェック */
extern int16_t usb_MSC_iMemCheck( void );
#endif

#endif

