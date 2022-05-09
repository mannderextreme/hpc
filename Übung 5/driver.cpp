#include "kernels/gemm_ref.h"
#include "kernels/gemm_compiler_32_32_32_32_32_32.h"
#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>

int main(){

    uint64_t l_n_repetitions = 5000;
    uint64_t l_matrix_size[8] = {4, 8, 12, 16, 24, 32, 48, 64};
    double l_sus_g_flops = 0; 
    std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;
    
    
    /*
        benchmarking reference kernel
    */
    

    for (uint64_t l_i = 0; l_i < 8; l_i++){ 
        std::cout << "running reference GEMM benchmarks" << std::endl << std::endl;
        
        uint64_t l_iterator = l_matrix_size[l_i];
        
        /*
            initializing matrizes
        */
        float * i_a = (float *) malloc(16*l_iterator*l_iterator);
        float * i_b = (float *) malloc(16*l_iterator*l_iterator);
        float * io_c = (float *) malloc(16*l_iterator*l_iterator);
        uint64_t i_m = l_iterator;
        uint64_t i_n = l_iterator;
        uint64_t i_k = l_iterator;
        uint64_t i_lda = l_iterator;
        uint64_t i_ldb = l_iterator;
        uint64_t i_ldc = l_iterator;

        for ( uint64_t i = 0; i < l_iterator; i++){
            for ( uint64_t j = 0; j < l_iterator; j++){
                i_a[i * i_lda + j]  = 0.1;
                i_b[i * i_ldb + j]  = 0.1;
                io_c[i * i_ldc + j] = 0.0;
            }
        }

        /*
            repeating calls to reference kernel
        */
        l_tp0 = std::chrono::high_resolution_clock::now();

        for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
            gemm_ref(   i_a,
                        i_b,
                        io_c,
                        i_m,
                        i_n,
                        i_k,
                        i_lda,
                        i_ldb,
                        i_ldc );
        }

        l_tp1 = std::chrono::high_resolution_clock::now();
        
        
        std::chrono::duration<double> l_dur = l_tp1 - l_tp0;
        std::chrono::duration<double> l_avg_dur = l_dur/l_n_repetitions;
        l_sus_g_flops = 2*i_m*i_n*i_k;
        l_sus_g_flops *= l_n_repetitions;
        l_sus_g_flops *= 1.0E-9;
        l_sus_g_flops /= l_dur.count(); 
        std::cout << "Matrix Size: " << l_iterator << std::endl;
        std::cout << "Avg. calc time: "<< l_avg_dur.count()  << std::endl;
        std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;

        free(i_a);
        free(i_b);
        free(io_c);

    }
    
    
    std::cout << std::endl << "benchmarking fixed matrix size kernels" << std::endl;
    
    uint64_t l_lambda = 32;
    
    float * i_a = (float *) malloc(l_lambda*l_lambda);
    float * i_b = (float *) malloc(l_lambda*l_lambda);
    float * io_c = (float *) malloc(l_lambda*l_lambda);
    float * io_c_mnk = (float *) malloc(l_lambda*l_lambda);
    float * io_c_nkm = (float *) malloc(l_lambda*l_lambda);
    

    for ( uint64_t i = 0; i < l_lambda; i++){
        for ( uint64_t j = 0; j < l_lambda; j++){
            i_a[i * l_lambda + j]  = 0.1;
            i_b[i * l_lambda + j]  = 0.1;
            io_c[i * l_lambda + j] = 0.0;
            io_c_mnk[i * l_lambda + j] = 0.0;
            io_c_nkm[i * l_lambda + j] = 0.0;
        }
    }
    std::cout << "Calculating reference kernel: "  << std::endl;
    l_tp0 = std::chrono::high_resolution_clock::now();
    for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
        gemm_ref( i_a, i_b, io_c, l_lambda, l_lambda, l_lambda, l_lambda, l_lambda, l_lambda);
    }
    
    l_sus_g_flops = 2*l_lambda*l_lambda*l_lambda;
    l_sus_g_flops *= l_n_repetitions;
    l_sus_g_flops *= 1.0E-9;

    l_tp1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> l_dur = l_tp1 - l_tp0;
    std::chrono::duration<double> l_avg_dur = l_dur/l_n_repetitions;

    l_sus_g_flops /= l_dur.count();
    std::cout << "dur: "<< l_dur.count()  << std::endl;
    std::cout << "Avg. calc time: "<< l_avg_dur.count()  << std::endl;
    std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;

    
    std::cout << "Calculating fixed mnk kernel: "  << std::endl;
     l_tp0 = std::chrono::high_resolution_clock::now();
    for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
       gemm_compiler_32_32_32_32_32_32_mnk(i_a, i_b, io_c_mnk);
    }
    l_sus_g_flops = 2*l_lambda*l_lambda*l_lambda;
    l_sus_g_flops *= l_n_repetitions;
    l_sus_g_flops *= 1.0E-9;
    l_sus_g_flops /= l_dur.count(); 
    l_tp1 = std::chrono::high_resolution_clock::now();
    l_dur = l_tp1 - l_tp0;
    l_avg_dur = l_dur/l_n_repetitions;
    std::cout << "dur: "<< l_dur.count()  << std::endl;
    std::cout << "Avg. calc time: "<< l_avg_dur.count()  << std::endl;
    std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;


    std::cout << "Calculating fixed nkm kernel: "  << std::endl;
     l_tp0 = std::chrono::high_resolution_clock::now();
    for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
         gemm_compiler_32_32_32_32_32_32_nkm(i_a, i_b, io_c_nkm);
    }
    l_sus_g_flops = 2*l_lambda*l_lambda*l_lambda;
    l_sus_g_flops *= l_n_repetitions;
    l_sus_g_flops *= 1.0E-9;
    l_sus_g_flops /= l_dur.count(); 
    l_tp1 = std::chrono::high_resolution_clock::now();
    l_dur = l_tp1 - l_tp0;
    l_avg_dur = l_dur/l_n_repetitions;
    std::cout << "dur: "<< l_dur.count()  << std::endl;
    std::cout << "Avg. calc time: "<< l_avg_dur.count()  << std::endl;
    std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;
     


       
}

