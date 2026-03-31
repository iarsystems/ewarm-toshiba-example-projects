#ifndef	_register_port_h_
#define	_register_port_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : -
 *   Micon : TMPA901CMXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file register_port.h
	\brief Header file of port register's macro define

	\author TOSHIBA CORPORATION

	\date 2009/01/09 New
 */
/* ************************************************************************ */

/* ************************************************************************ */

/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/* for GPIOA	*/
/*					<3:0>
	GPIOADATA	RO	0:low				1:high
	GPIOAIS		RW	0:edge detect		1:level detect
	GPIOAIBE	RW	0:fellow edge		1:both edge		(at edge detect)
	GPIOAIEV	RW	0:down edge or low	1:up edge or high
	GPIOAIE		RW	0:disable interrupt	1:enable interrupt
	GPIOARIS	RO	0:no interrupt		1:exist interrupt(befor GPIOAIE)
	GPIOAMIS	RO	0:no interrupt		1:exist interrupt(after GPIOAIE)
	GPIOAIC		WO	0:-					1:cleara interrupt(at edge interrupt)
 */
#define	CGPIOAxxxx_Reserved_MASK	0xFFFFFFF0	/* <31:4> */
#define	CGPIOAxxxx_Reserved			0x00000000
#define	CGPIOAxxxx_PA3_MASK			0x00000008	/* <3>	*/
#define	CGPIOAxxxx_PA3_T			0x00000008
#define	CGPIOAxxxx_PA3_F			0x00000000
#define	CGPIOAxxxx_PA2_MASK			0x00000004	/* <2>	*/
#define	CGPIOAxxxx_PA2_T			0x00000004
#define	CGPIOAxxxx_PA2_F			0x00000000
#define	CGPIOAxxxx_PA1_MASK			0x00000002	/* <1>	*/
#define	CGPIOAxxxx_PA1_T			0x00000002
#define	CGPIOAxxxx_PA1_F			0x00000000
#define	CGPIOAxxxx_PA0_MASK			0x00000001	/* <0>	*/
#define	CGPIOAxxxx_PA0_T			0x00000001
#define	CGPIOAxxxx_PA0_F			0x00000000

/* for GPIOB	*/
/*					<3:0>
	GPIOBDATA	RW	0:low				1:high
	GPIOBFR1	RW	0:output port		0:lcdc	1:key out	1:-
	GPIOBFR2	RW	0:					1:		0:			1:-
	GPIOBODE	RW	0:3state			1:Open Drain
 */
#define	CGPIOBxxxx_Reserved_MASK	0xFFFFFFF0	/* <31:4> */
#define	CGPIOBxxxx_Reserved			0x00000000
#define	CGPIOBxxxx_PB3_MASK			0x00000008	/* <3>	*/
#define	CGPIOBxxxx_PB3_T			0x00000008
#define	CGPIOBxxxx_PB3_F			0x00000000
#define	CGPIOBxxxx_PB2_MASK			0x00000004	/* <2>	*/
#define	CGPIOBxxxx_PB2_T			0x00000004
#define	CGPIOBxxxx_PB2_F			0x00000000
#define	CGPIOBxxxx_PB1_MASK			0x00000002	/* <1>	*/
#define	CGPIOBxxxx_PB1_T			0x00000002
#define	CGPIOBxxxx_PB1_F			0x00000000
#define	CGPIOBxxxx_PB0_MASK			0x00000001	/* <0>	*/
#define	CGPIOBxxxx_PB0_T			0x00000001
#define	CGPIOBxxxx_PB0_F			0x00000000


/* for GPIOC	*/
/*					<7:6,4:2>
	GPIOCDATA	RW	0:low				1:high
	GPIOCDIR	RW	0:in				1:out
	GPIOCFR1	RW	0:port				0:pwm	1:i2c	1:-
	GPIOCFR2	RW	0:					1:		0:		1:-
	GPIOCIS		RW	0:edge detect		1:level detect
	GPIOCIBE	RW	0:fellow edge		1:both edge		(at edge detect)
	GPIOCIEV	RW	0:down edge or low	1:up edge or high
	GPIOCIE		RW	0:disable interrupt	1:enable interrupt
	GPIOCRIS	RO	0:no interrupt		1:exist interrupt(befor GPIOAIE)
	GPIOCMIS	RO	0:no interrupt		1:exist interrupt(after GPIOAIE)
	GPIOCIC		WO	0:-					1:cleara interrupt(at edge interrupt)
 */
#define	CGPIOCFR1_Reserved_MASK	0xFFFFFF03	/* <31:8>, <1:0> */
#define	CGPIOCFR1_Reserved		0x00000000
#define	CGPIOCFR1_MLDALM_MASK	0x00000028
#define	CGPIOCFR1_MLDALM		0x00000028

#define	CGPIOCFR2_Reserved_MASK	0xFFFFFFE7	/* <31:8>, <7:5>, <2:0> */
#define	CGPIOCFR2_Reserved		0x00000000
#define	CGPIOCFR2_MLDALM_MASK	0x00000028
#define	CGPIOCFR2_MLDALM		0x00000000

#define	CGPIOCIE_Reserved_MASK	0xFFFFFF5F	/* <31:8>, <6>, <4:0> */
#define	CGPIOCIE_Reserved		0x00000000
#define	CGPIOCIE_PC7IE_MASK		0x00000080
# define CGPIOCIE_PC7IE_ENABLE	0x00000080
# define CGPIOCIE_PC7IE_DISABLE	0x00000000
#define	CGPIOCIE_PC5IE_MASK		0x00000020
# define CGPIOCIE_PC5IE_ENABLE	0x00000020
# define CGPIOCIE_PC5IE_DISABLE	0x00000000



/* for GPIOD(AD/TSI)
	PD<7,6,5,4> = <PY,PX(INTA),MY,MX>
	PD<5,4,3,2,1,0> = ch<5,4,3,2,1,0>
 */
#define CGPIOFR_ADCHBIT_MASK	0x01
#define CGPIOFR_ADCHBIT_NON		0x00

/* for GPIODFR1		*/
#define CGPIODFR1_Reserved_MASK				0xFFFFFFC0
# define CGPIODFR1_Reserved					0x00000000
#define CGPIODFR1_AD_MASK					0x0000003F
# define CGPIODFR1_TSI_MASK					0x00000030
# define CGPIODFR1_TSI						0x00000030

/* for GPIODFR2		*/
#define CGPIODFR2_Reserved_MASK				0xFFFFFF3F
# define CGPIODFR2_Reserved					0x00000000
#define CGPIODFR2_TSIMx_MASK				0x00000030
#define CGPIODFR2_TSIPx_MASK				0x000000C0
# define CGPIODFR2_TSIPx					0x000000C0

/*					PY, PX
					1					0
	GPIODIS		RW	level				edge
	GPIODIBE	RW	both sides			single side
	GPIODIEV	RW	down edge/low		up edge/high
	GPIODIE		RW	enable interrupt	disable interrupt
	GPIODRIS	RO	exist interrupt		non
	GPIODMIS	RO	exist interrupt		non
	GPIODIC		WO	clear interrupt		non
 */
#define CGPIODxxx_Reserved_MASK				0xFFFFFF3F
# define CGPIODxxx_Reserved					0x00000000
#define CGPIODxxx_PY_MASK					0x00000080
# define CGPIODxxx_PY_T						0x00000080
# define CGPIODxxx_PY_F						0x00000000
#define CGPIODxxx_PX_MASK					0x00000040
# define CGPIODxxx_PX_T						0x00000040
# define CGPIODxxx_PX_F						0x00000000



/* **************************************************************** */
#endif	/* _register_port_h_ */
