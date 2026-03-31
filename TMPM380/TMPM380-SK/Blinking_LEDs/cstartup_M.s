/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2009 IAR Systems. All rights reserved.
 *
 * $Revision: 503 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:ROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)               ; Top of Stack
        DCD     __iar_program_start       ; Reset Handler
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
        DCD     INT0_IRQHandler           ; 0:  Interrupt pin (PJ0)
        DCD     INT1_IRQHandler           ; 1:  Interrupt pin (PJ1)
        DCD     INT2_IRQHandler           ; 2:  Interrupt pin (PJ2)
        DCD     INT3_IRQHandler           ; 3:  Interrupt pin (PJ3)
        DCD     INT4_IRQHandler           ; 4:  Interrupt pin (PJ4)
        DCD     INT5_IRQHandler           ; 5:  Interrupt pin (PJ5)
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
        DCD     INTADTMR_IRQHandler       ; 56: ADC conversion triggered by timer is finished
        DCD     INT8_IRQHandler           ; 58: Interrupt Pin (PA7/TB4IN/INT8)
        DCD     INT9_IRQHandler           ; 59:  Interrupt Pin (PD3/INT9)
        DCD     INTA_IRQHandler           ; 60:  Interrupt Pin (PJ6/AIN6/INTA)
        DCD     INTB_IRQHandler           ; 61:  Interrupt Pin (PJ7/AIN7/INTB)
        DCD     INTENC0_IRQHandler        ; 62:  Encoder input0 interrupt
        DCD     INTENC1_IRQHandler        ; 63:  Encoder input1 interrupt
        DCD     INTRX3_IRQHandler         ; 64:  Serial reception (channel.3)
        DCD     INTTX3_IRQHandler         ; 65:  Serial transmit (channel.3)
        DCD     INTTB60_IRQHandler        ; 66:  16bit TMRB6 compare match detection 0 / Over flow
        DCD     INTTB61_IRQHandler        ; 67:  16bit TMRB6 compare match detection 1
        DCD     INTTB70_IRQHandler        ; 68:  16bit TMRB7 compare match detection 0 / Over flow
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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

      PUBWEAK NMI_Handler
      PUBWEAK HardFault_Handler
      PUBWEAK MemManage_Handler
      PUBWEAK BusFault_Handler
      PUBWEAK UsageFault_Handler
      PUBWEAK SVC_Handler
      PUBWEAK DebugMon_Handler
      PUBWEAK PendSV_Handler
      PUBWEAK SysTick_Handler
      PUBWEAK INT0_IRQHandler
      PUBWEAK INT1_IRQHandler
      PUBWEAK INT2_IRQHandler
      PUBWEAK INT3_IRQHandler
      PUBWEAK INT4_IRQHandler
      PUBWEAK INT5_IRQHandler
      PUBWEAK INTRX0_IRQHandler
      PUBWEAK INTTX0_IRQHandler
      PUBWEAK INTRX1_IRQHandler
      PUBWEAK INTTX1_IRQHandler
      PUBWEAK INTSSP0_IRQHandler
      PUBWEAK INTSSP1_IRQHandler
      PUBWEAK INTEMG0_IRQHandler
      PUBWEAK INTEMG1_IRQHandler
      PUBWEAK INTSBI0_IRQHandler
      PUBWEAK INTSBI1_IRQHandler
      PUBWEAK INTADPD0_IRQHandler
      PUBWEAK INTRTC_IRQHandler
      PUBWEAK INTADPD1_IRQHandler
      PUBWEAK INTRMCRX_IRQHandler
      PUBWEAK INTTB00_IRQHandler
      PUBWEAK INTTB01_IRQHandler
      PUBWEAK INTTB10_IRQHandler
      PUBWEAK INTTB11_IRQHandler
      PUBWEAK INTTB40_IRQHandler
      PUBWEAK INTTB41_IRQHandler
      PUBWEAK INTTB50_IRQHandler
      PUBWEAK INTTB51_IRQHandler
      PUBWEAK INTPMD0_IRQHandler
      PUBWEAK INTPMD1_IRQHandler
      PUBWEAK INTCAP00_IRQHandler
      PUBWEAK INTCAP01_IRQHandler
      PUBWEAK INTCAP10_IRQHandler
      PUBWEAK INTCAP11_IRQHandler
      PUBWEAK INTCAP40_IRQHandler
      PUBWEAK INTCAP41_IRQHandler
      PUBWEAK INTCAP50_IRQHandler
      PUBWEAK INTCAP51_IRQHandler
      PUBWEAK INT6_IRQHandler
      PUBWEAK INT7_IRQHandler
      PUBWEAK INTRX2_IRQHandler
      PUBWEAK INTTX2_IRQHandler
      PUBWEAK INTADCP0_IRQHandler
      PUBWEAK INTADCP1_IRQHandler
      PUBWEAK INTRX4_IRQHandler
      PUBWEAK INTTX4_IRQHandler
      PUBWEAK INTTB20_IRQHandler
      PUBWEAK INTTB21_IRQHandler
      PUBWEAK INTTB30_IRQHandler
      PUBWEAK INTTB31_IRQHandler
      PUBWEAK INTCAP20_IRQHandler
      PUBWEAK INTCAP21_IRQHandler
      PUBWEAK INTCAP30_IRQHandler
      PUBWEAK INTCAP31_IRQHandler
      PUBWEAK INTADSFT_IRQHandler
      PUBWEAK INTADTMR_IRQHandler
      PUBWEAK INT8_IRQHandler
      PUBWEAK INT9_IRQHandler
      PUBWEAK INTA_IRQHandler
      PUBWEAK INTB_IRQHandler
      PUBWEAK INTENC0_IRQHandler
      PUBWEAK INTENC1_IRQHandler
      PUBWEAK INTRX3_IRQHandler
      PUBWEAK INTTX3_IRQHandler
      PUBWEAK INTTB60_IRQHandler
      PUBWEAK INTTB61_IRQHandler
      PUBWEAK INTTB70_IRQHandler
      PUBWEAK INTTB71_IRQHandler
      PUBWEAK INTCAP60_IRQHandler
      PUBWEAK INTCAP61_IRQHandler
      PUBWEAK INTCAP70_IRQHandler
      PUBWEAK INTCAP71_IRQHandler
      PUBWEAK INTC_IRQHandler
      PUBWEAK INTD_IRQHandler
      PUBWEAK INTE_IRQHandler
      PUBWEAK INTF_IRQHandler
      PUBWEAK INTDMACERR_IRQHandler
      PUBWEAK INTDMACTC_IRQHandler
      PUBWEAK INTMTTB00_IRQHandler
      PUBWEAK INTMTTB01_IRQHandler
      PUBWEAK INTMTTB10_IRQHandler
      PUBWEAK INTMTTB11_IRQHandler
      PUBWEAK INTMTTB20_IRQHandler
      PUBWEAK INTMTTB21_IRQHandler
      PUBWEAK INTMTCAP00_IRQHandler
      PUBWEAK INTMTCAP01_IRQHandler
      PUBWEAK INTMTCAP10_IRQHandler
      PUBWEAK INTMTCAP11_IRQHandler
      PUBWEAK INTMTCAP20_IRQHandler
      PUBWEAK INTMTCAP21_IRQHandler
      PUBWEAK INTMTEMG0_IRQHandler
      PUBWEAK INTMTEMG1_IRQHandler
      PUBWEAK INTMTEMG2_IRQHandler

      SECTION .text:CODE:REORDER:NOROOT(1)
      THUMB
NMI_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler
INT0_IRQHandler
INT1_IRQHandler
INT2_IRQHandler
INT3_IRQHandler
INT4_IRQHandler
INT5_IRQHandler
INTRX0_IRQHandler
INTTX0_IRQHandler
INTRX1_IRQHandler
INTTX1_IRQHandler
INTSSP0_IRQHandler
INTSSP1_IRQHandler
INTEMG0_IRQHandler
INTEMG1_IRQHandler
INTSBI0_IRQHandler
INTSBI1_IRQHandler
INTADPD0_IRQHandler
INTRTC_IRQHandler
INTADPD1_IRQHandler
INTRMCRX_IRQHandler
INTTB00_IRQHandler
INTTB01_IRQHandler
INTTB10_IRQHandler
INTTB11_IRQHandler
INTTB40_IRQHandler
INTTB41_IRQHandler
INTTB50_IRQHandler
INTTB51_IRQHandler
INTPMD0_IRQHandler
INTPMD1_IRQHandler
INTCAP00_IRQHandler
INTCAP01_IRQHandler
INTCAP10_IRQHandler
INTCAP11_IRQHandler
INTCAP40_IRQHandler
INTCAP41_IRQHandler
INTCAP50_IRQHandler
INTCAP51_IRQHandler
INT6_IRQHandler
INT7_IRQHandler
INTRX2_IRQHandler
INTTX2_IRQHandler
INTADCP0_IRQHandler
INTADCP1_IRQHandler
INTRX4_IRQHandler
INTTX4_IRQHandler
INTTB20_IRQHandler
INTTB21_IRQHandler
INTTB30_IRQHandler
INTTB31_IRQHandler
INTCAP20_IRQHandler
INTCAP21_IRQHandler
INTCAP30_IRQHandler
INTCAP31_IRQHandler
INTADSFT_IRQHandler
INTADTMR_IRQHandler
INT8_IRQHandler
INT9_IRQHandler
INTA_IRQHandler
INTB_IRQHandler
INTENC0_IRQHandler
INTENC1_IRQHandler
INTRX3_IRQHandler
INTTX3_IRQHandler
INTTB60_IRQHandler
INTTB61_IRQHandler
INTTB70_IRQHandler
INTTB71_IRQHandler
INTCAP60_IRQHandler
INTCAP61_IRQHandler
INTCAP70_IRQHandler
INTCAP71_IRQHandler
INTC_IRQHandler
INTD_IRQHandler
INTE_IRQHandler
INTF_IRQHandler
INTDMACERR_IRQHandler
INTDMACTC_IRQHandler
INTMTTB00_IRQHandler
INTMTTB01_IRQHandler
INTMTTB10_IRQHandler
INTMTTB11_IRQHandler
INTMTTB20_IRQHandler
INTMTTB21_IRQHandler
INTMTCAP00_IRQHandler
INTMTCAP01_IRQHandler
INTMTCAP10_IRQHandler
INTMTCAP11_IRQHandler
INTMTCAP20_IRQHandler
INTMTCAP21_IRQHandler
INTMTEMG0_IRQHandler
INTMTEMG1_IRQHandler
INTMTEMG2_IRQHandler
Default_Handler
        B Default_Handler
        END
