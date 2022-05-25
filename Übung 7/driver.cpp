#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>

extern "C" {
        void gemm_asm_sve_64_6_1(   float i_a,
                                    float i_b,
                                    float io_c);
        void gemm_asm_sve_64_6_48(  float i_a,
                                    float i_b,
                                    float io_c);
}
int main(){


    uint64_t l_n_repetitions = 5000;
    
    double l_sus_g_flops = 0; 
    std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;

    float * i_a = (float *) malloc(64*4);
    float * i_b = (float *) malloc(6*4);
    float * io_c = (float *) malloc(6*64*4);

    std::cout << "running GEMM 64_6_1 benchmarks" << std::endl << std::endl;

    for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
            gemm_asm_sve_64_6_1(   i_a,
                        i_b,
                        io_c);
    }

    l_tp1 = std::chrono::high_resolution_clock::now();
    
    
    std::chrono::duration<double> l_dur = l_tp1 - l_tp0;
    std::chrono::duration<double> l_avg_dur = l_dur/l_n_repetitions;
    l_sus_g_flops = 16;
    l_sus_g_flops *= l_n_repetitions;
    l_sus_g_flops *= 1.0E-9;
    l_sus_g_flops /= l_dur.count(); 
    
    std::cout << "Calculation time: " << l_avg_dur.count()  << std::endl;
    std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;

    free(i_a);
    free(i_b);
    free(io_c);


    uint64_t l_n_repetitions = 5000;
    
    l_sus_g_flops = 0; 
    std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;

    float * i_a  = (float *) malloc(64*48*4);
    float * i_b  = (float *) malloc(6*48*4);
    float * io_c = (float *) malloc(6*64*4);

    std::cout << "running GEMM 64_6_1 benchmarks" << std::endl << std::endl;

    for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
            gemm_asm_sve_64_6_48(   i_a,
                                    i_b,
                                    io_c);
    }

    l_tp1 = std::chrono::high_resolution_clock::now();
    
    
    std::chrono::duration<double> l_dur = l_tp1 - l_tp0;
    std::chrono::duration<double> l_avg_dur = l_dur/l_n_repetitions;
    l_sus_g_flops = 16*48;
    l_sus_g_flops *= l_n_repetitions;
    l_sus_g_flops *= 1.0E-9;
    l_sus_g_flops /= l_dur.count(); 
    
    std::cout << "Calculation time: " << l_avg_dur.count()  << std::endl;
    std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;
}