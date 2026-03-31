/*
 * COPYRIGHT (C) 2017
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
/* VERSION : 20190118A */
/* TARGET  : TC35680-ROM001 */

#ifndef REGDEF_H
#define REGDEF_H

#include <stdint.h>

/*
 *  General Macro Function
 */
#define REG_RD32(x)   (*((volatile uint32_t*)(x)))
#define REG_WR32(x,y) (*((volatile uint32_t*)(x)) = ((uint32_t)(y)))

#define REG_WR32_OR(reg,value)   (REG_WR32((reg),(REG_RD32(reg) | (value))))
#define REG_WR32_AND(reg,value)  (REG_WR32((reg),(REG_RD32(reg) & (value))))
#define REG_WR32_NAND(reg,value) (REG_WR32((reg),(REG_RD32(reg) & ~(value))))
#define REG_WR32_XOR(reg,value)  (REG_WR32((reg),(REG_RD32(reg) ^ (value))))
#define REG_WR32_ADD(reg,value)  (REG_WR32((reg),(REG_RD32(reg) + (value))))
#define REG_WR32_SUB(reg,value)  (REG_WR32((reg),(REG_RD32(reg) - (value))))

/*
 * Register Addresses
 */
//************************************************** 
//*** DMAC
//************************************************** 
#define DMA_Int_Stat                        0x40001000L // 0x40001000 + 0x000
#define DMA_Int_TemCo_Stat                  0x40001004L // 0x40001000 + 0x004
#define DMA_Int_TemCo_Clr                   0x40001008L // 0x40001000 + 0x008
#define DMA_Int_Err_Stat                    0x4000100CL // 0x40001000 + 0x00C
#define DMA_Int_Err_Clr                     0x40001010L // 0x40001000 + 0x010
#define DMA_RawInt_Tem_Stat                 0x40001014L // 0x40001000 + 0x014
#define DMA_RawInt_Err_Stat                 0x40001018L // 0x40001000 + 0x018
#define DMA_Enable_ch                       0x4000101CL // 0x40001000 + 0x01C
#define DMA_Soft_burst_req                  0x40001020L // 0x40001000 + 0x020
#define DMA_Soft_single_req                 0x40001024L // 0x40001000 + 0x024
#define DMA_Config_req                      0x40001030L // 0x40001000 + 0x030
#define DMA_ch0_Source                      0x40001100L // 0x40001000 + 0x100
#define DMA_ch0_Dest                        0x40001104L // 0x40001000 + 0x104
#define DMA_ch0_Link                        0x40001108L // 0x40001000 + 0x108
#define DMA_ch0_Contrl                      0x4000110CL // 0x40001000 + 0x10C
#define DMA_ch0_Config                      0x40001110L // 0x40001000 + 0x110
#define DMA_ch1_Source                      0x40001120L // 0x40001000 + 0x120
#define DMA_ch1_Dest                        0x40001124L // 0x40001000 + 0x124
#define DMA_ch1_Link                        0x40001128L // 0x40001000 + 0x128
#define DMA_ch1_Contrl                      0x4000112CL // 0x40001000 + 0x12C
#define DMA_ch1_Config                      0x40001130L // 0x40001000 + 0x130
#define DMA_ch2_Source                      0x40001140L // 0x40001000 + 0x140
#define DMA_ch2_Dest                        0x40001144L // 0x40001000 + 0x144
#define DMA_ch2_Link                        0x40001148L // 0x40001000 + 0x148
#define DMA_ch2_Contrl                      0x4000114CL // 0x40001000 + 0x14C
#define DMA_ch2_Config                      0x40001150L // 0x40001000 + 0x150
#define DMA_ch3_Source                      0x40001160L // 0x40001000 + 0x160
#define DMA_ch3_Dest                        0x40001164L // 0x40001000 + 0x164
#define DMA_ch3_Link                        0x40001168L // 0x40001000 + 0x168
#define DMA_ch3_Contrl                      0x4000116CL // 0x40001000 + 0x16C
#define DMA_ch3_Config                      0x40001170L // 0x40001000 + 0x170
#define DMA_ch4_Source                      0x40001180L // 0x40001000 + 0x180
#define DMA_ch4_Dest                        0x40001184L // 0x40001000 + 0x184
#define DMA_ch4_Link                        0x40001188L // 0x40001000 + 0x188
#define DMA_ch4_Contrl                      0x4000118CL // 0x40001000 + 0x18C
#define DMA_ch4_Config                      0x40001190L // 0x40001000 + 0x190
#define DMA_ch5_Source                      0x400011A0L // 0x40001000 + 0x1A0
#define DMA_ch5_Dest                        0x400011A4L // 0x40001000 + 0x1A4
#define DMA_ch5_Link                        0x400011A8L // 0x40001000 + 0x1A8
#define DMA_ch5_Contrl                      0x400011ACL // 0x40001000 + 0x1AC
#define DMA_ch5_Config                      0x400011B0L // 0x40001000 + 0x1B0
#define DMA_ch6_Source                      0x400011C0L // 0x40001000 + 0x1C0
#define DMA_ch6_Dest                        0x400011C4L // 0x40001000 + 0x1C4
#define DMA_ch6_Link                        0x400011C8L // 0x40001000 + 0x1C8
#define DMA_ch6_Contrl                      0x400011CCL // 0x40001000 + 0x1CC
#define DMA_ch6_Config                      0x400011D0L // 0x40001000 + 0x1D0

//************************************************** 
//*** UART
//************************************************** 
// UART1
#define UART1_RBR_THR                       0x40044000L // 0x40044000 + 0x00
#define UART1_ICR                           0x40044004L // 0x40044000 + 0x04
#define UART1_ILSR                          0x40044008L // 0x40044000 + 0x08
#define UART1_IER                           0x4004400CL // 0x40044000 + 0x0C
#define UART1_LFCR                          0x40044010L // 0x40044000 + 0x10
#define UART1_OVCR                          0x40044014L // 0x40044000 + 0x14
#define UART1_CWTCR                         0x40044018L // 0x40044000 + 0x18
#define UART1_IBRD                          0x4004401CL // 0x40044000 + 0x1C
#define UART1_ABER                          0x40044020L // 0x40044000 + 0x20
#define UART1_ABSR                          0x40044024L // 0x40044000 + 0x24
#define UART1_ABPEIR                        0x40044028L // 0x40044000 + 0x28
#define UART1_ABNEIR                        0x4004402CL // 0x40044000 + 0x2C
#define UART1_FBRD                          0x40044030L // 0x40044000 + 0x30
// UART2
#define UART2_RBR_THR                       0x4005C000L // 0x4005C000 + 0x00
#define UART2_ICR                           0x4005C004L // 0x4005C000 + 0x04
#define UART2_ILSR                          0x4005C008L // 0x4005C000 + 0x08
#define UART2_IER                           0x4005C00CL // 0x4005C000 + 0x0C
#define UART2_LFCR                          0x4005C010L // 0x4005C000 + 0x10
#define UART2_OVCR                          0x4005C014L // 0x4005C000 + 0x14
#define UART2_CWTCR                         0x4005C018L // 0x4005C000 + 0x18
#define UART2_IBRD                          0x4005C01CL // 0x4005C000 + 0x1C
#define UART2_ABER                          0x4005C020L // 0x4005C000 + 0x20
#define UART2_ABSR                          0x4005C024L // 0x4005C000 + 0x24
#define UART2_ABPEIR                        0x4005C028L // 0x4005C000 + 0x28
#define UART2_ABNEIR                        0x4005C02CL // 0x4005C000 + 0x2C
#define UART2_FBRD                          0x4005C030L // 0x4005C000 + 0x30

//************************************************** 
//*** SPI
//************************************************** 
// SPI1
#define SPI1_CONTROL                         0x40046000L // 0x40046000 + 0x00
#define SPI1_TIMINGCONTROL                   0x40046004L // 0x40046000 + 0x04
#define SPI1_TXDATA                          0x40046008L // 0x40046000 + 0x08
#define SPI1_RXDATA                          0x4004600CL // 0x40046000 + 0x0C
#define SPI1_INTCONTROL                      0x40046010L // 0x40046000 + 0x10
#define SPI1_INTSTATUS                       0x40046014L // 0x40046000 + 0x14
#define SPI1_DEBUG1                          0x40046018L // 0x40046000 + 0x18
#define SPI1_DEBUG2                          0x4004601CL // 0x40046000 + 0x1C
#define SPI1_TIMINGCONTROL2                  0x40046020L // 0x40046000 + 0x20
#define SPI1_TXWAITTIMER0                    0x40046024L // 0x40046000 + 0x24
#define SPI1_TXWAITTIMER1                    0x40046028L // 0x40046000 + 0x28
#define SPI1_TXRXLENGTH                      0x4004602CL // 0x40046000 + 0x2C
// SPI2
#define SPI2_CONTROL                         0x40056000L // 0x40056000 + 0x00
#define SPI2_TIMINGCONTROL                   0x40056004L // 0x40056000 + 0x04
#define SPI2_TXDATA                          0x40056008L // 0x40056000 + 0x08
#define SPI2_RXDATA                          0x4005600CL // 0x40056000 + 0x0C
#define SPI2_INTCONTROL                      0x40056010L // 0x40056000 + 0x10
#define SPI2_INTSTATUS                       0x40056014L // 0x40056000 + 0x14
#define SPI2_DEBUG1                          0x40056018L // 0x40056000 + 0x18
#define SPI2_DEBUG2                          0x4005601CL // 0x40056000 + 0x1C
#define SPI2_TIMINGCONTROL2                  0x40056020L // 0x40056000 + 0x20
#define SPI2_TXWAITTIMER0                    0x40056024L // 0x40056000 + 0x24
#define SPI2_TXWAITTIMER1                    0x40056028L // 0x40056000 + 0x28
#define SPI2_TXRXLENGTH                      0x4005602CL // 0x40056000 + 0x2C

//************************************************** 
//*** I2C1
//************************************************** 
// I2C1
#define I2C1_CR1                            0x40048000L // 0x40048000 + 0x00
#define I2C1_DBR                            0x40048004L // 0x40048000 + 0x04
#define I2C1_AR                             0x40048008L // 0x40048000 + 0x08
#define I2C1_CR2                            0x4004800CL // 0x40048000 + 0x0C
#define I2C1_SR                             0x40048010L // 0x40048000 + 0x10
#define I2C1_PRS                            0x40048014L // 0x40048000 + 0x14
#define I2C1_IE                             0x40048018L // 0x40048000 + 0x18
#define I2C1_ST                             0x4004801CL // 0x40048000 + 0x1C
#define I2C1_OP                             0x40048020L // 0x40048000 + 0x20
#define I2C1_PM                             0x40048024L // 0x40048000 + 0x24
#define I2C1_AR2                            0x40048028L // 0x40048000 + 0x28
// I2C2
#define I2C2_CR1                            0x40058000L // 0x40058000 + 0x00
#define I2C2_DBR                            0x40058004L // 0x40058000 + 0x04
#define I2C2_AR                             0x40058008L // 0x40058000 + 0x08
#define I2C2_CR2                            0x4005800CL // 0x40058000 + 0x0C
#define I2C2_SR                             0x40058010L // 0x40058000 + 0x10
#define I2C2_PRS                            0x40058014L // 0x40058000 + 0x14
#define I2C2_IE                             0x40058018L // 0x40058000 + 0x18
#define I2C2_ST                             0x4005801CL // 0x40058000 + 0x1C
#define I2C2_OP                             0x40058020L // 0x40058000 + 0x20
#define I2C2_PM                             0x40058024L // 0x40058000 + 0x24
#define I2C2_AR2                            0x40058028L // 0x40058000 + 0x28

//************************************************** 
//*** GPADC
//************************************************** 
// GPADCC
#define GPADCC_CTRL                         0x4004A000L // 0x4004A000 + 0x00
#define GPADCC_SELAIN                       0x4004A004L // 0x4004A000 + 0x04
#define GPADCC_DATA                         0x4004A008L // 0x4004A000 + 0x08
#define GPADCC_INTMASK                      0x4004A00CL // 0x4004A000 + 0x0C
#define GPADCC_INTCLR                       0x4004A010L // 0x4004A000 + 0x10
#define GPADCC_STATE                        0x4004A014L // 0x4004A000 + 0x14
#define GPADCC_BUSYMASK                     0x4004A018L // 0x4004A000 + 0x18


//************************************************** 
//*** PWM
//************************************************** 
// PWMCH0_ADR
#define PWM_PCTRL_CH0                       0x4004A100L // 0x4004A100 + 0x00
#define PWM_PATTERN_CH0                     0x4004A104L // 0x4004A100 + 0x04
#define PWM_CYCLE_CH0                       0x4004A108L // 0x4004A100 + 0x08
#define PWM_DUTY_CH0                        0x4004A10CL // 0x4004A100 + 0x0C
#define PWM_UNIT_CH0                        0x4004A110L // 0x4004A100 + 0x10
#define PWM_STATE_CH0                       0x4004A114L // 0x4004A100 + 0x14
#define PWM_INTCLR_CH0                      0x4004A118L // 0x4004A100 + 0x18
// PWMCH1_ADR
#define PWM_PCTRL_CH1                       0x4004A200L // 0x4004A200 + 0x00
#define PWM_PATTERN_CH1                     0x4004A204L // 0x4004A200 + 0x04
#define PWM_CYCLE_CH1                       0x4004A208L // 0x4004A200 + 0x08
#define PWM_DUTY_CH1                        0x4004A20CL // 0x4004A200 + 0x0C
#define PWM_UNIT_CH1                        0x4004A210L // 0x4004A200 + 0x10
#define PWM_STATE_CH1                       0x4004A214L // 0x4004A200 + 0x14
#define PWM_INTCLR_CH1                      0x4004A218L // 0x4004A200 + 0x18
// PWMCH2_ADR
#define PWM_PCTRL_CH2                       0x4004A300L // 0x4004A300 + 0x00
#define PWM_PATTERN_CH2                     0x4004A304L // 0x4004A300 + 0x04
#define PWM_CYCLE_CH2                       0x4004A308L // 0x4004A300 + 0x08
#define PWM_DUTY_CH2                        0x4004A30CL // 0x4004A300 + 0x0C
#define PWM_UNIT_CH2                        0x4004A310L // 0x4004A300 + 0x10
#define PWM_STATE_CH2                       0x4004A314L // 0x4004A300 + 0x14
#define PWM_INTCLR_CH2                      0x4004A318L // 0x4004A300 + 0x18
// PWMCH3_ADR
#define PWM_PCTRL_CH3                       0x4004A400L // 0x4004A400 + 0x00
#define PWM_PATTERN_CH3                     0x4004A404L // 0x4004A400 + 0x04
#define PWM_CYCLE_CH3                       0x4004A408L // 0x4004A400 + 0x08
#define PWM_DUTY_CH3                        0x4004A40CL // 0x4004A400 + 0x0C
#define PWM_UNIT_CH3                        0x4004A410L // 0x4004A400 + 0x10
#define PWM_STATE_CH3                       0x4004A414L // 0x4004A400 + 0x14
#define PWM_INTCLR_CH3                      0x4004A418L // 0x4004A400 + 0x18
#define PWM_EN_WRAP                         0x4004A500L // 0x4004A500 + 0x00


//************************************************** 
//*** ckgen
//************************************************** 
// ckgen
#define CG_PWM_CTRL                         0x4004C004L // 0x4004C000 + 0x04
#define CG_DIVNUM1                          0x4004C008L // 0x4004C000 + 0x08
#define CG_DIVNUM2                          0x4004C00CL // 0x4004C000 + 0x0C
#define CG_DIVNUM3                          0x4004C010L // 0x4004C000 + 0x10
#define CG_DIVNUM4                          0x4004C014L // 0x4004C000 + 0x14
#define CG_DIVNUM5                          0x4004C018L // 0x4004C000 + 0x18
#define CG_CLK_CTRL                         0x4004C020L // 0x4004C000 + 0x20
#define CG_CLK_CTRL2                        0x4004C024L // 0x4004C000 + 0x24
#define CG_CG_CTRL                          0x4004C080L // 0x4004C000 + 0x80
#define CG_WD_INIT                          0x4004C0A0L // 0x4004C000 + 0xA0
#define CG_WD_CURNT                         0x4004C0A4L // 0x4004C000 + 0xA4
#define CG_DIVNUM6                          0x4004C0A8L // 0x4004C000 + 0xA8

//************************************************** 
//*** TIMER
//************************************************** 
// BCTIMER
#define TIM_BCTIMER_CTRL                    0x4004D000L // 0x4004D000 + 0x000
#define TIM_BCTIMER_STAT                    0x4004D004L // 0x4004D000 + 0x004
#define TIM_BCTIMER_A                       0x4004D008L // 0x4004D000 + 0x008
#define TIM_BCTIMER_B                       0x4004D00CL // 0x4004D000 + 0x00C
#define TIM_BCTIMER_C                       0x4004D010L // 0x4004D000 + 0x010
#define TIM_BCTIMER_A_RD                    0x4004D014L // 0x4004D000 + 0x014
#define TIM_BCTIMER_B_RD                    0x4004D018L // 0x4004D000 + 0x018
#define TIM_BCTIMER_C_RD                    0x4004D01CL // 0x4004D000 + 0x01C
// GTIMER
#define TIM_GTIMER_CTRL                     0x4004D100L // 0x4004D000 + 0x100
#define TIM_GTIMER_STAT                     0x4004D104L // 0x4004D000 + 0x104
#define TIM_GTIMER_A                        0x4004D108L // 0x4004D000 + 0x108
#define TIM_GTIMER_A_RD                     0x4004D114L // 0x4004D000 + 0x114

//************************************************** 
//*** GPIO
//************************************************** 
#define GPIO_MON0                           0x4004E000L // 0x4004E000 + 0x000
#define GPIO_MON1                           0x4004E004L // 0x4004E000 + 0x004
#define GPIO_MON2                           0x4004E008L // 0x4004E000 + 0x008
#define GPIO_MON3                           0x4004E00CL // 0x4004E000 + 0x00C
#define GPIO_MON4                           0x4004E010L // 0x4004E000 + 0x010
#define GPIO_MON5                           0x4004E014L // 0x4004E000 + 0x014
#define GPIO_MON6                           0x4004E018L // 0x4004E000 + 0x018
#define GPIO_MON7                           0x4004E01CL // 0x4004E000 + 0x01C
#define GPIO_MON8                           0x4004E020L // 0x4004E000 + 0x020
#define GPIO_MON9                           0x4004E024L // 0x4004E000 + 0x024
#define GPIO_MON10                          0x4004E028L // 0x4004E000 + 0x028
#define GPIO_MON11                          0x4004E02CL // 0x4004E000 + 0x02C
#define GPIO_MON12                          0x4004E030L // 0x4004E000 + 0x030
#define GPIO_MON13                          0x4004E034L // 0x4004E000 + 0x034
#define GPIO_MON14                          0x4004E038L // 0x4004E000 + 0x038
#define GPIO_MON15                          0x4004E03CL // 0x4004E000 + 0x03C
#define GPIO_MON16                          0x4004E040L // 0x4004E000 + 0x040
#define GPIO_MON17                          0x4004E044L // 0x4004E000 + 0x044
#define GPIO_OUT0                           0x4004E100L // 0x4004E100 + 0x000
#define GPIO_OUT1                           0x4004E104L // 0x4004E100 + 0x004
#define GPIO_OUT2                           0x4004E108L // 0x4004E100 + 0x008
#define GPIO_OUT3                           0x4004E10CL // 0x4004E100 + 0x00C
#define GPIO_OUT4                           0x4004E110L // 0x4004E100 + 0x010
#define GPIO_OUT5                           0x4004E114L // 0x4004E100 + 0x014
#define GPIO_OUT6                           0x4004E118L // 0x4004E100 + 0x018
#define GPIO_OUT7                           0x4004E11CL // 0x4004E100 + 0x01C
#define GPIO_OUT8                           0x4004E120L // 0x4004E100 + 0x020
#define GPIO_OUT9                           0x4004E124L // 0x4004E100 + 0x024
#define GPIO_OUT10                          0x4004E128L // 0x4004E100 + 0x028
#define GPIO_OUT11                          0x4004E12CL // 0x4004E100 + 0x02C
#define GPIO_OUT12                          0x4004E130L // 0x4004E100 + 0x030
#define GPIO_OUT13                          0x4004E134L // 0x4004E100 + 0x034
#define GPIO_OUT14                          0x4004E138L // 0x4004E100 + 0x038
#define GPIO_OUT15                          0x4004E13CL // 0x4004E100 + 0x03C
#define GPIO_OUT16                          0x4004E140L // 0x4004E100 + 0x040
#define GPIO_OUT17                          0x4004E144L // 0x4004E100 + 0x044
#define GPIO_OUT_EN0                        0x4004E200L // 0x4004E200 + 0x000
#define GPIO_OUT_EN1                        0x4004E204L // 0x4004E200 + 0x004
#define GPIO_OUT_EN2                        0x4004E208L // 0x4004E200 + 0x008
#define GPIO_OUT_EN3                        0x4004E20CL // 0x4004E200 + 0x00C
#define GPIO_OUT_EN4                        0x4004E210L // 0x4004E200 + 0x010
#define GPIO_OUT_EN5                        0x4004E214L // 0x4004E200 + 0x014
#define GPIO_OUT_EN6                        0x4004E218L // 0x4004E200 + 0x018
#define GPIO_OUT_EN7                        0x4004E21CL // 0x4004E200 + 0x01C
#define GPIO_OUT_EN8                        0x4004E220L // 0x4004E200 + 0x020
#define GPIO_OUT_EN9                        0x4004E224L // 0x4004E200 + 0x024
#define GPIO_OUT_EN10                       0x4004E228L // 0x4004E200 + 0x028
#define GPIO_OUT_EN11                       0x4004E22CL // 0x4004E200 + 0x02C
#define GPIO_OUT_EN12                       0x4004E230L // 0x4004E200 + 0x030
#define GPIO_OUT_EN13                       0x4004E234L // 0x4004E200 + 0x034
#define GPIO_OUT_EN14                       0x4004E238L // 0x4004E200 + 0x038
#define GPIO_OUT_EN15                       0x4004E23CL // 0x4004E200 + 0x03C
#define GPIO_OUT_EN16                       0x4004E240L // 0x4004E200 + 0x040
#define GPIO_OUT_EN17                       0x4004E244L // 0x4004E200 + 0x044
#define GPIO_CFG0                           0x4004E300L // 0x4004E300 + 0x000
#define GPIO_CFG1                           0x4004E304L // 0x4004E300 + 0x004
#define GPIO_CFG2                           0x4004E308L // 0x4004E300 + 0x008
#define GPIO_CFG3                           0x4004E30CL // 0x4004E300 + 0x00C
#define GPIO_CFG4                           0x4004E310L // 0x4004E300 + 0x010
#define GPIO_CFG5                           0x4004E314L // 0x4004E300 + 0x014
#define GPIO_CFG6                           0x4004E318L // 0x4004E300 + 0x018
#define GPIO_CFG7                           0x4004E31CL // 0x4004E300 + 0x01C
#define GPIO_CFG8                           0x4004E320L // 0x4004E300 + 0x020
#define GPIO_CFG9                           0x4004E324L // 0x4004E300 + 0x024
#define GPIO_CFG10                          0x4004E328L // 0x4004E300 + 0x028
#define GPIO_CFG11                          0x4004E32CL // 0x4004E300 + 0x02C
#define GPIO_CFG12                          0x4004E330L // 0x4004E300 + 0x030
#define GPIO_CFG13                          0x4004E334L // 0x4004E300 + 0x034
#define GPIO_CFG14                          0x4004E338L // 0x4004E300 + 0x038
#define GPIO_CFG15                          0x4004E33CL // 0x4004E300 + 0x03C
#define GPIO_CFG16                          0x4004E340L // 0x4004E300 + 0x040
#define GPIO_CFG17                          0x4004E344L // 0x4004E300 + 0x044
#define GPIO_MUXCFG_L                       0x4004E400L // 0x4004E400 + 0x000
#define GPIO_MUXCFG_M                       0x4004E404L // 0x4004E400 + 0x004
#define GPIO_MUXCFG_H                       0x4004E408L // 0x4004E400 + 0x008
#define GPIO_OBSMUXCFG                      0x4004E490L // 0x4004E480 + 0x010
#define GPIO_MON_WRAP                       0x4004E4C0L // 0x4004E4C0 + 0x000
#define GPIO_OUT_WRAP                       0x4004E4C4L // 0x4004E4C0 + 0x004
#define GPIO_OUT_EN_WRAP                    0x4004E4C8L // 0x4004E4C0 + 0x008

//************************************************** 
//*** PMU
//************************************************** 
// PMU_ADR
#define PMU_RTCWAKEUPCFG                    0x4005505CL // 0x40055000 + 0x5C
#define PMU_IOSTANDBYX                      0x40055078L // 0x40055000 + 0x78
#define PMU_RTC_TIME                        0x400550B0L // 0x40055000 + 0xB0
#define PMU_RTC_DAY                         0x400550B4L // 0x40055000 + 0xB4
#define PMU_RTC_PAGER                       0x400550B8L // 0x40055000 + 0xB8
#define PMU_RTC_RESTR                       0x400550BCL // 0x40055000 + 0xBC
#define PMU_RTC_TIME2                       0x400550C4L // 0x40055000 + 0xC4
#define PMU_RTC_TEST                        0x400550CCL // 0x40055000 + 0xCC
#define PMU_RTC_INTCLR                      0x400550D0L // 0x40055000 + 0xD0
#define PMU_RTC_INTEN                       0x400550D4L // 0x40055000 + 0xD4
#define PMU_RTC_CNTCFG                      0x400550D8L // 0x40055000 + 0xD8
#define PMU_XOSC_TRIMIN                     0x40055118L // 0x40055000 + 0x118
#define PMU_OSC32K_TRIMIN                   0x4005511CL // 0x40055000 + 0x11C
#define PMU_SLEEPCLK_STATUS                 0x40055160L // 0x40055000 + 0x160
#define PMU_SLEEPCLK_HL_STATUS              0x40055164L // 0x40055000 + 0x164




#define PMU_RTC_ADJDAT                      0x400550C0L // 0x40055000 + 0xC0
#define PMU_MODEREG                         0x40055000L // 0x40055000 + 0x00
#define PMU_CAUSEREG                        0x40055004L // 0x40055000 + 0x04
#define PMU_BUSYSTATUS                      0x40055008L // 0x40055000 + 0x08
#define PMU_MODECONFIG                      0x4005500CL // 0x40055000 + 0x0C
#define PMU_CLKCONFIG                       0x40055010L // 0x40055000 + 0x10
#define PMU_INVALTIMERCTRL                  0x40055014L // 0x40055000 + 0x14
#define PMU_INVALTIMER                      0x40055018L // 0x40055000 + 0x18
#define PMU_INVALTIMERINTCLR                0x4005501CL // 0x40055000 + 0x1C
#define PMU_INVALTIMERINTEN                 0x40055020L // 0x40055000 + 0x20
#define PMU_INVALTIMER_PERIOD               0x40055024L // 0x40055000 + 0x24
#define PMU_INVALTIMER_PWRON                0x40055028L // 0x40055000 + 0x28
#define PMU_INVALTIMER_ACT                  0x4005502CL // 0x40055000 + 0x2C
#define PMU_INVAL_DLYCTRL                   0x40055034L // 0x40055000 + 0x34
#define PMU_INVALTIMER_USPERIOD             0x40055038L // 0x40055000 + 0x38
#define PMU_INVALTIMER_CFG                  0x4005503CL // 0x40055000 + 0x3C
#define PMU_TIMER_MESNUM                    0x40055040L // 0x40055000 + 0x40
#define PMU_TIMER_MESRES                    0x40055044L // 0x40055000 + 0x44
#define PMU_TIMER_CNTCFG                    0x40055048L // 0x40055000 + 0x48
#define PMU_EXTWAKEUPCONFIG                 0x40055050L // 0x40055000 + 0x50
#define PMU_ANYKEY_WAKEUPCFG1               0x40055054L // 0x40055000 + 0x54
#define PMU_ANYKEY_WAKEUPCFG2               0x40055058L // 0x40055000 + 0x58
#define PMU_EXTWAKEUPINTCLR                 0x40055064L // 0x40055000 + 0x64
#define PMU_EXTWAKEUPINTEN                  0x40055068L // 0x40055000 + 0x68
#define PMU_LVDDISABLE                      0x4005506CL // 0x40055000 + 0x6C
#define PMU_IORESETX                        0x40055070L // 0x40055000 + 0x70
#define PMU_IOLATEN                         0x40055074L // 0x40055000 + 0x74
#define PMU_SWRSTCONFIG                     0x4005507CL // 0x40055000 + 0x7C
#define PMU_AUTOADV_MOD                     0x40055080L // 0x40055000 + 0x80
#define PMU_AUTOADV_CONFIG                  0x40055084L // 0x40055000 + 0x84
#define PMU_AUTOADV_RPT                     0x40055088L // 0x40055000 + 0x88
#define PMU_FSTRECFGMEMAD                   0x4005508CL // 0x40055000 + 0x8C
#define PMU_AUTOIOLATEN                     0x40055090L // 0x40055000 + 0x90
#define PMU_AUTOADV_BIT_PRESETVAL           0x40055094L // 0x40055000 + 0x94
#define PMU_LDOFCONFIG                      0x400550A0L // 0x40055000 + 0xA0
#define PMU_TEST_HVMODE                     0x400550A4L // 0x40055000 + 0xA4
#define PMU_DD_DVSSEL                       0x400550E8L // 0x40055000 + 0xE8
#define PMU_DD_VOSEL                        0x400550ECL // 0x40055000 + 0xEC
#define PMU_DD_CFGREG                       0x400550F0L // 0x40055000 + 0xF0
#define PMU_XO_CFGREG                       0x400550F4L // 0x40055000 + 0xF4
#define PMU_DD_TRIMIN_1                     0x40055104L // 0x40055000 + 0x104
#define PMU_DD_TRIMIN_2                     0x40055108L // 0x40055000 + 0x108
#define PMU_BGR_TRIMIN_1                    0x4005510CL // 0x40055000 + 0x10C
#define PMU_BGR_TRIMIN_2                    0x40055110L // 0x40055000 + 0x110
#define PMU_BGR_TRIMIN_3                    0x40055114L // 0x40055000 + 0x114
#define PMU_SIOSC_TRIMIN                    0x40055120L // 0x40055000 + 0x120
#define PMU_LDOT_TRIMIN                     0x40055124L // 0x40055000 + 0x124
#define PMU_BGR_CAL_MODE                    0x40055130L // 0x40055000 + 0x130
#define PMU_BGR_CAL_PARAM                   0x40055134L // 0x40055000 + 0x134
#define PMU_BGR_CAL_PERIOD                  0x40055138L // 0x40055000 + 0x138
#define PMU_BGR_CAL_VREFLDOS                0x4005513CL // 0x40055000 + 0x13C
#define PMU_SWD_OFF                         0x40055180L // 0x40055000 + 0x180
#define PMU_ADPADV_MODE                     0x40055190L // 0x40055000 + 0x190
#define PMU_ADPADV_CHKFRQ                   0x40055194L // 0x40055000 + 0x194
#define PMU_ADPADV_RSSITHR                  0x40055198L // 0x40055000 + 0x198
#define PMU_ADPADV_THR                      0x4005519CL // 0x40055000 + 0x19C
#define PMU_ADPADV_CNTMODE                  0x400551A0L // 0x40055000 + 0x1A0
#define PMU_ADPADV_REMAIN                   0x400551A4L // 0x40055000 + 0x1A4
#define PMU_PMUTESTSEL                      0x400551A8L // 0x40055000 + 0x1A8
#define PMU_ADPADV_REGMON                   0x400551ACL // 0x40055000 + 0x1AC

//************************************************** 
//*** Bluetooth Counter
//************************************************** 
#define LLC_LLCNT_HOLD_EN                   0x4004024CL /* 0x40040240 + 0x0C */
#define LLC_BC_LATCH_MA                     0x40040260L /* 0x40040240 + 0x20 */
#define LLC_SC_LATCH_MA                     0x40040264L /* 0x40040240 + 0x24 */

//************************************************** 
//*** Other
//************************************************** 
#define RFB_MD_MODEM_TDMUXCLK_EN            0x40040D64L // 0x40040C00 + 0x164
#define MACPHY_DMAC_OBSCTRL                 0x400401F8L // 0x40040000 + 0x1F8

#endif // #ifndef REGDEF_H
