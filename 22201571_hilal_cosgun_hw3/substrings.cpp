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
#include <algorithm> // only for sort
using namespace std;
long long int mod1 = 1000000007;
long long int mod2 = 1000000009;
bool compare(int* tuple1, int* tuple2) {
    return tuple1[0] < tuple2[0];  // Compare based on the first element
}
int modpower(int x, int y, long long int mod){
    long long result = 1;
    for(int i = 0; i < y; i++){
        result = (result*x) % mod;
    }
    return result % mod;
}
int findMatch(int**& hashes, int length, int hash1, int hash2){
    int low = 0;
    int high = length -1;
    int mid;
    bool match1 = 0;
    while (low <= high) {
        mid  = low + (high - low) / 2;
        if (hashes[mid][0] == hash1){
            match1 = 1;
            break;
        }
        if (hashes[mid][0] < hash1)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if(match1 == 1 && hashes[mid][1] == hash2){
        return hashes[mid][2];
    }
    return -1;
}

long long int hashFunction(char* pattern, int length, long long int mod){
    long long int hash = 0;
    for(int i = 0; i < length; i++){
        hash = (((hash*5) % mod) + (pattern[i] -'a'+1)) % mod;
    }
    return hash;
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
    char text[120000];
    char pattern[120000];
    int numOfPatterns;
    int textLen = 0;

    inputFile.getline(text,sizeof(text));

    textLen = inputFile.gcount() -1;
    inputFile>>numOfPatterns;
    inputFile.ignore();

    int** hashOfPatterns = new int*[numOfPatterns];
    for(int i = 0; i < numOfPatterns; i++){
        hashOfPatterns[i] = new int[3];
    }
    int* countOfPatterns = new int[numOfPatterns];
    for(int i = 0; i < numOfPatterns; i++){
        countOfPatterns[i] = 0;
    }
    int lenCount = 0;
    // take the first pattern to get
    int smallestSize = 1000010;
    for(int i = 0; i < numOfPatterns; i++){
        inputFile.getline(pattern,sizeof(pattern));
        int size = inputFile.gcount() -1;
        if(size<smallestSize){
            smallestSize = size;
        }
        int hash1 = hashFunction(pattern,size,mod1);
        int hash2 = hashFunction(pattern,size,mod2);
        hashOfPatterns[i][0] = hash1;
        hashOfPatterns[i][1] = hash2;
        hashOfPatterns[i][2] = i;

    }
    std::sort(hashOfPatterns, hashOfPatterns+numOfPatterns, compare);
    for(int k = 0; k < 6; k++){ // for each length
        int patLen = smallestSize+k;
        long long power1 = modpower(5,patLen-1,mod1);
        long long power2 = modpower(5,patLen-1,mod2); 
        int index;
        char* first = new char[patLen];
        long long curHash1,curHash2;
        for(int i = 0; i < patLen; i++){
            first[i] = text[i];
        }
        curHash1 = hashFunction(first,patLen,mod1);
        curHash2 = hashFunction(first,patLen,mod2);
        index = findMatch(hashOfPatterns,numOfPatterns,curHash1,curHash2);
        if(index != -1){
            countOfPatterns[index]++;
        }
        for(int i = 0; i < textLen-patLen+1; i++ ){
            curHash1 = (1ll*5*((curHash1 -1ll*(text[i]-'a'+1)*power1) %mod1 + mod1)  + (text[patLen+i]-'a'+1))%mod1;
            curHash2 = (1ll*5*((curHash2 -1ll*(text[i]-'a'+1)*power2) %mod2 + mod2) + (text[patLen+i]-'a'+1))%mod2;
            index = findMatch(hashOfPatterns,numOfPatterns,curHash1,curHash2);
            if(index != -1){
                countOfPatterns[index]++;
            }
        }
        delete[] first;
    }
    for(int i = 0; i < numOfPatterns; i++){
        outputFile<<countOfPatterns[i]<<endl;
    }
    for(int i = 0; i < numOfPatterns; i++){
        delete[] hashOfPatterns[i];
    }
    delete[] hashOfPatterns;
}    

