/**
* Title: Hashing
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 3
* 
*/
#include <iostream>
#include <fstream>
#include <climits>
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
    int tableSize;
    int num;
    int validCount = 0;
    if(!(inputFile>>tableSize)){
        return 1;
    }
    int* hashTable = new int[tableSize];
    for(int i = 0; i < tableSize; i++){
        if(!(inputFile>>num)){
            delete[] hashTable;
            return 1;
        }
        hashTable[i] = num;
        if(num != -1){
            validCount++;
        }
    } 
    int** isBefore = new int*[tableSize];
    for(int i = 0; i < tableSize; i++){
        isBefore[i] = new int[tableSize]{};
    }
    int* before = new int[tableSize]{};
    int* order = new int[validCount];
    int actualPlace = -1;
    for(int i = 0; i < tableSize; i++){
        if(hashTable[i] != -1){
            actualPlace = hashTable[i] % (tableSize);
            for(int j = actualPlace; j != i; j= (j+1) % tableSize){
                if(hashTable[j] != -1){
                    isBefore[j][i] = 1;
                }
                before[i]++; 
            }
        }   
    }
    bool isPossible = 1;
    int placedCount = 0; 
    while(placedCount < validCount){
        int smallest = INT_MAX;
        int smallestInd = -1;
        for(int i = 0; i < tableSize; i++){
            if(hashTable[i]!=-1 && before[i] == 0){
                if(hashTable[i] < smallest ){
                    smallest = hashTable[i];
                    smallestInd = i;
                }
            }
        }
        if(smallestInd == -1){
            isPossible = 0;
            break;
        }
        before[smallestInd] = -1;
        order[placedCount] = hashTable[smallestInd];
        placedCount++;
        for(int k = 0; k < tableSize; k++){
            if(isBefore[smallestInd][k] == 1){
                isBefore[smallestInd][k] = 0;
                before[k]--;
            }
        }
    }
    if(isPossible == 1){
        for(int i = 0; i < validCount-1; i++){
            outputFile<<order[i]<<" ";
        }
        outputFile<<order[validCount-1];
    }
    else{
        outputFile<<"Impossible";
    }
    delete[] hashTable;
    delete[] before;
    delete[] order;
    for(int i = 0; i < tableSize; i++){
        delete[] isBefore[i]; 
    }
}
