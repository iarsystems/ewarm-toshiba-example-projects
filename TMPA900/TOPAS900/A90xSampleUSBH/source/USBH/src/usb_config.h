/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
 */

/* $Id: usb_config.h 41 2014-01-27 14:05:18Z danielru $ */

/*

  USB Host Driver Configuration

*/

#ifndef USB_CONFIG_H
#define USB_CONFIG_H


#define CTLCS900H1 0
#define CTX09 1
#define MMCU_CORE 1


#if defined( USB_DEBUG )
#define USB_CHECK_COMM_QUALITY
#endif

#if(1)
# ifndef USB_CTX_SWT
# define USB_CTX_SWT
# endif
#endif

/*!
 * \brief 同時接続可能な最大デバイス数
 * \attention ルートハブもデバイスとして扱われるが、ここでは含めない。
 *
 * 最大同時接続可能なデバイス数を指定する。
 * この値を超えるデバイス数が同時に接続された場合、そのデバイスは
 * USBバス・ドライバでは処理を行わない。
 */
//#define USB_MAX_DEVICES     5
#define USB_MAX_DEVICES     2

/*!
 * \brief 1デバイスあたりの最大インターフェイス数
 *
 * １つのデバイスが持つ、最大インターフェイス数を指定する。
 * デバイスに対して、この値よりも多くのインターフェイスを持つ
 * コンフィグレーションを設定すること(SetConfigデバイス・リク
 * エスト)はできない。
 */
#define USB_MAX_IFACES          1

/*!
 * \brief 1インターフェイスあたりの最大エンドポイント数
 *
 * １つのインターフェイスに含まれる、最大エンドポイント数を指定
 * する。
 * デバイスに対して、この値よりも多くのエンドポイントを持つインタ
 * ーフェイスのあるコンフィグレーションを設定すること(SetConfigデ
 * バイス・リクエスト)はできない。
 */
#define USB_MAX_ENDPOINTS       3

/*!
 * \brief 最大同時接続可能なハブ数
 * \attention ルートハブは含まない。
 *
 * 同時接続可能な最大ハブ数を指定する。
 * ハブ・デバイスには、対応していないため 0 に固定。
 * この値を超えるハブ・デバイスを接続しても、USBバス・ドライバで
 * 処理を行なわない。
 */
#define USB_MAX_HUBS      2

/*!
 * \brief ハブの最大ポート数
 * \attention ルートハブのポート数にも該当する。
 *
 * 接続される１つのハブ・デバイスが持つ最大ポート数を指定する。
 * この値を超えるポート数を持つハブを接続した場合、USBバス・ドライバでは
 * そのハブの認識を行なわず、無視する。
 */
#define USB_MAX_HUB_PORTS   4

/*!
 * \brief 最大同時確保可能なクラス・ドライバ登録構造体の数
 * \attention ハブ・クラスは含まない。
 *
 * 同時確保可能なクラス・ドライバ登録構造体(USBD_typeClassDriver型)
 * の最大数を指定する。この値を超えるクラス・ドライバ登録構造体を
 * 確保すること(usb_USBD_ptAllocClassDriver())はできない。
 */
//#define USB_MAX_CLASS_DRIVERS 4
#define USB_MAX_CLASS_DRIVERS 2


/*!
 * \brief 最大登録可能インターフェース単位のクラスドライバ数
 *
 * クラスドライバ管理層に登録可能なインターフェース単位のクラスドライ
 * バの最大数を指定する。
 */
/*  */
#define USB_MAX_CLASS_IFACE_DRIVERS  (USB_MAX_CLASS_DRIVERS * USB_MAX_IFACES)

/*!
 * \brief 同時接続可能な合計最大インターフェース数
 *
 * 同時接続可能な最大インターフェース数の合計を指定する。
 * 現状では理論的な最大値 (最大のデバイス数×インターフェース数) を設定している
 */
#define USB_TOTAL_MAX_IFACES (USB_MAX_DEVICES * USB_MAX_IFACES)


/*!
 * \brief 同時使用可能な最大エンドポイント数
 *
 * 同時使用可能な最大エンドポイント数の合計を指定する。
 * 現状では理論的な最大値 (最大の合計インターフェース数×エンドポイント数) を設定している
 */
#define USB_TOTAL_MAX_ENDPOINTS (USB_TOTAL_MAX_IFACES * USB_MAX_ENDPOINTS + USB_MAX_DEVICES)


/*!
 * \brief 同時使用可能な最大転送ディスクリプタ数 (>= 3)
 *
 * 同時使用可能な最大転送ディスクリプタ数の合計を指定する。
 * 一つの転送ディスクリプタにつき、約4～8[kByte] のデータ転送が可能。
 * デバイスリクエストは同時に3つの転送ディスクリプタを使用するため、最低値は 3。
 */
#define USB_TOTAL_MAX_TRANSFER_DESCRIPTORS 3


#if __ICCARM__
#include <intrinsics.h>
#define __inline  inline
#endif

#endif /* USB_CONFIG_H */
