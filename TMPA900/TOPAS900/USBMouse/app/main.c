/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2009
 *
 *    File name   : main.c
 *    Description : Main module
 *
 *    History :
 *    1. Date        : 2, September 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *   This example project shows how to use the IAR Embedded Workbench
 *  for ARM to develop code for the Toshiba TOPAS900 board. It implements USB
 *  HID mouse. The any button will resume USB if device is suspended.
 *   The joystick control up, down, left, right and left mouse button.
 *  Controls:
 *   Joystick    - left, right, up, down movement, center left button
 *
 *    $Revision: 41 $
 **************************************************************************/
#include "includes.h"

#define TIMER0_IN_FREQ        PCLK
#define TIMER0_TICK_PER_SEC   1000

#define MOUSE_DELTA           1

volatile Boolean SysTickFl;

/*************************************************************************
 * Function Name: IRQ_Handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: IRQ handler
 *
 *************************************************************************/
__irq __arm void IRQ_Handler(void)
{
void (*interrupt_function)();
unsigned int vector;

  vector = VICADDRESS;     // Get interrupt vector.
  interrupt_function = (void(*)())vector;
  if(interrupt_function != NULL)
  {
    interrupt_function();  // Call vectored interrupt function.
  }
  else
  {
    VICADDRESS = 0;      // Clear interrupt in VIC.
  }
}

/*************************************************************************
 * Function Name: Timer0IntrHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 0 interrupt handler
 *
 *************************************************************************/
void Timer0IntrHandler (void)
{
  Timer0IntClr = 0;         // clear timer interrupt
  SysTickFl = TRUE;
  VICADDRESS = 0;
}

/*************************************************************************
 * Function Name: VIC_SetVectoredIRQ
 * Parameters:  void(*pIRQSub)()
 *              unsigned int VicIrqSlot
 *              unsigned int VicIntSouce
 *
 * Return: void
 *
 * Description:  Init vectored interrupts
 *
 *************************************************************************/
void VIC_SetVectoredIRQ(void(*pIRQSub)(), unsigned int Priority,
                        unsigned int VicIntSource)
{
unsigned long volatile *pReg;
  // load base address of vectored address registers
  pReg = &VICVECTADDR0;
  // Set Address of callback function to corresponding Slot
  *(pReg+VicIntSource) = (unsigned long)pIRQSub;
  // load base address of ctrl registers
  pReg = &VICVECTPRIORITY0;
  // Set source channel and enable the slot
  *(pReg+VicIntSource) = Priority;
  // Clear FIQ select bit
  VICINTSELECT &= ~(1<<VicIntSource);
}

/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description: main
 *
 *************************************************************************/
int main(void)
{
Int8S X = 0, Y = 0;
Int8U Buttons = 0, ButtonsHold = 0;
Buttons_t ButtCtrl;

  // Init MMU
  CP15_Mmu(FALSE);            // Disable MMU
  // Privileged permissions  User permissions AP
  // Read-only               Read-only        0
  CP15_SysProt(FALSE);
  CP15_RomProt(TRUE);

  CP15_InitMmuTtb(TtSB,TtTB); // Build L1 and L2 Translation tables
  CP15_SetTtb(L1Table);       // Set base address of the L1 Translation table
  CP15_SetDomain( (DomainManager << 2*1) | (DomainClient << 0)); // Set domains
  CP15_Mmu(TRUE);             // Enable MMU
  CP15_Cache(TRUE);           // Enable ICache,DCache

  // Init Time0
  Timer0Control_bit.TIMEN = 0;    // disable timer
  Timer0Control_bit.TIMMOD = 1;   // Period mode
  Timer0Control_bit.TIMSIZE = 1;  // 16 bits
  Timer0Control_bit.TIMPRS = 2;   // Set timer 0 prescaler /256
  Timer0Control_bit.TIMOSCTL = 0; // Wrapping mode
  // set timer 0 period
  Timer0Load = (TIMER0_IN_FREQ)/(256 * TIMER0_TICK_PER_SEC);

  // init timer 0 interrupt
  Timer0IntClr = 0;         // clear timer interrupt
  VIC_SetVectoredIRQ(Timer0IntrHandler,1,_INTR_TIMER01);
  VICINTENABLE = 1<<_INTR_TIMER01;

  // Initialize USB
  // HID USB
  HidInit();

  __enable_interrupt();

  Timer0Control_bit.TIMEN = 1;    // Enable timer
  // Soft connection enable
  USB_ConnectRes(TRUE);

  while(1)
  {
    if (SysTickFl)
    {
      SysTickFl = FALSE;
      if(UsbCoreReq(UsbCoreReqDevState) == UsbDevStatusConfigured)
      {
        // Buttons and Joystick processing
        ButtCtrl = GetButtons();
        if(ButtCtrl.JsUp)
        {
          Y -= MOUSE_DELTA;
        }
        else if(ButtCtrl.JsDown)
        {
          Y += MOUSE_DELTA;
        }

        if(ButtCtrl.JsRight)
        {
          X += MOUSE_DELTA;
        }
        else if(ButtCtrl.JsLeft)
        {
          X -= MOUSE_DELTA;
        }

        if(ButtCtrl.JsCenter)
        {
          Buttons |= 1;
        }
        else
        {
          Buttons &= ~1;
        }

        if(Y || X  || Buttons || (ButtonsHold ^ Buttons))
        {
          UsbWakeUp();  // wake-up
          // Send report
          HidMouseSendReport(X,Y,Buttons);
          ButtonsHold = Buttons;
          Y = X = Buttons = 0;
        }
      }
    }
  }
}
