;/**
; ***************************************************************************
; * @file     startup_TMPM3U6.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for the
; *           TOSHIBA 'TMPM3U6' Device Series 
; * @version  V2.0.2.10
; * @date     2019/02/01
; * 
; * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
; * 
; * (C)Copyright TOSHIBA ELECTRONIC DEVICES & STORAGE CORPORATION 2019 All rights reserved
; *****************************************************************************
; */
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; Cortex-M version
;

                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table

                DATA
__vector_table  DCD     sfe(CSTACK)
                DCD     Reset_Handler

                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     INT0_IRQHandler           ; 0:  Interrupt pin (PH0/AIN0/INT0)
                DCD     INT1_IRQHandler           ; 1:  Interrupt pin (PH1/AIN1/INT1)
                DCD     INT2_IRQHandler           ; 2:  Interrupt pin (PH2/AIN2/INT2)
                DCD     INT3_IRQHandler           ; 3:  Interrupt pin (PA0/TB0IN/INT3)
                DCD     INT4_IRQHandler           ; 4:  Interrupt pin (PA2/TB1IN/INT4)
                DCD     INT5_IRQHandler           ; 5:  Interrupt pin (PE4/TB2IN/INT5)
                DCD     INTRX0_IRQHandler         ; 6:  Serial reception (channel.0)
                DCD     INTTX0_IRQHandler         ; 7:  Serial transmission (channel.0)
                DCD     INTRX1_IRQHandler         ; 8:  Serial reception (channel.1)
                DCD     INTTX1_IRQHandler         ; 9:  Serial transmission (channel.1)
                DCD     INTSSP0_IRQHandler        ; 10: Syncronous Serial Port 0
                DCD     INTSSP1_IRQHandler        ; 11: Syncronous Serial Port 1
                DCD     INTEMG0_IRQHandler        ; 12: PMD0 EMG interrupt (MPT0)
                DCD     INTEMG1_IRQHandler        ; 13: PMD1 EMG interrupt (MPT1)
                DCD     INTSBI0_IRQHandler        ; 14: Serial Bus Interface 0 interrupt
                DCD     INTSBI1_IRQHandler        ; 15: Serial Bus Interface 1 interrupt
                DCD     INTADPD0_IRQHandler       ; 16: ADC conversion triggered by PMD0 is finished
                DCD     INTRTC_IRQHandler         ; 17: Realtime clock interrupt
                DCD     INTADPD1_IRQHandler       ; 18: ADC conversion triggered by PMD1 is finished
                DCD     INTRMCRX_IRQHandler       ; 19: Remote Controller reception interrupt
                DCD     INTTB00_IRQHandler        ; 20: 16bit TMRB0 compare match detection 0/ Over flow
                DCD     INTTB01_IRQHandler        ; 21: 16bit TMRB0 compare match detection 1
                DCD     INTTB10_IRQHandler        ; 22: 16bit TMRB1 compare match detection 0/ Over flow
                DCD     INTTB11_IRQHandler        ; 23: 16bit TMRB1 compare match detection 1
                DCD     INTTB40_IRQHandler        ; 24: 16bit TMRB4 compare match detection 0/ Over flow
                DCD     INTTB41_IRQHandler        ; 25: 16bit TMRB4 compare match detection 1
                DCD     INTTB50_IRQHandler        ; 26: 16bit TMRB5 compare match detection 0/ Over flow
                DCD     INTTB51_IRQHandler        ; 27: 16bit TMRB5 compare match detection 1
                DCD     INTPMD0_IRQHandler        ; 28: PMD0 PWM interrupt (MPT0)
                DCD     INTPMD1_IRQHandler        ; 29: PMD1 PWM interrupt (MPT1)
                DCD     INTCAP00_IRQHandler       ; 30: 16bit TMRB0 input capture 0
                DCD     INTCAP01_IRQHandler       ; 31: 16bit TMRB0 input capture 1
                DCD     INTCAP10_IRQHandler       ; 32: 16bit TMRB1 input capture 0
                DCD     INTCAP11_IRQHandler       ; 33: 16bit TMRB1 input capture 1
                DCD     INTCAP40_IRQHandler       ; 34: 16bit TMRB4 input capture 0
                DCD     INTCAP41_IRQHandler       ; 35: 16bit TMRB4 input capture 1
                DCD     INTCAP50_IRQHandler       ; 36: 16bit TMRB5 input capture 0
                DCD     INTCAP51_IRQHandler       ; 37: 16bit TMRB5 input capture 1
                DCD     INT6_IRQHandler           ; 38: Interrupt Pin (PE6/TB3IN/INT6)
                DCD     INT7_IRQHandler           ; 39: Interrupt Pin (PE7/TB3OUT/INT7)
                DCD     INTRX2_IRQHandler         ; 40: Serial reception (channel.2)
                DCD     INTTX2_IRQHandler         ; 41: Serial transmit (channel.2)
                DCD     INTADCP0_IRQHandler       ; 42: ADC conversion monitoring function interrupt 0
                DCD     INTADCP1_IRQHandler       ; 43: ADC conversion monitoring function interrupt 1
                DCD     INTRX4_IRQHandler         ; 44: Serial reception (channel.4)
                DCD     INTTX4_IRQHandler         ; 45: Serial transmit (channel.4)
                DCD     INTTB20_IRQHandler        ; 46: 16bit TMRB2 compare match detection 0/ Over flow
                DCD     INTTB21_IRQHandler        ; 47: 16bit TMRB2 compare match detection 1
                DCD     INTTB30_IRQHandler        ; 48: 16bit TMRB3 compare match detection 0/ Over flow
                DCD     INTTB31_IRQHandler        ; 49: 16bit TMRB3 compare match detection 1
                DCD     INTCAP20_IRQHandler       ; 50: 16bit TMRB2 input capture 0
                DCD     INTCAP21_IRQHandler       ; 51: 16bit TMRB2 input capture 1
                DCD     INTCAP30_IRQHandler       ; 52: 16bit TMRB3 input capture 0
                DCD     INTCAP31_IRQHandler       ; 53: 16bit TMRB3 input capture 1
                DCD     INTADSFT_IRQHandler       ; 54: ADC conversion started by software is finished
                DCD     0                         ; 55: Reserved
                DCD     INTADTMR_IRQHandler       ; 56: ADC conversion triggered by timer is finished
                DCD     0                         ; 57: Reserved
                DCD     INT8_IRQHandler           ; 58: Interrupt Pin (PA7/TB4IN/INT8)
                DCD     INT9_IRQHandler           ; 59: Interrupt Pin (PD3/INT9)
                DCD     INTA_IRQHandler           ; 60: Interrupt Pin (PJ6/AIN6/INTA)
                DCD     INTB_IRQHandler           ; 61: Interrupt Pin (PJ7/AIN7/INTB)
                DCD     INTENC0_IRQHandler        ; 62: Encoder input0 interrupt
                DCD     INTENC1_IRQHandler        ; 63: Encoder input1 interrupt
                DCD     INTRX3_IRQHandler         ; 64: Serial reception (channel.3)
                DCD     INTTX3_IRQHandler         ; 65: Serial transmit (channel.3)
                DCD     INTTB60_IRQHandler        ; 66: 16bit TMRB6 compare match detection 0 / Over flow
                DCD     INTTB61_IRQHandler        ; 67: 16bit TMRB6 compare match detection 1
                DCD     INTTB70_IRQHandler        ; 68: 16bit TMRB7 compare match detection 0 / Over flow
                DCD     INTTB71_IRQHandler        ; 69: 16bit TMRB7 compare match detection 1
                DCD     INTCAP60_IRQHandler       ; 70: 16bit TMRB6 input capture 0
                DCD     INTCAP61_IRQHandler       ; 71: 16bit TMRB6 input capture 1
                DCD     INTCAP70_IRQHandler       ; 72: 16bit TMRB7 input capture 0
                DCD     INTCAP71_IRQHandler       ; 73: 16bit TMRB7 input capture 1
                DCD     INTC_IRQHandler           ; 74: Interrupt Pin (PD0/ENCA0/TB5IN/INTC)
                DCD     INTD_IRQHandler           ; 75: Interrupt Pin (PD2/ENCZ0/INTD)
                DCD     INTE_IRQHandler           ; 76: Interrupt Pin (PN7/MT2IN/INTE)
                DCD     INTF_IRQHandler           ; 77: Interrupt Pin (PL2/INTF)
                DCD     INTDMACERR_IRQHandler     ; 78: DMA transfer error
                DCD     INTDMACTC_IRQHandler      ; 79: DMA end of transfer
                DCD     INTMTTB00_IRQHandler      ; 80: 16-bit MPT0 IGBT period/ compare match detection 0/Over flow
                DCD     INTMTTB01_IRQHandler      ; 81: 16-bit MPT0 IGBT trigger/ compare match detection 1
                DCD     INTMTTB10_IRQHandler      ; 82: 16-bit MPT1 IGBT period/ compare match detection 0/Over flow
                DCD     INTMTTB11_IRQHandler      ; 83: 16-bit MPT1 IGBT trigger/ compare match detection 1
                DCD     INTMTTB20_IRQHandler      ; 84: 16-bit MPT2 IGBT period/ compare match detection 0/Over flow
                DCD     INTMTTB21_IRQHandler      ; 85: 16-bit MPT2 IGBT trigger/ compare match detection 1
                DCD     INTMTCAP00_IRQHandler     ; 86: 16-bit MPT0 input capture 0
                DCD     INTMTCAP01_IRQHandler     ; 87: 16-bit MPT0 input capture 1
                DCD     INTMTCAP10_IRQHandler     ; 88: 16-bit MPT1 input capture 0
                DCD     INTMTCAP11_IRQHandler     ; 89: 16-bit MPT1 input capture 1
                DCD     INTMTCAP20_IRQHandler     ; 90: 16-bit MPT2 input capture 0
                DCD     INTMTCAP21_IRQHandler     ; 91: 16-bit MPT2 input capture 1
                DCD     INTMTEMG0_IRQHandler      ; 92: 16-bit MPT0 IGBT EMG interrupt
                DCD     INTMTEMG1_IRQHandler      ; 93: 16-bit MPT1 IGBT EMG interrupt
                DCD     INTMTEMG2_IRQHandler      ; 94: 16-bit MPT2 IGBT EMG interrupt

                THUMB
; Dummy Exception Handlers (infinite loops which can be modified)

                PUBWEAK Reset_Handler
                SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK NMI_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
                B       HardFault_Handler

                PUBWEAK MemManage_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
                B       MemManage_Handler

                PUBWEAK BusFault_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
                B       BusFault_Handler

                PUBWEAK UsageFault_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
                B       UsageFault_Handler

                PUBWEAK SVC_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
                B       SVC_Handler

                PUBWEAK DebugMon_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
                B       DebugMon_Handler

                PUBWEAK PendSV_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
                B       SysTick_Handler

                PUBWEAK INT0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT0_IRQHandler
                B       INT0_IRQHandler

                PUBWEAK INT1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT1_IRQHandler
                B       INT1_IRQHandler

                PUBWEAK INT2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT2_IRQHandler
                B       INT2_IRQHandler

                PUBWEAK INT3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT3_IRQHandler
                B       INT3_IRQHandler

                PUBWEAK INT4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT4_IRQHandler
                B       INT4_IRQHandler

                PUBWEAK INT5_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT5_IRQHandler
                B       INT5_IRQHandler

                PUBWEAK INTRX0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX0_IRQHandler
                B       INTRX0_IRQHandler

                PUBWEAK INTTX0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX0_IRQHandler
                B       INTTX0_IRQHandler

                PUBWEAK INTRX1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX1_IRQHandler
                B       INTRX1_IRQHandler

                PUBWEAK INTTX1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX1_IRQHandler
                B       INTTX1_IRQHandler

                PUBWEAK INTSSP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSSP0_IRQHandler
                B       INTSSP0_IRQHandler

                PUBWEAK INTSSP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSSP1_IRQHandler
                B       INTSSP1_IRQHandler

                PUBWEAK INTEMG0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEMG0_IRQHandler
                B       INTEMG0_IRQHandler

                PUBWEAK INTEMG1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEMG1_IRQHandler
                B       INTEMG1_IRQHandler

                PUBWEAK INTSBI0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSBI0_IRQHandler
                B       INTSBI0_IRQHandler

                PUBWEAK INTSBI1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSBI1_IRQHandler
                B       INTSBI1_IRQHandler

                PUBWEAK INTADPD0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADPD0_IRQHandler
                B       INTADPD0_IRQHandler

                PUBWEAK INTRTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRTC_IRQHandler
                B       INTRTC_IRQHandler

                PUBWEAK INTADPD1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADPD1_IRQHandler
                B       INTADPD1_IRQHandler

                PUBWEAK INTRMCRX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRMCRX_IRQHandler
                B       INTRMCRX_IRQHandler

                PUBWEAK INTTB00_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB00_IRQHandler
                B       INTTB00_IRQHandler

                PUBWEAK INTTB01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB01_IRQHandler
                B       INTTB01_IRQHandler

                PUBWEAK INTTB10_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB10_IRQHandler
                B       INTTB10_IRQHandler

                PUBWEAK INTTB11_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB11_IRQHandler
                B       INTTB11_IRQHandler

                PUBWEAK INTTB40_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB40_IRQHandler
                B       INTTB40_IRQHandler

                PUBWEAK INTTB41_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB41_IRQHandler
                B       INTTB41_IRQHandler

                PUBWEAK INTTB50_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB50_IRQHandler
                B       INTTB50_IRQHandler

                PUBWEAK INTTB51_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB51_IRQHandler
                B       INTTB51_IRQHandler

                PUBWEAK INTPMD0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPMD0_IRQHandler
                B       INTPMD0_IRQHandler

                PUBWEAK INTPMD1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPMD1_IRQHandler
                B       INTPMD1_IRQHandler

                PUBWEAK INTCAP00_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP00_IRQHandler
                B       INTCAP00_IRQHandler

                PUBWEAK INTCAP01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP01_IRQHandler
                B       INTCAP01_IRQHandler

                PUBWEAK INTCAP10_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP10_IRQHandler
                B       INTCAP10_IRQHandler

                PUBWEAK INTCAP11_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP11_IRQHandler
                B       INTCAP11_IRQHandler

                PUBWEAK INTCAP40_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP40_IRQHandler
                B       INTCAP40_IRQHandler

                PUBWEAK INTCAP41_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP41_IRQHandler
                B       INTCAP41_IRQHandler

                PUBWEAK INTCAP50_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP50_IRQHandler
                B       INTCAP50_IRQHandler

                PUBWEAK INTCAP51_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP51_IRQHandler
                B       INTCAP51_IRQHandler

                PUBWEAK INT6_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT6_IRQHandler
                B       INT6_IRQHandler

                PUBWEAK INT7_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT7_IRQHandler
                B       INT7_IRQHandler

                PUBWEAK INTRX2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX2_IRQHandler
                B       INTRX2_IRQHandler

                PUBWEAK INTTX2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX2_IRQHandler
                B       INTTX2_IRQHandler

                PUBWEAK INTADCP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCP0_IRQHandler
                B       INTADCP0_IRQHandler

                PUBWEAK INTADCP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCP1_IRQHandler
                B       INTADCP1_IRQHandler

                PUBWEAK INTRX4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX4_IRQHandler
                B       INTRX4_IRQHandler

                PUBWEAK INTTX4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX4_IRQHandler
                B       INTTX4_IRQHandler

                PUBWEAK INTTB20_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB20_IRQHandler
                B       INTTB20_IRQHandler

                PUBWEAK INTTB21_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB21_IRQHandler
                B       INTTB21_IRQHandler

                PUBWEAK INTTB30_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB30_IRQHandler
                B       INTTB30_IRQHandler

                PUBWEAK INTTB31_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB31_IRQHandler
                B       INTTB31_IRQHandler

                PUBWEAK INTCAP20_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP20_IRQHandler
                B       INTCAP20_IRQHandler

                PUBWEAK INTCAP21_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP21_IRQHandler
                B       INTCAP21_IRQHandler

                PUBWEAK INTCAP30_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP30_IRQHandler
                B       INTCAP30_IRQHandler

                PUBWEAK INTCAP31_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP31_IRQHandler
                B       INTCAP31_IRQHandler

                PUBWEAK INTADSFT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADSFT_IRQHandler
                B       INTADSFT_IRQHandler

                PUBWEAK INTADTMR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADTMR_IRQHandler
                B       INTADTMR_IRQHandler

                PUBWEAK INT8_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT8_IRQHandler
                B       INT8_IRQHandler

                 PUBWEAK INT9_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT9_IRQHandler
                B       INT9_IRQHandler

                 PUBWEAK INTA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTA_IRQHandler
                B       INTA_IRQHandler

                 PUBWEAK INTB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTB_IRQHandler
                B       INTB_IRQHandler

                 PUBWEAK INTENC0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC0_IRQHandler
                B       INTENC0_IRQHandler

                 PUBWEAK INTENC1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC1_IRQHandler
                B       INTENC1_IRQHandler

                 PUBWEAK INTRX3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX3_IRQHandler
                B       INTRX3_IRQHandler

                 PUBWEAK INTTX3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX3_IRQHandler
                B       INTTX3_IRQHandler

                 PUBWEAK INTTB60_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB60_IRQHandler
                B       INTTB60_IRQHandler

                 PUBWEAK INTTB61_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB61_IRQHandler
                B       INTTB61_IRQHandler

                 PUBWEAK INTTB70_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB70_IRQHandler
                B       INTTB70_IRQHandler

                 PUBWEAK INTTB71_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB71_IRQHandler
                B       INTTB71_IRQHandler

                 PUBWEAK INTCAP60_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP60_IRQHandler
                B       INTCAP60_IRQHandler

                 PUBWEAK INTCAP61_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP61_IRQHandler
                B       INTCAP61_IRQHandler

                 PUBWEAK INTCAP70_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP70_IRQHandler
                B       INTCAP70_IRQHandler

                 PUBWEAK INTCAP71_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP71_IRQHandler
                B       INTCAP71_IRQHandler

                 PUBWEAK INTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTC_IRQHandler
                B       INTC_IRQHandler

                 PUBWEAK INTD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTD_IRQHandler
                B       INTD_IRQHandler

                 PUBWEAK INTE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTE_IRQHandler
                B       INTE_IRQHandler

                 PUBWEAK INTF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTF_IRQHandler
                B       INTF_IRQHandler

                 PUBWEAK INTDMACERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMACERR_IRQHandler
                B       INTDMACERR_IRQHandler

                 PUBWEAK INTDMACTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMACTC_IRQHandler
                B       INTDMACTC_IRQHandler

                 PUBWEAK INTMTTB00_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTTB00_IRQHandler
                B       INTMTTB00_IRQHandler

                 PUBWEAK INTMTTB01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTTB01_IRQHandler
                B       INTMTTB01_IRQHandler

                 PUBWEAK INTMTTB10_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTTB10_IRQHandler
                B       INTMTTB10_IRQHandler

                 PUBWEAK INTMTTB11_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTTB11_IRQHandler
                B       INTMTTB11_IRQHandler

                 PUBWEAK INTMTTB20_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTTB20_IRQHandler
                B       INTMTTB20_IRQHandler

                 PUBWEAK INTMTTB21_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTTB21_IRQHandler
                B       INTMTTB21_IRQHandler

                 PUBWEAK INTMTCAP00_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTCAP00_IRQHandler
                B       INTMTCAP00_IRQHandler

                 PUBWEAK INTMTCAP01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTCAP01_IRQHandler
                B       INTMTCAP01_IRQHandler

                 PUBWEAK INTMTCAP10_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTCAP10_IRQHandler
                B       INTMTCAP10_IRQHandler

                 PUBWEAK INTMTCAP11_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTCAP11_IRQHandler
                B       INTMTCAP11_IRQHandler

                 PUBWEAK INTMTCAP20_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTCAP20_IRQHandler
                B       INTMTCAP20_IRQHandler

                 PUBWEAK INTMTCAP21_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTCAP21_IRQHandler
                B       INTMTCAP21_IRQHandler

                 PUBWEAK INTMTEMG0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTEMG0_IRQHandler
                B       INTMTEMG0_IRQHandler

                 PUBWEAK INTMTEMG1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTEMG1_IRQHandler
                B       INTMTEMG1_IRQHandler

                 PUBWEAK INTMTEMG2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMTEMG2_IRQHandler
                B       INTMTEMG2_IRQHandler

                END
