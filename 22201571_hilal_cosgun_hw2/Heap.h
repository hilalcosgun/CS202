/**
* Title: Heap Header
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 2 
*/
#ifndef HEAP_H
#define HEAP_H
#include<iostream>
using namespace std;
class Heap
{
private:
    int* array;
    int size;
    int count;
    int findMin(int x, int y);
public:
    Heap(int size);
    ~Heap();
    void heapRebuild(int rootIndex);
    void removeRoot();
    int peekRoot();
    void insert(int key);
    void findLeast5(int* least5);
};
#endif
