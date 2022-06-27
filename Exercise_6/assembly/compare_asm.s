        .text
        .align 4
        .type   compare_asm, %function
        .global compare_asm

        /*
        * Takes two 32 bit int input values and compares
         */
compare_asm:
        
        // load input values
        ldr w2, [x0]
        ldr w3, [x1]

        // compare instruction
        cmp w0, w1
        
        // using alias subs:
        //subs wzr, w0, w1
        

        //using maschine code
        
        
        mrs x0, nzcv


        ret
        .size compare_asm, (. - compare_asm)