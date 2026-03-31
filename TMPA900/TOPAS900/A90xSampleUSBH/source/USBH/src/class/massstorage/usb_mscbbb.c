/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_mscbbb.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Mass Storage Class Bulk-Only Transport

*/

#include <string.h>
#include "usb_tmr.h"
#include "usb_classdrv.h"
#include "usb_classdrvblock.h"
#include "usb_mscbbb.h"
#include "usb_classdrvmem.h"

/* ========== local functions ========== */

static int16_t sBBBCommandTransferred( USBC_typeInterface * ptIface, int16_t sStatus );
static int16_t sBBBDataTransferred( USBC_typeInterface * ptIface, int16_t sStatus );
static int16_t sBBBStatusTransferred( USBC_typeInterface * ptIface, void* pvBuffer, uint16_t usLength, int16_t sStatus );


/*
  CBW 作成
*/
static void vSetCbw( MSC_BBB_typeCBW* ptCbw, uint32_t ulTag, uint16_t usDataLen,
                     uint8_t ucFlags, uint8_t ucLun, uint8_t ucLength )
{
  USB_TRACE_ENTER( 3, vSetCbw );

  memset( ptCbw, 0, sizeof(MSC_BBB_typeCBW) );

  ptCbw->dCBWSignature = MSC_BBB_CBW_SIGNATURE;
  ptCbw->dCBWTag = ulTag;
  ptCbw->dCBWDataTransferLength = usDataLen;
  ptCbw->bmCBWFlags = ( ucFlags == USB_MSC_DIR_IN ) ? MSC_BBB_DIR_IN : MSC_BBB_DIR_OUT;
  ptCbw->bCBWLUN = ucLun;
  ptCbw->bCBWCBLength = ucLength;

  USB_TRACE_LEAVE( 3, vSetCbw );
}


/*
  コマンドブロック転送 (コマンド実行開始)
    dCBWTag に バッファアドレスを設定しておく必要あり
*/
static int16_t iTransferCbw( USBC_typeInterface* ptIface, MSC_BBB_typeCBW* ptCbw, int16_t* psError )
{
  int16_t iRet;

  USB_TRACE_ENTER( 1, iTransferCbw );

  /* 現状態チェック */
  ERROR_IF_WITHCODE( ptIface->ucState != MSC_STAT_READY, EXT_STAT_ERR, psError, USB_MSC_IN_USE );

  /* 状態遷移 */
  ptIface->ucState = MSC_STAT_COMMAND;

  /* コマンド転送実行 */
  iRet = usb_USBD_iIoPipe( ptIface->pulIdEp[MSC_BBB_BO], ptCbw, MSC_BBB_CBW_SIZE, 0, psError );
  if( iRet != USB_OK )
    {
      /* リセット復旧 */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      if( iRet != MSC_OK )
        {
          SET_ERRORCODE( psError, USB_MSC_DEVICE_ABNORMAL );
        }
      goto EXT;
    }

  USB_TRACE_LEAVE( 1, iTransferCbw );
  return( MSC_OK );
 EXT:
  /* 状態復帰 */
  ptIface->ucState = MSC_STAT_READY;

 EXT_STAT_ERR:
  DEBUG_ERROR_CALL( 0, "BBB:iTransferCbw", psError );
  USB_TRACE_LEAVE( 1, iTransferCbw );
  return( MSC_NG );
}


/* --- 転送完了時コールバック処理 --- */

/*
  コマンド転送完了時処理
*/
static int16_t sBBBCommandTransferred( USBC_typeInterface* ptIface, int16_t sStatus )
{
  int16_t iRet, sRetStat = MSC_STATUS_DRIVER_ERROR, sError = 0;
  MSC_BBB_typeCBW* ptCbw = &((MSC_BBB_typeBlock*)ptIface->pvBuffer)->tCbw;

  USB_TRACE_ENTER( 1, sBBBCommandTransferred );

  /* 転送ステータスチェック */
  switch( sStatus )
    {
    case USBD_NORMAL_COMPLETION:
      /* コマンド転送正常終了 */
      /* データフェイズに状態遷移 */
      ptIface->ucState = MSC_STAT_DATA;

      /* リトライ回数初期化 */
      ptIface->ucRetryCount = 0;
      break;

    case USBD_STALLED:
      /* Bulk-OUT で STALL 発生 */
      /* リセット復旧 */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      ERROR_IF_WITHCODE( iRet != MSC_OK, EXT, &sRetStat, MSC_STATUS_FATAL_ERROR );

      /* リトライ実行 */
      if( ptIface->ucRetryCount >= MSC_BBB_CBW_MAX_RETRY )
        {
          /* リトライ回数上限オーバー */
          sRetStat = MSC_STATUS_IO_ERROR;
          goto EXT;
        }
      else
        /* リトライ */
        {
          /* コマンド再転送 */
          iRet = iTransferCbw( ptIface, ptCbw, &sError );
          if( iRet != MSC_OK )
            {
              sRetStat = ( sError == USB_MSC_DEVICE_ABNORMAL ) ? MSC_STATUS_FATAL_ERROR : MSC_STATUS_IO_ERROR;
              goto EXT;
            }
          ptIface->ucRetryCount++;
        }
      /* リトライ時はこの関数を正常終了する */
      goto EXT_RETRY;

    case USBD_TIMEOUT:
      /* 転送タイムアウト */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_TIMEOUT : MSC_STATUS_FATAL_ERROR;
      goto EXT;

    case USBD_CANCELLED:
      /* 転送キャンセル */
      usb_MSC_BBB_iReset( ptIface, NULL );
      sRetStat = MSC_STATUS_CANCELLED;
      goto EXT;

    case USBD_IOERROR:
    default:
      /* その他エラー */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_IO_ERROR : MSC_STATUS_FATAL_ERROR;
      goto EXT;
    }

  /* もし転送データが存在する場合 */
  if( ptCbw->dCBWDataTransferLength > 0 )
    /* データ転送実行 */
    {
      int16_t iDirectory;
      uint16_t usFlags;

      /* データ転送方向によるエンドポイントの決定 */
      iDirectory = ( ptCbw->bmCBWFlags & MSC_BBB_DIR_IN ) ? MSC_BBB_BI : MSC_BBB_BO;

      /* データ転送方向によるフラグの決定 */
      usFlags = ( ptCbw->bmCBWFlags & MSC_BBB_DIR_IN ) ? USBD_SHORT_XFER_OK : 0;

      /* データ転送開始 */
      iRet = usb_USBD_iIoPipe( ptIface->pulIdEp[iDirectory], 
                               (void*)ptCbw->dCBWTag, (uint16_t)ptCbw->dCBWDataTransferLength,
                               usFlags, NULL );
      if( iRet != USB_OK )
        {
          iRet = usb_MSC_BBB_iReset( ptIface, NULL );
          sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_IO_ERROR : MSC_STATUS_FATAL_ERROR;
          goto EXT;
        }
    }
  else
    /* 存在しない場合は、データ転送完了後の処理を開始 */
    {
      /* データ転送完了 */
      sRetStat = sBBBDataTransferred( ptIface, USBD_NORMAL_COMPLETION );
      ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
    }

 EXT_RETRY:
  USB_TRACE_LEAVE( 1, sBBBCommandTransferred );
  return( MSC_STATUS_COMMAND_PASSED );
 EXT:
  DEBUG_ERROR_CALL( 1, "BBB:sBBBCommandTransferred", &sRetStat );
  USB_TRACE_LEAVE( 1, sBBBCommandTransferred );
  return( sRetStat );
}


/*
  データ転送完了時処理
*/
static int16_t sBBBDataTransferred( USBC_typeInterface* ptIface, int16_t sStatus )
{
  int16_t iRet, sRetStat = MSC_STATUS_DRIVER_ERROR;
  MSC_BBB_typeBlock* ptBlock = ptIface->pvBuffer;

  USB_TRACE_ENTER( 1, sBBBDataTransferred );

  /* データ転送の成否に関わらず、ステータスフェイズに状態遷移 */
  ptIface->ucState = MSC_STAT_STATUS;

  /* リトライ回数初期化 */
  ptIface->ucRetryCount = 0;

  switch( sStatus )
    {
    case USBD_NORMAL_COMPLETION:
      /* データ転送正常終了 */
      break;

    case USBD_TIMEOUT:
      /* 転送タイムアウト */
      ptIface->ucAddedStatus = MSC_STATUS_TIMEOUT;
      break;

    case USBD_CANCELLED:
      /* 転送キャンセル */
      ptIface->ucAddedStatus = MSC_STATUS_CANCELLED;

      /* リセットして終了 */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_CANCELLED : MSC_STATUS_FATAL_ERROR;
      goto EXT;

    case USBD_STALLED:
      {
        /* 発生した STALL を解除 */
        int16_t iDirectory = ( ptBlock->tCbw.bmCBWFlags & MSC_BBB_DIR_IN ) ? MSC_BBB_BI : MSC_BBB_BO;
        iRet = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[iDirectory], NULL );
        ERROR_IF_WITHCODE( iRet != USB_OK, EXT, &sRetStat, MSC_STATUS_FATAL_ERROR );
      }
      /* break しないで default の処理を続けて実行する*/

    default:
      /* その他エラー */
      /* データでエラーが発生したことを記録 */
      ptIface->ucAddedStatus = MSC_STATUS_IO_ERROR;
    }


  /* ステータス受信開始 */
  iRet = usb_USBD_iIoPipe( ptIface->pulIdEp[MSC_BBB_BI],
                           &ptBlock->tCsw, MSC_BBB_CSW_SIZE, 0, NULL );
  if( iRet != USB_OK )
    {
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_IO_ERROR : MSC_STATUS_FATAL_ERROR;
      goto EXT;
    }

  USB_TRACE_LEAVE( 1, sBBBDataTransferred );
  return( MSC_STATUS_COMMAND_PASSED );
 EXT:
  DEBUG_ERROR_CALL( 0, "BBB:sBBBDataTransferred", &sRetStat );
  USB_TRACE_LEAVE( 1, sBBBDataTransferred );
  return( sRetStat );
}


/*
  ステータス転送完了時処理
*/
static int16_t sBBBStatusTransferred( USBC_typeInterface* ptIface, void* pvBuffer, uint16_t usLength, int16_t sStatus )
{
  int16_t iRet, sRetStat = MSC_STATUS_DRIVER_ERROR;
  MSC_BBB_typeBlock* ptBlock = ptIface->pvBuffer;
  MSC_BBB_typeCBW* ptCbw = &ptBlock->tCbw;
  MSC_BBB_typeCSW* ptCsw = &ptBlock->tCsw;
  MSC_typeResult tRes = { 0, 0, 0 };

  USB_TRACE_ENTER( 1, sBBBStatusTransferred );

  /* 結果作成 */
  tRes.ucSCSICmd = ptCbw->CBWCB[0];
  tRes.pucBuffer = (void*)ptCbw->dCBWTag;
  tRes.usSize = (uint16_t)(ptCbw->dCBWDataTransferLength - ptCsw->dCSWDataResidue);

  switch( sStatus )
    {
    case USBD_NORMAL_COMPLETION:
      /* ステータス転送正常終了 */
      /* 待機フェイズに状態遷移 */
      ptIface->ucState = MSC_STAT_READY;
      break;

    case USBD_TIMEOUT:
      /* 転送タイムアウト */
      /* リセットして終了 */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_TIMEOUT : MSC_STATUS_FATAL_ERROR;
      goto EXT;

    case USBD_CANCELLED:
      /* 転送キャンセル */
      /* リセットして終了 */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_CANCELLED : MSC_STATUS_FATAL_ERROR;
      goto EXT;

    case USBD_IOERROR:
    case USBD_STALLED:
      /* Bulk-IN で STALL or 通信エラー発生 */
      /* CLEAR_STALL (ENDPOINRT_HALT) */
      iRet = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[MSC_BBB_BI], NULL );
      ERROR_IF_WITHCODE( iRet != USB_OK, EXT, &sRetStat, MSC_STATUS_FATAL_ERROR );

      if( ptIface->ucRetryCount >= MSC_BBB_CSW_MAX_RETRY )
        /* リトライ上限オーバー */
        {
          /* リセット復旧 */
          iRet = usb_MSC_BBB_iReset( ptIface, NULL );
          sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_IO_ERROR : MSC_STATUS_FATAL_ERROR;
          goto EXT;
        }
      else
        {
          /* リトライ実行 */
          sRetStat = sBBBDataTransferred( ptIface, USBD_NORMAL_COMPLETION );
          ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
          ptIface->ucRetryCount++;
          USB_TRACE_LEAVE( 1, sBBBStatusTransferred );
          return( MSC_STATUS_COMMAND_PASSED );
        }

    default:
      /* 上5つ以外のステータスはないはず */
      DEBUG_ERROR_CALL( 0, "BBB Comm Finished:Illegal Status", &sStatus );
      sRetStat = MSC_STATUS_IO_ERROR;
      goto EXT;
    }

  /* CSW 解析 */
  if( ptCsw != pvBuffer ||
      ptCsw->dCSWSignature != MSC_BBB_CSW_SIGNATURE ||
      ptCsw->dCSWTag != ptCbw->dCBWTag ||
      usLength != MSC_BBB_CSW_SIZE )
    /* 不正規 CSW */
    {
      /* リセット復旧 */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_ILLEGAL_CSW : MSC_STATUS_FATAL_ERROR;
      goto EXT;
    }

  /* CSW エラー処理 */
  sRetStat = ptCsw->bCSWStatus;
  if( sRetStat == MSC_STATUS_PHASE_ERROR )
    /* フェイズエラー */
    {
      /* リセット復旧 */
      iRet = usb_MSC_BBB_iReset( ptIface, NULL );
      if( iRet != MSC_OK )
        sRetStat = MSC_STATUS_FATAL_ERROR;
      goto EXT;
    }

  /* 共有ブロック解放 */
  usb_USBC_vFreeUnionBlock( ptIface->pvBuffer );
  ptIface->pvBuffer = NULL;

  /* データ転送エラー判別 */
  if( ptIface->ucAddedStatus != 0 )
    sRetStat = ptIface->ucAddedStatus;

  /* コマンド完了通知コールバック関数 */
  if( ptIface->tCallbacks.vDone != NULL )
    ptIface->tCallbacks.vDone( ptIface->tCallbacks.ulArg, &tRes, sRetStat );

  USB_TRACE_LEAVE( 1, sBBBStatusTransferred );
  return( MSC_STATUS_COMMAND_PASSED );
 EXT:
  /* データ転送エラー判別 */
  if( sRetStat != MSC_STATUS_FATAL_ERROR && ptIface->ucAddedStatus != 0 )
    sRetStat = ptIface->ucAddedStatus;

  DEBUG_ERROR_CALL( 0, "BBB:sBBBStatusTransferred", &sRetStat );
  USB_TRACE_LEAVE( 1, sBBBStatusTransferred );
  return( sRetStat );
}


/*
  転送完了通知コールバック関数
    引数 - ulArg:任意値, pvBuffer:転送バッファアドレス, usLength:転送長[bye], sStatus: 通信ステータス
    戻値 - なし
*/
static void vBBBCommFinished( uint32_t ulArg, void* pvBuffer, uint16_t usLength, int16_t sStatus )
{
  int16_t sRetStat = MSC_STATUS_DRIVER_ERROR;
  USBC_typeInterface* ptIface = (USBC_typeInterface*)ulArg;

  USB_TRACE_ENTER( 0, vBBBCommFinished );

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptIface == NULL || ptIface->pvBuffer == NULL, EXT, &sRetStat, MSC_STATUS_DRIVER_ERROR );

  switch( ptIface->ucState )
    {
    /* コマンド送信完了 */
    case MSC_STAT_COMMAND:
      {
        sRetStat = sBBBCommandTransferred( ptIface, sStatus );
        ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
        break;
      }

    /* データ転送完了 */
    case MSC_STAT_DATA:
      {
        sRetStat = sBBBDataTransferred( ptIface, sStatus);
        ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
        break;
      }

    /* ステータス受信完了 */
    case MSC_STAT_STATUS:
      {
        sRetStat = sBBBStatusTransferred( ptIface, pvBuffer, usLength, sStatus );
        ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
        break;
      }

    /* デバイスが抜き取られた */
    case MSC_STAT_NO_DEVICE:
      sRetStat = MSC_STATUS_REMOVE_DEVICE;
      goto EXT;

    /* 異常状態 */
    default:
      sRetStat = MSC_STATUS_DRIVER_ERROR;
      DEBUG_ERROR_CALL( 0, "MSC_BBB:Illegal State", &sStatus );
      goto EXT;
    }

  USB_TRACE_LEAVE( 0, vBBBCommFinished );
  return;
 EXT:
  if( ptIface != NULL )
    {
      MSC_BBB_typeBlock* ptBlock = ptIface->pvBuffer;
      MSC_typeResult tRes = { 0, 0, 0 };

      /* 結果作成 */
      if( ptBlock != NULL )
        {
          tRes.ucSCSICmd = ptBlock->tCbw.CBWCB[0];
          tRes.pucBuffer = (uint8_t*)ptBlock->tCbw.dCBWTag;
          tRes.usSize = 0;
        }
      else
        {
          /* memset( &tRes, 0, sizeof(MSC_typeResult) ) */;
        }

      /* 状態復帰 */
      if( ptIface->ucState != MSC_STAT_NO_DEVICE )
        ptIface->ucState = MSC_STAT_READY;

      /* 共有ブロック解放 */
      if( ptIface->pvBuffer != NULL )
        usb_USBC_vFreeUnionBlock( ptIface->pvBuffer );
      ptIface->pvBuffer = NULL;

      /* 完了通知コールバック */
      if( ptIface->tCallbacks.vDone != NULL )
        ptIface->tCallbacks.vDone( ptIface->tCallbacks.ulArg, &tRes, sRetStat );
    }

  DEBUG_ERROR_CALL( 0, "BBB:vBBBCommFinished", &sRetStat );
  USB_TRACE_LEAVE( 0, vBBBCommFinished );
  return;
}


/* ========== GLOBAL FUNCTIONS ========== */

/*
  デバイス接続時初期化処理
*/
int16_t usb_MSC_BBB_iInitialize( USBC_typeInterface* ptIface, int16_t* psError )
{
  int16_t iRet;
  int16_t iNum, i;
  uint32_t ulIdIface = 0, ulIdEp = 0;
  usb_endpoint_descriptor_t* ptDescEp = NULL;
  bool pblFlag[MSC_BBB_EP_NUM] = { false, false };

  USB_TRACE_ENTER( 1, usb_MSC_BBB_iInitialize );

  /* インターフェースオープン */
  iRet = usb_USBD_iOpenInterface( ptIface->ptDevice->ulIdDev, ptIface->ptDescIface->bInterfaceNumber, 
                                  &ulIdIface, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  ptIface->ulIdIface = ulIdIface;

  /* エンドポイント */
  for( i = 0; i < ptIface->ptDescIface->bNumEndpoints; i++ )
    {
      /* エンドポイントディスクリプタ取得 */
      iRet = usb_USBD_iGetEndpointDescriptor( ptIface->ulIdIface, (uint8_t)i, &ptDescEp, psError);
      ERROR_IF( iRet != USB_OK, EXT );

      if( ptDescEp->bmAttributes == UE_BULK )
        {
          iNum = ( (ptDescEp->bEndpointAddress & UE_DIR_IN) != 0 ) ? MSC_BBB_BI : MSC_BBB_BO;

          /* 使用済み */
          if( pblFlag[iNum] != false )
            continue;

          ptIface->pptDescEp[iNum] = ptDescEp;

          /* エンドポイントオープン */
          iRet = usb_USBD_iOpenPipe( ptIface->ulIdIface, ptDescEp, vBBBCommFinished, (uint32_t)ptIface, &ulIdEp, psError );
          ERROR_IF( iRet != USB_OK, EXT );

          ptIface->pulIdEp[iNum] = ulIdEp;

          pblFlag[iNum] = true;
        }
    }

  /* パイプチェック */
  for( i = 0; i < MSC_BBB_EP_NUM; i++ )
    {
      ERROR_IF_WITHCODE( pblFlag[i] == false, EXT, psError, USB_MSC_PARAMETER );
    }

  /* 状態遷移 */
  ptIface->ucState = MSC_STAT_READY;

  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iInitialize );
  return( MSC_OK );
 EXT:
  /* 終了処理 */
  usb_MSC_BBB_iFinalize( ptIface, NULL );

  DEBUG_ERROR_CALL( 0, "MSC_BBB_iInitialize", psError );
  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iInitialize );
  return( MSC_NG );
}


/*
  デバイス解除時終了処理
*/
int16_t usb_MSC_BBB_iFinalize( USBC_typeInterface* ptIface, int16_t* psError )
{
  int16_t i, iRet;

  USB_TRACE_ENTER( 1, usb_MSC_BBB_iFinalize );

  /* 状態遷移 */
  ptIface->ucState = MSC_STAT_NO_DEVICE;

  /* エンドポイントクローズ */
  for( i = 0; i < MSC_BBB_EP_NUM; i++ )
    {
      if( ptIface->pulIdEp[i] != 0 )
        {
          iRet = usb_USBD_iClosePipe( ptIface->pulIdEp[i], psError );
          if( iRet != USB_OK )
            DEBUG_ERROR_CALL( 0, "MSC_BBB_iFinalize", psError );
        }
      ptIface->pulIdEp[i] = 0;
      ptIface->pptDescEp[i] = NULL;
    }

  /* インターフェースクローズ */
  if( ptIface->ulIdIface != 0 )
    {
      iRet = usb_USBD_iCloseInterface( ptIface->ulIdIface, psError );
      if( iRet != USB_OK )
        DEBUG_ERROR_CALL( 0, "MSC_BBB_iFinalize", psError );
      ptIface->ulIdIface = 0;
    }

  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iFinalize );
  return( MSC_OK );
}


/*
  デバイスリセット
*/
int16_t usb_MSC_BBB_iReset( USBC_typeInterface* ptIface, int16_t* psError )
{
  int16_t iRet1, iRet2, sError1 = 0, sError2 = 0;
  uint32_t ulIdDev;
  usb_device_request_t* ptReq = NULL;

  USB_TRACE_ENTER( 1, usb_MSC_BBB_iReset );

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptIface == NULL || ptIface->ptDevice == NULL || ptIface->ptDevice->ulIdDev == 0,
                     EXT, psError, USB_MSC_PARAMETER );

  ulIdDev = ptIface->ptDevice->ulIdDev;

  /* デバイスリクエスト用構造体確保 */
  ptReq = usb_USBC_ptAllocDeviceRequest();
  ERROR_IF_WITHCODE( ptReq == NULL, EXT, psError, USB_MSC_NOMEM );

  /* デバイスリクエスト Bulk-Only Mass Storage Reset 発行 */
  ptReq->bmRequestType = UT_WRITE_CLASS_INTERFACE;
  ptReq->bRequest = MSC_BBB_REQUEST_RESET;
  USB_SETW(ptReq->wValue, 0);
  USB_SETW(ptReq->wIndex, ptIface->ptDescIface->bInterfaceNumber);
  USB_SETW(ptReq->wLength, 0);
  iRet1 = usb_USBD_iDeviceRequest( ulIdDev, ptReq, NULL, psError );
  /* 構造体解放 */
  usb_USBC_vFreeDeviceRequest( ptReq );
  ERROR_IF( iRet1 != USB_OK, EXT );

  /* リセット後の待ち */
  usb_TIMER_vWaiMsec( MSC_BBB_RESET_RECOVERY_WAIT );

  /* デバイスリクエスト CLEAR_FEATURE (ENDPOINT_HALT) to BULK-IN */
  iRet1 = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[MSC_BBB_BI], &sError1 );

  /* デバイスリクエスト CLEAR_FEATURE (ENDPOINT_HALT) to BULK-OUT */
  iRet2 = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[MSC_BBB_BO], &sError2 );

  ERROR_IF_WITHCODE( iRet1 != USB_OK, EXT, psError, sError1 );
  ERROR_IF_WITHCODE( iRet2 != USB_OK, EXT, psError, sError2 );

  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iReset );
  return( MSC_OK );
 EXT:
  DEBUG_ERROR_CALL( 0, "MSC_BBB_iReset", psError );
  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iReset );
  return( MSC_NG );
}


/*
  SCSI コマンド実行
*/
int16_t usb_MSC_BBB_iSCSICommand( USBC_typeInterface* ptIface, usb_MSC_typeCommandBlock* ptCmdBlk, int16_t* psError )
{
  int16_t iRet;
  MSC_BBB_typeCBW* ptCbw = NULL;
  MSC_BBB_typeBlock* ptBlock = NULL;

  USB_TRACE_ENTER( 1, usb_MSC_BBB_iSCSICommand );

  /* 状態チェック */
  ERROR_IF_WITHCODE( ptIface->ucState == MSC_STAT_NO_DEVICE, EXT, psError, USB_MSC_NO_DEVICE );
  ERROR_IF_WITHCODE( ptIface->ucState != MSC_STAT_READY, EXT, psError, USB_MSC_IN_USE );

  /* 共有ブロック確保 (1つしか存在しない) */
  ptBlock = (MSC_BBB_typeBlock*)usb_USBC_ptAllocUnionBlock();
  ERROR_IF_WITHCODE( ptBlock == NULL, EXT, psError, USB_MSC_IN_USE );
  ptIface->pvBuffer = ptBlock;
  ptCbw = &ptBlock->tCbw;

  /* リトライ回数初期化 */
  ptIface->ucRetryCount = 0;
  /* エクステンションステータス */
  ptIface->ucAddedStatus = 0;

  /* CBW 作成  dSBWTag にバッファアドレスを設定 */
  vSetCbw( ptCbw, (uint32_t)ptCmdBlk->pucBuffer, ptCmdBlk->usBufferSize, ptCmdBlk->ucDirection, ptCmdBlk->ucLun, ptCmdBlk->ucCmdSize );

  /* デバイスのサブクラスが ATAPI の場合、コマンドブロックサイズを固定値に変更 */
  if( ptIface->ptDescIface->bInterfaceSubClass == MSC_SUBCLASS_SFF8070I )
    {
      ptCbw->bCBWCBLength = MSC_ATAPI_CMD_SZ;
    }

  /* SCSIコマンドブロックコピー */
  memcpy( ptCbw->CBWCB, ptCmdBlk->pucCmdBlock, 16 );

  /* コマンド転送実行 */
  iRet = iTransferCbw( ptIface, ptCbw, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iSCSICommand );
  return( MSC_OK );
 EXT:
  /* 共有ブロック解放 */
  if( ptBlock != NULL )           /* 2006/05/24 修正 田谷 */
    usb_USBC_vFreeUnionBlock( ptBlock );
  ptIface->pvBuffer = NULL;

  DEBUG_ERROR_CALL( 0, "MSC_BBB_iSCSICommand", psError );
  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iSCSICommand );
  return( MSC_NG );
}


/*
  Class Request GetMaxLUN
*/
int16_t usb_MSC_BBB_iGetMaxLUN( USBC_typeInterface* ptIface, uint8_t* pucLun, int16_t* psError )
{
  int16_t iRet;
  uint32_t ulIdDev;
  usb_device_request_t* ptReq = NULL;
  uint8_t* pucLunBuf = NULL;
  USBC_typeUnionBlock* ptBlk = NULL;

  USB_TRACE_ENTER( 1, usb_MSC_BBB_iGetMaxLUN );

  /* 引数チェック */
  ERROR_IF_WITHCODE( pucLun == NULL || ptIface == NULL || ptIface->ptDevice == NULL || ptIface->ptDevice->ulIdDev == 0,
                     EXT, psError, USB_MSC_PARAMETER );

  /* 状態チェック */
  ERROR_IF_WITHCODE( ptIface->ucState == MSC_STAT_NO_DEVICE, EXT, psError, USB_MSC_NO_DEVICE );
  ERROR_IF_WITHCODE( ptIface->ucState != MSC_STAT_READY, EXT, psError, USB_MSC_IN_USE );

  ulIdDev = ptIface->ptDevice->ulIdDev;

  /* デバイスリクエスト用メモリ確保 */
  ptReq = usb_USBC_ptAllocDeviceRequest();
  ERROR_IF_WITHCODE( ptReq == NULL, EXT, psError, USB_MSC_NOMEM );
  ptBlk = usb_USBC_ptAllocUnionBlock();
  ERROR_IF_WITHCODE( ptBlk == NULL, EXT, psError, USB_MSC_IN_USE );
  pucLunBuf = ptBlk->pucBuf;

  /* デバイスリクエスト発行 */
  ptReq->bmRequestType = UT_READ_CLASS_INTERFACE;
  ptReq->bRequest = MSC_BBB_GET_MAX_LUN;
  USB_SETW(ptReq->wValue, 0);
  USB_SETW(ptReq->wIndex, ptIface->ptDescIface->bInterfaceNumber);
  USB_SETW(ptReq->wLength, 1);
  iRet = usb_USBD_iDeviceRequest( ulIdDev, ptReq, pucLunBuf, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  /* 論理ユニット番号 */
  *pucLun = *pucLunBuf;

  usb_USBC_vFreeDeviceRequest( ptReq );
  usb_USBC_vFreeUnionBlock( ptBlk );
  ptReq = NULL;
  ptBlk = NULL;

  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iGetMaxLUN );
  return( MSC_OK );
 EXT:
  if( ptReq != NULL )
    usb_USBC_vFreeDeviceRequest( ptReq );
  if( ptBlk != NULL )
    usb_USBC_vFreeUnionBlock( ptBlk );

  DEBUG_ERROR_CALL( 0, "MSC_BBB_iGerMaxLUN", psError );
  USB_TRACE_LEAVE( 1, usb_MSC_BBB_iGetMaxLUN );
  return( MSC_NG );
}

/* --- End of File --- */
