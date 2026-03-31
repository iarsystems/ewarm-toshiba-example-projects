/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohciinit.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI 初期化

*/

#include <string.h>
#include "usb_ohci.h"
#include "usb_ohcilib.h"
#include "usb_ohcimem.h"
#include "usb_ohcireg.h"

/* ========== DEFINES ========== */

#define OHCI_ENABLE_POWER_DELAY     5
#define OHCI_READ_DESC_DELAY        5

/* ========== GLOBAL VARIABLES ========== */

#pragma section = "HC_RAM_OHCIMEM"

OHCI_typeOhci usb_OHCI_tOHCI @ "HC_RAM_OHCIMEM";


/* ========== local functions ========== */

/*
  OHCI 構造体破棄
*/
static void vDeleteOhciStructure( OHCI_typeOhci* ptOhci )
{
	int16_t i;

	USB_TRACE_ENTER( 3, vDeleteOhciStructure );

	/* 引数チェック */
	ERROR_IF( ptOhci == NULL, EXT );

	/* ダミー割り込み ED 削除 */
#if defined( USB_OHCI_FORMAL_INTR )
	for( i = 0; i < OHCI_NUM_INTR_NODES; i++ )
		{
			if( ptOhci->pptSedIntr[i] != NULL )
				usb_OHCI_vFreeSed( ptOhci->pptSedIntr[i] );
		}
#else
	if( ptOhci->ptSedIntr != NULL )
		usb_OHCI_vFreeSed( ptOhci->ptSedIntr );
#endif

	/* ダミーバルク ED 削除 */
	if( ptOhci->ptSedBulkHead != NULL )
		usb_OHCI_vFreeSed( ptOhci->ptSedBulkHead );

	/* ダミーコントロール ED 削除 */
	if( ptOhci->ptSedCtrlHead != NULL )
		usb_OHCI_vFreeSed( ptOhci->ptSedCtrlHead );

	/* HCCA 領域解放*/
	if( ptOhci->ptHcca != NULL )
		usb_OHCI_vFreeHcca( ptOhci->ptHcca );

	/* OHCI 管理用構造体 */
	memset( ptOhci, 0, sizeof(OHCI_typeOhci) );

  EXT:
	USB_TRACE_LEAVE( 3, vDeleteOhciStructure );
}


/*
  OHCI 構造体作成
*/
static int16_t iCreateOhciStructure( OHCI_typeOhci** pptRetOhci, int16_t* psError )
{
	int16_t i;
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typeSoftEd* ptSed = NULL;

	USB_TRACE_ENTER( 3, iCreateOhciStructure );

	/* OHCI 管理用構造体 */
	memset( ptOhci, 0, sizeof(OHCI_typeOhci) );

	/* 引数チェック */
	ERROR_IF_WITHCODE( pptRetOhci == NULL, EXT, psError, USBD_INVAL );

	/* HCCA 領域確保 */
	ptOhci->ptHcca = usb_OHCI_ptAllocHcca();
	ERROR_IF_WITHCODE( ptOhci->ptHcca == NULL, EXT, psError, USBD_NOMEM );

	/* ダミーコントロール ED 生成 */
	ptOhci->ptSedCtrlHead = usb_OHCI_ptAllocSed();
	ERROR_IF_WITHCODE( ptOhci->ptSedCtrlHead == NULL, EXT, psError, USBD_NOMEM );
	ptOhci->ptSedCtrlHead->ptEd->bit.K = 1;

	/* ダミーバルク ED 生成 */
	ptOhci->ptSedBulkHead = usb_OHCI_ptAllocSed();
	ERROR_IF_WITHCODE( ptOhci->ptSedBulkHead == NULL, EXT, psError, USBD_NOMEM );
	ptOhci->ptSedBulkHead->ptEd->bit.K = 1;

	/* ダミー割り込み ED 生成 */
	ptSed = usb_OHCI_ptAllocSed();
	ERROR_IF_WITHCODE( ptSed == NULL, EXT, psError, USBD_NOMEM );
	ptSed->ptEd->bit.K = 1;

	/* ダミー割り込み ED セット */
#if defined( USB_OHCI_FORMAL_INTR )
	/* 正式版 */
	ptOhci->pptSedIntr[0] = ptSed;  /* RAM 節約のため先頭のみ */
#else
	/* 簡易版 */
	ptOhci->ptSedIntr = ptSed;
#endif
	for( i = 0; i < OHCI_NUM_INTRS; i++ )
		ptOhci->ptHcca->pulInterruptTable[i] = DMAADDR( ptSed->ptEd );

	/* 割り込み許可設定 */
	ptOhci->ulEnaIntrs = OHCI_INTR_MASK_NORMAL;

	/* 戻り値 */
	*pptRetOhci = ptOhci;

	USB_TRACE_LEAVE( 3, iCreateOhciStructure );
	return( OHCI_OK );

  EXT:
	vDeleteOhciStructure( ptOhci );

	DEBUG_ERROR_CALL( 0, "OHCI:iCreateOhciStructure", psError );
	USB_TRACE_LEAVE( 3, iCreateOhciStructure );
	return( OHCI_NG );
}


/*
  レジスタ初期化
*/
static int16_t iInitRegister( OHCI_typeOhci* ptOhci, int16_t* psError )
{
	int16_t i;
	uint32_t ulCtrl, ulStat, ulFrame, ulIval, ulHcr = 0, ulPer, ulDesca;

	USB_TRACE_ENTER( 3, iInitRegister );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptOhci == NULL, EXT, psError, USBD_INVAL );

	/* 初期の HC の動作モード */
	ulCtrl = OHCI_READ( OHCI_CONTROL );
#if 0  /* 今回の環境では不要 */
	/* 割り込み経路がSMIに設定されている場合、HCの制御権の移行を要求する */
	if( (ulCtrl & OHCI_CTRL_IR) != 0 )
		{
			/* SMM Active */
			/* OwnershipChangeRequest */
			ulStat = OHCI_READ( OHCI_COMMAND_STATUS );
			OHCI_WRITE( OHCI_COMMAND_STATUS, ulStat | OHCI_CMD_OCR );
			for( i = 0; i < 100; i++ )
				{
					MSEC_WAIT( 1 );
					ulCtrl = OHCI_READ( OHCI_CONTROL );
					if( (ulCtrl & OHCI_CTRL_IR) == 0 )
						{
							/* ハードウェアリセット */
							OHCI_WRITE( OHCI_CONTROL, OHCI_CTRL_HCFS_RESET );
							MSEC_WAIT( USB_BUS_RESET_DELAY );
							break;
						}
				}
		}
	else
#endif
		/* HC の状態が UsbOperational なら何もしない
		   UsbResume か UsbSuspend ならば UsbOperational に変更する*/
		if( ( ulCtrl & OHCI_CTRL_HCFS_MASK ) != OHCI_CTRL_HCFS_RESET )
			{
				if( ( ulCtrl & OHCI_CTRL_HCFS_MASK ) != OHCI_CTRL_HCFS_OPERATIONAL )
					{
						OHCI_WRITE( OHCI_CONTROL, OHCI_CTRL_HCFS_OPERATIONAL );
						MSEC_WAIT( USB_RESUME_DELAY );
					}
			}
		else
			{
				/* Controller was cold started. */
				MSEC_WAIT( USB_BUS_RESET_DELAY );
			}

	/* ハードウェアリセット */
	/* OHCI 仕様では必ずしも必要なリセットではないが、
	   リセットなしでは開始しないコントローラもある */
	OHCI_WRITE( OHCI_CONTROL, OHCI_CTRL_HCFS_RESET );
	MSEC_WAIT( USB_BUS_RESET_DELAY );

	ulIval = OHCI_FMI_IVAL( OHCI_READ( OHCI_FM_INTERVAL ) );
#if defined( USB_OHCI_FM_INTERVAL )
  ulIval = USB_OHCI_FM_INTERVAL;
#endif

	/* ソフトウェアリセット */
	/* これにより、ほとんどのレジスタが初期化され、
	   UsbSuspend 状態に移行する */
	OHCI_WRITE( OHCI_COMMAND_STATUS, OHCI_CMD_HCR );
	/* 通常ならばリセットは 10[us] で終了する */
	/* 念のため最大 10[ms] までループ */
	for ( i = 0; i < 10; i++ )
		{
			MSEC_WAIT( 1 );
			ulHcr = OHCI_READ( OHCI_COMMAND_STATUS ) & OHCI_CMD_HCR;
			if ( ulHcr == 0 )
				break;
		}
	ERROR_IF_WITHCODE( ulHcr != 0, EXT, psError, -1 );

	/* HC レジスタ群設定 */
	OHCI_WRITE( OHCI_HCCA, DMAADDR( ptOhci->ptHcca ) );
	OHCI_WRITE( OHCI_CONTROL_HEAD_ED, DMAADDR( ptOhci->ptSedCtrlHead->ptEd ) );
	OHCI_WRITE( OHCI_BULK_HEAD_ED, DMAADDR( ptOhci->ptSedBulkHead->ptEd ) );
	/* 割り込みマスク設定 */
	OHCI_WRITE( OHCI_INTERRUPT_DISABLE, OHCI_INTR_MASK_ALL );
	OHCI_WRITE( OHCI_INTERRUPT_ENABLE, ptOhci->ulEnaIntrs | OHCI_INTR_MIE );

	/* HC 動作開始 (UsbOperational に移行) */
	ulCtrl = OHCI_READ( OHCI_CONTROL );
	ulCtrl &= ~( OHCI_CTRL_CBSR_MASK | OHCI_CTRL_LES | OHCI_CTRL_HCFS_MASK | OHCI_CTRL_IR );
	ulCtrl |= OHCI_CTRL_PLE | OHCI_CTRL_CLE | OHCI_CTRL_BLE | OHCI_CTRL_CBSR_1_4 | OHCI_CTRL_HCFS_OPERATIONAL;
	OHCI_WRITE( OHCI_CONTROL, ulCtrl );

	/* HC 動作中に、最後のレジスタを設定する。
	   これはなるべく早く設定すべきだが、サスペンド状態では無視される */

	/* フレーム周期設定 */
	ulFrame = ( OHCI_READ( OHCI_FM_INTERVAL ) & OHCI_FMI_FIT ) ^ OHCI_FMI_FIT;
	ulFrame |= OHCI_FMI_CALC_FSMPS( ulIval ) | ulIval;
	OHCI_WRITE( OHCI_FM_INTERVAL, ulFrame );
	/* FmInterval から 10% OFF */
	ulPer = ulIval * 9 / 10;
	OHCI_WRITE( OHCI_PERIODIC_START, ulPer );

	/* ルートハブ初期化 */
#if 0
	/* NoOverCurrentProtection ビットを誤魔化して、チップバグを避ける */
	ulDesca = OHCI_READ( OHCI_RH_DESCRIPTOR_A );
	OHCI_WRITE( OHCI_RH_DESCRIPTOR_A, (ulDesca | OHCI_RHA_NPS) );
	OHCI_WRITE( OHCI_RH_STATUS, OHCI_RHS_LPSC );	  /* Enable port power */
	MSEC_WAIT ( OHCI_ENABLE_POWER_DELAY );
	OHCI_WRITE( OHCI_RH_DESCRIPTOR_A, ulDesca );
#else
	OHCI_WRITE( OHCI_RH_STATUS, OHCI_RHS_LPSC );	  /* Enable port power */
	MSEC_WAIT ( OHCI_ENABLE_POWER_DELAY );
	ulDesca = OHCI_READ( OHCI_RH_DESCRIPTOR_A );
	//lwi	OHCI_WRITE( OHCI_RH_DESCRIPTOR_A, ulDesca | OHCI_RHA_PSM | OHCI_RHA_OCPM );
   OHCI_WRITE( OHCI_RH_DESCRIPTOR_A, ulDesca | OHCI_RHA_PSM | OHCI_RHA_OCPM | OHCI_RHA_NOCP);
OHCI_WRITE( OHCI_RH_DESCRIPTOR_B, 0xffff0000 );
#endif

#if 0  /* 今回の環境では不要 */
	/* ある種のコントローラでは、ディスクリプタを再読する際にディレイが必要になる
	   (省くと異常な値を読んでしまう) */
	MSEC_WAIT ( OHCI_READ_DESC_DELAY );
#endif
	ptOhci->ucNdp = OHCI_RHA_NDP( OHCI_READ( OHCI_RH_DESCRIPTOR_A ) );

	USB_TRACE_LEAVE( 3, iInitRegister );
	return( OHCI_OK );

  EXT:
	DEBUG_ERROR_CALL( 0, "OHCI:iInitRegister", psError );
	USB_TRACE_LEAVE( 3, iInitRegister );
	return( OHCI_NG );
}


/*
  レジスタ終了処理
*/
static void vFinRegister( void )
{
	/* ルートハブ電源OFF */
	OHCI_WRITE( OHCI_RH_STATUS, OHCI_RHS_LPS );

	/* HC 動作終了 */
	OHCI_WRITE( OHCI_CONTROL, 0L );

	/* 割り込みマスク解除 */
	OHCI_WRITE( OHCI_INTERRUPT_DISABLE, OHCI_INTR_MASK_ALL | OHCI_INTR_MIE );

	/* 割り込みステータスクリア */
	OHCI_WRITE( OHCI_INTERRUPT_STATUS, OHCI_INTR_MASK_ALL );

	/* HCCA + ディスクリプタ解除 */
	OHCI_WRITE( OHCI_BULK_HEAD_ED, 0L );
	OHCI_WRITE( OHCI_CONTROL_HEAD_ED, 0L );
	OHCI_WRITE( OHCI_HCCA, 0L );
}

/* ========== GLOBAL FUNCTIONS ========== */

/*
  OHCI 初期化
*/
usbd_status usb_OHCI_iInitialize( void )
{
	int16_t iRet, sError = USBD_INVAL;
	uint32_t ulRev;
	OHCI_typeOhci* ptOhci = NULL;

	USB_TRACE_ENTER( 0, usb_OHCIInit );

	/* OHCI revision チェック */
	ulRev = OHCI_READ( OHCI_REVISION );
	ERROR_IF_WITHCODE( (ulRev & 0xff) != OHCI_CORRECT_REVISION, EXT, &sError, USBD_INVAL );

	/* メモリ領域初期化 */
	usb_OHCI_vInitMemory();

	/* OHCI 構造体生成 */
	iRet = iCreateOhciStructure( &ptOhci, &sError );
	ERROR_IF( iRet != OHCI_OK, EXT );

	/* レジスタ初期化 */
	iRet = iInitRegister( ptOhci, &sError );
	ERROR_IF( iRet != OHCI_OK, EXT );

	USB_TRACE_LEAVE( 0, usb_OHCIInit );
	return( USBD_NORMAL_COMPLETION );
  EXT:
	/* メモリ解放 */
	if( ptOhci != NULL )  vDeleteOhciStructure( ptOhci );

	DEBUG_ERROR_CALL( 0, "OHCIInit", &sError );
	USB_TRACE_LEAVE( 0, usb_OHCIInit );
	return( sError );
}


/*
  OHCI 終了処理
*/
void usb_OHCI_vFinalize( void )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;

	/* レジスタ終了処理 */
	vFinRegister();

	/* メモリ破棄 */
	vDeleteOhciStructure( ptOhci );
}


/* --- End of File --- */
