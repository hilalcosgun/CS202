/**
* Title: Binary Search Tree 
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 1
* Description : A linked base BST implementation with additional methods.
*/
#ifndef BST_H
#define BST_H
#include <iostream>
#include "Node.h"
#include "NodeQueue.h"
//#include "NodeStack.h"
using namespace std;
class BST{
private:
    int size;
    Node* rootPtr;
    bool insertHelper(int key, Node*& rootPtr);
    bool deleteHelper(int key, Node*& rootPtr);
    Node* findLmNode(Node* rootPtr);
    void inOrderHelper(NodeQueue& q,Node* rootPtr);
    Node* LCAHelper(int A, int B, Node* rootPtr);
    int maximumSumHelper(NodeQueue& maxPath, Node*rootPtr);
    void pathHelper(NodeQueue& path, int key, Node* rootPtr);
    int findHeightHelper(Node* rootPtr);
    void clear(Node* rootPtr);
    bool isExist(int key, Node* rootPtr);
public:
    BST();
    BST(int keys[], int size); 
    ~BST();
    void insertKey(int key);
    void insertforAnalysis(int key);
    void deleteKey(int key);
    void displayInorder();
    void findFullBTLevel();
    void lowestCommonAncestor(int A, int B);
    void maximumSumPath();
    void maximumWidth();
    void pathFromAtoB(int A, int B);
    int findHeight();
};
#endif