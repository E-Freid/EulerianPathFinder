
#ifndef PROGPROJ_UNDIRECTEDGRAPH_H
#define PROGPROJ_UNDIRECTEDGRAPH_H
#include "Graph.h"
#include <iostream>

class UndirectedGraph: public Graph {
private:
    void initPosOfIteratorsInAdjList();
    void addSingleEdge(Edge i_EdgeToAdd);
    void connectEdgesPointers(int i_FirstNode, int i_SecondNode);
    void visit(int i_NodeToVisit, COLOR* i_Colors);
    void initColorsToWhite(COLOR* i_Colors);
    bool checkIfAllNodesVisited(COLOR* i_Colors);
    bool checkIfDegreesAreEven(int* i_Degrees);
    list<int> getEulerCircle();
    list<int> findCircuit(int i_StartingNode);
    int* getDegrees();
    void markEdgeAsVisited(int i_CurrNode);
    void advanceToTheNextUnvisitedEdge(int i_CurrNode);
    void printEulerianCircle(list<int> i_EulerCircle);

public:
    UndirectedGraph(int i_NumOfNodes, int i_NumOfEdges);
    void AddEdges(Edge* i_EdgesList, int i_NumOfEdges) override;
    bool CheckIfGraphEulerian() override;
    void PrintEularCircleIfExists() override;
    bool IsGraphConnected();
    bool AreDegreesEven();
    void printGraphInfo();

};


#endif //PROGPROJ_UNDIRECTEDGRAPH_H
