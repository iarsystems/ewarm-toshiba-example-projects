/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2012 IAR Systems. All rights reserved.
 *
 * $Revision: 41 $
 *
 **************************************************/

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
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

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start

        PUBLIC  __vector_table
        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     __iar_program_start         ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; MPU Fault Handler
        DCD     BusFault_Handler            ; Bus Fault Handler
        DCD     UsageFault_Handler          ; Usage Fault Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     DebugMon_Handler            ; Debug Monitor Handler
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler
        DCD     INT_0_IRQHandler         		;   0 External Interrupt 0
        DCD     INT_1_IRQHandler         		;   1 External Interrupt 1
        DCD     INT_2_IRQHandler         		;   2 External Interrupt 2
        DCD     INT_3_IRQHandler         		;   3 External Interrupt 3
        DCD     INT_4_IRQHandler         		;   4 External Interrupt 4
        DCD     INT_5_IRQHandler         		;   5 External Interrupt 5
        DCD     INT_6_IRQHandler         		;   6 External Interrupt 6
        DCD     INT_7_IRQHandler         		;   7 External Interrupt 7
        DCD     INT_8_IRQHandler         		;   8 External Interrupt 8
        DCD     INT_9_IRQHandler         		;   9 External Interrupt 9
        DCD     INT_A_IRQHandler         		;  10 External Interrupt A
        DCD     INT_B_IRQHandler         		;  11 External Interrupt B
        DCD     INT_C_IRQHandler         		;  12 External Interrupt C
        DCD     INT_USBPON_IRQHandler       ;  13 USB Power On connection detection interrupt
        DCD     INT_E_IRQHandler        		;  14 External Interrupt E
        DCD     INT_F_IRQHandler        		;  15 External Interrupt F
        DCD     INT_RX0_IRQHandler   				;  16 Serial reception (channel.0)
        DCD     INT_TX0_IRQHandler   				;  17 Serial transmit (channel.0)
        DCD     INT_RX1_IRQHandler   				;  18 Serial reception (channel.1)
        DCD     INT_TX1_IRQHandler   				;  19 Serial transmit (channel.1)
        DCD     INT_RX2_IRQHandler   				;  10 Serial reception (channel.2)
        DCD     INT_TX2_IRQHandler   				;  21 Serial transmit (channel.2)
        DCD     INT_RX3_IRQHandler   				;  22 Serial reception (channel.3)
        DCD     INT_TX3_IRQHandler   				;  23 Serial transmit (channel.3)
        DCD     INT_UART0_IRQHandler        ;  24 UART interrupt (UART channel.0)
        DCD     INT_UART1_IRQHandler        ;  25 UART interrupt (UART channel.1)
        DCD     INT_SBI0_IRQHandler        	;  26 Serial bus interface 0
        DCD     INT_SBI1_IRQHandler        	;  27 Serial bus interface 1
        DCD     INT_SBI2_IRQHandler        	;  28 Serial bus interface 2
        DCD     INT_SSP0_IRQHandler        	;  29 SPI serial interface 0
        DCD     INT_SSP1_IRQHandler        	;  20 SPI serial interface 1
        DCD     INT_SSP2_IRQHandler        	;  31 SPI serial interface 2
        DCD     INT_USBH_IRQHandler        	;  32 USB Host Interrupt
        DCD     INT_USBD_IRQHandler        	;  33 USB Device Interrupt
        DCD     INT_USBWKUP_IRQHandler      ;  34 USB device wakeup Interrupt
        DCD     INT_CANRX_IRQHandler        ;  35 CAN reception
        DCD     INT_CANTX_IRQHandler        ;  36 CAN transmission
        DCD     INT_CANGB_IRQHandler        ;  37 CAN status
        DCD     INT_ETH_IRQHandler          ;  38 Ethernet interrupt
        DCD     INT_ETHWK_IRQHandler        ;  39 Ethernet interrupt
        DCD     INT_ADAHP_IRQHandler        ;  30 Highest priority AD conversion complete interrupt CH-A
        DCD     INT_ADAM0_IRQHandler        ;  41 AD conversion monitoring function interrupt 0 CH-A
        DCD     INT_ADAM1_IRQHandler        ;  42 AD conversion monitoring function interrupt 1 CH-A
        DCD     INT_ADA_IRQHandler        	;  43 AD conversion complete interrupt CH-A
        DCD     INT_ADBHP_IRQHandler        ;  44 Highest priority AD conversion complete interrupt CH-B
        DCD     INT_ADBM0_IRQHandler        ;  45 AD conversion monitoring function interrupt 0 CH-B
        DCD     INT_ADBM1_IRQHandler        ;  46 AD conversion monitoring function interrupt 1 CH-B
        DCD     INT_ADB_IRQHandler        	;  47 AD conversion complete interrupt CH-B
        DCD     INT_EMG0_IRQHandler        	;  48 PMD EMG interrupt (ch 0)
        DCD     INT_PMD0_IRQHandler         ;  49 PMD PWM interrupt (ch 0)
        DCD     INT_ENC0_IRQHandler         ;  50 PMD encoder input interrupt (ch 0)
        DCD     INT_EMG1_IRQHandler        	;  51 PMD EMG interrupt (ch 1)
        DCD     INT_PMD1_IRQHandler         ;  52 PMD PWM interrupt (ch 1)
        DCD     INT_ENC1_IRQHandler         ;  53 PMD encoder input interrupt (ch 1)
        DCD     INT_MTEMG0_IRQHandler       ;  54 MPT EMG interrupt (ch 0)
        DCD     INT_MTPTB00_IRQHandler      ;  55 MPT compare match0 interrupt (ch 0)
        DCD     INT_MTPTB01_IRQHandler      ;  56 MPT compare match1 interrupt (ch 0)
        DCD     INT_MTCAP00_IRQHandler      ;  57 MPT input capture0 interrupt (ch 0)
        DCD     INT_MTCAP01_IRQHandler      ;  58 MPT input capture1 interrupt (ch 0)
        DCD     INT_MTEMG1_IRQHandler       ;  59 MPT EMG interrupt (ch 1)
        DCD     INT_MTPTB10_IRQHandler      ;  60 MPT compare match0 interrupt (ch 1)
        DCD     INT_MTPTB11_IRQHandler      ;  61 MPT compare match1 interrupt (ch 1)
        DCD     INT_MTCAP10_IRQHandler      ;  62 MPT input capture0 interrupt (ch 1)
        DCD     INT_MTCAP11_IRQHandler      ;  63 MPT input capture1 interrupt (ch 1)
        DCD     INT_MTEMG2_IRQHandler       ;  64 MPT EMG interrupt (ch 2)
        DCD     INT_MTPTB20_IRQHandler      ;  65 MPT compare match0 interrupt (ch 2)
        DCD     INT_MTPTB21_IRQHandler      ;  66 MPT compare match1 interrupt (ch 2)
        DCD     INT_MTCAP20_IRQHandler      ;  67 MPT input capture0 interrupt (ch 2)
        DCD     INT_MTCAP21_IRQHandler      ;  68 MPT input capture1 interrupt (ch 2)
        DCD     INT_MTEMG3_IRQHandler       ;  69 MPT EMG interrupt (ch 3)
        DCD     INT_MTPTB30_IRQHandler      ;  70 MPT compare match0 interrupt (ch 3)
        DCD     INT_MTPTB31_IRQHandler      ;  71 MPT compare match1 interrupt (ch 3)
        DCD     INT_MTCAP30_IRQHandler      ;  72 MPT input capture0 interrupt (ch 3)
        DCD     INT_MTCAP31_IRQHandler      ;  73 MPT input capture1 interrupt (ch 3)
        DCD     INT_RMCRX_IRQHandler        ;  74 Remocon reception
        DCD     INT_TB0_IRQHandler        	;  75 TMRB compare match0 (ch-0)
        DCD     INT_TCAP00_IRQHandler       ;  76 TMRB input capture0 (ch-0)
        DCD     INT_TCAP01_IRQHandler       ;  77 TMRB input capture1 (ch-0)
        DCD     INT_TB1_IRQHandler        	;  78 TMRB compare match0 (ch-1)
        DCD     INT_TCAP10_IRQHandler       ;  79 TMRB input capture0 (ch-1)
        DCD     INT_TCAP11_IRQHandler       ;  80 TMRB input capture1 (ch-1)
        DCD     INT_TB2_IRQHandler        	;  81 TMRB compare match0 (ch-2)
        DCD     INT_TCAP20_IRQHandler       ;  82 TMRB input capture0 (ch-2)
        DCD     INT_TCAP21_IRQHandler       ;  83 TMRB input capture1 (ch-2)
        DCD     INT_TB3_IRQHandler        	;  84 TMRB compare match0 (ch-3)
        DCD     INT_TCAP30_IRQHandler       ;  85 TMRB input capture0 (ch-3)
        DCD     INT_TCAP31_IRQHandler       ;  86 TMRB input capture1 (ch-3)
        DCD     INT_TB4_IRQHandler        	;  87 TMRB compare match0 (ch-4)
        DCD     INT_TCAP40_IRQHandler       ;  88 TMRB input capture0 (ch-4)
        DCD     INT_TCAP41_IRQHandler       ;  89 TMRB input capture1 (ch-4)
        DCD     INT_TB5_IRQHandler        	;  90 TMRB compare match0 (ch-5)
        DCD     INT_TCAP50_IRQHandler       ;  91 TMRB input capture0 (ch-5)
        DCD     INT_TCAP51_IRQHandler       ;  92 TMRB input capture1 (ch-5)
        DCD     INT_TB6_IRQHandler        	;  93 TMRB compare match0 (ch-6)
        DCD     INT_TCAP60_IRQHandler       ;  94 TMRB input capture0 (ch-6)
        DCD     INT_TCAP61_IRQHandler       ;  95 TMRB input capture1 (ch-6)
        DCD     INT_TB7_IRQHandler        	;  96 TMRB compare match0 (ch-7)
        DCD     INT_TCAP70_IRQHandler       ;  97 TMRB input capture0 (ch-7)
        DCD     INT_TCAP71_IRQHandler       ;  98 TMRB input capture1 (ch-7)
        DCD     INT_RTC_IRQHandler        	;  99 RTC interrupt
        DCD     INT_DMAADA_IRQHandler       ; 100 DMA ADC conversion complete (ch-A)
        DCD     INT_DMAADB_IRQHandler       ; 101 DMA ADC conversion complete (ch-B)
        DCD     INT_DMADAA_IRQHandler       ; 102 DMA ADC conversion trigger (ch-A)
        DCD     INT_DMADAB_IRQHandler       ; 103 DMA ADC conversion trigger (ch-B)
        DCD     INT_DMASPT0_IRQHandler      ; 104 DMA SSP transmission (ch-0)
        DCD     INT_DMASPR0_IRQHandler      ; 105 DMA SSP reception (ch-0)
        DCD     INT_DMASPT1_IRQHandler      ; 106 DMA SSP transmission (ch-1)
        DCD     INT_DMASPR1_IRQHandler      ; 107 DMA SSP reception (ch-1)
        DCD     INT_DMASPT2_IRQHandler      ; 108 DMA SSP transmission (ch-2)
        DCD     INT_DMASPR2_IRQHandler      ; 109 DMA SSP reception (ch-2)
        DCD     INT_DMAUTR0_IRQHandler      ; 110 DMA UART reception (ch-0)
        DCD     INT_DMAUTT0_IRQHandler      ; 111 DMA UART transmission (ch-0)
        DCD     INT_DMAUTR1_IRQHandler      ; 112 DMA UART reception (ch-1)
        DCD     INT_DMAUTT1_IRQHandler      ; 113 DMA UART transmission (ch-1)
        DCD     INT_DMARX0_IRQHandler      	; 114 DMA SIO/UART reception (ch-0)
        DCD     INT_DMATX0_IRQHandler      	; 115 DMA SIO/UART transmission (ch-0)
        DCD     INT_DMARX1_IRQHandler      	; 116 DMA SIO/UART reception (ch-1)
        DCD     INT_DMATX1_IRQHandler      	; 117 DMA SIO/UART transmission (ch-1)
        DCD     INT_DMARX2_IRQHandler      	; 118 DMA SIO/UART reception (ch-2)
        DCD     INT_DMATX2_IRQHandler      	; 119 DMA SIO/UART transmission (ch-2)
        DCD     INT_DMARX3_IRQHandler      	; 120 DMA SIO/UART reception (ch-3)
        DCD     INT_DMATX3_IRQHandler      	; 121 DMA SIO/UART transmission (ch-3)
        DCD     INT_I2CI1_IRQHandler        ; 122 DMA I2C/SIO (ch-1)
        DCD     INT_I2CI1_IRQHandler        ; 123 DMA I2C/SIO (ch-2)
        DCD     INT_DMATB_IRQHandler        ; 124 DMA TMRB compare match (ch 0-4)
        DCD     INT_DMARQ_IRQHandler        ; 125 DMA request pin
        DCD     INT_DMAAERR_IRQHandler      ; 126 DMA transmission error interrupt (ch-A)
        DCD     INT_DMAAERR_IRQHandler      ; 127 DMA transmission error interrupt (ch-B)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        SECTION .text:CODE:REORDER:NOROOT(1)

        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK MemManage_Handler
        PUBWEAK BusFault_Handler
        PUBWEAK UsageFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK DebugMon_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK INT_0_IRQHandler
        PUBWEAK INT_1_IRQHandler
        PUBWEAK INT_2_IRQHandler
        PUBWEAK INT_3_IRQHandler
        PUBWEAK INT_4_IRQHandler
        PUBWEAK INT_5_IRQHandler
        PUBWEAK INT_6_IRQHandler
        PUBWEAK INT_7_IRQHandler
        PUBWEAK INT_8_IRQHandler
        PUBWEAK INT_9_IRQHandler
        PUBWEAK INT_A_IRQHandler
        PUBWEAK INT_B_IRQHandler
        PUBWEAK INT_C_IRQHandler
        PUBWEAK INT_USBPON_IRQHandler
        PUBWEAK INT_E_IRQHandler
        PUBWEAK INT_F_IRQHandler
        PUBWEAK INT_RX0_IRQHandler
        PUBWEAK INT_TX0_IRQHandler
        PUBWEAK INT_RX1_IRQHandler
        PUBWEAK INT_TX1_IRQHandler
        PUBWEAK INT_RX2_IRQHandler
        PUBWEAK INT_TX2_IRQHandler
        PUBWEAK INT_RX3_IRQHandler
        PUBWEAK INT_TX3_IRQHandler
        PUBWEAK INT_UART0_IRQHandler
        PUBWEAK INT_UART1_IRQHandler
        PUBWEAK INT_SBI0_IRQHandler
        PUBWEAK INT_SBI1_IRQHandler
        PUBWEAK INT_SBI2_IRQHandler
        PUBWEAK INT_SSP0_IRQHandler
        PUBWEAK INT_SSP1_IRQHandler
        PUBWEAK INT_SSP2_IRQHandler
        PUBWEAK INT_USBH_IRQHandler
        PUBWEAK INT_USBD_IRQHandler
        PUBWEAK INT_USBWKUP_IRQHandler
        PUBWEAK INT_CANRX_IRQHandler
        PUBWEAK INT_CANTX_IRQHandler
        PUBWEAK INT_CANGB_IRQHandler
        PUBWEAK INT_ETH_IRQHandler
        PUBWEAK INT_ETHWK_IRQHandler
        PUBWEAK INT_ADAHP_IRQHandler
        PUBWEAK INT_ADAM0_IRQHandler
        PUBWEAK INT_ADAM1_IRQHandler
        PUBWEAK INT_ADA_IRQHandler
        PUBWEAK INT_ADBHP_IRQHandler
        PUBWEAK INT_ADBM0_IRQHandler
        PUBWEAK INT_ADBM1_IRQHandler
        PUBWEAK INT_ADB_IRQHandler
        PUBWEAK INT_EMG0_IRQHandler
        PUBWEAK INT_PMD0_IRQHandler
        PUBWEAK INT_ENC0_IRQHandler
        PUBWEAK INT_EMG1_IRQHandler
        PUBWEAK INT_PMD1_IRQHandler
        PUBWEAK INT_ENC1_IRQHandler
        PUBWEAK INT_MTEMG0_IRQHandler
        PUBWEAK INT_MTPTB00_IRQHandler
        PUBWEAK INT_MTPTB01_IRQHandler
        PUBWEAK INT_MTCAP00_IRQHandler
        PUBWEAK INT_MTCAP01_IRQHandler
        PUBWEAK INT_MTEMG1_IRQHandler
        PUBWEAK INT_MTPTB10_IRQHandler
        PUBWEAK INT_MTPTB11_IRQHandler
        PUBWEAK INT_MTCAP10_IRQHandler
        PUBWEAK INT_MTCAP11_IRQHandler
        PUBWEAK INT_MTEMG2_IRQHandler
        PUBWEAK INT_MTPTB20_IRQHandler
        PUBWEAK INT_MTPTB21_IRQHandler
        PUBWEAK INT_MTCAP20_IRQHandler
        PUBWEAK INT_MTCAP21_IRQHandler
        PUBWEAK INT_MTEMG3_IRQHandler
        PUBWEAK INT_MTPTB30_IRQHandler
        PUBWEAK INT_MTPTB31_IRQHandler
        PUBWEAK INT_MTCAP30_IRQHandler
        PUBWEAK INT_MTCAP31_IRQHandler
        PUBWEAK INT_RMCRX_IRQHandler
        PUBWEAK INT_TB0_IRQHandler
        PUBWEAK INT_TCAP00_IRQHandler
        PUBWEAK INT_TCAP01_IRQHandler
        PUBWEAK INT_TB1_IRQHandler
        PUBWEAK INT_TCAP10_IRQHandler
        PUBWEAK INT_TCAP11_IRQHandler
        PUBWEAK INT_TB2_IRQHandler
        PUBWEAK INT_TCAP20_IRQHandler
        PUBWEAK INT_TCAP21_IRQHandler
        PUBWEAK INT_TB3_IRQHandler
        PUBWEAK INT_TCAP30_IRQHandler
        PUBWEAK INT_TCAP31_IRQHandler
        PUBWEAK INT_TB4_IRQHandler
        PUBWEAK INT_TCAP40_IRQHandler
        PUBWEAK INT_TCAP41_IRQHandler
        PUBWEAK INT_TB5_IRQHandler
        PUBWEAK INT_TCAP50_IRQHandler
        PUBWEAK INT_TCAP51_IRQHandler
        PUBWEAK INT_TB6_IRQHandler
        PUBWEAK INT_TCAP60_IRQHandler
        PUBWEAK INT_TCAP61_IRQHandler
        PUBWEAK INT_TB7_IRQHandler
        PUBWEAK INT_TCAP70_IRQHandler
        PUBWEAK INT_TCAP71_IRQHandler
        PUBWEAK INT_RTC_IRQHandler
        PUBWEAK INT_DMAADA_IRQHandler
        PUBWEAK INT_DMAADB_IRQHandler
        PUBWEAK INT_DMADAA_IRQHandler
        PUBWEAK INT_DMADAB_IRQHandler
        PUBWEAK INT_DMASPT0_IRQHandler
        PUBWEAK INT_DMASPR0_IRQHandler
        PUBWEAK INT_DMASPT1_IRQHandler
        PUBWEAK INT_DMASPR1_IRQHandler
        PUBWEAK INT_DMASPT2_IRQHandler
        PUBWEAK INT_DMASPR2_IRQHandler
        PUBWEAK INT_DMAUTR0_IRQHandler
        PUBWEAK INT_DMAUTT0_IRQHandler
        PUBWEAK INT_DMAUTR1_IRQHandler
        PUBWEAK INT_DMAUTT1_IRQHandler
        PUBWEAK INT_DMARX0_IRQHandler
        PUBWEAK INT_DMATX0_IRQHandler
        PUBWEAK INT_DMARX1_IRQHandler
        PUBWEAK INT_DMATX1_IRQHandler
        PUBWEAK INT_DMARX2_IRQHandler
        PUBWEAK INT_DMATX2_IRQHandler
        PUBWEAK INT_DMARX3_IRQHandler
        PUBWEAK INT_DMATX3_IRQHandler
        PUBWEAK INT_I2CI1_IRQHandler
        PUBWEAK INT_I2CI2_IRQHandler
        PUBWEAK INT_DMATB_IRQHandler
        PUBWEAK INT_DMARQ_IRQHandler
        PUBWEAK INT_DMAAERR_IRQHandler
        PUBWEAK INT_DMABERR_IRQHandler

NMI_Handler:
HardFault_Handler:
MemManage_Handler:
BusFault_Handler:
UsageFault_Handler:
SVC_Handler:
DebugMon_Handler:
PendSV_Handler:
SysTick_Handler:
Default_Handler:
INT_0_IRQHandler:
INT_1_IRQHandler:
INT_2_IRQHandler:
INT_3_IRQHandler:
INT_4_IRQHandler:
INT_5_IRQHandler:
INT_6_IRQHandler:
INT_7_IRQHandler:
INT_8_IRQHandler:
INT_9_IRQHandler:
INT_A_IRQHandler:
INT_B_IRQHandler:
INT_C_IRQHandler:
INT_USBPON_IRQHandler:
INT_E_IRQHandler:
INT_F_IRQHandler:
INT_RX0_IRQHandler:
INT_TX0_IRQHandler:
INT_RX1_IRQHandler:
INT_TX1_IRQHandler:
INT_RX2_IRQHandler:
INT_TX2_IRQHandler:
INT_RX3_IRQHandler:
INT_TX3_IRQHandler:
INT_UART0_IRQHandler:
INT_UART1_IRQHandler:
INT_SBI0_IRQHandler:
INT_SBI1_IRQHandler:
INT_SBI2_IRQHandler:
INT_SSP0_IRQHandler:
INT_SSP1_IRQHandler:
INT_SSP2_IRQHandler:
INT_USBH_IRQHandler:
INT_USBD_IRQHandler:
INT_USBWKUP_IRQHandler:
INT_CANRX_IRQHandler:
INT_CANTX_IRQHandler:
INT_CANGB_IRQHandler:
INT_ETH_IRQHandler:
INT_ETHWK_IRQHandler:
INT_ADAHP_IRQHandler:
INT_ADAM0_IRQHandler:
INT_ADAM1_IRQHandler:
INT_ADA_IRQHandler:
INT_ADBHP_IRQHandler:
INT_ADBM0_IRQHandler:
INT_ADBM1_IRQHandler:
INT_ADB_IRQHandler:
INT_EMG0_IRQHandler:
INT_PMD0_IRQHandler:
INT_ENC0_IRQHandler:
INT_EMG1_IRQHandler:
INT_PMD1_IRQHandler:
INT_ENC1_IRQHandler:
INT_MTEMG0_IRQHandler:
INT_MTPTB00_IRQHandler:
INT_MTPTB01_IRQHandler:
INT_MTCAP00_IRQHandler:
INT_MTCAP01_IRQHandler:
INT_MTEMG1_IRQHandler:
INT_MTPTB10_IRQHandler:
INT_MTPTB11_IRQHandler:
INT_MTCAP10_IRQHandler:
INT_MTCAP11_IRQHandler:
INT_MTEMG2_IRQHandler:
INT_MTPTB20_IRQHandler:
INT_MTPTB21_IRQHandler:
INT_MTCAP20_IRQHandler:
INT_MTCAP21_IRQHandler:
INT_MTEMG3_IRQHandler:
INT_MTPTB30_IRQHandler:
INT_MTPTB31_IRQHandler:
INT_MTCAP30_IRQHandler:
INT_MTCAP31_IRQHandler:
INT_RMCRX_IRQHandler:
INT_TB0_IRQHandler:
INT_TCAP00_IRQHandler:
INT_TCAP01_IRQHandler:
INT_TB1_IRQHandler:
INT_TCAP10_IRQHandler:
INT_TCAP11_IRQHandler:
INT_TB2_IRQHandler:
INT_TCAP20_IRQHandler:
INT_TCAP21_IRQHandler:
INT_TB3_IRQHandler:
INT_TCAP30_IRQHandler:
INT_TCAP31_IRQHandler:
INT_TB4_IRQHandler:
INT_TCAP40_IRQHandler:
INT_TCAP41_IRQHandler:
INT_TB5_IRQHandler:
INT_TCAP50_IRQHandler:
INT_TCAP51_IRQHandler:
INT_TB6_IRQHandler:
INT_TCAP60_IRQHandler:
INT_TCAP61_IRQHandler:
INT_TB7_IRQHandler:
INT_TCAP70_IRQHandler:
INT_TCAP71_IRQHandler:
INT_RTC_IRQHandler:
INT_DMAADA_IRQHandler:
INT_DMAADB_IRQHandler:
INT_DMADAA_IRQHandler:
INT_DMADAB_IRQHandler:
INT_DMASPT0_IRQHandler:
INT_DMASPR0_IRQHandler:
INT_DMASPT1_IRQHandler:
INT_DMASPR1_IRQHandler:
INT_DMASPT2_IRQHandler:
INT_DMASPR2_IRQHandler:
INT_DMAUTR0_IRQHandler:
INT_DMAUTT0_IRQHandler:
INT_DMAUTR1_IRQHandler:
INT_DMAUTT1_IRQHandler:
INT_DMARX0_IRQHandler:
INT_DMATX0_IRQHandler:
INT_DMARX1_IRQHandler:
INT_DMATX1_IRQHandler:
INT_DMARX2_IRQHandler:
INT_DMATX2_IRQHandler:
INT_DMARX3_IRQHandler:
INT_DMATX3_IRQHandler:
INT_I2CI1_IRQHandler:
INT_I2CI2_IRQHandler:
INT_DMATB_IRQHandler:
INT_DMARQ_IRQHandler:
INT_DMAAERR_IRQHandler:
INT_DMABERR_IRQHandler:
        B Default_Handler

        END
