/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_msc_core.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Mass Storage Class Driver Core

*/

#include <string.h>
#include "usb_classdrv.h"
#include "usb_classdrvmem.h"
#include "usb_classdrvblock.h"
#include "usb_msc_core.h"
#include "usb_mscbbb.h"
#include "usb_msccbi.h"
#include "usb_intr.h"

/* ========== local functions ========== */

/*
  デバイス接続時に呼び出されるコールバック関数
    引数 - ptInterface: インターフェース管理用構造体, ptDescIface: インターフェースディスクリプタ
    戻値 - true: 対象デバイス  false: 対象ではない
*/
static bool blAttachMscInterface( USBC_typeInterface* ptIface )
{
  int16_t  iRet;
  bool blRet;
  usb_interface_descriptor_t* ptDescIface;
  int16_t  (*iFinalize)( USBC_typeInterface*, int16_t * );
  iFinalize = NULL;

  USB_TRACE_ENTER( 1, blAttachMscInterface );

  /* インターフェースディスクリプタから、対応するクラスか否か判別する */

  /* 引数チェック */
  ERROR_IF( ptIface == NULL, EXT );

  /* Mass Storage Class */
  ptDescIface = ptIface->ptDescIface;
  ERROR_IF( ptDescIface == NULL || ptDescIface->bInterfaceClass != MSC_CLASS_CODE, EXT );

  /* -- インターフェース初期化 -- */
  /* 対応 SubClass = SCSI or ATAPI */
  if( ptDescIface->bInterfaceSubClass == MSC_SUBCLASS_SCSI ||
      ptDescIface->bInterfaceSubClass == MSC_SUBCLASS_SFF8070I )
    {
      /* Bulk-Only Transport */
      if( ptDescIface->bInterfaceProtocol == MSC_PROTOCOL_BBB )
        {
          iRet = usb_MSC_BBB_iInitialize( ptIface, NULL );
          ERROR_IF( iRet != MSC_OK, EXT );
          iFinalize = usb_MSC_BBB_iFinalize;
        }
      /* CBI Transport */
      else if( ptDescIface->bInterfaceProtocol == MSC_PROTOCOL_CBI_CCI ||
                ptDescIface->bInterfaceProtocol == MSC_PROTOCOL_CBI_NOCCI )
        {
          iRet = usb_MSC_CBI_iInitialize( ptIface, NULL );
          ERROR_IF( iRet != MSC_OK, EXT );
          iFinalize = usb_MSC_CBI_iFinalize;
        }
      else
        {
          goto EXT;
        }
    }
  else
    {
      goto EXT;
    }

  /* アプリケーションのコールバック呼び出し */
  if( ptIface->tCallbacks.blAttach != NULL )
    {
      blRet = ptIface->tCallbacks.blAttach( ptIface->tCallbacks.ulArg );
      ERROR_IF( blRet == false, EXT );
    }

  USB_TRACE_LEAVE( 1, blAttachMscInterface );
  return( true );
 EXT:
  /* インターフェース終了処理 */
  if( iFinalize != NULL )
    iFinalize( ptIface, NULL );

  USB_TRACE_LEAVE( 1, blAttachMscInterface );
  return( false );
}


/*
  デバイス解除時に呼び出されるコールバック関数
    引数 - ptInterface: インターフェース管理用構造体
    戻値 - なし
*/
static void vDetachMscInterface( USBC_typeInterface* ptIface )
{
  USB_TRACE_ENTER( 1, vDetachMscInterface );

  ERROR_IF( ptIface == NULL || ptIface->ptDescIface == NULL, EXT );

  /* クラスドライバ終了処理 */
  switch( ptIface->ptDescIface->bInterfaceProtocol )
    {
    /* Bulk-Only Transport */
    case MSC_PROTOCOL_BBB:
      usb_MSC_BBB_iFinalize( ptIface, NULL );
      break;

    /* CBI Transport */
    case MSC_PROTOCOL_CBI_CCI:
    case MSC_PROTOCOL_CBI_NOCCI:
      usb_MSC_CBI_iFinalize( ptIface, NULL );
      break;

    default:
      DEBUG_ERROR_CALL( 0, "vDetachMscInterface", NULL );
    }

  /* アプリケーションに通知 */
  if( ptIface->tCallbacks.vDetach )
    ptIface->tCallbacks.vDetach( ptIface->tCallbacks.ulArg );

 EXT:
  USB_TRACE_LEAVE( 1, vDetachMscInterface );
}



/* ========== GLOBAL FUNCTIONS ========== */

/*
  Mass Storage Class ドライバ使用開始
    引数
      ptCallbacks   コールバック関数群
      pulIdMsc      MSCデバイスID設定先
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: OK, MSC_NG: NG
*/
int16_t  usb_MSC_CORE_iOpen( USBC_typeCallbacks* ptCallbacks, uint32_t* pulIdMsc, int16_t * psError )
{
  int16_t  iRet;
  USBC_typeInterface* ptIface = NULL;

  USB_TRACE_ENTER( 0, usb_MSC_CORE_iOpen );

  /* 割り込み禁止 */
  USB_DIS_INTR();

  /* 引数チェック */
  ERROR_IF_WITHCODE( (pulIdMsc == NULL), EXT, psError, USB_MSC_PARAMETER );

  /* インターフェース管理用構造体メモリ確保 */
  ptIface = usb_USBC_ptAllocInterface();
  ERROR_IF_WITHCODE( (ptIface == NULL), EXT, psError, USB_MSC_NOMEM );

  /* コールバック関数群セット */
  ptIface->blAttachInterface = blAttachMscInterface;
  ptIface->vDetachInterface = vDetachMscInterface;
  if( ptCallbacks != NULL )
    memcpy( &ptIface->tCallbacks, ptCallbacks, sizeof(USBC_typeCallbacks) );

  /* MSC ドライバ登録 */
  iRet = usb_USBC_iRegistInterfaceDriver( ptIface, psError );
  ERROR_IF( iRet != USBC_OK, EXT );

  /* 戻り ID */
  *pulIdMsc = (uint32_t)ptIface;

  /* 割り込み許可 */
  USB_ENA_INTR();

  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iOpen );
  return( MSC_OK );
 EXT:

  /* メモリ解放 */
  if( ptIface != NULL )  usb_USBC_vFreeInterface( ptIface );

  USB_ENA_INTR();

  DEBUG_ERROR_CALL( 0, "MSC_iOpen", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iOpen );
  return( MSC_NG );
}


/*
  Mass Storage Class ドライバ使用終了
    引数
      ulIdMsc       MSCデバイスID
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: OK, MSC_NG: NG
*/
int16_t  usb_MSC_CORE_iClose( uint32_t ulIdMsc, int16_t * psError )
{
  int16_t  iRet;
  USBC_typeInterface* ptIface = (USBC_typeInterface*)ulIdMsc;

  USB_TRACE_ENTER( 0, usb_MSC_CORE_iClose );

  /* 割り込み禁止 */
  USB_DIS_INTR();

  /* 引数チェック */
  ERROR_IF_WITHCODE( (ulIdMsc == 0), EXT, psError, USB_MSC_PARAMETER );

  /* MSC ドライバ登録解除 */
  iRet = usb_USBC_iRemoveInterfaceDriver( ptIface, psError );
  ERROR_IF( iRet != USBC_OK, EXT );
  usb_USBC_vFreeInterface( ptIface );

  /* 割り込み許可 */
  USB_ENA_INTR();

  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iClose );
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "MSC_iClose", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iClose );
  return( MSC_NG );
}


/*
  Mass Storage リセット復旧
    引数
      ulIdMsc       MSCデバイスID
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: OK, MSC_NG: NG
*/
int16_t  usb_MSC_CORE_iResetRecovery( uint32_t ulIdMsc, int16_t * psError )
{
  int16_t  iRet;
  USBC_typeInterface* ptIface = (USBC_typeInterface*)ulIdMsc;

  USB_TRACE_ENTER( 0, usb_MSC_CORE_iResetRecovery );

  /* 割り込み禁止 */
  USB_DIS_INTR();

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptIface == NULL, EXT, psError, USB_MSC_PARAMETER );
  ERROR_IF_WITHCODE( ptIface->ptDescIface == NULL, EXT, psError, USB_MSC_NO_DEVICE );

  /* 通信キャンセル */
  iRet = usb_USBD_iCancelIoInterface( ptIface->ulIdIface, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  switch( ptIface->ptDescIface->bInterfaceProtocol )
    {
    /* Bulk-Only Transport */
    case MSC_PROTOCOL_BBB:
      iRet = usb_MSC_BBB_iReset( ptIface, psError);
      ERROR_IF( iRet != MSC_OK, EXT );
      break;

    /* CBI Transport */
    case MSC_PROTOCOL_CBI_CCI:
    case MSC_PROTOCOL_CBI_NOCCI:
      iRet = usb_MSC_CBI_iReset( ptIface, psError );
      ERROR_IF( iRet != MSC_OK, EXT );
      break;

    default:
      SET_ERRORCODE( psError, USB_MSC_PARAMETER );
      goto EXT;
    }

  /* パラメータ初期化 */
  if( ptIface->pvBuffer != NULL )
    usb_USBC_vFreeUnionBlock( ptIface->pvBuffer );
  ptIface->pvBuffer = NULL;
  ptIface->ucRetryCount = 0;
  ptIface->ucAddedStatus = 0;
  ptIface->ucState = MSC_STAT_READY;

  /* 割り込み許可 */
  USB_ENA_INTR();

  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iResetRecovery );
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "MSC_iResetRecovery", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iResetRecovery );
  return( MSC_NG );
}


/*
  SCSI コマンド発行
    コマンドの実行完了はコールバック USBC_typeCallbacks.vDone() で知らされる
    引数
      ulIdMsc       デバイスID
      ptCmdBlk      コマンドブロック
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: OK, MSC_NG: NG
*/
int16_t  usb_MSC_CORE_iSCSICommand( uint32_t ulIdMsc, usb_MSC_typeCommandBlock* ptCmdBlk, int16_t * psError )
{
  int16_t  iRet;
  USBC_typeInterface* ptIface = (USBC_typeInterface*)ulIdMsc;

  USB_TRACE_ENTER( 0, usb_MSC_CORE_iSCSICommand );

  /* 割り込み禁止 */
  USB_DIS_INTR();

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptIface == NULL || ptCmdBlk == NULL, EXT, psError, USB_MSC_PARAMETER );
  ERROR_IF_WITHCODE( ptIface->ptDescIface == NULL, EXT, psError, USB_MSC_NO_DEVICE );

  /* コマンドブロックチェック */
  ERROR_IF_WITHCODE( ptCmdBlk->ucCmdSize > 16, EXT, psError, USB_MSC_PARAMETER );

  switch( ptIface->ptDescIface->bInterfaceProtocol )
    {
    /* Bulk-Only Transport */
    case MSC_PROTOCOL_BBB:
      iRet = usb_MSC_BBB_iSCSICommand( ptIface, ptCmdBlk, psError);
      ERROR_IF( iRet != MSC_OK, EXT );
      break;

    /* CBI Transport */
    case MSC_PROTOCOL_CBI_CCI:
    case MSC_PROTOCOL_CBI_NOCCI:
      iRet = usb_MSC_CBI_iSCSICommand( ptIface, ptCmdBlk, psError );
      ERROR_IF( iRet != MSC_OK, EXT );
      break;

    default:
      SET_ERRORCODE( psError, USB_MSC_PARAMETER );
      goto EXT;
    }

  /* 割り込み許可 */
  USB_ENA_INTR();

  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iSCSICommand );
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "MSC_iSCSICommand", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iSCSICommand );
  return( MSC_NG );
}


/*
  SCSI Command キャンセル
    引数
      ulIdMsc       デバイスID
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: OK, MSC_NG: NG
*/
int16_t usb_MSC_CORE_iCancelCommand( uint32_t ulIdMsc, int16_t* psError )
{
  int16_t iRet;
  USBC_typeInterface* ptIface = (USBC_typeInterface*)ulIdMsc;

  /* 割り込み禁止 */
  USB_DIS_INTR();

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptIface == NULL, EXT, psError, USB_MSC_PARAMETER );
  ERROR_IF_WITHCODE( ptIface->ulIdIface == 0, EXT, psError, USB_MSC_NO_DEVICE );

  /* インターフェース単位の転送キャンセル */
  iRet = usb_USBD_iCancelIoInterface( ptIface->ulIdIface, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  /* 割り込み許可 */
  USB_ENA_INTR();
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "usb_MSC_CORE_iCancelCommand", psError );
  return( MSC_NG );
}


/*
  最大論理ユニット番号取得
*/
int16_t  usb_MSC_CORE_iGetMaxLUN( uint32_t ulIdMsc, uint8_t* pucMaxLun, int16_t * psError )
{
  int16_t  iRet;
  USBC_typeInterface* ptIface = (USBC_typeInterface*)ulIdMsc;

  USB_TRACE_ENTER( 0, usb_MSC_CORE_iGetMaxLUN );

  /* 割り込み禁止 */
  USB_DIS_INTR();

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptIface == NULL || pucMaxLun == NULL, EXT, psError, USB_MSC_PARAMETER );
  ERROR_IF_WITHCODE( ptIface->ptDescIface == NULL, EXT, psError, USB_MSC_NO_DEVICE );

  switch( ptIface->ptDescIface->bInterfaceProtocol )
    {
    /* Bulk-Only Transport */
    case MSC_PROTOCOL_BBB:
      iRet = usb_MSC_BBB_iGetMaxLUN( ptIface, pucMaxLun, psError );
      ERROR_IF( iRet != MSC_OK, EXT );
      break;

    /* CBI Transport */
    case MSC_PROTOCOL_CBI_CCI:
    case MSC_PROTOCOL_CBI_NOCCI:
      *pucMaxLun = 0;
      break;

    default:
      SET_ERRORCODE( psError, USB_MSC_PARAMETER );
      goto EXT;
    }

  /* 割り込み許可 */
  USB_ENA_INTR();

  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iGetMaxLUN );
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "MSC_iGetMaxLUN", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_CORE_iGetMaxLUN );
  return( MSC_NG );
}



/* --- End of File --- */
