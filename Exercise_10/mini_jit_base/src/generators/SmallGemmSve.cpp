#include "SmallGemmSve.h"
#include "../instructions/Base.h"
#include "../instructions/Sve.h"

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

  // TODO: finish implementation

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
