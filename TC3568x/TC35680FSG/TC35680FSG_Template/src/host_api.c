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
/* VERSION : 20180928A */
/* TARGET  : TC35680-ROM002 */

#include "host_api.h"
#ifdef __IAR_SYSTEMS_ICC__
#elif defined __UVISION_VERSION
#elif defined __GNUC__
  #define HEAP_SIZE (256)
  void data_init(void){
      uint32_t i = 0;
      extern uint32_t bss_table[]; // Defined in linker script.
      while(bss_table[i] != 0 ){
          OS_API_Memset( (void*)bss_table[i],
                         0x00,
                         (size_t)(bss_table[i+1]-bss_table[i]));
          i+=2;
      }
  }
  __attribute__((section("heap"))) uint8_t __heap[HEAP_SIZE];
#endif

// "__WEAK" is defined in CMSIS include file.
__WEAK uint32_t SystemCoreClock = 32000000;

RET_API  SYS_API_SetGpioMux( uint8_t bGpioNo, uint8_t bGpioVal)
{
	return ((RET_API  (*)( uint8_t bGpioNo, uint8_t bGpioVal)) 0x000001b9)(bGpioNo, bGpioVal) ;
}

RET_API  SYS_API_SetGpioEn( uint8_t bGpioNo, uint8_t bIO)
{
	return ((RET_API  (*)( uint8_t bGpioNo, uint8_t bIO)) 0x000001c1)(bGpioNo, bIO) ;
}

RET_API  SYS_API_SetGpioCfgReg( uint8_t bGpioNo, uint16_t wGpioVal)
{
	return ((RET_API  (*)( uint8_t bGpioNo, uint16_t wGpioVal)) 0x000001c9)(bGpioNo, wGpioVal) ;
}

RET_API  SYS_API_SetI2cEnable( uint8_t bScl, uint8_t bFlNum)
{
	return ((RET_API  (*)( uint8_t bScl, uint8_t bFlNum)) 0x000001d1)(bScl, bFlNum) ;
}

RET_API  SYS_API_ReadSysDataRamFromE2prom( uint8_t bDevAddr, uint16_t wReadLen, uint8_t bOffset, uint8_t bFrame2Len)
{
	return ((RET_API  (*)( uint8_t bDevAddr, uint16_t wReadLen, uint8_t bOffset, uint8_t bFrame2Len)) 0x000001d9)(bDevAddr, wReadLen, bOffset, bFrame2Len) ;
}

RET_API  SYS_API_WriteSysDataRamToE2prom( uint8_t bDevAddr, uint8_t bDataLen, uint8_t bOffset, uint8_t bWriteLen, uint8_t bFrame2Len)
{
	return ((RET_API  (*)( uint8_t bDevAddr, uint8_t bDataLen, uint8_t bOffset, uint8_t bWriteLen, uint8_t bFrame2Len)) 0x000001e1)(bDevAddr, bDataLen, bOffset, bWriteLen, bFrame2Len) ;
}

RET_API  SYS_API_GetSysData( uint8_t bOffset, uint8_t bDataLen, void* pRdPtr)
{
	return ((RET_API  (*)( uint8_t bOffset, uint8_t bDataLen, void* pRdPtr)) 0x000001ed)(bOffset, bDataLen, pRdPtr) ;
}

RET_API  SYS_API_SetSysData( uint8_t bDevAddr, uint8_t bOffset, uint8_t bDataLen, void* pWrData)
{
	return ((RET_API  (*)( uint8_t bDevAddr, uint8_t bOffset, uint8_t bDataLen, void* pWrData)) 0x000001f5)(bDevAddr, bOffset, bDataLen, pWrData) ;
}

RET_API  SYS_API_ReadGeneralDeviceViaI2c( uint8_t bDevAddr, uint8_t bFrame2Len, uint8_t bReadKind, uint8_t bReadLen, uint16_t wReadAddr, void* pRdPtr)
{
	return ((RET_API  (*)( uint8_t bDevAddr, uint8_t bFrame2Len, uint8_t bReadKind, uint8_t bReadLen, uint16_t wReadAddr, void* pRdPtr)) 0x00000215)(bDevAddr, bFrame2Len, bReadKind, bReadLen, wReadAddr, pRdPtr) ;
}

RET_API  SYS_API_WriteGeneralDeviceViaI2c( uint8_t bDevAddr, uint8_t bDataLen, uint8_t bFrame2Len, uint8_t bWriteLen, uint16_t wWriteAddr, void* pWrData)
{
	return ((RET_API  (*)( uint8_t bDevAddr, uint8_t bDataLen, uint8_t bFrame2Len, uint8_t bWriteLen, uint16_t wWriteAddr, void* pWrData)) 0x00000225)(bDevAddr, bDataLen, bFrame2Len, bWriteLen, wWriteAddr, pWrData) ;
}

RET_API  SYS_API_ExecSysData( uint16_t wSelectRamData)
{
	return ((RET_API  (*)( uint16_t wSelectRamData)) 0x00000235)(wSelectRamData) ;
}

RET_API  SYS_API_SetDeepSleep( void* pData, uint8_t bDataLen)
{
	return ((RET_API  (*)( void* pData, uint8_t bDataLen)) 0x0000023d)(pData, bDataLen) ;
}

RET_API  SYS_API_SetBlesglSleepClock( uint8_t bSleepClkSel, uint16_t wStartGtimA)
{
	return ((RET_API  (*)( uint8_t bSleepClkSel, uint16_t wStartGtimA)) 0x00000245)(bSleepClkSel, wStartGtimA) ;
}

RET_API  SYS_API_SetBlesglSleepCtrl( uint8_t bValue)
{
	return ((RET_API  (*)( uint8_t bValue)) 0x0000024d)(bValue) ;
}

RET_API  SYS_API_GpioDeepSleepCtrl( uint8_t bReserved1, uint8_t bStatus, uint8_t bHostWakeUp, uint8_t bReserved2)
{
	return ((RET_API  (*)( uint8_t bReserved1, uint8_t bStatus, uint8_t bHostWakeUp, uint8_t bReserved2)) 0x00000255)(bReserved1, bStatus, bHostWakeUp, bReserved2) ;
}

RET_API  SYS_API_SetTransmitPowerLevel( void* pData, uint8_t bDataLen)
{
	return ((RET_API  (*)( void* pData, uint8_t bDataLen)) 0x0000025d)(pData, bDataLen) ;
}

RET_API  SYS_API_GetTransmitPowerLevel( void* pData, uint8_t bDataLen, uint8_t* pPowerLevel)
{
	return ((RET_API  (*)( void* pData, uint8_t bDataLen, uint8_t* pPowerLevel)) 0x00000265)(pData, bDataLen, pPowerLevel) ;
}

RET_API  SYS_API_HwGpioIntHandlerInstall( void(*func)(uint32_t), uint32_t mMask)
{
	return ((RET_API  (*)( void(*func)(uint32_t), uint32_t mMask)) 0x0000026d)(func, mMask);
}

RET_API  SYS_API_SetWakeInt( uint8_t bChannelNo, uint8_t bCause, uint8_t bEdge)
{
	return ((RET_API  (*)( uint8_t bChannelNo, uint8_t bCause, uint8_t bEdge)) 0x00000275)(bChannelNo, bCause, bEdge) ;
}

int32_t  OS_API_GetTcuMsgMemory( int32_t dwMemID, SR_FAT_MSG** pPtr, uint16_t wTimeout)
{
	return ((int32_t  (*)( int32_t dwMemID, SR_FAT_MSG** pPtr, uint16_t wTimeout)) 0x0000028d)(dwMemID, pPtr, wTimeout) ;
}

int32_t  OS_API_ReleaseTcuMsgMemory( int32_t dwMemID, SR_FAT_MSG* pPtr)
{
	return ((int32_t  (*)( int32_t dwMemID, SR_FAT_MSG* pPtr)) 0x00000295)(dwMemID, pPtr) ;
}

void*    OS_API_Alloc( int32_t dwMemID)
{
	return ((void*    (*)( int32_t dwMemID)) 0x0000029d)(dwMemID) ;
}

void     OS_API_Free( int32_t dwMemID, void* pPtr)
{
	((void     (*)( int32_t dwMemID, void* pPtr)) 0x000002a5)(dwMemID, pPtr) ;
}

void     OS_API_SetEventFlg( int32_t dwFlagId, uint32_t dwFlag)
{
	((void     (*)( int32_t dwFlagId, uint32_t dwFlag)) 0x000002bd)(dwFlagId, dwFlag) ;
}

void     OS_API_ISetEventFlg( int32_t dwFlagId, uint32_t dwFlag)
{
	((void     (*)( int32_t dwFlagId, uint32_t dwFlag)) 0x000002c5)(dwFlagId, dwFlag) ;
}

void     OS_API_WaitEventFlg( int32_t dwFlagId, uint32_t* pdwFlag)
{
	((void     (*)( int32_t dwFlagId, uint32_t* pdwFlag)) 0x000002cd)(dwFlagId, pdwFlag) ;
}

int32_t  OS_API_GetMessage( int32_t dwMbxID, SR_FAT_MSG** ppPtr, uint16_t wTimeout)
{
	return ((int32_t  (*)( int32_t dwMbxID, SR_FAT_MSG** ppPtr, uint16_t wTimeout)) 0x000002dd)(dwMbxID, ppPtr, wTimeout) ;
}

int32_t  OS_API_PostMessage( int32_t dwMbxID, SR_FAT_MSG* pPtr)
{
	return ((int32_t  (*)( int32_t dwMbxID, SR_FAT_MSG* pPtr)) 0x000002e5)(dwMbxID, pPtr) ;
}

int32_t  OS_API_SetTimer( int32_t dwMbxID, uint32_t dwTimerID, uint16_t wTimeout)
{
	return ((int32_t  (*)( int32_t dwMbxID, uint32_t dwTimerID, uint16_t wTimeout)) 0x000002ed)(dwMbxID, dwTimerID, wTimeout) ;
}

int32_t  OS_API_SetTimer2( int32_t dwMbxID, uint32_t dwTimerID, uint16_t wTimeout)
{
	return ((int32_t  (*)( int32_t dwMbxID, uint32_t dwTimerID, uint16_t wTimeout)) 0x000002f5)(dwMbxID, dwTimerID, wTimeout) ;
}

int32_t  OS_API_KillTimer( int32_t dwMbxID, uint32_t dwTimerID)
{
	return ((int32_t  (*)( int32_t dwMbxID, uint32_t dwTimerID)) 0x000002fd)(dwMbxID, dwTimerID) ;
}

void     OS_API_Memcpy( void* pDst, const void* pSrc, size_t size)
{
	((void     (*)( void* pDst, const void* pSrc, size_t size)) 0x00000305)(pDst, pSrc, size) ;
}

void     OS_API_Memset( void* pPtr, int32_t val, size_t size)
{
	((void     (*)( void* pPtr, int32_t val, size_t size)) 0x0000030d)(pPtr, val, size) ;
}

int32_t  OS_API_Memcmp( const void* p1, const void* p2, size_t size)
{
	return ((int32_t  (*)( const void* p1, const void* p2, size_t size)) 0x00000315)(p1, p2, size) ;
}

void*    OS_API_Memchr( const void* pPrt, int32_t c, size_t size)
{
	return ((void*    (*)( const void* pPrt, int32_t c, size_t size)) 0x0000031d)(pPrt, c, size) ;
}

int32_t  OS_API_Sleep( uint32_t dwTime)
{
	return ((int32_t  (*)( uint32_t dwTime)) 0x00000325)(dwTime) ;
}

U_RESULT UART_API_Standby_Check( uint8_t bNo)
{
	return ((U_RESULT (*)( uint8_t bNo)) 0x0000032d)(bNo) ;
}

U_RESULT UART_API_Standby_Set( uint8_t bNo, PROTOCOL_STANDBY_CALLBACK callback)
{
	return ((U_RESULT (*)( uint8_t bNo, PROTOCOL_STANDBY_CALLBACK callback)) 0x00000335)(bNo, callback) ;
}

U_RESULT UART_API_KillRx( uint8_t bNo)
{
	return ((U_RESULT (*)( uint8_t bNo)) 0x0000033d)(bNo) ;
}

U_RESULT UART_API_SetCharTimer( uint8_t bNo, int32_t CharTimer)
{
	return ((U_RESULT (*)( uint8_t bNo, int32_t CharTimer)) 0x00000345)(bNo, CharTimer) ;
}

U_RESULT UART_API_SetHwFlow( uint8_t bNo, int32_t enable)
{
	PMU->PMU_IOSTANDBYX_b.GPIO8InputStandbyRelease = 1;
	return ((U_RESULT (*)( uint8_t bNo, int32_t enable)) 0x0000034d)(bNo, enable) ;
}

int32_t  UART_API_GetStatus( uint8_t bNo)
{
	return ((int32_t  (*)( uint8_t bNo)) 0x00000355)(bNo) ;
}

U_RESULT UART_API_Construct( uint8_t bNo)
{
	return ((U_RESULT (*)( uint8_t bNo)) 0x0000035d)(bNo) ;
}

U_RESULT UART_API_GFAT_Open( uint8_t bNo, PROTOCOL_BUFF_ALLOC CB_MemAlloc, PROTOCOL_BUFF_FREE CB_MemFree, PROTOCOL_MAIL_POST CB_MailPost, PROTOCOL_HW_ERROR CB_HwError, int32_t hostwakeup_enable)
{
	return ((U_RESULT (*)( uint8_t bNo, PROTOCOL_BUFF_ALLOC CB_MemAlloc, PROTOCOL_BUFF_FREE CB_MemFree, PROTOCOL_MAIL_POST CB_MailPost, PROTOCOL_HW_ERROR CB_HwError, int32_t hostwakeup_enable)) 0x00000365)(bNo, CB_MemAlloc, CB_MemFree, CB_MailPost, CB_HwError, hostwakeup_enable) ;
}

U_RESULT UART_API_GFAT_Close( uint8_t bNo)
{
	return ((U_RESULT (*)( uint8_t bNo)) 0x00000375)(bNo) ;
}

U_RESULT UART_API_Send( uint8_t bNo, PROTOCOL_MSG_TYPE type, uint8_t* pData, int32_t Len)
{
	return ((U_RESULT (*)( uint8_t bNo, PROTOCOL_MSG_TYPE type, uint8_t* pData, int32_t Len)) 0x0000037d)(bNo, type, pData, Len) ;
}

U_RESULT UART_API_SendWait( uint8_t bNo, PROTOCOL_MSG_TYPE type, uint8_t* pData, int32_t Len)
{
	return ((U_RESULT (*)( uint8_t bNo, PROTOCOL_MSG_TYPE type, uint8_t* pData, int32_t Len)) 0x00000385)(bNo, type, pData, Len) ;
}

U_RESULT UART_API_SetBaud( uint8_t bNo, int32_t baud)
{
	return ((U_RESULT (*)( uint8_t bNo, int32_t baud)) 0x0000038d)(bNo, baud) ;
}

void     UART_API_Set_HostWakeup_Time( uint8_t bNo, int32_t hostwakeup_time)
{
	((void     (*)( uint8_t bNo, int32_t hostwakeup_time)) 0x00000395)(bNo, hostwakeup_time) ;
}

U_RESULT UART_API_RTS_Suspend( uint8_t bNo)
{
	return ((U_RESULT (*)( uint8_t bNo)) 0x0000039d)(bNo) ;
}

U_RESULT UART_API_RTS_Resume( uint8_t bNo)
{
	return ((U_RESULT (*)( uint8_t bNo)) 0x000003a5)(bNo) ;
}

void     UART_API_RTS_ResumeByMemory( uint8_t bNo, PROTOCOL_MSG_TYPE MsgType)
{
	((void     (*)( uint8_t bNo, PROTOCOL_MSG_TYPE MsgType)) 0x000003ad)(bNo, MsgType) ;
}

U_RESULT UART_API_Destruct( uint8_t bNo)
{
	return ((U_RESULT (*)( uint8_t bNo)) 0x000003b5)(bNo) ;
}

RET_API  SYS_API_SetBlesglSleepCtrlModeSetting( void* pData, uint8_t bDataLen)
{
	return ((RET_API  (*)( void* pData, uint8_t bDataLen)) 0x000003c5)(pData, bDataLen) ;
}

void     SYS_API_Wakeup( SYS_API_CB_FUNC CB_Wakeup)
{
	((void     (*)( SYS_API_CB_FUNC CB_Wakeup)) 0x000003cd)(CB_Wakeup) ;
}

RET_API  SYS_API_GetWakeUpCauseValue( uint16_t* wReserved, uint16_t* wPmuCauseReg, uint16_t* wCgRstCause)
{
	return ((RET_API  (*)( uint16_t* wReserved, uint16_t* wPmuCauseReg, uint16_t* wCgRstCause)) 0x000003d5)(wReserved, wPmuCauseReg, wCgRstCause) ;
}

void     OS_API_HWARMIntrEnable( void)
{
	((void     (*)( void)) 0x000003dd)() ;
}

void     OS_API_HWARMIntrDisable( void)
{
	((void     (*)( void)) 0x000003e5)() ;
}

uint32_t SYS_API_Division32( uint32_t a, uint32_t b)
{
	return ((uint32_t (*)( uint32_t a, uint32_t b)) 0x000003ed)(a, b) ;
}

uint32_t SYS_API_Remainder32( uint32_t a, uint32_t b)
{
	return ((uint32_t (*)( uint32_t a, uint32_t b)) 0x000003f5)(a, b) ;
}

RET_API  SYS_API_ReadVer( uint8_t* pValueLen, void* pValue)
{
	return ((RET_API  (*)( uint8_t* pValueLen, void* pValue)) 0x000003fd)(pValueLen, pValue) ;
}

RET_API  SYS_API_LeRssiAllCtrl( void* pData, uint8_t bDataLen)
{
	return ((RET_API  (*)( void* pData, uint8_t bDataLen)) 0x00000405)(pData, bDataLen) ;
}

RET_API  SYS_API_GetLeRssiAll( uint8_t bDebugEnable, void* pDebugData, uint8_t bDebugDataLen, void* pValue)
{
	return ((RET_API  (*)( uint8_t bDebugEnable, void* pDebugData, uint8_t bDebugDataLen, void* pValue)) 0x0000040d)(bDebugEnable, pDebugData, bDebugDataLen, pValue) ;
}

RET_API  SYS_API_QSPIStorageOpen( uint8_t id, uint32_t protect)
{
	return ((RET_API  (*)( uint8_t id, uint32_t protect)) 0x00000425)(id, protect) ;
}

RET_API  SYS_API_QSPIStorageClose( void)
{
	return ((RET_API  (*)( void)) 0x0000042d)() ;
}

RET_API  SYS_API_QSPIStorageRead( uint32_t Addr, uint32_t Size, uint8_t* pBuff)
{
	return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint8_t* pBuff)) 0x00000435)(Addr, Size, pBuff) ;
}

RET_API  SYS_API_QSPIStorageChecksum( uint32_t Addr, uint32_t Size, uint32_t* pChecksum)
{
	unsigned char buf[3];
	int i;
	RET_API api_ret;
	unsigned checksum = 0;
	if( Size < 4 ){
		api_ret = SYS_API_QSPIStorageRead( Addr, Size, buf );
		if( api_ret != RET_API_NORMAL) return api_ret;
		for(i=0;i<Size;i++){
			checksum += buf[i];
		}
		*pChecksum = checksum;
		return RET_API_NORMAL;
	}
	else{
		return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint32_t* pChecksum)) 0x0000043d)(Addr, Size, pChecksum) ;
	}
}

RET_API  SYS_API_QSPIStorageSectorErase( uint32_t Addr)
{
	return ((RET_API  (*)( uint32_t Addr)) 0x00000445)(Addr) ;
}

RET_API  SYS_API_QSPIStorageWrite( uint32_t Addr, uint32_t Size, uint8_t* pBuff)
{
	return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint8_t* pBuff)) 0x0000044d)(Addr, Size, pBuff) ;
}

RET_API  SYS_API_QSPIStorageFlagRead( uint32_t Addr, uint32_t Size, uint32_t* pFlag)
{
	return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint32_t* pFlag)) 0x00000455)(Addr, Size, pFlag) ;
}

RET_API  SYS_API_QSPIStorageFlagWrite( uint32_t Addr, uint32_t Size, uint32_t Flag)
{
	return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint32_t Flag)) 0x0000045d)(Addr, Size, Flag) ;
}

RET_API  SYS_API_QSPIStorageReadSysData( uint16_t readSize, uint16_t ramOffsetAddr)
{
	return ((RET_API  (*)( uint16_t readSize, uint16_t ramOffsetAddr)) 0x00000465)(readSize, ramOffsetAddr) ;
}

RET_API  SYS_API_QSPIDirectStorageOpen( uint8_t id, uint32_t protect)
{
        return ((RET_API  (*)( uint8_t id, uint32_t protect)) 0x0000046d)(id, protect) ;
}

RET_API  SYS_API_QSPIDirectStorageClose( void)
{
        return ((RET_API  (*)( void)) 0x00000475)() ;
}

RET_API  SYS_API_QSPIDirectStorageRead( uint32_t Addr, uint32_t Size, uint8_t* pBuff)
{
        return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint8_t* pBuff)) 0x0000047d)(Addr, Size, pBuff) ;
}

RET_API  SYS_API_QSPIDirectStorageChecksum( uint32_t Addr, uint32_t Size, uint32_t* pChecksum)
{
	unsigned char buf[3];
	int i;
	RET_API api_ret;
	unsigned checksum = 0;
	if( Size < 4 ){
		api_ret = SYS_API_QSPIDirectStorageRead( Addr, Size, buf );
		if( api_ret != RET_API_NORMAL) return api_ret;
		for(i=0;i<Size;i++){
			checksum += buf[i];
		}
		*pChecksum = checksum;
		return RET_API_NORMAL;
	}
	else{
		return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint32_t* pChecksum)) 0x00000485)(Addr, Size, pChecksum) ;
	}
}

RET_API  SYS_API_QSPIDirectStorageSectorErase( uint32_t Addr)
{
        return ((RET_API  (*)( uint32_t Addr)) 0x0000048d)(Addr) ;
}

RET_API  SYS_API_QSPIDirectStorageWrite( uint32_t Addr, uint32_t Size, uint8_t* pBuff)
{
        return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint8_t* pBuff)) 0x00000495)(Addr, Size, pBuff) ;
}

RET_API  SYS_API_QSPIDirectStorageFlagRead( uint32_t Addr, uint32_t Size, uint32_t* pFlag)
{
        return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint32_t* pFlag)) 0x0000049d)(Addr, Size, pFlag) ;
}

RET_API  SYS_API_QSPIDirectStorageFlagWrite( uint32_t Addr, uint32_t Size, uint32_t Flag)
{
	uint8_t		bSu			= 0;
	RET_API		bResult		= RET_API_NORMAL;
	uint8_t		bMode;
	
	bMode = ((uint8_t  (*)(void)) 0x0001372f)();
	((void  (*)(uint8_t)) 0x00013729)( TRUE );
	
	{
		uint32_t	r;
		uint32_t	now_flag;
		uint8_t		result;
		uint32_t	read_cnt, one_detect, i, j;
		uint32_t 	buff[8];
		uint8_t		*pbuff;
		uint8_t		val;
		
		if(1 < Flag){
			bSu = 2;
			goto DIRECT_FLAG_WRITE_END;
		}

		result = ((uint8_t  (*)(uint32_t, uint32_t, uint32_t*, uint32_t*)) 0x00016f89)(Addr, Size, &now_flag, buff);
		if(0 != result){
			bSu = result;
			goto DIRECT_FLAG_WRITE_END;
		}

		/* Current Flag matches to the specified flag. No need to update. */
		if(now_flag == Flag){
			bSu = 0;
			goto DIRECT_FLAG_WRITE_END;
		}

		read_cnt = Size / 32;
		one_detect = 0;
		for(i=0;i<read_cnt;i++){
			r = ((uint32_t  (*)(uint32_t, uint32_t, uint32_t)) 0x000220df)((uint32_t)(Addr + (i * 32)), (uint32_t)buff, (uint32_t)32);
			if(FALSE == r){
				bSu = 3;
				goto DIRECT_FLAG_WRITE_END;
			}
			pbuff = (unsigned char *)buff;
			for(j=0;j<32;j++){
				val = *(pbuff + j);
				if(0xFF != val){
					/* Value Other than 0xFF is already used. Skip it. */
				}else{
					/* Update there with 0x00 */
					*(pbuff + j) = 0x00;
					r = ((uint32_t  (*)(uint32_t, uint32_t, uint32_t)) 0x00021d6d)((uint32_t)(Addr + (i * 32) + j), (uint32_t)pbuff, (uint32_t)1);
					if(FALSE == r){
						bSu = 3;
						goto DIRECT_FLAG_WRITE_END;
					}
					/* Brake the loop. */
					one_detect = 1;
					i = read_cnt;
					break;
				}
			}
		}

		if(0 == one_detect){
			/* In case all the area are used, return 4. */
			bSu = 4;
			goto DIRECT_FLAG_WRITE_END;
		}else{
			bSu = 0;
			goto DIRECT_FLAG_WRITE_END;
		}
	}
	
DIRECT_FLAG_WRITE_END:
	((void  (*)(uint8_t)) 0x00013729)( bMode );
	bResult = ((RET_API  (*)(uint8_t)) 0x00008cad)( bSu );
	
	return( bResult );
}

RET_API  SYS_API_QSPIDirectStorageReadSysData( uint16_t readSize, uint16_t ramOffsetAddr)
{
	return ((RET_API  (*)( uint16_t readSize, uint16_t ramOffsetAddr)) 0x000004ad)(readSize, ramOffsetAddr) ;
}

RET_API  SYS_API_SetDozeLAdverisingCount( uint32_t count)
{
	return ((RET_API  (*)( uint32_t count)) 0x000004b5)(count) ;
}

RET_API  SYS_API_SetDataAccessPassword( uint8_t bPasswordArea, uint8_t* pbPassword)
{
	return ((RET_API  (*)( uint8_t bPasswordArea, uint8_t* pbPassword)) 0x000004bd)(bPasswordArea, pbPassword) ;
}

RET_API  SYS_API_SetCallbackPMUTimInt( SYS_API_CB_FUNC CB_Func, uint32_t dwInt)
{
	return ((RET_API  (*)( SYS_API_CB_FUNC CB_Func, uint32_t dwInt)) 0x000004cd)(CB_Func, dwInt) ;
}

RET_API  SYS_API_SetCallbackPeripheralInt( SYS_API_CB_FUNC CB_Func, uint32_t dwInt)
{
	return ((RET_API  (*)( SYS_API_CB_FUNC CB_Func, uint32_t dwInt)) 0x000004d5)(CB_Func, dwInt) ;
}

RET_API  SYS_API_SetCallbackDMAInt( SYS_API_CB_FUNC CB_Func, uint32_t dwInt)
{
	return ((RET_API  (*)( SYS_API_CB_FUNC CB_Func, uint32_t dwInt)) 0x000004dd)(CB_Func, dwInt) ;
}

RET_API  SYS_API_ChangeSystemClock( uint8_t bValue)
{
	RET_API ret;
	ret = ((RET_API  (*)( uint8_t bValue)) 0x000004ed)(bValue) ;

	if( ret == RET_API_NORMAL ){
		if(bValue==0x00){
			SystemCoreClock = 16000000;
		}
		else{
			SystemCoreClock = 32000000;
		}
	}
	return ret;
}

RET_API  SYS_API_QSPIStorageSecurityRegRead( uint32_t Addr, uint32_t Size, uint8_t* pBuff)
{
	return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint8_t* pBuff)) 0x000004fd)(Addr, Size, pBuff) ;
}

RET_API  SYS_API_QSPIStorageSecurityRegErase( uint32_t Addr)
{
	return ((RET_API  (*)( uint32_t Addr)) 0x00000505)(Addr) ;
}

RET_API  SYS_API_QSPIStorageSecurityRegWrite( uint32_t Addr, uint32_t Size, uint8_t* pBuff)
{
	return ((RET_API  (*)( uint32_t Addr, uint32_t Size, uint8_t* pBuff)) 0x0000050d)(Addr, Size, pBuff) ;
}

RET_API  SYS_API_SetCallbackHwTimerInt( SYS_API_CB_FUNC CB_Func, uint32_t dwInt)
{
	return ((RET_API  (*)( SYS_API_CB_FUNC CB_Func, uint32_t dwInt)) 0x00000515)(CB_Func, dwInt) ;
}

int32_t  OS_API_TWaitEventFlg( int32_t dwFlagId, uint32_t* pdwFlag, uint32_t wTimeout)
{
	return ((int32_t  (*)( int32_t dwFlagId, uint32_t* pdwFlag, uint32_t wTimeout)) 0x0000051d)(dwFlagId, pdwFlag, wTimeout) ;
}

void     SYS_API_ReseedRandData( void)
{
	((void     (*)( void)) 0x00000525)() ;
}

RET_API  SYS_API_GetRandData( uint16_t size, uint8_t* pBuff)
{
	return ((RET_API  (*)( uint16_t size, uint8_t* pBuff)) 0x0000052d)(size, pBuff) ;
}

uint8_t  SYS_API_ReadFuseSwd(void)
{
	return ((uint8_t  (*)(void)) 0x00000535)() ;
}

RET_API  SYS_API_SetCELength( uint16_t ConnectionHandle, uint16_t MaxCELength, uint16_t MinCELength)
{
	return ((RET_API  (*)( uint16_t ConnectionHandle, uint16_t MaxCELength, uint16_t MinCELength)) 0x00000555)(ConnectionHandle, MaxCELength, MinCELength) ;
}

void    uart1_CharTimer_Enable(void)
{
	((void    (*)(void)) 0x00007571)() ;
}

void    uart1_Initialize(void)
{
	((void    (*)(void)) 0x000077a9)() ;
}

void    uart1_Set_CharTimer(int32_t CharTimer_us)
{
	((void    (*)(int32_t CharTimer_us)) 0x00007889)(CharTimer_us) ;
}

void    uart1_Set_BaudRate(int32_t Baud_bps)
{
	((void    (*)(int32_t Baud_bps)) 0x000078a5)(Baud_bps) ;
}

void    uart1_ll_Open(UARTCB_RECEIVE_COMPLETE  CB_Receive_Complete,  UARTCB_CHARTIMER_TIMEOUT CB_CharTimer_Timeout,  UARTCB_SEND_COMPLETE     CB_Send_Complete, UARTCB_SEND_REQ          CB_Send_Req,  UARTCB_ERROR             CB_Error,  UARTCB_TIMER_TIMEOUT     CB_Timer1_Timeout,  UARTCB_TIMER_TIMEOUT     CB_Timer2_Timeout,  UARTCB_TIMER_TIMEOUT     CB_Timer3_Timeout)
{
	((void    (*)(UARTCB_RECEIVE_COMPLETE  CB_Receive_Complete,  UARTCB_CHARTIMER_TIMEOUT CB_CharTimer_Timeout,  UARTCB_SEND_COMPLETE     CB_Send_Complete, UARTCB_SEND_REQ          CB_Send_Req,  UARTCB_ERROR             CB_Error,  UARTCB_TIMER_TIMEOUT     CB_Timer1_Timeout,  UARTCB_TIMER_TIMEOUT     CB_Timer2_Timeout,  UARTCB_TIMER_TIMEOUT     CB_Timer3_Timeout)) 0x00007995)(CB_Receive_Complete, CB_CharTimer_Timeout, CB_Send_Complete, CB_Send_Req, CB_Error, CB_Timer1_Timeout, CB_Timer2_Timeout, CB_Timer3_Timeout) ;
}

void    uart1_Close(void)
{
	((void    (*)(void)) 0x000079c3)() ;
}

void    uart1_ll_Receive_Start(uint8_t* pRcvBuff,  int32_t  RcvBuffSize,  int32_t  IntPos)
{
	((void    (*)(uint8_t* pRcvBuff,  int32_t  RcvBuffSize,  int32_t  IntPos)) 0x00007a4f)(pRcvBuff, RcvBuffSize, IntPos) ;
}

int32_t uart1_ll_Receive_Next(uint8_t* pRcvBuff,  int32_t  RcvBuffSize,  int32_t  IntPos,  int32_t  ContPos, int32_t* pIntPosFixed)
{
	return ((int32_t (*)(uint8_t* pRcvBuff,  int32_t  RcvBuffSize,  int32_t  IntPos,  int32_t  ContPos, int32_t* pIntPosFixed)) 0x00007b37)(pRcvBuff, RcvBuffSize, IntPos, ContPos, pIntPosFixed) ;
}

void    uart1_ll_Receive_Cont(int32_t IntPos)
{
	((void    (*)(int32_t IntPos)) 0x00007cad)(IntPos) ;
}

void    uart1_ll_Receive_Reset(uint8_t* pRcvBuff,  int32_t  RcvBuffSize,  int32_t  IntPos)
{
	((void    (*)(uint8_t* pRcvBuff,  int32_t  RcvBuffSize,  int32_t  IntPos)) 0x00007d61)(pRcvBuff, RcvBuffSize, IntPos) ;
}

int32_t uart1_Read_BaudRate(void)
{
	return ((int32_t (*)(void)) 0x00007da9)() ;
}

void    uart1_CharTimer_Disable(void)
{
	((void    (*)(void)) 0x00007dc1)() ;
}

void    uart1_Send_Req(void)
{
	((void    (*)(void)) 0x00007dd9)() ;
}

void    uart1_Send_Start(uint8_t* pSendBuff, int32_t  SendDataSize)
{
	((void    (*)(uint8_t* pSendBuff, int32_t  SendDataSize)) 0x00007de5)(pSendBuff, SendDataSize) ;
}

void    uart1_HwFlow_Enable(void)
{
	PMU->PMU_IOSTANDBYX_b.GPIO8InputStandbyRelease = 1;
	((void    (*)(void)) 0x00007e13)() ;
}

void    uart1_HwFlow_Disable(void)
{
	((void    (*)(void)) 0x00007e51)() ;
}

void    uart1_RTS_Control(int32_t Value)
{
	((void    (*)(int32_t Value)) 0x00007e5f)(Value) ;
}

void    uart1_FramingErrorInt_Enable(void)
{
	((void    (*)( void)) 0x00007f37)() ;
}

uint8_t  SYS_API_CheckRamFault( uint32_t Addr, uint32_t Size)
{
	return ((uint8_t  (*)( uint32_t Addr, uint32_t Size)) 0x00009d15)(Addr, Size) ;
}

