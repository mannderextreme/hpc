  .type gemm_asm_bf16_16_12_4, %function
        .global gemm_asm_bf16_16_12_4
        /*
         * Perform Matrix-Matrix-Multiplication C+= A*B using bfloat_16
         * Shapes are (16 X 12) = (16 X 4) * (4 X 12)
         * @param x0 pointer to A
         * @param x1 pointer to B
         * @param x2 pointer to C
         */ 
gemm_asm_bf16_16_12_4:
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

        // load accumulator C
        
        ldr z0, [x2]
        add x2, #32
        ldr z1, [x2]
        add x2, #32
        ldr z2, [x2]
        add x2, #32
        ldr z3, [x2]
        add x2, #32
        ldr z4, [x2]
        add x2, #32
        ldr z5, [x2]
        add x2, #32

        ldr z6, [x2]
        add x2, #32
        ldr z7, [x2]
        add x2, #32
        ldr z8, [x2]
        add x2, #32
        ldr z9, [x2]
        add x2, #32
        ldr z10, [x2]
        add x2, #32
        ldr z11, [x2]
        add x2, #32

        ldr z12, [x2]
        add x2, #32
        ldr z13, [x2]
        add x2, #32
        ldr z14, [x2]
        add x2, #32
        ldr z15, [x2]
        add x2, #32
        ldr z16, [x2]
        add x2, #32
        ldr z17, [x2]
        add x2, #32

        ldr z18, [x2]
        add x2, #32
        ldr z19, [x2]
        add x2, #32
        ldr z20, [x2]
        add x2, #32
        ldr z21, [x2]
        add x2, #32
        ldr z22, [x2]
        add x2, #32
        ldr z23, [x2]
        

        // broadcast B to 6 registers
        ld1rqh z24, p0, [x1]
        add x1, #32

        ld1rqh z25, p0, [x1]
        add x1, #32

        ld1rqh z26, p0, [x1]
        add x1, #32

        ld1rqh z27, p0, [x1]
        add x1, #32

        ld1rqh z28, p0, [x1]
        add x1, #32

        ld1rqh z29, p0, [x1]
        add x1, #32

        // load first half of A
        ldr z31, [x0]
        add x0, #32

        ldr z30, [x0]
        add x0, #32

        //calculate first 8 rows of C 

        bfmmla z0, z30, z24
        bfmmla z4, z30, z25
        bfmmla z8, z30, z26
        bfmmla z12, z30, z27
        bfmmla z16, z30, z28
        bfmmla z20, z30, z29

        bfmmla z1, z31, z24
        bfmmla z5, z31, z25
        bfmmla z9, z31, z26
        bfmmla z13, z31, z27
        bfmmla z17, z31, z28
        bfmmla z21, z31, z29

        // load second half of A
        ldr z31, [x0]
        add x0, #32

        ldr z30, [x0]
        add x0, #32
        

        // calculate last 8 rows of C
        bfmmla z2, z30, z24
        bfmmla z6, z30, z25
        bfmmla z10, z30, z26
        bfmmla z14, z30, z27
        bfmmla z18, z30, z28
        bfmmla z22, z30, z29

        bfmmla z3, z31, z24
        bfmmla z7, z31, z25
        bfmmla z11, z31, z26
        bfmmla z15, z31, z27
        bfmmla z19, z31, z28
        bfmmla z23, z31, z29
       

       // store accumulator C 
        str z23, [x2]
        sub x2, #32
        str z22, [x2]
        sub x2, #32
        str z21, [x2]
        sub x2, #32
        str 20, [x2]
        sub x2, #32
        str z19, [x2]
        sub x2, #32
        str z18, [x2]
        sub x2, #32

        str z17, [x2]
        sub x2, #32
        str z16, [x2]
        sub x2, #32
        str z15, [x2]
        sub x2, #32
        str z14, [x2]
        sub x2, #32
        str z13, [x2]
        sub x2, #32
        str z12, [x2]
        sub x2, #32

        str z11, [x2]
        sub x2, #32
        str z10, [x2]
        sub x2, #32
        str z9, [x2]
        sub x2, #32
        str z8, [x2]
        sub x2, #32
        str z7, [x2]
        sub x2, #32
        str z6, [x2]
        sub x2, #32

        str z5, [x2]
        sub x2, #32
        str z4, [x2]
        sub x2, #32
        str z3, [x2]
        sub x2, #32
        str z2, [x2]
        sub x2, #32
        str z1, [x2]
        sub x2, #32
        str 0, [x2]
        
       


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