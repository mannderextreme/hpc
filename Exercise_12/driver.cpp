#include "Tree.h"
#include "Node.h"
#include <random>
#include <stdcint>
#include <iostream>
#include <chrono>

int main(){

    std::cout << "running binary tree" << std::endl;
    std::mt19937 rng = new std::mt19937();
    Tree * l_bt = new Tree();
    Tree::initRandom(   32,
                        0.85,
                        0.85,
                        rng);

    Tree::printInorder(Tree->m_root);
    

    EXIT_SUCCESS;
}