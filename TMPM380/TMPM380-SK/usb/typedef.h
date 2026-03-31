/*******************************************************************************
* File Name 		 : m380_type.h
* Version			 : V1.0
* Date				 : 2010/01/xx
* Description		 : typedef
********************************************************************************/

#ifndef __M380_TYPE_H
#define __M380_TYPE_H

#define MHZ           *1000000l
#define KHZ           *1000l
#define HZ            *1l


#ifndef FALSE
#define FALSE (1 == 0)
#endif

#ifndef TRUE
#define TRUE  (1 == 1)
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif


typedef signed char		int8_t;
typedef signed short	int16_t;
typedef signed int		int32_t;

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;

typedef signed long long    	int64_t;
typedef unsigned long long    	uint64_t;

typedef unsigned int          Boolean;  // Boolean
typedef unsigned int        * pBoolean;

typedef struct tag_BIT_FIELD8_t {
	uint8_t	b0:1;
	uint8_t	b1:1;
	uint8_t	b2:1;
	uint8_t	b3:1;
	uint8_t	b4:1;
	uint8_t	b5:1;
	uint8_t	b6:1;
	uint8_t	b7:1;
} BIT_FIELD8_t;

typedef struct tag_BIT_FIELD16_t {
	uint8_t	b0:1;
	uint8_t	b1:1;
	uint8_t	b2:1;
	uint8_t	b3:1;
	uint8_t	b4:1;
	uint8_t	b5:1;
	uint8_t	b6:1;
	uint8_t	b7:1;
	uint8_t	b8:1;
	uint8_t	b9:1;
	uint8_t	b10:1;
	uint8_t	b11:1;
	uint8_t	b12:1;
	uint8_t	b13:1;
	uint8_t	b14:1;
	uint8_t	b15:1;
} BIT_FIELD16_t;

typedef struct tag_BIT_FIELD32_t {
	uint8_t	b0:1;
	uint8_t	b1:1;
	uint8_t	b2:1;
	uint8_t	b3:1;
	uint8_t	b4:1;
	uint8_t	b5:1;
	uint8_t	b6:1;
	uint8_t	b7:1;
	uint8_t	b8:1;
	uint8_t	b9:1;
	uint8_t	b10:1;
	uint8_t	b11:1;
	uint8_t	b12:1;
	uint8_t	b13:1;
	uint8_t	b14:1;
	uint8_t	b15:1;
	uint8_t	b16:1;
	uint8_t	b17:1;
	uint8_t	b18:1;
	uint8_t	b19:1;
	uint8_t	b20:1;
	uint8_t	b21:1;
	uint8_t	b22:1;
	uint8_t	b23:1;
	uint8_t	b24:1;
	uint8_t	b25:1;
	uint8_t	b26:1;
	uint8_t	b27:1;
	uint8_t	b28:1;
	uint8_t	b29:1;
	uint8_t	b30:1;
	uint8_t	b31:1;
} BIT_FIELD32_t;

typedef union tag_IO_SFR8_u {
	uint8_t		reg;
	uint8_t		byte[1];
	BIT_FIELD8_t  bit;
} IO_SFR8_u;

typedef union tag_IO_SFR16_u {
	uint16_t		reg;
	uint8_t		byte[2];
	BIT_FIELD16_t  bit;
} IO_SFR16_u;

typedef union tag_IO_SFR32_u {
	uint32_t		reg;
	uint8_t		byte[4];
	BIT_FIELD32_t  bit;
} IO_SFR32_u;

#define	SET			1				/* Bit set */
#define	CLEAR		0				/* Bit clear */
#define	HIGH		1
#define	LOW			0

/*#define	ELE_DEG(x)		(x * 2)	*//* Electric Angle (unit 0.5deg) */
#define	ELE_DEG(x)		((0x10000 * x)/384)	/* Electric Angle */



#define	BIT8( a,b,c,d,e,f,g,h )	( (a)*0x80+(b)*0x40+(c)*0x20+(d)*0x10 + (e)*0x08+(f)*0x04+(g)*0x02+(h)*0x01 )
#define	BIT16( a,b,c,d,e,f,g,h,aa,bb,cc,dd,ee,ff,gg,hh )	( (a)*0x8000+(b)*0x4000+(c)*0x2000+(d)*0x1000 + (e)*0x0800+(f)*0x0400+(g)*0x0200+(h)*0x0100 + \
                                                              (aa)*0x0080+(bb)*0x0040+(cc)*0x0020+(dd)*0x0010 + (ee)*0x0008+(ff)*0x0004+(gg)*0x0002+(hh)*0x0001 )
#define	BIT32( a,b,c,d,e,f,g,h,aa,bb,cc,dd,ee,ff,gg,hh,aaa,bbb,ccc,ddd,eee,fff,ggg,hhh,aaaa,bbbb,cccc,dddd,eeee,ffff,gggg,hhhh )	\
	( (a)*0x80000000+(b)*0x40000000+(c)*0x20000000+(d)*0x10000000 + (e)*0x08000000+(f)*0x04000000+(g)*0x02000000+(h)*0x01000000 + \
      (aa)*0x00800000+(bb)*0x00400000+(cc)*0x00200000+(dd)*0x00100000 + (ee)*0x00080000+(ff)*0x00040000+(gg)*0x00020000+(hh)*0x00010000 + \
      (aaa)*0x00008000+(bbb)*0x00004000+(ccc)*0x00002000+(ddd)*0x00001000 + (eee)*0x00000800+(fff)*0x00000400+(ggg)*0x00000200+(hhh)*0x00000100 + \
      (aaaa)*0x00000080+(bbbb)*0x00000040+(cccc)*0x00000020+(dddd)*0x00000010 + (eeee)*0x00000008+(ffff)*0x00000004+(gggg)*0x00000002+(hhhh)*0x00000001 )



typedef enum { DISABLE = 0, ENABLE =1 } IpFunctionState;
#define IP_FUNCTION_STATUS(STATUS)	((STATUS == DISABLE) || (STATUS == ENABLE))

#define BIT_ZERO	0
#define BIT_1		1


#define SRAM_BASE			0x20000000
#define BITBAND_SRAM_BASE	0x22000000
#define BITBAND_SRAM(a,b)	*((volatile uint32_t *)(BITBAND_SRAM_BASE + ((uint32_t)(&(a))-SRAM_BASE)*32 + (b*4)))

#define IP_BASE				0x40000000
#define BITBAND_IP_BASE		0x42000000
#define BITBAND_IP(a,b)		*((volatile uint8_t *)(BITBAND_IP_BASE + ((uint32_t)(&(a))-IP_BASE)*32 + (b*4)))

#define cBIT0		0
#define cBIT1		1
#define cBIT2		2
#define cBIT3		3
#define cBIT4		4
#define cBIT5		5
#define cBIT6		6
#define cBIT7		7
#define cBIT8		8
#define cBIT9		9
#define cBIT10		10
#define cBIT11		11
#define cBIT12		12
#define cBIT13		13
#define cBIT14		14
#define cBIT15		15
#define cBIT16		16
#define cBIT17		17
#define cBIT18		18
#define cBIT19		19
#define cBIT20		20
#define cBIT21		21
#define cBIT22		22
#define cBIT23		23
#define cBIT24		24
#define cBIT25		25
#define cBIT26		26
#define cBIT27		27
#define cBIT28		28
#define cBIT29		29
#define cBIT30		30
#define cBIT31		31

#endif /* __M380_TYPE_H */
