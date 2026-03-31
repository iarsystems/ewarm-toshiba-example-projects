/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 * @ingroup		usbd_subr
 */

/* $Id: usb_usbd_subr.c 41 2014-01-27 14:05:18Z danielru $ */

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

#include "usb_config.h"
#include <string.h>	/* memset(), memcpy() */
#include "usb_usbd_subr.h"
#include "usb_usbd_var.h"
#include "usb_uhub.h"
#include "usb_usbd_mem.h"
#include "hcd/ohci/usb_ohci.h"
#include "util/usb_tmr.h"

#include "util/usb_trace.h"
#include "util/usb_dbg.h"
#if defined(USBD_UTIL)
#include "usb_usbd_util.h"
#endif


/* ********************************************************* */
/*                 Constants & Macros                        */
/* ********************************************************* */
/*!
 * \param list	確認するリストの head
 * \retval 0	リストは空でない
 * \retval !0	リストは空である
 *
 * リストが空であるか判定するマクロ
 */
#define DLIST_IS_EMPTY(list)	((list)->first == NULL)


/* ********************************************************* */
/*                 Function Declarations                     */
/* ********************************************************* */
static usbd_status		setupPipe(usbd_device_t* ptDevice,
								  usbd_interface_t* ptIface,
								  usbd_endpoint_t* ptEp,
								  usbd_pipe_t** pptOutPipe);
static usbd_status		closePipe(usbd_pipe_t* ptPipe);

static usbd_status		attachDevice(usbd_device_t* ptDevice, uint8_t ucPortNo, uint8_t ucAddr);
static int16_t			getNewAddr(usbd_bus_t* ptBus);
#if 0 /* not used */
static void				discover(usb_softc_t* ptSc);
#endif

static usb_interface_descriptor_t*
						findIdesc(usb_config_descriptor_t* ptCdesc,
								  uint8_t ucIfcIdx,
								  uint8_t ucAltIdx);
static usbd_status		fillIfaceData(usbd_device_t* ptDevice, uint8_t ucIfcIdx, uint8_t ucAltIdx);
static void				freeIfaceData(usbd_device_t* ptDevice, uint8_t ucIfcNo);

static usbd_status		getDesc(usbd_device_t* ptDevice,
								int16_t sType,
								int16_t sIndex,
								uint16_t usLen,
								void* pvOutDesc);
static usbd_status		getFullDeviceDesc(usbd_device_t* ptDevice);
static usbd_status		getConfigDesc(usbd_device_t* ptDevice,
									  int16_t sConfIdx,
									  usb_config_descriptor_t* ptOutCdesc);
#if 0 /* not used */
static usbd_status		getInterface(usbd_interface_t* ptIface, uint8_t* pucOutIdesc);
#endif
static usbd_status		setAddress(usbd_device_t* ptDevice, uint8_t ucAddr);
static usbd_status		setConfig(usbd_device_t* ptDevice, uint8_t ucConfNo);
static usbd_status		getDeviceStatus(usbd_device_t* ptDevice, usb_status_t* ptSt);
static usbd_status		getStringDesc(usbd_device_t* ptDevice,
									  usb_string_descriptor_t* ptSdesc,
									  uint8_t ucSindex,
									  uint16_t usLangId,
									  uint16_t* pusSize);
static usbd_status		getString(usbd_device_t* ptDevice, uint8_t ucSi, int8_t* pcBuf);

#if 0 /* not used */
static usb_endpoint_descriptor_t*
						getEndpointDescriptorForIndex(usbd_interface_t* ptIface, uint8_t ucIndex);
static usb_endpoint_descriptor_t*
						getEndpointDescriptorForAddr(usbd_interface_t* ptIface, uint8_t ucAddr);
#endif /* not used */

static void				initDefaultXfer(usbd_xfer_t* ptXfer,
										usbd_device_t* ptDevice,
										int16_t sTimeout,
										usb_device_request_t* ptRequest,
										void* pvBuffer,
										uint16_t usLength,
										usbd_callback fpCallback);



/* ========================================================= */
/*                       パイプの操作                        */
/* ========================================================= */
/*!
 * \brief パイプをオープンする
 * \param ptIface		パイプに対応するインターフェイス
 * \param ucAddr		オープンするパイプのエンドポイントアドレス
 * \param pptOutPipe	オープンしたパイプ
 * \return				usbd_status 型によるエラーの通知
 *
 * ptIface, ucAddr で指定されたパイプをオープンして、pptOutPipe に返す。
 */
usbd_status
usb_USBDOpenPipe(usbd_interface_t* ptIface, uint8_t ucAddr, usbd_pipe_t** pptOutPipe)
{
	usbd_status err;
	usbd_endpoint_t* ptEp;
	uint8_t i;
	usbd_pipe_t* ptPipe = NULL;

	USB_TRACE_ENTER1(1, usb_USBDOpenPipe, ucAddr);
	if(!ptIface) {
		err = USBD_INVAL;
		goto end;
	}
	if(!ptIface->ptEndpoints) {
		err = USBD_IOERROR;
		goto end;
	}
	for(i = 0; i < ptIface->ptIdesc->bNumEndpoints; i++) {
		ptEp = &ptIface->ptEndpoints[i];
		if(!ptEp->ptEdesc) {
			DEBUG_ERROR_LOG(("usb_USBDOpenPipe: no endpoint desc for addr %u\n", i));
			err = USBD_IOERROR;
			goto end;
		}
		if(ptEp->ptEdesc->bEndpointAddress == ucAddr) {
			/* 既オープンしているパイプか調べる */
			{
				usbd_pipe_t* ptAPipe;
				
				SLIST_FOREACH(ptAPipe, usbd_pipe_t, &ptIface->pipes) {
					if(ptAPipe->ptEndpoint->ptEdesc->bEndpointAddress == ucAddr) {
						/* 既にオープンしている */
						err = USBD_IN_USE;
						goto end;
					}
				}
			}
			
			/* パイプのセットアップ */
			err = setupPipe(ptIface->ptDevice, ptIface, ptEp, &ptPipe);
			if(err) {
				DEBUG_ERROR_LOG(("usb_USBDOpenPipe: failed to pipe setup. (err=%u)\n", err));
				goto end;
			}
			DLIST_INSERT_HEAD(&ptIface->pipes, ptPipe);
			*pptOutPipe = ptPipe;
			err = USBD_NORMAL_COMPLETION;
			goto end;
		}
	}
	err = USBD_BAD_ADDRESS;
	DEBUG_ERROR_LOG(("usb_USBDOpenPipe: addr %u is invalid.\n", ucAddr));
  end:
	USB_TRACE_LEAVE1(1, usb_USBDOpenPipe, err);
	return err;
}

/*!
 * \brief パイプをクローズする
 * \param ptPipe	クローズするパイプ
 * \return			usbd_status 型によるエラーの通知
 *
 * ptPipe で指定されたパイプをクローズする。
 * 他にパイプを参照しているものがない場合、管理構造からも破棄する。
 * usb_USBDKillPipe からのみ呼び出される。パイプを破棄するには KillPipe() を利用すること。
 */
static usbd_status
closePipe(usbd_pipe_t* ptPipe)
{
	if(--ptPipe->cRefcnt)
		goto end;
	
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("closePipe: close and free pipe (%#08x)\n", ptPipe);
#endif
	if(ptPipe->ptIface) { /* not default pipe */
		DLIST_REMOVE(&ptPipe->ptIface->pipes, ptPipe); /* remove from list */
	}
	ptPipe->tMethods.fpClose(ptPipe);
	usb_OHCI_vFreePipe(ptPipe);

  end:
	return USBD_NORMAL_COMPLETION;
}

/*! 
 * \brief パイプをクローズする
 * \param ptPipe		クローズするパイプ
 *
 * ptPipe で指定されたパイプをクローズする。
 * ptPipe が転送中であれば、それのアボートも行なう。
 */
void
usb_USBDKillPipe(usbd_pipe_t* ptPipe)
{
	usbd_xfer_t* ptXfer;
	
	USB_TRACE_ENTER1(2, usb_USBDKillPipe, ptPipe);
	if(!ptPipe) {
		goto end;
	}
	ptXfer = ptPipe->ptXfer;
	if(ptXfer) {
		/* 転送中データが存在する場合 */
		usb_USBDAbortPipe(ptPipe); /* これにより HCD から TransferDone が呼び出される */
		if(ptXfer->cRepeat) {
			ptPipe->ptXfer = NULL; /* cRepeatをもつ xfer は TransferDone ではNULLにならないため */
			usb_USBDFreeXfer(ptXfer); /* cRepeat のときのみ。他の場合TransferDoneでされる */
		}
	}
	ptPipe->cRefcnt = 1;	/* closePipe() で、確実に破棄するため */
	closePipe(ptPipe);
  end:
	USB_TRACE_LEAVE(2, usb_USBDKillPipe);
}

/*!
 * \brief パイプのアボート
 * \param ptPipe	パイプ
 * \return			usbd_status 型によるエラーの通知
 *
 * ptPipe で指定したパイプの転送を中断する。
 */
usbd_status
usb_USBDAbortPipe(usbd_pipe_t* ptPipe)
{
	usbd_xfer_t* ptXfer;
	usbd_status err = USBD_NORMAL_COMPLETION;

	USB_TRACE_ENTER1(2, usb_USBDAbortPipe, ptPipe);
	if(!ptPipe) {
		err = USBD_IOERROR;
		goto end;
	}
	ptXfer  = ptPipe->ptXfer;

	if(ptXfer) {
		/* make the HC abort it (and invoke the callback) */
		ptPipe->tMethods.fpAbort(ptXfer);
	}
	
  end:
	USB_TRACE_LEAVE1(2, usb_USBDAbortPipe, USBD_NORMAL_COMPLETION);
	return err;
}

/*!
 * \brief パイプを新規作成する
 * \param ptDevice		デバイス
 * \param ptIface		インターフェイス
 * \param ptEp			エンドポイント
 * \param pptOutPipe	生成されたパイプ
 * \return				usbd_status 型によるエラーの通知
 *
 * ptDevice, ptIface, ptEp の内容からパイプを新規に生成し、pptOutPipe に
 * 出力する。
 */
static usbd_status
setupPipe(usbd_device_t* ptDevice,
		  usbd_interface_t* ptIface,
		  usbd_endpoint_t* ptEp,
		  usbd_pipe_t** pptOutPipe)
{
	usbd_status err;
	usbd_pipe_t* ptPipe;

	ptPipe = usb_OHCI_ptAllocPipe();
	if(!ptPipe) {
		err = USBD_NOMEM;
		goto bad;
	}
	/* ptPipe->ptXfer = NULL; (already cleared) */
	ptPipe->ptDevice = ptDevice;
	ptPipe->ptIface = ptIface;
	ptPipe->ptEndpoint = ptEp;
	ptEp->cRefcnt++;
	ptPipe->cRefcnt = 1;
	ptPipe->ucInterval = ptEp->ptEdesc->bInterval;
	DLIST_ENTRY_INIT(&ptPipe->pipes);
	err = usb_OHCI_iOpen(ptPipe);
	if(err) {
		ptEp->cRefcnt--;
		usb_OHCI_vFreePipe(ptPipe);
		DEBUG_ERROR_LOG(("setupPipe: failed to allocate pipe\n"));
		goto bad;
	}
	err = USBD_NORMAL_COMPLETION;
	*pptOutPipe = ptPipe;
  bad:
	return err;
}


/*!
 * \brief デバイスのアタッチ
 * \param ptDevice	アタッチされたデバイス
 * \param ucPortNo	アタッチされたポート番号
 * \param ucAddr	アタッチされたデバイスのアドレス
 * \return			usbd_status 型によるエラーの通知
 * \todo デバイスドライバが後からインストールされても、アタッチできるようにすることは可能？
 *
 * ucPortNo 番号のポートにデバイスアドレス ucAddr でデバイスをアタッチする。
 */
static usbd_status
attachDevice(usbd_device_t* ptDevice, uint8_t ucPortNo, uint8_t ucAddr)
{
	usbd_status err;
	USBD_typeClassDriver* ptDrv;
	int16_t sCfgIdx;
	bool blAttached;

#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv(">>>>> new device attached! <<<<< (attachDevice)\n");
	usb_Logv("  --> addr=%u, product='%s', manufacturer='%s', vendorID=%#04x, prodID=%#04x\n",
			 ptDevice->ucAddress, ptDevice->pcProdName, ptDevice->pcManuName,
			 ptDevice->tDdesc.idVendor, ptDevice->tDdesc.idProduct);
	usb_Logv("  --> class=%#02x(%s)\n", ptDevice->tDdesc.bDeviceClass,
			 ptDevice->tDdesc.bDeviceClass == UICLASS_HUB ? "HUB" : "notHUB");
	usb_Logv("--------------------------------\n");
#endif
	
	/* invoke notification */
	usb_USBDChangePortStage(ptDevice->ptPowerSrc, kPortIdentified, 0);
	
	/* attach a class driver to the device. */
	if(ptDevice->tDdesc.bDeviceClass == UICLASS_HUB) {
		/* hub device */
		err = usb_USBDSetConfigIndex(ptDevice, 0);
		if(err) {
			DEBUG_ERROR_LOG(("attachDevice: failed to set config index\n"));
			goto bad;
		}
		err = usb_iUHUBNewHub(ptDevice);
		goto found;
	}

	/* search for registered class drivers */
	SLIST_FOREACH(ptDrv, USBD_typeClassDriver, &ptDevice->ptBus->ptSoftc->drvs) {
		if(!ptDrv->ulDeviceId) {
			blAttached = ptDrv->blAttachDeviceFn((uint32_t)ptDevice, ptDrv->ulArg);
			if(blAttached) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
				usb_Logv("attachDevice: device(%u) driver attached!\n", ptDevice->ucAddress);
#endif
				/* register class driver to device */
				usb_USBDAttachClassDriver(ptDevice, ptDrv);
				err = USBD_NORMAL_COMPLETION;
				goto found;	/* driver accepted */
			}
		}
		/* try next driver */
	}
	err = USBD_NO_CLASS_DRIVER; /* no driver attached */
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("attachDevice: no driver attached! (class=%#02x, subclass=%#02x, protocol=%#02x\n",
			 ptDevice->tDdesc.bDeviceClass,
			 ptDevice->tDdesc.bDeviceSubClass,
			 ptDevice->tDdesc.bDeviceProtocol);
#endif
	
  found:
	/* invoke notification */
	if(!err) {
		usb_USBDChangePortStage(ptDevice->ptPowerSrc, kPortAttached, 0);
	}
	
  bad:
	USB_TRACE_LEAVE1(1, attachDevice, err);
	return err;
}


/*!
 * \brief ポート状態変化を通知コールバックで通知する
 * \param ptPort	状態変化が起きたポート
 * \param ptBus		USBバス管理構造
 * \param tStage	変化する状態(usbd_port_stage_t)
 * \param iErrCode	通知するエラーコード(Ignoreのときのみ使用)
 *
 * ptPort で指定するポートの状態を tStage に切替える。
 * ユーザAPIから対応する状態通知コールバックが登録されている場合
 * は、それを呼び出し状態の通知を行なう。
 * 対応する状態変化通知コールバックが登録されている場合には、
 * 通知は行なわれない。
 * kPortIgnored 状態に移る時には iErrCode で指定したエラーコードも通知される。
 * それ以外の場合には iErrCode 引数は無視される。
 * また、デバイスアドレスが１であるデバイス(=ルートハブ)については通知を行なわない。
 */
void
usb_USBDChangePortStage(usbd_port_t* ptPort,
						usbd_port_stage_t tStage,
						int16_t iErrCode)
{
	usbd_bus_t* ptBus;
	
	USB_TRACE_ENTER1(2, usb_USBDChangePortStage, ptPort);
	
	if(!ptPort)
		return;
	ptBus = ptPort->ptParent->ptBus;

	/* change port stage */
	ptPort->tPortStage = tStage;

	/* invoke notification */
	if(ptPort->ptDevice && ptPort->ptDevice->ucAddress == 1)
		/* device is roothub */
		return;
	
	if(tStage > kPortNoDevice) {
		if(tStage != kPortIgnored) {
			void (*fpCallback)(uint32_t);
			
			fpCallback = *(&ptBus->ptSoftc->tNotifications.fpConnected + tStage - kPortConnected);
			if(fpCallback) {
				(*fpCallback)((uint32_t)ptPort);
			}
		}
		else { /* tStage == kPortIgnored */
			if(ptBus->ptSoftc->tNotifications.fpIgnored) {
				(*ptBus->ptSoftc->tNotifications.fpIgnored)((uint32_t)ptPort, iErrCode);
			}
		}
	}

	USB_TRACE_LEAVE1(2, usb_USBDChangePortStage, 0);
}


/*!
 * \brief クラスドライバのアタッチ処理を行なう
 * \param ptDevice		アタッチするデバイス
 * \param ptClsDrv		デバイスにアタッチするクラスドライバ
 *
 * ptDevice で指定したデバイスに対し、ptClsDrv で指定したクラスドライバ
 * をアタッチする。
 */
void
usb_USBDAttachClassDriver(usbd_device_t* ptDevice, USBD_typeClassDriver* ptClsDrv)
{
	USB_TRACE_ENTER1(2, usb_USBDAttachClassDriver, ptDevice);
	
	if(!ptDevice || !ptClsDrv) {
		goto end;
	}

	ptDevice->ptDrv = ptClsDrv;
	ptClsDrv->ulDeviceId = (uint32_t)ptDevice;
	
  end:
	USB_TRACE_LEAVE1(2, usb_USBDAttachClassDriver, 0);
}

/*!
 * \brief デバイスに割り当てられているクラスドライバのデタッチ処理を行なう
 * \param ptDevice		クラスドライバのデタッチを行なうデバイス
 *
 * ptDevice に割り当てられているクラスドライバを解除し、「登録未割当」の状態に戻し、
 * 割り当てられているクラスドライバに対してデタッチを通知する。
 */
void
usb_USBDDetachClassDriver(usbd_device_t* ptDevice)
{
	USBD_typeClassDriver* ptClsDrv;
	
	USB_TRACE_ENTER1(2, usb_USBDDetachClassDriver, ptDevice);

	if(!ptDevice || !ptDevice->ptDrv) {
		goto end;
	}
	ptClsDrv = ptDevice->ptDrv;
	
	/* detach class driver from device */
	ptClsDrv->ulDeviceId = 0;
	ptDevice->ptDrv = NULL;
	
	/* invoke detach notification callback */
	if(ptClsDrv->vDetachDeviceFn) {
		(*ptClsDrv->vDetachDeviceFn)(ptClsDrv->ulArg);
	}
	
  end:
	USB_TRACE_LEAVE1(2, usb_USBDDetachClassDriver, 0);
}


/*!
 * \brief 新しいデバイスアドレスを取得する
 * \param ptBus		バス
 * \return	新しいデバイスに割り当てるアドレス。割り当て可能なアドレスが存在しない
 *			場合には -1 を返す。
 *
 * bus 上に重複しないように、デバイスアドレスを取得する。
 * 取得できなかった場合は、-1 を返す。
 */
static int16_t
getNewAddr(usbd_bus_t* ptBus)
{
	int16_t i;

	for(i = 0; i < USBD_MAX_DEVICES; i++) 
		if(!ptBus->pptDevices[i]) {
			if(i >= 0xff) {
				return -1; /* too match devices (over device->ucAddress) */
			}
			return i + 1;	/* addr 0 is reserved for start addr of a device. */
		}
	DEBUG_ERROR_LOG(("getNewAddr: do not provide new addr!\n"));
	return -1; /* no address */
}

/*!
 * \brief 新規デバイスの登録
 * \param ptBus			デバイスが属するバス
 * \param ucDepth		ルートハブからの深さ
 * \param cIsLowSpeed	デバイスのスピード
 * \param ptPort		デバイスに割り当てられたポート
 * \param ucPortNo		デバイスに割り当てられたポート番号
 * \return				usbd_status 型によるエラーの通知
 *
 * ハブポート上にある、Powered 状態のデバイスに対して、
 * アドレスの設定や各種デスクリプタの取得などを行ない、
 * Addressed 状態にして、各種情報を USBD 管理構造に登録する。
 */
usbd_status
usb_USBDNewDevice(usbd_bus_t* ptBus,
				  uint8_t ucDepth,
				  int8_t cIsLowSpeed,
				  struct usbd_port* ptPort,
				  uint8_t ucPortNo)
{
	usbd_status err;
	int16_t i;
	int16_t sAddr;
	usb_device_descriptor_t* ptDdesc;
	usbd_device_t* ptDevice = NULL;
	usb_port_status_t* ptPortStat = NULL;

	USB_TRACE_ENTER1(1, usb_USBDNewDevice, ptBus);
	/* get address */
	sAddr = getNewAddr(ptBus);
	if(sAddr < 0) {
		err = USBD_NO_ADDR;
		DEBUG_ERROR_LOG(("usb_USBDNewDevice: no address remains\n"));
		goto bad;
	}

	/* make device */
	ptDevice = usb_USBDAllocDevice();
	if(!ptDevice) {
		err = USBD_NOMEM;
		goto bad;
	}

	/* setup default endpoint */
	ptDevice->tDefEdesc.bLength = USB_ENDPOINT_DESC_SIZE;
	ptDevice->tDefEdesc.bDescriptorType = UDESC_ENDPOINT;
	ptDevice->tDefEdesc.bEndpointAddress = USB_CONTROL_ENDPOINT;
	ptDevice->tDefEdesc.bmAttributes = UE_CONTROL;
	USB_SETW(ptDevice->tDefEdesc.wMaxPacketSize, USB_MAX_IPACKET);
	ptDevice->tDefEdesc.bInterval = 0;
	ptDevice->tDefEp.ptEdesc = &ptDevice->tDefEdesc;
	ptDevice->ucAddress = USB_START_ADDR;
	ptDevice->tDdesc.bMaxPacketSize = 0;
	ptDevice->usPower = 0;
 	ptDevice->ucDepth = ucDepth;
	ptDevice->ptPowerSrc = ptPort;
	ptDevice->cLowSpeed = cIsLowSpeed;
	ptDevice->ptMyHub = ptPort->ptParent;
	ptDevice->ptBus = ptBus;
	/* ハブのポートに登録 */
	ptPort->ptDevice = ptDevice;

	/* establish the default pipe */
	err = setupPipe(ptDevice, 0, &ptDevice->tDefEp, (usbd_pipe_t**)&ptDevice->ptDefaultPipe);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDNewDevice: failed to setup default pipe\n"));
		goto bad;
	}

	{
		usbd_xfer_t* ptXfer;

		/* create the xfer for the control pipe. */
		/* パイプが Ctrl だったら xfer はパイプがクローズする(デバイスデタッチ)まで
		   解放せずに再利用する */
		if(!ptDevice->ptDefaultPipe->ptXfer) {
			ptXfer = usb_USBDAllocXfer(ptDevice);
			if(!ptXfer) {
				err = USBD_NOMEM;
				goto bad;
			}
			ptDevice->ptDefaultPipe->ptXfer = ptXfer;
			ptXfer->cRepeat = 1; /* a flag to use xfer without free */
		}
	}

	/* Set the address.  Do this early; some devices need that. */
	/* Try a few times in case the device is slow (i.e. outside specs.) */
	ptPortStat = usb_USBDAllocTinyBuffer(sizeof(*ptPortStat));
	if(!ptPortStat) {
		err = USBD_NOMEM;
		goto bad;
	}
	for(i = 0; i < 15; i++) {
		err = setAddress(ptDevice, (uint8_t)sAddr);
		if(!err)
			break;
		usb_USBDWaitMs(200); /* wait 200 msec */
		if((i & 3) == 3) { /* try reset. every 4-time-retry */
			usb_USBDResetPort(ptPort->ptParent, ptPort->ucPortNo, ptPortStat);
		}
	}
	if(err) {
		err = USBD_SET_ADDR_FAILED;
		DEBUG_ERROR_LOG(("usb_USBDNewDevice: failed to set address\n"));
		goto bad;
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("usb_USBDNewDevice: set the device address to %u.\n", sAddr);
#endif
	
	/* allow device time to set new address */
	usb_USBDWaitMs(USB_SET_ADDRESS_SETTLE);
	ptDevice->ucAddress = (uint8_t)sAddr; /* new device address now */
	ptDevice->ptBus->pptDevices[sAddr - 1] = ptDevice;

	/* get the first 8 bytes of the device descriptor */
	err = getDesc(ptDevice, UDESC_DEVICE, 0, USB_MAX_IPACKET, &ptDevice->tDdesc);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDNewDevice: failed to get short device descriptor\n"));
		goto bad;
	}
	if(ptDevice->tDdesc.bDescriptorType != UDESC_DEVICE) {
		/* Illegal device descriptor */
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBDNewDevice: invalid device descriptor\n"));
		goto bad;
	}

	/* set max-packet-size of Endpoint */
	USB_SETW(ptDevice->tDefEdesc.wMaxPacketSize, ptDevice->tDdesc.bMaxPacketSize);
	
	/* load full device descriptor */
	err = getFullDeviceDesc(ptDevice);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDNewDevice: failed to get full device descriptor\n"));
		goto bad;
	}

	err = getString(ptDevice, ptDevice->tDdesc.iProduct, ptDevice->pcProdName);
	if(err) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDNewDevice: getting string of iProduct failed.\n");
#else
		;
#endif
	}
	err = getString(ptDevice, ptDevice->tDdesc.iManufacturer, ptDevice->pcManuName);
	if(err) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDNewDevice: getting string of iManufacturer failed.\n");
#else
		;
#endif
	}
	
	/* assume 100mA bus powered for now. Changed when configured */
	ptDevice->usPower = USB_MIN_POWER;
	ptDevice->cSelfPowered = 0;

	err = attachDevice(ptDevice, ucPortNo, (uint8_t)sAddr);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDNewDevice: failed to attach device\n"));
		goto bad;
	}

	err = USBD_NORMAL_COMPLETION;
	goto good;

  bad:
	/* invoke notification */
	/* ASSERT(ptBus && ptBus->ptSoftc); */
	if(ptDevice && ptDevice->ptPowerSrc) {
		usb_USBDDisconnectPort(ptPort);
		ptDevice = NULL;
	}
	
  good:
	if(ptPortStat)
		usb_USBDDeallocTinyBuffer(ptPortStat);

	USB_TRACE_LEAVE1(1, usb_USBDNewDevice, err);
	return err;
}

/*!
 * \brief デバイス管理情報を解放する
 * \param ptDevice		解放するデバイス
 *
 * ptDevice で管理しているデバイス管理情報を解放する。
 */
void
usb_USBDFreeDevice(usbd_device_t* ptDevice)
{
	uint8_t i, ucNumIface;
	usbd_pipe_t *ptPipe, *ptNextPipe;

	USB_TRACE_ENTER1(1, usb_USBDFreeDevice, ptDevice);
	/* free default pipe */
	if(ptDevice->ptDefaultPipe) {
		usb_USBDKillPipe(ptDevice->ptDefaultPipe);
		ptDevice->ptDefaultPipe = NULL;
	}

	if(ptDevice->ptIfaces && ptDevice->ptCdesc) {
		/* SET_CONFIG されている */
		ucNumIface = ptDevice->ptCdesc->bNumInterfaces;
		for(i = 0; i < ucNumIface; i++) {
			/* free all pipes (abort and close) */
			for(ptPipe = (usbd_pipe_t*)ptDevice->ptIfaces[i].pipes.first;
				ptPipe;
				ptPipe = ptNextPipe) {
				ptNextPipe = (usbd_pipe_t*)ptPipe->pipes.next;
				usb_USBDKillPipe(ptPipe);
			}
			/* free all endpoints */
			freeIfaceData(ptDevice, i);
		}
		/* free interface */
		usb_USBDDeallocIfaces(ptDevice, ptDevice->ptIfaces);
		ptDevice->ptIfaces = NULL;
	}

	/* free config-desc */
	if(ptDevice->ptCdesc) {
		usb_USBDDeallocCDesc(ptDevice, ptDevice->ptCdesc);
		ptDevice->ptCdesc = NULL;
	}

	/* free hub data, if this device is a hub. */
	if(ptDevice->ptHub) {
		usb_vUHUBFreeHub(ptDevice->ptHub);
		ptDevice->ptHub = NULL;
	}
	USB_TRACE_LEAVE(1, usb_USBDFreeDevice);
}

#if 0 /* not used */
/*!
 * \brief ルートハブからデバイスツリーをチェックする
 * \param ptSc		usbドライバ固有パラメータ
 *
 * デバイスツリーをルートハブから探索して、バスイナミュレーション
 * を行なう。
 */
static void
usb_USBDDiscover(usb_softc_t* ptSc)
{
	int s;

	USB_TRACE_ENTER1(1, usb_USBDDiscover, sc->ptBus->cNeedsExplore);
	/*
	 * We need mutual exclusion while traversing the device tree,
	 * but this is guaranteed since this function is only called
	 * from the event thread for the controller.
	 */
	while(ptSc->ptBus->cNeedsExplore) {
		ptSc->ptBus->cNeedsExplore = 0;
		ptSc->ptBus->ptRootHub->ptHub->fpExplore(ptSc->ptBus->ptRootHub);
	}
	USB_TRACE_LEAVE(1, usb_USBDDiscover);
}
#endif /* not used */

/*!
 * \brief ポートに接続されているデバイスを取り除く
 * \param ptPort			処理するポート
 *
 * ptPort で指定するポートがディスコネクトした場合の
 * 処理を行なう。
 */
void
usb_USBDDisconnectPort(usbd_port_t* ptPort)
{
	usbd_device_t* ptDevice = ptPort->ptDevice;

	USB_TRACE_ENTER1(1, usb_USBDDisconnectPort, (uint32_t)ptPort);
	if(!ptDevice) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDDisconnectPort: device already disappeared! (portno=%u)\n",
				 ptPort->ucPortNo);
#endif
		goto end;
	}
	
	if(ptDevice->ucAddress > 0 && ptDevice->ucAddress <= USBD_MAX_DEVICES)
		ptDevice->ptBus->pptDevices[ptDevice->ucAddress - 1] = NULL;
	ptPort->ptDevice = NULL;
	usb_USBDFreeDevice(ptDevice);
	usb_USBDDeallocDevice(ptDevice);
	
  end:
	USB_TRACE_LEAVE(1, usb_USBDDisconnectPort);
}

/*!
 * \brief フルコンフィグデスクリプタから指定したインターフェイスデスクリプタを取り出す
 * \param ptCdesc	コンフィグデスクリプタ(フルサイズ)
 * \param ucIfcIdx	インターフェイスインデックス
 * \param ucAltIdx	オルタネイトインデックス
 * \return			インターフェイスデスクリプタ
 *
 * フルサイズのコンフィグレーションデスクリプタから、
 * ucIfcIdx, ucAltIdx で指定したインターフェイスのインターフェイスデスクリプタ
 * 部分を返す。
 *
 * \note インターフェイス・デスクリプタは、フルサイズのコンフィグ・デスクリプタに１つ
 * または複数アペンドされている。また、各インターフェイス・デスクリプタは、
 * 同じように０個以上のエンドポイント・デスクリプタがアペンドされた形となっている。
 */
static usb_interface_descriptor_t*
findIdesc(usb_config_descriptor_t* ptCdesc, uint8_t ucIfcIdx, uint8_t ucAltIdx)
{
	usb_interface_descriptor_t* ptIdesc;
	uint8_t ucCurIdx, ucLastIdx, ucCurAltIdx = 0;
	int8_t* cur = (int8_t*)ptCdesc;
	int8_t* end;

	USB_TRACE_ENTER1(2, findIdesc, ptCdesc);
	if(!ptCdesc) {
		goto bad;
	}
	end = cur + USB_GETW(ptCdesc->wTotalLength);
	
	for(ucCurIdx = ucLastIdx = 0xff; cur < end; ) {
		/* get idesc */
		ptIdesc = (usb_interface_descriptor_t*)cur;
		cur += ptIdesc->bLength;
		
		/* check idesc */
		if(ptIdesc->bLength == 0) { /* bad iface descriptor */
			DEBUG_ERROR_LOG(("findIdesc: bad descriptor (length = 0)\n"));
			break;
		}
		if((cur <= end) && (ptIdesc->bDescriptorType == UDESC_INTERFACE)) {
			if(ptIdesc->bInterfaceNumber != ucLastIdx) {
				ucLastIdx = ptIdesc->bInterfaceNumber;
				ucCurIdx++;
				ucCurAltIdx = 0;
			}
			else {
				/* alternate interface */
				ucCurAltIdx++;
			}
			if((ucIfcIdx == ucCurIdx) && (ucAltIdx == ucCurAltIdx)) {
				/* found */
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
				usb_Logv("findIdesc: found idesc idx=%u, altidx=%u\n",
						 ucCurIdx, ucCurAltIdx);
#endif
				goto end;
			}
		}
	}
  bad:
	ptIdesc = NULL;
	DEBUG_ERROR_LOG(("findIdesc: idesc not found for idx=%u altidx=%u\n", ucIfcIdx, ucAltIdx));
  end:
	USB_TRACE_LEAVE1(2, findIdesc, ptIdesc);
	return ptIdesc;
}

/*!
 * \brief インターフェイスとエンドポイントの情報をフィルする
 * \param ptDevice	デバイス
 * \param ucIfcIdx	インターフェイスインデックス
 * \param ucAltIdx	オルタネイトインデックス
 * \return			usbd_status 型によるエラーの通知
 *
 * フルサイズのコンフィグレーションデスクリプタから、
 * ucIfcIdx, ucAltIdx で指定したインターフェイスのインターフェイスデスクリプタ
 * 部分を選び、そのインターフェイスに含まれるすべてのエンドポイント・デスクリプタ
 * からエンドポイント管理構造体(usbd_endpoint_t)を準備/作成する。
 * 作成したエンドポイント構造体は ptDevice->ptIfaces[ucIfcIdx]->ptEndpoints[] に入れられる。
 */
static usbd_status
fillIfaceData(usbd_device_t* ptDevice, uint8_t ucIfcIdx, uint8_t ucAltIdx)
{
	usbd_status err;
	int8_t *cur, *end;
	uint8_t ucNumEd, i;
	usb_interface_descriptor_t* ptIdesc;
	usbd_interface_t* ptIfc = &ptDevice->ptIfaces[ucIfcIdx];

	USB_TRACE_ENTER1(2, fillIfaceData, ptDevice);
	if(!ptDevice->ptCdesc) {
		err = USBD_INVAL;
		goto bad;
	}
	ptIdesc = findIdesc(ptDevice->ptCdesc, ucIfcIdx, ucAltIdx);
	if(!ptIdesc) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("fillIfaceData: idesc for ifaceidx=%u, altidx=%u not found.\n",
						 ucIfcIdx, ucAltIdx));
		goto bad;
	}
	/* ucIfcIdx, ucAltIdx の値の正当性チェックは、上のfindIdesc()により処理されるため
	   チェックしない */
	ptIfc->ptDevice = ptDevice;
	ptIfc->ptIdesc = ptIdesc;
	ptIfc->ucIndex = ucIfcIdx;
	ptIfc->ucAltIndex = ucAltIdx;
	ucNumEd = ptIdesc->bNumEndpoints;
	if(ucNumEd) {
		ptIfc->ptEndpoints = usb_USBDAllocEndpoints(ptDevice, ucNumEd);
		if(!ptIfc->ptEndpoints) {
			err = USBD_NOMEM;
			goto bad;
		}
	}
	else {
		/* no endpoints */
		ptIfc->ptEndpoints = NULL;
	}
	
	/* get endpoint descriptors */
	cur = (int8_t*)ptIfc->ptIdesc + ptIfc->ptIdesc->bLength;
	end = (int8_t*)ptDevice->ptCdesc + USB_GETW(ptDevice->ptCdesc->wTotalLength);
#define ptEd ((usb_endpoint_descriptor_t*)cur)
	for(i = 0; i < ucNumEd; i++) {
		/* search an edesc from current pos till end of idesc */
		for( ; cur < end; cur += ptEd->bLength) {
			if(cur + ptEd->bLength <= end
			   && ptEd->bLength != 0
			   && ptEd->bDescriptorType == UDESC_ENDPOINT) {
				/* valid endpoint desc */
				goto found;
			}
			if(ptEd->bLength == 0 || ptEd->bDescriptorType == UDESC_INTERFACE) {
				/* invalid edesc or reached the end of idesc */
				break;
			}
		}
		/* passed end, or bad desc */
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("fillIfaceData: Bad Descriptor or edesc not found!\n"));
		goto bad;
		
	  found:
		/* found endpoint descriptor and establish it */
		ptIfc->ptEndpoints[i].ptEdesc = ptEd;
		ptIfc->ptEndpoints[i].cRefcnt = 0;
		cur += ptEd->bLength;
	}
#undef ptEd
	
	DLIST_INIT(&ptIfc->pipes);
	err = USBD_NORMAL_COMPLETION;
	goto good;
	
  bad:
	if(ptIfc->ptEndpoints) {
		usb_USBDDeallocEndpoints(ptDevice, ptIfc->ptEndpoints);
		ptIfc->ptEndpoints = NULL;
	}
  good:
	USB_TRACE_LEAVE1(2, fillIfaceData, err);
	return err;
}

/*!
 * \brief インタフェイス管理情報を解放する
 * \param ptDevice		デバイス
 * \param ucIfcNo		解放するインターフェイス番号
 *
 * ptDevice にある ucIfcNo で示されるインターフェイス番号をもつ
 * エンドポイント管理構造体をすべて解放する。
 */
static void
freeIfaceData(usbd_device_t* ptDevice, uint8_t ucIfcNo)
{
	usbd_interface_t* ptIfc;
	
	USB_TRACE_ENTER1(2, freeIfaceData, ptDevice);
	if(ptDevice && ptDevice->ptIfaces) {
		ptIfc = &ptDevice->ptIfaces[ucIfcNo];
	}
	else {
		goto end;
	}
	if(ptIfc->ptEndpoints) {
		usb_USBDDeallocEndpoints(ptDevice, ptIfc->ptEndpoints);
		ptIfc->ptEndpoints = NULL;
	}
  end:
	USB_TRACE_LEAVE(2, freeIfaceData);
}



/* --------------------------------------------------------- */
/*                  デバイスリクエスト関連                   */
/* --------------------------------------------------------- */
/*!
 * \brief デバイスリクエストの発行
 * \param device		デバイスリクエストを発行するデバイス
 * \param request		デバイスリクエスト
 * \param buffer		デバイスリクエストに付随する入出力データ(ない場合はNULLを指定)
 * \param outActlen		入出力データ長(不要な場合はNULLを指定)
 * \param timeout		転送のタイムアウト時間
 * \param callback		callback が NULL のときはブロッキングモードの転送となる
 * \return				usbd_status 型によるエラーの通知
 *
 * device で指定するデバイスに request で示されるデバイスリクエストを
 * 発行する。デバイスリクエストに送受信データが付随する場合には、
 * buffer でバッファを指定する。
 * outActlen に NULL 以外を指定すると、そのアドレスに送受信データ長が書き込まれる。
 * timeout には、転送のタイムアウト時間をミリ秒単位で指定する。
 * callback には、転送完了時に呼び出されるコールバック関数を指定する。
 * callback が NULL の場合には、コールバック呼び出しではなく、
 * 転送完了までがブロックされた動作となる。
 *
 * \note デバイス・リクエスト発行時に EP0 がストールした場合、内部で
 *       EP0 のストールの解除を試みる。発行したデバイス・リクエストはエラーのまま。
 *       この場合、エラーコードに USBD_STALL が返る。
 */
usbd_status
usb_USBDDeviceRequest(usbd_device_t* ptDevice,
					  usb_device_request_t* ptRequest,
					  void* pvBuffer,
					  uint16_t* pusOutActlen,
					  int16_t sTimeout,
					  usbd_callback fpCallback)
{
	usbd_status err;
	usbd_xfer_t* ptXfer = NULL;

	USB_TRACE_ENTER1(1, usb_USBDDeviceRequest, ptDevice);
	if(USB_GETW(ptRequest->wLength) > 0 && !pvBuffer) {
		err = USBD_INVAL;
		goto bad;
	}
	ptXfer = ptDevice->ptDefaultPipe->ptXfer;

	initDefaultXfer(ptXfer, ptDevice, sTimeout,
					ptRequest, pvBuffer, USB_GETW(ptRequest->wLength), 0);
	ptXfer->usFlags |= USBD_SYNCHRONOUS; /* XXX not referenced by HCD? */
	err = usb_USBDStartTransfer(ptXfer);

	if(pusOutActlen)
		*pusOutActlen = ptXfer->usActLen;
	
	if(err == USBD_STALLED) {
		/*
		 * The control endpoint has stalled.  Control endpoints
		 * should not halt, but some may do so anyway so clear
		 * any halt condition.
		 */
		/* endpoint 0 has stalled. */
		usb_device_request_t* ptReq;
		usb_status_t* ptStatus = NULL;
		usbd_status terr;

#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDDeviceRequest: endpoint 0 has stalled. retrying a transfer.\n");
#endif
#if defined(USBD_UTIL)
		USBD_COUNT_RETRY(device_request);
#endif
		ptReq = usb_USBDAllocDeviceRequest();
		if(!ptReq) {
			err = USBD_NOMEM;
			goto end_local;
		}
		ptStatus = usb_USBDAllocTinyBuffer(sizeof(*ptStatus));
		if(!ptStatus) {
			err = USBD_NOMEM;
			goto end_local;
		}

		/* get endpoint status */
		ptReq->bmRequestType = UT_READ_ENDPOINT;
		ptReq->bRequest = UR_GET_STATUS;
		USB_SETW(ptReq->wValue, 0);
		USB_SETW(ptReq->wIndex, 0);
		USB_SETW(ptReq->wLength, sizeof(*ptStatus));
		initDefaultXfer(ptXfer, ptDevice, USBD_DEFAULT_TIMEOUT,
						ptReq, ptStatus, sizeof(*ptStatus), 0);
		terr = usb_USBDStartTransfer(ptXfer);
		if(terr) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("usb_USBDDeviceRequest: the transfer of device request failed again.\n");
#endif
			goto end_local;
		}
		if(!(USB_GETW(ptStatus->wStatus) & UES_HALT)) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("usb_USBDDeviceRequest: endpoint 0 is not halting but don't move. bailout.\n");
#endif
			goto end_local;
		}
		/* clear endpoint halt */
		ptReq->bmRequestType = UT_WRITE_ENDPOINT;
		ptReq->bRequest = UR_CLEAR_FEATURE;
		USB_SETW(ptReq->wValue, UF_ENDPOINT_HALT);
		USB_SETW(ptReq->wIndex, 0);
		USB_SETW(ptReq->wLength, 0);
		initDefaultXfer(ptXfer, ptDevice, USBD_DEFAULT_TIMEOUT,
						ptReq, ptStatus, 0, 0);
		terr = usb_USBDStartTransfer(ptXfer);
		if(terr) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("usb_USBDDeviceRequest: failed to clear endpoint halt.\n");
#endif
			goto end_local;
		}
		/* TODO? retry device request? */
	  end_local:
		if(ptReq)
			usb_USBDDeallocDeviceRequest(ptReq);
		if(ptStatus)
			usb_USBDDeallocTinyBuffer(ptStatus);
		goto bad;
	}
	goto end;
	
  bad:
	DEBUG_ERROR_LOG(("usb_USBDDeviceRequest: failed to send device-request.\n"));
#if defined(USBD_UTIL)
	USBD_COUNT_ERROR(device_request);
#endif
  end:
	USB_TRACE_LEAVE1(1, usb_USBDDeviceRequest, err);
	return err;
}

/*!
 * \brief デバイスのポートをリセットする
 * \param ptDevice		リセットするポートを持つデバイス(ハブデバイス)
 * \param ucPortNo		リセットするポート番号
 * \param ptOutStatus	リセット後のポートのステータス
 * \return			usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、ptDevice で指定したデバイスの ucPortNo 番目の
 * ポートをリセットする。リセット後のステータスを ptOutStatus に返却する。
 */
usbd_status
usb_USBDResetPort(usbd_device_t* ptDevice, uint8_t ucPortNo, usb_port_status_t* ptOutStatus)
{
	usbd_status err;
	int16_t n;
	usb_device_request_t* ptReq = NULL;

	USB_TRACE_ENTER1(1, usb_USBDResetPort, (uint32_t)ptDevice);
	if(!ptOutStatus) {
		err = USBD_INVAL;
		goto end;
	}
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto end;
	}
	ptReq->bmRequestType = UT_WRITE_CLASS_OTHER;
	ptReq->bRequest = UR_SET_FEATURE;
	USB_SETW(ptReq->wValue, UHF_PORT_RESET);
	USB_SETW(ptReq->wLength, 0);
	USB_SETW(ptReq->wIndex, ucPortNo);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDResetPort: failed to UHF_PORT_RESET\n"));
		goto end;
	}
	
	n = 10; /* retry 10 times */
	do {
		/* wait for device to recover from reset */
		usb_USBDWaitMs(USB_PORT_RESET_DELAY);
		err = usb_USBDGetPortStatus(ptDevice, ucPortNo, ptOutStatus);
		if(err) {
			DEBUG_ERROR_LOG(("usb_USBDResetPort: failed to get port status\n"));
			goto end;
		}
		/* if the device disappeared, just give up */
		if(!(USB_GETW(ptOutStatus->wPortStatus) & UPS_CURRENT_CONNECT_STATUS)) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("usb_USBDResetPort: device disappeared (portno=%u).\n", ucPortNo);
#endif
			err = USBD_NORMAL_COMPLETION;
			goto end;
		}
	} while((USB_GETW(ptOutStatus->wPortChange) & UPS_C_PORT_RESET) == 0 && --n > 0);
	if(n == 0) {
		err = USBD_TIMEOUT;
		DEBUG_ERROR_LOG(("usb_USBDResetPort: port reset timeout. (try 10 times)\n"));
		goto end;
	}
	err = usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_C_PORT_RESET);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDResetPort: reset failed after retrying\n"));
	}

	/* wait for the device to recover from reset */
	usb_USBDWaitMs(USB_PORT_RESET_RECOVERY);

  end:
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_LEAVE1(1, usb_USBDResetPort, err);
	return err;
}

#if 0 /* XXX この方法ではうまくいかない */
/*!
 * \brief デバイスの初期化
 * \param ptDevice	初期化を行なうデバイス
 *
 * デバイスのポートリセットを行ない、かつ USBD 上での再初期化を行なう。
 *
 * \note 実験段階の実装
 */
usbd_status
usb_USBDResetDevice(usbd_device_t* ptDevice)
{
	usbd_status err;
	usbd_pipe_t* ptPipe;
	uint8_t	ucAddr, ucNumIface, ucPortNo, i;
	usb_port_status_t* ptPortStat = NULL;

	USB_TRACE_ENTER1(1, usb_USBDResetDevice, ptDevice);
	/* find the port number on a parent hub */
	ucPortNo = 0; /* 0 = port not found */
	if(ptDevice->ptMyHub) {
		for(i = 1; i <= ptDevice->ptMyHub->ptHub->tHubDesc.bNbrPorts; i++) {
			if(ptDevice->ptMyHub->ptHub->ptPorts[i-1].ptDevice == ptDevice) {
				ucPortNo = i;
				break;
			}
		}
	}

	/* abort all pipes */
	if(ptDevice->ptIfaces) {
		ucNumIface = ptDevice->ptCdesc->bNumInterfaces;
		for(i = 0; i < ucNumIface; i++) {
			DLIST_FOREACH(ptPipe, usbd_pipe_t, &ptDevice->ptIfaces[i].pipes.first) {
				usb_USBDAbortPipe(ptPipe);
				usb_USBDClearEndpointToggle(ptPipe);
			}
		}
	}
	/* abort default endpoint */
	if(ptDevice->ptDefaultPipe) {
		usb_USBDAbortPipe(ptDevice->ptDefaultPipe);
	}

	/* reset port */
	if(!ucPortNo) {
		/* no parent or did not be assigned any port(fatal) */
		err = USBD_INVAL;
		goto end;
	}
	ptPortStat = usb_USBDAllocTinyBuffer(sizeof(*ptPortStat));
	if(!ptPortStat) {
		err = USBD_NOMEM;
		goto end;
	}
	err = usb_USBDResetPort(ptDevice->ptMyHub, ucPortNo, ptPortStat);
	if(err) {
		goto end;
	}

	/* set the same address again */
	ucAddr = ptDevice->ucAddress;
	for(i = 0; i < 15; i++) {
		err = setAddress(ptDevice, ucAddr);
		if(!err) {
			usb_USBDWaitMs(USB_SET_ADDRESS_SETTLE);
			goto address_set;
		}
		usb_USBDWaitMs(200); /* wait before retry */
		if((i & 3) == 3) {
			usb_USBDResetPort(ptDevice->ptMyHub, ucPortNo, ptPortStat);
		}
	}
	err = USBD_IOERROR; /* failed to set address */
	goto end;

  address_set:
	/* XXX toggle clear は必要？ */
	/* set the same configuration */
	err = setConfig(ptDevice, ptDevice->ucConfig); /* issue device request only */
	if(err) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("USB_iResetDevice: failed to set config (index=%u)\n", ptDevice->ucConfig);
#endif
	}
	
  end:
	if(ptPortStat) {
		usb_USBDDeallocTinyBuffer(ptPortStat);
	}
	
	USB_TRACE_LEAVE1(1, usb_USBDResetDevice, err);
	return err;
}
#endif

/*!
 * \brief デスクリプタの取得(DeviceRequest)
 * \param device		デバイス
 * \param type			デスクリプタのタイプ(wValue の上位バイト)
 * \param index			wValue の下位バイト
 * \param len			デスクリプタ長
 * \param outDesc		取得したデスクリプタの格納先
 * \return				usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、デスクリプタの取得を行なう。
 * device で指定したデバイスの type と index で指定した
 * デスクリプタを取得する。取得先を outDesc, 取得長を len
 * に指定する。
 */
static usbd_status
getDesc(usbd_device_t* ptDevice, int16_t sType, int16_t sIndex, uint16_t usLen, void* pvOutDesc)
{
	usb_device_request_t* ptRequest;
	usbd_status err;

	USB_TRACE_ENTER1(1, getDesc, ptDevice);
	ptRequest = usb_USBDAllocDeviceRequest();
	if(!ptRequest) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptRequest->bmRequestType = UT_READ_DEVICE;
	ptRequest->bRequest = UR_GET_DESCRIPTOR;
	USB_SETW2(ptRequest->wValue, sType, sIndex & 0xff);
	USB_SETW(ptRequest->wIndex, 0);
	USB_SETW(ptRequest->wLength, usLen);
	err = usb_USBDDeviceRequest(ptDevice, ptRequest, pvOutDesc, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptRequest)
		usb_USBDDeallocDeviceRequest(ptRequest);
	USB_TRACE_LEAVE1(1, getDesc, err);
	return err;
}

/*!
 * \brief デバイスデスクリプタの取得(DeviceRequest)
 * \param ptDevice		デスクリプタを取得するデバイス
 * \return				usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、デバイスデスクリプタを取得する。
 * 取得したデバイスデスクリプタはデバイス管理構造体 ptDevice の
 * tDdesc メンバに格納される。
 * ３回までのリトライを行なう。
 */
static usbd_status
getFullDeviceDesc(usbd_device_t* ptDevice)
{
	int16_t i;
	usbd_status err = USBD_NORMAL_COMPLETION;

	USB_TRACE_ENTER1(1, getFullDeviceDesc, ptDevice);
	for(i = 0; i < 3; i++) {
		/* try to get 3 times */
		err = getDesc(ptDevice, UDESC_DEVICE, 0, USB_DEVICE_DESC_SIZE, &ptDevice->tDdesc);
		if(!err)
			break;
		usb_USBDWaitMs(200);
	}
	USB_TRACE_LEAVE1(1, getFullDeviceDesc, err);
	return err;
}

/*!
 * \brief コンフィグデスクリプタの取得(DeviceRequest)
 * \param ptDevice		デバイス
 * \param sConfIdx		コンフィグレーションインデックス番号
 * \param ptOutCdesc	コンフィグデスクリプタの出力先
 * \return				usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、ptDevice の持つ ucConfIdx
 * の示すコンフィグレーション番号のコンフィグレーションデスクリプタを
 * 取得する。
 */
static usbd_status
getConfigDesc(usbd_device_t* ptDevice, int16_t sConfIdx, usb_config_descriptor_t* ptOutCdesc)
{
	usbd_status err;

	USB_TRACE_ENTER1(1, getConfigDesc, ptDevice);
	err = getDesc(ptDevice, UDESC_CONFIG, sConfIdx, USB_CONFIG_DESC_SIZE, ptOutCdesc);
	if(err) {
		DEBUG_ERROR_LOG(("getConfigDesc: failed to get descriptor\n"));
		goto bad;
	}
	if(ptOutCdesc->bDescriptorType != UDESC_CONFIG) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("getConfigDesc: descriptor is not config-desc.\n"));
		goto bad;
	}
	err = USBD_NORMAL_COMPLETION;
  bad:
	USB_TRACE_LEAVE1(1, getConfigDesc, err);
	return err;
}

#if 0 /* not used */
/*!
 * \brief インターフェイスデスクリプタを取得する(DeviceRequest)
 * \param ptIface		インターフェイス
 * \param ptOutIdesc	インターフェイスデスクリプタの出力先
 * \return				usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、ptIface で指定するインターフェイスの
 * インターフェイスデスクリプタを ptOutIdesc に取得する。
 */
static usbd_status
getInterface(usbd_interface_t* ptIface, uint8_t* ptOutIdesc)
{
	usb_device_request_t* ptRequest;
	usbd_status err;

	USB_TRACE_ENTER1(1, getInterface, ptIface);
	ptRequest = usb_USBDAllocDeviceRequest();
	if(!ptRequest) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptRequest->bmRequestType = UT_READ_INTERFACE;
	ptRequest->bRequest = UR_GET_INTERFACE;
	USB_SETW(ptRequest->wValue, 0);
	USB_SETW(ptRequest->wIndex, ptIface->ptIdesc->bInterfaceNumber);
	USB_SETW(ptRequest->wLength, 1);
	err = usb_USBDDeviceRequest(ptIface->ptDevice, ptRequest, ptOutIdesc,
								0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptRequest)
		usb_USBDDeallocDeviceRequest(ptRequest);
	USB_TRACE_LEAVE1(1, getInterface, err);
	return err;
}
#endif /* not used */

/*!
 * \brief デバイスにアドレスを設定する(DeviceRequest)
 * \param ptDevice		アドレス設定するデバイス
 * \param ucAddr		設定するアドレス
 * \return				usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、デバイスに
 * デバイスアドレスを設定する。
 */
static usbd_status
setAddress(usbd_device_t* ptDevice, uint8_t ucAddr)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, setAddress, ptDevice);
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptReq->bmRequestType = UT_WRITE_DEVICE;
	ptReq->bRequest = UR_SET_ADDRESS;
	USB_SETW(ptReq->wValue, ucAddr);
	USB_SETW(ptReq->wIndex, 0);
	USB_SETW(ptReq->wLength, 0);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_ENTER1(1, setAddress, err);
	return err;
}

/*!
 * \brief ハブフィーチャーのセット(DeviceRequest)
 * \param ptDevice		デバイス(ハブデバイス)
 * \param usSel			フィーチャー(wValue)
 * \return				usbd_status 型によるエラーの通知
 *
 * HUBデバイスに対して SET_FEATURE を発行し、ハブフィーチャーをセットする。
 */
usbd_status
usb_USBDSetHubFeature(usbd_device_t* ptDevice, uint16_t usSel)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, usb_USBDSetHubFeature, ptDevice);

	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto end;
	}
	ptReq->bmRequestType = UT_WRITE_CLASS_DEVICE;
	ptReq->bRequest = UR_SET_FEATURE;
	USB_SETW(ptReq->wValue, usSel);
	USB_SETW(ptReq->wIndex, 0);
	USB_SETW(ptReq->wLength, 0);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
	
  end:
	USB_TRACE_LEAVE1(1, usb_USBDSetHubFeature, err);
	return err;
}

/*!
 * \brief ハブフィーチャーのクリア(DeviceRequest)
 * \param ptDevice		デバイス(ハブデバイス)
 * \param usSel			フィーチャー(wValue)
 * \return				usbd_status 型によるエラーの通知
 *
 * HUBデバイスに対して CLEAR_FEATURE を発行し、ハブフィーチャーをクリアする。
 */
usbd_status
usb_USBDClearHubFeature(usbd_device_t* ptDevice, uint16_t usSel)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, usb_USBDClearHubFeature, ptDevice);

	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto end;
	}
	ptReq->bmRequestType = UT_WRITE_CLASS_DEVICE;
	ptReq->bRequest = UR_CLEAR_FEATURE;
	USB_SETW(ptReq->wValue, usSel);
	USB_SETW(ptReq->wIndex, 0);
	USB_SETW(ptReq->wLength, 0);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
	
  end:
	USB_TRACE_LEAVE1(1, usb_USBDClearHubFeature, err);
	return err;
}

/*!
 * \brief ポートフィーチャを設定する(DeviceRequest)
 * \param ptDevice		デバイス
 * \param ucPortNo		ポート番号
 * \param usSel			セレクタ(wValue)
 * \return				usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、ptDevice の ucPortNo 番目のポートに
 * usSel で指定したフィーチャを設定する。
 */
usbd_status
usb_USBDSetPortFeature(usbd_device_t* ptDevice, uint8_t ucPortNo, uint16_t usSel)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, usb_USBDSetPortFeature, ptDevice);
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptReq->bmRequestType = UT_WRITE_CLASS_OTHER;
	ptReq->bRequest = UR_SET_FEATURE;
	USB_SETW(ptReq->wValue, usSel);
	USB_SETW(ptReq->wIndex, ucPortNo);
	USB_SETW(ptReq->wLength, 0);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_LEAVE1(1, usb_USBDSetPortFeature, err);
	return err;
}

/*!
 * \brief ポートフィーチャのクリア(DeviceRequest)
 * \param ptDevice		デバイス(ハブデバイス)
 * \param ucPortNo		ポート番号
 * \param usSel			フィーチャー(wValue)
 * \return				usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、ポートフィーチャをクリアする。
 */
usbd_status
usb_USBDClearPortFeature(usbd_device_t* ptDevice, uint8_t ucPortNo, uint16_t usSel)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, usb_USBDClearPortFeature, ptDevice);
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptReq->bmRequestType = UT_WRITE_CLASS_OTHER;
	ptReq->bRequest = UR_CLEAR_FEATURE;
	USB_SETW(ptReq->wValue, usSel);
	USB_SETW(ptReq->wIndex, ucPortNo);
	USB_SETW(ptReq->wLength, 0);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptReq) 
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_LEAVE1(1, usb_USBDClearPortFeature, err);
	return err;
}

/*!
 * \brief コンフィグレーションを指定番号に設定する(DeviceRequest)
 * \param ptDevice		デバイス
 * \param ucConfNo		コンフィグレーション番号
 * \return				usbd_status 型によるエラーの通知
 * \sa usb_USBDSetConfigIndex から利用される。
 *
 * デバイスリクエストを発行して、コンフィグレーションを
 * ucConfNo に設定する。
 * 単純なデバイスリクエストのみ。
 */
static usbd_status
setConfig(usbd_device_t* ptDevice, uint8_t ucConfNo)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, setConfig, ptDevice);
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptReq->bmRequestType = UT_WRITE_DEVICE;
	ptReq->bRequest = UR_SET_CONFIG;
	USB_SETW(ptReq->wValue, ucConfNo);
	USB_SETW(ptReq->wIndex, 0);
	USB_SETW(ptReq->wLength, 0);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_LEAVE1(1, setConfig, err);
	return err;
}

/*!
 * \brief コンフィグレーションの切替え(DeviceRequest)
 * \param ptDevice		デバイス
 * \param sIndex		切替えるコンフィグレーションインデックス
 * \return				usbd_status 型によるエラーの通知
 * \sa setConfig を内部で利用する。
 *
 * デバイスリクエストを発行して、sIndex で指定したインデックスのコンフィグレーション
 * デスクリプタのもつコンフィグレーション番号のコンフィグレーションに切替える。
 * setConfig の呼び出しとは異なり、USBD の内部状態に応じて状態を変化させながら動作。
 * sIndex に USB_UNCONFIG_INDEX を指定すると、Unconfigure を行なう。
 * Configuration を行なう時、全てのパイプがクローズしていること。クローズしていない場合には
 * エラーコード USBD_IN_USE が返却される。
 */
usbd_status
usb_USBDSetConfigIndex(usbd_device_t* ptDevice, int16_t sIndex)
{
	usbd_status err;
	uint16_t usLen;
	uint8_t ucNumIface;
	int16_t i;
	int8_t cSelfPowered;
	uint16_t usPower;
	usb_config_descriptor_t* ptCdesc = NULL;
	usb_status_t* ptStat = NULL;

	USB_TRACE_ENTER1(1, usb_USBDSetConfigIndex, ptDevice);
	/* unconfigure the device if not uncofigured */
	if(ptDevice->ucConfig != USB_UNCONFIG_NO && ptDevice->ptCdesc) {
		ucNumIface = ptDevice->ptCdesc->bNumInterfaces;

		/* check that all interfaces are idle */
		for(i = 0; i < ucNumIface; i++) {
			/* ASSERT(ptDevice->ptIfaces); */
			if(DLIST_IS_EMPTY(&ptDevice->ptIfaces[i].pipes))
				continue;
			err = USBD_IN_USE;
			DEBUG_ERROR_LOG(("usb_USBDSetConfigIndex: iface no.%u is in use!\n", i));
			goto good;
		}
		/* free all configuration data structure */
		for(i = 0; i < ucNumIface; i++)
			freeIfaceData(ptDevice, (uint8_t)i);
		if(ptDevice->ptIfaces) {
			usb_USBDDeallocIfaces(ptDevice, ptDevice->ptIfaces);
			ptDevice->ptIfaces = NULL;
		}
		if(ptDevice->ptCdesc) {
			usb_USBDDeallocCDesc(ptDevice, ptDevice->ptCdesc);
			ptDevice->ptCdesc = NULL;
			ptDevice->ucConfig = USB_UNCONFIG_NO;
		}
	}

	if(sIndex == USB_UNCONFIG_INDEX) {
		/* we are unconfiguring the device, so leave unallocated */
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDSetConfigIndex: unconfiguring...\n");
#endif
		err = setConfig(ptDevice, USB_UNCONFIG_NO);
		if(err) {
			DEBUG_ERROR_LOG(("usb_USBDSetConfigIndex: failed to set config (USB_UNCONFIG_NO)\n"));
			goto bad;
		}
		err = USBD_NORMAL_COMPLETION;
		goto good;
	}

	/* get the short descriptor */
	ptCdesc = usb_USBDAllocCDesc(ptDevice, sizeof(usb_config_descriptor_t));
	if(!ptCdesc) {
		err = USBD_NOMEM;
		goto bad;
	}
	err = getConfigDesc(ptDevice, sIndex, ptCdesc);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDSetConfigIndex: failed to get short cdesc for idx %u\n",
						 sIndex));
		goto bad;
	}
	/* get the full descriptor */
	usLen = USB_GETW(ptCdesc->wTotalLength);
	usb_USBDDeallocCDesc(ptDevice, ptCdesc);
	ptCdesc = usb_USBDAllocCDesc(ptDevice, usLen);
	if(!ptCdesc) {
		err = USBD_NOMEM;
		goto bad;
	}
	/* try a few times for slow devices */
	for(i = 0; i < 3; i++) {
		err = getDesc(ptDevice, UDESC_CONFIG, sIndex, usLen, ptCdesc);
		if(!err)
			break;
		usb_USBDWaitMs(200);
	}
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDSetConfigIndex: failed to get full cdesc\n"));
		goto bad;
	}
	if(ptCdesc->bDescriptorType != UDESC_CONFIG) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBDSetConfigIndex: invalid config descriptor\n"));
		goto bad;
	}

	/* figure out if the device is self or bus powered */
	cSelfPowered = 0;
	if(ptCdesc->bmAttributes & UC_SELF_POWERED) {
		/* maybe self powered */
		if(ptCdesc->bmAttributes & UC_BUS_POWERED) {
			/* must ask device */
			ptStat = usb_USBDAllocTinyBuffer(sizeof(*ptStat));
			if(!ptStat) {
				err = USBD_NOMEM;
				goto bad;
			}
			err = getDeviceStatus(ptDevice, ptStat);
			if(!err && USB_GETW(ptStat->wStatus) & UDS_SELF_POWERED) {
				cSelfPowered = 1;
			}
			usb_USBDDeallocTinyBuffer(ptStat);
			ptStat = NULL;
		}
		else { /* if(bmAttributes & UC_BUS_POWERED) */
			cSelfPowered = 1;
		}
	}
	
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("usb_USBDSetConfigIndex: device(addr=%u) cfgno=%u, attr=%#02x, %s, power=%d\n",
			 ptDevice->ucAddress,
			 ptCdesc->bConfigurationValue,
			 ptCdesc->bmAttributes,
			 (cSelfPowered ? "self-powered" : "bus-powered"),
			 ptCdesc->bMaxPower * 2);
#endif
	{
		usbd_status terr;

		terr = getString(ptDevice, ptCdesc->iConfiguration, ptDevice->pcConfName);
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDSetConfigIndex: device(addr=%u) numIfaces=%u, confname=%s\n",
				 ptDevice->ucAddress,
				 ptCdesc->bNumInterfaces,
				 ptDevice->pcConfName);
#endif
	}
	
	/* check if we have enough power */
	if(ptDevice->ptPowerSrc == NULL) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDSetConfigIndex: No power source?\n");
#endif
		err = USBD_IOERROR;
		goto bad;
	}
	usPower = ptCdesc->bMaxPower * 2;
	if(usPower > ptDevice->ptPowerSrc->usPower) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("@ device(addr=%u, config=%u) exceeds power budget, %d mA > %d mA\n",
				 ptDevice->ucAddress,
				 ptCdesc->bConfigurationValue,
				 usPower,
				 ptDevice->ptPowerSrc->usPower);
#endif
		err = USBD_NO_POWER;
		goto bad;
	}
	ptDevice->usPower = usPower;
	ptDevice->cSelfPowered = cSelfPowered;
	
	/* set the actual configuration value */
	err = setConfig(ptDevice, ptCdesc->bConfigurationValue);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDSetConfigIndex: failed to set config value\n"));
		goto bad;
	}

	/* allcate and fill interface data */
	ucNumIface = ptCdesc->bNumInterfaces;
	ptDevice->ptIfaces = usb_USBDAllocIfaces(ptDevice, ucNumIface);
	if(!ptDevice->ptIfaces) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptDevice->ptCdesc = ptCdesc;
	ptDevice->ucConfig = ptCdesc->bConfigurationValue;
	for(i = 0; i < ucNumIface; i++) {
		err = fillIfaceData(ptDevice, (uint8_t)i, 0);
		if(err) {
			DEBUG_ERROR_LOG(("usb_USBDSetConfigIndex: failed to fill ifaces\n"));
			while(--i >= 0)
				freeIfaceData(ptDevice, (uint8_t)i);
			ptDevice->ptCdesc = NULL; /* NOTE 解放はローカル変数 ptCdesc により行なう */
			ptDevice->ucConfig = USB_UNCONFIG_NO; /* XXX or previous value? */
			goto bad; /* XXX or try next ifaces? */
		}
	}
	err = USBD_NORMAL_COMPLETION;
	goto good;
	
  bad:
	if(ptCdesc) {
		usb_USBDDeallocCDesc(ptDevice, ptCdesc);
		ptDevice->ptCdesc = NULL;
	}
	if(ptDevice->ptIfaces) {
		usb_USBDDeallocIfaces(ptDevice, ptDevice->ptIfaces);
		ptDevice->ptIfaces = NULL;
	}
	if(ptStat) {
		usb_USBDDeallocTinyBuffer(ptStat);
		ptStat = NULL;
	}
  good:
	USB_TRACE_LEAVE1(1, usb_USBDSetConfigIndex, err);
	return err;
}

/*!
 * \brief ハブのステータスを取得する(DeviceRequest)
 * \param ptDevice		デバイス(ハブデバイス)
 * \param ptOutStat		ステータスの取得先
 * \return			usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、ptDevice で指定された
 * ハブのステータスを ptOutStat に取得する。
 */
usbd_status
usb_USBDGetHubStatus(usbd_device_t* ptDevice, usb_hub_status_t* ptOutStat)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, usb_USBDGetHubStatus, ptDevice);
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptReq->bmRequestType = UT_READ_CLASS_DEVICE;
	ptReq->bRequest = UR_GET_STATUS;
	USB_SETW(ptReq->wValue, 0);
	USB_SETW(ptReq->wIndex, 0);
	USB_SETW(ptReq->wLength, sizeof(*ptOutStat));
	err = usb_USBDDeviceRequest(ptDevice, ptReq, ptOutStat, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_LEAVE1(1, usb_USBDGetHubStatus, err);
	return err;
}

/*!
 * \brief ポートステータスを取得する(DeviceRequest)
 * \param ptDevice		デバイス(ハブデバイス)
 * \param ucPortNo		ポート番号
 * \param ptOutStat		ステータスの取得先
 * \return			usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、ptDevice, ucPortNo で指定された
 * ポートのステータスを ptOutStat に取得する。
 */
usbd_status
usb_USBDGetPortStatus(usbd_device_t* ptDevice, uint8_t ucPortNo, usb_port_status_t* ptOutStat)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, usb_USBDGetPortStatus, ptDevice);
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptReq->bmRequestType = UT_READ_CLASS_OTHER;
	ptReq->bRequest = UR_GET_STATUS;
	USB_SETW(ptReq->wValue, 0);
	USB_SETW(ptReq->wIndex, ucPortNo);
	USB_SETW(ptReq->wLength, sizeof(*ptOutStat));
	err = usb_USBDDeviceRequest(ptDevice, ptReq, ptOutStat, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_LEAVE1(1, usb_USBDGetPortStatus, err);
	return err;
}

/*!
 * \brief デバイスのステータスを取得する(DeviceRequest)
 * \param ptDevice	デバイス
 * \param ptOutStat	ステータスの取得先
 * \return			usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、デバイスのステータスを取得する。
 */
static usbd_status
getDeviceStatus(usbd_device_t* ptDevice, usb_status_t* ptOutStat)
{
	usb_device_request_t* ptReq;
	usbd_status err;

	USB_TRACE_ENTER1(1, getDeviceStatus, ptDevice);
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptReq->bmRequestType = UT_READ_DEVICE;
	ptReq->bRequest = UR_GET_STATUS;
	USB_SETW(ptReq->wValue, 0);
	USB_SETW(ptReq->wIndex, 0);
	USB_SETW(ptReq->wLength, sizeof(*ptOutStat));
	err = usb_USBDDeviceRequest(ptDevice, ptReq, ptOutStat, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_LEAVE1(1, getDeviceStatus, err);
	return err;
}

/*!
 * \brief エンドポイントストールをクリアする
 * \param ptPipe		パイプ
 * \return				usbd_status 型によるエラーの通知
 *
 * デバイスリクエストを発行して、ptPipe で指定するエンドポイントの
 * ストールをクリアする。
 */
usbd_status
usb_USBDClearEndpointStall(usbd_pipe_t* ptPipe)
{
	usbd_status err;
	usb_device_request_t* ptRequest;
	usbd_device_t* ptDevice = ptPipe->ptDevice;

	USB_TRACE_ENTER1(1, usb_USBDClearEndpointStall, ptPipe);
	/*
	 * Clearing en endpoint stall resets the endpoint toggle, so
	 * do the same to the HC toggle.
	 */
	if(ptPipe->tMethods.fpClearToggle)
		ptPipe->tMethods.fpClearToggle(ptPipe);

	ptRequest = usb_USBDAllocDeviceRequest();
	if(!ptRequest) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptRequest->bmRequestType = UT_WRITE_ENDPOINT;
	ptRequest->bRequest = UR_CLEAR_FEATURE;
	USB_SETW(ptRequest->wValue, UF_ENDPOINT_HALT);
	USB_SETW(ptRequest->wIndex, ptPipe->ptEndpoint->ptEdesc->bEndpointAddress);
	USB_SETW(ptRequest->wLength, 0);
	err = usb_USBDDeviceRequest(ptDevice, ptRequest, 0, 0, USBD_DEFAULT_TIMEOUT, 0);
  bad:
	if(ptRequest)
		usb_USBDDeallocDeviceRequest(ptRequest);
	USB_TRACE_LEAVE1(1, usb_USBDClearEndpointStall, err);
	return err;
}

/*!
 * \brief エンドポイントのトグルをクリアする
 * \param ptPipe	トグルクリアするパイプ
 *
 * ptPipe で指定したパイプのエンドポイントのトグルをクリアする。
 */
void
usb_USBDClearEndpointToggle(usbd_pipe_t* ptPipe)
{
	USB_TRACE_ENTER1(2, usb_USBDClearEndpointToggle, ptPipe);
	if(ptPipe->tMethods.fpClearToggle)
		ptPipe->tMethods.fpClearToggle(ptPipe);
	USB_TRACE_LEAVE(2, usb_USBDClearEndpointToggle);
}


/*!
 * \brief 文字列の取得
 * \param ptDevice		デバイス
 * \param ucSindex		ストリングインデックス
 * \param pcBuf			文字列の出力先
 * return usbd_status 型による返却
 *
 * si で指定した文字列インデックスをもつ文字列を取得する。
 * 取得された文字列は C 文字列である。
 */
static usbd_status
getString(usbd_device_t* ptDevice, uint8_t ucSindex, int8_t* pcBuf)
{
	uint16_t usSize = 0;
	usbd_status err = USBD_NORMAL_COMPLETION;
	usb_string_descriptor_t* ptStr = NULL;

	pcBuf[0] = '\0';
	if(ucSindex == 0) {
		err = USBD_INVAL;
		goto end;
	}
	/* setup default language */
	ptStr = usb_USBDAllocSDesc();
	if(!ptStr) {
		err = USBD_NOMEM;
		goto end;
	}
	err = getStringDesc(ptDevice, ptStr, 0, 0, &usSize);
	if(err || usSize < 4) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("getString: getting langid failed, using 0\n");
#endif
		USB_SETW(ptStr->bString[0], 0);
	}
	err = getStringDesc(ptDevice, ptStr, ucSindex, USB_GETW(ptStr->bString[0]), &usSize);
	if(err) {
		goto end;
	}

	/* convert unicode */
	{
		int8_t* s;
		int16_t i, n;
		uint16_t c;

		s = pcBuf;
		n = usSize / 2 - 1;
		for(i = 0; i < n; i++) {
			c = USB_GETW(ptStr->bString[i]);
			if((c & 0xff00) == 0)
				*s++ = (int8_t)c;
			else if((c & 0x00ff) == 0)
				*s++ = (int8_t)(c >> 8);
			else
				*s++ = '?';
		}
		/* strip trailing white spaces */
		while(s > pcBuf && *--s == ' ')
			*s = '\0';
		err = USBD_NORMAL_COMPLETION;
	}
  end:
	if(ptStr)
		usb_USBDDeallocSDesc(ptStr);
	return err;
}

/*!
 * \brief ストリングデスクリプタの取得
 * \param ptDevice		デバイス管理構造
 * \param ptOutSdesc	ストリングディスクリプタ書き出し先
 * \param ucSindex		ストリングインデックス
 * \param usLangId		言語ID
 * \param pusSize		読み込みサイズの出力先
 * \return usbd_status 型による返答
 *
 * sindex で指定したインデックス番号のストリングデスクリプタを取得する。
 */
static usbd_status
getStringDesc(usbd_device_t* ptDevice,
			  usb_string_descriptor_t* ptOutSdesc,
			  uint8_t ucSindex,
			  uint16_t usLangId,
			  uint16_t* pusSize)
{
	usbd_status err;
	usb_device_request_t* ptReq;
	uint16_t* pusLen = NULL;

	USB_TRACE_ENTER1(1, getStringDesc, ucSindex);
	
	/* get first 2 bytes of the descriptor */
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto end;
	}
	pusLen = (uint16_t*)usb_USBDAllocTinyBuffer(sizeof(*pusLen));
	if(!pusLen) {
		err = USBD_NOMEM;
		goto end;
	}
	ptReq->bmRequestType = UT_READ_DEVICE;
	ptReq->bRequest = UR_GET_DESCRIPTOR;
	USB_SETW2(ptReq->wValue, UDESC_STRING, ucSindex);
	USB_SETW(ptReq->wIndex, usLangId);
	USB_SETW(ptReq->wLength, 2);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, ptOutSdesc, pusLen, USBD_DEFAULT_TIMEOUT, NULL);
	if(err)
		goto end;
	if(*pusLen < 2) {
		err = USBD_SHORT_XFER;
		goto end;
	}

	/* get full size descriptor */
	USB_SETW(ptReq->wLength, ptOutSdesc->bLength);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, ptOutSdesc, pusLen, USBD_DEFAULT_TIMEOUT, NULL);
	if(err)
		goto end;

	if(*pusLen != ptOutSdesc->bLength) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("getString: expected %u byte, got %u byte\n",
				 ptOutSdesc->bLength, *pusLen);
#endif
	}
	*pusSize = *pusLen;
	err = USBD_NORMAL_COMPLETION;
	
  end:
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	if(pusLen)
		usb_USBDDeallocTinyBuffer(pusLen);
	USB_TRACE_LEAVE1(1, getStringDesc, err);
	return err;
}




/* ========================================================= */
/*                  管理構造へのアクセサ                     */
/* ========================================================= */
/*!
 * \brief デバイスが持っている、指定したインデックスのインターフェイスを取得する
 * \param device	インターフェイスを取得するデバイス
 * \param ifaceno	インターフェイスインデックス
 * \param outIface	インターフェイスの取得先
 * \return			usbd_status 型によるエラーの通知
 *
 * device の持つ、ifaceno 番目のインターフェイスを取得する。
 */
usbd_status
usb_USBDDeviceToInterface(usbd_device_t* ptDevice,
						  uint8_t ucIfaceNo,
						  usbd_interface_t** ptOutIface)
{
	usbd_status err;
	
	USB_TRACE_ENTER1(2, usb_USBDDeviceToInterface, ptDevice);
	if(!ptDevice->ptCdesc) {
		err = USBD_NOT_CONFIGURED;
		DEBUG_ERROR_LOG(("usb_USBDDeviceToInterface: device not configured\n"));
		goto bad;
	}
	if(ucIfaceNo >= ptDevice->ptCdesc->bNumInterfaces) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_USBDDeviceToInterface: invalid interface no %u\n", ucIfaceNo));
		goto bad;
	}
	if(!ptDevice->ptIfaces) {
		err = USBD_IOERROR;
		DEBUG_ERROR_LOG(("usb_USBDDeviceToInterface: no interface! maybe SetConfigIndex failed\n"));
		goto bad;
	}
	*ptOutIface = &ptDevice->ptIfaces[ucIfaceNo];
	err = USBD_NORMAL_COMPLETION;
	
  bad:
	USB_TRACE_LEAVE1(2, usb_USBDDeviceToInterface, err);
	return err;
}

/*!
 * \brief デバイスの持つインターフェイスの総数を取得する
 * \param ptDevice			デバイス
 * \param pucOutNumOfIfaces	インターフェイスの数
 * \return					usbd_status 型によるエラーの通知
 *
 * ptDevice の持つインターフェイス数を ptOutNumOfIfaces に出力する。
 */
usbd_status
usb_USBDGetInterfaceNumber(usbd_device_t* ptDevice, uint8_t* pucOutNumOfIfaces)
{
	usbd_status err;
	
	USB_TRACE_ENTER1(1, usb_USBDGetInterfaceNumber, ptDevice);
	if(!ptDevice->ptCdesc) {
		err = USBD_NOT_CONFIGURED;
		DEBUG_ERROR_LOG(("usb_USBDGetInterfaceNumber: device has no cdesc (not configured)\n"));
		goto end;
	}
	*pucOutNumOfIfaces = ptDevice->ptCdesc->bNumInterfaces;
	err = USBD_NORMAL_COMPLETION;
  end:
	USB_TRACE_LEAVE1(1, usb_USBDGetInterfaceNumber, err);
	return err;
}

/*!
 * \brief インターフェイスのn番目のエンドポイントのデスクリプタを取得する
 * \param ptIface	インターフェイス
 * \param ucIndex	エンドポイントの番号
 * \return			エンドポイントデスクリプタ。取得できなかった場合には NULL。
 *
 * ptIface で示すインターフェイスの持っている ucIndex 番のエンドポイントの
 * エンドポイントデスクリプタを戻り値として返却する。
 * ucIndex が、インターフェイスの持つエンドポイント数を越えている場合には、
 * NULL を返却する。
 */
usb_endpoint_descriptor_t*
usb_USBDInterfaceToEndpointDesc(usbd_interface_t* ptIface, uint8_t ucIndex)
{
	usb_endpoint_descriptor_t* ptEdesc;

	USB_TRACE_ENTER1(2, usb_USBDInterfaceToEndpointDesc, ptIface);
	if(!ptIface) {
		ptEdesc = NULL;
		goto end;
	}
	if(ucIndex >= ptIface->ptIdesc->bNumEndpoints) {
		ptEdesc = NULL;
		DEBUG_ERROR_LOG(("usb_USBDInterfaceToEndpointDesc: invalid index. endpoint not found\n"));
		goto end;
	}
	if(!ptIface->ptEndpoints) {
		ptEdesc = NULL;
		goto end;
	}
	ptEdesc = ptIface->ptEndpoints[ucIndex].ptEdesc;
  end:
	USB_TRACE_LEAVE1(2, usb_USBDInterfaceToEndpointDesc, ptEdesc);
	return ptEdesc;
}

#if 0 /* NOT USED */
/*!
 * \brief インターフェイスが持つエンドポイントデスクリプタの取得
 * \param iface		インターフェイス
 * \param index		エンドポイントの順番
 * \return			エンドポイントデスクリプタ
 * \todo 多分使ってない
 *
 * インターフェイスが保持している、先頭から index 番目の
 * エンドポイントのエンドポイントデスクリプタを取得する。
 */
static usb_endpoint_descriptor_t*
getEndpointDescriptorForIndex(usbd_interface_t* iface, uint8_t index)
{
	usb_endpoint_descriptor_t* edesc = NULL;
	
	if(index < iface->idesc->bNumEndpoints)
		edesc = iface->ptEndpoints[index].edesc;
	return edesc;
}

/*!
 * \brief インターフェイスが持つエンドポイントデスクリプタの取得(アドレス指定)
 * \param iface		インターフェイス
 * \param addr		エンドポイントアドレス
 * \return			エンドポイントデスクリプタ
 * \todo 多分使ってない
 *
 * インターフェイスが保持している addr で指定したエンドポイントアドレスを持つ
 * エンドポイントのエンドポイントデスクリプタを取得する。
 */
static usb_endpoint_descriptor_t*
getEndpointDescriptorForAddr(usbd_interface_t* iface, uint8_t addr)
{
	usbd_endpoint_t* ep;
	usb_endpoint_descriptor_t* edesc = NULL;
	int i;

	for(i = 0; i < iface->idesc->bNumEndpoints; i++) {
		ep = &iface->ptEndpoints[i];
		if(ep->edesc->bEndpointAddress == addr) {
			edesc = ep->edesc;
			break;
		}
	}
	return edesc;
}
#endif /* NOT USED */


/* ========================================================= */
/*                   ユーティリティ関数                      */
/* ========================================================= */
/*!
 * \brief 指定時間の待ち
 * \param interval		待ち時間を msec 単位で指定する
 */
void
usb_USBDWaitMs(uint16_t interval)
{
  usb_TIMER_vWaiMsec(interval);
}



/* ========================================================= */
/*                        xfer 関連                          */
/* ========================================================= */
/*!
 * \brief xfer を確保する
 * \param device		xferを確保するデバイス
 * \return				確保したxfer
 *
 * 転送に必要な情報を格納する xfer を確保し、返す。
 */
usbd_xfer_t*
usb_USBDAllocXfer(usbd_device_t* ptDevice)
{
	usbd_xfer_t* ptXfer;

	USB_TRACE_ENTER1(5, usb_USBDAllocXfer, ptDevice);
	ptXfer = usb_OHCI_ptAllocXfer();
	if(!ptXfer) {
		goto bad;
	}
	ptXfer->ptDevice = ptDevice;
  bad:
	USB_TRACE_LEAVE1(5, usb_USBDAllocXfer, ptXfer);
	return ptXfer;
}

/*!
 * \brief xfer を解放する
 * \param ptXfer	解放するxfer
 * \return			usbd_status 型によるエラーの通知
 *
 * ptXfer を解放する。
 */
usbd_status
usb_USBDFreeXfer(usbd_xfer_t* ptXfer)
{
	USB_TRACE_ENTER1(5, usb_USBDFreeXfer, ptXfer);
	if(ptXfer) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDFreeXfer: ed_addr=%#08x, ed_type=%#08x, devaddr=%u\n",
				 ptXfer->ptPipe->ptEndpoint->ptEdesc->bEndpointAddress,
				 ptXfer->ptPipe->ptEndpoint->ptEdesc->bDescriptorType,
				 ptXfer->ptPipe->ptDevice->ucAddress);
#endif
		usb_OHCI_vFreeXfer(ptXfer);
	}
	USB_TRACE_LEAVE1(5, usb_USBDFreeXfer, USBD_NORMAL_COMPLETION);
	return USBD_NORMAL_COMPLETION;
}

/*!
 * \brief xferを初期化する
 * \param ptXfer		初期化するxfer
 * \param ptPipe		xfer が属するパイプ
 * \param pvBuffer		xfer で転送するバッファ
 * \param usLength		転送長
 * \param sTimeout		タイムアウト時間(ミリ秒)
 * \param fpCallback	転送完了時に呼び出されるコールバック関数
 *
 * 引数で指定したパラメータで xfer をフィルする。
 */
void
usb_USBDInitXfer(usbd_xfer_t* ptXfer,
			  usbd_pipe_t* ptPipe,
			  void* pvBuffer,
			  uint16_t usLength,
			  int16_t sTimeout,
			  usbd_callback fpCallback)
{
	USB_TRACE_ENTER1(5, usb_USBDInitXfer, ptXfer);
	ptXfer->ptPipe = ptPipe;
	ptXfer->pvBuffer = pvBuffer;
	ptXfer->usLength = usLength;
	ptXfer->usActLen = 0;
	ptXfer->usFlags = 0;
	ptXfer->sTimeout = sTimeout;
	ptXfer->cRepeat = 0;
	ptXfer->cDone = 0;
	ptXfer->tStatus = USBD_NOT_STARTED;
	ptXfer->tCallback = fpCallback;
	ptPipe->ptXfer = ptXfer;
	USB_TRACE_LEAVE(5, usb_USBDInitXfer);
}

/*!
 * \brief デフォルトパイプ用のxferを初期化する
 * \param ptXfer		初期化するxfer
 * \param ptDevice		xfer が属するデバイス
 * \param sTimeout		タイムアウト時間(ミリ秒)
 * \param ptRequest		デバイスリクエスト
 * \param pvBuffer		xfer で転送するバッファ
 * \param usLength		転送長
 * \param fpCallback	転送完了時に呼び出されるコールバック関数
 *
 * 引数で指定したパラメータで xfer をフィルする。
 */
static void
initDefaultXfer(usbd_xfer_t* ptXfer,
				usbd_device_t* ptDevice,
				int16_t sTimeout,
				usb_device_request_t* ptRequest,
				void* pvBuffer,
				uint16_t usLength,
				usbd_callback fpCallback)
{
	USB_TRACE_ENTER1(5, initDefaultXfer, ptXfer);
	ptXfer->ptPipe = ptDevice->ptDefaultPipe;
	ptXfer->pvBuffer = pvBuffer;
	ptXfer->usLength = usLength;
	ptXfer->usActLen = 0;
	ptXfer->usFlags = 0;
	ptXfer->sTimeout = sTimeout;
	ptXfer->tStatus = USBD_NOT_STARTED;
	ptXfer->tCallback = fpCallback;
	ptXfer->ptRequest = ptRequest;
	USB_TRACE_LEAVE(5, initDefaultXfer);
}


/*!
 * \brief xfer の転送開始
 * \param ptXfer	転送する xfer
 * \return			usbd_status 型によるエラーの通知
 *
 * xfer の示す内容で転送を開始する。
 */
usbd_status
usb_USBDStartTransfer(usbd_xfer_t* ptXfer)
{
	usbd_status err;
	usbd_pipe_t* ptPipe = ptXfer->ptPipe;

	USB_TRACE_ENTER1(3, usb_USBDStartTransfer, ptXfer);
	ptXfer->cDone = 0;
#if defined(USBD_UTIL)
	usb_USBDWatchXfer_RegisterTransferingXfer(ptXfer);
#endif
	err = ptPipe->tMethods.fpStart(ptXfer);
	if(err) {
		DEBUG_ERROR_LOG(("usb_USBDStartTransfer: failed to start. err=%u\n", err));
	}
	USB_TRACE_LEAVE1(3, usb_USBDStartTransfer, err);
	return err;
}

/*!
 * \brief xfer の転送終了
 * \param ptXfer	転送の終了した xfer
 *
 * xfer の示す転送が何らかの理由で終了したときに呼び出される
 * コールバック関数。
 */
void
usb_USBDTransferDone(usbd_xfer_t* ptXfer)
{
	usbd_pipe_t* ptPipe = ptXfer->ptPipe;

	USB_TRACE_ENTER1(3, usb_USBDTransferDone, ptXfer);
	
	/* remove request from pipe */
	if(!ptXfer->cRepeat) {
		ptPipe->ptXfer = NULL;
	}

	/* set several parameters */
	ptXfer->cDone = 1;
	if(!ptXfer->tStatus && ptXfer->usActLen < ptXfer->usLength &&
	   !(ptXfer->usFlags & USBD_SHORT_XFER_OK)) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("usb_USBDTransferdone: short xfer\n");
#endif
		ptXfer->tStatus = USBD_SHORT_XFER;
	}

#if defined(USBD_UTIL)
	usb_USBDWatchXfer_RegisterTransferedXfer(ptXfer);
	if(usb_USBDWatchXfer_CheckXfer(ptXfer) != USB_OK) {
		DEBUG_ERROR_CALL( 0, "broken xfer!!!\n", NULL);
	}
#endif
	
	if(ptPipe->tMethods.fpDone)
		ptPipe->tMethods.fpDone(ptXfer);

	/* invoke callback fuction and free xfer */
	if(ptXfer->tCallback) {
		(*ptXfer->tCallback)(ptXfer, ptXfer->tStatus); /* CAUTION: free xfer in this callback
														  function if don't use the xfer anymore */
	}
	else {
		if(!ptXfer->cRepeat) {
			usb_USBDFreeXfer(ptXfer);
		}
	}
	USB_TRACE_LEAVE(3, usb_USBDTransferDone);
}

/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
