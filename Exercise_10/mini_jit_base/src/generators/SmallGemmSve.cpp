#include "SmallGemmSve.h"
#include "../instructions/Base.h"
#include "../instructions/Sve.h"

/*
* For M multiples of 64 are allowed
* For N multiples of 6 are allowed
* K is arbitrary
*/

void ( *mini_jit::generators::SmallGemmSve::generate( uint32_t i_m,
                                                      uint32_t i_n,
                                                      uint32_t i_k ) )( float const * i_a,
                                                                        float const * i_b,
                                                                        float       * io_c ) {
  uint32_t l_ins = 0;

  // store according to procedure call standard
  m_kernel.addInstruction( 0xA9BF53F3 );
  m_kernel.addInstruction( 0xA9BF5BF5 );
  m_kernel.addInstruction( 0xA9BF63F7 );
  m_kernel.addInstruction( 0xA9BF6BF9 );
  m_kernel.addInstruction( 0xA9BF73FB );
  m_kernel.addInstruction( 0xA9BF7BFD );

  m_kernel.addInstruction( 0x6DBF27E8 );
  m_kernel.addInstruction( 0x6DBF2FEA );
  m_kernel.addInstruction( 0x6DBF37EC );
  m_kernel.addInstruction( 0x6DBF3FEE );

  // initialise loop counters for three dimension M, N, K
  m_kernel.addInstruction(instructions::Base::dpMovImm( 3, uint16_t(i_m/64), 0 ));
  m_kernel.addInstruction(instructions::Base::dpMovImm( 4, uint16_t(i_n/6),  0 ));
  m_kernel.addInstruction(instructions::Base::dpMovImm( 5, uint16_t(i_k),    0 ));
  
  // set predicate register 
  m_kernel.addInstruction(instructions::Sve::prPtrue(0, mini_jit::instructions::Sve::sizespec_t::s));
  
  // load accumulator block C
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(0, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(1, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(2, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(3, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(4, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(5, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(6, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(7, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(8, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(9, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(10, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(11, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(12, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(13, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(04, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(15, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(16, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(17, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(18, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(19, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(20, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(21, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(22, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(23, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Base::dpSubImm(2, 2, 24*16*4 , 0));
  
 

  // reset offset 
  m_kernel.resetOffset();

  // decrease loop-counter
  l_ins = instructions::Base::dpSubImm( 1,
                                        1,
                                        1,
                                        0 );
  m_kernel.addInstruction( l_ins );

  // load 6 values of B, broadcastet
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLd1Rw(24, 0, 1, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(1, 1, i_k*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLd1Rw(25, 0, 1, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(1, 1, i_k*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLd1Rw(26, 0, 1, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(1, 1, i_k*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLd1Rw(27, 0, 1, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(1, 1, i_k*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLd1Rw(28, 0, 1, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(1, 1, i_k*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLd1Rw(29, 0, 1, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(1, 1, i_k*4, 0));

  // load 2*16 values of A
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(30, 0, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(0, 0, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(31, 0, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(0, 0, 16*4, 0));
  
  // calculate fmas
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(0, 0, 30, 24, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(4, 0, 30, 25, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(8, 0, 30, 26, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(12, 0, 30, 27, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(16, 0, 30, 28, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(20, 0, 30, 29, instructions::Sve::sizespec_t::s));

  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(1, 0, 31, 24, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(5, 0, 31, 25, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(9, 0, 31, 26, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(13, 0, 31, 27, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(17, 0, 31, 28, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(21, 0, 31, 29, instructions::Sve::sizespec_t::s));

  // load 2*16 values of A
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(30, 0, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(0, 0, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsLdrVec(31, 0, 0));
  
  
  // calculate fmas
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(2, 0, 30, 24, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(6, 0, 30, 25, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(10, 0, 30, 26, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(14, 0, 30, 27, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(18, 0, 30, 28, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(22, 0, 30, 29, instructions::Sve::sizespec_t::s));

  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(3, 0, 31, 24, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(7, 0, 31, 25, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(11, 0, 31, 26, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(15, 0, 31, 27, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(19, 0, 31, 28, instructions::Sve::sizespec_t::s));
  m_kernel.addInstruction(instructions::Sve::dpFmlaVec(23, 0, 31, 29, instructions::Sve::sizespec_t::s));
  

  // prepare pointer for next iteration
  m_kernel.addInstruction(mini_jit::instructions::Base::dpSubImm(1, 1, 6*i_k*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(0, 0, 16*4, 0));
  
  // loop if required
  int32_t l_jumpPc = -m_kernel.getOffset() / 4;
  l_ins = instructions::Base::bCbnz( 5,
                                     l_jumpPc,
                                     0 );
  m_kernel.addInstruction( l_ins );

  // store accumulator 
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(0, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(1, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(2, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(3, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(4, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(5, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(6, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(7, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(8, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(9, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(10, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(11, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(12, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(13, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(04, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(15, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(16, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(17, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(18, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(19, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));

  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(20, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(21, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(22, 2, 0));
  m_kernel.addInstruction(mini_jit::instructions::Base::dpAddImm(2, 2, 16*4, 0));
  m_kernel.addInstruction(mini_jit::instructions::Sve::lsStrVec(23, 2, 0));



  // restore according to procedure call standard
  m_kernel.addInstruction( 0x6CC13FEE );
  m_kernel.addInstruction( 0x6CC137EC );
  m_kernel.addInstruction( 0x6CC12FEA );
  m_kernel.addInstruction( 0x6CC127E8 );

  m_kernel.addInstruction( 0xA8C17BFD );
  m_kernel.addInstruction( 0xA8C173FB );
  m_kernel.addInstruction( 0xA8C16BF9 );
  m_kernel.addInstruction( 0xA8C163F7 );
  m_kernel.addInstruction( 0xA8C15BF5 );
  m_kernel.addInstruction( 0xA8C153F3 );

  // ret
  l_ins = instructions::Base::bRet();
  m_kernel.addInstruction( l_ins );

  // we might debug through file-io
  std::string l_file = "small_gemm_sve.bin";
  m_kernel.write( l_file.c_str() );

  m_kernel.setKernel();

  return (void (*)( float const *,
                    float const *,
                    float       *  )) m_kernel.getKernel();
}
