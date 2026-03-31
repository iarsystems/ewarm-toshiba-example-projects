/*******************************************************************************
* File Name 		 : m380_int.c
* Version			 : V1.0
* Date				 : 2010/01/XX
* Description		 : Interrupt liblary source
********************************************************************************/

#include "..\typedef.h"
#include "TMPM380_SYS.h"

#include "m380_int.h"


/*******************************************************************************
* Function Name  : API_INT_Init
* Description	 : 割込み関連の初期化を行う。
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_Init(void)
{
/*----- MCU(M380) INTERRUPT INITIALIZE -----*/
	API_INT_claer_Init();
	CG.RSTFLG = 0x00;
	API_CG_Active_Reset();

/*----- Cortex-M3 NVIC INITIALIZE -----*/
	API_INT_PR_Reset();				/* 割込みレベル */
	NVIC_INT_CTRL = 0x00000000;		/* 割込み制御状態レジスタ */
	NVIC_VECT_TABLE = 0x00000000;	/* ベクタテーブルオフセットレジスタ */
	NVIC_SYS_H_PRI1 = 0x00000000;	/* システムハンドラ優先順位レジスタ */
	NVIC_SYS_H_PRI2 = 0x00000000;
	NVIC_SYS_H_PRI3 = 0x00000000;
	NVIC_SYS_H_CTRL = 0x00000000;	/* システムハンドラ制御レジスタ */
	NVIC_ST_CTRL = 0x00000000;		/* SysTick 制御レジスタ */
}

/*******************************************************************************
* Function Name  : API_INT_clear_Init
* Description	 : 全てのスタンバイ解除要因クリア
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_claer_Init(void)
{
	CG.ICRCG = IP_INT_CLR_INT0;
	CG.ICRCG = IP_INT_CLR_INT1;
	CG.ICRCG = IP_INT_CLR_INT2;
	CG.ICRCG = IP_INT_CLR_INT3;
	CG.ICRCG = IP_INT_CLR_INT4;
	CG.ICRCG = IP_INT_CLR_INT5;
	CG.ICRCG = IP_INT_CLR_INT6;
	CG.ICRCG = IP_INT_CLR_INT7;
	CG.ICRCG = IP_INT_CLR_INT8;
	CG.ICRCG = IP_INT_CLR_INT9;
	CG.ICRCG = IP_INT_CLR_INTA;
	CG.ICRCG = IP_INT_CLR_INTB;
	CG.ICRCG = IP_INT_CLR_INTC;
	CG.ICRCG = IP_INT_CLR_INTD;
	CG.ICRCG = IP_INT_CLR_INTE;
	CG.ICRCG = IP_INT_CLR_INTF;
	CG.ICRCG = IP_INT_CLR_INTRTC;
	CG.ICRCG = IP_INT_CLR_INTRMCRX;
}


/*******************************************************************************
* Function Name  : API_CG_Active_Set
* Description	 : CG割込みモード、アクティブレベルを設定する。
* Input 		 : Enable Set 0-15
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_Active_Set(uint8_t ip_intnum, uint8_t active, uint8_t enable)
{
	CG.IMCG[ip_intnum] = active | enable;
}


/*******************************************************************************
* Function Name  : API_CG_Active_Reset
* Description	 : CG割込みモード、アクティブレベルを初期化する。
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_CG_Active_Reset(void)
{
	CG.IMCG[IP_INT_CLR_INT0] = 0x20;
	CG.IMCG[IP_INT_CLR_INT1] = 0x20;
	CG.IMCG[IP_INT_CLR_INT2] = 0x20;
	CG.IMCG[IP_INT_CLR_INT3] = 0x20;
	CG.IMCG[IP_INT_CLR_INT4] = 0x20;
	CG.IMCG[IP_INT_CLR_INT5] = 0x20;
	CG.IMCG[IP_INT_CLR_INT6] = 0x20;
	CG.IMCG[IP_INT_CLR_INT7] = 0x20;
	CG.IMCG[IP_INT_CLR_INT8] = 0x20;
	CG.IMCG[IP_INT_CLR_INT9] = 0x20;
	CG.IMCG[IP_INT_CLR_INTA] = 0x20;
	CG.IMCG[IP_INT_CLR_INTB] = 0x20;
	CG.IMCG[IP_INT_CLR_INTC] = 0x20;
	CG.IMCG[IP_INT_CLR_INTD] = 0x20;
	CG.IMCG[IP_INT_CLR_INTE] = 0x20;
	CG.IMCG[IP_INT_CLR_INTF] = 0x20;
	CG.IMCG[IP_INT_CLR_INTRTC] = 0x20;
	CG.IMCG[IP_INT_CLR_INTRMCRX] = 0x20;
}


/*******************************************************************************
* Function Name  : API_INT_CER_All_Set
* Description	 : 
* Input 		 : 全ての割込みを禁止する
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_CER_All_Set(void)
{
	NVIC_CLRENA.num[0] = 0xFFFFFFFF;			/* 0  - 31 */
	NVIC_CLRENA.num[1] = 0xFFFFFFFF;			/* 31 - 63 */
}



/*******************************************************************************
* Function Name  : API_INT_CER_Set
* Description	 : 指定された割込みを禁止する。
* Input 		 : Enable Clear IRQ 0-239
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_CER_Set(uint8_t intnum)
{
	uint8_t num,bit;
	uint32_t clerena;

	num = intnum/32;
	bit = intnum%32;
	clerena = NVIC_CLRENA.num[num];
    NVIC_CLRENA.num[num] = ~(clerena)|(0x00000001 << bit);
}


/*******************************************************************************
* Function Name  : API_INT_PR_Set
* Description	 : 指定された割込みの割込みレベルを設定する。
* Input 		 : Priority IRQ 0-239
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_PR_Set(uint8_t intnum, uint8_t pri)
{
	NVIC_PRI.num[intnum] = pri;
}


/*******************************************************************************
* Function Name  : API_INT_PR_Reset
* Description	 : 割込みの割込みレベルを初期化する。
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_PR_Reset(void)
{
	uint8_t i;
	for (i=0; i<240; i++){
		NVIC_PRI.num[i] = 0x00;
	}
}

/*******************************************************************************
* Function Name  : API_INT_SPR_ALL_Set
* Description	 : 全ての保留状態の割り込みをクリア
* Input 		 : 
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SPR_ALL_Set(void)
{
	NVIC_CLRPEND.num[0] = 0xFFFFFFFF;		/* 0  - 31 */
	NVIC_CLRPEND.num[1] = 0xFFFFFFFF;		/* 32 - 63 */
}


/*******************************************************************************
* Function Name  : API_INT_SPR_Set
* Description	 : 指定された保留状態の割り込みをクリア
* Input 		 : Clear Pending IRQ 0-239
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SPR_Set(uint8_t intnum)
{
	uint8_t num,bit;

	num = intnum/32;
	bit = intnum%32;
	NVIC_CLRPEND.num[num] |= (0x00000001 << bit);
}


/*******************************************************************************
* Function Name  : API_INT_SER_Set
* Description	 : 指定された割込みを許可する。
* Input 		 : Enable Set IRQ 0-239
* Output		 : 
* Return		 : 
*******************************************************************************/
void API_INT_SER_Set(uint8_t intnum)
{
	uint8_t num,bit;

	num = intnum/32;
	bit = intnum%32;
	NVIC_SETENA.num[num] |= (0x00000001 << bit);
}

/*********************************** END OF FILE ******************************/
