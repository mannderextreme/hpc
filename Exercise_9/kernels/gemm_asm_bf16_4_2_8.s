  .type gemm_asm_bf16_4_2_8, %function
        .global gemm_asm_bf16_4_2_8
        /*
         * Perform Matrix-Matrix-Multiplication C+= A*B using bfloat_16
         * Shapes are (4 X 2) = (4 X 8) * (8 X 2)
         * @param x0 pointer to A
         * @param x1 pointer to B
         * @param x2 pointer to C
         */ 
gemm_asm_bf16_4_2_8:
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


        // load matrices A, B, C 
        ldr z0, [x0]
        ldr z1, [x1]
        ldr z2, [x2]


        //calculate bfloat fma
        bfmmla z2.s, z0.h, z1.h    

        // store result 
        str z2, [x2]   
       
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
        .size gemm_asm_bf16_16_12_4, (. - gemm_asm_bf16_16_12_4)