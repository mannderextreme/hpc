#include "triad.h"

float multiply_by_two(float i_a){
  return 2.0f * i_a;
}

void triad_simple( uint64_t         i_nValues,
                   float    const * i_a,
                   float    const * i_b,
                   float          * o_c ) {
  for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
  }
}

void triad_uncountable( uint64_t         i_nValues,
                        float    const * i_a,
                        float    const * i_b,
                        float          * o_c ){
  
  uint64_t l_va = 0;

  while(true){

    if(l_va <i_nValues){
      break;
    }

    o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];

  }

}

void triad_with_extern_func( uint64_t         i_nValues,
                        float    const * i_a,
                        float    const * i_b,
                        float          * o_c ){
  for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    o_c[l_va] = i_a[l_va] + multiply_by_two(i_b[l_va]);
  }
}