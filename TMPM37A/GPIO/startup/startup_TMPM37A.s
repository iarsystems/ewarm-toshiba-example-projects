;/**
; *******************************************************************************
; * @file    startup_TMPM37A.s
; * @brief   CMSIS Cortex-M3 Core Device Startup File for the
; *          TOSHIBA 'TMPM37A' Device Series
; * @version V2.0.2.1 (Tentative)
; * @date    2015/10/08
; * 
; * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
; * 
; * (C)Copyright TOSHIBA CORPORATION 2015 All rights reserved
; *******************************************************************************
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
                DCD     INTRX0_IRQHandler         ; 0:	Serial reception (channel.0)
                DCD     INTTX0_IRQHandler         ; 1:	Serial transmit (channel.0)
                DCD     0                         ; 2:	-
                DCD     0                         ; 3:	-
                DCD     INTVCNB_IRQHandler        ; 4:	Vector Engine interrupt B
                DCD     INTEMG_IRQHandler         ; 5:	PMD EMG interrupt
                DCD     INTOVV_IRQHandler         ; 6:	PMD OVV interrupt
                DCD     INTADPDB_IRQHandler       ; 7:	ADC conversion triggered by PMD is finished
                DCD     INTTB00_IRQHandler        ; 8:	16bit TMRB0 compare match detection 0/ Over flow
                DCD     INTTB01_IRQHandler        ; 9:	16bit TMRB0 compare match detection 1
                DCD     INTTB40_IRQHandler        ; 10:	16bit TMRB4 compare match detection 0/ Over flow
                DCD     INTTB41_IRQHandler        ; 11:	16bit TMRB4 compare match detection 1
                DCD     INTTB50_IRQHandler        ; 12:	16bit TMRB5 compare match detection 0/ Over flow
                DCD     INTTB51_IRQHandler        ; 13:	16bit TMRB5 compare match detection 1
                DCD     INTPMD_IRQHandler         ; 14:	PMD PWM interrupt
                DCD     INTCAP00_IRQHandler       ; 15:	16bit TMRB0 input capture 0
                DCD     INTCAP01_IRQHandler       ; 16:	16bit TMRB0 input capture 1
                DCD     INTCAP40_IRQHandler       ; 17:	16bit TMRB4 input capture 0
                DCD     INTCAP41_IRQHandler       ; 18:	16bit TMRB4 input capture 1
                DCD     INT6_IRQHandler           ; 19:	Interrupt Pin (PE0/14pin)
                DCD     INT7_IRQHandler           ; 20:	Interrupt Pin (PE2/16pin)
                DCD     INTADCPA_IRQHandler       ; 21:	ADC conversion monitoring function interrupt A
                DCD     INTADCPB_IRQHandler       ; 22:	ADC conversion monitoring function interrupt B
                DCD     INTADSFT_IRQHandler       ; 23:	ADC conversion started by software is finished
                DCD     INTADTMR_IRQHandler       ; 24:	ADC conversion triggered by timer is finished
                DCD     0                         ; 25:	-
                DCD     INTTB70_IRQHandler        ; 26:	16bit TMRB7 compare match detection 0 / Over flow
                DCD     INTTB71_IRQHandler        ; 27:	16bit TMRB7 compare match detection 1
                DCD     INTCAP70_IRQHandler       ; 28:	16bit TMRB7 input capture 0
                DCD     INTCAP71_IRQHandler       ; 29:	16bit TMRB7 input capture 1
                DCD     INTC_IRQHandler           ; 30:	Interrupt Pin (PF0/17pin)
                DCD     INTSBI0_IRQHandler        ; 31:	Serial Bus Interface0
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

                PUBWEAK INTRX0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX0_IRQHandler
                B       INTRX0_IRQHandler

                PUBWEAK INTTX0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX0_IRQHandler
                B       INTTX0_IRQHandler

                PUBWEAK INTVCNB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTVCNB_IRQHandler
                B       INTVCNB_IRQHandler

                PUBWEAK INTEMG_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEMG_IRQHandler
                B       INTEMG_IRQHandler

                PUBWEAK INTOVV_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTOVV_IRQHandler
                B       INTOVV_IRQHandler

                PUBWEAK INTADPDB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADPDB_IRQHandler
                B       INTADPDB_IRQHandler

                PUBWEAK INTTB00_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB00_IRQHandler
                B       INTTB00_IRQHandler

                PUBWEAK INTTB01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB01_IRQHandler
                B       INTTB01_IRQHandler

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

                PUBWEAK INTPMD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPMD_IRQHandler
                B       INTPMD_IRQHandler

                PUBWEAK INTCAP00_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP00_IRQHandler
                B       INTCAP00_IRQHandler

                PUBWEAK INTCAP01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP01_IRQHandler
                B       INTCAP01_IRQHandler

                PUBWEAK INTCAP40_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP40_IRQHandler
                B       INTCAP40_IRQHandler

                PUBWEAK INTCAP41_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCAP41_IRQHandler
                B       INTCAP41_IRQHandler

                PUBWEAK INT6_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT6_IRQHandler
                B       INT6_IRQHandler

                PUBWEAK INT7_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT7_IRQHandler
                B       INT7_IRQHandler

                PUBWEAK INTADCPA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCPA_IRQHandler
                B       INTADCPA_IRQHandler

                PUBWEAK INTADCPB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCPB_IRQHandler
                B       INTADCPB_IRQHandler

                PUBWEAK INTADSFT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADSFT_IRQHandler
                B       INTADSFT_IRQHandler

                PUBWEAK INTADTMR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADTMR_IRQHandler
                B       INTADTMR_IRQHandler

                PUBWEAK INTTB70_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB70_IRQHandler
                B       INTTB70_IRQHandler

                PUBWEAK INTTB71_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB71_IRQHandler
                B       INTTB71_IRQHandler

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

                PUBWEAK INTSBI0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSBI0_IRQHandler
                B       INTSBI0_IRQHandler

                END
