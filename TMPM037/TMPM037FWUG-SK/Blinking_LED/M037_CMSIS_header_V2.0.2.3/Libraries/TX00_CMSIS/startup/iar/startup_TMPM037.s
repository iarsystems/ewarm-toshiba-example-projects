;/**
; *******************************************************************************
; * @file    startup_TMPM037.s
; * @brief   CMSIS Cortex-M0 Core Device Startup File for the
; *          TOSHIBA 'TMPM037' Device Series
; * @version V2.0.2.2 (Tentative)
; * @date    2014/04/30
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
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     INT0_IRQHandler           ; 0:	Interrupt Pin0(PB5)
                DCD     INT1_IRQHandler           ; 1:	Interrupt Pin1(PB6)
                DCD     INT2_IRQHandler           ; 2:	Interrupt Pin2(PB7)
                DCD     INT3_IRQHandler           ; 3:	Interrupt Pin3(PE7)
                DCD     INT4_IRQHandler           ; 4:	Interrupt Pin4(PE6)
                DCD     INT5_IRQHandler           ; 5:	Interrupt Pin5(PE5)
                DCD     INTRX0_IRQHandler         ; 6:	Serial reception (channel.0)
                DCD     INTTX0_IRQHandler         ; 7:	Serial transmission (channel.0)
                DCD     INTRX1_IRQHandler         ; 8:	Serial reception (channel.1)
                DCD     INTTX1_IRQHandler         ; 9:	Serial transmission (channel.1)
                DCD     0                         ; 10:	Reserved
                DCD     0                         ; 11:	Reserved
                DCD     INTI2C0_IRQHandler        ; 12:	Serial bus interface
                DCD     INTDMAC_IRQHandler        ; 13:	DMAC interrupt
                DCD     INTT16A0_IRQHandler       ; 14:	16-bit TMR16A match detection (channel.0)
                DCD     INTT16A1_IRQHandler       ; 15:	16-bit TMR16A match detection (channel.1)
                DCD     INTTMRB0_IRQHandler       ; 16:	16-bit TMRB interrupt(channel.0)
                DCD     INTTMRB1_IRQHandler       ; 17:	16-bit TMRB interrupt(channel.1)
                DCD     INTTMRB2_IRQHandler       ; 18:	16-bit TMRB interrupt(channel.2)
                DCD     INTTMRB3_IRQHandler       ; 19:	16-bit TMRB interrupt(channel.3)
                DCD     INTTMRB4_IRQHandler       ; 20:	16-bit TMRB interrupt(channel.4)
                DCD     INTTMRB5_IRQHandler       ; 21:	16-bit TMRB interrupt(channel.5)
                DCD     INTTMRB6_IRQHandler       ; 22:	16-bit TMRB interrupt(channel.6)
                DCD     INTTMRB7_IRQHandler       ; 23:	16-bit TMRB interrupt(channel.7)
                DCD     INTRX2_IRQHandler         ; 24:	Serial reception (channel.2)
                DCD     INTTX2_IRQHandler         ; 25:	Serial transmission (channel.2)
                DCD     INTRX3_IRQHandler         ; 26:	Serial reception (channel.3)
                DCD     INTTX3_IRQHandler         ; 27:	Serial transmission (channel.3)
                DCD     INTRX4_IRQHandler         ; 28:	Serial reception (channel.4)
                DCD     INTTX4_IRQHandler         ; 29:	Serial transmission (channel.4)
                DCD     INTADC_IRQHandler         ; 30:	A/D conversion combined interrupt
                DCD     INTAD_IRQHandler          ; 31:	Normal A/D conversion completion interrupt
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

                PUBWEAK SVC_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
                B       SVC_Handler

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

                PUBWEAK INTI2C0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0_IRQHandler
                B       INTI2C0_IRQHandler

                PUBWEAK INTDMAC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMAC_IRQHandler
                B       INTDMAC_IRQHandler

                PUBWEAK INTT16A0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT16A0_IRQHandler
                B       INTT16A0_IRQHandler

                PUBWEAK INTT16A1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT16A1_IRQHandler
                B       INTT16A1_IRQHandler

                PUBWEAK INTTMRB0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTMRB0_IRQHandler
                B       INTTMRB0_IRQHandler

                PUBWEAK INTTMRB1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTMRB1_IRQHandler
                B       INTTMRB1_IRQHandler

                PUBWEAK INTTMRB2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTMRB2_IRQHandler
                B       INTTMRB2_IRQHandler

                PUBWEAK INTTMRB3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTMRB3_IRQHandler
                B       INTTMRB3_IRQHandler

                PUBWEAK INTTMRB4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTMRB4_IRQHandler
                B       INTTMRB4_IRQHandler

                PUBWEAK INTTMRB5_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTMRB5_IRQHandler
                B       INTTMRB5_IRQHandler

                PUBWEAK INTTMRB6_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTMRB6_IRQHandler
                B       INTTMRB6_IRQHandler

                PUBWEAK INTTMRB7_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTMRB7_IRQHandler
                B       INTTMRB7_IRQHandler

                PUBWEAK INTRX2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX2_IRQHandler
                B       INTRX2_IRQHandler

                PUBWEAK INTTX2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX2_IRQHandler
                B       INTTX2_IRQHandler

                PUBWEAK INTRX3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX3_IRQHandler
                B       INTRX3_IRQHandler

                PUBWEAK INTTX3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX3_IRQHandler
                B       INTTX3_IRQHandler

                PUBWEAK INTRX4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX4_IRQHandler
                B       INTRX4_IRQHandler

                PUBWEAK INTTX4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX4_IRQHandler
                B       INTTX4_IRQHandler

                PUBWEAK INTADC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADC_IRQHandler
                B       INTADC_IRQHandler

                PUBWEAK INTAD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTAD_IRQHandler
                B       INTAD_IRQHandler

                END
