/******************** (c) Copyright IAR Systems 2009 *************************
* File Name          : adc.c
* Version            : V1.0
* Date               : 20/10/2008
* Description        : Potentiometer and microphone
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "adc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* external variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
* Function Name  : ADC_Init
* Description    : Initialize the adc
* Input          : None.
* Return         : None.
*******************************************************************************/
void ADC_Init(void)
{
	// Potentiometer  port --- PC, PD
	API_ADC_ChSet(ADC_IN);
	
	// set ADC as data polling mode
	API_ADC_MOD0_Set(0x04);
}

/*******************************************************************************
* Function Name  : ADC_Init
* Description    : Initialize the adc
* Input          : None.
* Return         : None.
*******************************************************************************/
void MIC_Init(void)
{
	// Potentiometer  port --- PC, PD
	API_ADC_Init();
	API_ADC_ChSet(MIC_AIN);
	// set ADC as data polling mode
	API_ADC_MOD0_Set(0x04);
}


/*******************************************************************************
* Function Name  : ADC_Get_Value
* Description    : Initialize the adc
* Input          : None.
* Return         : conversion value.
*******************************************************************************/
u_int16 ADC_Get_Value(void)
{
	u_int16 AdcValue = 0;
	//AdcValue = AdcValue << 2;
	API_ADC_VrefSet(ENABLE);
	Delay_ms(1);
	API_ADC_Start_Set();
	// wait the conversion complete
	while(!(API_ADC_MOD0_Read() & 0x80));
	AdcValue = API_ADC_DataRead(_ADCREG08);
	//AdcValue = API_ADC_DataRead(_ADCREG19);
	//AdcValue = API_ADC_DataRead(_ADCREG2A);
	//AdcValue = API_ADC_DataRead(_ADCREG3B);
	
	return AdcValue;
}

/*************************** END OF FILE **************************************/

