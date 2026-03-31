/*******************************************************************************
* File Name          : voice_ctrl.c
* Version            : V1.0
* Date				 : 2010/01/XX
* Description        : VOICE Contorl
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include	"ram_def.h"

#include	"..\mcu\m380_tmrb.h"
#include	"..\mcu\m380_mpt.h"

#include	"voice_ctrl.h"
#include	"spiflash.h"


/********************************************************************
 * Extern Definition
 ********************************************************************/

/********************************************************************
 * Variable Definition
 ********************************************************************/

/********************************************************************
 * Constant Definition
 ********************************************************************/

/********************************************************************
 * Function Definition
 ********************************************************************/

/****************************************************************************************
 * Module   : Voice_Write
 *---------------------------------------------------------------------------------------
 * Function : Voice_Write
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void Voice_Write(void)
{

	switch(g_md_sts){
		case STOP:
			break;
		case WAIT:
			break;
		case RUN:
			if( g_pcm_cnt > g_pcm_size - 1 ){
				g_ppg_data = cPPGDUDY50;
				g_pcm_cnt = 0;
				g_voice_flg = 0;
			}
			else{
#ifdef SAMPLE_8K
//				g_pcm_data = voice_data_08k[g_pcm_cnt];
				spiflash_read(F_OFS(&voice_data_08k[g_pcm_cnt]), 
							(uint8_t *)&g_pcm_data, sizeof(g_pcm_data));
#endif
#ifdef SAMPLE_16K
//				g_pcm_data = voice_data_16k[g_pcm_cnt];
				spiflash_read(F_OFS(&voice_data_16k[g_pcm_cnt]), 
							(uint8_t *)&g_pcm_data, sizeof(g_pcm_data));
#endif
				g_ppg_data = (uint32_t)((g_pcm_data + 0x8000) * cPPGDUDY100 ) >> 16;	/* PCN2PPG */
				g_pcm_cnt++;
			}
			API_MTTB_REG1_Write(MPT_0, g_ppg_data+cPPGADJUST);			/*set IGBT Timer REG2 */
			break;
		case HALT:
			g_ppg_data = cPPGDUDY50;
                        
			API_MTTB_REG1_Write(MPT_0, g_ppg_data+cPPGADJUST);			/*set IGBT Timer REG2 */
			g_voice_flg = 0;
			break;
		default:
			break;
	}
}

#if 0
void Voice_Write(void)
{

	if( g_pcm_cnt > g_pcm_size - 1 ){
		API_TMRB_Run(TMRB_0,TMRB_STOP);		/* TMBR0 Timer Stop */
		g_ppg_data = cPPGDUDY50;
		g_pcm_cnt = 0;
		g_voice_flg = 0;
	}
	else{
#ifdef SAMPLE_8K
				g_pcm_data = voice_data_08k[g_pcm_cnt];
#endif
#ifdef SAMPLE_16K
				g_pcm_data = voice_data_16k[g_pcm_cnt];
#endif
		g_ppg_data = (uint32_t)((g_pcm_data + 0x8000) * cPPGDUDY100 ) >> 16;	/* PCN2PPG */
		g_pcm_cnt++;
	}
	API_MTTB_REG1_Write(MPT_0, g_ppg_data+cPPGADJUST);			/*set IGBT Timer REG2 */

}
#endif
/*********************************** END OF FILE ******************************/
