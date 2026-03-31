;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Part one of the system initialization code,
;; contains low-level
;; initialization.
;;
;; Copyright 2007 IAR Systems. All rights reserved.
;;
;; $Revision: 1388 $
;;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION IRQ_STACK:DATA:NOROOT(3)
        SECTION FIQ_STACK:DATA:NOROOT(3)
        SECTION CSTACK:DATA:NOROOT(3)

;
; The module in this file are included in the libraries, and may be
; replaced by any user-defined modules that define the PUBLIC symbol
; __iar_program_start or a user defined start symbol.
;
; To override the cstartup defined in the library, simply add your
; modified version to the workbench project.

        SECTION .intvec:CODE:NOROOT(2)

        PUBLIC  __vector
        PUBLIC  __iar_program_start
        EXTERN  Undefined_Handler
        EXTERN  SWI_Handler
        EXTERN  Prefetch_Handler
        EXTERN  Abort_Handler
        EXTERN  IRQ_Handler
        EXTERN  FIQ_Handler

        DATA

__iar_init$$done:               ; The vector table is not needed
                                ; until after copy initialization is done

__vector:                       ; Make this a DATA label, so that stack usage
                                ; analysis doesn't consider it an uncalled fun

        ARM

        ; All default exception handlers (except reset) are
        ; defined as weak symbol definitions.
        ; If a handler is defined by the application it will take precedence.
        LDR     PC,Reset_Addr           ; Reset
        LDR     PC,Undefined_Addr       ; Undefined instructions
        LDR     PC,SWI_Addr             ; Software interrupt (SWI/SVC)
        LDR     PC,Prefetch_Addr        ; Prefetch abort
        LDR     PC,Abort_Addr           ; Data abort
        DCD     0                       ; RESERVED
        LDR     PC,IRQ_Addr             ; IRQ
        LDR     PC,FIQ_Addr             ; FIQ

        DATA

Reset_Addr:     DCD   __iar_program_start
Undefined_Addr: DCD   Undefined_Handler
SWI_Addr:       DCD   SWI_Handler
Prefetch_Addr:  DCD   Prefetch_Handler
Abort_Addr:     DCD   Abort_Handler
IRQ_Addr:       DCD   IRQ_Handler
FIQ_Addr:       DCD   FIQ_Handler


; --------------------------------------------------
; ?cstartup -- low-level system initialization code.
;
; After a reset execution starts here, the mode is ARM, supervisor
; with interrupts disabled.
;



        SECTION .text:CODE:NOROOT(2)

        EXTERN  __cmain
        REQUIRE __vector
        EXTWEAK __iar_init_core
        EXTWEAK __iar_init_vfp


        ARM

__iar_program_start:
?cstartup:

;
; Add initialization needed before setup of stackpointers here.
;

;
; Initialize the stack pointers.
; The pattern below can be used for any of the exception stacks:
; FIQ, IRQ, SVC, ABT, UND, SYS.
; The USR mode uses the same stack as SYS.
; The stack segments must be defined in the linker command file,
; and be declared above.
;


; --------------------
; Mode, correspords to bits 0-5 in CPSR

#define MODE_MSK 0x1F            ; Bit mask for mode bits in CPSR

#define USR_MODE 0x10            ; User mode
#define FIQ_MODE 0x11            ; Fast Interrupt Request mode
#define IRQ_MODE 0x12            ; Interrupt Request mode
#define SVC_MODE 0x13            ; Supervisor mode
#define ABT_MODE 0x17            ; Abort mode
#define UND_MODE 0x1B            ; Undefined Instruction mode
#define SYS_MODE 0x1F            ; System mode

/* if you set orignal MPU setting, disable this #if block, -> #if 0 */
#if 1

Region_16K      EQU     B'01101         ; MPU Region Size 16KB
Region_256K     EQU     B'10001         ; MPU Region Size 256KB
Region_1M       EQU     B'10011         ; MPU Region Size 1MB
Region_32M      EQU     B'11000         ; MPU Region Size 32MB
Region_Enable   EQU     B'1             ; '1' means memory region enabled. A memory region must be enabled before it is used.


        ; Region 0 - ATCM
        MOV     R1, #0x0
        MCR     p15, 0, R1, c6, c2, 0       ; Set memory region number register
        LDR     R2, =0x00000000
        MCR     p15, 0, R2, c6, c1, 0       ; Set region base address register
        LDR     R2, =0x0 | (Region_1M << 1) | Region_Enable
        MCR     p15, 0, R2, c6, c1, 2       ; Set region size & enable register
        LDR     R2, =0x0000060C             ; Execute, AP = 110(Privileged/User read-only), {TEX,C,B} = 00100(Normal(Outer and Inner Non-cacheable), Shared
        MCR     p15, 0, R2, c6, c1, 4       ; Set region access control register

        ; Region 1 - BTCM
        ADD     R1, R1, #0x1
        MCR     p15, 0, R1, c6, c2, 0       ; Set memory region number register
        LDR     R2, =0x10000000
        MCR     p15, 0, R2, c6, c1, 0       ; Set region base address register
        LDR     R2, =0x0 | (Region_256K << 1) | Region_Enable
        MCR     p15, 0, R2, c6, c1, 2       ; Set region size & enable register
        LDR     R2, =0x0000030C             ; Execute, AP = 011(Full access), {TEX,C,B} = 00100(Normal(Outer and Inner Non-cacheable), Shared
        MCR     p15, 0, R2, c6, c1, 4       ; Set region access control register

        ; Region 2 - SRAM
        ADD     R1, R1, #0x1
        MCR     p15, 0, R1, c6, c2, 0       ; Set memory region number register
        LDR     R2, =0x20000000
        MCR     p15, 0, R2, c6, c1, 0       ; Set region base address register
        LDR     R2, =0x0 | (Region_16K << 1) | Region_Enable
        MCR     p15, 0, R2, c6, c1, 2       ; Set region size & enable register
        LDR     R2, =0x00001301             ; No Execute, AP = 011(Full access),  {TEX,C,B} = 00001(Shareable Device)
        MCR     p15, 0, R2, c6, c1, 4       ; Set region access control register

        ; Region 3 - Peripheral
        ADD     R1, R1, #0x1
        MCR     p15, 0, R1, c6, c2, 0       ; Set memory region number register
        LDR     R2, =0x40000000
        MCR     p15, 0, R2, c6, c1, 0       ; Set region base address register
        LDR     R2, =0x0 | (Region_32M << 1) | Region_Enable
        MCR     p15, 0, R2, c6, c1, 2       ; Set region size & enable register
        LDR     R2, =0x00001301             ; No Execute, AP = 011(Full access),  {TEX,C,B} = 00001(Shareable Device)
        MCR     p15, 0, R2, c6, c1, 4       ; Set region access control register

        ; Region 4 - Flash Write
        ADD     R1, R1, #0x1
        MCR     p15, 0, R1, c6, c2, 0       ; Set memory region number register
        LDR     R2, =0x42000000
        MCR     p15, 0, R2, c6, c1, 0       ; Set region base address register
        LDR     R2, =0x0 | (Region_1M << 1) | Region_Enable
        MCR     p15, 0, R2, c6, c1, 2       ; Set region size & enable register
        LDR     R2, =0x00001301             ; No Execute, AP = 011(Full access),  {TEX,C,B} = 00001(Shareable Device)
        MCR     p15, 0, R2, c6, c1, 4       ; Set region access control register

        ; Set MPU enable
        MRC     p15, 0, R0, c1, c0, 0       ; Read CP15 Control Register
        ORR     R0, R0, #0x01               ; Set M bit to enable MPU
        DSB                                 ; Ensure all previous loads/stores have completed
        MCR     p15, 0, R0, c1, c0, 0       ; Write CP15 Control Register
        ISB                                 ; Ensure subsequent insts execute wrt new MPU settings

#endif 

        MRS     r0, cpsr                ; Original PSR value

        ;; Set up the interrupt stack pointer.

        BIC     r0, r0, #MODE_MSK       ; Clear the mode bits
        ORR     r0, r0, #IRQ_MODE       ; Set IRQ mode bits
        MSR     cpsr_c, r0              ; Change the mode
        LDR     sp, =SFE(IRQ_STACK)     ; End of IRQ_STACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned

        ;; Set up the fast interrupt stack pointer.

        BIC     r0, r0, #MODE_MSK       ; Clear the mode bits
        ORR     r0, r0, #FIQ_MODE       ; Set FIR mode bits
        MSR     cpsr_c, r0              ; Change the mode
        LDR     sp, =SFE(FIQ_STACK)     ; End of FIQ_STACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned

        ;; Set up the normal stack pointer.

        BIC     r0 ,r0, #MODE_MSK       ; Clear the mode bits
        ORR     r0 ,r0, #SYS_MODE       ; Set System mode bits
        MSR     cpsr_c, r0              ; Change the mode
        LDR     sp, =SFE(CSTACK)        ; End of CSTACK
        BIC     sp,sp,#0x7              ; Make sure SP is 8 aligned

        ;; Turn on core features assumed to be enabled.
          FUNCALL __iar_program_start, __iar_init_core
        BL      __iar_init_core

        ;; Initialize VFP (if needed).
          FUNCALL __iar_program_start, __iar_init_vfp
        BL      __iar_init_vfp

;;;
;;; Add more initialization here
;;;

;;; Continue to __cmain for C-level initialization.

          FUNCALL __iar_program_start, __cmain
        B       __cmain

        END
