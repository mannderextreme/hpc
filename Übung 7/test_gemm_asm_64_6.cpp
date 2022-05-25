#include "catch.hpp"


extern "C" {
        void gemm_asm_sve_64_6_1(   float* i_a,
                                    float* i_b,
                                    float* io_c);
        void gemm_asm_sve_64_6_48(  float* i_a,
                                    float* i_b,
                                    float* io_c);
}

TEST_CASE("Checking correctness of kernel 64_48_1"){
    
    
    float a[64][1] = {2.0};
    float b[1][6]  = {2.0};

    SECTION("Add to C = {0}"){

        float c[64][6] = {0.0};
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 6; j++ ){

            REQUIRE( c[i][j] == 4 );

            }
        }

    }

    SECTION("Add to C = {2.0}"){
        float c[64][6] = {2.0};
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 6; j++ ){

            REQUIRE( c[i][j] == 6 );

            }
        }
    }
    
}

TEST_CASE("Checking correctness of kernel 64_48_1 with a = {2.2}, b = {2.0}"){
    
    
    float a[64][1] = {2.2};
    float b[1][6]  = {2.0};

    SECTION("Add to C = {0}"){

        int c[64][6] = {0};
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 6; j++ ){

            REQUIRE( c[i][j] == 4.4 );

            }
        }

    }

    SECTION("Add to C = {2.0}"){
        float c[64][6] = {2.0};
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 6; j++ ){

            REQUIRE( c[i][j] == 6.4 );

            }
        }
    }

    SECTION("Add to C = {2.2}"){
        float c[64][6] = {2.2};
        gemm_asm_sve_64_6_1(*, b, c); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 6; j++ ){

            REQUIRE( c[i][j] == 6.6 );

            }
        }
    }
    
}

TEST_CASE("Checking correctness of 64_6_48 kernel a = {1.0}, b = {1/48} "){
    float a[64][48] = {1.0};
    float b[48][6]  = {1/48};

    SECTION("Add to C = {0}"){

        float c[64][6] = {0};
        gemm_asm_sve_64_6_48(*(*(a)), *(*(b)), *(*(c))); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 6; ++ ){

            REQUIRE( c[i][j] == 1 );

            }
        }

    }

    SECTION("Add to C = {2.2}"){
        float c[64][6] = {2.2};
        gemm_asm_sve_64_6_48(*(*(a)), *(*(b)), *(*(c))); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 6; j++ ){

            REQUIRE( c[i][j] == 3 );

            }
        }
    }

}
TEST_CASE("Checking correctness of 64_6_64 kernel a = {1/2}, b = {1/48}"){
    float *(*(a))[64][48] = {1/2};
    float b[48][6]  = {1/48};

    SECTION("Add to C = {0}"){

        float c[64][6] = {0};
        gemm_asm_sve_64_6_48(*(*(a)), *(*(b)), *(*(c))); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 64; j++ ){

            REQUIRE( c[i][j] == 0.5 );

            }
        }

    }

    SECTION("Add to C = {2.2}"){
        float c[64][6] = {2.2};
        gemm_asm_sve_64_6_48(*(*(a)), *(*(b)), *(*(c))); 

        for( int i = 0; i < 64; i++ ){
            for( int j = 0; j < 64; j++ ){

            REQUIRE( c[i][j] == 2.5 );

            }
        }
    }

}
