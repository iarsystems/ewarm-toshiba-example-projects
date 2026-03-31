/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *	Application			: USB Host Driver
 *	Micon				: TMP92xx28
 *	Development Tool	: Toshiba IDE
 *						:   TIDE.EXE Version 2.5.0.8
 *						:   TLCS-900 C Compiler (32) Version 4.70
 *   Copyright(C) TOSHIBA CORPORATION 2007 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file msctolsapi2.c
	\brief USB Host Driver & Mass Storage Class Driver Wrapper.

	\author TOSHIBA CORPORATION
	\date 2007/06/15 modify original file
		add function header
		add comment for doxygen
 */
/* ************************************************************************ */

/* ************************************************************************ */
/*

  API for connecting Tols File System

    Multiple device correspondence

*/

#include <string.h>
#include "usb_config.h"
#include "usb_usbd_class.h"
#include "usb_msc.h"
#include "usb_scsi_util.h"
#include "usb_timer.h"
#include "usb_interrupt.h"
#include "msctolsapi2.h"

#if defined( USB_DEBUG )
#include "usb_trace.h"
#include "usb_ohcimem.h"
#include "usb_classdrvmem.h"
#include "usb_mscmem.h"
#include "usb_tmr.h"
#endif

/* ========== defines ========== */

/*! Retry when the operations turns out an error, USB_MSC_IN_USE,
    because of the interrupt operations being undereway. */
#define USB_WRAPPER_INTERRUPT_WAIT

/*! Maximum number of device accessible (0 < x <= 32) */
#define NUM_WRAPS 16

#define CHK_LUN_CYCLE_TIME 1000   /*!< Regular device check [ms] */
#define SEM_WAIT_TIME 1000        /*!< Wait time of pseudosemaphore [ms] */
#define CONNECT_WAIT_MSEC 100
#define DISCONNECT_WAIT_LOOP 10
#define RECONNECT_WAIT_LOOP 50

#define SET_ERRORCODE( perr, code ) { if( perr ) *perr = code; }
#define ERROR_IF(is, jump)  { if( is )  goto jump; }
#define ERROR_IF_WITHCODE(is, jump, perr, code) { if( is ){ SET_ERRORCODE( perr, code ); goto jump; }}

/* ========== typedefs ========== */

/* Structure for wrapper layer management */
typedef struct tagUsbWrapper {
	uint32_t ulIdDev;							/*!< Device ID */
	union {
		struct {
			usb_MSC_typeCallbacks tCallbacks;	/*!< Callback */
			uint32_t ulBlkSz;					/*!< Block (sector) size */
			uint8_t ucLun;						/*!< Target logic unit number */
		} tMsc;									/*!< Structure for device data */
	} u;										/*!< Union Definition */
	bool blAttach;								/*!< Connection status */
} typeUsbWrapper;								/*!< Structure for wrapper layer management */


/* ========== global variables ========== */

/* tructure for wrapper layer management */
static uint8_t ucUSB_WRAP = 0;				/*!< Target MSC Device (ucDevNo)*/
static typeUsbWrapper ptUSB_WRAP[NUM_WRAPS];/*!< MSC device managing memory */

/*! Status notification function */
static USBD_typeNotification tNOTIFY;

/*! Wait status */
static volatile bool blWAITING;

/*! Error code */
static int16_t sERROR;

/*! Transfer size */
static uint32_t ulLENGTH;

/*! Timer handler ID for regular device check */
static uint32_t ulID_TIMER;

/*! Flag for semaphore */
static volatile bool blSEM_FLAG = false;

/* for stack reduction  */
static usb_MSC_typeCommandBlock tTUR_BLK;  /*!< TEST UNIT READY Command Block */


/* ========== externs ========== */
static void vRegistMscd( void );
static void vCyclicCheckLunHandler( uint32_t ulArg );

/* ************************************************************************ */
/*! \addtogroup MSCWrapper
 *  @{
 */

/* ************************************************************************ */
/*! \addtogroup Semaphore
 *  @{
 */

/* ======================================================================== */
/*! Semaphore operations
	Exclusive operations is necessary to be carried out between a regular device check
	and function call from an application.
	This operations are used for a USB packet transmission.

	\param  -
	\retval E_USB_OK		Succeeds in getting semaphore flag
	\retval E_USB_ERROR		Fails in getting semaphore flag
 */
/* ------------------------------------------------------------------------ */
static int16_t iPolSem( void )
{
	int16_t iRet = E_USB_ERROR;

	usb_vDisableAllIntr();

	if( blSEM_FLAG == false )
	{
		blSEM_FLAG = true;
		iRet = E_USB_OK;
	}

	usb_vEnableAllIntr();
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Wait operation for getting semaphore
	It waits for getting semaphore for a specified period of time.
	Provided the current operations waits until semaphore can be gotten, ignoring wait time.

	\param  iTime			Wait time [ms]
	\retval E_USB_OK		Succeeds in getting semaphore flag
	\retval E_USB_ERROR		Fails in getting semaphore flag　
 */
/* ------------------------------------------------------------------------ */
static int16_t iWaiSem( int16_t iTime )
{
	int16_t iRet, iCnt = 0;

#if 0
	iRet = iPolSem();

	while( iRet != E_USB_OK && (iCnt < iTime || iTime < 0) )
	{
		usb_TIMER_vWaiMsec( 1 );

		iCnt += 1;
		iRet = iPolSem();
	}
#else
	do
	{
		iRet = iPolSem();
	} while( iRet != E_USB_OK );
#endif

	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Semaphore release operation
	It waits for getting semaphore for a specified period of time.
	Provided the current operations waits until semaphore can be gotten, ignoring wait time.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vRelSem( void )
{
	usb_vDisableAllIntr();

	blSEM_FLAG = false;

	usb_vEnableAllIntr();
}
/* ======================================================================== */

/*! @} */ /* Semaphore */
/* ************************************************************************ */

/* ************************************************************************ */
/*! \addtogroup CallbackFunctions
 *  @{
 */

/* ======================================================================== */
/*! Devoce connection notification
	It operates when a device is connected.
	- It sets a connection status flag of a memory for an MSC device management.

	\param  ulArg		Device ID(a memory address for MSC device management)
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vWrapAttach( uint32_t ulArg )
{
	typeUsbWrapper* ptWrap = (typeUsbWrapper*)ulArg;

	ptWrap->blAttach = true;
}
/* ======================================================================== */

/* ======================================================================== */
/*! Device release notification
	It operates when a device is removed.
	- It clears a connection status flag of a memory for an MSC device management.

	\param  ulArg		Device ID(a memory address for MSC device management)
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vWrapDetach( uint32_t ulArg )
{
	typeUsbWrapper* ptWrap = (typeUsbWrapper*)ulArg;

	ptWrap->blAttach = false;
}
/* ======================================================================== */

/* ======================================================================== */
/*! Callback of SCSI command completion
	It operates when SCSI commands including read and write complete.
	- It releases semaphore flag.
	- It sets error code of transmission completion.
	- It sets data transfer size.

	\param  ulArg		Device ID(a memory address for MSC device management)
	\param  ulSize		Transfer size
	\param  sStatus		Error code
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vWrapDone( uint32_t ulArg, uint32_t ulSize, int16_t sStatus )
{
	blWAITING = false;
	sERROR = sStatus;
	ulLENGTH = ulSize;
}
/* ======================================================================== */

/* ======================================================================== */
/*! Callback of regular device check
	It operates when a regular device check completes. (TestUnitReady)
	- It releases semaphore flag.
	- It sets error code of transmission completion.
	- It sets data transfer size.

	\param  ulArg		Device ID(a memory address for MSC device management)
	\param  ulSize		Transfer size
	\param  sStatus		Error code
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vDoneCyclicCheck( uint32_t ulArg, uint32_t ulSize, int16_t sStatus )
{
	typeUsbWrapper* ptWrap = (typeUsbWrapper*)ulArg;

	/* Return an original callback */
	ptWrap->u.tMsc.tCallbacks.vDone = vWrapDone;
	usb_MSC_vSetCallback( ptWrap->ulIdDev, &ptWrap->u.tMsc.tCallbacks );

	/* Terminate exclusive operations */
	vRelSem();
}
/* ======================================================================== */

/* ======================================================================== */
/*! Device insertion notification
	It operates when a USB device is connected.
	If any device insertion function is registered, the registered function is executed.

	\param  ulIdNotify	A memory address for USB device management
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vNotfyConnect( uint32_t ulIdNotify )
{
	/* Register MSC driver */
	vRegistMscd();

	/* Notifiyi to an application */
	if( tNOTIFY.fpConnected != NULL ) {
		tNOTIFY.fpConnected( ulIdNotify );
	}
}
/* ======================================================================== */

/*! @} */ /* CallbackFunctions */
/* ************************************************************************ */

/* ************************************************************************ */
/*! \addtogroup LocalFunctions
 *  @{
 */

/* ======================================================================== */
/*! MSC driver registration
	It makes the status to the one in which only one mass storage class driver is registered.
	* The reason is under investigation.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vRegistMscd( void )
{
	int16_t i, iRet, iFstFreeWrap = -1;
	bool blFreeMscd = false;

	for( i = 0; i < NUM_WRAPS; i++ ) {
		if( ptUSB_WRAP[i].ulIdDev != 0 ) {
			if( ptUSB_WRAP[i].blAttach == false ) {
				if( blFreeMscd != false ) {
					/* Release unnecessary MSC driver */
					iRet = usb_MSC_iClose( ptUSB_WRAP[i].ulIdDev, NULL );
					if( iRet == USB_MSC_OK ) {
						ptUSB_WRAP[i].ulIdDev = 0;
					}
				}
				else {
					/* Detect a driver to which no device is connected */
					blFreeMscd = true;
				}
			}
		}
		else {
			/* Save the first driver number of drivers unused. */
			if( iFstFreeWrap < 0 ) {
				iFstFreeWrap = i;
			}
		}
	}

	/* Carry out registration when there is no driver available and registration is possible. */
	if( blFreeMscd == false && iFstFreeWrap >= 0 ) {
		/* Register a new MSC driver */
		typeUsbWrapper* ptWrap = &ptUSB_WRAP[iFstFreeWrap];
		usb_MSC_typeCallbacks* ptCb = &ptWrap->u.tMsc.tCallbacks;

		memset( ptWrap, 0, sizeof(typeUsbWrapper) );
		ptCb->ulArg = (uint32_t)ptWrap;
		ptCb->vAttach = vWrapAttach;
		ptCb->vDetach = vWrapDetach;
		ptCb->vDone = vWrapDone;
		usb_MSC_iOpen( ptCb, &ptWrap->ulIdDev, NULL );
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*! Release MSC driver registration
	It releases a registration of unused mass storage class driver.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vRemoveMscd( void )
{
	int16_t i, iRet = E_USB_OK, sError = 0;

	for( i = 0; i < NUM_WRAPS; i++ ) {
		if( ptUSB_WRAP[i].ulIdDev != 0 && ptUSB_WRAP[i].blAttach == false ) {
			/* Release unnecessary MSC drivers */
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
			do {
#endif
				iRet = usb_MSC_iClose( ptUSB_WRAP[i].ulIdDev, &sError );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
			} while( iRet != USB_MSC_OK && sError == USB_MSC_IN_USE );
#endif
			if( iRet == USB_MSC_OK ) {
				ptUSB_WRAP[i].ulIdDev = 0;
			}
		}
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*! MSC Device Disconnection
	It carries out a disconnection of mass storage class device.
	When it fails in disconnection, shuts it after saving the error code.

	\param  ptWrap			Device ID (a memory address for MSC device management)
	\param  pulIdPort		Port ID (a memory address for hub port management)
	\retval E_USB_OK		Succeeds in disconnection or unconnected
	\retval E_USB_ERROR		Fails in disconnection　
 */
/* ------------------------------------------------------------------------ */
static int16_t iDisconnectDevice( typeUsbWrapper* ptWrap, uint32_t* pulIdPort )
{
	int16_t i, iRet;

	if( ptWrap->blAttach == false ) {
		return( E_USB_OK );
	}

	/* Carry out disconnection */
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
	do {
#endif
		iRet = usb_MSC_iDisconnect( ptWrap->ulIdDev, pulIdPort, &sERROR );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
		if( iRet == USB_MSC_OK || ptWrap->blAttach == false ) {
			iRet = USB_MSC_OK;
			break;
		}
	} while( sERROR == USB_MSC_IN_USE );
#endif
	ERROR_IF( iRet != USB_MSC_OK, EXT );

	ERROR_IF_WITHCODE( ptWrap->blAttach != false, EXT, &sERROR, USB_MSC_TIMEOUT );

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Disconnect all MSC devices
	It disconnects all mass storage class devices.
	When it fails in any of disconnections, it returns an error.

	\param  -
	\retval E_USB_OK		Succeeds in disconnection
	\retval E_USB_ERROR		Fails in disconnection
 */
/* ------------------------------------------------------------------------ */
static int16_t iDisconnectAllDevice( void )
{
	int16_t i, iRet, iRes = E_USB_OK;

	for( i = 0; i < NUM_WRAPS; i++ ) {
		iRet = iDisconnectDevice( &ptUSB_WRAP[i], NULL );
		if( iRet != E_USB_OK ) {
			iRes = E_USB_ERROR;
		}
	}

	return( iRes );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Reconnect MSC device
	It releases a registration of unused mass storage class device.
	It carries out reconnection after shuts down an MSC device once.

	\param  ptWrap			Device ID (a memory address for MSC device management)
	\retval E_USB_OK		Succeeds in reconnection
	\retval E_USB_ERROR		Fails in reconnection　
 */
/* ------------------------------------------------------------------------ */
static int16_t iReconnectDevice( typeUsbWrapper* ptWrap )
{
	int16_t iRet, i;
	uint32_t ulIdPort = 0;

	/* Check connection status */
	ERROR_IF_WITHCODE( ptWrap->blAttach == false, EXT,
					   &sERROR, USB_MSC_NO_DEVICE );

	/* Release a registration of unnecessary driver to avoid any reconnection of different structure. */
	vRemoveMscd();

	/* Disconnect */
	iRet = iDisconnectDevice( ptWrap, &ulIdPort );
	ERROR_IF( iRet != E_USB_OK, EXT );

	/* Reconnect */
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
	do {
#endif
		iRet = usb_MSC_iConnect( ulIdPort, &sERROR );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
	} while( iRet != USB_MSC_OK && sERROR == USB_MSC_IN_USE );
#endif
	ERROR_IF( iRet != USB_MSC_OK, EXT );

	ERROR_IF_WITHCODE( ptWrap->blAttach == false, EXT, &sERROR, USB_MSC_TIMEOUT );

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Release all MSC drivers
	It releases registrations of all mass storage class drivers.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vRemoveAllMscd( void )
{
	int16_t i, iRet, sError = 0;
	typeUsbWrapper* ptWrap;

	for( i = 0; i < NUM_WRAPS; i++ ) {
		ptWrap = &ptUSB_WRAP[i];
		if( ptWrap->ulIdDev != 0 ) {
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
			do {
#endif
				iRet = usb_MSC_iClose( ptWrap->ulIdDev, &sError );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
			} while( iRet != USB_MSC_OK && sError == USB_MSC_IN_USE );
#endif
			if( iRet == USB_MSC_OK ) {
				ptWrap->ulIdDev = 0;
			}
		}
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*! Initialize MSC device
	It carries out an initialization when switching a target MSC device.
	As succeeds in an initialization, it carries out a regular check (TestUnitReady)
	of the ucLun number of a switched device.

	It takes an initiative of this processing until the initialization is completed.
	To release the process, it is necessary to revise the operations including upper functions.

	\param  ptWrap			Device ID (a memory address for MSC device management)
	\param  ucLun			Logic unit number
	\retval E_USB_OK		Succeeds in initialization　
	\retval E_USB_ERROR		Fails in initialization
 */
/* ------------------------------------------------------------------------ */
static int16_t iInitDevice( typeUsbWrapper* ptWrap, uint8_t ucLun )
{
	int16_t iRet;

	blWAITING = true;

	/* Initialize */
	sERROR = USB_MSC_OK;
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
	do {
#endif
		iRet = usb_MSC_iInitDevice( ptWrap->ulIdDev, ucLun, &sERROR );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
		if( iRet == USB_MSC_OK ) {
			break;
		}
		else if( ptWrap->blAttach == false ) {
			sERROR = USB_MSC_NO_DEVICE;
		}
	} while( sERROR == USB_MSC_IN_USE );
#endif
	ERROR_IF( iRet != USB_MSC_OK, EXT );

	/* Wait for completion */
	while( blWAITING != false ){
	};

	ERROR_IF( sERROR != USB_MSC_OK, EXT );

	/* Set a regular device check */
	if( ulID_TIMER == 0 ) {
		iRet = usb_TIMER_iSetHandler( vCyclicCheckLunHandler, 0,
									  CHK_LUN_CYCLE_TIME, &ulID_TIMER );
		ERROR_IF( iRet != E_USB_OK, EXT );
	}

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Read blocking mode sector

	It reads data of a number of sectors, usCount, starting from the number, ulStart.
	It saves read data in a buffer indicated by pucBuf.
	It takes an initiative of this processing until reading is completed.
	To release the process, it is necessary to revise the operations including upper functions.

	\param  ptWrap			Device ID (a memory address for MSC device management)
	\param  ulStart			Start sector number
	\param  usCount			A number of sectors
	\param  pucBuf			Storage buffer pointer of read data
	\retval E_USB_OK		Succeeds in reading　
	\retval E_USB_ERROR		Fails in reading
 */
/* ------------------------------------------------------------------------ */
static int16_t iReadSector( typeUsbWrapper* ptWrap, uint32_t ulStart, uint16_t usCount, uint8_t* pucBuf )
{
	int16_t iRet;

	blWAITING = true;

	/* Carry out reading */
	sERROR = USB_MSC_OK;
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
	do {
#endif
		iRet = usb_MSC_iRead( ptWrap->ulIdDev, ptWrap->u.tMsc.ucLun,
							  ulStart, usCount, pucBuf, &sERROR );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
		if( iRet == USB_MSC_OK ) {
			break;
		}
		else if( ptWrap->blAttach == false ) {
			sERROR = USB_MSC_NO_DEVICE;
		}
	} while( sERROR == USB_MSC_IN_USE );
#endif
	ERROR_IF( iRet != USB_MSC_OK, EXT );

	/* Wait for completion */
	while( blWAITING != false ){
	};
	ERROR_IF( sERROR != USB_MSC_OK, EXT );

	/* Check size */
	ERROR_IF( ulLENGTH != usCount * ptWrap->u.tMsc.ulBlkSz, EXT );

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Write blocking mode sector

	It writes data of a number of sectors, usCount starting from the number, ulStart.
	It writes the contents of a buffer indicated by pucBuf.
	It takes an initiative of this processing until writing is completed.
	To release the process, it is necessary to revise the operations including upper functions.

	\param  ptWrap			Device ID (a memory address for MSC device management)
	\param  ulStart			Start sector number
	\param  usCount			A number of sectors
	\param  pucBuf			Storage buffer pointer of written data
	\retval E_USB_OK		Succeeds in writing　
	\retval E_USB_ERROR		Fails in writing　
 */
/* ------------------------------------------------------------------------ */
static int16_t iWriteSector( typeUsbWrapper* ptWrap, uint32_t ulStart, uint16_t usCount, uint8_t* pucBuf )
{
	int16_t iRet;

	blWAITING = true;

	/* Carry out writing */
	sERROR = USB_MSC_OK;
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
	do {
#endif
		iRet = usb_MSC_iWrite( ptWrap->ulIdDev, ptWrap->u.tMsc.ucLun,
							   ulStart, usCount, pucBuf, &sERROR );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
		if( iRet == USB_MSC_OK ) {
			break;
		}
		else if( ptWrap->blAttach == false ) {
			sERROR = USB_MSC_NO_DEVICE;
		}
	} while( sERROR == USB_MSC_IN_USE );
#endif
	ERROR_IF( iRet != USB_MSC_OK, EXT );

	/* Wait for completion */
	while( blWAITING != false ) {
	};
	ERROR_IF( sERROR != USB_MSC_OK, EXT );

	/* Check size */
	ERROR_IF( ulLENGTH != usCount * ptWrap->u.tMsc.ulBlkSz, EXT );

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Issue SCSI command of blocking mode

	It specifies LUN of an SCSI command during the command blocking.

	It takes an initiative of this processing until the operation is completed.
	To release the process, it is necessary to revise the operations including upper functions.

	\param  ptWrap			Device ID (a memory address for MSC device management)
	\param  ptCmdBlk		Storage pointer of SCSI command
	\retval E_USB_OK		Succeeds in command　
	\retval E_USB_ERROR		Fails in command
 */
/* ------------------------------------------------------------------------ */
static int16_t iIoCtrl( typeUsbWrapper* ptWrap, usb_MSC_typeCommandBlock* ptCmdBlk )
{
	int16_t iRet;

	blWAITING = true;

	/* Carry out SCSI command */
	sERROR = USB_MSC_OK;
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
	do {
#endif
		iRet = usb_MSC_iIoControl( ptWrap->ulIdDev, ptCmdBlk, &sERROR );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
		if( iRet == USB_MSC_OK ) {
			break;
		}
		else if( ptWrap->blAttach == false ) {
			sERROR = USB_MSC_NO_DEVICE;
		}
	} while( sERROR == USB_MSC_IN_USE );
#endif
	ERROR_IF( iRet != USB_MSC_OK, EXT );

	/* Wait for completion */
	while( 	blWAITING != false ) {
	};
	ERROR_IF( sERROR != USB_MSC_OK, EXT );

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Initialize USB host driver
	It initializes a USB host driver.
	When it fails in initialization, it releases all the USB processing and terminates it.

	\param  -
	\retval E_USB_OK		Succeeds in USB host driver initialization
	\retval E_USB_ERROR		Fails in USB host driver initialization
 */
/* ------------------------------------------------------------------------ */
static int16_t iInitUsbDriver( void )
{
	int16_t iRet;

	/* Activate USB host driver */
	iRet = usb_USBD_iStart( &sERROR );
	ERROR_IF_WITHCODE( iRet != USB_OK, EXT, &iRet, E_USB_ERROR );

	return( E_USB_OK );
EXT:
	USBFin();
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Initialize USB host driver (carry out from a timer interrupt)
	This is used when returning a process to an application during an initialization of a USB host driver.
	The actual operations are carried out in the timer interrupt.
	As an initialization is completed, it carries out a registered callback if any, and terminates.

	\param  ulArg		Device ID (a memory address for MSC device management)
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vInitHandler( uint32_t ulArg )
{
	int16_t iRet;
	USBInitCallbackFn fvCb = (USBInitCallbackFn)ulArg;

	/* Carry out initialization */
	iRet = iInitUsbDriver();

	/* Notify the result */
	if( fvCb != NULL ) {
		fvCb( iRet );
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*! Test regularly a logic unit status (carry out from a timer interrupt)
	It starts testing with a device initialization as a trigger.

	\param  ulArg		DeviceID(a memory address for MSC device management)
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vCyclicCheckLunHandler( uint32_t ulArg )
{
	int16_t iRet, iSem;
	uint16_t usLuState = 0;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	ulID_TIMER = 0;

	/* Start exclusive operations */
	iSem = iPolSem();
	if( iSem == E_USB_OK ) {
		/* Get status */
		usb_MSC_vGetStatus( ptWrap->ulIdDev, NULL, &usLuState );

		/* If a target LUN is in uninitialized state, terminates a cyclical device check. */
		if( (usLuState & (1 << ptWrap->u.tMsc.ucLun)) == 0 ) {
			/* Terminate exclusive operations */
			vRelSem();
			goto EXT;
		}

		/* TEST UNIT READY */
		tTUR_BLK.ucLun = ptWrap->u.tMsc.ucLun;
		iRet = usb_MSC_iIoControl( ptWrap->ulIdDev, &tTUR_BLK, NULL );
		if( iRet == E_USB_OK ) {
			/* Change into a dedicated callback */
			ptWrap->u.tMsc.tCallbacks.vDone = vDoneCyclicCheck;
			usb_MSC_vSetCallback( ptWrap->ulIdDev, &ptWrap->u.tMsc.tCallbacks );
		}
		else {
			/* Terminate exclusive operations */
			vRelSem();
		}
	}

	/* Restart from a timer interrupt after a specific elapsed time. */
	usb_TIMER_iSetHandler( vCyclicCheckLunHandler, ulArg,
						   CHK_LUN_CYCLE_TIME, &ulID_TIMER );

EXT:
	;
}
/* ======================================================================== */

/*! @} */ /* LocalFunctions */
/* ************************************************************************ */

/* ************************************************************************ */
/*! \addtogroup GlobalFunctions
 *  @{
 */
/* ======================================================================== */
/*! Initialize MSC wrapper
	It initializes a USB host driver and MSC Driver.

	\param  fvCb			Callback function upon an initilization completion
	\param  ptNotifications		Registration type of notification callback of device connection status
	\retval E_USB_OK		Succeeds in MSC wrapper initialization　
	\retval E_USB_ERROR		Fails in MSC wrapper initialization　
 */
/* ------------------------------------------------------------------------ */
int16_t USBInit( USBInitCallbackFn fvCb, USBD_typeNotification* ptNotifications )
{
	int16_t iRet;
	uint32_t ulIdTimer = 0;

	/* Initialize a variable */
	ucUSB_WRAP = 0;
	blWAITING = false;
	sERROR = 0;
	ulLENGTH = 0;
	ulID_TIMER = 0;
	blSEM_FLAG = false;
	memset( ptUSB_WRAP, 0, sizeof(typeUsbWrapper) * NUM_WRAPS );
	if( ptNotifications != NULL ) {
		memcpy( &tNOTIFY, ptNotifications, sizeof(USBD_typeNotification) );
	}
	else {
		memset( &tNOTIFY, 0, sizeof(USBD_typeNotification) );
	}
	usb_SCSI_vTestUnitReady( 0, &tTUR_BLK );

	/* Initialize a timer */
	usb_TIMER_vInitialize();

	/* Initialize a mass class storage driver */
	usb_MSC_vInitialize();

	/* Initialize a USB host driver */
	iRet = usb_USBD_iInitialize( &sERROR );
	ERROR_IF_WITHCODE( iRet != USB_OK, EXT, &iRet, E_USB_ERROR );

	/* Register a status notification callback */
	{
		USBD_typeNotification tWrappedNotify = { 0 };
		memcpy( &tWrappedNotify, &tNOTIFY, sizeof(USBD_typeNotification) );
		tWrappedNotify.fpConnected = vNotfyConnect;
		iRet = usb_USBD_iSetNotifications( &tWrappedNotify, &sERROR );
		ERROR_IF_WITHCODE ( iRet != USB_OK, EXT, &iRet, E_USB_ERROR );
	}

	if( fvCb != NULL ) {
		/* Start up 0 [ms] after a timer interrupt */
		iRet = usb_TIMER_iSetHandler( vInitHandler, (uint32_t)fvCb,
									  0, &ulIdTimer );
	}
	else {
		/* Call directly */
		iRet = iInitUsbDriver();
	}

EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! End processing
	It carries out end processing of an MSC wrapper by disconnecting all devices.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void USBFin( void )
{
	int16_t iRet;

	usb_TIMER_vDisIntr();
	/* Release a regular check of logic unit */
	if( ulID_TIMER != 0 ) {
		usb_TIMER_vCancelHandler( ulID_TIMER );
		ulID_TIMER = 0;
	}
	usb_TIMER_vEnaIntr();

	/* Disconnect all devices */
	iDisconnectAllDevice();

	/* Disable any interrupt (no releasing is necessary since usb_USBD_vFinalize() enables end processing.) */
	usb_INTR_vDisable();

	/* Release a mass storage class driver */
	vRemoveAllMscd();

	/* Finish a USB host driver */
	usb_USBD_vFinalize();

	/* Finish a timer */
	usb_TIMER_vFinalize();

#if defined( USB_DEBUG )
	iRet = usb_USBC_iMemCheck();
	iRet += usb_OHCI_iMemCheck();
	iRet += usb_TIMER_iMemCheck();
	iRet += usb_MSC_iMemCheck();
#if defined(USBD_UTIL)
	iRet += usb_USBDMemDiagnose();
#endif
	if( iRet != 0 ) {
		DEBUG_ERROR_CALL( 2, "Illegal Memory State\n", &iRet );
	}
#endif
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get status of device connection
	It checks a device being connected.
	For *pulDevState, it sets 1 to the bit corresponding to the connected MSC device number.

	\param  pulDevState		Storage pointer of MSC device connection status
	\retval -
 */
/* ------------------------------------------------------------------------ */
void USBGetDeviceState( uint32_t* pulDevState )
{
	int16_t i;
	uint32_t ulState = 0;

	for( i = 0; i < NUM_WRAPS && i < 32; i++ ) {
		if( ptUSB_WRAP[i].ulIdDev != 0 && ptUSB_WRAP[i].blAttach != false ) {
			ulState |= (1UL << i);
		}
	}

	if( pulDevState != NULL ) {
		*pulDevState = ulState;
	}
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get a target device
	It returns an MSC device number that is a current target of operations.
	In a default setting, a device of the number 0 is a target.

	\param  -
	\retval 0 - 31			Operating target device number
 */
/* ------------------------------------------------------------------------ */
uint8_t USBGetTargetDevice( void )
{
	return( ucUSB_WRAP );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Change a target device
	It changes an operating target device to a device of the number
	specified by an argument, ucDevNo.
	The device numbers possible to be specified are in the range of 0 to 31.

	\param  ucDevNo		Operating target device number
	\retval E_USB_OK	Succeeds in change　
	\retval E_USB_ERROR	Fails in change (MSC device has yet to be connected）
 */
/* ------------------------------------------------------------------------ */
int16_t USBChangeTargetDevice( uint8_t ucDevNo )
{
	ERROR_IF_WITHCODE( ucDevNo >= NUM_WRAPS, EXT, &sERROR, USB_MSC_PARAMETER );
	ERROR_IF_WITHCODE( ptUSB_WRAP[ucDevNo].ulIdDev == 0
					   || ptUSB_WRAP[ucDevNo].blAttach == false,
					   EXT, &sERROR, USB_MSC_NO_DEVICE );

	ucUSB_WRAP = ucDevNo;

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get a number of logic units
	It gets a number of logic unit of an operating target device.
	Possible values to be logic unit numbers (LUN) are in the range of 0 to a number of logic units minus 1.

	\param  pucNumLus		Storage pointer of a gotten number of logic units.
	\retval E_USB_OK		Succeeds in getting
	\retval E_USB_ERROR		Fails in getting
 */
/* ------------------------------------------------------------------------ */
int16_t USBGetNumLus( uint8_t *pucNumLus )
{
	int16_t iRet;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	ERROR_IF_WITHCODE( pucNumLus == NULL, EXT, &sERROR, USB_MSC_PARAMETER );

	/* Start exclusive operations */
	iRet = iWaiSem( SEM_WAIT_TIME );
	ERROR_IF_WITHCODE( iRet != E_USB_OK, EXT, &sERROR, USB_MSC_IN_USE );

	/* Get a number of logic units */
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
	do {
#endif
		iRet = usb_MSC_iGetNumLus( ptWrap->ulIdDev, pucNumLus, &sERROR );
#if defined( USB_WRAPPER_INTERRUPT_WAIT )
		if( iRet == USB_MSC_OK ) {
			break;
		}
		else if( ptWrap->blAttach == false ) {
			sERROR = USB_MSC_NO_DEVICE;
		}
	} while( sERROR == USB_MSC_IN_USE );
#endif

	/* Terminate exclusive operations */
	vRelSem();

	ERROR_IF( iRet != USB_MSC_OK, EXT );

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get a target LUN
	It returns a logic unit number of a unit that is an operating target.
	It returns 0 when it is before a logic unit is specified by USBChangeTargetLun().

	\param  -
	\retval 0 - "a number of LUNs-1"		Target logic unit number
 */
/* ------------------------------------------------------------------------ */
uint8_t USBGetTargetLun( void )
{
	return( ptUSB_WRAP[ucUSB_WRAP].u.tMsc.ucLun );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Switch a target logic unit
	A logic unit indicated by a LUN specified by an argument becomes an operation target thereafter.
	In this function, an initialization of a device (logic unit) and
	regular check of a device are carried out.
	It is necessary to call this function right after inserting a device and
	before getting, reading, or writing of a number of sectors.
	Failure in an initialization turns out an error, and no switching of a target logic unit
	are carried out.

	This operations shall take an initiative of the process until an initialization of
	a device (logic unit) completes.

	\param  ucLun			Target logic unit number (LUN)
	\retval E_USB_OK		Succeeds in switching　
	\retval E_USB_ERROR		Fails in switching
 */
/* ------------------------------------------------------------------------ */
int16_t USBChangeTargetLun( uint8_t ucLun )
{
	int16_t iRet;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	/* Start exclusive operations */
	iRet = iWaiSem( SEM_WAIT_TIME );
	ERROR_IF_WITHCODE( iRet != E_USB_OK, EXT, &sERROR, USB_MSC_IN_USE );

	/* Initialize a device when switching */
	iRet = iInitDevice( ptWrap, ucLun );
	if( iRet == E_USB_OK ) {
		/* Get a block size */
		iRet = usb_MSC_iGetBlkInf( ptWrap->ulIdDev, ucLun, NULL,
								   &ptWrap->u.tMsc.ulBlkSz, &sERROR );

		if( iRet == E_USB_OK ) {
			/* Switch LUN after an initialization succeeds */
			ptWrap->u.tMsc.ucLun = ucLun;
		}
	}

	/* Terminate exclusive operations */
	vRelSem();

EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Check a logic unit
	It checks a logic unit specified by an argument whether it is usable or not.
	For example, a card reader without any card inserted results in unusable.

	\param  ucLun			Target logic unit number (LUN)
	\retval E_USB_OK		Target logic unit is usable
	\retval E_USB_ERROR		Target logic unit is unusable
 */
/* ------------------------------------------------------------------------ */
int16_t USBCheckLu( uint8_t ucLun )
{
	int16_t iRet, iSem;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	/* Start exclusive operations */
	iSem = iWaiSem( SEM_WAIT_TIME );
	if( iSem != E_USB_OK ) {
		return( E_USB_ERROR );
	}

	/* TEST UNIT READY */
	tTUR_BLK.ucLun = ucLun;
	iRet = iIoCtrl( ptWrap, &tTUR_BLK );

	/* Terminate exclusive operations */
	vRelSem();

	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get a total number of sectors (old)
	It gets a total number of sectors of an operating target device (operating target LUN).
	Use USBGetSectorInf() when sector size information is necessasry.

	\param  pulSectors		Storage pointer of a number of sectors
	\retval E_USB_OK		Succeeds in getting 　
	\retval E_USB_ERROR		Fails in getting
 */
/* ------------------------------------------------------------------------ */
int16_t USBGetStorageSize( uint32_t *pulSectors )
{
	int16_t iRet;
	uint32_t ulBlkSz = 0;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	/* Get block information */
	iRet = usb_MSC_iGetBlkInf( ptWrap->ulIdDev, ptWrap->u.tMsc.ucLun,
							   pulSectors, &ulBlkSz, &sERROR );
	if( iRet != USB_MSC_OK ) {
		goto EXT;
	}

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get sector information (new)
	It gets a total number of sectors and a size of one sector
	of an operating target device (operating target LUN).

	\param  pulSectors		Storage pointer of a number of sectors
	\param  pulSectorSz		Storage pointer of a sector size [byte]
	\retval E_USB_OK		Succeeds in getting
	\retval E_USB_ERROR		Fails in getting
 */
/* ------------------------------------------------------------------------ */
int16_t USBGetSectorInf( uint32_t *pulSectors, uint32_t* pulSectorSz )
{
	int16_t iRet;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	/* Get block information */
	iRet = usb_MSC_iGetBlkInf( ptWrap->ulIdDev, ptWrap->u.tMsc.ucLun,
							   pulSectors, pulSectorSz, &sERROR );
	if( iRet != USB_MSC_OK ) {
		goto EXT;
	}

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Read data by sector
	It reads a number of sectors specified by uscont from the number specified by ulstart,
	and then writes them in a memory indicated by pucbuf.
	Set a value of 1 or more to the number of sectors, count.
	When 0 is set, it receives an error.
	No processing result will return until reading is completed or an error occurs
	since this function operates in blocking mode.

	\param  ulStart			Start sector number
	\param  usCount			A number of sectors
	\param  pucBuf			Storage buffer pointer of read data
	\retval E_USB_OK		Succeeds in reading　
	\retval E_USB_ERROR		Fails in reading
 */
/* ------------------------------------------------------------------------ */
int16_t USBReadSector( uint32_t ulStart, uint16_t usCount, uint8_t* pucBuf )
{
	int16_t iRet;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	/* Start exclusive operations */
	iRet = iWaiSem( SEM_WAIT_TIME );
	ERROR_IF_WITHCODE( iRet != E_USB_OK, EXT, &sERROR, USB_MSC_IN_USE );

	/* Execute reading blocking */
	iRet = iReadSector( ptWrap, ulStart, usCount, pucBuf );

	/* Terminate exclusive operations */
	vRelSem();

EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Write data by sector
	It writes contents of a memory indicated by pucbuf in a number of sectors
	specified by uscont from the number specified by ulstart.
	Set a value of 1 or more to the number of sectors, uscount.
	when 0 is set, it receives an error.
	No processing result will return until writing is completed or an error occurs
	since this function operates in blocking mode.

	\param  ulStart			Start sector number
	\param  usCount			A number of sectors
	\param  pucBuf			Storage buffer pointer of written data
	\retval E_USB_OK		Succeeds in writing　
	\retval E_USB_ERROR		Fails in writing
 */
/* ------------------------------------------------------------------------ */
int16_t USBWriteSector( uint32_t ulStart, uint16_t usCount, uint8_t* pucBuf )
{
	int16_t iRet;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	/* Start exclusive operations */
	iRet = iWaiSem( SEM_WAIT_TIME );
	ERROR_IF_WITHCODE( iRet != E_USB_OK, EXT, &sERROR, USB_MSC_IN_USE );

	/* Execute writing blocking */
	iRet = iWriteSector( ptWrap, ulStart, usCount, pucBuf );

	/* Terminate exclusive operations */
	vRelSem();

EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! SCSI command
	It issues to a device an SCSI command expressed by an argument, ptCmdBlk.
	No processing result will return until the command execution is completed or an error occurs
	since this function operates in blocking mode.	
	Unlike other functions, an operating logic unit of an SCSI command issued by this function
	is specified to a structure to be passed to an argument.
	As for in this function, any specification of target logic units made by USBChangeTargetLun()
	will be ignored.

	\param  ptCmdBlk		SCSI Command Block
	\retval E_USB_OK		Succeeds in SCSI command response
	\retval E_USB_ERROR		Fails in SCSI command response
 */
/* ------------------------------------------------------------------------ */
int16_t USBIoCtrl( usb_MSC_typeCommandBlock* ptCmdBlk )
{
	int16_t iRet;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	/* Start exclusive operations */
	iRet = iWaiSem( SEM_WAIT_TIME );
	ERROR_IF_WITHCODE( iRet != E_USB_OK, EXT, &sERROR, USB_MSC_IN_USE );

	/* SCSI command */
	iRet = iIoCtrl( ptWrap, ptCmdBlk );

	/* Terminate exclusive operations */
	vRelSem();

EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Check device status
	It gets device status.
	It returns device status to *piStatus.
	
	\param  piStatus		Storage address of device status
	\retval E_USB_OK		Succeeds in getting
	\retval E_USB_ERROR		Parameter (piStatus) error
 */
/* ------------------------------------------------------------------------ */
#if(0)
int USBGetStatus( int* piStatus )
#else
int16_t USBGetStatus( int16_t* piStatus )
#endif
{
	uint16_t usLuState = 0;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	if( piStatus == NULL ) {
		return( E_USB_ERROR );
	}

	usb_MSC_vGetStatus( ptWrap->ulIdDev, piStatus, &usLuState );

	if( *piStatus == USB_MSC_OK
		&& (usLuState & (1 << ptWrap->u.tMsc.ucLun)) == 0 ) {
		*piStatus = USB_MSC_NOT_READY;
	}

	return( E_USB_OK );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Disconnect a selected device
	It disconnects a device of a number specified by the argument, ucDevNo.
	Operations are same as those of USBDisconnect() except that it specifies a device.

	\param  ucDevNo			Device number
	\retval E_USB_OK		Succeeds in disconnection, or yet to be connected
	\retval E_USB_ERROR		Fails in disconnection
 */
/* ------------------------------------------------------------------------ */
int16_t USBDisconnectDevice( uint8_t ucDevNo )
{
	int16_t iRet = E_USB_ERROR;
	uint16_t usLuState = 0;
	typeUsbWrapper* ptWrap;

	ERROR_IF_WITHCODE( ucDevNo >= NUM_WRAPS, EXT, &sERROR, USB_MSC_PARAMETER );

	ptWrap = &ptUSB_WRAP[ucDevNo];

	usb_MSC_vGetStatus( ptWrap->ulIdDev, NULL, &usLuState );
	if( (usLuState & (1 << ptWrap->u.tMsc.ucLun)) != 0 ) {
		/* TEST UNIT READY */
		iRet = USBCheckLu( ptWrap->u.tMsc.ucLun );
		if( iRet != E_USB_OK ) {
			goto EXT;
		}
	}

	/* Start exclusive operations */
	iRet = iWaiSem( SEM_WAIT_TIME );
	ERROR_IF_WITHCODE( iRet != E_USB_OK, EXT, &sERROR, USB_MSC_IN_USE );

	/* Disconnect */
	iRet = iDisconnectDevice( ptWrap, NULL );

	/* Terminate exclusive operations */
	vRelSem();

EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Disconnect a device
	It disconnects a operating target device.
	Call this function before removing a device, and disconnect a device.
	When this function is operated properly, a callback function
	for removing a device will be called.
	It is impossible to call this function during a communication is made.

	\param  -
	\retval E_USB_OK		Succeeds in disconnection or yet to be connected
	\retval E_USB_ERROR		Fails in disconnection
 */
/* ------------------------------------------------------------------------ */
int16_t USBDisconnect( void )
{
	int16_t iRet;

	iRet = USBDisconnectDevice( ucUSB_WRAP );

	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Reconnect a selected device
	It reconnects a device of the number specified by the argument, ucDevNo.
	Operations are same as those of USBDisconnect() except that it specifies a device.
	

	\param  ucDevNo			Device number
	\retval E_USB_OK		Succeeds in reconnection
	\retval E_USB_ERROR		Fails in reconnection
 */
/* ------------------------------------------------------------------------ */
int16_t USBReconnectDevice( uint8_t ucDevNo )
{
	int16_t iRet = E_USB_ERROR;

	ERROR_IF_WITHCODE( ucDevNo >= NUM_WRAPS, EXT, &sERROR, USB_MSC_PARAMETER );

	/* Start exclusive operations */
	iRet = iWaiSem( SEM_WAIT_TIME );
	ERROR_IF_WITHCODE( iRet != E_USB_OK, EXT, &sERROR, USB_MSC_IN_USE );

	/* Reconnect */
	iRet = iReconnectDevice( &ptUSB_WRAP[ucDevNo] );

	/* Terminate exclusive operations */
	vRelSem();

 EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Reconnect a device
	It carries out operations equivalent to reinserting a device
	by handling on/off of the power of a hub (root hub) to which a device is inserted.
	This function is used as the last measure when a device returns no response.
	Even though it is during communications are underway, they are cancelled
	and a reconnection will be carried out.

	\param  -
	\retval E_USB_OK		Succeeds in reconnection　
	\retval E_USB_ERROR		Fails in reconnection　
 */
/* ------------------------------------------------------------------------ */
int16_t USBReconnect( void )
{
	int16_t iRet;

	iRet = USBReconnectDevice( ucUSB_WRAP );

	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get device ID
	It gets an operation target device ID used in a wrapper,
	receiving it from an MSC driver.
	By using a device ID gotten by this API,
	using an MSC driver directly with no wrapper becomes possible.
	
	\param  -
	\retval Device ID（a devivce ID managed by a USB host driver）
 */
/* ------------------------------------------------------------------------ */
uint32_t USBGetDeviceID( void )
{
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];
	return( ptWrap->ulIdDev );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get error code
	It is possible to get the reason for errors when calling other APIs turns out an error.
	Values that can be gotten by this API may be either error codes of a USB host driver
	or MSC driver depending on the position where an error occurs.

	\param  -
	\retval Error Code
 */
/* ------------------------------------------------------------------------ */
int16_t USBGetErrorCode( void )
{
	return( sERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Get sense key
	When an error code gotten by USBGetErrorCode() is USB_MSC_SCSI_CMD_FAILED
	(when the result of an SCSI command is an error), it becomes possible to get
	sense key (detaisl of an SCSI command error).

	\param  -
	\retval SCSI Command Error Code
 */
/* ------------------------------------------------------------------------ */
uint8_t USBGetSenseKey( void )
{
	uint8_t ucSenseKey = USB_MSC_SK_UNKNOWN;
	typeUsbWrapper* ptWrap = &ptUSB_WRAP[ucUSB_WRAP];

	usb_MSC_iGetSenseKey( ptWrap->ulIdDev, &ucSenseKey, NULL );

	return( ucSenseKey );
}
/*! @} */ /* GlobalFunctions */
/* ************************************************************************ */

/*! @} */ /* MSCWrapper */
/* ************************************************************************ */

/* ************************************************************************ */
/* --- End of File --- */
