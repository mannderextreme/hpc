#include "Node.h"


double Node::getM_data(){
    return this -> m_data;
}

void Node::setM_data(double i_data){
    this -> m_data = i_data;
}
Node * Node::getM_left(){
    return this -> m_left;
}
void Node::setM_left(Node * i_node){
    this -> m_left = i_node;
}

Node * Node::getM_right(){
    return this -> m_right;

}
void Node::setM_right(Node *  i_node){
    this -> m_right = i_node;
}