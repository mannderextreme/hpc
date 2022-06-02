#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>

void triad_high( uint64_t i_nValues,
                 float    const * i_a,
                 float    const * i_b,
                 float          * o_c );