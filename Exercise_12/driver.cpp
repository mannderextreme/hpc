#include "Tree.h"
#include <random>
#include <cstdint>
#include <iostream>
#include <chrono>

int main(){

    std::cout << "running binary tree" << std::endl;
    std::mt19937_64 rng;
    
    Tree * l_bt = new Tree();
    l_bt->initRandom(   32,
                        0.85,
                        0.85,
                        rng);
    std::cout << l_bt->getM_root();
    l_bt->printInorder(l_bt->getM_root());
    

    return EXIT_SUCCESS;
}