#include "Triad.h"
#include "../instructions/Base.h"
#include "../instructions/Asimd.h"

void ( *mini_jit::generators::Triad::Triad::generate( uint64_t i_nValues ) )( float const * i_a,
                                                                              float const * i_b,
                                                                              float       * o_c ) {
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
  //std::string l_file = "triad.bin";
  //m_kernel.write( l_file.c_str() );

  m_kernel.setKernel();

  return (void (*)( float const *, float const *, float * )) m_kernel.getKernel();
}
