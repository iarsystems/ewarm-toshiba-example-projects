/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : drv_ioexp.h
 *    Description : Toshiba M374-STK IO Expander drv header file
 *
 *    History :
 *    1. Date        : 09.2011
 *       Author      : Stoyan Choynev
 *       Description : initial revision
 *
 *    $Revision: 41 $
 **************************************************************************/
/** include files **/
#include <stdint.h>

#ifndef __DRV_IOEXP_H
#define __DRV_IOEXP_H
/** definitions **/

/** default settings **/

/** public data **/

/** public functions **/
/*************************************************************************
 * Function Name: IOExp_Init
 * Parameters: none
 *             
 * Return: void
 *
 * Description: IO Expander initialization
 *
 *
 *************************************************************************/
extern int IOExp_Init(void);

/*************************************************************************
 * Function Name: IOExp_Update
 * Parameters: uint8_t
 *             
 * Return: void
 *
 * Description: Updates IO Expander data
 *
 *************************************************************************/
extern void IOExp_Update(uint8_t data);

/*************************************************************************
 * Function Name: IOExp_Get
 * Parameters: void
 *             
 * Return: uint8_t
 *
 * Description: return current IO Expander data
 *
 *************************************************************************/
extern uint8_t IOExp_Get();
#endif /* __DRV_IOEXP_H */
