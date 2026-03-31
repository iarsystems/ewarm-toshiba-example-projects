/*
 * COPYRIGHT (C) 2018
 * TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION
 * ALL RIGHTS RESERVED
 *
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * ELECTRONIC DEVICES & STORAGE CORPORATION MAKES NO OTHER WARRANTY OF ANY
 * KIND, WHETHER EXPRESS, IMPLIED OR, STATUTORY AND DISCLAIMS ANY AND ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, SATISFACTORY QUALITY, NON
 * INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA ELECTRONIC
 * DEVICES & STORAGE CORPORATION RESERVES THE RIGHT TO INCORPORATE
 * MODIFICATIONS TO THE SOURCE CODE IN LATER REVISIONS OF IT, AND TO MAKE
 * IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR THE PRODUCTS OR
 * TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 *
 * TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION SHALL NOT BE LIABLE FOR
 * ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR
 * USE OF THE SOURCE CODE OR ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO,
 * LOST REVENUES, DATA OR PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL NATURE, PUNITIVE DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS
 * ARISING OUT OF OR IN CONNECTION WITH THIS AGREEMENT, OR BEING UNUSABLE,
 * EVEN IF ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES AND
 * WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON WARRANTY, CONTRACT, TORT,
 * NEGLIGENCE OR OTHERWISE.
 */
/* VERSION : 20190213A */
/* TARGET  : TC35680-ROM002 */

/**
 * @file RTE_Device.h
 * @brief Device Configuration for TC35680 Series
 */

#ifndef RTE_DEVICE_H
#define RTE_DEVICE_H

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

/////////////////////////////////////////////////////////////////////////////
// <h> C2_patch
//  <h> Patch assign
//   <o> PATCH_ITEM_0 <0=>NotUsed <1=>23HOUR_CONNECTION <2=>23HOUR_EXT_SCAN <3=>ERRATUM10734
#define RTE_PATCH_ITEM_0 2
//   <o> PATCH_ITEM_1 <0=>NotUsed <1=>23HOUR_CONNECTION <2=>23HOUR_EXT_SCAN <3=>ERRATUM10734
#define RTE_PATCH_ITEM_1 3
//   <o> PATCH_ITEM_2 <0=>NotUsed <1=>23HOUR_CONNECTION <2=>23HOUR_EXT_SCAN <3=>ERRATUM10734
#define RTE_PATCH_ITEM_2 0
//   <o> PATCH_ITEM_3 <0=>NotUsed <1=>23HOUR_CONNECTION <2=>23HOUR_EXT_SCAN <3=>ERRATUM10734
#define RTE_PATCH_ITEM_3 0
//  </h>
//  <h> Other Patch settings
//   <q> ANYKEY CAUSE REG Issue <0=>Not Fix <1=>Fix this issue
//   <i> Default=1. Unless you have any special reasons, set 1.
#define RTE_PATCH_SWITCH_ANYKEY_CAUSE_REG 1
//   <q> 23HOUR_CONNECTION Issue <0=>Not Fix <1=>Fix this issue
//   <i> Default=1. If you set 1 to one of RTE_PATCH_ITEMs, set 0.
#define RTE_PATCH_SWITCH_23HOUR_CONNECTION 1
//   <q> 23HOUR_EXT_ADV Issue <0=>Not Fix <1=>Fix this issue
//   <i> Default=1. Unless you have any special reasons, set 1.
#define RTE_PATCH_SWITCH_23HOUR_EXT_ADV 1
//   <q> WIDE_SYNC_WINDOW <0=>Normal(LowPower) <1=>Wide(LongDistance)
//   <i> Set 1 if you want to connect to other devices with Coded-PHY, large TxPower value. Otherwise, set 0 to save power.
#define RTE_PATCH_SWITCH_WIDE_SYNC_WINDOW 1
//   <q> CHANNEL MAP in CS1 Issue <0=>Not Fix <1=>Fix this issue.
//   <i> Default=1. Unless you have any special reasons, set 1.
#define RTE_PATCH_SWITCH_CHANNEL_MAP_CS1 1
//   <q> Slave latency Issue <0=>Not Fix <1=>Fix this issue.
//   <i> Default=1. Unless you have any special reasons, set 1.
#define RTE_PATCH_SWITCH_SLAVE_LATENCY 1
//   <q> WhiteList with ADV_NONCONNIND Issue <0=>Not Fix <1=>Fix this issue.
//   <i> Default=1. Unless you have any special reasons, set 1.
#define RTE_PATCH_SWITCH_WHITELIST_NONCONN 1
//  </h>
// </h>

/////////////////////////////////////////////////////////////////////////////
// <h> UART
//  <h> UART1
//   <o> Use UART1 driver <0=>NotUsed <1=>Used
#define RTE_UART1 1
//   <o> Use DMA via UART1 <0=>NotUsed <1=>Used
#define RTE_UART1_DMAC_USE 0
//   <h> UART1 DMAC setting
//    <o> DMA ch for UART1 Tx <0-6>
#define RTE_UART1_DMAC_TX_CH 0
//    <o> DMA ch for UART1 Rx <0-6>
#define RTE_UART1_DMAC_RX_CH 1
//   </h>
//   <h> UART1 flow control setting
//    <o> GPIO No. for RTS in UART1 <7=>GPIO7 <13=>GPIO13
#define RTE_UART1_RTS_GPIO 13
//    <o> GPIO No. for CTS in UART1 <8=>GPIO8 <14=>GPIO14
#define RTE_UART1_CTS_GPIO 14
//   </h>
//  </h>
//  <h> UART2
//   <o> Use UART2 driver <0=>NotUsed <1=>Used
#define RTE_UART2 0
//   <o> Use DMA via UART2 <0=>NotUsed <1=>Used
#define RTE_UART2_DMAC_USE 0
//   <h> UART2 DMAC setting
//   <o> DMA ch for UART2 Tx <0-6>
#define RTE_UART2_DMAC_TX_CH 2
//   <o> DMA ch for UART2 Rx <0-6>
#define RTE_UART2_DMAC_RX_CH 3
//   </h>
//  </h>
// </h>

/////////////////////////////////////////////////////////////////////////////
// <h> I2C
// <h> Common
//    <o> Use DMAC via I2C <0=>NotUsed <1=>Use
#define RTE_I2C_DMAC_USE 0
// </h>
//  <h> I2C1
//   <h> I2C1 DMAC setting
//    <o> DMAC channel for I2C1 <0-6>
#define RTE_I2C1_DMAC_CH 5
//   </h>
//  </h>
//  <h> I2C2
//   <h> I2C2 DMAC setting
//    <o> DMAC channel for I2C2 <0-6>
#define RTE_I2C2_DMAC_CH 6
//   </h>
//   <h> I2C2 control pin setting
//    <o> Pin No. for I2C2 SCL <9=>GPIO9 <11=>GPIO11
#define RTE_I2C2_SCL 11
//    <o> Pin No. for I2C2 SDA <10=>GPIO10 <12=>GPIO12
#define RTE_I2C2_SDA 12
//   </h>
//  </h>
// </h>

/////////////////////////////////////////////////////////////////////////////
// <h> SPI
// <h> Common
//    <o> Use DMAC via SPI <0=>NotUsed <1=>Use
#define RTE_SPI_DMAC_USE 0
// </h>
//  <h> SPI1
//   <h> SPI1 DMAC setting
//    <o> DMAC channel for SPI1 TX <0-6>
#define RTE_SPI1_TX_DMAC_CH 5
//    <o> DMAC channel for SPI1 RX <0-6>
#define RTE_SPI1_RX_DMAC_CH 6
//   </h>
//  </h>
//  <h> SPI2
//   <h> SPI2 DMAC setting
//    <o> DMAC channel for SPI2 TX <0-6>
#define RTE_SPI2_TX_DMAC_CH 5
//    <o> DMAC channel for SPI2 RX <0-6>
#define RTE_SPI2_RX_DMAC_CH 6
//   </h>
//  </h>
// </h>

/////////////////////////////////////////////////////////////////////////////
// <h> ADC
//  <e> Enable/Disable Periodic scan
#define RTE_ADC_PERIODIC_SCAN_ENABLE 0
#if RTE_ADC_PERIODIC_SCAN_ENABLE
//   <o> DMAC channel used for Periodic ADC <0-6>
#define RTE_ADC_PERIODIC_SCAN_DMAC_CH 5
//  </e>
#endif // #if RTE_ADC_ENABLE_PERIODIC_SCAN
// </h>

/////////////////////////////////////////////////////////////////////////////
// <h> Connection information library
//  <h> Sector Address
//   <o> Sector A Address <0x0-0x3F000:0x1000>
#define RTE_CONN_INFO_SECTOR_A_ADDR 0x2000
//   <o> Sector B Address <0x0-0x3F000:0x1000>
#define RTE_CONN_INFO_SECTOR_B_ADDR 0x3000
//  </h>
// </h>

/////////////////////////////////////////////////////////////////////////////
// <h> UART1IO
//   <o> Use UART CMSIS Driver in UART1IO <0=>NotUsed(Use MaskROM API) <1=>Used
#define RTE_UART1IO_USE_CMSIS_DRIVER 0
//   <o> Baud Rate for UART1IO
#define RTE_UART1IO_BAUD_RATE 115200
// </h>

// <<< end of configuration section >>>
#endif  /* RTE_DEVICE_H */
