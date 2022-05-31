BUILD_DIR = ./build

micro_gemm_asm: driver.cpp kernels/gemm_asm_gp.s 
	gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_gp.s -o ${BUILD_DIR}/gemm_asm_gp.o
	g++ -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -O2 -fopenmp driver_sve.cpp ${BUILD_DIR}/gemm_asm_gp.o -o ${BUILD_DIR}/micro_gemm_asm

micro_gemm_asm_test: test_gemm.cpp kernels/gemm_asm_gp.s
	gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_gp.s -o ${BUILD_DIR}/gemm_asm_gp.o
	g++ -pedantic -Wall -Wextra -Werror -march=armv8-a+sve test_gemm.cpp ${BUILD_DIR}/gemm_asm_gp.o -o ${BUILD_DIR}/micro_gemm_asm_test

load_asm: driver_load.cpp assembly/load_asm.s
	gcc -pedantic -Wall -Wextra -Werror -g -c assembly/load_asm.s -o ${BUILD_DIR}/load_asm.o
	g++ -pedantic -Wall -Wextra -Werror -g driver_load.cpp ${BUILD_DIR}/load_asm.o -o ${BUILD_DIR}/load_asm

compare_asm: driver_cmp.cpp assembly/compare_asm.s
	gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c assembly/compare_asm.s -o ${BUILD_DIR}/compare_asm.o
	g++ -pedantic -Wall -Wextra -Werror -march=armv8-a+sve driver_cmp.cpp ${BUILD_DIR}/compare_asm.o -o ${BUILD_DIR}/compare_asm

copy_asm_c: driver_copy.cpp copy.c assembly/copy.s 
	gcc -pedantic -Wall -Wextra -Werror -g -c assembly/copy.s -o ${BUILD_DIR}/copy.o
	gcc -pedantic -Wall -Wextra -Werror -g -c copy.c -o ${BUILD_DIR}/copy_c.o
	g++ -pedantic -Wall -Wextra -Werror -g driver_copy.cpp ${BUILD_DIR}/copy.o ${BUILD_DIR}/copy_c.o -o ${BUILD_DIR}/copy_asm_c

hello_world: assembly/hello_world_asm.s
	gcc -g assembly/hello_world_asm.s -o ${BUILD_DIR}/hello_world


all: micro_gemm_asm

$(shell mkdir -p build) 