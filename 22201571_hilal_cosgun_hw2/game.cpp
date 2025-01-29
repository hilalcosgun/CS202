/**
* Title: Question 2
* Author : Hilal Cosgun
* ID: 22201571
* Section : 1
* Homework : 2 
*/
#include <iostream>
#include <fstream>
#include "AVLTree.h"
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
    int size;
    int num;  
    if(!(inputFile >> size)){
        return 1;
    }
    AVLTree bobo;
    AVLTree holo;
    int boboScore = 0;
    int holoScore = 0;
    for(int i = 0; i < size; i++){
        if(!(inputFile >> num)){
            return 1;
        }
        bobo.insert(num);
    }
    for(int i = 0; i < size; i++){
        if(!(inputFile >> num)){
            return 1;
        }
        holo.insert(num);
    }
    bool done = false;
    for(int i = 1; i <= size &&!done; i++){
        int boboCard;
        int holoCard;
        
        if(i % 2 == 1){
            boboCard = bobo.findMax();
            holoCard = holo.chooseForOther(boboCard);
        }
        else{
            holoCard = holo.findMax();
            boboCard = bobo.chooseForOther(holoCard);
        }
        if(boboCard == -1){
            boboScore = boboScore+size-i+1; // holo wins all other rounds.
            done = true;
        }
        else if(holoCard == -1){
            holoScore = holoScore+size-i+1;
            done = true;
        }
        else{
            bobo.remove(boboCard);
            holo.remove(holoCard);
            if(boboCard>holoCard){
                boboScore++;
            }
            else{
                holoScore++;
            }
        }
    }
    outputFile<<boboScore<<" "<<holoScore; 
}