/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    File name   : usb_hw.c
 *    Description : usb module (HAL)
 *
 *    History :
 *    1. Date        : 25, March 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 41 $
 **************************************************************************/
#define USB_HW_GLOBAL
#include "usb_hw.h"

#define _bmUSB_SetupInterrupt           0x00000001
#define _bmUSB_StatusNAK_Interrupt      0x00000002
#define _bmUSB_StatusInterrupt          0x00000004
#define _bmUSB_Rx0Interrupt             0x00000008
#define _bmUSB_SOF_Interrupt            0x00000010
#define _bmUSB_EP0_Interrupt            0x00000020
#define _bmUSB_EP_Interrupt             0x00000040
#define _bmUSB_NAC_Interrupt            0x00000080
#define _bmUSB_SuspendResumeInterrupt   0x00000100
#define _bmUSB_ResetInterrupt           0x00000200
#define _bmUSB_ResetEndInterrupt        0x00000400
#define _bmUSB_MW_SetAddrInterrupt      0x00020000
#define _bmUSB_MW_EndAddrInterrupt      0x00040000
#define _bmUSB_MW_TO_Interrupt          0x00080000
#define _bmUSB_MW_ErrorInterrupt        0x00100000
#define _bmUSB_MR_EndAddrInterrupt      0x00200000
#define _bmUSB_MR_EP_Data_Interrupt     0x00400000
#define _bmUSB_MR_ErrorInterrupt        0x00800000
#define _bmUSB_UDC2_AccCompInterrupt    0x01000000
#define _bmUSB_DMAC_AccCompInterrupt    0x02000000
#define _bmUSB_MWR_ErrorInterrupt       0x20000000

#define _UDC2AB_READ_ADDRESS_MASK       0x000003FC
#define _UDC2AB_READ_REQ_MASK           0x80000000

#define _bmUDC2_SetupInterrupt          0x00000001
#define _bmUDC2_StatusNAK_Interrupt     0x00000002
#define _bmUDC2_StatusInterrupt         0x00000004
#define _bmUDC2_RxDataZeroInterrupt     0x00000008
#define _bmUDC2_SOF_Interrupt           0x00000010
#define _bmUDC2_EP0_Interrupt           0x00000020
#define _bmUDC2_EP_Interrupt            0x00000040
#define _bmUDC2_NAK_Interrupt           0x00000080
#define UDC2_INTR_CLEAR_MAKS            (~0x000000FF)

#define _bmUDC2_SetupMaskInterrupt      0x00000100
#define _bmUDC2_StatusNAK_MaskInterrupt 0x00000200
#define _bmUDC2_StatusMaskInterrupt     0x00000400
#define _bmUDC2_RxDataZeroMaskInterrupt 0x00000800
#define _bmUDC2_SOF_Mask_Interrupt      0x00001000
#define _bmUDC2_EP0_Mask_Interrupt      0x00002000
#define _bmUDC2_EP_Mask_Interrupt       0x00004000
#define _bmUDC2_NAK_Mask_Interrupt      0x00008000

typedef enum _UD2_Cmd_t
{
   _Setup_Fin = 1, _Set_DATA0, _EP_Reset, _EP_Stall, _EP_Invalid,
   _EP_Disable = 7, _EP_Enable, _All_EP_Invalid, _USB_Ready,
   _Setup_Received, _EP_EOP, _EP_FIFO_Clear, _EP_TX_0DATA
} UD2_Cmd_t;


static volatile UsbDevStat_t USB_DevStatus;

static const UsbStandardEpDescriptor_t USB_CtrlEpDescr0 =
{
  sizeof(UsbStandardEpDescriptor_t),
  UsbDescriptorEp,
  UsbEpOut(CTRL_ENP_OUT>>1),
  {(Int8U)UsbEpTransferControl | (Int8U)UsbEpSynchNoSynchronization | (Int8U)UsbEpUsageData},
  Ep0MaxSize,
  0
};

static const UsbEP_ExtData_t USB_CtrlEpExtDescr0 =
{
  0,0
};

static const UsbStandardEpDescriptor_t USB_CtrlEpDescr1 =
{
  sizeof(UsbStandardEpDescriptor_t),
  UsbDescriptorEp,
  UsbEpIn(CTRL_ENP_IN>>1),
  {(Int8U)UsbEpTransferControl | (Int8U)UsbEpSynchNoSynchronization | (Int8U)UsbEpUsageData},
  Ep0MaxSize,
  0
};

static const UsbEP_ExtData_t USB_CtrlEpExtDescr1 =
{
  0,0
};

#if  USB_SOF_EVENT > 0
Int32U  USB_SofNumbHold;
#endif

/*************************************************************************
 * Function Name: _UDC2_Write
 * Parameters: Int32U RegAddr, Int32U Data
 *
 * Return: none
 *
 * Description: Write to UDC2 registers
 *
 *************************************************************************/
static
void _UDC2_Write (Int32U RegAddr, Int32U Data)
{
volatile Int16U * pReg = (volatile Int16U *)RegAddr;
Int32U save;
  ENTR_CRT_SECTION(save);
  *pReg = Data;
  while(UDC2RDREQ_bit.udc2rdreq);
  UDINTSTS = _bmUSB_UDC2_AccCompInterrupt;
  EXT_CRT_SECTION(save);
}

/*************************************************************************
 * Function Name: _UDC2_WriteByte
 * Parameters: Int32U RegAddr, Int32U Data
 *
 * Return: none
 *
 * Description: Write to UDC2 registers
 *
 *************************************************************************/
static
void _UDC2_WriteByte (Int32U RegAddr, Int32U Data)
{
volatile Int8U * pReg = (volatile Int8U *)RegAddr;
Int32U save;
  ENTR_CRT_SECTION(save);
  *pReg = Data;
  while(UDC2RDREQ_bit.udc2rdreq);
  UDINTSTS = _bmUSB_UDC2_AccCompInterrupt;
  EXT_CRT_SECTION(save);
}

/*************************************************************************
 * Function Name: _UDC2_Read
 * Parameters: Int32U RegAddr
 *
 * Return: Int16U
 *
 * Description: Read from UDC2 registers
 *
 *************************************************************************/
static
Int16U _UDC2_Read (Int32U RegAddr)
{
Int32U save;
Int16U data;
  ENTR_CRT_SECTION(save);
  RegAddr &= _UDC2AB_READ_ADDRESS_MASK;
  RegAddr |= _UDC2AB_READ_REQ_MASK;
  UDC2RDREQ = RegAddr;
  while(UDC2RDREQ_bit.udc2rdreq);
  UDINTSTS = _bmUSB_UDC2_AccCompInterrupt;
  data = UDC2RDVL;
  EXT_CRT_SECTION(save);
  return(data);
}

/*************************************************************************
 * Function Name: _UDC2_Cmd
 * Parameters: Int32U Ep, UD2_Cmd_t Cmd
 *
 * Return: none
 *
 * Description: Send command to UDC2 engine
 *
 *************************************************************************/
static
void _UDC2_Cmd(Int32U Ep, UD2_Cmd_t Cmd)
{
Int16U reg;
  reg = ((Ep<<4) & 0xF0UL) | Cmd;
  _UDC2_Write((Int32U)&UD2CMD,reg);
}

/*************************************************************************
 * Function Name: USB_HwInit
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init USB
 *
 *************************************************************************/
void USB_HwInit(void)
{
#define _SYSCR_BASE_ADDR   (0xF0050000)
#define _CLKCR4         (*(volatile unsigned int *)(_SYSCR_BASE_ADDR + 0x0050))
#define USB_ENABLE              0x00000001

  TRACE("-I- USB HwInit\n\r");

  // Init SOF number hold
  #if  USB_SOF_EVENT > 0
  USB_SofNumbHold = 0;
  #endif

  // Init clocks
  if(SYSCR5_bit.PROTECT)
  {
    // System registers unlock
    SYSCR6 = 0x5A;
    SYSCR7 = 0xA5;
    SYSCR6 = 0xA5;
    SYSCR7 = 0x5A;
  }

  // Clk init
#if 0 < USB_EXT_CLK_SEL
  SYSCR0_bit.USBCLKSEL = 2;
#else
  SYSCR0_bit.USBCLKSEL = 1;
#endif

  //_CLKCR4 = USB_ENABLE;

  // System registers lock
  SYSCR6 = 0x5A;
  SYSCR7 = 0xA5;
  SYSCR6 = 0xA5;
  SYSCR7 = 0x5A;

  // Disable USB interrupts
  VICINTENCLEAR = (1UL<<_INTR_USB);
  UDINTENB      = 0;
  // Disable master transfer
  UDMSTSET      = 0;

  // Disconnect device
  USB_ConnectRes(FALSE);

  // clear all pending interrupts
  UDINTSTS = 0x23FE0700;
  _UDC2_Write((Int32U)&UD2INT,0x0000FFFF);
  // Init controls endpoints
  USB_HwReset();
  // Init Device status
  UsbSetDevState(UsbDevStatusUnknow);

  // Enable USB interrupts
  // USB interrupt connect to VIC
  // USB interrupt enable
  VIC_SetVectoredIRQ(USB_ISR,USB_INTR_PRIORITY,_INTR_USB);
  VICINTENABLE = (1<<_INTR_USB);
}

/*************************************************************************
 * Function Name: USB_HwReset
 * Parameters: none
 *
 * Return: none
 *
 * Description: Reset USB engine
 *
 *************************************************************************/
void USB_HwReset (void)
{
  TRACE("-I- USB HwReset\n\r");
  // Disable all endpoint interrupts
  _UDC2_Write((Int32U)&UD2INTEPMSK,0xF);
  // Disable all endpoints
  _UDC2_Cmd(0,_All_EP_Invalid);
  // Reset Master transfer
  UDMSTSET = (1UL << 2) | (1UL << 6);

  for(Int32U i = 0; i < ENP_MAX_NUMB; ++i)
  {
    EpCnfg[i].MaxSize = 0;
  }

  // Control EP Init
  USB_RealizeEp(&USB_CtrlEpDescr0,&USB_CtrlEpExtDescr0,TRUE);
  USB_RealizeEp(&USB_CtrlEpDescr1,&USB_CtrlEpExtDescr1,TRUE);

  // Enable Device interrupts
  UDINTENB_bit.suspend_resume_en = 1;
  UDINTENB_bit.usb_reset_end_en  = 1;
  UDINTENB_bit.usb_reset_en      = 0;
  // Disable NAK interrupt
  _UDC2_Write((Int32U)&UD2INT,
                 _bmUDC2_NAK_Mask_Interrupt
               | ((0 == USB_SOF_EVENT)?_bmUDC2_SOF_Mask_Interrupt:0)
             );
  // Disable NAK interrupt
  _UDC2_Write((Int32U)&UD2INTNAKMSK,0xE);
}

/*************************************************************************
 * Function Name: USB_RealizeEp
 * Parameters: const UsbStandardEpDescriptor_t * pEP_Desc,
 *             const UsbEP_ExtData_t * pUsbEP_ExtData,
 *             Boolean Enable
 *
 * Return: USB_ErrorCodes_t
 *
 * Description: Enable or disable an endpoint
 *
 *************************************************************************/
USB_ErrorCodes_t USB_RealizeEp(const UsbStandardEpDescriptor_t * pEP_Desc,
                               const UsbEP_ExtData_t * pUsbEP_ExtData,
                               Boolean Enable)
{
USB_Endpoint_t ep = (USB_Endpoint_t)USB_EpLogToPhysAdd(pEP_Desc->bEndpointAddress);
Int32U mask = (1 << (ep>>1));
Int32U addr = (Int32U)&UD2EP0MSZ;
Int32U mode;
  addr += ((Int32U)&UD2EP1MSZ-(Int32U)&UD2EP0MSZ)*(ep>>1);
  if (Enable)
  {
    TRACE("-I- USB Realize EP 0x%X, MaxSize %d\n\r",
           pEP_Desc->bEndpointAddress,
           pEP_Desc->wMaxPacketSize);
    // Set EP status
    EpCnfg[ep].Status  = NOT_READY;
    // Init EP flags
    EpCnfg[ep].Flags = 0;
    EpCnfg[ep].bDMA_Transfer   = pUsbEP_ExtData->Master_Transfer;
    EpCnfg[ep].bDoubleBuffered = pUsbEP_ExtData->DoubleBuffered;
    // Set endpoint type
    EpCnfg[ep].EpType = (UsbEpTransferType_t)pEP_Desc->bmAttributes.TransferType;
    // Init EP max packet size
    EpCnfg[ep].MaxSize = pEP_Desc->wMaxPacketSize;
    // EP base address
    EpCnfg[ep].EpAddrBase = addr;

    switch(ep>>1)
    {
    case 0:
      mode = 0;
      break;
    case 1:
      if(   (0 == (pEP_Desc->bEndpointAddress & 0x80))
         || (UsbEpTransferBulk != pEP_Desc->bmAttributes.TransferType))
      {
        return(USB_EP_NOT_VALID);
      }
      if(EpCnfg[ep].bDoubleBuffered)
      {
        mode = 0x8088;
      }
      else
      {
        mode = 0x0088;
      }
      break;
    case 2:
      if(   (pEP_Desc->bEndpointAddress & 0x80)
         || (UsbEpTransferBulk != pEP_Desc->bmAttributes.TransferType))
      {
        return(USB_EP_NOT_VALID);
      }
      if(EpCnfg[ep].bDoubleBuffered)
      {
        mode = 0x8008;
      }
      else
      {
        mode = 0x0008;
      }
      break;
    case 3:
      if(   (0 == (pEP_Desc->bEndpointAddress & 0x80))
         || (UsbEpTransferInterrupt != pEP_Desc->bmAttributes.TransferType)
         || EpCnfg[ep].bDoubleBuffered)
      {
        return(USB_EP_NOT_VALID);
      }
      mode = 0x008C;
      break;
    default:
      return(USB_EP_NOT_VALID);
    }
    // Reset EP
    _UDC2_Cmd(ep>>1,_EP_Reset);
    // Set Size
    _UDC2_Write(addr,pEP_Desc->wMaxPacketSize);
    // Set Mode
    _UDC2_Write(addr+4,mode);
    // Enable Interrupts
    mode = _UDC2_Read((Int32U)&UD2INTEPMSK);
    mode &= 0xF;
    mode |= mask;
    _UDC2_Write((Int32U)&UD2INTEPMSK,0xF);
  }
  else
  {
    TRACE("-I- USB Disable EP 0x%X\n\r",
           pEP_Desc->bEndpointAddress);
    // Disable relevant endpoint and interrupt
    _UDC2_Cmd(ep>>1,_EP_Disable);
    mode  = _UDC2_Read((Int32U)&UD2INTEPMSK);
    mode &= 0xF;
    mode &= ~mask;
    _UDC2_Write((Int32U)&UD2INTEPMSK,0xF);
    EpCnfg[ep].MaxSize = 0;
  }
  return(USB_OK);
}

/*************************************************************************
 * Function Name: USB_SetAdd
 * Parameters: Int32U DevAdd - device address between 0 - 127
 *
 * Return: none
 *
 * Description: Set device address
 *
 *************************************************************************/
Int32U addr_hold;
Int32U enable;
void USB_SetAdd(Int32U DevAdd)
{
Int16U reg;
  TRACE("-I- USB Set Address %d\n\r",DevAdd);
  reg  = _UDC2_Read((Int32U)&UD2ADR);
  reg &= ~((7UL << 8) | (0x7FUL));
  if (DevAdd)
  {
    enable = 1;
    reg |= (DevAdd & 0x7FUL) | (2UL << 8);
  }
  else
  {
    // default address
    reg |= (1UL << 8);

  }
  _UDC2_Write((Int32U)&UD2ADR,reg);
  if(enable)
  {
    enable = 0;
    addr_hold  = _UDC2_Read((Int32U)&UD2ADR);
  }
}

/*************************************************************************
 * Function Name: USB_ConnectRes
 * Parameters: Boolean Conn
 *
 * Return: none
 *
 * Description: Connect USB
 *
 *************************************************************************/
void USB_ConnectRes (Boolean Conn)
{
  if(Conn)
  {
    TRACE("-I- USB Enable Pullup\n\r");
    _UDC2_Cmd(0,_USB_Ready);
  }
  else
  {
    TRACE("-I- USB Disable Pullup\n\r");
    // USB Power Reset
    UDPWCTL = 0;
    for(volatile Int32U i = 1000; i; i--);
    UDPWCTL = (1UL << 1) | (1UL << 5);
    for(volatile Int32U i = 1000; i; i--);
  }
}

/*************************************************************************
 * Function Name: USB_Configure
 * Parameters: Boolean Configure
 *
 * Return: none
 *
 * Description: Configure device
 *              When Configure != 0 enable all Realize Ep
 *
 *************************************************************************/
void USB_Configure (Boolean Configure)
{
Int16U reg;
  if(Configure)
  {
    reg  = _UDC2_Read((Int32U)&UD2ADR);
    reg &= ~(7UL << 8);
    TRACE("-I- USB Configure\n\r");
    reg |= (4UL << 8);
    _UDC2_Write((Int32U)&UD2ADR,reg);
  }
}

#if USB_REMOTE_WAKEUP != 0
/*************************************************************************
 * Function Name: USB_WakeUp
 * Parameters: none
 *
 * Return: none
 *
 * Description: Wake up USB
 *
 *************************************************************************/
void USB_WakeUp (void)
{
  TRACE("-I- USB Remote wakeup\n\r");
  UDPWCTL |= 1UL << 6;
}
#endif // USB_REMOTE_WAKEUP != 0

/*************************************************************************
 * Function Name: USB_GetDevStatus
 * Parameters: USB_DevStatusReqType_t Type
 *
 * Return: Boolean
 *
 * Description: Return USB device status
 *
 *************************************************************************/
Boolean USB_GetDevStatus (USB_DevStatusReqType_t Type)
{
  switch (Type)
  {
  case USB_DevConnectStatus:
    return(USB_DevStatus.Connect);
  case USB_SuspendStatus:
    return(USB_DevStatus.Suspend);
  case USB_ResetStatus:
    return(USB_DevStatus.Reset);
  }
  return(FALSE);
}

/*************************************************************************
 * Function Name: USB_SetStallEP
 * Parameters: USB_Endpoint_t EndPoint, Boolean Stall
 *
 * Return: none
 *
 * Description: The endpoint stall/unstall
 *
 *************************************************************************/
void USB_SetStallEP (USB_Endpoint_t EP, Boolean Stall)
{
Boolean CurrStallStatus;
  assert(EpCnfg[EP].MaxSize);  // check whether is a realized EP

  _UDC2_Cmd(EP>>1,_EP_Stall);

  USB_GetStallEP(EP,&CurrStallStatus);
  if(CurrStallStatus != Stall)
  {
    if(Stall)
    {
      TRACE("-I- USB Stall EP 0x%X\n\r",(EP&1)?(EP>>1) | 0x80:(EP>>1));
      _UDC2_Cmd(EP>>1,_EP_Stall);
    }
    else
    {
      TRACE("-I- USB Unstall EP 0x%X\n\r",(EP&1)?(EP>>1) | 0x80:(EP>>1));
      _UDC2_Cmd(EP>>1,_EP_Reset);
    }
  }
}

/*************************************************************************
 * Function Name: USB_StallCtrlEP
 * Parameters: none
 *
 * Return: none
 *
 * Description: Stall both direction of the CTRL EP
 *
 *************************************************************************/
void USB_StallCtrlEP (void)
{
  TRACE("-I- USB Stall Ctrl EP\n\r");
  _UDC2_Cmd(0,_EP_Stall);
}

/*************************************************************************
 * Function Name: USB_GetStallEP
 * Parameters: USB_Endpoint_t EndPoint, pBoolean pStall
 *
 * Return: none
 *
 * Description: Get stall state of the endpoint
 *
 *************************************************************************/
void USB_GetStallEP (USB_Endpoint_t EP, pBoolean pStall)
{
  assert(EpCnfg[EP].MaxSize);  // check whether is a realized EP
  *pStall = (0x3U<<9) == ((0x7U<<9)
                          & _UDC2_Read((Int32U)(EpCnfg[EP].EpAddrBase+4)));
}

/*************************************************************************
 * Function Name: USB_EP_IO
 * Parameters: USB_Endpoint_t EndPoint
 *
 * Return: none
 *
 * Description: Endpoint Write (IN)
 *
 *************************************************************************/
void USB_EP_IO(USB_Endpoint_t EP)
{

Int16U Data;
Int32U Count;
Int32U EpFifo;
Boolean SendCmd;

  assert(EpCnfg[EP].MaxSize);  // check whether is a realized EP

  if(EpCnfg[EP].Status != BEGIN_SERVICED &&
     EpCnfg[EP].Status != NO_SERVICED)
  {
    return;
  }
  Data    = _UDC2_Read((Int32U)EpCnfg[EP].EpAddrBase);
  EpFifo = (Int32U)(EpCnfg[EP].EpAddrBase + 12);
  if(EP & 1)
  {
    // IN
    Count   = EpCnfg[EP].Size - EpCnfg[EP].Offset;
    while(0 == ((1UL << 12) & Data))
    {
      if(Count == 0 && !EpCnfg[EP].bZeroPacket)
      {
        break;
      }

      SendCmd = FALSE;

      // Set Status
      EpCnfg[EP].Status = BEGIN_SERVICED;
      // Get data size
      if(EpCnfg[EP].bZeroPacketPossible && Count == EpCnfg[EP].MaxSize)
      {
        EpCnfg[EP].bZeroPacketPossible = 0;
        EpCnfg[EP].bZeroPacket = 1;
      }

      if(Count >= EpCnfg[EP].MaxSize)
      {
        Count = EpCnfg[EP].MaxSize;
      }
      else
      {
        SendCmd = TRUE;
      }
      Int32U Offset = EpCnfg[EP].Offset;
      EpCnfg[EP].Offset += Count;
      TRACE("-I- USB Write %d to EP 0x%X\n\r",Count,(EP&1)?(EP>>1) | 0x80:(EP>>1));
      // Write data to SIE buffer
      if(Count)
      {
        do
        {
          Data = *(EpCnfg[EP].pBuffer+Offset++);
          if (--Count)
          {
            Data |= (Int32U)(*(EpCnfg[EP].pBuffer+Offset++))<<8;
            --Count;
            // Short access
            _UDC2_Write(EpFifo,Data);
          }
          else
          {
            // Byte access
            _UDC2_WriteByte(EpFifo,Data);
          }
        }
        while (Count);
      }
      else
      {
        EpCnfg[EP].bZeroPacket = 0;
        SendCmd = TRUE;
      }

      if(   (1 == EP)
         && (1UL << 15) & _UDC2_Read((Int32U)(EpCnfg[EP].EpAddrBase+4)))
      {
        EpCnfg[EP].Status = SETUP_OVERWRITE;
        return;
      }

      if(SendCmd)
      {
        _UDC2_Cmd(EP>>1,_EP_EOP);
      }
      Count = EpCnfg[EP].Size - EpCnfg[EP].Offset;
      Data  = _UDC2_Read((Int32U)EpCnfg[EP].EpAddrBase);
    }

    if(!EpCnfg[EP].bZeroPacket && !Count)
    {
      EpCnfg[EP].Status = COMPLETE;
      //call callback function
      if(EpCnfg[EP].pFn)
      {
        ((void(*)(USB_Endpoint_t))EpCnfg[EP].pFn)(EP);
      }
    }
  }
  else
  {
    // OUT
    while((1UL << 12) & Data)
    {
      // Get data size
      Count = _UDC2_Read((Int32U)(EpCnfg[EP].EpAddrBase+8));
      if(Count > (EpCnfg[EP].Size - EpCnfg[EP].Offset))
      {
        EpCnfg[EP].Status = BUFFER_OVERRUN;
        EpCnfg[EP].Size = EpCnfg[EP].Offset;
        break;
      }
      else if (Count < EpCnfg[EP].MaxSize)
      {
        EpCnfg[EP].Status = BUFFER_UNDERRUN;
        EpCnfg[EP].Size = EpCnfg[EP].Offset + Count;
      }
      else
      {
        EpCnfg[EP].Status = BEGIN_SERVICED;
      }

      Int32U Offset = EpCnfg[EP].Offset;
      EpCnfg[EP].Offset += Count;

      TRACE("-I- USB Read %d from EP 0x%X\n\r",Count,(EP&1)?(EP>>1) | 0x80:(EP>>1));

      // Read data from SIE buffer
      do
      {
        //assert(RCVEPKTLEN_bit.DV);
        Data = _UDC2_Read(EpFifo);
        // because zero lenght packe is possible
        if(Count)
        {
          *(EpCnfg[EP].pBuffer+Offset++) = Data;
          if (--Count)
          {
            Data >>= 8;
            *(EpCnfg[EP].pBuffer+Offset++) = Data;
            --Count;
          }
        }
      }
      while (Count);

      if(   (0 == EP)
         && (1UL << 15) & _UDC2_Read((Int32U)(EpCnfg[EP].EpAddrBase+4)))
      {
        EpCnfg[EP].Status = SETUP_OVERWRITE;
        return;
      }

      if (!(Count = (EpCnfg[EP].Size - EpCnfg[EP].Offset)))
      {
        EpCnfg[EP].Status = COMPLETE;
        break;
      }
      Data  = _UDC2_Read((Int32U)EpCnfg[EP].EpAddrBase);
    }

    if (EpCnfg[EP].Status != BEGIN_SERVICED && EpCnfg[EP].Status != NO_SERVICED)
    {
      //call callback function
      if(EpCnfg[EP].pFn)
      {
        ((void(*)(USB_Endpoint_t))EpCnfg[EP].pFn)(EP);
      }
    }
  }
}

/*************************************************************************
 * Function Name: USB_EpLogToPhysAdd
 * Parameters: Int8U EpLogAdd
 *
 * Return: USB_Endpoint_t
 *
 * Description: Convert the logical to physical address
 *
 *************************************************************************/
USB_Endpoint_t USB_EpLogToPhysAdd (Int8U EpLogAdd)
{
USB_Endpoint_t Address = (USB_Endpoint_t)((EpLogAdd & 0x0F)<<1);
  if(0x80 & EpLogAdd)
  {
    ++Address;
  }
  return(Address);
}

#if USB_SOF_EVENT > 0
/*************************************************************************
 * Function Name: USB_GetFrameNumb
 * Parameters: none
 *
 * Return: Int32U
 *
 * Description: Return current value of SOF number
 *
 *************************************************************************/
Int32U USB_GetFrameNumb (void)
{
  return(USB_SofNumbHold & 0x3FF);
}
#endif

/*************************************************************************
 * Function Name: USB_StatusPhase
 * Parameters: Boolean In
 *
 * Return: none
 *
 * Description: Prepare status phase
 *
 *************************************************************************/
void USB_StatusPhase (Boolean In)
{
  TRACE("-I- USB Setup status enable\n\r");
  _UDC2_Cmd(0,_Setup_Fin);
}

/*************************************************************************
 * Function Name: USB_ISR
 * Parameters: none
 *
 * Return: none
 *
 * Description: USB interrupt subroutine
 *
 *************************************************************************/
void USB_ISR (void)
{
Int32U val;
Int32U udc2_intr;

  USB_INTR_ENTRY_HOOK();

  if(UDINTSTS_bit.int_suspend_resume)
  {
    UDINTSTS = _bmUSB_SuspendResumeInterrupt;
    TRACE("-I- USB Suspend/Resume\n\r");
    UsbDevSuspendCallback(0 == UDPWCTL_bit.suspend_x);
  }
  else if(UDINTSTS_bit.int_usb_reset_end)
  {
    UDINTSTS = _bmUSB_ResetEndInterrupt;
    TRACE("-I- USB Reset end\n\r");
    USB_HwReset();
    UsbDevConnectCallback(TRUE);
    UsbDevResetCallback();
  }
  else if (UDINTSTS_bit.int_ep)
  {
    TRACE("-I- USB EP interrupt\n\r");
    val = _UDC2_Read((Int32U)&UD2INTEP);
    if ((1UL<<1) & val)
    {
      _UDC2_Write((Int32U)&UD2INTEP,(1UL<<1));
      // EP1 IN
      USB_EP_IO(ENP1_IN);
    }
    if((1UL<<2) & val)
    {
      // EP2 OUT
      _UDC2_Write((Int32U)&UD2INTEP,(1UL<<2));
      USB_EP_IO(ENP2_OUT);
    }
    if((1UL<<3) & val)
    {
      _UDC2_Write((Int32U)&UD2INTEP,(1UL<<3));
      // EP3 IN
      USB_EP_IO(ENP3_IN);
    }
  }
#if USB_SOF_EVENT > 0
  else if (UDINTSTS_bit.int_sof)
  {
    // Clear Interrupt flag
    udc2_intr  = _UDC2_Read((Int32U)&UD2INT);
    udc2_intr &= UDC2_INTR_CLEAR_MAKS;
    udc2_intr |= _bmUDC2_SOF_Interrupt;
    _UDC2_Write((Int32U)&UD2INT,udc2_intr);
    USB_SofNumbHold = _UDC2_Read((Int32U)&UD2FRM);
    if((0x1UL<<12)== (USB_SofNumbHold & (0x3UL<<12)))
    {
    #if USB_SOF_FRAME_NUMB > 0
      USB_FRAME_HOOK(0x3FF & USB_SofNumbHold);
    #else
      USB_FRAME_HOOK(0);
    #endif
    }

  }
#endif // USB_SOF_EVENT > 0
  else if (UDINTSTS_bit.int_setup)
  {
    // Clear Interrupt flag
    udc2_intr  = _UDC2_Read((Int32U)&UD2INT);
    udc2_intr &= UDC2_INTR_CLEAR_MAKS;
    udc2_intr |= _bmUDC2_SetupInterrupt;
    _UDC2_Write((Int32U)&UD2INT,udc2_intr);
    TRACE("-I- USB Setup\n\r");

    // Read Setup packet data
    for(Int32U i = 0, setup_addr = (Int32U)&UD2BRQ;
               i < sizeof(UsbEp0SetupPacket);
               setup_addr+=4)
    {
      Int16U Data;
      Data = _UDC2_Read(setup_addr);
      UsbEp0SetupPacket.Data[i++] = Data;
      UsbEp0SetupPacket.Data[i++] = Data>>8;
    }
    // UDC2 Setup AKN
    _UDC2_Cmd(0,_Setup_Received);

    // reset pending IN data
    USB_IO_Data(CTRL_ENP_IN,NULL,(Int32U)-1,NULL);
    // Prepare status OUT phase
    if (   (UsbDevice2Host == UsbEp0SetupPacket.mRequestType.Dir)
        && (0              == UsbEp0SetupPacket.wLength.Word)
       )
    {
      USB_StatusHandler(CTRL_ENP_OUT);
    }

    // Processing Setup packet
    USB_SetupHandler();

    if(STALLED == EpCnfg[CTRL_ENP_OUT].Status)
    {
      // Error or unsupported request
      USB_StallCtrlEP();
    }
  }
  else if (UDINTSTS_bit.int_status_nak)
  {
    // Clear Interrupt flag
    udc2_intr  = _UDC2_Read((Int32U)&UD2INT);
    udc2_intr &= UDC2_INTR_CLEAR_MAKS & ~_bmUDC2_StatusNAK_MaskInterrupt;
    udc2_intr |= _bmUDC2_StatusNAK_Interrupt | _bmUDC2_StatusNAK_MaskInterrupt;
    _UDC2_Write((Int32U)&UD2INT,udc2_intr);
    TRACE("-I- USB Status NAK\n\r");
    _UDC2_Cmd(0,_Setup_Fin);
    if(UsbEp0SetupPacket.mRequestType.Dir == UsbDevice2Host &&
       EpCnfg[CTRL_ENP_OUT].pFn)
    {
      ((void(*)(USB_Endpoint_t))EpCnfg[CTRL_ENP_OUT].pFn)(CTRL_ENP_OUT);
    }
    else if(UsbEp0SetupPacket.mRequestType.Dir == UsbHost2Device &&
       EpCnfg[CTRL_ENP_IN].pFn)
    {
      ((void(*)(USB_Endpoint_t))EpCnfg[CTRL_ENP_IN].pFn)(CTRL_ENP_IN);
    }
  }
  else if (UDINTSTS_bit.int_status)
  {
    // Clear Interrupt flag
    udc2_intr  = _UDC2_Read((Int32U)&UD2INT);
    udc2_intr &= UDC2_INTR_CLEAR_MAKS;
    udc2_intr |= _bmUDC2_StatusInterrupt | _bmUDC2_StatusNAK_MaskInterrupt;
    _UDC2_Write((Int32U)&UD2INT,udc2_intr);
    // Status phase callback function call
    TRACE("-I- USB Status End\n\r");
    if(UsbEp0SetupPacket.mRequestType.Dir == UsbDevice2Host &&
       EpCnfg[CTRL_ENP_OUT].pFn)
    {
      ((void(*)(USB_Endpoint_t))EpCnfg[CTRL_ENP_OUT].pFn)(CTRL_ENP_OUT);
    }
    else if(UsbEp0SetupPacket.mRequestType.Dir == UsbHost2Device &&
       EpCnfg[CTRL_ENP_IN].pFn)
    {
      ((void(*)(USB_Endpoint_t))EpCnfg[CTRL_ENP_IN].pFn)(CTRL_ENP_IN);
    }
  }
  else if (UDINTSTS_bit.int_ep0)
  {
    TRACE("-I- USB Cntrl EP interrupt\n\r");
    udc2_intr  = _UDC2_Read((Int32U)&UD2INT);
    udc2_intr &= UDC2_INTR_CLEAR_MAKS;
    udc2_intr |= _bmUDC2_EP0_Interrupt;
    _UDC2_Write((Int32U)&UD2INT,udc2_intr);

    if(UsbEp0SetupPacket.mRequestType.Dir == UsbDevice2Host)
    {
      USB_EP_IO(CTRL_ENP_IN);
    }
    else
    {
      USB_EP_IO(CTRL_ENP_OUT);
    }
  }
  else if (UDINTSTS_bit.int_rx_zero)
  {
    val = _UDC2_Read((Int32U)&UD2INTRX0);
    for(Int32U i = CTRL_ENP_OUT;
        (i < ENP_MAX_NUMB) && val;
         i +=2)
    {
      Int32U mask = 1UL << (i>>1);
      if(mask & val)
      {
        _UDC2_Write((Int32U)&UD2INTRX0,mask);
        USB_EP_IO((USB_Endpoint_t)i);
        val &= ~mask;
      }
    }
  }

  USB_INTR_EXIT_HOOK();
  VICADDRESS = 0;    // Clear interrupt in VIC.
}
