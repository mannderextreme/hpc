BUILD_DIR = ./build
triad: driver.cpp kernels/triad_high.cpp kernels/triad_low.s
	gcc -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/triad_low.s  -o ${BUILD_DIR}/triad_low.o
	g++ -pedantic -Wall -Wextra -Werror -march=armv8-a+sve -c kernels/triad_high.cpp -o ${BUILD_DIR}/triad_high.o
	g++ -pedantic -Wall -Wextra -Werror -march=armv8-a+sve driver.cpp ${BUILD_DIR}/triad_high.o ${BUILD_DIR}/triad_low.o -o ${BUILD_DIR}/triad

sve_functions: driver_sve2.cpp kernels/eor3_sve2.s kernels/fmlalb_sve2.s kernels/fmlalt_sve2
	clang -pedantic -Wall -Wextra -Werror -march=armv8-a+sve2 -c kernels/eor3_sve2.s  -o ${BUILD_DIR}/eor3_sve2.o
	clang -pedantic -Wall -Wextra -Werror -march=armv8-a+sve2 -c kernels/fmlalb_sve2.s  -o ${BUILD_DIR}/fmlalb_sve2.o
	clang -pedantic -Wall -Wextra -Werror -march=armv8-a+sve2 -c kernels/fmlalt_sve2.s  -o ${BUILD_DIR}/fmlalt_sve2.o
	g++ -pedantic -Wall -Wextra -Werror  driver_sve2  ${BUILD_DIR}/eor3_sve2.o ${BUILD_DIR}/fmlalb_sve2.o ${BUILD_DIR}/fmlalt_sve2.o -o ${BUILD_DIR}/sve_functions

$(shell mkdir -p build) 