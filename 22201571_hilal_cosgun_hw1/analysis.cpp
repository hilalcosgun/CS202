/**
* Title: BST Insertion Analysis 
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 1
* Description : Analyzes the height and time complexity of random insertions into a BST
*/
#include "analysis.h"
#include <iostream>
#include <ctime>
using namespace std;
void analysis::timeAnalysis(){
    srand(time(NULL));
    BST b;
    int arr[10000];
    clock_t start, stop;
    for(int i = 0; i < 10000 ; i++){
        arr[i] = rand();
    }
    for(int i = 1; i <= 10; i++){
        cout<<"Round "<<i<<":"<<endl;
        start = clock();
        for(int j = 0; j < 1000; j++){
            b.insertforAnalysis(arr[1000*(i-1)+j]);
        }
        stop = clock();
        cout<<"Elapsed time: "<< (stop - start) / (double)CLOCKS_PER_SEC<<endl;
        cout<<"Height: "<<b.findHeight()<<endl;
    }

}