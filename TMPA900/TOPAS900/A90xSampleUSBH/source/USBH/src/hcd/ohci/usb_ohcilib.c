/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohcilib.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI Utility

*/

#include "usb_ohci.h"
#include "usb_ohcilib.h"
#include "usb_ohcimem.h"

/* ========== local functions ========== */


/* ========== GLOBAL FUNCTIONS ========== */
/*
  Endpoint Descriptor リスト追加
*/
void usb_OHCI_vAddEd( OHCI_typeSoftEd* ptSed, OHCI_typeSoftEd* ptHead )
{
	ptSed->next = ptHead->next;
	ptSed->ptEd->dw.ulNextED = ptHead->ptEd->dw.ulNextED;
	ptHead->next = ptSed;
	ptHead->ptEd->dw.ulNextED = DMAADDR( ptSed->ptEd );
}


/*
  Endpoint Descriptor リスト除去
*/
void usb_OHCI_vRemoveEd( OHCI_typeSoftEd* ptSed, OHCI_typeSoftEd* ptHead )
{
	OHCI_typeSoftEd* p;

	for( p = ptHead; p != NULL && p->next != ptSed; p = p->next );
	ERROR_IF( p == NULL, EXT );

	p->next = ptSed->next;
	p->ptEd->dw.ulNextED = ptSed->ptEd->dw.ulNextED;
	return;

  EXT:
	DEBUG_ERROR_CALL( 2, "OHCI:vRemoveEd", NULL );
}


/* 
   以下、転送完了割り込み後、DoneList から SoftTD (ソフト上でのTD管理に使用) を
   検索するための仕掛け。
   本来であればハッシュを利用して検索の効率化を計る箇所だが、現状ではハッシュは省
   略している。(使用する TD の数が少なければ必要ない)
*/

/*
  ハッシュ TD 追加
*/
void usb_OHCI_vHashAddTd( OHCI_typeOhci* ptOhci, OHCI_typeSoftTd* ptStd )
{
	ptStd->hnext.le_next = ptOhci->ptStdHashFirst;
	if( ptOhci->ptStdHashFirst != NULL )
		ptOhci->ptStdHashFirst->hnext.le_prev = &ptStd->hnext.le_next;
	ptOhci->ptStdHashFirst = ptStd;
	ptStd->hnext.le_prev = (struct OHCI_tagSoftTd**)&ptOhci->ptStdHashFirst;
}

/*
  ハッシュ TD 除去
*/
void usb_OHCI_vHashRemoveTd( OHCI_typeOhci* ptOhci, OHCI_typeSoftTd* ptStd )
{
	if( ptStd->hnext.le_next != NULL )
		ptStd->hnext.le_next->hnext.le_prev = ptStd->hnext.le_prev;
	*ptStd->hnext.le_prev = ptStd->hnext.le_next;
}

/*
  ハッシュ TD 検索
*/
OHCI_typeSoftTd* usb_OHCI_ptHashFindTd( OHCI_typeOhci* ptOhci, uint32_t ulHeadP )
{
	OHCI_typeSoftTd* ptStd = NULL;

	for( ptStd = ptOhci->ptStdHashFirst; ptStd != NULL; ptStd = ptStd->hnext.le_next )
		{
			if( DMAADDR( ptStd->ptTd ) == ulHeadP )
				return( ptStd );
		}
	return( NULL );
}


/*
  指定した xfer に属する未転送 TD の削除
*/
void usb_OHCI_vDeleteTdsInXfer( OHCI_typeOhci* ptOhci, usbd_xfer_t* ptXfer )
{
	OHCI_typePipe* ptOPipe;
	OHCI_typeSoftEd* ptSed;
	OHCI_typeEd* ptEd;
	OHCI_typeSoftTd* ptStd,* ptStdNext,* ptStdNewHead = NULL,* ptStdNewTail = NULL;

	ERROR_IF( ptOhci == NULL || ptXfer == NULL, EXT );

	ptOPipe = (OHCI_typePipe*)ptXfer->ptPipe;

	ERROR_IF( ptOPipe == NULL || ptOPipe->ptSed == NULL, EXT );

	ptSed = ptOPipe->ptSed;
	ptEd = ptSed->ptEd;

	/* ED sKip */
	ptEd->bit.K = 1;

	/* ED のスキップを保証するために 2[ms] 待ち */
	MSEC_WAIT( 2 );

	ptStd = usb_OHCI_ptHashFindTd( ptOhci, ptEd->dw.ulHeadP & OHCI_ED_HEADP_MASK );
	if( ptStd != NULL )
		{
			for( ; ptStd != NULL; ptStd = ptStdNext )
				{
					ptStdNext = ptStd->nexttd;
					if( ptStd->ptXfer == ptXfer )
						{
							/* 指定した xfer に属する TD 削除 */
							usb_OHCI_vHashRemoveTd( ptOhci, ptStd );
							usb_OHCI_vFreeStd( ptStd );
						}
					else
						{
							/* 新規リストの作成 */
							ptStd->nexttd = NULL;
							ptStd->ptTd->dw.ulNextTD = NULL;
							if( ptStdNewHead == NULL )
								{
									ptStdNewHead = ptStdNewTail = ptStd;
								}
							else
								{
									ptStdNewTail->nexttd = ptStd;
									ptStdNewTail->ptTd->dw.ulNextTD = DMAADDR( (uint32_t)ptStd->ptTd & OHCI_ED_HEADP_MASK );
									ptStdNewTail = ptStd;
								}
						}
				}

			/* TD 繋ぎ直し */
			ptEd->dw.ulHeadP &= ~OHCI_ED_HEADP_MASK;
			if( ptStdNewHead != NULL )		/* 2006/05/24 修正 田谷 NULLチェック追加 */
				ptEd->dw.ulHeadP |= DMAADDR( (uint32_t)ptStdNewHead->ptTd & OHCI_ED_HEADP_MASK );
			ptOPipe->ptStdTail = ptStdNewTail;
		}

	/* 処理再開 */
	ptEd->bit.H = 0;
	ptEd->bit.K = 0;
	return;
 EXT:
	DEBUG_ERROR_CALL( 2, "usb_OHCI_vDeleteTdsInXfer", NULL );
}

/* --- End of File --- */
