/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : Sample Application
 *   Micon : TMPA90xCRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2009 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file sub_main.c
	\brief Initialize system

	\author TOSHIBA CORPORATION

	\date 2009/03/17 New Creat
 */
/* ************************************************************************ */

/* ************************************************************************ */
/*
 * --------------------------------------------------------------------------
 *   Header Include Area
 * --------------------------------------------------------------------------
 */
#include "system_def.h"
#include <string.h>
#include "main.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#define CSYSCR0		CSYSCR0_Reserved

/* define of SYSCR1,SYSCR2,SYSCR3 */
#if(MSYS_CLK == CSYS_CLK192M)
# define CSYSCR1	0x00000000L		/* Gear:1/1		*/
# define CSYSCR2	0x00000002L		/* select fpll	*/
# define CSYSCR3	0x00000087L		/* PLL on, x8	*/
# define CSYSCR4	0x00000065L		/* depend on fsys	*/
#elif(MSYS_CLK == CSYS_CLK144M)
# define CSYSCR1	0x00000000L		/* Gear:1/1		*/
# define CSYSCR2	0x00000002L		/* select fpll	*/
# define CSYSCR3	0x00000085L		/* PLL on, x6	*/
# define CSYSCR4	0x00000065L		/* depend on fsys	*/
#elif(MSYS_CLK == CSYS_CLK048M)
# define CSYSCR1	0x00000002L		/* Gear:1/4		*/
# define CSYSCR2	0x00000002L		/* select fpll	*/
# define CSYSCR3	0x00000087L		/* PLL on, x8	*/
# define CSYSCR4	0x00000065L		/* depend on fsys	*/
#else
# error
#endif

/* SYSCR2<LUPFLAG> */
#define	FLUPFLAG_MASK				0x00000001L
#define	FLUPFLAG_ON					0x00000000L
#define	FLUPFLAG_END				0x00000001L

/* PMCDRV			*/
#define CPMCDRV_Init				0x00000073		/* for target of WinCE */
/*#define CPMCDRV_Init				0x00000071	*/	/* Mou2 reference setting */

/* for sdram	*/
#define Csmc_set_opmode_3_Init		0x00000001
#define Csmc_direct_cmd_3_Init		0x00400000

#define MSDRAM_A910	CSDRAM_A910
#define CSDRAM_A90x	0
#define CSDRAM_A910	1

#if(MSDRAM_A910	== CSDRAM_A910) /* A910	*/
# define Cdmc_refresh_prd_3_Init		0x00000080
# define Cdmc_cas_latency_3_Init		0x00000006
#else
# define Cdmc_refresh_prd_3_Init		0x00000040
# define Cdmc_cas_latency_3_Init		0x00000004
#endif

#define Cdmc_t_dqss_3_Init			0x00000000
#define Cdmc_t_mrd_3_Init			0x00000002
#define Cdmc_t_ras_3_Init			0x00000007
#define Cdmc_t_rc_3_Init			0x0000000b
#define Cdmc_t_rcd_3_Init			0x00000015
#define Cdmc_t_rfc_3_Init			0x000001f2
#define Cdmc_t_rp_3_Init			0x00000015
#define Cdmc_t_rrd_3_Init			0x00000002
#define Cdmc_t_wr_3_Init			0x00000003
#define Cdmc_t_wtr_3_Init			0x00000002
#define Cdmc_t_xp_3_Init			0x00000001
#define Cdmc_t_xsr_3_Init			0x0000000a
#define Cdmc_t_esr_3_Init			0x00000014

#if(MSDRAM_A910	== CSDRAM_A910) /* A910	*/
# define Cdmc_memory_cfg_3_Init		0x00010011
# define Cdmc_user_config_3_Init	0x00000011
#define Cdmc_id_2_cfg_3_Init		0x00000007
#else
# define Cdmc_memory_cfg_3_Init		0x00018011
# define Cdmc_user_config_3_Init	0x00000001
# define Cdmc_id_2_cfg_3_Init		0x00000003
#endif

#define Cdmc_chip_0_cfg_3_Init		0x000140fc

#define Cdmc_direct_cmd_3_NOP			0x000c0000
#define Cdmc_direct_cmd_3_Prechargeall	0x00000000
#define Cdmc_direct_cmd_3_Autorefresh	0x00040000

#if(MSDRAM_A910	== CSDRAM_A910) /* A910	*/
# define Cdmc_direct_cmd_3_AccessModereg	0x00080032
#else
# define Cdmc_direct_cmd_3_AccessModereg	0x00080023
#endif

#define Cdmc_memc_cmd_3_Go			0x00000000

/*
 * --------------------------------------------------------------------------
 *   Style Define Area
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Variable Define
 * --------------------------------------------------------------------------
 */


/*
 * --------------------------------------------------------------------------
 *   Prototype Declaration Area
 * --------------------------------------------------------------------------
 */


/* ************************************************************************** */

/* ======================================================================== */
/*!
	Set System Clock

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
//int mama(void)
unsigned int long	submainTEST;
int	__low_level_init( void )
{
#if 0
	UINT32_t reg_data;
	submainTEST=0x55;	
	/* Set System Clock */
	SYSCR0 = CSYSCR0;		/* for USB Clock */
	SYSCR1 = CSYSCR1;		/* set clock gear */

	SYSCR3 = CSYSCR3;
	SYSCR4 = CSYSCR4;

#if (MPLL == CPLL_x1)
 error1
#else
	//error2
	/* check lockup counter */
	submainTEST |= 0xaa00;
	do{
		reg_data = SYSCR2;
	}while( (reg_data & FLUPFLAG_MASK) == FLUPFLAG_ON );
#endif
	SYSCR2 = CSYSCR2;

#endif
	return(1);
}
/* ======================================================================== */

/* ======================================================================== */
/*!
	set MPMC(SDRAM)

	\param  -
	\retval -
 */
/* ------------------------------------------------------------------------ */
void set_mpmc( void )
{
	smc_set_opmode_3 = Csmc_set_opmode_3_Init;
	smc_direct_cmd_3 = Csmc_direct_cmd_3_Init;

	PMCDRV			  = CPMCDRV_Init;

	dmc_refresh_prd_3 = Cdmc_refresh_prd_3_Init;
	dmc_cas_latency_3 = Cdmc_cas_latency_3_Init;
	dmc_t_dqss_3      = Cdmc_t_dqss_3_Init;
	dmc_t_mrd_3       = Cdmc_t_mrd_3_Init;
	dmc_t_ras_3       = Cdmc_t_ras_3_Init;
	dmc_t_rc_3        = Cdmc_t_rc_3_Init;
	dmc_t_rcd_3       = Cdmc_t_rcd_3_Init;
	dmc_t_rfc_3       = Cdmc_t_rfc_3_Init;
	dmc_t_rp_3        = Cdmc_t_rp_3_Init;
	dmc_t_rrd_3       = Cdmc_t_rrd_3_Init;
	dmc_t_wr_3        = Cdmc_t_wr_3_Init;
	dmc_t_wtr_3       = Cdmc_t_wtr_3_Init;
	dmc_t_xp_3        = Cdmc_t_xp_3_Init;
	dmc_t_xsr_3       = Cdmc_t_xsr_3_Init;
	dmc_t_esr_3       = Cdmc_t_esr_3_Init;
	dmc_memory_cfg_3  = Cdmc_memory_cfg_3_Init;
	dmc_user_config_3 = Cdmc_user_config_3_Init;
	dmc_id_2_cfg_3	  = Cdmc_id_2_cfg_3_Init;

	dmc_chip_0_cfg_3  = Cdmc_chip_0_cfg_3_Init;

	/* input direct-command	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_NOP;	/* NOP			*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Prechargeall;	/* Prechargeall	*/

	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Autorefresh;	/* Autorefresh	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Autorefresh;	/* Autorefresh	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Autorefresh;	/* Autorefresh	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Autorefresh;	/* Autorefresh	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Autorefresh;	/* Autorefresh	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Autorefresh;	/* Autorefresh	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Autorefresh;	/* Autorefresh	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_Autorefresh;	/* Autorefresh	*/

	/* Modereg or Extended modereg accsess	*/
	dmc_direct_cmd_3  = Cdmc_direct_cmd_3_AccessModereg;

	/* input memc-command	*/
	dmc_memc_cmd_3    = Cdmc_memc_cmd_3_Go;	/* Go	*/
}
/* ======================================================================== */

/* ************************************************************************ */
