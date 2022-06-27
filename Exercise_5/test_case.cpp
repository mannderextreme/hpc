#include <catch2/catch_test_macros.hpp>
#include "kernels/gemm_ref.h"
#include "kernels/gemm_compiler_32_32_32_32_32_32.h"


int ab_ref[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9}
int c_ref[3][3]  = {30, 36, 42, 66, 81, 96, 102, 126, 150}

TEST_CASE("Testing all matrix kernels with int:"){
    int ab_ref[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9}
    int c_ref[3][3]  = {30, 36, 42, 66, 81, 96, 102, 126, 150}
    int c[3][3]  = {0}
    SECTION( "Reference kernel working as expected." ){

        gemm_ref(ab_ref, ab_ref, c)

        REQUIRE( c[0][0] == c_ref[0][0]);
        REQUIRE( c[0][1] == c_ref[0][1]);
        REQUIRE( c[0][2] == c_ref[0][2]);
        REQUIRE( c[1][0] == c_ref[1][0]);
        REQUIRE( c[1][1] == c_ref[1][1]);
        REQUIRE( c[1][2] == c_ref[1][2]);
        REQUIRE( c[2][0] == c_ref[2][0]);
        REQUIRE( c[2][1] == c_ref[2][1]);
        REQUIRE( c[2][2] == c_ref[2][2]);
    }
    SECTION("mnk kernel with fixed size is working as expected."){

        gemm_32_32_32_32_32_32_mnk(ab_ref, ab_ref, c)

        REQUIRE( c[0][0] == c_ref[0][0]);
        REQUIRE( c[0][1] == c_ref[0][1]);
        REQUIRE( c[0][2] == c_ref[0][2]);
        REQUIRE( c[1][0] == c_ref[1][0]);
        REQUIRE( c[1][1] == c_ref[1][1]);
        REQUIRE( c[1][2] == c_ref[1][2]);
        REQUIRE( c[2][0] == c_ref[2][0]);
        REQUIRE( c[2][1] == c_ref[2][1]);
        REQUIRE( c[2][2] == c_ref[2][2]);
    }
    SECTION("nkm kernel with fixed size is working as expected."){

        gemm_32_32_32_32_32_32_nkm(&ab_ref, &ab_ref, &c)
    
        REQUIRE( c[0][0] == c_ref[0][0]);
        REQUIRE( c[0][1] == c_ref[0][1]);
        REQUIRE( c[0][2] == c_ref[0][2]);
        REQUIRE( c[1][0] == c_ref[1][0]);
        REQUIRE( c[1][1] == c_ref[1][1]);
        REQUIRE( c[1][2] == c_ref[1][2]);
        REQUIRE( c[2][0] == c_ref[2][0]);
        REQUIRE( c[2][1] == c_ref[2][1]);
        REQUIRE( c[2][2] == c_ref[2][2]);
    }
}





TEST_CASE("Testing all matrix kernels with float:"){
    float c[3][3]  = {0}
    float ab_float_ref[3][3] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9}
    float c_float_ref[3][3]        = {0.3, .36, 0.42, 0.66, 0.81, 0.96, 0.102, 0.126, 1.50}
    SECTION("reference kernel with fixed size is working as expected."){

        gemm_ref(ab_ref, ab_ref, c)

        REQUIRE( c[0][0] == c_float_ref[0][0]);
        REQUIRE( c[0][1] == c_float_ref[0][1]);
        REQUIRE( c[0][2] == c_float_ref[0][2]);
        REQUIRE( c[1][0] == c_float_ref[1][0]);
        REQUIRE( c[1][1] == c_float_ref[1][1]);
        REQUIRE( c[1][2] == c_float_ref[1][2]);
        REQUIRE( c[2][0] == c_float_ref[2][0]);
        REQUIRE( c[2][1] == c_float_ref[2][1]);
        REQUIRE( c[2][2] == c_float_ref[2][2]);
    }
    SECTION("mnk kernel with fixed size is working as expected."){

        gemm_32_32_32_32_32_32_mnk(ab_ref, ab_ref, c)

        REQUIRE( c[0][0] == c_float_ref[0][0]);
        REQUIRE( c[0][1] == c_float_ref[0][1]);
        REQUIRE( c[0][2] == c_float_ref[0][2]);
        REQUIRE( c[1][0] == c_float_ref[1][0]);
        REQUIRE( c[1][1] == c_float_ref[1][1]);
        REQUIRE( c[1][2] == c_float_ref[1][2]);
        REQUIRE( c[2][0] == c_float_ref[2][0]);
        REQUIRE( c[2][1] == c_float_ref[2][1]);
        REQUIRE( c[2][2] == c_float_ref[2][2]);
    }
    SECTION("nkm kernel with fixed size is working as expected."){

        gemm_32_32_32_32_32_32_nkm(ab_ref, ab_ref, c)

        REQUIRE( c[0][0] == c_float_ref[0][0]);
        REQUIRE( c[0][1] == c_float_ref[0][1]);
        REQUIRE( c[0][2] == c_float_ref[0][2]);
        REQUIRE( c[1][0] == c_float_ref[1][0]);
        REQUIRE( c[1][1] == c_float_ref[1][1]);
        REQUIRE( c[1][2] == c_float_ref[1][2]);
        REQUIRE( c[2][0] == c_float_ref[2][0]);
        REQUIRE( c[2][1] == c_float_ref[2][1]);
        REQUIRE( c[2][2] == c_float_ref[2][2]);
    }
}

