/*******************************************************************************
* File Name 		 : m380_cg.c
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : cg liblary source
********************************************************************************/
#include "..\typedef.h"
#include "TMPM380_SYS.h"

#include "m380_cg.h"


/*******************************************************************************
* Function Name  : API_CG_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_Init(void)
{
	uint16_t t;

	if (CG.PLLSEL & 0x1) {
		return;			// Already initialized
	}

	CG.SYSCR0  = cSYSCR0_INI;
	CG.SYSCR1  = cSYSCR1_INI;
	CG.SYSCR2  = cSYSCR2_INI;

	CG.OSCCR0  = cOSCCR0_INI;
	CG.OSCCR1  = cOSCCR1_INI;
	CG.OSCCR2  = cOSCCR2_INI;
	CG.OSCCR3  = cOSCCR3_INI;
	
	CG.STBYCR0 = cSTBYCR0_INI;
	CG.STBYCR1 = cSTBYCR1_INI;
	CG.STBYCR2 = cSTBYCR2_INI;

	CG.CKSEL   = cCKSEL_INI;

	CG.PLLSEL  = cPLLSEL_INI;

	BITBAND_IP(CG.OSCCR0, cBIT2) = 0;			// PLL OFF
	BITBAND_IP(CG.OSCCR0, cBIT3) = 0;			// Select warming up counter
	t = 100 * 10 / 4;							// 100us
	CG.OSCCR2 = ((uint8_t)(t << 2) &
	  ~BIT8(0,0,0,0, 1,1,1,1)) | cOSCCR2_INI;	// WUODR 2:5
	CG.OSCCR3 = (uint8_t)(t >> 6);				// WUODR 6:13
	BITBAND_IP(CG.OSCCR2, cBIT2) = 1;			// HOSCON(0:PORT M, 1:X1/X2)
	BITBAND_IP(CG.OSCCR1, cBIT0) = 1;			// XEN1(0:Stop, 1:Oscillation)
	BITBAND_IP(CG.OSCCR2, cBIT3) = 1;			// WUPSEL2(0:Internal(OSC2), 1:External(OSC1))
	BITBAND_IP(CG.OSCCR0, cBIT0) = 1;			// Warming up timer(WUP)Start
	while(BITBAND_IP(CG.OSCCR0, cBIT1) == 1);	// Wait WUP complete

	/* Select High Frequency OSC */
	BITBAND_IP(CG.OSCCR2, cBIT1) = 1;			// OSCSEL(0:Internal(OSC2), 1:External(OSC1))
	
	/* Stop internal OSC */
	BITBAND_IP(CG.OSCCR2, cBIT0) = 0;			// XEN2(0:Stop, 1:Oscillation)

	BITBAND_IP(CG.OSCCR0, cBIT2) = 1;			// PLL ON
	BITBAND_IP(CG.OSCCR0, cBIT3) = 0;			// Select warming up counter
	BITBAND_IP(CG.OSCCR2, cBIT3) = 1;			// WUPSEL2(0:Internal(OSC2), 1:External(OSC1))
	t = 200 * 10 / 4;							// Select warming up time 200us
	CG.OSCCR2 = ((uint8_t)(t << 2) &
	  ~BIT8(0,0,0,0, 1,1,1,1)) | cOSCCR2_OSC1_SET;	// WUODR 2:5
	CG.OSCCR3 = (uint8_t)(t >> 6);				// WUODR 6:13
	BITBAND_IP(CG.OSCCR0, cBIT0) = 1;			// Warming up timer(WUP)Start
	while(BITBAND_IP(CG.OSCCR0, cBIT1) == 1);	// Wait WUP complete

	/* Select and use PLL */
	BITBAND_IP(CG.PLLSEL, cBIT0) = 1;


}
