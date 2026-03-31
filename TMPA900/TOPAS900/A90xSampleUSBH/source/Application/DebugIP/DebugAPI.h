#ifndef _debugapi_h_
#define _debugapi_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : Debug IP
 *   Micon : -
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file DebugAPI.h
	\brief header file of DebugAPI.c

	\author TOSHIBA CORPORATION

	\date 2004/04/09 New Create
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
#include "cmn_type.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#define E_DEBUGAPI_FALSE	FALSE	/* failed of DEBUG API process	*/
#define E_DEBUGAPI_TRUE		TRUE	/* succeed of DEBUG API process	*/

#define CDEBUGAPI_STRBUF_SIZE	80

#define PRM_MAX		5				/* 入力可能パラメータ最大数			*/
#define	PRG_LEN		80				/* プログラム名称文字数				*/
#define	VER_LEN		4				/* バージョン文字数					*/
#define	SYM_LEN		16				/* シンボル文字数					*/


/*
 * --------------------------------------------------------------------------
 *   Style Define Area
 * --------------------------------------------------------------------------
 */
typedef struct
{
	UINT8_t* strCmd;				/* コマンド文字列ポインタ			*/
	void (*CmdFunc)(void);			/* コマンド処理関数					*/
} CMD_REC;


/****************************************************/
/* シンボル情報										*/
/* シンボル文字列＝"\0"時、終了レコードと判断する。 */
/****************************************************/
typedef struct {
	UINT8_t strSymbol[SYM_LEN+1];	/* シンボル文字列					*/
	UINT32_t lAddr;				/* シンボルアドレス					*/
} SYM_INF;


/********************************************************/
/* 書込み禁止ブロック情報								*/
/* lStartAddr > lEndAddr 時、終了レコードと判断する。   */
/********************************************************/
typedef struct {
	UINT32_t lStartAddr;			/* ブロック開始アドレス				*/
	UINT32_t lEndAddr;				/* ブロック終了アドレス				*/
} WPBLK_INF;


/********************************************************/
/* ユーザ環境情報										*/
/********************************************************/
typedef struct {
	UINT8_t strPrgName[PRG_LEN+1];/* プログラム名称文字列				*/
	UINT8_t strPrgVer[VER_LEN+1]; /* バージョン文字列					*/
	WPBLK_INF* pgWpBlk;					/* 書込み禁止ブロック情報ポインタ   */
	SYM_INF* pgSymInf;					/* シンボル情報テーブル先頭ポインタ */
} DBG_CFG;


/*
 * --------------------------------------------------------------------------
 *   Variable Define
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Prototype Declaration Area
 * --------------------------------------------------------------------------
 */
void dbgInit(void);
void dbgCmdHandle(void);
void dbgLogOut(UINT8_t* strLog);

void Cmd_r(void);
void Cmd_w(void);
void Cmd_s(void);
void Cmd_l(void);
void Cmd_h(void);
void Cmd_i(void);
void Cmd_d(void);

INT32_t MakeAddr(UINT8_t* strData,UINT32_t* plBin);
INT32_t MakeBin(UINT8_t* strData,UINT32_t* plBin);
void MakeAddrString(INT8_t* pstrDisp, UINT32_t nAddr);
void MakeByteString(INT8_t* pstrDisp, UINT32_t nData);
void MakeWordString(INT8_t* pstrDisp, UINT32_t nData);
void MakeDataString(INT8_t* pstrDisp, UINT32_t nAddr, INT32_t nFigure);
void MakeSymString(INT8_t* pstrDisp, UINT8_t* strSym, INT32_t nFigure);
void OutStr(UINT8_t* strData);


/* ************************************************************************** */
#endif	/* _debugapi_h_ */
