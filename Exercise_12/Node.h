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
   * @brief Construct a new Node object
   * 
   */
    Node(){

    }
    /**
     * Destructor of the node.
     * Frees all allocated memory.
     **/
    ~Node() {
      if( m_left  != nullptr ) delete m_left;
      if( m_right != nullptr ) delete m_right;
    }
    /**
     * @brief getter for m_data
     * 
     * @return double 
     */
    double getM_data();

    /**
     * @brief setter for m_data
     * 
     * @param i_data 
     */
    void setM_data(double i_data);

    /**
     * @brief getter for m_left
     * 
     * @return Node* 
     */
    Node * getM_left();

    /**
     * @brief setter for m_left
     * 
     * @param i_node 
     */
    void setM_left(Node * i_node);

    /**
     * @brief getter for m_right
     * 
     * @param i_node 
     * @return Node* 
     */
    Node * getM_right();
    /**
     * @brief setter for m_right
     * 
     * @param i_node 
     */
    void setM_right(Node *  i_node);
};