/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_intr_old.c 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB 割り込み管理

*/

#include  <stdlib.h>
#include "usb_ctxswt.h"
#include "usb_dbg.h"
#include "usb_ohcitypes.h"
#include "usb_ohcireg.h"
#include "usb_intr_hw.h"
#include "tmpa900cm.h"

#if(MMCU_CORE == CTLCS900H1)
#else
# include "system_def.h"
#endif


extern OHCI_typeOhci usb_OHCI_tOHCI;

//#if(MMCU_CORE == CTLCS900H1)
//# error
//#else

//lwi __inline static void enable_IRQ(void);
void enable_IRQ(void);
//lwi __inline static void disable_IRQ(void);
void disable_IRQ(void);
void enable_IRQ(void)
{
#if(0)
	int tmp;
	__asm {
		MRS tmp, CPSR;
		BIC tmp, tmp, #0x80;
		MSR CPSR_c, tmp;
	}
#else

	VICINTENABLE = reg_VICINTENABLE_Buffer;
#endif
}




#define __EI()	enable_IRQ()
#define __DI()	disable_IRQ()
// #endif



/* ========== DEFINES & EXTERNS ========== */


/* ========== global variables ========== */
static int16_t iUSB_INTR = 0;
static int16_t iTIMER_INTR = 0;
static uint32_t reg_VICINTENABLE_Buffer;

/* ========== GLOBAL FUNCTIONS ========== */
/* USB 割り込み初期化 */
void usb_INTR_vInitialize( void )
{
	iUSB_INTR = 0;
	usb_INTR_vSetInterruptLevel();
}


/*
  USB 割り込み終了
    2006/08/02 追加
*/
void usb_INTR_vFinalize( void )
{
	iUSB_INTR = 0;
	usb_INTR_vClearInterruptLevel();
}


/*
  USB 割り込み許可処理
*/
static void usb_INTR_vEnableFunction( void )
{
	iUSB_INTR++;
#if defined( USB_DEBUG ) // test
# if(0)
	if( iUSB_INTR > 0 || (INTEUSB & 0x01) != 0x00 )
	{
		DEBUG_ERROR_CALL( 3, "Interrupt Enable", NULL );
	}
# endif
#endif
	if( iUSB_INTR == 0 )
	{
		OHCI_WRITE( OHCI_INTERRUPT_DISABLE, OHCI_INTR_MIE );
		usb_INTR_vSetInterruptLevel();
		OHCI_WRITE( OHCI_INTERRUPT_ENABLE, OHCI_INTR_MIE );
	}
}

/*
  USB 割り込み禁止処理
*/
static void usb_INTR_vDisableFunction( void )
{
#if defined( USB_DEBUG ) // test
# if(0)
	if( iUSB_INTR >= 0 && (INTEUSB & 0x01) != 0x01 )
	{
		DEBUG_ERROR_CALL( 3, "Interrupt Disable", NULL );
	}
# endif
#endif
	usb_INTR_vClearInterruptLevel();
	iUSB_INTR--;
}

/*
  割り込み許可呼び出し口
    2006/10/20 追加
    アプリケーションスタックからの呼び出し時には DI/EI で割り込みを禁止する
*/
void usb_INTR_vEnable( void )
{
	bool blIntr;

#if defined( USB_CTX_SWT )
	blIntr = usb_CTXSWT_blIntrCtx();
#else
	blIntr = false;
#endif
	
	if( blIntr == false )
	{
		__DI();
	}

	usb_INTR_vEnableFunction();

	if( blIntr == false )
	{
		__EI();
	}
}


/*
  割り込み禁止呼び出し口
    2006/10/20 追加
    アプリケーションスタックからの呼び出し時には DI/EI で割り込みを禁止する
*/
void usb_INTR_vDisable( void )
{
	bool blIntr;

#if defined( USB_CTX_SWT )
	blIntr = usb_CTXSWT_blIntrCtx();
#else
	blIntr = false;
#endif

	if( blIntr == false )
	{
		__DI();
	}

	usb_INTR_vDisableFunction();

	if( blIntr == false )
	{
		__EI();
	}
}


/*
  USB 割り込み禁止状態か否か
*/
bool usb_INTR_blDisable( void )
{
	/* 2006/05/24 修正 田谷  '>' -> '<' */
	return( (iUSB_INTR < 0) ? true : false );
}


/* --- TIMER Interrupt --- */
/*
  タイマ割り込み開始
*/
void usb_TIMER_vStartIntr(void )
{
	iTIMER_INTR = 0;
	usb_TIMER_vSetTimerInit();
}

/* タイマ割り込み終了 */
void usb_TIMER_vEndIntr( void )
{
	usb_TIMER_vStopTimer();
}

/* タイマ割り込み禁止処理 */
static void usb_TIMER_vDisIntrFunction( void )
{
	usb_TIMER_vStopTimer();
	iTIMER_INTR--;
}

/* タイマ割り込み許可処理 */
static void usb_TIMER_vEnaIntrFunction( void )
{
	iTIMER_INTR++;
	if( iTIMER_INTR == 0 )
	{
		/* タイマカウント開始  INTTA3 START */
		usb_TIMER_vStartTimer();           // INTTA3 START
	}
}


/*
  タイマ割り込み禁止呼び出し口
    2006/10/20 追加
    アプリケーションスタックからの呼び出し時には DI/EI で割り込みを禁止する
*/
void usb_TIMER_vDisIntr( void )
{
	bool blIntr;

#if defined( USB_CTX_SWT )
	blIntr = usb_CTXSWT_blIntrCtx();
#else
	blIntr = false;
#endif

	if( blIntr == false )
	{
		__DI();
	}

	usb_TIMER_vDisIntrFunction();

	if( blIntr == false )
	{
		__EI();
	}
}


/*
  タイマ割り込み許可呼び出し口
    2006/10/20 追加
    アプリケーションスタックからの呼び出し時には DI/EI で割り込みを禁止する
*/
void usb_TIMER_vEnaIntr( void )
{
	bool blIntr;

#if defined( USB_CTX_SWT )
	blIntr = usb_CTXSWT_blIntrCtx();
#else
	blIntr = false;
#endif

	if( blIntr == false )
	{
		__DI();
	}

	usb_TIMER_vEnaIntrFunction();

	if( blIntr == false )
	{
		__EI();
	}
}


/*
  USB/タイマ割り込み同時許可
    2006/10/20 追加
    アプリケーションスタックからの呼び出し時には DI/EI で割り込みを禁止する
*/
void usb_vEnableAllIntr( void )
{
	bool blIntr;

#if defined( USB_CTX_SWT )
	blIntr = usb_CTXSWT_blIntrCtx();
#else
	blIntr = false;
#endif

	if( blIntr == false )
	{
		__DI();
	}

	usb_TIMER_vEnaIntrFunction();
	usb_INTR_vEnableFunction() ;

	if( blIntr == false )
	{
		__EI();
	}
}


/*
  USB/タイマ割り込み同時禁止
    2006/10/20 追加
    アプリケーションスタックからの呼び出し時には DI/EI で割り込みを禁止する
*/
void usb_vDisableAllIntr( void )
{
	bool blIntr;

#if defined( USB_CTX_SWT )
	blIntr = usb_CTXSWT_blIntrCtx();
#else
	blIntr = false;
#endif

	if( blIntr == false )
	{
		__DI();
	}

	usb_INTR_vDisableFunction() ;
	usb_TIMER_vDisIntrFunction() ;

	if( blIntr == false )
	{
		__EI();
	}
}


#if(MMCU_CORE == CTLCS900H1)
#else
/* ======================================================================== */
/*
	Enable IRQ Function
	Don't use user mode
*/
/* ------------------------------------------------------------------------ */
//__inline static void enable_IRQ(void)
void enable_IRQ(void)
{
#if(0)
	int tmp;
	__asm {
		MRS tmp, CPSR;
		BIC tmp, tmp, #0x80;
		MSR CPSR_c, tmp;
	}
#else

	VICINTENABLE = reg_VICINTENABLE_Buffer;
#endif
}
/* ======================================================================== */

/* ======================================================================== */
/*
	Disable IRQ Function
	Don't use user mode
*/
/* ------------------------------------------------------------------------ */
__inline static void disable_IRQ(void)
//void disable_IRQ(void)

{
#if(0)
	int tmp;
	__asm {
		MRS tmp, CPSR;
		ORR tmp, tmp, #0x80;
		MSR CPSR_c, tmp;
	}
#else
	uint32_t reg_VICINTSELECT_buf;

	reg_VICINTSELECT_buf = VICINTSELECT;
	reg_VICINTENABLE_Buffer = VICINTENABLE;
	VICINTENABLE = reg_VICINTSELECT_buf;
#endif
}
/* ======================================================================== */
#endif

/* --- End of File --- */
