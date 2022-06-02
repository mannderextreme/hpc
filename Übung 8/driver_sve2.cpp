#include <arm_fpvec_len.h>
#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>

extern "C"{
    fmlalb_sve2(floatvec_len_t * v_a,
                floatvec_len_t * v_b,
                float * v_c);
    fmlalt_sve2(floatvec_len_t * v_a,
                floatvec_len_t * v_b,
                float * v_c);
    eor3_sve2(  int * v_a,
                int * v_b,
                int * v_c);
}
int main(){

//16 floats fit in one 512 bit vector register
int vec_len = 16;
//allocate memory for fmlalt/b

floatvec_len_t * v_a = new floatvec_len_t[vec_len];
floatvec_len_t * v_b = new floatvec_len_t[vec_len];
float * v_c_top = new float[vec_len];
float * v_c_bot = new float[vec_len];


//set values
for(int i = 0 ; i < vec_len; i++){
    v_a[i] = i*10;
    va_b[i] = i*10;
    v_c_bot = 0;
    v_c_top = 0;
}

//calculate top and bottom fma
fmlalt_sve2(v_a, v_b, v_c_top);
fmlalb_sve2(v_a, v_b, v_c_bottom);

for(int i = 0 ; i < vec_len; i++){
    std::cout << v_a[i] << "  " << v_b[i] << "  " 
    << v_c_top << "  " << v_c_bot << std::endl;
}

delete[] v_a;
delete[] v_b;
delete[] v_c;

// allocate memory for eor
/*
* there are mainly 4 different possibilities for xor 
* 111, 110, 100, 000
* using even / uneven numbers last bit of each number can be set to 0 / 1
*/
int * v_a = new [vec_len];
int * v_b = new [vec_len];
int * v_c = new [vec_len];

//obv redundance but better readable
//case 1
v_a[0] = 1;
v_b[0] = 1;
v_c[0] = 1;

//case 2
v_a[1] = 2;
v_b[1] = 1;
v_c[1] = 1;

//case 3
v_a[2] = 2;
v_b[2] = 2;
v_c[2] = 1;

//case 4
v_a[3] = 2;
v_b[3] = 2;
v_c[3] = 2;

for(int i = 4; i < vec_len; i++){
    v_a = 0;
    v_b = 0;
    v_c = 0;
}
for(int i = 0; i < 4; i++)
    int bit = v_c[i] >> 31 << 31;
    std::cout << "Case: " << i + 1 << std::endl;
    << "Resulting bit: " << bit << std::endl << std::endl;



}
