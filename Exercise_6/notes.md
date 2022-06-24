# 6.1 

# 6.2

## 2. GDB 

###  register content inital breakpoint (load_asm)


x0             0x3b391ec0       993599168
x1             0x3e8    1000
x2             0x3e8    1000
x3             0x3b391f00       993599232
x4             0x3b391eb0       993599152
x5             0x400004254a00   70368813730304
x6             0x0      0
x7             0x4000   16384
x8             0x80     128
x9             0x7      7
x10            0x0      0
x11            0x0      0
x12            0x0      0
x13            0x0      0
x14            0x2      2
x15            0x0      0

### register content after first instruction (ldr)

x0             0x3b391ec8       993599176
x1             0x190    400
x2             0x3e8    1000
x3             0x3b391f00       993599232
x4             0x3b391eb0       993599152
x5             0x400004254a00   70368813730304
x6             0x0      0
x7             0x4000   16384
x8             0x80     128
x9             0x7      7
x10            0x0      0
x11            0x0      0
x12            0x0      0
x13            0x0      0
x14            0x2      2
x15            0x0      0

### register content after second instruction (ldp)

x0             0x3b391ec8       993599176
x1             0x190    400
x2             0x190    400
x3             0x1f4    500
x4             0x3b391eb0       993599152
x5             0x400004254a00   70368813730304
x6             0x0      0
x7             0x4000   16384
x8             0x80     128
x9             0x7      7
x10            0x0      0
x11            0x0      0
x12            0x0      0
x13            0x0      0
x14            0x2      2
x15            0x0      0

### register content after third instruction (ldp)

x0             0x3b391ec8       993599176
x1             0x190    400
x2             0x190    400
x3             0x1f4    500
x4             0x258    600
x5             0x2bc    700
x6             0x0      0
x7             0x4000   16384
x8             0x80     128
x9             0x7      7
x10            0x0      0
x11            0x0      0
x12            0x0      0
x13            0x0      0
x14            0x2      2
x15            0x0      0

## 1. legal
RANKS: <0>

HEAP SUMMARY:
  in use at exit: 0 bytes in 0 blocks

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts (suppressed 0)

<strong>Code loads from memory to registers. 4* 64 bit values are loaded from pointer (x0 + 1  : x0 +4), one value is loaded twice </strong>

## 3. not legal 1

RANKS: <0>

Invalid read of size 8
  at main (in driver_load.cpp:18)
Address is 24 bytes after a block of size 80 in arena "client"


RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:7)
Address is 24 bytes after a block of size 80 in arena "client"


RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:8)
Address is 24 bytes before an unallocated block of size 4,121,296 in arena "client"


RANKS: <0>

HEAP SUMMARY:
  in use at exit: 0 bytes in 0 blocks

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 3 errors from 5 contexts (suppressed 0)


<strong>10* 64 bit are allocated, pointer + 12 goes out of allocated memory. each of the load instructions has invalid read</strong>


## 3. not legal 2
RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:7)
Address is 0 bytes after a block of size 80 alloc'd
  at operator new[](unsigned long) (in vg_replace_malloc.c:429)
  by main (in driver_load.cpp:9)


RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:8)
Address is 8 bytes after a block of size 80 alloc'd
  at operator new[](unsigned long) (in vg_replace_malloc.c:429)
  by main (in driver_load.cpp:9)


RANKS: <0>

HEAP SUMMARY:
  in use at exit: 0 bytes in 0 blocks

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 2 errors from 3 contexts (suppressed 0)

<strong>Same reasoning as above but first load instruction (ldr) is executed. The two others (ldp) fail though</strong>

## 3. not legal 3
RANKS: <0>

Invalid read of size 8
  at load_asm (in load_asm.s:8)
Address is 0 bytes after a block of size 80 alloc'd
  at operator new[](unsigned long) (in vg_replace_malloc.c:429)
  by main (in driver_load.cpp:9)


RANKS: <0>

HEAP SUMMARY:
  in use at exit: 0 bytes in 0 blocks

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 1 errors from 1 contexts (suppressed 0)

<strong>Same reasoning as above but two load instruction (ldr/ldp) are executed. The other one (ldp) fails though</strong>