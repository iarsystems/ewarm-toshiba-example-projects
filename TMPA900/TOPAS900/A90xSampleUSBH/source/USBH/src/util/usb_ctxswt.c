/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ctxswt.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Host Driver 簡易コンテキストスイッチ (TLCS900)

    ・USB 割り込みが入ったらコンテキストを切り替える
    ・USB 割り込み内で待ちが発生したら、コンテキストを戻して終了
    ・待ち時間が経過したら、タイマ割り込みからコンテキストを切り替え、USB 割り
      込みの続きを行う

*/

#include "usb_ctxswt.h"

#if defined( USB_CTX_SWT )

#include <string.h>
#include "usb_dbg.h"
#include "usb_intr.h"

/* ========== DEFINES ========== */
#define CARM_ASM_CODE_TRUE		1
#define CARM_ASM_CODE_FALSE		0

#if(MMCU_CORE == CTLCS900H1)
#define MARM_ASM_CODE	CARM_ASM_CODE_TRUE
//#define MARM_ASM_CODE	CARM_ASM_CODE_FALSE
#else
#define MARM_ASM_CODE	CARM_ASM_CODE_FALSE
#endif

/* USB 割り込み (多重割り込み含む) 用スタックサイズ */
#define STACK_ELEMENTS   (USB_INTR_STACK_SZ / sizeof(unsigned long))

/* ========== TYPE_DEFS ========== */


/* アプリケーション SP/PC 保存用構造体 */
typedef struct tagIntSaveReg {
	uint32_t  ulSP;
	uint32_t  ulPC;
} typeIntSaveReg ;

#if(MMCU_CORE == CTLCS900H1)
/* USB 割り込みコンテキスト保存用構造体 */
typedef struct tagAllSaveReg {
	bool      blSavedFlag;
	uint32_t  ulXWA;
	uint32_t  ulXBC;
	uint32_t  ulXDE;
	uint32_t  ulXHL;
	uint32_t  ulXIX;
	uint32_t  ulXIY;
	uint32_t  ulXIZ;
	uint32_t  ulXSP;
	uint32_t  ulPC;
} typeAllSaveReg;

#else
/* USB 割り込みコンテキスト保存用構造体 for IRQ	*/
typedef struct tagAllSaveReg {
	bool      blSavedFlag;
	uint32_t  ul_r0;
	uint32_t  ul_r1;
	uint32_t  ul_r2;
	uint32_t  ul_r3;
	uint32_t  ul_r4;
	uint32_t  ul_r5;
	uint32_t  ul_r6;
	uint32_t  ul_r7;
	uint32_t  ul_r8;
	uint32_t  ul_r9;
	uint32_t  ul_r10;
	uint32_t  ul_r11;
	uint32_t  ul_r12;

	uint32_t  ul_sp;	/* r13	*/
	uint32_t  ul_lr;	/* r14	*/
	uint32_t  ul_pc;	/* r15	*/
} typeAllSaveReg;
#endif


/* ========== static variables ========== */

#if(MMCU_CORE == CTLCS900H1)
/* USB 割り込み (多重割り込み含む) 用スタック領域 */
static uint32_t pulSTACK_AREA_BUF[ STACK_ELEMENTS ] ;
static uint32_t* pulSTACK_AREA = pulSTACK_AREA_BUF;
/* USB_INT用 SP/PC 保存領域 */
static typeIntSaveReg  tUSB_INT_REG;
/* USBホストドライバ処理用コンテキスト保存領域 */
static typeAllSaveReg  tUSB_SAVE_REG = { false, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
/* 割り込み処理関数 */
static void (*fvUSB_INTR)( void );
#else
/* USB 割り込み (多重割り込み含む) 用スタック領域 */
uint32_t pulSTACK_AREA_BUF[ STACK_ELEMENTS ] ;
uint32_t* pulSTACK_AREA = pulSTACK_AREA_BUF;
/* USB_INT用 SP/PC 保存領域 */
typeIntSaveReg  tUSB_INT_REG;
/* USBホストドライバ処理用コンテキスト保存領域 */
typeAllSaveReg  tUSB_SAVE_REG = { false,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
/* 割り込み処理関数 */
void (*fvUSB_INTR)( void );
#endif

/* ========== GLOBAL FUNCTIONS ========== */

/* ======================================================================== */
/*
  2006/08/01 追加
  簡易コンテキストスイッチ初期化
*/
/* ------------------------------------------------------------------------ */
void usb_CTXSWT_vInitialize( void )
{
	memset( &tUSB_SAVE_REG, 0, sizeof(typeAllSaveReg) );

#if defined( USB_DEBUG )
	memset( pulSTACK_AREA, 0, STACK_ELEMENTS * sizeof(uint32_t) );
#endif
}
/* ======================================================================== */

/* ======================================================================== */
/*
  2006/08/01 追加
  簡易コンテキストスイッチ終了
*/
/* ------------------------------------------------------------------------ */
void usb_CTXSWT_vFinalize( void )
{
	usb_CTXSWT_vInitialize();
}
/* ======================================================================== */

#if(MMCU_CORE == CTLCS900H1)

/* ======================================================================== */
/*
  USB 割込みコンテキスト切り替え
    USB 割り込み発生時にコンテキストを切り替えて実行する
    タイマ割り込みから、中断した USB 割り込みを復帰する

    引数
      fvUsbIntr 割り込み処理関数
*/
/* ------------------------------------------------------------------------ */
void usb_CTXSWT_vChgIntrCtx( void (*fvUsbIntr)( void ) )
{
	/* エラーチェック */
	if( (fvUsbIntr == NULL && tUSB_SAVE_REG.blSavedFlag == false)
		|| (fvUsbIntr != NULL && tUSB_SAVE_REG.blSavedFlag != false) )
	{
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
		DEBUG_ERROR_CALL( 3, "CTXSWT_vChgIntrCtx", NULL );
#else
	tUSB_INT_REG.ulSP = 0x40;	/* dummy	*/
#endif
		return;
	}

	/* スタックポインタの保存 */
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
	tUSB_INT_REG.ulSP = __XSP;
#else
	tUSB_INT_REG.ulSP = 0x55;	/* dummy	*/
#endif

	/* 割り込み処理関数 */
	fvUSB_INTR = fvUsbIntr;

	/* 次に実行開始するプログラムカウンタの保存 */
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
	__asm( "LD   XWA, USB_END_LABEL" );
	tUSB_INT_REG.ulPC = __XWA;
#else
	tUSB_INT_REG.ulPC = 0xAA;	/* dummy	*/
#endif

	/* コンテキスト保存されているか否かの確認 */
	if( tUSB_SAVE_REG.blSavedFlag == false )
	{
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
		/* スタックポインタの設定 (警告は問題ない) */
		__XSP = (uint32_t)&pulSTACK_AREA[ STACK_ELEMENTS ];
#else
	tUSB_INT_REG.ulPC = 0xA0;	/* dummy	*/
#endif

		/* USB割込み処理の呼び出し */
		fvUSB_INTR();
	}
	else
		/* 以前に中断したコンテキストの実行 */
	{
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
		__XSP = tUSB_SAVE_REG.ulXSP;
		__XWA = tUSB_SAVE_REG.ulPC;
		__asm( "JP   XWA" );
#else
	tUSB_INT_REG.ulPC = 0x50;	/* dummy	*/
#endif
	}

	/* 終了ジャンプ用フラグ */
	__asm( "USB_END_LABEL:" );

	/* スタックポインタの復帰 */
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
	__XSP = tUSB_INT_REG.ulSP;
#else
	tUSB_INT_REG.ulPC = 0x51;	/* dummy	*/
#endif
}
/* ======================================================================== */
#else	/* #if(MMCU_CORE == CTLCS900H1)	*/
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
#if 0
#if(1)
__asm void usb_CTXSWT_vChgIntrCtx( void (*fvUsbIntr)( void ) )
{
	/* save data "fvUsbIntr, lr"	*/
	PUSH		{r4,lr};
	
	/* if((fvUsbIntr==NULL) && (tUSB_SAVE_REG.blSavedFlag==false))	*/
	MOV		r4,r0;					/* get fvUsbIntr				*/
	CMP		r4,#0;					/* if(fvUsbIntr == NULL)		*/
	BNE		LINE_vChgIntrCtx_CONDITION1_ELSE;	/* else				*/

	LDR		r0, =__cpp(&tUSB_SAVE_REG.blSavedFlag);
	LDRB	r0,[r0,#0];
	CMP		r0,#0;					/* if(tUSB_SAVE_REG.blSavedFlag == false)	*/
	BEQ		LINE_vChgIntrCtx_CONDITION2_THEN;	/* then							*/

LINE_vChgIntrCtx_CONDITION1_ELSE;
	/* if((fvUsbIntr != NULL) && (tUSB_SAVE_REG.blSavedFlag != false))	*/
	CMP		r4,#0;							/* if(fvUsbIntr != NULL)	*/
	BEQ		LINE_vChgIntrCtx_CONDITION3_THEN;	/* then					*/

	LDR		r0, =__cpp(&tUSB_SAVE_REG.blSavedFlag);
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
	LDR		r0, =__cpp(&tUSB_INT_REG.ulSP);	/* tUSB_INT_REG.ulSP = __XSP;	*/
	STR		sp, [r0];

	/* 割り込み処理関数 */
	LDR		r0, =__cpp(&fvUSB_INTR);		/* fvUSB_INTR = fvUsbIntr;	*/
	STR		r4,[r0];

	/* 次に実行開始するプログラムカウンタの保存 */
	LDR		r1, =LINE_USB_END_LABEL			/* 	__asm( "LD   XWA, USB_END_LABEL" );	*/
	LDR		r0, =__cpp(&tUSB_INT_REG.ulPC);	/* 	tUSB_INT_REG.ulPC = __XWA;	*/
	STR		r1, [r0];

	/* コンテキスト保存されているか否かの確認 */
	/* if(tUSB_SAVE_REG.blSavedFlag==false)	*/
	LDR		r0, =__cpp(&tUSB_SAVE_REG.blSavedFlag);
	LDRB	r0,[r0,#0];
	CMP		r0,#0;			/* if(tUSB_SAVE_REG.blSavedFlag == false)	*/
	BNE		LINE_vChgIntrCtx_CONDITION5_ELSE;		/* else				*/

	/* スタックポインタの設定	*/
	/* __XSP = (uint32_t)&pulSTACK_AREA[ STACK_ELEMENTS ];	*/
#if(0)
	LDR		r0, =__cpp(&pulSTACK_AREA[STACK_ELEMENTS]);
#else
	LDR		r0, =__cpp(&pulSTACK_AREA);
	LDR		r0,[r0,#0];
	ADD		r0,r0,#0x800;
#endif
#if(1)
	MOV		sp, r0;
#else
	MOV		r0,sp;
#endif

	/* USB割込み処理の呼び出し */
	LDR		r0, =__cpp(&fvUSB_INTR);
	LDR		r0,[r0,#0];
	BLX		r0;				/* fvUSB_INTR()	*/
	B		LINE_USB_END_LABEL;

LINE_vChgIntrCtx_CONDITION5_ELSE;
	/* 以前に中断したコンテキストの実行 */
	/* __XSP = tUSB_SAVE_REG.ulXSP;		*/
	LDR		r0, =__cpp(&tUSB_SAVE_REG.ul_sp);	
	LDR		r0,[r0,#0];
#if(1)
//	STR		[r0],sp;
	MOV		sp, r0;
#else
	MOV		r0,sp;
#endif

	/* __XWA = tUSB_SAVE_REG.ulPC;	*/
	LDR		r0, =__cpp(&tUSB_SAVE_REG.ul_pc);
	LDR		r0,[r0,#0];
	/* __asm( "JP   XWA" );			*/
#if(1)
//	STR		[r0],pc;
//	LDR		pc, [r0];
	BX		r0;
#else
	MOV		r0,pc;
#endif

	/* 終了ジャンプ用フラグ */
LINE_USB_END_LABEL;		/* 	__asm( "USB_END_LABEL:" );	*/

	/* スタックポインタの復帰 */
	LDR		r0, =__cpp(&tUSB_INT_REG.ulSP);	/* 	__XSP = tUSB_INT_REG.ulSP;	*/
	LDR		r0,[r0,#0];
#if(1)
//	STR		[r0],sp;
//	LDR		sp, [r0];
	MOV		sp, r0;
#else
	MOV		r0,sp;
#endif
	B		LINE_END_PROCEDURE;

}
#else
void usb_CTXSWT_vChgIntrCtx( void (*fvUsbIntr)( void ) )
{
	fvUSB_INTR();
}
#endif
#endif

/* ======================================================================== */
#endif	/* #if(MMCU_CORE == CTLCS900H1)	*/

#if(MMCU_CORE == CTLCS900H1)
/* ======================================================================== */
/*
  復帰されるまで、割り込み処理を中断する
*/
/* ------------------------------------------------------------------------ */
void usb_CTXSWT_vSlpIntrCtx( void )
{
	/* すでにコンテキスト保存済み */
	if( tUSB_SAVE_REG.blSavedFlag != false )
	{
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
		DEBUG_ERROR_CALL( 3, "CTXSWT_vSlpIntrCtx", NULL );
#else
		tUSB_SAVE_REG.blSavedFlag = false;	/* dummy	*/
#endif
		return;
	}

	/* 割り込み禁止
     待ちの最中に USB 割り込みが入ると、順序関係が狂う */
	USB_DIS_INTR();

	/* コンテキスト保存フラグを ON */
	tUSB_SAVE_REG.blSavedFlag = true;

	/* 全レジスタを保存 */
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
	tUSB_SAVE_REG.ulXWA = __XWA;
	tUSB_SAVE_REG.ulXBC = __XBC;
	tUSB_SAVE_REG.ulXDE = __XDE;
	tUSB_SAVE_REG.ulXHL = __XHL;
	tUSB_SAVE_REG.ulXIX = __XIX;
	tUSB_SAVE_REG.ulXIY = __XIY;
	tUSB_SAVE_REG.ulXIZ = __XIZ;
	tUSB_SAVE_REG.ulXSP = __XSP;
	__asm( "LD   XWA, USB_START_LABEL" );
	tUSB_SAVE_REG.ulPC = __XWA;

	/* 呼び出し元コンテキストに復帰する */
	__XSP = tUSB_INT_REG.ulSP;
	__XWA = tUSB_INT_REG.ulPC;
	__asm( "JP   XWA" );
#else
	tUSB_SAVE_REG.ulXWA = 0x11;		/* dummy	*/
	tUSB_SAVE_REG.ulXBC = 0x12;		/* dummy	*/
	tUSB_SAVE_REG.ulXDE = 0x13;		/* dummy	*/
	tUSB_SAVE_REG.ulXHL = 0x14;		/* dummy	*/
	tUSB_SAVE_REG.ulXIX = 0x15;		/* dummy	*/
	tUSB_SAVE_REG.ulXIY = 0x16;		/* dummy	*/
	tUSB_SAVE_REG.ulXIZ = 0x17;		/* dummy	*/
	tUSB_SAVE_REG.ulXSP = 0x18;		/* dummy	*/
#endif

	/* ---------- ここに待ちが入る ---------- */

	/* 次の割込みが入ったときに処理を開始するラベル */
	__asm( "USB_START_LABEL:" ) ;

#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
	/* 全レジスタを復帰 */
	__XWA = tUSB_SAVE_REG.ulXWA;
	__XBC = tUSB_SAVE_REG.ulXBC;
	__XDE = tUSB_SAVE_REG.ulXDE;
	__XHL = tUSB_SAVE_REG.ulXHL;
	__XIX = tUSB_SAVE_REG.ulXIX;
	__XIY = tUSB_SAVE_REG.ulXIY;
	__XIZ = tUSB_SAVE_REG.ulXIZ;
	__XSP = tUSB_SAVE_REG.ulXSP;
#else
	tUSB_INT_REG.ulPC = tUSB_SAVE_REG.ulXWA;	/* dummy	*/
#endif

	/* コンテキスト保存フラグをクリアする */
	tUSB_SAVE_REG.blSavedFlag = false;

	/* 割り込み許可 */
	USB_ENA_INTR();

	/* 呼び出し元へ戻る */
}
/* ======================================================================== */
#else	/* #if(MMCU_CORE == CTLCS900H1)	*/
/* ======================================================================== */
/*
  復帰されるまで、割り込み処理を中断する
  main <=> interrupt
*/
/* ------------------------------------------------------------------------ */
#if 0
#if(1)
__asm void usb_CTXSWT_vSlpIntrCtx( void )
{
	PRESERVE8

	PUSH		{r4,lr}

	/* すでにコンテキスト保存済み */
	LDR		r0, =__cpp(&tUSB_SAVE_REG.blSavedFlag);
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
	IMPORT	usb_INTR_vDisable;
	BLX		usb_INTR_vDisable;

	/* コンテキスト保存フラグを ON 			*/
	/* tUSB_SAVE_REG.blSavedFlag = true;	*/
	MOV		r0,#1		/* get true	*/
	LDR		r1, =__cpp(&tUSB_SAVE_REG.blSavedFlag);
	STRB	r0,[r1,#0];

	/* 全レジスタを保存 */
	LDR		r0, =__cpp(&tUSB_SAVE_REG.ul_r0);
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
	LDR		r0, =__cpp(&tUSB_INT_REG.ulSP);
	LDR		r0,[r0,#0];
#if(1)
	MOV		sp, r0;
#else
	MOV		r0,sp;
#endif
	LDR		r0, =__cpp(&tUSB_INT_REG.ulPC);
	LDR		r0,[r0,#0];
//	MOV		r0,pc;					/* jump pc?	*/
	BX		r0;

LINE_USB_START_LABEL;
	/* 全レジスタを復帰 */
	LDR		r0, =__cpp(&tUSB_SAVE_REG.ul_r0);
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
	LDR		r1, =__cpp(&tUSB_SAVE_REG.blSavedFlag);
	STRB	r0,[r1,#0];

	/* 割り込み許可 */
	IMPORT	usb_INTR_vEnable;
	BLX		usb_INTR_vEnable
	/* 呼び出し元へ戻る */
	B		LINE_vSlpIntrCtx_END_PROCEDURE;
}
#else
void usb_CTXSWT_vSlpIntrCtx( void )
{
	USB_ENA_INTR();
}

#endif
#endif

/* ======================================================================== */
#endif	/* #if(MMCU_CORE == CTLCS900H1)	*/

#if(MMCU_CORE == CTLCS900H1)

/* ======================================================================== */
/*
  現在のコンテキストが割り込みか否かを調べる
*/
/* ------------------------------------------------------------------------ */
bool usb_CTXSWT_blIntrCtx( void )
{
  /* 使用スタックをチェック (警告は問題ない) */
#if(MARM_ASM_CODE == CARM_ASM_CODE_FALSE)
  if( (uint32_t)pulSTACK_AREA < __XSP && __XSP <= (uint32_t)&pulSTACK_AREA[STACK_ELEMENTS] )
#else
  if( (uint32_t)pulSTACK_AREA < tUSB_INT_REG.ulSP &&
	  tUSB_INT_REG.ulSP <= (uint32_t)&pulSTACK_AREA[STACK_ELEMENTS] )	/* dummy	*/
#endif
    {
      return( true );
    }

  return( false );
}
/* ======================================================================== */
#else	/* #if(MMCU_CORE == CTLCS900H1)	*/

/* ======================================================================== */
/*
  現在のコンテキストが割り込みか否かを調べる
*/
/* ------------------------------------------------------------------------ */
#if 0
#if(1)		
__asm bool usb_CTXSWT_blIntrCtx( void )
{
	 	
	/* 使用スタックをチェック (警告は問題ない) */
	/* if((uint32_t)pulSTACK_AREA < __XSP)	*/
#if(1)	/* 2009/05/27 武安 */

	LDR		r1,=__cpp(&pulSTACK_AREA);		
#else
	LDR		r1,__cpp(&pulSTACK_AREA);
#endif
	LDR		r1,[r1,#0];
	CMP		sp,r1;
	BLS		LINE_blIntrCtx_CONDITION1_ELSE;	/* else	*/
	/* if(__XSP <= (uint32_t)&pulSTACK_AREA[STACK_ELEMENTS])	*/
#if(1)	/* 2009/05/27 武安 */
	LDR		r1,=__cpp(&pulSTACK_AREA);
#else
	LDR		r1,__cpp(&pulSTACK_AREA);
#endif
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
}
#else
__asm bool usb_CTXSWT_blIntrCtx( void )
{
	MRS	r1, CPSR;
	AND r1,#0x0000001F;
	CMP r1,#0x0000001F;
	BEQ LINE_RETURN_TRUE;
	MOV		r0,#1;
	B	LINE_RETURN;

LINE_RETURN_TRUE;
	MOV		r0,#0;
LINE_RETURN;
	BX		lr;
}
#endif
#endif
/* ======================================================================== */
#endif	/* #if(MMCU_CORE == CTLCS900H1)	*/


#else	/*#if defined( USB_CTX_SWT )	*/
/* コンパイルエラー対策 */
static void vDummy( void ) {}
#endif	/*#if defined( USB_CTX_SWT )	*/

/* --- End of File --- */

