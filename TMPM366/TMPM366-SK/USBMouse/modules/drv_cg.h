/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : drv_cg.h
 *    Description : Toshiba TMPM366 Clock/Mode Control Drv header
 *
 *    History :
 *    1. Date        : 1.2011
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    $Revision: 41 $
 **************************************************************************/
/** include files **/

#ifndef __DRV_CG_H
#define __DRV_CG_H
/** definitions **/
#define IHOSC   (10000000UL)
/* SCOUT out select typedef */
typedef enum
{
  SCOSEL_FSYS_2 = 1,     /* fsys/2 */
  SCOSEL_FSYS,           /* fsys */
  SCOSEL_FPERIPH         /* fperiph */
} cg_scosel_t;

/* Peripheral clock sel typedef */
typedef enum
{
  FPSEL_FGEAR = 0,     /* select fgear as periph divider input */
  FPSEL_FC             /* select fc as periph divider input */
} cg_fpsel_t;

/* Peripheral clock divider typedef */
typedef enum
{
  PRCK_1 = 0,     /* divider 1 */
  PRCK_2,         /* divider 2 */
  PRCK_4,         /* divider 4 */
  PRCK_8,         /* divider 8 */
  PRCK_16,        /* divider 16 */
  PRCK_32         /* divider 32 */
} cg_prck_t;

/*SYS clock divider typedef */
typedef enum
{
  GEAR_FC = 0,    /* fc */
  GEAR_FC_2 = 4,  /* fc/2 */
  GEAR_FC_4,      /* fc/4 */
  GEAR_FC_8,      /* fc/8 */
  GEAR_FC_16      /* fc/16 */
} cg_gear_t;

/*Fosc sel typedef */
typedef enum
{
  FOSCSEL_INTOSC = 0,    /* internal oscilator */
  FOSCSEL_EXTCLK,        /* external input clock */
  FOSCSEL_EXTOSC = 3     /* external oscilator */
} cg_foscsel_t;

/*Fc sel typedef */
typedef enum
{
  FCSEL_FOSC = 0,       /* select fosc as fc clock oscilator */
  FCSEL_FPLL_2,         /* select fpll/2 as fc clock oscilator */
} cg_fcsel_t;

/*pll multiplying typedef*/
typedef enum
{
  PLLSET_MUL_6 = 0X3816,  /* multiply by 6*/
  PLLSET_MUL_8 = 0X381E   /* multiply by 8*/
} cg_pllset_t;

/*cg enable disable typedef*/
typedef enum
{
  CG_ENABLE,         /**/
  CG_DISABLE         /**/
} cg_enable_t;

/*cg clk typedef*/
typedef enum
{
  CLK_FOCS,                 /*fosc clock*/
  CLK_FPLL,                 /*fpll clock*/
  CLK_FC,                   /*fc clock*/
  CLK_FSYS,                 /*fsys clock*/
  CLK_FPERIPH,              /*fperiph clock*/
  CLK_TO,                   /*divider clock*/
} cg_clk_t;

/*clock init structure */
typedef struct
{
  cg_gear_t     gear;
  cg_fcsel_t    fcsel;
  cg_fpsel_t    pfsel;
  cg_prck_t     prck;
  cg_foscsel_t  fosc;
  cg_enable_t pll_enable;
  cg_pllset_t pllmul; 
} cg_clkinit_t;

/** default settings **/

/** public data **/

/** public functions **/
/*************************************************************************
 * Function Name: CG_RegsProtect
 * Parameters: cg_enable_t wr_enable 
 * Return: void
 *
 * Description: CG register write enable or disable
 *
 *
 *************************************************************************/
void CG_RegsProtect(cg_enable_t wr_enable);

/*************************************************************************
 * Function Name: CG_ExtOscEnable
 * Parameters: cg_enable_t osc_enable
 *             
 * Return: void
 *
 * Description: External Oscilator enable disable
 *
 *
 *************************************************************************/
void CG_ExtOscEnable(cg_enable_t osc_enable);

/*************************************************************************
 * Function Name: CG_IntOscEnable
 * Parameters: cg_enable_t osc_enable
 *             
 * Return: void
 *
 * Description: Internal Oscilator enable disable
 *
 *
 *************************************************************************/
void CG_IntOscEnable(cg_enable_t osc_enable);

/*************************************************************************
 * Function Name: CG_SetFosc
 * Parameters: cg_foscsel_t fosc - selec internal osc, ext osc or ext clk
 *             
 * Return: void
 *
 * Description: set fosc
 *
 *************************************************************************/
void CG_SetFosc(cg_foscsel_t fosc);

/*************************************************************************
 * Function Name: CG_SetSysClk
 * Parameters: cg_fcsel_t fcssel - select fc fosc or fpll/2
 *             cg_gear_t gear  - select fsys divider
 * Return: void
 *
 * Description: set fsys clock
 *
 *
 *************************************************************************/
void CG_SetSysClk(cg_fcsel_t fcssel,cg_gear_t gear);

/*************************************************************************
 * Function Name: CG_SetPerifClk
 * Parameters: cg_fpsel_t pfsel - select fc or fsys
 *             cg_prck_t prck - select peripheral clock divider
 * Return: void
 *
 * Description: set peripheral clock
 *
 *
 *************************************************************************/
void CG_SetPerifClk(cg_fpsel_t pfsel, cg_prck_t prck);

/*************************************************************************
 * Function Name: CG_SetPll
 * Parameters: cg_enable_t pllenalbe - enalbe or disable pll
 *             cg_pllset_t pllmul  - set pll mul
 *
 * Return: void
 *
 * Description: set pll 
 *
 *
 *************************************************************************/
void CG_SetPll(cg_enable_t pllenable, cg_pllset_t pllmul);

/*************************************************************************
 * Function Name: CG_SetPll
 * Parameters: cg_clk_t clock - clock to get
 *
 * Return: int clock frequency in Hz 
 *
 * Description: get clock frequency
 *
 *
 *************************************************************************/
int CG_GetClock(cg_clk_t clock);

/*
InitClock
*/
void InitClock(cg_clkinit_t * clkinit);



#endif /* __DRV_CG_H */
