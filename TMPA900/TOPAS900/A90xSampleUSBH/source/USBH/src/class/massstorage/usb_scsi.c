/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_scsi.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  SCSI Command Block çÏê¨

*/

#include <string.h>
#include "usb_scsi_util.h"


/* ========== GLOBAL FUNCTIONS ========== */


/*
  INQUIRY
*/
void usb_SCSI_vInquiry( uint8_t ucLun, uint8_t* pucBuffer, uint8_t ucBufSize, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_IN;
  ptCmdBlk->ucCmdSize = SCSI_INQUIRY_CMD_SZ;
  ptCmdBlk->pucBuffer = pucBuffer;
  ptCmdBlk->usBufferSize = ucBufSize;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_INQUIRY;
  pucBlock[4] = ucBufSize;
}


/*
  MODE SENSE(6)
*/
void usb_SCSI_vModeSense6( uint8_t ucLun, uint8_t* pucBuffer, uint8_t ucBufSize, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_IN;
  ptCmdBlk->ucCmdSize = SCSI_MODE_SENSE6_CMD_SZ;
  ptCmdBlk->pucBuffer = pucBuffer;
  ptCmdBlk->usBufferSize = ucBufSize;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_MODE_SENSE6;
  pucBlock[2] = SCSI_MODE_SENSE6_PAGE_CODE;
  pucBlock[4] = ucBufSize;
}


/*
  PREVENT ALLOW MEDIUM REMOVAL
*/
void usb_SCSI_vPreventAllowMediumRemoval( uint8_t ucLun, bool blLock, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_OUT;
  ptCmdBlk->ucCmdSize = SCSI_PREVENT_ALLOW_MEDIUM_CMD_SZ;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_PREVENT_ALLOW_MEDIUM;
  if( blLock != false )
    pucBlock[4] = SCSI_PREVENT_ALLOW_MEDIUM_LOCK;
}


/*
  READ(10)
*/
void usb_SCSI_vRead10( uint8_t ucLun, uint32_t ulStartBlk, uint16_t usNumBlks,
                 uint8_t* pucBuffer, uint16_t usBufferSize, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_IN;
  ptCmdBlk->ucCmdSize = SCSI_READ10_CMD_SZ;
  ptCmdBlk->pucBuffer = pucBuffer;
  ptCmdBlk->usBufferSize = usBufferSize;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_READ10;
  pucBlock[2] = (uint8_t)((ulStartBlk >> 24) & 0xff);
  pucBlock[3] = (uint8_t)((ulStartBlk >> 16) & 0xff);
  pucBlock[4] = (uint8_t)((ulStartBlk >> 8) & 0xff);
  pucBlock[5] = (uint8_t)(ulStartBlk & 0xff);
  pucBlock[7] = (uint8_t)((usNumBlks >> 8) & 0xff);
  pucBlock[8] = (uint8_t)(usNumBlks & 0xff);
}


/*
  READ CAPACITY(10)
    pcBuffer ÇÕ 8[byte]å¿íË
*/
void usb_SCSI_vReadCapacity10( uint8_t ucLun, uint8_t* pucBuffer, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_IN;
  ptCmdBlk->ucCmdSize = SCSI_READ_CAPACITY_CMD_SZ;
  ptCmdBlk->pucBuffer = pucBuffer;
  ptCmdBlk->usBufferSize = SCSI_READ_CAPACITY_BUF_SZ;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_READ_CAPACITY;
}


/*
  REQUEST SENSE
*/
void usb_SCSI_vRequestSense( uint8_t ucLun, uint8_t* pucBuffer, uint8_t ucBufSize, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_IN;
  ptCmdBlk->ucCmdSize = SCSI_REQUEST_SENSE_CMD_SZ;
  ptCmdBlk->pucBuffer = pucBuffer;
  ptCmdBlk->usBufferSize = ucBufSize;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_REQUEST_SENSE;
  pucBlock[4] = ucBufSize;
}


/*
  START/STOP UNIT
*/
void usb_SCSI_vStartStopUnit( uint8_t ucLun, uint8_t ucOperation, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_OUT;
  ptCmdBlk->ucCmdSize = SCSI_START_STOP_UNIT_CMD_SZ;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_START_STOP_UNIT;
  pucBlock[4] = (uint8_t)(ucOperation & 0x03);
}


/*
  TEST UNIT READY
*/
void usb_SCSI_vTestUnitReady( uint8_t ucLun, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_OUT;
  ptCmdBlk->ucCmdSize = SCSI_TESTUNIT_READY_CMD_SZ;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_TEST_UNIT_READY;
}


/*
  WRITE(10)
*/
void usb_SCSI_vWrite10( uint8_t ucLun, uint32_t ulStartBlk, uint16_t usNumBlks,
                  uint8_t* pucBuffer, uint16_t usBufferSize, usb_MSC_typeCommandBlock* ptCmdBlk )
{
  uint8_t* pucBlock;

  if( ptCmdBlk == NULL )
    return;

  pucBlock = ptCmdBlk->pucCmdBlock;

  memset( ptCmdBlk, 0, sizeof(usb_MSC_typeCommandBlock) );
  ptCmdBlk->ucDirection = USB_MSC_DIR_OUT;
  ptCmdBlk->ucCmdSize = SCSI_WRITE10_CMD_SZ;
  ptCmdBlk->pucBuffer = pucBuffer;
  ptCmdBlk->usBufferSize = usBufferSize;
  ptCmdBlk->ucLun = ucLun;

  pucBlock[0] = SCSI_WRITE10;
  pucBlock[2] = (uint8_t)((ulStartBlk >> 24) & 0xff);
  pucBlock[3] = (uint8_t)((ulStartBlk >> 16) & 0xff);
  pucBlock[4] = (uint8_t)((ulStartBlk >> 8) & 0xff);
  pucBlock[5] = (uint8_t)(ulStartBlk & 0xff);
  pucBlock[7] = (uint8_t)((usNumBlks>> 8) & 0xff);
  pucBlock[8] = (uint8_t)(usNumBlks& 0xff);
}

/* --- End of File --- */
