/**  
 * Title: Array Based Circular Queue Header 
 * Author : Hilal Cosgun
 * ID: 22201571 
 * Section : 1 
 * Homework : 4 
 */
#include <iostream>
using namespace std;
 struct edge{
        int from;
        int to;
        int cost;

        edge(int f, int t, int c){
            from = f;
            to = t;
            cost = c;
        }
        edge() : from(-1), to(-1), cost(0){};
 };
class Queue{
    private:
        edge* arr; 
        int count;
        int capacity;
        int first;
    public:
        Queue(int capacity);
        ~Queue();
        bool isEmpty() const;
        void enqueue(int from, int to, int cost);
        void dequeue();
        edge peekFirst() const;
        int getCount() const;

};