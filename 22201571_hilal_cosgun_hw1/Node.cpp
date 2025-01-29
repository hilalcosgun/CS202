/**
* Title: Binary Search Tree Node
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 1
* Description : Node class to create nodes for a linked based BST 
*/
#include <iostream>
#include "Node.h"
using namespace std;
Node::Node(){
}
Node::Node(int keyValue, Node* left, Node* right){
    key = keyValue;
    leftPtr = left;
    rightPtr = right;
}


