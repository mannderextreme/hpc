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

        bfmmla z0.s, z30.h, z24.h
        bfmmla z4.s, z30.h, z25.h
        bfmmla z8.s, z30.h, z26.h
        bfmmla z12.s, z30.h, z27.h
        bfmmla z16.s, z30.h, z28.h
        bfmmla z20.s, z30.h, z29.h

        bfmmla z1.s, z31.h, z24.h
        bfmmla z5.s, z31.h, z25.h
        bfmmla z9.s, z31.h, z26.h
        bfmmla z13.s, z31.h, z27.h
        bfmmla z17.s, z31.h, z28.h
        bfmmla z21.s, z31.h, z29.h

        // load second half of A
        ldr z31, [x0]
        add x0, #32

        ldr z30, [x0]
        add x0, #32
        

        // calculate last 8 rows of C
        bfmmla z2.s, z30.h, z24.h
        bfmmla z6.s, z30.h, z25.h
        bfmmla z10.s, z30.h, z26.h
        bfmmla z14.s, z30.h, z27.h
        bfmmla z18s.s, z30.h, z28.h
        bfmmla z22.s, z30, z29.h

        bfmmla z3.s, z31.h, z24.h
        bfmmla z7.s, z31.h, z25.h
        bfmmla z11.s, z31.h, z26.h
        bfmmla z15.s, z31.h, z27.h
        bfmmla z19.s, z31.h, z28.h
        bfmmla z23.s, z31.h, z29.h
       

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