#include <iostream>
#include "generators/Simple.h"
#include "generators/Loop.h"
#include "generators/Triad.h"
#include "benchmarks/SmallGemm.h"
#include "generators/SmallGemmSve.h"

int main() {
  std::cout << "###########################" << std::endl;
  std::cout << "### welcome to mini_jit ###" << std::endl;
  std::cout << "###########################" << std::endl;

  /*
   * Simple
   */
  std::cout << "simple:" << std::endl;
  std::cout << "  generating simple kernel" << std::endl;
  mini_jit::generators::Simple l_simple;
  uint32_t (* l_funcSimple)() = l_simple.generate();

  std::cout << "  running" << std::endl;
  std::cout << "    result: " << l_funcSimple() << std::endl;

  /*
   * Loop
   */
  std::cout << "loop:" << std::endl;
  std::cout << "  generating" << std::endl;
  mini_jit::generators::Loop l_loop;
  uint32_t (* l_funcLoop)() = l_loop.generate( 32 );

  std::cout << "  running" << std::endl;
  std::cout << "    result: " << l_funcLoop() << std::endl;

  /*
   * Triad
   */
  std::cout << "triad:" << std::endl;
  std::cout << "  generating" << std::endl;
  mini_jit::generators::Triad l_triad;

  float l_a[95] = {0};
  float l_b[95] = {0};
  float l_c[95] = {0};
  for( unsigned short l_va = 0; l_va < 95; l_va++ ) {
    l_a[l_va] = l_va;
    l_b[l_va] = l_va+1;
  }
  void (* l_funcTriad)( float const *,
                        float const *,
                        float       * ) = l_triad.generate( 95 );
  std::cout << "  running" << std::endl;
  l_funcTriad( l_a,
               l_b,
               l_c );

  std::cout << "    result (id / a / b / c): " << std::endl;
  for( unsigned short l_va = 0; l_va < 95; l_va++ ) {
    std::cout << "    " << l_va << " / " << l_a[l_va] << " / " << l_b[l_va] << " / " << l_c[l_va] << std::endl;
  }

  /*
   * SmallGemmSve
   */
  std::cout << "SmallGemmSve M / N / K: 64 / 6 / 1" << std::endl;
  mini_jit::generators::SmallGemmSve l_smallGemmSve;
  void (* l_kernelGemmSve)( float const *,
                            float const *,
                            float       * ) = l_smallGemmSve.generate( 64,
                                                                       6,
                                                                       1 );

  std::cout << "    maximum difference: " << mini_jit::benchmarks::SmallGemm::verify( 64,
                                                                                      6,
                                                                                      1,
                                                                                      l_kernelGemmSve ) << std::endl;
  std::cout << "    GFLOPS: " << mini_jit::benchmarks::SmallGemm::bench( 64,
                                                                         6,
                                                                         1,
                                                                         100000000,
                                                                         l_kernelGemmSve ) << std::endl;

  std::cout << "##############################" << std::endl;
  std::cout << "### mini_jit says bye, bye ###" << std::endl;
  std::cout << "##############################" << std::endl;

  return EXIT_SUCCESS;
}
