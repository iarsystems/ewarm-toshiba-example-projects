/* ************************************************************************** */
/*
 * --------------------------------------------------------------------------
 *	Application			: USB Host Driver
 *	Micon				: TMP92xx28
 *	Development Tool	: -
 * 	Complie Option		: -
 *  Copyright(C) TOSHIBA CORPORATION 2007 All rights reserved
 * --------------------------------------------------------------------------
 */

/*! \file usb_msc.h
	\brief Declaration of USB Host Driver MSC Driver Function

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */

#ifndef USB_MSC_PUBLIC_H
#define USB_MSC_PUBLIC_H

#include "usb_types.h"

/* ========== DEFINES ========== */

#define USB_MSC_OK 0
#define USB_MSC_NG (-1)

/* エラーコード */
enum {
  USB_MSC_NO_DEVICE     = -1,       /*!< デバイスが挿入されていない */
  USB_MSC_NOT_READY     = -2,       /*!< デバイスが初期化されていない */
  USB_MSC_NOMEM         = -3,       /*!< メモリ不足 */
  USB_MSC_PARAMETER     = -4,       /*!< 引数が正常でない */
  USB_MSC_IN_USE        = -5,       /*!< デバイス使用(通信)中 */
  USB_MSC_TIMEOUT       = -6,       /*!< タイムアウト */
  USB_MSC_CANCELLED     = -7,       /*!< 通信キャンセル */
  USB_MSC_DEVICE_ABNORMAL = -8,     /*!< デバイス異常、再挿入が必要 */
  USB_MSC_DRIVER_ABNORMAL = -9,     /*!< ドライバ異常、初期化からのやり直しが必要 */
  USB_MSC_SCSI_CMD_FAILED = -10     /*!< SCSIコマンドでエラー発生、SenseKey参照 */
};

/* SENSE KEY */
enum {
  USB_MSC_SK_NO_SENSE         = 0,
  USB_MSC_SK_RECOVERED_ERROR  = 1,
  USB_MSC_SK_NOT_READY        = 2,
  USB_MSC_SK_MEDIUM_ERROR     = 3,
  USB_MSC_SK_HARDWARE_ERROR   = 4,
  USB_MSC_SK_ILLEGAL_ERROR    = 5,
  USB_MSC_SK_UNIT_ATTENTION   = 6,
  USB_MSC_SK_DATA_PROTECT     = 7,
  USB_MSC_SK_BLANK_CHECK      = 8,
  USB_MSC_SK_VENDOR_SPECIFIC  = 9,
  USB_MSC_SK_ABORTED_COMMAND  = 11,
  USB_MSC_SK_VOLUME_OVERFLOW  = 13,
  USB_MSC_SK_MISCOMPARE       = 14
};
#define USB_MSC_SK_UNKNOWN 15

/* 転送方向 usb_MSC_typeCommandBlock.ucDirection */
#define USB_MSC_DIR_OUT 0x00		/*!< MSC Data Direction Out */
#define USB_MSC_DIR_IN  0x80		/*!< MSC Data Direction In  */

/* ========== TYPE_DEFS ========== */

/*! SCSIコマンド用構造体  25[byte] */
typedef struct usb_MSC_tagCommandBlock {
  uint8_t*  pucBuffer;              /*!< バッファポインタ */
  uint16_t  usBufferSize;           /*!< バッファサイズ */
#define USB_MSC_CMDBLK_SZ 16		/*!< コマンドブロックサイズ */
  uint8_t   pucCmdBlock[USB_MSC_CMDBLK_SZ]; /*!< コマンドブロック本体 */
  uint8_t   ucCmdSize;              /*!< コマンドブロック長 */
  uint8_t   ucDirection;            /*!< 入出力方向 */
  uint8_t   ucLun;                  /*!< 論理ユニット番号 */
} usb_MSC_typeCommandBlock;


/*! MSC コールバック関数設定用構造体 16[byte] */
typedef struct usb_MSC_tagCallbacks {
  uint32_t ulArg;						/*!< コールバック引数 */
  void (*vAttach)( uint32_t ulArg );	/*!< デバイス接続時のコールバック関数 */
  void (*vDetach)( uint32_t ulArg );	/*!< デバイス解除時のコールバック関数 */
  void (*vDone)( uint32_t ulArg, uint32_t ulSize, int16_t sStatus );	/*!< デバイス操作完了時のコールバック関数 */
} usb_MSC_typeCallbacks;


/* ========== EXTERNS ========== */
/*! MSC 初期化 */
extern void usb_MSC_vInitialize( void );
/*! MSC 使用開始 */
extern int16_t usb_MSC_iOpen( usb_MSC_typeCallbacks* ptCallbacks,
							  uint32_t* pulIdDev, int16_t * psError );
/*! MSC 使用終了 */
extern int16_t usb_MSC_iClose( uint32_t ulIdDev, int16_t * psError );
/*! ブロック書き込み */
extern int16_t usb_MSC_iWrite( uint32_t ulIdDev, uint8_t ucLun,
							   uint32_t ulStartBlk, uint16_t usNumBlks,
							   uint8_t* pucBuffer, int16_t * psError );
/*! ブロック読み込み */
extern int16_t usb_MSC_iRead( uint32_t ulIdDev, uint8_t ucLun,
							  uint32_t ulStartBlk, uint16_t usNumBlks,
							  uint8_t* pucBuffer, int16_t * psError );
/*! MSC デバイス初期化 */
extern int16_t usb_MSC_iInitDevice( uint32_t ulIdDev, uint8_t ucLun,
									int16_t *psError );
/*! SCSI コマンド実行 */
extern int16_t usb_MSC_iIoControl( uint32_t ulIdDev,
								   usb_MSC_typeCommandBlock* ptCmdBlk,
								   int16_t * psError );
/*! デバイス操作キャンセル */
extern int16_t usb_MSC_iIoCancel( uint32_t ulIdDev, int16_t* psError );
/*! 状態取得 */
extern void usb_MSC_vGetStatus( uint32_t ulIdDev, int16_t * psStatus,
								uint16_t* pusLuState );
/*! デバイスの論理ユニット数取得 */
extern int16_t usb_MSC_iGetNumLus( uint32_t ulIdDev, uint8_t* pucNumLus,
								   int16_t * psError );
/*! デバイスブロック情報取得 */
extern int16_t usb_MSC_iGetBlkInf( uint32_t ulIdDev, uint8_t ucLun,
								   uint32_t* pulBlkNum,
								   uint32_t* pulBytePerBlk, int16_t * psError );
/*! SenseKey 取得 */
extern int16_t usb_MSC_iGetSenseKey( uint32_t ulIdDev, uint8_t* pucSenseKey,
									 int16_t* psError );
/*! コールバック関数セット */
extern void usb_MSC_vSetCallback( uint32_t ulIdDev,
								  usb_MSC_typeCallbacks* ptCallbacks );
/*! デバイス切断 */
extern int16_t usb_MSC_iDisconnect( uint32_t ulIdDev, uint32_t* pulIdPort,
									int16_t* psError );
/*! デバイス再接続 */
extern int16_t usb_MSC_iConnect( uint32_t ulIdPort, int16_t* psError );

#endif
