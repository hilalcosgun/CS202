/**
* Title: Queue with BST Nodes
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 1
* Description : A linked based queue implementation consisting of BST nodes
*/
#ifndef NODEQUEUE_H
#define NODEQUEUE_H
#include "Node.h"
#include <iostream>
using namespace std;
class NodeQueue{
    private:
        struct ListNode{
            Node* BSTnode;
            ListNode* next;
            ListNode(Node* Bstnode) : BSTnode(Bstnode), next(nullptr){};
        };
        ListNode* front;
        ListNode* back;
        int count;
    public:
        NodeQueue();
        ~NodeQueue();
        void operator=(const NodeQueue& other);
        bool isEmpty() const;
        void enqueue(Node* node);
        void dequeue();
        Node* peekFront() const;
        int getCount() const;
        void toString() const;
        void toStringReverse() const;

};
#endif
