/* ======================================================================== */
/*
  復帰されるまで、割り込み処理を中断する
  main <=> interrupt
*/
/* ------------------------------------------------------------------------ */

  PUBLIC  usb_CTXSWT_vSlpIntrCtx

  IMPORT  tUSB_SAVE_REG
  IMPORT  fvUSB_INTR
  IMPORT  pulSTACK_AREA
  IMPORT  tUSB_INT_REG
  IMPORT	usb_INTR_vDisable;
	IMPORT	usb_INTR_vEnable;

?blSavedFlag  DEFINE    0
?ul_r0        DEFINE    4
?ul_sp        DEFINE    56
?ul_pc        DEFINE    64

?ulSP         DEFINE    0
?ulPC         DEFINE    4

    SECTION .text:CODE:NOROOT(2)
    ARM
usb_CTXSWT_vSlpIntrCtx
	PRESERVE8

	PUSH		{r4,lr}

	/* すでにコンテキスト保存済み */
	LDR		r0, = tUSB_SAVE_REG + ?blSavedFlag;
	LDRB	r0,[r0,#0];
	CMP		r0,#0;					/* if(tUSB_SAVE_REG.blSavedFlag != false)	*/
	BEQ		LINE_vSlpIntrCtx_CONDITION1_THEN		/* then	*/

	/*
		DEBUG_ERROR_CALL( 3, "CTXSWT_vChgIntrCtx", NULL );
	 */
LINE_vSlpIntrCtx_END_PROCEDURE;
	/*	return;	*/
	POP		{r4,pc};

LINE_vSlpIntrCtx_CONDITION1_THEN;
	/* 割り込み禁止
     待ちの最中に USB 割り込みが入ると、順序関係が狂う */
	
	BLX		usb_INTR_vDisable;

	/* コンテキスト保存フラグを ON 			*/
	/* tUSB_SAVE_REG.blSavedFlag = true;	*/
	MOV		r0,#1		/* get true	*/
	LDR		r1, = tUSB_SAVE_REG + ?blSavedFlag;
	STRB	r0,[r1,#0];

	/* 全レジスタを保存 */
	LDR		r0, = tUSB_SAVE_REG + ?ul_r0;
	STR		r0,[r0,#0x00];
	STR		r1,[r0,#0x04];
	STR		r2,[r0,#0x08];
	STR		r3,[r0,#0x0C];
	STR		r4,[r0,#0x10];
	STR		r5,[r0,#0x14];
	STR		r6,[r0,#0x18];
	STR		r7,[r0,#0x1C];
	STR		r8,[r0,#0x20];
	STR		r9,[r0,#0x24];
	STR		r10,[r0,#0x28];
	STR		r11,[r0,#0x2C];
	STR		r12,[r0,#0x30];
	STR		sp,[r0,#0x34];
	STR		lr,[r0,#0x38];

	LDR		r1,=LINE_USB_START_LABEL;
	STR		r1,[r0,#0x3C];			/* save next pc	*/

	/* 呼び出し元コンテキストに復帰する */
	LDR		r0, =tUSB_INT_REG+?ulSP;
	LDR		r0,[r0,#0];
#if 1
	MOV		sp, r0;
#else
	MOV		r0,sp;
#endif
	LDR		r0, =tUSB_INT_REG+?ulPC;
	LDR		r0,[r0,#0];
//	MOV		r0,pc;					/* jump pc?	*/
	BX		r0;

LINE_USB_START_LABEL;
	/* 全レジスタを復帰 */
	LDR		r0, =tUSB_SAVE_REG + ?ul_r0;
	LDR		r1,[r0,#0x04];
	LDR		r2,[r0,#0x08];
	LDR		r3,[r0,#0x0C];
	LDR		r4,[r0,#0x10];
	LDR		r5,[r0,#0x14];
	LDR		r6,[r0,#0x18];
	LDR		r7,[r0,#0x1C];
	LDR		r8,[r0,#0x20];
	LDR		r9,[r0,#0x24];
	LDR		r10,[r0,#0x28];
	LDR		r11,[r0,#0x2C];
	LDR		r12,[r0,#0x30];
	LDR		sp,[r0,#0x34];
	LDR		lr,[r0,#0x38];

	/* コンテキスト保存フラグをクリアする */
	MOV		r0,#0		/* get false	*/
	LDR		r1, =tUSB_SAVE_REG + ?blSavedFlag;
	STRB	r0,[r1,#0];

	/* 割り込み許可 */
	BLX		usb_INTR_vEnable
	/* 呼び出し元へ戻る */
	B		LINE_vSlpIntrCtx_END_PROCEDURE;

  END
