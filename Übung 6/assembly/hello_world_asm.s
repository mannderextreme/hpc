         .section .rodata          // read only data section
my_msg: .asciz   "Hello World!\n" // null-terminated string

        .text                     // text section
        .global main

        /*
         * Prints "Hello World!\n" and returns 0.
         */
main:   stp     x29, x30, [sp, #-16]!

        // print "Hello World!\n" by calling printf
        adr     x0, my_msg
        bl      printf

        // return 0

        mov     w0, #0


        ldp     x29, x30, [sp], #16
        ret

        // size of main section
        .size   main, (. - main)
