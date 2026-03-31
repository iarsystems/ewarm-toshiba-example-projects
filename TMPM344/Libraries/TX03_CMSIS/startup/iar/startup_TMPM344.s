;/**
; *******************************************************************************
; * @file    startup_TMPM344.s
; * @brief   CMSIS Cortex-M3 Core Device Startup File for the
; *          TOSHIBA 'TMPM344' Device Series
; * @version V2.0.2.2 (Tentative)
; * @date    2014/05/20
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
                DCD     INT0_IRQHandler           ; 0:	Interrupt pin 0
                DCD     INT1_IRQHandler           ; 1:	Interrupt pin 1
                DCD     INT2_IRQHandler           ; 2:	Interrupt pin 2
                DCD     INT3_IRQHandler           ; 3:	Interrupt pin 3
                DCD     INT4_IRQHandler           ; 4:	Interrupt pin 4
                DCD     INT5_IRQHandler           ; 5:	Interrupt pin 5
                DCD     INT6_IRQHandler           ; 6:	Interrupt pin 6
                DCD     INT7_IRQHandler           ; 7:	Interrupt pin 7
                DCD     INT8_IRQHandler           ; 8:	Interrupt pin 8
                DCD     INT9_IRQHandler           ; 9:	Interrupt pin 9
                DCD     INTA_IRQHandler           ; 10:	Interrupt pin A
                DCD     INTB_IRQHandler           ; 11:	Interrupt pin B
                DCD     INTC_IRQHandler           ; 12:	Interrupt pin C
                DCD     INTD_IRQHandler           ; 13:	Interrupt pin D
                DCD     INTE_IRQHandler           ; 14:	Interrupt pin E
                DCD     INTF_IRQHandler           ; 15:	Interrupt pin F
                DCD     INTPSCASTOP_IRQHandler    ; 16:	PSC end interrupt (unitA)
                DCD     INTPSCABRK_IRQHandler     ; 17:	PSC break interrupt (unitA)
                DCD     INTPSCASTEP_IRQHandler    ; 18:	PSC step interrupt (unitA)
                DCD     INTPSCAII_IRQHandler      ; 19:	PSC unjustified instruction interrupt (unitA)
                DCD     INTPSCAIA_IRQHandler      ; 20:	PSC unjustified address interrupt (unitA)
                DCD     INTPSCBSTOP_IRQHandler    ; 21:	PSC end interrupt (unitB)
                DCD     INTPSCBBRK_IRQHandler     ; 22:	PSC break interrupt (unitB)
                DCD     INTPSCBSTEP_IRQHandler    ; 23:	PSC step interrupt (unitB)
                DCD     INTPSCBII_IRQHandler      ; 24:	PSC unjustified instruction interrupt (unitB)
                DCD     INTPSCBIA_IRQHandler      ; 25:	PSC unjustified address interrupt (unitB)
                DCD     INTPSCCSTOP_IRQHandler    ; 26:	PSC end interrupt (unitC)
                DCD     INTPSCCBRK_IRQHandler     ; 27:	PSC break interrupt (unitC)
                DCD     INTPSCCSTEP_IRQHandler    ; 28:	PSC step interrupt (unitC)
                DCD     INTPSCCII_IRQHandler      ; 29:	PSC unjustified instruction interrupt (unitC)
                DCD     INTPSCCIA_IRQHandler      ; 30:	PSC unjustified address interrupt (unitC)
                DCD     INTPSCDSTOP_IRQHandler    ; 31:	PSC end interrupt (unitD)
                DCD     INTPSCDBRK_IRQHandler     ; 32:	PSC break interrupt (unitD)
                DCD     INTPSCDSTEP_IRQHandler    ; 33:	PSC step interrupt (unitD)
                DCD     INTPSCDII_IRQHandler      ; 34:	PSC unjustified instruction interrupt (unitD)
                DCD     INTPSCDIA_IRQHandler      ; 35:	PSC unjustified address interrupt (unitD)
                DCD     INTT0RX_IRQHandler        ; 36:	TSPI0 reception interrupt
                DCD     INTT0TX_IRQHandler        ; 37:	TSPI0 transmission interrupt
                DCD     INTT0ERR_IRQHandler       ; 38:	TSPI0 error interrupt
                DCD     INTT1RX_IRQHandler        ; 39:	TSPI1 reception interrupt
                DCD     INTT1TX_IRQHandler        ; 40:	TSPI1 transmission interrupt
                DCD     INTT1ERR_IRQHandler       ; 41:	TSPI1 error interrupt
                DCD     INTT2RX_IRQHandler        ; 42:	TSPI2 reception interrupt
                DCD     INTT2TX_IRQHandler        ; 43:	TSPI2 transmission interrupt
                DCD     INTT2ERR_IRQHandler       ; 44:	TSPI2 error interrupt
                DCD     INTT3RX_IRQHandler        ; 45:	TSPI3 reception interrupt
                DCD     INTT3TX_IRQHandler        ; 46:	TSPI3 transmission interrupt
                DCD     INTT3ERR_IRQHandler       ; 47:	TSPI3 error interrupt
                DCD     INTT4RX_IRQHandler        ; 48:	TSPI4 reception interrupt
                DCD     INTT4TX_IRQHandler        ; 49:	TSPI4 transmission interrupt
                DCD     INTT4ERR_IRQHandler       ; 50:	TSPI4 error interrupt
                DCD     INTUART0_IRQHandler       ; 51:	Full UART0 transmission and reception interrupt
                DCD     INTRX0_IRQHandler         ; 52:	Serial0 reception interrupt
                DCD     INTTX0_IRQHandler         ; 53:	Serial0 transmission interrupt
                DCD     INTI2C_IRQHandler         ; 54:	I2C interrupt
                DCD     INTADA_IRQHandler         ; 55:	AD conversion interrupt (unitA)
                DCD     INTADB_IRQHandler         ; 56:	AD conversion interrupt (unitB)
                DCD     INTADC_IRQHandler         ; 57:	AD conversion interrupt (unitC)
                DCD     INTADAHP_IRQHandler       ; 58:	High Priority AD conversion interrupt (unitA)
                DCD     INTADBHP_IRQHandler       ; 59:	High Priority AD conversion interrupt (unitB)
                DCD     INTADCHP_IRQHandler       ; 60:	High Priority AD conversion interrupt (unitC)
                DCD     INTEPHC0_IRQHandler       ; 61:	Two-phase pulse input counter 0 interrupt
                DCD     INTPHCP0OVF_IRQHandler    ; 62:	EPHC0 overflow interrupt
                DCD     INTPHCP0PHE_IRQHandler    ; 63:	EPHC0 phase error interrupt
                DCD     INTPHCP0CY0_IRQHandler    ; 64:	EPHC0 cycle interrupt 0
                DCD     INTPHCP0CY1_IRQHandler    ; 65:	EPHC0 cycle interrupt 1
                DCD     INTPHCP0CY2_IRQHandler    ; 66:	EPHC0 cycle interrupt 2
                DCD     INTPHCP0CY3_IRQHandler    ; 67:	EPHC0 cycle interrupt 3
                DCD     INTPHCP0LMT_IRQHandler    ; 68:	EPHC0 cycle outrange interrupt
                DCD     INTEPHC1_IRQHandler       ; 69:	Two-phase pulse input counter 1 interrupt
                DCD     INTPHCP1OVF_IRQHandler    ; 70:	EPHC1 overflow interrupt
                DCD     INTPHCP1PHE_IRQHandler    ; 71:	EPHC1 phase error interrupt
                DCD     INTPHCP1CY0_IRQHandler    ; 72:	EPHC1 cycle interrupt 0
                DCD     INTPHCP1CY1_IRQHandler    ; 73:	EPHC1 cycle interrupt 1
                DCD     INTPHCP1CY2_IRQHandler    ; 74:	EPHC1 cycle interrupt 2
                DCD     INTPHCP1CY3_IRQHandler    ; 75:	EPHC1 cycle interrupt 3
                DCD     INTPHCP1LMT_IRQHandler    ; 76:	EPHC1 cycle outrange interrupt
                DCD     INTEPHC2_IRQHandler       ; 77:	Two-phase pulse input counter 2 interrupt
                DCD     INTPHCP2OVF_IRQHandler    ; 78:	EPHC2 overflow interrupt
                DCD     INTPHCP2PHE_IRQHandler    ; 79:	EPHC2 phase error interrupt
                DCD     INTPHCP2CY0_IRQHandler    ; 80:	EPHC2 cycle interrupt 0
                DCD     INTPHCP2CY1_IRQHandler    ; 81:	EPHC2 cycle interrupt 1
                DCD     INTPHCP2CY2_IRQHandler    ; 82:	EPHC2 cycle interrupt 2
                DCD     INTPHCP2CY3_IRQHandler    ; 83:	EPHC2 cycle interrupt 3
                DCD     INTPHCP2LMT_IRQHandler    ; 84:	EPHC2 cycle outrange interrupt
                DCD     INTTDA0CMP0_IRQHandler    ; 85:	TMRD0 compare match detection interrupt 0 (blockA)
                DCD     INTTDA0CMP1_IRQHandler    ; 86:	TMRD0 compare match detection interrupt 1 (blockA)
                DCD     INTTDA0CMP2_IRQHandler    ; 87:	TMRD0 compare match detection interrupt 2 (blockA)
                DCD     INTTDA0CMP3_IRQHandler    ; 88:	TMRD0 compare match detection interrupt 3 (blockA)
                DCD     INTTDA0CMP4_IRQHandler    ; 89:	TMRD0 compare match detection interrupt 4 (blockA)
                DCD     INTTDA1CMP0_IRQHandler    ; 90:	TMRD1 compare match detection interrupt 0 (blockA)
                DCD     INTTDA1CMP1_IRQHandler    ; 91:	TMRD1 compare match detection interrupt 1 (blockA)
                DCD     INTTDA1CMP2_IRQHandler    ; 92:	TMRD1 compare match detection interrupt 2 (blockA)
                DCD     INTTDA1CMP3_IRQHandler    ; 93:	TMRD1 compare match detection interrupt 3 (blockA)
                DCD     INTTDA1CMP4_IRQHandler    ; 94:	TMRD1 compare match detection interrupt 4 (blockA)
                DCD     INTTDB0CMP0_IRQHandler    ; 95:	TMRD0 compare match detection interrupt 0 (blockB)
                DCD     INTTDB0CMP1_IRQHandler    ; 96:	TMRD0 compare match detection interrupt 1 (blockB)
                DCD     INTTDB0CMP2_IRQHandler    ; 97:	TMRD0 compare match detection interrupt 2 (blockB)
                DCD     INTTDB0CMP3_IRQHandler    ; 98:	TMRD0 compare match detection interrupt 3 (blockB)
                DCD     INTTDB0CMP4_IRQHandler    ; 99:	TMRD0 compare match detection interrupt 4 (blockB)
                DCD     INTTDB1CMP0_IRQHandler    ; 100:	TMRD1 compare match detection interrupt 0 (blockB)
                DCD     INTTDB1CMP1_IRQHandler    ; 101:	TMRD1 compare match detection interrupt 1 (blockB)
                DCD     INTTDB1CMP2_IRQHandler    ; 102:	TMRD1 compare match detection interrupt 2 (blockB)
                DCD     INTTDB1CMP3_IRQHandler    ; 103:	TMRD1 compare match detection interrupt 3 (blockB)
                DCD     INTTDB1CMP4_IRQHandler    ; 104:	TMRD1 compare match detection interrupt 4 (blockB)
                DCD     INTTB0_IRQHandler         ; 105:	TMRB0 compare match detection interrupt
                DCD     INTTB1_IRQHandler         ; 106:	TMRB1 compare match detection interrupt
                DCD     INTTB2_IRQHandler         ; 107:	TMRB2 compare match detection interrupt
                DCD     INTTB3_IRQHandler         ; 108:	TMRB3 compare match detection interrupt
                DCD     INTTB4_IRQHandler         ; 109:	TMRB4 compare match detection interrupt
                DCD     INTTB5_IRQHandler         ; 110:	TMRB5 compare match detection interrupt
                DCD     INTTB6_IRQHandler         ; 111:	TMRB6 compare match detection interrupt
                DCD     INTTB7_IRQHandler         ; 112:	TMRB7 compare match detection interrupt
                DCD     INTTB8_IRQHandler         ; 113:	TMRB8 compare match detection interrupt
                DCD     INTTB9_IRQHandler         ; 114:	TMRB9 compare match detection interrupt
                DCD     INTTBA_IRQHandler         ; 115:	TMRBA compare match detection interrupt
                DCD     INTTBB_IRQHandler         ; 116:	TMRBB compare match detection interrupt
                DCD     INTTBC_IRQHandler         ; 117:	TMRBC compare match detection interrupt
                DCD     INTTBD_IRQHandler         ; 118:	TMRBD compare match detection interrupt
                DCD     INTTBE_IRQHandler         ; 119:	TMRBE compare match detection interrupt
                DCD     INTTBF_IRQHandler         ; 120:	TMRBF compare match detection interrupt
                DCD     INTTBCCAP0_IRQHandler     ; 121:	TMRBC input capture 0 detection interrupt
                DCD     INTTBCCAP1_IRQHandler     ; 122:	TMRBC input capture 1 detection interrupt
                DCD     INTTBDCAP0_IRQHandler     ; 123:	TMRBD input capture 0 detection interrupt
                DCD     INTTBDCAP1_IRQHandler     ; 124:	TMRBD input capture 1 detection interrupt
                DCD     INTTBECAP0_IRQHandler     ; 125:	TMRBE input capture 0 detection interrupt
                DCD     INTTBECAP1_IRQHandler     ; 126:	TMRBE input capture 1 detection interrupt
                DCD     INTTBFCAP0_IRQHandler     ; 127:	TMRBF input capture 0 detection interrupt
                DCD     INTTBFCAP1_IRQHandler     ; 128:	TMRBF input capture 1 detection interrupt
                DCD     INTADAM0_IRQHandler       ; 129:	SAR ADC monitor 0 interrupt (unitA)
                DCD     INTADAM1_IRQHandler       ; 130:	SAR ADC monitor 1 interrupt (unitA)
                DCD     INTADBM0_IRQHandler       ; 131:	SAR ADC monitor 0 interrupt (unitB)
                DCD     INTADBM1_IRQHandler       ; 132:	SAR ADC monitor 1 interrupt (unitB)
                DCD     INTADCM0_IRQHandler       ; 133:	SAR ADC monitor 0 interrupt (unitC)
                DCD     INTADCM1_IRQHandler       ; 134:	SAR ADC monitor 1 interrupt (unitC)
                DCD     INTDMACATC_IRQHandler     ; 135:	DMA terminal count status interrupt (unitA)
                DCD     INTDMACAERR_IRQHandler    ; 136:	DMA error status interrupt (unitA)
                DCD     INTDMACBTC_IRQHandler     ; 137:	DMA terminal count status interrupt (unitB)
                DCD     INTDMACBERR_IRQHandler    ; 138:	DMA error status interrupt (unitB)
                DCD     INTDMACCTC_IRQHandler     ; 139:	DMA terminal count status interrupt (unitC)
                DCD     INTDMACCERR_IRQHandler    ; 140:	DMA error status interrupt (unitC)
                THUMB
; Dummy Exception Handlers (infinite loops which can be modified)

                SECTION .CF_PSW:CODE
                PUBLIC  __psw_table
__psw_table
                DATA
                DCD     0x0F0F0F0F
                DCD     0x0F0F0F0F
                DCD     0x0F0F0F0F
                DCD     0x0F0F0F0F

                THUMB
                
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

                PUBWEAK INTPSCASTOP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCASTOP_IRQHandler
                B       INTPSCASTOP_IRQHandler

                PUBWEAK INTPSCABRK_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCABRK_IRQHandler
                B       INTPSCABRK_IRQHandler

                PUBWEAK INTPSCASTEP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCASTEP_IRQHandler
                B       INTPSCASTEP_IRQHandler

                PUBWEAK INTPSCAII_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCAII_IRQHandler
                B       INTPSCAII_IRQHandler

                PUBWEAK INTPSCAIA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCAIA_IRQHandler
                B       INTPSCAIA_IRQHandler

                PUBWEAK INTPSCBSTOP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCBSTOP_IRQHandler
                B       INTPSCBSTOP_IRQHandler

                PUBWEAK INTPSCBBRK_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCBBRK_IRQHandler
                B       INTPSCBBRK_IRQHandler

                PUBWEAK INTPSCBSTEP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCBSTEP_IRQHandler
                B       INTPSCBSTEP_IRQHandler

                PUBWEAK INTPSCBII_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCBII_IRQHandler
                B       INTPSCBII_IRQHandler

                PUBWEAK INTPSCBIA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCBIA_IRQHandler
                B       INTPSCBIA_IRQHandler

                PUBWEAK INTPSCCSTOP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCCSTOP_IRQHandler
                B       INTPSCCSTOP_IRQHandler

                PUBWEAK INTPSCCBRK_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCCBRK_IRQHandler
                B       INTPSCCBRK_IRQHandler

                PUBWEAK INTPSCCSTEP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCCSTEP_IRQHandler
                B       INTPSCCSTEP_IRQHandler

                PUBWEAK INTPSCCII_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCCII_IRQHandler
                B       INTPSCCII_IRQHandler

                PUBWEAK INTPSCCIA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCCIA_IRQHandler
                B       INTPSCCIA_IRQHandler

                PUBWEAK INTPSCDSTOP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCDSTOP_IRQHandler
                B       INTPSCDSTOP_IRQHandler

                PUBWEAK INTPSCDBRK_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCDBRK_IRQHandler
                B       INTPSCDBRK_IRQHandler

                PUBWEAK INTPSCDSTEP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCDSTEP_IRQHandler
                B       INTPSCDSTEP_IRQHandler

                PUBWEAK INTPSCDII_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCDII_IRQHandler
                B       INTPSCDII_IRQHandler

                PUBWEAK INTPSCDIA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPSCDIA_IRQHandler
                B       INTPSCDIA_IRQHandler

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

                PUBWEAK INTUART0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTUART0_IRQHandler
                B       INTUART0_IRQHandler

                PUBWEAK INTRX0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTRX0_IRQHandler
                B       INTRX0_IRQHandler

                PUBWEAK INTTX0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTX0_IRQHandler
                B       INTTX0_IRQHandler

                PUBWEAK INTI2C_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTI2C_IRQHandler
                B       INTI2C_IRQHandler

                PUBWEAK INTADA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADA_IRQHandler
                B       INTADA_IRQHandler

                PUBWEAK INTADB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADB_IRQHandler
                B       INTADB_IRQHandler

                PUBWEAK INTADC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADC_IRQHandler
                B       INTADC_IRQHandler

                PUBWEAK INTADAHP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAHP_IRQHandler
                B       INTADAHP_IRQHandler

                PUBWEAK INTADBHP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBHP_IRQHandler
                B       INTADBHP_IRQHandler

                PUBWEAK INTADCHP_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCHP_IRQHandler
                B       INTADCHP_IRQHandler

                PUBWEAK INTEPHC0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEPHC0_IRQHandler
                B       INTEPHC0_IRQHandler

                PUBWEAK INTPHCP0OVF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP0OVF_IRQHandler
                B       INTPHCP0OVF_IRQHandler

                PUBWEAK INTPHCP0PHE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP0PHE_IRQHandler
                B       INTPHCP0PHE_IRQHandler

                PUBWEAK INTPHCP0CY0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP0CY0_IRQHandler
                B       INTPHCP0CY0_IRQHandler

                PUBWEAK INTPHCP0CY1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP0CY1_IRQHandler
                B       INTPHCP0CY1_IRQHandler

                PUBWEAK INTPHCP0CY2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP0CY2_IRQHandler
                B       INTPHCP0CY2_IRQHandler

                PUBWEAK INTPHCP0CY3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP0CY3_IRQHandler
                B       INTPHCP0CY3_IRQHandler

                PUBWEAK INTPHCP0LMT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP0LMT_IRQHandler
                B       INTPHCP0LMT_IRQHandler

                PUBWEAK INTEPHC1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEPHC1_IRQHandler
                B       INTEPHC1_IRQHandler

                PUBWEAK INTPHCP1OVF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP1OVF_IRQHandler
                B       INTPHCP1OVF_IRQHandler

                PUBWEAK INTPHCP1PHE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP1PHE_IRQHandler
                B       INTPHCP1PHE_IRQHandler

                PUBWEAK INTPHCP1CY0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP1CY0_IRQHandler
                B       INTPHCP1CY0_IRQHandler

                PUBWEAK INTPHCP1CY1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP1CY1_IRQHandler
                B       INTPHCP1CY1_IRQHandler

                PUBWEAK INTPHCP1CY2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP1CY2_IRQHandler
                B       INTPHCP1CY2_IRQHandler

                PUBWEAK INTPHCP1CY3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP1CY3_IRQHandler
                B       INTPHCP1CY3_IRQHandler

                PUBWEAK INTPHCP1LMT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP1LMT_IRQHandler
                B       INTPHCP1LMT_IRQHandler

                PUBWEAK INTEPHC2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTEPHC2_IRQHandler
                B       INTEPHC2_IRQHandler

                PUBWEAK INTPHCP2OVF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP2OVF_IRQHandler
                B       INTPHCP2OVF_IRQHandler

                PUBWEAK INTPHCP2PHE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP2PHE_IRQHandler
                B       INTPHCP2PHE_IRQHandler

                PUBWEAK INTPHCP2CY0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP2CY0_IRQHandler
                B       INTPHCP2CY0_IRQHandler

                PUBWEAK INTPHCP2CY1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP2CY1_IRQHandler
                B       INTPHCP2CY1_IRQHandler

                PUBWEAK INTPHCP2CY2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP2CY2_IRQHandler
                B       INTPHCP2CY2_IRQHandler

                PUBWEAK INTPHCP2CY3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP2CY3_IRQHandler
                B       INTPHCP2CY3_IRQHandler

                PUBWEAK INTPHCP2LMT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTPHCP2LMT_IRQHandler
                B       INTPHCP2LMT_IRQHandler

                PUBWEAK INTTDA0CMP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA0CMP0_IRQHandler
                B       INTTDA0CMP0_IRQHandler

                PUBWEAK INTTDA0CMP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA0CMP1_IRQHandler
                B       INTTDA0CMP1_IRQHandler

                PUBWEAK INTTDA0CMP2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA0CMP2_IRQHandler
                B       INTTDA0CMP2_IRQHandler

                PUBWEAK INTTDA0CMP3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA0CMP3_IRQHandler
                B       INTTDA0CMP3_IRQHandler

                PUBWEAK INTTDA0CMP4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA0CMP4_IRQHandler
                B       INTTDA0CMP4_IRQHandler

                PUBWEAK INTTDA1CMP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA1CMP0_IRQHandler
                B       INTTDA1CMP0_IRQHandler

                PUBWEAK INTTDA1CMP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA1CMP1_IRQHandler
                B       INTTDA1CMP1_IRQHandler

                PUBWEAK INTTDA1CMP2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA1CMP2_IRQHandler
                B       INTTDA1CMP2_IRQHandler

                PUBWEAK INTTDA1CMP3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA1CMP3_IRQHandler
                B       INTTDA1CMP3_IRQHandler

                PUBWEAK INTTDA1CMP4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDA1CMP4_IRQHandler
                B       INTTDA1CMP4_IRQHandler

                PUBWEAK INTTDB0CMP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB0CMP0_IRQHandler
                B       INTTDB0CMP0_IRQHandler

                PUBWEAK INTTDB0CMP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB0CMP1_IRQHandler
                B       INTTDB0CMP1_IRQHandler

                PUBWEAK INTTDB0CMP2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB0CMP2_IRQHandler
                B       INTTDB0CMP2_IRQHandler

                PUBWEAK INTTDB0CMP3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB0CMP3_IRQHandler
                B       INTTDB0CMP3_IRQHandler

                PUBWEAK INTTDB0CMP4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB0CMP4_IRQHandler
                B       INTTDB0CMP4_IRQHandler

                PUBWEAK INTTDB1CMP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB1CMP0_IRQHandler
                B       INTTDB1CMP0_IRQHandler

                PUBWEAK INTTDB1CMP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB1CMP1_IRQHandler
                B       INTTDB1CMP1_IRQHandler

                PUBWEAK INTTDB1CMP2_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB1CMP2_IRQHandler
                B       INTTDB1CMP2_IRQHandler

                PUBWEAK INTTDB1CMP3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB1CMP3_IRQHandler
                B       INTTDB1CMP3_IRQHandler

                PUBWEAK INTTDB1CMP4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTDB1CMP4_IRQHandler
                B       INTTDB1CMP4_IRQHandler

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

                PUBWEAK INTTB4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB4_IRQHandler
                B       INTTB4_IRQHandler

                PUBWEAK INTTB5_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB5_IRQHandler
                B       INTTB5_IRQHandler

                PUBWEAK INTTB6_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB6_IRQHandler
                B       INTTB6_IRQHandler

                PUBWEAK INTTB7_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB7_IRQHandler
                B       INTTB7_IRQHandler

                PUBWEAK INTTB8_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB8_IRQHandler
                B       INTTB8_IRQHandler

                PUBWEAK INTTB9_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTB9_IRQHandler
                B       INTTB9_IRQHandler

                PUBWEAK INTTBA_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBA_IRQHandler
                B       INTTBA_IRQHandler

                PUBWEAK INTTBB_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBB_IRQHandler
                B       INTTBB_IRQHandler

                PUBWEAK INTTBC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBC_IRQHandler
                B       INTTBC_IRQHandler

                PUBWEAK INTTBD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBD_IRQHandler
                B       INTTBD_IRQHandler

                PUBWEAK INTTBE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBE_IRQHandler
                B       INTTBE_IRQHandler

                PUBWEAK INTTBF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBF_IRQHandler
                B       INTTBF_IRQHandler

                PUBWEAK INTTBCCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBCCAP0_IRQHandler
                B       INTTBCCAP0_IRQHandler

                PUBWEAK INTTBCCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBCCAP1_IRQHandler
                B       INTTBCCAP1_IRQHandler

                PUBWEAK INTTBDCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBDCAP0_IRQHandler
                B       INTTBDCAP0_IRQHandler

                PUBWEAK INTTBDCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBDCAP1_IRQHandler
                B       INTTBDCAP1_IRQHandler

                PUBWEAK INTTBECAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBECAP0_IRQHandler
                B       INTTBECAP0_IRQHandler

                PUBWEAK INTTBECAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBECAP1_IRQHandler
                B       INTTBECAP1_IRQHandler

                PUBWEAK INTTBFCAP0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBFCAP0_IRQHandler
                B       INTTBFCAP0_IRQHandler

                PUBWEAK INTTBFCAP1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTTBFCAP1_IRQHandler
                B       INTTBFCAP1_IRQHandler

                PUBWEAK INTADAM0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAM0_IRQHandler
                B       INTADAM0_IRQHandler

                PUBWEAK INTADAM1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADAM1_IRQHandler
                B       INTADAM1_IRQHandler

                PUBWEAK INTADBM0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBM0_IRQHandler
                B       INTADBM0_IRQHandler

                PUBWEAK INTADBM1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADBM1_IRQHandler
                B       INTADBM1_IRQHandler

                PUBWEAK INTADCM0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCM0_IRQHandler
                B       INTADCM0_IRQHandler

                PUBWEAK INTADCM1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTADCM1_IRQHandler
                B       INTADCM1_IRQHandler

                PUBWEAK INTDMACATC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMACATC_IRQHandler
                B       INTDMACATC_IRQHandler

                PUBWEAK INTDMACAERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMACAERR_IRQHandler
                B       INTDMACAERR_IRQHandler

                PUBWEAK INTDMACBTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMACBTC_IRQHandler
                B       INTDMACBTC_IRQHandler

                PUBWEAK INTDMACBERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMACBERR_IRQHandler
                B       INTDMACBERR_IRQHandler

                PUBWEAK INTDMACCTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMACCTC_IRQHandler
                B       INTDMACCTC_IRQHandler

                PUBWEAK INTDMACCERR_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
INTDMACCERR_IRQHandler
                B       INTDMACCERR_IRQHandler

                END
