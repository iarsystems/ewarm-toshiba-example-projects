/***************************************************************************
 **
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2013
 *
 *    File name   : drv_cg.h
 *    Description : Toshiba TMPM440 Clock/Mode Control Drv header
 *
 ***************************************************************************/
#ifndef __DRV_CG_H
#define __DRV_CG_H

/** definitions **/
#define IHOSC   (10000000UL)

/*SYS clock divider typedef */
typedef enum _cg_gear_t
{
  GEAR_FC = 0,    /* fc */
  GEAR_FC_2 = 4,  /* fc/2 */
  GEAR_FC_4,      /* fc/4 */
  GEAR_FC_8,      /* fc/8 */
  GEAR_FC_16      /* fc/16 */
} cg_gear_t;

/* Peripheral clock divider typedef */
typedef enum _cg_prck_t
{
  PRCK_1 = 0,     /* divider 1 */
  PRCK_2,         /* divider 2 */
  PRCK_4,         /* divider 4 */
  PRCK_8,         /* divider 8 */
  PRCK_16,        /* divider 16 */
  PRCK_32         /* divider 32 */
} cg_prck_t;

/* Peripheral clock sel typedef */
typedef enum _cg_fpsel_t
{
  FPSEL_FGEAR = 0,     /* select fgear as periph divider input */
  FPSEL_FC             /* select fc as periph divider input */
} cg_fpsel_t;

/*Fosc sel typedef */
typedef enum _cg_foscsel_t
{
  FOSCSEL_INTOSC = 0,    /* internal oscilator */
  FOSCSEL_EXTOSC         /* external oscilator */
} cg_foscsel_t;

/*cg enable disable typedef*/
typedef enum _cg_enable_t
{
  CG_ENABLE = 0,     /**/
  CG_DISABLE         /**/
} cg_enable_t;


/*pll multiplying typedef*/
typedef enum _cg_pllmul_t
{
  PLLMUL_5 = 0,   /* multiplier = 5 */
  PLLMUL_6,       /* multiplier = 6 */
  PLLMUL_8,       /* multiplier = 8 */
  PLLMUL_10,      /* multiplier = 10 */
} cg_pllmul_t;

/*TMRD clk divider typedef */
typedef enum _tmrd_gear_t
{
  TMRD_FC = 0,    /* fc */
  TMRD_FC_2 = 1,  /* fc/2 */
  TMRD_FC_4,      /* fc/4 */
} tmrd_gear_t;

/*SCO clk divider typedef */
typedef enum _sco_gear_t
{
  SCO_FC_4 = 0,	/* fc/4 */
  SCO_FC_8 = 1,  	/* fc/8 */
  SCO_FOSC,      	/* fosc */
  STOP_SCO,      	/* stop sco clock */
} sco_gear_t;


/* clock init structure */
typedef struct _cg_clkinit_t
{
  cg_foscsel_t    fosc;
  cg_enable_t     pll0;
  cg_enable_t     pll1;
  cg_pllmul_t     pll0mul;
  cg_pllmul_t     pll1mul;
  cg_fpsel_t      pfsel;
  cg_gear_t       gear;
  cg_prck_t       prck;
  sco_gear_t      scock;
} cg_clkinit_t;


/*cg clk typedef*/
typedef enum _cg_clk_t
{
  CLK_FOCS, 				/*fosc clock*/
  CLK_FPLL0, 				/*fpll0 clock*/
  CLK_FPLL1, 				/*fpll1 clock*/
  CLK_FC,					/*fc clock*/
  CLK_FSYS, 				/*fsys clock*/
  CLK_FPERIPH,				/*fperiph clock*/
  CLK_TO,					/*divider clock*/
  CLK_TMRD,					/*TMRD divider clock*/
} cg_clk_t;


/*peripheral clock enable control definitions*/

#define FCLK_TMRB(x)		(1<<(x))
#define FCLK_TMRC(x)		(1<<(x))
#define FCLK_TMRCTBT		(1<<(8))
#define FCLK_DAC(x)			(1<<(x))
#define FCLK_ADC(x)			(1<<(x))
#define FCLK_UART(x)		(1<<(x))
#define FCLK_DMAC(x)		(1<<(x))

#define FCLK_PORTA			(1<<0)
#define FCLK_PORTB			(1<<1)
#define FCLK_PORTC			(1<<2)
#define FCLK_PORTD			(1<<3)
#define FCLK_PORTE			(1<<4)
#define FCLK_PORTF			(1<<5)
#define FCLK_PORTG			(1<<6)
#define FCLK_PORTH			(1<<7)
#define FCLK_PORTJ			(1<<8)
#define FCLK_PORTK			(1<<9)
#define FCLK_PORTL			(1<<10)
#define FCLK_PORTM			(1<<11)
#define FCLK_PORTN			(1<<12)
#define FCLK_PORTP			(1<<13)
#define FCLK_PORTR			(1<<14)
#define FCLK_PORTT			(1<<15)
#define FCLK_PORTU			(1<<16)
#define FCLK_PORTV			(1<<17)
#define FCLK_PORTW			(1<<18)
#define FCLK_PORTY			(1<<19)
#define FCLK_PORTAA			(1<<20)
#define FCLK_PORTAB			(1<<21)
#define FCLK_PORTAC			(1<<22)
#define FCLK_PORTAD			(1<<23)
#define FCLK_PORTAE			(1<<24)
#define FCLK_PORTAF			(1<<25)
#define FCLK_PORTAG			(1<<26)
#define FCLK_PORTAH			(1<<27)
#define FCLK_PORTAJ			(1<<28)

#define FCLK_ESIO(x)		(1<<(x))
#define FCLK_SIO(x)			(1<<(x))


/** public data **/

/** public functions **/
void InitClock(const cg_clkinit_t * clkinit);
int CG_GetClock(cg_clk_t clock);

void fclk_ena_tmrd(const tmrd_gear_t gear);

void fclk_ena_tmrb(uint32_t portnum_msk);
void fclk_ena_tmrc(uint32_t portnum_msk);
void fclk_ena_dac(uint32_t portnum_msk);
void fclk_ena_adc(uint32_t portnum_msk);
void fclk_ena_dmac(uint32_t portnum_msk);
void fclk_ena_port(uint32_t portnum_msk);
void fclk_ena_esio(uint32_t portnum_msk);
void fclk_ena_sio(uint32_t portnum_msk);
void fclk_ena_ebif(void);
void fclk_ena_ephc(void);
void fclk_ena_sbi(void);
void fclk_ena_wdt(void);

void fclk_dis_tmrb(uint32_t portnum_msk);
void fclk_dis_tmrc(uint32_t portnum_msk);
void fclk_dis_dac(uint32_t portnum_msk);
void fclk_dis_adc(uint32_t portnum_msk);
void fclk_dis_dmac(uint32_t portnum_msk);
void fclk_dis_port(uint32_t portnum_msk);
void fclk_dis_esio(uint32_t portnum_msk);
void fclk_dis_sio(uint32_t portnum_msk);
void fclk_dis_ebif(void);
void fclk_dis_ephc(void);
void fclk_dis_sbi(void);
void fclk_dis_wdt(void);
void fclk_dis_tmrd(void);


#endif /* __DRV_CG_H */
