;/* ************************************************************************ */
;/*
; * ------------------------------------------------------------------------
; *   Application : 
; *   Micon : TMPA901CMXBG
; *   Copyright(C) TOSHIBA CORPORATION 2008 All rights reserved
; * ------------------------------------------------------------------------
; */
;
;/*! \file ioTMPA901CM_asm.h
;	\brief Header file of SFR difinition for Assembler
;
;	\author TOSHIBA CORPORATION
;
;	\date 2009/01/06 New Create
; */
;/* ************************************************************************ */

;======================
; SysCtrl(Remap)
;======================
Remap                        EQU             0xF0000004

;======================
; WDT
;======================
WdogLoad                     EQU             0xF0010000
WdogValue                    EQU             0xF0010004
WdogControl                  EQU             0xF0010008
WdogIntClr                   EQU             0xF001000C
WdogRIS                      EQU             0xF0010010
WdogMIS                      EQU             0xF0010014
;
WdogLock                     EQU             0xF0010C00

;======================
; PMC
;======================
BPARELE                      EQU             0xF0020200
BPDRELE                      EQU             0xF0020204
BRTRELE                      EQU             0xF0020208
BPXRELE                      EQU             0xF002020C
;
BPAEDGE                      EQU             0xF0020220
BPDEDGE                      EQU             0xF0020224
;
BPXEDGE                      EQU             0xF002022C
;
BADRINT                      EQU             0xF0020240
BPDRINT                      EQU             0xF0020244
BRTRINT                      EQU             0xF0020248
BPXRINT                      EQU             0xF002024C
;
PMCDRV                       EQU             0xF0020260
;
DMCCKECTL                    EQU             0xF0020280
;
PMCCTL                       EQU             0xF0020300
;
PMCWV1                       EQU             0xF0020400
;
PMCWV2                       EQU             0xF0020408
;
PMCRES                       EQU             0xF002041C
;
BSADATA                      EQU             0xF0020800
BSBDATA                      EQU             0xF0020804
BSCDATA                      EQU             0xF0020808
BSDDATA                      EQU             0xF002080C
BSEDATA                      EQU             0xF0020810
BSFDATA                      EQU             0xF0020814
BSGDATA                      EQU             0xF0020818
BSHDATA                      EQU             0xF002081C
;
BSJDATA                      EQU             0xF0020824
BSKDATA                      EQU             0xF0020828
BSLDATA                      EQU             0xF002082C
;
BSTDATA                      EQU             0xF002084C
BSUDATA                      EQU             0xF0020850
;
BPADATA                      EQU             0xF0020900
BPBDATA                      EQU             0xF0020904
BPCDATA                      EQU             0xF0020908
BPDDATA                      EQU             0xF002090C
;
BPFDATA                      EQU             0xF0020914
BPGDATA                      EQU             0xF0020918
;
BPJDATA                      EQU             0xF0020924
BPKDATA                      EQU             0xF0020928
BPLDATA                      EQU             0xF002092C
BPMDATA                      EQU             0xF0020930
BPNDATA                      EQU             0xF0020934
;
BPRDATA                      EQU             0xF0020944
;
BPTDATA                      EQU             0xF002094C
BPUDATA                      EQU             0xF0020950
BPVDATA                      EQU             0xF0020954
;
BSAOE                        EQU             0xF0020A80
BSBOE                        EQU             0xF0020A84
BSCOE                        EQU             0xF0020A88
BSDOE                        EQU             0xF0020A8C
BSEOE                        EQU             0xF0020A90
BSFOE                        EQU             0xF0020A94
BSGOE                        EQU             0xF0020A98
BSHOE                        EQU             0xF0020A9C
;
BSJOE                        EQU             0xF0020AA4
BSKOE                        EQU             0xF0020AA8
BSLOE                        EQU             0xF0020AAC
;
BSTOE                        EQU             0xF0020ACC
BSUOE                        EQU             0xF0020AD0
;
BPBOE                        EQU             0xF0020B84
BPCOE                        EQU             0xF0020B88
BPDOE                        EQU             0xF0020B8C
;
BPFOE                        EQU             0xF0020B94
BPGOE                        EQU             0xF0020B98
;
BPJOE                        EQU             0xF0020BA4
BPKOE                        EQU             0xF0020BA8
BPLOE                        EQU             0xF0020BAC
BPMOE                        EQU             0xF0020BB0
BPNOE                        EQU             0xF0020BB4
;
BPROE                        EQU             0xF0020BC4
;
BPTOE                        EQU             0xF0020BCC
BPUOE                        EQU             0xF0020BD0
BPVOE                        EQU             0xF0020BD4
;
BPAIE                        EQU             0xF0020D80
;
BPCIE                        EQU             0xF0020D88
BPDIE                        EQU             0xF0020D8C
;
BPFIE                        EQU             0xF0020D94
;
BPNIE                        EQU             0xF0020DB4
;
BPRIE                        EQU             0xF0020DC4

;======================
; RTC/MLD
;======================
RTCDATA                      EQU             0xF0030000
RTCCOMP                      EQU             0xF0030004
RTCPRST                      EQU             0xF0030008
;
MLDALMINV                    EQU             0xF0030100
MLDALMSEL                    EQU             0xF0030104
ALMCNTCR                     EQU             0xF0030108
ALMPATERN                    EQU             0xF003010C
MLDCNTCR                     EQU             0xF0030110
MLDFRQ                       EQU             0xF0030114
;
RTCALMINTCTR                 EQU             0xF0030200
RTCALMMIS                    EQU             0xF0030204
;

;======================
; Timer01/PWM
;======================
Timer0Load                   EQU             0xF0040000
Timer0Value                  EQU             0xF0040004
Timer0Control                EQU             0xF0040008
Timer0IntClr                 EQU             0xF004000C
Timer0RIS                    EQU             0xF0040010
Timer0MIS                    EQU             0xF0040014
Timer0BGLoad                 EQU             0xF0040018
Timer0Mode                   EQU             0xF004001C
;
Timer0Compare1               EQU             0xF00400A0
;
Timer0CmpIntClr1             EQU             0xF00400C0
;
Timer0CmpEn                  EQU             0xF00400E0
Timer0CmpRIS                 EQU             0xF00400E4
Timer0CmpMIS                 EQU             0xF00400E8
Timer0BGCmp                  EQU             0xF00400EC
;
Timer1Load                   EQU             0xF0040100
Timer1Value                  EQU             0xF0040104
Timer1Control                EQU             0xF0040108
Timer1IntClr                 EQU             0xF004010C
Timer1RIS                    EQU             0xF0040110
Timer1MIS                    EQU             0xF0040114
Timer1BGLoad                 EQU             0xF0040118
;

;======================
; Timer23/PWM
;======================
Timer2Load                   EQU             0xF0041000
Timer2Value                  EQU             0xF0041004
Timer2Control                EQU             0xF0041008
Timer2IntClr                 EQU             0xF004100C
Timer2RIS                    EQU             0xF0041010
Timer2MIS                    EQU             0xF0041014
Timer2BGLoad                 EQU             0xF0041018
Timer2Mode                   EQU             0xF004101C
;
Timer2Compare1               EQU             0xF00410A0
;
Timer2CmpIntClr1             EQU             0xF00410C0
Timer2CmpEn                  EQU             0xF00410E0
Timer2CmpRIS                 EQU             0xF00410E4
Timer2CmpMIS                 EQU             0xF00410E8
Timer2BGCmp                  EQU             0xF00410EC
;
Timer3Load                   EQU             0xF0041100
Timer3Value                  EQU             0xF0041104
Timer3Control                EQU             0xF0041108
Timer3IntClr                 EQU             0xF004110C
Timer3RIS                    EQU             0xF0041110
Timer3MIS                    EQU             0xF0041114
Timer3BGLoad                 EQU             0xF0041118

;======================
; Timer45
;======================
Timer4Load                   EQU             0xF0042000
Timer4Value                  EQU             0xF0042004
Timer4Control                EQU             0xF0042008
Timer4IntClr                 EQU             0xF004200C
Timer4RIS                    EQU             0xF0042010
Timer4MIS                    EQU             0xF0042014
Timer4BGLoad                 EQU             0xF0042018
;
Timer5Load                   EQU             0xF0042100
Timer5Value                  EQU             0xF0042104
Timer5Control                EQU             0xF0042108
Timer5IntClr                 EQU             0xF004210C
Timer5RIS                    EQU             0xF0042110
Timer5MIS                    EQU             0xF0042114
Timer5BGLoad                 EQU             0xF0042118

;======================
; PLLCG
;======================
SYSCR0                       EQU             0xF0050000
SYSCR1                       EQU             0xF0050004
SYSCR2                       EQU             0xF0050008
SYSCR3                       EQU             0xF005000C
SYSCR4                       EQU             0xF0050010
SYSCR5                       EQU             0xF0050014
SYSCR6                       EQU             0xF0050018
SYSCR7                       EQU             0xF005001C
SYSCR8                       EQU             0xF0050020
;
CLKCR5                       EQU             0xF0050054

;======================
; TSI
;======================
TSICR0                       EQU             0xF00601F0
TSICR1                       EQU             0xF00601F4

;======================
; I2C0
;======================
I2C0CR1                      EQU             0xF0070000
I2C0DBR                      EQU             0xF0070004
I2C0AR                       EQU             0xF0070008
I2C0CR2                      EQU             0xF007000C
I2C0SR                       EQU             I2C0CR2
I2C0PRS                      EQU             0xF0070010
I2C0IE                       EQU             0xF0070014
I2C0IR                       EQU             0xF0070018

;======================
; ADC
;======================
ADREG0L                      EQU             0xF0080000
ADREG0H                      EQU             0xF0080004
ADREG1L                      EQU             0xF0080008
ADREG1H                      EQU             0xF008000C
ADREG2L                      EQU             0xF0080010
ADREG2H                      EQU             0xF0080014
ADREG3L                      EQU             0xF0080018
ADREG3H                      EQU             0xF008001C
ADREG4L                      EQU             0xF0080020
ADREG4H                      EQU             0xF0080024
ADREG5L                      EQU             0xF0080028
ADREG5H                      EQU             0xF008002C
ADREG6L                      EQU             0xF0080030
ADREG6H                      EQU             0xF0080034
ADREG7L                      EQU             0xF0080038
ADREG7H                      EQU             0xF008003C
ADREGSPL                     EQU             0xF0080040
ADREGSPH                     EQU             0xF0080044
ADCOMREGL                    EQU             0xF0080048
ADCOMREGH                    EQU             0xF008004C
ADMOD0                       EQU             0xF0080050
ADMOD1                       EQU             0xF0080054
ADMOD2                       EQU             0xF0080058
ADMOD3                       EQU             0xF008005C
ADMOD4                       EQU             0xF0080060
;
ADCLK                        EQU             0xF0080070
ADIE                         EQU             0xF0080074
ADIS                         EQU             0xF0080078
ADIC                         EQU             0xF008007C

;======================
; OFD
;======================
CLKSCR1                      EQU             0xF0090000
CLKSCR2                      EQU             0xF0090004
CLKSCR3                      EQU             0xF0090008
;
CLKSMN                       EQU             0xF0090010
;
CLKSMX                       EQU             0xF0090020

;======================
; SDHC BRIDGE
;======================

;======================
; LCDOP
;======================
STN64CR                      EQU             0xF00B0000

;======================
; PA
;======================
GPIOADATA                    EQU             0xF08003FC
;GPIOADIR                     EQU             0xF0800400
;GPIOAFR1                     EQU             0xF0800424
;GPIOAFR2                     EQU             0xF0800428
GPIOAIS                      EQU             0xF0800804
GPIOAIBE                     EQU             0xF0800808
GPIOAIEV                     EQU             0xF080080C
GPIOAIE                      EQU             0xF0800810
GPIOARIS                     EQU             0xF0800814
GPIOAMIS                     EQU             0xF0800818
GPIOAIC                      EQU             0xF080081C
;GPIOAODE                     EQU             0xF0800C00

;======================
; PB
;======================
GPIOBDATA                    EQU             0xF08013FC
;GPIOBDIR                     EQU             0xF0801400
GPIOBFR1                     EQU             0xF0801424
GPIOBFR2                     EQU             0xF0801428
;GPIOBIS                      EQU             0xF0801804
;GPIOBIBE                     EQU             0xF0801808
;GPIOBIEV                     EQU             0xF080180C
;GPIOBIE                      EQU             0xF0801810
;GPIOBRIS                     EQU             0xF0801814
;GPIOBMIS                     EQU             0xF0801818
;GPIOBIC                      EQU             0xF080181C
GPIOBODE                     EQU             0xF0801C00

;======================
; PC
;======================
GPIOCDATA                    EQU             0xF08023FC
GPIOCDIR                     EQU             0xF0802400
GPIOCFR1                     EQU             0xF0802424
GPIOCFR2                     EQU             0xF0802428
GPIOCIS                      EQU             0xF0802804
GPIOCIBE                     EQU             0xF0802808
GPIOCIEV                     EQU             0xF080280C
GPIOCIE                      EQU             0xF0802810
GPIOCRIS                     EQU             0xF0802814
GPIOCMIS                     EQU             0xF0802818
GPIOCIC                      EQU             0xF080281C
GPIOCODE                     EQU             0xF0802C00

;======================
; PD
;======================
GPIODDATA                    EQU             0xF08033FC
;GPIODDIR                     EQU             0xF0803400
GPIODFR1                     EQU             0xF0803424
GPIODFR2                     EQU             0xF0803428
GPIODIS                      EQU             0xF0803804
GPIODIBE                     EQU             0xF0803808
GPIODIEV                     EQU             0xF080380C
GPIODIE                      EQU             0xF0803810
GPIODRIS                     EQU             0xF0803814
GPIODMIS                     EQU             0xF0803818
GPIODIC                      EQU             0xF080381C
;GPIODODE                     EQU             0xF0803C00

;======================
; PU
;======================
GPIOUDATA                    EQU             0xF08043FC
GPIOUDIR                     EQU             0xF0804400
GPIOUFR1                     EQU             0xF0804424
GPIOUFR2                     EQU             0xF0804428
;GPIOUIS                      EQU             0xF0804804
;GPIOUIBE                     EQU             0xF0804808
;GPIOUIEV                     EQU             0xF080480C
;GPIOUIE                      EQU             0xF0804810
;GPIOURIS                     EQU             0xF0804814
;GPIOUMIS                     EQU             0xF0804818
;GPIOUIC                      EQU             0xF080481C
;GPIOUODE                     EQU             0xF0804C00

;======================
; PV
;======================
GPIOVDATA                    EQU             0xF08073FC
GPIOVDIR                     EQU             0xF0807400
GPIOVFR1                     EQU             0xF0807424
GPIOVFR2                     EQU             0xF0807428
;GPIOVIS                      EQU             0xF0807804
;GPIOVIBE                     EQU             0xF0807808
;GPIOVIEV                     EQU             0xF080780C
;GPIOVIE                      EQU             0xF0807810
;GPIOVRIS                     EQU             0xF0807814
;GPIOVMIS                     EQU             0xF0807818
;GPIOVIC                      EQU             0xF080781C
;GPIOVODE                     EQU             0xF0807C00

;======================
; PN
;======================
GPIONDATA                    EQU             0xF080C3FC
GPIONDIR                     EQU             0xF080C400
GPIONFR1                     EQU             0xF080C424
GPIONFR2                     EQU             0xF080C428
GPIONIS                      EQU             0xF080C804
GPIONIBE                     EQU             0xF080C808
GPIONIEV                     EQU             0xF080C80C
GPIONIE                      EQU             0xF080C810
GPIONRIS                     EQU             0xF080C814
GPIONMIS                     EQU             0xF080C818
GPIONIC                      EQU             0xF080C81C
;GPIONODE                     EQU             0xF080CC00

;======================
; PT
;======================
GPIOTDATA                    EQU             0xF080F3FC
GPIOTDIR                     EQU             0xF080F400
GPIOTFR1                     EQU             0xF080F424
GPIOTFR2                     EQU             0xF080F428
;GPIOTIS                      EQU             0xF080F804
;GPIOTIBE                     EQU             0xF080F808
;GPIOTIEV                     EQU             0xF080F80C
;GPIOTIE                      EQU             0xF080F810
;GPIOTRIS                     EQU             0xF080F814
;GPIOTMIS                     EQU             0xF080F818
;GPIOTIC                      EQU             0xF080F81C
;GPIOTODE                     EQU             0xF080FC00

;======================
; UART0
;======================
UART0DR                      EQU             0xF2000000
UART0SR                      EQU             0xF2000004
UART0ECR                     EQU             UART0SR
;
UART0FR                      EQU             0xF2000018
;
UART0ILPR                    EQU             0xF2000020
UART0IBRD                    EQU             0xF2000024
UART0FBRD                    EQU             0xF2000028
UART0LCRH                   EQU             0xF200002C
UART0CR                      EQU             0xF2000030
UART0IFLS                    EQU             0xF2000034
UART0IMSC                    EQU             0xF2000038
UART0RIS                     EQU             0xF200003C
UART0MIS                     EQU             0xF2000040
UART0ICR                     EQU             0xF2000044
UART0DMACR                   EQU             0xF2000048

;======================
; UART1
;======================
UART1DR                      EQU             0xF2001000
UART1SR                      EQU             0xF2001004
UART1ECR                     EQU             UART1SR
;
UART1FR                      EQU             0xF2001018
;
UART1ILPR                    EQU             0xF2001020
UART1IBRD                    EQU             0xF2001024
UART1FBRD                    EQU             0xF2001028
UART1LCRH                   EQU             0xF200102C
UART1CR                      EQU             0xF2001030
UART1IFLS                    EQU             0xF2001034
UART1IMSC                    EQU             0xF2001038
UART1RIS                     EQU             0xF200103C
UART1MIS                     EQU             0xF2001040
UART1ICR                     EQU             0xF2001044

;======================
; SSP0
;======================
SSP0CR0                      EQU             0xF2002000
SSP0CR1                      EQU             0xF2002004
SSP0DR                       EQU             0xF2002008
SSP0SR                       EQU             0xF200200C
SSP0CPSR                     EQU             0xF2002010
SSP0IMSC                     EQU             0xF2002014
SSP0RIS                      EQU             0xF2002018
SSP0MIS                      EQU             0xF200201C
SSP0ICR                      EQU             0xF2002020
SSP0DMACR                    EQU             0xF2002024

;======================
; NANDC
;======================
NDFMCR0                      EQU             0xF2010000
NDFMCR1                      EQU             0xF2010004
NDFMCR2                      EQU             0xF2010008
NDFINTC                      EQU             0xF201000C
NDFDTR                       EQU             0xF2010010
NDECCRD0                     EQU             0xF2010020
NDECCRD1                     EQU             0xF2010024
NDECCRD2                     EQU             0xF2010028
;
NDRSCA0                      EQU             0xF2010030
NDRSCD0                      EQU             0xF2010034
NDRSCA1                      EQU             0xF2010038
NDRSCD1                      EQU             0xF201003C
NDRSCA2                      EQU             0xF2010040
NDRSCD2                      EQU             0xF2010044
NDRSCA3                      EQU             0xF2010048
NDRSCD3                      EQU             0xF201004C

;======================
; I2S
;======================
I2STCON                      EQU             0xF2040000
I2STSLVON                    EQU             0xF2040004
I2STFCLR                     EQU             0xF2040008
I2STMS                       EQU             0xF204000C
I2STMCON                     EQU             0xF2040010
I2STMSTP                     EQU             0xF2040014
I2STDMA1                     EQU             0xF2040018
;
I2SRCON                      EQU             0xF2040020
I2SRSLVON                    EQU             0xF2040024
I2SFRFCLR                    EQU             0xF2040028
I2SRMS                       EQU             0xF204002C
I2SRMCON                     EQU             0xF2040030
I2SRMSTP                     EQU             0xF2040034
I2SRDMA1                     EQU             0xF2040038
;
I2SCOMMON                    EQU             0xF2040044
I2STST                       EQU             0xF2040048
I2SRST                       EQU             0xF204004C
I2SINT                       EQU             0xF2040050
I2SINTMSK                    EQU             0xF2040054
;
I2STDAT                      EQU             0xF2041000
I2SRDAT                      EQU             0xF2042000

;======================
; LCDDAreg
;======================
LDACR0                       EQU             0xF2050000
LDADRSRC1                    EQU             0xF2050004
LDADRSRC0                    EQU             0xF2050008
LDAFCPSRC1                   EQU             0xF205000C
LDAEFCPSRC1                  EQU             0xF2050010
LDADVSRC1                    EQU             0xF2050014
LDACR2                       EQU             0xF2050018
LDADXDST                     EQU             0xF205001C
LDADYDST                     EQU             0xF2050020
LDASSIZE                     EQU             0xF2050024
LDADSIZE                     EQU             0xF2050028
LDAS0AD                      EQU             0xF205002C
LDADAD                       EQU             0xF2050030
LDACR1                       EQU             0xF2050034
LDADVSRC0                    EQU             0xF2050038

;======================
; INTCreg
;======================
VICIRQSTATUS                 EQU             0xF4000000
VICFIQSTATUS                 EQU             0xF4000004
VICRAWINTR                   EQU             0xF4000008
VICINTSELECT                 EQU             0xF400000C
VICINTENABLE                 EQU             0xF4000010
VICINTENCLEAR                EQU             0xF4000014
VICSOFTINT                   EQU             0xF4000018
VICSOFTINTCLEAR              EQU             0xF400001C
VICPROTECTION                EQU             0xF4000020
VICSWPRIORITYMASK            EQU             0xF4000024
;
VICVECTADDR0                 EQU             0xF4000100
VICVECTADDR1                 EQU             0xF4000104
VICVECTADDR2                 EQU             0xF4000108
VICVECTADDR3                 EQU             0xF400010C
VICVECTADDR4                 EQU             0xF4000110
VICVECTADDR5                 EQU             0xF4000114
VICVECTADDR6                 EQU             0xF4000118
;VICVECTADDR7                 EQU             0xF400011C
VICVECTADDR8                 EQU             0xF4000120
;VICVECTADDR9                 EQU             0xF4000124
VICVECTADDR10                EQU             0xF4000128
VICVECTADDR11                EQU             0xF400012C
VICVECTADDR12                EQU             0xF4000130
;VICVECTADDR13                EQU             0xF4000134
VICVECTADDR14                EQU             0xF4000138
;VICVECTADDR15                EQU             0xF400013C
VICVECTADDR16                EQU             0xF4000140
VICVECTADDR17                EQU             0xF4000144
VICVECTADDR18                EQU             0xF4000148
;VICVECTADDR19                EQU             0xF400014C
VICVECTADDR20                EQU             0xF4000150
VICVECTADDR21                EQU             0xF4000154
;VICVECTADDR22                EQU             0xF4000158
VICVECTADDR23                EQU             0xF400015C
;VICVECTADDR24                EQU             0xF4000160
;VICVECTADDR25                EQU             0xF4000164
;VICVECTADDR26                EQU             0xF4000168
VICVECTADDR27                EQU             0xF400016C
;VICVECTADDR28                EQU             0xF4000160
;VICVECTADDR29                EQU             0xF4000164
VICVECTADDR30                EQU             0xF4000168
VICVECTADDR31                EQU             0xF400016C
;
VICVECTPRIORITY0             EQU             0xF4000200
VICVECTPRIORITY1             EQU             0xF4000204
VICVECTPRIORITY2             EQU             0xF4000208
VICVECTPRIORITY3             EQU             0xF400020C
VICVECTPRIORITY4             EQU             0xF4000210
VICVECTPRIORITY5             EQU             0xF4000214
VICVECTPRIORITY6             EQU             0xF4000218
;VICVECTPRIORITY7             EQU             0xF400021C
VICVECTPRIORITY8             EQU             0xF4000220
;VICVECTPRIORITY9             EQU             0xF4000224
VICVECTPRIORITY10            EQU             0xF4000228
VICVECTPRIORITY11            EQU             0xF400022C
VICVECTPRIORITY12            EQU             0xF4000230
;VICVECTPRIORITY13            EQU             0xF4000234
VICVECTPRIORITY14            EQU             0xF4000238
;VICVECTPRIORITY15            EQU             0xF400023C
VICVECTPRIORITY16            EQU             0xF4000240
VICVECTPRIORITY17            EQU             0xF4000244
VICVECTPRIORITY18            EQU             0xF4000248
;VICVECTPRIORITY19            EQU             0xF400024C
VICVECTPRIORITY20            EQU             0xF4000250
VICVECTPRIORITY21            EQU             0xF4000254
;VICVECTPRIORITY22            EQU             0xF4000258
VICVECTPRIORITY23            EQU             0xF400025C
;VICVECTPRIORITY24            EQU             0xF4000260
;VICVECTPRIORITY25            EQU             0xF4000264
;VICVECTPRIORITY26            EQU             0xF4000268
VICVECTPRIORITY27            EQU             0xF400026C
;VICVECTPRIORITY28            EQU             0xF4000270
;VICVECTPRIORITY29            EQU             0xF4000274
VICVECTPRIORITY30            EQU             0xF4000278
VICVECTPRIORITY31            EQU             0xF400027C
;
VICADDRESS                   EQU             0xF4000F00

;======================
; DMAreg
;======================
DMACIntStatus                EQU             0xF4100000
DMACIntTCStatus              EQU             0xF4100004
DMACIntTCClear               EQU             0xF4100008
DMACIntErrorStatus           EQU             0xF410000C
DMACIntErrClr                EQU             0xF4100010
DMACRawIntTCStatus           EQU             0xF4100014
DMACRawIntErrorStatus        EQU             0xF4100018
DMACEnbldChns                EQU             0xF410001C
DMACSoftBReq                 EQU             0xF4100020
DMACSoftSReq                 EQU             0xF4100024
;
DMACConfiguration            EQU             0xF4100030
;
DMACC0SrcAddr                EQU             0xF4100100
DMACC0DestAddr               EQU             0xF4100104
DMACC0LLI                    EQU             0xF4100108
DMACC0Control                EQU             0xF410010C
DMACC0Configuration          EQU             0xF4100110
;
DMACC1SrcAddr                EQU             0xF4100120
DMACC1DestAddr               EQU             0xF4100124
DMACC1LLI                    EQU             0xF4100128
DMACC1Control                EQU             0xF410012C
DMACC1Configuration          EQU             0xF4100130
;
DMACC2SrcAddr                EQU             0xF4100140
DMACC2DestAddr               EQU             0xF4100144
DMACC2LLI                    EQU             0xF4100148
DMACC2Control                EQU             0xF410014C
DMACC2Configuration          EQU             0xF4100150
;
DMACC3SrcAddr                EQU             0xF4100160
DMACC3DestAddr               EQU             0xF4100164
DMACC3LLI                    EQU             0xF4100168
DMACC3Control                EQU             0xF410016C
DMACC3Configuration          EQU             0xF4100170
;
DMACC4SrcAddr                EQU             0xF4100180
DMACC4DestAddr               EQU             0xF4100184
DMACC4LLI                    EQU             0xF4100188
DMACC4Control                EQU             0xF410018C
DMACC4Configuration          EQU             0xF4100190
;
DMACC5SrcAddr                EQU             0xF41001A0
DMACC5DestAddr               EQU             0xF41001A4
DMACC5LLI                    EQU             0xF41001A8
DMACC5Control                EQU             0xF41001AC
DMACC5Configuration          EQU             0xF41001B0
;
DMACC6SrcAddr                EQU             0xF41001C0
DMACC6DestAddr               EQU             0xF41001C4
DMACC6LLI                    EQU             0xF41001C8
DMACC6Control                EQU             0xF41001CC
DMACC6Configuration          EQU             0xF41001D0
;
DMACC7SrcAddr                EQU             0xF41001E0
DMACC7DestAddr               EQU             0xF41001E4
DMACC7LLI                    EQU             0xF41001E8
DMACC7Control                EQU             0xF41001EC
DMACC7Configuration          EQU             0xF41001F0

;======================
; LCDCreg
;======================
LCDTiming0                   EQU             0xF4200000
LCDTiming1                   EQU             0xF4200004
LCDTiming2                   EQU             0xF4200008
LCDTiming3                   EQU             0xF420000C
LCDUPBASE                    EQU             0xF4200010
LCDLPBASE                    EQU             0xF4200014
LCDIMSC                      EQU             0xF4200018
LCDControl                   EQU             0xF420001C
LCDRIS                       EQU             0xF4200020
LCDMIS                       EQU             0xF4200024
LCDICR                       EQU             0xF4200028
LCDUPCURR                    EQU             0xF420002C
LCDLPCURR                    EQU             0xF4200030
;
LCDPalette                   EQU             0xF4200200

;======================
; MPMCreg（PL243）
;======================
dmc_memc_status_3            EQU             0xF4300000
dmc_memc_cmd_3               EQU             0xF4300004
dmc_direct_cmd_3             EQU             0xF4300008
dmc_memory_cfg_3             EQU             0xF430000C
dmc_refresh_prd_3            EQU             0xF4300010
dmc_cas_latency_3            EQU             0xF4300014
dmc_t_dqss_3                 EQU             0xF4300018
dmc_t_mrd_3                  EQU             0xF430001C
dmc_t_ras_3                  EQU             0xF4300020
dmc_t_rc_3                   EQU             0xF4300024
dmc_t_rcd_3                  EQU             0xF4300028
dmc_t_rfc_3                  EQU             0xF430002C
dmc_t_rp_3                   EQU             0xF4300030
dmc_t_rrd_3                  EQU             0xF4300034
dmc_t_wr_3                   EQU             0xF4300038
dmc_t_wtr_3                  EQU             0xF430003C
dmc_t_xp_3                   EQU             0xF4300040
dmc_t_xsr_3                  EQU             0xF4300044
dmc_t_esr_3                  EQU             0xF4300048
;
dmc_id_0_cfg_3               EQU             0xF4300100
dmc_id_1_cfg_3               EQU             0xF4300104
dmc_id_2_cfg_3               EQU             0xF4300108
dmc_id_3_cfg_3               EQU             0xF430010C
;
dmc_chip_0_cfg_3             EQU             0xF4300200
;
dmc_user_config_3            EQU             0xF4300304
;

;
smc_memif_cfg_3              EQU             0xF4301004
;
smc_direct_cmd_3             EQU             0xF4301010
smc_set_cycles_3             EQU             0xF4301014
smc_set_opmode_3             EQU             0xF4301018
;
smc_sram_cycles0_0_3         EQU             0xF4301100
smc_opmode0_0_3              EQU             0xF4301104
;
smc_sram_cycles0_1_3         EQU             0xF4301120
smc_opmode0_1_3              EQU             0xF4301124
;
smc_sram_cycles0_2_3         EQU             0xF4301140
smc_opmode0_2_3              EQU             0xF4301144
;
smc_sram_cycles0_3_3         EQU             0xF4301160
smc_opmode0_3_3              EQU             0xF4301164
;

;======================
; MPMC_reg（PL245）
;======================
dmc_memc_status_5            EQU             0xF4310000
dmc_memc_cmd_5               EQU             0xF4310004
dmc_direct_cmd_5             EQU             0xF4310008
dmc_memory_cfg_5             EQU             0xF431000C
mc_refresh_prd_5            EQU             0xF4310010
dmc_cas_latency_5            EQU             0xF4310014
dmc_t_dqss_5                 EQU             0xF4310018
dmc_t_mrd_5                  EQU             0xF431001C
dmc_t_ras_5                  EQU             0xF4310020
dmc_t_rc_5                   EQU             0xF4310024
dmc_t_rcd_5                  EQU             0xF4310028
dmc_t_rfc_5                  EQU             0xF431002C
dmc_t_rp_5                   EQU             0xF4310030
dmc_t_rrd_5                  EQU             0xF4310034
dmc_t_wr_5                   EQU             0xF4310038
dmc_t_wtr_5                  EQU             0xF431003C
dmc_t_xp_5                   EQU             0xF4310040
dmc_t_xsr_5                  EQU             0xF4310044
dmc_t_esr_5                  EQU             0xF4310048
;
dmc_id_0_cfg_5               EQU             0xF4310100
dmc_id_1_cfg_5               EQU             0xF4310104
dmc_id_2_cfg_5               EQU             0xF4310108
dmc_id_3_cfg_5               EQU             0xF431010C
dmc_id_4_cfg_5               EQU             0xF4310110
dmc_id_5_cfg_5               EQU             0xF4310114
;
dmc_chip_0_cfg_5             EQU             0xF4310200
;
dmc_user_config_5            EQU             0xF4310304

smc_memc_status_5            EQU             0xF4311000
smc_memif_cfg_5              EQU             0xF4311004
;
smc_direct_cmd_5             EQU             0xF4311010
smc_set_cycles_5             EQU             0xF4311014
smc_set_opmode_5             EQU             0xF4311018
;
smc_sram_cycles0_0_5         EQU             0xF4311100
smc_opmode0_0_5              EQU             0xF4311104
;
smc_sram_cycles0_1_5         EQU             0xF4311120
smc_opmode0_1_5              EQU             0xF4311124
;
smc_sram_cycles0_2_5         EQU             0xF4311140
smc_opmode0_2_5              EQU             0xF4311144
;
smc_sram_cycles0_3_5         EQU             0xF4311160
smc_opmode0_3_5              EQU             0xF4311164
;

;======================
; USB_reg
;======================
UDINTSTS                     EQU             0xF4400000
UDINTENB                     EQU             0xF4400004
UDMWTOUT                     EQU             0xF4400008
UDC2STSET                    EQU             0xF440000C
UDMSTSET                     EQU             0xF4400010
DMACRDREQ                    EQU             0xF4400014
DMACRDVL                     EQU             0xF4400018
UDC2RDREQ                    EQU             0xF440001C
UDC2RDVL                     EQU             0xF4400020
;
ARBTSET                      EQU             0xF440003C
UDMWSADR                     EQU             0xF4400040
UDMWEADR                     EQU             0xF4400044
UDMWCADR                     EQU             0xF4400048
UDMWAHBADR                   EQU             0xF440004C
UDMRSADR                     EQU             0xF4400050
UDMREADR                     EQU             0xF4400054
UDMRCADR                     EQU             0xF4400058
UDMRAHBADR                   EQU             0xF440005C
;
UDPWCTL                      EQU             0xF4400080
UDMSTSTS                     EQU             0xF4400084
UDTOUTCNT                    EQU             0xF4400088
;
UD2ADR                       EQU             0xF4400200
UD2FRM                       EQU             0xF4400204
UD2TMD                       EQU             0xF4400208
UD2CMD                       EQU             0xF440020C
UD2BRQ                       EQU             0xF4400210
UD2WVL                       EQU             0xF4400214
UD2WIDX                      EQU             0xF4400218
UD2WLGTH                     EQU             0xF440021C
UD2INT                       EQU             0xF4400220
UD2INTEP                     EQU             0xF4400224
UD2INTEPMSK                  EQU             0xF4400228
UD2INTRX0                    EQU             0xF440022C
UD2EP0MSZ                    EQU             0xF4400230
UD2EP0STS                    EQU             0xF4400234
UD2EP0DSZ                    EQU             0xF4400238
UD2EP0FIFO                   EQU             0xF440023C
UD2EP1MSZ                    EQU             0xF4400240
UD2EP1STS                    EQU             0xF4400244
UD2EP1DSZ                    EQU             0xF4400248
UD2EP1FIFO                   EQU             0xF440024C
UD2EP2MSZ                    EQU             0xF4400250
UD2EP2STS                    EQU             0xF4400254
UD2EP2DSZ                    EQU             0xF4400258
UD2EP2FIFO                   EQU             0xF440025C
UD2EP3MSZ                    EQU             0xF4400260
UD2EP3STS                    EQU             0xF4400264
UD2EP3DSZ                    EQU             0xF4400268
UD2EP3FIFO                   EQU             0xF440026C
;
UD2INTNAK                    EQU             0xF4400330
UD2INTNAKMSK                 EQU             0xF4400334

;======================
; USB_HOST_reg
;======================
HcRevision                   EQU             0xF4500000
HcControl                    EQU             0xF4500004
HcCommandStatus              EQU             0xF4500008
HcInterruptStatus            EQU             0xF450000C
HcInterruptEnable            EQU             0xF4500010
HcInterruptDisable           EQU             0xF4500014
HcHCCA                       EQU             0xF4500018
HcPeriodCurrentED            EQU             0xF450001C
HcControlHeadED              EQU             0xF4500020
HcControlCurrentED           EQU             0xF4500024
HcBulkHeadED                 EQU             0xF4500028
HcBulkCurrentED              EQU             0xF450002C
HcDoneHead                   EQU             0xF4500030
HcFmInterval                 EQU             0xF4500034
HcFmRemaining                EQU             0xF4500038
HcFmNumber                   EQU             0xF450003C
HcPeriodicStart              EQU             0xF4500040
HcLSThreshold                EQU             0xF4500044
HcRhDescriptorA              EQU             0xF4500048
HcRhDescriptorB              EQU             0xF450004C
HcRhStatus                   EQU             0xF4500050
HcRhPortStatus               EQU             0xF4500054
;
HCBCR0                       EQU             0xF4500080
;

			     END
