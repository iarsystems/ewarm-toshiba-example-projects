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

/*! \file usb_interrupt.h
	\brief Declaration of USB Host Driver SCSI Utility

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */

/*

  SCSI Command Block 作成

*/

#ifndef USB_MSC_SCSI_CMD_H
#define USB_MSC_SCSI_CMD_H

#include "usb_msc.h"

/* ========== DEFINES ========== */

/* --- Operation Code --- */
#define SCSI_FORMAT_UNIT			0x04	/*!< FORMAT UNIT */
#define SCSI_INQUIRY				0x12	/*!< INQUIRY */
#define SCSI_MODE_SENSE6			0x1a	/*!< MODE SENS(6) */
#define SCSI_PREVENT_ALLOW_MEDIUM	0x1e	/*!< PREVENT/ALLOW MEDIUM REMOVAL */
#define SCSI_READ10					0x28	/*!< READ(10) */
#define SCSI_READ_CAPACITY			0x25	/*!< READ CAPACITY */
#define SCSI_REQUEST_SENSE			0x03	/*!< REQUEST SENS */
#define SCSI_START_STOP_UNIT		0x1b	/*!< START STOP UNIT */
#define SCSI_SEND_DIAGNOSTIC		0x1d	/*!< SEND DIAGNOSTIC */
#define SCSI_TEST_UNIT_READY		0x00	/*!< TEST UNIT READY */
#define SCSI_WRITE10				0x2a	/*!< WRITE(10) */


/* コマンドサイズ usb_MSC_typeCommandBlock.ulCmdSize  */
#define SCSI_FORMAT_UNIT_CMD_SZ				6	/*!< FORMAT UNIT Command Size */
#define SCSI_INQUIRY_CMD_SZ					6	/*!< INQUIRY Command Size */
#define SCSI_MODE_SENSE6_CMD_SZ				6	/*!< MODE SENS(6) Command Size */
#define SCSI_PREVENT_ALLOW_MEDIUM_CMD_SZ	6	/*!< PREVENT/ALLOW MEDIUM REMOVAL Command Size */
#define SCSI_READ10_CMD_SZ					10	/*!< READ(10) Command Size */
#define SCSI_READ_CAPACITY_CMD_SZ			10	/*!< READ CAPACITY Command Size */
#define SCSI_SEND_DIAGNOSTIC_CMD_SZ			6	/*!< REQUEST SENS Command Size */
#define SCSI_START_STOP_UNIT_CMD_SZ			6	/*!< START STOP UNIT Command Size */
#define SCSI_REQUEST_SENSE_CMD_SZ			6	/*!< SEND DIAGNOSTIC Command Size */
#define SCSI_TESTUNIT_READY_CMD_SZ			6	/*!< TEST UNIT READY Command Size */
#define SCSI_WRITE10_CMD_SZ					10	/*!< WRITE(10) Command Size */


/* バッファサイズ usb_MSC_typeCommandBlock.ulBufferSize */
#define SCSI_INQUIRY_BUF_SZ					0x24
#define SCSI_MODE_SENSE6_MAX_BUF_SZ			0xff
#define SCSI_REQUEST_SENSE_BUF_SZ			18
#define SCSI_READ_CAPACITY_BUF_SZ			8


#define SCSI_MODE_SENSE6_PAGE_CODE			0x1c

#define SCSI_PREVENT_ALLOW_MEDIUM_LOCK		1

#define SCSI_SEND_DIAGNOSTIC_SELF_TEST		0x04

#define SCSI_START_STOP_UNIT_STOP			0x0
#define SCSI_START_STOP_UNIT_START			0x1
#define SCSI_START_STOP_UNIT_EJECT			0x2
#define SCSI_START_STOP_UNIT_LOAD			0x3


/* ========== TYPE_DEFS ========== */


/* ========== EXTERNS ========== */

/* INQUIRY */
extern void usb_SCSI_vInquiry( uint8_t ucLun, uint8_t* pucBuffer, uint8_t ucBufSize, usb_MSC_typeCommandBlock* ptCmdBlk );
/* MODE SENSE(6) */
extern void usb_SCSI_vModeSense6( uint8_t ucLun, uint8_t* pucBuffer, uint8_t ucBufSize, usb_MSC_typeCommandBlock* ptCmdBlk );
/* PREVENT ALLOW MEDIUN REMOVAL */
extern void usb_SCSI_vPreventAllowMediumRemoval( uint8_t ucLun, bool blLock, usb_MSC_typeCommandBlock* ptCmdBlk );
/* READ(10) */
extern void usb_SCSI_vRead10( uint8_t ucLun, uint32_t ulStartBlk, uint16_t usNumBlks,
						uint8_t* pucBuffer, uint16_t usBufferSize, usb_MSC_typeCommandBlock* ptCmdBlk );
/* READ CAPACITY(10) */
extern void usb_SCSI_vReadCapacity10( uint8_t ucLun, uint8_t* pucBuffer, usb_MSC_typeCommandBlock* ptCmdBlk );
/* REQUEST SENSE */
extern void usb_SCSI_vRequestSense( uint8_t ucLun, uint8_t* pucBuffer, uint8_t ucBufSize, usb_MSC_typeCommandBlock* ptCmdBlk );
/* START/STOP UNIT */
extern void usb_SCSI_vStartStopUnit( uint8_t ucLun, uint8_t ucOperation, usb_MSC_typeCommandBlock* ptCmdBlk );
/* TEST UNIT READY */
extern void usb_SCSI_vTestUnitReady( uint8_t ucLun, usb_MSC_typeCommandBlock* ptCmdBlk );
/* WRITE(10) */
extern void usb_SCSI_vWrite10( uint8_t ucLun, uint32_t ulStartBlk, uint16_t usNumBlks,
						 uint8_t* pucBuffer, uint16_t usBufferSize, usb_MSC_typeCommandBlock* ptCmdBlk );

#endif
