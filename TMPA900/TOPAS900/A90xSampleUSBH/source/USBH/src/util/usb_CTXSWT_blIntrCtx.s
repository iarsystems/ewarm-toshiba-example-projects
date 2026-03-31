/* ======================================================================== */
/*
  現在のコンテキストが割り込みか否かを調べる
*/
/* ------------------------------------------------------------------------ */
 PUBLIC  usb_CTXSWT_blIntrCtx

  IMPORT  pulSTACK_AREA

?blSavedFlag  DEFINE    0
?ul_r0        DEFINE    4
?ul_sp        DEFINE    56
?ul_pc        DEFINE    64

?ulSP         DEFINE    0
?ulPC         DEFINE    4

    SECTION .text:CODE:NOROOT(2)
    ARM

usb_CTXSWT_blIntrCtx:
	 	
	/* 使用スタックをチェック (警告は問題ない) */
	/* if((uint32_t)pulSTACK_AREA < __XSP)	*/

  LDR		r1,=pulSTACK_AREA;		
  LDR		r1,[r1,#0];
	CMP		sp,r1;
	BLS		LINE_blIntrCtx_CONDITION1_ELSE;	/* else	*/
	/* if(__XSP <= (uint32_t)&pulSTACK_AREA[STACK_ELEMENTS])	*/
	LDR		r1,=pulSTACK_AREA;
	LDR		r1,[r1,#0];
//	ADD		r1,r1,#0x400;		/* &pulSTACK_AREA[STACK_ELEMENTS]	*/
	ADD		r1,r1,#0x800;		/* &pulSTACK_AREA[STACK_ELEMENTS]	*/
	CMP		sp,r1;
	BHI		LINE_blIntrCtx_CONDITION2_ELSE;	/* else	*/

	MOV		r0,#1;
LINE_blIntrCtx_END_PROCEDURE;
	BX		lr;

LINE_blIntrCtx_CONDITION1_ELSE;
LINE_blIntrCtx_CONDITION2_ELSE;
	/* return( false );	*/
	MOV		r0,#0;
	B		LINE_blIntrCtx_END_PROCEDURE;

  END
