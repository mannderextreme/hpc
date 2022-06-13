BUILD_DIR = ./build

micro_bf16: driver.cpp kernels/gemm_ref.cpp kernels/gemm_asm_bf16_16_12_4.s kernels/gemm_asm_bf16_4_2_8.s kernels/gemm_asm_bf16_16_12_64.s
	clang++ -pedantic -Wall -Wextra -Werror -march=armv8-a+sve+bf16 -c kernels/gemm_ref.cpp -o $(BUILD_DIR)/gemm_ref.o 
	clang   -pedantic -Wall -Wextra -Werror -march=armv8-a+sve+bf16 -c kernels/gemm_asm_bf16_4_2_8.s -o $(BUILD_DIR)/gemm_asm_bf16_4_2_8.o 
	clang   -pedantic -Wall -Wextra -Werror -march=armv8-a+sve+bf16 -c kernels/gemm_asm_bf16_16_12_4.s -o $(BUILD_DIR)/gemm_asm_bf16_16_12_4.o 
	clang   -pedantic -Wall -Wextra -Werror -march=armv8-a+sve+bf16 -c kernels/gemm_asm_bf16_16_12_64.s -o $(BUILD_DIR)/gemm_asm_bf16_16_12_64.o 
	clang++ -pedantic -Wall -Wextra -Werror -march=armv8-a+sve+bf16 driver.cpp $(BUILD_DIR)/gemm_ref.o $(BUILD_DIR)/gemm_asm_bf16_4_2_8.o $(BUILD_DIR)/gemm_asm_bf16_16_12_64.o $(BUILD_DIR)/gemm_asm_bf16_16_12_4.o -o micro_bf16

all: micro_bf16
$(shell mkdir -p build)