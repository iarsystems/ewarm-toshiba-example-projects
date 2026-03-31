;----------------------------------------------------------------------
; $RCSfile: init.s,v $
; $Revision: 41 $
; $Date: 2014-01-27 15:05:18 +0100 (mån, 27 jan 2014) $
; $Name:  $
; $Author: danielru $
;----------------------------------------------------------------------
;
;
;----------------------------------------------------------------------
; Description :
;----------------------------------------------------------------------

	GET	ioTMPA900CM_asm.h

; --- Standard definitions of mode bits and interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F ; available on ARM Arch 4 and later

I_Bit           EQU     0x80 ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40 ; when F bit is set, FIQ is disabled


; --- Amount of memory (in bytes) allocated for stacks

Len_FIQ_Stack    EQU     0x0800
Len_IRQ_Stack    EQU     0x0800
Len_ABT_Stack    EQU     0x0000
Len_UND_Stack    EQU     0x0000
Len_SVC_Stack    EQU     0x0800
Len_SYS_Stack    EQU     0x0800

; Add lengths >0 for FIQ_Stack, ABT_Stack, UND_Stack if you need them.
; Offsets will be loaded as immediate values.
; Offsets must be 8 byte aligned.

Offset_FIQ_Stack         EQU     0
Offset_IRQ_Stack         EQU     Offset_FIQ_Stack + Len_FIQ_Stack
Offset_ABT_Stack         EQU     Offset_IRQ_Stack + Len_IRQ_Stack
Offset_UND_Stack         EQU     Offset_ABT_Stack + Len_ABT_Stack
Offset_SVC_Stack         EQU     Offset_UND_Stack + Len_UND_Stack
Offset_SYS_Stack         EQU     Offset_SVC_Stack + Len_SVC_Stack
Offset_USR_Stack         EQU     Offset_SYS_Stack




;************** Init routine ***************************************
	AREA Init,CODE,READONLY

		EXPORT  Reset_Handler

Reset_Handler

; --- Initialize stack pointer registers

; Enter each mode in turn and set up the stack pointer

		IMPORT  top_of_stacks       				; defined in stack.s and located by scatter file
		LDR     r0, =top_of_stacks

		;  Enter FIQ Mode and set its Stack Pointer
		;lwi MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit ; No interrupts
		;lwi SUB     sp, r0, #Offset_FIQ_Stack
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #Offset_FIQ_Stack

		;  Enter IRQ Mode and set its Stack Pointer
		;lwi MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit ; No interrupts
		;lwi SUB     sp, r0, #Offset_IRQ_Stack
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #Offset_IRQ_Stack

		;  Enter ABT Mode and set its Stack Pointer
		;lwi MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit ; No interrupts
		;lwi SUB     sp, r0, #Offset_ABT_Stack
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #Offset_ABT_Stack

		;  Enter UND Mode and set its Stack Pointer
		;lwi MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit ; No interrupts
		;lwi SUB     sp, r0, #Offset_UND_Stack
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #Offset_UND_Stack


		;  Enter SVC Mode and set its Stack Pointer
		;lwi MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit ; No interrupts
		;lwi SUB     sp, r0, #Offset_SVC_Stack
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #Offset_SVC_Stack


		;  Enter SYS Mode and set its Stack Pointer
		;lwi MSR     CPSR_c, #Mode_SYS					; accept interrupt
		;lwi SUB     sp, r0, #Offset_SYS_Stack			; same as USER stack
                MSR     CPSR_c, #Mode_USR
                MOV     SP, R0
                SUB     R0, SP, #Offset_SYS_Stack






;		MSR     CPSR_c, #Mode_USR					; accept interrupt
;		SUB     sp, r0, #Offset_USR_Stack
; --- Initialize critical IO devices

		IMPORT	set_mpmc
		LDR	r0, =set_mpmc
		BLX	r0

		IMPORT	__main
		B       __main   ; note use B not BL, because an application will never return this way

		END
