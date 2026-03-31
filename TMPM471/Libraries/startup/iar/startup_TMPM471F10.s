;/**
; *******************************************************************************
; * @file    startup_TMPM471F10.s
; * @brief   CMSIS Cortex-M4 Core Device Startup File for the
; *          TOSHIBA 'TMPM471F10' Device Series
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
                DCD     INT0_IRQHandler           ; 0:	External interrupt 0
                DCD     INT1_IRQHandler           ; 1:	External interrupt 1
                DCD     INT2_IRQHandler           ; 2:	External interrupt 2
                DCD     INT3_IRQHandler           ; 3:	External interrupt 3
                DCD     INT4_IRQHandler           ; 4:	External interrupt 4
                DCD     INT5_IRQHandler           ; 5:	External interrupt 5
                DCD     INT6_IRQHandler           ; 6:	External interrupt 6
                DCD     INT7_IRQHandler           ; 7:	External interrupt 7
                DCD     INT8_IRQHandler           ; 8:	External interrupt 8
                DCD     INT9_IRQHandler           ; 9:	External interrupt 9
                DCD     INTA_IRQHandler           ; 10:	External interrupt A
                DCD     INTB_IRQHandler           ; 11:	External interrupt B
                DCD     INTC_IRQHandler           ; 12:	External interrupt C
                DCD     INTD_IRQHandler           ; 13:	External interrupt D
                DCD     INTE_IRQHandler           ; 14:	External interrupt E
                DCD     INTF_IRQHandler           ; 15:	External interrupt F
                DCD     INTEMG0_IRQHandler        ; 16:	A-PMD ch0 EMG Interrupt
                DCD     INTEMG1_IRQHandler        ; 17:	A-PMD ch1 EMG Interrupt
                DCD     INTOVV0_IRQHandler        ; 18:	A-PMD ch0 OVV Interrupt
                DCD     INTOVV1_IRQHandler        ; 19:	A-PMD ch1 OVV Interrupt
                DCD     INTPWM0_IRQHandler        ; 20:	A-PMD ch0 PWM Interrupt
                DCD     INTPWM1_IRQHandler        ; 21:	A-PMD ch1 PWM Interrupt
                DCD     INTENC00_IRQHandler       ; 22:	A-ENC32 ch0 Encoder input interrupt 0
                DCD     INTENC01_IRQHandler       ; 23:	A-ENC32 ch0 Encoder input interrupt 1
                DCD     INTENC10_IRQHandler       ; 24:	A-ENC32 ch1 Encoder input interrupt 0
                DCD     INTENC11_IRQHandler       ; 25:	A-ENC32 ch1 Encoder input interrupt 1
                DCD     INTADAPDA_IRQHandler      ; 26:	ADC unit A PMD trigger program conversion complete A
                DCD     INTADAPDB_IRQHandler      ; 27:	ADC unit A PMD trigger program conversion complete B
                DCD     INTADACP0_IRQHandler      ; 28:	ADC unit A Monitor function 0 interrupt
                DCD     INTADACP1_IRQHandler      ; 29:	ADC unit A Monitor function 1 interrupt
                DCD     INTADATRG_IRQHandler      ; 30:	ADC unit A general trigger program conversion complete
                DCD     INTADASGL_IRQHandler      ; 31:	ADC unit A single program conversion completion
                DCD     INTADACNT_IRQHandler      ; 32:	ADC unit A continuous program conversion complete
                DCD     INTADBPDA_IRQHandler      ; 33:	ADC unit B PMD trigger program conversion complete A
                DCD     INTADBPDB_IRQHandler      ; 34:	ADC unit B PMD trigger program conversion complete B
                DCD     INTADBCP0_IRQHandler      ; 35:	ADC unit B Monitor function 0 interrupt
                DCD     INTADBCP1_IRQHandler      ; 36:	ADC unit B Monitor function 1 interrupt
                DCD     INTADBTRG_IRQHandler      ; 37:	ADC unit B general trigger program conversion complete
                DCD     INTADBSGL_IRQHandler      ; 38:	ADC unit B single program conversion completion
                DCD     INTADBCNT_IRQHandler      ; 39:	ADC unit B continuous program conversion complete
                DCD     INTSC0RX_IRQHandler       ; 40:	TSPI ch0 reception interrupt /UART ch0 reception interrupt
                DCD     INTSC0TX_IRQHandler       ; 41:	TSPI ch0 transmit interrupt /UART ch0 transmit interrupt
                DCD     INTSC0ERR_IRQHandler      ; 42:	TSPI ch0 error interrupt /UART ch0 error interrupt
                DCD     INTSC1RX_IRQHandler       ; 43:	TSPI ch1 reception interrupt /UART ch1 reception interrupt
                DCD     INTSC1TX_IRQHandler       ; 44:	TSPI ch1 transmit interrupt /UART ch1 transmit interrupt
                DCD     INTSC1ERR_IRQHandler      ; 45:	TSPI ch1 error interrupt /UART ch1 error interrupt
                DCD     INTSC2RX_IRQHandler       ; 46:	TSPI ch2 reception interrupt /UART ch2 reception interrupt
                DCD     INTSC2TX_IRQHandler       ; 47:	TSPI ch2 transmit interrupt /UART ch2 transmit interrupt
                DCD     INTSC2ERR_IRQHandler      ; 48:	TSPI ch2 error interrupt /UART ch2 error interrupt
                DCD     INTSC3RX_IRQHandler       ; 49:	TSPI ch3 reception interrupt /UART ch3 reception interrupt
                DCD     INTSC3TX_IRQHandler       ; 50:	TSPI ch3 transmit interrupt /UART ch3 transmit interrupt
                DCD     INTSC3ERR_IRQHandler      ; 51:	TSPI ch3 error interrupt /UART ch3 error interrupt
                DCD     INTUART4RX_IRQHandler     ; 52:	UART ch4 reception interrupt
                DCD     INTUART4TX_IRQHandler     ; 53:	UART ch4 transmit interrupt
                DCD     INTUART4ERR_IRQHandler    ; 54:	UART ch4 error interrupt
                DCD     INTI2C0ST_IRQHandler      ; 55:	EI2C ch0 status interrupt
                DCD     INTI2C0TBE_IRQHandler     ; 56:	EI2C ch0 transmit buffer empty interrupt
                DCD     INTI2C0RBF_IRQHandler     ; 57:	EI2C ch0 receive buffer full interrupt
                DCD     INTI2C1ST_IRQHandler      ; 58:	EI2C ch1 status interrupt
                DCD     INTI2C1TBE_IRQHandler     ; 59:	EI2C ch1 transmit buffer empty interrupt
                DCD     INTI2C1RBF_IRQHandler     ; 60:	EI2C ch1 receive buffer full interrupt
                DCD     INTT32A00AC_IRQHandler    ; 61:	T32A ch0 timer A/C match, overflow, and underflow
                DCD     INTT32A00ACCAP0_IRQHandler; 62:	T32A ch0 timer A/C capture 0
                DCD     INTT32A00ACCAP1_IRQHandler; 63:	T32A ch0 timer A/C capture 1
                DCD     INTT32A00B_IRQHandler     ; 64:	T32A ch0 timer B match, overflow, and underflow
                DCD     INTT32A00BCAP0_IRQHandler ; 65:	T32A ch0 timer B capture 0
                DCD     INTT32A00BCAP1_IRQHandler ; 66:	T32A ch0 timer B capture 1
                DCD     INTT32A01AC_IRQHandler    ; 67:	T32A ch1 timer A/C match, Overflow, and underflow
                DCD     INTT32A01ACCAP0_IRQHandler; 68:	T32A ch1 timer A/C capture 0
                DCD     INTT32A01ACCAP1_IRQHandler; 69:	T32A ch1 timer A/C capture 1
                DCD     INTT32A01B_IRQHandler     ; 70:	T32A ch1 timer B match, overflow, and underflow
                DCD     INTT32A01BCAP0_IRQHandler ; 71:	T32A ch1 timer B capture 0
                DCD     INTT32A01BCAP1_IRQHandler ; 72:	T32A ch1 timer B capture 1
                DCD     INTT32A02AC_IRQHandler    ; 73:	T32A ch2 timer A/C match, overflow, and underflow
                DCD     INTT32A02ACCAP0_IRQHandler; 74:	T32A ch2 timer A/C capture 0
                DCD     INTT32A02ACCAP1_IRQHandler; 75:	T32A ch2 timer A/C capture 1
                DCD     INTT32A02B_IRQHandler     ; 76:	T32A ch2 timer B match, overflow, and underflow
                DCD     INTT32A02BCAP0_IRQHandler ; 77:	T32A ch2 timer B capture 0
                DCD     INTT32A02BCAP1_IRQHandler ; 78:	T32A ch2 timer B capture 1
                DCD     INTT32A03AC_IRQHandler    ; 79:	T32A ch3 timer A/C match, overflow, and underflow
                DCD     INTT32A03ACCAP0_IRQHandler; 80:	T32A ch3 timer A/C capture 0
                DCD     INTT32A03ACCAP1_IRQHandler; 81:	T32A ch3 timer A/C capture 1
                DCD     INTT32A03B_IRQHandler     ; 82:	T32A ch3 timer B match, overflow, and underflow
                DCD     INTT32A03BCAP0_IRQHandler ; 83:	T32A ch3 timer B capture 0
                DCD     INTT32A03BCAP1_IRQHandler ; 84:	T32A ch3 timer B capture 1
                DCD     INTT32A04AC_IRQHandler    ; 85:	T32A ch4 timer A/C match, overflow, and underflow
                DCD     INTT32A04ACCAP0_IRQHandler; 86:	T32A ch4 timer A/C capture 0
                DCD     INTT32A04ACCAP1_IRQHandler; 87:	T32A ch4 timer A/C capture 1
                DCD     INTT32A04B_IRQHandler     ; 88:	T32A ch4 timer B match, overflow, and underflow
                DCD     INTT32A04BCAP0_IRQHandler ; 89:	T32A ch4 timer B capture 0
                DCD     INTT32A04BCAP1_IRQHandler ; 90:	T32A ch4 timer B capture 1
                DCD     INTPARI0_IRQHandler       ; 91:	RAM Parity interrupt 0
                DCD     INTPARI1_IRQHandler       ; 92:	RAM Parity interrupt 1
                DCD     INTDMAATC_IRQHandler      ; 93:	DMAC transfer completion interrupt (ch0 to 31)
                DCD     INTDMAAERR_IRQHandler     ; 94:	DMAC transfer error interrupt
                DCD     INTFLCRDY_IRQHandler      ; 95:	Code FLASH Ready interrupt
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

                PUBWEAK INT6_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT6_IRQHandler
                B       INT6_IRQHandler

                PUBWEAK INT7_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT7_IRQHandler
                B       INT7_IRQHandler

                PUBWEAK INT8_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT8_IRQHandler
                B       INT8_IRQHandler

                PUBWEAK INT9_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT9_IRQHandler
                B       INT9_IRQHandler

                PUBWEAK INTA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTA_IRQHandler
                B       INTA_IRQHandler

                PUBWEAK INTB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTB_IRQHandler
                B       INTB_IRQHandler

                PUBWEAK INTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTC_IRQHandler
                B       INTC_IRQHandler

                PUBWEAK INTD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTD_IRQHandler
                B       INTD_IRQHandler

                PUBWEAK INTE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTE_IRQHandler
                B       INTE_IRQHandler

                PUBWEAK INTF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTF_IRQHandler
                B       INTF_IRQHandler

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

                PUBWEAK INTENC10_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC10_IRQHandler
                B       INTENC10_IRQHandler

                PUBWEAK INTENC11_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTENC11_IRQHandler
                B       INTENC11_IRQHandler

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

                PUBWEAK INTSC3RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC3RX_IRQHandler
                B       INTSC3RX_IRQHandler

                PUBWEAK INTSC3TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC3TX_IRQHandler
                B       INTSC3TX_IRQHandler

                PUBWEAK INTSC3ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSC3ERR_IRQHandler
                B       INTSC3ERR_IRQHandler

                PUBWEAK INTUART4RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART4RX_IRQHandler
                B       INTUART4RX_IRQHandler

                PUBWEAK INTUART4TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART4TX_IRQHandler
                B       INTUART4TX_IRQHandler

                PUBWEAK INTUART4ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART4ERR_IRQHandler
                B       INTUART4ERR_IRQHandler

                PUBWEAK INTI2C0ST_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0ST_IRQHandler
                B       INTI2C0ST_IRQHandler

                PUBWEAK INTI2C0TBE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0TBE_IRQHandler
                B       INTI2C0TBE_IRQHandler

                PUBWEAK INTI2C0RBF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C0RBF_IRQHandler
                B       INTI2C0RBF_IRQHandler

                PUBWEAK INTI2C1ST_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C1ST_IRQHandler
                B       INTI2C1ST_IRQHandler

                PUBWEAK INTI2C1TBE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C1TBE_IRQHandler
                B       INTI2C1TBE_IRQHandler

                PUBWEAK INTI2C1RBF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C1RBF_IRQHandler
                B       INTI2C1RBF_IRQHandler

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

                END
