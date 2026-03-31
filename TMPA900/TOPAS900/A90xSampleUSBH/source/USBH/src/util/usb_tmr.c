/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_tmr.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Timer

*/

#include "usb_tmr.h"
#include "usb_dbg.h"
#include "usb_intr.h"
#if defined( USB_CTX_SWT )
#include "usb_ctxswt.h"
#endif

/* ========== externs ========== */

/* ========== global variables ========== */
/* タイマ起動状態 */
static bool blTIMER_ON = false;
/* タイマカウンタ[ms] (最上位ビットはキャリーフラグ扱い) */
static volatile uint32_t ulTIMER;
/* タイマハンドラリスト */
static usb_slist_head_t tHDR_HEAD;
/* 残ウェイト時間 (アプリケーション用) */
static volatile int32_t lWAI_REMAIN;

#if defined( USB_CTX_SWT )
/* USB 割り込みハンドラ内待ち時間 */
static uint32_t ulWAIT = 0xffffffffUL;
#endif

/* タイマハンドラ構造体用メモリ領域 */
static usb_slist_head_t tBUF_HEAD;
static TIMER_typeHandler ptHDR_BUFFER[TIMER_HDR_MAX_NUM];


/* ========== local functions ========== */

/* タイマハンドラ構造体メモリ確保 */
static TIMER_typeHandler* ptAllocTimerHdr( void )
{
	TIMER_typeHandler* ptHdr;

	/* リストから構造体の実体を取得 */
	ptHdr = (TIMER_typeHandler*)SLIST_REMOVE_HEAD( &tBUF_HEAD );

	return( ptHdr );
}

/* タイマハンドラ構造体メモリ解放 */
static void vFreeTimerHdr( TIMER_typeHandler* ptHdr )
{
#if defined( USB_DEBUG )
	usb_slist_entry_t* ptList;
	for( ptList = tBUF_HEAD.first; ptList; ptList = ptList->next )
	{
		if( (uint32_t)ptList == (uint32_t)ptHdr )
			DEBUG_ERROR_CALL( 0, "vFreeTimerHdr", NULL );
	}
#endif

	/* リストに実体を返却 */
	SLIST_INSERT_TAIL( &tBUF_HEAD, ptHdr );
}


/*
  タイマハンドラ実行ポーリング
*/
static void vTimerPolling( void )
{
	TIMER_typeHandler* ptHdr;
	usb_slist_entry_t* ptEnt,* ptNextEnt;
	usb_TIMER_fnHdr vHandlerFn;
	uint32_t ulArg;

	/* 登録ハンドラチェック */
	while( tHDR_HEAD.first != NULL )
	{
		/* 指定時間経過 */
		if( ((TIMER_typeHandler*)tHDR_HEAD.first)->ulCount <= ulTIMER )
		{
			/* リストから外してコールバックを呼び出し */
			ptHdr = (TIMER_typeHandler*)SLIST_REMOVE_HEAD( &tHDR_HEAD );
			if( ptHdr != NULL )
			{
				/* メモリ解放 */
				vHandlerFn = ptHdr->vHdr;
				ulArg = ptHdr->ulArg;
				vFreeTimerHdr( ptHdr );

				/* ハンドラ実行 */
				vHandlerFn( ulArg );
			}
			else
			{
				DEBUG_ERROR_CALL( 3, "vTimerPolling", NULL );
				break;
			}
		}
		else
		{
			/* 検索終了 */
			break;
		}
	}
}


#if defined( USB_CTX_SWT )
/*
  タイマカウンタがオーバーフローしたときの処理
*/
static void vTimerOverflow( void )
{
	TIMER_typeHandler* ptHdr;

	/* 待ち時間調整 */
	if( ulWAIT != 0xffffffffUL )
	{
		ulWAIT &= ~TIMER_CARRY_FLAG;
	}

	/* タイマハンドラの時間調整 */
	SLIST_FOREACH( ptHdr, TIMER_typeHandler, &tHDR_HEAD )
	{
		if( ptHdr->ulCount < TIMER_CARRY_FLAG )
			ptHdr->ulCount = 0;
		else
			ptHdr->ulCount &= ~TIMER_CARRY_FLAG;
	}

	/* タイマカウンタ */
	ulTIMER &= ~TIMER_CARRY_FLAG;
}
#endif

/* ========== GLOBAL FUNCTIONS ========== */

/*
  タイマ初期化
*/
void usb_TIMER_vInitialize( void )
{
	int16_t i;

	/* タイマ停止 */
	usb_TIMER_vEndIntr();

	ulTIMER = 0;
#if defined( USB_CTX_SWT )
	ulWAIT = 0xffffffffUL;
#endif
	SLIST_INIT( &tHDR_HEAD );
	SLIST_INIT( &tBUF_HEAD );

	for( i = 0; i < TIMER_HDR_MAX_NUM; i++ )
	{
		/* タイマハンドラ構造体用メモリのリスト作成 */
		ptHDR_BUFFER[i].list.next = NULL;
		SLIST_INSERT_HEAD( &tBUF_HEAD, &ptHDR_BUFFER[i] );
	}

#if defined( USB_CTX_SWT )
	/* 簡易コンテキストスイッチ初期化 */
	usb_CTXSWT_vInitialize();
#endif

	/* タイマ起動 */
	blTIMER_ON = true;
	usb_TIMER_vStartIntr();
}


/*
  タイマ終了処理
*/
void usb_TIMER_vFinalize( void )
{
	/* タイマ停止 */
	usb_TIMER_vEndIntr();
	blTIMER_ON = false;

#if defined( USB_CTX_SWT )
	ulWAIT = 0xffffffffUL;
#endif

#if defined( USB_CTX_SWT )
	/* 簡易コンテキストスイッチ終了 */
	usb_CTXSWT_vFinalize();
#endif
}


/*
  タイマハンドラセット
*/
int16_t usb_TIMER_iSetHandler( usb_TIMER_fnHdr vHdr, uint32_t ulArg, int16_t sTime, uint32_t* pulIdTimer )
{
	TIMER_typeHandler* ptHdr = NULL;

	/* 引数チェック1 */
	if( pulIdTimer == NULL || vHdr == NULL )
		goto EXT;

	/* 待ち時間が負の値であれば、ハンドラをセットせずに終了する */
	if( sTime < 0 )
	{
		*pulIdTimer = 0;
		return( 0 );
	}

	/* メモリ確保 */
	ptHdr = ptAllocTimerHdr();
	if( ptHdr == NULL )  goto EXT;

	/* タイマハンドラ ID */
	*pulIdTimer = (uint32_t)ptHdr;

	/* ハンドラ、引数、開始時刻 */
	ptHdr->vHdr = vHdr;
	ptHdr->ulArg = ulArg;
	ptHdr->ulCount = ulTIMER + sTime;

	/* タイマ割り込み禁止 */
	usb_TIMER_vDisIntr();

	/* 起動時間の短い順にリストを作成 */
	{
		TIMER_typeHandler* ptCurHdr,* ptBefore = NULL,* ptAfter = NULL;

		/* リスト挿入箇所検索 */
		SLIST_FOREACH( ptCurHdr, TIMER_typeHandler, &tHDR_HEAD )
		{
			if( ptCurHdr->ulCount > ptHdr->ulCount )
			{
				ptAfter = ptCurHdr;
				break;
			}

			ptBefore = ptCurHdr;
		}

		/* ハンドラリスト追加 */
		if( ptBefore == NULL )
		{
			SLIST_INSERT_HEAD( &tHDR_HEAD, ptHdr );
		}
		else if( ptAfter == NULL)
		{
			SLIST_INSERT_TAIL( &tHDR_HEAD, ptHdr );
		}
		else
		{
			SLIST_INSERT_AFTER( &tHDR_HEAD, ptBefore, ptHdr );
		}
	}

	/* タイマ割り込み許可 */
	usb_TIMER_vEnaIntr();

	return( 0 );
EXT:
	DEBUG_ERROR_CALL( 0, "TIMER_iSetHandler", NULL );
	return( -1 );
}


/*
  タイマハンドラキャンセル
*/
void usb_TIMER_vCancelHandler( uint32_t ulIdTimer )
{
	TIMER_typeHandler* ptHdr;

	/* タイマ割り込み禁止 */
	usb_TIMER_vDisIntr();

	/* タイマハンドラ登録リストから除去 */
	ptHdr = (TIMER_typeHandler*)SLIST_REMOVE( &tHDR_HEAD, ulIdTimer );

	/* タイマ割り込み許可 */
	usb_TIMER_vEnaIntr();

	if( ptHdr == NULL )
	{
		DEBUG_ERROR_CALL( 0, "TIMER_vCancelHandler", NULL );
		return;
	}

	/* メモリ解放 */
	vFreeTimerHdr( ptHdr );
}


/*
  現在時刻ミリ秒取得 (0～0x7fffffff)
*/
int32_t usb_TIMER_lGetTime( void )
{
	return( (int32_t)(ulTIMER & 0x7fffffff) );
}


/*
  ミリ秒ウェイト
*/
void usb_TIMER_vWaiMsec( uint16_t usMs )
{
#if defined( USB_CTX_SWT )  /* コンテキストスイッチ使用待ち */
	bool blIntr = usb_CTXSWT_blIntrCtx();

	if( blIntr == false )
		/* アプリケーションスタックからの待ち */
	{
		lWAI_REMAIN = usMs;
		while( lWAI_REMAIN > 0 );
	}
	else
		/* USB 割り込みスタックからの待ち */
	{
		/* 待ち時間設定 */
		ulWAIT = ulTIMER + usMs;

		/* コンテキスト切り替え */
		usb_CTXSWT_vSlpIntrCtx();
	}
#else /* 通常待ち */
	uint32_t ulWAI_TRG_TIME;
	
	ulWAI_TRG_TIME = ulTIMER + usMs;
	while( ulTIMER < ulWAI_TRG_TIME )
		;
#endif
}


/*
  タイマ割り込み
*/
void usb_TIMER_vIntr( void )
{
	bool blDisIntr;

	/* タイマ未初期化状態 */
	if( blTIMER_ON == false )
		return;

	/* カウンタインクリメント */
	ulTIMER += TIMER_INTR_CYCLE_MS;

	/* アプリ用ウェイト時間デクリメント */
	lWAI_REMAIN -= TIMER_INTR_CYCLE_MS;

#if defined( USB_CTX_SWT )
	/* 待ち完了 */
	if( ulTIMER >= ulWAIT )     /* 2006/05/24 修正 田谷 '>' -> '>=' */
	{
		ulWAIT = 0xffffffffUL;

		/* コンテキスト復帰 */
		usb_CTXSWT_vChgIntrCtx( NULL );

		/* 上関数内で再び待ちが発生した場合、
         ulWAIT を書き換えた上で即座にここに戻ってくる */
		goto EXT;
	}

	if( ulWAIT != 0xffffffffUL )
	{
		/* コンテキストを切り替えての待ちの最中は、タイマハンドラ実行不可 */
		goto EXT;
	}
#endif

	/* タイマハンドラチェック */
	blDisIntr = usb_INTR_blDisable();
	if( blDisIntr == false )
	{
		/* 割り込み禁止中 (USBドライバ処理中) は実行不可 */
#if defined( USB_CTX_SWT )
		/* コンテキスト切り替え */
		usb_CTXSWT_vChgIntrCtx( vTimerPolling );
#else
		vTimerPolling();
#endif
	}

EXT: /* 2006/05/24 修正 田谷  追加 */

	/* キャリーフラグ(最上位ビット)ON */
	if( (ulTIMER & TIMER_CARRY_FLAG) != 0 )
	{
#if defined( USB_CTX_SWT )
		vTimerOverflow();
#endif
	}
}


#if defined( USB_CTX_SWT )
/*
  コンテキストを切り替えての待ちが存在しているか否かをチェック
*/
bool usb_CTXSWT_blWaiting( void )
{
	if( ulWAIT != 0xffffffffUL )
		return( true );
	return( false );
}

/*
  コンテキストを切り替えての待ちをキャンセル
    ホストドライバ終了時に usb_USBD_vFinalize() から呼び出す
*/
void usb_CTXSWT_vCancelWait( void )
{
	usb_vDisableAllIntr();

	ulWAIT = 0xffffffffUL;
	/* コンテキスト初期化 */
	usb_CTXSWT_vInitialize();

	usb_vEnableAllIntr();
}
#endif


#if defined( USB_DEBUG )
/* メモリチェック */
int16_t usb_TIMER_iMemCheck( void )
{
	int16_t iRet = 0;
	usb_slist_entry_t* ptList;

	for( ptList = tBUF_HEAD.first; ptList; ptList = ptList->next )
		iRet++;
	iRet = TIMER_HDR_MAX_NUM - iRet;

	return( iRet );
}
#endif

/* --- End of File --- */
