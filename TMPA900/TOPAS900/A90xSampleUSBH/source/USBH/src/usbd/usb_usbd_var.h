/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 * @ingroup	usbd_subr
 */

/* $Id: usb_usbd_var.h 41 2014-01-27 14:05:18Z danielru $ */

#ifndef _USB_USBD_VAR_H_SEEN_
#define _USB_USBD_VAR_H_SEEN_

#include "usb_config.h"
#include <usb.h>
#include "usb_usbd_class.h"

/*!
 * \addtogroup usbd_subr USBDサブルーチン
 * \ingroup usbd
 * @{
 */

/* ********************************************************* */
/*              Type Definitions & Constants                 */
/* ********************************************************* */
/*!
 * USBドライバのバス上に存在できる最大デバイス数。
 * ルートハブも１つのデバイスとなるため USB_MAX_DEVICES よりも１大きくなる。
 */
#define USBD_MAX_DEVICES		(USB_MAX_DEVICES + 1)


/*!
 * USBD のポート初期化段階
 */
typedef enum {
	kPortNoDevice = 0,
	kPortConnected,
	kPortIdentified,
	kPortAttached,
	kPortDisconnected,
	kPortIgnored
} usbd_port_stage_t;


struct usbd_pipe;
struct usbd_bus;
struct usbd_xfer;


/*!
 * USBD コールバック型
 */
typedef void (*usbd_callback)(struct usbd_xfer*, usbd_status); /* xfer, stat */



/*!
 * USBD エンドポイント管理構造
 */
typedef struct usbd_endpoint {
	usb_endpoint_descriptor_t*		ptEdesc;			/* endpoint desc */
	int8_t							cRefcnt;			/* reference counter */
} usbd_endpoint_t;

/*!
 * パイプ操作関数管理構造
 */
typedef struct usbd_pipe_methods {
	usbd_status				(*fpStart)(struct usbd_xfer* ptXfer);
	void					(*fpAbort)(struct usbd_xfer* ptXfer);
	void					(*fpClose)(struct usbd_pipe* ptPipe);
	void					(*fpClearToggle)(struct usbd_pipe* ptPipe);
	void					(*fpDone)(struct usbd_xfer* ptXfer);	/* いらない？ */
} usbd_pipe_methods_t;

/*!
 * USBD ポート管理構造
 */
typedef struct usbd_port {
	usb_port_status_t				tStatus;		/* port status */
	uint16_t						usPower;		/* power */
	uint8_t							ucPortNo;		/* assigned port number */
	uint8_t							ucRestartCnt;
#define USBD_RESTART_MAX	5
	struct usbd_device*				ptDevice;		/* connected device (reference) */
	struct usbd_device*				ptParent;		/* ports hub (reference) */
	usbd_port_stage_t				tPortStage;		/* initialization stage(for notification) */
} usbd_port_t;

/*!
 * USBD ハブ管理構造
 */
typedef struct usbd_hub {
	usbd_status						(*fpExplore)(struct usbd_device* ptHub);
	void*							vpHubSoftc;		/* hub controller */
	usb_hub_descriptor_t			tHubDesc;		/* hub descriptor */
	usb_hub_status_t				tHubStatus;		/* hub status */
	struct usbd_port				ptPorts[1];		/* ports[2,3...] allocated dynamically */
} usbd_hub_t;

/*!
 * USBD バス管理構造
 */
typedef struct usbd_bus {
	/* filled by usb driver */
	struct usbd_device*				ptRootHub;		/* a reference to device of root-hub on bus */
	struct usbd_device*				pptDevices[USBD_MAX_DEVICES];	/* devices on a bus */
	struct usb_softc*				ptSoftc;		/* reference to parent (ctrl) */
	struct usb_device_stats			tStats;			/* device status */
	int8_t							cNeedsExplore;	/* a flag for explore the bus */
} usbd_bus_t;

/*!
 * USBD デバイス管理構造
 */
typedef struct usbd_device {
	struct usbd_bus*				ptBus;			/* our controller (reference) */
	struct usbd_pipe*				ptDefaultPipe;	/* pipe 0 */
	uint8_t							ucAddress;		/* device address */
	uint8_t							ucConfig;		/* current configuration number */
	int8_t							cSelfPowered;	/* flag for self powered */
	int8_t							cLowSpeed;		/* if 1, device is low-speed device. otherwise 0 */
	uint16_t						usPower;		/* mA the device uses */
	uint8_t							ucDepth;		/* depth */
	struct usbd_port*				ptPowerSrc;		/* upstream hub port, or 0 */
	struct usbd_device*				ptMyHub;		/* my parent hub (reference) */
	struct usbd_endpoint			tDefEp;			/* for pipe 0 */
	usb_endpoint_descriptor_t		tDefEdesc;		/* for pipe 0 */
	struct usbd_interface*			ptIfaces;		/* array of all interfaces */
	usb_device_descriptor_t			tDdesc;			/* device descriptor */
	usb_config_descriptor_t*		ptCdesc;		/* full config descr */
	struct usbd_hub*				ptHub;			/* only if this device is a hub, otherwise NULL */
	struct USBD_tagClassDriver*		ptDrv;			/* class driver attached for this device */
	int8_t							pcProdName[32];	/* string of product name */
	int8_t							pcManuName[32];	/* string of manufacturer name */
	int8_t							pcConfName[32]; /* string of configuration name */
} usbd_device_t;

/*!
 * USBD インターフェイス管理構造
 */
typedef struct usbd_interface {
	usb_dlist_head_t				pipes;			/* list head of usbd_pipe_t */
	struct usbd_device*				ptDevice;		/* my device (reference) */
	usb_interface_descriptor_t*		ptIdesc;		/* interface descriptor */
	uint8_t							ucIndex;			/* current index */
	uint8_t							ucAltIndex;		/* current alternate index */
	struct usbd_endpoint*			ptEndpoints;	/* endpoints */
} usbd_interface_t;

/*!
 * USBD パイプ管理構造
 */
typedef struct usbd_pipe {
	usb_dlist_entry_t				pipes;			/* list entry of usbd_pipe_t */
	struct usbd_interface*			ptIface;		/* my interface (reference) */
	struct usbd_device*				ptDevice;		/* my device (reference) */
	struct usbd_endpoint*			ptEndpoint;		/* endpoint */
	struct usbd_xfer*				ptXfer;			/* xfer (free on each transaction) */

	struct pipe_callback {
		USBD_typeCommFinished		fpCallback;
		uint32_t					ulArg;
	} tCallback;

	/* pipe methods (filled by HC driver) */
	struct usbd_pipe_methods		tMethods;

	int8_t							cRefcnt;		/* reference counter of pipe */
	uint8_t							ucInterval;		/* interrupt interval */
} usbd_pipe_t;

/*!
 * USBD 転送管理構造
 */
typedef struct usbd_xfer {
	struct usbd_pipe*		ptPipe;					/* my pipe */
	void*					pvBuffer;				/* buffer (reference) */
	uint16_t				usLength;				/* buffer length */
	uint16_t				usActLen;				/* actual transfer length */
	uint16_t				usFlags;				/* several transfer flags */
	int16_t					sTimeout;				/* msec of transfer timeout */
#define USBD_NO_TIMEOUT			-1
#define USBD_DEFAULT_TIMEOUT	5000	/* ms = 5 s */
	usbd_status				tStatus;				/* status of transfer */
	usbd_callback			tCallback;				/* callback when transfer is done */
	int8_t					cDone;					/* transfer done flag */
	int8_t					cRepeat;				/* if !0, reuse this xfer (don't free) */

	/* for control pipe */
	usb_device_request_t*	ptRequest;				/* device request (reference) */

	struct usbd_device*		ptDevice;				/* my device (reference) */
} usbd_xfer_t;


/*!
 * USBドライバのドライバ固有変数群
 */
typedef struct usb_softc {
	usb_slist_head_t				drvs;		/*!< registered class drvs (USBD_tagClassDriver) */
	USBD_typeNotification			tNotifications;	/*!< usbd notifications */
	USBD_typeCaughtUnrecovError		fpUnrecovError;	/*!< callback for notify unrecoverable error */
	struct usbd_bus*				ptBus;			/*!< USB bus */
	struct usbd_port				tPort;			/*!< dummy port for root hub */ 
} usb_softc_t;


#endif /* _USB_USBD_VAR_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
