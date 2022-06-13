BUILD_DIR = ./build

micro_bf16: driver.cpp kernels/gemm_asm_bf16_16_12_4
	clang -pedantic -Wall -Wextra -Werror -march=armv8-a+sve+bf16 -c kernels/gemm_ref.cpp -o $(BUILD_DIR)/gemm_ref.o 
	clang -pedantic -Wall -Wextra -Werror -march=armv8-a+sveb+f16 -c kernels/gemm_asm_bf16_16_12_4 -o $(BUILD_DIR)/gemm_asm_bf16_16_12_4.o 
	clang -pedantic -Wall -Wextra -Werror -march=armv8-a+sve+bf16 driver.cpp $(BUILD_DIR)/gemm_ref.o $(BUILD_DIR)/gemm_asm_bf16_16_12_4.o -o micro_bf16

all: micro_bf16
$(shell mkdir -p build)