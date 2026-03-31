/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohcixfer.c 4200 2015-08-14 12:44:49Z oscarmo $ */

/*

  OHCI 転送処理

*/

#include <string.h>
#include "usb_ohci.h"
#include "usb_ohcireg.h"
#include "usb_ohcilib.h"
#include "usb_ohcimem.h"
#include "usb_ohcixfer.h"
#include "usb_ohciroothub.h"
#include "usb_usbd_subr.h" /* usb_USBD_vTransferDone() */

/* ========== DEFINES ========== */

/* 使用可能な帯域幅 (理論値) */
#ifdef USB_OHCI_FM_INTERVAL
#define USB_BANDWIDTH_AVAILABLE (USB_OHCI_FM_INTERVAL*9/80)
#else
#define USB_BANDWIDTH_AVAILABLE (1350)
#endif

/* ========== GLOBAL VARIABLES ========== */
#pragma section = "HC_RAM_OHCIMEM"

extern OHCI_typeOhci usb_OHCI_tOHCI;

/* ========== static variables ========== */
/* Root Hub 操作関数 */
static const usbd_pipe_methods_t OHCI_tROOT_CTRL_METHODS = {
	usb_OHCI_iRootCtrlStart,
	usb_OHCI_vRootCtrlAbort,
	usb_OHCI_vRootCtrlClose,
	0,
	0
};
static const usbd_pipe_methods_t OHCI_tROOT_INTR_METHODS = {
	usb_OHCI_iRootIntrStart,
	usb_OHCI_vRootIntrAbort,
	usb_OHCI_vRootIntrClose,
	0,
	0
};
/* 転送関数 */
static const usbd_pipe_methods_t OHCI_tDEVICE_CTRL_METHODS = {
	usb_OHCI_iCtrlStart,
	usb_OHCI_vCtrlAbort,
	usb_OHCI_vCtrlClose,
	0,
	0
};
static const usbd_pipe_methods_t OHCI_tDEVICE_BULK_METHODS = {
	usb_OHCI_iBulkStart,
	usb_OHCI_vBulkAbort,
	usb_OHCI_vBulkClose,
	usb_OHCI_vClearToggle,
	0
};
static const usbd_pipe_methods_t OHCI_tDEVICE_INTR_METHODS = {
	usb_OHCI_iIntrStart,
	usb_OHCI_vIntrAbort,
	usb_OHCI_vIntrClose,
	usb_OHCI_vClearToggle,
	0
};

/* ========== EXTERNS ========== */



/* ========== local functions ========== */

/*
  TD フラグ標準設定
*/
static void vSetTDFlags( OHCI_typeTd* ptTd, bool blShortOK, bool blRead, uint8_t ucIntr, uint8_t ucToggle )
{
	USB_TRACE_ENTER( 3, vSetTDFlags );

	ptTd->bit.R = (blShortOK == false) ? 0 : 1;					 /* Buffer Rounding */
	ptTd->bit.DP = (blRead == false) ? OHCI_TD_DIR_OUT : OHCI_TD_DIR_IN;
	ptTd->bit.CC = OHCI_TD_NOCC;
	ptTd->bit.DI = ucIntr;										  /* Delay Interrupt */
	ptTd->bit.T = ucToggle;										  /* データトグル */

	USB_TRACE_LEAVE( 3, vSetTDFlags );
}

/*
  TD バッファ設定
*/
static void vSetTDBuffer( OHCI_typeSoftTd* ptStd, OHCI_typeSoftTd* ptStdNext, void* pvBuffer, uint16_t usLen )
{
	OHCI_typeTd* ptTd = ptStd->ptTd;

	USB_TRACE_ENTER( 3, vSetTDBuffer );

	ptTd->dw.ulNextTD = DMAADDR( ptStdNext->ptTd );
	if( usLen == 0 )
		ptTd->dw.ulCurBufPnt = ptTd->dw.ulBufEnd = 0;
	else
		{
			ptTd->dw.ulCurBufPnt = DMAADDR( pvBuffer );
			ptTd->dw.ulBufEnd = ptTd->dw.ulCurBufPnt + usLen - 1;
		}
	ptStd->usLen = usLen;
	ptStd->nexttd = ptStdNext;

	USB_TRACE_LEAVE( 3, vSetTDBuffer );
}


/*
  データ TD 挿入
*/
static int16_t iInsertDataTd( usbd_xfer_t* ptXfer, OHCI_typeSoftTd* ptStdStart, OHCI_typeSoftTd** pptStdEnd, int16_t* psError )
{
	OHCI_typeSoftTd* ptStdNext = NULL,* ptStdCur = NULL;
	OHCI_typeTd tTdTemplate = {{ 0, 0, 0, 0 }};
	bool blRead;
	uint16_t usLen, usLenCur;
	uint32_t ulBufCur;

	USB_TRACE_ENTER( 3, iInsertDataTd );

	memset( &tTdTemplate, 0, sizeof(OHCI_typeTd) );

	ptStdCur = ptStdStart;
	ulBufCur = (uint32_t)ptXfer->pvBuffer;
	usLen = ptXfer->usLength;
	blRead = ((ptXfer->ptPipe->ptEndpoint->ptEdesc->bEndpointAddress & UE_DIR_IN) == 0) ? false : true;

	/* フラグ作成 */
	vSetTDFlags( &tTdTemplate, ((ptXfer->usFlags & USBD_SHORT_XFER_OK) == 0) ? false : true,
				 blRead, OHCI_TD_NOINTR, OHCI_TD_TOGGLE_CARRY );

	for(;;)
		{
			/* 末尾 TD 作成 */
			ptStdNext = usb_OHCI_ptAllocStd();
			ERROR_IF_WITHCODE( ptStdNext == NULL, EXT, psError, USBD_NOMEM );

			/* 1つの TD で転送できるサイズに分割 */
			usLenCur = OHCI_PAGE_SIZE * 2 - (uint16_t)OHCI_PAGE_FRACTION( ulBufCur );
			if( usLenCur >= usLen )
				{
					usLenCur = usLen;
				}
			else
				{
					/* Short Packet で転送が終了するので、
					   中途のデータ長は wMaxPacketSize の整数倍でなければならない */
					usLenCur -= usLenCur % USB_GETW(ptXfer->ptPipe->ptEndpoint->ptEdesc->wMaxPacketSize);
				}

			/* データ TD 作成 */
			ptStdCur->ptTd->dw.ulFlags = tTdTemplate.dw.ulFlags;
			vSetTDBuffer( ptStdCur, ptStdNext, (void*)ulBufCur, usLenCur );
			ptStdCur->usFlags = OHCI_ADD_LEN;
			ptStdCur->ptXfer = ptXfer;

			/* 残データ長が 0 になったら処理終了 */
			ERROR_IF_WITHCODE( usLen < usLenCur, EXT, psError, USBD_INVAL );
			usLen -= usLenCur;
			if( usLen == 0 )
				break;

			/* バッファ開始位置移動 */
			ulBufCur += usLenCur;
			/* 対象 TD 移動 */
			ptStdCur = ptStdNext;
		}

	/* バッファサイズが wMaxPacketSize の整数倍で、
	   かつ転送終了の合図のための Short Packet を要求されている場合、
	   末尾に 0 Length Packet を付加する */
	if( (ptXfer->usFlags & USBD_FORCE_SHORT_XFER) != 0 &&
		(ptXfer->usLength % USB_GETW(ptXfer->ptPipe->ptEndpoint->ptEdesc->wMaxPacketSize)) == 0 )
		{
			ptStdCur = ptStdNext;
			ptStdNext = usb_OHCI_ptAllocStd();
			ERROR_IF_WITHCODE( ptStdNext == NULL, EXT, psError, USBD_NOMEM );

			ptStdCur->ptTd->dw.ulFlags = tTdTemplate.dw.ulFlags;
			vSetTDBuffer( ptStdCur, ptStdNext, NULL, 0 );
			ptStdCur->ptXfer = ptXfer;
		}

	*pptStdEnd = ptStdCur;

	USB_TRACE_LEAVE( 3, iInsertDataTd );
	return( OHCI_OK );
  EXT:
	{
		OHCI_typeTd* ptTd;
		/* メモリ解放 */
		for( ptStdCur = ptStdStart->nexttd; ptStdCur != NULL; ptStdCur = ptStdNext )
			{
				ptStdNext = ptStdCur->nexttd;
				usb_OHCI_vFreeStd( ptStdCur );
			}
		ptTd = ptStdStart->ptTd;
		memset( ptStdStart->ptTd, 0, sizeof(OHCI_typeTd) );
		memset( ptStdStart, 0, sizeof(OHCI_typeSoftTd) );
		ptStdStart->ptTd = ptTd;
	}

	DEBUG_ERROR_CALL( 2, "OHCI:iInsertDataTd", psError );
	USB_TRACE_LEAVE( 3, iInsertDataTd );
	return( OHCI_NG );
}


/*
  転送中断
*/
static void vAbortXfer( OHCI_typeOhci* ptOhci, usbd_xfer_t* ptXfer, usbd_status status )
{
	int16_t sError = OHCI_OK;
	OHCI_typeXfer* ptOXfer = (OHCI_typeXfer*)ptXfer;
	OHCI_typeSoftTd* ptStd;

	USB_TRACE_ENTER( 3, vAbortXfer );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptXfer == NULL, EXT, &sError, OHCI_NG );

	/* ステータス */
	ptXfer->tStatus = status;

	/* タイマハンドラキャンセル */
	if( status != USBD_TIMEOUT && ptOXfer->ulIdTimer != 0 )
		{
			usb_TIMER_vCancelHandler( ptOXfer->ulIdTimer );
			ptOXfer->ulIdTimer = 0;
		}

	/* 関係 TD に削除フラグを立てる */
	ptStd = ptOXfer->ptStdHead;
	ERROR_IF( ptStd == NULL, EXT );
	ptOXfer->ptStdHead = NULL;
	for( ; ptStd != NULL; ptStd = ptStd->nexttd )
		{
			if( ptStd->ptXfer == ptXfer )
				{
					ptStd->usFlags |= OHCI_TD_DELETE;
				}
		}

	/* 未転送 TD 削除 */
	usb_OHCI_vDeleteTdsInXfer( ptOhci, ptXfer );

	/* 転送完了通知 */
	usb_USBD_vTransferDone( ptXfer );

 EXT:
	if( sError == OHCI_NG )
		DEBUG_ERROR_CALL( 2, "OHCI:vAbortXfer", NULL );
	USB_TRACE_LEAVE( 3, vAbortXfer );
}


/*
  パイプクローズ
*/
static void vClosePipe( usbd_pipe_t* ptPipe, OHCI_typeSoftEd* ptSedHead )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = (OHCI_typePipe*)ptPipe;
	OHCI_typeSoftEd* ptSed;

	USB_TRACE_ENTER( 3, vClosePipe );

	ptSed = ptOPipe->ptSed;

	/* 転送中ならば中断する */
	if( ptPipe->ptXfer != NULL )
		{
			vAbortXfer( ptOhci, ptPipe->ptXfer, USBD_CANCELLED );
		}

	/* リストから ED を取り除く */
	usb_OHCI_vRemoveEd( ptOPipe->ptSed, ptSedHead );

	/* HC が ED にアクセスしていないことを保証するための 1[ms] */
	usb_TIMER_vWaiMsec( 2 );

	/* ED の削除 */
	usb_OHCI_vFreeSed( ptOPipe->ptSed );
	ptOPipe->ptSed = NULL;

	USB_TRACE_LEAVE( 3, vClosePipe );
}


/*
	Interrupt 転送正式版用
*/
#if defined( USB_OHCI_FORMAL_INTR )

/* セットするノードの位置を検索 */
static int16_t iSearchNodePos( OHCI_typeOhci* ptOhci, uint8_t ucOrgIval, uint8_t* pucPos, uint8_t* pucSlots, uint16_t* pusBandwidth )
{
	uint8_t i, j;
	uint8_t ucIval, ucLow, ucHigh, ucSlots, ucPos = 0;
	uint16_t usBandwidth, usLeastBandwidth, usTemp;

	/* 不法な bInterval */
	if( ucOrgIval == 0 )
		return( OHCI_NG );

	/* bInterval の値を OHCI が使用できる値に置き換える */
	/* ucIval = 32, 16, 8, 4, 2, 1 */
	ucIval = OHCI_NUM_INTRS;
	while( ucIval > ucOrgIval )
		ucIval >>= 1;

	/* 指定転送間隔の ED をセットするノードに対応する配列の範囲を算出 */
	/* ucLow <= ucPos < ucHigh */
	ucLow = ucIval - 1;
	ucHigh = ucLow + ucIval;

	/* ED をセットするノードから繋がる末端ノードの数 */
	ucSlots = OHCI_NUM_INTRS / ucIval;

	/* 最も使用帯域の少ない経路のノードを検索 */
	for( i = ucLow, usLeastBandwidth = 0xffff; i < ucHigh; i++ )
		{
			/* 最大帯域の経路を検索 */
			for( j = 0, usBandwidth = 0; j < ucSlots; j++ )
				{
					usTemp = ptOhci->pusBwidthIntr[(i * ucSlots + j) % OHCI_NUM_INTRS];
					if( usTemp > usBandwidth )
						usBandwidth = usTemp;
				}
			/* 最小値の記録 */
			if( usBandwidth < usLeastBandwidth )
				{
					ucPos = i;
					usLeastBandwidth = usBandwidth;
				}
		}

	/* 戻り値 */
	*pucPos = ucPos;
	*pucSlots = ucSlots;
	*pusBandwidth = usLeastBandwidth;

	return( OHCI_OK );
}

typedef struct OHCI_tagIntrNode {
	OHCI_typeOhci* ptOhci;
	OHCI_typeSoftEd* ptSed;
	uint8_t ucPos;
} OHCI_typeIntrNode;


/* 木に ED を挿入する */
/* ptNode->ucPos は書き換わることに注意 */
static int16_t iLinkNode( OHCI_typeIntrNode* ptNode )
{
	OHCI_typeSoftEd* ptSedTemp;
	uint8_t ucPos = ptNode->ucPos;
	int16_t iRet;

	ptSedTemp = ptNode->ptOhci->pptSedIntr[ucPos];
	if( ptSedTemp != NULL )
		{
			uint8_t ucSlots = ptSedTemp->ptOPipe->u.tIntr.ucSlots;

			/* ノード上の末尾の ED からリンクする */
			for( ; ptSedTemp->next != NULL &&
						 ptSedTemp->next->ptOPipe != NULL &&
						 ucSlots == ptSedTemp->next->ptOPipe->u.tIntr.ucSlots;
					 ptSedTemp = ptSedTemp->next )
				;

			ptNode->ptSed->next = ptSedTemp->next;
			ptNode->ptSed->ptEd->dw.ulNextED = ptSedTemp->ptEd->dw.ulNextED;
			ptSedTemp->next = ptNode->ptSed;
			ptSedTemp->ptEd->dw.ulNextED = DMAADDR( ptNode->ptSed->ptEd );
		}
	else
		{
			if( ucPos >= 31 )
				{
					/* 子が存在しないので HCCA に直リンク */
					/* SoftED を検索 */
					uint32_t* pulPhyAddr = &ptNode->ptOhci->ptHcca->pulInterruptTable[ucPos - 31];
					do
						{
							ucPos = (ucPos - 1) >> 1;
							ptSedTemp = ptNode->ptOhci->pptSedIntr[ucPos];
						} while( ptSedTemp == NULL && ucPos > 0 );
					/* 発見した SoftED の正当性のチェック */
					if( ptSedTemp == NULL || DMAADDR( ptSedTemp->ptEd ) != *pulPhyAddr )
						{
							DEBUG_ERROR_CALL( 2, "iSetIntrEd: Driver Abnormal", NULL );
							goto EXT;
						}
					/* リンク */
					ptNode->ptSed->next = ptSedTemp;
					ptNode->ptSed->ptEd->dw.ulNextED = DMAADDR( ptSedTemp->ptEd );
					*pulPhyAddr = DMAADDR( ptNode->ptSed->ptEd );
				}
			else
				{
					/* 二つの子ノードを検索 */
					ptNode->ucPos = (ucPos << 1) + 1;
					iRet = iLinkNode( ptNode );
					ERROR_IF( iRet != OHCI_OK, EXT );
					ptNode->ucPos = (ucPos << 1) + 2;
					iRet = iLinkNode( ptNode );
					ERROR_IF( iRet != OHCI_OK, EXT );
				}
		}

	return( OHCI_OK );
 EXT:
	return( OHCI_NG );
}

/* 木から ED を取り除く */
/* ptNode->ucPos は書き換わることに注意 */
static int16_t iUnlinkNode( OHCI_typeIntrNode* ptNode )
{
	OHCI_typeSoftEd* ptSedTemp;
	uint8_t ucPos = ptNode->ucPos;
	int16_t iRet;

	ptSedTemp = ptNode->ptOhci->pptSedIntr[ucPos];
	if( ptSedTemp != NULL && ptSedTemp != ptNode->ptSed )
		{
			/* ED リストからリンクを外す */
			for( ; ptSedTemp->next != ptNode->ptSed && ptSedTemp->next != NULL; ptSedTemp = ptSedTemp->next )
				;
			if( ptSedTemp->next == NULL )
				{
					DEBUG_ERROR_CALL( 2, "iUnlinkNode: Linked ED Not Found", NULL );
					goto EXT;
				}
			ptSedTemp->next = ptNode->ptSed->next;
			ptSedTemp->ptEd->dw.ulNextED = ptNode->ptSed->ptEd->dw.ulNextED;
		}
	else
		{
			if( ptNode->ucPos >= 31 )
				{
					/* 子が存在しないので HCCA からのリンクを外す */
					if( ptNode->ptOhci->ptHcca->pulInterruptTable[ucPos - 31] == DMAADDR( ptNode->ptSed->ptEd ) )
						ptNode->ptOhci->ptHcca->pulInterruptTable[ucPos - 31] = ptNode->ptSed->ptEd->dw.ulNextED;
					else
						{
							DEBUG_ERROR_CALL( 2, "iUnlinkNode(): Linked ED Not Found", NULL );
							goto EXT;
						}
				}
			else
				{
					/* 二つの子ノードを検索 */
					ptNode->ucPos = (ucPos << 1) + 1;
					iRet = iUnlinkNode( ptNode );
					ERROR_IF( iRet != OHCI_OK, EXT );
					ptNode->ucPos = (ucPos << 1) + 2;
					iRet = iUnlinkNode( ptNode );
					ERROR_IF( iRet != OHCI_OK, EXT );
				}
		}

	return( OHCI_OK );
 EXT:
	return( OHCI_NG );
}

/* Interrupt パイプのクローズ */
static int16_t iCloseIntrPipe( usbd_pipe_t* ptPipe )
{
	int16_t iRet;
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = (OHCI_typePipe*)ptPipe;
	OHCI_typeSoftEd* ptSed = ptOPipe->ptSed,* ptSedTemp;
	uint8_t ucCnt, ucPos = ptOPipe->u.tIntr.ucPos, ucSlots = ptOPipe->u.tIntr.ucSlots;

	/* 引数チェック */
	ERROR_IF( ptSed == NULL || ucPos >= OHCI_NUM_INTR_NODES, EXT );

	/* 転送中ならば中断する	 */
	if( ptPipe->ptXfer != NULL )
		{
			vAbortXfer( ptOhci, ptPipe->ptXfer, USBD_CANCELLED );
		}

	/* リストから ED を取り除く */
	{
		/* 木からの除去 */
		OHCI_typeIntrNode tNode = { 0, 0, 0 };
		tNode.ptOhci = ptOhci;
		tNode.ptSed = ptSed;
		tNode.ucPos = ucPos;
		iRet = iUnlinkNode( &tNode );
		ERROR_IF( iRet != OHCI_OK, EXT );

		/* テーブルからの除去 */
		if( ptOhci->pptSedIntr[ucPos] == ptSed )
			{
				/* 親ノード検索 */
				ucCnt = ucPos;
				while( ucCnt != 0 )
					{
						ucCnt = (ucCnt - 1) >> 1;
						if( ptOhci->pptSedIntr[ucCnt] != NULL )
							break;
					}
				if( ptSed->next == ptOhci->pptSedIntr[ucCnt] )
					/* リストの次 ED と親ノードの ED が同じ場合、現ノードは空になる */
					ptOhci->pptSedIntr[ucPos] = NULL;
				else
					/* リストの次 ED と親ノードの ED が異なる場合、現ノードに次 ED をセット */
					ptOhci->pptSedIntr[ucPos] = ptSed->next;
			}
	}

	if( ptPipe->ptEndpoint != NULL && ptPipe->ptEndpoint->ptEdesc != NULL && ptPipe->ptDevice != NULL )
		{
			/* クローズするパイプの使用帯域 */
			uint16_t usBandwidth = USB_GETW( ptPipe->ptEndpoint->ptEdesc->wMaxPacketSize ) + 13;
			/* Low-Speed の場合 */
			if( ptPipe->ptDevice->cLowSpeed != 0 )
				usBandwidth *= 8;

		/* 関係する経路の使用帯域量から減算 */
			for( ucCnt = 0; ucCnt < ucSlots; ucCnt++ )
				ptOhci->pusBwidthIntr[(ucPos * ucSlots + ucCnt) % OHCI_NUM_INTRS] -= usBandwidth;
		}

	/* HC が ED にアクセスしていないことを保証するための 1[ms] */
	usb_TIMER_vWaiMsec( 2 );

	/* ED の削除 */
	usb_OHCI_vFreeSed( ptOPipe->ptSed );
	ptOPipe->ptSed = NULL;

	return( OHCI_OK );
 EXT:
	DEBUG_ERROR_CALL( 1, "iCloseIntrPipe", NULL );
	return( OHCI_NG );
}
#endif


/*
  Interrupt Endpoint セット
*/
static int16_t iSetIntrEd( OHCI_typeOhci* ptOhci, OHCI_typePipe* ptOPipe, uint8_t ucIval, int16_t* psError )
{
	OHCI_typeSoftEd* ptSed;
#if defined( USB_OHCI_FORMAL_INTR )
	uint8_t ucPos = 0, ucSlots = 0, ucCnt;
	int16_t iRet;
	uint16_t usCurBandwidth = 0, usBandwidth;
#endif

	USB_TRACE_ENTER( 3, iSetIntrEd );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptOhci == NULL || ptOPipe == NULL || ucIval == 0 ||
										 ptOPipe->ptSed == NULL || ptOPipe->tPipe.ptEndpoint == NULL ||
										 ptOPipe->tPipe.ptEndpoint->ptEdesc == NULL,
										 EXT, psError, USBD_INVAL );

	ptSed = ptOPipe->ptSed;

#if defined( USB_OHCI_FORMAL_INTR )
	/* 正式版 */
	/* オープンするパイプの必要帯域 */
	usBandwidth = USB_GETW( ptOPipe->tPipe.ptEndpoint->ptEdesc->wMaxPacketSize ) + 13;
	/* Low-Speed の場合 */
	if( ptOPipe->tPipe.ptDevice->cLowSpeed != 0 )
		usBandwidth *= 8;

	/* セットするノードの位置を検索 */
	iRet = iSearchNodePos( ptOhci, ucIval, &ucPos, &ucSlots, &usCurBandwidth );
	ERROR_IF_WITHCODE( iRet != OHCI_OK, EXT, psError, USBD_INVAL );

	/* 使用可能な帯域を超えたらエラー */
	ERROR_IF_WITHCODE( usCurBandwidth + usBandwidth > USB_BANDWIDTH_AVAILABLE, EXT, psError, USBD_IN_USE );

	/* ED を Interrupt Tree のノードにセット */
		{
			OHCI_typeIntrNode tNode = { 0, 0, 0 };
			tNode.ptOhci = ptOhci;
			tNode.ptSed = ptSed;
			tNode.ucPos = ucPos;

			/* 木構造のノードに挿入 */
			iRet = iLinkNode( &tNode );
			ERROR_IF_WITHCODE( iRet != OHCI_OK, EXT, psError, USBD_INVAL );

			/* Interrupt ED のテーブルにセット */
			if( ptOhci->pptSedIntr[ucPos] == NULL )
				ptOhci->pptSedIntr[ucPos] = ptSed;
		}

	/* 関係する経路の使用帯域量に加算 */
	{
		for( ucCnt = 0; ucCnt < ucSlots; ucCnt++ )
			ptOhci->pusBwidthIntr[(ucPos * ucSlots + ucCnt) % OHCI_NUM_INTRS] += usBandwidth;
	}

	/* ED の位置と先頭ノードの数を保存 */
	ptOPipe->u.tIntr.ucSlots = ucSlots;
	ptOPipe->u.tIntr.ucPos = ucPos;

#else
	/* 省略版 全ての割り込みを一定周期として扱う */
	/* HCCA にセットされている空の ED にリンクすることで HCCA から繋がる */
	usb_OHCI_vAddEd( ptSed, ptOhci->ptSedIntr );
#endif

	USB_TRACE_LEAVE( 3, iSetIntrEd );
	return( OHCI_OK );

  EXT:
	DEBUG_ERROR_CALL( 0, "OHCI:iSetIntrEd", NULL );
	USB_TRACE_LEAVE( 3, iSetIntrEd );
	return( OHCI_NG );
}


/*
  タイムアウト用タイマハンドラ
*/
static void vTransferTimeOut( uint32_t ulArg )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typeXfer* ptOXfer = (OHCI_typeXfer*)ulArg;
	usbd_xfer_t *ptXfer = (usbd_xfer_t*)ulArg;

	/* タイマハンドラ ID 破棄 */
	ptOXfer->ulIdTimer = 0;

	/* アボート */
	vAbortXfer( ptOhci, ptXfer, USBD_TIMEOUT );
}


/* ========== GLOBAL FUNCTIONS ========== */

/*
  デバイスリクエスト発行
*/
int16_t usb_OHCI_iDeviceRequest( usbd_xfer_t* ptXfer, int16_t* psError )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = NULL;
	usbd_device_t* ptDev = NULL;
	OHCI_typeSoftTd* ptStdSetup = NULL,* ptStdStat = NULL,* ptStdData = NULL,* ptStdNext = NULL,* ptStdTail = NULL;
	OHCI_typeSoftEd* ptSed = NULL;
	bool blRead;
	uint8_t ucAddr;
	uint16_t usLen;

	USB_TRACE_ENTER( 0, usb_OHCI_iDeviceRequest );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptXfer == NULL || ptXfer->ptPipe == NULL ||
										 ptXfer->ptPipe->ptDevice == NULL,
										  EXT, psError, USBD_INVAL );

	ptOPipe = (OHCI_typePipe*)ptXfer->ptPipe;
	ptDev = ptOPipe->tPipe.ptDevice;
	ucAddr = ptDev->ucAddress;
	blRead = ((ptXfer->ptRequest->bmRequestType & UT_READ) == 0) ? false : true;  /* 転送方向 */
	usLen = USB_GETW(ptXfer->ptRequest->wLength);
	ptSed = ptOPipe->ptSed;

	/* コントロール転送に必要な TD 作成 */
	ptStdSetup = ptOPipe->ptStdTail;
	ptStdStat = usb_OHCI_ptAllocStd();
	ptStdTail = usb_OHCI_ptAllocStd();
	ERROR_IF_WITHCODE( ptStdStat == NULL || ptStdTail == NULL, EXT, psError, USBD_NOMEM );

	/* デバイスのアドレスと最大パケットサイズを設定 */
	ptSed->ptEd->bit.FA = ucAddr;
	ptSed->ptEd->bit.MPS = USB_GETW(ptOPipe->tPipe.ptEndpoint->ptEdesc->wMaxPacketSize);

	ptStdNext = ptStdStat;

	/* データ長が 0 でなければ、DATA トランザクションをセット */
	if( usLen != 0 )
		{
			/* データ転送用 TD 確保 */
			ptStdData = usb_OHCI_ptAllocStd();
			ERROR_IF_WITHCODE( ptStdData == NULL, EXT, psError, USBD_NOMEM );

			vSetTDFlags( ptStdData->ptTd, ptXfer->usFlags & USBD_SHORT_XFER_OK, blRead, OHCI_TD_NOINTR, OHCI_TD_TOGGLE_1 );
			vSetTDBuffer( ptStdData, ptStdStat, ptXfer->pvBuffer, usLen );
			ptStdData->usFlags = OHCI_ADD_LEN;
			ptStdData->ptXfer = ptXfer;

			ptStdNext = ptStdData;
		}
	else
		ptStdNext = ptStdStat;

	/* SETUP トランザクション */
	vSetTDFlags( ptStdSetup->ptTd, false, false, OHCI_TD_NOINTR, OHCI_TD_TOGGLE_0 );
	vSetTDBuffer( ptStdSetup, ptStdNext, ptXfer->ptRequest, sizeof(usb_device_request_t) );
	ptStdSetup->ptTd->bit.DP = OHCI_TD_DIR_SETUP;
	ptStdSetup->ptXfer = ptXfer;

	/* STATUS トランザクション */
	vSetTDFlags( ptStdStat->ptTd, false, !blRead, 0, OHCI_TD_TOGGLE_1 );
	vSetTDBuffer( ptStdStat, ptStdTail, NULL, 0 );
	ptStdStat->ptXfer = ptXfer;
	ptStdStat->usFlags = OHCI_CALL_DONE;

	/* TD をハッシュに追加 */
	usb_OHCI_vHashAddTd( ptOhci, ptStdSetup );
	if( usLen != 0 )  usb_OHCI_vHashAddTd( ptOhci, ptStdData );
	usb_OHCI_vHashAddTd( ptOhci, ptStdStat );

	/* ED にセット */
	((OHCI_typeXfer*)ptXfer)->ptStdHead = ptStdSetup;
	ptOPipe->ptStdTail = ptStdTail;
	ptSed->ptEd->dw.ulTailP = DMAADDR( ptStdTail->ptTd );

	/* タイムアウト用タイマハンドラ登録 */
	if( ptXfer->tCallback != NULL )
		{
			OHCI_typeXfer* ptOXfer = (OHCI_typeXfer*)ptXfer;
			usb_TIMER_iSetHandler( vTransferTimeOut, (uint32_t)ptXfer, ptXfer->sTimeout, &ptOXfer->ulIdTimer );
		}

	/* sKip 解除 */
	ptSed->ptEd->bit.K = 0;

	/* Command - ControlListFilled */
	OHCI_WRITE( OHCI_COMMAND_STATUS, OHCI_CMD_CLF );

	return( OHCI_OK );

  EXT:
	/* メモリ解放 */
	if( ptStdData != NULL )	 usb_OHCI_vFreeStd( ptStdData );
	if( ptStdTail != NULL )	 usb_OHCI_vFreeStd( ptStdTail );
	if( ptStdStat != NULL )	 usb_OHCI_vFreeStd( ptStdStat );

	DEBUG_ERROR_CALL( 0, "iDeviceRequest", psError );
	USB_TRACE_LEAVE( 0, usb_OHCI_iDeviceRequest );
	return( OHCI_NG );
}


/*
  パイプオープン
*/
usbd_status usb_OHCI_iOpen( usbd_pipe_t* ptPipe )
{
	int16_t sError = USBD_INVAL, iRet;
	uint8_t cAddr;
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = (OHCI_typePipe*)ptPipe;
	OHCI_typeSoftEd* ptSed = NULL;
	OHCI_typeSoftTd* ptStd = NULL;
	usb_endpoint_descriptor_t* ptDescEp = NULL;
	usbd_device_t* ptDevice = NULL;

	USB_TRACE_ENTER( 0, usb_OHCI_iOpen );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptPipe == NULL || ptPipe->ptEndpoint == NULL, EXT, &sError, USBD_INVAL );

	ptDescEp = ptPipe->ptEndpoint->ptEdesc;
	ptDevice = ptPipe->ptDevice;

	ERROR_IF_WITHCODE( ptDescEp == NULL || ptDevice == NULL, EXT, &sError, USBD_INVAL );

	cAddr = ptDevice->ucAddress;

	/* 対象が Root Hub であれば */
	if( cAddr == ptOhci->ucDevAddr )
		{
			/* Root Hub メソッド選択 */
			switch( ptDescEp->bEndpointAddress )
				{
				case USB_CONTROL_ENDPOINT:
					ptPipe->tMethods = OHCI_tROOT_CTRL_METHODS;
					break;
				case UE_DIR_IN | OHCI_INTR_ENDPT:
					ptPipe->tMethods = OHCI_tROOT_INTR_METHODS;
					break;
				default:
					sError = USBD_INVAL;
					goto EXT;
				}
		}
	else
		{
			/* Soft ED, TD 生成 */
			ptSed = usb_OHCI_ptAllocSed();
			ptStd = usb_OHCI_ptAllocStd();
			ERROR_IF_WITHCODE( ptSed == NULL || ptStd == NULL, EXT, &sError, USBD_NOMEM );

			ptOPipe->ptSed = ptSed;
			ptOPipe->ptStdTail = ptStd;	  /* 空 TD を末尾(兼先頭)に追加 */
#if defined( USB_OHCI_FORMAL_INTR )
			ptSed->ptOPipe = ptOPipe;
#endif

			/* Endpoint の設定 */
			{
				ohci_ed_t* ptEd = ptSed->ptEd;
				ptEd->bit.MPS = USB_GETW(ptDescEp->wMaxPacketSize);				/* Maximum Packet Size */
				ptEd->bit.F = ((ptDescEp->bmAttributes & UE_XFERTYPE) == UE_ISOCHRONOUS) ?
					OHCI_ED_FORMAT_ISO : OHCI_ED_FORMAT_GEN ;		  /* Format */
				ptEd->bit.K = 1;												/* sKip */
				ptEd->bit.S = (ptDevice->cLowSpeed != 0) ? OHCI_ED_SPEED : 0;	 /* Speed */
				ptEd->bit.D = OHCI_ED_DIR_TD;									/* Direction */
				ptEd->bit.EN = ptDescEp->bEndpointAddress;						/* Endpoint Number */
				ptEd->bit.FA = cAddr;											/* Function Address */
				ptEd->dw.ulHeadP = ptEd->dw.ulTailP = DMAADDR( ptStd->ptTd );
			}

			switch( ptDescEp->bmAttributes & UE_XFERTYPE )
				{
				case UE_CONTROL:
					ptPipe->tMethods = OHCI_tDEVICE_CTRL_METHODS;
					usb_OHCI_vAddEd( ptSed, ptOhci->ptSedCtrlHead );
					break;

				case UE_INTERRUPT:
					ptPipe->tMethods = OHCI_tDEVICE_INTR_METHODS;
					iRet = iSetIntrEd( ptOhci, ptOPipe, ptDescEp->bInterval, &sError );
					ERROR_IF( iRet != OHCI_OK, EXT );
					break;

				case UE_ISOCHRONOUS:
					sError = USBD_INVAL;
					goto EXT;

				case UE_BULK:
					ptPipe->tMethods = OHCI_tDEVICE_BULK_METHODS;
					usb_OHCI_vAddEd( ptSed, ptOhci->ptSedBulkHead );
					break;

				default:
					sError = USBD_INVAL;
					goto EXT;
				}
		}

	USB_TRACE_LEAVE( 0, usb_OHCI_iOpen );
	return( USBD_NORMAL_COMPLETION );
  EXT:
	/* メモリ解放 */
	if( ptStd != NULL )	 usb_OHCI_vFreeStd( ptStd );
	if( ptSed != NULL )	 usb_OHCI_vFreeSed( ptSed );

	DEBUG_ERROR_CALL( 0, "OHCIOpen", &sError );
	USB_TRACE_LEAVE( 0, usb_OHCI_iOpen );
	return( sError );
}


/* ----- Control 転送 ----- */

/*
  Control 転送開始
*/
usbd_status usb_OHCI_iCtrlStart( usbd_xfer_t* ptXfer )
{
	int16_t sError = USBD_INVAL, iRet;
	int32_t lTime1, lTime2;
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;

	USB_TRACE_ENTER( 0, usb_OHCICtrlStart );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptXfer == NULL, EXT, &sError, USBD_INVAL );

	/* デバイスリクエスト発行 */
	iRet = usb_OHCI_iDeviceRequest( ptXfer, &sError );
	ERROR_IF( iRet != OHCI_OK, EXT );

#if !defined( USB_NO_POLLING )
	/* 転送完了待ち */
	lTime1 = usb_TIMER_lGetTime();

#if defined( USB_DEBUG )
	if( (ptOhci->ulEnaIntrs & OHCI_INTR_RHSC) == 0 )
		{
			DEBUG_ERROR_CALL( 3, "Recursive DeviceRequest", NULL );
		}
#endif

	usb_OHCI_vRhscAble( ptOhci, false );
	for( ;; )
		{
			usb_OHCI_vIntr();  /* ポーリング */

			if( ptXfer->cDone != false )
				break;

			MSEC_WAIT( 0 );

			/* タイムアウトチェック */
			lTime2 = usb_TIMER_lGetTime();
			if( lTime1 > lTime2 )
				lTime1 -= 0x80000000;
			if( (lTime2 - lTime1) > ptXfer->sTimeout )
				{
				  /* 転送キャンセル (タイムアウト) */
					vAbortXfer( ptOhci, ptXfer, USBD_TIMEOUT );
					break;
				}
		}
	usb_OHCI_vRhscAble( ptOhci, true );

	sError = ptXfer->tStatus;
	ERROR_IF( sError != USBD_NORMAL_COMPLETION, EXT );
#endif

	USB_TRACE_LEAVE( 0, usb_OHCICtrlStart );
	return( USBD_NORMAL_COMPLETION );
  EXT:
	DEBUG_ERROR_CALL( 1, "OHCICtrlStart", &sError );
	USB_TRACE_LEAVE( 0, usb_OHCICtrlStart );
	return( sError );
}

/*
  Control 転送中断
*/
void usb_OHCI_vCtrlAbort( usbd_xfer_t* ptXfer)
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;

	USB_TRACE_ENTER( 0, usb_OHCICtrlAbort );

	vAbortXfer( ptOhci, ptXfer, USBD_CANCELLED );

	USB_TRACE_LEAVE( 0, usb_OHCICtrlAbort );
}

/*
  Control パイプクローズ
  OHCIOpen() に対応
*/
void usb_OHCI_vCtrlClose( usbd_pipe_t* ptPipe )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = (OHCI_typePipe*)ptPipe;

	USB_TRACE_ENTER( 0, usb_OHCICtrlClose );

	/* 引数チェック */
	ERROR_IF( ptPipe == NULL || ptOPipe->ptSed == NULL || ptOPipe->ptStdTail == NULL, EXT );

	/* パイプクローズ */
	vClosePipe( ptPipe, ptOhci->ptSedCtrlHead );

	/* ダミー TD 削除 */
	usb_OHCI_vFreeStd( ptOPipe->ptStdTail );

	USB_TRACE_LEAVE( 0, usb_OHCICtrlClose );
	return;
  EXT:
	DEBUG_ERROR_CALL( 1, "OHCICtrlClose", NULL );
	USB_TRACE_LEAVE( 0, usb_OHCICtrlClose );
}


/* ----- Bulk 転送 ----- */

/*
  Bulk 転送開始
*/
usbd_status usb_OHCI_iBulkStart( usbd_xfer_t* ptXfer )
{
	int16_t sError = USBD_INVAL, iRet;
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = NULL;
	OHCI_typeSoftEd* ptSed = NULL;
	OHCI_typeSoftTd* ptStdData = NULL,* ptStdTail = NULL;
	usb_endpoint_descriptor_t* ptDescEp = NULL;
	uint8_t ucAddr;
	bool blRead;

	USB_TRACE_ENTER( 0, usb_OHCIBulkStart );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptXfer == NULL || ptXfer->ptPipe == NULL ||
										 ptXfer->ptPipe->ptEndpoint == NULL ||
										 ptXfer->ptPipe->ptEndpoint->ptEdesc == NULL ||
										 ptXfer->ptPipe->ptDevice == NULL ||
										 ((OHCI_typePipe*)ptXfer->ptPipe)->ptSed == NULL,
										 EXT, &sError, USBD_INVAL );

	ptOPipe = (OHCI_typePipe*)ptXfer->ptPipe;
	ptSed = ptOPipe->ptSed;
	ptDescEp = ptXfer->ptPipe->ptEndpoint->ptEdesc;
	blRead = ((ptDescEp->bEndpointAddress & UE_DIR_IN) == 0) ? false : true;
	ucAddr = ptOPipe->tPipe.ptDevice->ucAddress;

	/* デバイスアドレス更新 */
	ptSed->ptEd->bit.FA = ucAddr;

	/* データトランザクション */
	ptStdData = ptOPipe->ptStdTail;
	iRet = iInsertDataTd( ptXfer, ptStdData, &ptStdTail, &sError );
	ERROR_IF( iRet != OHCI_OK, EXT );

	/* 終了 TD */
	ptStdTail->ptTd->bit.DI = 1;
	ptStdTail->usFlags |= OHCI_CALL_DONE;
	ptStdTail = ptStdTail->nexttd;

	ptXfer->tStatus = /* USBD_IN_PROGRESS */ USBD_NORMAL_COMPLETION;

	/* ED をスケジュールに挿入 */
	{
		OHCI_typeSoftTd* ptStd = ptStdData;
		for( ; ptStd != NULL && ptStd != ptStdTail; ptStd = ptStd->nexttd )
			usb_OHCI_vHashAddTd( ptOhci, ptStd );
	}

	((OHCI_typeXfer*)ptXfer)->ptStdHead = ptStdData;
	ptOPipe->ptStdTail = ptStdTail;
	ptSed->ptEd->dw.ulTailP = DMAADDR( ptStdTail->ptTd );

	/* タイムアウト用タイマハンドラ登録 */
	{
		OHCI_typeXfer* ptOXfer = (OHCI_typeXfer*)ptXfer;
		usb_TIMER_iSetHandler( vTransferTimeOut, (uint32_t)ptXfer, ptXfer->sTimeout, &ptOXfer->ulIdTimer );
	}

	/* sKip 解除 */
	ptSed->ptEd->bit.K = 0;

	/* 転送開始 */
	OHCI_WRITE( OHCI_COMMAND_STATUS, OHCI_CMD_BLF );

	USB_TRACE_LEAVE( 0, usb_OHCIBulkStart );
	return( /* USBD_IN_PROGRESS */USBD_NORMAL_COMPLETION );
  EXT:
	DEBUG_ERROR_CALL( 0, "OHCIBulkStart", &sError );
	USB_TRACE_LEAVE( 0, usb_OHCIBulkStart );
	return( sError );
}

/*
  Bulk 転送中断
*/
void usb_OHCI_vBulkAbort( usbd_xfer_t* ptXfer)
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;

	USB_TRACE_ENTER( 0, usb_OHCIBulkAbort );

	vAbortXfer( ptOhci, ptXfer, USBD_CANCELLED );

	USB_TRACE_LEAVE( 0, usb_OHCIBulkAbort );
}

/*
  Bulk パイプクローズ
  OHCIOpen() に対応
*/
void usb_OHCI_vBulkClose( usbd_pipe_t* ptPipe )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = (OHCI_typePipe*)ptPipe;

	USB_TRACE_ENTER( 0, usb_OHCIBulkClose );

	/* 引数チェック */
	ERROR_IF( ptPipe == NULL || ptOPipe->ptSed == NULL || ptOPipe->ptStdTail == NULL, EXT );

	/* パイプクローズ */
	vClosePipe( ptPipe, ptOhci->ptSedBulkHead );

	/* ダミー TD 削除 */
	usb_OHCI_vFreeStd( ptOPipe->ptStdTail );

	USB_TRACE_LEAVE( 0, usb_OHCIBulkClose );
	return;
  EXT:
	DEBUG_ERROR_CALL( 1, "OHCIBulkClose", NULL );
	USB_TRACE_LEAVE( 0, usb_OHCIBulkClose );
}


/* ----- Interrupt 転送 ----- */

/*
  Interrupt 転送開始
*/
usbd_status usb_OHCI_iIntrStart( usbd_xfer_t* ptXfer )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = NULL;
	OHCI_typeSoftEd* ptSed = NULL;
	OHCI_typeSoftTd* ptStdData = NULL,* ptStdTail = NULL;
	int16_t sError = USBD_INVAL;
	bool blRead;
	uint16_t usLen;

	USB_TRACE_ENTER( 0, usb_OHCI_iIntrStart );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptXfer == NULL || ptXfer->ptPipe == NULL ||
										 ptXfer->ptPipe->ptEndpoint == NULL ||
										 ptXfer->ptPipe->ptEndpoint->ptEdesc == NULL ||
										 ptXfer->ptPipe->ptDevice == NULL ||
										 ptXfer->usLength > OHCI_PAGE_SIZE,
										 EXT, &sError, USBD_INVAL );

	ptOPipe = (OHCI_typePipe*)ptXfer->ptPipe;
	ptSed = ptOPipe->ptSed;
	usLen = ptXfer->usLength;
	blRead = ((ptXfer->ptPipe->ptEndpoint->ptEdesc->bEndpointAddress & UE_DIR_IN) == 0) ? false : true;

	ERROR_IF_WITHCODE( usLen == 0 || ptSed == NULL, EXT, &sError, USBD_INVAL );

	/* TD リストに新規 TD を挿入 */
	ptStdData = ptOPipe->ptStdTail;
	ptStdTail = usb_OHCI_ptAllocStd();
	ERROR_IF_WITHCODE( ptStdTail == NULL, EXT, &sError, USBD_NOMEM );
	ptStdTail->ptXfer = NULL;

	ptXfer->tStatus = /* USBD_IN_PROGRESS */ USBD_NORMAL_COMPLETION;

	/* TD 設定 */
	vSetTDFlags( ptStdData->ptTd, 1, blRead, 1, OHCI_TD_TOGGLE_CARRY );
	vSetTDBuffer( ptStdData, ptStdTail, ptXfer->pvBuffer, usLen );
	ptStdData->usFlags = OHCI_CALL_DONE | OHCI_ADD_LEN;
	ptStdData->ptXfer = ptXfer;

	/* ED をスケジュールに追加 */
	usb_OHCI_vHashAddTd( ptOhci, ptStdData );

	/* ED にセット */
	((OHCI_typeXfer*)ptXfer)->ptStdHead = ptStdData;
	ptOPipe->ptStdTail = ptStdTail;
	ptSed->ptEd->dw.ulTailP = DMAADDR( ptStdTail->ptTd );

	/* タイムアウト用タイマハンドラ登録 */
	{
		OHCI_typeXfer* ptOXfer = (OHCI_typeXfer*)ptXfer;
		usb_TIMER_iSetHandler( vTransferTimeOut, (uint32_t)ptXfer, ptXfer->sTimeout, &ptOXfer->ulIdTimer );
	}

	/* sKip 解除 */
	ptSed->ptEd->bit.K = 0;

	USB_TRACE_LEAVE( 0, usb_OHCI_iIntrStart );
	return( /* USBD_IN_PROGRESS */ USBD_NORMAL_COMPLETION );
  EXT:
	if( ptStdTail != NULL )
		usb_OHCI_vFreeStd( ptStdTail );

	USB_TRACE_LEAVE( 0, usb_OHCI_iIntrStart );
	DEBUG_ERROR_CALL( 0, "OHCIIntrStart", &sError );
	return( sError );
}

/*
  Interrupt 転送中断
*/
void usb_OHCI_vIntrAbort( usbd_xfer_t* ptXfer)
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;

	USB_TRACE_ENTER( 0, usb_OHCIIntrAbort );

	vAbortXfer( ptOhci, ptXfer, USBD_CANCELLED );

	USB_TRACE_LEAVE( 0, usb_OHCIIntrAbort );
}

/*
  Interrupt パイプクローズ
  OHCIOpen() に対応
*/
void usb_OHCI_vIntrClose( usbd_pipe_t* ptPipe )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = (OHCI_typePipe*)ptPipe;

	USB_TRACE_ENTER( 0, usb_OHCIIntrClose );

	/* 引数チェック */
	ERROR_IF( ptPipe == NULL || ptOPipe->ptSed == NULL || ptOPipe->ptStdTail == NULL, EXT );

	/* パイプクローズ */
#if defined( USB_OHCI_FORMAL_INTR )
	iCloseIntrPipe( ptPipe );
#else
	vClosePipe( ptPipe, ptOhci->ptSedIntr );
#endif

	/* ダミー TD 削除 */
	usb_OHCI_vFreeStd( ptOPipe->ptStdTail );

	USB_TRACE_LEAVE( 0, usb_OHCIIntrClose );
	return;
 EXT:
	DEBUG_ERROR_CALL( 1, "OHCIIntrClose", NULL );
	USB_TRACE_LEAVE( 0, usb_OHCIIntrClose );
}


/*
  トグルビットクリア
*/
void usb_OHCI_vClearToggle( usbd_pipe_t* ptPipe )
{

	OHCI_typePipe* ptOPipe = (OHCI_typePipe*)ptPipe;

	USB_TRACE_ENTER( 1, usb_OHCIClearToggle );

	if( ptOPipe != NULL )
		ptOPipe->ptSed->ptEd->bit.C = 0;

	USB_TRACE_LEAVE( 1, usb_OHCIClearToggle );
}


#if defined( USB_DEBUG )
/*
  TD スキャン
*/
int16_t usb_OHCI_sScanTds( void )
{
	int16_t i, sNumTds = 0;
	uint32_t ulCtrl, ulTemp;
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typeEd* pptEd[3] = { NULL, NULL, NULL },* ptEd;
	OHCI_typeTd* ptTd;

	/* サスペンド */
	ulCtrl = OHCI_READ( OHCI_CONTROL );
	OHCI_WRITE( OHCI_CONTROL, ulCtrl | OHCI_CTRL_HCFS_SUSPEND );
	usb_TIMER_vWaiMsec( 6 );

	/* TD スキャン */
	/* memset( pptEd, 0, 4 * 3 ); */
	if( (ulTemp = OHCI_READ( OHCI_BULK_HEAD_ED )) != 0 )
		pptEd[0] = (OHCI_typeEd*)CPUADDR( ulTemp );
	if( (ulTemp = OHCI_READ( OHCI_CONTROL_HEAD_ED )) != 0 )
		pptEd[1] = (OHCI_typeEd*)CPUADDR(ulTemp );
	if( (ulTemp = ptOhci->ptHcca->pulInterruptTable[0]) != 0 )
		pptEd[2] = (OHCI_typeEd*)CPUADDR(ulTemp );

	for( i = 0; i < 3; i++ )
		{
			for( ptEd = pptEd[i]; ptEd != NULL; ptEd = (ptEd->dw.ulNextED == 0) ? NULL : (OHCI_typeEd*)CPUADDR(ptEd->dw.ulNextED) )
				{
					if( (ptEd->dw.ulHeadP & OHCI_ED_HEADP_MASK) != (ptEd->dw.ulTailP & OHCI_ED_TAILP_MASK) )
						{
							sNumTds++;
							for( ptTd = (OHCI_typeTd*)CPUADDR(ptEd->dw.ulHeadP); ptTd != NULL && (uint32_t)ptTd != CPUADDR(ptEd->dw.ulTailP); ptTd = (ptTd->dw.ulNextTD == 0) ? NULL : (OHCI_typeTd*)CPUADDR(ptTd->dw.ulNextTD) )
								{
									sNumTds++;
								}
						}
				}
		}

	/* レジューム */
	ulCtrl = (ulCtrl & ~OHCI_CTRL_HCFS_MASK) | OHCI_CTRL_HCFS_OPERATIONAL;
	OHCI_WRITE( OHCI_CONTROL, ulCtrl );
	usb_TIMER_vWaiMsec( 6 );

	return( sNumTds );
}
#endif

/* --- End of File --- */
