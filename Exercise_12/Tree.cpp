#include "Tree.h"
#include "Node.h"
#include <random>
#include <stdcint>
#include <iostream>



void Tree::initRandom(  uint64_t       i_nLevels,
                        uint64_t       i_levelCount,
                        Node *         i_node,
                        double         i_probLeft,
                        double         i_probRight,
                        std::mt19937 & i_generator ){
    
    if ( l_level_count < i_nLevels){
        
        i_levelCount++;
        
        // init random number 
        std::uniform_real_distribution<double> unif(0, 1);
        double l_curr_random = unif(i_generator);

        if (l_curr_random < i_probLeft){
            Node * l_nodeLeft = new Node();
            l_node-> m_left = l_nodeLeft;
            l_node-> m_left->m_data = m_data+1;
            initRandom(i_nLevels,
                        i_levelCount,
                        l_node->m_left,
                        i_probLeft,
                        i_probRight,
                        i_generator);
        }

        l_curr_random = unif(i_generator);
        if ( l_curr_random < i_probRight){
            Node * l_nodeRight = new Node();
            l_node->m_rigth = l_nodeRight;
            l_node-> m_right->m_data = m_data+2;

            initRandom( i_nLevels,
                        i_levelCount,
                        l_node->m_right,
                        i_probLeft,
                        i_probRight,
                        i_generator);
        }
    }
}

void Tree::printInorder( Node i_node){
    printInorder(i_node->m_left);
    std::cout << i_node;
    printInorder(i_node->m_left);
    
}

void Tree::initRandom(  uint64_t       i_nLevels,
                        double         i_probLeft,
                        double         i_probRight,
                        std::mt19937 & i_generator ){
    if ( 0 > i_nLevels){
        
        Node * l_root = new Node();
        m_root = l_root;
        m_root-> m_data = 1
        uint64_t l_levelCount = 0;
        initRandom( i_nLevels,
                        l_levelCount,
                        m_root,
                        i_probLeft,
                        i_probRight,
                        i_generator);
    }
}
    