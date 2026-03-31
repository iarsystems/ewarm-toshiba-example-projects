;/**
; *******************************************************************************
; * @file    startup_TMPM4L1.s
; * @brief   CMSIS Cortex-M4 Core Device Startup File for the
; *          TOSHIBA 'TMPM4L1' Device Series
; * @version V1.0.1.0
; * $Date::            #$
; * 
; * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
; * 
; * (C)Copyright TOSHIBA MICROELECTRONICS CORPORATION 2018 All rights reserved
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
                DCD     INT00_IRQHandler          ; 0:	Interrupt pin 00
                DCD     INT01_IRQHandler          ; 1:	Interrupt pin 01
                DCD     INT02_IRQHandler          ; 2:	Interrupt pin 02
                DCD     INT03_IRQHandler          ; 3:	Interrupt pin 03
                DCD     INT04_IRQHandler          ; 4:	Interrupt pin 04
                DCD     INT05_IRQHandler          ; 5:	Interrupt pin 05
                DCD     INT06_IRQHandler          ; 6:	Interrupt pin 06
                DCD     0                         ; 7:	Reserved
                DCD     INTT32A00_AT_CT_IRQHandler; 8:	T32A00 Timer Interrupt A/Timer Interrupt C
                DCD     INTT32A00_A01_C0_IRQHandler; 9:	T32A00 Capture A0,A1,C0 Interrupt
                DCD     INTT32A00_BT_C1_IRQHandler; 10:	T32A00 Timer Interrupt B/Capture C1 Interrupt
                DCD     INTT32A00_B01_IRQHandler  ; 11:	T32A00 Capture B0,B1 Interrupt
                DCD     INTT32A01_AT_CT_IRQHandler; 12:	T32A01 Timer Interrupt A/Timer Interrupt C
                DCD     INTT32A01_A01_C0_IRQHandler; 13:	T32A01 Capture A0,A1,C0 Interrupt
                DCD     INTT32A01_BT_C1_IRQHandler; 14:	T32A01 Timer Interrupt B/Capture C1 Interrupt
                DCD     INTT32A01_B01_IRQHandler  ; 15:	T32A01 Capture B0,B1 Interrupt
                DCD     INTT32A02_AT_CT_IRQHandler; 16:	T32A02 Timer Interrupt A/Timer Interrupt C
                DCD     INTT32A02_A01_C0_IRQHandler; 17:	T32A02 Capture A0,A1,C0 Interrupt
                DCD     INTT32A02_BT_C1_IRQHandler; 18:	T32A02 Timer Interrupt B/Capture C1 Interrupt
                DCD     INTT32A02_B01_IRQHandler  ; 19:	T32A02 Capture B0,B1 Interrupt
                DCD     INTT32A03_AT_CT_IRQHandler; 20:	T32A03 Timer Interrupt A/Timer Interrupt C
                DCD     INTT32A03_A01_C0_IRQHandler; 21:	T32A03 Capture A0,A1,C0 Interrupt
                DCD     INTT32A03_BT_C1_IRQHandler; 22:	T32A03 Timer Interrupt B/Capture C1 Interrupt
                DCD     INTT32A03_B01_IRQHandler  ; 23:	T32A03 Capture B0,B1 Interrupt
                DCD     INTVCN0_IRQHandler        ; 24:	A-VE ch0 interrupt
                DCD     INTVCT0_IRQHandler        ; 25:	A-VE ch0 task termination interrupt
                DCD     INTEMG0_IRQHandler        ; 26:	PMD+ ch0 EMG interrupt
                DCD     INTOVV0_IRQHandler        ; 27:	PMD+ ch0 OVV interrupt
                DCD     INTPWM0_IRQHandler        ; 28:	PMD+ ch0 PWM interrupt
                DCD     INTENC00_IRQHandler       ; 29:	A-ENC32 ch0 Encoder interupt 0
                DCD     INTENC01_IRQHandler       ; 30:	A-ENC32 ch0 Encoder interupt 1
                DCD     0                         ; 31:	Reserved
                DCD     INTADAPDA_IRQHandler      ; 32:	ADC unit A PMD trigger program interrupt A
                DCD     INTADAPDB_IRQHandler      ; 33:	ADC unit A PMD trigger program interrupt B
                DCD     INTADACP0_IRQHandler      ; 34:	ADC conversion monitoring function interrupt 0
                DCD     INTADACP1_IRQHandler      ; 35:	ADC conversion monitoring function interrupt 1
                DCD     INTADATRG_IRQHandler      ; 36:	ADC conversion triggered by General purpose is finished
                DCD     INTADASGL_IRQHandler      ; 37:	ADC conversion triggered by Single program is finished
                DCD     INTADACNT_IRQHandler      ; 38:	ADC conversion triggered by Continuity program is finished
                DCD     INTT0RX_IRQHandler        ; 39:	TSPI/SIO reception (channel 0)
                DCD     INTT0TX_IRQHandler        ; 40:	TSPI/SIO transmit (channel 0)
                DCD     INTT0ERR_IRQHandler       ; 41:	TSPI/SIO error (channel 0)
                DCD     INTT1RX_IRQHandler        ; 42:	TSPI/SIO reception (channel 1)
                DCD     INTT1TX_IRQHandler        ; 43:	TSPI/SIO transmit (channel 1)
                DCD     INTT1ERR_IRQHandler       ; 44:	TSPI/SIO error (channel 1)
                DCD     INTT2RX_IRQHandler        ; 45:	TSPI/SIO reception (channel 2)
                DCD     INTT2TX_IRQHandler        ; 46:	TSPI/SIO transmit (channel 2)
                DCD     INTT2ERR_IRQHandler       ; 47:	TSPI/SIO error (channel 2)
                DCD     INTUART0RX_IRQHandler     ; 48:	UART reception (channel 0)
                DCD     INTUART0TX_IRQHandler     ; 49:	UART transmit (channel 0)
                DCD     INTUART0ERR_IRQHandler    ; 50:	UART error (channel 0)
                DCD     INTUART1RX_IRQHandler     ; 51:	UART reception (channel 1)
                DCD     INTUART1TX_IRQHandler     ; 52:	UART transmit (channel 1)
                DCD     INTUART1ERR_IRQHandler    ; 53:	UART error (channel 1)
                DCD     INTUART2RX_IRQHandler     ; 54:	UART reception (channel 2)
                DCD     INTUART2TX_IRQHandler     ; 55:	UART transmit (channel 2)
                DCD     INTUART2ERR_IRQHandler    ; 56:	UART error (channel 2)
                DCD     INTPARI0_IRQHandler       ; 57:	RAM parity ch0 Parity error interrupt
                DCD     INTFLCRDY_IRQHandler      ; 58:	Code FLASH Ready interrupt
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

                PUBWEAK INT00_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT00_IRQHandler
                B       INT00_IRQHandler

                PUBWEAK INT01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT01_IRQHandler
                B       INT01_IRQHandler

                PUBWEAK INT02_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT02_IRQHandler
                B       INT02_IRQHandler

                PUBWEAK INT03_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT03_IRQHandler
                B       INT03_IRQHandler

                PUBWEAK INT04_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT04_IRQHandler
                B       INT04_IRQHandler

                PUBWEAK INT05_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT05_IRQHandler
                B       INT05_IRQHandler

                PUBWEAK INT06_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT06_IRQHandler
                B       INT06_IRQHandler

                PUBWEAK INTT32A00_AT_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00_AT_CT_IRQHandler
                B       INTT32A00_AT_CT_IRQHandler

                PUBWEAK INTT32A00_A01_C0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00_A01_C0_IRQHandler
                B       INTT32A00_A01_C0_IRQHandler

                PUBWEAK INTT32A00_BT_C1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00_BT_C1_IRQHandler
                B       INTT32A00_BT_C1_IRQHandler

                PUBWEAK INTT32A00_B01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00_B01_IRQHandler
                B       INTT32A00_B01_IRQHandler

                PUBWEAK INTT32A01_AT_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01_AT_CT_IRQHandler
                B       INTT32A01_AT_CT_IRQHandler

                PUBWEAK INTT32A01_A01_C0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01_A01_C0_IRQHandler
                B       INTT32A01_A01_C0_IRQHandler

                PUBWEAK INTT32A01_BT_C1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01_BT_C1_IRQHandler
                B       INTT32A01_BT_C1_IRQHandler

                PUBWEAK INTT32A01_B01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01_B01_IRQHandler
                B       INTT32A01_B01_IRQHandler

                PUBWEAK INTT32A02_AT_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02_AT_CT_IRQHandler
                B       INTT32A02_AT_CT_IRQHandler

                PUBWEAK INTT32A02_A01_C0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02_A01_C0_IRQHandler
                B       INTT32A02_A01_C0_IRQHandler

                PUBWEAK INTT32A02_BT_C1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02_BT_C1_IRQHandler
                B       INTT32A02_BT_C1_IRQHandler

                PUBWEAK INTT32A02_B01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02_B01_IRQHandler
                B       INTT32A02_B01_IRQHandler

                PUBWEAK INTT32A03_AT_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03_AT_CT_IRQHandler
                B       INTT32A03_AT_CT_IRQHandler

                PUBWEAK INTT32A03_A01_C0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03_A01_C0_IRQHandler
                B       INTT32A03_A01_C0_IRQHandler

                PUBWEAK INTT32A03_BT_C1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03_BT_C1_IRQHandler
                B       INTT32A03_BT_C1_IRQHandler

                PUBWEAK INTT32A03_B01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03_B01_IRQHandler
                B       INTT32A03_B01_IRQHandler

                PUBWEAK INTVCN0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTVCN0_IRQHandler
                B       INTVCN0_IRQHandler

                PUBWEAK INTVCT0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTVCT0_IRQHandler
                B       INTVCT0_IRQHandler

                PUBWEAK INTEMG0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEMG0_IRQHandler
                B       INTEMG0_IRQHandler

                PUBWEAK INTOVV0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTOVV0_IRQHandler
                B       INTOVV0_IRQHandler

                PUBWEAK INTPWM0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPWM0_IRQHandler
                B       INTPWM0_IRQHandler

                PUBWEAK INTENC00_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC00_IRQHandler
                B       INTENC00_IRQHandler

                PUBWEAK INTENC01_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC01_IRQHandler
                B       INTENC01_IRQHandler

                PUBWEAK INTADAPDA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAPDA_IRQHandler
                B       INTADAPDA_IRQHandler

                PUBWEAK INTADAPDB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAPDB_IRQHandler
                B       INTADAPDB_IRQHandler

                PUBWEAK INTADACP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADACP0_IRQHandler
                B       INTADACP0_IRQHandler

                PUBWEAK INTADACP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADACP1_IRQHandler
                B       INTADACP1_IRQHandler

                PUBWEAK INTADATRG_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADATRG_IRQHandler
                B       INTADATRG_IRQHandler

                PUBWEAK INTADASGL_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADASGL_IRQHandler
                B       INTADASGL_IRQHandler

                PUBWEAK INTADACNT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADACNT_IRQHandler
                B       INTADACNT_IRQHandler

                PUBWEAK INTT0RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT0RX_IRQHandler
                B       INTT0RX_IRQHandler

                PUBWEAK INTT0TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT0TX_IRQHandler
                B       INTT0TX_IRQHandler

                PUBWEAK INTT0ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT0ERR_IRQHandler
                B       INTT0ERR_IRQHandler

                PUBWEAK INTT1RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT1RX_IRQHandler
                B       INTT1RX_IRQHandler

                PUBWEAK INTT1TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT1TX_IRQHandler
                B       INTT1TX_IRQHandler

                PUBWEAK INTT1ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT1ERR_IRQHandler
                B       INTT1ERR_IRQHandler

                PUBWEAK INTT2RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT2RX_IRQHandler
                B       INTT2RX_IRQHandler

                PUBWEAK INTT2TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT2TX_IRQHandler
                B       INTT2TX_IRQHandler

                PUBWEAK INTT2ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT2ERR_IRQHandler
                B       INTT2ERR_IRQHandler

                PUBWEAK INTUART0RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART0RX_IRQHandler
                B       INTUART0RX_IRQHandler

                PUBWEAK INTUART0TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART0TX_IRQHandler
                B       INTUART0TX_IRQHandler

                PUBWEAK INTUART0ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART0ERR_IRQHandler
                B       INTUART0ERR_IRQHandler

                PUBWEAK INTUART1RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART1RX_IRQHandler
                B       INTUART1RX_IRQHandler

                PUBWEAK INTUART1TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART1TX_IRQHandler
                B       INTUART1TX_IRQHandler

                PUBWEAK INTUART1ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART1ERR_IRQHandler
                B       INTUART1ERR_IRQHandler

                PUBWEAK INTUART2RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART2RX_IRQHandler
                B       INTUART2RX_IRQHandler

                PUBWEAK INTUART2TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART2TX_IRQHandler
                B       INTUART2TX_IRQHandler

                PUBWEAK INTUART2ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART2ERR_IRQHandler
                B       INTUART2ERR_IRQHandler

                PUBWEAK INTPARI0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPARI0_IRQHandler
                B       INTPARI0_IRQHandler

                PUBWEAK INTFLCRDY_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTFLCRDY_IRQHandler
                B       INTFLCRDY_IRQHandler

                END
