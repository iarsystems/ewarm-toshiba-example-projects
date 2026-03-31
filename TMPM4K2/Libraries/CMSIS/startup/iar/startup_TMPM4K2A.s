;/**
; *******************************************************************************
; * @file    startup_TMPM4K2A.s
; * @brief   CMSIS Cortex-M4 Core Device Startup File for the
; *          TOSHIBA 'TMPM4K2A' Device Series
; * @version V0.0.4.0
; * $Date:: 2018-06-25 #$
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
                DCD     INT00_IRQHandler          ; 0:	Interrupt Pin0
                DCD     INT01_IRQHandler          ; 1:	Interrupt Pin1
                DCD     INT02_IRQHandler          ; 2:	Interrupt Pin2
                DCD     INT03_IRQHandler          ; 3:	Interrupt Pin3
                DCD     INT04_IRQHandler          ; 4:	Interrupt Pin4
                DCD     INT05_IRQHandler          ; 5:	Interrupt Pin5
                DCD     INT06_IRQHandler          ; 6:	Interrupt Pin6
                DCD     INT07_IRQHandler          ; 7:	Interrupt Pin7
                DCD     INT08_IRQHandler          ; 8:	Interrupt Pin8
                DCD     INT09_IRQHandler          ; 9:	Interrupt Pin9
                DCD     0                         ; 10:	Reserved
                DCD     INTVCN0_IRQHandler        ; 11:	A-VE interrupt 0
                DCD     INTVCT0_IRQHandler        ; 12:	A-VE task termination interrupt 0
                DCD     INTEMG0_IRQHandler        ; 13:	PMD0 EMG interrupt
                DCD     INTEMG1_IRQHandler        ; 14:	PMD1 EMG interrupt
                DCD     INTOVV0_IRQHandler        ; 15:	PMD0 OVV interrupt
                DCD     INTOVV1_IRQHandler        ; 16:	PMD1 OVV interrupt
                DCD     INTPWM0_IRQHandler        ; 17:	PMD0 PWM interrupt
                DCD     INTPWM1_IRQHandler        ; 18:	PMD1 PWM interrupt
                DCD     INTENC00_IRQHandler       ; 19:	Encoder 0 interrupt 0
                DCD     INTENC01_IRQHandler       ; 20:	Encoder 0 interrupt 1
                DCD     INTADAPDA_IRQHandler      ; 21:	ADC A conversion triggered by PMD is finished A
                DCD     INTADAPDB_IRQHandler      ; 22:	ADC A conversion triggered by PMD is finished B
                DCD     INTADAPDC_IRQHandler      ; 23:	ADC A conversion triggered by PMD is finished C
                DCD     INTADAPDD_IRQHandler      ; 24:	ADC A conversion triggered by PMD is finished D
                DCD     INTADAPFLG_IRQHandler     ; 25:	ADC A Priority interrupt
                DCD     INTADACP0_IRQHandler      ; 26:	ADC A conversion monitoring function interrupt 0
                DCD     INTADACP1_IRQHandler      ; 27:	ADC A conversion monitoring function interrupt 1
                DCD     INTADATRG_IRQHandler      ; 28:	ADC A conversion triggered by General purpose is finished
                DCD     INTADASGL_IRQHandler      ; 29:	ADC A conversion triggered by Single program is finished
                DCD     INTADACNT_IRQHandler      ; 30:	ADC A conversion triggered by Continuity program is finished
                DCD     INTSC0RX_IRQHandler       ; 31:	TSPI0 / UART0 reception interrupt
                DCD     INTSC0TX_IRQHandler       ; 32:	TSPI0 / UART0 transmit interrupt
                DCD     INTSC0ERR_IRQHandler      ; 33:	TSPI0 / UART0 error interrupt
                DCD     INTSC1RX_IRQHandler       ; 34:	TSPI1 / UART1 reception interrupt
                DCD     INTSC1TX_IRQHandler       ; 35:	TSPI1 / UART1 transmit interrupt
                DCD     INTSC1ERR_IRQHandler      ; 36:	TSPI1 / UART1 error interrupt
                DCD     INTSC2RX_IRQHandler       ; 37:	TSPI2 / UART2 reception interrupt
                DCD     INTSC2TX_IRQHandler       ; 38:	TSPI2 / UART2 transmit interrupt
                DCD     INTSC2ERR_IRQHandler      ; 39:	TSPI2 / UART2 error interrupt
                DCD     0                         ; 40:	Reserved
                DCD     0                         ; 41:	Reserved
                DCD     0                         ; 42:	Reserved
                DCD     INTI2C0_IRQHandler        ; 43:	I2C0 transmission and reception interrupt
                DCD     INTI2C0AL_IRQHandler      ; 44:	I2C0 arbitration lost interrupt
                DCD     INTI2C0BF_IRQHandler      ; 45:	I2C0 bus free interrupt
                DCD     INTI2C0NA_IRQHandler      ; 46:	I2C0 no ack interrupt
                DCD     INTT32A0AC_IRQHandler     ; 47:	T32A0 TimmerA/C compare match detection / Over flow / under flow
                DCD     INTT32A0ACCAP0_IRQHandler ; 48:	T32A0 TimmerA/C input capture 0
                DCD     INTT32A0ACCAP1_IRQHandler ; 49:	T32A0 TimmerA/C input capture 1
                DCD     INTT32A0B_IRQHandler      ; 50:	T32A0 TimmerB compare match detection / Over flow / under flow
                DCD     INTT32A0BCAP0_IRQHandler  ; 51:	T32A0 TimmerB input capture 0
                DCD     INTT32A0BCAP1_IRQHandler  ; 52:	T32A0 TimmerB input capture 1
                DCD     INTT32A1AC_IRQHandler     ; 53:	T32A1 TimmerA/C compare match detection / Over flow / under flow
                DCD     INTT32A1ACCAP0_IRQHandler ; 54:	T32A1 TimmerA/C input capture 0
                DCD     INTT32A1ACCAP1_IRQHandler ; 55:	T32A1 TimmerA/C input capture 1
                DCD     INTT32A1B_IRQHandler      ; 56:	T32A1 TimmerB compare match detection / Over flow / under flow
                DCD     INTT32A1BCAP0_IRQHandler  ; 57:	T32A1 TimmerB input capture 0
                DCD     INTT32A1BCAP1_IRQHandler  ; 58:	T32A1 TimmerB input capture 1
                DCD     INTT32A2AC_IRQHandler     ; 59:	T32A2 TimmerA/C compare match detection / Over flow / under flow
                DCD     INTT32A2ACCAP0_IRQHandler ; 60:	T32A2 TimmerA/C input capture 0
                DCD     INTT32A2ACCAP1_IRQHandler ; 61:	T32A2 TimmerA/C input capture 1
                DCD     INTT32A2B_IRQHandler      ; 62:	T32A2 TimmerB compare match detection / Over flow / under flow
                DCD     INTT32A2BCAP0_IRQHandler  ; 63:	T32A2 TimmerB input capture 0
                DCD     INTT32A2BCAP1_IRQHandler  ; 64:	T32A2 TimmerB input capture 1
                DCD     INTT32A3AC_IRQHandler     ; 65:	T32A3 TimmerA/C compare match detection / Over flow / under flow
                DCD     INTT32A3ACCAP0_IRQHandler ; 66:	T32A3 TimmerA/C input capture 0
                DCD     INTT32A3ACCAP1_IRQHandler ; 67:	T32A3 TimmerA/C input capture 1
                DCD     INTT32A3B_IRQHandler      ; 68:	T32A3 TimmerB compare match detection / Over flow / under flow
                DCD     INTT32A3BCAP0_IRQHandler  ; 69:	T32A3 TimmerB input capture 0
                DCD     INTT32A3BCAP1_IRQHandler  ; 70:	T32A3 TimmerB input capture 1
                DCD     INTT32A4AC_IRQHandler     ; 71:	T32A4 TimmerA/C compare match detection / Over flow / under flow
                DCD     INTT32A4ACCAP0_IRQHandler ; 72:	T32A4 TimmerA/C input capture 0
                DCD     INTT32A4ACCAP1_IRQHandler ; 73:	T32A4 TimmerA/C input capture 1
                DCD     INTT32A4B_IRQHandler      ; 74:	T32A4 TimmerB compare match detection / Over flow / under flow
                DCD     INTT32A4BCAP0_IRQHandler  ; 75:	T32A4 TimmerB input capture 0
                DCD     INTT32A4BCAP1_IRQHandler  ; 76:	T32A4 TimmerB input capture 1
                DCD     INTT32A5AC_IRQHandler     ; 77:	T32A5 TimmerA/C compare match detection / Over flow / under flow
                DCD     INTT32A5ACCAP0_IRQHandler ; 78:	T32A5 TimmerA/C input capture 0
                DCD     INTT32A5ACCAP1_IRQHandler ; 79:	T32A5 TimmerA/C input capture 1
                DCD     INTT32A5B_IRQHandler      ; 80:	T32A5 TimmerB compare match detection / Over flow / under flow
                DCD     INTT32A5BCAP0_IRQHandler  ; 81:	T32A5 TimmerB input capture 0
                DCD     INTT32A5BCAP1_IRQHandler  ; 82:	T32A5 TimmerB input capture 1
                DCD     INTPARI_IRQHandler        ; 83:	RAM parity interrupt
                DCD     INTDMAATC_IRQHandler      ; 84:	DMA end of transfer
                DCD     INTDMAAERR_IRQHandler     ; 85:	DMA transfer error
                DCD     0                         ; 86:	Reserved
                DCD     INTFLCRDY_IRQHandler      ; 87:	Code FLASH Ready interrupt
                DCD     0                         ; 88:	Reserved
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

                PUBWEAK INT07_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT07_IRQHandler
                B       INT07_IRQHandler

                PUBWEAK INT08_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT08_IRQHandler
                B       INT08_IRQHandler

                PUBWEAK INT09_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT09_IRQHandler
                B       INT09_IRQHandler

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

                PUBWEAK INTEMG1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEMG1_IRQHandler
                B       INTEMG1_IRQHandler

                PUBWEAK INTOVV0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTOVV0_IRQHandler
                B       INTOVV0_IRQHandler

                PUBWEAK INTOVV1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTOVV1_IRQHandler
                B       INTOVV1_IRQHandler

                PUBWEAK INTPWM0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPWM0_IRQHandler
                B       INTPWM0_IRQHandler

                PUBWEAK INTPWM1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPWM1_IRQHandler
                B       INTPWM1_IRQHandler

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

                PUBWEAK INTADAPDC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAPDC_IRQHandler
                B       INTADAPDC_IRQHandler

                PUBWEAK INTADAPDD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAPDD_IRQHandler
                B       INTADAPDD_IRQHandler

                PUBWEAK INTADAPFLG_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAPFLG_IRQHandler
                B       INTADAPFLG_IRQHandler

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

                PUBWEAK INTSC0RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC0RX_IRQHandler
                B       INTSC0RX_IRQHandler

                PUBWEAK INTSC0TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC0TX_IRQHandler
                B       INTSC0TX_IRQHandler

                PUBWEAK INTSC0ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC0ERR_IRQHandler
                B       INTSC0ERR_IRQHandler

                PUBWEAK INTSC1RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC1RX_IRQHandler
                B       INTSC1RX_IRQHandler

                PUBWEAK INTSC1TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC1TX_IRQHandler
                B       INTSC1TX_IRQHandler

                PUBWEAK INTSC1ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC1ERR_IRQHandler
                B       INTSC1ERR_IRQHandler

                PUBWEAK INTSC2RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC2RX_IRQHandler
                B       INTSC2RX_IRQHandler

                PUBWEAK INTSC2TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC2TX_IRQHandler
                B       INTSC2TX_IRQHandler

                PUBWEAK INTSC2ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC2ERR_IRQHandler
                B       INTSC2ERR_IRQHandler

                PUBWEAK INTI2C0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0_IRQHandler
                B       INTI2C0_IRQHandler

                PUBWEAK INTI2C0AL_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0AL_IRQHandler
                B       INTI2C0AL_IRQHandler

                PUBWEAK INTI2C0BF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0BF_IRQHandler
                B       INTI2C0BF_IRQHandler

                PUBWEAK INTI2C0NA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0NA_IRQHandler
                B       INTI2C0NA_IRQHandler

                PUBWEAK INTT32A0AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A0AC_IRQHandler
                B       INTT32A0AC_IRQHandler

                PUBWEAK INTT32A0ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A0ACCAP0_IRQHandler
                B       INTT32A0ACCAP0_IRQHandler

                PUBWEAK INTT32A0ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A0ACCAP1_IRQHandler
                B       INTT32A0ACCAP1_IRQHandler

                PUBWEAK INTT32A0B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A0B_IRQHandler
                B       INTT32A0B_IRQHandler

                PUBWEAK INTT32A0BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A0BCAP0_IRQHandler
                B       INTT32A0BCAP0_IRQHandler

                PUBWEAK INTT32A0BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A0BCAP1_IRQHandler
                B       INTT32A0BCAP1_IRQHandler

                PUBWEAK INTT32A1AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A1AC_IRQHandler
                B       INTT32A1AC_IRQHandler

                PUBWEAK INTT32A1ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A1ACCAP0_IRQHandler
                B       INTT32A1ACCAP0_IRQHandler

                PUBWEAK INTT32A1ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A1ACCAP1_IRQHandler
                B       INTT32A1ACCAP1_IRQHandler

                PUBWEAK INTT32A1B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A1B_IRQHandler
                B       INTT32A1B_IRQHandler

                PUBWEAK INTT32A1BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A1BCAP0_IRQHandler
                B       INTT32A1BCAP0_IRQHandler

                PUBWEAK INTT32A1BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A1BCAP1_IRQHandler
                B       INTT32A1BCAP1_IRQHandler

                PUBWEAK INTT32A2AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A2AC_IRQHandler
                B       INTT32A2AC_IRQHandler

                PUBWEAK INTT32A2ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A2ACCAP0_IRQHandler
                B       INTT32A2ACCAP0_IRQHandler

                PUBWEAK INTT32A2ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A2ACCAP1_IRQHandler
                B       INTT32A2ACCAP1_IRQHandler

                PUBWEAK INTT32A2B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A2B_IRQHandler
                B       INTT32A2B_IRQHandler

                PUBWEAK INTT32A2BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A2BCAP0_IRQHandler
                B       INTT32A2BCAP0_IRQHandler

                PUBWEAK INTT32A2BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A2BCAP1_IRQHandler
                B       INTT32A2BCAP1_IRQHandler

                PUBWEAK INTT32A3AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A3AC_IRQHandler
                B       INTT32A3AC_IRQHandler

                PUBWEAK INTT32A3ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A3ACCAP0_IRQHandler
                B       INTT32A3ACCAP0_IRQHandler

                PUBWEAK INTT32A3ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A3ACCAP1_IRQHandler
                B       INTT32A3ACCAP1_IRQHandler

                PUBWEAK INTT32A3B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A3B_IRQHandler
                B       INTT32A3B_IRQHandler

                PUBWEAK INTT32A3BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A3BCAP0_IRQHandler
                B       INTT32A3BCAP0_IRQHandler

                PUBWEAK INTT32A3BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A3BCAP1_IRQHandler
                B       INTT32A3BCAP1_IRQHandler

                PUBWEAK INTT32A4AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A4AC_IRQHandler
                B       INTT32A4AC_IRQHandler

                PUBWEAK INTT32A4ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A4ACCAP0_IRQHandler
                B       INTT32A4ACCAP0_IRQHandler

                PUBWEAK INTT32A4ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A4ACCAP1_IRQHandler
                B       INTT32A4ACCAP1_IRQHandler

                PUBWEAK INTT32A4B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A4B_IRQHandler
                B       INTT32A4B_IRQHandler

                PUBWEAK INTT32A4BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A4BCAP0_IRQHandler
                B       INTT32A4BCAP0_IRQHandler

                PUBWEAK INTT32A4BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A4BCAP1_IRQHandler
                B       INTT32A4BCAP1_IRQHandler

                PUBWEAK INTT32A5AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A5AC_IRQHandler
                B       INTT32A5AC_IRQHandler

                PUBWEAK INTT32A5ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A5ACCAP0_IRQHandler
                B       INTT32A5ACCAP0_IRQHandler

                PUBWEAK INTT32A5ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A5ACCAP1_IRQHandler
                B       INTT32A5ACCAP1_IRQHandler

                PUBWEAK INTT32A5B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A5B_IRQHandler
                B       INTT32A5B_IRQHandler

                PUBWEAK INTT32A5BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A5BCAP0_IRQHandler
                B       INTT32A5BCAP0_IRQHandler

                PUBWEAK INTT32A5BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A5BCAP1_IRQHandler
                B       INTT32A5BCAP1_IRQHandler

                PUBWEAK INTPARI_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPARI_IRQHandler
                B       INTPARI_IRQHandler

                PUBWEAK INTDMAATC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMAATC_IRQHandler
                B       INTDMAATC_IRQHandler

                PUBWEAK INTDMAAERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMAAERR_IRQHandler
                B       INTDMAAERR_IRQHandler

                PUBWEAK INTFLCRDY_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTFLCRDY_IRQHandler
                B       INTFLCRDY_IRQHandler

                END
