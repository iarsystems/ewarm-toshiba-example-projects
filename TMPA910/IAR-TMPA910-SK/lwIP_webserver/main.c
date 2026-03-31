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
 *    1. Date        : 1, September 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *  This example application demonstrates the operation of the IAR TMPA910-SK
 * and DM9000A Ethernet controller using the lwIP TCP/IP Stack.  The project can be
 * configured to use Static IP or DHCP. The address that is selected will be shown
 * on the IO windows.
 *
 *   The WEB serever example project is compatible with IAR TMPA910-SK
 *  evaluation board. By default the project is configured to use the
 *  J-Link JTAG interface.
 *
 *  Jumpers:
 *     JP2  - 2-3 (1) Boot Select
 *     JP3  - 1-2 (0) Boot Select
 *     JP4  - 1-2     SN0
 *     JP5  - 2-3     SN1
 *     JP6  - 1-2     SN2
 *     JP11 - filled  +1.8V
 *     JP13 - filled  +1.5V
 *     JP14 - filled  +3.3V
 *     JP20 - filled
 *
 *    $Revision: 41 $
 **************************************************************************/

#include <intrinsics.h>
#include <stdio.h>
#include <assert.h>
#include "board.h"
#include "arm926ej_cp15_drv.h"
#include "ttbl.h"
#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/netifapi.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/tcpip.h"
#include "lwip/sockets.h"
#include "lwip/mem.h"
#include "lwip/init.h"
#include "lwip/dhcp.h"
#include "lwip/autoip.h"
#include "netif/etharp.h"

extern int  iar_tmpa910if_input(struct netif *netif);
extern err_t iar_tmpa910if_init(struct netif *netif);
extern void httpd_init(void);

#define ASSERT  assert

#define TIMER0_IN_FREQ          PCLK
#define TIMER0_TICK_PER_SEC     1000

#define IPADDR_USE_STATIC       0
#define IPADDR_USE_DHCP         1
#define IPADDR_USE_AUTOIP       2
#define LED_TIMER_MSECS         (100)


#define IPADDR(a,b,c,d)         ((a<<24) | (b<<16) | (c<<8) | d)
//*****************************************************************************
//
// The lwIP network interface structure for the Stellaris Ethernet MAC.
//
//*****************************************************************************
struct netif lwip_netif;

/** private data **/
//*****************************************************************************
//
// The local time for the lwIP Library Abstraction layer, used to support the
// Host and lwIP periodic callback functions.
//
//*****************************************************************************
static unsigned long g_ulLocalTimer = 0;

//*****************************************************************************
//
// The local time when the TCP timer was last serviced.
//
//*****************************************************************************
static unsigned long g_ulTCPTimer = 0;

//*****************************************************************************
//
// The local time when the HOST timer was last serviced.
//
//*****************************************************************************
#if HOST_TMR_INTERVAL
static unsigned long g_ulHostTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the ARP timer was last serviced.
//
//*****************************************************************************
#if LWIP_ARP
static unsigned long g_ulARPTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the AutoIP timer was last serviced.
//
//*****************************************************************************
#if LWIP_AUTOIP
static unsigned long g_ulAutoIPTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the DHCP Coarse timer was last serviced.
//
//*****************************************************************************
#if LWIP_DHCP
static unsigned long g_ulDHCPCoarseTimer = 0;
#endif

//*****************************************************************************
//
// The local time when the DHCP Fine timer was last serviced.
//
//*****************************************************************************
#if LWIP_DHCP
static unsigned long g_ulDHCPFineTimer = 0;
#endif

//*****************************************************************************
//
// The default IP address aquisition mode.
//
//*****************************************************************************
static unsigned long g_ulIPMode = IPADDR_USE_STATIC;

//*****************************************************************************
//
// The local time when the LED timer was last serviced.
//
//*****************************************************************************
static unsigned long g_ulLedTimer = 0;

//*****************************************************************************
//
// The most recently assigned IP address.  This is used to detect when the IP
// address has changed (due to DHCP/AutoIP) so that the new address can be
// printed.
//
//*****************************************************************************
static unsigned long g_ulLastIPAddr = 0;

/** public functions **/

/** private functions **/
static void lwIPHostTimerHandler(void);

//*****************************************************************************
//
// Required by lwIP library to support any host-related timer functions.
//
//*****************************************************************************
#if HOST_TMR_INTERVAL
static
void lwIPHostTimerHandler(void)
{
    unsigned long ulIPAddress;

    //
    // Get the local IP address.
    //
    ulIPAddress = lwip_netif.ip_addr.addr;

    //
    // See if an IP address has been assigned.
    //
    //
    // Check if IP address has changed, and display if it has.
    //
    if(ulIPAddress != g_ulLastIPAddr)
    {
        //
        // Display the new IP address.
        //
        printf("\rIP: %d.%d.%d.%d       \n", ulIPAddress & 0xff,
               (ulIPAddress >> 8) & 0xff, (ulIPAddress >> 16) & 0xff,
               (ulIPAddress >> 24) & 0xff);

        //
        // Save the new IP address.
        //
        g_ulLastIPAddr = ulIPAddress;

        //
        // Display the new network mask.
        //
        ulIPAddress = lwip_netif.netmask.addr;
        printf("Netmask: %d.%d.%d.%d\n", ulIPAddress & 0xff,
               (ulIPAddress >> 8) & 0xff, (ulIPAddress >> 16) & 0xff,
               (ulIPAddress >> 24) & 0xff);

        //
        // Display the new gateway address.
        //
        ulIPAddress = lwip_netif.gw.addr;
        printf("Gateway: %d.%d.%d.%d\n", ulIPAddress & 0xff,
               (ulIPAddress >> 8) & 0xff, (ulIPAddress >> 16) & 0xff,
               (ulIPAddress >> 24) & 0xff);
    }
}
#endif

//*****************************************************************************
//
//! Initializes the lwIP TCP/IP stack.
//!
//! \param pucMAC is a pointer to a six byte array containing the MAC
//! address to be used for the interface.
//! \param ulIPAddr is the IP address to be used (static).
//! \param ulNetMask is the network mask to be used (static).
//! \param ulGWAddr is the Gateway address to be used (static).
//! \param ulIPMode is the IP Address Mode.  \b IPADDR_USE_STATIC will force
//! static IP addressing to be used, \b IPADDR_USE_DHCP will force DHCP with
//! fallback to Link Local (Auto IP), while \b IPADDR_USE_AUTOIP will force
//! Link Local only.
//!
//! This function performs initialization of the lwIP TCP/IP stack for the
//! Stellaris Ethernet MAC, including DHCP and/or AutoIP, as configured.
//!
//! \return None.
//
//*****************************************************************************
void
lwIPInit(const unsigned char *pucMAC, unsigned long ulIPAddr,
         unsigned long ulNetMask, unsigned long ulGWAddr,
         unsigned long ulIPMode)
{
    struct ip_addr ip_addr;
    struct ip_addr net_mask;
    struct ip_addr gw_addr;

    //
    // Check the parameters.
    //
#if LWIP_DHCP && LWIP_AUTOIP
    ASSERT((ulIPMode == IPADDR_USE_STATIC) ||
           (ulIPMode == IPADDR_USE_DHCP) ||
           (ulIPMode == IPADDR_USE_AUTOIP));
#elif LWIP_DHCP
    ASSERT((ulIPMode == IPADDR_USE_STATIC) ||
           (ulIPMode == IPADDR_USE_DHCP));
#elif LWIP_AUTOIP
    ASSERT((ulIPMode == IPADDR_USE_STATIC) ||
           (ulIPMode == IPADDR_USE_AUTOIP));
#else
    ASSERT(ulIPMode == IPADDR_USE_STATIC);
#endif

    //
    // Initialize lwIP library modules
    //
    lwip_init();

    //
    // Setup the network address values.
    //
    if(ulIPMode == IPADDR_USE_STATIC)
    {
        ip_addr.addr = htonl(ulIPAddr);
        net_mask.addr = htonl(ulNetMask);
        gw_addr.addr = htonl(ulGWAddr);
    }
#if LWIP_DHCP || LWIP_AUTOIP
    else
    {
        ip_addr.addr = 0;
        net_mask.addr = 0;
        gw_addr.addr = 0;
    }
#endif

    //
    // Create, configure and add the Ethernet controller interface with
    // default settings.
    //
    netif_add(&lwip_netif, &ip_addr, &net_mask, &gw_addr, NULL,
              iar_tmpa910if_init, ip_input);
    netif_set_default(&lwip_netif);

    //
    // Indicate that we are running in static IP mode.
    //
    g_ulIPMode = ulIPMode;

    //
    // Start DHCP, if enabled.
    //
#if LWIP_DHCP
    if(g_ulIPMode == IPADDR_USE_DHCP)
    {
        dhcp_start(&lwip_netif);
    }
#endif

    //
    // Start AutoIP, if enabled and DHCP is not.
    //
#if LWIP_AUTOIP
    if(g_ulIPMode == IPADDR_USE_AUTOIP)
    {
        autoip_start(&lwip_netif);
    }
#endif

    //
    // Bring the interface up.
    //
    netif_set_up(&lwip_netif);
}

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
  Timer0IntClr = 0;             // clear timer interrupt
  ++g_ulLocalTimer;
  //
  // Service the host timer.
  //
#if HOST_TMR_INTERVAL
  if((g_ulLocalTimer - g_ulHostTimer) >= HOST_TMR_INTERVAL)
  {
    g_ulHostTimer = g_ulLocalTimer;
    lwIPHostTimerHandler();
  }
#endif

  //
  // Service the ARP timer.
  //
#if LWIP_ARP
  if((g_ulLocalTimer - g_ulARPTimer) >= ARP_TMR_INTERVAL)
  {
    g_ulARPTimer = g_ulLocalTimer;
    etharp_tmr();
  }
#endif

  //
  // Service the TCP timer.
  //
  if((g_ulLocalTimer - g_ulTCPTimer) >= TCP_TMR_INTERVAL)
  {
    g_ulTCPTimer = g_ulLocalTimer;
    tcp_tmr();
  }

  //
  // Service the AutoIP timer.
  //
#if LWIP_AUTOIP
  if((g_ulLocalTimer - g_ulAutoIPTimer) >= AUTOIP_TMR_INTERVAL)
  {
    g_ulAutoIPTimer = g_ulLocalTimer;
    autoip_tmr();
  }
#endif

  //
  // Service the DCHP Coarse Timer.
  //
#if LWIP_DHCP
  if((g_ulLocalTimer - g_ulDHCPCoarseTimer) >= DHCP_COARSE_TIMER_MSECS)
  {
    g_ulDHCPCoarseTimer = g_ulLocalTimer;
    dhcp_coarse_tmr();
  }
#endif

  //
  // Service the DCHP Fine Timer.
  //
#if LWIP_DHCP
  if((g_ulLocalTimer - g_ulDHCPFineTimer) >= DHCP_FINE_TIMER_MSECS)
  {
    g_ulDHCPFineTimer = g_ulLocalTimer;
    dhcp_fine_tmr();
  }
#endif

  if((g_ulLocalTimer - g_ulLedTimer) >= LED_TIMER_MSECS)
  {
    g_ulLedTimer = g_ulLocalTimer;
    GPIOBDATA_bit.PB0 ^= 1;   // toggle led pin
  }

  iar_tmpa910if_input(&lwip_netif);

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
unsigned char pucMACArray[8];
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

  // Set led pin (PB0) to output
  GPIOBODE_bit.PB0ODE = 0;

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

#if LWIP_DHCP
  //
  // Initialze the lwIP library, using DHCP.
  //
  lwIPInit(pucMACArray, 0, 0, 0, IPADDR_USE_DHCP);
#else
  //
  // Initialze the lwIP library, using Static IP.
  //
  lwIPInit(pucMACArray, IPADDR(192,168,0,100), IPADDR(255,255,255,0), \
                        IPADDR(192,168,0,1), IPADDR_USE_STATIC);  
#endif
  __enable_interrupt();

  Timer0Control_bit.TIMEN = 1;    // Enable timer

  //
  // Initialize a sample httpd server.
  //
  httpd_init();

  while(1)
  {

  }
}
