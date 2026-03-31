/*******************************************************************************
* File Name 		 : m330_flash.c
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : FLASH liblary source
********************************************************************************/


#include "m330_flash.h"


/*******************************************************************************
* Function Name  : API_FLASH_Init
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_FLASH_Init(void)
{
	/* FLASH Reg Initialize */
	FLASH->IO_SECBIT.reg = IO_FLASH_SECBIT_INIT;
}

/*******************************************************************************
* Function Name  : API_FLASH_BlproRead
* Description	 : 
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
u_int8 API_FLASH_BlproRead(void)
{
	u_int32	BlockProSt;
	BlockProSt = FLASH->IO_FLCS.reg;
	BlockProSt >>= FLASH_BPS_SHIFT;
	BlockProSt &= FLASH_UI32BIT5_0_MASK;
	return (u_int8)BlockProSt;
}

/*******************************************************************************
* Function Name  : API_FLASH_RdyBsyRead
* Description	 : 
* Input 		 : RdyBsy
* Output		 : FLCS<D21-D16>/<BLPRO5-BLPRO0>
* Return		 : 
*******************************************************************************/
u_int8 API_FLASH_RdyBsyRead(void)
{
	u_int8	RdyBsy;
	RdyBsy = BITBAND_IP(FLASH->IO_FLCS.reg,BIT0);
	return RdyBsy;
}

/*******************************************************************************
* Function Name  : API_FLASH_SecbitRead
* Description	 : 
* Input 		 : Secbit
* Output		 : SECBIT<D0>/<SECBIT>
* Return		 : 
*******************************************************************************/
u_int8 API_FLASH_SecbitRead(void)
{
	u_int8	Secbit;
	Secbit = BITBAND_IP(FLASH->IO_SECBIT.reg,BIT0);
	return Secbit;
}

/*******************************************************************************
* Function Name  : API_FLASH_SecbitSet
* Description	 : 
* Input 		 : SECBIT<D0>/<SECBIT>
* Output		 : secbit(setting data)
* Return		 : 
*******************************************************************************/
void API_FLASH_SecbitSet(u_int8 secbit)
{
	BITBAND_IP(FLASH->IO_SECBIT.reg,BIT0) = (u_int8)secbit;
}


