#ifndef MINI_JIT_BENCHMARKS_SMALL_GEMM_H
#define MINI_JIT_BENCHMARKS_SMALL_GEMM_H

#include <cstdint>

namespace mini_jit {
  namespace benchmarks {
    class SmallGemm;
  }
}

class mini_jit::benchmarks::SmallGemm {
  private:
    /**
     * Reference implementation of a GEMM kernel.
     * Performs C += A * B.
     *
     * @param i_a column-major matrix A.
     * @param i_b column-major matrix B.
     * @param io_c column-major matrix C.
     * @param i_m BLAS-parameter M.
     * @param i_n BLAS-parameter N.
     * @param i_k BLAS-parameter K.
     * @param i_lda leading dimension of A.
     * @param i_ldb leading dimension of B.
     * @param i_ldc leading dimension of C.
     **/
    static void gemmRef( float const * i_a,
                         float const * i_b,
                         float       * io_c,
                         uint32_t      i_m,
                         uint32_t      i_n,
                         uint32_t      i_k,
                         uint32_t      i_lda,
                         uint32_t      i_ldb,
                         uint32_t      i_ldc );

    /**
     * Computes the maximum element-wise difference of two matrices.
     *
     * @param i_mat0 first matrix.
     * @param i_mat1 second matrix.
     * @param i_m number of rows.
     * @param i_n number of columns.
     * @param i_ld leading dimension.
     *
     * @return maximum element-wise difference.
     **/
    static float maxDiff( float const * i_mat0,
                          float const * i_mat1,
                          uint32_t      i_m,
                          uint32_t      i_n,
                          uint32_t      i_ld );

  public:
    /**
     * Compares the jitted kernel to our reference kernel.
     * Operations is C += A*B with randomly initialized A, B and C.
     *
     * @param i_m BLAS-parameter M.
     * @param i_n BLAS-parameter N.
     * @param i_k BLAS-parameter K.
     * @param i_kernel function pointer of the kernel.
     *
     * @return maximum difference of any two values in the jitted and reference version of C.
     **/ 
    static float verify( uint32_t i_m,
                         uint32_t i_n,
                         uint32_t i_k,
                         void (*  i_kernel)( float const *,
                                             float const *,
                                             float       * ) );

    /**
     * Benchmarks the performance of the jitted kernel.
     * Operations is C += A*B with randomly initialized A, B and C.
     *
     * @param i_m BLAS-parameter M.
     * @param i_n BLAS-parameter N.
     * @param i_k BLAS-parameter K.
     * @param i_nReps number of repetitions.
     * @param i_kernel function pointer of the kernel.
     *
     * @return sustained FP32-GFLOPS.
     **/ 
    static double bench( uint32_t i_m,
                         uint32_t i_n,
                         uint32_t i_k,
                         uint64_t i_nReps,
                         void (*  i_kernel)( float const *,
                                             float const *,
                                             float       * ) );
};

#endif