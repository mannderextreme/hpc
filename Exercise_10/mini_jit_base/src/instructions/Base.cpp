#include "Base.h"

uint32_t mini_jit::instructions::Base::nop() {
  return 0xd503201f;
}

uint32_t mini_jit::instructions::Base::bRet() {
  return 0xd65f03c0;
}

uint32_t mini_jit::instructions::Base::bCbnz( uint8_t i_regGp,
                                              int32_t i_imm19,
                                              uint8_t i_size ) {
  uint32_t l_ins = 0x35000000;
  l_ins |= 0x1f & i_regGp;
  l_ins |= (0x7FFFF & i_imm19) << 5;
  l_ins |= (0x1 & i_size) << 31;

  return l_ins;
}

uint32_t mini_jit::instructions::Base::dpMovImm( uint8_t  i_regGp,
                                                 uint16_t i_imm16,
                                                 uint8_t  i_size ) {
  uint32_t l_ins = 0x52800000;
  l_ins |= 0x1f & i_regGp;
  l_ins |= i_imm16 << 5;
  l_ins |= (0x1 & i_size) << 31;

  return l_ins;
}

uint32_t mini_jit::instructions::Base::dpAddImm( uint8_t  i_regGpDes,
                                                 uint8_t  i_regGpSrc,
                                                 uint16_t i_imm12,
                                                 uint8_t  i_size ) {
  uint32_t l_ins = 0x11000000;

  l_ins |= 0x1f & i_regGpDes;
  l_ins |= (0x1f & i_regGpSrc) << 5;
  l_ins |= (0xfff & i_imm12) << 10;
  l_ins |= (0x1 & i_size) << 31;

  return l_ins;
}


uint32_t mini_jit::instructions::Base::dpAddSr( uint8_t i_regGpDes,
                                                uint8_t i_regGpSrc0,
                                                uint8_t i_regGpSrc1,
                                                uint8_t i_imm6,
                                                shift_t i_shift,
                                                uint8_t i_size  ) {
  uint32_t l_ins = 0xb000000;

  l_ins |= 0x1f & i_regGpDes;
  l_ins |= (0x1f & i_regGpSrc0) << 5;
  l_ins |= (0x3f & i_imm6) << 10;
  l_ins |= (0x1f & i_regGpSrc1) << 16;
  l_ins |= (0x3 & i_shift) << 22;
  l_ins |= (0x1 & i_size) << 31;

  return l_ins;
}

uint32_t mini_jit::instructions::Base::dpSubImm( uint8_t  i_regGpDes,
                                                 uint8_t  i_regGpSrc,
                                                 uint16_t i_imm12,
                                                 uint8_t  i_size ) {
  uint32_t l_ins = 0x51000000;

  l_ins |= 0x1f & i_regGpDes;
  l_ins |= (0x1f & i_regGpSrc) << 5;
  l_ins |= (0xfff & i_imm12) << 10;
  l_ins |= (0x1 & i_size) << 31;

  return l_ins;
}

uint32_t mini_jit::instructions::Base::dpAndImm(uint8_t  i_regGpDes,
                                                 uint8_t  i_regGpSrc,
                                                 uint16_t i_imm12,
                                                 uint8_t  i_size ){
  uint32_t l_ins = 0x12000000;

  l_ins |= 0x1f & i_regGpDes;
  l_ins |= (0x1f & i_regGpSrc) << 5;
  l_ins |= (0xfff & i_imm12) << 10;
  l_ins |= (0x1 & i_size) << 31;

  return l_ins;

}
