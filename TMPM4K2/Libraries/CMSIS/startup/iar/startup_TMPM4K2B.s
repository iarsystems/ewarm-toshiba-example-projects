;/**
; *******************************************************************************
; * @file    startup_TMPM4K2B.s
; * @brief   CMSIS Cortex-M4 Core Device Startup File for the
; *          TOSHIBA 'TMPM4K2B' Device Series
; * @version V1.0.0.0
; * 
; * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
; * 
;  * Copyright(C) Toshiba Electronic Device Solutions Corporation 2024
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
                DCD     INT00_IRQHandler          ; 0:	Interrupt pin 00a/00b
                DCD     INT01_IRQHandler          ; 1:	Interrupt pin 01a/01b
                DCD     INT02_IRQHandler          ; 2:	Interrupt pin 02a/02b
                DCD     INT03_IRQHandler          ; 3:	Interrupt pin 03a/03b
                DCD     INT04_IRQHandler          ; 4:	Interrupt pin 04
                DCD     INT05_IRQHandler          ; 5:	Interrupt pin 05
                DCD     INT06_IRQHandler          ; 6:	Interrupt pin 06
                DCD     INT07_IRQHandler          ; 7:	Interrupt pin 07a/07b
                DCD     INT08_IRQHandler          ; 8:	Interrupt pin 08
                DCD     INT09_IRQHandler          ; 9:	Interrupt pin 09
                DCD     0                         ; 10:	Reserved
                DCD     0                         ; 11:	Reserved
                DCD     0                         ; 12:	Reserved
                DCD     INTEMG0_IRQHandler        ; 13:	A-PMD ch0 EMG interrupt
                DCD     INTEMG1_IRQHandler        ; 14:	A-PMD ch1 EMG interrupt
                DCD     INTOVV0_IRQHandler        ; 15:	A-PMD ch0 OVV interrupt
                DCD     INTOVV1_IRQHandler        ; 16:	A-PMD ch1 OVV interrupt
                DCD     INTPWM0_IRQHandler        ; 17:	A-PMD ch0 PWM interrupt
                DCD     INTPWM1_IRQHandler        ; 18:	A-PMD ch1 PWM interrupt
                DCD     INTENC00_IRQHandler       ; 19:	A-ENC32 ch0 Encoder input interrupt 0
                DCD     INTENC01_IRQHandler       ; 20:	A-ENC32 ch0 Encoder input interrupt 1
                DCD     INTADAPDA_IRQHandler      ; 21:	ADC unit A PMD trigger interrupt A
                DCD     INTADAPDB_IRQHandler      ; 22:	ADC unit A PMD trigger interrupt B
                DCD     0                         ; 23:	Reserved
                DCD     0                         ; 24:	Reserved
                DCD     0                         ; 25:	Reserved
                DCD     INTADACP0_IRQHandler      ; 26:	ADC unit A Monitor function 0 interrupt
                DCD     INTADACP1_IRQHandler      ; 27:	ADC unit A Monitor function 1 interrupt
                DCD     INTADATRG_IRQHandler      ; 28:	ADC unit A General-purpose trigger interrupt
                DCD     INTADASGL_IRQHandler      ; 29:	ADC unit A Single conversion interrupt
                DCD     INTADACNT_IRQHandler      ; 30:	ADC unit A Continuous conversion interrupt
                DCD     INTSC0RX_IRQHandler       ; 31:	TSPI ch0 Receive interrupt/UART ch0 Reception interrupt
                DCD     INTSC0TX_IRQHandler       ; 32:	TSPI ch0 Transmit interrupt/UART ch0 Transmission interrupt
                DCD     INTSC0ERR_IRQHandler      ; 33:	TSPI ch0 Error interrupt/UART ch0 Error interrupt
                DCD     INTSC1RX_IRQHandler       ; 34:	TSPI ch1 Receive interrupt/UART ch1 Reception interrupt
                DCD     INTSC1TX_IRQHandler       ; 35:	TSPI ch1 Transmit interrupt/UART ch1 Transmission interrupt
                DCD     INTSC1ERR_IRQHandler      ; 36:	TSPI ch1 Error interrupt/UART ch1 Error interrupt
                DCD     INTSC2RX_IRQHandler       ; 37:	TSPI ch2 Receive interrupt/UART ch2 Reception interrupt
                DCD     INTSC2TX_IRQHandler       ; 38:	TSPI ch2 Transmit interrupt/UART ch2 Transmission interrupt
                DCD     INTSC2ERR_IRQHandler      ; 39:	TSPI ch2 Error interrupt/UART ch2 Error interrupt
                DCD     0                         ; 40:	Reserved
                DCD     0                         ; 41:	Reserved
                DCD     0                         ; 42:	Reserved
                DCD     INTI2C0NST_IRQHandler     ; 43:	I2C ch0 interrupt /EI2C ch0 status interrupt
                DCD     INTI2C0ATX_IRQHandler     ; 44:	I2C ch0 arbitration lost detection interrupt/EI2C ch0 transmit buffer empty interrupt
                DCD     INTI2C0BRX_IRQHandler     ; 45:	I2C ch0 bus free detection interrupt/EI2C ch0 receive buffer full interrupt
                DCD     INTI2C0NA_IRQHandler      ; 46:	I2C ch0 I2C NACK detection interrupt
                DCD     INTT32A00AC_IRQHandler    ; 47:	T32A ch0 timer A/C match, overflow, and underflow
                DCD     INTT32A00ACCAP0_IRQHandler; 48:	T32A ch0 timer A/C capture 0
                DCD     INTT32A00ACCAP1_IRQHandler; 49:	T32A ch0 timer A/C capture 1
                DCD     INTT32A00B_IRQHandler     ; 50:	T32A ch0 timer B match, overflow, and underflow
                DCD     INTT32A00BCAP0_IRQHandler ; 51:	T32A ch0 timer B capture 0
                DCD     INTT32A00BCAP1_IRQHandler ; 52:	T32A ch0 timer B capture 1
                DCD     INTT32A01AC_IRQHandler    ; 53:	T32A ch1 timer A/C match, overflow, and underflow
                DCD     INTT32A01ACCAP0_IRQHandler; 54:	T32A ch1 timer A/C capture 0
                DCD     INTT32A01ACCAP1_IRQHandler; 55:	T32A ch1 timer A/C capture 1
                DCD     INTT32A01B_IRQHandler     ; 56:	T32A ch1 timer B match, overflow, and underflow
                DCD     INTT32A01BCAP0_IRQHandler ; 57:	T32A ch1 timer B capture 0
                DCD     INTT32A01BCAP1_IRQHandler ; 58:	T32A ch1 timer B capture 1
                DCD     INTT32A02AC_IRQHandler    ; 59:	T32A ch2 timer A/C match, overflow, and underflow
                DCD     INTT32A02ACCAP0_IRQHandler; 60:	T32A ch2 timer A/C capture 0
                DCD     INTT32A02ACCAP1_IRQHandler; 61:	T32A ch2 timer A/C capture 1
                DCD     INTT32A02B_IRQHandler     ; 62:	T32A ch2 timer B match, overflow, and underflow
                DCD     INTT32A02BCAP0_IRQHandler ; 63:	T32A ch2 timer B capture 0
                DCD     INTT32A02BCAP1_IRQHandler ; 64:	T32A ch2 timer B capture 1
                DCD     INTT32A03AC_IRQHandler    ; 65:	T32A ch3 timer A/C match, overflow, and underflow
                DCD     INTT32A03ACCAP0_IRQHandler; 66:	T32A ch3 timer A/C capture 0
                DCD     INTT32A03ACCAP1_IRQHandler; 67:	T32A ch3 timer A/C capture 1
                DCD     INTT32A03B_IRQHandler     ; 68:	T32A ch3 timer B match, overflow, and underflow
                DCD     INTT32A03BCAP0_IRQHandler ; 69:	T32A ch3 timer B capture 0
                DCD     INTT32A03BCAP1_IRQHandler ; 70:	T32A ch3 timer B capture 1
                DCD     INTT32A04AC_IRQHandler    ; 71:	T32A ch4 timer A/C match, overflow, and underflow
                DCD     INTT32A04ACCAP0_IRQHandler; 72:	T32A ch4 timer A/C capture 0
                DCD     INTT32A04ACCAP1_IRQHandler; 73:	T32A ch4 timer A/C capture 1
                DCD     INTT32A04B_IRQHandler     ; 74:	T32A ch4 timer B match, overflow, and underflow
                DCD     INTT32A04BCAP0_IRQHandler ; 75:	T32A ch4 timer B capture 0
                DCD     INTT32A04BCAP1_IRQHandler ; 76:	T32A ch4 timer B capture 1
                DCD     INTT32A05AC_IRQHandler    ; 77:	T32A ch5 timer A/C match, overflow, and underflow
                DCD     INTT32A05ACCAP0_IRQHandler; 78:	T32A ch5 timer A/C capture 0
                DCD     INTT32A05ACCAP1_IRQHandler; 79:	T32A ch5 timer A/C capture 1
                DCD     INTT32A05B_IRQHandler     ; 80:	T32A ch5 timer B match, overflow, and underflow
                DCD     INTT32A05BCAP0_IRQHandler ; 81:	T32A ch5 timer B capture 0
                DCD     INTT32A05BCAP1_IRQHandler ; 82:	T32A ch5 timer B capture 1
                DCD     INTPARI_IRQHandler        ; 83:	RAMP RAM Parity interrupt
                DCD     INTDMAATC_IRQHandler      ; 84:	DMAC unit A transmission end interrupt (ch0 to 31)
                DCD     INTDMAAERR_IRQHandler     ; 85:	DMAC unit A transmission error interrupt (ch0 to 31)
                DCD     0                         ; 86:	Reserved
                DCD     INTFLCRDY_IRQHandler      ; 87:	Code FLASH Ready interrupt
                DCD     0                         ; 88:	Reserved
                DCD     INTENC10_IRQHandler       ; 89:	A-ENC32 ch1 Encoder input interrupt 0
                DCD     INTENC11_IRQHandler       ; 90:	A-ENC32 ch1 Encoder input interrupt 1
                DCD     INTADBPDA_IRQHandler      ; 91:	ADC unit B PMD trigger interrupt A
                DCD     INTADBPDB_IRQHandler      ; 92:	ADC unit B PMD trigger interrupt B
                DCD     INTADBCP0_IRQHandler      ; 93:	ADC unit B Monitor function 0 interrupt
                DCD     INTADBCP1_IRQHandler      ; 94:	ADC unit B Monitor function 1 interrupt
                DCD     INTADBTRG_IRQHandler      ; 95:	ADC unit B General-purpose trigger interrupt
                DCD     INTADBSGL_IRQHandler      ; 96:	ADC unit B Single conversion interrupt
                DCD     INTADBCNT_IRQHandler      ; 97:	ADC unit B Continuous conversion interrupt
                DCD     INTADCCMP_IRQHandler      ; 98:	ADC Conversion result compare interrupt
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

                PUBWEAK INTI2C0NST_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0NST_IRQHandler
                B       INTI2C0NST_IRQHandler

                PUBWEAK INTI2C0ATX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0ATX_IRQHandler
                B       INTI2C0ATX_IRQHandler

                PUBWEAK INTI2C0BRX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0BRX_IRQHandler
                B       INTI2C0BRX_IRQHandler

                PUBWEAK INTI2C0NA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0NA_IRQHandler
                B       INTI2C0NA_IRQHandler

                PUBWEAK INTT32A00AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00AC_IRQHandler
                B       INTT32A00AC_IRQHandler

                PUBWEAK INTT32A00ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00ACCAP0_IRQHandler
                B       INTT32A00ACCAP0_IRQHandler

                PUBWEAK INTT32A00ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00ACCAP1_IRQHandler
                B       INTT32A00ACCAP1_IRQHandler

                PUBWEAK INTT32A00B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00B_IRQHandler
                B       INTT32A00B_IRQHandler

                PUBWEAK INTT32A00BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00BCAP0_IRQHandler
                B       INTT32A00BCAP0_IRQHandler

                PUBWEAK INTT32A00BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00BCAP1_IRQHandler
                B       INTT32A00BCAP1_IRQHandler

                PUBWEAK INTT32A01AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01AC_IRQHandler
                B       INTT32A01AC_IRQHandler

                PUBWEAK INTT32A01ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01ACCAP0_IRQHandler
                B       INTT32A01ACCAP0_IRQHandler

                PUBWEAK INTT32A01ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01ACCAP1_IRQHandler
                B       INTT32A01ACCAP1_IRQHandler

                PUBWEAK INTT32A01B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01B_IRQHandler
                B       INTT32A01B_IRQHandler

                PUBWEAK INTT32A01BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01BCAP0_IRQHandler
                B       INTT32A01BCAP0_IRQHandler

                PUBWEAK INTT32A01BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01BCAP1_IRQHandler
                B       INTT32A01BCAP1_IRQHandler

                PUBWEAK INTT32A02AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02AC_IRQHandler
                B       INTT32A02AC_IRQHandler

                PUBWEAK INTT32A02ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02ACCAP0_IRQHandler
                B       INTT32A02ACCAP0_IRQHandler

                PUBWEAK INTT32A02ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02ACCAP1_IRQHandler
                B       INTT32A02ACCAP1_IRQHandler

                PUBWEAK INTT32A02B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02B_IRQHandler
                B       INTT32A02B_IRQHandler

                PUBWEAK INTT32A02BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02BCAP0_IRQHandler
                B       INTT32A02BCAP0_IRQHandler

                PUBWEAK INTT32A02BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02BCAP1_IRQHandler
                B       INTT32A02BCAP1_IRQHandler

                PUBWEAK INTT32A03AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03AC_IRQHandler
                B       INTT32A03AC_IRQHandler

                PUBWEAK INTT32A03ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03ACCAP0_IRQHandler
                B       INTT32A03ACCAP0_IRQHandler

                PUBWEAK INTT32A03ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03ACCAP1_IRQHandler
                B       INTT32A03ACCAP1_IRQHandler

                PUBWEAK INTT32A03B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03B_IRQHandler
                B       INTT32A03B_IRQHandler

                PUBWEAK INTT32A03BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03BCAP0_IRQHandler
                B       INTT32A03BCAP0_IRQHandler

                PUBWEAK INTT32A03BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03BCAP1_IRQHandler
                B       INTT32A03BCAP1_IRQHandler

                PUBWEAK INTT32A04AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A04AC_IRQHandler
                B       INTT32A04AC_IRQHandler

                PUBWEAK INTT32A04ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A04ACCAP0_IRQHandler
                B       INTT32A04ACCAP0_IRQHandler

                PUBWEAK INTT32A04ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A04ACCAP1_IRQHandler
                B       INTT32A04ACCAP1_IRQHandler

                PUBWEAK INTT32A04B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A04B_IRQHandler
                B       INTT32A04B_IRQHandler

                PUBWEAK INTT32A04BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A04BCAP0_IRQHandler
                B       INTT32A04BCAP0_IRQHandler

                PUBWEAK INTT32A04BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A04BCAP1_IRQHandler
                B       INTT32A04BCAP1_IRQHandler

                PUBWEAK INTT32A05AC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A05AC_IRQHandler
                B       INTT32A05AC_IRQHandler

                PUBWEAK INTT32A05ACCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A05ACCAP0_IRQHandler
                B       INTT32A05ACCAP0_IRQHandler

                PUBWEAK INTT32A05ACCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A05ACCAP1_IRQHandler
                B       INTT32A05ACCAP1_IRQHandler

                PUBWEAK INTT32A05B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A05B_IRQHandler
                B       INTT32A05B_IRQHandler

                PUBWEAK INTT32A05BCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A05BCAP0_IRQHandler
                B       INTT32A05BCAP0_IRQHandler

                PUBWEAK INTT32A05BCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A05BCAP1_IRQHandler
                B       INTT32A05BCAP1_IRQHandler

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

                PUBWEAK INTENC10_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC10_IRQHandler
                B       INTENC10_IRQHandler

                PUBWEAK INTENC11_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC11_IRQHandler
                B       INTENC11_IRQHandler

                PUBWEAK INTADBPDA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBPDA_IRQHandler
                B       INTADBPDA_IRQHandler

                PUBWEAK INTADBPDB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBPDB_IRQHandler
                B       INTADBPDB_IRQHandler

                PUBWEAK INTADBCP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBCP0_IRQHandler
                B       INTADBCP0_IRQHandler

                PUBWEAK INTADBCP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBCP1_IRQHandler
                B       INTADBCP1_IRQHandler

                PUBWEAK INTADBTRG_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBTRG_IRQHandler
                B       INTADBTRG_IRQHandler

                PUBWEAK INTADBSGL_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBSGL_IRQHandler
                B       INTADBSGL_IRQHandler

                PUBWEAK INTADBCNT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBCNT_IRQHandler
                B       INTADBCNT_IRQHandler

                PUBWEAK INTADCCMP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCCMP_IRQHandler
                B       INTADCCMP_IRQHandler

                END
