/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 * @ingroup		usbd_mem
 */

/* $Id: usb_usbd_mem.h 41 2014-01-27 14:05:18Z danielru $ */

#ifndef _USB_USBD_MEM_H_SEEN_
#define _USB_USBD_MEM_H_SEEN_

#include "usb_config.h"
#include <stdlib.h>		/* size_t */
#include <usb_types.h>
#include "usb_usbd_class.h"
#include "usb_uhub.h"


/*!
 * \addtogroup usbd_mem		USBバスドライバのメモリ管理
 * \ingroup usbd
 * @{
 */

/* ********************************************************* */
/*                  Function Prototypes                      */
/* ********************************************************* */
extern int16_t					usb_USBDMemInit(void);

extern usbd_device_t*			usb_USBDAllocDevice(void);
extern void						usb_USBDDeallocDevice(usbd_device_t* dev);

extern usb_config_descriptor_t*	usb_USBDAllocCDesc(usbd_device_t* dev, size_t size);
extern void						usb_USBDDeallocCDesc(usbd_device_t* dev,
													  usb_config_descriptor_t* cdesc);
#if(0)
extern usbd_interface_t*		usb_USBDAllocIfaces(usbd_device_t* dev, int num);
#else
extern usbd_interface_t*		usb_USBDAllocIfaces(usbd_device_t* dev, int16_t num);
#endif
extern void						usb_USBDDeallocIfaces(usbd_device_t* dev,
													   usbd_interface_t* ifaces);
#if(0)
extern usbd_endpoint_t*			usb_USBDAllocEndpoints(usbd_device_t* dev, int num);
#else
extern usbd_endpoint_t*			usb_USBDAllocEndpoints(usbd_device_t* dev, int16_t num);
#endif
extern void						usb_USBDDeallocEndpoints(usbd_device_t* dev,
														  usbd_endpoint_t* ed);

extern void*					usb_USBDAllocTinyBuffer(size_t size);
extern void						usb_USBDDeallocTinyBuffer(void* ptr);

extern usb_hub_descriptor_t*	usb_USBDAllocHubDesc(void);
extern void						usb_USBDDeallocHubDesc(usb_hub_descriptor_t* hubdesc);

extern usb_device_request_t*	usb_USBDAllocDeviceRequest(void);
extern void						usb_USBDDeallocDeviceRequest(usb_device_request_t* req);
extern usbd_hub_t*				usb_USBDAllocHub(size_t size);
extern void						usb_USBDDeallocHub(usbd_hub_t* hub);
extern uhub_softc_t*			usb_USBDAllocHubsoftc(void);
extern void						usb_USBDDeallocHubsoftc(uhub_softc_t* hubsoftc);

extern usbd_bus_t*				usb_USBDAllocBus(void);
extern void						usb_USBDDeallocBus(usbd_bus_t* bus);
extern usb_softc_t*				usb_USBDAllocSoftc(void);
extern void						usb_USBDDeallocSoftc(usb_softc_t* sc);

extern USBD_typeClassDriver*	usb_USBDAllocClassDriver(void);
extern void						usb_USBDDeallocClassDriver(USBD_typeClassDriver* drv);

/* --------------------------------------------------------- */
extern usb_string_descriptor_t*	usb_USBDAllocSDesc(void);
extern void						usb_USBDDeallocSDesc(usb_string_descriptor_t* sdesc);

#if defined(USBD_UTIL)
extern uint16_t					usb_USBDMemDiagnose(void);
#endif

/*!
 * @}
 */
#endif /* _USB_USBD_MEM_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
