/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 */

/* $Id: usb_trace.c 41 2014-01-27 14:05:18Z danielru $ */

#include "usb_types.h"
#include "usb_trace.h"
#include <string.h>		/* memset() */

#pragma section = "IRAM"

#if defined(USB_TRACE_ENABLE)
#if defined(USB_DEBUG_OUTPUT2STDOUT)
/* ********************************************************* */
/*           関数名を標準出力に出力するトレース              */
/* ********************************************************* */

/*!
 * トレースの表示レベル。USB_TRACE_INIT() により初期化時に指定された値を保持する。
 */
int16_t		usb_sTRACE_LEVEL @ "IRAM";

/*!
 * トレースのインデントレベル。ENTER/LEAVE により、増減するインデント量を保持する。
 */
int16_t		usb_sTRACE_INDENT @ "IRAM";


#elif defined(USB_DEBUG_OUTPUT2BUF)/* !defined(USB_DEBUG_OUTPUT2STDOUT) */
/* ********************************************************* */
/*           関数名をバッファに格納するトレース              */
/* ********************************************************* */

/* ========================================================= */
/*			Types, Constants and Local Variables			 */
/* ========================================================= */
typedef struct {
	uint8_t		indent;
	int8_t		dir; /* IN or OUT */
	int8_t		funcname[26];
	uint32_t	param;
} USB_typeTraceEntry;

/*!
 * 関数トレースバッファ
 */
USB_typeTraceEntry	usb_ptTRACE[USB_TRACE_MAX] @ "IRAM";
int16_t		usb_sTRACE_INDEX @ "IRAM";
uint8_t		usb_ucTRACE_INDENT @ "IRAM";
int16_t		usb_sTRACE_LEVEL @ "IRAM";

/*!
 * トレースの表示レベル。USB_TRACE_INIT() により初期化時に指定された値を保持する。
 */
int16_t		usb_sTRACE_LEVEL @ "IRAM";

/*!
 * トレースのインデントレベル。ENTER/LEAVE により、増減するインデント量を保持する。
 */
int16_t		usb_sTRACE_INDENT @ "IRAM";

/* ========================================================= */
/*				   Function Implementations					 */
/* ========================================================= */
/*!
 * \brief トレース情報の初期化とレベルを設定をする。
 * \param level		トレースレベル(指定されたレベル以下をトレースする)
 */
void
usb_vTraceInit(int16_t sLevel)
{
	usb_sTRACE_LEVEL = sLevel;
	usb_sTRACE_INDEX = 0;
	usb_ucTRACE_INDENT = 0;
	memset(usb_ptTRACE, 0, sizeof(usb_ptTRACE));
}

static __inline void
setEntry(int8_t direction, const int8_t* pcFuncName, uint32_t ulParam)
{
	usb_ptTRACE[usb_sTRACE_INDEX].indent = usb_ucTRACE_INDENT;
	if(direction == 0) {
		/* IN */
		usb_ptTRACE[usb_sTRACE_INDEX].dir = '>';
		usb_ucTRACE_INDENT += 1;
	}
	else {
		/* OUT */
		usb_ptTRACE[usb_sTRACE_INDEX].dir = '<';
		usb_ucTRACE_INDENT -= 1;
	}
	strncpy(usb_ptTRACE[usb_sTRACE_INDEX].funcname, pcFuncName, 26);
	usb_ptTRACE[usb_sTRACE_INDEX].param = ulParam;

	/* next */
	usb_sTRACE_INDEX++;
	if(usb_sTRACE_INDEX >= USB_TRACE_MAX) {
		usb_sTRACE_INDEX = 0;
	}
	memset(&usb_ptTRACE[usb_sTRACE_INDEX], -1, sizeof(USB_typeTraceEntry));
}

void
usb_vTraceSetIn(int16_t sLevel, const int8_t* pcFuncName, uint32_t ulParam)
{
	if(sLevel <= usb_sTRACE_LEVEL) {
		setEntry(0, pcFuncName, ulParam);
	}
}

void
usb_vTraceSetOut(int16_t sLevel, const int8_t* pcFuncName, uint32_t ulParam)
{
	if(sLevel <= usb_sTRACE_LEVEL) {
		setEntry(1, pcFuncName, ulParam);
	}
}


#else /* !defined(USB_DEBUG_OUTPUT2STDOUT) && !defined(USB_DEBUG_OUTPUT2BUF) */
/* ********************************************************* */
/*               関数アドレスを格納するトレース              */
/* ********************************************************* */

/* ========================================================= */
/*			Types, Constants and Local Variables			 */
/* ========================================================= */
/*!
 * 関数トレース情報
 */
typedef struct {
	int16_t		sLevel;						/*!< トレースレベル */
	uint16_t	usEntryCnt;					/*!< 現在のトレース登録数 */
} trace_inf_t;

/*!
 * 関数トレース登録情報
 */
typedef struct {
	int8_t		cInOrOut;						/*!< 関数の入口or出口 */
#define TRACE_DIR_IN			0
#define TRACE_DIR_OUT			1
	void*		pvFuncAddr;						/*!< トレースする関数のアドレス */
	uint32_t	ulParam;						/*!< 任意なパラメータ */
} trace_entry_t;


static trace_inf_t tTRACE_INF @ "IRAM";

static trace_entry_t ptTRACE_ENTRY[USB_TRACE_MAX] @ "IRAM";


/* ========================================================= */
/*				   Function Implementations					 */
/* ========================================================= */
/*!
 * \brief トレース情報の初期化とレベルを設定をする。
 * \param level		トレースレベル(指定されたレベル以下をトレースする)
 */
void
usb_vTraceInit(int16_t sLevel)
{
	tTRACE_INF.sLevel = sLevel;									/* 取得レベル設定 */
	tTRACE_INF.usEntryCnt = 0;									/* 登録数を初期化 */
	memset(ptTRACE_ENTRY,0,sizeof(ptTRACE_ENTRY));				/* 登録情報を初期化 */
}

/*!
 * \brief トレースに登録する
 * \param sLevel		登録する関数のトレースレベル
 * \param pvFuncAddr	登録する関数アドレス
 * \param cDirection	関数の入口or出口
 * \param ulParam		任意パラメータ
 */
static __inline void
vSetEntry(int16_t sLevel, void* pvFuncAddr, int8_t cDirection, uint32_t ulParam)
{
	if(sLevel <= tTRACE_INF.sLevel) {
		ptTRACE_ENTRY[tTRACE_INF.usEntryCnt].pvFuncAddr = pvFuncAddr;
		ptTRACE_ENTRY[tTRACE_INF.usEntryCnt].cInOrOut = cDirection;
		ptTRACE_ENTRY[tTRACE_INF.usEntryCnt].ulParam = ulParam;
	}
}

void
usb_vTraceSetIn(int16_t sLevel, void* pvFuncAddr, uint32_t ulParam)
{
	vSetEntry(sLevel, pvFuncAddr, TRACE_DIR_IN, ulParam);
}

void
usb_vTraceSetOut(int16_t sLevel, void* pvFuncAddr, uint32_t ulParam)
{
	vSetEntry(sLevel, pvFuncAddr, TRACE_DIR_OUT, ulParam);
}

#endif /* defined(USB_DEBUG_OUTPUT2STDOUT) */

#else /* !defined(USB_TRACE_ENABLE) */

static void vDummy( void ) {}  /* IDE アセンブラエラー避け */

#endif /* defined(USB_TRACE_ENABLE) */


