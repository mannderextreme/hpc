.text
        .type gemm_asm_gp, %function
        .global gemm_asm_gp
        /*
         * Performs the matrix-multiplication C+=A*B
         * with the shapes (4x2) = (4x2) * (2x2).
         * The input-data is of type uint32_t.
         *
         * @param x0 pointer to A.
         * @param x1 pointer to B.
         * @param x2 pointer to C.
         */ 
gemm_asm_gp:
        // store
        stp x19, x20, [sp, #-16]!
        stp x21, x22, [sp, #-16]!
        stp x23, x24, [sp, #-16]!
        stp x25, x26, [sp, #-16]!
        stp x27, x28, [sp, #-16]!
        stp x29, x30, [sp, #-16]!


        //load matrix C

        ldp w3, w4  [x2, #8]!
        ldp x5, w6  [x2, #8]!
        ldp w7, w8  [x2, #8]!
        ldp w9, w10 [x2, #8]!


        // load first column of A

        ldp w11, w12 [x0, #8]!
        ldp w13, w14 [x0, #8]!


        //load first value of B

        ldr w15      [x1, #0]


        //MADD first row of a with first value of b

        MADD w3, w11, w15, w3
        MADD w4, w12, w15, w4
        MADD w5, w13, w15, w5
        MADD w6, w14, w15, w6


        //load second value of B

        ldr w15      [w1, #4]


        //MADD first row of a with second value of b

        MADD w3, w11, w15, w3
        MADD w4, w12, w15, w4
        MADD w5, w13, w15, w5
        MADD w6, w14, w15, w6


        // load second column of A

        ldp w11, w12 [w0, #8]!
        ldp w13, w14 [w0, #8]!

        
        //load third value of B

        ldr w15      [w1, #8]


        //MADD second row of a with third value of b

        MADD  w7, w11, w15, w7
        MADD  w8, w12, w15, w8
        MADD  w9, w13, w15, w9
        MADD w10, w14, w15, w10


        //load fourth value of B

        ldr w15      [w1, #12]


        //MADD second row of a with fourth valua of b

        MADD  w7, w11, w15, w7
        MADD  w8, w12, w15, w8
        MADD  w9, w13, w15, w9
        MADD w10, w14, w15, w10


        //write back C 
        stp w9, w10 [w2, #-8]!
        stp w7, w8  [w2, #-8]!
        stp w5, w6  [w2, #-8]!
        stp w3, w4  [w2, #-8]!



        // restore
        ldp x29, x30, [sp], #16
        ldp x27, x28, [sp], #16
        ldp x25, x26, [sp], #16
        ldp x23, x24, [sp], #16
        ldp x21, x22, [sp], #16
        ldp x19, x20, [sp], #16

        ret
        .size gemm_asm_gp, (. - gemm_asm_gp)