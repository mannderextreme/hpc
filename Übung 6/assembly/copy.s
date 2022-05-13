        .text
        .type copy_asm, %function
        .global copy_asm
        /*
         * function that copys a 32-byte 
         * unsigned int array into a 64-
         *  byte unsigned int array.
         *
         * @param x0 pointer to i_a.
         * @param x1 pointer to o_b.
         */ 
copy_asm:
        // store
        stp x19, x20, [sp, #-16]!
        stp x21, x22, [sp, #-16]!
        stp x23, x24, [sp, #-16]!
        stp x25, x26, [sp, #-16]!
        stp x27, x28, [sp, #-16]!
        stp x29, x30, [sp, #-16]!

        //loading values as w gives 32 bit view
        ldp w2, w3,   [x0,  #0]
        ldp w4, w5,   [x0,  #8]
        ldp w6, w7,   [x0, #16]
        ldr w8        [x0, #24]
        
        //storing whole 64 bit registers, offsets change
        str x8,       [x1, #48]
        stp x6, x7,   [x1, #32]
        stp x4, x5,   [x1, #16]
        stp x2, x3,   [x1,  #0]

        // restore
        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size gemm_asm_gp, (. - gemm_asm_gp)