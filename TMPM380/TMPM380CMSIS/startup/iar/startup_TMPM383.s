;/**
; *******************************************************************************
; * @file    startup_TMPM383.s
; * @brief   CMSIS Cortex-M3 Core Device Startup File for the
; *          TOSHIBA 'TMPM383' Device Series
; * @version V2.0.2.2 (Tentative)
; * @date    2015/04/23
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
                DCD     INT0_IRQHandler           ; 0:	Interrupt pin (PH0/AIN0/INT0)
                DCD     INT1_IRQHandler           ; 1:	Interrupt pin (PH1/AIN1/INT1)
                DCD     INT2_IRQHandler           ; 2:	Interrupt pin (PH2/AIN2/INT2)
                DCD     INT3_IRQHandler           ; 3:	Interrupt pin (PA0/TB0IN/INT3)
                DCD     INT4_IRQHandler           ; 4:	Interrupt pin (PA2/TB1IN/INT4)
                DCD     INT5_IRQHandler           ; 5:	Interrupt pin (PE4/TB2IN/INT5)
                DCD     INTRX0_IRQHandler         ; 6:	Serial reception (channel.0)
                DCD     INTTX0_IRQHandler         ; 7:	Serial transmission (channel.0)
                DCD     INTRX1_IRQHandler         ; 8:	Serial reception (channel.1)
                DCD     INTTX1_IRQHandler         ; 9:	Serial transmission (channel.1)
                DCD     INTSSP0_IRQHandler        ; 10:	Syncronous Serial Port 0
                DCD     0                         ; 11:	Reserved
                DCD     0                         ; 12:	Reserved
                DCD     0                         ; 13:	Reserved
                DCD     INTSBI0_IRQHandler        ; 14:	Serial Bus Interface 0 interrupt
                DCD     0                         ; 15:	Reserved
                DCD     0                         ; 16:	Reserved
                DCD     INTRTC_IRQHandler         ; 17:	Realtime clock interrupt
                DCD     0                         ; 18:	Reserved
                DCD     INTRMCRX_IRQHandler       ; 19:	Remote Controller reception interrupt
                DCD     INTTB00_IRQHandler        ; 20:	16bit TMRB0 compare match detection 0
                DCD     INTTB01_IRQHandler        ; 21:	16bit TMRB0 compare match detection 1
                DCD     INTTB10_IRQHandler        ; 22:	16bit TMRB1 compare match detection 0
                DCD     INTTB11_IRQHandler        ; 23:	16bit TMRB1 compare match detection 1
                DCD     INTTB40_IRQHandler        ; 24:	16bit TMRB4 compare match detection 0
                DCD     INTTB41_IRQHandler        ; 25:	16bit TMRB4 compare match detection 1
                DCD     INTTB50_IRQHandler        ; 26:	16bit TMRB5 compare match detection 0
                DCD     INTTB51_IRQHandler        ; 27:	16bit TMRB5 compare match detection 1
                DCD     0                         ; 28:	Reserved
                DCD     0                         ; 29:	Reserved
                DCD     INTCAP00_IRQHandler       ; 30:	16bit TMRB0 input capture 0
                DCD     INTCAP01_IRQHandler       ; 31:	16bit TMRB0 input capture 1
                DCD     INTCAP10_IRQHandler       ; 32:	16bit TMRB1 input capture 0
                DCD     INTCAP11_IRQHandler       ; 33:	16bit TMRB1 input capture 1
                DCD     INTCAP40_IRQHandler       ; 34:	16bit TMRB4 input capture 0
                DCD     INTCAP41_IRQHandler       ; 35:	16bit TMRB4 input capture 1
                DCD     INTCAP50_IRQHandler       ; 36:	16bit TMRB5 input capture 0
                DCD     INTCAP51_IRQHandler       ; 37:	16bit TMRB5 input capture 1
                DCD     0                         ; 38:	Reserved
                DCD     0                         ; 39:	Reserved
                DCD     0                         ; 40:	Reserved
                DCD     0                         ; 41:	Reserved
                DCD     INTADCP0_IRQHandler       ; 42:	ADC conversion monitoring function interrupt 0
                DCD     INTADCP1_IRQHandler       ; 43:	ADC conversion monitoring function interrupt 1
                DCD     INTUART0_IRQHandler       ; 44:	UART transmission and reception interrupt (channel.0)
                DCD     0                         ; 45:	Reserved
                DCD     INTTB20_IRQHandler        ; 46:	16bit TMRB2 compare match detection 0
                DCD     INTTB21_IRQHandler        ; 47:	16bit TMRB2 compare match detection 1
                DCD     INTTB30_IRQHandler        ; 48:	16bit TMRB3 compare match detection 0
                DCD     INTTB31_IRQHandler        ; 49:	16bit TMRB3 compare match detection 1
                DCD     INTCAP20_IRQHandler       ; 50:	16bit TMRB2 input capture 0
                DCD     INTCAP21_IRQHandler       ; 51:	16bit TMRB2 input capture 1
                DCD     INTCAP30_IRQHandler       ; 52:	16bit TMRB3 input capture 0
                DCD     INTCAP31_IRQHandler       ; 53:	16bit TMRB3 input capture 1
                DCD     INTADSFT_IRQHandler       ; 54:	ADC conversion started by software is finished
                DCD     0                         ; 55:	Reserved
                DCD     INTADTMR_IRQHandler       ; 56:	ADC conversion triggered by timer is finished
                DCD     0                         ; 57:	Reserved
                DCD     INT8_IRQHandler           ; 58:	Interrupt Pin (PA7/TB4IN/INT8)
                DCD     0                         ; 59:	Reserved
                DCD     0                         ; 60:	Reserved
                DCD     0                         ; 61:	Reserved
                DCD     0                         ; 62:	Reserved
                DCD     0                         ; 63:	Reserved
                DCD     0                         ; 64:	Reserved
                DCD     0                         ; 65:	Reserved
                DCD     INTTB60_IRQHandler        ; 66:	16bit TMRB6 compare match detection 0
                DCD     INTTB61_IRQHandler        ; 67:	16bit TMRB6 compare match detection 1
                DCD     INTTB70_IRQHandler        ; 68:	16bit TMRB7 compare match detection 0
                DCD     INTTB71_IRQHandler        ; 69:	16bit TMRB7 compare match detection 1
                DCD     INTCAP60_IRQHandler       ; 70:	16bit TMRB6 input capture 0
                DCD     INTCAP61_IRQHandler       ; 71:	16bit TMRB6 input capture 1
                DCD     INTCAP70_IRQHandler       ; 72:	16bit TMRB7 input capture 0
                DCD     INTCAP71_IRQHandler       ; 73:	16bit TMRB7 input capture 1
                DCD     0                         ; 74:	Reserved
                DCD     0                         ; 75:	Reserved
                DCD     0                         ; 76:	Reserved
                DCD     INTF_IRQHandler           ; 77:	Interrupt Pin (PL2/INTF)
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

                PUBWEAK INTSBI0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSBI0_IRQHandler
                B       INTSBI0_IRQHandler

                PUBWEAK INTRTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRTC_IRQHandler
                B       INTRTC_IRQHandler

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

                PUBWEAK INTADCP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCP0_IRQHandler
                B       INTADCP0_IRQHandler

                PUBWEAK INTADCP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCP1_IRQHandler
                B       INTADCP1_IRQHandler

                PUBWEAK INTUART0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART0_IRQHandler
                B       INTUART0_IRQHandler

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

                PUBWEAK INTF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTF_IRQHandler
                B       INTF_IRQHandler

                END
