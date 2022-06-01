       .text
        .type triad_low, %function
        .global triad_low
        /*
         * Performs triad operation 
         *
         * @param x0 number of elements in vectors a, b, c.
         * @param x1 pointer to a.
         * @param x2 pointer to b.
         * @param x3 pointer to c.
         */ 
triad_low:
        // set predicate register to true
        ptrue p0.b

        // store
        stp x19, x20, [sp, #-16]!
        stp x21, x22, [sp, #-16]!
        stp x23, x24, [sp, #-16]!
        stp x25, x26, [sp, #-16]!
        stp x27, x28, [sp, #-16]!
        stp x29, x30, [sp, #-16]!

        stp  d8,  d9, [sp, #-16]!
        stp d10, d11, [sp, #-16]!
        stp d12, d13, [sp, #-16]!
        stp d14, d15, [sp, #-16]!

        // triad operation:

        mov x4, x0

loop:   
        
        whilelt 

        
        cbnz x4, loop




        // restore
        ldp d14, d15, [sp], #16
        ldp d12, d13, [sp], #16
        ldp d10, d11, [sp], #16
        ldp  d8,  d9, [sp], #16

        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size triad_low, (. - triad_low)