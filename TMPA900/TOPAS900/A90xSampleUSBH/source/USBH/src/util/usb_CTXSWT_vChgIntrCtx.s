/* ======================================================================== */
/*
  USB 割込みコンテキスト切り替え
    USB 割り込み発生時にコンテキストを切り替えて実行する
    タイマ割り込みから、中断した USB 割り込みを復帰する

    引数
      fvUsbIntr 割り込み処理関数

	interrupt(timer) <=> interrupt(usb)
 */
/* ------------------------------------------------------------------------ */
  PUBLIC  usb_CTXSWT_vChgIntrCtx

  IMPORT  tUSB_SAVE_REG
  IMPORT  fvUSB_INTR
  IMPORT  pulSTACK_AREA
  IMPORT  tUSB_INT_REG

    SECTION .text:CODE:NOROOT(2)
    ARM

?blSavedFlag  DEFINE    0
?ul_sp        DEFINE    56
?ul_pc        DEFINE    64

?ulSP         DEFINE    0
?ulPC         DEFINE    4


usb_CTXSWT_vChgIntrCtx:

  /* save data "fvUsbIntr, lr"	*/
	PUSH		{r4,lr};
	
	/* if((fvUsbIntr==NULL) && (tUSB_SAVE_REG.blSavedFlag==false))	*/
	MOV		r4,r0;					/* get fvUsbIntr				*/
	CMP		r4,#0;					/* if(fvUsbIntr == NULL)		*/
	BNE		LINE_vChgIntrCtx_CONDITION1_ELSE;	/* else				*/

	LDR		r0, = (tUSB_SAVE_REG + ?blSavedFlag);
	LDRB	r0,[r0,#0];
	CMP		r0,#0;					/* if(tUSB_SAVE_REG.blSavedFlag == false)	*/
	BEQ		LINE_vChgIntrCtx_CONDITION2_THEN;	/* then							*/

LINE_vChgIntrCtx_CONDITION1_ELSE:
	/* if((fvUsbIntr != NULL) && (tUSB_SAVE_REG.blSavedFlag != false))	*/
	CMP		r4,#0;							/* if(fvUsbIntr != NULL)	*/
	BEQ		LINE_vChgIntrCtx_CONDITION3_THEN;	/* then					*/

	LDR		r0, = (tUSB_SAVE_REG + ?blSavedFlag);
	LDRB	r0,[r0,#0];
	CMP		r0,#0;				/* if(tUSB_SAVE_REG.blSavedFlag != false)	*/
	BEQ		LINE_vChgIntrCtx_CONDITION4_ELSE;	/* else						*/

LINE_vChgIntrCtx_CONDITION2_THEN;
	/*
		DEBUG_ERROR_CALL( 3, "CTXSWT_vChgIntrCtx", NULL );
	 */
LINE_END_PROCEDURE;
	/*	return;	*/
	POP		{r4,pc};

LINE_vChgIntrCtx_CONDITION3_THEN;
LINE_vChgIntrCtx_CONDITION4_ELSE;

	/* スタックポインタの保存 */
	LDR		r0, = tUSB_INT_REG + ?ulSP;	/* tUSB_INT_REG.ulSP = __XSP;	*/
	STR		sp, [r0];

	/* 割り込み処理関数 */
	LDR		r0, = fvUSB_INTR ;		/* fvUSB_INTR = fvUsbIntr;	*/
	STR		r4,[r0];

	/* 次に実行開始するプログラムカウンタの保存 */
	LDR		r1, =LINE_USB_END_LABEL			/* 	__asm( "LD   XWA, USB_END_LABEL" );	*/
	LDR		r0, =tUSB_INT_REG + ?ulPC;	/* 	tUSB_INT_REG.ulPC = __XWA;	*/
	STR		r1, [r0];

	/* コンテキスト保存されているか否かの確認 */
	/* if(tUSB_SAVE_REG.blSavedFlag==false)	*/
	LDR		r0, = tUSB_SAVE_REG + ?blSavedFlag;
	LDRB	r0,[r0,#0];
	CMP		r0,#0;			/* if(tUSB_SAVE_REG.blSavedFlag == false)	*/
	BNE		LINE_vChgIntrCtx_CONDITION5_ELSE;		/* else				*/

	/* スタックポインタの設定	*/
	/* __XSP = (uint32_t)&pulSTACK_AREA[ STACK_ELEMENTS ];	*/
#if 0
	LDR		r0, =__cpp(&pulSTACK_AREA[STACK_ELEMENTS]);
#else
	LDR		r0, =pulSTACK_AREA;
	LDR		r0,[r0,#0];
	ADD		r0,r0,#0x800;
#endif

#if 1
	MOV		sp, r0;
#else
	MOV		r0,sp;
#endif

	/* USB割込み処理の呼び出し */
	LDR		r0, =fvUSB_INTR;
	LDR		r0,[r0,#0];
	BLX		r0;				/* fvUSB_INTR()	*/
	B		LINE_USB_END_LABEL;

LINE_vChgIntrCtx_CONDITION5_ELSE;
	/* 以前に中断したコンテキストの実行 */
	/* __XSP = tUSB_SAVE_REG.ulXSP;		*/
	LDR		r0, = tUSB_SAVE_REG + ?ul_sp;	
	LDR		r0,[r0,#0];
#if 1
//	STR		[r0],sp;
	MOV		sp, r0;
#else
	MOV		r0,sp;
#endif

	/* __XWA = tUSB_SAVE_REG.ulPC;	*/
	LDR		r0, =tUSB_SAVE_REG + ?ul_pc;
	LDR		r0,[r0,#0];
	/* __asm( "JP   XWA" );			*/
#if 1
//	STR		[r0],pc;
//	LDR		pc, [r0];
	BX		r0;
#else
	MOV		r0,pc;
#endif

	/* 終了ジャンプ用フラグ */
LINE_USB_END_LABEL;		/* 	__asm( "USB_END_LABEL:" );	*/

	/* スタックポインタの復帰 */
	LDR		r0, =tUSB_INT_REG + ?ulSP;	/* 	__XSP = tUSB_INT_REG.ulSP;	*/
	LDR		r0,[r0,#0];

#if 1
//	STR		[r0],sp;
//	LDR		sp, [r0];
	MOV		sp, r0;
#else
	MOV		r0,sp;
#endif
	B		LINE_END_PROCEDURE;

  END