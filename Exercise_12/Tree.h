exit#include <random>

class Tree {
  private:
    //! root node of the tree
    Node * m_root = nullptr;

  public:
    /**
     * Destructor which frees all allocated memory.
     **/
    ~Tree() {
      if( m_root != nullptr ) delete m_root;
    };
    /**
     * Insert a given node into the search tree
     * 
     * @param m_data 
     * @param node 
     */
    void insertNode( double m_data, 
                      Node * node);


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
                     std::mt19937 & i_generator );

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