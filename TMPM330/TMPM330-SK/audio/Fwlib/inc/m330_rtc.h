/*******************************************************************************
* File Name 		 : m330_rtc.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : RTC header
********************************************************************************/

/* avoid double definition */
#ifndef __M330_RTC_H
#define __M330_RTC_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* RTC initial data */
#define IO_RTC_INIT				(u_int8)0x30		/* CLOCK,TIMER Reg Initialize */


#define STOP		0
#define ACTIVE		1


	/* Batch setting symbol */

	/* SECR */				/* API_RTC_Set_ClkHMS */
							/* API_RTC_Set_Sec */
#define _00S		0x00		/*  0 sec	 */
#define _01S		0x01		/*  1 sec	 */
#define _02S		0x02		/*  2 sec	 */
#define _03S		0x03		/*  3 sec	 */
#define _04S		0x04		/*  4 sec	 */
#define _05S		0x05		/*  5 sec	 */
#define _06S		0x06		/*  6 sec	 */
#define _07S		0x07		/*  7 sec	 */
#define _08S		0x08		/*  8 sec	 */
#define _09S		0x09		/*  9 sec	 */
#define _10S		0x10		/* 10 sec	 */
#define _11S		0x11		/* 11 sec	 */
#define _12S		0x12		/* 12 sec	 */
#define _13S		0x13		/* 13 sec	 */
#define _14S		0x14		/* 14 sec	 */
#define _15S		0x15		/* 15 sec	 */
#define _16S		0x16		/* 16 sec	 */
#define _17S		0x17		/* 17 sec	 */
#define _18S		0x18		/* 18 sec	 */
#define _19S		0x19		/* 19 sec	 */
#define _20S		0x20		/* 20 sec	 */
#define _21S		0x21		/* 21 sec	 */
#define _22S		0x22		/* 22 sec	 */
#define _23S		0x23		/* 23 sec	 */
#define _24S		0x24		/* 24 sec	 */
#define _25S		0x25		/* 25 sec	 */
#define _26S		0x26		/* 26 sec	 */
#define _27S		0x27		/* 27 sec	 */
#define _28S		0x28		/* 28 sec	 */
#define _29S		0x29		/* 29 sec	 */
#define _30S		0x30		/* 30 sec	 */

#define _31S		0x31		/* 31 sec	 */
#define _32S		0x32		/* 32 sec	 */
#define _33S		0x33		/* 33 sec	 */
#define _34S		0x34		/* 34 sec	 */
#define _35S		0x35		/* 35 sec	 */
#define _36S		0x36		/* 36 sec	 */
#define _37S		0x37		/* 37 sec	 */
#define _38S		0x38		/* 38 sec	 */
#define _39S		0x39		/* 39 sec	 */
#define _40S		0x40		/* 40 sec	 */
#define _41S		0x41		/* 41 sec	 */
#define _42S		0x42		/* 42 sec	 */
#define _43S		0x43		/* 43 sec	 */
#define _44S		0x44		/* 44 sec	 */
#define _45S		0x45		/* 45 sec	 */
#define _46S		0x46		/* 46 sec	 */
#define _47S		0x47		/* 47 sec	 */
#define _48S		0x48		/* 48 sec	 */
#define _49S		0x49		/* 49 sec	 */
#define _50S		0x50		/* 50 sec	 */
#define _51S		0x51		/* 51 sec	 */
#define _52S		0x52		/* 52 sec	 */
#define _53S		0x53		/* 53 sec	 */
#define _54S		0x54		/* 54 sec	 */
#define _55S		0x55		/* 55 sec	 */
#define _56S		0x56		/* 56 sec	 */
#define _57S		0x57		/* 57 sec	 */
#define _58S		0x58		/* 58 sec	 */
#define _59S		0x59		/* 59 sec	 */
	/* MINR */				/* API_RTC_Set_ClkHMS */
							/* API_RTC_Set_AlmHM */
							/* API_RTC_Set_Min */
#define _00M		0x00		/*  0 min	 */
#define _01M		0x01		/*  1 min	 */
#define _02M		0x02		/*  2 min	 */
#define _03M		0x03		/*  3 min	 */
#define _04M		0x04		/*  4 min	 */
#define _05M		0x05		/*  5 min	 */
#define _06M		0x06		/*  6 min	 */
#define _07M		0x07		/*  7 min	 */
#define _08M		0x08		/*  8 min	 */
#define _09M		0x09		/*  9 min	 */
#define _10M		0x10		/* 10 min	 */
#define _11M		0x11		/* 11 min	 */
#define _12M		0x12		/* 12 min	 */
#define _13M		0x13		/* 13 min	 */
#define _14M		0x14		/* 14 min	 */
#define _15M		0x15		/* 15 min	 */
#define _16M		0x16		/* 16 min	 */
#define _17M		0x17		/* 17 min	 */
#define _18M		0x18		/* 18 min	 */
#define _19M		0x19		/* 19 min	 */
#define _20M		0x20		/* 20 min	 */
#define _21M		0x21		/* 21 min	 */
#define _22M		0x22		/* 22 min	 */
#define _23M		0x23		/* 23 min	 */
#define _24M		0x24		/* 24 min	 */
#define _25M		0x25		/* 25 min	 */
#define _26M		0x26		/* 26 min	 */
#define _27M		0x27		/* 27 min	 */
#define _28M		0x28		/* 28 min	 */
#define _29M		0x29		/* 29 min	 */
#define _30M		0x30		/* 30 min	 */

#define _31M		0x31		/* 31 min	 */
#define _32M		0x32		/* 32 min	 */
#define _33M		0x33		/* 33 min	 */
#define _34M		0x34		/* 34 min	 */
#define _35M		0x35		/* 35 min	 */
#define _36M		0x36		/* 36 min	 */
#define _37M		0x37		/* 37 min	 */
#define _38M		0x38		/* 38 min	 */
#define _39M		0x39		/* 39 min	 */
#define _40M		0x40		/* 40 min	 */
#define _41M		0x41		/* 41 min	 */
#define _42M		0x42		/* 42 min	 */
#define _43M		0x43		/* 43 min	 */
#define _44M		0x44		/* 44 min	 */
#define _45M		0x45		/* 45 min	 */
#define _46M		0x46		/* 46 min	 */
#define _47M		0x47		/* 47 min	 */
#define _48M		0x48		/* 48 min	 */
#define _49M		0x49		/* 49 min	 */
#define _50M		0x50		/* 50 min	 */
#define _51M		0x51		/* 51 min	 */
#define _52M		0x52		/* 52 min	 */
#define _53M		0x53		/* 53 min	 */
#define _54M		0x54		/* 54 min	 */
#define _55M		0x55		/* 55 min	 */
#define _56M		0x56		/* 56 min	 */
#define _57M		0x57		/* 57 min	 */
#define _58M		0x58		/* 58 min	 */
#define _59M		0x59		/* 59 min	 */

			/* HOURR(24H/12H) */			/* API_RTC_Set_Hour */
//		#define _00H		0x00		/*  0 hour (24h) /  0 hour (AM)	 */
//		#define _01H		0x01		/*  1 hour (24h) /  1 hour (AM)	 */
//		#define _02H		0x02		/*  2 hour (24h) /  2 hour (AM)	 */
//		#define _03H		0x03		/*  3 hour (24h) /  3 hour (AM)	 */
//		#define _04H		0x04		/*  4 hour (24h) /  4 hour (AM)	 */
//		#define _05H		0x05		/*  5 hour (24h) /  5 hour (AM)	 */
//		#define _06H		0x06		/*  6 hour (24h) /  6 hour (AM)	 */
//		#define _07H		0x07		/*  7 hour (24h) /  7 hour (AM)	 */
//		#define _08H		0x08		/*  8 hour (24h) /  8 hour (AM)	 */
//		#define _09H		0x09		/*  9 hour (24h) /  9 hour (AM)	 */
//		#define _10H		0x10		/* 10 hour (24h) / 10 hour (AM)	 */
//		#define _11H		0x11		/* 11 hour (24h) / 11 hour (AM)	 */
//		#define _12H		0x12		/* 12 hour (24h) /  0 hour (PM) : 0x20 (0x20-0x12=0x0E)	 */
//		#define _13H		0x13		/* 13 hour (24h) /  1 hour (PM) : 0x21 (0x0E)	 */
//		#define _14H		0x14		/* 14 hour (24h) /  2 hour (PM) : 0x22 (0x0E)	 */
//		#define _15H		0x15		/* 15 hour (24h) /  3 hour (PM) : 0x23 (0x0E)	 */
//		#define _16H		0x16		/* 16 hour (24h) /  4 hour (PM) : 0x24 (0x0E)	 */
//		#define _17H		0x17		/* 17 hour (24h) /  5 hour (PM) : 0x25 (0x0E)	 */
//		#define _18H		0x18		/* 18 hour (24h) /  6 hour (PM) : 0x26 (0x0E)	 */
//		#define _19H		0x19		/* 19 hour (24h) /  7 hour (PM) : 0x27 (0x0E)	 */
//		#define _20H		0x20		/* 20 hour (24h) /  8 hour (PM) : 0x28 (0x08)	 */
//		#define _21H		0x21		/* 21 hour (24h) /  9 hour (PM) : 0x29 (0x08)	 */
//		#define _22H		0x22		/* 22 hour (24h) / 10 hour (PM) : 0x30 (0x0E)	 */
//		#define _23H		0x23		/* 23 hour (24h) / 11 hour (PM) : 0x31 (0x0E)	 */

	/* HOURR(24H) */		/* API_RTC_Set_ClkHMS */
							/* API_RTC_Set_AlmHM */
							/* API_RTC_Set_Hour */
#define _00H		0x00		/*  0 hour (24h)	 */
#define _01H		0x01		/*  1 hour (24h)	 */
#define _02H		0x02		/*  2 hour (24h)	 */
#define _03H		0x03		/*  3 hour (24h)	 */
#define _04H		0x04		/*  4 hour (24h)	 */
#define _05H		0x05		/*  5 hour (24h)	 */
#define _06H		0x06		/*  6 hour (24h)	 */
#define _07H		0x07		/*  7 hour (24h)	 */
#define _08H		0x08		/*  8 hour (24h)	 */
#define _09H		0x09		/*  9 hour (24h)	 */
#define _10H		0x10		/* 10 hour (24h)	 */
#define _11H		0x11		/* 11 hour (24h)	 */
#define _12H		0x12		/* 12 hour (24h)	 */
#define _13H		0x13		/* 13 hour (24h)	 */
#define _14H		0x14		/* 14 hour (24h)	 */
#define _15H		0x15		/* 15 hour (24h)	 */
#define _16H		0x16		/* 16 hour (24h)	 */
#define _17H		0x17		/* 17 hour (24h)	 */
#define _18H		0x18		/* 18 hour (24h)	 */
#define _19H		0x19		/* 19 hour (24h)	 */
#define _20H		0x20		/* 20 hour (24h)	 */
#define _21H		0x21		/* 21 hour (24h)	 */
#define _22H		0x22		/* 22 hour (24h)	 */
#define _23H		0x23		/* 23 hour (24h)	 */
	/* HOURR(12H) */		/* API_RTC_Set_ClkHMS */
							/* API_RTC_Set_AlmHM */
#define _AM00H		0x00		/*  0 hour (AM)	 */
#define _AM01H		0x01		/*  1 hour (AM)	 */
#define _AM02H		0x02		/*  2 hour (AM)	 */
#define _AM03H		0x03		/*  3 hour (AM)	 */
#define _AM04H		0x04		/*  4 hour (AM)	 */
#define _AM05H		0x05		/*  5 hour (AM)	 */
#define _AM06H		0x06		/*  6 hour (AM)	 */
#define _AM07H		0x07		/*  7 hour (AM)	 */
#define _AM08H		0x08		/*  8 hour (AM)	 */
#define _AM09H		0x09		/*  9 hour (AM)	 */
#define _AM10H		0x10		/* 10 hour (AM)	 */
#define _AM11H		0x11		/* 11 hour (AM)	 */
#define _PM00H		0x20		/*  0 hour (PM)	 */
#define _PM01H		0x21		/*  1 hour (PM)	 */
#define _PM02H		0x22		/*  2 hour (PM)	 */
#define _PM03H		0x23		/*  3 hour (PM)	 */
#define _PM04H		0x24		/*  4 hour (PM)	 */
#define _PM05H		0x25		/*  5 hour (PM)	 */
#define _PM06H		0x26		/*  6 hour (PM)	 */
#define _PM07H		0x27		/*  7 hour (PM)	 */
#define _PM08H		0x28		/*  8 hour (PM)	 */
#define _PM09H		0x29		/*  9 hour (PM)	 */
#define _PM10H		0x30		/* 10 hour (PM)	 */
#define _PM11H		0x31		/* 11 hour (PM)	 */

	/* DAYR *//* Page0,1 */			/* API_RTC_Set_ClkYMDW */
									/* API_RTC_Set_AlmDW */
									/* API_RTC_Set_Week */
#define _SUN		0x00		/* 日曜日	 */
#define _MON		0x01		/* 月曜日	 */
#define _TUE		0x02		/* 火曜日	 */
#define _WED		0x03		/* 水曜日	 */
#define _THU		0x04		/* 木曜日	 */
#define _FRI		0x05		/* 金曜日	 */
#define _SAT		0x06		/* 土曜日	 */
	/* DATER *//* Page0,1 */		/* API_RTC_Set_ClkYMDW */
									/* API_RTC_Set_AlmDW */
#define _00D		0x00		/*  0 日	 */
#define _01D		0x01		/*  1 日	 */
#define _02D		0x02		/*  2 日	 */
#define _03D		0x03		/*  3 日	 */
#define _04D		0x04		/*  4 日	 */
#define _05D		0x05		/*  5 日	 */
#define _06D		0x06		/*  6 日	 */
#define _07D		0x07		/*  7 日	 */
#define _08D		0x08		/*  8 日	 */
#define _09D		0x09		/*  9 日	 */
#define _10D		0x10		/* 10 日	 */
#define _11D		0x11		/* 11 日	 */
#define _12D		0x12		/* 12 日	 */
#define _13D		0x13		/* 13 日	 */
#define _14D		0x14		/* 14 日	 */
#define _15D		0x15		/* 15 日	 */
#define _16D		0x16		/* 16 日	 */
#define _17D		0x17		/* 17 日	 */
#define _18D		0x18		/* 18 日	 */
#define _19D		0x19		/* 19 日	 */
#define _20D		0x20		/* 20 日	 */
#define _21D		0x21		/* 21 日	 */
#define _22D		0x22		/* 22 日	 */
#define _23D		0x23		/* 23 日	 */
#define _24D		0x24		/* 24 日	 */
#define _25D		0x25		/* 25 日	 */
#define _26D		0x26		/* 26 日	 */
#define _27D		0x27		/* 27 日	 */
#define _28D		0x28		/* 28 日	 */
#define _29D		0x29		/* 29 日	 */
#define _30D		0x30		/* 30 日	 */
#define _31D		0x31		/* 31 日	 */
	/* MONTHR *//* Page0 */			/* API_RTC_Set_ClkYMDW */
#define _01M		0x01		/*  1 月	 */
#define _02M		0x02		/*  2 月	 */
#define _03M		0x03		/*  3 月	 */
#define _04M		0x04		/*  4 月	 */
#define _05M		0x05		/*  5 月	 */
#define _06M		0x06		/*  6 月	 */
#define _07M		0x07		/*  7 月	 */
#define _08M		0x08		/*  8 月	 */
#define _09M		0x09		/*  9 月	 */
#define _10M		0x10		/* 10 月	 */
#define _11M		0x11		/* 11 月	 */
#define _12M		0x12		/* 12 月	 */
	/* YEARR *//* Page0 */			/* API_RTC_Set_ClkYMDW */
#define _00Y		0x00		/*  0 年	 */
#define _01Y		0x01		/*  1 年	 */
#define _02Y		0x02		/*  2 年	 */
#define _03Y		0x03		/*  3 年	 */
#define _04Y		0x04		/*  4 年	 */
#define _05Y		0x05		/*  5 年	 */
#define _06Y		0x06		/*  6 年	 */
#define _07Y		0x07		/*  7 年	 */
#define _08Y		0x08		/*  8 年	 */
#define _09Y		0x09		/*  9 年	 */
#define _10Y		0x10		/* 10 年	 */
#define _11Y		0x11		/* 11 年	 */
#define _12Y		0x12		/* 12 年	 */
#define _13Y		0x13		/* 13 年	 */
#define _14Y		0x14		/* 14 年	 */
#define _15Y		0x15		/* 15 年	 */
#define _16Y		0x16		/* 16 年	 */
#define _17Y		0x17		/* 17 年	 */
#define _18Y		0x18		/* 18 年	 */
#define _19Y		0x19		/* 19 年	 */
#define _20Y		0x20		/* 20 年	 */

#define _21Y		0x21		/* 21 年	 */
#define _22Y		0x22		/* 22 年	 */
#define _23Y		0x23		/* 23 年	 */
#define _24Y		0x24		/* 24 年	 */
#define _25Y		0x25		/* 25 年	 */
#define _26Y		0x26		/* 26 年	 */
#define _27Y		0x27		/* 27 年	 */
#define _28Y		0x28		/* 28 年	 */
#define _29Y		0x29		/* 29 年	 */
#define _30Y		0x30		/* 30 年	 */
#define _31Y		0x31		/* 31 年	 */
#define _32Y		0x32		/* 32 年	 */
#define _33Y		0x33		/* 33 年	 */
#define _34Y		0x34		/* 34 年	 */
#define _35Y		0x35		/* 35 年	 */
#define _36Y		0x36		/* 36 年	 */
#define _37Y		0x37		/* 37 年	 */
#define _38Y		0x38		/* 38 年	 */
#define _39Y		0x39		/* 39 年	 */
#define _40Y		0x40		/* 40 年	 */

#define _41Y		0x41		/* 41 年	 */
#define _42Y		0x42		/* 42 年	 */
#define _43Y		0x43		/* 43 年	 */
#define _44Y		0x44		/* 44 年	 */
#define _45Y		0x45		/* 45 年	 */
#define _46Y		0x46		/* 46 年	 */
#define _47Y		0x47		/* 47 年	 */
#define _48Y		0x48		/* 48 年	 */
#define _49Y		0x49		/* 49 年	 */
#define _50Y		0x50		/* 50 年	 */
#define _51Y		0x51		/* 51 年	 */
#define _52Y		0x52		/* 52 年	 */
#define _53Y		0x53		/* 53 年	 */
#define _54Y		0x54		/* 54 年	 */
#define _55Y		0x55		/* 55 年	 */
#define _56Y		0x56		/* 56 年	 */
#define _57Y		0x57		/* 57 年	 */
#define _58Y		0x58		/* 58 年	 */
#define _59Y		0x59		/* 59 年	 */
#define _60Y		0x60		/* 60 年	 */

#define _61Y		0x61		/* 61 年	 */
#define _62Y		0x62		/* 62 年	 */
#define _63Y		0x63		/* 63 年	 */
#define _64Y		0x64		/* 64 年	 */
#define _65Y		0x65		/* 65 年	 */
#define _66Y		0x66		/* 66 年	 */
#define _67Y		0x67		/* 67 年	 */
#define _68Y		0x68		/* 68 年	 */
#define _69Y		0x69		/* 69 年	 */
#define _70Y		0x70		/* 60 年	 */
#define _71Y		0x71		/* 71 年	 */
#define _72Y		0x72		/* 72 年	 */
#define _73Y		0x73		/* 73 年	 */
#define _74Y		0x74		/* 74 年	 */
#define _75Y		0x75		/* 75 年	 */
#define _76Y		0x76		/* 76 年	 */
#define _77Y		0x77		/* 77 年	 */
#define _78Y		0x78		/* 78 年	 */
#define _79Y		0x79		/* 79 年	 */
#define _80Y		0x80		/* 80 年	 */

#define _81Y		0x81		/* 81 年	 */
#define _82Y		0x82		/* 82 年	 */
#define _83Y		0x83		/* 83 年	 */
#define _84Y		0x84		/* 84 年	 */
#define _85Y		0x85		/* 85 年	 */
#define _86Y		0x86		/* 86 年	 */
#define _87Y		0x87		/* 87 年	 */
#define _88Y		0x88		/* 88 年	 */
#define _89Y		0x89		/* 89 年	 */
#define _90Y		0x90		/* 90 年	 */
#define _91Y		0x91		/* 91 年	 */
#define _92Y		0x92		/* 92 年	 */
#define _93Y		0x93		/* 93 年	 */
#define _94Y		0x94		/* 94 年	 */
#define _95Y		0x95		/* 95 年	 */
#define _96Y		0x96		/* 96 年	 */
#define _97Y		0x97		/* 97 年	 */
#define _98Y		0x98		/* 98 年	 */
#define _99Y		0x99		/* 99 年	 */


	/* MONTHR<MO0> *//* Page1 */		/* API_RTC_Set_24_12_mode */
#define IP_RTC_12H					0x00	/* 12H Clock	 */
#define IP_RTC_24H					0x01	/* 24H Clock	 */
	/* YEARR *//* Page1 */			/* API_RTC_Set_LeapYear */
#define IP_RTC_LEAPYEAR				0x00	/* Leap year	 */
#define IP_RTC_LEAPYEAR_OVER1Y		0x01	/* 1year from Leap year	 */
#define IP_RTC_LEAPYEAR_OVER2Y		0x02	/* 2year from Leap year	 */
#define IP_RTC_LEAPYEAR_OVER3Y		0x03	/* 3year from Leap year	 */

	/* PAGER.7<INTENA> */				/* API_RTC_Set_IntRTC */
#define IP_RTC_INT_ENABLE			(u_int8)0x80		/* INTRTC ENABLE	 */
#define IP_RTC_INT_DISABLE			(u_int8)0x00		/* INTRTC DISABLE	 */
	/* PAGER.4<ADJUST> */				/* API_RTC_Set_SecAdjust */
#define IP_RTC_SECADJUST			(u_int8)0x10		/* Sec Adjust	 */
	/* PAGER.3<ENATMR> */				/* API_RTC_Set_ClkEnaDis */
#define IP_RTC_CLK_ENABLE			(u_int8)0x08		/* CLOCK ENABLE		 */
#define IP_RTC_CLK_DISABLE			(u_int8)0x00		/* CLOCK DISABLE	 */
	/* PAGER.2<ENAALM> */				/* API_RTC_Set_AlmEnaDis */
#define IP_RTC_ALM_ENABLE			(u_int8)0x04		/* ALARM ENABLE		 */
#define IP_RTC_ALM_DISABLE			(u_int8)0x00		/* ALARM DISABLE	 */
	/* PAGER.0<PAGE> */					/* API_RTC_Set_PageSel */
#define IP_RTC_PAGE0				0x00				/* PAGE0 Select	 */
#define IP_RTC_PAGE1				0x01				/* PAGE1 Select	 */


/**************************************************************/
void API_RTC_Init(void);
void API_RTC_Set_ClkHMS(u_int8 hourr,u_int8 minr,u_int8 secr);
void API_RTC_Set_AlmHM(u_int8 hourr,u_int8 minr);
u_int32 API_RTC_Read_ClkHMS(void);
u_int16 API_RTC_Read_AlmHM(void);
void API_RTC_Set_Sec(u_int8 secr);
void API_RTC_Set_Min(u_int8 page,u_int8 minr);
void API_RTC_Set_Hour(u_int8 page,u_int8 hourr);
void API_RTC_Set_ClkYMDW(u_int8 yearr,u_int8 monthr,u_int8 dater,u_int8 dayr);
void API_RTC_Set_AlmDW(u_int8 dater,u_int8 dayr);
u_int32 API_RTC_Read_ClkYMDW(void);
u_int16 API_RTC_Read_AlmDW(void);
void API_RTC_Set_Week(u_int8 page,u_int8 dayr);
void API_RTC_Set_Day(u_int8 page,u_int8 dater);
void API_RTC_Set_Month(u_int8 monthr);
void API_RTC_Set_Year(u_int8 yearr);
void API_RTC_Set_24_12_mode(u_int8 hourmode);
void API_RTC_Set_LeapYear(u_int8 leapyear);
void API_RTC_Set_PAGER(u_int8 pager);
//	void API_RTC_Set_IntRTC(IpFunctionState NewState);
void API_RTC_Set_IntRTC(u_int8 IntRtc);
void API_RTC_Set_SecAdjust(void);
//	void API_RTC_Set_ClkEnaDis(IpFunctionState NewState);
//	void API_RTC_Set_AlmEnaDis(IpFunctionState NewState);
//	void API_RTC_Set_PageSel(u_int8 page);
void API_RTC_Set_ClkEnaDis(u_int8 ClkEnable);
void API_RTC_Set_AlmEnaDis(u_int8 AlmEnable);
void API_RTC_Set_PageSel(u_int8 Page);
void API_RTC_Set_RESTR(u_int8 restr);


#endif /*  avoid double definition  */



