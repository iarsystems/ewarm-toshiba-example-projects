/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_msccbi.c 4200 2015-08-14 12:44:49Z oscarmo $ */

/*

  USB Mass Storage Class Control/Bulk/Interrupt Transport Driver

*/

#include <string.h>
#include "usb_tmr.h"
#include "usb_classdrv.h"
#include "usb_classdrvblock.h"
#include "usb_msccbi.h"
#include "usb_classdrvmem.h"

/* ========== DEFINES ========== */

#define RESET_CMD_BLK_SZ 12

/* ========== Global Variables ========== */

/* CBI Reset Command */
static const uint8_t pucRESET_CMD_BLK[RESET_CMD_BLK_SZ]
  = { 0x1d, 0x04, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff };

/* ========== local functions ========== */

static int16_t sCBIDataTransferred( USBC_typeInterface * ptIface, int16_t sStatus );
static int16_t sCBIStatusTransferred( USBC_typeInterface * ptIface, int16_t sStatus );


/*
  デバイスリクエスト ADSC によるコマンド転送
*/
static int16_t iAcceptDeviceSpecificCommand( USBC_typeInterface* ptIface, usb_MSC_typeCommandBlock* ptCmdBlk, int16_t* psError )
{
  int16_t iRet;
  uint32_t ulIdDev = ptIface->ptDevice->ulIdDev;
  usb_device_request_t* ptReq = NULL;

  USB_TRACE_ENTER( 3, iAcceptDeviceSpecificCommand );

  /* 現状態チェック */
  ERROR_IF_WITHCODE( ptIface->ucState != MSC_STAT_READY, EXT_STAT_ERR, psError, USB_MSC_IN_USE );

  /* 転送情報設定 */
  ptIface->ucState = MSC_STAT_COMMAND;                  /* 状態遷移 */

  /* デバイスリクエスト用メモリ確保 */
  ptReq = usb_USBC_ptAllocDeviceRequest();
  ERROR_IF_WITHCODE( ptReq == NULL, EXT, psError, USB_MSC_NOMEM );

  ptReq->bmRequestType = UT_WRITE_CLASS_INTERFACE;
  ptReq->bRequest = MSC_CBI_REQUEST_ADSC;
  USB_SETW(ptReq->wValue, 0);
  USB_SETW(ptReq->wIndex, ptIface->ptDescIface->bInterfaceNumber);
  USB_SETW(ptReq->wLength, ptCmdBlk->ucCmdSize);

  /* デバイスリクエスト発行 */
  iRet = usb_USBD_iDeviceRequest( ulIdDev, ptReq, ptCmdBlk->pucCmdBlock, psError );

  /* デバイスリクエスト用メモリ解放 */
  usb_USBC_vFreeDeviceRequest( ptReq );

  if( iRet != USB_OK )
    {
      /* リセット */
      iRet = usb_MSC_CBI_iReset( ptIface, NULL );
      if( iRet != MSC_OK )
        {
          SET_ERRORCODE( psError, USB_MSC_DEVICE_ABNORMAL );
        }
      goto EXT;
    }

  USB_TRACE_LEAVE( 3, iAcceptDeviceSpecificCommand );
  return( MSC_OK );
 EXT:
  /* 状態復帰 */
  ptIface->ucState = MSC_STAT_READY;

 EXT_STAT_ERR:
  DEBUG_ERROR_CALL( 0, "CBI:iAcceptDeviceSpecificCommand", psError );
  USB_TRACE_LEAVE( 3, iAcceptDeviceSpecificCommand );
  return( MSC_NG );
}


/*
  コマンド転送完了後の、データ転送 or ステータス受信処理
*/
static int16_t sCBICommandTransferred( USBC_typeInterface * ptIface )
{
  int16_t iRet, sRetStat;
  usb_MSC_typeCommandBlock* ptCmdBlk = &((MSC_CBI_typeBlock*)ptIface->pvBuffer)->tCmdBlk;

  USB_TRACE_ENTER( 1, sCBICommandTransferred );

  /* データフェイズに状態遷移 */
  ptIface->ucState = MSC_STAT_DATA;

  /* バッファが存在する場合、データ転送開始 */
  if( ptCmdBlk->usBufferSize > 0 )
    {
      int16_t iDirection;
      uint16_t usFlags;

      iDirection = ( ptCmdBlk->ucDirection & USB_MSC_DIR_IN ) ? MSC_CBI_BI : MSC_CBI_BO;
      usFlags = ( ptCmdBlk->ucDirection & USB_MSC_DIR_IN ) ? USBD_SHORT_XFER_OK : 0;
      iRet = usb_USBD_iIoPipe( ptIface->pulIdEp[iDirection], ptCmdBlk->pucBuffer, ptCmdBlk->usBufferSize, usFlags, NULL );
      if( iRet != USB_OK )
        {
          iRet = usb_MSC_CBI_iReset( ptIface, NULL );
          sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_IO_ERROR : MSC_STATUS_FATAL_ERROR;
          goto EXT;
        }
    }
  else
    /* 存在しない場合は、データ転送完了後の処理を開始 */
    {
      /* データ転送完了 */
      sRetStat = sCBIDataTransferred( ptIface, USBD_NORMAL_COMPLETION );
      ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
    }

  USB_TRACE_LEAVE( 1, sCBICommandTransferred );
  return( MSC_STATUS_COMMAND_PASSED );
 EXT:
  DEBUG_ERROR_CALL( 0, "CBI:sCBICommandTransferred", &sRetStat );
  USB_TRACE_LEAVE( 1, sCBICommandTransferred );
  return( sRetStat );
}



/* --- 転送完了時コールバック処理 --- */

/*
  データ転送完了時処理
*/
static int16_t sCBIDataTransferred( USBC_typeInterface * ptIface, int16_t sStatus )
{
  int16_t iRet, sRetStat = MSC_STATUS_DRIVER_ERROR;
  MSC_CBI_typeBlock* ptUBlock = ptIface->pvBuffer;
  usb_MSC_typeCommandBlock* ptCmdBlk = &ptUBlock->tCmdBlk;
  MSC_CBI_typeIntDataBlock* ptStatBlk = &ptUBlock->tStatBlk;

  USB_TRACE_ENTER( 1, sCBIDataTransferred );

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
      iRet = usb_MSC_CBI_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_CANCELLED : MSC_STATUS_FATAL_ERROR;
      goto EXT;

    case USBD_STALLED:
      {
        /* 発生した STALL を解除 */
        int16_t iDirection = ( ptCmdBlk->ucDirection & USB_MSC_DIR_IN ) ? MSC_CBI_BI : MSC_CBI_BO;
        iRet = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[iDirection], NULL );
        ERROR_IF_WITHCODE( iRet != USB_OK, EXT, &sRetStat, MSC_STATUS_FATAL_ERROR );
      }
      /* break しないで default の処理を続けて実行する*/

    default:
      /* その他エラー */
      /* データでエラーが発生したことを記録 */
      ptIface->ucAddedStatus = MSC_STATUS_IO_ERROR;
    }

  /* ステータス受信開始 (with CCI 限定) */
  if( ptIface->ptDescIface->bInterfaceProtocol == MSC_PROTOCOL_CBI_CCI )
    {
      /* 受信実行 */
      iRet = usb_USBD_iIoPipe( ptIface->pulIdEp[MSC_CBI_IN],
                          ptStatBlk, sizeof(MSC_CBI_typeIntDataBlock), 0, NULL );
      if( iRet != USB_OK )
        {
          iRet = usb_MSC_CBI_iReset( ptIface, NULL );
          sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_IO_ERROR : MSC_STATUS_FATAL_ERROR;
          goto EXT;
        }
    }
  else
    {
      /* NOCCI の場合は、ステータス受信をとばす */
      sRetStat = sCBIStatusTransferred( ptIface, USBD_NORMAL_COMPLETION );
      ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
    }

  USB_TRACE_LEAVE( 1, sCBIDataTransferred );
  return( MSC_STATUS_COMMAND_PASSED );
EXT:
  DEBUG_ERROR_CALL( 0, "CBI:sCBIDataTransferred", &sRetStat );
  USB_TRACE_LEAVE( 1, sCBIDataTransferred );
  return( sRetStat );
}


/*
  ステータス転送完了時処理
*/
static int16_t sCBIStatusTransferred( USBC_typeInterface * ptIface, int16_t sStatus )
{
  int16_t iRet, sRetStat = MSC_STATUS_COMMAND_PASSED;
  MSC_CBI_typeBlock* ptUBlock = ptIface->pvBuffer;
  usb_MSC_typeCommandBlock* ptCmdBlk = &ptUBlock->tCmdBlk;
  MSC_CBI_typeIntDataBlock* ptStatBlk = &ptUBlock->tStatBlk;
  MSC_typeResult tRes = { 0, 0, 0 };

  tRes.ucSCSICmd = ptCmdBlk->pucCmdBlock[0];
  tRes.pucBuffer = ptCmdBlk->pucBuffer;
  tRes.usSize = ptCmdBlk->usBufferSize;

  USB_TRACE_ENTER( 1, sCBIStatusTransferred );

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
      iRet = usb_MSC_CBI_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_TIMEOUT : MSC_STATUS_FATAL_ERROR;
      goto EXT;

    case USBD_CANCELLED:
      /* 転送キャンセル */
      /* リセットして終了 */
      iRet = usb_MSC_CBI_iReset( ptIface, NULL );
      sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_CANCELLED : MSC_STATUS_FATAL_ERROR;
      goto EXT;

    case USBD_IOERROR:
    case USBD_STALLED:
      /* Bulk-IN で STALL or 通信エラー発生 */
      /* CLEAR_STALL (ENDPOINRT_HALT) */
      iRet = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[MSC_CBI_IN], NULL );
      ERROR_IF_WITHCODE( iRet != USB_OK, EXT, &sRetStat, MSC_STATUS_FATAL_ERROR );

       if( ptIface->ucRetryCount >= MSC_CBI_CSW_MAX_RETRY )
        /* リトライ上限オーバー */
        {
          /* リセット復旧 */
          iRet = usb_MSC_CBI_iReset( ptIface, NULL );
          sRetStat = ( iRet == MSC_OK ) ? MSC_STATUS_IO_ERROR : MSC_STATUS_FATAL_ERROR;
          goto EXT;
        }
      else
        {
          /* リトライ実行 */
          sRetStat = sCBIDataTransferred( ptIface, USBD_NORMAL_COMPLETION );
          ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
          ptIface->ucRetryCount++;
          USB_TRACE_LEAVE( 1, sCBIStatusTransferred );
          return( MSC_STATUS_COMMAND_PASSED );
        }

    default:
      /* 上5つ以外のステータスはないはず */
      DEBUG_ERROR_CALL( 0, "BBB Comm Finished:Illegal Status", &sStatus );
      sRetStat = MSC_STATUS_IO_ERROR;
      goto EXT;
    }

  /* ステータス解析 */
  if( ptIface->ptDescIface->bInterfaceProtocol == MSC_PROTOCOL_CBI_CCI )
    {
      if( ptStatBlk->bType != 0 )
        sRetStat = MSC_STATUS_COMMAND_FAILED;
      else
        {
          sRetStat = ptStatBlk->bValue & 0x03;
          if( sRetStat == MSC_STATUS_PHASE_ERROR || sRetStat == MSC_STATUS_PERSISTENT_FAILURE )
            {
              /* リセット */
              iRet = usb_MSC_CBI_iReset( ptIface, NULL );
              if( iRet != MSC_OK )
                sRetStat = MSC_STATUS_FATAL_ERROR;
              goto EXT;
            }
        }
    }

  /* 共有ブロック解放 */
  usb_USBC_vFreeUnionBlock( ptIface->pvBuffer );
  ptIface->pvBuffer = NULL;

  /* コマンド実行過程でのエラー判別 */
  if( ptIface->ucAddedStatus != 0 )
    sRetStat = ptIface->ucAddedStatus;

  /* コマンド完了通知コールバック関数 */
  if( ptIface->tCallbacks.vDone != NULL )
    ptIface->tCallbacks.vDone( ptIface->tCallbacks.ulArg, &tRes, sRetStat );

  USB_TRACE_LEAVE( 1, sCBIStatusTransferred );
  return( MSC_STATUS_COMMAND_PASSED );
 EXT:
  DEBUG_ERROR_CALL( 0, "CBI:sCBIStatusTransferred", &sRetStat );
  USB_TRACE_LEAVE( 1, sCBIStatusTransferred );
  return( sRetStat );
}


/*
  転送完了通知コールバック関数
    引数 - ulArg:任意値, pvBuffer:転送バッファアドレス, usLength:転送長[bye], sStatus: 通信ステータス
    戻値 - なし
*/
static void vCBICommFinished( uint32_t ulArg, void* pvBuffer, uint16_t usLength, int16_t sStatus )
{
  int16_t sRetStat = MSC_STATUS_DRIVER_ERROR;
  USBC_typeInterface* ptIface = (USBC_typeInterface*)ulArg;

  USB_TRACE_ENTER( 0, vCBICommFinished );

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptIface == NULL || ptIface->pvBuffer == NULL, EXT, &sRetStat, MSC_STATUS_DRIVER_ERROR );

  switch( ptIface->ucState )
    {
    /* データ転送完了 */
    case MSC_STAT_DATA:
      {
        sRetStat = sCBIDataTransferred( ptIface, sStatus);
        ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
        break;
      }

    /* ステータス受信完了 */
    case MSC_STAT_STATUS:
      {
        sRetStat = sCBIStatusTransferred( ptIface, sStatus );
        ERROR_IF( sRetStat != MSC_STATUS_COMMAND_PASSED, EXT );
        break;
      }

    /* デバイスが抜き取られた */
    case MSC_STAT_NO_DEVICE:
      sRetStat = MSC_STATUS_REMOVE_DEVICE;
      goto EXT;

    /* 状態異常 */
    case MSC_STAT_COMMAND:
    default:
      sRetStat = MSC_STATUS_DRIVER_ERROR;
      DEBUG_ERROR_CALL( 0, "MSC_CBI:Illegal State", &sStatus );
      goto EXT;
    }

  USB_TRACE_LEAVE( 0, vCBICommFinished );
  return;
 EXT:
  if( ptIface != NULL )
    {
      MSC_CBI_typeBlock* ptBlock = ptIface->pvBuffer;
      MSC_typeResult tRes = { 0, 0, 0 };

      if( ptBlock != NULL )
        {
          tRes.ucSCSICmd = ptBlock->tCmdBlk.pucCmdBlock[0];
          tRes.pucBuffer = ptBlock->tCmdBlk.pucBuffer;
          tRes.usSize = 0;
        }
      else
        {
          /* memset( &tRes, 0, sizeof(MSC_typeResult) ); */
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

  DEBUG_ERROR_CALL( 0, "CBI:vCBICommFinished", &sRetStat );
  USB_TRACE_LEAVE( 0, vCBICommFinished );
  return;
}


/* ========== GLOBAL FUNCTIONS ========== */

/*
  デバイス接続時初期化処理
*/
int16_t usb_MSC_CBI_iInitialize( USBC_typeInterface* ptIface, int16_t* psError )
{
  int16_t iRet;
  int16_t iNum, i;
  uint32_t ulIdIface = 0, ulIdEp = 0;
  usb_endpoint_descriptor_t* ptDescEp = NULL;
  bool pblFlag[MSC_CBI_EP_NUM] = { false, false, false };

  USB_TRACE_ENTER( 1, usb_MSC_CBI_iInitialize );

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

      /* 転送タイプ別に処理 */
      if( ptDescEp->bmAttributes == UE_BULK )
        iNum = ( (ptDescEp->bEndpointAddress & UE_DIR_IN) != 0 ) ? MSC_CBI_BI : MSC_CBI_BO;
      else if( ptDescEp->bmAttributes == UE_INTERRUPT && (ptDescEp->bEndpointAddress & UE_DIR_IN) != 0 )
        iNum = MSC_CBI_IN;
      else
        continue;

      /* 使用済み */
      if( pblFlag[iNum] != false )
        continue;

      /* エンドポイントディスクリプタ */
      ptIface->pptDescEp[iNum] = ptDescEp;

      /* エンドポイントオープン */
      iRet = usb_USBD_iOpenPipe( ptIface->ulIdIface, ptDescEp, vCBICommFinished, (uint32_t)ptIface, &ulIdEp, psError );
      ERROR_IF( iRet != USB_OK, EXT );

      ptIface->pulIdEp[iNum] = ulIdEp;

      pblFlag[iNum] = true;
    }

  /* パイプチェック */
  for( i = 0; i < MSC_CBI_EP_NUM; i++ )
    {
      if( i == MSC_CBI_IN && ptIface->ptDescIface->bInterfaceProtocol == MSC_PROTOCOL_CBI_NOCCI )
        break;
      ERROR_IF_WITHCODE( pblFlag[i] == false, EXT, psError, USB_MSC_PARAMETER );
    }

  /* 状態遷移 */
  ptIface->ucState = MSC_STAT_READY;

  USB_TRACE_LEAVE( 1, usb_MSC_CBI_iInitialize );
  return( MSC_OK );
 EXT:
  /* 終了処理 */
  usb_MSC_CBI_iFinalize( ptIface, NULL );

  DEBUG_ERROR_CALL( 0, "MSC_CBI_iInitialize", psError );
  USB_TRACE_LEAVE( 1, usb_MSC_CBI_iInitialize );
  return( MSC_NG );

}


/*
  デバイス解除時終了処理
*/
int16_t usb_MSC_CBI_iFinalize( USBC_typeInterface* ptIface, int16_t* psError )
{
  int16_t iRet;
  int16_t i;

  USB_TRACE_ENTER( 1, usb_MSC_CBI_iFinalize );

  /* 状態遷移 */
  ptIface->ucState = MSC_STAT_NO_DEVICE;

  /* エンドポイントクローズ */
  for( i = 0; i < MSC_CBI_EP_NUM; i++ )
    {
      if( ptIface->pulIdEp[i] != 0 )
        {
          iRet = usb_USBD_iClosePipe( ptIface->pulIdEp[i], psError );
          if( iRet != USB_OK )
            DEBUG_ERROR_CALL( 0, "MSC_CBI_iFinalize", psError );
        }
      ptIface->pulIdEp[i] = 0;
      ptIface->pptDescEp[i] = NULL;
    }

  /* インターフェースクローズ */
  if( ptIface->ulIdIface != 0 )
    {
      iRet = usb_USBD_iCloseInterface( ptIface->ulIdIface, psError );
      if( iRet != USB_OK )
        DEBUG_ERROR_CALL( 0, "MSC_CBI_iFinalize", psError );
      ptIface->ulIdIface = 0;
    }

  USB_TRACE_LEAVE( 1, usb_MSC_CBI_iFinalize );
  return( MSC_OK );
}


/*
  デバイスリセット
*/
int16_t usb_MSC_CBI_iReset( USBC_typeInterface* ptIface, int16_t* psError )
{
  int16_t iRet, iRet1, iRet2, iRet3 = USB_OK;
  int16_t sError1 = 0, sError2 = 0, sError3 = 0;
  uint32_t ulIdDev = ptIface->ptDevice->ulIdDev;
  usb_device_request_t* ptReq = NULL;
  uint8_t* pucCmdBlk = NULL;
  USBC_typeUnionBlock* ptBlk = NULL;

  USB_TRACE_ENTER( 1, usb_MSC_CBI_iReset );

  /* Send Diagnostic Command */

  /* デバイスリクエスト用メモリ確保 */
  ptReq = usb_USBC_ptAllocDeviceRequest();
  ERROR_IF_WITHCODE( ptReq == NULL, EXT, psError, USB_MSC_NOMEM );

  /* コマンドブロックには共有ブロックを使用 */
  if( ptIface->pvBuffer != NULL )
    pucCmdBlk = ptIface->pvBuffer;
  else
    {
      ptBlk = usb_USBC_ptAllocUnionBlock();
      ERROR_IF_WITHCODE( ptBlk == NULL, EXT, psError, USB_MSC_IN_USE );
      pucCmdBlk = ptBlk->pucBuf;
    }
  memcpy( pucCmdBlk, pucRESET_CMD_BLK, RESET_CMD_BLK_SZ );

  /* Device Request ADSC */
  ptReq->bmRequestType = UT_WRITE_CLASS_INTERFACE;
  ptReq->bRequest = MSC_CBI_REQUEST_ADSC;
  USB_SETW(ptReq->wValue, 0);
  USB_SETW(ptReq->wIndex, ptIface->ptDescIface->bInterfaceNumber);
  USB_SETW(ptReq->wLength, RESET_CMD_BLK_SZ );

  /* デバイスリクエスト発行 */
  iRet = usb_USBD_iDeviceRequest( ulIdDev, ptReq, pucCmdBlk, psError );

  /* メモリ解放 */
  usb_USBC_vFreeDeviceRequest( ptReq );
  if( ptBlk != NULL )
    usb_USBC_vFreeUnionBlock( ptBlk );
  ptReq = NULL;
  ptBlk = NULL;

  ERROR_IF( iRet != USB_OK, EXT );

  /* リセット後の待ち */
  usb_TIMER_vWaiMsec( MSC_CBI_RESET_RECOVERY_WAIT );

  /* -- CLEAR_STALL (ENDPOINRT_HALT) -- */
  /* Bulk-In */
  iRet1 = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[MSC_CBI_BI], &sError1 );
  /* Bulk-Out */
  iRet2 = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[MSC_CBI_BO], &sError2 );
  /* Interrupt */
  if( ptIface->ptDescIface->bInterfaceProtocol == MSC_PROTOCOL_CBI_CCI )
    {
      iRet3 = usb_USBD_iClearFeatureEndpoint( ptIface->pulIdEp[MSC_CBI_IN], &sError3 );
    }
  ERROR_IF_WITHCODE( iRet1 != USB_OK, EXT, psError, sError1 );
  ERROR_IF_WITHCODE( iRet2 != USB_OK, EXT, psError, sError2 );
  ERROR_IF_WITHCODE( iRet3 != USB_OK, EXT, psError, sError3 );

  USB_TRACE_LEAVE( 1, usb_MSC_CBI_iReset );
  return( MSC_OK );
 EXT:
  if( ptReq != NULL )
    usb_USBC_vFreeDeviceRequest( ptReq );
  if( ptBlk != NULL )
    usb_USBC_vFreeUnionBlock( ptBlk );

  DEBUG_ERROR_CALL( 0, "usb_MSC_CBI_iReset", psError );
  USB_TRACE_LEAVE( 1, usb_MSC_CBI_iReset );
  return( MSC_NG );
}


/*
  SCSI コマンド実行
*/
int16_t usb_MSC_CBI_iSCSICommand( USBC_typeInterface* ptIface, usb_MSC_typeCommandBlock* ptCmdBlk, int16_t* psError )
{
  int16_t iRet;
  MSC_CBI_typeBlock* ptBlock = NULL;

  USB_TRACE_ENTER( 1, usb_MSC_CBI_iSCSICommand );

  /* 状態チェック */
  ERROR_IF_WITHCODE( ptIface->ucState == MSC_STAT_NO_DEVICE, EXT, psError, USB_MSC_NO_DEVICE );
  ERROR_IF_WITHCODE( ptIface->ucState != MSC_STAT_READY, EXT, psError, USB_MSC_IN_USE );

  /* 共有ブロック確保 (1つしか存在しない) */
  ptBlock = (MSC_CBI_typeBlock*)usb_USBC_ptAllocUnionBlock();
  ERROR_IF_WITHCODE( ptBlock == NULL, EXT, psError, USB_MSC_IN_USE );

  /* コマンドブロックをRAMにコピー */
  memcpy( &ptBlock->tCmdBlk, ptCmdBlk, sizeof(MSC_CBI_typeBlock) );
  ptIface->pvBuffer = ptBlock;
  /* デバイスのサブクラスが ATAPI の場合、コマンドブロックサイズを固定値に変更 */
  if( ptIface->ptDescIface->bInterfaceSubClass == MSC_SUBCLASS_SFF8070I )
    {
      ptBlock->tCmdBlk.ucCmdSize = MSC_ATAPI_CMD_SZ;
    }

  /* リトライカウンタ初期化 */
  ptIface->ucRetryCount = 0;
  /* エクステンションステータス */
  ptIface->ucAddedStatus = 0;

  /* デバイスリクエスト ADSC によるコマンド転送 */
  iRet = iAcceptDeviceSpecificCommand( ptIface, &ptBlock->tCmdBlk, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* コマンド転送後処理 (データ転送 or ステータス受信) */
  iRet = sCBICommandTransferred( ptIface );
  if( iRet != MSC_STATUS_COMMAND_PASSED )
    {
      if( iRet == MSC_STATUS_FATAL_ERROR )
        {
          SET_ERRORCODE( psError, USB_MSC_DEVICE_ABNORMAL );
        }
      else
        {
          SET_ERRORCODE( psError, USB_MSC_SCSI_CMD_FAILED );
        }
      goto EXT;
    }

  USB_TRACE_LEAVE( 1, usb_MSC_CBI_iSCSICommand );
  return( MSC_OK );
 EXT:
  /* 共有ブロック解放 */
  if( ptBlock != NULL )
    usb_USBC_vFreeUnionBlock( ptBlock );
  ptIface->pvBuffer = NULL;
  ptIface->ucState = MSC_STAT_READY;

  DEBUG_ERROR_CALL( 0, "MSC_CBI_iSCSICommand", psError );
  USB_TRACE_LEAVE( 1, usb_MSC_CBI_iSCSICommand );
  return( MSC_NG );
}

/* --- End of File --- */
