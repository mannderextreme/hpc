#include <catch2/catch_test_macros.hpp>


extern "C"{
    void gemm_asm_gp( uint32_t const * i_a,
                      uint32_t const * i_b,
                      uint32_t       * io_c );
}

TEST_CASE("Checking correctness of kernel"){
    
    int c_ref [4][2] = {7, 10, 15, 22, 23, 34, 31, 46}
    int c[4][2]      = {0}
    int a[4][2]      = {1, 2, 3, 4, 5, 6, 7, 8}
    int b[2][2]      = {1, 2, 3, 4}


    gemm_asm_gp(a, b, c);


    REQUIRE( c[0][0] == c_ref[0][0]);
    REQUIRE( c[1][0] == c_ref[1][0]);
    REQUIRE( c[2][0] == c_ref[2][0]);
    REQUIRE( c[3][0] == c_ref[3][0]);

    REQUIRE( c[0][1] == c_ref[0][1]);
    REQUIRE( c[1][1] == c_ref[1][1]);
    REQUIRE( c[2][1] == c_ref[2][1]);
    REQUIRE( c[3][1] == c_ref[3][1]);
    
}

TEST_CASE("Checking trivial cases"){
    
    int c[4][2]     = {0}
    int a[4][2]     = {1, 2, 3, 4, 5, 6, 7, 8}

    SECTION("Multiply by unit matrix"){
        
        int c_ref[4][2] = {1, 2, 3, 4, 5, 6, 7, 8}
        int b[2][2] = {1, 0, 0, 1}
        
        
        gemm_asm_gp(a, b, c);

        REQUIRE( c[0][0] == c_ref[0][0]);
        REQUIRE( c[1][0] == c_ref[1][0]);
        REQUIRE( c[2][0] == c_ref[2][0]);
        REQUIRE( c[3][0] == c_ref[3][0]);

        REQUIRE( c[0][1] == c_ref[0][1]);
        REQUIRE( c[1][1] == c_ref[1][1]);
        REQUIRE( c[2][1] == c_ref[2][1]);
        REQUIRE( c[3][1] == c_ref[3][1]);

    }

    SECTION("Multiply by zero matrix"){

        int c_ref[4][2] = {0}
        int b[2][2]     = {1, 0, 0, 1}
        
        
        gemm_asm_gp(a, b, c);

        REQUIRE( c[0][0] == c_ref[0][0]);
        REQUIRE( c[1][0] == c_ref[1][0]);
        REQUIRE( c[2][0] == c_ref[2][0]);
        REQUIRE( c[3][0] == c_ref[3][0]);

        REQUIRE( c[0][1] == c_ref[0][1]);
        REQUIRE( c[1][1] == c_ref[1][1]);
        REQUIRE( c[2][1] == c_ref[2][1]);
        REQUIRE( c[3][1] == c_ref[3][1]);
    }
}