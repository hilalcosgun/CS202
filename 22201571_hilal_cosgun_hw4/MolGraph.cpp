/**  
 * Title: Molecule Graph Implementation 
 * Author : Hilal Cosgun
 * ID: 22201571 
 * Section : 1 
 * Homework : 4 
 */
#include <iostream>
#include <fstream>
#include "MolGraph.h"
#include "Queue.h"
using namespace std;
bool compare(int edge1[2], int edge2[2]){
    if(edge1[0] < edge2[0]){
        return 1;
    }
    else if(edge1[0] == edge2[0]){
        return edge1[1] < edge2[1];
    }
    return 0;
}
MolGraph::MolGraph(const std::string& filename){
    ifstream file(filename);
    file >> numOfAtoms;
    adjList = new int*[numOfAtoms];
    adjCounts = new int[numOfAtoms];
    int id;
    int adjCount;
    int adjID;
    for(int i = 0; i < numOfAtoms; i++){
        file >> id;
        file >> adjCount;
        adjCounts[i] = adjCount;
        adjList[i] = new int[adjCount];
        for(int j = 0; j < adjCount; j++){
            file >> adjID;
            adjList[i][j] = adjID;

        }
    } 

}
MolGraph::~MolGraph(){
    for(int i = 0; i < numOfAtoms; i++){
        delete[] adjList[i];
    }
    delete[] adjList;
    delete[] adjCounts;
    numOfAtoms = 0;
}
int** MolGraph::BFSToAllVertices(int source, int dest){
    Queue q(numOfAtoms);
    bool isVisited[numOfAtoms];
    int** pathAndCost = new int*[numOfAtoms];
    for(int i = 0; i < numOfAtoms; i++){
        isVisited[i] = false;
        pathAndCost[i] = new int[2];
        pathAndCost[i][0] = -1;
        pathAndCost[i][1] = -1;
    }
    for(int i = 0; i < adjCounts[source]; i++){
        q.enqueue(source,adjList[source][i],1);
        isVisited[source] = 1;

    }
    while(!q.isEmpty()){
        int from = q.peekFirst().from;
        int to = q.peekFirst().to;
        int cost = q.peekFirst().cost;
        q.dequeue();
        if(isVisited[to]){
            continue;
        }      
        pathAndCost[to][0] = from;
        pathAndCost[to][1] = cost; 
        isVisited[to] = true;
        if(to==dest){
            return pathAndCost;
        } 
        for(int i = 0; i < adjCounts[to]; i++){
            q.enqueue(to,adjList[to][i],cost+1);
        }
    }
    return pathAndCost;
}
void MolGraph::minBondPath(int source, int destination){
    int** pathsAndCost = BFSToAllVertices(source,destination);
    int cost = pathsAndCost[destination][1];
    if(cost == -1){
        cout<<"No path is found";
        return;
    }
    cout<<"Minimum number of bonds to traverse from atom "<<source<<" to atom "<<destination<<": "<<cost<<endl;
    int* path = new int[cost];
    int i = 0;
    for(int vertix = destination; vertix!= source; vertix = pathsAndCost[vertix][0]){
        path[i] = vertix;
        i++;
    }
    cout<<"Path: "<<source<<" -> ";
    for(int i = cost-1; i > 0; i--){
        cout<<path[i]<<" -> ";
    }
    cout<<path[0]<<endl;
    for(int i = 0; i < numOfAtoms; i++){
        delete[] pathsAndCost[i];
    }
    delete[] pathsAndCost;
    delete[] path;
  
}
void MolGraph::getDiameter(){
    int max = -1;
    for(int i = 0; i < numOfAtoms; i++){
        int** pathsAndCost = BFSToAllVertices(i,-1);
        for(int j = 0; j < numOfAtoms; j++){
            if(pathsAndCost[j][1] > max){
                max = pathsAndCost[j][1];
            }
        }
        if(max == numOfAtoms-1){
            cout<<"Diameter of the molecule: "<<max<<endl;
            for(int i = 0; i < numOfAtoms; i++){
                delete[] pathsAndCost[i];
            }
            delete[] pathsAndCost;
            return;
        }
        for(int i = 0; i < numOfAtoms; i++){
            delete[] pathsAndCost[i];
        }
        delete[] pathsAndCost;
    }
    cout<<"Diameter of the molecule: "<<max<<endl;   
}
void MolGraph::getMST(){
    int** pathsAndCost = BFSToAllVertices(0,-1);
    int edges[numOfAtoms-1][2];
    int smaller, larger;
    cout<<"Minimum Spanning Tree:"<<endl;
    cout<<"Cost: "<<numOfAtoms-1<<endl;
    cout<<"Edges:"<<endl;
    for(int i = 1; i < numOfAtoms; i++){
        smaller = pathsAndCost[i][0];
        larger = i;
        if(smaller > larger){
            larger = smaller;
            smaller = larger; 
        }
        edges[i-1][0] = smaller;
        edges[i-1][1] = larger;
    }
    for (int i = 0; i < numOfAtoms - 2; i++) {
        for (int j = 0; j < numOfAtoms-i-2; j++) {
            if (!compare(edges[j],edges[j+1])) {
                int temp0 = edges[j][0];
                int temp1 = edges[j][1];
                edges[j][0] = edges[j+1][0];
                edges[j][1] = edges[j+1][1];
                edges[j+1][0] = temp0;
                edges[j+1][1] = temp1;
            }
        }
    }
    for (int i = 0; i < numOfAtoms-1; i++) {
        cout << edges[i][0] << " - " << edges[i][1] << endl;
    }
    for(int i = 0; i < numOfAtoms; i++){
        delete[] pathsAndCost[i];
    }
    delete[] pathsAndCost;
}
