/**
* Title: AVL Tree Header
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 2 
*/
#ifndef AVLTREE_H
#define AVLTREE_H

struct Node {
    int key;
    int height;
    int count;
    Node* leftPtr;
    Node* rightPtr;

    Node(int k) : key(k), height(1), count(1), leftPtr(nullptr), rightPtr(nullptr) {}
};

class AVLTree {
private:
    Node* rootPtr;
    void clear(Node* rootPtr);
    void insertHelper(int key, Node*& rootPtr);
    void removeHelper(int key, Node*& rootPtr);
    int getBalanceFactor(Node* rootPtr);
    void balance(Node*& rootPtr);
    void leftRotation(Node*& rootPtr);
    void rightRotation( Node*& rootPtr);
    int max(int x, int y);
    int getHeight(Node* node);
    void findMaxLesserHelper(int key,Node* rootPtr,int& maxLesser);
    int findLmNode(Node* rootPtr);
    bool findKeyHelper(int key, Node* rootptr);
    
public:
    AVLTree();
    ~AVLTree();
    void insert(int key);
    void remove(int key);
    int chooseForOther(int key);
    int findMax();
    int findMin();
    bool findKey(int key);
    
    //int getMin();
    //int getMax();
    //bool compare(AVLTree other);
};

#endif