/*******************************************************************************
* File Name 		 : m330_sfr.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : typedef
********************************************************************************/

/* avoid double definition  */
#ifndef __M330_TYPE_H
#define __M330_TYPE_H




typedef signed char		int8;
typedef signed short	int16;
typedef signed int		int32;

typedef unsigned char	u_int8;
typedef unsigned short	u_int16;
typedef unsigned int	u_int32;

typedef struct tag_BIT_FIELD8_t {
	u_int8	B0:1;
	u_int8	B1:1;
	u_int8	B2:1;
	u_int8	B3:1;
	u_int8	B4:1;
	u_int8	B5:1;
	u_int8	B6:1;
	u_int8	B7:1;
} BIT_FIELD8_t;

typedef struct tag_BIT_FIELD16_t {
	u_int8	B0:1;
	u_int8	B1:1;
	u_int8	B2:1;
	u_int8	B3:1;
	u_int8	B4:1;
	u_int8	B5:1;
	u_int8	B6:1;
	u_int8	B7:1;
	u_int8	B8:1;
	u_int8	B9:1;
	u_int8	B10:1;
	u_int8	B11:1;
	u_int8	B12:1;
	u_int8	B13:1;
	u_int8	B14:1;
	u_int8	B15:1;
} BIT_FIELD16_t;

typedef struct tag_BIT_FIELD32_t {
	u_int8	B0:1;
	u_int8	B1:1;
	u_int8	B2:1;
	u_int8	B3:1;
	u_int8	B4:1;
	u_int8	B5:1;
	u_int8	B6:1;
	u_int8	B7:1;
	u_int8	B8:1;
	u_int8	B9:1;
	u_int8	B10:1;
	u_int8	B11:1;
	u_int8	B12:1;
	u_int8	B13:1;
	u_int8	B14:1;
	u_int8	B15:1;
	u_int8	B16:1;
	u_int8	B17:1;
	u_int8	B18:1;
	u_int8	B19:1;
	u_int8	B20:1;
	u_int8	B21:1;
	u_int8	B22:1;
	u_int8	B23:1;
	u_int8	B24:1;
	u_int8	B25:1;
	u_int8	B26:1;
	u_int8	B27:1;
	u_int8	B28:1;
	u_int8	B29:1;
	u_int8	B30:1;
	u_int8	B31:1;
} BIT_FIELD32_t;

typedef union tag_IO_SFR8_u {
	u_int8		reg;
	u_int8		byte[1];
	BIT_FIELD8_t  bit;
} IO_SFR8_u;

typedef union tag_IO_SFR16_u {
	u_int16		reg;
	u_int8		byte[2];
	BIT_FIELD16_t  bit;
} IO_SFR16_u;

typedef union tag_IO_SFR32_u {
	u_int32		reg;
	u_int8		byte[4];
	BIT_FIELD32_t  bit;
} IO_SFR32_u;


typedef enum { DISABLE = 0, ENABLE =1 } IpFunctionState;
#define IP_FUNCTION_STATUS(STATUS)	((STATUS == DISABLE) || (STATUS == ENABLE))

#define BIT_ZERO	0
#define BIT_1		1


#define SRAM_BASE			0x20000000
#define BITBAND_SRAM_BASE	0x22000000
#define BITBAND_SRAM(a,b)	*((volatile u_int32 *)(BITBAND_SRAM_BASE + ((u_int32)(&(a))-SRAM_BASE)*32 + (b*4)))

#define IP_BASE				0x40000000
#define BITBAND_IP_BASE		0x42000000
#define BITBAND_IP(a,b)		*((volatile u_int8 *)(BITBAND_IP_BASE + ((u_int32)(&(a))-IP_BASE)*32 + (b*4)))

#define BIT0		0
#define BIT1		1
#define BIT2		2
#define BIT3		3
#define BIT4		4
#define BIT5		5
#define BIT6		6
#define BIT7		7
#define BIT8		8
#define BIT9		9
#define BIT10		10
#define BIT11		11
#define BIT12		12
#define BIT13		13
#define BIT14		14
#define BIT15		15
#define BIT16		16
#define BIT17		17
#define BIT18		18
#define BIT19		19
#define BIT20		20
#define BIT21		21
#define BIT22		22
#define BIT23		23
#define BIT24		24
#define BIT25		25
#define BIT26		26
#define BIT27		27
#define BIT28		28
#define BIT29		29
#define BIT30		30
#define BIT31		31


#endif /* avoid double definition  */
