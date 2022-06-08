#include "kernels/triad_high.h"
#include <cmath>
#include <cstdint>
#include <chrono>
#include <omp.h>
#include <iostream>



extern "C"{
    void triad_low( uint64_t         i_nValues,
                    float    const * i_a,
                    float    const * i_b,
                    float          * o_c );
}

int main(){
    int i_nValues; 

    std::cout << "Enter vector length: " << std::endl;
    std::cin >> i_nValues;
    //allocate memory 
    float * v_a = new float[i_nValues];
    float * v_b = new float[i_nValues];
    float * v_c = new float[i_nValues];
    float * v_cref = new float[i_nValues];

    // initialise vectors
    for(int i = 0; i < i_nValues; i++){
        v_a[i] = (float) drand48();
        v_b[i] = (float) drand48();
        v_c[i] = 0;
        v_cref[i] = 0;
    } 

    //calculate reference
    triad_high(i_nValues, v_a, v_b, v_cref);
    

    //calculate result with low level function
    triad_low(i_nValues, v_a, v_b, v_c);

    //compare results
    float max_diff = 0;
    for(int i = 0; i < i_nValues; i++){
        float diff = v_c[i] - v_cref[i];
        diff = std::abs(diff);
        max_diff = std::max(diff, max_diff);
        // std::cout << v_c[i] << "   " << v_cref[i] << std::endl;
    }

    std::cout << max_diff << std::endl;

    delete[] v_a;
    delete[] v_b;
    delete[] v_c;
    delete[] v_cref;

}

