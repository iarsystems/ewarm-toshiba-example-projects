/*
 * @file
 * USB Host Driver source file
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 */

/* $Id: usb_dbg.h 41 2014-01-27 14:05:18Z danielru $ */


#ifndef _USB_UTIL_DBG_H_SEEN_
#define _USB_UTIL_DBG_H_SEEN_

#include "usb_config.h"

/*!
 * \page debug_util	デバッグ用ユーティリティについて
 * 
 * \section enabling 機能のオンオフ
 *	このユーティリティで提供されるインターフェイスは、コンパイル時の
 *	プリデファイン・マクロ \b USB_DEBUG を指定することで、機能が有効になります。
 *	デバッグ用関数を有効にした場合、以下の方法でメッセージの出力先を指定することが
 *	できます。以下のどちらも指定しなかった場合には、メッセージ文字列は、表示されません。
 *
 *	\arg USB_DEBUG_OUTPUT2STDOUT
 *		メッセージ文字列を \i printf を用いて、標準出力へと出力します。
 *
 *	\arg USB_DEBUG_OUTPUT2BUF
 *		メッセージ文字列をメッセージ用バッファへと出力します。
 *
 * \subsection msg_buf メッセージ用バッファ
 *	メッセージ文字列をバッファへと出力するように指定した場合、
 *	出力用のバッファサイズなどの設定を以下で行なうことができます。
 *	バッファがいっぱいになった場合には、バッファをクリア後に再びバッファ先頭から
 *	出力を行ないます。
 *
 *	\arg USB_LOG_BUFSIZ
 *		ログ出力用のバッファサイズをバイト数で指定します。
 *
 *	\arg USB_LOG_MSGSIZ
 *		ログ出力用の１メッセージにおける最大文字列長を指定します。
 *		ログ出力用関数に指定する文字列長さが、この指定値を超えないようにして下さい。
 */

#include "usb_types.h"
#if defined(USB_DEBUG) && defined(USB_DEBUG_OUTPUT2STDOUT)
#include <stdio.h> /* printf() */
#endif


/* ---------- 動作ログ＆エラーログの出力 ---------- */
#if defined(USB_DEBUG)

#if defined(USB_DEBUG_OUTPUT2BUF)
/*!
 * 動作ログ＆エラーログ出力用バッファサイズ
 */
#define USB_LOG_BUFSIZ		0x1000

/*!
 * 動作ログ＆エラーログ出力用最大メッセージ長さ
 */
#define USB_LOG_MSGSIZ		0x100

#endif /* defined(USB_DEBUG_OUTPUT2BUF) */


/*!
 * \brief ログを表示する
 * \param fmt		フォーマット文字列
 *
 * ログ出力を行なう。fmt 以後の引数は printf と同様の可変引数をとる。
 */
#if defined(USB_DEBUG_OUTPUT2BUF) || defined(USB_DEBUG_OUTPUT2STDOUT)
extern void			usb_Logv(int8_t const* fmt, ...);
#else
#define				usb_Logv			/* empty */
#endif

#if defined(USB_DEBUG_OUTPUT2BUF)
extern void			usb_ErrorLogv(int8_t const* fmt, ...);
#endif

/*!
 * \brief エラーログを表示する
 * \param str           表示するエラー文字列のポインタ
 * \param perr          表示する任意データのポインタ
 */
#if defined(USB_DEBUG_OUTPUT2STDOUT)
#define DEBUG_ERROR_LOG(args)		(printf("ERROR: "),  printf  args)
#elif defined(USB_DEBUG_OUTPUT2BUF)
#define DEBUG_ERROR_LOG(args)		(usb_ErrorLogv args)
#else
#define DEBUG_ERROR_LOG(args)		/* empty */
#endif

#else	/* !defined(USB_DEBUG) */

#define	usb_Logv					/* empty */
#define DEBUG_ERROR_LOG(args)		/* empty */

#endif	/* defined(USB_DEBUG) */


/* ---------- エラーキャッチ関数 ---------- */
#if defined(USB_DEBUG)

#if(0)
extern void usb_vDebugCall( uint8_t, const int8_t*, int* );
#else
extern void usb_vDebugCall( uint8_t, const int8_t*, int16_t* );
#endif

/*!
 * \param str	エラー出力用文字列
 * \param perr	エラーコードを格納している変数のアドレス(?)
 *
 * エラー時に呼び出す関数
 */
#define DEBUG_ERROR_CALL(lv,str,perr)		usb_vDebugCall((lv), (str), (perr))

#else /* !defined(USB_DEBUG) */

#define DEBUG_ERROR_CALL(lv,str, perr)		/* empty */

#endif /* defined(USB_DEBUG) */


#endif /* _USB_UTIL_DBG_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
