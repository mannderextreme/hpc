#include <stdio.h>

unsigned char l_data1  = 1;
unsigned char l_data2  = 255;

//leads to overflow
unsigned char l_data3  = l_data2 + 1;

//expected binary for A is 1010 and for 1 it is 0001
unsigned char l_data4  = 0xA1;
unsigned char l_data5  = 0b1001011;

//printable charakters in ASCII H is 1001000 
unsigned char l_data6  = 'H';
//complement representation for -4
         char l_data7  = -4;

//1 with 11 left shifts
unsigned int  l_data8  = 1u << 11;

//21 more left shifts leads to 1 going out of bound
unsigned int  l_data9 = l_data8 << 21;

//max_int  with 5 rightshifts
unsigned int  l_data10  = 0xFFFFFFFF >> 5;

//bitwise XOR giving 0110
unsigned int  l_data11 = 0b1001 ^ 0b01111;

//bitwise negate givin mostly 1s and two 0s at pos 0 and 4
unsigned int  l_data12 = ~0b1001;

//bitwise AND 
unsigned int  l_data13 = 0xF0 & 0b1010101;

//bitwise OR
unsigned int  l_data14 = 0b001 | 0b101;

//unsigned repr. of 7743
unsigned int  l_data15 = 7743;

//complement representation of 7743
         int  l_data16 = -7743;


unsigned int i_vec_instr = 0b01001110001000001100110000000000;

unsigned char i_vec_reg_dst = 0b00000000;

unsigned char i_vec_reg_src_0 = 0b00000001;

unsigned char i_vec_reg_src_1 = 0b00000010;

void print_binary(size_t const size, void const * const ptr){
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    // iterate through different bytes
    for(i = size-1; i >= 0; i--){
        //iterate inside byte
        for (j=7; j >=0; j--){
            //shift and bitwise AND 
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
            
        }
    }
    printf( "\n");
}



unsigned int instruction_asimd_compute( unsigned int  i_vec_instr,
                                        unsigned char i_vec_reg_dst,
                                        unsigned char i_vec_reg_src_0,
                                        unsigned char i_vec_reg_src_1 ){
    // bit manipulation using bitmasks                                     
    i_vec_instr = ((i_vec_instr & 0xFFFFFFE0)) | i_vec_reg_dst << 11 >> 11;
    i_vec_instr = ((i_vec_instr & 0xFFFFFC1F)) | i_vec_reg_src_0 << 11 >> 6;
    i_vec_instr = ((i_vec_instr & 0xFFE0FFFF)) | (unsigned int) i_vec_reg_src_1 << 26 >>10;
    return i_vec_instr;
}

int main(int argv, char* argc[]){
    unsigned int result = 0;
    printf("\n l_data1\n");
    print_binary(sizeof(l_data1), &l_data1);
    printf("\n l_data2\n");
    print_binary(sizeof(l_data2), &l_data2);
    printf("\n l_data3\n");
    print_binary(sizeof(l_data3), &l_data3);
    printf("\n l_data4\n");
    print_binary(sizeof(l_data4), &l_data4);
    printf("\n l_data5\n");
    print_binary(sizeof(l_data5), &l_data5);
    printf("\n l_data6\n");
    print_binary(sizeof(l_data6), &l_data6);
    printf("\n l_data7\n");
    print_binary(sizeof(l_data7), &l_data7);
    printf("\n l_data8\n");
    print_binary(sizeof(l_data8), &l_data8);
    printf("\n l_data9\n");
    print_binary(sizeof(l_data9), &l_data9);
    printf("\n l_data10\n");
    print_binary(sizeof(l_data10), &l_data10);
    printf("\n l_data11\n");
    print_binary(sizeof(l_data11), &l_data11);
    printf("\n l_data12\n");
    print_binary(sizeof(l_data12), &l_data12);
    printf("\n l_data13\n");
    print_binary(sizeof(l_data13), &l_data13);
    printf("\n l_data14 \n");
    print_binary(sizeof(l_data14), &l_data14);
    printf("\n l_data15 \n");
    print_binary(sizeof(l_data15), &l_data15);
    printf("\n l_data16 \n");
    print_binary(sizeof(l_data16), &l_data16);

    printf("\n Instruction asimd compute: \n");
    printf("Expected outcome:  \n01001110001000101100110000100000 \n");
    result = instruction_asimd_compute(i_vec_instr, i_vec_reg_dst, i_vec_reg_src_0, i_vec_reg_src_1 );
    print_binary(sizeof(result), &result);
    /*  TASK 3:
        We did set the bits of the FMLA instruction that encode the registers (two source registers and one destination register)
    
    */
}