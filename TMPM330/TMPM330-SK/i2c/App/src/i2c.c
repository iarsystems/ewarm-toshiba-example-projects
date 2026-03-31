/******************** (c) Copyright IAR Systems 2009 ***************************
* File Name          : i2c.c
* Version            : V1.0
* Date               : 20/10/2008
* Description        : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_Speed              400000
#define I2C1_SLAVE_ADDRESS7    0xA0
#define I2C_PageSize           8
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
* Function Name  : I2C_Init
* Description    : Initialize the I2C
* Input          : None.
* Return         : None.
*******************************************************************************/
void I2C_Init(void)
{
	API_SBI_Init(SBI2);
	// enable the SBI(CR0) then can setting the registers
	API_SBI_IP_Enable(SBI2,ENABLE);
	// wait the bus is free 
	// 这里要在最后修改，不能在这里死循环！！！！！！！！！！！！！！！！！！！
	//while(API_SBI_StatusRead(SBI2)&0x20);
	// enable ACK and SCL clock
 	API_SBI_CR1_Set(SBI2,0x09);
	// write the addr of SBI2
	API_SBIi_SlvAddressSet(SBI2,0xA0);
	// wait the bus is free 
	while(API_SBI_StatusRead(SBI2)&0x20);
	// Configures the SBI as a I2C slave receiver
	API_SBI_CR2_Set(SBI2,0x18);
	API_SBI_Idle(SBI2,ENABLE);
	
}

/*******************************************************************************
* Function Name  : I2C_ByteWrite
* Description    : Writes one byte to the I2C EEPROM.
* Input          : - pBuffer : pointer to the buffer  containing the data to be 
*                    written to the EEPROM.
*                  - WriteAddr : EEPROM's internal address to write to.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_ByteWrite(u_int8* pBuffer, u_int8 WriteAddr)
{
	// Send STRAT condition
  // wait the bus is free 
	while(API_SBI_StatusRead(SBI2)&0x20);
	// enable ACK and SCL clock
 	API_SBI_CR1_Set(SBI2,0x19);
	// set the addr of slave device and the direction is write data(bit0 =0)
	API_SBI_SndDataSet(SBI2,0xA0);
	// set MST, TRX, BB, PIN (CR2)generate 'start' and output 8-bit data(Addr + R/W)
	API_SBI_CR2_Set(SBI2,0xF8);
	// 'start' had be generated, bus is busy
	//while(!(API_SBI_StatusRead(SBI2)&0x20));	
	// read INTSBI2(SR) if as '0', ack returned 
	while(API_SBI_StatusRead(SBI2)&0x10);
	// clear the interrupt
	//API_SBI_CR2_Set(SBI2,0xF8);
	// Send the EEPROM's internal address to write to 
	API_SBI_SndDataSet(SBI2,WriteAddr);
	// wait the ack
	while(API_SBI_StatusRead(SBI2)&0x10);
	// clear the interrupt
	//API_SBI_CR2_Set(SBI2,0xF8);
	// Send the byte to be written 
  //API_SBI_SndDataSet(SBI2, *pBuffer); 
  API_SBI_SndDataSet(SBI2, *pBuffer); 
	while(API_SBI_StatusRead(SBI2)&0x10); 
  // 'start' had be generated, bus is busy
  while(!(API_SBI_StatusRead(SBI2)&0x20));	  
  // Send STOP condition 
	API_SBI_CR2_Set(SBI2,0xD8);
}

/*******************************************************************************
* Function Name  : I2C_EE_PageWrite
* Description    : Writes more than one byte to the EEPROM with a single WRITE
*                  cycle. The number of byte can't exceed the EEPROM page size.
* Input          : - pBuffer : pointer to the buffer containing the data to be 
*                    written to the EEPROM.
*                  - WriteAddr : EEPROM's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the EEPROM.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_PageWrite(u_int8* pBuffer, u_int8 WriteAddr, u_int8 NumByteToWrite)
{
  // wait the bus is free 
	while(API_SBI_StatusRead(SBI2)&0x20);
  // enable ACK and SCL clock
 	API_SBI_CR1_Set(SBI2,0x19);
	// set the addr of slave device and the direction is write data(bit0 =0)
	API_SBI_SndDataSet(SBI2,0xA0);
	// set MST, TRX, BB, PIN (CR2)generate 'start' and output 8-bit data(Addr + R/W)
	API_SBI_CR2_Set(SBI2,0xF8);
	// 'start' had be generated, bus is busy
	//while(!(API_SBI_StatusRead(SBI2)&0x20));	
	// read INTSBI2(SR) if as '0', ack returned 
	while(API_SBI_StatusRead(SBI2)&0x10);
	// clear the interrupt
	//API_SBI_CR2_Set(SBI2,0xF8);
	// Send the EEPROM's internal address to write to 
	API_SBI_SndDataSet(SBI2,WriteAddr);
	// wait the ack
	while(API_SBI_StatusRead(SBI2)&0x10); 
  
  // While there is data to be written 
  while(NumByteToWrite--)  
  {
    // Send the byte to be written 
  	API_SBI_SndDataSet(SBI2, *pBuffer); 
    // Point to the next byte to be written 
    pBuffer++; 
    // read INTSBI2(SR) if as '0', ack returned 
		while(API_SBI_StatusRead(SBI2)&0x10);
  }
  // 'start' had be generated, bus is busy
  while(!(API_SBI_StatusRead(SBI2)&0x20));
	// Send STOP condition 
	API_SBI_CR2_Set(SBI2,0xD8);
}

/************************END OF FILE*******************************************/
