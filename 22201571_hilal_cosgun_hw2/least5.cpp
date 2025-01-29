/**
* Title: Question 1
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 2 
*/
#include <iostream>
#include <fstream>
#include "Heap.h"
using namespace std;
int main(int argc, char* argv[]){
    fstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        return 1;
    }
    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        return 1;
    }
    int actionNum;
    if(!(inputFile >> actionNum)){
        return 1;
    }
    Heap myHeap(actionNum);
    for(int i = 0; i < actionNum; i++){
        char c;
        int key;
        if(!(inputFile >> c)){
            return 1;
        }
        if(c == 'a'){
            if(!(inputFile >> key)){
                return 1;
            }
            myHeap.insert(key);
        }
        else if(c == 'r'){
            myHeap.removeRoot();
        }
        else if(c == 'g'){
            int least5[5];
            myHeap.findLeast5(least5);
            if(least5[0] != -1){
                for(int i = 0; i < 5; i++){
                    outputFile<<least5[i]<<endl;
                }
            }
            else{
                outputFile<<-1<<endl;
            }
        }
    }
}