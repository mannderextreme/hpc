#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>

extern "C" {
        void gemm_asm_sve_64_6_1(   float * i_a,
                                    float * i_b,
                                    float * io_c);
        void gemm_asm_sve_64_6_48(  float * i_a,
                                    float * i_b,
                                    float * io_c);
        void gemm_asm_sve_128_6_48( float * i_a,
                                    float * i_b,
                                    float * io_c);
        void gemm_asm_sve_128_48_48( float * i_a,
                                    float * i_b,
                                    float * io_c);
        
}
int main(){


        uint64_t l_n_repetitions = 10000000;

        double l_sus_g_flops = l_n_repetitions; 
        std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;

        float * i_a = (float *) malloc(64*4);
        float * i_b = (float *) malloc(6*4);
        float * io_c = (float *) malloc(6*64*4);
        l_tp0 = std::chrono::high_resolution_clock::now();
        std::cout << "running GEMM 64_6_1 benchmarks" << std::endl;

        for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
                gemm_asm_sve_64_6_1(   i_a,
                                i_b,
                                io_c);
        }

        l_tp1 = std::chrono::high_resolution_clock::now();


        std::chrono::duration<double> l_dur = l_tp1 - l_tp0;
        
        l_sus_g_flops *= 64 * 6 * 1 * 2;
        l_sus_g_flops *= 1.0E-9;
        l_sus_g_flops /= l_dur.count(); 
        std::cout << "Repetitions: " << l_n_repetitions  << std::endl;
        std::cout << "Calculation time: " << l_dur.count()  << std::endl;
        std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;


        free(i_a);
        free(i_b);
        free(io_c);


        l_n_repetitions = l_n_repetitions;

        l_sus_g_flops = l_n_repetitions; 

        i_a  = (float *) malloc(64*48*4);
        i_b  = (float *) malloc(6*48*4);
        io_c = (float *) malloc(6*64*4);

        std::cout << "running GEMM 64_6_48 benchmarks" <<  std::endl;
        l_tp0 = std::chrono::high_resolution_clock::now();
        for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
                gemm_asm_sve_64_6_48(   i_a,
                                        i_b,
                                        io_c);
        }

        l_tp1 = std::chrono::high_resolution_clock::now();

        l_dur = l_tp1 - l_tp0;

        l_sus_g_flops *= 64 * 6 * 48 * 2;
        l_sus_g_flops *= 1.0E-9;
        l_sus_g_flops /= l_dur.count(); 
        std::cout << "Repetitions: " << l_n_repetitions  << std::endl;
        std::cout << "Calculation time: " << l_dur.count()  << std::endl;
        std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;

        
        free(i_a);
        free(i_b);
        free(io_c);

        l_n_repetitions = l_n_repetitions;

        l_sus_g_flops = l_n_repetitions; 

        i_a  = (float *) malloc(128*48*4);
        i_b  = (float *) malloc(6*48*4);
        io_c = (float *) malloc(6*128*4);

        std::cout << "running GEMM 128_6_48 benchmarks" << std::endl;
        l_tp0 = std::chrono::high_resolution_clock::now();
        for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
                gemm_asm_sve_128_6_48(   i_a,
                                        i_b,
                                        io_c);
        }

        l_tp1 = std::chrono::high_resolution_clock::now();

        l_dur = l_tp1 - l_tp0;

        l_sus_g_flops *= 128 * 6 * 48 * 2;
        l_sus_g_flops *= 1.0E-9;
        l_sus_g_flops /= l_dur.count(); 
        std::cout << "Repetitions: " << l_n_repetitions  << std::endl;
        std::cout << "Calculation time: " << l_dur.count()  << std::endl;
        std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;

        
        free(i_a);
        free(i_b);
        free(io_c);
/*
        l_n_repetitions = l_n_repetitions;

        l_sus_g_flops = l_n_repetitions; 

        i_a  = (float *) malloc(128*48*4);
        i_b  = (float *) malloc(6*48*4);
        io_c = (float *) malloc(6*128*4);

        std::cout << "running GEMM 128_6_48 benchmarks" << std::endl << std::endl;
        l_tp0 = std::chrono::high_resolution_clock::now();
        for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
                gemm_asm_sve_128_48_48(   i_a,
                                        i_b,
                                        io_c);
        }

        l_tp1 = std::chrono::high_resolution_clock::now();

        l_dur = l_tp1 - l_tp0;

        l_sus_g_flops *= 128 * 6 * 48 * 2;
        l_sus_g_flops *= 1.0E-9;
        l_sus_g_flops /= l_dur.count(); 
        std::cout << "Repetitions: " << l_n_repetitions  << std::endl;
        std::cout << "Calculation time: " << l_dur.count()  << std::endl;
        std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;

        
        free(i_a);
        free(i_b);
        free(io_c);*/
 }