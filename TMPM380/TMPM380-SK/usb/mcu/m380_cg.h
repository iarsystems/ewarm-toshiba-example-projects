/*******************************************************************************
* File Name 		 : m380_cg.h
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : cg header
********************************************************************************/

#ifndef __M380_CG_H
#define __M380_CG_H

#include "..\typedef.h"

/* CG initialize */

#define		cSYSCR0_INI		BIT8(0,0,0,0,0,0,0,0)
/*							     | | | | | +-+-+------; GEAR	Specifies the high-speed clock (fc) gear.
							     | | | | |            ;			{ 000:fc,   001:Reserved, 010:Reserved, 011:Reserved
							     | | | | |            ;			  100:fc/2, 101:fc/4,     110:fc/8,     111:fc/16     }
							     +-+-+-+-+------------; none
*/

#define		cSYSCR1_INI		BIT8(0,0,0,0,0,0,0,1)
/*							     | | | | | +-+-+------; PRCK	Specifies the prescaler clock to peripheral I/O.
							     | | | | |            ;			{ 000:fperiph,    001:fperiph/2,  010:fperiph/4, 011:fperiph/8
							     | | | | |            ;			  100:fperiph/16, 101:fperiph/32, 110:Reserved,  111:Reserved
							     | | | | +------------; none
							     | | | +--------------; FPSEL	Specifies the source clock to fperiph.
							     | | |                ;			{ 0:fsys, 1:fc }
							     +-+-+----------------; none
*/

#define		cSYSCR2_INI		BIT8(0,0,0,0,0,0,0,1)
/*							     | | | | | | +-+------; SCOSEL	SCOUT clock
							     | | | | | |          ;			{ 00:fs,   01:fsys/2, 10:fsys, 11:φT0}
							     | | | +--------------; FCSTOP	Specifies the fclk to ADC.
							     + + + + + +----------;	Reserved
*/

#define		cOSCCR0_INI		BIT8(0,0,1,1,0,0,0,0)
/*							     | | | | | | | +------; WUEON	Enables to start the warm-up timer.
							     | | | | | | |        ;			{ 0:don't care, 1:starting warm-up }
							     | | | | | | +--------; WUEF	Enables to monitor the status of the warm-up timer.
							     | | | | | |          ;			{ 0:warm-up completed, 1:warm-up in operation }
							     | | | | | +----------; PLLON	Specifies operation of the PLL.
							     | | | | |            ;			{ 0:Stop, 1:Oscillation }
							     | | | | +------------; WUPSEL1	source clock for warm-up timer
							     | | | |              ;			{ 0:High-speed oscillator, 1:Low-speed oscillator }
							     +-+-+-+--------------; "0011"
*/

#define		cOSCCR1_INI		BIT8(0,0,0,0,0,0,0,0)
/*							     | | | | | | | +------; XEN1	Specifies operation of the high-speed oscillator1.
							     | | | | | | |        ;			{ 0:Stop, 1:Oscillation }
							     | | | | | | +--------; XEN		Specifies operation of the low-speed oscillator.
							     | | | | | |          ;			{ 0:Stop, 1:Oscillation }
							     | | +-+--------------; "00"
							     +-+------------------; WUODR1,0	warm-up counter設定値 bit0,1
*/


#define		cOSCCR2_INI		BIT8(0,0,0,0,0,0,0,1)
/*							     | | | | | | | +------; XEN2	Specifies operation of the high-speed oscillator2.
							     | | | | | | |        ;			{ 0:Stop, 1:Oscillation }
							     | | | | | | +--------; OSCSEL	Select high-speed oscillator
							     | | | | | |          ;			{ 0:Internal(OSC2), 1:External(OSC1)}
							     | | | | | +----------; HOSCON	Specifies Port M or X1/X2
							     | | | | |            ;			{ 0:PORT M, 1:X1/X2 }
							     | | | | +------------; WUPSEL2	Select source clock for warm-up timer
							     | | | |              ;			{ 0:Internal(OSC2), 1:External(OSC1)}
							     +-+-+-+--------------; WUODR2-5	warm-up counter設定値 
*/


#define		cOSCCR3_INI		BIT8(1,0,0,0,0,0,0,0)
/*							     +-+-+-+-+-+-+-+------; WUODR6-13	warm-up counter設定値 
*/


#define		cSTBYCR0_INI	BIT8(0,0,0,0,0,0,1,1)
/*							     | | | | | +-+-+------; STBY		Specifies the low power consumption mode.
							     | | | | |            ;				{ 000:Reserved, 001:STOP, 010:Reserved, 011:IDLE
							     | | | | |            ;				  1**:Reserved }
							     +-+-+-+-+------------; none
*/

#define		cSTBYCR1_INI	BIT8(0,0,0,0,0,0,0,1)
/*							     | | | | | | | +------; RXEN		Specifies the high-speed oscillator operation after releasing the STOP mode.
							     | | | | | | |        ;				{ 0:Stop, 1:Oscillation }
							     | | | | | | +--------; RTXEN		Specifies the Low-speed oscillator operation after releasing the STOP mode.
							     | | | | | |          ;				{ 0:Stop, 1:Oscillation }
							     +-+-+-+-+-+----------; none
*/

#define		cSTBYCR2_INI	BIT8(0,0,0,0,0,0,0,0)
/*							     | | | | | | | +------; DRVE		Specifies the pin status in the STOP mode.
							     | | | | | | |        ;				{ 0:Hi-Z, 1:Drive }
							     | | | | | | +--------; "0"
							     +-+-+-+-+-+----------; none
*/

#define		cPLLSEL_INI		BIT16(0,1,1,1, 0,0,1,0, 0,0,0,1, 1,1,1,0)
/*							      | | | |  | | | |  | | | |  | | | +------; PLLSEL		Specifies use or disuse of the clock multiplied by the PLL.
							      | | | |  | | | |  | | | |  | | |        ;				{ 0:fosc, 1:fpll }
							      | | | |  | | | |  +-+-+-+--+-+-+--------; "0001111"
							      | | | |  | +-+-+------------------------; "010"
							      | | | |--+------------------------------; none
							      +-+-+-+---------------------------------; "0111"
*/


#define		cCKSEL_INI		BIT8(0,0,0,0,0,0,0,0)
/*							                 | +------; SYSCKFLG	system clock status
							                 +--------; SYSCK		system clock select
*/


#define		cOSCCR2_OSC1_SET	BIT8(0,0,0,0,1,1,1,0)
/*								     | | | | | | | +------; XEN2	Specifies operation of the high-speed oscillator2.
								     | | | | | | |        ;			{ 0:Stop, 1:Oscillation }
								     | | | | | | +--------; OSCSEL	Select high-speed oscillator
								     | | | | | |          ;			{ 0:Internal(OSC2), 1:External(OSC1)}
								     | | | | | +----------; HOSCON	Specifies Port M or X1/X2
								     | | | | |            ;			{ 0:PORT M, 1:X1/X2 }
								     | | | | +------------; WUPSEL2	Select source clock for warm-up timer
								     | | | |              ;			{ 0:Internal(OSC2), 1:External(OSC1)}
								     +-+-+-+--------------; WUODR2-5	warm-up counter設定値 
*/

/**************************************************************/

void API_CG_Init(void);


#endif /* __M380_CG_H */





