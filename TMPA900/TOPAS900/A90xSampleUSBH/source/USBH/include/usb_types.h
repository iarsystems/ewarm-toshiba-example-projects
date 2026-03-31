/* ************************************************************************** */
/*
 * --------------------------------------------------------------------------
 *	Application			: USB Host Driver
 *	Micon				: TMP92xD28
 *	Development Tool	: -
 * 	Complie Option		: -
 *  Copyright(C) TOSHIBA CORPORATION 2007 All rights reserved
 * --------------------------------------------------------------------------
 */

/*! \file usb_types.h
	\brief Declaration of USB Host Driver common types

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */


#ifndef _USB_TYPES_H_SEEN_
#define _USB_TYPES_H_SEEN_


/* NULL */
#include <stddef.h>


/* primary types */
typedef char			int8_t;
typedef unsigned char	uint8_t;
#if(0)
typedef int				int16_t;
typedef unsigned int	uint16_t;
#else
typedef short				int16_t;
typedef unsigned short	uint16_t;
#endif
typedef long			int32_t;
typedef unsigned long	uint32_t;


#if !defined(USB_EXPORT)
# define USB_EXPORT      extern
#endif

/* bool */
typedef enum {
    false = 0,
    true
} bool;


#endif  /* _USB_TYPES_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 */
