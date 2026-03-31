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

/* OSC typedef */
typedef enum
{
  OSC_EH,                /* External High Speed*/
  OSC_EL                 /* External Low Speed*/
} cg_osc_t;

/* SCOUT out select typedef */
typedef enum
{
  SCOSEL_FSYS_2 = 1,     /* fsys/2 */
  SCOSEL_FSYS,           /* fsys */
  SCOSEL_FPERIPH         /* fperiph */
} cg_scosel_t;

/*Fsys sel typedef */
typedef enum
{
  FSYSSEL_FGEAR = 0,   /* select fgear as system flock */
  FSYSSEL_FS,          /* select fs as system clock*/
} cg_fsyssel_t;

/* Peripheral clock sel typedef */
typedef enum
{
  FPSEL_FGEAR = 0,     /* select fgear as periph divider input */
  FPSEL_FC             /* select fc as periph divider input */
} cg_fpsel_t;

/* Peripheral clock divider typedef */
typedef enum
{
  FT0SEL_1 = 0,     /* divider 1 */
  FT0SEL_2,         /* divider 2 */
  FT0SEL_4,         /* divider 4 */
  FT0SEL_8,         /* divider 8 */
  FT0SEL_16,        /* divider 16 */
  FT0SEL_32,        /* divider 32 */ 
  FT0SEL_FC         /* FS*/  
} cg_ft0sel_t;

/*SYS clock divider typedef */
typedef enum
{
  GEAR_FC = 0,    /* fc */
  GEAR_FC_2 = 4,  /* fc/2 */
  GEAR_FC_4,      /* fc/4 */
  GEAR_FC_8,      /* fc/8 */
} cg_gear_t;

/*Fc sel typedef */
typedef enum
{
  FCSEL_FOSC = 0,       /* select fosc as fc clock oscilator */
  FCSEL_FPLL,           /* select fpll as fc clock oscilator */
} cg_fcsel_t;

/*pll multiplying typedef*/
typedef enum
{
  PLLSET_MUL_4 = 0X721E,  /* multiply by 6*/
  PLLSET_MUL_8 = 0XA13E   /* multiply by 8*/
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
  CLK_FOSC,                 /*high speed clock*/
  CLK_FS,                   /*Low speed clock*/
  CLK_FPLL ,                 /*pll clock*/
  CLK_FC,                   /*fc clock*/
  CLK_FGEAR,                /*fgear clock*/
  CLK_FSYS,                 /*fsys clock*/
  CLK_FPERIPH,              /*fperiph clock*/
  CLK_FT0,                  /*divider clock*/
} cg_clk_t;

/*clock init structure */
typedef struct
{
  cg_gear_t     gear;
  cg_fcsel_t    fcsel;
  cg_fpsel_t    pfsel;
  cg_ft0sel_t   ft0sel;
  cg_fsyssel_t  fsyssel;
  cg_enable_t   pll_enable;
  cg_pllset_t   pllmul;
} cg_clkinit_t;

/** default settings **/

/** public data **/

/** public functions **/
/*************************************************************************
 * Function Name: CG_ExtHOscEnable
 * Parameters: cg_enable_t osc_enable, cg_osc_t osc
 *             
 * Return: void
 *
 * Description: External High speed Oscilator enable disable
 *
 *
 *************************************************************************/
void CG_ExtOscEnable(cg_enable_t osc_enable, cg_osc_t osc);

/*************************************************************************
 * Function Name: CG_SetFcClk
 * Parameters: cg_fcsel_t fcssel - select fc fosc or fpll
 *             
 * Return: void
 *
 * Description: set fc clock
 *
 *
 *************************************************************************/
void CG_SetFcClk(cg_fcsel_t fcssel);

/*************************************************************************
 * Function Name: CG_SetFgearClk
 * Parameters: cg_fgearsel_t fgearsel - select fgear
 *             
 * Return: void
 *
 * Description: set Fgear clock
 *
 *
 *************************************************************************/
void CG_SetFgearClk(cg_gear_t gear);

/*************************************************************************
 * Function Name: CG_SetPerifClk
 * Parameters: cg_fpsel_t pfsel - select fc or fsys
 *             
 * Return: void
 *
 * Description: set peripheral clock
 *
 *
 *************************************************************************/
void CG_SetPerifClk(cg_fpsel_t pfsel);

/*************************************************************************
 * Function Name: CG_SetPerifClk
 * Parameters: cg_fsyssel_t fsyssel - select fsys clock
 *            
 * Return: void
 *
 * Description: set sys clock gear of fs
 *
 *
 *************************************************************************/
void CG_SetFsysClk(cg_fsyssel_t fsyssel);

/*************************************************************************
 * Function Name: CG_SetT0Clk
 * Parameters: cg_ft0sel_t ft0sel - select ft0 clock
 *            
 * Return: void
 *
 * Description: set ft0 clock
 *
 *
 *************************************************************************/
void CG_SetT0Clk(cg_ft0sel_t ft0sel);

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
