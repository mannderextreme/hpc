#include <iostream>
#include <arm_bf16.h>
#include <arm_neon.h>
#include "kernels/gemm_ref.h"
#include <cmath>
#include <chrono>

// ssh rene@52.41.181.2

extern "C" {
    void gemm_asm_bf16_4_2_8   (bfloat16_t const * i_a,
                                bfloat16_t const * i_b,
                                float            * io_c );
    void gemm_asm_bf16_16_12_4 (bfloat16_t const * i_a,
                                bfloat16_t const * i_b,
                                float            * io_c );
    void gemm_asm_bf16_16_12_64(bfloat16_t const * i_a,
                                bfloat16_t const * i_b,
                                float            * io_c );
    
}

void convert_a_to_bfmmla( uint64_t           i_m,
                          uint64_t           i_n,
                          //uint64_t           i_ld,
                          bfloat16_t const * i_a_col_major,
                          bfloat16_t       * o_a_fmmla ){
                        
                        int iter = 0;
                        for(uint64_t i = 0; i < i_m; i+=2){
                            for(uint64_t j = 0; j < i_n; j+=4){
                                
                                o_a_fmmla[iter + 0] = i_a_col_major[(i+0)*i_m + j    ];
                                o_a_fmmla[iter + 1] = i_a_col_major[(i+1)*i_m + j    ];
                                o_a_fmmla[iter + 2] = i_a_col_major[(i+2)*i_m + j    ];
                                o_a_fmmla[iter + 3] = i_a_col_major[(i+3)*i_m + j    ];

                                o_a_fmmla[iter + 4] = i_a_col_major[(i+0)*i_m + j + 1];
                                o_a_fmmla[iter + 5] = i_a_col_major[(i+1)*i_m + j + 1];
                                o_a_fmmla[iter + 6] = i_a_col_major[(i+2)*i_m + j + 1];
                                o_a_fmmla[iter + 7] = i_a_col_major[(i+3)*i_m + j + 1];

                            iter += 8;

                            }
                        }
                        
}

void convert_b_to_bfmmla( uint64_t           i_m,
                          uint64_t           i_n,
                          //uint64_t           i_ld,
                          bfloat16_t const * i_b_col_major,
                          bfloat16_t       * o_b_fmmla ){
                        
                        int iter = 0;
                        for(uint64_t i = 0; i < i_m; i+=4){
                            for(uint64_t j = 0; j < i_n; j+=2){

                                o_b_fmmla[iter + 0] = i_b_col_major[i*i_m     + j + 1];
                                o_b_fmmla[iter + 1] = i_b_col_major[i*i_m     + j + 1];
                                o_b_fmmla[iter + 2] = i_b_col_major[i*i_m     + j + 2];
                                o_b_fmmla[iter + 3] = i_b_col_major[i*i_m     + j + 3];

                                o_b_fmmla[iter + 4] = i_b_col_major[(i+1)*i_m + j + 0];
                                o_b_fmmla[iter + 5] = i_b_col_major[(i+1)*i_m + j + 1];
                                o_b_fmmla[iter + 6] = i_b_col_major[(i+1)*i_m + j + 2];
                                o_b_fmmla[iter + 7] = i_b_col_major[(i+1)*i_m + j + 3];


                                iter += 8;

                            }
                        }
}

void convert_c_to_bfmmla( uint64_t         i_m,
                          uint64_t         i_n,
                          //uint64_t         i_ld,
                          float    const * i_c_col_major,
                          float          * o_c_fmmla ){
                        
                        int iter = 0;
                        for(uint64_t i = 0; i < i_m; i+=2){
                            for(uint64_t j = 0; j < i_n; j+=2){
                                o_c_fmmla[iter+0] = i_c_col_major[i*i_m     + j    ];
                                o_c_fmmla[iter+1] = i_c_col_major[i*i_m     + j + 1];
                                o_c_fmmla[iter+2] = i_c_col_major[(i+1)*i_m + j    ];
                                o_c_fmmla[iter+3] = i_c_col_major[(i+1)*i_m + j + 1];

                                iter += 4;
                                
                            }
                        }


}

void convert_c_from_bfmmla( uint64_t         i_m,
                            uint64_t         i_n,
                            //uint64_t         i_ld,
                            float    const * i_c_fmmla,
                            float          * o_c_col_major ){
                        
                        int iter = 0;
                        for(uint64_t i = 0; i < i_m; i+=2){
                            for(uint64_t j = 0; j < i_n; j+=2){
                                o_c_col_major[i*i_m     + j    ] = i_c_fmmla[iter+0];
                                o_c_col_major[i*i_m     + j + 1] = i_c_fmmla[iter+1];
                                o_c_col_major[(i+1)*i_m + j    ] = i_c_fmmla[iter+2];
                                o_c_col_major[(i+1)*i_m + j + 1] = i_c_fmmla[iter+3];

                                iter += 4;
                                
                            }
                        }
}

int main (){

    //validating result for exxample kernel 
    bfloat16_t * a_ex[] = {  vcvth_bf16_f32(0.0),  vcvth_bf16_f32(1.0,  vcvth_bf16_f32(2.0),  vcvth_bf16_f32(3.0),  vcvth_bf16_f32(4.0),  vcvth_bf16_f32(5.0),  vcvth_bf16_f32(6.0),  vcvth_bf16_f32(7.0),
                             vcvth_bf16_f32(8.0),  vcvth_bf16_f32(9.0, vcvth_bf16_f32(10.0), vcvth_bf16_f32(11.0), vcvth_bf16_f32(12.0), vcvth_bf16_f32(13.0), vcvth_bf16_f32(14.0), vcvth_bf16_f32(15.0), 
                            vcvth_bf16_f32(16.0), vcvth_bf16_f32(17.0, vcvth_bf16_f32(18.0), vcvth_bf16_f32(19.0), vcvth_bf16_f32(20.0), vcvth_bf16_f32(21.0), vcvth_bf16_f32(22.0), vcvth_bf16_f32(23.0), 
                            vcvth_bf16_f32(24.0), vcvth_bf16_f32(25.0, vcvth_bf16_f32(26.0), vcvth_bf16_f32(27.0), vcvth_bf16_f32(28.0), vcvth_bf16_f32(29.0), vcvth_bf16_f32(30.0), vcvth_bf16_f32(31.0) }; 

    bfloat16_t * b_ex[] = {  vcvth_bf16_f32(0.0,   vcvth_bf16_f32(1.0)v,
 )                            vcvth_bf16_f32(2.0,  vcvth_bf16_f32(3.0),
 )                            vcvth_bf16_f32(4.0,  vcvth_bf16_f32(5.0),
 )                            vcvth_bf16_f32(6.0,  vcvth_bf16_f32(7.0),
 )                            vcvth_bf16_f32(8.0,  vcvth_bf16_f32(9.0),
 )                           vcvth_bf16_f32(10.0, vcvth_bf16_f32(11.0),
 )                           vcvth_bf16_f32(12.0, vcvth_bf16_f32(13.0), 
)                            vcvth_bf16_f32(14.0, vcvth_bf16_f32(15.0) };)
    float      * c_ex[] = { vcvth_bf16_f32(0.5), vcvth_bf16_f32(1.5), vcvth_bf16_f32(2.5), vcvth_bf16_f32(3.5),
                        vcvth_bf16_f32(4.5), vcvth_bf16_f32(5.5), vcvth_bf16_f32(6.5), vcvth_bf16_f32(7.5) };

    std::cout << "Show example of bfmmla: " << std::endl;
    std::cout << c_ex[0] << ", " << c_ex[2] << std::endl;
    std::cout << c_ex[1] << ", " << c_ex[3] << std::endl;
    std::cout << c_ex[4] << ", " << c_ex[6] << std::endl;
    std::cout << c_ex[5] << ", " << c_ex[7] << std::endl;

    delete[] a_ex;
    delete[] b_ex;
    delete[] c_ex;
    
    uint64_t l_n_repetitions = 10000000;
    double l_sus_g_flops = l_n_repetitions; 
    std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;
    double l_peak = 1.8 * 1 * 2;
    double l_percent_of_peak = 0;
    std::cout << "Run kernel test for M=16, N=12, K=4: " << std::endl;

   
    
    // allocate memory for A,B, C

    int m = 16;
    int n = 12; 
    int k = 4;

    float * A_ref = new float[m*k];
    bfloat16_t * A = new bfloat16_t[m*k];
    bfloat16_t * A_fmmla = new bfloat16_t[m*k];

    float * B_ref = new float[k*n];
    bfloat16_t * B = new bfloat16_t[k*n];
    bfloat16_t * B_fmmla = new bfloat16_t[k*n];

    float      * C_ref = new float[m*n];
    float      * C = new float[m*n];
    float      * C_fmmla = new float[m*n];

    //initialise Matrices 
    float tmp = 0;
    for(int t_i = 0; i < m*k; t_i++){
        tmp = (float) drand48();
        tmp = vcvth_bf16_f32(tmp);
        A[t_i]     = tmp; 
        A_ref[t_i] = vcvtah_f32_bf16(tmp);
        
    }

    for(int t_i = 0; i < n*k; t_i++){
        tmp = (float) drand48();
        tmp = vcvth_bf16_f32(tmp);
        B[t_i]    = tmp; 
        B_ref[t_i] = vcvtah_f32_bf16(tmp);
    }

    for(int t_i = 0; i < m*n; t_i++){
        tmp = (float) drand48();
        C[t_i]     = tmp; 
        C_ref[t_i] = tmp;
    }


    // calculate reference 
    gemm_ref(A_ref, B_ref, C_ref, m, n, k, m, n, k);
    
    // transform matrices to correct form
    convert_a_to_bfmmla(m, k, A, A_fmmla);
    convert_b_to_bfmmla(k, n, B, B_fmmla);
    convert_c_to_bfmmla(m, n, C, C_fmmla);

    // calculate result using bfloat kernel
    
    gemm_asm_bf16_16_12_4(A, B, C);
    
    float max_diff = 0;
     for( int t_i = 0; i < m*n; t_i++){
        float diff = C[i] - C_ref[i];
        diff = std::abs(diff);
        max_diff = std::max(diff, max_diff);
    } 

    std::cout << "Maximum difference to reference kernel was: " << max_diff << std::endl;

    std::cout << "Running gemm_bf16 16, 12, 4 benchmark" << std::endl;

    l_tp0 = std::chrono::high_resolution_clock::now();
    for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
            gemm_asm_bf16_16_12_4( A_fmmla,
                                    B_fmmla,
                                    C_fmmla);
    }

    l_tp1 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> l_dur = l_tp1 - l_tp0;

    l_sus_g_flops *= 16 * 12 * 4 * 2;
    l_sus_g_flops *= 1.0E-9;
    l_sus_g_flops /= l_dur.count(); 


    std::cout << "Repetitions: " << l_n_repetitions  << std::endl;
    std::cout << "Calculation time: " << l_dur.count()  << std::endl;
    std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;
    l_percent_of_peak = l_sus_g_flops/l_peak;
    std::cout << "Percent of peak: " << l_percent_of_peak << std::endl << std::endl;

    delete[] A;
    delete[] A_ref;
    delete[] A_fmmla;
    delete[] B;
    delete[] B_ref;
    delete[] B_fmmla;
    delete[] C;
    delete[] C_ref;
    delete[] A_fmmla;


    std::cout << "Run kernel test for M=16, N=12, K=4: " << std::endl;

     // allocate memory for A,B, C

    m = 16;
    n = 12; 
    k = 64;

    A_ref = new float[m*k];
    A = new bfloat16_t[m*k];
    A_fmmla = new bfloat16_t[m*k];

    B_ref = new float[k*n];
    B = new bfloat16_t[k*n];
    B_fmmla = new bfloat16_t[k*n];

    C_ref = new float[m*n];
    C = new float[m*n];
    C_fmmla = new float[m*n];

    //initialise Matrices 
    tmp = 0;
    for(int t_i = 0; i < m*k; t_i++){
        tmp = (float) drand48();
        tmp = vcvth_bf16_f32(tmp);
        A[t_i]     = tmp; 
        A_ref[t_i] = vcvtah_f32_bf16(tmp);
        
    }

    for(int t_i = 0; i < n*k; t_i++){
        tmp = (float) drand48();
        tmp = vcvth_bf16_f32(tmp);
        B[t_i]    = tmp; 
        B_ref[t_i] = vcvtah_f32_bf16(tmp);
    }

    for(int t_i = 0; i < m*n; t_i++){
        tmp = (float) drand48();
        C[t_i]     = tmp; 
        C_ref[t_i] = tmp;
    }


    // calculate reference 
    gemm_ref(A_ref, B_ref, C_ref, m, n, k, m, n, k);
    
    // transform matrices to correct form
    convert_a_to_bfmmla(m, k, A, A_fmmla);
    convert_b_to_bfmmla(k, n, B, B_fmmla);
    convert_c_to_bfmmla(m, n, C, C_fmmla);

    // calculate result using bfloat kernel
    
    gemm_asm_bf16_16_12_64(A_fmmla, B_fmmla, C_fmmla);
    convert_c_from_bfmmla(m, n, m, C_fmmla, C);
    
    float max_diff = 0;
     for( int t_i = 0; i < m*n; t_i++){
        float diff = C[i] - C_ref[i];
        diff = std::abs(diff);
        max_diff = std::max(diff, max_diff);
    } 

    std::cout << "Maximum difference to reference kernel was: " << max_diff << std::endl;

    std::cout << "Running gemm_bf16 16, 12, 64 benchmark" << std::endl;

    l_tp0 = std::chrono::high_resolution_clock::now();
    for (uint64_t l_j = 0; l_j < l_n_repetitions; l_j++){
            gemm_asm_sbf16_16_12_4( A_fmmla,
                                    B_fmmla,
                                    C_fmmla);
    }

    l_tp1 = std::chrono::high_resolution_clock::now();

    l_dur = l_tp1 - l_tp0;

    l_sus_g_flops *= 16 * 12 * 64 * 2;
    l_sus_g_flops *= 1.0E-9;
    l_sus_g_flops /= l_dur.count(); 


    std::cout << "Repetitions: " << l_n_repetitions  << std::endl;
    std::cout << "Calculation time: " << l_dur.count()  << std::endl;
    std::cout << "Sustained GFLOPS: " << l_sus_g_flops << std::endl << std::endl;
    l_percent_of_peak = l_sus_g_flops/l_peak;
    std::cout << "Percent of peak: " << l_percent_of_peak << std::endl << std::endl;

    delete[] A;
    delete[] A_ref;
    delete[] A_fmmla;
    delete[] B;
    delete[] B_ref;
    delete[] B_fmmla;
    delete[] C;
    delete[] C_ref;
    delete[] A_fmmla;


    

}
