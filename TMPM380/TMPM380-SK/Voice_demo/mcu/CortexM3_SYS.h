/*******************************************************************************
* File Name          : CortexM3_sys.h
* Version            : V1.0
* Date				 : 2009/05/xx
* Description        : Cortex-M3 definition file
*******************************************************************************/

#ifndef __CortexM3_SYS_H
#define __CortexM3_SYS_H

#if 0
#define REG8(x)  (*((volatile unsigned char  *)(x)))
#define REG16(x) (*((volatile unsigned short *)(x)))
#define REG32(x) (*((volatile unsigned long  *)(x)))
#endif

typedef unsigned char  REG8;
typedef unsigned short REG16;
typedef unsigned long  REG32;


/* NVIC Registers */
	__IO_REG(NVIC_INT_TYPE,		0xE000E004, REG32);
	__IO_REG(NVIC_ST_CTRL,		0xE000E010, REG32);
	__IO_REG(NVIC_ST_RELOAD,	0xE000E014, REG32);
	__IO_REG(NVIC_ST_CURRENT,	0xE000E018, REG32);
	__IO_REG(NVIC_ST_CALIB,		0xE000E01C, REG32);

typedef struct{
	volatile unsigned long	num[8];
}INT_GR;

	__IO_REG(NVIC_SETENA,		0xE000E100, INT_GR);
	__IO_REG(NVIC_CLRENA ,		0xE000E180, INT_GR);
	__IO_REG(NVIC_SETPEND,		0xE000E200, INT_GR);
	__IO_REG(NVIC_CLRPEND,		0xE000E280, INT_GR);
	__IO_REG(NVIC_ACTIVE ,		0xE000E300, INT_GR);

typedef struct{
	volatile unsigned char 	num[240];
}PRI_GR;

	__IO_REG(NVIC_PRI ,		0xE000E400, PRI_GR);


	__IO_REG( NVIC_CPUID     ,	0xE000ED00	, REG32);
	__IO_REG( NVIC_INT_CTRL  ,	0xE000ED04	, REG32);
	__IO_REG( NVIC_VECT_TABLE,	0xE000ED08	, REG32);
	__IO_REG( NVIC_AP_INT_RST,	0xE000ED0C	, REG32);
	__IO_REG( NVIC_SYS_CTRL  ,	0xE000ED10	, REG32);
	__IO_REG( NVIC_CFG_CTRL  ,	0xE000ED14	, REG32);
	__IO_REG( NVIC_SYS_H_PRI1,	0xE000ED18	, REG32);
	__IO_REG( NVIC_SYS_H_PRI2,	0xE000ED1C	, REG32);
	__IO_REG( NVIC_SYS_H_PRI3,	0xE000ED20	, REG32);
	__IO_REG( NVIC_SYS_H_CTRL,	0xE000ED24	, REG32);
	__IO_REG( NVIC_FAULT_STA ,	0xE000ED28	, REG32);
	__IO_REG( NVIC_HARD_F_STA,	0xE000ED2C	, REG32);
	__IO_REG( NVIC_DBG_F_STA ,	0xE000ED30	, REG32);
	__IO_REG( NVIC_MM_F_ADR  ,	0xE000ED34	, REG32);
	__IO_REG( NVIC_BUS_F_ADR ,	0xE000ED38	, REG32);
	__IO_REG( NVIC_SW_TRIG   ,	0xE000EF00	, REG32);


/* MPU Registers */
	__IO_REG( MPU_TYPE       ,	0xE000ED90	, REG32);
	__IO_REG( MPU_CTRL       ,	0xE000ED94	, REG32);
	__IO_REG( MPU_RG_NUM     ,	0xE000ED98	, REG32);
	__IO_REG( MPU_RG_ADDR    ,	0xE000ED9C	, REG32);
	__IO_REG( MPU_RG_AT_SZ   ,	0xE000EDA0	, REG32);


#endif  // __CortexM3_SYS_H

/*************************** END OF FILE **************************************/

