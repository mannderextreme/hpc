BUILD_DIR = ./build

micro_gemm_asm: driver.cpp kernels/gemm_asm_sve_64_6_1.s kernels/gemm_asm_sve_64_6_48.s
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_64_6_1.s  -o ${BUILD_DIR}/gemm_asm_sve_64_6_1.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_63_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_63_6_48.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_64_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_48.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_128_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_128_6_48.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_128_48_48.s -o ${BUILD_DIR}/gemm_asm_sve_128_48_48.o
		g++ -pedantic -Wall -Wextra -Werror driver.cpp ${BUILD_DIR}/gemm_asm_sve_64_6_1.o ${BUILD_DIR}/gemm_asm_sve_64_6_48.o ${BUILD_DIR}/gemm_asm_sve_63_6_48.o ${BUILD_DIR}/gemm_asm_sve_128_6_48.o ${BUILD_DIR}/gemm_asm_sve_128_48_48.o -o ${BUILD_DIR}/micro_gemm_asm
	
test_gemm_asm_64_6: test_gemm_asm_64_6.cpp kernels/gemm_asm_sve_64_6_1.s kernels/gemm_asm_sve_64_6_48.s
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_64_6_1.s  -o ${BUILD_DIR}/gemm_asm_sve_64_6_1.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_64_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_64_6_48.o
		gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/gemm_asm_sve_128_6_48.s -o ${BUILD_DIR}/gemm_asm_sve_128_6_48.o
		g++ -pedantic -Wall -Wextra -Werror -march=armv8-a+sve test_gemm_asm_64_6.cpp ${BUILD_DIR}/gemm_asm_sve_64_6_1.o ${BUILD_DIR}/gemm_asm_sve_64_6_48.o ${BUILD_DIR}/gemm_asm_sve_128_6_48.o -o ${BUILD_DIR}/test_gemm_asm_64_6

all: micro_gemm_asm test_gemm_asm_64_6

$(shell mkdir -p build) 