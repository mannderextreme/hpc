#include "copy.h"
#include <cstdint>
#include <cstdlib>

void copy_c ( uint32_t const * i_a, uint64_t * o_b){

    //allocate memory for seven 64bit unsigned integers
    o_b = (uint64_t*) malloc(sizeof(uint64_t)*7); 
    
    copy 
    for ( int i = 0; i<7; i++ ){

        // copy values from i_a to o_b 
        o_b[i] = i_a[i];

    }
}
