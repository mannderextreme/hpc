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
        
        //constant factor (2)
        fmov z0.s, #2
        //loop counter
        mov x4, #0
        //set predicate 
        whilelt p0.s, x4, x0

        b.none end_loop
        
loop:
        //load into vector registers from a and b
        ld1w z1.s, p0/z, [x1, x4, lsl #2] 
        ld1w z2.s, p0/z, [x2, x4, lsl #2]
        //calculate fma a += 2 * b
        fmla z1.s, p0/m, z0.s, z2.s 
        //store result in c
        st1w z1.s, p0, [x3, x4, lsl #2]

        //increment loop counter
        /*
        * incw x4
        * cmp x4, x0
        * bne loop
        */

        //increase loop counter by vector length
        incw x4
        //prepare for next loop
        whilelt p0.s, x4, x0
        b.any loop

end_loop:





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