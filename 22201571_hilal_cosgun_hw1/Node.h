/**
* Title: Binary Search Tree Node
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 1
* Description : Node class to create nodes for a linked based BST 
*/
#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;
class Node{
private:
    int key;
    Node* leftPtr;
    Node* rightPtr;
public:
    Node();
    Node(int keyValue, Node* left = nullptr, Node* right = nullptr);
    friend class BST;
    friend class NodeQueue;
};
#endif