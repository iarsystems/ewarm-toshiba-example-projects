/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_mscapi.c 4200 2015-08-14 12:44:49Z oscarmo $ */

/*

  Mass Storage Class Driver USER API

*/

#include <string.h>
#include "usb_msc_core.h"
#include "usb_mscapi.h"
#include "usb_mscmem.h"
#include "usb_scsi_util.h"
#include "usb_intr.h"
#include "usb_tmr.h"

/* ========== local functions ========== */
static void vSCSICmdDone( uint32_t ulArg, void* pvResult, int16_t sStatus );

/*
  R/W パラメータ算出
    MSC_iRead(), MSC_iWrite() の引数から、READ(10),WRITE(10) に使用する値を算出
    転送サイズが 65535Byte 以上の場合、分割する
*/
static void vCalcRwParameter( MSC_typeReadWriteParameter* ptCurRwPar, uint16_t usBytePerBlk )
{
  /* 次ブロックへ移行 */
  ptCurRwPar->ulStartBlk += ptCurRwPar->usNumBlks;
  ptCurRwPar->pucBuffer += (uint32_t)usBytePerBlk * (uint32_t)ptCurRwPar->usNumBlks;
  ptCurRwPar->usNumBlks = ptCurRwPar->usRemainBlks;

  /* バッファサイズが 16bit に納まるようにブロック数を調節 */
  if( (uint32_t)ptCurRwPar->usNumBlks * usBytePerBlk > 0xffff )
      ptCurRwPar->usNumBlks = (uint16_t)(0xffff / usBytePerBlk);

  /* 残余ブロック */
  ptCurRwPar->usRemainBlks -= ptCurRwPar->usNumBlks;
}


/*
  通信状態チェック
*/
static int16_t iCheckState( MSC_typeMsc* ptMsc, uint8_t ucLun, uint8_t ucChkKind, int16_t* psError )
{
  /* デバイスが挿入されていない */
  ERROR_IF_WITHCODE( ptMsc->ucState == MSC_APP_STAT_NO_DEVICE, EXT, psError, USB_MSC_NO_DEVICE );

  /* 2006/06/21 修正 田谷  LUN チェックの場所をここへ移動 */
  ERROR_IF_WITHCODE( ucLun > ptMsc->ucMaxLun, EXT, psError, USB_MSC_PARAMETER );

  switch( ucChkKind )
    {
    case MSC_CHECK_RW:
      /* 読み書き可能か否か */
      {
        switch( ptMsc->ucState )
          {
          case MSC_APP_STAT_IDLE:
            break;
          case MSC_APP_STAT_ACTIVE:
            SET_ERRORCODE( psError, USB_MSC_IN_USE );
            goto EXT;
        }
        /* 論理ユニット状態チェック */
        ERROR_IF_WITHCODE( (ptMsc->usLuState & (1 << ucLun)) == 0, EXT, psError, USB_MSC_NOT_READY );
        break;
      }

    case MSC_CHECK_COMM:
      /* 通信可能か否か */
      {
        switch( ptMsc->ucState )
          {
          case MSC_APP_STAT_ACTIVE:
            SET_ERRORCODE( psError, USB_MSC_IN_USE );
            goto EXT;
          }
        break;
      }

    case MSC_CHECK_READY:
      /* 初期化完了済みか否か */
      {
        /* 論理ユニット状態チェック */
        ERROR_IF_WITHCODE( (ptMsc->usLuState & (1 << ucLun)) == 0, EXT, psError, USB_MSC_NOT_READY );
        break;
      }

    default:
      DEBUG_ERROR_CALL( 0, "MSC:CheckState", psError );
      goto EXT;
    }

  return( MSC_OK );
 EXT:
  return( MSC_NG );
}


/* --- シナリオ --- */

/* シナリオ番号 */
enum {
  SCENARIO_TESTUNITREADY = 0,
  SCENARIO_INQUIRY,
  SCENARIO_READCAPACITY,
  SCENARIO_REQUESTSENSE,
  SCENARIO_READ,
  SCENARIO_WRITE,
  SCENARIO_SCSI,
  SCENARIO_INIT_END,
  SCENARIO_TOTAL_NUM
};


/*
  TEST UNIT READY
*/
static int16_t iTestUnitReadyProc( MSC_typeMsc* ptMsc, MSC_typeResult* ptRes, int16_t* psError )
{
  int16_t iRet;

  if( ptRes == NULL )
    {
      usb_MSC_typeCommandBlock *ptCmdBlk;
      ptCmdBlk = usb_MSC_pvAllocTempMemory();
      ERROR_IF_WITHCODE( ptCmdBlk == NULL, EXT, psError, USB_MSC_NOMEM );

      /* TEST UNIT READY 発行 */
      usb_SCSI_vTestUnitReady( ptMsc->ucLun, ptCmdBlk );
      iRet = usb_MSC_CORE_iSCSICommand( ptMsc->ulIdMsc, ptCmdBlk, psError );

      usb_MSC_vFreeTempMemory( ptCmdBlk );
      ERROR_IF( iRet != MSC_OK, EXT );
    }
  else
    {
      /* 完了コマンドチェック */
      ERROR_IF_WITHCODE( ptRes->ucSCSICmd != SCSI_TEST_UNIT_READY, EXT, psError, USB_MSC_DRIVER_ABNORMAL );

      /* パラメータ初期化 */
      ptMsc->ucRetry = 0;
    }

  return( MSC_OK );
 EXT:
  DEBUG_ERROR_CALL( 0, "MSC:TestUnitReady Proc", psError );
  return( MSC_NG );
}

/*
  INQUIRY
*/
static int16_t iInquiryProc( MSC_typeMsc* ptMsc, MSC_typeResult* ptRes, int16_t* psError )
{
  int16_t iRet;

  if( ptRes == NULL )
    {
      usb_MSC_typeCommandBlock *ptCmdBlk;
      ptCmdBlk = usb_MSC_pvAllocTempMemory();
      ERROR_IF_WITHCODE( ptCmdBlk == NULL, EXT, psError, USB_MSC_NOMEM );

      /* INQUIRY 発行 */
      usb_SCSI_vInquiry( ptMsc->ucLun, ptMsc->pvBuffer, SCSI_INQUIRY_BUF_SZ, ptCmdBlk );
      iRet = usb_MSC_CORE_iSCSICommand( ptMsc->ulIdMsc, ptCmdBlk, psError );
      usb_MSC_vFreeTempMemory( ptCmdBlk );
      ERROR_IF( iRet != MSC_OK, EXT );
    }
  else
    {
      /* 完了コマンドチェック */
      ERROR_IF_WITHCODE( ptRes->ucSCSICmd != SCSI_INQUIRY, EXT, psError, USB_MSC_DRIVER_ABNORMAL );

      /* パラメータ初期化 */
      ptMsc->ucRetry = 0;
    }

  return( MSC_OK );
 EXT:
  DEBUG_ERROR_CALL( 0, "MSC:Inquiry Proc", psError );
  return( MSC_NG );
}

/*
  READ CAPACITY
*/
static int16_t iReadCapacityProc( MSC_typeMsc* ptMsc, MSC_typeResult* ptRes, int16_t* psError )
{
  int16_t iRet;

  if( ptRes == NULL )
    {
      usb_MSC_typeCommandBlock *ptCmdBlk;

      ptCmdBlk = usb_MSC_pvAllocTempMemory();
      ERROR_IF_WITHCODE( ptCmdBlk == NULL, EXT, psError, USB_MSC_NOMEM );

      /* READ CAPACITY 発行 */
      usb_SCSI_vReadCapacity10( ptMsc->ucLun, ptMsc->pvBuffer, ptCmdBlk );
      iRet = usb_MSC_CORE_iSCSICommand( ptMsc->ulIdMsc, ptCmdBlk, psError );

      usb_MSC_vFreeTempMemory( ptCmdBlk );
      ERROR_IF( iRet != MSC_OK, EXT );
    }
  else
    {
      uint8_t* pucBuffer = ptMsc->pvBuffer;

      /* 完了コマンドチェック */
      ERROR_IF_WITHCODE( ptRes->ucSCSICmd != SCSI_READ_CAPACITY, EXT, psError, USB_MSC_DRIVER_ABNORMAL );

      /* パラメータ初期化 */
      ptMsc->ucRetry = 0;

      /* READ CAPACITY の結果取得 */
      ptMsc->pulNumBlks[ptMsc->ucLun] =
        ((((uint32_t)pucBuffer[0] << 24) & 0xff000000) |
        (((uint32_t)pucBuffer[1] << 16) & 0x00ff0000) |
        (((uint32_t)pucBuffer[2] << 8) & 0x0000ff00) |
        (((uint32_t)pucBuffer[3]) & 0x000000ff)) + 1;

      ptMsc->pusBytePerBlk[ptMsc->ucLun] =
        (((uint16_t)pucBuffer[6] << 8) & 0xff00) |
        ((uint16_t)pucBuffer[7] & 0x00ff);

      /* 1ブロックあたりのバイト数が 16bit を越えているデバイスは不可 */
      ERROR_IF_WITHCODE( pucBuffer[4] != 0 || pucBuffer[5] != 0, EXT, psError, USB_MSC_NO_DEVICE );
    }

  return( MSC_OK );
 EXT:
  DEBUG_ERROR_CALL( 0, "MSC:ReadCapacity Proc", psError );
  return( MSC_NG );
}

/*
  REQUEST SENSE
*/
static int16_t iRequestSenseProc( MSC_typeMsc* ptMsc, MSC_typeResult* ptRes, int16_t* psError )
{
  int16_t iRet;
  /* REQUEST SENSE は他のコマンドの合間に発行するため、ptMsc->pvBuffer 使用できない
     REQUEST SENSE 専用のバッファを用意する */
  static uint8_t pucReadSense[SCSI_REQUEST_SENSE_BUF_SZ];

  if( ptRes == NULL )
    {
      usb_MSC_typeCommandBlock *ptCmdBlk;

      ptCmdBlk = usb_MSC_pvAllocTempMemory();
      ERROR_IF_WITHCODE( ptCmdBlk == NULL, EXT, psError, USB_MSC_NOMEM );

      /* REQUEST SENSE 発行 */
      usb_SCSI_vRequestSense( ptMsc->ucLun, pucReadSense, SCSI_REQUEST_SENSE_BUF_SZ, ptCmdBlk );
      iRet = usb_MSC_CORE_iSCSICommand( ptMsc->ulIdMsc, ptCmdBlk, psError );

      usb_MSC_vFreeTempMemory( ptCmdBlk );
      ERROR_IF( iRet != MSC_OK, EXT );
    }
  else
    {
      /* 完了コマンドチェック */
      ERROR_IF_WITHCODE( ptRes->ucSCSICmd != SCSI_REQUEST_SENSE, EXT, psError, USB_MSC_DRIVER_ABNORMAL );

      /* エラー内容 (SENSE KEY) */
      ptMsc->ucSenseKey = pucReadSense[2] & 0x0f;

      /* リトライ上限値オーバー */
      ERROR_IF_WITHCODE( ptMsc->ucRetry >= MSC_MAX_RETRY_SCSICMD, EXT, psError, USB_MSC_SCSI_CMD_FAILED );

      /* リトライカウンタ */
      ptMsc->ucRetry++;
    }

  return( MSC_OK );
 EXT:
  DEBUG_ERROR_CALL( 0, "MSC:RequestSense Proc", psError );
  return( MSC_NG );
}

/*
  読み込み処理
*/
static int16_t iReadProc( MSC_typeMsc* ptMsc, MSC_typeResult* ptRes, int16_t* psError )
{
  int16_t iRet;
  MSC_typeReadWriteParameter* ptRw = ptMsc->pvBuffer;
  uint16_t usBytePerBlk = ptMsc->pusBytePerBlk[ptMsc->ucLun];

  if( ptRes == NULL )
    {
      usb_MSC_typeCommandBlock *ptCmdBlk;

      ptCmdBlk = usb_MSC_pvAllocTempMemory();
      ERROR_IF_WITHCODE( ptCmdBlk == NULL, EXT, psError, USB_MSC_NOMEM );

      /* SCSI コマンド READ (10) 実行 */
      usb_SCSI_vRead10( ptMsc->ucLun, ptRw->ulStartBlk, ptRw->usNumBlks, ptRw->pucBuffer,
                           ptRw->usNumBlks * usBytePerBlk, ptCmdBlk );
      iRet = usb_MSC_CORE_iSCSICommand( ptMsc->ulIdMsc, ptCmdBlk, psError );

      usb_MSC_vFreeTempMemory( ptCmdBlk );
      ERROR_IF( iRet != MSC_OK, EXT );
    }
  else
    {
      /* 完了コマンドチェック */
      ERROR_IF_WITHCODE( ptRes->ucSCSICmd != SCSI_READ10, EXT, psError, USB_MSC_DRIVER_ABNORMAL );

      /* パラメータ初期化 */
      ptMsc->ucRetry = 0;

      /* 転送済みバッファサイズ */
      ptMsc->ulTransBufSz += ptRes->usSize;

      /* 読み込みが終了していなければ継続 */
      if( ptRw->usRemainBlks != 0 )
        {
          MSC_typeScenario* ptScen;

          /* シナリオ先頭に READ(10) を挿入 (これ自体は消されてしまうが、前の READ(10) が残る) */
          ptScen = usb_MSC_ptAddHeadScenario( &ptMsc->ptScenarioList, SCENARIO_READ );
          ERROR_IF_WITHCODE( ptScen == NULL, EXT, psError, USB_MSC_NOMEM );

          /* 次リードパラメータ計算 */
          vCalcRwParameter( ptRw, usBytePerBlk );
        }
    }

  return( MSC_OK );
 EXT:
  DEBUG_ERROR_CALL( 0, "MSC:Read Proc", psError );
  return( MSC_NG );
}

/*
  書き込み処理
*/
static int16_t iWriteProc( MSC_typeMsc* ptMsc, MSC_typeResult* ptRes, int16_t* psError )
{
  int16_t iRet;
  MSC_typeReadWriteParameter* ptRw = ptMsc->pvBuffer;
  uint16_t usBytePerBlk = ptMsc->pusBytePerBlk[ptMsc->ucLun];

  if( ptRes == NULL )
    {
      usb_MSC_typeCommandBlock *ptCmdBlk;
      ptCmdBlk = usb_MSC_pvAllocTempMemory();
      ERROR_IF_WITHCODE( ptCmdBlk == NULL, EXT, psError, USB_MSC_NOMEM );

      /* SCSI コマンド WRITE (10) 実行 */
      usb_SCSI_vWrite10( ptMsc->ucLun, ptRw->ulStartBlk, ptRw->usNumBlks, ptRw->pucBuffer,
                           ptRw->usNumBlks * usBytePerBlk, ptCmdBlk );
      iRet = usb_MSC_CORE_iSCSICommand( ptMsc->ulIdMsc, ptCmdBlk, psError );

      usb_MSC_vFreeTempMemory( ptCmdBlk );
      ERROR_IF( iRet != MSC_OK, EXT );
    }
  else
    {
      /* 完了コマンドチェック */
      ERROR_IF_WITHCODE( ptRes->ucSCSICmd != SCSI_WRITE10, EXT, psError, USB_MSC_DRIVER_ABNORMAL );

      /* パラメータ初期化 */
      ptMsc->ucRetry = 0;

      /* 転送済みバッファサイズ */
      ptMsc->ulTransBufSz += ptRes->usSize;

      /* 読み込みが終了していなければ継続 */
      if( ptRw->usRemainBlks != 0 )
        {
          MSC_typeScenario* ptScen;

          /* シナリオ先頭に WRITE(10) を挿入 (これ自体は消されてしまうが、前の WRITE(10) が残る) */
          ptScen = usb_MSC_ptAddHeadScenario( &ptMsc->ptScenarioList, SCENARIO_WRITE );
          ERROR_IF_WITHCODE( ptScen == NULL, EXT, psError, USB_MSC_NOMEM );

          /* 次ライトパラメータ計算 */
          vCalcRwParameter( ptRw, usBytePerBlk );
        }
    }

  return( MSC_OK );
 EXT:
  DEBUG_ERROR_CALL( 0, "MSC:Write Proc", psError );
  return( MSC_NG );
}

/*
  その他 SCSI コマンド
*/
static int16_t iSCSICmdProc( MSC_typeMsc* ptMsc, MSC_typeResult* ptRes, int16_t* psError )
{
  int16_t iRet;
  usb_MSC_typeCommandBlock* ptCmdBlk = ptMsc->pvBuffer;

  if( ptRes == NULL )
    {
      /* SCSI コマンド発行 */
      iRet = usb_MSC_CORE_iSCSICommand( ptMsc->ulIdMsc, ptCmdBlk, psError );
      ERROR_IF( iRet != MSC_OK, EXT );
    }
  else
    {
      /* 完了コマンドチェック */
      ERROR_IF_WITHCODE( ptRes->ucSCSICmd != ptCmdBlk->pucCmdBlock[0], EXT, psError, USB_MSC_DRIVER_ABNORMAL );

      /* パラメータ初期化 */
      ptMsc->ucRetry = 0;

      /* 転送済みバッファサイズ */
      ptMsc->ulTransBufSz += ptRes->usSize;
    }

  return( MSC_OK );
 EXT:
  DEBUG_ERROR_CALL( 0, "MSC:SCSI Proc", psError );
  return( MSC_NG );
}


/*
  デバイス初期化終了
*/
static int16_t iInitEnd( MSC_typeMsc* ptMsc, MSC_typeResult* ptRes, int16_t* psError )
{
  if( ptRes == NULL )
    {
      MSC_typeResult tRes = { 0, 0, 0 };
      /* memset( &tRes, 0, sizeof(MSC_typeResult) ); */

      /* 転送完了コールバックの再起呼び出し */
      vSCSICmdDone( (uint32_t)ptMsc, &tRes, MSC_STATUS_COMMAND_PASSED );
    }
  else
    {
      /* 論理ユニットの初期化終了フラグを立てる */
      ptMsc->usLuState |= (1 << ptMsc->ucLun);
    }

  return( MSC_OK );
}

/* シナリオテーブル */
typedef int16_t(* p_mcs_func)(MSC_typeMsc*, MSC_typeResult*, int16_t* );
static const p_mcs_func piSCEN_FUNC[SCENARIO_TOTAL_NUM] =
{
  iTestUnitReadyProc,
  iInquiryProc,
  iReadCapacityProc,
  iRequestSenseProc,
  iReadProc,
  iWriteProc,
  iSCSICmdProc,
  iInitEnd
};

/* --- コールバック関数 --- */

/*
  コマンド完了時コールバック関数
*/
static void vSCSICmdDone( uint32_t ulArg, void* pvResult, int16_t sStatus )
{
  int16_t iRet = MSC_NG, sError = USB_MSC_DRIVER_ABNORMAL;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulArg;
  MSC_typeResult* ptRes = (MSC_typeResult*)pvResult;
  MSC_typeScenario* ptScen;

  if( ptMsc == NULL )
    {
      DEBUG_ERROR_CALL( 0, "MSC:Command Done", NULL );
      return;
    }

  ERROR_IF_WITHCODE( ptMsc->pvBuffer == NULL || ptRes == NULL, EXT, &sError, USB_MSC_DRIVER_ABNORMAL );

  ptScen = ptMsc->ptScenarioList;

  /* エラーチェック */
  if( sStatus != MSC_STATUS_COMMAND_PASSED )
    {
      switch( sStatus )
        {
        case MSC_STATUS_FATAL_ERROR:
          /* ポートリセットかデバイスの挿抜が必要 */
          iRet = MSC_NG;
          sError = USB_MSC_DEVICE_ABNORMAL;
          goto EXT;

        case MSC_STATUS_DRIVER_ERROR:
          iRet = MSC_NG;
          sError = USB_MSC_DRIVER_ABNORMAL;
          goto EXT;

        case MSC_STATUS_TIMEOUT:
          iRet = MSC_NG;
          sError = USB_MSC_TIMEOUT;
          goto EXT;

        case MSC_STATUS_CANCELLED:
          iRet = MSC_NG;
          sError = USB_MSC_CANCELLED;
          goto EXT;

        case MSC_STATUS_REMOVE_DEVICE:
          iRet = MSC_NG;
          sError = USB_MSC_NO_DEVICE;
          goto EXT;

        default:
          /* REQUEST SENSE のエラー時は SK_UNKNOWN を設定して終了 */
          if( ptScen->ucScenNo == SCENARIO_REQUESTSENSE )
            {
              iRet = MSC_NG;
              sError = USB_MSC_SCSI_CMD_FAILED;
              ptMsc->ucSenseKey = USB_MSC_SK_UNKNOWN;
              goto EXT;
            }

          /* シナリオに REQUEST SENSE を挿入 */
          ptScen = usb_MSC_ptAddHeadScenario( &ptMsc->ptScenarioList, SCENARIO_REQUESTSENSE );
          if( ptScen == NULL )
            {
              iRet = MSC_NG;
              sError = USB_MSC_NOMEM;
              goto EXT;
            }
          break;
        }
    }
  else
    {
      /* 転送後処理実行 */
      iRet = piSCEN_FUNC[ptScen->ucScenNo]( ptMsc, ptRes, &sError );
      ERROR_IF(iRet != MSC_OK, EXT );

      /* 次シナリオへ移行 */
      ptScen = usb_MSC_ptJumpNextScenario( &ptMsc->ptScenarioList );
    }

  if( ptScen != NULL )
    {
      /* 次シナリオ処理実行 */
      iRet = piSCEN_FUNC[ptScen->ucScenNo]( ptMsc, NULL, &sError );
      ERROR_IF(iRet != MSC_OK, EXT );
      return;
    }

 EXT:
  /* メモリ解放 */
  if( ptMsc->ptScenarioList != NULL )
    {
      usb_MSC_vDeleteScenarioList( ptMsc->ptScenarioList );
      ptMsc->ptScenarioList = NULL;
    }
  if( ptMsc->pvBuffer != NULL )
    {
      usb_MSC_vFreeTransferBuffer( ptMsc->pvBuffer );
      ptMsc->pvBuffer = NULL;
    }

  /* エラー発生時は初期化未完了状態に移行 */
  if( iRet != MSC_OK )
    {
      ptMsc->usLuState &= ~(1 << ptMsc->ucLun);
      DEBUG_ERROR_CALL( 0, "MSC:Command Done", &sError );
    }

  /* 状態遷移 */
  if( ptMsc->ucState != MSC_APP_STAT_NO_DEVICE )
    ptMsc->ucState = MSC_APP_STAT_IDLE;

  /* 終了コールバック呼び出し */
  if( ptMsc->tCallbacks.vDone != NULL )
    {
      if( iRet == MSC_OK )
        {
          sError = MSC_OK;
        }
      ptMsc->tCallbacks.vDone( ptMsc->tCallbacks.ulArg, ptMsc->ulTransBufSz, sError );
    }
}


/*
  デバイス接続時コールバック関数
*/
static bool blAttachMSC( uint32_t ulArg )
{
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulArg;

  USB_TRACE_ENTER( 0, blAttachMSC );

  /* 状態遷移 */
  ptMsc->ucState = MSC_APP_STAT_IDLE;

  /* パラメータ初期化 */
  ptMsc->ucSenseKey = USB_MSC_SK_NO_SENSE;
  ptMsc->usLuState = 0;
  ptMsc->ucMaxLun = 0;
  memset( ptMsc->pulNumBlks, 0, sizeof(uint32_t) * MSC_MAX_NUM_LUS );
  memset( ptMsc->pusBytePerBlk, 0, sizeof(uint16_t) * MSC_MAX_NUM_LUS );

  /* 最大論理ユニット番号取得 */
  usb_MSC_CORE_iGetMaxLUN( ptMsc->ulIdMsc, &ptMsc->ucMaxLun, NULL );
  if( ptMsc->ucMaxLun > MSC_MAX_NUM_LUS - 1 )
    ptMsc->ucMaxLun = MSC_MAX_NUM_LUS - 1;

  /* コールバック呼び出し */
  {
    usb_MSC_typeCallbacks* ptCb = &ptMsc->tCallbacks;
    if( ptCb->vAttach != NULL )
      ptCb->vAttach( ptCb->ulArg );
  }

  USB_TRACE_LEAVE( 0, blAttachMSC );

  return( true );
}


/*
  デバイス解除時コールバック関数
*/
static void vDetachMSC( uint32_t ulArg )
{
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulArg;

  USB_TRACE_ENTER( 0, vDetachMSC );

  /* 状態遷移 */
  ptMsc->ucState = MSC_APP_STAT_NO_DEVICE;

  /* パラメータ初期化 */
  ptMsc->usLuState = 0;
  ptMsc->ucMaxLun = 0;
  memset( ptMsc->pulNumBlks, 0, sizeof(uint32_t) * MSC_MAX_NUM_LUS );
  memset( ptMsc->pusBytePerBlk, 0, sizeof(uint16_t) * MSC_MAX_NUM_LUS );

  /* コールバック呼び出し */
  {
    usb_MSC_typeCallbacks* ptCb = &ptMsc->tCallbacks;
    if( ptCb->vDetach != NULL )
      ptCb->vDetach( ptCb->ulArg );
  }

  USB_TRACE_LEAVE( 0, vDetachMSC );
}


/* ========== GLOBAL FUNCTIONS ========== */

/*
  MSC 初期化
*/
void usb_MSC_vInitialize( void )
{
  /* メモリ初期化 */
  usb_MSC_vInitMemory();
}


/*
  MSC 使用開始
    引数
      ptMscCbs      コールバック関数群
      pulIdDev      デバイスID格納先ポインタ
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iOpen( usb_MSC_typeCallbacks* ptMscCbs, uint32_t* pulIdDev, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = NULL;
  USBC_typeCallbacks* ptClassCbs;

  USB_TRACE_ENTER( 0, usb_MSC_iInitialize );

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT;
    }
#endif

  /* 引数チェック */
  ERROR_IF_WITHCODE( pulIdDev == NULL || ptMscCbs == NULL, EXT, psError, USB_MSC_PARAMETER );

  /* メモリ確保 */
  ptMsc = usb_MSC_ptAllocMsc();
  ERROR_IF_WITHCODE( ptMsc == NULL, EXT, psError, USB_MSC_NOMEM );
  memset( ptMsc, 0, sizeof(MSC_typeMsc) );

  /* コールバック設定 */
  memcpy( &ptMsc->tCallbacks, ptMscCbs, sizeof(usb_MSC_typeCallbacks) );

  ptClassCbs = usb_MSC_pvAllocTempMemory();
  ERROR_IF_WITHCODE( ptClassCbs == NULL, EXT, psError, USB_MSC_NOMEM );
  ptClassCbs->ulArg = (uint32_t)ptMsc;
  ptClassCbs->blAttach = blAttachMSC;
  ptClassCbs->vDetach = vDetachMSC;
  ptClassCbs->vDone = vSCSICmdDone;

  /* ドライバ使用開始 */
  iRet = usb_MSC_CORE_iOpen( ptClassCbs, &ptMsc->ulIdMsc, psError );
  usb_MSC_vFreeTempMemory( ptClassCbs );
  ERROR_IF_WITHCODE( iRet != MSC_OK, EXT, pulIdDev, 0 );

  /* ID セット */
  *pulIdDev = (uint32_t)ptMsc;

  /* 割り込み許可 */
  USB_ENA_INTR();

  SET_ERRORCODE( psError, MSC_OK );
  USB_TRACE_LEAVE( 0, usb_MSC_iInitialize );
  return( MSC_OK );
 EXT:
  /* メモリ解放 */
  if( ptMsc != NULL )
    usb_MSC_vFreeMsc( ptMsc );

  USB_ENA_INTR();

  DEBUG_ERROR_CALL( 0, "MSC_iInitialize", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_iInitialize );
  return( MSC_NG );
}


/*
  MSC 使用終了
    引数
      ulIdDev       デバイスID
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iClose( uint32_t ulIdDev, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  USB_TRACE_ENTER( 0, usb_MSC_iFinalize );

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT;
    }
#endif

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptMsc == NULL, EXT, psError, USB_MSC_PARAMETER );


  /* ドライバ使用終了 */
  iRet = usb_MSC_CORE_iClose( ptMsc->ulIdMsc, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* メモリ解放 */
  usb_MSC_vFreeMsc( ptMsc );

  /* 割り込み許可 */
  USB_ENA_INTR();

  SET_ERRORCODE( psError, MSC_OK );
  USB_TRACE_LEAVE( 0, usb_MSC_iFinalize );
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "MSC_iFinalize", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_iFinalize );
  return( MSC_NG );
}


/*
  ブロック書き込み
    引数
      ulIdDev       デバイスID
      ucLun         論理ユニット番号
      ulStartBlk    書き込み開始ブロック番号
      usNumBlks     書き込みブロック数
      pcBuffer      書き込みバッファ
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iWrite( uint32_t ulIdDev, uint8_t ucLun,
                        uint32_t ulStartBlk, uint16_t usNumBlks,
                        uint8_t* pucBuffer, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;
  MSC_typeReadWriteParameter* ptRwPar;

  USB_TRACE_ENTER( 0, usb_MSC_iWrite );

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT2;  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */
    }
#endif

  /* 引数チェック */
  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */
  /* 2006/06/21 修正 田谷  LUN チェックの場所を他へ移動 */
  ERROR_IF_WITHCODE( ptMsc == NULL, EXT2, psError, USB_MSC_PARAMETER );

  /* 通信状態チェック */
  iRet = iCheckState( ptMsc, ucLun, MSC_CHECK_RW, psError );
  ERROR_IF( iRet != MSC_OK, EXT2 );  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */

  /* ドライバ状態チェック */
  ERROR_IF_WITHCODE( ptMsc->ptScenarioList != NULL || ptMsc->pvBuffer != NULL,
                     EXT, psError, USB_MSC_DRIVER_ABNORMAL );

  /* サイズチェック */
  ERROR_IF_WITHCODE( usNumBlks == 0 || pucBuffer == NULL || ulStartBlk + usNumBlks > ptMsc->pulNumBlks[ucLun],
                     EXT, psError, USB_MSC_PARAMETER );

  /* シナリオ作成 */
  {
    uint8_t ucScen = SCENARIO_WRITE;
    MSC_typeScenario* ptScen;
    ptScen = usb_MSC_ptCreateScenarioList( &ucScen, 1 );
    ERROR_IF_WITHCODE( ptScen == NULL, EXT, psError, USB_MSC_NOMEM );
    ptMsc->ptScenarioList = ptScen;
  }

  /* 初期パラメータセット */
  ptRwPar = usb_MSC_pvAllocTransferBuffer();
  ERROR_IF_WITHCODE( ptRwPar == NULL, EXT, psError, USB_MSC_IN_USE );
  ptRwPar->ulStartBlk = ulStartBlk;
  ptRwPar->pucBuffer = pucBuffer;
  ptRwPar->usNumBlks = 0;
  ptRwPar->usRemainBlks = usNumBlks;
  vCalcRwParameter( ptRwPar, ptMsc->pusBytePerBlk[ptMsc->ucLun] );
  ptMsc->pvBuffer = ptRwPar;

  /* --- パラメータ初期化 --- */

  /* リトライカウンタ */
  ptMsc->ucRetry = 0;

  /* 転送済みバッファサイズ */
  ptMsc->ulTransBufSz = 0;

  /* 論理ユニット番号 */
  ptMsc->ucLun = ucLun;

  /* シナリオスタート */
  iRet = piSCEN_FUNC[ptMsc->ptScenarioList->ucScenNo]( ptMsc, NULL, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* 状態遷移 */
  ptMsc->ucState = MSC_APP_STAT_ACTIVE;

  /* 割り込み許可 */
  USB_ENA_INTR();

  SET_ERRORCODE( psError, MSC_OK );
  USB_TRACE_LEAVE( 0, usb_MSC_iWrite );
  return( MSC_OK );
 EXT:
  /* メモリ解放 */
  if( ptMsc->ptScenarioList != NULL )
    {
      usb_MSC_vDeleteScenarioList( ptMsc->ptScenarioList );
      ptMsc->ptScenarioList = NULL;
    }
  if( ptMsc->pvBuffer != NULL )
    {
      usb_MSC_vFreeTransferBuffer( ptMsc->pvBuffer );
      ptMsc->pvBuffer = NULL;
    }

 EXT2:  /* 2006/06/13 修正 田谷  追加 */
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "MSC_iWrite", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_iWrite );
  return( MSC_NG );
}


/*
  ブロック読み込み
    引数
      ulIdDev       デバイスID
      ucLun         論理ユニット番号
      ulStartBlk    読み込み開始ブロック番号
      usNumBlks     読み込みブロック数
      pcBuffer      読み込みバッファ
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iRead( uint32_t ulIdDev, uint8_t ucLun,
                       uint32_t ulStartBlk, uint16_t usNumBlks,
                       uint8_t* pucBuffer, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;
  MSC_typeReadWriteParameter* ptRwPar;

  USB_TRACE_ENTER( 0, usb_MSC_iRead );

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT2;  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */
    }
#endif

  /* 引数チェック */
  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */
  /* 2006/06/21 修正 田谷  LUN チェックの場所を他へ移動 */
  ERROR_IF_WITHCODE( ptMsc == NULL, EXT2, psError, USB_MSC_PARAMETER );

  /* 通信状態チェック */
  iRet = iCheckState( ptMsc, ucLun, MSC_CHECK_RW, psError );
  ERROR_IF( iRet != MSC_OK, EXT2 );  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */

  /* ドライバ状態チェック */
  ERROR_IF_WITHCODE( ptMsc->ptScenarioList != NULL || ptMsc->pvBuffer != NULL,
                     EXT, psError, USB_MSC_DRIVER_ABNORMAL );

  /* サイズチェック */
  ERROR_IF_WITHCODE( usNumBlks == 0 || pucBuffer == NULL || ulStartBlk + usNumBlks > ptMsc->pulNumBlks[ucLun],
                     EXT, psError, USB_MSC_PARAMETER );

  /* シナリオ作成 */
  {
    uint8_t ucScen = SCENARIO_READ;
    MSC_typeScenario* ptScen;
    ptScen = usb_MSC_ptCreateScenarioList( &ucScen, 1 );
    ERROR_IF_WITHCODE( ptScen == NULL, EXT, psError, USB_MSC_NOMEM );
    ptMsc->ptScenarioList = ptScen;
  }

  /* 初期パラメータセット */
  ptRwPar = usb_MSC_pvAllocTransferBuffer();
  ERROR_IF_WITHCODE( ptRwPar == NULL, EXT, psError, USB_MSC_IN_USE );
  ptRwPar->ulStartBlk = ulStartBlk;
  ptRwPar->pucBuffer = pucBuffer;
  ptRwPar->usNumBlks = 0;
  ptRwPar->usRemainBlks = usNumBlks;
  vCalcRwParameter( ptRwPar, ptMsc->pusBytePerBlk[ptMsc->ucLun] );
  ptMsc->pvBuffer = ptRwPar;

  /* --- パラメータ初期化 --- */

  /* リトライカウンタ */
  ptMsc->ucRetry = 0;

  /* 転送済みバッファサイズ */
  ptMsc->ulTransBufSz = 0;

  /* 論理ユニット番号 */
  ptMsc->ucLun = ucLun;

  /* シナリオスタート */
  iRet = piSCEN_FUNC[ptMsc->ptScenarioList->ucScenNo]( ptMsc, NULL, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* 状態遷移 */
  ptMsc->ucState = MSC_APP_STAT_ACTIVE;

  /* 割り込み許可 */
  USB_ENA_INTR();

  SET_ERRORCODE( psError, MSC_OK );
  USB_TRACE_LEAVE( 0, usb_MSC_iRead );
  return( MSC_OK );
 EXT:
  /* メモリ解放 */
  if( ptMsc->ptScenarioList != NULL )
    {
      usb_MSC_vDeleteScenarioList( ptMsc->ptScenarioList );
      ptMsc->ptScenarioList = NULL;
    }
  if( ptMsc->pvBuffer != NULL )
    {
      usb_MSC_vFreeTransferBuffer( ptMsc->pvBuffer );
      ptMsc->pvBuffer = NULL;
    }

 EXT2:  /* 2006/06/13 修正 田谷  追加 */
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "MSC_iRead", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_iRead );
  return( MSC_NG );
}


/*
  MSC デバイス初期化
    引数
      ulIdDev       デバイスID
      ucLun         論理ユニット番号
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iInitDevice( uint32_t ulIdDev, uint8_t ucLun, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  USB_TRACE_ENTER( 0, usb_MSC_iInitDevice );

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT2;  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */
    }
#endif

  /* 引数チェック */
  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */
  /* 2006/06/21 修正 田谷  LUN チェックの場所を他へ移動 */
  ERROR_IF_WITHCODE( ptMsc == NULL, EXT2, psError, USB_MSC_PARAMETER );

  /* 通信状態チェック */
  iRet = iCheckState( ptMsc, ucLun, MSC_CHECK_COMM, psError );
  ERROR_IF( iRet != MSC_OK, EXT2 );  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */

  /* ドライバ状態チェック */
  ERROR_IF_WITHCODE( ptMsc->ptScenarioList != NULL || ptMsc->pvBuffer != NULL,
                     EXT, psError, USB_MSC_DRIVER_ABNORMAL );

  /* シナリオ作成 */
  {
#define NORMAL_INIT_SCENARIO_LEN 4
    uint8_t pucScen[NORMAL_INIT_SCENARIO_LEN]
      = { SCENARIO_INQUIRY, SCENARIO_TESTUNITREADY, SCENARIO_READCAPACITY, SCENARIO_INIT_END };
    MSC_typeScenario* ptScen;
    ptScen = usb_MSC_ptCreateScenarioList( pucScen, NORMAL_INIT_SCENARIO_LEN );
    ERROR_IF_WITHCODE( ptScen == NULL, EXT, psError, USB_MSC_NOMEM );
    ptMsc->ptScenarioList = ptScen;
  }

  /* バッファ確保 */
  ptMsc->pvBuffer = usb_MSC_pvAllocTransferBuffer();
  ERROR_IF_WITHCODE( ptMsc->pvBuffer == NULL, EXT, psError, USB_MSC_IN_USE );

  /* --- パラメータ初期化 --- */

  /* リトライカウンタ */
  ptMsc->ucRetry = 0;

  /* 転送済みバッファサイズ */
  ptMsc->ulTransBufSz = 0;

  /* 論理ユニット番号 */
  ptMsc->ucLun = ucLun;
  ptMsc->usLuState &= ~(1 << ucLun);

  /* シナリオスタート */
  iRet = piSCEN_FUNC[ptMsc->ptScenarioList->ucScenNo]( ptMsc, NULL, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* 状態遷移 */
  ptMsc->ucState = MSC_APP_STAT_ACTIVE;

  /* 割り込み許可 */
  USB_ENA_INTR();

  USB_TRACE_LEAVE( 0, usb_MSC_iInitDevice );
  return( MSC_OK );
 EXT:
  /* メモリ解放 */
  if( ptMsc->ptScenarioList != NULL )
    {
      usb_MSC_vDeleteScenarioList( ptMsc->ptScenarioList );
      ptMsc->ptScenarioList = NULL;
    }
  if( ptMsc->pvBuffer != NULL )
    {
      usb_MSC_vFreeTransferBuffer( ptMsc->pvBuffer );
      ptMsc->pvBuffer = NULL;
    }

 EXT2:  /* 2006/06/13 修正 田谷  追加 */
  USB_ENA_INTR();
  USB_TRACE_LEAVE( 0, usb_MSC_iInitDevice );
  return( MSC_NG );
}


/*
  SCSI コマンド実行
    引数
      ulIdDev       デバイスID
      ptCmdBlk      コマンドブロック
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iIoControl( uint32_t ulIdDev, usb_MSC_typeCommandBlock* ptCmdBlk, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  USB_TRACE_ENTER( 0, usb_MSC_iIoControl );

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT2;  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */
    }
#endif

  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */
  ERROR_IF_WITHCODE( ptMsc == NULL || ptCmdBlk == NULL, EXT2, psError, USB_MSC_PARAMETER );

  /* 通信状態チェック */
  iRet = iCheckState( ptMsc, 0, MSC_CHECK_COMM, psError );
  ERROR_IF( iRet != MSC_OK, EXT2 );  /* 2006/06/13 修正 田谷  EXT -> EXT2 に変更 */

  /* ドライバ状態チェック */
  ERROR_IF_WITHCODE( ptMsc->ptScenarioList != NULL || ptMsc->pvBuffer != NULL,
                     EXT, psError, USB_MSC_DRIVER_ABNORMAL );

  /* シナリオ作成 */
  {
    uint8_t ucScen = SCENARIO_SCSI;
    MSC_typeScenario* ptScen;
    ptScen = usb_MSC_ptCreateScenarioList( &ucScen, 1 );
    ERROR_IF_WITHCODE( ptScen == NULL, EXT, psError, USB_MSC_NOMEM );
    ptMsc->ptScenarioList = ptScen;
  }

  /* --- パラメータ初期化 --- */

  /* リトライカウンタ */
  ptMsc->ucRetry = 0;

  /* 転送済みバッファサイズ */
  ptMsc->ulTransBufSz = 0;

  /* 論理ユニット番号 */
  ptMsc->ucLun = ptCmdBlk->ucLun;

  /* コマンドブロック作成 */
  ptMsc->pvBuffer = usb_MSC_pvAllocTransferBuffer();
  ERROR_IF_WITHCODE( ptMsc->pvBuffer == NULL, EXT, psError, USB_MSC_IN_USE );
  memcpy( ptMsc->pvBuffer, ptCmdBlk, sizeof(usb_MSC_typeCommandBlock) );

  /* シナリオスタート */
  iRet = piSCEN_FUNC[ptMsc->ptScenarioList->ucScenNo]( ptMsc, NULL, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* 状態遷移 */
  ptMsc->ucState = MSC_APP_STAT_ACTIVE;

  /* 割り込み許可 */
  USB_ENA_INTR();

  SET_ERRORCODE( psError, MSC_OK );
  USB_TRACE_LEAVE( 0, usb_MSC_iIoControl );
  return( MSC_OK );
 EXT:
  /* メモリ解放 */
  if( ptMsc->ptScenarioList != NULL )
    {
      usb_MSC_vDeleteScenarioList( ptMsc->ptScenarioList );
      ptMsc->ptScenarioList = NULL;
    }
  if( ptMsc->pvBuffer != NULL )
    {
      usb_MSC_vFreeTransferBuffer( ptMsc->pvBuffer );
      ptMsc->pvBuffer = NULL;
    }

 EXT2:  /* 2006/06/13 修正 田谷  追加 */
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "usb_MSC_iIoControl", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_iIoControl );
  return( MSC_NG );
}


/*
  デバイス操作キャンセル
    引数
      ulIdDev       デバイスID
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iIoCancel( uint32_t ulIdDev, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT;
    }
#endif

  ERROR_IF_WITHCODE( ptMsc == NULL, EXT, psError, USB_MSC_PARAMETER );

  /* キャンセル実行 */
  iRet = usb_MSC_CORE_iCancelCommand( ptMsc->ulIdMsc, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* 割り込み許可 */
  USB_ENA_INTR();

  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "usb_MSC_iIoCancel", psError );
  return( MSC_NG );
}


/*
  状態取得
    引数
      ulIdDev       デバイスID
      psStatus      状態格納先ポインタ
      pusLuState    論理ユニット状態格納先ポインタ
    戻値
      なし
*/
void usb_MSC_vGetStatus( uint32_t ulIdDev, int16_t* psStatus, uint16_t* pusLuState )
{
  int16_t sStatus;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  USB_TRACE_ENTER( 0, MSC_vGetStatus );

  /* 割り込み禁止 */
  USB_DIS_INTR();

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptMsc == NULL, EXT, psStatus, USB_MSC_PARAMETER );

  /* 状態チェック */
  switch( ptMsc->ucState )
    {
    case MSC_APP_STAT_IDLE:
      sStatus = USB_MSC_OK;
      break;
    case MSC_APP_STAT_NO_DEVICE:
      sStatus = USB_MSC_NO_DEVICE;
      break;
    case MSC_APP_STAT_ACTIVE:
      sStatus = USB_MSC_IN_USE;
      break;
    default:
      /* 警告避け */
      sStatus = USB_MSC_DRIVER_ABNORMAL;
    }

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      sStatus = USB_MSC_IN_USE;
    }
#endif

  if( psStatus != NULL )
    *psStatus = sStatus;
  if( pusLuState != NULL )
    *pusLuState = ( sStatus == USB_MSC_NO_DEVICE ) ? 0 : ptMsc->usLuState;

 EXT:
  /* 割り込み許可 */
  USB_ENA_INTR();
  USB_TRACE_LEAVE( 0, MSC_vGetStatus );
}


/*
  デバイスの論理ユニット数取得
    引数
      ulIdDev       デバイスID
      pucNumLus     論理ユニット数格納先ポインタ
      pusLuState    論理ユニット状態格納先ポインタ
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iGetNumLus( uint32_t ulIdDev, uint8_t* pucNumLus, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  USB_TRACE_ENTER( 0, usb_MSC_iGetNumLus );

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT;
    }
#endif

  /* 引数チェック */
  ERROR_IF_WITHCODE( ptMsc == NULL, EXT, psError, USB_MSC_PARAMETER );

  /* 通信状態チェック */
  iRet = iCheckState( ptMsc, 0, MSC_CHECK_COMM, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* 最大論理ユニット番号取得 */
  iRet = usb_MSC_CORE_iGetMaxLUN( ptMsc->ulIdMsc, &ptMsc->ucMaxLun, psError );
  ERROR_IF( iRet != MSC_OK, EXT );
  if( ptMsc->ucMaxLun > MSC_MAX_NUM_LUS - 1 )
    ptMsc->ucMaxLun = MSC_MAX_NUM_LUS - 1;

  if( pucNumLus != NULL )
    *pucNumLus = ptMsc->ucMaxLun + 1;

  /* 割り込み許可 */
  USB_ENA_INTR();

  USB_TRACE_LEAVE( 0, usb_MSC_iGetNumLus );
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  DEBUG_ERROR_CALL( 0, "MSC_iGetBlkInf", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_iGetNumLus );
  return( MSC_NG );
}


/*
  デバイスブロック情報取得
    引数
      ulIdDev       デバイスID
      ucLun         論理ユニット番号
      pulNumBlks    総ブロック数
      pulBytePerBlk 1ブロック当たりのバイト数
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iGetBlkInf( uint32_t ulIdDev, uint8_t ucLun, uint32_t* pulNumBlks, uint32_t* pulBytePerBlk, int16_t* psError )
{
  int16_t iRet;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  USB_TRACE_ENTER( 0, usb_MSC_iGetBlkInf );

  /* 割り込み禁止 */
#if 0 /* 2006/10/20 一括で禁止/許可を行うように修正 田谷 */
  USB_DIS_INTR();
  usb_TIMER_vDisIntr();
#else
  usb_vDisableAllIntr();
#endif

  /* 引数チェック */
  /* 2006/06/21 修正 田谷  LUN チェックの場所を他へ移動 */
  ERROR_IF_WITHCODE( ptMsc == NULL, EXT, psError, USB_MSC_PARAMETER );

  /* 状態チェック */
  iRet = iCheckState( ptMsc, ucLun, MSC_CHECK_READY, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  /* パラメータ取得 */
  if( pulBytePerBlk != NULL )
    *pulBytePerBlk = ptMsc->pusBytePerBlk[ucLun];
  if( pulNumBlks != NULL )
    *pulNumBlks = ptMsc->pulNumBlks[ucLun];

  /* 割り込み許可 */
#if 0 /* 2006/10/20 一括で禁止/許可を行うように修正 田谷 */
  usb_TIMER_vEnaIntr();
  USB_ENA_INTR();
#else
  usb_vEnableAllIntr();
#endif

  USB_TRACE_LEAVE( 0, usb_MSC_iGetBlkInf );
  return( MSC_OK );
 EXT:
#if 0 /* 2006/10/20 一括で禁止/許可を行うように修正 田谷 */
  usb_TIMER_vEnaIntr();
  USB_ENA_INTR();
#else
  usb_vEnableAllIntr();
#endif
  DEBUG_ERROR_CALL( 0, "MSC_iGetBlkInf", psError );
  USB_TRACE_LEAVE( 0, usb_MSC_iGetBlkInf );
  return( MSC_NG );
}


/*
  SenseKey 取得
    エラー USB_MSC_SCSI_CMD_FAILED の後、SenseKey を取得する
    引数
      ulIdDev       デバイスID
      pucSenseKey   SenseKey 格納先ポインタ
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iGetSenseKey( uint32_t ulIdDev, uint8_t* pucSenseKey, int16_t* psError )
{
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  ERROR_IF_WITHCODE( ptMsc == NULL || pucSenseKey == NULL, EXT, psError, USB_MSC_PARAMETER );

  /* SenseKey */
  *pucSenseKey = ptMsc->ucSenseKey;

  return( MSC_OK );
 EXT:
  return( MSC_NG );
}


/*
  コールバック関数セット
    引数
      ulIdDev       デバイスID
      ptMscCbs      コールバック関数群
      psError       エラーコード格納先ポインタ
    戻値
      なし
*/
void usb_MSC_vSetCallback( uint32_t ulIdDev, usb_MSC_typeCallbacks* ptMscCbs )
{
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;

  USB_TRACE_ENTER( 0, usb_MSC_vSetCallback );

  /* 割り込み禁止 */
#if 0 /* 2006/10/20 一括で禁止/許可を行うように修正 田谷 */
  usb_TIMER_vDisIntr();
  USB_DIS_INTR();
#else
  usb_vDisableAllIntr();
#endif

  if( ptMsc != NULL && ptMscCbs != NULL )
    {
      memcpy( &ptMsc->tCallbacks, ptMscCbs, sizeof(usb_MSC_typeCallbacks) );
    }

  /* 割り込み許可 */
#if 0 /* 2006/10/20 一括で禁止/許可を行うように修正 田谷 */
  USB_ENA_INTR();
  usb_TIMER_vEnaIntr();
#else
  usb_vEnableAllIntr();
#endif

  USB_TRACE_LEAVE( 0, usb_MSC_vSetCallback );
}


/*
  デバイス切断
    引数
      ulIdDev       デバイスID
      pulIdPort     ポート ID 格納先ポインタ
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iDisconnect( uint32_t ulIdDev, uint32_t* pulIdPort, int16_t* psError )
{
  int16_t iRet;
  uint32_t ulIdDevice, ulIdPort = 0;
  MSC_typeMsc* ptMsc = (MSC_typeMsc*)ulIdDev;
  USBC_typeInterface* ptIface;
  USBC_typeDevice* ptDevice;

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT;
    }
#endif

  ERROR_IF_WITHCODE( ptMsc == NULL, EXT, psError, USB_MSC_PARAMETER );

  /* 状態チェック */
  iRet = iCheckState( ptMsc, 0, MSC_CHECK_COMM, psError );
  ERROR_IF( iRet != MSC_OK, EXT );

  ptIface = (USBC_typeInterface*)ptMsc->ulIdMsc;
  ERROR_IF_WITHCODE( ptIface == NULL || ptIface->ptDevice == NULL, EXT, psError, USB_MSC_PARAMETER );

  /* ポート ID 取得 */
  iRet = usb_USBD_iGetPortId( ptIface->ptDevice->ulIdDev, &ulIdPort, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  /* 切断実行 */
  iRet = usb_USBD_iDisconnectPort( ulIdPort, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  /*
    パラメータはデタッチ処理でクリアされる
  */

  /* ポート ID を返す */
  if( pulIdPort != NULL )
    *pulIdPort = ulIdPort;

  /* 割り込み許可 */
  USB_ENA_INTR();
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  return( MSC_NG );
}


/*
  デバイス再接続
    引数
      ulIdPort      ポート ID
      psError       エラーコード格納先ポインタ
    戻値
      MSC_OK: 正常終了,  MSC_NG: 異常終了
*/
int16_t usb_MSC_iConnect( uint32_t ulIdPort, int16_t* psError )
{
  int16_t iRet;

  /* 割り込み禁止 */
  USB_DIS_INTR();

#if defined( USB_CTX_SWT )
  /* UDB ドライバの割り込み処理が待ちの最中は使用不可 */
  if( usb_CTXSWT_blWaiting() != false )
    {
      SET_ERRORCODE( psError, USB_MSC_IN_USE );
      goto EXT;
    }
#endif

  /* 接続実行 */
  iRet = usb_USBD_iConnectPort( ulIdPort, psError );
  ERROR_IF( iRet != USB_OK, EXT );

  /* 割り込み許可 */
  USB_ENA_INTR();
  return( MSC_OK );
 EXT:
  USB_ENA_INTR();
  return( MSC_NG );
}


/* --- End of File --- */
