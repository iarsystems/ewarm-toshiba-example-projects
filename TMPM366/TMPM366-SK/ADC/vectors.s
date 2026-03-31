/**************************************************
 *
 * Toshiba TMPM366 vector table
 *
 * Copyright 2011 IAR Systems. All rights reserved.
 *
 * $Revision: 503 $
 *
 **************************************************/
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
        DCD     INT0_IRQHandler           ; 0:  External Interrupt 0
        DCD     INT1_IRQHandler           ; 1:  External Interrupt 1
        DCD     INT2_IRQHandler           ; 2:  External Interrupt 2
        DCD     INT3_IRQHandler           ; 3:  External Interrupt 3
        DCD     INT4_IRQHandler           ; 4:  External Interrupt 4
        DCD     INT5_IRQHandler           ; 5:  External Interrupt 5
        DCD     INT6_IRQHandler           ; 6:  External Interrupt 6
        DCD     INT7_IRQHandler           ; 7:  External Interrupt 7
        DCD     INTRX0_IRQHandler         ; 8:  Serial reception (channel.0)
        DCD     INTTX0_IRQHandler         ; 9:  Serial transmission (channel.0)
        DCD     INTRX1_IRQHandler         ; 10: Serial reception (channel.1)
        DCD     INTTX1_IRQHandler         ; 11: Serial transmission (channel.1)
        DCD     INTUSBWKUP_IRQHandler     ; 12: USB Wake-up interrupt
        DCD     0                         ; Reserved
        DCD     INTSBI0_IRQHandler        ; 14: Serial Bus Interface 0 interrupt
        DCD     INTSBI1_IRQHandler        ; 15: Serial Bus Interface 1 interrupt
        DCD     INTADHP_IRQHandler        ; 16: Highest priority AD conversion complete interrupt
        DCD     INTAD_IRQHandler          ; 17: AD conversion complete interrupt
        DCD     INTADM0_IRQHandler        ; 18: AD conversion monitoring function interrupt 0
        DCD     INTADM1_IRQHandler        ; 19: AD conversion monitoring function interrupt 1
        DCD     INTTB0_IRQHandler         ; 20: 16bit TMRB0 match detection
        DCD     INTTB1_IRQHandler         ; 21: 16bit TMRB1 match detection
        DCD     INTTB2_IRQHandler         ; 22: 16bit TMRB2 match detection
        DCD     INTTB3_IRQHandler         ; 23: 16bit TMRB3 match detection
        DCD     INTTB4_IRQHandler         ; 24: 16bit TMRB4 match detection
        DCD     INTTB5_IRQHandler         ; 25: 16bit TMRB5 match detection
        DCD     INTTB6_IRQHandler         ; 26: 16bit TMRB6 match detection
        DCD     INTTB7_IRQHandler         ; 27: 16bit TMRB7 match detection
        DCD     INTTB8_IRQHandler         ; 28: 16bit TMRB8 match detection
        DCD     INTTB9_IRQHandler         ; 29: 16bit TMRB9 match detection
        DCD     INTUSB_IRQHandler         ; 30: USB interrupt
        DCD     INTSSP2_IRQHandler        ; 31: SPI serial interface 2
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     INTUSBPON_IRQHandler      ; 34: USB Power On connection detection interrupt
        DCD     INTUART_IRQHandler        ; 35: UART interrupt (UART channel.2)
        DCD     INTCAP00_IRQHandler       ; 36: 16bit TMRB input capture 00
        DCD     INTCAP01_IRQHandler       ; 37: 16bit TMRB input capture 01
        DCD     INTCAP10_IRQHandler       ; 38: 16bit TMRB input capture 10
        DCD     INTCAP11_IRQHandler       ; 39: 16bit TMRB input capture 11
        DCD     INTCAP20_IRQHandler       ; 40: 16bit TMRB input capture 20
        DCD     INTCAP21_IRQHandler       ; 41: 16bit TMRB input capture 21
        DCD     INTCAP30_IRQHandler       ; 42: 16bit TMRB input capture 30
        DCD     INTCAP31_IRQHandler       ; 43: 16bit TMRB input capture 31
        DCD     INTCAP40_IRQHandler       ; 44: 16bit TMRB input capture 40
        DCD     INTCAP41_IRQHandler       ; 45: 16bit TMRB input capture 41
        DCD     INTCAP50_IRQHandler       ; 46: 16bit TMRB input capture 50
        DCD     INTCAP51_IRQHandler       ; 47: 16bit TMRB input capture 51
        DCD     INTCAP60_IRQHandler       ; 48: 16bit TMRB input capture 60
        DCD     INTCAP61_IRQHandler       ; 49: 16bit TMRB input capture 61
        DCD     INTCAP70_IRQHandler       ; 50: 16bit TMRB input capture 70
        DCD     INTCAP71_IRQHandler       ; 51: 16bit TMRB input capture 71
        DCD     INTCAP80_IRQHandler       ; 52: 16bit TMRB input capture 80
        DCD     INTCAP81_IRQHandler       ; 53: 16bit TMRB input capture 81
        DCD     INTCAP90_IRQHandler       ; 54: 16bit TMRB input capture 90
        DCD     INTCAP91_IRQHandler       ; 55: 16bit TMRB input capture 91
        DCD     INT8_IRQHandler           ; 56: External Interrupt 8
        DCD     INT9_IRQHandler           ; 57: External Interrupt 9
        DCD     INTSSP1_IRQHandler        ; 58: SPI serial interface 1
        DCD     INTSSP0_IRQHandler        ; 59: SPI serial interface 0
        DCD     INTDMAC0TC_IRQHandler     ; 60: DMAC0 transfer complete Interrupt
        DCD     INTDMAC1TC_IRQHandler     ; 61: DMAC1 transfer complete Interrupt
        DCD     INTDMAC0ERR_IRQHandler    ; 62: DMAC0 transfer error Interrupt
        DCD     INTDMAC1ERR_IRQHandler    ; 63: DMAC0 transfer error Interrupt

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
      PUBWEAK INT6_IRQHandler
      PUBWEAK INT7_IRQHandler
      PUBWEAK INTRX0_IRQHandler
      PUBWEAK INTTX0_IRQHandler
      PUBWEAK INTRX1_IRQHandler
      PUBWEAK INTTX1_IRQHandler
      PUBWEAK INTUSBWKUP_IRQHandler
      PUBWEAK INTSBI0_IRQHandler
      PUBWEAK INTSBI1_IRQHandler
      PUBWEAK INTADHP_IRQHandler
      PUBWEAK INTAD_IRQHandler
      PUBWEAK INTADM0_IRQHandler
      PUBWEAK INTADM1_IRQHandler
      PUBWEAK INTTB0_IRQHandler
      PUBWEAK INTTB1_IRQHandler
      PUBWEAK INTTB2_IRQHandler
      PUBWEAK INTTB3_IRQHandler
      PUBWEAK INTTB4_IRQHandler
      PUBWEAK INTTB5_IRQHandler
      PUBWEAK INTTB6_IRQHandler
      PUBWEAK INTTB7_IRQHandler
      PUBWEAK INTTB8_IRQHandler
      PUBWEAK INTTB9_IRQHandler
      PUBWEAK INTUSB_IRQHandler
      PUBWEAK INTSSP2_IRQHandler
      PUBWEAK INTUSBPON_IRQHandler
      PUBWEAK INTUART_IRQHandler
      PUBWEAK INTCAP00_IRQHandler
      PUBWEAK INTCAP01_IRQHandler
      PUBWEAK INTCAP10_IRQHandler
      PUBWEAK INTCAP11_IRQHandler
      PUBWEAK INTCAP20_IRQHandler
      PUBWEAK INTCAP21_IRQHandler
      PUBWEAK INTCAP30_IRQHandler
      PUBWEAK INTCAP31_IRQHandler
      PUBWEAK INTCAP40_IRQHandler
      PUBWEAK INTCAP41_IRQHandler
      PUBWEAK INTCAP50_IRQHandler
      PUBWEAK INTCAP51_IRQHandler
      PUBWEAK INTCAP60_IRQHandler
      PUBWEAK INTCAP61_IRQHandler
      PUBWEAK INTCAP70_IRQHandler
      PUBWEAK INTCAP71_IRQHandler
      PUBWEAK INTCAP80_IRQHandler
      PUBWEAK INTCAP81_IRQHandler
      PUBWEAK INTCAP90_IRQHandler
      PUBWEAK INTCAP91_IRQHandler
      PUBWEAK INT8_IRQHandler
      PUBWEAK INT9_IRQHandler
      PUBWEAK INTSSP1_IRQHandler
      PUBWEAK INTSSP0_IRQHandler
      PUBWEAK INTDMAC0TC_IRQHandler
      PUBWEAK INTDMAC1TC_IRQHandler
      PUBWEAK INTDMAC0ERR_IRQHandler
      PUBWEAK INTDMAC1ERR_IRQHandler

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
INTRX0_IRQHandler
INTTX0_IRQHandler
INTRX1_IRQHandler
INTTX1_IRQHandler
INTUSBWKUP_IRQHandler
INTSBI0_IRQHandler
INTSBI1_IRQHandler
INTADHP_IRQHandler
INTAD_IRQHandler
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
INTUSB_IRQHandler
INTSSP2_IRQHandler
INTUSBPON_IRQHandler
INTUART_IRQHandler
INTCAP00_IRQHandler
INTCAP01_IRQHandler
INTCAP10_IRQHandler
INTCAP11_IRQHandler
INTCAP20_IRQHandler
INTCAP21_IRQHandler
INTCAP30_IRQHandler
INTCAP31_IRQHandler
INTCAP40_IRQHandler
INTCAP41_IRQHandler
INTCAP50_IRQHandler
INTCAP51_IRQHandler
INTCAP60_IRQHandler
INTCAP61_IRQHandler
INTCAP70_IRQHandler
INTCAP71_IRQHandler
INTCAP80_IRQHandler
INTCAP81_IRQHandler
INTCAP90_IRQHandler
INTCAP91_IRQHandler
INT8_IRQHandler
INT9_IRQHandler
INTSSP1_IRQHandler
INTSSP0_IRQHandler
INTDMAC0TC_IRQHandler
INTDMAC1TC_IRQHandler
INTDMAC0ERR_IRQHandler
INTDMAC1ERR_IRQHandler
Default_Handler
        B Default_Handler
        END
