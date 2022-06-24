   .text
        .type eor3_sve2, %function
        .global eor3_sve2
        /*
         * Performs bitwise eor of vectors a, b, c and saves them in c
         */ 
eor3_sve2:
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

        // load vectors a, b, c 
        ld1w z0.s, p1/z, [x0]
        ld1w z1.s, p1/z, [x1]
        ld1w z2.s, p0/z, [x2]

        // bitwise xor
        eor3 z2, z1, z0

        //store result in c
        st1w z2.s, p0, [x2]


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
        .size eor3_sve2, (. - eor3_sve2)
        