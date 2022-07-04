#include <cstdint>

/**
 * A function that multiplies float input with 2
 * 
 * @param i_a float value a.
 * @return float i_a*2.
 */
float multiply_by_two(float i_a);

/**
 * A simple implementation of the triad c[:] = a[:] + 2.0f * b[:]
 *
 * @param i_nValues number of values in the arrays.
 * @param i_a pointer to array a.
 * @param i_b pointer to array b.
 * @param o_c pointer to array c.
 **/
void triad_simple( uint64_t         i_nValues,
                   float    const * i_a,
                   float    const * i_b,
                   float          * o_c );

/**
 * A simple implementation of the triad c[:] = a[:] + 2.0f * b[:]
 * but with an uncountable loop 
 *
 * @param i_nValues number of values in the arrays.
 * @param i_a pointer to array a.
 * @param i_b pointer to array b.
 * @param o_c pointer to array c.
 **/
void triad_uncountable( uint64_t         i_nValues,
                        float    const * i_a,
                        float    const * i_b,
                        float          * o_c );

                        
/**
 * A simple implementation of the triad c[:] = a[:] + 2.0f * b[:]
 * but with an uncountable loop 
 *
 * @param i_nValues number of values in the arrays.
 * @param i_a pointer to array a.
 * @param i_b pointer to array b.
 * @param o_c pointer to array c.
 **/
void triad_with_extern_func( uint64_t         i_nValues,
                        float    const * i_a,
                        float    const * i_b,
                        float          * o_c );

/**
 * A simple implementation of the triad c[:] = a[:] + 2.0f * b[:]
 * parallelized with omp 
 *
 * @param i_nValues number of values in the arrays.
 * @param i_a pointer to array a.
 * @param i_b pointer to array b.
 * @param o_c pointer to array c.
 **/
void triad_parallel( uint64_t         i_nValues,
                   float    const * i_a,
                   float    const * i_b,
                   float          * o_c );