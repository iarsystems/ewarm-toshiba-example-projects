/*
** Copyright (C) ARM Limited, 2001. All rights reserved.
*/
#include <rt_misc.h>
extern unsigned int top_of_heap;

__value_in_regs struct __initial_stackheap __user_initial_stackheap(
        unsigned R0, unsigned SP, unsigned R2, unsigned SL)
{
    struct __initial_stackheap config;
    
    config.heap_base = (unsigned int)&top_of_heap;    /* defined in heap.s */
                                                      /* placed by scatterfile */
    config.stack_base = SP;                           /* inherit SP from the execution environment */

    return config;
}

/*
Below is an equivalent example assembler version of __user_initial_stackheap.

It will be entered with the value of the stackpointer in r1 (as set in init.s), 
this does not need to be changed and so can be passed unmodified out of the 
function. 

    IMPORT bottom_of_heap
    EXPORT __user_initial_stackheap

__user_initial_stackheap    
    LDR   r0,=bottom_of_heap
    MOV   pc,lr
*/    
