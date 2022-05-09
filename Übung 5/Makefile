BUILD_DIR = ./build

micro_gemm: driver.cpp kernels/gemm_ref.cpp kernels/gemm_compiler_32_32_32_32_32_32.cpp
	g++ -pedantic -Wall -Wextra -Werror -c kernels/gemm_ref.cpp -o ${BUILD_DIR}/gemm_ref.o
	g++ -pedantic -Wall -Wextra -Werror -c kernels/gemm_compiler_32_32_32_32_32_32.cpp -o ${BUILD_DIR}/gemm_compiler_32_32_32_32_32_32.o
	g++ -pedantic -Wall -Wextra -Werror driver.cpp ${BUILD_DIR}/gemm_ref.o ${BUILD_DIR}/gemm_compiler_32_32_32_32_32_32.o -o ${BUILD_DIR}/micro_gemm  

all: micro_gemm

$(shell mkdir -p build)