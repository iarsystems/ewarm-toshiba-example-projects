/*
 * COPYRIGHT (C) 2018
 * TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION
 * ALL RIGHTS RESERVED
 *
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * ELECTRONIC DEVICES & STORAGE CORPORATION MAKES NO OTHER WARRANTY OF ANY
 * KIND, WHETHER EXPRESS, IMPLIED OR, STATUTORY AND DISCLAIMS ANY AND ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, SATISFACTORY QUALITY, NON
 * INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA ELECTRONIC
 * DEVICES & STORAGE CORPORATION RESERVES THE RIGHT TO INCORPORATE
 * MODIFICATIONS TO THE SOURCE CODE IN LATER REVISIONS OF IT, AND TO MAKE
 * IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR THE PRODUCTS OR
 * TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 *
 * TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION SHALL NOT BE LIABLE FOR
 * ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR
 * USE OF THE SOURCE CODE OR ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO,
 * LOST REVENUES, DATA OR PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL NATURE, PUNITIVE DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS
 * ARISING OUT OF OR IN CONNECTION WITH THIS AGREEMENT, OR BEING UNUSABLE,
 * EVEN IF ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES AND
 * WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON WARRANTY, CONTRACT, TORT,
 * NEGLIGENCE OR OTHERWISE.
 */
/* VERSION : 20180831A */
/* TARGET  : TC35680-ROM002 */

/*****************************************************************************/
#ifndef HOST_API_H_
#define HOST_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include "TC35680.h"

#define SERIES_TC35680 (0x80) /* TC35680 or TC35681 */
#define TC3568X_SERIES SERIES_TC35680
#define TC3568X_ROM_VER 2

/****************************************************************************
 Compiler dependent settings
*****************************************************************************/
#if defined __IAR_SYSTEMS_ICC__
    extern void __iar_data_init3(void);
    #define DATA_INIT() __iar_data_init3();
    #define C2_ENTRY _Pragma("location=\"C2_Entry\"")
#elif defined __UVISION_VERSION
    #define DATA_INIT()
    #define C2_ENTRY __attribute__((section("C2_Entry")))
#elif defined __GNUC__
    extern void data_init(void);
    #define DATA_INIT() data_init()
    #define C2_ENTRY __attribute__((section("C2_Entry")))
#else
    #define DATA_INIT()
    #define C2_ENTRY
#endif

/****************************************************************************
 type declaration
*****************************************************************************/
typedef     uint32_t                CMN_ID;
typedef     uint32_t                CMN_ER;

/****************************************************************************
 macro declaration
*****************************************************************************/
/* general */
#ifndef NULL
#define NULL                            ((void *)0)
#endif /* NULL */
#ifndef FALSE
#define FALSE                           (0)
#endif /* FALSE */
#ifndef TRUE
#define TRUE                            (1)
#endif /* TRUE */

/* os system call return mode */
#define CMN_INFINITE                    (0xFFFF)    /* return immediately       */
#define CMN_NOWAIT                      (0x0000)    /* return after complate    */

/* system call return value */
#define RET_OS_OK               (0)     /* normal completion                    */
#define RET_OS_SYS              (-1)    /* system error                         */
#define RET_OS_PAR              (-33)   /* parameter error                      */
#define RET_OS_OBJ              (-63)   /* invalid object state                 */
#define RET_OS_TMOUT            (-85)   /* polling failure or timeout exceeded  */

/****************************************************************************
 structure declaration
*****************************************************************************/
/* System common header structure */
typedef struct {
    uint8_t     MsgHeader[4];       /* Used by OS                    */
    int16_t     nMbxID;             /* Destination Mail box ID       */
    uint16_t    wModuleID;          /* Sender Module ID              */
    int16_t     nMemID;             /* Memory ID of this message     */
    uint16_t    wMemFlags;          /* sizeof(CMN_MSG)               */
    uint32_t    dwLength;           /* Lenth of message data         */
    uint32_t    dwUserData;         /* Arbitrary data 1              */
    uint32_t    dwUserData2;        /* Arbitrary data 2              */
} CMN_MSG;

/* TCU Command struct */
typedef struct {
    CMN_MSG     cmn;                /* Common msg */
    uint8_t     length_l;           /* TCU command length(lower 8bit) */
    uint8_t     length_h;           /* TCU command length(mid 8bit) */
    uint8_t     high_length;        /* TCU command length(upper 8bit) */
    uint8_t     service_id;         /* TCU command section header Service ID */
    uint8_t     opcode;             /* TCU command section header Operation Code */
    uint8_t     parameter_length_l; /* TCU parameter length of cmd header (upper 8bit) */
    uint8_t     parameter_length_h; /* TCU parameter length of cmd header (lower 8bit) */
    uint8_t     parameter[];        /* Parameter data. */
} SR_FAT_MSG;

/****************************************************************************
 constant value declaration
*****************************************************************************/
/* API return status */
typedef enum {
    RET_API_NORMAL,                   /* 0x00:command successfull       */
    RET_API_INVALID_PARAMETER,        /* 0x01:command failure           */
    RET_API_EEPROM_ALREADY_ENABLE,    /* 0x02:EEPROM already enable     */
    RET_API_EEPROM_UNINITIALIZED,     /* 0x03:EEPROM uninitialized      */
    RET_API_EEPROM_FAILURE,           /* 0x04:EEPROM broke down         */
    RET_API_SYSTEM_ERROR,             /* 0x05:system error              */
    RET_API_GENERAL_DEVICE_FAILURE,   /* 0x06:General device broke down */
    RET_API_BITMAP_FULL,              /* 0x07:bitmap full               */
} RET_API;

/* Result of memory allocation used for UART */
typedef enum {
    E_ALLOC_OK = 0,             /* Memory allocation success                   */
    E_SIZE_ERROR,               /* Failed because requested size is invalid    */
    E_EMPTY_ERROR,              /* Failed because there is no available memory */
    E_TYPE_ERROR                /* Failed because PROTOCOL_MSG_TYPE is invalid */
} ALLOC_RESULT;

/* API return value of UART_IF */
typedef enum {
    U_RESULT_OK = 0,            /* Success               */
    U_RESULT_WAIT,              /* Wait                  */
    U_RESULT_TIMEOUT,           /* Timeout               */
    U_RESULT_NG                 /* Failed                */
} U_RESULT;

/* UART Protocol Fixed length memory type */
typedef enum {
    PROTOCOL_RX_HEADER = 0,     /* 0x00:Header Receive Buffer                 */
    PROTOCOL_RX_CMD,            /* 0x01:HCI Command Receive Buffer            */
    PROTOCOL_RX_ACL,            /* 0x02:ACL Data Receive Buffer               */
    PROTOCOL_RX_SCO,            /* 0x03:SCO Data Receive Buffer               */
    PROTOCOL_RX_EVT,            /* 0x04:HCI Event Receive Buffer              */
    PROTOCOL_RX_CTL,            /* 0x05:Special Frame Receive Buffer          */
    PROTOCOL_RX_FAT,            /* 0x06:FAT Command, FAT Event Receive Buffer */
    PROTOCOL_RX_TRACE_DATA,     /* 0x07:Trace Data Receive                    */
    PROTOCOL_RX_TRACE_ERR,      /* 0x08:Trace Error Receive                   */

    PROTOCOL_TX_HEADER = 0x80,  /* 0x80:Unused                                */
    PROTOCOL_TX_CMD,            /* 0x81:HCI Command Send Buffer               */
    PROTOCOL_TX_ACL,            /* 0x82:ACL Data Send Buffer( And FAT Command, FAT Event)*/
    PROTOCOL_TX_SCO,            /* 0x83:SCO Data Send Buffer                  */
    PROTOCOL_TX_EVT,            /* 0x84:HCI Event Send Buffer                 */
    PROTOCOL_TX_CTL,            /* 0x85:Special Frame Send Buffer             */
    PROTOCOL_TX_FAT,            /* 0x86:FAT Command, FAT Event Send Buffer    */
    PROTOCOL_TX_TRACE_DATA,     /* 0x87:Trace Data Send                       */
    PROTOCOL_TX_TRACE_ERR,      /* 0x88:Trace Error Send                      */

    PROTOCOL_HW_ERR,            /* 0x89:Buffer to notify HwError to upper task*/

    PROTOCOL_MSG_INVALID = 0xFF,/* 0xFF:Unused                                */
} PROTOCOL_MSG_TYPE;

/* UART Callback function prototype (for backward compatibility) */
typedef ALLOC_RESULT (*PROTOCOL_BUFF_ALLOC)  ( PROTOCOL_MSG_TYPE type, int32_t RequireSize, uint8_t** ppBuff, int32_t* pBuffSize );
typedef void (*PROTOCOL_BUFF_FREE)           ( PROTOCOL_MSG_TYPE type, uint8_t* pBuff );
typedef void (*PROTOCOL_MAIL_POST)           ( PROTOCOL_MSG_TYPE type, uint8_t* pBuff, uint16_t Length );
typedef void (*PROTOCOL_HW_ERROR)            ( int32_t Reason );
typedef void (*PROTOCOL_STANDBY_CALLBACK)    (void);

/* UART Callback function prototype */
typedef enum tagUART_ERROR_REASON{
	UART_ERROR_UNKNOWN = 0,
	UART_ERROR_OVER_WRITE,
	UART_ERROR_OVERRUN,
	UART_ERROR_FRAMING,
	UART_ERROR_PARITY
} UART_ERROR_REASON;
typedef void (*UARTCB_RECEIVE_COMPLETE)(uint8_t* pRcvBuff, 
                                        int32_t  RcvDataSize);
typedef void (*UARTCB_CHARTIMER_TIMEOUT)(uint8_t* pRcvBuff, 
                                         int32_t  RcvDataSize);
typedef void (*UARTCB_SEND_COMPLETE)(uint8_t* pSendBuff);
typedef void (*UARTCB_SEND_REQ)(void);
typedef void (*UARTCB_CTS_OFF_DET)(void);
typedef void (*UARTCB_ERROR)(uint8_t*          pRcvBuff, 
                             int32_t           RcvDataSize,
                             UART_ERROR_REASON Reason);
typedef void (*UARTCB_TIMER_TIMEOUT)        (void);

/* C2 Callback function protorype */
typedef void (*SYS_API_CB_FUNC)              (void);

extern void C2_Patch( void );

/****************************************************************************
 API declaration
*****************************************************************************/
/* Bluetooth and Inter Task Communications */
extern int32_t  OS_API_GetTcuMsgMemory( int32_t dwMemID, SR_FAT_MSG** pPtr, uint16_t wTimeout );
extern int32_t  OS_API_ReleaseTcuMsgMemory( int32_t dwMemID, SR_FAT_MSG* pPtr );
extern void     OS_API_SetEventFlg( int32_t dwFlagId, uint32_t dwFlag );
extern void     OS_API_ISetEventFlg( int32_t dwFlagId, uint32_t dwFlag );
extern void     OS_API_WaitEventFlg( int32_t dwFlagId, uint32_t* pdwFlag );
extern int32_t  OS_API_TWaitEventFlg( int32_t dwFlagId, uint32_t* pdwFlag, uint32_t wTimeout );
extern int32_t  OS_API_GetMessage( int32_t dwMbxID, SR_FAT_MSG** ppPtr, uint16_t wTimeout );
extern int32_t  OS_API_PostMessage( int32_t dwMbxID, SR_FAT_MSG* pPtr );

/* Bluetooth RF */
extern RET_API  SYS_API_SetTransmitPowerLevel( void* pData, uint8_t bDataLen );
extern RET_API  SYS_API_GetTransmitPowerLevel( void* pData, uint8_t bDataLen, uint8_t* pPowerLevel );
extern RET_API  SYS_API_LeRssiAllCtrl( void* pData, uint8_t bDataLen );
extern RET_API  SYS_API_GetLeRssiAll( uint8_t bDebugEnable, void* pDebugData, uint8_t bDebugDataLen, void* pValue );
extern RET_API  SYS_API_SetCELength( uint16_t ConnectionHandle, uint16_t MaxCELength, uint16_t MinCELength);

/* General I/O */
extern RET_API  SYS_API_SetGpioMux( uint8_t bGpioNo, uint8_t bGpioVal );
extern RET_API  SYS_API_SetGpioEn( uint8_t bGpioNo, uint8_t bIO );
extern RET_API  SYS_API_SetGpioCfgReg( uint8_t bGpioNo, uint16_t wGpioVal );

/* UART (for backward compatibility)*/
extern U_RESULT UART_API_Construct( uint8_t bNo );
extern U_RESULT UART_API_Destruct( uint8_t bNo );
extern U_RESULT UART_API_GFAT_Open( uint8_t bNo,
                                    PROTOCOL_BUFF_ALLOC CB_MemAlloc,
                                    PROTOCOL_BUFF_FREE CB_MemFree,
                                    PROTOCOL_MAIL_POST CB_MailPost,
                                    PROTOCOL_HW_ERROR CB_HwError,
                                    int32_t hostwakeup_enable );
extern U_RESULT UART_API_GFAT_Close( uint8_t bNo );
extern U_RESULT UART_API_Standby_Check( uint8_t bNo );
extern U_RESULT UART_API_Standby_Set( uint8_t bNo, PROTOCOL_STANDBY_CALLBACK callback );
extern U_RESULT UART_API_SetCharTimer( uint8_t bNo, int32_t CharTimer );
extern U_RESULT UART_API_SetHwFlow( uint8_t bNo, int32_t enable );
extern U_RESULT UART_API_SetBaud( uint8_t bNo, int32_t baud );
extern void     UART_API_Set_HostWakeup_Time( uint8_t bNo, int32_t hostwakeup_time );
extern U_RESULT UART_API_KillRx( uint8_t bNo );
extern int32_t  UART_API_GetStatus( uint8_t bNo );
extern U_RESULT UART_API_Send( uint8_t bNo, PROTOCOL_MSG_TYPE type, uint8_t* pData, int32_t Len );
extern U_RESULT UART_API_SendWait( uint8_t bNo, PROTOCOL_MSG_TYPE type, uint8_t* pData, int32_t Len );
extern U_RESULT UART_API_RTS_Suspend( uint8_t bNo );
extern U_RESULT UART_API_RTS_Resume( uint8_t bNo );
extern void     UART_API_RTS_ResumeByMemory( uint8_t bNo, PROTOCOL_MSG_TYPE MsgType );

/* UART function prototype */
extern void    uart1_Initialize(void);
extern void    uart1_ll_Open(UARTCB_RECEIVE_COMPLETE  CB_Receive_Complete, 
                             UARTCB_CHARTIMER_TIMEOUT CB_CharTimer_Timeout, 
                             UARTCB_SEND_COMPLETE     CB_Send_Complete,
                             UARTCB_SEND_REQ          CB_Send_Req, 
                             UARTCB_ERROR             CB_Error, 
                             UARTCB_TIMER_TIMEOUT     CB_Timer1_Timeout, 
                             UARTCB_TIMER_TIMEOUT     CB_Timer2_Timeout, 
                             UARTCB_TIMER_TIMEOUT     CB_Timer3_Timeout);
extern void    uart1_Close(void);
extern void    uart1_ll_Receive_Start(uint8_t* pRcvBuff, 
                                   int32_t  RcvBuffSize, 
                                   int32_t  IntPos);
extern int32_t uart1_ll_Receive_Next(uint8_t* pRcvBuff, 
                                     int32_t  RcvBuffSize, 
                                     int32_t  IntPos, 
                                     int32_t  ContPos,
                                     int32_t* pIntPosFixed);
extern void    uart1_ll_Receive_Cont(int32_t IntPos);
extern void    uart1_ll_Receive_Reset(uint8_t* pRcvBuff, 
                                      int32_t  RcvBuffSize, 
                                      int32_t  IntPos);
extern int32_t uart1_Read_BaudRate(void);
extern void    uart1_Set_BaudRate(int32_t Baud_bps);
extern void    uart1_Set_CharTimer(int32_t CharTimer_us);
extern void    uart1_CharTimer_Enable(void);
extern void    uart1_CharTimer_Disable(void);
extern void    uart1_Send_Req(void);
extern void    uart1_Send_Start(uint8_t* pSendBuff,
                                int32_t  SendDataSize);
extern void    uart1_HwFlow_Enable(void);
extern void    uart1_HwFlow_Disable(void);
extern void    uart1_RTS_Control(int32_t Value);
extern void    uart1_FramingErrorInt_Enable(void);

/* NVM(On-Chip FLASH memory) */
extern RET_API  SYS_API_QSPIStorageOpen( uint8_t id, uint32_t protect );
extern RET_API  SYS_API_QSPIStorageClose( void );
extern RET_API  SYS_API_QSPIStorageRead( uint32_t Addr, uint32_t Size, uint8_t* pBuff );
extern RET_API  SYS_API_QSPIStorageWrite( uint32_t Addr, uint32_t Size, uint8_t* pBuff );
extern RET_API  SYS_API_QSPIStorageSectorErase( uint32_t Addr );
extern RET_API  SYS_API_QSPIStorageChecksum( uint32_t Addr, uint32_t Size, uint32_t* pChecksum );
extern RET_API  SYS_API_QSPIStorageFlagRead( uint32_t Addr, uint32_t Size, uint32_t* pFlag );
extern RET_API  SYS_API_QSPIStorageFlagWrite( uint32_t Addr, uint32_t Size, uint32_t Flag );
extern RET_API  SYS_API_QSPIStorageReadSysData( uint16_t readSize, uint16_t ramOffsetAddr );
extern RET_API  SYS_API_SetDataAccessPassword( uint8_t bPasswordArea, uint8_t* pbPassword );
extern RET_API  SYS_API_QSPIStorageSecurityRegRead( uint32_t Addr, uint32_t Size, uint8_t* pBuff );
extern RET_API  SYS_API_QSPIStorageSecurityRegErase( uint32_t Addr );
extern RET_API  SYS_API_QSPIStorageSecurityRegWrite( uint32_t Addr, uint32_t Size, uint8_t* pBuff );
#define SYS_API_QSPIStorageSecurityRegOpen SYS_API_QSPIStorageOpen
#define SYS_API_QSPIStorageSecurityRegClose SYS_API_QSPIStorageClose
extern RET_API  SYS_API_QSPIDirectStorageOpen( uint8_t id, uint32_t protect );
extern RET_API  SYS_API_QSPIDirectStorageClose( void );
extern RET_API  SYS_API_QSPIDirectStorageRead( uint32_t Addr, uint32_t Size, uint8_t* pBuff );
extern RET_API  SYS_API_QSPIDirectStorageWrite( uint32_t Addr, uint32_t Size, uint8_t* pBuff );
extern RET_API  SYS_API_QSPIDirectStorageSectorErase( uint32_t Addr );
extern RET_API  SYS_API_QSPIDirectStorageChecksum( uint32_t Addr, uint32_t Size, uint32_t* pChecksum );
extern RET_API  SYS_API_QSPIDirectStorageFlagRead( uint32_t Addr, uint32_t Size, uint32_t* pFlag );
extern RET_API  SYS_API_QSPIDirectStorageFlagWrite( uint32_t Addr, uint32_t Size, uint32_t Flag );
extern RET_API  SYS_API_QSPIDirectStorageReadSysData( uint16_t readSize, uint16_t ramOffsetAddr );

/* I2C */
extern RET_API  SYS_API_SetI2cEnable( uint8_t bScl, uint8_t bFlNum );
extern RET_API  SYS_API_ReadSysDataRamFromE2prom( uint8_t bDevAddr, uint16_t wReadLen, uint8_t bOffset, uint8_t bFrame2Len );
extern RET_API  SYS_API_WriteSysDataRamToE2prom( uint8_t bDevAddr, uint8_t bDataLen, uint8_t bOffset, uint8_t bWriteLen, uint8_t bFrame2Len);
extern RET_API  SYS_API_ReadGeneralDeviceViaI2c( uint8_t bDevAddr, uint8_t bFrame2Len, uint8_t bReadKind,
                                                 uint8_t bReadLen, uint16_t wReadAddr, void* pRdPtr );
extern RET_API  SYS_API_WriteGeneralDeviceViaI2c( uint8_t bDevAddr, uint8_t bDataLen, uint8_t bFrame2Len,
                                                  uint8_t bWriteLen, uint16_t wWriteAddr, void* pWrData );
extern RET_API  SYS_API_ReadSysDataRamFromE2prom( uint8_t bDevAddr, uint16_t wReadLen, uint8_t bOffset, uint8_t bFrame2Len );
extern RET_API  SYS_API_WriteSysDataRamToE2prom( uint8_t bDevAddr, uint8_t bDataLen, uint8_t bOffset, uint8_t bWriteLen, uint8_t bFrame2Len);

/* System Data */
extern RET_API  SYS_API_GetSysData( uint8_t bOffset, uint8_t bDataLen, void* pRdPtr );
extern RET_API  SYS_API_SetSysData( uint8_t bDevAddr, uint8_t bOffset, uint8_t bDataLen, void* pWrData );
extern RET_API  SYS_API_ExecSysData( uint16_t wSelectRamData );

/* Low power mode */
extern RET_API  SYS_API_SetDeepSleep( void* pData, uint8_t bDataLen );
extern RET_API  SYS_API_SetBlesglSleepClock( uint8_t bSleepClkSel, uint16_t wStartGtimA );
extern RET_API  SYS_API_SetBlesglSleepCtrl( uint8_t bValue );
extern RET_API  SYS_API_GpioDeepSleepCtrl( uint8_t bReserved1, uint8_t bStatus, uint8_t bHostWakeUp, uint8_t bReserved2 );
extern RET_API  SYS_API_SetBlesglSleepCtrlModeSetting( void* pData, uint8_t bDataLen );
extern void     SYS_API_Wakeup( SYS_API_CB_FUNC CB_Wakeup );
extern RET_API  SYS_API_GetWakeUpCauseValue( uint16_t* wReserved, uint16_t* wPmuCauseReg, uint16_t* wCgRstCause );
extern RET_API  SYS_API_SetDozeLAdverisingCount( uint32_t count );

/* Interrupt */
extern RET_API  SYS_API_HwGpioIntHandlerInstall( void(*func)(uint32_t), uint32_t mMask );
extern RET_API  SYS_API_SetWakeInt( uint8_t bChannelNo, uint8_t bCause, uint8_t bEdge );
extern RET_API  SYS_API_SetCallbackPMUTimInt( SYS_API_CB_FUNC CB_Func, uint32_t dwInt );
extern RET_API  SYS_API_SetCallbackPeripheralInt( SYS_API_CB_FUNC CB_Func, uint32_t dwInt );
extern RET_API  SYS_API_SetCallbackDMAInt( SYS_API_CB_FUNC CB_Func, uint32_t dwInt );
extern RET_API  SYS_API_SetCallbackHwTimerInt( SYS_API_CB_FUNC CB_Func, uint32_t dwInt );
extern void     OS_API_HWARMIntrDisable( void );
extern void     OS_API_HWARMIntrEnable( void );

/* Timer */
extern int32_t  OS_API_SetTimer( int32_t dwMbxID, uint32_t dwTimerID, uint16_t wTimeout );
extern int32_t  OS_API_SetTimer2( int32_t dwMbxID, uint32_t dwTimerID, uint16_t wTimeout );
extern int32_t  OS_API_KillTimer( int32_t dwMbxID, uint32_t dwTimerID );

/* Other System APIs */
extern RET_API  SYS_API_ChangeSystemClock( uint8_t bValue );
extern RET_API  SYS_API_ReadVer( uint8_t* pValueLen, void* pValue );
extern int32_t  OS_API_Sleep( uint32_t dwTime );
extern void     SYS_API_ReseedRandData( void );
extern RET_API  SYS_API_GetRandData( uint16_t size, uint8_t* pBuff );
extern uint8_t  SYS_API_ReadFuseSwd(void);
extern uint8_t  SYS_API_CheckRamFault( uint32_t Addr, uint32_t Size );

/* Other Supporting APIs */
extern uint32_t SYS_API_Division32( uint32_t a, uint32_t b );
extern uint32_t SYS_API_Remainder32( uint32_t a, uint32_t b );
extern void*    OS_API_Alloc( int32_t dwMemID );
extern void     OS_API_Free( int32_t dwMemID, void* pPtr );
extern void     OS_API_Memcpy( void* pDst, const void* pSrc, size_t size );
extern void     OS_API_Memset( void* pPtr, int32_t val, size_t size );
extern int32_t  OS_API_Memcmp( const void* p1, const void* p2, size_t size );
extern void*    OS_API_Memchr( const void* pPrt, int32_t c, size_t size );

/* data */

#ifdef __cplusplus
}
#endif

#endif /* HOST_API_H_ */
