class Node {
  private:
    //! data item of the node
    double m_data = 0.0;
    //! pointer to left child if any
    Node * m_left = nullptr;
    //! pointer to right child if any
    Node * m_right = nullptr;

  public:
    /**
     * Destructor of the node.
     * Frees all allocated memory.
     **/
    ~Node() {
      if( m_left  != nullptr ) delete m_left;
      if( m_right != nullptr ) delete m_right;
    }

    // TODO: finish implementation
};