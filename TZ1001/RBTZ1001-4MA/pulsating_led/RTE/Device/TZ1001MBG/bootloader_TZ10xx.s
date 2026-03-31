; A simple boot loader for TZ10xx

; COPYRIGHT (C) 2014
; TOSHIBA CORPORATION SEMICONDUCTOR & STORAGE PRODUCTS COMPANY
; ALL RIGHTS RESERVED
;
; THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
; CORPORATION MAKES NO OTHER WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR,
; STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
; SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
; 
; THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA CORPORATION
; RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
; REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
; THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
; 
; TOSHIBA CORPORATION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
; CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
; ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
; PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
; DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
; WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
; PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
; WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.

                MODULE  ?cstartup

                ; initial vector table @ 0x0000_0000
                SECTION CSTACK:DATA:NOROOT(3)
                SECTION .startup:CODE:ROOT(2)
                SECTION .startup_init:CODE:ROOT(2)
                
                SECTION .intvec:CODE:ROOT(2)
                
                PUBLIC __vector_table

                DATA
__vector_table
                DCD     0x20000400                ; Top of Stack
#ifdef TZ10XX_BOOT_FLASH
                DCD     BootLoader                ; Reset Handler
#else
                DCD     InfiniteLoop              ; Reset Handler
#endif ;; TZ10XX_BOOT_FLASH
                DCD     InfiniteLoop              ; NMI Handler
                DCD     InfiniteLoop              ; Hard Fault Handler
            
          

                ; copy .startup section from flash to sram
#ifdef  TZ10XX_BOOT_FLASH
                CODE
                
BootLoader
                LDR     r0, =sfb(.startup_init)
                LDR     r1, =sfb(.startup)
                LDR     r2, =sizeof(.startup)

InitialCopyLoop
                LDM     r0!, {r3-r6}
                STM     r1!, {r3-r6}
                SUBS    r2, r2, #0x10
                BHI     InitialCopyLoop
                
                ; switch vector table to RAM @ 0x1000_0000
                ; *VTOR = 0x1000_0000
                LDR     r0, =0x10000000
                LDR     r1, =0xe000ed08 ; VTOR
                STR     r0, [r1, #0]
                ; MSP = *(uint32_t *)(0x1000_0000)
                LDR     sp, [r0, #0]
                ; PC = *(uint32_t *)(0x1000_0004)
                LDR     r0, [r0, #4]
                BX      r0
#endif  ;; TZ10XX_BOOT_FLASH

InfiniteLoop
                B       .

                END
