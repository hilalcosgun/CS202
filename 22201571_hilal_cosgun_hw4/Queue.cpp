/**  
 * Title: Array Based Circular Queue Implementation 
 * Author : Hilal Cosgun
 * ID: 22201571 
 * Section : 1 
 * Homework : 4 
 */
#include <iostream>
#include "Queue.h"
using namespace std;

Queue::Queue(int capacity){
    first = 0;
    this->capacity = capacity;
    arr = new edge[capacity];
    count = 0;
}
Queue::~Queue(){
    delete[] arr;
}
bool Queue::isEmpty() const{
    return count==0;
}
void Queue::enqueue(int from, int to, int cost){
    if(count < capacity){
        int ind = (first + count) %capacity;
        arr[ind].from = from;
        arr[ind].to = to;
        arr[ind].cost = cost;
        count++; 
    }  
    
}
void Queue::dequeue(){
    if(!isEmpty()){
        first = (first +1) % capacity;
        count--;
    }
    
}
edge Queue::peekFirst() const{
    return arr[first];
}
int Queue::getCount() const{
    return count;
}
