#define CATCH_CONFIG_MAIN
#include "catch.hpp"


extern "C" {
        void gemm_asm_sve_64_6_1(   float* i_a,
                                    float* i_b,
                                    float* io_c);
        void gemm_asm_sve_64_6_48(  float* i_a,
                                    float* i_b,
                                    float* io_c);
        void gemm_asm_sve_128_6_48( float * i_a,
                                    float * i_b,
                                    float * io_c);
}

TEST_CASE("Checking correctness of kernel 64_48_1"){
    
    
    float a[64] = {2.0};
    float b[6]  = {2.0};
    std::fill(std::begin(a), std::end(a), 2.0);
    std::fill(std::begin(b), std::end(b), 2.0);

    SECTION("Add to C = {0}"){

        float sum = 0;
        float c[64*6] = {0.0};
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){
            
            
            sum  += c[i];

            
        }
        REQUIRE( Approx(sum) == 64*6*4 );
    }

    SECTION("Add to C = {2.0}"){
        float sum = 0;
        float c[64*6] = {2.0};
        std::fill(std::begin(c), std::end(c), 2.0);
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){
            sum  += c[i];

            
        }
        REQUIRE( Approx(sum) == 64*6*4 + 64*6*2 );
    }
    
}

TEST_CASE("Checking correctness of kernel 64_48_1 with a = {2.2}, b = {2.0}"){
    
    
    float a[64*1] = {2.2};
    float b[1*6]  = {2.0};
    std::fill(std::begin(a), std::end(a), 2.2);
    std::fill(std::begin(b), std::end(b), 2);

    SECTION("Add to C = {0}"){
        float sum = 0;
        float c[64*6] = {0};
        std::fill(std::begin(c), std::end(c), 0);
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){

            sum  += c[i];

        }
        REQUIRE( Approx(sum) == 64*6*4.4 );
    }

    SECTION("Add to C = {2.0}"){
        float sum = 0;
        float c[64*6] = {2.0};
        std::fill(std::begin(c), std::end(c), 2.0);
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){
            

            sum  += c[i];

            
        }
        REQUIRE( Approx(sum) == 64*6*4.4 + 64*6*2 );
    }

    SECTION("Add to C = {2.2}"){
        float sum = 0;
        float c[64*6] = {2.2};
        std::fill(std::begin(c), std::end(c), 2.2);
        gemm_asm_sve_64_6_1(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){
           

            sum  += c[i];

            
        }
        REQUIRE( Approx(sum) == 64*6*4.4 + 64*6*2.2 );
    }
    
}

TEST_CASE("Checking correctness of 64_6_48 kernel a = {1.0}, b = {1/48} "){
    float a[64*48] = {1.0};
    float b[48*6]  = {2};
    std::fill(std::begin(a), std::end(a), 1.0);
    std::fill(std::begin(b), std::end(b), 2);

    SECTION("Add to C = {0}"){
        float sum = 0;
        float c[64*6] = {0};
        std::fill(std::begin(c), std::end(c), 0.0);

        gemm_asm_sve_64_6_48(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){
            
            std::cout << c[i] << std::endl;
            sum  += c[i];

            
        }
        REQUIRE( Approx(sum) == 64*6*48*2);
    }

    SECTION("Add to C = {2.2}"){
        float sum = 0;
        float c[64*6] = {2.2};
        std::fill(std::begin(c), std::end(c), 2.2);
        gemm_asm_sve_64_6_48(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){
            

           sum  += c[i];

            
        }
        REQUIRE( Approx(sum) == 64*6*48*2 + 64*6*2.2 );
    }

}
TEST_CASE("Checking correctness of 64_6_48 kernel a = {1/2}, b = {1/48}"){
    float a[64*48] = {0.5};
    float b[48*6]  = {2};
    std::fill(std::begin(a), std::end(a), 0.5);
    std::fill(std::begin(b), std::end(b), 2);
    

    SECTION("Add to C = {0}"){
        float sum = 0;
        float c[64*6] = {0};
        std::fill(std::begin(c), std::end(c), 0);
        gemm_asm_sve_64_6_48(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){
           

            sum  += c[i];

        }
        REQUIRE( Approx(sum) == 64*6*48 );
    }

    

    SECTION("Add to C = {2.2}"){
        float sum = 0;
        float c[64*6] = {2.2};
        std::fill(std::begin(c), std::end(c), 2.2);
        gemm_asm_sve_64_6_48(a, b, c); 

        for( int i = 0; i < 64*6; i++ ){
            

            sum  += c[i];

            
        }
        REQUIRE( Approx(sum) == 64*6*48 + 64*6*2.2 );
    }

}

TEST_CASE("Checking correctness of 128_6_48 kernel a = {.5}, b = {2}"){
    float a[128*48] = {0.5};
    float b[48*6]  = {2};
    std::fill(std::begin(a), std::end(a), 0.5);
    std::fill(std::begin(b), std::end(b), 2);
    

    SECTION("Add to C = {0}"){
        float sum = 0;
        float c[128*6] = {0};
        std::fill(std::begin(c), std::end(c), 0);
        gemm_asm_sve_128_6_48(a, b, c); 

        for( int i = 0; i < 128*6; i++ ){
           

            sum  += c[i];

        }
        REQUIRE( Approx(sum) == 128*6*48 );
    }

    

    SECTION("Add to C = {2.2}"){
        float sum = 0;
        float c[128*6] = {2.2};
        std::fill(std::begin(c), std::end(c), 2.2);
        gemm_asm_sve_128_6_48(a, b, c); 

        for( int i = 0; i < 128*6; i++ ){
            

            sum  += c[i];

            
        }
        REQUIRE( Approx(sum) == 128*6*48 + 128*6*2.2 );
    }

}