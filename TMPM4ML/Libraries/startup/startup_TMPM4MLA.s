;/**
; *******************************************************************************
; * @file    startup_TMPM4MLA.s
; * @brief   CMSIS Cortex-M4 Core Device Startup File for the
; *          TOSHIBA 'TMPM4MLA' Device Series
; * @version V1.0.0.0
; * 
; * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
; * 
;  * Copyright(C) Toshiba Electronic Device Solutions Corporation 2023
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
                DCD     INT01_IRQHandler          ; 1:	Interrupt pin 01a/01b
                DCD     INT02_IRQHandler          ; 2:	Interrupt pin 02a/02b
                DCD     INT03_IRQHandler          ; 3:	Interrupt pin 03a/03b
                DCD     INT04_IRQHandler          ; 4:	Interrupt pin 04a/04b
                DCD     INT05_IRQHandler          ; 5:	Interrupt pin 05a/05b
                DCD     INT06_IRQHandler          ; 6:	Interrupt pin 06a/06b
                DCD     INT07_IRQHandler          ; 7:	Interrupt pin 07a/07b
                DCD     INT08_IRQHandler          ; 8:	Interrupt pin 08a/08b
                DCD     INT09_IRQHandler          ; 9:	Interrupt pin 09
                DCD     INT10_IRQHandler          ; 10:	Interrupt pin 10
                DCD     INT11_IRQHandler          ; 11:	Interrupt pin 11a/11b
                DCD     INT12_IRQHandler          ; 12:	Interrupt pin 12
                DCD     INT13_IRQHandler          ; 13:	Interrupt pin 13
                DCD     0                         ; 14:	Reserved
                DCD     0                         ; 15:	Reserved
                DCD     0                         ; 16:	Reserved
                DCD     0                         ; 17:	Reserved
                DCD     0                         ; 18:	Reserved
                DCD     0                         ; 19:	Reserved
                DCD     0                         ; 20:	Reserved
                DCD     INT21_IRQHandler          ; 21:	Interrupt pin 21
                DCD     INTVCN0_IRQHandler        ; 22:	A-VE+ ch0 Interrupt
                DCD     INTVCT0_IRQHandler        ; 23:	A-VE+ ch0 Task termination interrupt
                DCD     INTEMG0_IRQHandler        ; 24:	A-PMD ch0 EMG interrupt
                DCD     INTEMG1_IRQHandler        ; 25:	A-PMD ch1 EMG interrupt
                DCD     INTEMG2_IRQHandler        ; 26:	A-PMD ch2 EMG interrupt
                DCD     INTOVV0_IRQHandler        ; 27:	A-PMD ch0 OVV interrupt
                DCD     INTOVV1_IRQHandler        ; 28:	A-PMD ch1 OVV interrupt
                DCD     INTOVV2_IRQHandler        ; 29:	A-PMD ch2 OVV interrupt
                DCD     INTPWM0_IRQHandler        ; 30:	A-PMD ch0 PWM interrupt
                DCD     INTPWM1_IRQHandler        ; 31:	A-PMD ch1 PWM interrupt
                DCD     INTPWM2_IRQHandler        ; 32:	A-PMD ch2 PWM interrupt
                DCD     0                         ; 33:	Reserved
                DCD     0                         ; 34:	Reserved
                DCD     0                         ; 35:	Reserved
                DCD     0                         ; 36:	Reserved
                DCD     INTENC20_IRQHandler       ; 37:	A-ENC32 ch2 Encoder interrupt 0
                DCD     INTENC21_IRQHandler       ; 38:	A-ENC32 ch2 Encoder interrupt 1
                DCD     INTADAPDA_IRQHandler      ; 39:	ADC unit A PMD trigger program interrupt A
                DCD     INTADAPDB_IRQHandler      ; 40:	ADC unit A PMD trigger program interrupt B
                DCD     INTADACP0_IRQHandler      ; 41:	ADC unit A Monitor function 0 interrupt
                DCD     INTADACP1_IRQHandler      ; 42:	ADC unit A Monitor function 1 interrupt
                DCD     INTADATRG_IRQHandler      ; 43:	ADC unit A General purpose trigger program interrupt
                DCD     INTADASGL_IRQHandler      ; 44:	ADC unit A Single program interrupt
                DCD     INTADACNT_IRQHandler      ; 45:	ADC unit A Continuity program interrupt
                DCD     INTADBPDA_IRQHandler      ; 46:	ADC unit B PMD trigger program interrupt A
                DCD     INTADBPDB_IRQHandler      ; 47:	ADC unit B PMD trigger program interrupt B
                DCD     INTADBCP0_IRQHandler      ; 48:	ADC unit B Monitor function 0 interrupt
                DCD     INTADBCP1_IRQHandler      ; 49:	ADC unit B Monitor function 1 interrupt
                DCD     INTADBTRG_IRQHandler      ; 50:	ADC unit B General purpose trigger program interrupt
                DCD     INTADBSGL_IRQHandler      ; 51:	ADC unit B Single program interrupt
                DCD     INTADBCNT_IRQHandler      ; 52:	ADC unit B Continuity program interrupt
                DCD     INTADCPDA_IRQHandler      ; 53:	ADC unit C PMD trigger program interrupt A
                DCD     INTADCPDB_IRQHandler      ; 54:	ADC unit C PMD trigger program interrupt B
                DCD     INTADCCP0_IRQHandler      ; 55:	ADC unit C Monitor function 0 interrupt
                DCD     INTADCCP1_IRQHandler      ; 56:	ADC unit C Monitor function 1 interrupt
                DCD     INTADCTRG_IRQHandler      ; 57:	ADC unit C General purpose trigger program interrupt
                DCD     INTADCSGL_IRQHandler      ; 58:	ADC unit C Single program interrupt
                DCD     INTADCCNT_IRQHandler      ; 59:	ADC unit C Continuity program interrupt
                DCD     INTSC0RX_IRQHandler       ; 60:	TSPI/UART ch0 Reception interrupt
                DCD     INTSC0TX_IRQHandler       ; 61:	TSPI/UART ch0 Transmit interrupt
                DCD     INTSC0ERR_IRQHandler      ; 62:	TSPI/UART ch0 Error interrupt
                DCD     INTSC1RX_IRQHandler       ; 63:	TSPI/UART ch1 Reception interrupt
                DCD     INTSC1TX_IRQHandler       ; 64:	TSPI/UART ch1 Transmit interrupt
                DCD     INTSC1ERR_IRQHandler      ; 65:	TSPI/UART ch1 Error interrupt
                DCD     INTSC2RX_IRQHandler       ; 66:	UART ch2 Reception interrupt
                DCD     INTSC2TX_IRQHandler       ; 67:	UART ch2 Transmit interrupt
                DCD     INTSC2ERR_IRQHandler      ; 68:	UART ch2 Error interrupt
                DCD     0                         ; 69:	Reserved
                DCD     0                         ; 70:	Reserved
                DCD     0                         ; 71:	Reserved
                DCD     INTI2C0NST_IRQHandler     ; 72:	I2C ch0 Interrupt / EI2C ch0 Status interrupt
                DCD     INTI2C0ATX_IRQHandler     ; 73:	I2C ch0 Arbitration lost detection interrupt / EI2C ch0 Transmission buffer empty interrupt
                DCD     INTI2C0BRX_IRQHandler     ; 74:	I2C ch0 Bus free detection interrupt / EI2C ch0 Reception buffer full interrupt
                DCD     INTI2C0NA_IRQHandler      ; 75:	I2C ch0 NACK detection interrupt
                DCD     INTI2C1NST_IRQHandler     ; 76:	I2C ch1 Interrupt / EI2C ch1 Status interrupt
                DCD     INTI2C1ATX_IRQHandler     ; 77:	I2C ch1 Arbitration lost detection interrupt / EI2C ch1 Transmission buffer empty interrupt
                DCD     INTI2C1BRX_IRQHandler     ; 78:	I2C ch1 Bus free detection interrupt / EI2C ch1 Reception buffer full interrupt
                DCD     INTI2C1NA_IRQHandler      ; 79:	I2C ch1 NACK detection interrupt
                DCD     INTCANAGLB_IRQHandler     ; 80:	CAN unit A Global interrupt
                DCD     INTCANARXD_IRQHandler     ; 81:	CAN unit A Receive completion interrupt
                DCD     INTCANATXD_IRQHandler     ; 82:	CAN unit A Transmit completion interrupt
                DCD     INTT32A00AC_IRQHandler    ; 83:	T32A ch0 Timer A/C Compare match detection / Over flow / Under flow
                DCD     INTT32A00ACCAP0_IRQHandler; 84:	T32A ch0 Timer A/C Input capture 0
                DCD     INTT32A00ACCAP1_IRQHandler; 85:	T32A ch0 Timer A/C Input capture 1
                DCD     INTT32A00B_IRQHandler     ; 86:	T32A ch0 Timer B Compare match detection / Over flow / Under flow
                DCD     INTT32A00BCAP0_IRQHandler ; 87:	T32A ch0 Timer B Input capture 0
                DCD     INTT32A00BCAP1_IRQHandler ; 88:	T32A ch0 Timer B Input capture 1
                DCD     INTT32A01AC_IRQHandler    ; 89:	T32A ch1 Timer A/C Compare match detection / Over flow / Under flow
                DCD     INTT32A01ACCAP0_IRQHandler; 90:	T32A ch1 Timer A/C Input capture 0
                DCD     INTT32A01ACCAP1_IRQHandler; 91:	T32A ch1 Timer A/C Input capture 1
                DCD     INTT32A01B_IRQHandler     ; 92:	T32A ch1 Timer B Compare match detection / Over flow / Under flow
                DCD     INTT32A01BCAP0_IRQHandler ; 93:	T32A ch1 Timer B Input capture 0
                DCD     INTT32A01BCAP1_IRQHandler ; 94:	T32A ch1 Timer B Input capture 1
                DCD     INTT32A02AC_IRQHandler    ; 95:	T32A ch2 Timer A/C Compare match detection / Over flow / Under flow
                DCD     INTT32A02ACCAP0_IRQHandler; 96:	T32A ch2 Timer A/C Input capture 0
                DCD     INTT32A02ACCAP1_IRQHandler; 97:	T32A ch2 Timer A/C Input capture 1
                DCD     INTT32A02B_IRQHandler     ; 98:	T32A ch2 Timer B Compare match detection / Over flow / Under flow
                DCD     INTT32A02BCAP0_IRQHandler ; 99:	T32A ch2 Timer B Input capture 0
                DCD     INTT32A02BCAP1_IRQHandler ; 100:	T32A ch2 Timer B Input capture 1
                DCD     INTT32A03AC_IRQHandler    ; 101:	T32A ch3 Timer A/C Compare match detection / Over flow / Under flow
                DCD     INTT32A03ACCAP0_IRQHandler; 102:	T32A ch3 Timer A/C Input capture 0
                DCD     INTT32A03ACCAP1_IRQHandler; 103:	T32A ch3 Timer A/C Input capture 1
                DCD     INTT32A03B_IRQHandler     ; 104:	T32A ch3 Timer B Compare match detection / Over flow / Under flow
                DCD     INTT32A03BCAP0_IRQHandler ; 105:	T32A ch3 Timer B Input capture 0
                DCD     INTT32A03BCAP1_IRQHandler ; 106:	T32A ch3 Timer B Input capture 1
                DCD     INTT32A04AC_IRQHandler    ; 107:	T32A ch4 Timer A/C Compare match detection / Over flow / Under flow
                DCD     INTT32A04ACCAP0_IRQHandler; 108:	T32A ch4 Timer A/C Input capture 0
                DCD     INTT32A04ACCAP1_IRQHandler; 109:	T32A ch4 Timer A/C Input capture 1
                DCD     INTT32A04B_IRQHandler     ; 110:	T32A ch4 Timer B Compare match detection / Over flow / Under flow
                DCD     INTT32A04BCAP0_IRQHandler ; 111:	T32A ch4 Timer B Input capture 0
                DCD     INTT32A04BCAP1_IRQHandler ; 112:	T32A ch4 Timer B Input capture 1
                DCD     INTT32A05AC_IRQHandler    ; 113:	T32A ch5 Timer A/C Compare match detection / Over flow / Under flow
                DCD     INTT32A05ACCAP0_IRQHandler; 114:	T32A ch5 Timer A/C Input capture 0
                DCD     INTT32A05ACCAP1_IRQHandler; 115:	T32A ch5 Timer A/C Input capture 1
                DCD     INTT32A05B_IRQHandler     ; 116:	T32A ch5 Timer B Compare match detection / Over flow / Under flow
                DCD     INTT32A05BCAP0_IRQHandler ; 117:	T32A ch5 Timer B Input capture 0
                DCD     INTT32A05BCAP1_IRQHandler ; 118:	T32A ch5 Timer B Input capture 1
                DCD     INTPARI0_IRQHandler       ; 119:	RAMP ch0 Parity error interrupt
                DCD     INTPARI1_IRQHandler       ; 120:	RAMP ch1 Parity error interrupt
                DCD     INTDMAATC_IRQHandler      ; 121:	DMAC unit A End of transfer (ch0 - 31)
                DCD     INTDMAAERR_IRQHandler     ; 122:	DMAC unit A Transfer error
                DCD     INTFLCRDY_IRQHandler      ; 123:	Code FLASH Ready interrupt
                DCD     INTFLDRDY_IRQHandler      ; 124:	Data FLASH Ready interrupt
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

                PUBWEAK INT10_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT10_IRQHandler
                B       INT10_IRQHandler

                PUBWEAK INT11_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT11_IRQHandler
                B       INT11_IRQHandler

                PUBWEAK INT12_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT12_IRQHandler
                B       INT12_IRQHandler

                PUBWEAK INT13_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT13_IRQHandler
                B       INT13_IRQHandler

                PUBWEAK INT21_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT21_IRQHandler
                B       INT21_IRQHandler

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

                PUBWEAK INTEMG2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEMG2_IRQHandler
                B       INTEMG2_IRQHandler

                PUBWEAK INTOVV0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTOVV0_IRQHandler
                B       INTOVV0_IRQHandler

                PUBWEAK INTOVV1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTOVV1_IRQHandler
                B       INTOVV1_IRQHandler

                PUBWEAK INTOVV2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTOVV2_IRQHandler
                B       INTOVV2_IRQHandler

                PUBWEAK INTPWM0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPWM0_IRQHandler
                B       INTPWM0_IRQHandler

                PUBWEAK INTPWM1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPWM1_IRQHandler
                B       INTPWM1_IRQHandler

                PUBWEAK INTPWM2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPWM2_IRQHandler
                B       INTPWM2_IRQHandler

                PUBWEAK INTENC20_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC20_IRQHandler
                B       INTENC20_IRQHandler

                PUBWEAK INTENC21_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC21_IRQHandler
                B       INTENC21_IRQHandler

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

                PUBWEAK INTADCPDA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCPDA_IRQHandler
                B       INTADCPDA_IRQHandler

                PUBWEAK INTADCPDB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCPDB_IRQHandler
                B       INTADCPDB_IRQHandler

                PUBWEAK INTADCCP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCCP0_IRQHandler
                B       INTADCCP0_IRQHandler

                PUBWEAK INTADCCP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCCP1_IRQHandler
                B       INTADCCP1_IRQHandler

                PUBWEAK INTADCTRG_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCTRG_IRQHandler
                B       INTADCTRG_IRQHandler

                PUBWEAK INTADCSGL_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCSGL_IRQHandler
                B       INTADCSGL_IRQHandler

                PUBWEAK INTADCCNT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCCNT_IRQHandler
                B       INTADCCNT_IRQHandler

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

                PUBWEAK INTI2C1NST_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C1NST_IRQHandler
                B       INTI2C1NST_IRQHandler

                PUBWEAK INTI2C1ATX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C1ATX_IRQHandler
                B       INTI2C1ATX_IRQHandler

                PUBWEAK INTI2C1BRX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C1BRX_IRQHandler
                B       INTI2C1BRX_IRQHandler

                PUBWEAK INTI2C1NA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C1NA_IRQHandler
                B       INTI2C1NA_IRQHandler

                PUBWEAK INTCANAGLB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANAGLB_IRQHandler
                B       INTCANAGLB_IRQHandler

                PUBWEAK INTCANARXD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANARXD_IRQHandler
                B       INTCANARXD_IRQHandler

                PUBWEAK INTCANATXD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANATXD_IRQHandler
                B       INTCANATXD_IRQHandler

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

                PUBWEAK INTPARI0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPARI0_IRQHandler
                B       INTPARI0_IRQHandler

                PUBWEAK INTPARI1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPARI1_IRQHandler
                B       INTPARI1_IRQHandler

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

                PUBWEAK INTFLDRDY_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTFLDRDY_IRQHandler
                B       INTFLDRDY_IRQHandler

                END
