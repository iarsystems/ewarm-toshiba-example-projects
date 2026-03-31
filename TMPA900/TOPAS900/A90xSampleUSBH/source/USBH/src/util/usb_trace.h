/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 */

/* $Id: usb_trace.h 41 2014-01-27 14:05:18Z danielru $ */

#ifndef _USB_UTIL_TRACE_H_SEEN_
#define _USB_UTIL_TRACE_H_SEEN_

#include "usb_config.h"
#include "usb_types.h"


/*
 * \page trace	デバッグ用関数トレーシング
 *
 * USBドライバの関数呼び出しのトレースを収集するためのモジュールです。
 *
 * \section enabling	トレースの取得
 *	トレース機能を有効にするには、コンパイル・オプションに
 *	\b USB_TRACE_ENABLE プリデファイン・マクロを付加して再ビルドを行なって下さい。
 *
 *	\arg USB_DEBUG_OUTPUT2STDOUT
 *		トレース情報を標準出力に出力します。
 *
 *	\arg USB_DEBUG_OUTPUT2BUF
 *		トレース情報をバッファに格納します。
 */


/* ********************************************************* */
/*              トレースのコンフィグレーション               */
/* ********************************************************* */
/*!
 * \brief トレース取得最大数
 *
 * トレースのバッファ出力を行なう場合の、最大トレース数。
 */
#define USB_TRACE_MAX	(100)

/*!
 * \brief 関数の最大文字数
 *
 * トレースをprintf出力する場合の、関数名の最大表示文字数。
 */
#define USB_TRACE_FUNCNAME_LEN	(20)



#if defined(USB_TRACE_ENABLE)

#if defined(USB_DEBUG_OUTPUT2STDOUT)
/* --------------------------------------------------------- */
/*                    表示するトレース                       */
/* --------------------------------------------------------- */

#include <stdio.h>

extern int16_t		usb_sTRACE_LEVEL;
extern int16_t		usb_sTRACE_INDENT;


/*!
 * \brief トレース情報の初期化と取得トレースレベルを設定をする。
 * \param level		取得トレースレベル(指定されたレベル以下をトレースする)
 */
#define USB_TRACE_INIT(level) { usb_gsTraceLevel = (level); usb_gsTraceIndent = 1; }

/*!
 * \brief 関数の入口をトレースに登録する(1つのパラメータつき)
 * \param level			登録する関数のトレースレベル
 * \param funcname		登録する関数アドレス
 * \param param			任意パラメータ
 */
#define USB_TRACE_ENTER1(level, funcname, param)	\
	if((level) <= usb_sTRACE_LEVEL) {				\
		printf("%*[ENTER] %-*s 0x%x\n",				\
			   usb_sTRACE_INDENT++, USB_TRACE_FUNCNAME_LEN, (#funcname), (uint32_t)(param));	\
	}

/*!
 * \brief 関数の入口をトレースに登録する
 * \param level			登録する関数のトレースレベル
 * \param funcname		登録する関数アドレス
 */
#define USB_TRACE_ENTER(level, funcname)	\
	if((level) <= usb_sTRACE_LEVEL) {		\
		printf("%*[ENTER] %-*s\n",			\
			   usb_sTRACE_INDENT++, USB_TRACE_FUNCNAME_LEN, (#funcname));	\
	}

/*!
 * \brief 関数の出口をトレースに登録する(1つのパラメータつき)
 * \param level			登録する関数のトレースレベル
 * \param funcname		登録する関数アドレス
 * \param param			任意パラメータ
 */
#define USB_TRACE_LEAVE1(level, funcname, param)	\
	if((level) <= usb_sTRACE_LEVEL) {				\
		printf("%*[LEAVE] %-*s 0x%x\n",				\
			   --usb_sTRACE_INDENT, USB_TRACE_FUNCNAME_LEN, (#funcname), (uint32_t)(param)); \
	}

/*!
 * \brief 関数の出口をトレースに登録する
 * \param level			登録する関数のトレースレベル
 * \param funcname		登録する関数アドレス
 */
#define USB_TRACE_LEAVE(level, funcname)	\
	if((level) <= usb_sTRACE_LEVEL) {		\
		printf("%*[LEAVE] %-*s\n",			\
			   --usb_sTRACE_INDENT, USB_TRACE_FUNCNAME_LEN, (#funcname)); \
	}


#else /* !defined(USB_DEBUG_OUTPUT2STDOUT) */

/* --------------------------------------------------------- */
/*               バッファに出力するトレース                  */
/* --------------------------------------------------------- */

extern void		usb_vTraceInit(int16_t sLevel);
#if defined(USB_DEBUG_OUTPUT2BUF)
extern void		usb_vTraceSetIn(int16_t sLevel, const int8_t* pcFuncName, uint32_t ulParam);
extern void		usb_vTraceSetOut(int16_t sLevel, const int8_t* pcFuncName, uint32_t ulParam);
#else
extern void		usb_vTraceSetIn(int16_t sLevel, void* pvFuncAddr, uint32_t ulParam);
extern void		usb_vTraceSetOut(int16_t sLevel, void* pvFuncAddr, uint32_t ulParam);
#endif

/*!
 * \brief トレース情報の初期化と取得トレースレベルを設定をする。
 * \param level		取得トレースレベル(指定されたレベル以下をトレースする)
 */
#define USB_TRACE_INIT(level) usb_vTraceInit((level))

/*!
 * \brief 関数の入口をトレースに登録する(1つのパラメータつき)
 * \param level			登録する関数のトレースレベル
 * \param funcname		登録する関数アドレス
 * \param param			任意パラメータ
 */
#if defined(USB_DEBUG_OUTPUT2BUF)
#define USB_TRACE_ENTER1(level, funcname, param)	\
	usb_vTraceSetIn((level), (#funcname), (uint32_t)(param))
#else
#define USB_TRACE_ENTER1(level, funcname, param)	\
	usb_vTraceSetIn((level), (funcname), (uint32_t)(param))
#endif

/*!
 * \brief 関数の入口をトレースに登録する
 * \param level			登録する関数のトレースレベル
 * \param funcname		登録する関数アドレス
 */
#if defined(USB_DEBUG_OUTPUT2BUF)
#define USB_TRACE_ENTER(level, funcname)	\
	usb_vTraceSetIn((level), (#funcname), 0xffffffff)
#else
#define USB_TRACE_ENTER(level, funcname)	\
	usb_vTraceSetIn((level), (funcname), 0xffffffff)
#endif

/*!
 * \brief 関数の出口をトレースに登録する(1つのパラメータつき)
 * \param level			登録する関数のトレースレベル
 * \param funcname		登録する関数アドレス
 * \param param			任意パラメータ
 */
#if defined(USB_DEBUG_OUTPUT2BUF)
#define USB_TRACE_LEAVE1(level, funcname, param)	\
	usb_vTraceSetOut((level), (#funcname), (uint32_t)(param))
#else
#define USB_TRACE_LEAVE1(level, funcname, param)	\
	usb_vTraceSetOut((level), (funcname), (uint32_t)(param))
#endif

/*!
 * \brief 関数の出口をトレースに登録する
 * \param level			登録する関数のトレースレベル
 * \param funcname		登録する関数アドレス
 */
#if defined(USB_DEBUG_OUTPUT2BUF)
#define USB_TRACE_LEAVE(level, funcname) \
	usb_vTraceSetOut((level), (#funcname), 0xffffffff)
#else
#define USB_TRACE_LEAVE(level, funcname) \
	usb_vTraceSetOut((level), (funcname), 0xffffffff)
#endif

#endif /* defined(USB_DEBUG_OUTPUT2STDOUT) */

#else /* !defined(USB_TRACE_ENABLE) */

#define USB_TRACE_INIT(level)						/* empty */
#define USB_TRACE_ENTER1(level, funcname, param)	/* empty */
#define USB_TRACE_ENTER(level, funcname)			/* empty */
#define USB_TRACE_LEAVE1(level, funcname, param)	/* empty */
#define USB_TRACE_LEAVE(level, funcname)			/* empty */

#endif /* defined(USB_TRACE_ENABLE) */

#endif /* !defined(_USB_UTIL_TRACE_H_SEEN_) */
