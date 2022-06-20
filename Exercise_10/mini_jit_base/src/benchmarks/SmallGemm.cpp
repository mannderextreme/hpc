#include "SmallGemm.h"
#include <cmath>
#include <algorithm>
#include <chrono>

void mini_jit::benchmarks::SmallGemm::gemmRef( float const * i_a,
                                               float const * i_b,
                                               float       * io_c,
                                               uint32_t      i_m,
                                               uint32_t      i_n,
                                               uint32_t      i_k,
                                               uint32_t      i_lda,
                                               uint32_t      i_ldb,
                                               uint32_t      i_ldc ) {
  for( uint32_t l_m = 0; l_m < i_m; l_m++ ) {
    for( uint32_t l_n = 0; l_n < i_n; l_n++ ) {
      for( uint32_t l_k = 0; l_k < i_k; l_k++ ) {
        io_c[ l_n*i_ldc + l_m ] += i_a[ l_k*i_lda + l_m ] * i_b[ l_n*i_ldb + l_k ];
      }
    }
  }
}

float mini_jit::benchmarks::SmallGemm::maxDiff( float const * i_mat0,
                                                float const * i_mat1,
                                                uint32_t      i_m,
                                                uint32_t      i_n,
                                                uint32_t      i_ld ) {
  float l_maxDiff = 0;

  for( uint32_t l_m = 0; l_m < i_m; l_m++ ) {
    for( uint32_t l_n = 0; l_n < i_n; l_n++ ) {
      float l_diff = i_mat0[ l_n*i_ld + l_m ] - i_mat1[ l_n*i_ld + l_m ];
      l_diff = std::abs( l_diff );

      l_maxDiff = std::max( l_maxDiff, l_diff );
    }
  }

  return l_maxDiff;
}

float mini_jit::benchmarks::SmallGemm::verify( uint32_t i_m,
                                               uint32_t i_n,
                                               uint32_t i_k,
                                               void (*  i_kernel)( float const *,
                                                                   float const *,
                                                                   float       * ) ) {
  // alloc memory
  std::size_t l_sizeA  = i_m;
              l_sizeA *= i_k;
  std::size_t l_sizeB  = i_k;
              l_sizeB *= i_n;
  std::size_t l_sizeC  = i_m;
              l_sizeC *= i_n;

  float * l_a    = new float[ l_sizeA ];
  float * l_b    = new float[ l_sizeB ];
  float * l_c    = new float[ l_sizeC ];
  float * l_cRef = new float[ l_sizeC ];

  // init data
  srand48( time(NULL) );
  for( unsigned int l_id = 0; l_id < l_sizeA; l_id++ ) {
    l_a[l_id] = (float) drand48();
  }
  for( unsigned int l_id = 0; l_id < l_sizeB; l_id++ ) {
    l_b[l_id] = (float) drand48();
  }
  for( unsigned int l_id = 0; l_id < l_sizeC; l_id++ ) {
    l_c[l_id] = (float) drand48();
  }
  for( unsigned int l_id = 0; l_id < l_sizeC; l_id++ ) {
    l_cRef[l_id] = l_c[l_id];
  }  

  // run reference
  gemmRef( l_a,
           l_b,
           l_cRef,
           i_m,
           i_n,
           i_k,
           i_m,
           i_k,
           i_m );

  // run kernel
  i_kernel( l_a,
            l_b,
            l_c );

  // compare solutions
  float l_diff = maxDiff( l_c,
                          l_cRef,
                          i_m,
                          i_n,
                          i_m );

  // free memory
  delete[] l_a;
  delete[] l_b;
  delete[] l_c;
  delete[] l_cRef;

  return l_diff;
}

double mini_jit::benchmarks::SmallGemm::bench( uint32_t i_m,
                                               uint32_t i_n,
                                               uint32_t i_k,
                                               uint64_t i_nReps,
                                               void (*  i_kernel)( float const *,
                                                                   float const *,
                                                                   float       * ) ) {
  std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;
  std::chrono::duration<double> l_dur;

  // alloc memory
  std::size_t l_sizeA  = i_m;
              l_sizeA *= i_k;
  std::size_t l_sizeB  = i_k;
              l_sizeB *= i_n;
  std::size_t l_sizeC  = i_m;
              l_sizeC *= i_n;

  float * l_a = new float[ l_sizeA ];
  float * l_b = new float[ l_sizeB ];
  float * l_c = new float[ l_sizeC ];

  // init data
  srand48( time(NULL) );
  for( unsigned int l_id = 0; l_id < l_sizeA; l_id++ ) {
    l_a[l_id] = (float) drand48();
  }
  for( unsigned int l_id = 0; l_id < l_sizeB; l_id++ ) {
    l_b[l_id] = (float) drand48();
  }
  for( unsigned int l_id = 0; l_id < l_sizeC; l_id++ ) {
    l_c[l_id] = (float) drand48();
  }

  // do a dry run
  i_kernel( l_a,
            l_b,
            l_c );

  // benchmark the kernel's performance
  l_tp0 = std::chrono::high_resolution_clock::now();
  for( unsigned int l_re = 0; l_re < i_nReps; l_re++ ) {
    i_kernel( l_a,
              l_b,
              l_c );
  }
  l_tp1 = std::chrono::high_resolution_clock::now();

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  double l_gFlops  = i_nReps;
         l_gFlops *= i_m * i_n * i_k * 2;
         l_gFlops *= 1.0E-9;
         l_gFlops /= l_dur.count();

  // free memory
  delete[] l_a;
  delete[] l_b;
  delete[] l_c;

  return l_gFlops;
}
