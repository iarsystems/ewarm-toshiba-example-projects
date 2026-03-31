/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohciroothub.c 4200 2015-08-14 12:44:49Z oscarmo $ */

/*

  OHCI Root Hub 処理

*/

#include <string.h>
#include "usb_ohcilib.h"
#include "usb_ohcireg.h"
#include "usb_ohcimem.h"
#include "usb_ohciroothub.h"
#include "usb_usbd_subr.h" /* usb_USBD_vTransferDone() */

/* ========== DEFINES ========== */
#undef min
#define min(x1,x2) (((x1) > (x2))? (x2):(x1))
#define C(x,y) (((uint16_t)x) | (((uint16_t)y) << 8))

/* ========== GLOBAL VARIABLES ========== */
#pragma section = "HC_RAM_OHCIMEM"

extern OHCI_typeOhci usb_OHCI_tOHCI;

/* ========== static variables ========== */

/* ルートハブ - デバイスディスクリプタ */
static const usb_device_descriptor_t tRH_DESC_DEV= {
	USB_DEVICE_DESC_SIZE,
	UDESC_DEVICE,		  /* type */
	{0x00,				/* USB version(Lo) */
	 0x10},				 /* USB version(Hi) */
	UDCLASS_HUB,		  /* class */
	UDSUBCLASS_HUB,		  /* subclass */
	UDPROTO_FSHUB,		  /* protocol */
	64,					/* max packet */
	{0,0}, {0,0}, {0x00,0x01},	 /* device id */
	1,2,0,				/* string indicies */
	1					/* # of configurations */
};

/* ルートハブ - コンフィギュレーションディスクリプタ */
static const usb_config_descriptor_t tRH_DESC_CFG= {
	USB_CONFIG_DESC_SIZE,
	UDESC_CONFIG,
	{(USB_CONFIG_DESC_SIZE +
	  USB_INTERFACE_DESC_SIZE +
	  USB_ENDPOINT_DESC_SIZE),
	 (USB_CONFIG_DESC_SIZE +
	  USB_INTERFACE_DESC_SIZE +
	  USB_ENDPOINT_DESC_SIZE) >> 8 },
	1,
	1,
	0,
	UC_SELF_POWERED,
	0	   /* max power */
};

/* ルートハブ - インターフェースディスクリプタ */
static const usb_interface_descriptor_t tRH_DESC_IFACE= {
	USB_INTERFACE_DESC_SIZE,
	UDESC_INTERFACE,
	0,
	0,
	1,
	UICLASS_HUB,
	UISUBCLASS_HUB,
	UIPROTO_FSHUB,
	0
};

/* ルートハブ - エンドポイントディスクリプタ */
static const usb_endpoint_descriptor_t tRH_DESC_EP= {
	USB_ENDPOINT_DESC_SIZE,
	UDESC_ENDPOINT,
	UE_DIR_IN | OHCI_INTR_ENDPT,
	UE_INTERRUPT,
	{8,0},		  /* max packet */
	255			  /* interval */
};

/* ルートハブ - ハブディスクリプタ */
static const usb_hub_descriptor_t tRH_DESC_HUB= {
	USB_HUB_DESC_SIZE,
	UDESC_HUB,
	0,
	{0,0},	/* characteristics */
	0,		/* bPwrOn2PwrGood */
	0,		/* bHubContrCurrent */
	{0}		/* DeviceRemovable[] */
};


/* ========== local functions ========== */

/*
  Root Hub String Descriptor セット
*/
static int16_t sSetStringDescriptor( usb_string_descriptor_t* ptDescStr, uint16_t usLen, uint8_t *pucStr )
{
	int16_t i;

	if( usLen == 0 )
		return( 0 );
	ptDescStr->bLength = (uint8_t)strlen( (char*)pucStr ) * 2 + 2;
	if( usLen == 1 )
		return( 1 );
	ptDescStr->bDescriptorType = UDESC_STRING;
	usLen -= 2;
	for( i = 0; pucStr[i] != '\0' && usLen > 1; i++, usLen -= 2 )
		USB_SETW2(ptDescStr->bString[i], 0, pucStr[i]);
	return( i * 2 + 2 );
}


/*
  ルートハブ 標準デバイスリクエスト処理
*/
static int16_t iRhStandardDeviceRequestProc( OHCI_typeOhci* ptOhci, usb_device_request_t* ptReq, uint8_t* pucBuffer, uint16_t* pusTotalLen, int16_t* psError )
{	static uint32_t count;
	uint16_t usValue, usIndex, usLen, usTemp;
	uint16_t usTotalLen = 0;

	USB_TRACE_ENTER( 3, iRhStandardDeviceRequestProc );

	usValue = USB_GETW(ptReq->wValue);
	usIndex = USB_GETW(ptReq->wIndex);
	usLen = USB_GETW(ptReq->wLength);

	ERROR_IF_WITHCODE( usLen > 0 && pucBuffer == NULL, EXT, psError, USBD_IOERROR );
count++;
	switch( C( ptReq->bRequest, ptReq->bmRequestType ) )
		{
			/* CLEAR_FEATURE */
		case C(UR_CLEAR_FEATURE, UT_WRITE_DEVICE):
		case C(UR_CLEAR_FEATURE, UT_WRITE_INTERFACE):
		case C(UR_CLEAR_FEATURE, UT_WRITE_ENDPOINT):
			/* 処理の必要なし*/
			break;

			/* GET_CONFIG */
		case C(UR_GET_CONFIG, UT_READ_DEVICE):
			if( usLen > 0 )
				{
					*pucBuffer = ptOhci->ucDevCfg;
					usTotalLen = 1;
				}
			break;

			/* GET_DESCRIPTOR  ディスクリプタ取得 */
		case C(UR_GET_DESCRIPTOR, UT_READ_DEVICE):
			switch( usValue >> 8 )
				{
					/* Device Descriptor */
				case UDESC_DEVICE:
					ERROR_IF_WITHCODE( (usValue & 0xff) != 0, EXT, psError, USBD_IOERROR );
					usTotalLen = usTemp = min( usLen, USB_DEVICE_DESC_SIZE );
					memcpy( pucBuffer, &tRH_DESC_DEV, usTemp );
					break;
					/* Configuration Descriptor */
				case UDESC_CONFIG:
					ERROR_IF_WITHCODE( (usValue & 0xff) != 0, EXT, psError, USBD_IOERROR );
					usTotalLen = usTemp = min( usLen, USB_CONFIG_DESC_SIZE );
					memcpy( pucBuffer, &tRH_DESC_CFG, usTemp );
					pucBuffer += usTemp;
					usLen -= usTemp;
					usTemp = min( usLen, USB_INTERFACE_DESC_SIZE );
					usTotalLen += usTemp;
					memcpy( pucBuffer, &tRH_DESC_IFACE, usTemp );
					pucBuffer += usTemp;
					usLen -= usTemp;
					usTemp = min( usLen, USB_ENDPOINT_DESC_SIZE );
					usTotalLen += usTemp;		/* 2006/05/24 修正 田谷 */
					memcpy( pucBuffer, &tRH_DESC_EP, usTemp );
					break;
					/* String Descriptor */
				case UDESC_STRING:
					if( usLen == 0 )
						break;
					else if( usLen == 1 )
						{
							*pucBuffer = 0;
							usTotalLen = 1;
						}
					else
						{
							*pucBuffer = 0;
							*(pucBuffer + 1) = 0;
							usTotalLen = 2;
						}

					switch( usValue & 0xff )
						{
						case 1:	 /* Vendor */
							usTotalLen = sSetStringDescriptor( (void*)pucBuffer, usLen, (uint8_t*)"unknown" );
							break;
						case 2:	 /* Product */
							usTotalLen = sSetStringDescriptor( (void*)pucBuffer, usLen, (uint8_t*)"OHCI root hub" );
							break;
						}
					break;
				default:
					*psError = USBD_IOERROR;
					goto EXT;
				}
			break;

			/* GET_INTERFACE  代替インターフェース取得 */
		case C(UR_GET_INTERFACE, UT_READ_INTERFACE):
			if( usLen > 0 )
				{
					*pucBuffer = 0;
					usTotalLen = 1;
				}
			break;

			/* GET_STATUS (Device) */
		case C(UR_GET_STATUS, UT_READ_DEVICE):
			if( usLen > 1 )
				{
					USB_SETW(((usb_status_t*)pucBuffer)->wStatus, UDS_SELF_POWERED);
					usTotalLen = 2;
				}
			break;

			/* GET_STATUS (Interface or Endpoint) */
		case C(UR_GET_STATUS, UT_READ_INTERFACE):
		case C(UR_GET_STATUS, UT_READ_ENDPOINT):
			if( usLen > 1 )
				{
					USB_SETW(((usb_status_t*)pucBuffer)->wStatus, 0);
					usTotalLen = 2;
				}
			break;

			/* SET_ADDRESS */
		case C(UR_SET_ADDRESS, UT_WRITE_DEVICE):
			ERROR_IF_WITHCODE( usValue > USBD_MAX_DEVICES, EXT, psError, USBD_IOERROR );
			ptOhci->ucDevAddr = (uint8_t)usValue;
			break;

			/* SET_CONFIG */
		case C(UR_SET_CONFIG, UT_WRITE_DEVICE):
			ERROR_IF_WITHCODE( usValue != 0 && usValue != 1, EXT, psError, USBD_IOERROR );
			ptOhci->ucDevCfg = (uint8_t)usValue;
			break;

			/* SET_DESCRIPTOR */
		case C(UR_SET_DESCRIPTOR, UT_WRITE_DEVICE ):
			break;
			/* SET_FEATURE */
		case C(UR_SET_FEATURE, UT_WRITE_DEVICE):
		case C(UR_SET_FEATURE, UT_WRITE_INTERFACE):
		case C(UR_SET_FEATURE, UT_WRITE_CLASS_ENDPOINT):
			*psError = USBD_IOERROR;
			goto EXT;
			/* SET_INTERFACE  代替インターフェース設定 */
		case C(UR_SET_INTERFACE, UT_WRITE_INTERFACE):
			break;
			/* SYNCH_FRAME */
		case C(UR_SYNCH_FRAME, UT_WRITE_ENDPOINT):
			break;
		default:
			*psError = USBD_INVAL;
			goto EXT2;
		}

	/* 転送サイズ */
	*pusTotalLen = usTotalLen;

	USB_TRACE_LEAVE( 3, iRhStandardDeviceRequestProc );
	return( OHCI_OK );
  EXT:
	DEBUG_ERROR_CALL( 0, "OHCI:iRhStandardDeviceRequestProc", psError );
  EXT2:
	USB_TRACE_LEAVE( 3, iRhStandardDeviceRequestProc );
	return( OHCI_NG );
}


/*
  ルートハブ クラスリクエスト処理
*/
static int16_t iRhClassDeviceRequestProc( OHCI_typeOhci* ptOhci, usb_device_request_t* ptReq, uint8_t* pucBuffer, uint16_t* pusTotalLen, int16_t* psError )
{
	int16_t i, j;
	uint16_t usValue, usIndex, usLen, usPort, usTemp;
	uint16_t usTotalLen = 0;
	uint32_t ulRhReg;
	usb_hub_descriptor_t tDescHub;
	usb_port_status_t tPortStat = { 0, 0 };

	USB_TRACE_ENTER( 3, iRhClassDeviceRequestProc );

	usValue = USB_GETW(ptReq->wValue);
	usIndex = USB_GETW(ptReq->wIndex);
	usLen = USB_GETW(ptReq->wLength);

	ERROR_IF_WITHCODE( usLen > 0 && pucBuffer == NULL, EXT, psError, USBD_IOERROR );

	switch( C( ptReq->bRequest, ptReq->bmRequestType ) )
		{
		case C(UR_CLEAR_FEATURE, UT_WRITE_CLASS_DEVICE):
			break;
		case C(UR_CLEAR_FEATURE, UT_WRITE_CLASS_OTHER):
			ERROR_IF_WITHCODE( usIndex < 1 || usIndex > ptOhci->ucNdp, EXT, psError, USBD_IOERROR );
			usPort = OHCI_RH_PORT_STATUS( usIndex );
			switch( usValue )
				{
				case UHF_PORT_ENABLE:
					OHCI_WRITE( usPort, UPS_CURRENT_CONNECT_STATUS );
					break;
				case UHF_PORT_SUSPEND:
					OHCI_WRITE( usPort, UPS_OVERCURRENT_INDICATOR );
					break;
				case UHF_PORT_POWER:
					OHCI_WRITE( usPort, UPS_LOW_SPEED );
					break;
				case UHF_C_PORT_CONNECTION:
					OHCI_WRITE( usPort, UPS_C_CONNECT_STATUS << 16 );
					break;
				case UHF_C_PORT_ENABLE:
					OHCI_WRITE( usPort, UPS_C_PORT_ENABLED << 16 );
					break;
				case UHF_C_PORT_SUSPEND:
					OHCI_WRITE( usPort, UPS_C_SUSPEND << 16 );
					break;
				case UHF_C_PORT_OVER_CURRENT:
					OHCI_WRITE( usPort, UPS_C_OVERCURRENT_INDICATOR << 16 );
					break;
				case UHF_C_PORT_RESET:
					OHCI_WRITE( usPort, UPS_C_PORT_RESET << 16 );
					break;
				default:
					*psError = USBD_IOERROR;
					goto EXT;
				}
			switch( usValue )
				{
				case UHF_C_PORT_CONNECTION:
				case UHF_C_PORT_ENABLE:
				case UHF_C_PORT_SUSPEND:
				case UHF_C_PORT_OVER_CURRENT:
				case UHF_C_PORT_RESET:
					break;
				default:
					break;
				}
			break;
		case C(UR_GET_DESCRIPTOR, UT_READ_CLASS_DEVICE):
			ERROR_IF_WITHCODE( (usValue & 0xff) != 0, EXT, psError, USBD_IOERROR );
			/* Root Hub Descriptor A */
			ulRhReg = OHCI_READ( OHCI_RH_DESCRIPTOR_A );
			tDescHub = tRH_DESC_HUB;
			tDescHub.bNbrPorts = ptOhci->ucNdp;
			{
				uint16_t usHubChars = (ulRhReg & OHCI_RHA_NPS) ? UHD_PWR_NO_SWITCH :
					((ulRhReg & OHCI_RHA_PSM) ? UHD_PWR_GANGED : UHD_PWR_INDIVIDUAL );
				memcpy( tDescHub.wHubCharacteristics, &usHubChars, 2 );
			}
			tDescHub.bPwrOn2PwrGood = (uint8_t)OHCI_RHA_POTPGT( ulRhReg );
			/* Root Hub Descriptor B */
			ulRhReg = OHCI_READ( OHCI_RH_DESCRIPTOR_B );
			for( i = 0, j = ptOhci->ucNdp; j > 0 && i < 2; i++, j -= 8, ulRhReg >>= 8 )
				tDescHub.DeviceRemovable[i] = (uint8_t)(ulRhReg & 0xff);
			tDescHub.bDescLength = USB_HUB_DESC_SIZE;
			usTemp = min( usLen, tDescHub.bDescLength );
			usTotalLen = usTemp;
			memcpy( pucBuffer, &tDescHub, usTemp );
			break;
		case C(UR_GET_STATUS, UT_READ_CLASS_DEVICE):
			ERROR_IF_WITHCODE( usLen != 4, EXT, psError, USBD_IOERROR );
			memset( pucBuffer, 0, usLen );
			usTotalLen = usLen;
			break;
		case C(UR_GET_STATUS, UT_READ_CLASS_OTHER):
			ERROR_IF_WITHCODE( usIndex < 1 || usIndex > ptOhci->ucNdp || usLen != 4, EXT, psError, USBD_IOERROR );
			ulRhReg = OHCI_READ( OHCI_RH_PORT_STATUS( usIndex ) );
			USB_SETW(tPortStat.wPortStatus, (uint16_t)(ulRhReg & 0xffff));
			USB_SETW(tPortStat.wPortChange, (uint16_t)((ulRhReg >> 16) & 0xffff));
			usTotalLen = usTemp = min( usLen, sizeof(usb_port_status_t) );
			memcpy( pucBuffer, &tPortStat, usTemp );
			break;
		/* 2006/05/24 修正 田谷  'UR_GET_STATUS' -> 'UR_SET_DESCRIPTOR' */
		case C(UR_SET_DESCRIPTOR, UT_WRITE_CLASS_DEVICE):
			*psError = USBD_IOERROR;
			goto EXT;
		case C(UR_SET_FEATURE, UT_WRITE_CLASS_DEVICE):
			break;
		case C(UR_SET_FEATURE, UT_WRITE_CLASS_OTHER):
			ERROR_IF_WITHCODE( usIndex < 1 || usIndex > ptOhci->ucNdp, EXT, psError, USBD_IOERROR );
			usPort = OHCI_RH_PORT_STATUS( usIndex );
			switch( usValue )
				{
				case UHF_PORT_ENABLE:
					OHCI_WRITE( usPort, UPS_PORT_ENABLED );
					break;
				case UHF_PORT_SUSPEND:
					OHCI_WRITE( usPort, UPS_SUSPEND );
					break;
				case UHF_PORT_RESET:
					OHCI_WRITE( usPort, UPS_RESET );
					/* 5[ms] 秒経過後はリセットが終了しなくても処理を終える */
					/* リセット未完了については、上位側が解決する */
					for( i = 0; i < 5; i++ )
						{
							MSEC_WAIT( USB_PORT_ROOT_RESET_DELAY );
							if( (OHCI_READ( usPort ) & UPS_RESET) == 0 )
								break;
						}
					break;
				case UHF_PORT_POWER:
					OHCI_WRITE( usPort, UPS_PORT_POWER );
					break;
				default:
					*psError = USBD_IOERROR;
					goto EXT;
				}
			break;
		default:
			*psError = USBD_INVAL;
			goto EXT;
		}

	/* 転送サイズ */
	*pusTotalLen = usTotalLen;

	USB_TRACE_LEAVE( 3, iRhClassDeviceRequestProc );
	return( OHCI_OK );
  EXT:
	DEBUG_ERROR_CALL( 0, "OHCI:iRhClassDeviceRequestProc", psError );
	USB_TRACE_LEAVE( 3, iRhClassDeviceRequestProc );
	return( OHCI_NG );
}


/* ========== GLOBAL FUNCTIONS ========== */

/*
  Root Hub Status Change 割り込み許可/禁止
*/
void usb_OHCI_vRhscAble( OHCI_typeOhci* ptOhci, bool blAble )
{

	ERROR_IF( ptOhci == NULL, EXT );

	if( blAble == false )
		{
			ptOhci->ulEnaIntrs &= ~OHCI_INTR_RHSC;
			OHCI_WRITE( OHCI_INTERRUPT_DISABLE, OHCI_INTR_RHSC );
		}
	else
		{
			ptOhci->ulEnaIntrs |= OHCI_INTR_RHSC;
			OHCI_WRITE( OHCI_INTERRUPT_ENABLE, OHCI_INTR_RHSC );
		}

	return;
  EXT:
	DEBUG_ERROR_CALL( 0, "OHCI_vAbleRhsc", NULL );
}


/*
  Root Hub Status Change 割り込み処理
*/
void usb_OHCI_vRhsc( OHCI_typeOhci* ptOhci, usbd_xfer_t* ptXfer )
{
	usbd_pipe_t* ptPipe = NULL;
	OHCI_typePipe* ptOPipe;
	uint32_t ulHubStat, ulPortStat;
	uint8_t ucMin;
	uint8_t* pucPointer = NULL;
	int16_t i;

	USB_TRACE_ENTER( 0, usb_OHCI_vRhsc );

	ERROR_IF( ptOhci == NULL || ptXfer == NULL, EXT );

	/* Hub Status 取得 */
	ulHubStat = OHCI_READ( OHCI_RH_STATUS );

	ptPipe = ptXfer->ptPipe;
	ptOPipe = (OHCI_typePipe*)ptPipe;

	pucPointer = (uint8_t*)CPUADDR( ptXfer->pvBuffer );

	ucMin = (uint8_t)min( ptOhci->ucNdp, ptXfer->usLength * 8 - 1 );
	/* size_t = uint16_t or uint32_t */
	if( ptXfer->usLength < sizeof(size_t) )
		memset( pucPointer, 0, (size_t)ptXfer->usLength );
	else
		{
			memset( pucPointer, 0, sizeof(size_t) );
			memset( pucPointer + sizeof(size_t), 0, (size_t)(ptXfer->usLength - sizeof(size_t)) );
		}

	/* Change ビットをピックアップする (LSB は Reserved なため 1 から開始) */
	for( i = 1; i <= ucMin; i++ )
		{
			ulPortStat = OHCI_READ( OHCI_RH_PORT_STATUS( i ) );

			/* Port Reset Status Cheange は無視する */
			if( (ulPortStat & OHCI_RPS_PRSC) != 0 )
				ulPortStat &= ~OHCI_RPS_PRSC;
			if( (ulPortStat >> 16) != 0 )
				pucPointer[i / 8] |= (uint8_t)(1 << ( i % 8 ));
		}

	ptXfer->usActLen = ptXfer->usLength;
	ptXfer->tStatus = USBD_NORMAL_COMPLETION;

	if( ptOhci->ptXferIntr == (OHCI_typeXfer*)ptXfer )
		ptOhci->ptXferIntr = NULL;

	/* 転送完了通知 */
	usb_USBD_vTransferDone( ptXfer );

	USB_TRACE_LEAVE( 0, usb_OHCI_vRhsc );
	return;
  EXT:
	DEBUG_ERROR_CALL( 0, "OHCI_vRhsc", NULL );
	USB_TRACE_LEAVE( 0, usb_OHCI_vRhsc );
}



/* ----- Control 転送 ----- */
/*
  Control 転送開始
  ルートハブ デバイスリクエスト処理
*/
usbd_status usb_OHCI_iRootCtrlStart( usbd_xfer_t* ptXfer )
{
	int16_t iRet, sError = USBD_NORMAL_COMPLETION;
	uint16_t usTotalLen = 0;
	uint8_t* pucBuffer = NULL;
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	usb_device_request_t* ptReq = NULL;

	USB_TRACE_ENTER( 0, OHCIRootCtrlStart );

	/* 引数チェック */
	ERROR_IF_WITHCODE( ptXfer == NULL, EXT, &sError, USBD_INVAL );

	/* デバイスリクエストとバッファ */
	ptReq = ptXfer->ptRequest;
	if( USB_GETW(ptReq->wLength) != 0 )
		{
			pucBuffer = ptXfer->pvBuffer;
			ERROR_IF_WITHCODE( pucBuffer == NULL, EXT, &sError, USBD_INVAL );
		}

	/* 標準デバイスリクエスト処理 */
	iRet = iRhStandardDeviceRequestProc( ptOhci, ptReq, pucBuffer, &usTotalLen, &sError );
	if( iRet != OHCI_OK )
		{
			/* 標準デバイスリクエストでない場合、クラスリクエスト処理 */
			if( sError == USBD_INVAL )
				iRet = iRhClassDeviceRequestProc( ptOhci, ptReq, pucBuffer, &usTotalLen, &sError );
			if( iRet != OHCI_OK )
				{
					sError =USBD_IOERROR;
					goto EXT;
				}
		}

	/* 実送受信バッファ長, エラーコード */
	ptXfer->usActLen = usTotalLen;
	sError = USBD_NORMAL_COMPLETION;

  EXT:
	ptXfer->tStatus = sError;

	/* 転送完了通知 */
	usb_USBD_vTransferDone( ptXfer );

	if( sError != USBD_NORMAL_COMPLETION ) {
		DEBUG_ERROR_CALL( 0, "OHCIRootCtrlStart", &sError );
	}
	USB_TRACE_LEAVE( 0, OHCIRootCtrlStart );
	return( sError );
}

/*
  Control 転送中断
*/
void usb_OHCI_vRootCtrlAbort( usbd_xfer_t* ptXfer)
{
	USB_TRACE_ENTER( 0, OHCIRootCtrlAbort );
	/* 転送は同期しているため、処理の必要なし */
	USB_TRACE_LEAVE( 0, OHCIRootCtrlAbort );
}

/*
  Control パイプクローズ
*/
void usb_OHCI_vRootCtrlClose( usbd_pipe_t* ptPipe )
{
	USB_TRACE_ENTER( 0, OHCIRootCtrlClose );
	/* 処理の必要なし */
	USB_TRACE_LEAVE( 0, OHCIRootCtrlClose );
}

/* ----- Interrupt 転送 ----- */
/*
  Interrupt 転送開始
*/
usbd_status usb_OHCI_iRootIntrStart( usbd_xfer_t* ptXfer )
{
	int16_t sError = USBD_INVAL;
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;
	OHCI_typePipe* ptOPipe = NULL;

	USB_TRACE_ENTER( 0, OHCIRootIntrStart );

	/* 引数チェック  2006/05/24 修正 田谷  ptPipeのNULLチェックを追加 */
	ERROR_IF_WITHCODE( ptXfer == NULL || ptXfer->usLength == 0 || ptXfer->ptPipe == NULL,
										 EXT, &sError, USBD_INVAL );

	ptOPipe = (OHCI_typePipe*)ptXfer->ptPipe;
	ptOhci->ptXferIntr = (OHCI_typeXfer*)ptXfer;

	USB_TRACE_LEAVE( 0, OHCIRootIntrStart );
	return( /*USBD_IN_PROGRESS*/ USBD_NORMAL_COMPLETION );

  EXT:
	DEBUG_ERROR_CALL( 0, "OHCIRootIntrStart", &sError );
	USB_TRACE_LEAVE( 0, OHCIRootIntrStart );
	return( sError );
}

/*
  Interrupt 転送中断
*/
void usb_OHCI_vRootIntrAbort( usbd_xfer_t* ptXfer )
{
	OHCI_typeOhci *ptOhci = &usb_OHCI_tOHCI;

	if( ptXfer == NULL )
		return;

	if( ptOhci->ptXferIntr == (OHCI_typeXfer*)ptXfer )
		{
			ptOhci->ptXferIntr = NULL;

			ptXfer->tStatus = USBD_CANCELLED;

			usb_USBD_vTransferDone( ptXfer );
		}
}

/*
  Interrupt パイプクローズ
*/
void usb_OHCI_vRootIntrClose( usbd_pipe_t* ptPipe )
{
	OHCI_typeOhci* ptOhci = &usb_OHCI_tOHCI;

	if( ptPipe->ptXfer != NULL )
		usb_OHCI_vRootIntrAbort( ptPipe->ptXfer );

	/* 2006/05/24 修正 田谷 追加 */
	ptOhci->ptXferIntr = NULL;
}

/* --- End of File --- */
