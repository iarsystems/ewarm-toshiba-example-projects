/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohcimem.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI メモリ管理

*/

#include <string.h>
#include "usb_ohci.h"
#include "usb_ohcimem.h"
#include "usb_dbg.h"
#include "usb_queue.h"
#if defined( PRINTF_ON )
#include <stdio.h>
#endif

/* ========== DEFINES ========== */
#define OHCI_MAX_HCCA_NUM 1			/* HCCA 構造体最大数 */

/* リスト追加 (ED,TD用) */
#define OHCI_ENQUEUE_LIST( head, next, add )  { (add)->next = head;	 head = add; }
/* リスト除去 (ED,TD用) */
#define OHCI_DEQUEUE_LIST( head, next, ret )  { ret = head; if( ret != NULL ) head = ret->next; }
/* リスト作成 (ED,TD用) */
#define OHCI_CREATE_LIST( head, next, buffer, num ) \
  { int16_t i; for( i = 0; i < num; i++ ){ OHCI_ENQUEUE_LIST( head, next, &buffer[i] ); } }
/* リスト要素数チェック (ED,TD用) */
#define OHCI_NUM_CHECK_LIST( head, next, type, count ) \
  { type* temp; for( count = 0, temp = head; temp != NULL; count++, temp = temp->next ); }

/* 構造体関連付け (ED,TD用) */
#define ASSOCIATE_SOFT_ENTITY( soft, m_pnt, entity, num ) \
  { int16_t i; for( i = 0; i < num; i ++ ) { soft[i].m_pnt = (void*)CPUADDR(&entity[i]); } }

typedef int8_t type16Byte[16];
typedef int8_t type256Byte[256];


/* ========== global variables ========== */

#pragma section = "HC_RAM_OHCIMEM"
/* 各種空き構造体リスト */
static OHCI_typePipe*	ptPIPE_FREE_HEAD @ "HC_RAM_OHCIMEM";	 /* 空き Pipe リスト */
static OHCI_typeXfer*	ptXFER_FREE_HEAD @ "HC_RAM_OHCIMEM";	 /* 空き Xfer リスト */
static OHCI_typeSoftEd* ptSED_FREE_HEAD @ "HC_RAM_OHCIMEM";	 /* 空き ED リスト */
static OHCI_typeSoftTd* ptSTD_FREE_HEAD @ "HC_RAM_OHCIMEM";	 /* 空き TD リスト */

/* 各種構造体メモリ領域 */
static OHCI_typePipe	ptPIPE_BUFFER[OHCI_MAX_PIPES] @ "HC_RAM_OHCIMEM";	 /* Pipe バッファ */
static OHCI_typeXfer	ptXFER_BUFFER[OHCI_MAX_XFERS] @ "HC_RAM_OHCIMEM";	 /* Xfer バッファ */
static OHCI_typeSoftEd	ptSED_BUFFER[OHCI_MAX_EDS] @ "HC_RAM_OHCIMEM";		 /* SoftED バッファ */
static OHCI_typeSoftTd	ptSTD_BUFFER[OHCI_MAX_TDS] @ "HC_RAM_OHCIMEM";		 /* SoftTD バッファ */

/* 境界調整の必要があるメモリ */
/* FPGA_RAM の一部を予約して境界調整を行っている */
#pragma section = "HC_RAM"
static type256Byte		ptHCCA_BUFFER[OHCI_MAX_HCCA_NUM] @ "HC_RAM"; /* HCCA バッファ(一個)(256byte境界) */
static type16Byte		ptED_BUFFER[OHCI_MAX_EDS] @ "HC_RAM";	 /* ED バッファ (16byte境界) */
static type16Byte		ptTD_BUFFER[OHCI_MAX_TDS] @ "HC_RAM";	 /* TD バッファ (16byte境界) */
#pragma section = "HC_RAM_OHCIMEM"
//#pragma arm section zidata

/* HCCA フラグ */
/* 2006/05/24 修正 田谷 場所移動 */
static bool blHCCA @ "HC_RAM_OHCIMEM";


/* ========== local functions ========== */

/* ========== GLOBAL FUNCTIONS ========== */

/*
  メモリ初期化
*/
void usb_OHCI_vInitMemory( void )
{
	OHCI_typeEd* ptEd = NULL;
	OHCI_typeTd* ptTd = NULL;

#if defined( USB_DEBUG )
	/* 境界チェック */
	if( (((uint32_t)ptED_BUFFER & 0xfUL) != 0)
		|| (((uint32_t)ptTD_BUFFER & 0xfUL) != 0)
		|| (((uint32_t)ptHCCA_BUFFER & 0xffUL) != 0) )
		{
			DEBUG_ERROR_CALL( 3, "usb_OHCI_vInitMemory", NULL);
		}

#endif

	/* ヘッダ初期値 */
	ptPIPE_FREE_HEAD = NULL;
	ptXFER_FREE_HEAD = NULL;
	ptSED_FREE_HEAD = NULL;
	ptSTD_FREE_HEAD = NULL;

	/* ED <-> SoftED, TD <-> SoftTD 結び付け */
	ASSOCIATE_SOFT_ENTITY( ptSED_BUFFER, ptEd, ptED_BUFFER, OHCI_MAX_EDS );
	ASSOCIATE_SOFT_ENTITY( ptSTD_BUFFER, ptTd, ptTD_BUFFER, OHCI_MAX_TDS );

	/* 各種構造体リスト作成 */
	USB_CREATE_LIST( ptPIPE_FREE_HEAD, ptPIPE_BUFFER, OHCI_MAX_PIPES );
	USB_CREATE_LIST( ptXFER_FREE_HEAD, ptXFER_BUFFER, OHCI_MAX_XFERS );
	OHCI_CREATE_LIST( ptSED_FREE_HEAD, next, ptSED_BUFFER, OHCI_MAX_EDS );
	OHCI_CREATE_LIST( ptSTD_FREE_HEAD, nexttd, ptSTD_BUFFER, OHCI_MAX_TDS );

	/* HCCA フラグ初期化 */
	/* 2006/05/24 修正 田谷 場所移動 */
	blHCCA = false;
}



/*
  Pipe 構造体確保
*/
usbd_pipe_t* usb_OHCI_ptAllocPipe( void )
{
	OHCI_typePipe* ptOPipe;

	/* Pipe リストから1つ取り出してリターン */
	USB_DEQUEUE_LIST( ptPIPE_FREE_HEAD, ptOPipe )

		/* 0 クリア */
		if( ptOPipe != NULL )
			{
				memset( ptOPipe, 0, sizeof(OHCI_typePipe) );
			}
		else
			{
				DEBUG_ERROR_CALL( 0, "OHCI:Pipe nomem\n", NULL );
			}

	return( (usbd_pipe_t*)ptOPipe );
}

/*
  Pipe 構造体解放
*/
void usb_OHCI_vFreePipe( usbd_pipe_t* ptPipe )
{
#if defined( USB_DEBUG )
	usb_typeListMgr* p = (usb_typeListMgr*)ptPIPE_FREE_HEAD;
	for( ; p; p = p->next )
		if( (uint32_t)ptPipe == (uint32_t)p )
			{
				DEBUG_ERROR_CALL( 3, "OHCIFreePipe", NULL );
				return;
			}
#endif

	/* Pipe リストに追加 */
	USB_ENQUEUE_LIST( ptPIPE_FREE_HEAD, (OHCI_typePipe*)ptPipe );
}

/*
  ノード xfer 確保
*/
usbd_xfer_t* usb_OHCI_ptAllocXfer( void )
{
	OHCI_typeXfer* ptXfer;

	/* Xfer リストから1つ取り出してリターン */
	USB_DEQUEUE_LIST( ptXFER_FREE_HEAD, ptXfer )

		/* 0 クリア */
		if( ptXfer != NULL )
			{
				memset( ptXfer, 0, sizeof(OHCI_typeXfer) );
			}
		else
			{
				DEBUG_ERROR_CALL( 0, "OHCI:Xfer nomem\n", NULL );
			}

	return( (usbd_xfer_t*)ptXfer );
}

/*
  ノード Xfer 解放
*/
void usb_OHCI_vFreeXfer( usbd_xfer_t* ptXfer )
{
#if defined( USB_DEBUG )
	usb_typeListMgr* p = (usb_typeListMgr*)ptXFER_FREE_HEAD;
	for( ; p; p = p->next )
		if( (uint32_t)ptXfer == (uint32_t)p )
			{
				DEBUG_ERROR_CALL( 3, "OHCIFreeXfer", NULL );
				return;
			}
#endif

	/* Xfer リストに追加 */
	USB_ENQUEUE_LIST( ptXFER_FREE_HEAD, (OHCI_typeXfer*)ptXfer );
}

/*
  ED 管理用構造体確保
*/
OHCI_typeSoftEd* usb_OHCI_ptAllocSed( void )
{
	OHCI_typeEd* ptEd;
	OHCI_typeSoftEd* ptSedRet;

	/* SoftED リストから1つ取り出してリターン */
	OHCI_DEQUEUE_LIST( ptSED_FREE_HEAD, next, ptSedRet )

		/* 0 クリア */
		if( ptSedRet != NULL )
			{
				ptEd = ptSedRet->ptEd;
				memset( ptEd, 0, sizeof(OHCI_typeEd) );
				memset( ptSedRet, 0, sizeof(OHCI_typeSoftEd) );
				ptSedRet->ptEd = ptEd;
			}
		else
			{
				DEBUG_ERROR_CALL( 0, "OHCI:SoftED nomem\n", NULL );
			}

	return( ptSedRet );
}

/*
  ED 管理用構造体解放
*/
void usb_OHCI_vFreeSed( OHCI_typeSoftEd* ptSed )
{
#if defined( USB_DEBUG )
	OHCI_typeSoftEd* p = ptSED_FREE_HEAD;
	for( ; p; p = p->next )
		if( ptSed == p )
			{
				DEBUG_ERROR_CALL( 3, "OHCI_vFreeSed", NULL );
				return;
			}
#endif

	/* SoftED リストに追加 */
	OHCI_ENQUEUE_LIST( ptSED_FREE_HEAD, next, ptSed );
}

/*
  TD 管理用構造体確保
*/
OHCI_typeSoftTd* usb_OHCI_ptAllocStd( void )
{
	OHCI_typeTd* ptTd;
	OHCI_typeSoftTd* ptStdRet;

	/* SoftTD リストから1つ取り出してリターン */
	OHCI_DEQUEUE_LIST( ptSTD_FREE_HEAD, nexttd, ptStdRet )

		/* 0 クリア */
		if( ptStdRet != NULL )
			{
				ptTd = ptStdRet->ptTd;
				memset( ptTd, 0, sizeof(OHCI_typeTd) );
				memset( ptStdRet, 0, sizeof(OHCI_typeSoftTd) );
				ptStdRet->ptTd = ptTd;
			}
		else
			{
				DEBUG_ERROR_CALL( 0, "OHCI:SoftTD nomem\n", NULL );
			}

	return( ptStdRet );
}

/*
  TD 管理用構造体解放
*/
void usb_OHCI_vFreeStd( OHCI_typeSoftTd* ptStd )
{
#if defined( USB_DEBUG )
	OHCI_typeSoftTd* p = ptSTD_FREE_HEAD;
	for( ; p; p = p->nexttd )
		if( ptStd == p )
			{
				DEBUG_ERROR_CALL( 3, "OHCI_vFreeSed", NULL );
				return;
			}
#endif

	/* SoftTD リストに追加 */
	OHCI_ENQUEUE_LIST( ptSTD_FREE_HEAD, nexttd, ptStd );
}

/*
  HCCA 確保 (一個限定)
*/
OHCI_typeHcca* usb_OHCI_ptAllocHcca( void )
{
	OHCI_typeHcca* ptHcca = NULL;

	if( blHCCA == false )
		{
			ptHcca = (OHCI_typeHcca*)CPUADDR(ptHCCA_BUFFER);
			memset( ptHcca, 0, sizeof(OHCI_typeHcca) );
			blHCCA = true;
		}

	return( ptHcca );
}

/*
  HCCA 解放 (一個限定)
*/
void usb_OHCI_vFreeHcca( OHCI_typeHcca* ptHcca )
{
	if( ptHcca == (OHCI_typeHcca*)CPUADDR(ptHCCA_BUFFER) )
		blHCCA = false;
}


/*
  メモリ使用状態チェック
  戻り値：使用中メモリ数
*/
#if defined( USB_DEBUG )
int16_t usb_OHCI_iMemCheck( void )
{
	int16_t iPipe, iXfer, iEd, iTd, iRet = 0;

	/* Pipe バッファ */
	USB_NUM_CHECK_LIST( ptPIPE_FREE_HEAD, iPipe );
	/* Xfer バッファ */
	USB_NUM_CHECK_LIST( ptXFER_FREE_HEAD, iXfer );
	iRet += (OHCI_MAX_PIPES - iPipe) + (OHCI_MAX_XFERS - iXfer);
	/* SoftED バッファ */
	OHCI_NUM_CHECK_LIST( ptSED_FREE_HEAD, next, OHCI_typeSoftEd, iEd );
	/* SoftTD バッファ */
	OHCI_NUM_CHECK_LIST( ptSTD_FREE_HEAD, nexttd, OHCI_typeSoftTd, iTd );
	iRet += (OHCI_MAX_EDS - iEd) + (OHCI_MAX_TDS - iTd);

#if defined( PRINTF_ON )
	printf("usbd pipe structure	 total:%d, free:%d\n", OHCI_MAX_PIPES, iPipe );
	printf("usbd xfer structure	 total:%d, free:%d\n", OHCI_MAX_XFERS, iXfer );
	printf("ohci soft endpoint descriptor  total:%d, free:%d\n", OHCI_MAX_EDS, iEd );
	printf("ohci soft transport descriptor	total:%d, free:%d\n", OHCI_MAX_TDS, iTd );
#endif

	return( iRet );
}
#endif


/* --- End of File --- */
