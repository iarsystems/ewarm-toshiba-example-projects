/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : audio_class.c
 *    Description : AUDIO CLASS module
 *
 *    History :
 *    1. Date        : April 7, 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 41 $
 **************************************************************************/
#define AUDIO_CLASS_GLOBAL
#include "audio_class.h"

extern void NVIC_IntEnable(Int32U IntNumber);
extern void NVIC_IntDisable(Int32U IntNumber);
extern void NVIC_ClrPend(Int32U IntNumber);
extern void NVIC_IntPri(Int32U IntNumber, Int8U Priority);

volatile Boolean SampEna;
Int32U  SampCount,SampPeriod,Delta;
pInt16S pSpkData;
Int32U  SampPerCurrHold,DeltaPer;

const Int32U VolumeMul [] =
{
  //-46dB- 0x0
  2,
  //-45dB- 0x1
  2,
  //-44dB- 0x2
  3,
  //-43dB- 0x3
  3,
  //-42dB- 0x4
  3,
  //-41dB- 0x5
  4,
  //-40dB- 0x6
  4,
  //-39dB- 0x7
  4,
  //-38dB- 0x8
  5,
  //-37dB- 0x9
  6,
  //-36dB- 0xA
  6,
  //-35dB- 0xB
  7,
  //-34dB- 0xC
  8,
  //-33dB- 0xD
  9,
  //-32dB- 0xE
  10,
  //-31dB- 0xF
  11,
  //-30dB- 0x10
  13,
  //-29dB- 0x11
  14,
  //-28dB- 0x12
  16,
  //-27dB- 0x13
  18,
  //-26dB- 0x14
  20,
  //-25dB- 0x15
  22,
  //-24dB- 0x16
  25,
  //-23dB- 0x17
  28,
  //-22dB- 0x18
  32,
  //-21dB- 0x19
  36,
  //-20dB- 0x1A
  40,
  //-19dB- 0x1B
  45,
  //-18dB- 0x1C
  50,
  //-17dB- 0x1D
  56,
  //-16dB- 0x1E
  63,
  //-15dB- 0x1F
  71,
  //-14dB- 0x20
  80,
  //-13dB- 0x21
  90,
  //-12dB- 0x22
  100,
  //-11dB- 0x23
  113,
  //-10dB- 0x24
  126,
  //-9dB - 0x25
  142,
  //-8dB - 0x26
  159,
  //-7dB - 0x27
  179,
  //-6dB - 0x28
  200,
  //-5dB - 0x29
  225,
  //-4dB - 0x2A
  252,
  //-3dB - 0x2B
  283,
  //-2dB - 0x2C
  318,
  //-1dB - 0x2D
  357,
  // 0dB - 0x2E
  400
};

#pragma segment="USB_DMA_RAM"
#pragma location="USB_DMA_RAM"
#pragma data_alignment=4
__no_init Int16S AudioSpkData[SampRerFrame * 3];

#pragma data_alignment=4
Int8U AudioBuf[2];

Int8U   AudioRequest,AudioCS,AudioCN,AudioId;
Int16U  AudioDataSize;

Int16S  AudioFeat1Vol;
Int32U  AudioSpkVolMul;
Boolean AudioFeat1Mute;

/*************************************************************************
 * Function Name: UsbAudioClassInit
 * Parameters: none
 *
 * Return: none
 *
 * Description: USB Class Audio Init
 *
 *************************************************************************/
void UsbAudioClassInit (void)
{
volatile int dummy;
// Init Audio Class variables
  SampEna         =\
  AudioFeat1Mute  = FALSE;
  SampCount       =\
  AudioFeat1Vol   = 0;
  AudioSpkVolMul = (VolumeMul[((AudioFeat1Vol-(Int16S)Feat1MinVol))]);  pSpkData        = AudioSpkData;
  SampPerCurrHold = SampPeriod;
 
  /*Enable TMR0 module*/
  TB0EN_bit.TBEN = 1;
  /*Double buffer*/
  TB0CR_bit.TBWBF = 1;
  /*Synchronous mode off*/
  TB0CR_bit.TBSYNC = 0;
  /*Count start by software*/
  TB0CR_bit.CSSEL = 0;
  /*Select clock T0/2*/
  TB0MOD_bit.TBCLK = 1;
  /*TB0RG1 match clears the timer*/
  TB0MOD_bit.TBCLE = 1;
  /*Disable capture*/
  TB0MOD_bit.TBCPM = 0;
  /*Disable flip-flop reverse by capture */
  TB0FFCR_bit.TBC1T1 = 0;
  TB0FFCR_bit.TBC0T1 = 0;
  /*Enable flip-flop reverse on match*/
  TB0FFCR_bit.TBE1T1 = 1;
  TB0FFCR_bit.TBE0T1 = 1;
  
  SampPeriod = (CG_GetClock(CLK_TO)/2)/SampFreq;
  DeltaPer = SampPeriod/(SampRerFrame*2);

  /*Set Timer Period*/
  TB0RG1 = SampPeriod;
  /**/
  TB0RG0 = SampPeriod/2;
  /*clear flip-flop*/
  TB0FFCR_bit.TBFF0C = 2;
  /*dummy status read*/
  dummy = TB0ST;
  /*Interrupt enable*/
  TB0IM_bit.TBIM1 = 1;
  NVIC_IntEnable(INT_TB0);
  /*Highest priority*/
  NVIC_IntPri(INT_TB0,0);
  
  /*PWM Output configure*/
  PWM_FR |= PWM_OUT;
  PWM_CR |= PWM_OUT;
  /*Start timer*/
  TB0RUN = 5;
  
  UsbClassAudioConfigure(NULL);
  UsbCoreInit();
}

/*************************************************************************
 * Function Name: UsbClassAudioConfigure
 * Parameters:  pUsbDevCtrl_t pDev
 *
 * Return: none
 *
 * Description: USB Class Audio configure
 *
 *************************************************************************/
void UsbClassAudioConfigure (pUsbDevCtrl_t pDev)
{
  if(pDev == NULL)
  {
    if(UsbCoreReq(UsbCoreReqConfiquration) != 0)
    {
      SampEna = FALSE;
    }
  }
  else
  {
    if((pDev->Configuration == 1))
    {
      if (pDev->AlternateSetting[USB_SPK_INTERFACE] == 1)
      {
        pSpkData = AudioSpkData;
        Delta = 0;
        USB_IO_Data( SpkEp,
                    (pInt8U)AudioSpkData,
                     SpkEpMaxSize,
                    (void*)AudioInHadler);
      }
    }
  }
}

/*************************************************************************
 * Function Name: AudioInHadler
 * Parameters:  USB_Endpoint_t EP
 *
 * Return: none
 *
 * Description: USB Class Audio Out EP handler
 *
 *************************************************************************/
static
void AudioInHadler (USB_Endpoint_t EP)
{
#if __CORE__ < 7
  Int32U save;
#endif // __CORE__ < 7
  assert(SpkEp == EP);

  pSpkData += EpCnfg[EP].Size/sizeof(Int16U);
  if(pSpkData >= AudioSpkData + sizeof(AudioSpkData)/sizeof(Int16U))
  {
    pSpkData = AudioSpkData;
  }

  if(SampEna)
  {
    // Adapt sample rate
    if (Delta > (SampRerFrame * SubFrameSize))
    {
      SampPerCurrHold = SampPeriod - DeltaPer;
    }
    else if (Delta < (SampRerFrame * SubFrameSize))
    {
      SampPerCurrHold = SampPeriod + DeltaPer;
    }
    else
    {
      SampPerCurrHold = SampPeriod;
    }
  }
  else
  {
    if(pSpkData >= (AudioSpkData + (sizeof(AudioSpkData))/(2*sizeof(Int16U))))
    {
      // Enable output
      SampCount = 0;
      SampEna   = TRUE;
    }
  }

  #if __CORE__ < 7
    ENTR_CRT_SECTION_F(save);
  #else
    ENTR_CRT_SECTION();
  #endif // __CORE__ < 7
  Delta  += EpCnfg[EP].Size;
  #if __CORE__ < 7
    EXT_CRT_SECTION(Save);
  #else
    EXT_CRT_SECTION();
  #endif // __CORE__ < 7

  USB_IO_Data(SpkEp,(pInt8U)pSpkData,SpkEpMaxSize,(void*)AudioInHadler);
}

/*************************************************************************
 * Function Name: TMR0_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description:
 *
 *************************************************************************/
void INTTB0_IRQHandler (void)
{
static union ValUnion
{
  Int32S Data;
  struct
  {
    Int16U DataLo;
    Int16S DataHi;
  };
} Val = {0x00000000};
volatile int dummy;

static int counter = 0;  
  
  /*dummy status read*/
  dummy = TB0ST;
  /*LED blink*/
  if(SampFreq/2 == ++counter)
  {
     counter = 0;
     LED_PORT ^= LED1;
  }

  if (SampEna)
  {
    if(Delta > 1)
    {
      // Get next input sample
      Val.Data = AudioSpkData[SampCount++];
      Delta   -= 2;
      // Correct pointer to sample buffer
      if(SampCount >= sizeof(AudioSpkData)/sizeof(Int16U))
      {
        SampCount = 0;
      }
      if(!AudioFeat1Mute)
      {
        // Apply volume
        Val.Data *= AudioSpkVolMul;
      }
      else
      {
        // set middle of range
        Val.DataHi = 0;
      }
    }
    else
    {
      // Disable output stream after emptying the buffer
      SampEna = FALSE;
      SampPerCurrHold = SampPeriod;
    }
  }
  else
  {
    SampPerCurrHold = SampPeriod;
  }
  
  /*Load result in the Match Register*/
  TB0RG0 =(Int16S)SampPeriod/2 + (Val.DataHi);
  /*Sample corection*/
  TB0RG1 = SampPerCurrHold;
}

/*************************************************************************
 * Function Name: AudioFeatureGetReg
 * Parameters:  Int32U CS, Int32U Id
 *
 * Return: Boolean
 *
 * Description:
 *
 *************************************************************************/
static
Boolean AudioFeatureGetReg (Int32U CS, Int32U Id)
{
  switch (CS)
  {
  case REQUEST_GET_CUR:
    // Load current value of Volume in the transmit buffer
    if (Id == FeatUnit1Id)
    {
      AudioBuf[1] = (AudioFeat1Vol>>8)& 0xFF;
      AudioBuf[0] =  AudioFeat1Vol    & 0xFF;
    }
    else
    {
      return(FALSE);
    }
    break;
  case REQUEST_GET_MIN:
    // Load minimum value of Volume in the transmit buffer
    if (Id == FeatUnit1Id)
    {
      AudioBuf[1] = (Feat1MinVol>>8)  & 0xFF;
      AudioBuf[0] =  Feat1MinVol      & 0xFF;
    }
    else
    {
      return(FALSE);
    }
    break;
  case REQUEST_GET_MAX:
    // Load maximum value of Volume in the transmit buffer
    if (Id == FeatUnit1Id)
    {
      AudioBuf[1] = (Feat1MaxVol>>8)  & 0xFF;
      AudioBuf[0] =  Feat1MaxVol      & 0xFF;
    }
    else
    {
      return(FALSE);
    }
    break;
  case REQUEST_GET_RES:
    // Load resolution value of Volume in the transmit buffer
    if (Id == FeatUnit1Id)
    {
      AudioBuf[1] = (Feat1ResVol>>8)  & 0xFF;
      AudioBuf[0] =  Feat1ResVol      & 0xFF;
    }
    else
    {
      return(FALSE);
    }
    break;
  default:
    return(FALSE);
  }
  return(TRUE);
}

/*************************************************************************
 * Function Name: UsbClassAudioRequest
 * Parameters:  pUsbSetupPacket_t pSetup
 *
 * Return: UsbCommStatus_t
 *
 * Description: USB Class Audio Requests
 *
 *************************************************************************/
UsbCommStatus_t UsbClassAudioRequest (pUsbSetupPacket_t pSetup)
{
  // Validate Request
  switch (pSetup->mRequestType.Recipient)
  {
  case UsbRecipientInterface:
    // Feature Unit requests only Imlement for interface 0
    if ((pSetup->wIndex.Word == (FeatUnit1Id << 8)))
    {
      // Request type
      switch (pSetup->wValue.Hi)
      {
      case FU_MUTE_CONTROL:
        if ((pSetup->bRequest == REQUEST_SET_CUR) &&
            (pSetup->wLength.Word == 1))
        {
          // Set mute flag
          AudioRequest  = pSetup->bRequest;
          AudioId       = pSetup->wIndex.Hi;
          AudioCS       = pSetup->wValue.Hi;
          AudioCN       = pSetup->wValue.Lo;
          AudioDataSize = pSetup->wLength.Word;
          USB_IO_Data(CTRL_ENP_OUT,
                      AudioBuf,
                      USB_T9_Size(1,pSetup->wLength.Word),
                     (void *)UsbClassAudioData);
          return(UsbPass);
        }
        else if ((pSetup->bRequest == REQUEST_GET_CUR) &&
                 (pSetup->wLength.Word == 1))
        {
          // Read mute flag
          AudioBuf[0]  = AudioFeat1Mute;
          USB_IO_Data(CTRL_ENP_IN,
                      AudioBuf,
                      USB_T9_Size(1,pSetup->wLength.Word),
                     (void *)USB_StatusHandler);
          return(UsbPass);
        }
        break;
      case FU_VOLUME_CONTROL:
        if(pSetup->bRequest & 0x80)
        {
          // Read different volume values
          if((pSetup->wLength.Word == 2) &&
              AudioFeatureGetReg(pSetup->bRequest,pSetup->wIndex.Hi))
          {
          USB_IO_Data(CTRL_ENP_IN,
                      AudioBuf,
                      USB_T9_Size(2,pSetup->wLength.Word),
                     (void *)USB_StatusHandler);
            return(UsbPass);
          }
        }
        else if((pSetup->bRequest == REQUEST_SET_CUR) &&
                (pSetup->wLength.Word  == 2))
        {
          // Set volume value
          AudioRequest  = pSetup->bRequest;
          AudioId       = pSetup->wIndex.Hi;
          AudioCS       = pSetup->wValue.Hi;
          AudioCN       = pSetup->wValue.Lo;
          AudioDataSize = pSetup->wLength.Word;
          USB_IO_Data(CTRL_ENP_OUT,
                      AudioBuf,
                      USB_T9_Size(2,pSetup->wLength.Word),
                     (void *)UsbClassAudioData);
          return(UsbPass);
        }
        break;
      }
    }
    // Selector Unit requests only Imlement for interface 0
    else if (pSetup->wIndex.Word == (SelUnit1ID << 8))
    {
      if(pSetup->wValue.Word == 0)
      {
        // Read different selector unit values
        if(pSetup->bRequest & 0x80)
        {
          if(pSetup->wLength.Word == 1)
          {
            AudioBuf[0] = 1;
            USB_IO_Data(CTRL_ENP_IN,
                        AudioBuf,
                        USB_T9_Size(1,pSetup->wLength.Word),
                       (void *)USB_StatusHandler);
            return(UsbPass);
          }
        }
        else
        {
          // Set channel
          AudioRequest  = pSetup->bRequest;
          AudioId       = pSetup->wIndex.Hi;
          AudioDataSize = pSetup->wLength.Word;
          USB_IO_Data(CTRL_ENP_OUT,
                      AudioBuf,
                      USB_T9_Size(1,pSetup->wLength.Word),
                     (void *)UsbClassAudioData);
          return(UsbPass);
        }
      }
    }
    return(UsbFault);
  case UsbRecipientEndpoint:
    return(UsbFault);
  }
  return(UsbFault);
}

/*************************************************************************
 * Function Name: UsbClassAudioData
 * Parameters:  USB_Endpoint_t EP
 *
 * Return: none
 *
 * Description: USB Class Audio Data receive
 *
 *************************************************************************/
static
void UsbClassAudioData (USB_Endpoint_t EP)
{
  if (EpCnfg[EP].Status != COMPLETE)
  {
    USB_StallCtrlEP();
    return;
  }
  if((AudioId == FeatUnit1Id))
  {
    switch (AudioCS)
    {
    case FU_MUTE_CONTROL:
      // Set mute flag
      if (AudioId == FeatUnit1Id)
      {
        AudioFeat1Mute = AudioBuf[0];
      }
      else
      {
        USB_StallCtrlEP();
        return;
      }
      break;
    case FU_VOLUME_CONTROL:
      // Set volume value
      if (AudioId == FeatUnit1Id)
      {
        AudioFeat1Vol = AudioBuf[0] + ((Int16U)AudioBuf[1]<<8);
        if((Int16U)AudioFeat1Vol == MinVol)
        {
          AudioSpkVolMul = 0;
        }
        else
        {
          if (AudioFeat1Vol < (Int16S)Feat1MinVol)
          {
            AudioFeat1Vol = Feat1MinVol;
          }
          else if(AudioFeat1Vol > (Int16S)Feat1MaxVol)
          {
            AudioFeat1Vol = Feat1MaxVol;
          }
          // -46dB - +0dB multiply
          AudioSpkVolMul = (VolumeMul[((AudioFeat1Vol-(Int16S)Feat1MinVol))]);
        }
      }
      else
      {
        USB_StallCtrlEP();
        return;
      }
      break;
    default:
      USB_StallCtrlEP();
      return;
    }
  }
  else if (AudioId == SelUnit1ID)
  {
    // empty
  }
  else
  {
    USB_StallCtrlEP();
    return;
  }
  USB_StatusHandler(CTRL_ENP_IN);
}
