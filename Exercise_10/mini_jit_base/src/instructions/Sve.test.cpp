#include <catch.hpp>
#include "Sve.h"

TEST_CASE( "Tests lsLdrVec.", "[Sve][lsLdrVec]" ) {
  uint32_t l_ins = 0;
  l_ins = mini_jit::instructions::Sve::lsLdrVec(31,
                                                31,
                                                 511);
  
  REQUIRE(l_ins == 0x85bf5fff);
}

TEST_CASE( "Tests lsStrVec.", "[Sve][lsStrVec]" ) {
  uint32_t l_ins = 0;
  l_ins = mini_jit::instructions::Sve::lsStrVec(31,
                                                31,
                                                 511);
  REQUIRE(l_ins == 0xE5bf5fff);
}

TEST_CASE( "Tests lsLd1Rw.", "[Sve][lsLd1Rw]" ) {
  uint32_t l_ins = 0;

  // echo "ld1rw {z0.s}, p0/z, [x0]" | llvm-mc -triple=aarch64 -mattr=+sve --show-encoding
  l_ins = mini_jit::instructions::Sve::lsLd1Rw( 0,
                                                0,
                                                0,
                                                0 );
  REQUIRE( l_ins == 0x8540c000 );

  // echo "ld1rw {z0.s}, p0/z, [x1]" | llvm-mc -triple=aarch64 -mattr=+sve --show-encoding
  l_ins = mini_jit::instructions::Sve::lsLd1Rw( 23,
                                                5,
                                                18,
                                                32/4 );
  REQUIRE( l_ins == 0x8548d657 );
}

TEST_CASE( "Tests prPtrue.", "[Sve][prPtrue]" ) {
  uint32_t l_ins = 0;

  // echo "ptrue p0.b" | llvm-mc -triple=aarch64 -mattr=+sve --show-encoding
  l_ins = mini_jit::instructions::Sve::prPtrue( 0,
                                                mini_jit::instructions::Sve::sizespec_t::b );
  REQUIRE( l_ins == 0x2518e3e0 );

  // echo "ptrue p5.d" | llvm-mc -triple=aarch64 -mattr=+sve --show-encoding
  l_ins = mini_jit::instructions::Sve::prPtrue( 5,
                                                mini_jit::instructions::Sve::sizespec_t::d );
  REQUIRE( l_ins == 0x25d8e3e5 );
}

TEST_CASE( "Tests prWhilelt", "[Sve][prWhilelt]" ) {
  uint32_t l_ins = 0;

  // echo "whilelt p0.b, x0, x0" | llvm-mc -triple=aarch64 -mattr=+sve --show-encoding
  l_ins = mini_jit::instructions::Sve::prWhileLt( 0,
                                                  mini_jit::instructions::Sve::sizespec_t::b,
                                                  0,
                                                  0 );
  REQUIRE( l_ins == 0x25201400 );

  // echo "whilelt p3.s, x5, x12" | llvm-mc -triple=aarch64 -mattr=+sve --show-encoding
  l_ins = mini_jit::instructions::Sve::prWhileLt( 3,
                                                  mini_jit::instructions::Sve::sizespec_t::s,
                                                  5,
                                                  12 );
  REQUIRE( l_ins == 0x25ac14a3 );
}

TEST_CASE( "Tests dpFmlaVec", "[Sve][dpFmlaVec]" ) {
  uint32_t l_ins = 0;
  l_ins = mini_jit::instructions::Sve::dpFmlaVec( 31,
                                          7,
                                          31,
                                          31,
                                          mini_jit::instructions::Sve::sizespec_t::d);

  REQUIRE(l_ins == 0x65ff1fff);
}
