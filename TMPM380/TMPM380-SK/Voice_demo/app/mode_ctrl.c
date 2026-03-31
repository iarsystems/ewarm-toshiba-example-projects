/*******************************************************************************
* File Name          : mode_ctrl.c
* Version            : V1.0
* Date				 : 2010/01/XX
* Description        : Timer Contorl
*******************************************************************************/
#include	"ram_def.h"

#include	"..\mcu\m380_tmrb.h"
#include	"..\mcu\m380_mpt.h"

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
 * Module   : Mode_ctrl
 *---------------------------------------------------------------------------------------
 * Function : Mode_ctrl
 * Input    : none
 * Output   : none
 * Note     : 
 ****************************************************************************************/
void Mode_ctrl(void)
{

	switch(g_md_sts){
		case STOP:
		case WAIT:
			if(g_wait_timer >= cWAITTIMER_MAX){ /* voice start */
				g_wait_timer = 0;
				g_pcm_cnt = 0;
				g_led_timer = 0;
				API_TMRB_Run(TMRB_0,TMRB_RUN);		/* TMBR0 Timer Start */
				g_voice_flg = 1;
				g_md_sts = RUN;
			}
			break;
		case RUN:
			if(g_led_timer > cLEDTIMER_MAX){ /* counter clear */
				g_led_timer=0;
			}
			if(g_voice_flg == 0){  /* voice stop */
				g_wait_timer = 0;
				g_md_sts=WAIT;
			}
			if(g_sw1_data == 1){  /* voice pause */
				API_TMRB_Run(TMRB_0,TMRB_STOP);		/* TMBR0 Timer Stop */
				g_ppg_data = cPPGDUDY50;
				API_MTTB_REG1_Write(MPT_0, g_ppg_data+cPPGADJUST);		/*set IGBT Timer REG2 */
				g_led_timer_buf = g_led_timer;
				g_voice_flg = 0;
				g_md_sts = HALT;
			}
			break;
		case HALT:
			if(g_sw1_data == 0){  /* voice restart */
				g_led_timer = g_led_timer_buf;
				API_TMRB_Run(TMRB_0,TMRB_RUN);		/* TMBR0 Timer Start */
				g_voice_flg = 1;
				g_md_sts = RUN;
			}
			break;
		default:
			break;
	}
}

/*********************************** END OF FILE ******************************/
