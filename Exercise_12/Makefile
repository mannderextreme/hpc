BUILD_DIR = ./build


binary_tree: driver.cpp Node.cpp Tree.cpp
	g++ -g -pedantic -Wall -Wextra -Werror -O2 -fopenmp -c Node.cpp -o ${BUILD_DIR}/Node.o
	g++ -g -pedantic -Wall -Wextra -Werror -O2 -fopenmp -c Tree.cpp -o ${BUILD_DIR}/Tree.o
	g++ -g -pedantic -Wall -Wextra -Werror -O2 -fopenmp driver.cpp -o ${BUILD_DIR}/binary_tree

$(shell mkdir -p build)

