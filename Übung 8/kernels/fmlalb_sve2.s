 .text
        .type fmlalb_sve2, %function
        .global fmlalb_sve2
        /*
         * Performs product of two half precicion vectors a, b and adds them
         * to the bottom of single precision vector c
         */ 
fmlalb_sve2:
        // set predicate register to hp and sp
        ptrue p0.s 
        ptrue p1.h 

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

        // load vectors a, b, c with predicates for hp (a,b) and sp (c)
        ld1w z0.h, p0/z, [x0]
        ld1w z1.h, p0/z, [x1]
        ld1w z2.s, p0/z, [x2]

        //calculate fma bottom
        fmlalb z2.s, z1.h, z2.h
        

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
        .size fmlalb_sve2, (. - fmlalb_sve2)