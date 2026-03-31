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

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c

        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     __iar_program_start         ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; MPU Fault Handler
        DCD     BusFault_Handler            ; Bus Fault Handler
        DCD     UsageFault_Handler          ; Usage Fault Handler
__vector_table_0x1c
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     DebugMon_Handler            ; Debug Monitor Handler
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler

        DCD     INTERR_IRQHandler
        DCD     INTWARN_IRQHandler
        DCD     INTINFO_IRQHandler
        DCD     INTWDTERR_IRQHandler
        DCD     INTPOEMG_IRQHandler
        DCD     INTCOEMG_IRQHandler
        DCD     INTOVF0_IRQHandler
        DCD     INTCMP00_IRQHandler
        DCD     INTCMP01_IRQHandler
        DCD     INTOVF1_IRQHandler
        DCD     INTCMP10_IRQHandler
        DCD     INTCMP11_IRQHandler
        DCD     INTOVF2_IRQHandler
        DCD     INTCMP20_IRQHandler
        DCD     INTCMP21_IRQHandler
        DCD     INTOVF3_IRQHandler
        DCD     INTCMP30_IRQHandler
        DCD     INTCMP31_IRQHandler
        DCD     INTOVF4_IRQHandler
        DCD     INTCMP40_IRQHandler
        DCD     INTCMP41_IRQHandler
        DCD     INTTBTOVF_IRQHandler
        DCD     INTTBTI0_IRQHandler
        DCD     INTTBTI1_IRQHandler
        DCD     INTTBTI2_IRQHandler
        DCD     INTTBTI3_IRQHandler
        DCD     INTTCAP0R_IRQHandler
        DCD     INTTCAP0F_IRQHandler
        DCD     INTTCAP1R_IRQHandler
        DCD     INTTCAP1F_IRQHandler
        DCD     INTTCAP2R_IRQHandler
        DCD     INTTCAP2F_IRQHandler
        DCD     INTTCAP3R_IRQHandler
        DCD     INTTCAP3F_IRQHandler
        DCD     INTTCAP4R_IRQHandler
        DCD     INTTCAP4F_IRQHandler
        DCD     INTTCAP5R_IRQHandler
        DCD     INTTCAP5F_IRQHandler
        DCD     INTTCMP0_IRQHandler
        DCD     INTTCMP1_IRQHandler
        DCD     INTTCAP7R_IRQHandler
        DCD     INTTCAP7F_IRQHandler
        DCD     INTPWM0_IRQHandler
        DCD     INTPWM1_IRQHandler
        DCD     INTPWM2_IRQHandler
        DCD     INTPWM3_IRQHandler
        DCD     INTRX0_IRQHandler
        DCD     INTTX0_IRQHandler
        DCD     INTRX1_IRQHandler
        DCD     INTTX1_IRQHandler
        DCD     INTRX2_IRQHandler
        DCD     INTTX2_IRQHandler
        DCD     INTESEIERR0_IRQHandler
        DCD     INTESEIRX0_IRQHandler
        DCD     INTESEITX0_IRQHandler
        DCD     INTESEIERR1_IRQHandler
        DCD     INTESEIRX1_IRQHandler
        DCD     INTESEITX1_IRQHandler
        DCD     INTCR0_IRQHandler
        DCD     INTCT0_IRQHandler
        DCD     INTCG0_IRQHandler
        DCD     INTCR1_IRQHandler
        DCD     INTCT1_IRQHandler
        DCD     INTCG1_IRQHandler
        DCD     INTCR2_IRQHandler
        DCD     INTCT2_IRQHandler
        DCD     INTCG2_IRQHandler
        DCD     INTADC0_IRQHandler
        DCD     INTADC1_IRQHandler
        DCD     INTADC2_IRQHandler
        DCD     INTADC3_IRQHandler
        DCD     INTEXC_IRQHandler
        DCD     INTVE_IRQHandler
        DCD     INTRDC0_IRQHandler
        DCD     INTZ_IRQHandler
        DCD     INTCIUT0
        DCD     INTCAR0A_IRQHandler
        DCD     INTCAR0B_IRQHandler
        DCD     INTCAR1_IRQHandler
        DCD     INTCAR2_IRQHandler
        DCD     INTCPWM0_IRQHandler
        DCD     INTCPWM1_IRQHandler
        DCD     INTFPWM0_IRQHandler
        DCD     INTFPWM1_IRQHandler
        DCD     INTDMAXFEND0_IRQHandler
        DCD     INTDMAXFEND1_IRQHandler
        DCD     INTTCAP13R_IRQHandler
        DCD     INTRDC1_IRQHandler
        DCD     INTLVCLR_IRQHandler


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

        PUBWEAK INTERR_IRQHandler
        PUBWEAK INTWARN_IRQHandler
        PUBWEAK INTINFO_IRQHandler
        PUBWEAK INTWDTERR_IRQHandler
        PUBWEAK INTPOEMG_IRQHandler
        PUBWEAK INTCOEMG_IRQHandler
        PUBWEAK INTOVF0_IRQHandler
        PUBWEAK INTCMP00_IRQHandler
        PUBWEAK INTCMP01_IRQHandler
        PUBWEAK INTOVF1_IRQHandler
        PUBWEAK INTCMP10_IRQHandler
        PUBWEAK INTCMP11_IRQHandler
        PUBWEAK INTOVF2_IRQHandler
        PUBWEAK INTCMP20_IRQHandler
        PUBWEAK INTCMP21_IRQHandler
        PUBWEAK INTOVF3_IRQHandler
        PUBWEAK INTCMP30_IRQHandler
        PUBWEAK INTCMP31_IRQHandler
        PUBWEAK INTOVF4_IRQHandler
        PUBWEAK INTCMP40_IRQHandler
        PUBWEAK INTCMP41_IRQHandler
        PUBWEAK INTTBTOVF_IRQHandler
        PUBWEAK INTTBTI0_IRQHandler
        PUBWEAK INTTBTI1_IRQHandler
        PUBWEAK INTTBTI2_IRQHandler
        PUBWEAK INTTBTI3_IRQHandler
        PUBWEAK INTTCAP0R_IRQHandler
        PUBWEAK INTTCAP0F_IRQHandler
        PUBWEAK INTTCAP1R_IRQHandler
        PUBWEAK INTTCAP1F_IRQHandler
        PUBWEAK INTTCAP2R_IRQHandler
        PUBWEAK INTTCAP2F_IRQHandler
        PUBWEAK INTTCAP3R_IRQHandler
        PUBWEAK INTTCAP3F_IRQHandler
        PUBWEAK INTTCAP4R_IRQHandler
        PUBWEAK INTTCAP4F_IRQHandler
        PUBWEAK INTTCAP5R_IRQHandler
        PUBWEAK INTTCAP5F_IRQHandler
        PUBWEAK INTTCMP0_IRQHandler
        PUBWEAK INTTCMP1_IRQHandler
        PUBWEAK INTTCAP7R_IRQHandler
        PUBWEAK INTTCAP7F_IRQHandler
        PUBWEAK INTPWM0_IRQHandler
        PUBWEAK INTPWM1_IRQHandler
        PUBWEAK INTPWM2_IRQHandler
        PUBWEAK INTPWM3_IRQHandler
        PUBWEAK INTRX0_IRQHandler
        PUBWEAK INTTX0_IRQHandler
        PUBWEAK INTRX1_IRQHandler
        PUBWEAK INTTX1_IRQHandler
        PUBWEAK INTRX2_IRQHandler
        PUBWEAK INTTX2_IRQHandler
        PUBWEAK INTESEIERR0_IRQHandler
        PUBWEAK INTESEIRX0_IRQHandler
        PUBWEAK INTESEITX0_IRQHandler
        PUBWEAK INTESEIERR1_IRQHandler
        PUBWEAK INTESEIRX1_IRQHandler
        PUBWEAK INTESEITX1_IRQHandler
        PUBWEAK INTCR0_IRQHandler
        PUBWEAK INTCT0_IRQHandler
        PUBWEAK INTCG0_IRQHandler
        PUBWEAK INTCR1_IRQHandler
        PUBWEAK INTCT1_IRQHandler
        PUBWEAK INTCG1_IRQHandler
        PUBWEAK INTCR2_IRQHandler
        PUBWEAK INTCT2_IRQHandler
        PUBWEAK INTCG2_IRQHandler
        PUBWEAK INTADC0_IRQHandler
        PUBWEAK INTADC1_IRQHandler
        PUBWEAK INTADC2_IRQHandler
        PUBWEAK INTADC3_IRQHandler
        PUBWEAK INTEXC_IRQHandler
        PUBWEAK INTVE_IRQHandler
        PUBWEAK INTRDC0_IRQHandler
        PUBWEAK INTZ_IRQHandler
        PUBWEAK INTCIUT0
        PUBWEAK INTCAR0A_IRQHandler
        PUBWEAK INTCAR0B_IRQHandler
        PUBWEAK INTCAR1_IRQHandler
        PUBWEAK INTCAR2_IRQHandler
        PUBWEAK INTCPWM0_IRQHandler
        PUBWEAK INTCPWM1_IRQHandler
        PUBWEAK INTFPWM0_IRQHandler
        PUBWEAK INTFPWM1_IRQHandler
        PUBWEAK INTDMAXFEND0_IRQHandler
        PUBWEAK INTDMAXFEND1_IRQHandler
        PUBWEAK INTTCAP13R_IRQHandler
        PUBWEAK INTRDC1_IRQHandler
        PUBWEAK INTLVCLR_IRQHandler

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
INTERR_IRQHandler
INTWARN_IRQHandler
INTINFO_IRQHandler
INTWDTERR_IRQHandler
INTPOEMG_IRQHandler
INTCOEMG_IRQHandler
INTOVF0_IRQHandler
INTCMP00_IRQHandler
INTCMP01_IRQHandler
INTOVF1_IRQHandler
INTCMP10_IRQHandler
INTCMP11_IRQHandler
INTOVF2_IRQHandler
INTCMP20_IRQHandler
INTCMP21_IRQHandler
INTOVF3_IRQHandler
INTCMP30_IRQHandler
INTCMP31_IRQHandler
INTOVF4_IRQHandler
INTCMP40_IRQHandler
INTCMP41_IRQHandler
INTTBTOVF_IRQHandler
INTTBTI0_IRQHandler
INTTBTI1_IRQHandler
INTTBTI2_IRQHandler
INTTBTI3_IRQHandler
INTTCAP0R_IRQHandler
INTTCAP0F_IRQHandler
INTTCAP1R_IRQHandler
INTTCAP1F_IRQHandler
INTTCAP2R_IRQHandler
INTTCAP2F_IRQHandler
INTTCAP3R_IRQHandler
INTTCAP3F_IRQHandler
INTTCAP4R_IRQHandler
INTTCAP4F_IRQHandler
INTTCAP5R_IRQHandler
INTTCAP5F_IRQHandler
INTTCMP0_IRQHandler
INTTCMP1_IRQHandler
INTTCAP7R_IRQHandler
INTTCAP7F_IRQHandler
INTPWM0_IRQHandler
INTPWM1_IRQHandler
INTPWM2_IRQHandler
INTPWM3_IRQHandler
INTRX0_IRQHandler
INTTX0_IRQHandler
INTRX1_IRQHandler
INTTX1_IRQHandler
INTRX2_IRQHandler
INTTX2_IRQHandler
INTESEIERR0_IRQHandler
INTESEIRX0_IRQHandler
INTESEITX0_IRQHandler
INTESEIERR1_IRQHandler
INTESEIRX1_IRQHandler
INTESEITX1_IRQHandler
INTCR0_IRQHandler
INTCT0_IRQHandler
INTCG0_IRQHandler
INTCR1_IRQHandler
INTCT1_IRQHandler
INTCG1_IRQHandler
INTCR2_IRQHandler
INTCT2_IRQHandler
INTCG2_IRQHandler
INTADC0_IRQHandler
INTADC1_IRQHandler
INTADC2_IRQHandler
INTADC3_IRQHandler
INTEXC_IRQHandler
INTVE_IRQHandler
INTRDC0_IRQHandler
INTZ_IRQHandler
INTCIUT0
INTCAR0A_IRQHandler
INTCAR0B_IRQHandler
INTCAR1_IRQHandler
INTCAR2_IRQHandler
INTCPWM0_IRQHandler
INTCPWM1_IRQHandler
INTFPWM0_IRQHandler
INTFPWM1_IRQHandler
INTDMAXFEND0_IRQHandler
INTDMAXFEND1_IRQHandler
INTTCAP13R_IRQHandler
INTRDC1_IRQHandler
INTLVCLR_IRQHandler
Default_Handler
        B Default_Handler

        END
