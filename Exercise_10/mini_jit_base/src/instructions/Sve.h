#ifndef MINI_JIT_INSTRUCTIONS_SVE_H
#define MINI_JIT_INSTRUCTIONS_SVE_H

#include <cstdint>

namespace mini_jit {
  namespace instructions {
    class Sve;
  }
}

class mini_jit::instructions::Sve {
  public:
    enum sizespec_t: char {
      b = 0,
      h = 1,
      s = 2,
      d = 3
    };

    /**
     * Gets the machine code for load vector register.
     *
     * @param i_regSveVec SVE vector register.
     * @param i_regGpAddr general purpose register holding the address from which the data is loaded.
     * @param i_imm9 value of the 9-bit immediate.
     *
     * @return instruction.
     **/
    static uint32_t lsLdrVec( uint8_t  i_regSveVec,
                              uint8_t  i_regGpAddr,
                              uint32_t i_imm9 );

    /**
     * Gets the machine code for store vector register.
     *
     * @param i_regSveVec SVE vector register.
     * @param i_regGpAddr general purpose register holding the address to which the the is stored.
     * @param i_imm9 value of the 9-bit immediate.
     *
     * @return instruction.
     **/
    static uint32_t lsStrVec( uint8_t  i_regSveVec,
                              uint8_t  i_regGpAddr,
                              uint32_t i_imm9 );

   /**
    * Gets the machine code for load and broadcast unsigned word to vector.
    *
    * @param i_regSveVec SVE vector register.
    * @param i_regSvePre SVE predicate register.
    * @param i_regGpAddr general purpose register holding the address to which the the is stored.
    * @param i_imm6 value of the 6-bit immediate.
    *
    * @return instruction.
    **/
    static uint32_t lsLd1Rw( uint8_t  i_regSveVec,
                             uint8_t  i_regSvePred,
                             uint8_t  i_regGpAddr,
                             uint32_t i_imm6 );

   /**
    * Gets the machine code for initialize predicate from named constaint.
    *
    * @param i_regSvePred SVE predicate register.
    * @param i_sizeSpec size specifier.
    *
    * @return instruction.
    **/
    static uint32_t prPtrue( uint8_t    i_regSvePred,
                             sizespec_t i_sizeSpec );

   /**
    * Gets the machine code for while incrementing signed scalar while less than scalar.
    *
    * @param i_regSvePre SVE predicate register.
    * @param i_sizeSpec size specifier.
    * @param i_regGpSrc0 first source GPR.
    * @param i_regGpSrc1 second source GPR.
    *
    * @return instruction.
    **/
    static uint32_t prWhileLt( uint8_t    i_regSvePred,
                               sizespec_t i_sizeSpec,
                               uint8_t    i_regGpSrc0,
                               uint8_t    i_regGpSrc1 );

   /**
    * Gets the machine code for Floating-point fused multiply-add vectors (predicated).
    *
    * @param i_regSveVecA third source and destination vector register.
    * @param i_regSvePred size specifier.
    * @param i_regSveVecN first source vector register.
    * @param i_regSveVecM second source vector register.
    * @param i_sizeSpec size specifier.
    *
    * @return instruction.
    **/
    static uint32_t dpFmlaVec( uint8_t i_regSveVecA,
                               uint8_t i_regSvePred,
                               uint8_t i_regSveVecN,
                               uint8_t i_regSveVecM,
                               sizespec_t i_sizeSpec );
};

#endif