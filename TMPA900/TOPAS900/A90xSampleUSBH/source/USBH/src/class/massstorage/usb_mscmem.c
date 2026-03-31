/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_mscmem.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Mass Storage Class Driver メモリ管理

*/

#include "usb_mscmem.h"
#include "usb_queue.h"

/* ========== global variables ========== */

#pragma section = "HC_RAM_MSCMEM"
/* MSC 管理用構造体バッファ */
static MSC_typeMsc ptMSC_BUFFER[MSC_MAX_NUM] @ "HC_RAM_MSCMEM";
static MSC_typeMsc* ptMSC_FREE_HEAD @ "HC_RAM_MSCMEM";

/* シナリオリスト用構造体バッファ */
static MSC_typeScenario ptSCENARIO_BUFFER[MSC_MAX_NUM_SECENARIOS] @ "HC_RAM_MSCMEM";
static MSC_typeScenario* ptSCENARIO_FREE_HEAD @ "HC_RAM_MSCMEM";

/* SCSI コマンド 転送データ用バッファ */
static MSC_typeBuffer tTRANSFER_BUFFER @ "HC_RAM_MSCMEM";
static bool blTRANSFER_BUFFER @ "HC_RAM_MSCMEM";

/* スタック軽減用メモリ */
static union tagTempMemory {
  usb_MSC_typeCommandBlock tCmdBlk;
  USBC_typeCallbacks tCbs;
} tTEMPMEM_BUFFER @ "HC_RAM_MSCMEM";

static bool blTEMPMEM_BUFFER;

/* ========== local functions ========== */

/* ========== GLOBAL FUNCTIONS ========== */

/*
  MSC メモリ初期化
*/
void usb_MSC_vInitMemory( void )
{
  /* メモリ作成 */
  ptMSC_FREE_HEAD = NULL;
  ptSCENARIO_FREE_HEAD = NULL;
  USB_CREATE_LIST( ptMSC_FREE_HEAD, ptMSC_BUFFER, MSC_MAX_NUM );
  USB_CREATE_LIST( ptSCENARIO_FREE_HEAD, ptSCENARIO_BUFFER, MSC_MAX_NUM_SECENARIOS );

  blTRANSFER_BUFFER = false;
  blTEMPMEM_BUFFER = false;
}


/*
  MSC 管理用構造体確保
*/
MSC_typeMsc* usb_MSC_ptAllocMsc( void )
{
  MSC_typeMsc* ptMsc = NULL;

  /* リストから取り出し */
  USB_DEQUEUE_LIST( ptMSC_FREE_HEAD, ptMsc );

  return( ptMsc );
}

/*
  MSC 管理用構造体解放
*/
void usb_MSC_vFreeMsc( MSC_typeMsc* ptMsc )
{
  /* リストへ返却 */
  USB_ENQUEUE_LIST( ptMSC_FREE_HEAD, ptMsc );
}


/*
  MSC シナリオリスト用構造体確保
*/
MSC_typeScenario* usb_MSC_ptAllocScenario( void )
{
  MSC_typeScenario* ptScen;

  /* リストから取り出し */
  USB_DEQUEUE_LIST( ptSCENARIO_FREE_HEAD, ptScen );

  return( ptScen );
}

/*
  MSC シナリオリスト用構造体解放
*/
void usb_MSC_vFreeScenario( MSC_typeScenario* ptScen )
{
  /* リストへ返却 */
  USB_ENQUEUE_LIST( ptSCENARIO_FREE_HEAD, ptScen );
}

/*
  シナリオ削除
*/
void usb_MSC_vDeleteScenarioList( MSC_typeScenario* ptScenHead )
{
  MSC_typeScenario* ptTemp;

  for( ; ptScenHead; )
    {
      ptTemp = ptScenHead;
      ptScenHead = ptScenHead->next;
      usb_MSC_vFreeScenario( ptTemp );
    }
}

/*
  シナリオ作成
*/
MSC_typeScenario* usb_MSC_ptCreateScenarioList( uint8_t* pucScen, uint8_t ucLen )
{
  int16_t iCnt;
  MSC_typeScenario* ptHead = NULL,* ptTemp;

  for( iCnt = ucLen - 1, ptTemp = NULL; iCnt >= 0; iCnt--, ptTemp = ptHead )
    {
      /* メモリ確保 */
      ptHead = usb_MSC_ptAllocScenario();
      ERROR_IF( ptHead == NULL, EXT );

      /* リスト先頭に挿入 */
      ptHead->ucScenNo = pucScen[iCnt];
      ptHead->next = ptTemp;
    }

  return( ptHead );
 EXT:
  /* リスト削除 */
  usb_MSC_vDeleteScenarioList( ptTemp );
  return( NULL );
}

/*
  先頭にシナリオ追加
*/
MSC_typeScenario* usb_MSC_ptAddHeadScenario( MSC_typeScenario** pptHead, uint8_t ucScenNo )
{
  MSC_typeScenario* ptScen;

  /* 追加シナリオ作成 */
  ptScen = usb_MSC_ptCreateScenarioList( &ucScenNo, 1 );
  if( ptScen != NULL )
    {
      /* 追加 */
      ptScen->next = (*pptHead);
      *pptHead = ptScen;
    }

  return( ptScen );
}

/*
  次シナリオ取り出し
*/
MSC_typeScenario* usb_MSC_ptJumpNextScenario( MSC_typeScenario** pptHead )
{
  MSC_typeScenario* ptScen;

  if( (*pptHead) != NULL )
    {
      /* 先頭除去 */
      ptScen = *pptHead;
      *pptHead = (*pptHead)->next;

      /* メモリ解放 */
      usb_MSC_vFreeScenario( ptScen );
    }

  return( *pptHead );
}


/*
  転送時使用バッファ確保
*/
void* usb_MSC_pvAllocTransferBuffer( void )
{
  void* pvBuf = NULL;

  if( blTRANSFER_BUFFER == false )
    {
      pvBuf = &tTRANSFER_BUFFER;
      blTRANSFER_BUFFER =true;
    }

  return( pvBuf );
}

/*
  転送時使用バッファ解放
*/
void usb_MSC_vFreeTransferBuffer( void* pvBuf )
{
  if( pvBuf == &tTRANSFER_BUFFER )
    {
      blTRANSFER_BUFFER = false;
    }
}

/*
  スタック軽減用メモリ確保
*/
void* usb_MSC_pvAllocTempMemory( void )
{
  void* pvBuf = NULL;

  if( blTEMPMEM_BUFFER == false )
    {
      pvBuf = &tTEMPMEM_BUFFER;
      blTEMPMEM_BUFFER = true;
    }

  return( pvBuf );
}

/*
  スタック軽減用メモリ解放
*/
void usb_MSC_vFreeTempMemory( void* pvBuf )
{
  if( pvBuf == &tTEMPMEM_BUFFER )
    {
      blTEMPMEM_BUFFER = false;
    }
}


/*
  メモリ使用状態チェック
*/
#if defined( USB_DEBUG )
int16_t usb_MSC_iMemCheck( void )
{
  int16_t iScen, iMsc, iRet = 0;

  USB_NUM_CHECK_LIST( ptMSC_FREE_HEAD, iMsc );
  iRet += MSC_MAX_NUM - iMsc;

  USB_NUM_CHECK_LIST( ptSCENARIO_FREE_HEAD, iScen );
  iRet += MSC_MAX_NUM_SECENARIOS - iScen;

  return( iRet );
}
#endif

/* --- End of File --- */
