/**
* Title: Heap Implementation
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 2 
*/
#include<iostream>
#include "Heap.h" 
using namespace std;
Heap::Heap(int size){
    this->size = size;
    array = new int[size];
    count = 0;

}
Heap::~Heap(){
    delete[] array;
}
void Heap::removeRoot(){
    if(count == 0){
        return;
    }
    array[0] = array[count-1];
    count--;
    heapRebuild(0);
}
int Heap::peekRoot(){
    return array[0];
}
void Heap::insert(int key){
    if(count == size){
        return;
    }
    array[count] = key;
    int insertedInd = count;
    count++;
    bool done = false;
    while(!done){
        if(insertedInd <= 0){
            return;
        }
        int parentInd = (insertedInd-1)/2;
        if(key < array[parentInd]){
            array[insertedInd] = array[parentInd];
            insertedInd = parentInd;
        }
        else{
            done = true;
        }
        array[insertedInd] = key;
    }    
}
void Heap::heapRebuild(int rootIndex){
    int leftInd = rootIndex*2+1;
    int rightInd = rootIndex*2+2;
    if(leftInd >= count & rightInd >= count){
        return;
    }
    int smallerInd = leftInd;
    if(rightInd < count){
        if(array[rightInd] < array[leftInd]){
            smallerInd = rightInd;
        }
    }
    if(array[smallerInd] < array[rootIndex]){
        int temp = array[rootIndex];
        array[rootIndex] = array[smallerInd];
        array[smallerInd] = temp;
    }
    heapRebuild(smallerInd);
}
int Heap::findMin(int x, int y){
    if(x < y){
        return x;
    }
    return y;
}
void Heap::findLeast5(int* least5){
    if(count < 5){
        least5[0] = -1;
        return;
    }
    //only the first 5 levels need to be checked. least 5 elementh cannot be in the 6th level and below.
    least5[0] = array[0]; //root is always the minimum
    int arrSize = findMin(count,31)-1;
    int tempArr[arrSize];
    for(int i = 0; i < arrSize; i++){
        tempArr[i] = array[i+1];
    }
    for (int i = 0; i < 4; i++) {
        int minIndex = i;
        for (int j = i + 1; j < arrSize; j++) {
            if (tempArr[j] <= tempArr[minIndex]) {
                minIndex = j; 
            }
        }
        least5[i+1] = tempArr[minIndex];
        tempArr[minIndex] = tempArr[i];
        
    }
}
    

