/**************************************************
 *
 * Toshiba TMPM364 vector table
 *
 * Copyright 2011 IAR Systems. All rights reserved.
 *
 **************************************************/
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM.
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
        DCD   INT0_IRQHandler             ; 0:  Interrupt pin 0
        DCD   INT1_IRQHandler             ; 1:  Interrupt pin 1
        DCD   INT2_IRQHandler             ; 2:  Interrupt pin 2
        DCD   INT3_IRQHandler             ; 3:  Interrupt pin 3
        DCD   INT4_IRQHandler             ; 4:  Interrupt pin 4
        DCD   INT5_IRQHandler             ; 5:  Interrupt pin 5
        DCD   INT6_IRQHandler             ; 6:  Interrupt pin 6
        DCD   INT7_IRQHandler             ; 7:  Interrupt pin 7
        DCD   INT8_IRQHandler             ; 8:  Interrupt pin 8
        DCD   INT9_IRQHandler             ; 9:  Interrupt pin 9
        DCD   INTA_IRQHandler             ; 10: Interrupt pin A
        DCD   INTB_IRQHandler             ; 11: Interrupt pin B
        DCD   INTC_IRQHandler             ; 12: Interrupt pin C
        DCD   INTD_IRQHandler             ; 13: Interrupt pin D
        DCD   0                           ; 14: Reserved
        DCD   0                           ; 15: Reserved
        DCD   INTRX0_IRQHandler           ; 16: Serial reception (channel.0)
        DCD   INTTX0_IRQHandler           ; 17: Serial transmission (channel.0)
        DCD   INTRX1_IRQHandler           ; 18: Serial reception (channel.1)
        DCD   INTTX1_IRQHandler           ; 19: Serial transmission (channel.1)
        DCD   INTRX2_IRQHandler           ; 20: Serial reception (channel.2)
        DCD   INTTX2_IRQHandler           ; 21: Serial transmission (channel.2)
        DCD   INTRX3_IRQHandler           ; 22: Serial reception (channel.3)
        DCD   INTTX3_IRQHandler           ; 23: Serial transmission (channel.3)
        DCD   INTRX4_IRQHandler           ; 24: Serial reception (channel.4)
        DCD   INTTX4_IRQHandler           ; 25: Serial transmission (channel.4)
        DCD   INTSBI0_IRQHandler          ; 26: Serial bus interface (channel.0)
        DCD   INTSBI1_IRQHandler          ; 27: Serial bus interface (channel.1)
        DCD   INTCECRX_IRQHandler         ; 28: CEC reception
        DCD   INTCECTX_IRQHandler         ; 29: CEC transmission
        DCD   INTRMCRX0_IRQHandler        ; 30: Remote control signal reception (channel.0)
        DCD   INTRMCRX1_IRQHandler        ; 31: Remote control signal reception (channel.1)
        DCD   INTRTC_IRQHandler           ; 32: Real time clock timer
        DCD   INTKWUP_IRQHandler          ; 33: Key on wake up
        DCD   INTSBI2_IRQHandler          ; 34: Serial bus interface (channel.2)
        DCD   INTSBI3_IRQHandler          ; 35: Serial bus interface (channel.3)
        DCD   INTSBI4_IRQHandler          ; 36: Serial bus interface (channel.4)
        DCD   INTADHP_IRQHandler          ; 37: Highest priority AD conversion complete interrupt
        DCD   INTADM0_IRQHandler          ; 38: AD conversion monitoring function interrupt 0
        DCD   INTADM1_IRQHandler          ; 39: AD conversion monitoring function interrupt 1
        DCD   INTTB0_IRQHandler           ; 40: 16bit TMRB match detection 0
        DCD   INTTB1_IRQHandler           ; 41: 16bit TMRB match detection 1
        DCD   INTTB2_IRQHandler           ; 42: 16bit TMRB match detection 2
        DCD   INTTB3_IRQHandler           ; 43: 16bit TMRB match detection 3
        DCD   INTTB4_IRQHandler           ; 44: 16bit TMRB match detection 4
        DCD   INTTB5_IRQHandler           ; 45: 16bit TMRB match detection 5
        DCD   INTTB6_IRQHandler           ; 46: 16bit TMRB match detection 6
        DCD   INTTB7_IRQHandler           ; 47: 16bit TMRB match detection 7
        DCD   INTTB8_IRQHandler           ; 48: 16bit TMRB match detection 8
        DCD   INTTB9_IRQHandler           ; 49: 16bit TMRB match detection 9
        DCD   INTTBA_IRQHandler           ; 50: 16bit TMRB match detection A
        DCD   INTTBB_IRQHandler           ; 51: 16bit TMRB match detection B
        DCD   INTTBC_IRQHandler           ; 52: 16bit TMRB match detection C
        DCD   INTTBD_IRQHandler           ; 53: 16bit TMRB match detection D
        DCD   INTTBE_IRQHandler           ; 54: 16bit TMRB match detection E
        DCD   INTTBF_IRQHandler           ; 55: 16bit TMRB match detection F
        DCD   INTUSB_IRQHandler           ; 56: USB
        DCD   INTCANSTA_IRQHandler        ; 57: CAN STATUS
        DCD   INTAD_IRQHandler            ; 58: A/D conversion completion
        DCD   INTSSP_IRQHandler           ; 59: Synchronous Serial Port
        DCD   INTRX5_IRQHandler           ; 60: Serial reception (channel.5)
        DCD   INTTX5_IRQHandler           ; 61: Serial transmission (channel.5)
        DCD   INTRX6_IRQHandler           ; 62: Serial reception (channel.6)
        DCD   INTTX6_IRQHandler           ; 63: Serial transmission (channel.6)
        DCD   INTRX7_IRQHandler           ; 64: Serial reception (channel.7)
        DCD   INTTX7_IRQHandler           ; 65: Serial transmission (channel.7)
        DCD   INTRX8_IRQHandler           ; 66: Serial reception (channel.8)
        DCD   INTTX8_IRQHandler           ; 67: Serial transmission (channel.8)
        DCD   INTRX9_IRQHandler           ; 68: Serial reception (channel.9)
        DCD   INTTX9_IRQHandler           ; 69: Serial transmission (channel.9)
        DCD   INTRX10_IRQHandler          ; 70: Serial reception (channel.10)
        DCD   INTTX10_IRQHandler          ; 71: Serial transmission (channel.10)
        DCD   INTRX11_IRQHandler          ; 72: Serial reception (channel.11)
        DCD   INTTX11_IRQHandler          ; 73: Serial transmission (channel.11)
        DCD   INTCAP10_IRQHandler         ; 74: 16bit TMRB input capture 10
        DCD   INTCAP11_IRQHandler         ; 75: 16bit TMRB input capture 11
        DCD   INTCAP20_IRQHandler         ; 76: 16bit TMRB input capture 20
        DCD   INTCAP21_IRQHandler         ; 77: 16bit TMRB input capture 21
        DCD   INTCANRX_IRQHandler         ; 78: CAN RX
        DCD   INTCANTX_IRQHandler         ; 79: CAN TX
        DCD   INTCAP50_IRQHandler         ; 80: 16bit TMRB input capture 50
        DCD   INTCAP51_IRQHandler         ; 81: 16bit TMRB input capture 51
        DCD   INTCAP60_IRQHandler         ; 82: 16bit TMRB input capture 60
        DCD   INTCAP61_IRQHandler         ; 83: 16bit TMRB input capture 61
        DCD   INTCAP70_IRQHandler         ; 84: 16bit TMRB input capture 70
        DCD   INTCAP71_IRQHandler         ; 85: 16bit TMRB input capture 71
        DCD   INTCAP90_IRQHandler         ; 86: 16bit TMRB input capture 90
        DCD   INTCAP91_IRQHandler         ; 87: 16bit TMRB input capture 91
        DCD   INTCAPA0_IRQHandler         ; 88: 16bit TMRB input capture A0
        DCD   INTCAPA1_IRQHandler         ; 89: 16bit TMRB input capture A1
        DCD   INTCAPB0_IRQHandler         ; 90: 16bit TMRB input capture B0
        DCD   INTCAPB1_IRQHandler         ; 91: 16bit TMRB input capture B1
        DCD   INTCAPD0_IRQHandler         ; 92: 16bit TMRB input capture D0
        DCD   INTCAPD1_IRQHandler         ; 93: 16bit TMRB input capture D1
        DCD   INTCAPE0_IRQHandler         ; 94: 16bit TMRB input capture E0
        DCD   INTCAPE1_IRQHandler         ; 95: 16bit TMRB input capture E1
        DCD   INTCAPF0_IRQHandler         ; 96: 16bit TMRB input capture F0
        DCD   INTCAPF1_IRQHandler         ; 97: 16bit TMRB input capture F1
        DCD   INTDMACERR_IRQHandler       ; 98: DMA transmission error
        DCD   INTDMACTC0_IRQHandler       ; 99: DMA transmission completion

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

      PUBWEAK INT0_IRQHandler         ; 0:  Interrupt pin 0
      PUBWEAK INT1_IRQHandler         ; 1:  Interrupt pin 1
      PUBWEAK INT2_IRQHandler         ; 2:  Interrupt pin 2
      PUBWEAK INT3_IRQHandler         ; 3:  Interrupt pin 3
      PUBWEAK INT4_IRQHandler         ; 4:  Interrupt pin 4
      PUBWEAK INT5_IRQHandler         ; 5:  Interrupt pin 5
      PUBWEAK INT6_IRQHandler         ; 6:  Interrupt pin 6
      PUBWEAK INT7_IRQHandler         ; 7:  Interrupt pin 7
      PUBWEAK INT8_IRQHandler         ; 8:  Interrupt pin 8
      PUBWEAK INT9_IRQHandler         ; 9:  Interrupt pin 9
      PUBWEAK INTA_IRQHandler         ; 10: Interrupt pin A
      PUBWEAK INTB_IRQHandler         ; 11: Interrupt pin B
      PUBWEAK INTC_IRQHandler         ; 12: Interrupt pin C
      PUBWEAK INTD_IRQHandler         ; 13: Interrupt pin D
      PUBWEAK INTRX0_IRQHandler       ; 16: Serial reception (channel.0)
      PUBWEAK INTTX0_IRQHandler       ; 17: Serial transmission (channel.0)
      PUBWEAK INTRX1_IRQHandler       ; 18: Serial reception (channel.1)
      PUBWEAK INTTX1_IRQHandler       ; 19: Serial transmission (channel.1)
      PUBWEAK INTRX2_IRQHandler       ; 20: Serial reception (channel.2)
      PUBWEAK INTTX2_IRQHandler       ; 21: Serial transmission (channel.2)
      PUBWEAK INTRX3_IRQHandler       ; 22: Serial reception (channel.3)
      PUBWEAK INTTX3_IRQHandler       ; 23: Serial transmission (channel.3)
      PUBWEAK INTRX4_IRQHandler       ; 24: Serial reception (channel.4)
      PUBWEAK INTTX4_IRQHandler       ; 25: Serial transmission (channel.4)
      PUBWEAK INTSBI0_IRQHandler      ; 26: Serial bus interface (channel.0)
      PUBWEAK INTSBI1_IRQHandler      ; 27: Serial bus interface (channel.1)
      PUBWEAK INTCECRX_IRQHandler     ; 28: CEC reception
      PUBWEAK INTCECTX_IRQHandler     ; 29: CEC transmission
      PUBWEAK INTRMCRX0_IRQHandler    ; 30: Remote control signal reception (channel.0)
      PUBWEAK INTRMCRX1_IRQHandler    ; 31: Remote control signal reception (channel.1)
      PUBWEAK INTRTC_IRQHandler       ; 32: Real time clock timer
      PUBWEAK INTKWUP_IRQHandler      ; 33: Key on wake up
      PUBWEAK INTSBI2_IRQHandler      ; 34: Serial bus interface (channel.2)
      PUBWEAK INTSBI3_IRQHandler      ; 35: Serial bus interface (channel.3)
      PUBWEAK INTSBI4_IRQHandler      ; 36: Serial bus interface (channel.4)
      PUBWEAK INTADHP_IRQHandler      ; 37: Highest priority AD conversion complete interrupt
      PUBWEAK INTADM0_IRQHandler      ; 38: AD conversion monitoring function interrupt 0
      PUBWEAK INTADM1_IRQHandler      ; 39: AD conversion monitoring function interrupt 1
      PUBWEAK INTTB0_IRQHandler       ; 40: 16bit TMRB match detection 0
      PUBWEAK INTTB1_IRQHandler       ; 41: 16bit TMRB match detection 1
      PUBWEAK INTTB2_IRQHandler       ; 42: 16bit TMRB match detection 2
      PUBWEAK INTTB3_IRQHandler       ; 43: 16bit TMRB match detection 3
      PUBWEAK INTTB4_IRQHandler       ; 44: 16bit TMRB match detection 4
      PUBWEAK INTTB5_IRQHandler       ; 45: 16bit TMRB match detection 5
      PUBWEAK INTTB6_IRQHandler       ; 46: 16bit TMRB match detection 6
      PUBWEAK INTTB7_IRQHandler       ; 47: 16bit TMRB match detection 7
      PUBWEAK INTTB8_IRQHandler       ; 48: 16bit TMRB match detection 8
      PUBWEAK INTTB9_IRQHandler       ; 49: 16bit TMRB match detection 9
      PUBWEAK INTTBA_IRQHandler       ; 50: 16bit TMRB match detection A
      PUBWEAK INTTBB_IRQHandler       ; 51: 16bit TMRB match detection B
      PUBWEAK INTTBC_IRQHandler       ; 52: 16bit TMRB match detection C
      PUBWEAK INTTBD_IRQHandler       ; 53: 16bit TMRB match detection D
      PUBWEAK INTTBE_IRQHandler       ; 54: 16bit TMRB match detection E
      PUBWEAK INTTBF_IRQHandler       ; 55: 16bit TMRB match detection F
      PUBWEAK INTUSB_IRQHandler       ; 56: USB
      PUBWEAK INTCANSTA_IRQHandler    ; 57: CAN STATUS
      PUBWEAK INTAD_IRQHandler        ; 58: A/D conversion completion
      PUBWEAK INTSSP_IRQHandler       ; 59: Synchronous Serial Port
      PUBWEAK INTRX5_IRQHandler       ; 60: Serial reception (channel.5)
      PUBWEAK INTTX5_IRQHandler       ; 61: Serial transmission (channel.5)
      PUBWEAK INTRX6_IRQHandler       ; 62: Serial reception (channel.6)
      PUBWEAK INTTX6_IRQHandler       ; 63: Serial transmission (channel.6)
      PUBWEAK INTRX7_IRQHandler       ; 64: Serial reception (channel.7)
      PUBWEAK INTTX7_IRQHandler       ; 65: Serial transmission (channel.7)
      PUBWEAK INTRX8_IRQHandler       ; 66: Serial reception (channel.8)
      PUBWEAK INTTX8_IRQHandler       ; 67: Serial transmission (channel.8)
      PUBWEAK INTRX9_IRQHandler       ; 68: Serial reception (channel.9)
      PUBWEAK INTTX9_IRQHandler       ; 69: Serial transmission (channel.9)
      PUBWEAK INTRX10_IRQHandler      ; 70: Serial reception (channel.10)
      PUBWEAK INTTX10_IRQHandler      ; 71: Serial transmission (channel.10)
      PUBWEAK INTRX11_IRQHandler      ; 72: Serial reception (channel.11)
      PUBWEAK INTTX11_IRQHandler      ; 73: Serial transmission (channel.11)
      PUBWEAK INTCAP10_IRQHandler     ; 74: 16bit TMRB input capture 10
      PUBWEAK INTCAP11_IRQHandler     ; 75: 16bit TMRB input capture 11
      PUBWEAK INTCAP20_IRQHandler     ; 76: 16bit TMRB input capture 20
      PUBWEAK INTCAP21_IRQHandler     ; 77: 16bit TMRB input capture 21
      PUBWEAK INTCANRX_IRQHandler     ; 78: CAN RX
      PUBWEAK INTCANTX_IRQHandler     ; 79: CAN TX
      PUBWEAK INTCAP50_IRQHandler     ; 80: 16bit TMRB input capture 50
      PUBWEAK INTCAP51_IRQHandler     ; 81: 16bit TMRB input capture 51
      PUBWEAK INTCAP60_IRQHandler     ; 82: 16bit TMRB input capture 60
      PUBWEAK INTCAP61_IRQHandler     ; 83: 16bit TMRB input capture 61
      PUBWEAK INTCAP70_IRQHandler     ; 84: 16bit TMRB input capture 70
      PUBWEAK INTCAP71_IRQHandler     ; 85: 16bit TMRB input capture 71
      PUBWEAK INTCAP90_IRQHandler     ; 86: 16bit TMRB input capture 90
      PUBWEAK INTCAP91_IRQHandler     ; 87: 16bit TMRB input capture 91
      PUBWEAK INTCAPA0_IRQHandler     ; 88: 16bit TMRB input capture A0
      PUBWEAK INTCAPA1_IRQHandler     ; 89: 16bit TMRB input capture A1
      PUBWEAK INTCAPB0_IRQHandler     ; 90: 16bit TMRB input capture B0
      PUBWEAK INTCAPB1_IRQHandler     ; 91: 16bit TMRB input capture B1
      PUBWEAK INTCAPD0_IRQHandler     ; 92: 16bit TMRB input capture D0
      PUBWEAK INTCAPD1_IRQHandler     ; 93: 16bit TMRB input capture D1
      PUBWEAK INTCAPE0_IRQHandler     ; 94: 16bit TMRB input capture E0
      PUBWEAK INTCAPE1_IRQHandler     ; 95: 16bit TMRB input capture E1
      PUBWEAK INTCAPF0_IRQHandler     ; 96: 16bit TMRB input capture F0
      PUBWEAK INTCAPF1_IRQHandler     ; 97: 16bit TMRB input capture F1
      PUBWEAK INTDMACERR_IRQHandler   ; 98: DMA transmission error
      PUBWEAK INTDMACTC0_IRQHandler   ; 99: DMA transmission completion

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
INT6_IRQHandler
INT7_IRQHandler
INT8_IRQHandler
INT9_IRQHandler
INTA_IRQHandler
INTB_IRQHandler
INTC_IRQHandler
INTD_IRQHandler
INTRX0_IRQHandler
INTTX0_IRQHandler
INTRX1_IRQHandler
INTTX1_IRQHandler
INTRX2_IRQHandler
INTTX2_IRQHandler
INTRX3_IRQHandler
INTTX3_IRQHandler
INTRX4_IRQHandler
INTTX4_IRQHandler
INTSBI0_IRQHandler
INTSBI1_IRQHandler
INTCECRX_IRQHandler
INTCECTX_IRQHandler
INTRMCRX0_IRQHandler
INTRMCRX1_IRQHandler
INTRTC_IRQHandler
INTKWUP_IRQHandler
INTSBI2_IRQHandler
INTSBI3_IRQHandler
INTSBI4_IRQHandler
INTADHP_IRQHandler
INTADM0_IRQHandler
INTADM1_IRQHandler
INTTB0_IRQHandler
INTTB1_IRQHandler
INTTB2_IRQHandler
INTTB3_IRQHandler
INTTB4_IRQHandler
INTTB5_IRQHandler
INTTB6_IRQHandler
INTTB7_IRQHandler
INTTB8_IRQHandler
INTTB9_IRQHandler
INTTBA_IRQHandler
INTTBB_IRQHandler
INTTBC_IRQHandler
INTTBD_IRQHandler
INTTBE_IRQHandler
INTTBF_IRQHandler
INTUSB_IRQHandler
INTCANSTA_IRQHandler
INTAD_IRQHandler
INTSSP_IRQHandler
INTRX5_IRQHandler
INTTX5_IRQHandler
INTRX6_IRQHandler
INTTX6_IRQHandler
INTRX7_IRQHandler
INTTX7_IRQHandler
INTRX8_IRQHandler
INTTX8_IRQHandler
INTRX9_IRQHandler
INTTX9_IRQHandler
INTRX10_IRQHandler
INTTX10_IRQHandler
INTRX11_IRQHandler
INTTX11_IRQHandler
INTCAP10_IRQHandler
INTCAP11_IRQHandler
INTCAP20_IRQHandler
INTCAP21_IRQHandler
INTCANRX_IRQHandler
INTCANTX_IRQHandler
INTCAP50_IRQHandler
INTCAP51_IRQHandler
INTCAP60_IRQHandler
INTCAP61_IRQHandler
INTCAP70_IRQHandler
INTCAP71_IRQHandler
INTCAP90_IRQHandler
INTCAP91_IRQHandler
INTCAPA0_IRQHandler
INTCAPA1_IRQHandler
INTCAPB0_IRQHandler
INTCAPB1_IRQHandler
INTCAPD0_IRQHandler
INTCAPD1_IRQHandler
INTCAPE0_IRQHandler
INTCAPE1_IRQHandler
INTCAPF0_IRQHandler
INTCAPF1_IRQHandler
INTDMACERR_IRQHandler
INTDMACTC0_IRQHandler
Default_Handler
        B Default_Handler
        END
