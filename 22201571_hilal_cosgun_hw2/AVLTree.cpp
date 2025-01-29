/**
* Title: AVL Tree Implementation
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 2 
*/
#include "AVLTree.h"
#include <iostream>
AVLTree::AVLTree(){
    rootPtr = nullptr;
}
AVLTree::~AVLTree(){
    clear(rootPtr);
}
void AVLTree::clear(Node* rootPtr){
    if(rootPtr == nullptr){
        return;
    }
    clear(rootPtr->leftPtr);
    clear(rootPtr->rightPtr);
    delete rootPtr;
}
int AVLTree::max(int x, int y){
    if(x > y){
        return x;
    }
    return y;
}
int AVLTree::getHeight(Node* node){
    if(node == nullptr){
        return 0;
    }
    return node->height;
}
int AVLTree::getBalanceFactor(Node* rootPtr){
    if(rootPtr == nullptr){
        return 0;
    }
    return getHeight(rootPtr->leftPtr)- getHeight(rootPtr->rightPtr);
}
void AVLTree::balance(Node*& rootPtr){
    if(rootPtr == nullptr ){
        return;
    }
    if((getBalanceFactor(rootPtr)) > 1 ){
        if(getBalanceFactor(rootPtr->leftPtr) > 0){ //RR 
            rightRotation(rootPtr);
        }
        else{
            leftRotation(rootPtr->leftPtr); //LR
            rightRotation(rootPtr);
        }
    }
    if((getBalanceFactor(rootPtr)) < -1){
        if(getBalanceFactor(rootPtr->rightPtr) < 0){ //LL
            leftRotation(rootPtr);
        }
        else{
            rightRotation(rootPtr->rightPtr); //RL
            leftRotation(rootPtr);
        }
    }
    rootPtr->height = max(getHeight(rootPtr->rightPtr),getHeight(rootPtr->leftPtr)) + 1;
}
void AVLTree::rightRotation( Node*& rootPtr){
    Node* newRootPtr = rootPtr->leftPtr;
    rootPtr->leftPtr = newRootPtr->rightPtr;
    newRootPtr->rightPtr = rootPtr;
    rootPtr->height = max(getHeight(rootPtr->leftPtr),getHeight(rootPtr->rightPtr))+ 1;
    newRootPtr->height = max(getHeight(newRootPtr->leftPtr),getHeight(newRootPtr->rightPtr)) + 1;
    rootPtr = newRootPtr;
}
void AVLTree::leftRotation( Node*& rootPtr){
    Node* newRootPtr = rootPtr->rightPtr;
    rootPtr->rightPtr = newRootPtr->leftPtr;
    newRootPtr->leftPtr = rootPtr;
    rootPtr->height = max(getHeight(rootPtr->leftPtr),getHeight(rootPtr->rightPtr))+ 1;
    newRootPtr->height = max(getHeight(newRootPtr->leftPtr),getHeight(newRootPtr->rightPtr)) + 1;
    rootPtr = newRootPtr;
}
void AVLTree::insertHelper(int key, Node*& rootPtr){
    if(rootPtr == nullptr){
        rootPtr = new Node(key);    
    }
    else if(key < rootPtr->key){
        insertHelper(key, rootPtr->leftPtr);
    }
    else if(key > rootPtr->key){
        insertHelper(key, rootPtr->rightPtr);
    }
    else{
        (rootPtr->count)++;
        return;
    }
    balance(rootPtr);
}
void AVLTree::insert(int key){
    insertHelper(key,rootPtr);
}
void AVLTree::remove(int key){
    removeHelper(key,rootPtr);
}
void AVLTree::removeHelper(int key,Node*& rootPtr){
    if(rootPtr == nullptr){
        return;
    }
    else if(key < rootPtr->key){
        removeHelper(key, rootPtr->leftPtr);
    }
    else if(key > rootPtr->key){
        removeHelper(key, rootPtr->rightPtr);
    }
    else if(key == rootPtr->key){ //key is found
        if(rootPtr->count > 1){
            (rootPtr->count)--;
            return;
        }
        if(rootPtr->leftPtr == nullptr && rootPtr->rightPtr == nullptr){
            delete rootPtr;
            rootPtr = nullptr;
        }
        else if(rootPtr->leftPtr == nullptr ){
            Node* del = rootPtr;
            rootPtr = rootPtr->rightPtr;
            delete del;
        }
        else if(rootPtr->rightPtr == nullptr ){
            Node* del = rootPtr;
            rootPtr = rootPtr->leftPtr;
            delete del;
        }
        else{
            int lmRight = findLmNode(rootPtr->rightPtr);
            rootPtr->key = lmRight;
            removeHelper(lmRight, rootPtr->rightPtr); 
        }
    }
    balance(rootPtr);
}
int AVLTree::findLmNode(Node* rootPtr){
    while(rootPtr->leftPtr != nullptr){
            rootPtr = rootPtr->leftPtr;
    }
    return rootPtr->key;
}
int AVLTree::chooseForOther(int key){
    int best = -1;
    findMaxLesserHelper(key,rootPtr,best);
    return best;
}
void AVLTree::findMaxLesserHelper(int key,Node* rootPtr,int& maxLesser){
    if(rootPtr == nullptr){
        return;
    }
    if(rootPtr->key > key){
        findMaxLesserHelper(key,rootPtr->leftPtr,maxLesser);
    }
    else if(rootPtr->key < key){
        maxLesser= rootPtr->key;
        findMaxLesserHelper(key,rootPtr->rightPtr,maxLesser);
    }
}

int AVLTree::findMax(){
    if(rootPtr == nullptr){
        return -1;
    }
    Node* temp = rootPtr;
    while(temp->rightPtr != nullptr){
        temp = temp->rightPtr;
    }
    return temp->key;
}
int AVLTree::findMin(){
    if(rootPtr == nullptr){
        return -1;
    }
    Node* temp = rootPtr;
    while(temp->leftPtr != nullptr){
        temp = temp->leftPtr;
    }
    return temp->key;
}
bool AVLTree::findKeyHelper(int key, Node* rootptr){
    if(rootptr == nullptr){
        return false;
    }
    if(key > rootptr->key){
        return findKeyHelper(key,rootptr->rightPtr);
    }
    else if(key < rootptr->key){
        return findKeyHelper(key,rootptr->leftPtr);
    }
    else{
        return true;
    }
}
bool AVLTree::findKey(int key){
    return findKeyHelper(key,rootPtr);
}


