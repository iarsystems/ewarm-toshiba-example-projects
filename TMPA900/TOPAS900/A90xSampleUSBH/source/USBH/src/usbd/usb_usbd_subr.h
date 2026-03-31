/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 * @ingroup		usbd_subr
 */

/* $Id: usb_usbd_subr.h 41 2014-01-27 14:05:18Z danielru $ */

/*-
 * Copyright (c) 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (lennart@augustsson.net) at
 * Carlstedt Research & Technology.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _USB_USBD_SUBR_H_SEEN_
#define _USB_USBD_SUBR_H_SEEN_

#include "usb_config.h"
#include "usb_usbd_class.h"
#include "usb_usbd_var.h"


/*!
 * \addtogroup usbd_subr USBDサブルーチン
 * \ingroup	usbd
 * @{
 */


/* ********************************************************* */
/*                  Function Declarations                    */
/* ********************************************************* */
/* -------------------- basic -------------------- */
extern usbd_status			usb_USBDOpenPipe(usbd_interface_t* ptIface,
											 uint8_t ucAddr,
											 usbd_pipe_t** pptOutPipe);
extern void					usb_USBDKillPipe(usbd_pipe_t* ptPipe);
extern usbd_status			usb_USBDAbortPipe(usbd_pipe_t* ptPipe);

extern void					usb_USBDChangePortStage(usbd_port_t* ptPort,
													usbd_port_stage_t tStage,
													int16_t iErrCode);
extern void					usb_USBDAttachClassDriver(usbd_device_t* ptDevice,
													  USBD_typeClassDriver* ptClsDrv);
extern void					usb_USBDDetachClassDriver(usbd_device_t* ptDevice);
extern usbd_status			usb_USBDNewDevice(usbd_bus_t* ptBus,
											  uint8_t ucDepth,
											  int8_t cIsLowSpeed,
											  usbd_port_t* ptPort,
											  uint8_t ucPortNo);
extern void					usb_USBDFreeDevice(usbd_device_t* ptDevice);
extern void					usb_USBDDisconnectPort(usbd_port_t* ptPort);



/* -------------------- device request -------------------- */
extern usbd_status			usb_USBDDeviceRequest(usbd_device_t* ptDevice,
												  usb_device_request_t* ptRequest,
												  void* pvBuffer,
												  uint16_t* pusOutActlen,
												  int16_t sTimeout,
												  usbd_callback fpCallback);
extern usbd_status			usb_USBDResetPort(usbd_device_t* ptDevice,
											  uint8_t ucPortNo,
											  usb_port_status_t* ptOutStatus);
extern usbd_status			usb_USBDSetHubFeature(usbd_device_t* ptDevice, uint16_t usSel);
extern usbd_status			usb_USBDClearHubFeature(usbd_device_t* ptDevice, uint16_t usSel);
extern usbd_status			usb_USBDSetPortFeature(usbd_device_t* ptDevice,
												   uint8_t ucPortNo,
												   uint16_t usSel);
extern usbd_status			usb_USBDClearPortFeature(usbd_device_t* ptDevice,
													 uint8_t ucPortNo,
													 uint16_t usSel);
extern usbd_status			usb_USBDSetConfigIndex(usbd_device_t* ptDevice, int16_t sIndex);
extern usbd_status			usb_USBDGetHubStatus(usbd_device_t* ptDevice,
												 usb_hub_status_t* ptOutStat);
extern usbd_status			usb_USBDGetPortStatus(usbd_device_t* ptDevice,
												  uint8_t ucPortNo,
												  usb_port_status_t* ptOutStat);
extern void					usb_USBDClearEndpointToggle(usbd_pipe_t* ptPipe);

/* -------------------- accessor -------------------- */
extern usbd_status			usb_USBDDeviceToInterface(usbd_device_t* ptDevice,
													  uint8_t ucIfaceNo,
													  usbd_interface_t** pptOutIface);
extern usbd_status			usb_USBDGetInterfaceNumber(usbd_device_t* ptDevice,
													   uint8_t* pucOutNumOfIfaces);
extern usbd_device_t*		usb_USBDPipeToDevice(usbd_pipe_t* ptPipe);
extern usb_endpoint_descriptor_t*
							usb_USBDInterfaceToEndpointDesc(usbd_interface_t* ptIface,
															uint8_t ucIndex);

extern usbd_status			usb_USBDClearEndpointStall(usbd_pipe_t* ptPipe);



/* -------------------- utils -------------------- */
extern void					usb_USBDWaitMs(uint16_t usInterval);
#if 0
extern usbd_status			usb_USBDResetDevice(usbd_device_t* ptDevice);
#endif

/* -------------------- xfer -------------------- */
extern usbd_xfer_t*			usb_USBDAllocXfer(usbd_device_t* ptDevice);
extern usbd_status			usb_USBDFreeXfer(usbd_xfer_t* ptXfer);
extern void					usb_USBDInitXfer(usbd_xfer_t* ptXfer,
											 usbd_pipe_t* ptPipe,
											 void* vpBuffer,
											 uint16_t usLength,
											 int16_t sTimeout,
											 usbd_callback fpCallback);
extern usbd_status			usb_USBDStartTransfer(usbd_xfer_t* ptXfer);
extern void					usb_USBDTransferDone(usbd_xfer_t* ptXfer);


/* ********************************************************* */
/*                 下位(HCD)への公開関数                     */
/* ********************************************************* */
/* 転送完了時に HCD から呼び出される関数 */
USB_EXPORT void				usb_USBD_vTransferDone(usbd_xfer_t* ptXfer);
USB_EXPORT void				usb_USBD_vRaiseUnrecoverableError(void);

/*!
 * @}
 */



#endif /* _USB_USBD_SUBR_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
