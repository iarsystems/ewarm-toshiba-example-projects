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
        DCD     EII_IRQHandler            ; External Interrupt
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     INT_5_IRQHandler          ; Interrupt Pin (PE4/TB2IN/15pin or 17pin)*/
        DCD     INT_RX0_IRQHandler        ; Serial reception (channel.0)
        DCD     INT_TX0_IRQHandler        ; Serial transmit (channel.0)
        DCD     INT_RX1_IRQHandler        ; Serial reception (channel.1)
        DCD     INT_TX1_IRQHandler        ; Serial transmit (channel.1)
        DCD     0                         ; Reserved
        DCD     INT_VCNB_IRQHandler       ; Vector Engine interrupt B
        DCD     0                         ; Reserved
        DCD     INT_EMG1_IRQHandler       ; PMD1 EMG interrupt
        DCD     0                         ; Reserved
        DCD     INT_OVV1_IRQHandler       ; PMD1 OVV interrupt
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     INT_ADBPDB_IRQHandler     ; ADCB conversion triggered by PMD1 is finished
        DCD     INT_TB00_IRQHandler       ; 16bit TMRB0 compare match detection 0/ Over flow
        DCD     INT_TB01_IRQHandler       ; 16bit TMRB0 compare match detection 1
        DCD     INT_TB10_IRQHandler       ; 16bit TMRB1 compare match detection 0/ Over flow
        DCD     INT_TB11_IRQHandler       ; 16bit TMRB1 compare match detection 1
        DCD     INT_TB40_IRQHandler       ; 16bit TMRB4 compare match detection 0/ Over flow
        DCD     INT_TB41_IRQHandler       ; 16bit TMRB4 compare match detection 1
        DCD     INT_TB50_IRQHandler       ; 16bit TMRB5 compare match detection 0/ Over flow
        DCD     INT_TB51_IRQHandler       ; 16bit TMRB5 compare match detection 1
        DCD     0                         ; Reserved
        DCD     INT_PMD1_IRQHandler       ; PMD1 PWM interrupt
        DCD     INT_CAP00_IRQHandler      ; 16bit TMRB0 input capture 0
        DCD     0                         ; Reserved
        DCD     INT_CAP10_IRQHandler      ; 16bit TMRB1 input capture 0
        DCD     0                         ; Reserved
        DCD     INT_CAP40_IRQHandler      ; 16bit TMRB4 input capture 0
        DCD     0                         ; Reserved
        DCD     INT_CAP50_IRQHandler      ; 16bit TMRB5 input capture 0
        DCD     0                         ; Reserved
        DCD     INT_6_IRQHandler          ; Interrupt Pin (PE6/TB3IN/17pin or 19pin)
        DCD     INT_7_IRQHandler          ; Interrupt Pin (PE7/TB3OUT/18pin or 20pin)
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     INT_ADBCPA_IRQHandler     ; ADB conversion monitoring function interrupt A
        DCD     0                         ; Reserved
        DCD     INT_ADBCPB_IRQHandler     ; ADB conversion monitoring function interrupt B
        DCD     INT_TB20_IRQHandler       ; 16bit TMRB2 compare match detection 0/ Over flow
        DCD     INT_TB21_IRQHandler       ; 16bit TMRB2 compare match detection 1
        DCD     INT_TB30_IRQHandler       ; 16bit TMRB3 compare match detection 0/ Over flow
        DCD     INT_TB31_IRQHandler       ; 16bit TMRB3 compare match detection 1
        DCD     INT_CAP20_IRQHandler      ; 16bit TMRB2 input capture 0
        DCD     INT_CAP21_IRQHandler      ; 16bit TMRB2 input capture 1
        DCD     INT_CAP30_IRQHandler      ; 16bit TMRB3 input capture 0
        DCD     INT_CAP31_IRQHandler      ; 16bit TMRB3 input capture 1
        DCD     0                         ; Reserved
        DCD     INT_ADBSFT_IRQHandler     ; ADCB conversion started by software is finished
        DCD     0                         ; Reserved
        DCD     INT_ADBTMR_IRQHandler     ; ADCB conversion triggered by timer is finished
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     INT_ENC1_IRQHandler       ; Ender input1 interrupt
        DCD     INT_RX3_IRQHandler        ; Serial reception (channel.3)
        DCD     INT_TX3_IRQHandler        ; Serial transmit (channel.3)
        DCD     INT_TB60_IRQHandler       ; 16bit TMRB6 compare match detection 0 / Over flow
        DCD     INT_TB61_IRQHandler       ; 16bit TMRB6 compare match detection 1
        DCD     INT_TB70_IRQHandler       ; 16bit TMRB7 compare match detection 0 / Over flow
        DCD     INT_TB71_IRQHandler       ; 16bit TMRB7 compare match detection 1
        DCD     INT_CAP60_IRQHandler      ; 16bit TMRB6 input capture 0
        DCD     INT_CAP61_IRQHandler      ; 16bit TMRB6 input capture 1
        DCD     INT_CAP70_IRQHandler      ; 16bit TMRB7 input capture 0
        DCD     INT_CAP71_IRQHandler      ; 16bit TMRB7 input capture 1
        DCD     INT_C_IRQHandler          ; Interrupt Pin (PJ6/AINB9/74pin or 76 pin)
        DCD     INT_D_IRQHandler          ; Interrupt Pin (PJ7/AINB10/73pin or 75pin)
        DCD     INT_E_IRQHandler          ; Interrupt Pin (PK0/AINB11/72pin or 74pin)
        DCD     INT_F_IRQHandler          ; Interrupt Pin (PK1/AINB12/71pin or 73pin)

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
      PUBWEAK EII_IRQHandler
      PUBWEAK INT_5_IRQHandler
      PUBWEAK INT_RX0_IRQHandler
      PUBWEAK INT_TX0_IRQHandler
      PUBWEAK INT_RX1_IRQHandler
      PUBWEAK INT_TX1_IRQHandler
      PUBWEAK INT_VCNB_IRQHandler
      PUBWEAK INT_EMG1_IRQHandler
      PUBWEAK INT_OVV1_IRQHandler
      PUBWEAK INT_ADBPDB_IRQHandler
      PUBWEAK INT_TB00_IRQHandler
      PUBWEAK INT_TB01_IRQHandler
      PUBWEAK INT_TB10_IRQHandler
      PUBWEAK INT_TB11_IRQHandler
      PUBWEAK INT_TB40_IRQHandler
      PUBWEAK INT_TB41_IRQHandler
      PUBWEAK INT_TB50_IRQHandler
      PUBWEAK INT_TB51_IRQHandler
      PUBWEAK INT_PMD1_IRQHandler
      PUBWEAK INT_CAP00_IRQHandler
      PUBWEAK INT_CAP10_IRQHandler
      PUBWEAK INT_CAP40_IRQHandler
      PUBWEAK INT_CAP50_IRQHandler
      PUBWEAK INT_6_IRQHandler
      PUBWEAK INT_7_IRQHandler
      PUBWEAK INT_ADBCPA_IRQHandler
      PUBWEAK INT_ADBCPB_IRQHandler
      PUBWEAK INT_TB20_IRQHandler
      PUBWEAK INT_TB21_IRQHandler
      PUBWEAK INT_TB30_IRQHandler
      PUBWEAK INT_TB31_IRQHandler
      PUBWEAK INT_CAP20_IRQHandler
      PUBWEAK INT_CAP21_IRQHandler
      PUBWEAK INT_CAP30_IRQHandler
      PUBWEAK INT_CAP31_IRQHandler
      PUBWEAK INT_ADBSFT_IRQHandler
      PUBWEAK INT_ADBTMR_IRQHandler
      PUBWEAK INT_ENC1_IRQHandler
      PUBWEAK INT_RX3_IRQHandler
      PUBWEAK INT_TX3_IRQHandler
      PUBWEAK INT_TB60_IRQHandler
      PUBWEAK INT_TB61_IRQHandler
      PUBWEAK INT_TB70_IRQHandler
      PUBWEAK INT_TB71_IRQHandler
      PUBWEAK INT_CAP60_IRQHandler
      PUBWEAK INT_CAP61_IRQHandler
      PUBWEAK INT_CAP70_IRQHandler
      PUBWEAK INT_CAP71_IRQHandler
      PUBWEAK INT_C_IRQHandler
      PUBWEAK INT_D_IRQHandler
      PUBWEAK INT_E_IRQHandler
      PUBWEAK INT_F_IRQHandler

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
EII_IRQHandler
INT_5_IRQHandler
INT_RX0_IRQHandler
INT_TX0_IRQHandler
INT_RX1_IRQHandler
INT_TX1_IRQHandler
INT_VCNB_IRQHandler
INT_EMG1_IRQHandler
INT_OVV1_IRQHandler
INT_ADBPDB_IRQHandler
INT_TB00_IRQHandler
INT_TB01_IRQHandler
INT_TB10_IRQHandler
INT_TB11_IRQHandler
INT_TB40_IRQHandler
INT_TB41_IRQHandler
INT_TB50_IRQHandler
INT_TB51_IRQHandler
INT_PMD1_IRQHandler
INT_CAP00_IRQHandler
INT_CAP10_IRQHandler
INT_CAP40_IRQHandler
INT_CAP50_IRQHandler
INT_6_IRQHandler
INT_7_IRQHandler
INT_ADBCPA_IRQHandler
INT_ADBCPB_IRQHandler
INT_TB20_IRQHandler
INT_TB21_IRQHandler
INT_TB30_IRQHandler
INT_TB31_IRQHandler
INT_CAP20_IRQHandler
INT_CAP21_IRQHandler
INT_CAP30_IRQHandler
INT_CAP31_IRQHandler
INT_ADBSFT_IRQHandler
INT_ADBTMR_IRQHandler
INT_ENC1_IRQHandler
INT_RX3_IRQHandler
INT_TX3_IRQHandler
INT_TB60_IRQHandler
INT_TB61_IRQHandler
INT_TB70_IRQHandler
INT_TB71_IRQHandler
INT_CAP60_IRQHandler
INT_CAP61_IRQHandler
INT_CAP70_IRQHandler
INT_CAP71_IRQHandler
INT_C_IRQHandler
INT_D_IRQHandler
INT_E_IRQHandler
INT_F_IRQHandler
Default_Handler
        B Default_Handler
        END
