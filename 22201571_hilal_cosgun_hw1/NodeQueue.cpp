/**
* Title: Queue with BST Nodes
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 1
* Description : A linked based queue implementation consisting of BST nodes
*/
#include <iostream>
#include "NodeQueue.h"
using namespace std;

NodeQueue::NodeQueue(){
    front = nullptr;
    back = nullptr;
    count = 0;
    
}
NodeQueue::~NodeQueue(){
    while(!isEmpty()){
        dequeue();
    }
}
bool NodeQueue::isEmpty() const{
    return front == nullptr;
}
void NodeQueue::enqueue(Node* node){
    if(node == nullptr){
        return;
    }
    ListNode* newPtr = new ListNode(node);
    if(isEmpty()){
        front = back = newPtr;
    }
    else{
        back->next = newPtr;
        back = newPtr;
    }
    count++;
}
void NodeQueue::dequeue(){
    if(!isEmpty()){
        ListNode* temp = front;
        front = front->next;
        count--;
        if(front == nullptr){
            back = nullptr;
        }
        delete temp;
    }
}
Node* NodeQueue::peekFront() const{
    if(isEmpty()){
        return nullptr;
    }
    return front->BSTnode;
}
int NodeQueue::getCount() const{
    return count;
}
void NodeQueue::toString() const{
    ListNode* curNode = front;
    while(curNode != nullptr){
        if(curNode != back){
            cout<<curNode->BSTnode->key<<", ";
        }
        else{
            cout<<curNode->BSTnode->key;
        }
        curNode = curNode->next;
    }    
}
void NodeQueue::toStringReverse() const{ 
    int keys[count];
    int i = 0;
    ListNode* curNode = front;
    while(curNode != nullptr){
        keys[i] = curNode->BSTnode->key;
        i++;
        curNode = curNode->next;
    }  
    for(int k = count-1; k > 0; k--){
        cout<<keys[k]<<", ";
    }
    cout<<keys[0];
}
void NodeQueue::operator=(const NodeQueue& other){
    if(this == &other){
        return;
    }
    while(!isEmpty()){
        dequeue();
    }
    ListNode* curPtr = other.front;
    while(curPtr != nullptr){
        enqueue(curPtr->BSTnode);
        curPtr = curPtr->next;
    }
}
