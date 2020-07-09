#include"node.h"
#include<iostream>

using namespace std;

void Node::addChild(Node *child){
    if(child_num == n){
        tooManyChildren e;
        throw e;
    }
    child->parent = this;
    // children[child_num] = new Node(0, n);
    children[child_num] = child;
    height = 1;
    child_num++;
}
// REQUIRES: n of the child node is the same with n of this
// EFFECTS: add the node child to the children array
//          throw an exception tooManyChildren when child_num exceed n


Node::Node(int _value, int _n):
value(_value), child_num(0), n(_n), parent(nullptr), children(new Node*[n]), height(0)
{
}
// EFFECTS: create a root node with value and n

Node::~Node(){
    if(height == 0){
        // delete[] **children;
        delete[] children;
        return;
    }
   // for(int i = 0; i < child_num; i++){
    //    this->children[i]->~Node();
    //}
    // delete
    for(int i = 0; i < child_num; i++){
        delete children[i];
    }
    delete[] children;
}
// EFFECTS: destroy the whole tree rooted at sub

void Node::addChild(int _value){
    Node* child = new Node(_value, n);
    addChild(child);
}
// EFFECTS: create a child node with value and add it to the children array
//			throw an exception tooManyChildren when child_num exceed n



void Node::traverse(){
    cout << value << " ";
    for(int i = 0; i < child_num; i++){
        this->children[i]->traverse();
    }
}
// EFFECTS: print the value of the nodes using a pre-order traversal,
//          separated by a space.
//          A pre-order traversal print the value of the node
//          and then traverse its child nodes
//          according to the sequence in children array.
//          For example, the output of the tree above is
//          1 2 4 5 6 8 9 3 7
//          And the output of the tree below is
//          1 3 5 6 2 4

bool Node::contain(Node *sub){
    if(sub->value != value){
        return false;
    }
    if(!sub->height){
        // leaf case
        return true;
    }

    bool out = true;
    for(int i = 0; i < sub->child_num; i++){
        out *= this->children[i]->contain(sub->children[i]);
        if(!out)
            break;
    }
    return out;
}
// EFFECTS: return whether the tree rooted at sub is a subtree of this

int Node::getHeight(){
    int max = 0;
    for(int i = 0; i < child_num; i++){
        int out = 0;
        if(!child_num)
            break;
        out = 1 + children[i]->getHeight();
        if(out > max)
            max = out;
    }
    return max;
}
// EFFECTS: return height of this

Node &Node::operator[](int i){
    return **(children + i);
}
// EFFECTS: return a reference of (i+1) th child node of this,
//          e.g. node1[0] returns a reference of the first child node of node1
//          if i is invalid, throw an invalidIndex
