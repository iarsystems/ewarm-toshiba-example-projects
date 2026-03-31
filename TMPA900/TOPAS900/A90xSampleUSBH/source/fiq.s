;/*****************************************************************************/
;/* IRQ.S: FIQ Handler for Toshiba TMPA910 device series                 */
;/*****************************************************************************/
        PUBLIC  FIQ_Handler
        SECTION .text:CODE:NOROOT(2)
        ARM
;//lwi below code exchanged with Japan code for FIQ_Handler
;FIQ_Handler     B       FIQ_Handler
FIQ_Handler
	SUB	lr, lr, #4
	STMFD	sp!, {lr}
	MRS	r14, SPSR
	STMFD	sp!, {r0-r7,lr}	; Store user registers
	LDR	r0, =FIQ_ADDR		; Load FIQ ADDRESS
	LDR	r0,[r0]
	BLX	r0			; Jump to ISR

	LDMFD	sp!, {r0-r7,lr}	; Restore user registers
	MSR	SPSR_cf, r14		; re-enalbe irq ,user mode
	LDMFD	sp!, {pc}^		;

;	IMPORT Interrupt_DMACIntTCStatus	;
	IMPORT int_ta3	;
	
;FIQ_ADDR DCD Interrupt_DMACIntTCStatus
FIQ_ADDR DCD int_ta3
;//lwi below code exchanged with Japan code for FIQ_Handler

                END
