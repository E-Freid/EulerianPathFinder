
#ifndef PROGPROJ_UNDIRECTEDGRAPH_H
#define PROGPROJ_UNDIRECTEDGRAPH_H
#include "Graph.h"
#include <iostream>

class UndirectedGraph: public Graph {
private:
    void addSingleEdge(Edge i_EdgeToAdd) override;
    void connectEdgesPointers(int i_FirstNode, int i_SecondNode);
    bool checkIfDegreesAreEven(int* i_Degrees);
    int* getDegrees();
    void markEdgeAsVisited(int i_CurrNode);
    void advanceToTheNextUnvisitedEdge(int i_CurrNode);

public:
    UndirectedGraph(int i_NumOfNodes, int i_NumOfEdges);
    bool CheckIfGraphEulerian() override;
    bool IsGraphConnected();
    bool AreDegreesEven();
    void printGraphInfo();
};


#endif //PROGPROJ_UNDIRECTEDGRAPH_H
