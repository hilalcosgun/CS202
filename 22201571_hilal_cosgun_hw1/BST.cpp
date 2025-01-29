/**
* Title: Binary Search Tree 
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 1
* Description : A linked base BST implementation with additional methods.
*/
#include <iostream>
#include "BST.h"

using namespace std;
BST::BST(){
    rootPtr = nullptr;
    size = 0;
}
BST::BST(int keys[], int size){
    rootPtr = nullptr;
    this->size = size;
    for(int i = 0; i < size; i++){
        insertHelper(keys[i],rootPtr);
    } 
    cout<<"BST with size "<<size<<" is created."<<endl;
} 
BST::~BST(){
    clear(rootPtr);
}
void BST::clear(Node* rootPtr){
    if(rootPtr == nullptr){
        return;
    }
    clear(rootPtr->leftPtr);
    clear(rootPtr->rightPtr);
    delete rootPtr;
}
void BST::insertKey(int key){
    bool success = insertHelper(key, this->rootPtr);
    if(success){
        cout<<"Key "<< key <<" is added."<<endl;
        size++;
    }
    else{
        cout<<"Key "<< key <<" is not added. It exists!"<<endl;
    }
    
}
void BST::insertforAnalysis(int key){
    insertHelper(key, this->rootPtr);
}
bool BST::insertHelper(int key, Node*& rootPtr){
    if(rootPtr == nullptr){
        rootPtr = new Node(key);
        return true;
    }
    else if(key == rootPtr->key){
        return false;
    }
    else if(key < rootPtr->key){
        return insertHelper(key, rootPtr->leftPtr);
    }
    else if(key > rootPtr->key){
        return insertHelper(key, rootPtr->rightPtr);
    }
    return false; 
}
void BST::deleteKey(int key){
    bool success = deleteHelper(key,this->rootPtr);
    if(success){
        cout<<"Key "<< key <<" is deleted."<<endl;
        return;
    }
    cout<<"Key "<< key <<" is not deleted. It does not exist!"<<endl;
}
bool BST::deleteHelper(int key, Node*& rootPtr){
    if(rootPtr == nullptr){
        return false;
    }
    else if(key < rootPtr->key){
        deleteHelper(key, rootPtr->leftPtr);
    }
    else if(key > rootPtr->key){
        deleteHelper(key, rootPtr->rightPtr);
    }
    else if(key == rootPtr->key){ //key is found
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
            Node* lmRight = findLmNode(rootPtr->rightPtr);
            rootPtr->key = lmRight->key;
            deleteHelper(lmRight->key, rootPtr->rightPtr); 
        }
        size--;
        return true;
    }
    return false;
}
Node* BST::findLmNode(Node* rootPtr){
    while(rootPtr->leftPtr != nullptr){
            rootPtr = rootPtr->leftPtr;
    }
    return rootPtr;
}
void BST::displayInorder(){
    if(rootPtr == nullptr){
        cout<<"The tree is empty."<<endl;
        return;
    }
    int index = 0;
    NodeQueue q;
    inOrderHelper(q,rootPtr);
    cout<<"Inorder display is: ";
    q.toString();
    cout<<endl;
}
void BST::inOrderHelper(NodeQueue& q,Node* rootPtr){
    if(rootPtr == nullptr){
        return;
    }
    else{
        inOrderHelper(q,rootPtr->leftPtr);
        q.enqueue(rootPtr);
        inOrderHelper(q,rootPtr->rightPtr);
    }
}
void BST::findFullBTLevel(){
    if(rootPtr == nullptr){
        cout<<"The tree is empty.";
        return;
    }
    NodeQueue q;
    q.enqueue(rootPtr);
    int level = 1;
    bool isLevelFull = true;
    while(!q.isEmpty() & isLevelFull){
        int repeat = q.getCount();
        for(int i = 0; i < repeat ; i++){
            Node* temp = q.peekFront();
            if(temp->leftPtr == nullptr || temp->rightPtr == nullptr){
                isLevelFull = false;
            }
            q.enqueue(temp->leftPtr);
            q.enqueue(temp->rightPtr);
            q.dequeue();
        }
        if(isLevelFull){
            level++;  
        }  
    }
    cout<<"Full binary tree level is: "<<level<<endl;
}
Node* BST::LCAHelper(int A, int B, Node* rootPtr){
    if(A < rootPtr->key & B < rootPtr->key){
        return LCAHelper(A,B,rootPtr->leftPtr);
    }
    else if(A > rootPtr->key & B > rootPtr->key){
        return LCAHelper(A,B,rootPtr->rightPtr);
    }
    else{
        return rootPtr;
    }
}
void BST::lowestCommonAncestor(int A, int B){
    if(!isExist(A,rootPtr) || !isExist(B,rootPtr)){
        cout<<"Error: One or both keys (A, B) do not exist in the tree."<<endl;
        return;
    }
    cout<<"Lowest common ancestor of "<<A<<" and "<<B<<" is: ";
    cout<<LCAHelper(A,B,rootPtr)->key<<endl; 
}
void BST::maximumSumPath(){
    if(rootPtr == nullptr){
        cout<<"The tree is empty."<<endl;
    }
    NodeQueue q;
    maximumSumHelper(q, rootPtr);
    cout<<"Maximum sum path is: ";
    q.toStringReverse();
    cout<<endl;
}
int BST::maximumSumHelper(NodeQueue& maxPathSoFar, Node*rootPtr){
    int sum = 0;
    NodeQueue rightPath;
    NodeQueue leftPath;
    if(rootPtr == nullptr){
        return 0;
    }
    sum += rootPtr->key;
    int leftMaxSum = maximumSumHelper(leftPath,rootPtr->leftPtr);    
    int rightMaxSum = maximumSumHelper(rightPath,rootPtr->rightPtr);
    if(leftMaxSum >= rightMaxSum){
        sum += leftMaxSum;
        maxPathSoFar = leftPath;
        maxPathSoFar.enqueue(rootPtr);
    }
    else{
        sum += rightMaxSum;
        maxPathSoFar = rightPath;
        maxPathSoFar.enqueue(rootPtr);
    }
    return sum;
}
void BST::maximumWidth(){
    if(rootPtr == nullptr){
        cout<<"The tree is empty."<<endl;
        return;
    }
    cout<<"Maximum level is: ";
    int maxWidth = -1;
    NodeQueue q;
    if(rootPtr == nullptr){
        return;
    }
    q.enqueue(rootPtr);
    maxWidth = 1;
    NodeQueue maxQ;
    while(!q.isEmpty()){
        int repeat = q.getCount();
        for(int i = 0; i < repeat ; i++){
            Node* temp = q.peekFront();
            if(temp->leftPtr != nullptr){
                q.enqueue(temp->leftPtr);
            }
            if(temp->rightPtr != nullptr){
                q.enqueue(temp->rightPtr);
            }
            q.dequeue();
        }
        if(q.getCount() > maxWidth){
            maxWidth = q.getCount();
            maxQ = q;
        } 
    } 
    q.toString(); 
    maxQ.toString();
    cout<<endl;
}
void BST::pathFromAtoB(int A, int B){
    if(!isExist(A,rootPtr) || !isExist(B,rootPtr)){
        cout<<"Error: One or both keys (A, B) do not exist in the tree."<<endl;
        return;
    }
    cout<<"Path from "<<A<<" to "<<B<<" is: ";
    Node* lca = LCAHelper(A,B, rootPtr);
    NodeQueue aToLca;
    NodeQueue bToLca;
    pathHelper(aToLca,A,lca);
    pathHelper(bToLca,B,lca);
    aToLca.toStringReverse();
    bToLca.dequeue();
    if(bToLca.isEmpty()){
        cout<<endl;
        return;
    }
    cout<<", ";
    bToLca.toString();
    cout<<endl;
}
void BST::pathHelper(NodeQueue& path, int key, Node* rootPtr){
    if(rootPtr == nullptr){
        return;
    }
    path.enqueue(rootPtr);
    if(key < rootPtr->key){
        pathHelper(path,key,rootPtr->leftPtr);
    }
    if(key > rootPtr->key){
        pathHelper(path,key,rootPtr->rightPtr);
    }
    else{
        return;
    }
}
int BST::findHeightHelper(Node* rootPtr){
    if(rootPtr == nullptr){
        return 0;
    }
    int leftHeight = findHeightHelper(rootPtr->leftPtr);
    int rightHeight = findHeightHelper(rootPtr->rightPtr);
    return 1+ max(leftHeight,rightHeight);
}
int BST::findHeight(){
    return findHeightHelper(rootPtr);
}
bool BST::isExist(int key, Node* rootPtr){
    if(key == rootPtr->key){
        return true;
    }
    else if(key < rootPtr->key){
        return isExist(key, rootPtr->leftPtr);
    }
    else if(key > rootPtr->key){
        return isExist(key, rootPtr->rightPtr);
    }
    return false;
}