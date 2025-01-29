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
#include <math.h>
using namespace std;
int mod = 1000000009;
int factorial(int n)
{
    long long result = 1;
    for (int i = 2; i <= n; i++)
        result = (result*i) %mod;

    return result;
}
int modpower(int x, int y, long long int mod){
    if(y == 0){
        return 1;
    }
    int result = modpower(x,y/2,mod);
    result = (1ll*result*result) % mod;
    if(y % 2 == 1){
        result = (1ll*result*x)% mod;
    } 
    return result % mod;
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
    int tableSize;
    int num;
    int validCount = 0;
    if(!(inputFile>>tableSize)){
        return 1;
    }
    int* hashTable = new int[tableSize];
    for(int i = 0; i < tableSize; i++){
        if(!(inputFile>>num)){
            return 1;
            
        }
        hashTable[i] = num;
        if(num!=-1){
            validCount++;
        }
    } 
    int* before = new int[tableSize];
    for(int i = 0; i < tableSize; i++){
            before[i] = 0; 
    }
    int actualPlace = -1;
    int isPossible = 1;
    for(int i = 0; i < tableSize; i++){
        if(hashTable[i] != -1){
            actualPlace = hashTable[i] % (tableSize);
            if(actualPlace == i){
                before[i] = 0;
            }
            else if((actualPlace+1) % tableSize == i){
                before[i] = 1 + before[actualPlace];

            }
            else if((actualPlace+2) % tableSize == i){
               before[i] = 2;
            }   
     }
    }
    int powers[3];
    powers[0] = modpower(6,mod-2,mod);
    powers[1] = modpower(3,mod-2,mod);
    powers[2] = modpower(2,mod-2,mod);
   long long result = factorial(validCount) ;
    for(int i = 0; i < tableSize; i++){
       if(before[i] == 2){
        if(before[(i-1+tableSize)%tableSize] == 1){
            result = (result*powers[0]) % mod;
            before[i] = -1;
            before[(i-1 +tableSize)%tableSize] = -1;
            before[(i-2 +tableSize)%tableSize] = -1;

        }
        else if(before[(i-1)%tableSize] == 0){
            result = (result*powers[1]) %mod;
        }
       }
    }
    for(int i = 0; i < tableSize; i++){
       if(before[i] == 1){
            result = (result*powers[2]) % mod;
            before[i] = -1;
            before[(i-1 +tableSize)%tableSize] = -1;
        }
    }
    outputFile<<result;
    delete[] hashTable;
    delete[] before;
}
