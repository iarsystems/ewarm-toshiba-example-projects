#ifndef	_register_clock_controller_h_
#define	_register_clock_controller_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : -
 *   Micon : TMPA901CMXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file register_clock_controller.h
	\brief Header file of clock control register's macro define

	\author TOSHIBA CORPORATION

	\date 2009/03/09 New
 */
/* ************************************************************************ */

/* ************************************************************************ */

/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
/* for SYSCR0	*/
#define	CSYSCR0_Reserved_MASK		0xFFFFFFFF	/* <31:0> */
#define	CSYSCR0_Reserved			0x00000022

/* for SYSCR1	*/
#define	CSYSCR1_Reserved_MASK		0xFFFFFFF8	/* <31:3> */
#define	CSYSCR1_Reserved			0x00000000
#define	CSYSCR1_GEAR_MASK			0x00000007	/* RW<2:0>	*/
#define	CSYSCR1_GEAR_fc				0x00000000
#define	CSYSCR1_GEAR_fc_div_2		0x00000001
#define	CSYSCR1_GEAR_fc_div_4		0x00000002
#define	CSYSCR1_GEAR_fc_div_8		0x00000003

/* for SYSCR2	*/
#define	CSYSCR2_Reserved_MASK		0xFFFFFFFC	/* RW<31:2> */
#define	CSYSCR2_Reserved			0x00000000
#define	CSYSCR2_FSCEL_MASK			0x00000002	/* RW<1>	*/
#define	CSYSCR2_FSCEL_fOSCH			0x00000000
#define	CSYSCR2_FSCEL_fPLL			0x00000002
#define	CSYSCR2_LUPFLAG_MASK		0x00000001	/* RO<0>	*/
#define	CSYSCR2_LUPFLAG_End			0x00000001
#define	CSYSCR2_LUPFLAG_NodEnd		0x00000000

/* for SYSCR3	*/
#define	CSYSCR3_Reserved_MASK		0xFFFFFF40	/* <31:8>,<6> */
#define	CSYSCR3_Reserved			0x00000000
#define	CSYSCR3_PLLOON_MASK			0x00000080	/* <7>	*/
#define	CSYSCR3_PLLOON_ON			0x00000080
#define	CSYSCR3_PLLOON_OFF			0x00000000
#define	CSYSCR3_C2S_MASK			0x00000020	/* <5>	*/
#define	CSYSCR3_C2S_ZERO			0x00000000
#define	CSYSCR3_ND_MASK				0x0000001F	/* <4:0>	*/
#define	CSYSCR3_ND_x6				0x00000005
#define	CSYSCR3_ND_x8				0x00000007

/* for SYSCR4	*/
#define	CSYSCR4_Reserved_MASK		0xFFFFFF00	/* <31:8> */
#define	CSYSCR4_Reserved			0x00000000
#define	CSYSCR4_RS_MASK				0x000000F0	/* <7:4>	*/
#define	CSYSCR4_RS_x8_oe_140		0x00000060	/* over equal 140MHz at x8	*/
#define	CSYSCR4_RS_x8_ul_140		0x00000090	/* less than  140MHz at x8	*/
#define	CSYSCR4_RS_x6_oe_140		0x00000060	/* over equal 140MHz at x6	*/
#define	CSYSCR4_RS_x6_ul_140		0x00000070	/* less than  140MHz at x6	*/
#define	CSYSCR4_IS_MASK				0x0000000C	/* <3:2>	*/
#define	CSYSCR4_IS_01				0x00000004
#define	CSYSCR4_FS_MASK				0x00000003	/* <1:0>	*/
#define	CSYSCR4_FS_x8_oe_140		0x00000001	/* over equal 140MHz at x8	*/
#define	CSYSCR4_FS_x8_ul_140		0x00000002	/* less than  140MHz at x8	*/
#define	CSYSCR4_FS_x6_oe_140		0x00000001	/* over equal 140MHz at x6	*/
#define	CSYSCR4_FS_x6_ul_140		0x00000002	/* less than  140MHz at x6	*/

/* for SYSCR5	*/
#define	CSYSCR5_Reserved_MASK		0xFFFFFFFE	/* <31:1> */
#define	CSYSCR5_Reserved			0x00000000
#define	CSYSCR5_PROTECT_MASK		0x00000001	/* <0>	*/
#define	CSYSCR5_PROTECT_ON			0x00000001
#define	CSYSCR5_PROTECT_OFF			0x00000000

/* for SYSCR6	*/
#define	CSYSCR6_Reserved_MASK		0xFFFFFF00	/* <31:8> */
#define	CSYSCR6_Reserved			0x00000000
#define	CSYSCR6_P_CODE0_MASK		0x00000000	/* WO<7:0>	*/

/* for SYSCR7	*/
#define	CSYSCR7_Reserved_MASK		0xFFFFFFF0	/* <31:8> */
#define	CSYSCR7_Reserved			0x00000000
#define	CSYSCR7_P_CODE1_MASK		0x00000000	/* WO<7:0>	*/

/* for SYSCR8	*/
#define	CSYSCR8_Reserved_MASK		0xFFFFFFC8	/* <31:8><7:6><3> */
#define	CSYSCR8_Reserved			0x00000000
#define	CSYSCR8_USBD_CLKSEL_MASK			0x00000030	/* <5:4>	*/
#define	CSYSCR8_USBD_CLKSEL_FIX_0			0x00000000
#define	CSYSCR8_USBD_CLKSEL_X1USB_div_2		0x00000010
#define	CSYSCR8_USBD_CLKSEL_X1USB			0x00000020
#define	CSYSCR8_USBD_CLKSEL_X1				0x00000030
#define	CSYSCR8_USBH_CLKSEL_MASK			0x00000007	/* <2:0>	*/
#define	CSYSCR8_USBH_CLKSEL_FIX_0			0x00000000
#define	CSYSCR8_USBH_CLKSEL_X1USB			0x00000001
#define	CSYSCR8_USBH_CLKSEL_PLL_div_3		0x00000002
#define	CSYSCR8_USBH_CLKSEL_PLL_div_4		0x00000004
#define	CSYSCR8_USBH_CLKSEL_X1				0x00000005

/* for CLKCR5	*/
#define CCLKCR5_Reserved_MASK		0xFFFFFFE0	/* <31:7><6><5>	*/
#define CCLKCR5_Reserved			0x00000040
#define	CCLKCR5_USBH_CLKEN_MASK				0x00000010	/* <4>	*/
#define	CCLKCR5_USBH_CLKEN_ENABLE			0x00000010
#define	CCLKCR5_USBH_CLKEN_DISABLE			0x00000000
#define	CCLKCR5_SEL_SMC_MCLK_MASK			0x00000008	/* <3>	*/
#define	CCLKCR5_SEL_SMC_MCLK_fHCLK			0x00000008
#define	CCLKCR5_SEL_SMC_MCLK_fHCLK_div_2	0x00000000
#define	CCLKCR5_SEL_TIM45_MASK				0x00000004	/* <2>	*/
#define	CCLKCR5_SEL_TIM45_fHCLK_div_2		0x00000004
#define	CCLKCR5_SEL_TIM45_fs				0x00000000
#define	CCLKCR5_SEL_TIM23_MASK				0x00000002	/* <1>	*/
#define	CCLKCR5_SEL_TIM23_fHCLK_div_2		0x00000002
#define	CCLKCR5_SEL_TIM23_fs				0x00000000
#define	CCLKCR5_SEL_TIM01_MASK				0x00000001	/* <0>	*/
#define	CCLKCR5_SEL_TIM01_fHCLK_div_2		0x00000001
#define	CCLKCR5_SEL_TIM01_fs				0x00000000


/* **************************************************************** */
#endif	/* _register_clock_controller_h_ */
