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

/*! \file main.c
	\brief Sample Code of USB Host MSC Wrapper

	\author TOSHIBA CORPORATION
	\date 2007/06/15 modify original file

 */
/* ************************************************************************** */

/*
	Test code
*/

#include "system_def.h"

#include "msctolsapi2.h"
#include "usb_timer.h"
#include "usb.h"

#include "DebugAPI.h"
#include "Debug_hw.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>



#include "usb_intr_hw.h"
/*! After converting 4-byte data into character codes, output them by using a UART. */

static INT16_t usb_init_process(void);
static INT16_t usb_connect_check(void);

#pragma section="HC_RAM_MSCAPI"

//#define BUF_SZ  (512 * 4)					/*!< Work Buffer Size */
#define BUF_SZ  (512 * 1)					/*!< Work Buffer Size */
static UINT8_t pucBuffer1[BUF_SZ] @ "HC_RAM_MSCAPI";	/*!< Work Buffer 1 */
static UINT8_t pucBuffer2[BUF_SZ] @ "HC_RAM_MSCAPI";	/*!< Work Buffer 2 */

UINT32_t ulDBG_COUNT = 0;

uint8_t ucStrDisp[32];					/*!< Work Buffer for Uart */
int8_t ucProdName[128];					/*!< Work Buffer for ProductName */
int8_t ucManuName[128];					/*!< Work Buffer for ManufactureName */
usb_device_descriptor_t tdescriptor;	/*!< Work Buffer for Descriptor */

int8_t cUSB_DRIVER_STATE;				/*!< Driver Error Check Buffer */


static void usbh_main( void );


/* ************************************************************************ */
/*! \addtogroup SampleFunctions
 *  @{
 */

/* ************************************************************************ */
/*! \addtogroup LunTestFunctions
 *  @{
 */
/* ======================================================================== */
/*! Select LUN
	Select a target logic unit.
	When failed, it retries after waiting one second.
	It retries switching up to five times.

	\param  ucLun			Target logic unit number (LUN)
	\retval E_USB_OK		Succeeds in switching
	\retval E_USB_ERROR		Fails in switching
 */
/* ------------------------------------------------------------------------ */
static INT16_t iSelectLun( UINT8_t ucLun )
{
	INT16_t i, iRet = 0, iStatus = USB_MSC_OK, iError;
	UINT8_t ucSenseKey;

	/* Set LUN */
	/* When an initialization made by UNIT_ATTENTION fails, retry after waiting one second. */
	for( i = 0; i < 5; i++ ) {
		iRet = USBChangeTargetLun( ucLun );
		if( iRet == E_USB_OK ){
			break;
		}
		else{
			iError = USBGetErrorCode();
			ucSenseKey = USBGetSenseKey();
			if( iError != USB_MSC_SCSI_CMD_FAILED
				|| ucSenseKey != USB_MSC_SK_UNIT_ATTENTION ){
				goto EXT;
			}
		}
		usb_TIMER_vWaiMsec( 1000 );
	}

EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Compare after reading twice
	Reading the same sector data, it compares data contents.

	\param  ulStart			Start sector number
	\param  usReadSect		A number of sectors
	\retval E_USB_OK		Compared contents correspond each other
	\retval E_USB_ERROR		Fails in reading, or data does not correspond each other
 */
/* ------------------------------------------------------------------------ */
static INT16_t iReadAndCompare( UINT32_t ulStart, UINT16_t usReadSect )
{
	INT16_t iRet;

	/* READ 1 */
	memset( pucBuffer1, 0x00, BUF_SZ );
	iRet = USBReadSector( ulStart, usReadSect, pucBuffer1 );
	if( iRet != E_USB_OK ){
		goto EXT;
	}

	/* READ 2 */
	memset( pucBuffer2, 0xff, BUF_SZ );
	iRet = USBReadSector( ulStart, usReadSect, pucBuffer2 );
	if( iRet != E_USB_OK ){
		goto EXT;
	}

	/* Compare */
	if( memcmp( pucBuffer2, pucBuffer1, BUF_SZ ) != 0 )	{
		if( memcmp( pucBuffer2, pucBuffer1, BUF_SZ ) != 0 )	{
			iRet = E_USB_ERROR;
			goto EXT;
		}
	}

EXT:
	return( iRet );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Multiple LUN reading test
	It gets a number of logic unit of a target device.
	It returns STALL to GetMaxLUN depending on a device.
	In this case, it operates with MaxLUN as 1 thereafter.
	It gets sector information, reads data of 2 kbytes from a boot sector twice,
	and then compares the contents.

	\param  -
	\retval E_USB_OK		Succeeds in LUN test (Compared contents correspond each other)
	\retval E_USB_ERROR		Fails in LUN test
 */
/* ------------------------------------------------------------------------ */
static INT16_t iMultiLunTest( void )
{
	INT16_t iRet, iError;
	UINT32_t ulSectors = 0, ulSectSz = 0;
	UINT16_t usReadSect;
	UINT8_t ucLun, ucNumLus = 0, ucSenseKey = USB_MSC_SK_NO_SENSE;

	/* Get a number of LUs */
	iRet = USBGetNumLus( &ucNumLus );
	if( iRet != E_USB_OK ){
		ucNumLus = 1;
	}

	for( ucLun = 0; ucLun < ucNumLus; ucLun++ )	{
		/* Selet and initialize a target LUN */
		iRet = iSelectLun( ucLun );
		if( iRet != E_USB_OK ){
			/* Transit to the next LUN if NOT_READY */
			iError = USBGetErrorCode();
			ucSenseKey = USBGetSenseKey();
			if( iError == USB_MSC_SCSI_CMD_FAILED
				&& ucSenseKey == USB_MSC_SK_NOT_READY ){
				continue;
			}
			OutStr((UINT8_t*)"Error iSelectLun\r\n");
			goto EXT;
		}

		/* Get sector information */
		iRet = USBGetSectorInf( &ulSectors, &ulSectSz );
		if( iRet != E_USB_OK ){
			iError = USBGetErrorCode();
			OutStr((UINT8_t*)"Error USBGetSectorInf\r\n");
			goto EXT;
		}
		usReadSect = (UINT16_t)(BUF_SZ / ulSectSz);

		/* Read */
		iRet = iReadAndCompare( 0, usReadSect );
		if( iRet != E_USB_OK ){
			iError = USBGetErrorCode();
			OutStr((UINT8_t*)"Error iReadAndCompare\r\n");
			goto EXT;
		}

		ulDBG_COUNT++;
	}

	return( E_USB_OK );
EXT:
	return( E_USB_ERROR );
}
/* ======================================================================== */

/* ======================================================================== */
/*! Multiple devices reading test
	It checks a connection status of an MSC device.
	It waits there until a connection is made.
	When a connection is made, it carries out a multiple LUN test (iMultiLunTest) in order.

	\param  -
	\retval E_USB_OK		Succeeds in all device checks
	\retval E_USB_ERROR		Fails in a device check
 */
/* ------------------------------------------------------------------------ */
static INT16_t iMultiDeviceTest( void )
{
	INT16_t iRet = E_USB_ERROR;
	UINT8_t ucDev;
	UINT32_t ulDevState = 0;

	/* Wait for insertion */
	do {
		/* Get a device connection status */
		USBGetDeviceState( &ulDevState );
	} while( ulDevState == 0 );

	/* Scan all devices */
	for( ucDev = 0; ucDev < 32; ucDev++ ){
		USBGetDeviceState( &ulDevState );
		if( (ulDevState & (1UL << ucDev)) != 0 ){
			/* Set a target device */
			iRet = USBChangeTargetDevice( ucDev );
			if( iRet != E_USB_OK ){
				break;
			}

			/* Multiple LUN test */
			iRet = iMultiLunTest();
			if( iRet != E_USB_OK ){
				break;
			}
		}
	}

	return( iRet );
}
/* ======================================================================== */

/*! @} */ /* LunTestFunctions */
/* ************************************************************************ */

/* ************************************************************************ */
/*! \addtogroup CallBackFunctions
 *  @{
 */

/* ------------ Status Notification Function ------------------ */

/* ======================================================================== */
/*! Status notification of device connection
	It is called when a USB device is connected.

	\param  notID		Device notification ID
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void deviceConnected(uint32_t notID)
{
	OutStr((UINT8_t*)"Device Connect\r\n");
	MakeAddrString((INT8_t*)ucStrDisp, notID);
	OutStr((UINT8_t*)"notID = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n\r\n");
	OutStr((UINT8_t*)">>");
}

/* ======================================================================== */

/* ======================================================================== */
/*! Status notification of device disconnection
	It is called when a USB device is disconnected.

	It outputs the device ID information by using a UART.

	\param  notID		Device notification ID
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void deviceDisconnected(uint32_t notID)
{
	OutStr((UINT8_t*)"Device Disconnect\r\n");
	MakeAddrString((INT8_t*)ucStrDisp, notID);
	OutStr((UINT8_t*)"notID = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n\r\n");
	OutStr((UINT8_t*)">>");
}
/* ======================================================================== */

/* ======================================================================== */
/*! Notification of recognitions made by a bus driver
	It is called when a USB host driver recognizes a connected device.

	\param  notID		Device notification ID
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void deviceIdentified(uint32_t notID)
{
}
/* ======================================================================== */

/* ======================================================================== */
/*! Notification of a negrect of device by a bus driver
	It notifies that a USB host driver ignores a connected device.
	
	It outputs an ignored dvice ID information by using a UART.

	\param  notID		Device notification ID
	\param  err		Error information about a neglect of a device
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void deviceIgnored(uint32_t notID, usbd_status err)
{
	OutStr((UINT8_t*)"Device Ignored\r\n");
	MakeAddrString((INT8_t*)ucStrDisp, notID);
	OutStr((UINT8_t*)"notID = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n\r\n");
	OutStr((UINT8_t*)">>");
}
/* ======================================================================== */

/* ======================================================================== */
/*! Notification of attached class driver
	It notifies the success of an MSC driver connection.

	It outputs a connected MSC device information by using a UART.

	\param  notID		Device notification ID
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void deviceAttached(uint32_t notID)
{
	INT16_t iRet;
	uint8_t portNo=0x55;
	int8_t speed =0x55;
	uint8_t addr  =0x55;
	int8_t *pucProdName;
	int8_t *pucManuName;
	usb_device_descriptor_t* ptdescriptor;
	int8_t cPowerType=0x55;
	uint16_t usMaxPower = 0x8000;

	UINT32_t ulDevState = 0;

	OutStr((UINT8_t*)"Device Attached\r\n");

	MakeAddrString((INT8_t*)ucStrDisp, notID);
	OutStr((UINT8_t*)"notID = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");


	USBGetDeviceState( &ulDevState );
	MakeAddrString((INT8_t*)ucStrDisp, ulDevState);
	OutStr((UINT8_t*)"DeviceState = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");


	iRet = usb_USBD_Notify_iGetPortNumber(notID, &portNo);
	if(iRet != USB_OK){
		goto EXT;
	}
	MakeAddrString((INT8_t*)ucStrDisp, (UINT32_t)portNo);
	OutStr((UINT8_t*)"portNo = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");


	iRet = usb_USBD_Notify_iGetDeviceAddress(notID, &addr);
	if(iRet != USB_OK){
		goto EXT;
	}
	MakeAddrString((INT8_t*)ucStrDisp, (UINT32_t)addr);
	OutStr((UINT8_t*)"addr = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");

	ptdescriptor = &tdescriptor;
	iRet = usb_USBD_Notify_iGetDeviceDesc(notID, &ptdescriptor);
	if(iRet != USB_OK){
		goto EXT;
	}
	MakeAddrString((INT8_t*)ucStrDisp, (UINT32_t)ptdescriptor->bDeviceClass);
	OutStr((UINT8_t*)"bDeviceClass = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");

	MakeAddrString((INT8_t*)ucStrDisp,
				   (UINT32_t)ptdescriptor->bDeviceProtocol);
	OutStr((UINT8_t*)"bDeviceProtocol = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");

	MakeAddrString((INT8_t*)ucStrDisp,
				   (UINT32_t)(*(UINT16_t*)ptdescriptor->idVendor));
	OutStr((UINT8_t*)"idVendor = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");

	MakeAddrString((INT8_t*)ucStrDisp, (UINT32_t)
				   (*(UINT16_t*)ptdescriptor->idProduct));
	OutStr((UINT8_t*)"idProduct = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");

	MakeAddrString((INT8_t*)ucStrDisp, (UINT32_t)
				   (*(UINT16_t*)ptdescriptor->bcdDevice));
	OutStr((UINT8_t*)"bcdDevice = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");

	MakeAddrString((INT8_t*)ucStrDisp, (UINT32_t)ptdescriptor->iSerialNumber);
	OutStr((UINT8_t*)"iSerialNumber = ");
	OutStr(ucStrDisp);
	OutStr((UINT8_t*)"\r\n");


	pucProdName = ucProdName;
	iRet = usb_USBD_Notify_iGetProductName(notID, &pucProdName);
	if(iRet != USB_OK){
		goto EXT;
	}
	OutStr((UINT8_t*)"ProductName = ");
	OutStr((UINT8_t*)pucProdName);
	OutStr((UINT8_t*)"\r\n");

	pucManuName = ucManuName;
	iRet = usb_USBD_Notify_iGetManufacturerName(notID, &pucManuName);
	if(iRet != USB_OK){
		goto EXT;
	}
	OutStr((UINT8_t*)"ManufactureName = ");
	OutStr((UINT8_t*)pucManuName);
	OutStr((UINT8_t*)"\r\n");

EXT:
	OutStr((UINT8_t*)"\r\n\r\n");
	OutStr((UINT8_t*)">>");
}
/* ======================================================================== */

/* ======================================================================== */
/*! HCD unrecoverable error occurrence
	It is called when unrecoverable error occurs at a USB host controller.
	At this time, it is necessasry to terminate a USB driver once and retry
	operations from initialization processing.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void vUnrecoverableErr( void )
{
	cUSB_DRIVER_STATE = (int8_t)-1;
}
/* ======================================================================== */

/*! @} */ /* CallBackFunctions */
/* ************************************************************************ */

/* ************************************************************************ */
/*! \addtogroup MSCWrapperTestFunctions
 *  @{
 */
/* ======================================================================== */
/*! USB test
	It initializes a USB driver.
	As succeeds in initialization, it monitors connection status of an MSC device.
	If the device is connected newly, it carries out a LUN test.
	When an unrecoverable error occurs at the host, it tris a return processing.

	PC<7> USBOCn
	PC<6> USBPON

				7	6
	GPIOCFR1	0	0
	GPIOFR2		1	1
	GPIOCIE		0	0
	GPIOCODE	0	0

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void sample_usbh( void )
{
	UINT32_t reg_data;
	UINT32_t reg_data_syscr8;

	UINT32_t gpiot_data, gpiot_buf, i;

	uart1_init();
	uart1_start_tx(NULL);		/* start uart1 tx	*/
	uart1_start_rx(dbgIntRx);	/* start uart1 rx	*/
	dbgInit();					/* init DebugIP		*/

	/* USBOCn(PC<7>), USBPON(PC<6>)	*/
	reg_data = GPIOCDIR & 0x0000003F;
	GPIOCDIR = reg_data;
	reg_data = GPIOCFR1 & 0x0000003F;
	GPIOCFR1 = reg_data;
	reg_data = GPIOCFR2 & 0x0000003F;
	reg_data |= 0x000000C0;
	GPIOCFR2 = reg_data;;
	reg_data = GPIOCIE & 0x0000003F;
	GPIOCIE = reg_data;
	reg_data = GPIOCODE & 0x0000003F;
	GPIOCODE = reg_data;;

	/* simple chattering	*/
	gpiot_data = 0x00000000;
	gpiot_buf  = GPIOTDATA & 0x00000080;
	for(;;) {
		for(i = 0; i < 100; i++) {
			/* do nothing */
		}
		gpiot_data  = GPIOTDATA & 0x00000080;
		if(gpiot_data == gpiot_buf) {
			break;
		}
		else {
			gpiot_buf = gpiot_data;
		}
	}
	
	/* set USBH clock	*/
	reg_data_syscr8	= SYSCR8 & ~(CSYSCR8_Reserved_MASK | CSYSCR8_USBH_CLKSEL_MASK);
	if( (gpiot_data & 0x00000080) == 0x00000000 ) {
		/* use internal clock	*/
		reg_data_syscr8 |= CSYSCR8_USBH_CLKSEL_PLL_div_4;
	}
	else {
		reg_data = GPIOTFR1 & 0xFFFFFF7F;
		reg_data |= 0x00000080;
		GPIOTFR1 = reg_data;
		reg_data = GPIOTFR2 & 0xFFFFFF7F;
		GPIOTFR2 = reg_data;

		/* use external clock	*/
		reg_data_syscr8 |= CSYSCR8_USBH_CLKSEL_X1USB;
	}
	SYSCR8 = reg_data_syscr8;

	reg_data	= CLKCR5;
	reg_data	&= ~(CCLKCR5_Reserved_MASK | CCLKCR5_USBH_CLKEN_MASK);
	reg_data	|= (CCLKCR5_Reserved | CCLKCR5_USBH_CLKEN_ENABLE);
	CLKCR5		= reg_data;

	/* set USBH interrupt	*/
	reg_data = VICINTSELECT & ~CInterruptUSBH_MASK;
	VICINTSELECT = reg_data;					/* Select IRQ interrupt		*/
	VICVECTADDR27 = (UINT32_t)int_usbhost;		/* Set interrupt function	*/
	HCBCR0 = 0x00000000;                /* OHCI ON */
//	HCBCR0 = 0x00000001;                /* OHCI ON */

	usbh_main();
	for(;;);
}
/* ======================================================================== */

/* ======================================================================== */
/*! USB test
	It initializes a USB driver.
	As succeeds in initialization, it monitors connection status of an MSC device.
	If the device is connected newly, it carries out a LUN test.
	When an unrecoverable error occurs at the host, it tris a return processing.

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
static void usbh_main( void )
{
	volatile INT16_t iRet;
	INT16_t iStat = USB_MSC_NO_DEVICE;
	UINT8_t ucDev;
	UINT32_t ulDevState = 0;
	UINT8_t i,j;
	UINT32_t reg_data;

	iRet = usb_init_process();
	if( iRet != E_USB_OK ) {
		goto EXT;
	}

#if(0)
	/* Mutliple devices and LUN tests */
	iRet = iMultiDeviceTest();
#endif
	for(;;){
		if(cUSB_DRIVER_STATE == (int8_t)-1){
			OutStr((UINT8_t*)"UnrecoverableErr");
			OutStr((UINT8_t*)">>");
			USBFin();
			iRet = usb_init_process();
			if( iRet != E_USB_OK ) {
				goto EXT;
			}
		}
		else{
			iRet = usb_connect_check();
			if( iRet != E_USB_OK ) {
				OutStr((UINT8_t*)"Connect Check Error\r\n");
			}
//			dbgCmdHandle();
		}
	}

EXT:
	/* Cancel all devices */
	USBGetDeviceState( &ulDevState );
	for( ucDev = 0; ucDev < 32; ucDev++ ){
		if( (ulDevState & (1UL << ucDev)) != 0 ){
			USBDisconnectDevice( ucDev );
		}
	}

	/* Terminate */
	USBFin();

	/* for installing a break point */
	if( iRet != E_USB_OK ) {
		iRet = E_USB_ERROR;
	}

#if(1)
	OutStr((UINT8_t*)"USB Init Error");
	for(;;){
//		dbgCmdHandle();
	}
#endif
}
/* ======================================================================== */

/* ======================================================================== */
/*! Overall operations regarding a USB initialization
	It carries out a USb initialization necessary to access an MSC device.
	It notifies an unrecoverable error after succeeding in initialization.

	\param  -
	\retval E_USB_OK		Succeeds in MSC wrapper initialization
	\retval E_USB_ERROR		Fails in MSC wrapper initialization
 */
/* ------------------------------------------------------------------------ */
static INT16_t usb_init_process(void)
{
	USBD_typeNotification tNotify = { NULL, NULL, NULL, NULL, NULL };
	volatile INT16_t iRet;

	/* Registration of status notification function */
	tNotify.fpConnected = deviceConnected;
	tNotify.fpDisconnected = deviceDisconnected;
	tNotify.fpIdentified = deviceIdentified;
	tNotify.fpAttached = deviceAttached;
	tNotify.fpIgnored = deviceIgnored;

	/* Initialize blocking mode */
	iRet = USBInit( NULL, &tNotify );
	if( iRet == E_USB_OK ){
		/* Notify HCD unrecoverable error */
		cUSB_DRIVER_STATE = (int8_t)1;
		iRet = usb_USBD_iRegisterUnrecovErrorCallback( vUnrecoverableErr, NULL );
	}
	return iRet;
}
/* ======================================================================== */

/* ======================================================================== */
/*! Connection check
	It checks an MSC device connection.
	If an MSC device is connected newly, it carries out a LUN test.

	\param  -
	\retval E_USB_OK		Succeeds in LUN test
	\retval E_USB_ERROR		Fails in LUN test
 */
/* ------------------------------------------------------------------------ */
static INT16_t usb_connect_check(void)
{
	INT16_t iRet = E_USB_OK;
	static UINT32_t ulDevState = 0;
	static UINT32_t ulDevStateOld = 0;
	UINT32_t ulDevWork;
	UINT8_t ucDev;

	USBGetDeviceState( &ulDevState );

	if(ulDevStateOld != ulDevState) {
		ulDevWork = ulDevState ^ ulDevStateOld;
		ulDevWork = ulDevWork & ulDevState;
		ulDevStateOld = ulDevState;

		if(ulDevWork != 0) {
			for( ucDev = 0; ucDev < 32; ucDev++ ){
				if( (ulDevState & (1UL << ucDev)) != 0 ){
					/* Set a target device */
					iRet = USBChangeTargetDevice( ucDev );
					if( iRet != E_USB_OK ){
						OutStr((UINT8_t*)"Error USBChangeTargetDevice\r\n");
						break;
					}

					/* Test multiple LUNs */
					iRet = iMultiLunTest();
					if( iRet != E_USB_OK ){
						OutStr((UINT8_t*)"Error iMultiLunTest\r\n");
						break;
					}
				}
			}
		}
	}

	return iRet;
}
/* ======================================================================== */
/*! @} */ /* MSCWrapperTestFunctions */
/* ************************************************************************ */


/*! @} */ /* SampleFunctions */
/* ************************************************************************ */

/* --- End of File --- */

