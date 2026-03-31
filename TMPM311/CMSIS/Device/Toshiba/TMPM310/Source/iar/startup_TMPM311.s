;/**
; *******************************************************************************
; * @file    startup_TMPM311.s
; * @brief   CMSIS Cortex-M3 Core Device Startup File for the
; *          TOSHIBA 'TMPM311' Device Series
; * @version V2.0.2.1 (Tentative)
; * @date    2014/09/05
; * 
; * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
; * 
; * (C)Copyright TOSHIBA CORPORATION 2014 All rights reserved
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
                DCD     INTDSADA_IRQHandler       ; 0:	DSAD conversion complete interrupt (unitA)
                DCD     INTDSADB_IRQHandler       ; 1:	DSAD conversion complete interrupt (unitB)
                DCD     INTDSADC_IRQHandler       ; 2:	DSAD conversion complete interrupt (unitC)
                DCD     INTDSADD_IRQHandler       ; 3:	DSAD conversion complete interrupt (unitD)
                DCD     INT0_IRQHandler           ; 4:	Interrupt pin 0
                DCD     INT1_IRQHandler           ; 5:	Interrupt pin 1
                DCD     INTSSP0_IRQHandler        ; 6:	SSP0 interrupt
                DCD     INTRX0_IRQHandler         ; 7:	Serial0 reception interrupt
                DCD     INTTX0_IRQHandler         ; 8:	Serial0 transmission interrupt
                DCD     INTTB0_IRQHandler         ; 9:	16-bit TMRB0 compare match detection interrupt
                DCD     INTTB1_IRQHandler         ; 10:	16-bit TMRB1 compare match detection interrupt
                DCD     INTTB2_IRQHandler         ; 11:	16-bit TMRB2 compare match detection interrupt
                DCD     INTTB3_IRQHandler         ; 12:	16-bit TMRB3 compare match detection interrupt
                DCD     INTCAP00_IRQHandler       ; 13:	16-bit TMRB0 input capture 0 detection interrupt
                DCD     INTCAP01_IRQHandler       ; 14:	16-bit TMRB0 input capture 1 detection interrupt
                DCD     INTCAP10_IRQHandler       ; 15:	16-bit TMRB1 input capture 0 detection interrupt
                DCD     INTCAP11_IRQHandler       ; 16:	16-bit TMRB1 input capture 1 detection interrupt
                DCD     INTT16A0_IRQHandler       ; 17:	16-bit TMR16A0 match detection
                DCD     INTDMAATC0_IRQHandler     ; 18:	DMAC 0 transmission completion interrupt (unitA)
                DCD     INTDMAATC1_IRQHandler     ; 19:	DMAC 1 transmission completion interrupt (unitA)
                DCD     INTDMAATC2_IRQHandler     ; 20:	DMAC 2 transmission completion interrupt (unitA)
                DCD     INTDMAATC3_IRQHandler     ; 21:	DMAC 3 transmission completion interrupt (unitA)
                DCD     INTDMAAERR_IRQHandler     ; 22:	DMAC transmissioni error interrupt (unitA)
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

                PUBWEAK INTDSADA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDSADA_IRQHandler
                B       INTDSADA_IRQHandler

                PUBWEAK INTDSADB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDSADB_IRQHandler
                B       INTDSADB_IRQHandler

                PUBWEAK INTDSADC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDSADC_IRQHandler
                B       INTDSADC_IRQHandler

                PUBWEAK INTDSADD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDSADD_IRQHandler
                B       INTDSADD_IRQHandler

                PUBWEAK INT0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT0_IRQHandler
                B       INT0_IRQHandler

                PUBWEAK INT1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT1_IRQHandler
                B       INT1_IRQHandler

                PUBWEAK INTSSP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSSP0_IRQHandler
                B       INTSSP0_IRQHandler

                PUBWEAK INTRX0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX0_IRQHandler
                B       INTRX0_IRQHandler

                PUBWEAK INTTX0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX0_IRQHandler
                B       INTTX0_IRQHandler

                PUBWEAK INTTB0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB0_IRQHandler
                B       INTTB0_IRQHandler

                PUBWEAK INTTB1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB1_IRQHandler
                B       INTTB1_IRQHandler

                PUBWEAK INTTB2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB2_IRQHandler
                B       INTTB2_IRQHandler

                PUBWEAK INTTB3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB3_IRQHandler
                B       INTTB3_IRQHandler

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

                PUBWEAK INTT16A0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT16A0_IRQHandler
                B       INTT16A0_IRQHandler

                PUBWEAK INTDMAATC0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMAATC0_IRQHandler
                B       INTDMAATC0_IRQHandler

                PUBWEAK INTDMAATC1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMAATC1_IRQHandler
                B       INTDMAATC1_IRQHandler

                PUBWEAK INTDMAATC2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMAATC2_IRQHandler
                B       INTDMAATC2_IRQHandler

                PUBWEAK INTDMAATC3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMAATC3_IRQHandler
                B       INTDMAATC3_IRQHandler

                PUBWEAK INTDMAAERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMAAERR_IRQHandler
                B       INTDMAAERR_IRQHandler

                END
