#include "Sve.h"

uint32_t mini_jit::instructions::Sve::lsLdrVec( uint8_t  i_regSveVec,
                                                uint8_t  i_regGpAddr,
                                                uint32_t i_imm9 ) {
  uint32_t l_ins = 0x0;

  // TODO: finish implementation

  return l_ins;
}

uint32_t mini_jit::instructions::Sve::lsStrVec( uint8_t  i_regSveVec,
                                                uint8_t  i_regGpAddr,
                                                uint32_t i_imm9 ) {
  uint32_t l_ins = 0x0;

  // TODO: finish implementation

  return l_ins;
}

uint32_t mini_jit::instructions::Sve::lsLd1Rw( uint8_t  i_regSveVec,
                                               uint8_t  i_regSvePred,
                                               uint8_t  i_regGpAddr,
                                               uint32_t i_imm6 ) {
  uint32_t l_ins = 0x8540c000;

  l_ins |= 0x1f & i_regSveVec;
  l_ins |= (0x1f & i_regGpAddr) << 5;
  l_ins |= (0x7 & i_regSvePred) << 10;
  l_ins |= (0x3f & i_imm6) << 16;

  return l_ins;
}


uint32_t mini_jit::instructions::Sve::prPtrue( uint8_t    i_regSvePred,
                                               sizespec_t i_sizeSpec ) {
  uint32_t l_ins = 0x2518e3e0;

  l_ins |= 0x1f & i_regSvePred;
  l_ins |= (0x3 & i_sizeSpec) << 22;

  return l_ins;
}

uint32_t mini_jit::instructions::Sve::prWhileLt( uint8_t    i_regSvePred,
                                                 sizespec_t i_sizeSpec,
                                                 uint8_t    i_regGpSrc0,
                                                 uint8_t    i_regGpSrc1 ) {
  uint32_t l_ins = 0x25201400;

  l_ins |= 0xf & i_regSvePred;
  l_ins |= (0x1f & i_regGpSrc0) << 5;
  l_ins |= (0x1f & i_regGpSrc1) << 16;
  l_ins |= (0x3 & i_sizeSpec) << 22;

  return l_ins;
}

uint32_t mini_jit::instructions::Sve::dpFmlaVec( uint8_t    i_regSveVecA,
                                                 uint8_t    i_regSvePred,
                                                 uint8_t    i_regSveVecN,
                                                 uint8_t    i_regSveVecM,
                                                 sizespec_t i_sizeSpec ) {
  uint32_t l_ins = 0x0;

  // TODO: finish implementation

  return l_ins;                                                  
}
