/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : Debug IP
 *   Micon : -
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file Debug_hw.c
	\brief Source Code of DebugAPI module depend on hardware

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Debug_hw.h"
#include "uart.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#define		SEND_TIMEOUT	5000		/* 送信チェックタイムアウト回数		*/


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */


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
UINT8_t		gRcvBuf[RCV_MAX];		/* UART受信データ格納バッファ		*/
UINT32_t	nRcvPutIdx;				/* 受信バッファデータ格納先ＩＤＸ   */
UINT32_t	nRcvGetIdx;				/* 受信バッファデータ取込先ＩＤＸ   */

UINT8_t		gCmdLineTbl[RCV_CMD_NUM][RCV_LINE_MAX+1];
									/* コマンド保持テーブル				*/
UINT32_t	nCmdPutIdx;				/* 受信バッファデータ格納先ＩＤＸ   */
UINT32_t	nCmdGetIdx;				/* 受信バッファデータ取込先ＩＤＸ   */

INT32_t		bDebugFlg;				/* DebugIP 有効／無効フラグ			*/
INT32_t		bLogMode;				/* プログラムログモードフラグ		*/
UINT8_t*	gpArgv[PRM_MAX];		/* コマンドライン分解テーブル		*/
INT32_t		nArgc;					/* 入力トークン数					*/

const CMD_REC gCmdTbl[]=
{
	{(UINT8_t*)"!r",  Cmd_r},
	{(UINT8_t*)"!w",  Cmd_w},
	{(UINT8_t*)"!s",  Cmd_s},
	{(UINT8_t*)"!l",  Cmd_l},
	{(UINT8_t*)"!h",  Cmd_h},
	{(UINT8_t*)"!i",  Cmd_i},
	{(UINT8_t*)"!d",  Cmd_d},

	/* TODO: please add command table if you want to add original command	*/
	{(UINT8_t*)NULL,	(void (*)(void))NULL}		/* End recode		*/
};

/*
 *	table of disable write block
 */
const WPBLK_INF gWpBlk[] = 
{
	/* TODO: please add disable write block	*/

	{0xffffffff,	0x00000000}		/* TODO: End recode	*/
};


/*
 *	symbole table
 */
const SYM_INF gSymTbl[]=
{
	/* TODO: please add symbol recode	*/

	{NULL,				0}		/* TODO: End recode	*/
};


/*
 *	information of user program
 */
const DBG_CFG gDbgConfig =
{
	"DebugIp_Demo",		/* name of program		*/
	"1.1",				/* version information	*/
	(WPBLK_INF*)gWpBlk,	/* disable write block information
							(please write "NULL" if you don't need)
						 */
	(SYM_INF*)gSymTbl	/* symbol table (please write "NULL" if you don't need)
						 */
};


/*
 * --------------------------------------------------------------------------
 *   Prototype Declaration Area
 * --------------------------------------------------------------------------
 */


/* ************************************************************************** */
/*! \addtogroup Application_Functions
 *  @{
 */
/*! \addtogroup DebugAPI_Functions
 *  @{
 */
/* ======================================================================== */
/*!
	interrupt of receive data

	\param -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void dbgIntRx(void)
{
	UINT8_t nRcvData;				/* receive data				*/
	INT32_t nIdx;
	INT32_t status;

	status = get_char(&nRcvData);

	if(status == FALSE) {
		/* unavailable of DebugIP			*/
		return;
	}

	if(nRcvData == '\n') {
		return;
	}
	if(nRcvData == '\r') {
		nRcvData = '\0';
	}

	if(bLogMode == TRUE) {
		/* enable log mode								*/
		if(nRcvData != 0x03) {
			/* receive data without "Ctrl-C"			*/
			return;
		}
		nRcvData = '\0';
	}

	if(nRcvData == 0x08) {
		/* input "BS"							*/
		if(nRcvPutIdx != nRcvGetIdx) {
			if(!nRcvPutIdx) {
				nRcvPutIdx = RCV_MAX - 1;
			}
			else {
				nRcvPutIdx--;
			}
		}
		return;
	}

	gRcvBuf[nRcvPutIdx] = nRcvData;
	nRcvPutIdx++;
	if(nRcvPutIdx >= RCV_MAX) {
		/* 受信データ格納					*/
		nRcvPutIdx = 0;
	}

	/* コマンド入力完了判定 */
	if(nRcvData == '\0') {
		/* 改行コード受信					*/
		for(nIdx=0;;nIdx++) {
			/* コマンドライン取得				*/
			gCmdLineTbl[nCmdPutIdx][nIdx] = gRcvBuf[nRcvGetIdx];
			nRcvGetIdx++;
			if(nRcvGetIdx >= RCV_MAX) {
				nRcvGetIdx = 0;
			}
			if(nRcvGetIdx == nRcvPutIdx) {
				break;
			}
		}
		nCmdPutIdx++;
		if(nCmdPutIdx >= RCV_CMD_NUM) {
			nCmdPutIdx = 0;
		}
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	convert of send char function for debugAPI library

	\param data					pointer of send data
	\retval E_DEBUGAPI_TRUE		correct
	\retval E_DEBUGAPI_FALSE	failed
 */
/* ------------------------------------------------------------------------ */
UINT32_t debugAPI_send_char(const UINT8_t *const data)
{
	UINT32_t rtn;
	
	rtn = send_char(data);
	if(rtn == E_UART_TRUE) {
		rtn = E_DEBUGAPI_TRUE;
	}
	else {
		rtn = E_DEBUGAPI_FALSE;
	}
	return rtn;
}
/* ======================================================================== */
/*! @}	*/ /* DebugAPI_Functions */

/*! @}	*/ /* Application_Functions */
/* ************************************************************************** */
