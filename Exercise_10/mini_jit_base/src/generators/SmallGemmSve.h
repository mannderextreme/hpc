#ifndef MINI_JIT_GENERATORS_SMALL_GEMM_SVE_H
#define MINI_JIT_GENERATORS_SMALL_GEMM_SVE_H

#include "../backend/Kernel.h"

namespace mini_jit {
  namespace generators {
    class SmallGemmSve;
  }
}

class mini_jit::generators::SmallGemmSve {
  private:
    //! kernel backend
    backend::Kernel m_kernel;

  public:
    /**
     * Generates a matrix kernel which performs the operation C += A*B.
     * The generated kernel takes pointer to A, B and C as input.
     *
     * @param i_m BLAS-parameter M.
     * @param i_n BLAS-parameter N.
     * @param i_k BLAS-parameter K.
     *
     * @return function pointer to kernel.
     **/
    void ( *generate( uint32_t i_m,
                      uint32_t i_n,
                      uint32_t i_k ) )( float const * i_a,
                                        float const * i_b,
                                        float       * io_c );
};

#endif
