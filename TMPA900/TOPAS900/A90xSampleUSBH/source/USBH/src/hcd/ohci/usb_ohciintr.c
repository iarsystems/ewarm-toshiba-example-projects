/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohciintr.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI 割り込み処理

*/

#include "usb_ohci.h"
#include "usb_ohcilib.h"
#include "usb_ohcireg.h"
#include "usb_ohcimem.h"
#include "usb_ohciroothub.h"
#include "usb_usbd_subr.h" /* usb_USBD_vTransferDone() */

/* ========== GLOBAL VARIABLES ========== */

#pragma section = "HC_RAM_OHCIMEM"

extern OHCI_typeOhci usb_OHCI_tOHCI;

#if defined( USB_CHECK_COMM_QUALITY )
static uint32_t ulTRS_COUNT @ "HC_RAM_OHCIMEM"= 0;
static uint32_t ulTRS_ERR_COUNT @ "HC_RAM_OHCIMEM"= 0;
static uint32_t ulPKT_ERR_COUNT @ "HC_RAM_OHCIMEM"= 0;
#endif

/* ========== local functions ========== */


/* ========== GLOBAL FUNCTIONS ========== */

/*
  Done List 作成
*/
void usb_OHCI_vProcDoneList( OHCI_typeOhci* ptOhci, uint32_t ulDone )
{
	OHCI_typeSoftTd* ptStd = NULL,* ptStdDone = NULL,** pptStd = NULL;
	OHCI_typeSoftTd* ptStdDelay = NULL;
	bool blDelay = ((ptOhci->ulEnaIntrs & OHCI_INTR_RHSC) != 0) ? false : true;

	USB_TRACE_ENTER( 1, usb_OHCI_vProcDoneList );

	/* Done リスト作成 */
	for( ptStdDone = NULL; ulDone != 0; )
		{
			ptStd = usb_OHCI_ptHashFindTd( ptOhci, ulDone );
			if( ptStd == NULL )
				{
					DEBUG_ERROR_CALL( 3, "OHCI:vProcDoneHead", NULL );
					goto EXT;
				}

			/* RHSC が禁止されている場合、Control 以外の転送を遅延する */
			/* Control であれば ptRequest に実体がある */
			if( blDelay != false && ptStd->ptXfer != NULL && ptStd->ptXfer->ptRequest == NULL )
				{
					/* 遅延リスト */
					ptStd->dnext = ptStdDelay;
					ptStdDelay = ptStd;
				}
			else
				{
					ptStd->dnext = ptStdDone;
					ptStdDone = ptStd;
				}
			ulDone = ptStd->ptTd->dw.ulNextTD;
		}

	/* Done リスト設置 */
	for( pptStd = &ptOhci->ptStdDoneHead; *pptStd != NULL; pptStd = (OHCI_typeSoftTd**)&(*pptStd)->dnext )
		;
	*pptStd = ptStdDone;

	/* 遅延リスト設置 */
	if( blDelay != false )
		{
			for( pptStd = &ptOhci->ptStdDelayDoneHead; *pptStd != NULL; pptStd = (OHCI_typeSoftTd**)&(*pptStd)->dnext )
				;
			*pptStd = ptStdDelay;

			/* 次の SOF 割り込みで遅延リストを処理する */
			ptOhci->ulEnaIntrs |= OHCI_INTR_SF;
			OHCI_WRITE( OHCI_INTERRUPT_ENABLE, OHCI_INTR_SF );
		}

 EXT:
	USB_TRACE_LEAVE( 1, usb_OHCI_vProcDoneList );
}


/*
  転送完了処理
*/
void usb_OHCI_vProcTransferDone( OHCI_typeOhci* ptOhci, OHCI_typeSoftTd** pptStdDoneHead )
{
	OHCI_typeSoftTd *ptStd, *ptStdNext = NULL;
	usbd_xfer_t* ptXfer = NULL;
	OHCI_typeXfer* ptOXfer = NULL;
	uint8_t ucCc;
	uint16_t usLen;

	if( pptStdDoneHead == NULL || *pptStdDoneHead == NULL )
		return;

	USB_TRACE_ENTER( 0, usb_OHCI_vProcTransferDone );

	/* Done リストクリア */
	ptStd = *pptStdDoneHead;
	*pptStdDoneHead = NULL;

	/* Done リスト処理 */
	for( ; ptStd != NULL; ptStd = ptStdNext )
		{
			ptStdNext = ptStd->dnext;
			ptXfer = ptStd->ptXfer;
			ptOXfer = (OHCI_typeXfer*)ptXfer;

			/* 削除フラグ */
			if( (ptStd->usFlags & OHCI_TD_DELETE) != 0 )
				{
					usb_OHCI_vHashRemoveTd( ptOhci, ptStd );
					usb_OHCI_vFreeStd( ptStd );
					continue;
				}

			if( ptXfer == NULL )
				{
					DEBUG_ERROR_CALL( 3, "OHCI:vProcDoneHead", NULL );
					continue;
				}

			/* 転送はキャンセルされている (この条件に引っかかることはないはず) */
			if( ptXfer->tStatus == USBD_CANCELLED || ptXfer->tStatus == USBD_TIMEOUT )
				{
					DEBUG_ERROR_CALL( 3, "OHCI:vProcDoneHead", NULL );
					continue;
				}

			/* 実転送サイズ計算 */
			usLen = ptStd->usLen;
			if( ptStd->ptTd->bit.CBP != 0 )
				usLen -= (uint16_t)(ptStd->ptTd->dw.ulBufEnd - ptStd->ptTd->dw.ulCurBufPnt + 1);
			if( (ptStd->usFlags & OHCI_ADD_LEN) != 0 )
				ptXfer->usActLen += usLen;

#if defined( USB_CHECK_COMM_QUALITY )
			/* トランザクション回数 */
			ulTRS_COUNT++;
			/* パケット失敗回数 */
			ulPKT_ERR_COUNT += ptStd->ptTd->bit.EC;
#endif

			/* Condition Code によるエラー判別 */
			ucCc = (uint8_t)ptStd->ptTd->bit.CC;
			if( ucCc == OHCI_CC_NO_ERROR )
				{
					/* 先頭 TD 更新 */
					if( ptStd->nexttd != NULL && ptStd->nexttd->ptXfer == ptXfer )
						ptOXfer->ptStdHead = ptStd->nexttd;
					else
						ptOXfer->ptStdHead = NULL;

					/* 転送完了フラグ(最終TD) */
					if( (ptStd->usFlags & OHCI_CALL_DONE) != 0 )
						{
							ptXfer->tStatus = USBD_NORMAL_COMPLETION;

							/* タイムアウト用タイマハンドラ登録解除 */
							{
								if( ptOXfer->ulIdTimer != 0 )
									usb_TIMER_vCancelHandler( ptOXfer->ulIdTimer );
								ptOXfer->ulIdTimer = 0;
							}

							/* 転送完了通知 */
							usb_USBD_vTransferDone( ptXfer );
						}
					/* TD 削除 */
					usb_OHCI_vHashRemoveTd( ptOhci, ptStd );
					usb_OHCI_vFreeStd( ptStd );
				}
			else
				/* エラー発生 */
				{
					OHCI_typeSoftEd* ptSed = NULL;
					OHCI_typeSoftTd* ptStdTemp, ptStdTempNext;

#if defined( USB_CHECK_COMM_QUALITY )
					/* トランザクション失敗回数 */
					ulTRS_ERR_COUNT++;
#endif
#if defined( USB_DEBUG )
#if(0)
					DEBUG_ERROR_CALL( 0, "OHCI: CC error!\n", (int*)ucCc);
#else
					DEBUG_ERROR_CALL( 0, "OHCI: CC error!\n", (int16_t*)ucCc);
#endif
#endif

					/* --- TD の後始末 --- */
					ptStdTemp = ptStd->nexttd;
					usb_OHCI_vHashRemoveTd( ptOhci, ptStd );
					usb_OHCI_vFreeStd( ptStd );
					ptOXfer->ptStdHead = NULL;

					/* TD 削除フラグON */
					for( ; ptStdTemp != NULL; ptStdTemp = ptStdTemp->nexttd )
						{
							if( ptStdTemp->ptXfer == ptXfer )
								{
									ptStdTemp->usFlags |= OHCI_TD_DELETE;
								}
						}

					/* 未転送 TD 削除 */
					usb_OHCI_vDeleteTdsInXfer( ptOhci, ptXfer );

					if( ucCc == OHCI_CC_STALL )
						ptXfer->tStatus = USBD_STALLED;
					else
						ptXfer->tStatus = USBD_IOERROR;

					/* タイムアウト用タイマハンドラ登録解除 */
					{
						if( ptOXfer->ulIdTimer != 0 )
							usb_TIMER_vCancelHandler( ptOXfer->ulIdTimer );
						ptOXfer->ulIdTimer = 0;
					}

					/* 転送完了通知 */
					usb_USBD_vTransferDone( ptXfer );
				}
		}

	USB_TRACE_LEAVE( 0, usb_OHCI_vProcTransferDone );
}


/*
  割り込み処理
  転送完了割り込み時は true を、それ以外では false を返す
*/
void usb_OHCI_vIntr( void )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typeHcca* ptHcca = ptOhci->ptHcca;
	uint32_t ulIntrs = 0, ulEnaIntrs;
	volatile uint32_t ulDone = 0;

	USB_TRACE_ENTER( 0, usb_OHCI_vIntr );

	/* 転送完了リストヘッダ検出 */
	ulDone = ptHcca->ulDoneHead;
	if( ulDone != 0 )
		{
#if 1  /* 16bit アクセス問題回避コード */
			volatile uint32_t ulTemp = ptHcca->ulDoneHead;
			if( ulTemp != ulDone )
				{
					DEBUG_ERROR_CALL( 0, "OHCIIntr", NULL );
					ulDone = ptHcca->ulDoneHead;
				}
#endif

			if( (ulDone & ~OHCI_DONE_INTRS) != 0 )
				/* 割り込みステータス指定 */
				ulIntrs = OHCI_INTR_WDH;
			if( (ulDone & OHCI_DONE_INTRS) != 0 )
				{
					/* 割り込みステータス取得 */
					ulIntrs |= OHCI_READ( OHCI_INTERRUPT_STATUS );
					ulDone &= ~OHCI_DONE_INTRS;
				}
			ptHcca->ulDoneHead = 0;
		}
	else
		{
			/* 割り込みステータス取得 (転送完了を除く) */
			ulIntrs = OHCI_READ( OHCI_INTERRUPT_STATUS ) & ~OHCI_INTR_WDH;
		}

#if 0 /* 2006/10/05 削除 田谷 */
	/* 割り込み要因解除 */
	ulIntrs &= ~OHCI_INTR_MIE;
	OHCI_WRITE( OHCI_INTERRUPT_STATUS, ulIntrs );
#endif

	/* 許可されている割り込みがなければリターン */
	ulEnaIntrs = ulIntrs & ptOhci->ulEnaIntrs;
	if( ulEnaIntrs == 0 )
		goto EXT;

	if( (ulEnaIntrs & 0x00000010L) == 0x0000001L) {
		for(;;);
	}
	else {
	}

	
#if 1 /* 2006/10/05  田谷 */
	/* 以下のコードで処理予定の割り込み要因を解除 */
	OHCI_WRITE( OHCI_INTERRUPT_STATUS, ulEnaIntrs );
#endif

	/* Start of Frame Interrupt */
	if( (ulEnaIntrs & OHCI_INTR_SF) != 0 )
		{
			/* ハブ割り込み禁止中の遅延処理を実行 */
			if( (ptOhci->ulEnaIntrs & OHCI_INTR_RHSC) != 0 )
				{
					/* 遅延リスト処理 */
					usb_OHCI_vProcTransferDone( ptOhci, &ptOhci->ptStdDelayDoneHead );

					/* SOF 割り込み禁止 */
					ptOhci->ulEnaIntrs &= ~OHCI_INTR_SF;
					OHCI_WRITE( OHCI_INTERRUPT_DISABLE, OHCI_INTR_SF );
				}
		}

	/* Writeback Done Head Interrupt */
	if( (ulEnaIntrs & OHCI_INTR_WDH) != 0 )
		{
			/* Done リスト作成 */
			if( ulDone != 0 )
				usb_OHCI_vProcDoneList( ptOhci, ulDone & ~OHCI_DONE_INTRS );
			/* Done 処理 */
			usb_OHCI_vProcTransferDone( ptOhci, &ptOhci->ptStdDoneHead );
		}

	/* Unrecoverable Error Interrupt */
	if( (ulEnaIntrs & OHCI_INTR_UE) != 0 )
		{
			/* リセットによるエラー回復 */
			OHCI_WRITE( OHCI_CONTROL, OHCI_CTRL_HCFS_RESET );

			/* アプリケーションへの通知 (USBD経由) */
			usb_USBD_vRaiseUnrecoverableError();
		}

	/* Root Hub Status Change Interrupt */
	if( (ulEnaIntrs & OHCI_INTR_RHSC) != 0 )
		{
			if( ptOhci->ptXferIntr != NULL )
				{
					/* ルートハブ挿抜処理 */
					usb_OHCI_vRhsc( ptOhci, &ptOhci->ptXferIntr->tXfer);
				}
		}

  EXT:
	USB_TRACE_LEAVE( 0, usb_OHCI_vIntr );
	return;
}


#if defined( USB_CHECK_COMM_QUALITY )
/*
  通信品質記録リセット
*/
void usb_OHCI_vResetCommQualityLog( void )
{
	ulTRS_COUNT = 0;
	ulTRS_ERR_COUNT = 0;
	ulPKT_ERR_COUNT = 0;
}

/*
  トランザクション単位での通信品質チェック
  引数
  pulTrsCnt		トランザクション回数格納先
  pulTrsErrCnt	トランザクションエラー回数格納先
  pulPktErrCnt	パケットエラー回数格納先
*/
void usb_OHCI_vCheckCommQuality( uint32_t* pulTrsCnt, uint32_t* pulTrsErrCnt, uint32_t* pulPktErrCnt )
{
	if( pulTrsCnt != NULL )
		*pulTrsCnt = ulTRS_COUNT;
	if( pulTrsErrCnt != NULL )
		*pulTrsErrCnt = ulTRS_ERR_COUNT;
	if( pulPktErrCnt != NULL )
		*pulPktErrCnt = ulPKT_ERR_COUNT;
}
#endif

/* --- End of File --- */
