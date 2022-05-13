#include <cstdint>
#include <iostream>
#include <bitset>


extern "C"{
    void hello_world_asm();
    uint64_t compare_asm(   uint32_t i_a,
                            uint32_t i_b);
}

int main(   int    i_argc,
            char * i_argv[]){


    uint32_t l_a    = 10;
    uint32_t l_b    = 15;
    uint64_t l_nzcv = compare_asm(l_a, l_b);

    std::cout   << "compare_asm("
                << l_a << ", "
                << l_b << ") #1: "
                << std::bitset < 64 > (l_nzcv)
                << std::endl;

    l_a    = 10;
    l_b    = 10;
    l_nzcv = compare_asm(l_a, l_b);

    std::cout   << "compare_asm("
                << l_a << ", "
                << l_b << ") #2: "
                << std::bitset < 64 > (l_nzcv)
                << std::endl;

    return EXIT_SUCCESS;
}