/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_classdrv.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Class Driver Header

*/

#ifndef USB_CLASS_DRIVER_H
#define USB_CLASS_DRIVER_H

#include "usb_config.h"
#include "usb_types.h"
#include "usb_queue.h"
#include "usb_trace.h"
#include "usb_dbg.h"
#include "usb_usbd_class.h"

/* ========== DEFINES ========== */

#define USBC_OK 0
#define USBC_NG (-1)

/* 最大エンドポイントディスクリプタ数 */
#define USBC_MAX_ED_NUM (USB_MAX_ENDPOINTS)

#define SET_ERRORCODE( perr, code ) { if( perr ) *perr = code; }
#define ERROR_IF(is, jump)  { if( is )  goto jump; }
#define ERROR_IF_WITHCODE(is, jump, perr, code) { if( is ){ SET_ERRORCODE( perr, code ); goto jump; }}


/* ========== TYPE_DEFS ========== */

struct USBC_tagDevice;
struct USBC_tagInterface;

typedef USBD_typeCommFinished USB_fpCommFinished;
typedef bool (*USBC_fpAttachDevice)( uint32_t ulIdDev, uint32_t ulArg);
typedef void (*USBC_fpDetachDevice)( uint32_t ulArg );
typedef bool (*USBC_fpAttachInterface)( struct USBC_tagInterface* ptInterface );
typedef void (*USBC_fpDetachInterface)( struct USBC_tagInterface* ptInterface );


/* アプリケーション コールバック群 */
typedef struct USBC_tagCallbacks {
  uint32_t ulArg;
  bool (*blAttach)( uint32_t ulArg );
  void (*vDetach)( uint32_t ulArg );
  void (*vDone)( uint32_t ulArg, void* pvResult, int16_t iStatus );
} USBC_typeCallbacks;


/* インターフェース管理用構造体 */
typedef struct USBC_tagInterface {
  usb_slist_entry_t list;
  struct USBC_tagDevice* ptDevice;        /* 所属デバイス構造体 */
  usb_config_descriptor_t* ptDescCfg;       /* コンフィギュレーションディスクリプタ */
  usb_interface_descriptor_t* ptDescIface;  /* インターフェースディスクリプタ */
  uint32_t ulIdIface;                       /* インターフェースID */
  usb_endpoint_descriptor_t* pptDescEp[USBC_MAX_ED_NUM]; /* エンドポイントディスクリプタ */
  uint32_t pulIdEp[USBC_MAX_ED_NUM];        /* エンドポイントID */
  USBC_fpAttachInterface blAttachInterface; /* デバイス接続時コールバック関数 */
  USBC_fpDetachInterface vDetachInterface;  /* デバイス解除時コールバック関数 */
  uint8_t ucState;                          /* インターフェース状態 */
  uint8_t ucRetryCount;                     /* リトライカウンタ */
  uint8_t ucAddedStatus;                    /* 付加的ステータス */
  void* pvBuffer;                           /* 通信バッファ */
  USBC_typeCallbacks tCallbacks;            /* アプリへの通信完了通知用コールバック関数 32B */
} USBC_typeInterface;


/* デバイス管理用構造体   24[byte] */
typedef struct USBC_tagDevice {
  USBD_typeClassDriver* ptClsDrv;        /* 所属クラス構造体 */
  uint32_t ulIdDev;              /* デバイスID */
  usb_device_descriptor_t* ptDescDev;      /* デバイスディスクリプタ */
  usb_string_descriptor_t* ptDescStr;      /* ストリングディスクリプタ */
  usb_slist_head_t tInterface;        /* デバイスに所属するインターフェースのリスト */
} USBC_typeDevice;

/* ========== EXTERNS ========== */

/* クラスドライバ初期化 */
extern void usb_USBC_vInitialize( void );
/* デバイス単位のクラスドライバ登録 */
extern int16_t usb_USBC_iRegistDeviceDriver( USBC_fpAttachDevice blAttDevFn, USBC_fpDetachDevice vDetDevFn,
                       USBC_typeDevice* ptDevice, int16_t* psError );
/* インターフェース単位のクラスドライバ登録 */
extern int16_t usb_USBC_iRegistInterfaceDriver( USBC_typeInterface* ptInterface, int16_t* psError );
/* デバイス単位のクラスドライバ登録解除 */
extern int16_t usb_USBC_iRemoveDeviceDriver( USBC_typeDevice* ptDevice, int16_t* psError );
/* インターフェース単位のクラスドライバ登録解除 */
extern int16_t usb_USBC_iRemoveInterfaceDriver( USBC_typeInterface* ptInterface, int16_t* psError );

#endif
