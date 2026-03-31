/*

  Tols File System 接続用 API 

*/

#ifndef USB_MSC_TOLS_API_H
#define USB_MSC_TOLS_API_H


#include "usb_msc.h"
#include "usb_usbd.h"


/* ========== DEFINES ========== */

#define E_USB_OK    0
#define E_USB_ERROR (-1)

/* ========== TYPE_DEFS ========== */

/* 初期化終了時コールバック */
typedef void (*USBInitCallbackFn)( int16_t iRet );

/* ========== EXTERNS ========== */

/* 初期化 */
extern int16_t USBInit( USBInitCallbackFn fvCb, USBD_typeNotification* ptNotifications );
/* 終了処理 */
extern void USBFin( void );
/* デバイス接続状態取得 */
extern void USBGetDeviceState( uint32_t* pulDevState );
/* 対象デバイス取得 */
extern uint8_t USBGetTargetDevice( void );
/* デバイス変更 */
extern int16_t USBChangeTargetDevice( uint8_t ucDevNo );
/* 論理ユニット数取得 */
extern int16_t USBGetNumLus( uint8_t *pucNumLus );
/* 対象 LUN 取得 */
extern uint8_t USBGetTargetLun( void );
/* 対象論理ユニット切り替え */
extern int16_t USBChangeTargetLun( uint8_t ucLun );
/* 論理ユニットチェック */
extern int16_t USBCheckLu( uint8_t ucLun );
/* 総セクタ数取得 (旧) */
extern int16_t USBGetStorageSize( uint32_t *pulSectors );
/* セクタ情報取得 */
extern int16_t USBGetSectorInf( uint32_t *pulSectors, uint32_t* pulSectorSz );
/* セクタ単位データリード */
extern int16_t USBReadSector( uint32_t ulStart, uint16_t usCount, uint8_t* ucBuf );
/* セクタ単位データライト */
extern int16_t USBWriteSector( uint32_t ulStart, uint16_t usCount, uint8_t* ucBuf );
/* SCSI コマンド実行 */
extern int16_t USBIoCtrl( usb_MSC_typeCommandBlock* ptCmdBlk );
/* デバイス状態チェック */
#if(0)
extern int USBGetStatus( int16_t* piStatus );
#else
#endif
/* デバイス切断 */
extern int16_t USBDisconnect( void );
/* 選択デバイス切断 */
extern int16_t USBDisconnectDevice( uint8_t ucDevNo );
/* デバイス再接続 */
extern int16_t USBReconnect( void );
/* 選択デバイス再接続 */
extern int16_t USBReconnectDevice( uint8_t ucDevNo );
/* デバイス ID 取得 */
extern uint32_t USBGetDeviceID( void );
/* エラーコード取得 */
extern int16_t USBGetErrorCode( void );
/* Sense Key 取得 */
extern uint8_t USBGetSenseKey( void );
#endif
