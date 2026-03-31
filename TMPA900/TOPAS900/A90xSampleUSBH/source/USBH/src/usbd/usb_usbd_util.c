/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 */

/* $Id: usb_usbd_util.c 41 2014-01-27 14:05:18Z danielru $ */

#include "usb_config.h"
#include <string.h>		/* memset() */
#include "usb_usbd_util.h"

#pragma section = "HC_RAM_USBDMEM"
static usbd_retry_count_t tRETRY @ "HC_RAM_USBDMEM";	/*!< USBドライバでのリトライ発生数カウンタ */
static usbd_error_count_t tERROR @ "HC_RAM_USBDMEM";	/*!< USBドライバでのエラー発生数カウンタ */


#if defined(USBD_UTIL)

usbd_retry_count_t* usb_ptUSBD_RETRY_COUNT @ "HC_RAM_USBDMEM" = NULL;	/*!< リトライカウンタ(公開) */
usbd_error_count_t* usb_ptUSBD_ERROR_COUNT @ "HC_RAM_USBDMEM" = NULL;	/*!< エラーカウンタ(公開) */


/* ========================================================= */
/*                    発生エラーの確認                       */
/* ========================================================= */
void
usb_USBDCountInit(void)
{
	usb_ptUSBD_RETRY_COUNT = &tRETRY;
	usb_ptUSBD_ERROR_COUNT = &tERROR;

	memset(&tRETRY, 0, sizeof(tRETRY));
	memset(&tERROR, 0, sizeof(tERROR));
}


/* ========================================================= */
/*                     xfer をチェック                       */
/* ========================================================= */
#include <usb.h>
#include <string.h>
#include "util/usb_dbg.h"

typedef struct usbd_xfer_log {
	usbd_xfer_t		start;
	usbd_xfer_t		end;
	usbd_xfer_t*	start_addr;
	usbd_xfer_t*	end_addr;
} usbd_xfer_log_t;


usbd_xfer_log_t	usb_tXFERLOG @ "HC_RAM_USBDMEM";
usbd_xfer_log_t usb_tINTR_XFERLOG @ "HC_RAM_USBDMEM";

#define XFER_ETYPE(xfer)		\
	UE_GET_XFERTYPE((xfer)->ptPipe->ptEndpoint->ptEdesc->bmAttributes)


void
usb_USBDWatchXfer_RegisterTransferingXfer(usbd_xfer_t* xfer)
{
	if(XFER_ETYPE(xfer) != UE_INTERRUPT) {
		usb_tXFERLOG.start = *xfer;
		usb_tXFERLOG.start_addr = xfer;
	}
	else {
		usb_tINTR_XFERLOG.start = *xfer;
		usb_tINTR_XFERLOG.start_addr = xfer;
	}
}

void
usb_USBDWatchXfer_RegisterTransferedXfer(usbd_xfer_t* xfer)
{
	if(XFER_ETYPE(xfer) != UE_INTERRUPT) {
		usb_tXFERLOG.end = *xfer;
		usb_tXFERLOG.end_addr = xfer;
	}
	else {
		usb_tINTR_XFERLOG.end = *xfer;
		usb_tINTR_XFERLOG.end_addr = xfer;
	}
}

int16_t
usb_USBDWatchXfer_CheckXfer(usbd_xfer_t* xfer)
{
	int16_t err = USB_OK;
	usbd_xfer_log_t* log;
	const usbd_xfer_t* ptBefore;
	const usbd_xfer_t* ptAfter;

	if(XFER_ETYPE(xfer) != UE_INTERRUPT) {
		log = &usb_tXFERLOG;
	}
	else {
		log = &usb_tINTR_XFERLOG;
	}
	ptBefore = &log->start;
	ptAfter  = &log->end;

	if(log->start_addr != log->end_addr) {
		DEBUG_ERROR_CALL( 0, "xfer is not same!!!\n", (int*)log);
		err = USB_NG;
	}

	if(!ptBefore->ptPipe || !ptAfter->ptPipe) {
		DEBUG_ERROR_CALL( 0, "pipe lost!", NULL);
		err = USB_NG;
		goto end;
	}
	if(ptBefore->ptPipe != ptAfter->ptPipe) {
		DEBUG_ERROR_CALL( 0, "different pipe!", NULL);
		err = USB_NG;
	}
	if(ptBefore->pvBuffer != ptAfter->pvBuffer) {
		DEBUG_ERROR_CALL( 0, "buffer addr is changed!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->usLength != ptAfter->usLength) {
		DEBUG_ERROR_CALL( 0, "length info is changed!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->usActLen != 0) {
		DEBUG_ERROR_CALL( 0, "actual xfer length is not 0, before transfer!\n", NULL);
		err = USB_NG;
	}
	if(!(ptAfter->usFlags & (USBD_SHORT_XFER_OK | USBD_FORCE_SHORT_XFER)) &&
	   ptAfter->usActLen != ptAfter->usLength &&
		ptAfter->tStatus != USBD_SHORT_XFER) {
		DEBUG_ERROR_CALL( 0, "illegal short xfer!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->usFlags != ptAfter->usFlags) {
		DEBUG_ERROR_CALL( 0, "flag is changed!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->sTimeout != ptAfter->sTimeout) {
		DEBUG_ERROR_CALL( 0, "timeout time is changed!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->tStatus != USBD_NOT_STARTED) {
		DEBUG_ERROR_CALL( 0, "xfer initialize error!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->tCallback != ptAfter->tCallback) {
		DEBUG_ERROR_CALL( 0, "callback is changed!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->cDone || !ptAfter->cDone) {
		DEBUG_ERROR_CALL( 0, "cDone is insane!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->cRepeat != ptAfter->cRepeat) {
		DEBUG_ERROR_CALL( 0, "cRepeat has changed!\n", NULL);
		err = USB_NG;
	}
	if(XFER_ETYPE(ptAfter) != UE_CONTROL &&
	   XFER_ETYPE(ptAfter) != UE_INTERRUPT &&
	   ptAfter->cRepeat) {
		DEBUG_ERROR_CALL( 0, "invalid cRepeat flag!\n", NULL);
		err = USB_NG;
	}
	if(XFER_ETYPE(ptAfter) == UE_CONTROL && !ptAfter->ptRequest) {
		DEBUG_ERROR_CALL( 0, "device request without request!\n", NULL);
		err = USB_NG;
	}
	if(XFER_ETYPE(ptAfter) == UE_CONTROL && ptBefore->ptRequest != ptAfter->ptRequest) {
		DEBUG_ERROR_CALL( 0, "request has changed!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->ptDevice != ptAfter->ptDevice) {
		DEBUG_ERROR_CALL( 0, "parent device has changed!\n", NULL);
		err = USB_NG;
	}
	if(ptBefore->ptDevice != ptBefore->ptPipe->ptDevice) {
		DEBUG_ERROR_CALL( 0, "reference to the device is invalid\n", NULL);
		err = USB_NG;
	}
	
  end:
	return err;
}





#endif	/* defined(USBD_UTIL) */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
