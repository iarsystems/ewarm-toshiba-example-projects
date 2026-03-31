#ifndef _debug_hw_h_
#define _debug_hw_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : Debug IP
 *   Micon : -
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file Debug_hw.h
	\brief header file of Debug_hw.c

	\author TOSHIBA CORPORATION

	\date 2004/03/22 New Create
	\date 2008/10/15 Header renewal
	\date 2008/10/24 A910 Sample version 1.0
 */
/* ************************************************************************ */

/* ************************************************************************ */
/*
 * --------------------------------------------------------------------------
 *   Header Include Area
 * --------------------------------------------------------------------------
 */
#include "DebugAPI.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#define RCV_MAX			128			/* UART受信データ格納バッファサイズ */
#define	RCV_LINE_MAX 	128			/* コマンドラインバッファサイズ		*/
#define	RCV_CMD_NUM		5			/* コマンド保持数					*/


#define	PRG_LEN			80			/* プログラム名称文字数				*/
#define	VER_LEN			4			/* バージョン文字数					*/
#define	SYM_LEN			16			/* シンボル文字数					*/

#define	PRM_MAX			5			/* 入力可能パラメータ最大数			*/


/*
 * --------------------------------------------------------------------------
 *   Style Define Area
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Variable Define
 * --------------------------------------------------------------------------
 */
extern const CMD_REC gCmdTbl[];		/* コマンドテーブル					*/
extern const DBG_CFG gDbgConfig;	/* ユーザ環境情報					*/

extern UINT8_t	gRcvBuf[RCV_MAX];	/* UART受信データ格納バッファ		*/
extern UINT32_t nRcvPutIdx;			/* 受信バッファデータ格納先ＩＤＸ   */
extern UINT32_t nRcvGetIdx;			/* 受信バッファデータ取込先ＩＤＸ   */

extern UINT8_t	gCmdLineTbl[RCV_CMD_NUM][RCV_LINE_MAX+1];
									/* コマンド保持テーブル				*/
extern UINT32_t nCmdPutIdx;			/* 受信バッファデータ格納先ＩＤＸ   */
extern UINT32_t nCmdGetIdx;			/* 受信バッファデータ取込先ＩＤＸ   */

extern INT32_t	bDebugFlg;			/* DebugIP 有効／無効フラグ			*/
extern INT32_t	bLogMode;			/* プログラムログモードフラグ		*/
extern UINT8_t*	gpArgv[PRM_MAX];	/* コマンドライン分解テーブル		*/
extern INT32_t	nArgc;				/* 入力トークン数					*/


/*
 * --------------------------------------------------------------------------
 *   Prototype Declaration Area
 * --------------------------------------------------------------------------
 */
extern void dbgIntRx(void);
extern UINT32_t debugAPI_send_char(const UINT8_t *const data);


/* ************************************************************************ */
#endif	/* _debug_hw_h_ */
