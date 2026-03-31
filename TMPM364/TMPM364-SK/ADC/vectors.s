/**************************************************
 *
 * Toshiba TMPM364 vector table
 *
 * Copyright 2011 IAR Systems. All rights reserved.
 *
 * $Revision: 503 $
 *
 **************************************************/
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:ROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)               ; Top of Stack
        DCD     __iar_program_start       ; Reset Handler
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
        DCD     INT0_IRQHandler           ; 0:  External Interrupt 0
        DCD     INT1_IRQHandler           ; 1:  External Interrupt 1
        DCD     INT2_IRQHandler           ; 2:  External Interrupt 2
        DCD     INT3_IRQHandler           ; 3:  External Interrupt 3
        DCD     INT4_IRQHandler           ; 4:  External Interrupt 4
        DCD     INT5_IRQHandler           ; 5:  External Interrupt 5
        DCD     INT6_IRQHandler           ; 6:  External Interrupt 6
        DCD     INT7_IRQHandler           ; 7:  External Interrupt 7
        DCD     INT8_IRQHandler           ; 8:  External Interrupt 8
        DCD     INT9_IRQHandler           ; 9:  External Interrupt 9
        DCD     INTA_IRQHandler           ;10:  External Interrupt A
        DCD     INTB_IRQHandler           ;11:  External Interrupt B
        DCD     INTC_IRQHandler           ;12:  External Interrupt C
        DCD     INTD_IRQHandler           ;13:  External Interrupt D
        DCD     0                         ;14:	Reserved
        DCD     0                         ;15:	Reserved
        DCD     INTRX0_IRQHandler         ;16:  Serial reception (channel.0)
        DCD     INTTX0_IRQHandler         ;17:  Serial transmission (channel.0)
        DCD     INTRX1_IRQHandler         ;18:  Serial reception (channel.1)
        DCD     INTTX1_IRQHandler         ;19:  Serial transmission (channel.1)
        DCD     INTRX2_IRQHandler         ;20:  Serial reception (channel.2)
        DCD     INTTX2_IRQHandler         ;21:  Serial transmission (channel.2)
        DCD     INTRX3_IRQHandler         ;22:  Serial reception (channel.3)
        DCD     INTTX3_IRQHandler         ;23:  Serial transmission (channel.3)
        DCD     INTRX4_IRQHandler         ;24:  Serial reception (channel.4)
        DCD     INTTX4_IRQHandler         ;25:  Serial transmission (channel.4)
        DCD     INTSBI0_IRQHandler        ;26:  Serial Bus Interface 0 interrupt
        DCD     INTSBI1_IRQHandler        ;27:  Serial Bus Interface 1 interrupt
        DCD     INTCECRX_IRQHandler       ;28:  CEC reception
        DCD     INTCECTX_IRQHandler       ;29:  CEC transmission
        DCD     INTAINTRMCRX0_IRQHandler  ;30:  Remote control signal reception (channel.0)
        DCD     INTAINTRMCRX1_IRQHandler  ;31:  Remote control signal reception (channel.1)
        DCD     INTRTC_IRQHandler         ;32:  Real time clock timer
        DCD     INTKWUP_IRQHandler        ;33:  Key On wakeup
        DCD     INTSBI2_IRQHandler        ;34:  Serial Bus Interface 2 interrupt
        DCD     INTSBI3_IRQHandler        ;35:  Serial Bus Interface 3 interrupt
        DCD     INTSBI4_IRQHandler        ;36:  Serial Bus Interface 4 interrupt
        DCD     INTADHP_IRQHandler        ;37:  Highest priority AD conversion complete interrupt
        DCD     INTADM0_IRQHandler        ;38:  AD conversion monitoring function interrupt 0
        DCD     INTADM1_IRQHandler        ;39:  AD conversion monitoring function interrupt 1
        DCD     INTTB0_IRQHandler         ;40:  16bit TMRB0 match detection
        DCD     INTTB1_IRQHandler         ;41:  16bit TMRB1 match detection
        DCD     INTTB2_IRQHandler         ;42:  16bit TMRB2 match detection
        DCD     INTTB3_IRQHandler         ;43:  16bit TMRB3 match detection
        DCD     INTTB4_IRQHandler         ;44:  16bit TMRB4 match detection
        DCD     INTTB5_IRQHandler         ;45:  16bit TMRB5 match detection
        DCD     INTTB6_IRQHandler         ;46:  16bit TMRB6 match detection
        DCD     INTTB7_IRQHandler         ;47:  16bit TMRB7 match detection
        DCD     INTTB8_IRQHandler         ;48:  16bit TMRB8 match detection
        DCD     INTTB9_IRQHandler         ;49:  16bit TMRB9 match detection
        DCD     INTTBA_IRQHandler         ;50:  16bit TMRBA match detection
        DCD     INTTBB_IRQHandler         ;51:  16bit TMRBB match detection
        DCD     INTTBC_IRQHandler         ;52:  16bit TMRBC match detection
        DCD     INTTBD_IRQHandler         ;53:  16bit TMRBD match detection
        DCD     INTTBE_IRQHandler         ;54:  16bit TMRBE match detection
        DCD     INTTBF_IRQHandler         ;55:  16bit TMRBF match detection
        DCD     INTUSB_IRQHandler         ;56:  USB interrupt
        DCD     INTCANSTA_IRQHandler      ;57:  CAN Status
        DCD     INTAD_IRQHandler          ;58:  AD conversion complete interrupt
        DCD     INTSSP0_IRQHandler        ;59:  Syncronus serial port
        DCD     INTRX5_IRQHandler         ;60:  Serial reception (channel.5)
        DCD     INTTX5_IRQHandler         ;61:  Serial transmission (channel.5)
        DCD     INTRX6_IRQHandler         ;62:  Serial reception (channel.6)
        DCD     INTTX6_IRQHandler         ;63:  Serial transmission (channel.6)
        DCD     INTRX7_IRQHandler         ;64:  Serial reception (channel.7)
        DCD     INTTX7_IRQHandler         ;65:  Serial transmission (channel.7)
        DCD     INTRX8_IRQHandler         ;66:  Serial reception (channel.8)
        DCD     INTTX8_IRQHandler         ;67:  Serial transmission (channel.8)
        DCD     INTRX9_IRQHandler         ;68:  Serial reception (channel.9)
        DCD     INTTX9_IRQHandler         ;69:  Serial transmission (channel.9)
        DCD     INTRX10_IRQHandler        ;70:  Serial reception (channel.A)
        DCD     INTTX10_IRQHandler        ;71:  Serial transmission (channel.A)
        DCD     INTRX11_IRQHandler        ;72:  Serial reception (channel.B)
        DCD     INTTX11_IRQHandler        ;73:  Serial transmission (channel.B)
        DCD     INTCAP10_IRQHandler       ;74: 16bit TMRB input capture 10
        DCD     INTCAP11_IRQHandler       ;75: 16bit TMRB input capture 11
        DCD     INTCAP20_IRQHandler       ;76: 16bit TMRB input capture 20
        DCD     INTCAP21_IRQHandler       ;77: 16bit TMRB input capture 21
        DCD     INTCANRX_IRQHandler       ;78: CAN Reception
        DCD     INTCANTX_IRQHandler       ;79: CAN Transmission
        DCD     INTCAP50_IRQHandler       ;80: 16bit TMRB input capture 50
        DCD     INTCAP51_IRQHandler       ;81: 16bit TMRB input capture 51
        DCD     INTCAP60_IRQHandler       ;82: 16bit TMRB input capture 60
        DCD     INTCAP61_IRQHandler       ;83: 16bit TMRB input capture 61
        DCD     INTCAP70_IRQHandler       ;84: 16bit TMRB input capture 70
        DCD     INTCAP71_IRQHandler       ;85: 16bit TMRB input capture 71
        DCD     INTCAP90_IRQHandler       ;86: 16bit TMRB input capture 90
        DCD     INTCAP91_IRQHandler       ;87: 16bit TMRB input capture 91
        DCD     INTCAPA0_IRQHandler       ;88: 16bit TMRB input capture A0
        DCD     INTCAPA1_IRQHandler       ;89: 16bit TMRB input capture A1
        DCD     INTCAPB0_IRQHandler       ;90: 16bit TMRB input capture B0
        DCD     INTCAPB1_IRQHandler       ;91: 16bit TMRB input capture B1
        DCD     INTCAPD0_IRQHandler       ;92: 16bit TMRB input capture D0
        DCD     INTCAPD1_IRQHandler       ;93: 16bit TMRB input capture D1
        DCD     INTCAPE0_IRQHandler       ;94: 16bit TMRB input capture E0
        DCD     INTCAPE1_IRQHandler       ;95: 16bit TMRB input capture E1
        DCD     INTCAPF0_IRQHandler       ;96: 16bit TMRB input capture F0
        DCD     INTCAPF1_IRQHandler       ;97: 16bit TMRB input capture F1
        DCD     INTDMACERR_IRQHandler     ;98: DMA transmission error
        DCD     INTDMACTC_IRQHandler      ;99: DMA transmission completion

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
      PUBWEAK NMI_Handler
      PUBWEAK HardFault_Handler
      PUBWEAK MemManage_Handler
      PUBWEAK BusFault_Handler
      PUBWEAK UsageFault_Handler
      PUBWEAK SVC_Handler
      PUBWEAK DebugMon_Handler
      PUBWEAK PendSV_Handler
      PUBWEAK SysTick_Handler
      PUBWEAK INT0_IRQHandler
      PUBWEAK INT1_IRQHandler
      PUBWEAK INT2_IRQHandler
      PUBWEAK INT3_IRQHandler
      PUBWEAK INT4_IRQHandler
      PUBWEAK INT5_IRQHandler
      PUBWEAK INT6_IRQHandler
      PUBWEAK INT7_IRQHandler
      PUBWEAK INT8_IRQHandler
      PUBWEAK INT9_IRQHandler
      PUBWEAK INTA_IRQHandler
      PUBWEAK INTB_IRQHandler
      PUBWEAK INTC_IRQHandler
      PUBWEAK INTD_IRQHandler
      PUBWEAK INTRX0_IRQHandler
      PUBWEAK INTTX0_IRQHandler
      PUBWEAK INTRX1_IRQHandler
      PUBWEAK INTTX1_IRQHandler
      PUBWEAK INTRX2_IRQHandler
      PUBWEAK INTTX2_IRQHandler
      PUBWEAK INTRX3_IRQHandler
      PUBWEAK INTTX3_IRQHandler
      PUBWEAK INTRX4_IRQHandler
      PUBWEAK INTTX4_IRQHandler
      PUBWEAK INTSBI0_IRQHandler
      PUBWEAK INTSBI1_IRQHandler
      PUBWEAK INTCECRX_IRQHandler
      PUBWEAK INTCECTX_IRQHandler
      PUBWEAK INTAINTRMCRX0_IRQHandler
      PUBWEAK INTAINTRMCRX1_IRQHandler
      PUBWEAK INTRTC_IRQHandler
      PUBWEAK INTKWUP_IRQHandler
      PUBWEAK INTSBI2_IRQHandler
      PUBWEAK INTSBI3_IRQHandler
      PUBWEAK INTSBI4_IRQHandler
      PUBWEAK INTADHP_IRQHandler
      PUBWEAK INTADM0_IRQHandler
      PUBWEAK INTADM1_IRQHandler
      PUBWEAK INTTB0_IRQHandler
      PUBWEAK INTTB1_IRQHandler
      PUBWEAK INTTB2_IRQHandler
      PUBWEAK INTTB3_IRQHandler
      PUBWEAK INTTB4_IRQHandler
      PUBWEAK INTTB5_IRQHandler
      PUBWEAK INTTB6_IRQHandler
      PUBWEAK INTTB7_IRQHandler
      PUBWEAK INTTB8_IRQHandler
      PUBWEAK INTTB9_IRQHandler
      PUBWEAK INTTBA_IRQHandler
      PUBWEAK INTTBB_IRQHandler
      PUBWEAK INTTBC_IRQHandler
      PUBWEAK INTTBD_IRQHandler
      PUBWEAK INTTBE_IRQHandler
      PUBWEAK INTTBF_IRQHandler
      PUBWEAK INTUSB_IRQHandler
      PUBWEAK INTCANSTA_IRQHandler
      PUBWEAK INTAD_IRQHandler
      PUBWEAK INTSSP0_IRQHandler
      PUBWEAK INTRX5_IRQHandler
      PUBWEAK INTTX5_IRQHandler
      PUBWEAK INTRX6_IRQHandler
      PUBWEAK INTTX6_IRQHandler
      PUBWEAK INTRX7_IRQHandler
      PUBWEAK INTTX7_IRQHandler
      PUBWEAK INTRX8_IRQHandler
      PUBWEAK INTTX8_IRQHandler
      PUBWEAK INTRX9_IRQHandler
      PUBWEAK INTTX9_IRQHandler
      PUBWEAK INTRX10_IRQHandler
      PUBWEAK INTTX10_IRQHandler
      PUBWEAK INTRX11_IRQHandler
      PUBWEAK INTTX11_IRQHandler
      PUBWEAK INTCAP10_IRQHandler
      PUBWEAK INTCAP11_IRQHandler
      PUBWEAK INTCAP20_IRQHandler
      PUBWEAK INTCAP21_IRQHandler
      PUBWEAK INTCANRX_IRQHandler
      PUBWEAK INTCANTX_IRQHandler
      PUBWEAK INTCAP50_IRQHandler
      PUBWEAK INTCAP51_IRQHandler
      PUBWEAK INTCAP60_IRQHandler
      PUBWEAK INTCAP61_IRQHandler
      PUBWEAK INTCAP70_IRQHandler
      PUBWEAK INTCAP71_IRQHandler
      PUBWEAK INTCAP90_IRQHandler
      PUBWEAK INTCAP91_IRQHandler
      PUBWEAK INTCAPA0_IRQHandler
      PUBWEAK INTCAPA1_IRQHandler
      PUBWEAK INTCAPB0_IRQHandler
      PUBWEAK INTCAPB1_IRQHandler
      PUBWEAK INTCAPD0_IRQHandler
      PUBWEAK INTCAPD1_IRQHandler
      PUBWEAK INTCAPE0_IRQHandler
      PUBWEAK INTCAPE1_IRQHandler
      PUBWEAK INTCAPF0_IRQHandler
      PUBWEAK INTCAPF1_IRQHandler
      PUBWEAK INTDMACERR_IRQHandler
      PUBWEAK INTDMACTC_IRQHandler

      SECTION .text:CODE:REORDER:NOROOT(1)
      THUMB
NMI_Handler
HardFault_Handler
MemManage_Handler
BusFault_Handler
UsageFault_Handler
SVC_Handler
DebugMon_Handler
PendSV_Handler
SysTick_Handler
INT0_IRQHandler
INT1_IRQHandler
INT2_IRQHandler
INT3_IRQHandler
INT4_IRQHandler
INT5_IRQHandler
INT6_IRQHandler
INT7_IRQHandler
INT8_IRQHandler
INT9_IRQHandler
INTA_IRQHandler
INTB_IRQHandler
INTC_IRQHandler
INTD_IRQHandler
INTRX0_IRQHandler
INTTX0_IRQHandler
INTRX1_IRQHandler
INTTX1_IRQHandler
INTRX2_IRQHandler
INTTX2_IRQHandler
INTRX3_IRQHandler
INTTX3_IRQHandler
INTRX4_IRQHandler
INTTX4_IRQHandler
INTSBI0_IRQHandler
INTSBI1_IRQHandler
INTCECRX_IRQHandler
INTCECTX_IRQHandler
INTAINTRMCRX0_IRQHandler
INTAINTRMCRX1_IRQHandler
INTRTC_IRQHandler
INTKWUP_IRQHandler
INTSBI2_IRQHandler
INTSBI3_IRQHandler
INTSBI4_IRQHandler
INTADHP_IRQHandler
INTADM0_IRQHandler
INTADM1_IRQHandler
INTTB0_IRQHandler
INTTB1_IRQHandler
INTTB2_IRQHandler
INTTB3_IRQHandler
INTTB4_IRQHandler
INTTB5_IRQHandler
INTTB6_IRQHandler
INTTB7_IRQHandler
INTTB8_IRQHandler
INTTB9_IRQHandler
INTTBA_IRQHandler
INTTBB_IRQHandler
INTTBC_IRQHandler
INTTBD_IRQHandler
INTTBE_IRQHandler
INTTBF_IRQHandler
INTUSB_IRQHandler
INTCANSTA_IRQHandler
INTAD_IRQHandler
INTSSP0_IRQHandler
INTRX5_IRQHandler
INTTX5_IRQHandler
INTRX6_IRQHandler
INTTX6_IRQHandler
INTRX7_IRQHandler
INTTX7_IRQHandler
INTRX8_IRQHandler
INTTX8_IRQHandler
INTRX9_IRQHandler
INTTX9_IRQHandler
INTRX10_IRQHandler
INTTX10_IRQHandler
INTRX11_IRQHandler
INTTX11_IRQHandler
INTCAP10_IRQHandler
INTCAP11_IRQHandler
INTCAP20_IRQHandler
INTCAP21_IRQHandler
INTCANRX_IRQHandler
INTCANTX_IRQHandler
INTCAP50_IRQHandler
INTCAP51_IRQHandler
INTCAP60_IRQHandler
INTCAP61_IRQHandler
INTCAP70_IRQHandler
INTCAP71_IRQHandler
INTCAP90_IRQHandler
INTCAP91_IRQHandler
INTCAPA0_IRQHandler
INTCAPA1_IRQHandler
INTCAPB0_IRQHandler
INTCAPB1_IRQHandler
INTCAPD0_IRQHandler
INTCAPD1_IRQHandler
INTCAPE0_IRQHandler
INTCAPE1_IRQHandler
INTCAPF0_IRQHandler
INTCAPF1_IRQHandler
INTDMACERR_IRQHandler
INTDMACTC_IRQHandler
Default_Handler
        B Default_Handler
        END
