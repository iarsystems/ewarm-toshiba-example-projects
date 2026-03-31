/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohcireg.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI Registers

*/

#ifndef USB_OHCI_REGISTERS_DEFINE_H
#define USB_OHCI_REGISTERS_DEFINE_H

#include "usb_ohciconfig.h"

/* ベースアドレス */
#if(0)	/* 92Fx28 */
# define OHCI_BASEADDR			0x00001C00UL
#else	/* A90x	*/
# define OHCI_BASEADDR			0xF4500000UL
#endif

/* レジスタ読み書き */
#define OHCI_READ( reg )		*(volatile uint32_t*)( OHCI_BASEADDR + reg )
#define OHCI_WRITE( reg, para ) { *(volatile uint32_t*)( OHCI_BASEADDR + reg ) = (para); }



/* OHCI レジスタ */ 
#define OHCI_REVISION			0x00				/* OHCI Revision */
#define OHCI_CONTROL			0x04				/* HC コントロール */
#define OHCI_COMMAND_STATUS		0x08				/* HC ステータス */
#define OHCI_INTERRUPT_STATUS	0x0c				/* 割り込み原因 */
#define OHCI_INTERRUPT_ENABLE	0x10				/* 割り込み許可 */
#define OHCI_INTERRUPT_DISABLE	0x14				/* 割り込み禁止 */
#define OHCI_HCCA				0x18				/* HCCA 物理アドレス */
#define OHCI_PERIDOD_CURRENT_ED 0x1c				/* 実行中周期ED 物理アドレス */
#define OHCI_CONTROL_HEAD_ED	0x20				/* コントロールED(EP0)リスト先頭物理アドレス */
#define OHCI_CONTROL_CURRENT_ED 0x24				/* 実行中コントロールED 物理アドレス */
#define OHCI_BULK_HEAD_ED		0x28				/* バルクEDリスト先頭物理アドレス */
#define OHCI_BULK_CURRENT_ED	0x2c				/* 実行中バルクED 物理アドレス */
#define OHCI_DONE_HEAD			0x30				/* 転送済みTDリスト先頭物理アドレス */
#define OHCI_FM_INTERVAL		0x34				/* フレーム間隔 */
#define OHCI_FM_REMAINING		0x38				/* 次フレームまでの残り時間 */
#define OHCI_FM_NUMBER			0x3c				/* 実行フレーム数の累計 */
#define OHCI_PERIODIC_START		0x40				/* 1フレームにおける周期EDの割合 */
#define OHCI_LS_THRESHOLD		0x44				/* LowSpeed の閾値 */
#define OHCI_RH_DESCRIPTOR_A	0x48				/* ルートハブディスクリプタ前半部 */
#define OHCI_RH_DESCRIPTOR_B	0x4c				/* ルートハブディスクリプタ後半部 */
#define OHCI_RH_STATUS			0x50				/* ルートハブ状態 */
#define OHCI_RH_PORT_STATUS(n)	(0x50 + (n) * 4)	/* ルートハブポート状態 */



/* OHCI レジスタ パラメータ */ 

/* HcRevision */
#define OHCI_CORRECT_REVISION 0x10

/* HcControl */
#define OHCI_CTRL_CBSR_1_1			0x00000000L		/* Control/Bulk Service Ratio */
#define OHCI_CTRL_CBSR_1_2			0x00000001L
#define OHCI_CTRL_CBSR_1_3			0x00000002L
#define OHCI_CTRL_CBSR_1_4			0x00000003L
#define OHCI_CTRL_CBSR_MASK			0x00000003L
#define OHCI_CTRL_PLE				0x00000004L		/* Periodic List Enable */
#define OHCI_CTRL_IE				0x00000008L		/* Isochronous Enable */
#define OHCI_CTRL_CLE				0x00000010L		/* Control List Enable */
#define OHCI_CTRL_BLE				0x00000020L		/* Bulk List Enable */
#define OHCI_CTRL_HCFS_RESET		0x00000000L		/* Host Controller Functional State */
#define OHCI_CTRL_HCFS_RESUME		0x00000040L
#define OHCI_CTRL_HCFS_OPERATIONAL	0x00000080L
#define OHCI_CTRL_HCFS_SUSPEND		0x000000c0L
#define OHCI_CTRL_HCFS_MASK			0x000000c0L
#define OHCI_CTRL_IR				0x00000100L		/* Interrupt Routing */
#define OHCI_CTRL_RWC				0x00000200L		/* Remote Wakeup Connected */
#define OHCI_CTRL_RWE				0x00000400L		/* Remote Wakeup Enable */
#define OHCI_CTRL_LES				(OHCI_CTRL_PLE | OHCI_CTRL_IE | OHCI_CTRL_CLE | OHCI_CTRL_BLE)

/* HcCommandStatus */
#define OHCI_CMD_HCR			0x00000001L			/* Host Controller Reset */
#define OHCI_CMD_CLF			0x00000002L			/* Control List Filled */
#define OHCI_CMD_BLF			0x00000004L			/* Bulk List Filled */
#define OHCI_CMD_OCR			0x00000008L			/* Ownership Change Request */
#define OHCI_CMD_SOC			0x00030000L			/* Scheduling Overrun Count */

/* HcInterruptStatus */
/* HcInterruptEnable */
/* HcInterruptDisable */
#define OHCI_INTR_SO			0x00000001L			/* Scheduling Overrun */
#define OHCI_INTR_WDH			0x00000002L			/* Writeback Done Head */
#define OHCI_INTR_SF			0x00000004L			/* Start of Frame */
#define OHCI_INTR_RD			0x00000008L			/* Resume Detected */
#define OHCI_INTR_UE			0x00000010L			/* Unrecoverable Error */
#define OHCI_INTR_FNO			0x00000020L			/* Frame Number Overflow */
#define OHCI_INTR_RHSC			0x00000040L			/* Root Hub Status Change */
#define OHCI_INTR_OC			0x40000000L			/* Ownership Change */
#define OHCI_INTR_MIE			0x80000000L			/* Master Interrupt Enable */
#define OHCI_INTR_MASK_ALL		(OHCI_INTR_SO | OHCI_INTR_WDH | OHCI_INTR_SF | OHCI_INTR_RD | \
								OHCI_INTR_UE | OHCI_INTR_FNO | OHCI_INTR_RHSC | OHCI_INTR_OC)
#define OHCI_INTR_MASK_NORMAL	(OHCI_INTR_WDH | OHCI_INTR_UE | OHCI_INTR_RHSC)

/* HcFmInterval */
#define OHCI_FMI_IVAL(s)		((s) & 0x3fff)
#define OHCI_FMI_CALC_FSMPS(i)	(((i - 210) * 6 / 7) << 16)
#define OHCI_FMI_FIT			0x80000000L


/* HcRhDescriptorA */
#define OHCI_RHA_NDP(s)			(uint8_t)((s) & 0xff)
#define OHCI_RHA_PSM			0x0100L				/* Power Switching Mode */
#define OHCI_RHA_NPS			0x0200L				/* No Power Switching */

#define OHCI_RHA_OCPM		0x0800L				/* Over Current Protection Mode */
#define OHCI_RHA_NOCP		0x1000L				/* No Over Current Protection */


#define OHCI_RHA_POTPGT(s)		((s) >> 24)


/* HcRhStatus */
#define OHCI_RHS_LPS			0x00000001L			/* Local Power Status */
#define OHCI_RHS_OCI			0x00000002L			/* OverCurrent Indicator */
#define OHCI_RHS_DRWE			0x00008000L			/* Device Remote Wakeup Enable */
#define OHCI_RHS_LPSC			0x00010000L			/* Local Power Status Change */
#define OHCI_RHS_CCIC			0x00020000L			/* OverCurrent Indicator Change */
#define OHCI_RHS_CRWE			0x80000000L			/* Clear Remote Wakeup Enable */


/* HcRhPortStatus */
#define OHCI_RPS_PRSC			0x00100000L			/* Port Reset Status Change */

#endif
