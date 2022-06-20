#include "MyExample.h"

uint32_t ( *mini_jit::generators::MyExample::generate() )() {
  uint32_t l_ins = 0;

  // perform bitwise and of w0 with 0
  l_ins = instructions::Base::dpAndImm( 0,
                                        0,
                                        0,
                                        0 );
  m_kernel.addInstruction( l_ins );

  // ret
  l_ins = instructions::Base::bRet();
  m_kernel.addInstruction( l_ins );


  // we might debug through file-io
  // std::string l_file = "MyExample.bin";
  // m_kernel.write( l_file.c_str() );

  m_kernel.setKernel();

  return (uint32_t (*)()) m_kernel.getKernel();
}