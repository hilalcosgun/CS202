/**
* Title: Question 4
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 2 
*/
#include <iostream>
#include <fstream>
#include "AVLTree.h"
using namespace std;
bool isGreater(int A[], int B[], int start, int stop,int M,int K){
    AVLTree treeA;
    AVLTree treeB;
    for(int i = start; i < start+M; i++){
        treeA.insert(A[i]);
    }
    for(int i = start+M ; i < stop; i++){
        int minA = treeA.findMin();
        if(A[i] > minA){
            treeA.remove(minA);
            treeA.insert(A[i]);
        }
    }
    for(int i = start; i < start+K; i++){
        treeB.insert(B[i]);
    }
    for(int i = start+K; i < stop; i++){
        int maxB = treeB.findMax();
        if(B[i] < maxB){
            treeB.remove(maxB);
            treeB.insert(B[i]);
        }
    }
    if(treeA.findMin() > treeB.findMax()){
        return true;
    }
    return false;
}
int main(int argc, char* argv[]){ 
    fstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        return 1;
    }
    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        return 1;
    }
    int N;
    int M;
    int K;
    int num;
    if(!(inputFile>>N>>M>>K)){
        return 1;
    }
    int arrayA[N];
    int arrayB[N];
    for(int i = 0; i < N; i++){
        if(!(inputFile >> num)){
            return 1;
        }
        arrayA[i] = num;
    }
    for(int i = 0; i < N; i++){
        if(!(inputFile >> num)){
            return 1;
        }
        arrayB[i] = num;
    }
    int start = 0; 
    int stop = M;
    int output = N+1;
    while (stop-start >= M && stop <= N) { //sliding window model(at least what i tried to do)
        if (isGreater(arrayA,arrayB,start,stop,M,K)){
            if(stop-start < output){
                output = stop-start;
            }
            start++;
        }
        else{
            stop++;
        }
    }
    outputFile<<output;
    return 0;
};

 
