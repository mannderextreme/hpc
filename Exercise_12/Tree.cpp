#include "Tree.h"
#include <random>
#include <cstdint>
#include <iostream>

Node* Tree::getM_root(){
    return this -> m_root;
}

void Tree::setM_root(Node* i_root){
    this->m_root = i_root;
}

void Tree::initRandom(  uint64_t       i_nLevels,
                        uint64_t       i_levelCount,
                        Node *         i_node,
                        double         i_probLeft,
                        double         i_probRight,
                        std::mt19937_64 & i_generator ){
    
    if ( i_levelCount < i_nLevels){
        
        i_levelCount++;
        
        // init random number 
        std::uniform_real_distribution<double> unif(0, 1);
        double l_curr_random = unif(i_generator);

        if (l_curr_random < i_probLeft){
            Node * l_nodeLeft = new Node();
            i_node->setM_left(l_nodeLeft);
            i_node->getM_left()->setM_data(i_node->getM_data()+1);
            initRandom(i_nLevels,
                        i_levelCount,
                        i_node->getM_left(),
                        i_probLeft,
                        i_probRight,
                        i_generator);
        }

        l_curr_random = unif(i_generator);
        if ( l_curr_random < i_probRight){
            Node * l_nodeRight = new Node();
            i_node->setM_right(l_nodeRight);
            i_node-> getM_right()->setM_data(i_node->getM_data()+2);

            initRandom( i_nLevels,
                        i_levelCount,
                        i_node->getM_right(),
                        i_probLeft,
                        i_probRight,
                        i_generator);
        }
    }
}

void Tree::initRandom(  uint64_t       i_nLevels,
                        double         i_probLeft,
                        double         i_probRight,
                        std::mt19937_64 & i_generator ){
    if ( 0 < i_nLevels){
        
        Node * l_root = new Node();
        l_root-> setM_data(1);
        this->setM_root(l_root);
        uint64_t l_levelCount = 0;
        initRandom( i_nLevels,
                    l_levelCount,
                    m_root,
                    i_probLeft,
                    i_probRight,
                    i_generator);
    }

}

void Tree::printInorder( Node * i_node){
    printInorder(i_node->getM_left());
    std::cout << i_node->getM_data();
    printInorder(i_node->getM_right());
    
}
    