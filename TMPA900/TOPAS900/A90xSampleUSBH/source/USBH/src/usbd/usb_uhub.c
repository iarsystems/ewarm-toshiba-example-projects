/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 */

/* $Id: usb_uhub.c 41 2014-01-27 14:05:18Z danielru $ */

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
#include <string.h>
#include <usb.h>
#include "usb_usbd_class.h"
#include "usb_usbd_subr.h"
#include "usb_uhub.h"
#include "usb_usbd_mem.h"
#include "hcd/ohci/usb_ohci.h"

#include "util/usb_trace.h"
#include "util/usb_dbg.h"
#if defined(USBD_UTIL)
#include "usb_usbd_util.h"
#endif


#define UHUB_INTR_INTERVAL 255	/* ms */



/* --------------------------------------------------------- */
/*             Hub クラス デバッグ用関数                     */
/* --------------------------------------------------------- */
#if defined(USB_DEBUG_HUB)

#include <stdarg.h>
#include <stdio.h>

#define USB_DEBUG_HUB_LOG_BUFSIZ	0x1000

#pragma arm section zidata = "HC_RAM_USBDMEM"

int8_t usb_pcHubLog[USB_DEBUG_HUB_LOG_BUFSIZ];
static int8_t* usb_pcHubLogPos = usb_pcHubLog;

/*!
 * \brief Hubクラスの動作ログを出力する
 * \param fmt printf()形式のフォーマット文字列
 * \param ... 可変引数列
 *
 * Hubクラスのログを出力する。
 * 引数は、printf() 関数と同じ。
 */
static void
hubLogv(int8_t const* fmt, ...)
{
	va_list arg;
	static int8_t buf[255];
	int len;

	/* USB_DIS_INTR() */
	va_start(arg, fmt);
	len = sprintf(buf, "[HUB]:");
	len += vsprintf(buf + 0x6, fmt, arg);
	
	/* 書き込み位置のまき戻し */
	if(usb_pcHubLogPos + len + 1 >= usb_pcHubLog + USB_DEBUG_HUB_LOG_BUFSIZ) {
		usb_pcHubLogPos = usb_pcHubLog;
	}
	if(usb_pcHubLogPos == usb_pcHubLog) {
		memset(usb_pcHubLog, 0, USB_DEBUG_HUB_LOG_BUFSIZ);
	}
	
	strcpy(usb_pcHubLogPos, buf);
	usb_pcHubLogPos += len + 1;
	va_end(arg);
	/* USB_ENA_INTR() */
}
#endif


/* ********************************************************* */
/*                  Function Prototypes                      */
/* ********************************************************* */
static void				hubPowerOnAllPorts(usbd_device_t* ptDevice);
static void				hubInterruptCallback(usbd_xfer_t* ptXfer, usbd_status iStatus);

static usbd_status		establishConnection(usbd_device_t* ptDevice, uint8_t ucPortNo);



/* ********************************************************* */
/*                  Function Definitions                     */
/* ********************************************************* */
/*!
 * \brief ハブ全ポートの電力の供給開始
 * \param ptDevice 電力供給を開始するハブ・デバイス
 *
 * ptDevice で指定されたハブのポート番号1からucNumPortsまでの
 * ポートの電力供給を開始する。
 * パワーオン後に、それぞれハブ・デスクリプタでしていされた時間分の
 * 待ちを行なう。
 */
static void
hubPowerOnAllPorts(usbd_device_t* ptDevice)
{
	usbd_status err;
	uint8_t ucPort;
	uint8_t ucNumPorts;

	if(!ptDevice || !ptDevice->ptHub) {
		return;
	}
	ucNumPorts = ptDevice->ptHub->tHubDesc.bNbrPorts;
	for(ucPort = 1; ucPort <= ucNumPorts; ucPort++) {
		err = usb_USBDSetPortFeature(ptDevice, ucPort, UHF_PORT_POWER);
		if(err) {
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
			usb_Logv("usb_iUHUBNewHub: power-on failure (port#=%u)\n", ucPort);
#endif
			; /* XXX ignore error */
		}
		/* wait for stable power */
		usb_USBDWaitMs(ptDevice->ptHub->tHubDesc.bPwrOn2PwrGood * UHD_PWRON_FACTOR +
					   USB_EXTRA_POWER_UP_TIME);
	}
}

/*!
 * \brief 新しいHubデバイスの追加
 * \param ptDevice		追加するハブデバイス
 * \return				usbd_status 型によるエラーの通知
 *
 * ptDevice で示すハブデバイスの登録処理を行なう。
 * ハブの周期Interrupt-IN転送の開始、またそれぞれの
 * ポートに対し、通電, ポートの有効化などの処理を行なう。
 */
usbd_status
usb_iUHUBNewHub(usbd_device_t* ptDevice)
{
	uhub_softc_t* ptSc;
	usb_endpoint_descriptor_t* ptEd;
	uint8_t i, ucPort, ucNumPorts;
	usbd_status err;
	usb_device_request_t* ptReq = NULL;
	usb_hub_descriptor_t* ptHubdesc = NULL;
	usbd_hub_t* ptHub = NULL;
	usbd_interface_t* ptIface = NULL;
	uint16_t usHubChar;

	USB_TRACE_ENTER1(1, usb_iUHUBNewHub, ptDevice);
	/* create hub sc */
	ptSc = usb_USBDAllocHubsoftc();
	if(!ptSc) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptSc->ptHub = ptDevice;
	ptSc->ptIpipe = NULL;

	/* ハブのネストの深さをチェック */
	if(ptDevice->ucDepth > USB_HUB_MAX_DEPTH) {
		err = USBD_TOO_DEEP;
		DEBUG_ERROR_LOG(("usb_iUHUBNewHub: hub is too deep!\n"));
		goto bad;
	}

	/* ハブデスクリプタの取得 */
	ptHubdesc = usb_USBDAllocHubDesc();
	if(!ptHubdesc) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptReq = usb_USBDAllocDeviceRequest();
	if(!ptReq) {
		err = USBD_NOMEM;
		goto bad;
	}
	memset(ptHubdesc, 0, sizeof(*ptHubdesc));
	ptReq->bmRequestType = UT_READ_CLASS_DEVICE;
	ptReq->bRequest = UR_GET_DESCRIPTOR;
	USB_SETW2(ptReq->wValue, (ptDevice->ucAddress > 1 ? UDESC_HUB : 0), 0);
	USB_SETW(ptReq->wIndex, 0);
	USB_SETW(ptReq->wLength, USB_HUB_DESC_SIZE);
	err = usb_USBDDeviceRequest(ptDevice, ptReq, ptHubdesc, 0, USBD_DEFAULT_TIMEOUT, 0);
	if(err) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_iUHUBNewHub: cannot get hub-desc.\n"));
		goto bad;
	}
	ucNumPorts = ptHubdesc->bNbrPorts;

	if(ucNumPorts > USB_MAX_HUB_PORTS) {
		/* too much ports! */
		err = USBD_NOMEM;
		goto bad;
	}
	
	if(ucNumPorts > 7) {
		USB_SETW(ptReq->wLength, USB_HUB_DESC_SIZE + (ucNumPorts >> 3));
		err = usb_USBDDeviceRequest(ptDevice, ptReq, ptHubdesc, 0, USBD_DEFAULT_TIMEOUT, 0);
		if(err) {
			DEBUG_ERROR_LOG(("usb_UHUBNewHub: cannot get full hub-desc.\n"));
			goto bad;
		}
	}

#if defined(USB_DEBUG)
	/* check removable port (for debug) */
	for(i = 0, ucPort = 1; ucPort <= ucNumPorts; ucPort++) {
		if(!UHD_NOT_REMOV(ptHubdesc, ucPort))
			i++;
	}
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
	usb_Logv("usb_iUHUBNewHub: %d port with %d removable, %s powered\n", ucNumPorts, i,
			 ptDevice->cSelfPowered ? "self" : "bus");
#endif
#endif

	if(ucNumPorts == 0) {
		err = USBD_INVAL;
		DEBUG_ERROR_LOG(("usb_iUHUBNewHub: device has no port.\n"));
		goto bad;
	}

	/* ハブ情報の構築 */
	ptHub = usb_USBDAllocHub(sizeof(usbd_hub_t) + (ucNumPorts-1) * sizeof(usbd_port_t));
	if(!ptHub) {
		err = USBD_NOMEM;
		goto bad;
	}
	ptHub->vpHubSoftc = ptSc;
	ptHub->fpExplore = usb_iUHUBExplore;
	ptHub->tHubDesc = *ptHubdesc;
	ptDevice->ptHub = ptHub;

	/* ハブの Interrupt In パイプを設定 */
	err = usb_USBDDeviceToInterface(ptDevice, 0, &ptIface);
	if(err) {
		DEBUG_ERROR_LOG(("usb_iUHUBNewHub: cannot get interface from device\n"));
		goto bad;
	}
	ptEd = usb_USBDInterfaceToEndpointDesc(ptIface, 0);
	if(ptEd == NULL) {
		err = USBD_NOT_CONFIGURED;
		DEBUG_ERROR_LOG(("usb_iUHUBNewHub: cannot get endpoint-desc from iface\n"));
		goto bad;
	}
	if((ptEd->bmAttributes & UE_XFERTYPE) != UE_INTERRUPT) {
		DEBUG_ERROR_LOG(("usb_UHUBDNewHub: hub-intr-pipe not found!\n"));
		err = USBD_INVAL;
		goto bad;
	}
	/* Interrupt In のオープンと開始 */
	{
		usbd_xfer_t* ptXfer;
		
		err = usb_USBDOpenPipe(ptIface, ptEd->bEndpointAddress, (usbd_pipe_t**)&ptSc->ptIpipe);
		if(err) {
			goto bad;
		}
		ptSc->ptIpipe->ucInterval = UHUB_INTR_INTERVAL;
		
		/* xfer の準備 */
		ptXfer = usb_USBDAllocXfer(ptIface->ptDevice);
		if(!ptXfer) {
			err = USBD_NOMEM;
			goto bad;
		}
		usb_USBDInitXfer(ptXfer, ptSc->ptIpipe, ptSc->pucStatus, sizeof(ptSc->pucStatus),
						 USBD_NO_TIMEOUT, hubInterruptCallback);
		ptXfer->usFlags = USBD_SHORT_XFER_OK;
		ptXfer->cRepeat = 1; /* 転送後に xfer を解放しない(再利用するため) */
		ptSc->ptIpipe->ptXfer = ptXfer;

		/* Interrupt In パイプの開始 */
		err = usb_USBDStartTransfer(ptXfer);
		if(err) {
			ptSc->ptIpipe->ptXfer = NULL;
			usb_USBDFreeXfer(ptXfer);
		}
	}

	if(err) {
		DEBUG_ERROR_LOG(("usb_iUHUBNewHub: hub-intr-pipe cannot open!\n"));
		goto bad;
	}

	/* wait with power off for a while */
	usb_USBDWaitMs(USB_POWER_DOWN_TIME);

	/*
	 * To have the best chance of success we do things in the exact same
	 * order as Windoze98.  This should not be necessary, but some
	 * devices do not follow the USB specs to the letter.
	 *
	 * These are the events on the bus when a hub is attached:
	 *  Get device and config descriptors (see attach code)
	 *  Get hub descriptor (see above)
	 *  For all ports
	 *     turn on power
	 *     wait for power to become stable
	 * (all below happens in explore code)
	 *  For all ports
	 *     clear C_PORT_CONNECTION
	 *  For all ports
	 *     get port status
	 *     if device connected
	 *        wait 100 ms
	 *        turn on reset
	 *        wait
	 *        clear C_PORT_RESET
	 *        get port status
	 *        proceed with device attachment
	 */

	/* setup hub-port data structures */
	for(i = 0; i < ucNumPorts; i++) {
		usbd_port_t* ptPort = &ptHub->ptPorts[i];
		ptPort->ptDevice = NULL;
		ptPort->ptParent = ptDevice;
		ptPort->ucPortNo = i+1;
		if(ptDevice->cSelfPowered)
			/* self powered hub, give ports maximum current */
			ptPort->usPower = USB_MAX_POWER;
		else
			ptPort->usPower = USB_MIN_POWER;
		ptPort->ucRestartCnt = 0;
	}

	hubPowerOnAllPorts(ptDevice);

#if defined(USB_DEBUG_HUB) /* for debug */
	usHubChar = USB_GETW(ptHub->tHubDesc.wHubCharacteristics);
	if(usHubChar & UHD_OC_GLOBAL) {
		; /* global overcurrent protection */
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("global overcurrent\n");
#endif
	}
	else if(usHubChar & UHD_OC_INDIVIDUAL) {
		; /* port individual overcurrent protection */
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("port individual overcurrent\n");
#endif
	}
	else {
		; /* no overcurrent protection */
#if defined(USB_DEBUG) && (defined(USB_DEBUG_OUTPUT2STD) || defined(USB_DEBUG_OUTPUT2BUF))
		usb_Logv("no overcurrent\n");
#endif
	}
#endif /* for debug */
	
	/* the usual exploration will finish */
	
	err = USBD_NORMAL_COMPLETION;
#if defined(USB_DEBUG_HUB)
	hubLogv("new hub: addr=%u, power=%s, port#=%u",
		   ptDevice->ucAddress,
		   ptDevice->cSelfPowered ? "self" : "bus",
		   ucNumPorts);
#endif
	goto good;
		
  bad:
	if(ptHub) {
		usb_USBDDeallocHub(ptHub);
	}
	if(ptSc && ptSc->ptIpipe) {
		usb_USBDKillPipe(ptSc->ptIpipe);
	}
	if(ptSc) {
		usb_USBDDeallocHubsoftc(ptSc);
	}
	ptDevice->ptHub = NULL;
  good:
	if(ptHubdesc)
		usb_USBDDeallocHubDesc(ptHubdesc);
	if(ptReq)
		usb_USBDDeallocDeviceRequest(ptReq);
	USB_TRACE_LEAVE(1, usb_iUHUBNewHub);
	return err;
}

/*!
 * \brief Hub を解放する
 * \param	ptHub		解放するハブ
 * \todo  各ポートに接続されているデバイスの解放処理も行なうこと。
 *
 * hub で指定されたハブを解放する。
 */
void
usb_vUHUBFreeHub(usbd_hub_t* ptHub)
{
	usbd_xfer_t* ptXfer;
	struct usbd_port* ptPort;
	uint8_t ucPortNo;
	
	USB_TRACE_ENTER1(1, usb_vUHUBFreeHub, ptHub);
#if defined(USB_DEBUG_HUB)
	hubLogv("free hub");
#endif
	if(ptHub && ptHub->vpHubSoftc) {
		/* disconnect devices on each ports (recursively) */
		if(ptHub->ptPorts) {
			for(ucPortNo = 1; ucPortNo <= ptHub->tHubDesc.bNbrPorts; ucPortNo++) {
				ptPort = &ptHub->ptPorts[ucPortNo-1];

				/* invoke port notification if device exists */
				if(ptPort->ptDevice) {
					usb_USBDChangePortStage(ptPort, kPortDisconnected, 0);
				}
#define ANNOUNCE_IGNORED_DISCONNECTION
#if defined(ANNOUNCE_IGNORED_DISCONNECTION)
				else if(ptPort->tPortStage == kPortIgnored) { /* ignored port */
					usb_USBDChangePortStage(ptPort, kPortDisconnected, 0);
				}
#endif
				
				/* notify to the class driver */
				if(ptPort->ptDevice && ptPort->ptDevice->ptDrv) {
					usb_USBDDetachClassDriver(ptPort->ptDevice);
				}
				/* free connected device and port information */
				usb_USBDDisconnectPort(ptPort);
				usb_USBDChangePortStage(ptPort, kPortNoDevice, 0);
			}
		}
		
		usb_USBDDeallocHubsoftc(ptHub->vpHubSoftc);
		usb_USBDDeallocHub(ptHub);
	}
	USB_TRACE_LEAVE(1, usb_vUHUBFreeHub);
}


/*!
 * \brief ポートの接続状態を確立する
 * \param ptDevice	対象ポートを持つハブデバイス
 * \param ucPortNo	対象ポートのポート番号
 * \retval USBD_NORMAL_COMPLETION	接続の確立
 * \retval USBD_IOERROR				接続の確立失敗
 *
 * ptDevice で指定するハブデバイスの ucPortNo 番号のポートに対して
 * ポートが接続状態を確立させる。
 * ポートステータスの wStatus, wChange により、接続状態になるまで
 * 監視しリトライを行なう。
 */
static usbd_status
establishConnection(usbd_device_t* ptDevice, uint8_t ucPortNo)
{
	uint16_t usDelay;
	uint16_t usConnection;
	uint16_t usStableCount;
	uint16_t usStatus;
	uint16_t usChange;
	struct usbd_port* ptPort;
	usbd_status err = USBD_NORMAL_COMPLETION;

	usConnection = 0;
	usStableCount = 0;
	usStatus = 0; /* for warning 'USED BEFORE SET' */
	ptPort = &ptDevice->ptHub->ptPorts[ucPortNo-1];
	
	for(usDelay = 0; usDelay < USB_DEBOUNCE_TIMEOUT; usDelay += USB_DEBOUNCE_STEP) {
		/* increasing wait */
		usb_USBDWaitMs(usDelay);

		err = usb_USBDGetPortStatus(ptDevice, ucPortNo, &ptPort->tStatus);
		if(err) {
			goto end;
		}
		usStatus = USB_GETW(ptPort->tStatus.wPortStatus);
		usChange = USB_GETW(ptPort->tStatus.wPortChange);

		/* check the connection status change */
		if((usStatus & UPS_CURRENT_CONNECT_STATUS) == usConnection) {
			/* no change in connect status */
			if(usConnection) {
				/* wait for stable connection (check connection several times) */
				if(++usStableCount >= USB_DEBOUNCE_STABLE) {
					break;
				}
			}
		}
		
		else {
			/* change connect status -> start checking stable connection */
			usStableCount = 0;
		}
		
		usConnection = (uint16_t)(usStatus & UPS_CURRENT_CONNECT_STATUS);
		if(usChange & UPS_C_CONNECT_STATUS) {
			usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_C_PORT_CONNECTION);
		}
	}
	err = usStatus & UPS_CURRENT_CONNECT_STATUS ? USBD_NORMAL_COMPLETION : USBD_IOERROR;
	
  end:
	return err;
}

/*!
 * \brief ConnectStatusChange 状態を処理する
 * \param ptDevice		対象のハブデバイス
 * \param ucPortNo		ハブの対象となるポート番号
 * \param ptPortStatus	対象ポートのポートステータス
 *
 * ptDevice で指定したハブの ucPortNo で指定したポートの、
 * ptPortStatus で渡したポートステータス状態に応じた処理を行なう。
 */
void
usb_vUHUBProcConnectStatusChange(usbd_device_t* ptDevice,
								 uint8_t ucPortNo,
								 usb_port_status_t* ptPortStatus)
{
	usbd_status err;
	uint16_t usStatus;
	uint16_t usChange;
	int8_t	 cIsLowSpeed;
	struct usbd_port* ptPort;
	int i;

	usStatus = USB_GETW(ptPortStatus->wPortStatus);
	usChange = USB_GETW(ptPortStatus->wPortChange);
	ptPort = &ptDevice->ptHub->ptPorts[ucPortNo - 1];
	if(!ptPort) {
		err = USBD_INVAL;
		goto end;
	}
	
	usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_C_PORT_CONNECTION);
	
	/* disconnect if any devices exists on the port */
	if(ptPort->ptDevice) {
		/* usb_disconnect() */
		usb_USBDChangePortStage(ptPort, kPortDisconnected, 0);
		usb_USBDDetachClassDriver(ptPort->ptDevice);
		usb_USBDDisconnectPort(ptPort);
		usb_USBDChangePortStage(ptPort, kPortNoDevice, 0);
	}
	
	/* disconnection ignored device */
	else if(ptPort->tPortStage == kPortIgnored) {
		usb_USBDChangePortStage(ptPort, kPortDisconnected, 0);
		/* nothing is connected in bus driver */
		usb_USBDChangePortStage(ptPort, kPortNoDevice, 0);
	}
	
	/* nothing is connected -> disabling the port */
	if(!(usStatus & UPS_CURRENT_CONNECT_STATUS)) {
		if(usStatus & UPS_PORT_ENABLED) {
			usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_PORT_ENABLE);
		}
		goto end;
	}

	err = establishConnection(ptDevice, ucPortNo);
	if(err) {
		/* disabling the port */
		usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_PORT_ENABLE);
		goto end;
	}

	usb_USBDWaitMs(USB_PORT_POWERUP_DELAY); /* enough low for low speed port */

	/* --- make a device --- */
	/* reset a port, so enable it */
	err = usb_USBDResetPort(ptDevice, ucPortNo, &ptPort->tStatus);
	if(err) {
		goto end;
	}

	/* get port status again, it might have changed during reset */
	err = usb_USBDGetPortStatus(ptDevice, ucPortNo, &ptPort->tStatus);
	if(err) {
		goto end;
	}
	usStatus = USB_GETW(ptPort->tStatus.wPortStatus);
	usChange = USB_GETW(ptPort->tStatus.wPortChange);

	/* no device connected */
	if(!(usStatus & UPS_CURRENT_CONNECT_STATUS)) {
		/* nothing connected, just ignore it */
		goto end;
	}

	if(usStatus & UPS_LOW_SPEED)
		cIsLowSpeed = 1;
	else
		cIsLowSpeed = 0;

	/* invoke notification */
	usb_USBDChangePortStage(ptPort, kPortConnected, 0);

	/* adding new device */
	for(i = 0; i < 3; i++) { /* retry */
		err = usb_USBDResetPort(ptDevice, ucPortNo, &ptPort->tStatus);
		if(err) {
			break;
		}
		err = usb_USBDNewDevice(ptDevice->ptBus, ptDevice->ucDepth + 1,
								cIsLowSpeed, ptPort, ucPortNo);
		if(!err) {
			if(ptPort->ptDevice && ptPort->ptDevice->ptHub) {
				/* this is a hub device. explore it */
#if 0 /* if necessary */
				{
					struct uhub_softc* ptHubSc = ptPort->ptDevice->ptHub->vpHubSoftc;
					
					memset(ptHubSc->pucStatus,
						   0xff,
						   USB_STATUS_CHANGE_BITMAP_SIZE(USB_MAX_HUB_PORTS));
				}
#endif
				ptPort->ptDevice->ptHub->fpExplore(ptPort->ptDevice);
			}
			/* adding a new device successfully */
			goto end;
		}
	}

	/* --failed to make a new device-- */
	/* invoke notification */
	usb_USBDChangePortStage(ptPort, kPortIgnored, err);
	
	/* disable the port */
	usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_PORT_ENABLE);
	
  end:
	return;
}


/*!
 * \brief ハブに接続されたデバイスを探索する
 * \param ptDevice	ハブデバイス
 * \return			usbd_status 型によるエラーの通知
 *
 * USBハブデバイスからなるデバイスツリーを探索して、
 * USBDに未登録のデバイスを登録, 抜かれたデバイスの
 * 登録解除を行なう。
 * ルートハブでは挿抜割り込み、ハブデバイスではハブの周期Interrupt転送
 * をトリガとして呼び出される。
 * ハブの各ポート状態/変化を取得(デバイス・リクエスト)して、状態変化に
 * 応じた処理を行なう。
 */
usbd_status
usb_iUHUBExplore(usbd_device_t* ptDevice)
{
	usb_hub_descriptor_t* ptHDesc;
	struct uhub_softc* ptHubSc;
	struct usbd_port* ptPort;
	int8_t cIsLowSpeed;
	uint8_t ucPortNo;
	uint16_t usChange, usStatus;
	usbd_status err = USBD_NORMAL_COMPLETION;

	USB_TRACE_ENTER1(1, usb_iUHUBExplore, ptDevice);

	/* check and ready parameters */
	if(!ptDevice->ptHub || !ptDevice->ptHub->vpHubSoftc) {
		err = USBD_INVAL;
		goto end;
	}
	ptHDesc = &ptDevice->ptHub->tHubDesc;
	ptHubSc = (struct uhub_softc*)ptDevice->ptHub->vpHubSoftc;

	/* ignore hubs that are too deep */
	if(ptDevice->ucDepth > USB_HUB_MAX_DEPTH) {
		err = USBD_TOO_DEEP;
		DEBUG_ERROR_LOG(("usb_iUHUBExplore: this hub device is too deep. ignore\n"));
		goto end;
	}

	/* error -> reset -[fail]-> disconnect */

	/* --- handle port status changes --- */
	for(ucPortNo = 1; ucPortNo <= ptHDesc->bNbrPorts; ucPortNo++) {
		/* scan bitmap */
		if(!(USB_STATUS_CHANGE_BITMAP_PORT(ptHubSc->pucStatus, ucPortNo))) {
			continue;
		}
		
		ptPort = &ptDevice->ptHub->ptPorts[ucPortNo-1];

		/* get port-status and port-change */
		err = usb_USBDGetPortStatus(ptDevice, ucPortNo, &ptPort->tStatus);
		if(err) {
			continue;
		}
		usStatus = USB_GETW(ptPort->tStatus.wPortStatus);
		usChange = USB_GETW(ptPort->tStatus.wPortChange);

		if(usChange & UPS_C_CONNECT_STATUS) {
			/* change port connect-status */
			usb_vUHUBProcConnectStatusChange(ptDevice, ucPortNo, &ptPort->tStatus);
		}
		
		else if(usChange & UPS_C_PORT_ENABLED) {
			/* change port enable */
			usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_C_PORT_ENABLE);

#if 1 /* port disabled by hub (EMI?) -> re-enabling */
			if(!(usStatus & UPS_PORT_ENABLED) &&
			   (usStatus & UPS_CURRENT_CONNECT_STATUS) &&
			   ptPort->ptDevice) {
				usb_vUHUBProcConnectStatusChange(ptDevice, ucPortNo, &ptPort->tStatus);
			}
#endif
		}

		if(usChange & UPS_C_SUSPEND) {
			/* change port suspend */
			usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_C_PORT_SUSPEND);
		}

		if(usChange & UPS_C_OVERCURRENT_INDICATOR) {
			/* change port overcurrent */
			usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_C_PORT_OVER_CURRENT);
#if 0
			hubPowerOnAllPorts(ptDevice);
#else
			/* ルートハブのときのみ、回避不能エラーとして通知 */
			if(ptDevice->ucAddress == 1) {
				usb_USBD_vRaiseUnrecoverableError();
			}
#endif
		}
		
		if(usChange & UPS_C_PORT_RESET) {
			/* change port reset */
			usb_USBDClearPortFeature(ptDevice, ucPortNo, UHF_C_PORT_RESET);
		}
	}

	/* --- handle hub status changes --- */
	/* scan bitmap */
	if(!(ptHubSc->pucStatus[0] & 1)) {
		goto end;
	}
	
	/* get hub status and changes */
	err = usb_USBDGetHubStatus(ptDevice, &ptDevice->ptHub->tHubStatus);
	if(err) {
		goto end;
	}
	usStatus = USB_GETW(ptDevice->ptHub->tHubStatus.wHubStatus);
	usChange = USB_GETW(ptDevice->ptHub->tHubStatus.wHubChange);

	if(usChange & UHS_C_LOCAL_POWER) {
		/* change hub local power */
		usb_USBDClearHubFeature(ptDevice, UHF_C_HUB_LOCAL_POWER);
	}
	if(usChange & UHS_C_OVER_CURRENT) {
		/* change hub overcurrent */
		usb_USBDWaitMs(500); /* cool down */
		usb_USBDClearHubFeature(ptDevice, UHF_C_HUB_OVER_CURRENT);
#if 0
		hubPowerOnAllPorts(ptDevice);
#else
		/* ルートハブのときのみ、回避不能エラーとして通知 */
		if(ptDevice->ucAddress == 1) {
			usb_USBD_vRaiseUnrecoverableError();
		}
#endif
	}

  end:
	USB_TRACE_LEAVE1(1, usb_iUHUBExplore, err);
	return err;
}


/*!
 * \brief ハブデバイスのステータスチェンジ時のコールバック関数
 * \param ptXfer		ステータスチェンジを通知したIntrのxfer
 * \param iStatus	ハブのIntr転送の転送状態
 *
 * ハブデバイスでステータスチェンジが発生した時に、
 * usb_iUHUBNewHub でオープンしたインターラプト・パイプによる
 * 通知で呼び出されるコールバック関数。
 */
static void
hubInterruptCallback(usbd_xfer_t* ptXfer, usbd_status iStatus)
{
	usbd_device_t* ptHub = ptXfer->ptPipe->ptDevice;
	usbd_status err;
	uhub_softc_t* ptSc;

	USB_TRACE_ENTER(3, hubInterruptCallback);
	if(!ptXfer->ptPipe->ptDevice->ptHub) { /* detached hub */
		goto end;
	}
	ptSc = (uhub_softc_t*)ptXfer->ptPipe->ptDevice->ptHub->vpHubSoftc;

	if(iStatus == USBD_STALLED) {
		usb_USBDClearEndpointStall(ptSc->ptIpipe);
	}
	else if(iStatus == USBD_NORMAL_COMPLETION) {
		/* TODO explore() の開始タイミングを遅延させるほうが好ましい。 */
		err = usb_iUHUBExplore(ptHub);
	}
	if(iStatus == USBD_CANCELLED) {
		/* interrupt-IN pipe aborted */
		goto end;
	}
	
	/* restart interrupt-in pipe */
	usb_USBDInitXfer(ptXfer, ptSc->ptIpipe, &ptSc->pucStatus, sizeof(ptSc->pucStatus),
					 USBD_NO_TIMEOUT, hubInterruptCallback);
	ptXfer->usFlags = USBD_SHORT_XFER_OK;
	ptXfer->cRepeat = 1; /* not free after transfer */

	err = usb_USBDStartTransfer(ptXfer);
	if(err) {
		ptSc->ptIpipe->ptXfer = NULL;
		usb_USBDFreeXfer(ptXfer);
		/* TODO what shall I do? this hub cannot use anymore! */
	}
	
  end:
	USB_TRACE_LEAVE(3, hubInterruptCallback);
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
