;/**
; *******************************************************************************
; * @file    startup_TMPM4NQ.s
; * @brief   CMSIS Cortex-M4 Core Device Startup File for the
; *          TOSHIBA 'TMPM4NQ' Device Series
; * @version V1.0.0
; * 
; * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
; * 
; * Copyright(C) Toshiba Electronic Device Solutions Corporation 2020
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
                DCD     INT01_IRQHandler          ; 1:	Interrupt pin 01a/00b
                DCD     INT02_IRQHandler          ; 2:	Interrupt pin 02a/00b
                DCD     INT03_IRQHandler          ; 3:	Interrupt pin 03a/03b
                DCD     INT04_IRQHandler          ; 4:	Interrupt pin 04a/04b
                DCD     INT05_IRQHandler          ; 5:	Interrupt pin 05a/05b
                DCD     INT06_IRQHandler          ; 6:	Interrupt pin 06a/06b
                DCD     INT07_IRQHandler          ; 7:	Interrupt pin 07a/07b
                DCD     INT08_IRQHandler          ; 8:	Interrupt pin 08a/08b
                DCD     INT09_IRQHandler          ; 9:	Interrupt pin 09a/09b
                DCD     INT10_IRQHandler          ; 10:	Interrupt pin 10a/10b
                DCD     INT11_IRQHandler          ; 11:	Interrupt pin 11a/11b
                DCD     0                         ; 12:	Reserved
                DCD     0                         ; 13:	Reserved
                DCD     INT14_IRQHandler          ; 14:	Interrupt pin 14a/14b
                DCD     INT15_IRQHandler          ; 15:	Interrupt pin 15a/15b
                DCD     INTRTC_IRQHandler         ; 16:	Real time clock(XHz) interrupt
                DCD     INTCEC0RX_IRQHandler      ; 17:	CEC reception interrupt (channel 0)
                DCD     INTCEC0TX_IRQHandler      ; 18:	CEC transmission interrupt (channel 0)
                DCD     INTISDA_IRQHandler        ; 19:	Interval Sensing Detector interrupt (Unit A)
                DCD     INTISDB_IRQHandler        ; 20:	Interval Sensing Detector interrupt (Unit B)
                DCD     0                         ; 21:	Reserved
                DCD     INTRMC0_IRQHandler        ; 22:	Remote control reception interrupt 0
                DCD     INTRMC1_IRQHandler        ; 23:	Remote control reception interrupt 1
                DCD     INTLTTMR0_IRQHandler      ; 24:	Long Term Timer Interrupt(channel 0)
                DCD     INTHDMAATC_IRQHandler     ; 25:	HDMA complete of transfer(Unit A)
                DCD     INTHDMAAERR_IRQHandler    ; 26:	HDMA transfer error(Unit A)
                DCD     INTHDMABTC_IRQHandler     ; 27:	HDMA end of transfer(Unit B)
                DCD     INTHDMABERR_IRQHandler    ; 28:	HDMA transfer error(Unit B)
                DCD     INTMDMAATC_IRQHandler     ; 29:	MDMA complete of transfer(Unit A)
                DCD     INTT32A00_A_CT_IRQHandler ; 30:	T32A00 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A00_B_C01_CPC_IRQHandler; 31:	T32A00 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A01_A_CT_IRQHandler ; 32:	T32A01 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A01_B_C01_CPC_IRQHandler; 33:	T32A01 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A02_A_CT_IRQHandler ; 34:	T32A02 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A02_B_C01_CPC_IRQHandler; 35:	T32A02 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A03_A_CT_IRQHandler ; 36:	T32A03 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A03_B_C01_CPC_IRQHandler; 37:	T32A03 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A04_A_CT_IRQHandler ; 38:	T32A04 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A04_B_C01_CPC_IRQHandler; 39:	T32A04 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A05_A_CT_IRQHandler ; 40:	T32A05 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A05_B_C01_CPC_IRQHandler; 41:	T32A05 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A06_A_CT_IRQHandler ; 42:	T32A06 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A06_B_C01_CPC_IRQHandler; 43:	T32A06 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A07_A_CT_IRQHandler ; 44:	T32A07 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A07_B_C01_CPC_IRQHandler; 45:	T32A07 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A08_A_CT_IRQHandler ; 46:	T32A08 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A08_B_C01_CPC_IRQHandler; 47:	T32A08 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A09_A_CT_IRQHandler ; 48:	T32A09 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A09_B_C01_CPC_IRQHandler; 49:	T32A09 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A10_A_CT_IRQHandler ; 50:	T32A10 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A10_B_C01_CPC_IRQHandler; 51:	T32A10 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A11_A_CT_IRQHandler ; 52:	T32A11 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A11_B_C01_CPC_IRQHandler; 53:	T32A11 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A12_A_CT_IRQHandler ; 54:	T32A12 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A12_B_C01_CPC_IRQHandler; 55:	T32A12 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTT32A13_A_CT_IRQHandler ; 56:	T32A13 TimerA all interrupt /TimerC match, overflow, and underflow
                DCD     INTT32A13_B_C01_CPC_IRQHandler; 57:	T32A13 TimerB all interrupt /TimerC capture C0_C1, pulse count interrupt
                DCD     INTEMG0_IRQHandler        ; 58:	PMD0 EMG interrupt
                DCD     INTOVV0_IRQHandler        ; 59:	PMD0 OVV interrupt
                DCD     INTPWM0_IRQHandler        ; 60:	PMD0 interrupt
                DCD     INTT0RX_IRQHandler        ; 61:	TSPI/SIO reception (channel 0) interrupt
                DCD     INTT0TX_IRQHandler        ; 62:	TSPI/SIO transmit (channel 0) interrupt
                DCD     INTT0ERR_IRQHandler       ; 63:	TSPI/SIO error (channel 0) interrupt
                DCD     INTT1RX_IRQHandler        ; 64:	TSPI/SIO reception (channel 1) interrupt
                DCD     INTT1TX_IRQHandler        ; 65:	TSPI/SIO transmit (channel 1) interrupt
                DCD     INTT1ERR_IRQHandler       ; 66:	TSPI/SIO error (channel 1) interrupt
                DCD     INTT2RX_IRQHandler        ; 67:	TSPI/SIO reception (channel 2) interrupt
                DCD     INTT2TX_IRQHandler        ; 68:	TSPI/SIO transmit (channel 2) interrupt
                DCD     INTT2ERR_IRQHandler       ; 69:	TSPI/SIO error (channel 2) interrupt
                DCD     INTT3RX_IRQHandler        ; 70:	TSPI/SIO reception (channel 3) interrupt
                DCD     INTT3TX_IRQHandler        ; 71:	TSPI/SIO transmit (channel 3) interrupt
                DCD     INTT3ERR_IRQHandler       ; 72:	TSPI/SIO error (channel 3) interrupt
                DCD     INTT4RX_IRQHandler        ; 73:	TSPI/SIO reception (channel 4) interrupt
                DCD     INTT4TX_IRQHandler        ; 74:	TSPI/SIO transmit (channel 4) interrupt
                DCD     INTT4ERR_IRQHandler       ; 75:	TSPI/SIO error (channel 4) interrupt
                DCD     INTT5RX_IRQHandler        ; 76:	TSPI/SIO reception (channel 5) interrupt
                DCD     INTT5TX_IRQHandler        ; 77:	TSPI/SIO transmit (channel 5) interrupt
                DCD     INTT5ERR_IRQHandler       ; 78:	TSPI/SIO error (channel 5) interrupt
                DCD     INTT6RX_IRQHandler        ; 79:	TSPI/SIO reception (channel 6) interrupt
                DCD     INTT6TX_IRQHandler        ; 80:	TSPI/SIO transmit (channel 6) interrupt
                DCD     INTT6ERR_IRQHandler       ; 81:	TSPI/SIO error (channel 6) interrupt
                DCD     INTT7RX_IRQHandler        ; 82:	TSPI/SIO reception (channel 7) interrupt
                DCD     INTT7TX_IRQHandler        ; 83:	TSPI/SIO transmit (channel 7) interrupt
                DCD     INTT7ERR_IRQHandler       ; 84:	TSPI/SIO error (channel 7) interrupt
                DCD     0                         ; 85:	Reserved
                DCD     0                         ; 86:	Reserved
                DCD     0                         ; 87:	Reserved
                DCD     INTSMI0_IRQHandler        ; 88:	Serial Memory Interface interrupt
                DCD     INTUART0RX_IRQHandler     ; 89:	UART reception (channel 0) interrupt
                DCD     INTUART0TX_IRQHandler     ; 90:	UART transmit (channel 0) interrupt
                DCD     INTUART0ERR_IRQHandler    ; 91:	UART error (channel 0) interrupt
                DCD     INTUART1RX_IRQHandler     ; 92:	UART reception (channel 1) interrupt
                DCD     INTUART1TX_IRQHandler     ; 93:	UART transmit (channel 1) interrupt
                DCD     INTUART1ERR_IRQHandler    ; 94:	UART error (channel 1) interrupt
                DCD     INTUART2RX_IRQHandler     ; 95:	UART reception (channel 2) interrupt
                DCD     INTUART2TX_IRQHandler     ; 96:	UART transmit (channel 2) interrupt
                DCD     INTUART2ERR_IRQHandler    ; 97:	UART error (channel 2) interrupt
                DCD     INTUART3RX_IRQHandler     ; 98:	UART reception (channel 3) interrupt
                DCD     INTUART3TX_IRQHandler     ; 99:	UART transmit (channel 3) interrupt
                DCD     INTUART3ERR_IRQHandler    ; 100:	UART error (channel 3) interrupt
                DCD     INTUART4RX_IRQHandler     ; 101:	UART reception (channel 4) interrupt
                DCD     INTUART4TX_IRQHandler     ; 102:	UART transmit (channel 4) interrupt
                DCD     INTUART4ERR_IRQHandler    ; 103:	UART error (channel 4) interrupt
                DCD     0                         ; 104:	Reserved
                DCD     0                         ; 105:	Reserved
                DCD     0                         ; 106:	Reserved
                DCD     INTFUART0_IRQHandler      ; 107:	FUART interrupt(channel 0)
                DCD     INTFUART1_IRQHandler      ; 108:	FUART interrupt(channel 1)
                DCD     INTI2C0NST_IRQHandler     ; 109:	I2C0 interrupt / EI2C0 status interrupt
                DCD     INTI2C0ATX_IRQHandler     ; 110:	I2C0 arbitration lost detection interrupt / EI2C0 transmit buffer empty interrupt
                DCD     INTI2C0BRX_IRQHandler     ; 111:	I2C0 bus free detection interrupt / EI2C0receive buffer empty interrupt
                DCD     INTI2C0NA_IRQHandler      ; 112:	I2C0 NACK detection interrupt
                DCD     INTI2C1NST_IRQHandler     ; 113:	I2C1 interrupt / EI2C0 status interrupt
                DCD     INTI2C1ATX_IRQHandler     ; 114:	I2C1 arbitration lost detection interrupt / EI2C0 transmit buffer empty interrupt
                DCD     INTI2C1BRX_IRQHandler     ; 115:	I2C1 bus free detection interrupt / EI2C0receive buffer empty interrupt
                DCD     INTI2C1NA_IRQHandler      ; 116:	I2C1 NACK detection interrupt
                DCD     INTI2C2NST_IRQHandler     ; 117:	I2C2 interrupt / EI2C0 status interrupt
                DCD     INTI2C2ATX_IRQHandler     ; 118:	I2C2 arbitration lost detection interrupt / EI2C0 transmit buffer empty interrupt
                DCD     INTI2C2BRX_IRQHandler     ; 119:	I2C2 bus free detection interrupt / EI2C0receive buffer empty interrupt
                DCD     INTI2C2NA_IRQHandler      ; 120:	I2C2 NACK detection interrupt
                DCD     INTI2C3NST_IRQHandler     ; 121:	I2C3 interrupt / EI2C0 status interrupt
                DCD     INTI2C3ATX_IRQHandler     ; 122:	I2C3 arbitration lost detection interrupt / EI2C0 transmit buffer empty interrupt
                DCD     INTI2C3BRX_IRQHandler     ; 123:	I2C3 bus free detection interrupt / EI2C0receive buffer empty interrupt
                DCD     INTI2C3NA_IRQHandler      ; 124:	I2C3 NACK detection interrupt
                DCD     INTI2C4NST_IRQHandler     ; 125:	I2C4 interrupt / EI2C0 status interrupt
                DCD     INTI2C4ATX_IRQHandler     ; 126:	I2C4 arbitration lost detection interrupt / EI2C0 transmit buffer empty interrupt
                DCD     INTI2C4BRX_IRQHandler     ; 127:	I2C4 bus free detection interrupt / EI2C0receive buffer empty interrupt
                DCD     INTI2C4NA_IRQHandler      ; 128:	I2C4 NACK detection interrupt
                DCD     INTADACP0_IRQHandler      ; 129:	ADC conversion monitoring function interrupt 0
                DCD     INTADACP1_IRQHandler      ; 130:	ADC conversion monitoring function interrupt 1
                DCD     INTADATRG_IRQHandler      ; 131:	ADC conversion triggered by General purpose is finished
                DCD     INTADASGL_IRQHandler      ; 132:	ADC conversion triggered by Single program is finished
                DCD     INTADACNT_IRQHandler      ; 133:	ADC conversion triggered by Continuity program is finished
                DCD     INTADAHP_IRQHandler       ; 134:	ADC high priority AD conversion interrupt
                DCD     INTFLDRDY_IRQHandler      ; 135:	Data FLASH Ready interrupt
                DCD     INTFLCRDY_IRQHandler      ; 136:	Code FLASH Area0/1 Ready interrupt
                DCD     0                         ; 137:	Reserved
                DCD     0                         ; 138:	Reserved
                DCD     INTMDMAABERR_IRQHandler   ; 139:	MDMA bus error(Unit A) interrupt
                DCD     INTMDMAADERR_IRQHandler   ; 140:	MDMA descriptor error(Unit A) interrupt
                DCD     INTI2S0SI_IRQHandler      ; 141:	I2S ch0 SI transfer end interrupt
                DCD     INTI2S0SIERR_IRQHandler   ; 142:	I2S ch0 SI error interrupt
                DCD     INTI2S0SO_IRQHandler      ; 143:	I2S ch0 SO transfer end interrupt
                DCD     INTI2S0SOERR_IRQHandler   ; 144:	I2S ch0 SO error interrupt
                DCD     INTI2S1SI_IRQHandler      ; 145:	I2S ch1 SI transfer end interrupt
                DCD     INTI2S1SIERR_IRQHandler   ; 146:	I2S ch1 SI error interrupt
                DCD     INTI2S1SO_IRQHandler      ; 147:	I2S ch1 SO transfer end interrupt
                DCD     INTI2S1SOERR_IRQHandler   ; 148:	I2S ch1 SO error interrupt
                DCD     INTFIR0_IRQHandler        ; 149:	FIR ch0 interrupt
                DCD     INTTSSI0RX_IRQHandler     ; 150:	TSSI ch0 receive interrupt
                DCD     INTTSSI0TX_IRQHandler     ; 151:	TSSI ch0 transmission interrupt
                DCD     INTTSSI0ERR_IRQHandler    ; 152:	TSSI ch0 error interrupt
                DCD     0                         ; 153:	Reserved
                DCD     0                         ; 154:	Reserved
                DCD     0                         ; 155:	Reserved
                DCD     INTEMA_IRQHandler         ; 156:	ETHM unit A interrupt
                DCD     INTEMAMP_IRQHandler       ; 157:	ETHM unit A magic packet detection interrupt
                DCD     INTCANARXD_IRQHandler     ; 158:	CAN unit A receive interrupt
                DCD     INTCANATXD_IRQHandler     ; 159:	CAN unit A transmission interrupt
                DCD     INTCANAGLB_IRQHandler     ; 160:	CAN unit A Global interrupt
                DCD     INTCANBRXD_IRQHandler     ; 161:	CAN unit B receive interrupt
                DCD     INTCANBTXD_IRQHandler     ; 162:	CAN unit B transmission interrupt
                DCD     INTCANBGLB_IRQHandler     ; 163:	CAN unit B Global interrupt
                DCD     INTUSBOTGA_IRQHandler     ; 164:	USB OTG unit A interrupt
                DCD     INTUSBOTGAWK_IRQHandler   ; 165:	USB OTG unit A Wakeup interrupt
                DCD     INTUSBOTGB_IRQHandler     ; 166:	USB OTG unit B interrupt
                DCD     INTUSBOTGBWK_IRQHandler   ; 167:	USB OTG unit B Wakeup interrupt
                DCD     INTT32A14_A_IRQHandler    ; 168:	T32A14 TimerA all interrupt
                DCD     INTT32A14_B_IRQHandler    ; 169:	T32A14 TimerB all interrupt
                DCD     INTT32A14_CT_IRQHandler   ; 170:	T32A14 TimerC match, overflow, and underflow Interrupt
                DCD     INTT32A15_A_IRQHandler    ; 171:	T32A15 TimerA all interrupt
                DCD     INTT32A15_B_IRQHandler    ; 172:	T32A15 TimerB all interrupt
                DCD     INTT32A15_C_IRQHandler    ; 173:	T32A15 TimerC all interrupt
                DCD     INTMDMAADISR_IRQHandler   ; 174:	MDMAC unit A Descriptor interrupt
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

                PUBWEAK INT14_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT14_IRQHandler
                B       INT14_IRQHandler

                PUBWEAK INT15_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INT15_IRQHandler
                B       INT15_IRQHandler

                PUBWEAK INTRTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRTC_IRQHandler
                B       INTRTC_IRQHandler

                PUBWEAK INTCEC0RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCEC0RX_IRQHandler
                B       INTCEC0RX_IRQHandler

                PUBWEAK INTCEC0TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCEC0TX_IRQHandler
                B       INTCEC0TX_IRQHandler

                PUBWEAK INTISDA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTISDA_IRQHandler
                B       INTISDA_IRQHandler

                PUBWEAK INTISDB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTISDB_IRQHandler
                B       INTISDB_IRQHandler

                PUBWEAK INTRMC0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRMC0_IRQHandler
                B       INTRMC0_IRQHandler

                PUBWEAK INTRMC1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRMC1_IRQHandler
                B       INTRMC1_IRQHandler

                PUBWEAK INTLTTMR0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTLTTMR0_IRQHandler
                B       INTLTTMR0_IRQHandler

                PUBWEAK INTHDMAATC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTHDMAATC_IRQHandler
                B       INTHDMAATC_IRQHandler

                PUBWEAK INTHDMAAERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTHDMAAERR_IRQHandler
                B       INTHDMAAERR_IRQHandler

                PUBWEAK INTHDMABTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTHDMABTC_IRQHandler
                B       INTHDMABTC_IRQHandler

                PUBWEAK INTHDMABERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTHDMABERR_IRQHandler
                B       INTHDMABERR_IRQHandler

                PUBWEAK INTMDMAATC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMDMAATC_IRQHandler
                B       INTMDMAATC_IRQHandler

                PUBWEAK INTT32A00_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00_A_CT_IRQHandler
                B       INTT32A00_A_CT_IRQHandler

                PUBWEAK INTT32A00_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A00_B_C01_CPC_IRQHandler
                B       INTT32A00_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A01_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01_A_CT_IRQHandler
                B       INTT32A01_A_CT_IRQHandler

                PUBWEAK INTT32A01_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A01_B_C01_CPC_IRQHandler
                B       INTT32A01_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A02_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02_A_CT_IRQHandler
                B       INTT32A02_A_CT_IRQHandler

                PUBWEAK INTT32A02_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A02_B_C01_CPC_IRQHandler
                B       INTT32A02_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A03_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03_A_CT_IRQHandler
                B       INTT32A03_A_CT_IRQHandler

                PUBWEAK INTT32A03_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A03_B_C01_CPC_IRQHandler
                B       INTT32A03_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A04_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A04_A_CT_IRQHandler
                B       INTT32A04_A_CT_IRQHandler

                PUBWEAK INTT32A04_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A04_B_C01_CPC_IRQHandler
                B       INTT32A04_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A05_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A05_A_CT_IRQHandler
                B       INTT32A05_A_CT_IRQHandler

                PUBWEAK INTT32A05_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A05_B_C01_CPC_IRQHandler
                B       INTT32A05_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A06_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A06_A_CT_IRQHandler
                B       INTT32A06_A_CT_IRQHandler

                PUBWEAK INTT32A06_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A06_B_C01_CPC_IRQHandler
                B       INTT32A06_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A07_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A07_A_CT_IRQHandler
                B       INTT32A07_A_CT_IRQHandler

                PUBWEAK INTT32A07_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A07_B_C01_CPC_IRQHandler
                B       INTT32A07_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A08_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A08_A_CT_IRQHandler
                B       INTT32A08_A_CT_IRQHandler

                PUBWEAK INTT32A08_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A08_B_C01_CPC_IRQHandler
                B       INTT32A08_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A09_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A09_A_CT_IRQHandler
                B       INTT32A09_A_CT_IRQHandler

                PUBWEAK INTT32A09_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A09_B_C01_CPC_IRQHandler
                B       INTT32A09_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A10_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A10_A_CT_IRQHandler
                B       INTT32A10_A_CT_IRQHandler

                PUBWEAK INTT32A10_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A10_B_C01_CPC_IRQHandler
                B       INTT32A10_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A11_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A11_A_CT_IRQHandler
                B       INTT32A11_A_CT_IRQHandler

                PUBWEAK INTT32A11_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A11_B_C01_CPC_IRQHandler
                B       INTT32A11_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A12_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A12_A_CT_IRQHandler
                B       INTT32A12_A_CT_IRQHandler

                PUBWEAK INTT32A12_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A12_B_C01_CPC_IRQHandler
                B       INTT32A12_B_C01_CPC_IRQHandler

                PUBWEAK INTT32A13_A_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A13_A_CT_IRQHandler
                B       INTT32A13_A_CT_IRQHandler

                PUBWEAK INTT32A13_B_C01_CPC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A13_B_C01_CPC_IRQHandler
                B       INTT32A13_B_C01_CPC_IRQHandler

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

                PUBWEAK INTT3RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT3RX_IRQHandler
                B       INTT3RX_IRQHandler

                PUBWEAK INTT3TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT3TX_IRQHandler
                B       INTT3TX_IRQHandler

                PUBWEAK INTT3ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT3ERR_IRQHandler
                B       INTT3ERR_IRQHandler

                PUBWEAK INTT4RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT4RX_IRQHandler
                B       INTT4RX_IRQHandler

                PUBWEAK INTT4TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT4TX_IRQHandler
                B       INTT4TX_IRQHandler

                PUBWEAK INTT4ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT4ERR_IRQHandler
                B       INTT4ERR_IRQHandler

                PUBWEAK INTT5RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT5RX_IRQHandler
                B       INTT5RX_IRQHandler

                PUBWEAK INTT5TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT5TX_IRQHandler
                B       INTT5TX_IRQHandler

                PUBWEAK INTT5ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT5ERR_IRQHandler
                B       INTT5ERR_IRQHandler

                PUBWEAK INTT6RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT6RX_IRQHandler
                B       INTT6RX_IRQHandler

                PUBWEAK INTT6TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT6TX_IRQHandler
                B       INTT6TX_IRQHandler

                PUBWEAK INTT6ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT6ERR_IRQHandler
                B       INTT6ERR_IRQHandler

                PUBWEAK INTT7RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT7RX_IRQHandler
                B       INTT7RX_IRQHandler

                PUBWEAK INTT7TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT7TX_IRQHandler
                B       INTT7TX_IRQHandler

                PUBWEAK INTT7ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT7ERR_IRQHandler
                B       INTT7ERR_IRQHandler

                PUBWEAK INTSMI0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTSMI0_IRQHandler
                B       INTSMI0_IRQHandler

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

                PUBWEAK INTUART3RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART3RX_IRQHandler
                B       INTUART3RX_IRQHandler

                PUBWEAK INTUART3TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART3TX_IRQHandler
                B       INTUART3TX_IRQHandler

                PUBWEAK INTUART3ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART3ERR_IRQHandler
                B       INTUART3ERR_IRQHandler

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

                PUBWEAK INTFUART0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTFUART0_IRQHandler
                B       INTFUART0_IRQHandler

                PUBWEAK INTFUART1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTFUART1_IRQHandler
                B       INTFUART1_IRQHandler

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

                PUBWEAK INTI2C2NST_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C2NST_IRQHandler
                B       INTI2C2NST_IRQHandler

                PUBWEAK INTI2C2ATX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C2ATX_IRQHandler
                B       INTI2C2ATX_IRQHandler

                PUBWEAK INTI2C2BRX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C2BRX_IRQHandler
                B       INTI2C2BRX_IRQHandler

                PUBWEAK INTI2C2NA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C2NA_IRQHandler
                B       INTI2C2NA_IRQHandler

                PUBWEAK INTI2C3NST_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C3NST_IRQHandler
                B       INTI2C3NST_IRQHandler

                PUBWEAK INTI2C3ATX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C3ATX_IRQHandler
                B       INTI2C3ATX_IRQHandler

                PUBWEAK INTI2C3BRX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C3BRX_IRQHandler
                B       INTI2C3BRX_IRQHandler

                PUBWEAK INTI2C3NA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C3NA_IRQHandler
                B       INTI2C3NA_IRQHandler

                PUBWEAK INTI2C4NST_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C4NST_IRQHandler
                B       INTI2C4NST_IRQHandler

                PUBWEAK INTI2C4ATX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C4ATX_IRQHandler
                B       INTI2C4ATX_IRQHandler

                PUBWEAK INTI2C4BRX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C4BRX_IRQHandler
                B       INTI2C4BRX_IRQHandler

                PUBWEAK INTI2C4NA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C4NA_IRQHandler
                B       INTI2C4NA_IRQHandler

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

                PUBWEAK INTADAHP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAHP_IRQHandler
                B       INTADAHP_IRQHandler

                PUBWEAK INTFLDRDY_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTFLDRDY_IRQHandler
                B       INTFLDRDY_IRQHandler

                PUBWEAK INTFLCRDY_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTFLCRDY_IRQHandler
                B       INTFLCRDY_IRQHandler

                PUBWEAK INTMDMAABERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMDMAABERR_IRQHandler
                B       INTMDMAABERR_IRQHandler

                PUBWEAK INTMDMAADERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMDMAADERR_IRQHandler
                B       INTMDMAADERR_IRQHandler

                PUBWEAK INTI2S0SI_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2S0SI_IRQHandler
                B       INTI2S0SI_IRQHandler

                PUBWEAK INTI2S0SIERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2S0SIERR_IRQHandler
                B       INTI2S0SIERR_IRQHandler

                PUBWEAK INTI2S0SO_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2S0SO_IRQHandler
                B       INTI2S0SO_IRQHandler

                PUBWEAK INTI2S0SOERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2S0SOERR_IRQHandler
                B       INTI2S0SOERR_IRQHandler

                PUBWEAK INTI2S1SI_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2S1SI_IRQHandler
                B       INTI2S1SI_IRQHandler

                PUBWEAK INTI2S1SIERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2S1SIERR_IRQHandler
                B       INTI2S1SIERR_IRQHandler

                PUBWEAK INTI2S1SO_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2S1SO_IRQHandler
                B       INTI2S1SO_IRQHandler

                PUBWEAK INTI2S1SOERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2S1SOERR_IRQHandler
                B       INTI2S1SOERR_IRQHandler

                PUBWEAK INTFIR0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTFIR0_IRQHandler
                B       INTFIR0_IRQHandler

                PUBWEAK INTTSSI0RX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTSSI0RX_IRQHandler
                B       INTTSSI0RX_IRQHandler

                PUBWEAK INTTSSI0TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTSSI0TX_IRQHandler
                B       INTTSSI0TX_IRQHandler

                PUBWEAK INTTSSI0ERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTSSI0ERR_IRQHandler
                B       INTTSSI0ERR_IRQHandler

                PUBWEAK INTEMA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEMA_IRQHandler
                B       INTEMA_IRQHandler

                PUBWEAK INTEMAMP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEMAMP_IRQHandler
                B       INTEMAMP_IRQHandler

                PUBWEAK INTCANARXD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANARXD_IRQHandler
                B       INTCANARXD_IRQHandler

                PUBWEAK INTCANATXD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANATXD_IRQHandler
                B       INTCANATXD_IRQHandler

                PUBWEAK INTCANAGLB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANAGLB_IRQHandler
                B       INTCANAGLB_IRQHandler

                PUBWEAK INTCANBRXD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANBRXD_IRQHandler
                B       INTCANBRXD_IRQHandler

                PUBWEAK INTCANBTXD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANBTXD_IRQHandler
                B       INTCANBTXD_IRQHandler

                PUBWEAK INTCANBGLB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTCANBGLB_IRQHandler
                B       INTCANBGLB_IRQHandler

                PUBWEAK INTUSBOTGA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUSBOTGA_IRQHandler
                B       INTUSBOTGA_IRQHandler

                PUBWEAK INTUSBOTGAWK_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUSBOTGAWK_IRQHandler
                B       INTUSBOTGAWK_IRQHandler

                PUBWEAK INTUSBOTGB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUSBOTGB_IRQHandler
                B       INTUSBOTGB_IRQHandler

                PUBWEAK INTUSBOTGBWK_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUSBOTGBWK_IRQHandler
                B       INTUSBOTGBWK_IRQHandler

                PUBWEAK INTT32A14_A_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A14_A_IRQHandler
                B       INTT32A14_A_IRQHandler

                PUBWEAK INTT32A14_B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A14_B_IRQHandler
                B       INTT32A14_B_IRQHandler

                PUBWEAK INTT32A14_CT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A14_CT_IRQHandler
                B       INTT32A14_CT_IRQHandler

                PUBWEAK INTT32A15_A_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A15_A_IRQHandler
                B       INTT32A15_A_IRQHandler

                PUBWEAK INTT32A15_B_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A15_B_IRQHandler
                B       INTT32A15_B_IRQHandler

                PUBWEAK INTT32A15_C_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTT32A15_C_IRQHandler
                B       INTT32A15_C_IRQHandler

                PUBWEAK INTMDMAADISR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTMDMAADISR_IRQHandler
                B       INTMDMAADISR_IRQHandler

                END
