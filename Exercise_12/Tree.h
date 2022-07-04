#include "Node.h"
#include <random>
#include <cstdint>
#include <iostream>

class Tree {
  private:
    //! root node of the tree
    Node * m_root = nullptr;

  public:
    /**
     * @brief Construct a new Tree object
     * 
     */
    Tree(){
      
    }
    /**
     * Destructor which frees all allocated memory.
     **/
    ~Tree() {
      if( m_root != nullptr ) delete m_root;
    };

    /**
     * @brief Get the M root object
     * 
     * @return Node* 
     */
    Node* getM_root();

    /**
     * @brief Set the M root object
     * 
     * @param i_root 
     */
    void setM_root(Node* i_root);
    
    /**
     * Insert a given node into the search tree
     * 
     * @param m_data 
     * @param node 
     */
    void insertNode( double m_data, 
                      Node * node);

    /**
     * @brief helper method for recursive calls
     * 
     * @param i_nLevels 
     * @param i_levelCount 
     * @param i_node 
     * @param i_probLeft 
     * @param i_probRight 
     * @param i_generator 
     */
    void initRandom(  uint64_t         i_nLevels,
                        uint64_t       i_levelCount,
                        Node *         i_node,
                        double         i_probLeft,
                        double         i_probRight,
                        std::mt19937_64 & i_generator );
    /**
     * Randomly initializes the tree.
     *
     * @param i_n_levels number of levels in the tree.
     * @param i_probLeft probability that a node has a left child.
     * @param i_probRight probability that a node has right child.
     * @param i_generator random number generator.
     **/
    void initRandom( uint64_t       i_nLevels,
                     double         i_probLeft,
                     double         i_probRight,
                     std::mt19937_64 & i_generator );
    
    /**
     * @brief print the traversed tree inorder
     * 
     * @param i_node 
     */
    void printInorder( Node * i_node);
    
    /**
     * Applies a function to all data items of the tree's nodes.
     *
     * @param i_func function which is applied.
     *               has the current level, parent node's data and node's data as args.
     **/
    void applyFunction( double(* i_func)( uint64_t i_lvl,
                                          double   i_dataParent,
                                          double   i_dataNode ) );

    // TODO: finish implementation
};