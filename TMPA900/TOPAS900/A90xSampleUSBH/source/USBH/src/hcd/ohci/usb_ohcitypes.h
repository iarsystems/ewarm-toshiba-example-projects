/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohcitypes.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI 構造体定義

*/

#ifndef USB_OHCI_TYPEDEF_H
#define USB_OHCI_TYPEDEF_H

#include "usb_ohciconfig.h"
#include "usb_types.h"
#include "usb_trace.h"
#include "usb_usbd_var.h"

/* ========== DEFINES ========== */

#define OHCI_OK 0
#define OHCI_NG (-1)

#define OHCI_NUM_INTRS      32  /* HCCA 上の割り込みED数 */
#define OHCI_NUM_INTR_NODES 63  /* Interrupt Tree のノード数 */

/* --- ED --- */
/* D */
#define OHCI_ED_DIR_TD      0   /* TD 準拠 */
#define OHCI_ED_DIR_OUT     1   /* 出力 */
#define OHCI_ED_DIR_IN      2   /* 入力 */
/* S */
#define OHCI_ED_SPEED     1   /* Low Speed */
/* F */
#define OHCI_ED_FORMAT_GEN    0   /* 汎用 TD */
#define OHCI_ED_FORMAT_ISO    1   /* Isochronous 専用 TD */
/* TailP */
#define OHCI_ED_TAILP_MASK    0xfffffff0UL
/* HeadP */
#define OHCI_ED_HEADP_MASK    0xfffffff0UL
/* NextED */
#define OHCI_ED_NEXTED_MASK   0xfffffff0UL


/* --- TD --- */

/* DP */
#define OHCI_TD_DIR_SETUP   0   /* セットアップ */
#define OHCI_TD_DIR_OUT     1   /* 出力 */
#define OHCI_TD_DIR_IN      2   /* 入力 */
/* DI */
#define OHCI_TD_NOINTR      7
/* T */
#define OHCI_TD_TOGGLE_CARRY  0
#define OHCI_TD_TOGGLE_0    2
#define OHCI_TD_TOGGLE_1    3
/* CC */
#define OHCI_TD_NOCC      0xf
/* NextTD */
#define OHCI_TD_NEXTTD_MASK   0xfffffff0UL

/* Condition Code */
#define OHCI_CC_NO_ERROR        0
#define OHCI_CC_CRC           1
#define OHCI_CC_BIT_STUFFING      2
#define OHCI_CC_DATA_TOGGLE_MISMATCH  3
#define OHCI_CC_STALL         4
#define OHCI_CC_DEVICE_NOT_RESPONDING 5
#define OHCI_CC_PID_CHECK_FAILURE   6
#define OHCI_CC_UNEXPECTED_PID      7
#define OHCI_CC_DATA_OVERRUN      8
#define OHCI_CC_DATA_UNDERRUN     9
#define OHCI_CC_BUFFER_OVERRUN       12
#define OHCI_CC_BUFFER_UNDERRUN      13
#define OHCI_CC_NOT_ACCESSED       15

/* TD Flags */
#define OHCI_CALL_DONE  0x0001
#define OHCI_ADD_LEN    0x0002
#define OHCI_TD_DELETE  0x0004

/* Done Head */
#define OHCI_DONE_INTRS 1

/* Interrupt エンドポイント (usb_endpoint_descriptor_t.bEndpointAddress) */
#define OHCI_INTR_ENDPT 1

/* ========== TYPE_DEFS ========== */

/* ----- OHCI 仕様準拠 ----- */

/* Host Controller Communicate Area  256[Byte] */
typedef struct OHCI_tagHcca {
	uint32_t  pulInterruptTable[OHCI_NUM_INTRS];    /* 割り込み ED テーブル(32) */
	uint16_t  usFrameNumber;
	uint16_t  Pad1;
	uint32_t  ulDoneHead;
	uint32_t  Reserved[30];
} OHCI_typeHcca;


/* エンドポイントディスクリプタ  16[Byte] */
typedef union OHCI_tagEndpointDescriptor {
	struct {
		/* Dword0 */
#if(0)
		uint32_t  Reserved0 :5;
		uint32_t  MPS     :11;  /* Maximum Packet Size */
		uint32_t  F     :1;   /* Format */
		uint32_t  K     :1;   /* sKip */
		uint32_t  S     :1;   /* Speed */
		uint32_t  D     :2;   /* Direction */
		uint32_t  EN      :4;   /* Endpoint Number */
		uint32_t  FA      :7;   /* Function Address */
#else
		uint32_t  FA      :7;   /* Function Address */
		uint32_t  EN      :4;   /* Endpoint Number */
		uint32_t  D     :2;   /* Direction */
		uint32_t  S     :1;   /* Speed */
		uint32_t  K     :1;   /* sKip */
		uint32_t  F     :1;   /* Format */
		uint32_t  MPS     :11;  /* Maximum Packet Size */
		uint32_t  Reserved0 :5;
#endif
		/* Dword1 */
#if(0)
		uint32_t  TailP1    :16;
		uint32_t  TailP2    :12;
		uint32_t  Reserved1 :4;
#else
		uint32_t  Reserved1 :4;
		uint32_t  TailP2    :12;
		uint32_t  TailP1    :16;
#endif
		/* Dword2 */
#if(0)
		uint32_t  HeadP1    :16;
		uint32_t  HeadP2    :12;
		uint32_t  Reserved2 :2;
		uint32_t  C     :1;   /* toggle Carry  */
		uint32_t  H     :1;   /* Halted */
#else
		uint32_t  H     :1;   /* Halted */
		uint32_t  C     :1;   /* toggle Carry  */
		uint32_t  Reserved2 :2;
		uint32_t  HeadP2    :12;
		uint32_t  HeadP1    :16;
#endif
		/* Dword3 */
#if(0)
		uint32_t  NextED1    :16;
		uint32_t  NextED2    :12;
		uint32_t  Reserved3 :4;
#else
		uint32_t  Reserved3 :4;
		uint32_t  NextED2    :12;
		uint32_t  NextED1    :16;
#endif
	} bit;
	struct {
		uint32_t  ulFlags;
		uint32_t  ulTailP;      /* TD queue Tail Pointer */
		uint32_t  ulHeadP;      /* TD queue Head Pointer */
		uint32_t  ulNextED;     /* Next ED */
	} dw;
} OHCI_typeEd, ohci_ed_t;


/* 転送ディスクリプタ  16[Byte] */
typedef union OHCI_tagTransportDescriptor {
	struct {
		/* Dword0 */
#if(0)
		uint32_t  CC      :4;   /* Codition Code */
		uint32_t  EC      :2;   /* Error Count */
		uint32_t  T     :2;   /* data Toggle */
		uint32_t  DI      :3;   /* Delay Interrupt */
		uint32_t  DP      :2;   /* Direction / PID */
		uint32_t  R     :1;   /* buffer Rounding */
		uint32_t  Reserved2 :2;
		uint32_t  Reserved0 :16;
#else
		uint32_t  Reserved0 :16;
		uint32_t  Reserved2 :2;
		uint32_t  R     :1;   /* buffer Rounding */
		uint32_t  DP      :2;   /* Direction / PID */
		uint32_t  DI      :3;   /* Delay Interrupt */
		uint32_t  T     :2;   /* data Toggle */
		uint32_t  EC      :2;   /* Error Count */
		uint32_t  CC      :4;   /* Codition Code */
#endif
		/* Dword1 */
		uint32_t  CBP;        /* Current Buffer Pointer */
		/* Dword2 */
#if(0)
		uint32_t  NextTD1   :16;
		uint32_t  NextTD2   :12;
		uint32_t  Reserved1 :4;
#else
		uint32_t  Reserved1 :4;
		uint32_t  NextTD2   :12;
		uint32_t  NextTD1   :16;
#endif
		/* Dword3 */
		uint32_t  BE;         /* Buffer End */
	} bit;
	struct {
		uint32_t  ulFlags;
		uint32_t  ulCurBufPnt;    /* Current Buffer Pointer */
		uint32_t  ulNextTD;     /* Next TD */
		uint32_t  ulBufEnd;     /* Buffer End */
	} dw;
} OHCI_typeTd, ohci_td_t;


/* ----- 独自定義 ----- */

struct OHCI_tagPipe;

/* エンドポイントディスクリプタ管理用構造体 8(12)[Byte] */
typedef struct OHCI_tagSoftEd {
	OHCI_typeEd*        ptEd;
#if defined( USB_OHCI_FORMAL_INTR )
	struct OHCI_tagPipe*      ptOPipe;
#endif
	struct OHCI_tagSoftEd*    next;
} OHCI_typeSoftEd, ohci_soft_ed_t;


/* 転送ディスクリプタ管理用構造体  28[Byte] */
typedef struct OHCI_tagSoftTd {
	OHCI_typeTd*        ptTd;
	usbd_xfer_t*        ptXfer;
	uint16_t          usLen;    /* length of link list? */
	uint16_t          usFlags;    /* done, ... */
	struct OHCI_tagSoftTd*    nexttd;   /* mirrors NextTD in TD */
	struct OHCI_tagSoftTd*    dnext;    /* next in done list */
	struct {
		struct OHCI_tagSoftTd*  le_next;  /* next element */
		struct OHCI_tagSoftTd** le_prev;  /* addr of previous next element */
	} hnext;
} OHCI_typeSoftTd, ohci_soft_td_t;


/* OHCI 用パイプ管理構造体  usbd_pipe_t+8(+2)[Byte] */
typedef struct OHCI_tagPipe {
	usbd_pipe_t     tPipe;
	OHCI_typeSoftEd*  ptSed;
	OHCI_typeSoftTd*  ptStdTail;
#if defined( USB_OHCI_FORMAL_INTR )
	union {  /* 保存情報 */
		struct {
			uint8_t ucSlots;
			uint8_t ucPos;
		} tIntr;
	} u;
#endif
} OHCI_typePipe, ohci_pipe_t;


/* OHCI 用転送管理構造体  usbd_xfer_t+8[Byte] */
typedef struct OHCI_tagXfer {
	usbd_xfer_t       tXfer;
	uint32_t        ulIdTimer;  /* タイマハンドラ ID */
	OHCI_typeSoftTd*  ptStdHead;  /* 先頭TD */
} OHCI_typeXfer, ohci_xfer_t;


/* ホストコントローラ管理用構造体  35(347)[Byte] */
typedef struct OHCI_tagSoftC {
	OHCI_typeHcca*    ptHcca;         /* Host Controller Communication Area */
	OHCI_typeSoftEd*  ptSedCtrlHead;  /* Control List Header */
	OHCI_typeSoftEd*  ptSedBulkHead;  /* Bulk List Header */
	OHCI_typeXfer*    ptXferIntr;     /* ルートハブ割り込み転送 */
#if defined( USB_OHCI_FORMAL_INTR )  /* 割り込みエンドポイント */
	OHCI_typeSoftEd*  pptSedIntr[OHCI_NUM_INTR_NODES]; /* 正式版 */
	uint16_t          pusBwidthIntr[OHCI_NUM_INTRS];  /* 各経路の使用帯域 */
#else
	OHCI_typeSoftEd*  ptSedIntr;      /* 簡易版 */
#endif
	OHCI_typeSoftTd*  ptStdHashFirst; /* Dummy Hash Table */
	OHCI_typeSoftTd*  ptStdDoneHead;  /* Done List Header */
	OHCI_typeSoftTd*  ptStdDelayDoneHead; /* Delay Done List Header */
	uint32_t          ulEnaIntrs;     /* 割り込み許可マスク */
	uint8_t           ucNdp;          /* Number DownStream Ports */
	uint8_t           ucDevAddr;      /* ルートハブ用 device address */
	uint8_t           ucDevCfg;       /* ルートハブ用 device configuration */
} OHCI_typeOhci, ohci_softc_t;

#endif
