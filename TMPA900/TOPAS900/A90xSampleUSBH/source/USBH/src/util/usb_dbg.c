/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_dbg.c 41 2014-01-27 14:05:18Z danielru $ */

#include "usb_dbg.h"

//#pragma section area IRAM 

#if defined( USB_DEBUG )

/*
  DEBUG_ERROR_CALLマクロでアクセスする事
*/
void usb_vDebugCall( uint8_t lv, const int8_t* str, int16_t* perr )
{
	volatile uint8_t ucMark;

	/* ブレークポイントを張るための分岐 */
	if( lv >= 1 )
		if( lv >= 2 )
			if( lv >= 3 )
				ucMark = 0;

#if defined( USB_DEBUG_OUTPUT2STDOUT )
  if( perr )
    DEBUG_ERROR_LOG(("%d: %s \n", *perr, str ));
  else
    DEBUG_ERROR_LOG(("NULL: %s \n", str));
#endif
}


#include <stdio.h>	/* fprintf(), sprintf() */
#include <stdarg.h> /* vfprintf(), va_start(), va_list, va_end() */

#if defined(USB_DEBUG_OUTPUT2STDOUT)
/*!
 * ログ出力用関数
 */
extern void
usb_Logv(int8_t const* fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	fprintf(stdout, "[USBLog]: ");
	vfprintf(stdout, fmt, arg);
	va_end(arg);
}

#elif defined(USB_DEBUG_OUTPUT2BUF) /* !defined(USB_DEBUG_OUTPUT2STDOUT) */

#include <string.h> /* strcpy(), memset() */

/*!
 * 動作ログ＆エラーログ出力用バッファ
 */
int8_t usb_pcLOG[USB_LOG_BUFSIZ];

/*!
 * ログ＆エラー出力用バッファの現在位置を示すポインタ
 */
static int8_t* usb_pcLOG_CURR_POS = usb_pcLOG;


/*!
 * ログ出力用関数
 */
extern void
usb_Logv(int8_t const* fmt, ...)
{
	va_list arg;
	static int8_t buf[USB_LOG_MSGSIZ];
	int len;

	/* USB_DIS_INTR() */
	va_start(arg, fmt);
	len = sprintf(buf, "[LOG]:");
	len += vsprintf(buf + 0x6, fmt, arg);
	
	/* 書き込み位置のまき戻し */
	if(usb_pcLOG_CURR_POS + len + 1 >= usb_pcLOG + USB_LOG_BUFSIZ) {
		usb_pcLOG_CURR_POS = usb_pcLOG;
	}
	if(usb_pcLOG_CURR_POS == usb_pcLOG) {
		memset(usb_pcLOG, 0, USB_LOG_BUFSIZ);
	}
	
	strcpy(usb_pcLOG_CURR_POS, buf);
	usb_pcLOG_CURR_POS += len + 1;
	va_end(arg);
	/* USB_ENA_INTR() */
}

/*!
 * エラー出力用関数
 */
void
usb_ErrorLogv(int8_t const* fmt, ...)
{
	va_list arg;
	static int8_t buf[USB_LOG_MSGSIZ];
	int len;

	/* USB_DIS_INTR() */
	va_start(arg, fmt);
	len = sprintf(buf, "[ERR]:");
	len += vsprintf(buf + 0x6, fmt, arg);

	/* 書き込み位置のまき戻し */
	if(usb_pcLOG_CURR_POS + len + 1 >= usb_pcLOG + USB_LOG_BUFSIZ) {
		usb_pcLOG_CURR_POS = usb_pcLOG;
	}
	if(usb_pcLOG_CURR_POS == usb_pcLOG) {
		memset(usb_pcLOG, 0, USB_LOG_BUFSIZ);
	}
	
	strcpy(usb_pcLOG_CURR_POS, buf);
	usb_pcLOG_CURR_POS += len + 1;
	va_end(arg);
	/* USB_ENA_INTR() */
}

#endif /* !defined(USB_DEBUG_OUTPUT2STDOUT) && !defined(USB_DEBUG_OUTPUT2BUF) */

#else

/* empty */
static void vDummy( void ) {}  /* IDE コンパイルエラー避け */

#endif /* defined(USB_DEBUG) */

//#pragma section area 

