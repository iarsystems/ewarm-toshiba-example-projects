/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_ohciconfig.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  OHCI パラメータ設定

*/

#ifndef USB_OHCI_PARAMETER_DEFINE_H
#define USB_OHCI_PARAMETER_DEFINE_H

#include "usb_config.h"

/* Interrupt 転送正式実装版の使用 */
#define USB_OHCI_FORMAL_INTR

/* Pipe 最大数 (エンドポイント + ルートハブ(CTRL + INTR) ) */
#define OHCI_MAX_PIPES  (USB_TOTAL_MAX_ENDPOINTS + 2)
/* XFER 最大数 (デバイス(CTRL) + ハブ(INTR) + ルートハブ + 1) */
#define OHCI_MAX_XFERS  (USB_MAX_DEVICES + USB_MAX_HUBS + 3)
/* エンドポイントディスクリプタ最大数 (+ ダミー) */
#define OHCI_MAX_EDS    (USB_TOTAL_MAX_ENDPOINTS + 3)
/* トランスポートディスクリプタ最大数 */
#define OHCI_MAX_TDS    (USB_TOTAL_MAX_TRANSFER_DESCRIPTORS + USB_TOTAL_MAX_ENDPOINTS + USB_MAX_HUBS)

/* HcFmInterval SOF の間隔 0 - 0x3fff (未設定の場合初期値(11999)が使用される) */
//#define USB_OHCI_FM_INTERVAL  11860

#endif
