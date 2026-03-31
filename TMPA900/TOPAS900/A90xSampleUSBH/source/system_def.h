#ifndef	_system_def_h_
#define	_system_def_h_
/* ************************************************************************ */
/*
 * ------------------------------------------------------------------------
 *   Application : -
 *   Micon : TMPA900CRAXBG
 *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
 * ------------------------------------------------------------------------
 */

/*! \file system_def.h
	\brief Header file of system define

	\author TOSHIBA CORPORATION

	\date 2009/03/17 New Create

 */
/* ************************************************************************ */

/* ************************************************************************ */
/*
 * --------------------------------------------------------------------------
 *   Header Include Area
 * --------------------------------------------------------------------------
 */
#include "tmpa900cm.h"
#include "register_interrupt.h"
#include "register_port.h"
#include "register_clock_controller.h"


/*
 * --------------------------------------------------------------------------
 *   Macro Define
 * --------------------------------------------------------------------------
 */
#define MSYS_CLK	CSYS_CLK192M
# define CSYS_CLK192M		192
# define CSYS_CLK144M		144
# define CSYS_CLK048M		48
# define CSYS_CLK024M		24

#define MPLL		CPLL_x8
# define CPLL_x1	0
# define CPLL_x6	1
# define CPLL_x8	2

#define MCLKGEAR		Cfc_DIV1
# define Cfc_DIV1		0
# define Cfc_DIV2		1
# define Cfc_DIV4		2
# define Cfc_DIV8		3


#if(MSYS_CLK == CSYS_CLK192M)
# if(MPLL == CPLL_x8)
# else
#  error
# endif
# if(MCLKGEAR == Cfc_DIV1)
# else
#  error
# endif
#elif(MSYS_CLK == CSYS_CLK144M)
# if(MPLL == CPLL_x6)
# else
#  error
# endif
# if(MCLKGEAR == Cfc_DIV1)
# else
#  error
# endif
#else
# error
#endif


/* **************************************************************** */
#endif	/* _system_def_h_ */
