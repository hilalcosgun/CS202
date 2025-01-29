/**  
 * Title: Molecule Graph Header 
 * Author : Hilal Cosgun
 * ID: 22201571 
 * Section : 1 
 * Homework : 4 
 */
#include <string>
using namespace std;
class MolGraph
{
private:
    int** adjList;
    int* adjCounts;
    int numOfAtoms;
    int** BFSToAllVertices(int source, int dest);

public:
    MolGraph(const std::string& filename);
    ~MolGraph();
    void minBondPath(int source, int destination);
    void getDiameter();
    void getMST();
};

