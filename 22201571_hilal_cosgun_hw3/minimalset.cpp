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
#include <algorithm> //only for sort

using namespace std;
int reverseCount, minimalSubsetSize, i,j,k,a,b,c,n, countLeft, countRight;
bool visited[100005] = {0};
int mod2 = 100000007;
int mod1 = 100000009;
int base = 32;
bool compare(int* tuple1, int* tuple2) {
    return tuple1[0] < tuple2[0];  // Compare based on the first element
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
        return mid;
    }
    return -1;
}

long long hashFunction(char* pattern, int length, long long int mod){
    long long hash = 0;
    for(int i = 0; i < length; i++){
        hash = (((hash*base) % mod) + (pattern[i] -'a'+1)) % mod;
    }
    return hash;
}
long long modpower(long long x, long long y, long long int mod){
    if(y == 0){
        return 1;
    }
    long long  result = modpower(x,y/2,mod);
    result = (1ll*result*result) % mod;
    if(y % 2 == 1){
        result = (1ll*result*x)% mod;
    } 
    return result % mod;
}
long long shift(int hash, char first, int length, long long mod) {
    long long power = modpower(base,length-1,mod);
    return (1ll*base*((hash - 1ll*(first-'a'+1)*power) %mod +mod) + (first-'a'+1))%mod;

}
void reverseHash(char* pattern, int length, long long& hash1, long long&hash2){
    char* p = new char[length];
    for(int i = 0; i < length; i++){
        p[i] = pattern[length-i-1];
    }
    hash1 = hashFunction(p,length,mod1);
    hash2 = hashFunction(p,length,mod2);
    delete[] p;
}
int main(int argc, char *argv[]){
    fstream inputFile(argv[1]);
    if(!inputFile.is_open()){
        return 1;
    }
    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        return 1;
    }
    int numOfPatterns;

    inputFile>>numOfPatterns;
    inputFile.ignore();
    char pattern[100100];
    int** hashOfPatterns = new int*[numOfPatterns];
    char** patterns = new char*[numOfPatterns];

    for(int i = 0; i < numOfPatterns; i++){
        hashOfPatterns[i] = new int[5];
    }
    for(int i = 0; i < numOfPatterns; i++){
        inputFile.getline(pattern,sizeof(pattern));
        int size = inputFile.gcount();
        if(!inputFile.eof()){
            size = size-1;
        }
        patterns[i] = new char[size];
        for(int j = 0; j < size; j++){
            patterns[i][j] = pattern[j];
        }
        long long hash1 = hashFunction(pattern,size,mod1);
        long long hash2 = hashFunction(pattern,size,mod2);
        int visited = 0;
        hashOfPatterns[i][0] = hash1;
        hashOfPatterns[i][1] = hash2;
        hashOfPatterns[i][2] = i;
        hashOfPatterns[i][3] = size;
        hashOfPatterns[i][4] = visited;
    }
    long long newHash1, newHash2;
    std::sort(hashOfPatterns, hashOfPatterns+numOfPatterns, compare);

    for( int i = 0; i < numOfPatterns; i++ ){
         if( !hashOfPatterns[i][4] ){
             minimalSubsetSize++;
             hashOfPatterns[i][4] = 1;
             countLeft = countRight = 0;
             countLeft++;
             int length = hashOfPatterns[i][3];
                newHash1 = hashOfPatterns[i][0];
                newHash2 = hashOfPatterns[i][1];
             for( int j = 0; j < length-1 ; j++ ){
                newHash1 = shift(newHash1,patterns[(hashOfPatterns[i][2])][j],length,mod1);
                newHash2 = shift(newHash2,patterns[(hashOfPatterns[i][2])][j],length,mod2);
                  int ind = findMatch(hashOfPatterns,numOfPatterns,newHash1,newHash2);
                  if ( ind != -1 && !hashOfPatterns[ind][4]){
					  hashOfPatterns[ind][4] = 1;
					  countLeft++;

				}  
		     }
		    reverseHash(patterns[(hashOfPatterns[i][2])],length,newHash1,newHash2);
		      for( int j = 0; j < length; j++){
                  int ind = findMatch(hashOfPatterns,numOfPatterns,newHash1,newHash2);
                  if ( ind != -1  && !hashOfPatterns[ind][4]){
					  hashOfPatterns[ind][4] = 1;
					  countRight++;
				  }
				  newHash1 = shift(newHash1,patterns[(hashOfPatterns[i][2])][length-j-1],length,mod1);
                  newHash2 = shift(newHash2,patterns[(hashOfPatterns[i][2])][length-j-1],length,mod2);
		     }
		     reverseCount+= min ( countLeft, countRight );
		 }
		 
		 
    
    
    }
    outputFile<<reverseCount<<endl;
    outputFile<<minimalSubsetSize<<endl;
    for(int i = 0; i < numOfPatterns; i++){
        delete[] hashOfPatterns[i];
        delete[] patterns[i];
    } 
    delete hashOfPatterns;
    delete patterns;
}
