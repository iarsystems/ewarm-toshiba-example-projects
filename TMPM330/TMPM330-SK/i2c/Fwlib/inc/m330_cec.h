/*******************************************************************************
* File Name 		 : m330_sfr.h
* Version			 : V1.0
* Date				 : 20xx/xx/xx
* Description		 : SFR define
********************************************************************************/

/* avoid double definition */
#ifndef __M330_CEC_H
#define __M330_CEC_H

#include "m330_ip.h"


	/* Individual setting symbol */

/* CEC recive register initial data */
#define IO_CEC_CECRCR1_Init		((u_int32)0x00000000)
#define IO_CEC_CECRCR2_Init		((u_int16)0x0000)
#define IO_CEC_CECRCR3_Init		((u_int32)0x00000000)

typedef enum { CEC_ACK = 0, CEC_NACK =1 } IpCEC_AckRespons;
#define IP_CEC_ACK_RESPONS(STATUS)	((STATUS == CEC_ACK) || (STATUS == CEC_NACK))

typedef enum { CEC_ERR_NO_HOLD = 0, CEC_ERR_HOLD =1 } IpCEC_HoldState;
#define IP_CEC_ERR_HOLD_STATUS(STATUS)	((STATUS == CEC_ERR_NO_HOLD) || (STATUS == CEC_ERR_HOLD))

typedef enum { CEC_NO_SNOOP = 0, CEC_SNOOP =1 } IpCEC_SnoopState;
#define IP_CEC_SNOOP_STATUS(STATUS)	((STATUS == CEC_NO_SNOOP) || (STATUS == CEC_SNOOP))

typedef enum { CEC_DIRECT = 0, CEC_BROADCAST =1 } IpCEC_BroadcastState;
#define IP_CEC_BROADCAST_STATUS(STATUS)	((STATUS == CEC_DIRECT) || (STATUS == CEC_BROADCAST))

/* CEC send register initial data */
#define IO_CEC_CECTCR_Init		((u_int32)0x00000000)

/* CEC Ack/NACK respons */
#define IO_CEC_Ack				((u_int32)0x00000001)
#define IO_CEC_Nack				((u_int32)0x00000000)

/* CEC receive error hold */
#define IO_CEC_ErrorNoHold		((u_int32)0x00000000)
#define IO_CEC_ErrorHold		((u_int32)0x00000001)

/* CEC receive snoop */
#define IO_CEC_NoSnoop			((u_int32)0x00000000)
#define IO_CEC_Snoop			((u_int32)0x00000001)

/* CEC send Enable/Disable */
#define IO_CEC_SEND_Enable		((u_int8)0x01)
#define IO_CEC_SEND_Disable		((u_int8)0xFE)

/* CEC send broadcast */
#define IO_CEC_Direct			((u_int32)0x00000000)
#define IO_CEC_Broadcast		((u_int32)0x00000001)

/* CEC bus free mask */
#define IO_CEC_BUS_MASK			((u_int32)0xFFFFFFF0)


#define STOP		0
#define ACTIVE		1





	/* Batch setting symbol */

	/* CECRCR1 */

#define IP_CEC_ACKDIS	0x01000000		/* CECACKDIS			 */

#define IP_CEC_HNC00	0x00000000		/* Noize cancel 00 cycle */
#define IP_CEC_HNC01	0x00100000		/* Noize cancel 01 cycle */
#define IP_CEC_HNC02	0x00200000		/* Noize cancel 02 cycle */
#define IP_CEC_HNC03	0x00300000		/* Noize cancel 03 cycle */

#define IP_CEC_LNC00	0x00000000		/* Noize cancel 00 cycle */
#define IP_CEC_LNC01	0x00010000		/* Noize cancel 01 cycle */
#define IP_CEC_LNC02	0x00020000		/* Noize cancel 02 cycle */
#define IP_CEC_LNC03	0x00030000		/* Noize cancel 03 cycle */
#define IP_CEC_LNC04	0x00040000		/* Noize cancel 04 cycle */
#define IP_CEC_LNC05	0x00050000		/* Noize cancel 05 cycle */
#define IP_CEC_LNC06	0x00060000		/* Noize cancel 06 cycle */
#define IP_CEC_LNC07	0x00070000		/* Noize cancel 07 cycle */

#define IP_CEC_MIN00	0x00000000		/* MIN. 2.05mS           */
#define IP_CEC_MIN01	0x00001000		/* MIN. 2.05mS + 1 cycle */
#define IP_CEC_MIN02	0x00002000		/* MIN. 2.05mS + 2 cycle */
#define IP_CEC_MIN03	0x00003000		/* MIN. 2.05mS + 3 cycle */
#define IP_CEC_MIN04	0x00004000		/* MIN. 2.05mS - 1 cycle */
#define IP_CEC_MIN05	0x00005000		/* MIN. 2.05mS - 2 cycle */
#define IP_CEC_MIN06	0x00006000		/* MIN. 2.05mS - 3 cycle */
#define IP_CEC_MIN07	0x00007000		/* MIN. 2.05mS - 4 cycle */

#define IP_CEC_MAX00	0x00000000		/* MAX. 2.75mS           */
#define IP_CEC_MAX01	0x00000100		/* MAX. 2.75mS + 1 cycle */
#define IP_CEC_MAX02	0x00000200		/* MAX. 2.75mS + 2 cycle */
#define IP_CEC_MAX03	0x00000300		/* MAX. 2.75mS + 3 cycle */
#define IP_CEC_MAX04	0x00000400		/* MAX. 2.75mS - 1 cycle */
#define IP_CEC_MAX05	0x00000500		/* MAX. 2.75mS - 2 cycle */
#define IP_CEC_MAX06	0x00000600		/* MAX. 2.75mS - 3 cycle */
#define IP_CEC_MAX07	0x00000700		/* MAX. 2.75mS - 4 cycle */

#define IP_CEC_DATA00	0x00000000		/* DATA 1.05mS           */
#define IP_CEC_DATA01	0x00000010		/* DATA 1.05mS + 2 cycle */
#define IP_CEC_DATA02	0x00000020		/* DATA 1.05mS + 4 cycle */
#define IP_CEC_DATA03	0x00000030		/* DATA 1.05mS + 6 cycle */
#define IP_CEC_DATA04	0x00000040		/* DATA 1.05mS - 2 cycle */
#define IP_CEC_DATA05	0x00000050		/* DATA 1.05mS - 4 cycle */
#define IP_CEC_DATA06	0x00000060		/* DATA 1.05mS - 6 cycle */

#define IP_CEC_TIMOT00	0x00000000		/* Time Out 1 bit        */
#define IP_CEC_TIMOT01	0x00000004		/* Time Out 2 bit        */
#define IP_CEC_TIMOT02	0x00000008		/* Time Out 3 bit        */

#define IP_CEC_RIHLD	0x00000002		/* CECRIHLD		         */
#define IP_CEC_OTH		0x00000001		/* CECOTH		         */




	/* CECRCR2 */
#define IP_CEC_SWAV3_00		0x0000		/* Start bit WAVE_3 4.7mS          */
#define IP_CEC_SWAV3_01		0x1000		/* Start bit WAVE_3 4.7mS + 1 cycle */
#define IP_CEC_SWAV3_02		0x2000		/* Start bit WAVE_3 4.7mS + 2 cycle */
#define IP_CEC_SWAV3_03		0x3000		/* Start bit WAVE_3 4.7mS + 3 cycle */
#define IP_CEC_SWAV3_04		0x4000		/* Start bit WAVE_3 4.7mS + 4 cycle */
#define IP_CEC_SWAV3_05		0x5000		/* Start bit WAVE_3 4.7mS + 5 cycle */
#define IP_CEC_SWAV3_06		0x6000		/* Start bit WAVE_3 4.7mS + 6 cycle */
#define IP_CEC_SWAV3_07		0x7000		/* Start bit WAVE_3 4.7mS + 7 cycle */

#define IP_CEC_SWAV2_00		0x0000		/* Start bit WAVE_2 4.3mS          */
#define IP_CEC_SWAV2_01		0x0100		/* Start bit WAVE_2 4.3mS - 1 cycle */
#define IP_CEC_SWAV2_02		0x0200		/* Start bit WAVE_2 4.3mS - 2 cycle */
#define IP_CEC_SWAV2_03		0x0300		/* Start bit WAVE_2 4.3mS - 3 cycle */
#define IP_CEC_SWAV2_04		0x0400		/* Start bit WAVE_2 4.3mS - 4 cycle */
#define IP_CEC_SWAV2_05		0x0500		/* Start bit WAVE_2 4.3mS - 5 cycle */
#define IP_CEC_SWAV2_06		0x0600		/* Start bit WAVE_2 4.3mS - 6 cycle */
#define IP_CEC_SWAV2_07		0x0700		/* Start bit WAVE_2 4.3mS - 7 cycle */

#define IP_CEC_SWAV1_00		0x0000		/* Start bit WAVE_1 3.9mS          */
#define IP_CEC_SWAV1_01		0x0010		/* Start bit WAVE_1 3.9mS + 1 cycle */
#define IP_CEC_SWAV1_02		0x0020		/* Start bit WAVE_1 3.9mS + 2 cycle */
#define IP_CEC_SWAV1_03		0x0030		/* Start bit WAVE_1 3.9mS + 3 cycle */
#define IP_CEC_SWAV1_04		0x0040		/* Start bit WAVE_1 3.9mS + 4 cycle */
#define IP_CEC_SWAV1_05		0x0050		/* Start bit WAVE_1 3.9mS + 5 cycle */
#define IP_CEC_SWAV1_06		0x0060		/* Start bit WAVE_1 3.9mS + 6 cycle */
#define IP_CEC_SWAV1_07		0x0070		/* Start bit WAVE_1 3.9mS + 7 cycle */

#define IP_CEC_SWAV0_00		0x0000		/* Start bit WAVE_0 3.5mS          */
#define IP_CEC_SWAV0_01		0x0001		/* Start bit WAVE_0 3.5mS - 1 cycle */
#define IP_CEC_SWAV0_02		0x0002		/* Start bit WAVE_0 3.5mS - 2 cycle */
#define IP_CEC_SWAV0_03		0x0003		/* Start bit WAVE_0 3.5mS - 3 cycle */
#define IP_CEC_SWAV0_04		0x0004		/* Start bit WAVE_0 3.5mS - 4 cycle */
#define IP_CEC_SWAV0_05		0x0005		/* Start bit WAVE_0 3.5mS - 5 cycle */
#define IP_CEC_SWAV0_06		0x0006		/* Start bit WAVE_0 3.5mS - 6 cycle */
#define IP_CEC_SWAV0_07		0x0007		/* Start bit WAVE_0 3.5mS - 7 cycle */

	/* CECRCR3 */
#define IP_CEC_WAV3_00		0x00000000		/* WAVE_3 1.7mS          */
#define IP_CEC_WAV3_01		0x00100000		/* WAVE_3 1.7mS + 1 cycle */
#define IP_CEC_WAV3_02		0x00200000		/* WAVE_3 1.7mS + 2 cycle */
#define IP_CEC_WAV3_03		0x00300000		/* WAVE_3 1.7mS + 3 cycle */
#define IP_CEC_WAV3_04		0x00400000		/* WAVE_3 1.7mS + 4 cycle */
#define IP_CEC_WAV3_05		0x00500000		/* WAVE_3 1.7mS + 5 cycle */
#define IP_CEC_WAV3_06		0x00600000		/* WAVE_3 1.7mS + 6 cycle */
#define IP_CEC_WAV3_07		0x00700000		/* WAVE_3 1.7mS + 7 cycle */
                            
#define IP_CEC_WAV2_00		0x00000000		/* WAVE_2 1.3mS          */
#define IP_CEC_WAV2_01		0x00010000		/* WAVE_2 1.3mS - 1 cycle */
#define IP_CEC_WAV2_02		0x00020000		/* WAVE_2 1.3mS - 2 cycle */
#define IP_CEC_WAV2_03		0x00030000		/* WAVE_2 1.3mS - 3 cycle */
#define IP_CEC_WAV2_04		0x00040000		/* WAVE_2 1.3mS - 4 cycle */
#define IP_CEC_WAV2_05		0x00050000		/* WAVE_2 1.3mS - 5 cycle */
#define IP_CEC_WAV2_06		0x00060000		/* WAVE_2 1.3mS - 6 cycle */
#define IP_CEC_WAV2_07		0x00070000		/* WAVE_2 1.3mS - 7 cycle */
                            
#define IP_CEC_WAV1_00		0x00000000		/* WAVE_1 0.8mS          */
#define IP_CEC_WAV1_01		0x00001000		/* WAVE_1 0.8mS + 1 cycle */
#define IP_CEC_WAV1_02		0x00002000		/* WAVE_1 0.8mS + 2 cycle */
#define IP_CEC_WAV1_03		0x00003000		/* WAVE_1 0.8mS + 3 cycle */
#define IP_CEC_WAV1_04		0x00004000		/* WAVE_1 0.8mS + 4 cycle */
#define IP_CEC_WAV1_05		0x00005000		/* WAVE_1 0.8mS + 5 cycle */
#define IP_CEC_WAV1_06		0x00006000		/* WAVE_1 0.8mS + 6 cycle */
#define IP_CEC_WAV1_07		0x00007000		/* WAVE_1 0.8mS + 7 cycle */
                            
#define IP_CEC_WAV0_00		0x00000000		/* WAVE_0 0.4mS          */
#define IP_CEC_WAV0_01		0x00000100		/* WAVE_0 0.4mS - 1 cycle */
#define IP_CEC_WAV0_02		0x00000200		/* WAVE_0 0.4mS - 2 cycle */
#define IP_CEC_WAV0_03		0x00000300		/* WAVE_0 0.4mS - 3 cycle */
#define IP_CEC_WAV0_04		0x00000400		/* WAVE_0 0.4mS - 4 cycle */
#define IP_CEC_WAV0_05		0x00000500		/* WAVE_0 0.4mS - 5 cycle */
#define IP_CEC_WAV0_06		0x00000600		/* WAVE_0 0.4mS - 6 cycle */
#define IP_CEC_WAV0_07		0x00000700		/* WAVE_0 0.4mS - 7 cycle */

#define IP_CEC_WAVEN		0x00000001		/* WAVEN		          */



	/* CECTCR */
#define IP_CEC_STRS_00		0x00000000		/* STRS typ.           */
#define IP_CEC_STRS_01		0x00100000		/* STRS typ. - 1 cycle */
#define IP_CEC_STRS_02		0x00200000		/* STRS typ. - 2 cycle */
#define IP_CEC_STRS_03		0x00300000		/* STRS typ. - 3 cycle */
#define IP_CEC_STRS_04		0x00400000		/* STRS typ. - 4 cycle */
#define IP_CEC_STRS_05		0x00500000		/* STRS typ. - 5 cycle */
#define IP_CEC_STRS_06		0x00600000		/* STRS typ. - 6 cycle */
#define IP_CEC_STRS_07		0x00700000		/* STRS typ. - 7 cycle */
                            
#define IP_CEC_SPRD_00		0x00000000		/* SPRD typ.           */
#define IP_CEC_SPRD_01		0x00010000		/* SPRD typ. - 1 cycle */
#define IP_CEC_SPRD_02		0x00020000		/* SPRD typ. - 2 cycle */
#define IP_CEC_SPRD_03		0x00030000		/* SPRD typ. - 3 cycle */
#define IP_CEC_SPRD_04		0x00040000		/* SPRD typ. - 4 cycle */
#define IP_CEC_SPRD_05		0x00050000		/* SPRD typ. - 5 cycle */
#define IP_CEC_SPRD_06		0x00060000		/* SPRD typ. - 6 cycle */
#define IP_CEC_SPRD_07		0x00070000		/* SPRD typ. - 7 cycle */
                            
#define IP_CEC_DTRS_00		0x00000000		/* DTRS typ.           */
#define IP_CEC_DTRS_01		0x00001000		/* DTRS typ. - 1 cycle */
#define IP_CEC_DTRS_02		0x00002000		/* DTRS typ. - 2 cycle */
#define IP_CEC_DTRS_03		0x00003000		/* DTRS typ. - 3 cycle */
#define IP_CEC_DTRS_04		0x00004000		/* DTRS typ. - 4 cycle */
#define IP_CEC_DTRS_05		0x00005000		/* DTRS typ. - 5 cycle */
#define IP_CEC_DTRS_06		0x00006000		/* DTRS typ. - 6 cycle */
#define IP_CEC_DTRS_07		0x00007000		/* DTRS typ. - 7 cycle */
                            
#define IP_CEC_DPRD_00		0x00000000		/* DPRD typ.           */
#define IP_CEC_DPRD_01		0x00000100		/* DPRD typ. -  1 cycle */
#define IP_CEC_DPRD_02		0x00000200		/* DPRD typ. -  2 cycle */
#define IP_CEC_DPRD_03		0x00000300		/* DPRD typ. -  3 cycle */
#define IP_CEC_DPRD_04		0x00000400		/* DPRD typ. -  4 cycle */
#define IP_CEC_DPRD_05		0x00000500		/* DPRD typ. -  5 cycle */
#define IP_CEC_DPRD_06		0x00000600		/* DPRD typ. -  6 cycle */
#define IP_CEC_DPRD_07		0x00000700		/* DPRD typ. -  7 cycle */
#define IP_CEC_DPRD_08		0x00000800		/* DPRD typ. -  8 cycle */
#define IP_CEC_DPRD_09		0x00000900		/* DPRD typ. -  9 cycle */
#define IP_CEC_DPRD_10		0x00000A00		/* DPRD typ. - 10 cycle */
#define IP_CEC_DPRD_11		0x00000B00		/* DPRD typ. - 11 cycle */
#define IP_CEC_DPRD_12		0x00000C00		/* DPRD typ. - 12 cycle */
#define IP_CEC_DPRD_13		0x00000D00		/* DPRD typ. - 13 cycle */
#define IP_CEC_DPRD_14		0x00000E00		/* DPRD typ. - 14 cycle */
#define IP_CEC_DPRD_15		0x00000F00		/* DPRD typ. - 15 cycle */

#define IP_CEC_FREE_00		0x00000000		/* Bus Free  1 bit     */
#define IP_CEC_FREE_01		0x00000001		/* Bus Free  2 bit     */
#define IP_CEC_FREE_02		0x00000002		/* Bus Free  3 bit     */
#define IP_CEC_FREE_03		0x00000003		/* Bus Free  4 bit     */
#define IP_CEC_FREE_04		0x00000004		/* Bus Free  5 bit     */
#define IP_CEC_FREE_05		0x00000005		/* Bus Free  6 bit     */
#define IP_CEC_FREE_06		0x00000006		/* Bus Free  7 bit     */
#define IP_CEC_FREE_07		0x00000007		/* Bus Free  8 bit     */
#define IP_CEC_FREE_08		0x00000008		/* Bus Free  9 bit     */
#define IP_CEC_FREE_09		0x00000009		/* Bus Free 10 bit     */
#define IP_CEC_FREE_10		0x0000000A		/* Bus Free 11 bit     */
#define IP_CEC_FREE_11		0x0000000B		/* Bus Free 12 bit     */
#define IP_CEC_FREE_12		0x0000000C		/* Bus Free 13 bit     */
#define IP_CEC_FREE_13		0x0000000D		/* Bus Free 14 bit     */
#define IP_CEC_FREE_14		0x0000000E		/* Bus Free 15 bit     */
#define IP_CEC_FREE_15		0x0000000F		/* Bus Free 16 bit     */

#define IP_CEC_BRD			0x00000010		/* CECBRD	           */


/**************************************************************/

void API_CEC_Init(void);
void API_CEC_SoftReset(void);
void API_CEC_IP_Enable(IpFunctionState NewState);
void API_CEC_Idle(IpFunctionState NewState);
void API_CEC_IntEnable(void);
void API_CEC_RcvEnable(IpFunctionState NewState);
u_int8 API_CEC_RcvStatus(void);
void API_CEC_RcvRegInit(void);
void API_CEC_RcvRegSet(u_int32,u_int16,u_int32);
void API_CEC_SndRegSet(u_int32);
void API_CEC_SndRegInit(void);
void API_CEC_LogAdrSet(u_int16);
u_int16 API_CEC_RcvDataRead(void);
void API_CEC_AckRespons(IpCEC_AckRespons AckRespons);
void API_CEC_RcvErrIntHold(IpCEC_HoldState HoldState);
void API_CEC_RcvSnoop(IpCEC_SnoopState SnoopState);
void API_CEC_WebErrDet(IpFunctionState NewState);
void API_CEC_SndStart(IpFunctionState NewState);
u_int8 API_CEC_SndStatus(void);
void API_CEC_SndDataSet(u_int16);
void API_CEC_SndBroadcast(IpCEC_BroadcastState BroadcastState);
void API_CEC_BusFree(u_int8);
u_int8 API_CEC_RcvIntStatus(void);
u_int8 API_CEC_SndIntStatus(void);












#endif /* avoid double definition */
