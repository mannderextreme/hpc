#include <iostream>
#include <arm_bf16.h>
#include <arm_neon.h>

// ssh rene@52.41.181.2

extern "C" {
    void gemm_asm_bf16_4_2_8(
        bfloat16_t const * i_a,
        bfloat16_t const * i_b,
        float            * io_c );
}

void convert_a_to_bfmmla( uint64_t           i_m,
                          uint64_t           i_n,
                          uint64_t           i_ld,
                          bfloat16_t const * i_a_col_major,
                          bfloat16_t       * o_a_fmmla ){
                        int iter = 0
                        for(int i = 0; i < i_m; i+2){
                            for(int j = 0; j < i_n; i+4){
                                
                                o_a_fmmla[iter + 0] = i_a_col_major[(i+0)*i_m + j];
                                o_a_fmmla[iter + 1] = i_a_col_major[(i+1)*i_m + j];
                                o_a_fmmla[iter + 2] = i_a_col_major[(i+2)*i_m + j];
                                o_a_fmmla[iter + 3] = i_a_col_major[(i+3)*i_m + j];

                                o_a_fmmla[iter + 4] = i_a_col_major[(i+0)*i_m + j + 1];
                                o_a_fmmla[iter + 5] = i_a_col_major[(i+1)*i_m + j + 1];
                                o_a_fmmla[iter + 6] = i_a_col_major[(i+2)*i_m + j + 1];
                                o_a_fmmla[iter + 7] = i_a_col_major[(i+3)*i_m + j + 1];

                            }
                        }
                        
}

void convert_b_to_bfmmla( uint64_t           i_m,
                          uint64_t           i_n,
                          uint64_t           i_ld,
                          bfloat16_t const * i_b_col_major,
                          bfloat16_t       * o_b_fmmla ){
                        int iter = 0
                        for(int i = 0; i < i_n; i+2){
                            for(int j = 0; j < i_m; i+4){

                                o_b_fmmla[iter + 0] = i_b_col_major[i*i_m + j + 1];
                                o_b_fmmla[iter + 1] = i_b_col_major[i*i_m + j + 1];
                                o_b_fmmla[iter + 2] = i_b_col_major[i*i_m + j + 2];
                                o_b_fmmla[iter + 3] = i_b_col_major[i*i_m + j + 3];

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
                          uint64_t         i_ld,
                          float    const * i_c_col_major,
                          float          * o_c_fmmla ){


}

void convert_c_from_bfmmla( uint64_t         i_m,
                            uint64_t         i_n,
                            uint64_t         i_ld,
                            float    const * i_c_fmmla,
                            float          * o_c_col_major ){

}

int main (){
    // allocate memory for A,B, C

    bfloat16_t * A = new bfloat16_t[16*4];
    bfloat16_t * A_fmmla = new bfloat16_t[16*4];

    bfloat16_t * B = new bfloat16_t[4*12];
    bfloat16_t * B_fmmla = new bfloat16_t[4*12];

    float      * C = new float[16*12];
    float      * C_fmmla = new float[16*12];



}
