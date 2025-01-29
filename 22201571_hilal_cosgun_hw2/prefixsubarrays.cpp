/**
* Title: Question 3
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 2 
*/
#include <iostream>
#include <fstream>
#include "AVLTree.h"
using namespace std;
bool isGreater(int A[], int B[], int L, int M){
    AVLTree treeA;
    AVLTree treeB;
    if(L < M){
        return false;
    }
    for(int i = 0; i < M; i++){
        treeA.insert(A[i]);
        treeB.insert(B[i]);
    }
    for(int i = M ; i < L; i++){ 
        int minA = treeA.findMin();
        if(A[i] > minA){
            treeA.remove(minA);
            treeA.insert(A[i]);
        }
        int maxB = treeB.findMax();
        if(B[i] < maxB){
            treeB.remove(maxB);
            treeB.insert(B[i]);
        }
    }
    for(int i = 0; i < M; i++){
        int minA = treeA.findMin();
        int minB = treeB.findMin();
        if(minA <= minB ){
            return false;
        }
        treeA.remove(minA);
        treeB.remove(minB);
    }
    return true;
}

int main(int argc, char* argv[]){ //
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
    int num;
    if(!(inputFile>>N>>M)){
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
    int output = N+1;
    //binary search approach to find minimum valid L. Because it is efficient than incrementing L 1 by 1.
    int low = 0; //minimum length
    int high = N; // max length
    while (low <= high ) { 
        int L = low + (high - low) / 2;
        if (isGreater(arrayA,arrayB,L,M)){
            if(L < output){
                output = L;
            }
            high = L-1;
        }
        else{
            low = L+1;
        }
    }
    outputFile<<output;
}


 
