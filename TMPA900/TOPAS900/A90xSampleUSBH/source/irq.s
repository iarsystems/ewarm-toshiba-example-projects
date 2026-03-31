;/*****************************************************************************/
;/* IRQ.S: IRQ Handler for Toshiba TMPA910 device series                 */
;/*****************************************************************************/
        PUBLIC  IRQ_Handler
        SECTION .text:CODE:NOROOT(2)
        ARM
;//lwi below code exchanged with Japan code for IRQ_Handler
;IRQ_Handler     STMDB   SP!,{R0,PC}               ; Store R0, PC (PC is dummy)
;                LDR     R0, =0xF4000F00           ; Address of VICADDRESS
;                LDR     R0,[R0, #0]               ; IRQ Address from VICADDRESS
;                STR     R0,[SP, #4]               ; Put address of IRQ on stack
;                LDMIA   SP!,{R0,PC}               ; Jump to IRQ and restore R0
VICADDRESS                   EQU             0xF4000F00
IRQ_Handler
	SUB	lr, lr, #4				;
	STMFD	sp!, {lr}			;
	MRS	r14, SPSR				;
	STMFD	sp!, {r0-r12, lr}	; Store user registers
	LDR	r0, =VICADDRESS		; Load VICADDRESS
	LDR	r0,[r0]
	BLX	r0						; Jump to ISR

	LDR	r0, =VICADDRESS		; Load VICADDRESS
	MOV r1,#0x00000000
	STR r1,[r0]
	LDMFD	sp!, {r0-r12, lr}	; Restore user registers
	MSR	SPSR_cf, r14			;
	LDMFD	sp!, {pc}^			; re-enalbe irq ,user mode
;//lwi below code exchanged with Japan code for IRQ_Handler

                END
