/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_classdrv.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Class Driver

*/

#include "usb_classdrv.h"
#include "usb_classdrvmem.h"
#include "usb_classdrvblock.h"

/* ========== global variables ========== */
#pragma section = "HC_RAM_CLASSDRVMEM"
/* インターフェース登録リスト */
static usb_slist_head_t tINTERFACE_LIST @ "HC_RAM_CLASSDRVMEM";

/* インターフェース登録用ダミー構造体 (static) */
/* 2006/05/24 修正 田谷  場所移動 */
static USBC_typeDevice* ptDEVICE_DUMMY @ "HC_RAM_CLASSDRVMEM";


/* ========== local functions ========== */
static bool blAttachDevice( uint32_t ulIdDev, uint32_t ulArg );
static void vDetachDevice( uint32_t ulArg );

/*
  ダミーデバイス管理
    インターフェース単位でのドライバの登録・使用状況に応じて、
    ダミーデバイスの登録･解除を行う
*/
static void vManageDummyDevice( USBC_typeDevice* ptAttDevice, USBC_typeDevice* ptDetDevice )
{
  int16_t iRet;
  USBC_typeDevice* ptDevice = NULL;

  /* 使用されたダミーデバイスを取り外す */
  if( ptAttDevice == ptDEVICE_DUMMY )
    {
      ptDEVICE_DUMMY = NULL;
    }

  /* 登録済みインターフェースが存在しない場合、ダミーデバイスは必要ない */
  if( tINTERFACE_LIST.first == NULL )
    {
      if( ptDEVICE_DUMMY != NULL )
        {
          /* ダミーデバイスの登録解除 */
          iRet = usb_USBC_iRemoveDeviceDriver( ptDEVICE_DUMMY, NULL );
          ERROR_IF( iRet != USBC_OK, EXT );
          /* メモリ解放 */
          usb_USBC_vFreeDevice( ptDEVICE_DUMMY );
          ptDEVICE_DUMMY = NULL;
        }
    }
  /* 登録済みインターフェースが存在する場合、一つのダミーデバイスが必要 */
  else
    {
      if( ptDEVICE_DUMMY == NULL )
        {
          if( ptDetDevice != NULL )
            {
              /* 引数をダミーデバイスとして終了 */
              ptDEVICE_DUMMY = ptDetDevice;
              ptDetDevice = NULL;
            }
          else
            {
              /* 新たにダミーデバイスを作成する */
              /* デバイス管理用構造体メモリ確保 */
              ptDevice = usb_USBC_ptAllocDevice();
              ERROR_IF( ptDevice == NULL, EXT );

              /* デバイス登録 */
              iRet = usb_USBC_iRegistDeviceDriver( blAttachDevice, vDetachDevice, ptDevice, NULL );
              ERROR_IF( iRet != USBC_OK, EXT );
              ptDEVICE_DUMMY = ptDevice;
              ptDevice = NULL;
            }
        }
    }

 EXT:
  /* 無用なデバイスの登録解除 & メモリ解放 */
  if( ptDetDevice != NULL )
    {
      iRet = usb_USBC_iRemoveDeviceDriver( ptDetDevice, NULL );
      if( iRet == USBC_OK )
        usb_USBC_vFreeDevice( ptDetDevice );
      else
        {
          DEBUG_ERROR_CALL( 0, "Illegal Dummy Device", NULL );
        }
    }
  if( ptDevice )
    usb_USBC_vFreeDevice( ptDevice );
}


/* インターフェース対応クラスドライバ検索 */
static bool blSearchInterfaceDriver( USBC_typeDevice* ptDevice, usb_config_descriptor_t* ptDescCfg,
                                     usb_interface_descriptor_t* ptDescIface )
{
  bool blDetect = false, blRet = false;
  USBC_typeInterface* ptInterface = NULL;

  USB_TRACE_ENTER( 1, blSearchInterfaceDriver );

  /* 登録されているインターフェースリストから検索 (for文) */
  SLIST_FOREACH( ptInterface, USBC_typeInterface, &tINTERFACE_LIST )
    {
      /* 必要なパラメータの仮設定 */
      ptInterface->ptDevice = ptDevice;
      ptInterface->ptDescCfg = ptDescCfg;
      ptInterface->ptDescIface = ptDescIface;

      /* インターフェース接続通知 */
      if( ptInterface->blAttachInterface != NULL )  /* 2006/06/08 修正 田谷 追加 */
        blRet = ptInterface->blAttachInterface( ptInterface );
      if( blRet == false )
        /* 対象デバイスでなければ、仮設定を解除して検索継続 */
        {
          ptInterface->ptDevice = NULL;
          ptInterface->ptDescCfg = NULL;
          ptInterface->ptDescIface = NULL;
        }
      else
        /* 対応するインターフェースを発見し次第終了 */
        {
          /* 登録リストから削除 */
          SLIST_REMOVE( &tINTERFACE_LIST, ptInterface );

          /* デバイス管理構造体にインターフェースを追加 */
          SLIST_INSERT_TAIL( &ptDevice->tInterface, ptInterface );

          blDetect = true;
          break;
        }
    }

  USB_TRACE_LEAVE( 1, blSearchInterfaceDriver );
  return( blDetect );
}



/* コンフィギュレーション対応クラスドライバ検索 */
static bool blSearchCofigDriver( USBC_typeDevice* ptDevice, usb_config_descriptor_t* ptDescCfg )
{
  int16_t iRet;
  uint8_t ucIfaceNum;
  bool blRet, blDetect = false;
  usb_interface_descriptor_t* ptDescIface = NULL;

  USB_TRACE_ENTER( 1, blSearchCofigDriver );

  for( ucIfaceNum = 0; ucIfaceNum < ptDescCfg->bNumInterfaces; ucIfaceNum++ )
    {
      /* インターフェースディスクリプタ取得 */
      iRet = usb_USBD_iGetInterfaceDescriptor( ptDevice->ulIdDev, ucIfaceNum, &ptDescIface, NULL );
      if( iRet != USB_OK )
        {
          DEBUG_ERROR_CALL( 0, "USBC:iIdentifyConfiguration", NULL );
          continue;
        }

      /* インターフェース対応クラスドライバ検索 */
      blRet = blSearchInterfaceDriver( ptDevice, ptDescCfg, ptDescIface );
      if( blRet != false )
        blDetect = true;
    }

  USB_TRACE_LEAVE( 1, blSearchCofigDriver );
  return( blDetect );
}


/* デバイス対応クラスドライバ検索 */
static bool blSearchDeviceDriver( USBC_typeDevice* ptDevice )
{
  int16_t iRet;
  int16_t i;
  bool blDetect = false;
  usb_device_descriptor_t* ptDescDev = ptDevice->ptDescDev;
  usb_config_descriptor_t* ptDescCfg = NULL;

  USB_TRACE_ENTER( 1, blSearchDeviceDriver );

  /* デバイスオープン */
  iRet = usb_USBD_iOpenDevice( ptDevice->ulIdDev, NULL );
  ERROR_IF( iRet != USB_OK, EXT1 );

  for( i = 0; i < ptDescDev->bNumConfigurations; i++ )
    {
      /* コンフィギュレーションディスクリプタ取得 */
      /* 取得すると同時に、デバイスのコンフィギュレーションが変更される *//* 20060731 無用なキャストを削除 */
      iRet = usb_USBD_iGetConfigDescriptor( ptDevice->ulIdDev, i, &ptDescCfg, NULL );
      ERROR_IF( iRet != USB_OK, EXT2 );

      /* コンフィギュレーション対応クラスドライバ検索 */
      /* 番号の若いコンフィギュレーションを優先して使う */
      blDetect = blSearchCofigDriver( ptDevice, ptDescCfg );
      if( blDetect != false )
        break;
    }

 EXT2:
  /* 対応するドライバが登録されていなければデバイスクローズ */
  if( blDetect == false )
    usb_USBD_iCloseDevice( ptDevice->ulIdDev, NULL );

 EXT1:
  USB_TRACE_LEAVE( 1, blSearchDeviceDriver );
  return( blDetect );
}



/*
  デバイス接続時コールバック関数 (インターフェース単位での登録時に使用)
*/
static bool blAttachDevice( uint32_t ulIdDev, uint32_t ulArg )
{
  int16_t iRet, sError = USBD_NORMAL_COMPLETION;
  bool blDetect = false;
  USBC_typeDevice* ptDevice = (USBC_typeDevice*)ulArg;

  USB_TRACE_ENTER( 0, blAttachDevice );

  ERROR_IF( ptDevice == NULL, EXT );

  ptDevice->ulIdDev = ulIdDev;

  /* デバイスディスクリプタ取得 */
  iRet = usb_USBD_iGetDeviceDescriptor( ulIdDev, &ptDevice->ptDescDev, &sError );
  ERROR_IF( iRet != USB_OK, EXT );

  /* デバイス対応クラスドライバ検索 */
  blDetect = blSearchDeviceDriver( ptDevice );
  ERROR_IF( blDetect == false, EXT );

  /* ダミーデバイス管理 */
  vManageDummyDevice( ptDevice, NULL );

  USB_TRACE_LEAVE( 0, blAttachDevice );
  return( true );
 EXT:
  if( sError != USBD_NORMAL_COMPLETION )
    {
      DEBUG_ERROR_CALL( 0, "USBC:blAttachDevice", &sError);
    }
  USB_TRACE_LEAVE( 0, blAttachDevice );
  return( false );
}


/*
  デバイス解除時コールバック関数 (インターフェース単位での登録時に使用)
*/
static void vDetachDevice( uint32_t ulArg )
{
  int16_t iRet;
  USBC_typeDevice* ptDevice = (USBC_typeDevice*)ulArg;
  USBC_typeInterface* ptInterface;

  USB_TRACE_ENTER( 0, vDetachDevice );

  ERROR_IF( ptDevice == NULL, EXT );

  /* デバイス内のインターフェース */
  while( (ptInterface = (USBC_typeInterface*)SLIST_REMOVE_HEAD( &ptDevice->tInterface )) != NULL )
    {
      /* インターフェース解除 */
      if( ptInterface->vDetachInterface != NULL )
        ptInterface->vDetachInterface( ptInterface );

      ptInterface->ptDevice = NULL;
      ptInterface->ptDescCfg = NULL;
      ptInterface->ptDescIface = NULL;

      /* インターフェース登録リストに追加 */
      SLIST_INSERT_HEAD( &tINTERFACE_LIST, ptInterface );
    }

  /* デバイスクローズ */
  usb_USBD_iCloseDevice( ptDevice->ulIdDev, NULL );

  ptDevice->ulIdDev = 0;
  ptDevice->ptDescDev = NULL;
  ptDevice->ptDescStr = NULL;

  /* ダミーデバイス管理 */
  vManageDummyDevice( NULL, ptDevice);

  USB_TRACE_LEAVE( 0, vDetachDevice );
  return;
 EXT:
  DEBUG_ERROR_CALL( 0, "USBC:vDetachDevice", NULL );
  USB_TRACE_LEAVE( 0, vDetachDevice );
}


/* ========== GLOBAL FUNCTIONS ========== */

/*
  クラスドライバ初期化
*/
void usb_USBC_vInitialize( void )
{
  SLIST_INIT( &tINTERFACE_LIST );

  ptDEVICE_DUMMY = NULL;

  /* メモリ初期化 */
  usb_USBC_vInitMemory();

  usb_USBC_vInitUnionBlock();
}


/*
  デバイス単位のクラスドライバ登録
    引数
      blAttDevFn  デバイス接続時コールバック関数
      vDetDevFn   デバイス解除時コールバック関数
      ptDevice    デバイス管理用構造体
      psError     エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_USBC_iRegistDeviceDriver( USBC_fpAttachDevice blAttDevFn, USBC_fpDetachDevice vDetDevFn,
                                  USBC_typeDevice* ptDevice, int16_t* psError )
{
  int16_t iRet;
  USBD_typeClassDriver* ptClsDrv = NULL;

  USB_TRACE_ENTER( 0, usb_USBC_iRegistDeviceDriver );

  /* 引数チェック */
  ERROR_IF_WITHCODE( blAttDevFn == NULL || vDetDevFn == NULL || ptDevice == NULL, EXT, psError, USBD_INVAL );

  /* クラスドライバ管理用構造体メモリ確保 */
  ptClsDrv = usb_USBD_ptAllocClassDriver();
  ERROR_IF_WITHCODE( ptClsDrv == NULL, EXT, psError, USBD_NOMEM );

  ptDevice->ptClsDrv = ptClsDrv;
  SLIST_INIT( &ptClsDrv->queue );
  ptClsDrv->ulArg = (uint32_t)ptDevice;
  ptClsDrv->blAttachDeviceFn = blAttDevFn;
  ptClsDrv->vDetachDeviceFn = vDetDevFn;

  /* クラスドライバ登録 */
  iRet = usb_USBD_iRegistClassDriver( ptClsDrv, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  USB_TRACE_LEAVE( 0, usb_USBC_iRegistDeviceDriver );
  return( USBC_OK );

 EXT:
  /* メモリ解放 */
  if( ptClsDrv != NULL )  usb_USBD_vFreeClassDriver( ptClsDrv );

  DEBUG_ERROR_CALL( 0, "usb_USBC_iRegistDeviceDriver", psError );
  USB_TRACE_LEAVE( 0, usb_USBC_iRegistDeviceDriver );
  return( USBC_NG );
}


/*
  インターフェース単位のクラスドライバ登録
    引数
      ptInterface インターフェース管理用構造体
      psError     エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_USBC_iRegistInterfaceDriver( USBC_typeInterface* ptInterface, int16_t* psError )
{
  int16_t iRet;

  USB_TRACE_ENTER( 0, USBC_iRegistInterfaceDriver );

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptInterface == NULL, EXT, psError, USBD_INVAL);

  /* インターフェースリスト追加 */
  SLIST_INSERT_TAIL( &tINTERFACE_LIST, ptInterface );

  /* ダミーデバイス管理 */
  vManageDummyDevice( NULL, NULL );

  USB_TRACE_LEAVE( 0, USBC_iRegistInterfaceDriver );
  return( USBC_OK );

 EXT:

  DEBUG_ERROR_CALL( 0, "USBC_iRegistInterfaceDriver", psError );
  USB_TRACE_LEAVE( 0, USBC_iRegistInterfaceDriver );
  return( USBC_NG );
}


/*
  デバイス単位のクラスドライバ登録解除
    引数
      ptDevice    デバイス管理用構造体
      psError     エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_USBC_iRemoveDeviceDriver( USBC_typeDevice* ptDevice, int16_t* psError )
{
  int16_t iRet;
  USBD_typeClassDriver* ptClsDrv;

  USB_TRACE_ENTER( 0, usb_USBC_iRemoveDeviceDriver );

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptDevice == NULL || ptDevice->ptClsDrv == NULL, EXT, psError, USBD_INVAL );

  ptClsDrv = ptDevice->ptClsDrv;

  /* クラスドライバ登録解除 */
  iRet = usb_USBD_iRemoveClassDriver( ptClsDrv, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  /* クラスドライバ管理用構造体メモリ解放 */
  usb_USBD_vFreeClassDriver( ptClsDrv );
  ptDevice->ptClsDrv = NULL;

  USB_TRACE_LEAVE( 0, usb_USBC_iRemoveDeviceDriver );
  return( USBC_OK );

 EXT:
  DEBUG_ERROR_CALL( 0, "usb_USBC_iRemoveDeviceDriver", psError );
  USB_TRACE_LEAVE( 0, usb_USBC_iRemoveDeviceDriver );
  return( USBC_NG );
}


/*
  インターフェース単位のクラスドライバ登録解除
    引数
      ptInterface インターフェース管理用構造体
      psError     エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_USBC_iRemoveInterfaceDriver( USBC_typeInterface* ptInterface, int16_t* psError )
{
  int16_t iRet;

  USB_TRACE_ENTER( 0, usb_USBC_iRemoveInterfaceDriver );

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptInterface == NULL, EXT, psError, USBD_INVAL );

  if( ptInterface->ptDevice != NULL )
    /* Attach状態 */
    {
      SET_ERRORCODE( psError, USBD_IN_USE );
      goto EXT;
    }
  else
    /* 非Attach状態 */
    {
      /* インターフェース登録リストから除去 */
      SLIST_REMOVE( &tINTERFACE_LIST, ptInterface );

      /* ダミーデバイス管理 */
      vManageDummyDevice( NULL, NULL );
    }

  USB_TRACE_LEAVE( 0, usb_USBC_iRemoveInterfaceDriver );
  return( USBC_OK );

 EXT:
  DEBUG_ERROR_CALL( 0, "USBC_iRemoveInterfaceDriver", psError );
  USB_TRACE_LEAVE( 0, usb_USBC_iRemoveInterfaceDriver );
  return( USBC_NG );
}

/* --- End of File --- */
