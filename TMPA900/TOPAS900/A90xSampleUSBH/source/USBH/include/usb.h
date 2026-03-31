/* ************************************************************************** */
/*
 * --------------------------------------------------------------------------
 *	Application			: USB Host Driver
 *	Micon				: TMP92xx28
 *	Development Tool	: -
 * 	Complie Option		: -
 *  Copyright(C) TOSHIBA CORPORATION 2007 All rights reserved
 * --------------------------------------------------------------------------
 */

/*! \file usb.h
	\brief Declaration of USB Specification

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */

#ifndef _USB_USB_H_SEEN_
#define _USB_USB_H_SEEN_


#include "usb_types.h"			/* 基本 型定義 */

typedef uint8_t		uByte;
typedef uint8_t		uWord[2];
typedef uint8_t		uDWord[4];

#if 1 /* Little Endian */
#define USB_SETW2(word,hi,lo)	((word)[0] = (uint8_t)(lo), (word)[1] = (uint8_t)(hi))
#define USB_GETW(word)		((((uint16_t)((word)[1])) << 8) | (word)[0])
#define USB_SETW(word,val)	((word)[1] = (uint8_t)((val) >> 8), (word)[0] = (uint8_t)(val))
#define USB_GETDW(word)		(((((uint32_t)(word)[3])) << 24) | (((uint32_t)((word)[2])) << 16) | (((uint32_t)((word)[1])) << 8) | (word)[0])
#define USB_SETDW(word,val)	((word)[0] = (uint8_t)((val) >> 24),	\
							 (word)[1] = (uint8_t)((val) >> 16),	\
							 (word)[2] = (uint8_t)((val) >> 8),		\
							 (word)[3] = (uint8_t)(val))
#else /* Big Endian */
#error not support big endian
#endif


/*!
 * USBドライバで、デバイスへの SetAddress を行なう前に利用するアドレス
 */
#define USB_START_ADDR			0

/*!
 * コントロール・エンドポイントのエンドポイント・アドレス
 */
#define USB_CONTROL_ENDPOINT	0

/*!
 * 最大ハブネスト数
 */
#define USB_HUB_MAX_DEPTH		5


/* ******************** Structures ******************** */
/**
 * USB Descriptor
 */
typedef struct usb_descriptor {
	uByte	bLength;
	uByte	bDescriptorType;
	uByte	bDescriptorSubType;
} usb_descriptor_t;

/**
 * USB Device Descriptor (9.6.1)
 */
typedef struct usb_device_descriptor {
	uByte	bLength;
	uByte	bDescriptorType;
	uWord	bcdUSB;
	uByte	bDeviceClass;
	uByte	bDeviceSubClass;
	uByte	bDeviceProtocol;
	uByte	bMaxPacketSize;
	uWord	idVendor;
	uWord	idProduct;
	uWord	bcdDevice;
	uByte	iManufacturer;
	uByte	iProduct;
	uByte	iSerialNumber;
	uByte	bNumConfigurations;
} usb_device_descriptor_t;
#define USB_DEVICE_DESC_SIZE		18

/**
 * USB Configuration Descriptor (9.6.2)
 */
typedef struct usb_config_descriptor {
	uByte	bLength;
	uByte	bDescriptorType;
	uWord	wTotalLength;
	uByte	bNumInterfaces;
	uByte	bConfigurationValue;
	uByte	iConfiguration;
	uByte	bmAttributes;
#define UC_BUS_POWERED		0x80
#define UC_SELF_POWERED		0x40
	uByte	bMaxPower;
#define UC_POWER_FACTOR 2
} usb_config_descriptor_t;
#define USB_CONFIG_DESC_SIZE		9

/**
 * USB Interface Descriptor (9.6.3)
 */
typedef struct usb_interface_descriptor {
	uByte	bLength;
	uByte	bDescriptorType;
	uByte	bInterfaceNumber;
	uByte	bAlternateSetting;
	uByte	bNumEndpoints;
	uByte	bInterfaceClass;
	uByte	bInterfaceSubClass;
	uByte	bInterfaceProtocol;
	uByte	iInterface;
} usb_interface_descriptor_t;
#define USB_INTERFACE_DESC_SIZE		9

/**
 * USB Endpoint Descriptor (9.6.4)
 */
typedef struct usb_endpoint_descriptor {
	uByte	bLength;
	uByte	bDescriptorType;
	uByte	bEndpointAddress;
#define UE_GET_DIR(a)	((a) & 0x80)
#define UE_SET_DIR(a,d) ((a) | (((d)&1) << 7))
#define UE_DIR_IN		0x80
#define UE_DIR_OUT		0x00
#define UE_ADDR			0x0f
#define UE_GET_ADDR(a)	((a) & UE_ADDR)
	uByte	bmAttributes;
#define UE_XFERTYPE		0x03
#define	 UE_CONTROL		0x00
#define	 UE_ISOCHRONOUS 0x01
#define	 UE_BULK		0x02
#define	 UE_INTERRUPT	0x03
#define UE_GET_XFERTYPE(a)	((a) & UE_XFERTYPE)
#define UE_ISO_TYPE		0x0c
#define	 UE_ISO_ASYNC	0x04
#define	 UE_ISO_ADAPT	0x08
#define	 UE_ISO_SYNC	0x0c
#define UE_GET_ISO_TYPE(a)	((a) & UE_ISO_TYPE)
	uWord	wMaxPacketSize;
	uByte	bInterval;
} usb_endpoint_descriptor_t;
#define USB_ENDPOINT_DESC_SIZE		7

/**
 * USB String Descriptor
 */
typedef struct usb_string_descriptor {
	uByte	bLength;
	uByte	bDescriptorType;
	uWord	bString[64];		/* XXX 64bytes at once */
} usb_string_descriptor_t;

/**
 * USB Hub Descriptor (11.15.2.1)
 */
typedef struct usb_hub_descriptor {
	uByte	bDescLength;
	uByte	bDescriptorType;
	uByte	bNbrPorts;
	uWord	wHubCharacteristics;
#define UHD_PWR				0x0003
#define	 UHD_PWR_GANGED		0x0000
#define	 UHD_PWR_INDIVIDUAL 0x0001
#define	 UHD_PWR_NO_SWITCH	0x0002
#define UHD_COMPOUND		0x0004
#define UHD_OC				0x0018
#define	 UHD_OC_GLOBAL		0x0000
#define	 UHD_OC_INDIVIDUAL	0x0008
#define	 UHD_OC_NONE		0x0010
#define UHD_TT_THINK		0x0060
#define	 UHD_TT_THINK_8		0x0000
#define	 UHD_TT_THINK_16	0x0020
#define	 UHD_TT_THINK_24	0x0040
#define	 UHD_TT_THINK_32	0x0060
#define UHD_PORT_IND		0x0080
	uByte	bPwrOn2PwrGood;
#define UHD_PWRON_FACTOR 2		/* delay in 2 ms units */
	uByte	bHubContrCurrent;
	uByte	DeviceRemovable[32]; /* bits indicates if a port has a removable device attached. up to a max 255 ports */
#define UHD_NOT_REMOV(desc, i) \
	(((desc)->DeviceRemovable[(i)/8] >> ((i) % 8)) & 1)	/* Is the Nth port not removable? */
	uByte	PortPowerCtrlMask[1];
} usb_hub_descriptor_t;
#define USB_HUB_DESC_SIZE	9 /* DeviceRemovable[2], [3]... PortPowerCtrlMask[2], [3].... are optionals */

/**
 * USB Device Request (9.3)
 */
typedef struct usb_device_request {
	uByte	bmRequestType;
#define UT_WRITE		0x00
#define UT_READ			0x80
#define UT_STANDARD		0x00
#define UT_CLASS		0x20
#define UT_VENDOR		0x40
#define UT_DEVICE		0x00
#define UT_INTERFACE	0x01
#define UT_ENDPOINT		0x02
#define UT_OTHER		0x03

#define UT_READ_DEVICE				(UT_READ  | UT_STANDARD | UT_DEVICE)
#define UT_READ_INTERFACE			(UT_READ  | UT_STANDARD | UT_INTERFACE)
#define UT_READ_ENDPOINT			(UT_READ  | UT_STANDARD | UT_ENDPOINT)
#define UT_WRITE_DEVICE				(UT_WRITE | UT_STANDARD | UT_DEVICE)
#define UT_WRITE_INTERFACE			(UT_WRITE | UT_STANDARD | UT_INTERFACE)
#define UT_WRITE_ENDPOINT			(UT_WRITE | UT_STANDARD | UT_ENDPOINT)
#define UT_READ_CLASS_DEVICE		(UT_READ  | UT_CLASS | UT_DEVICE)
#define UT_READ_CLASS_INTERFACE		(UT_READ  | UT_CLASS | UT_INTERFACE)
#define UT_READ_CLASS_OTHER			(UT_READ  | UT_CLASS | UT_OTHER)
#define UT_READ_CLASS_ENDPOINT		(UT_READ  | UT_CLASS | UT_ENDPOINT)
#define UT_WRITE_CLASS_DEVICE		(UT_WRITE | UT_CLASS | UT_DEVICE)
#define UT_WRITE_CLASS_INTERFACE	(UT_WRITE | UT_CLASS | UT_INTERFACE)
#define UT_WRITE_CLASS_OTHER		(UT_WRITE | UT_CLASS | UT_OTHER)
#define UT_WRITE_CLASS_ENDPOINT		(UT_WRITE | UT_CLASS | UT_ENDPOINT)
#define UT_READ_VENDOR_DEVICE		(UT_READ  | UT_VENDOR | UT_DEVICE)
#define UT_READ_VENDOR_INTERFACE	(UT_READ  | UT_VENDOR | UT_INTERFACE)
#define UT_READ_VENDOR_OTHER		(UT_READ  | UT_VENDOR | UT_OTHER)
#define UT_READ_VENDOR_ENDPOINT		(UT_READ  | UT_VENDOR | UT_ENDPOINT)
#define UT_WRITE_VENDOR_DEVICE		(UT_WRITE | UT_VENDOR | UT_DEVICE)
#define UT_WRITE_VENDOR_INTERFACE	(UT_WRITE | UT_VENDOR | UT_INTERFACE)
#define UT_WRITE_VENDOR_OTHER		(UT_WRITE | UT_VENDOR | UT_OTHER)
#define UT_WRITE_VENDOR_ENDPOINT	(UT_WRITE | UT_VENDOR | UT_ENDPOINT)
	uByte	bRequest;
#define UR_GET_STATUS						0x00
#define UR_CLEAR_FEATURE					0x01
#define UR_SET_FEATURE						0x03
#define UR_SET_ADDRESS						0x05
#define UR_GET_DESCRIPTOR					0x06
#define	 UDESC_DEVICE						0x01
#define	 UDESC_CONFIG						0x02
#define	 UDESC_STRING						0x03
#define	 UDESC_INTERFACE					0x04
#define	 UDESC_ENDPOINT						0x05
#define	 UDESC_DEVICE_QUALIFIER 			0x06
#define	 UDESC_OTHER_SPEED_CONFIGURATION	0x07
#define	 UDESC_INTERFACE_POWER				0x08
#define	 UDESC_OTG							0x09
#define	 UDESC_CS_DEVICE					0x21	/* class specific */
#define	 UDESC_CS_CONFIG					0x22
#define	 UDESC_CS_STRING					0x23
#define	 UDESC_CS_INTERFACE					0x24
#define	 UDESC_CS_ENDPOINT					0x25
#define	 UDESC_HUB							0x29
#define UR_SET_DESCRIPTOR					0x07
#define UR_GET_CONFIG						0x08
#define UR_SET_CONFIG						0x09
#define UR_GET_INTERFACE					0x0a
#define UR_SET_INTERFACE					0x0b
#define UR_SYNCH_FRAME						0x0c
	uWord	wValue;
	uWord	wIndex;
	uWord	wLength;
} usb_device_request_t;

#define USB_MAX_IPACKET			8 /* maximum size of the initial packet */

/* ----- Feature numbers ----- */
#define UF_ENDPOINT_HALT		0
#define UF_DEVICE_REMOTE_WAKEUP 1
#define UF_TEST_MODE			2

/* ===== Hub specific ===== */
/* ----- hub requests ----- */
#define UR_GET_BUS_STATE		0x02
#define UR_CLEAR_TT_BUFFER		0x08
#define UR_RESET_TT				0x09
#define UR_GET_TT_STATE			0x0a
#define UR_STOP_TT				0x0b

/* ----- hub features ----- */
#define UHF_C_HUB_LOCAL_POWER	0
#define UHF_C_HUB_OVER_CURRENT	1
#define UHF_PORT_CONNECTION		0
#define UHF_PORT_ENABLE			1
#define UHF_PORT_SUSPEND		2
#define UHF_PORT_OVER_CURRENT	3
#define UHF_PORT_RESET			4
#define UHF_PORT_POWER			8
#define UHF_PORT_LOW_SPEED		9
#define UHF_C_PORT_CONNECTION	16
#define UHF_C_PORT_ENABLE		17
#define UHF_C_PORT_SUSPEND		18
#define UHF_C_PORT_OVER_CURRENT 19
#define UHF_C_PORT_RESET		20
#define UHF_PORT_TEST			21
#define UHF_PORT_INDICATOR		22


struct usb_device_stats {
	uint32_t	uds_requests[4];	/* indexed by transfer type UE_* */
};




typedef struct {
	uWord		wStatus;
#define UDS_SELF_POWERED	0x0001		/* device status: self powered */
#define UDS_REMOTE_WAKEUP	0x0002		/* device status: wakeup */
#define UES_HALT			0x0001		/* endpoint status: halt */
} usb_status_t;

typedef struct {
	uWord		wHubStatus;
#define UHS_LOCAL_POWER		0x0001
#define UHS_OVER_CURRENT	0x0002
	uWord		wHubChange;
#define UHS_C_LOCAL_POWER	0x0001
#define UHS_C_OVER_CURRENT	0x0002
} usb_hub_status_t;

typedef struct {
	uWord		wPortStatus;
#define UPS_CURRENT_CONNECT_STATUS	0x0001L
#define UPS_PORT_ENABLED			0x0002L
#define UPS_SUSPEND					0x0004L
#define UPS_OVERCURRENT_INDICATOR	0x0008L
#define UPS_RESET					0x0010L
#define UPS_PORT_POWER				0x0100L
#define UPS_LOW_SPEED				0x0200L
#define UPS_HIGH_SPEED				0x0400L
#define UPS_PORT_TEST				0x0800L
#define UPS_PORT_INDICATOR			0x1000L
	uWord		wPortChange;
#define UPS_C_CONNECT_STATUS		0x0001L
#define UPS_C_PORT_ENABLED			0x0002L
#define UPS_C_SUSPEND				0x0004L
#define UPS_C_OVERCURRENT_INDICATOR 0x0008L
#define UPS_C_PORT_RESET			0x0010L
} usb_port_status_t;


/* ----- Device class codes ----- */
#define UDCLASS_IN_INTERFACE	0x00
#define UDCLASS_COMM			0x02
#define UDCLASS_HUB				0x09
#define	 UDSUBCLASS_HUB			0x00
#define	 UDPROTO_FSHUB			0x00
#define	 UDPROTO_HSHUBSTT		0x01
#define	 UDPROTO_HSHUBMTT		0x02
#define UDCLASS_DIAGNOSTIC		0xdc
#define UDCLASS_WIRELESS		0xe0
#define	 UDSUBCLASS_RF			0x01
#define	  UDPROTO_BLUETOOTH		0x01
#define UDCLASS_VENDOR			0xff

/* ----- Interface class codes ----- */
#define UICLASS_UNSPEC			0x00
/* mass storage class */
#define UICLASS_MASS			0x08
#define	 UISUBCLASS_RBC			1
#define	 UISUBCLASS_SFF8020I	2
#define	 UISUBCLASS_QIC157		3
#define	 UISUBCLASS_UFI			4
#define	 UISUBCLASS_SFF8070I	5
#define	 UISUBCLASS_SCSI		6
#define	 UIPROTO_MASS_CBI_I		0
#define	 UIPROTO_MASS_CBI		1
#define	 UIPROTO_MASS_BBB_OLD	2	/* Not in the spec anymore */
#define	 UIPROTO_MASS_BBB		80	/* 'P' for the Iomega Zip drive */

/* hub class */
#define UICLASS_HUB				0x09
#define	 UISUBCLASS_HUB			0
#define	 UIPROTO_FSHUB			0
#define	 UIPROTO_HSHUBSTT		0 /* Yes, same as previous */
#define	 UIPROTO_HSHUBMTT		1

/* vendor class */
#define UICLASS_VENDOR			0xff


/* ===== Wait interval ===== */
/*
 * Minimum time a device needs to be powered down to go through
 * a power cycle.  XXX Are these time in the spec?
 */
#define USB_POWER_DOWN_TIME			200 /* ms */
#define USB_PORT_POWER_DOWN_TIME	100 /* ms */

/* Allow for marginal (i.e. non-conforming) devices. */
#define USB_PORT_RESET_DELAY		50	/* ms */
#define USB_PORT_ROOT_RESET_DELAY	250  /* ms */
#define USB_PORT_RESET_RECOVERY		250	 /* ms */
#define USB_PORT_POWERUP_DELAY		300 /* ms */
#define USB_SET_ADDRESS_SETTLE		10	/* ms */
#define USB_RESUME_DELAY			(50*5)	/* ms */
#define USB_RESUME_WAIT				50	/* ms */
#define USB_RESUME_RECOVERY			50	/* ms */
#define USB_EXTRA_POWER_UP_TIME		20	/* ms */

#define USB_BUS_RESET_DELAY			100 /* ms XXX?*/


/* ========== other constants ========== */
#define USB_MIN_POWER				100 /* mA */
#define USB_MAX_POWER				500 /* mA */

#define USB_SPEED_LOW  1
#define USB_SPEED_FULL 2
#define USB_SPEED_HIGH 3

#define USB_UNCONFIG_NO			0
#define USB_UNCONFIG_INDEX		(-1)



#endif
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
