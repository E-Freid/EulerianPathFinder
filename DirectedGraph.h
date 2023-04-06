#ifndef PROGPROJ_DIRECTEDGRAPH_H
#define PROGPROJ_DIRECTEDGRAPH_H
#include "Graph.h"
#include <iostream>

class DirectedGraph: public Graph {
private:
    void addSingleEdge(Edge i_EdgeToAdd) override;
    int* getVertexOutDegrees();
    int* getVertexInDegrees();
    bool checkInAndOutDegreeForEachVertex(int* i_InDegreesArr, int* i_OutDegreesArr);
    void markEdgeAsVisited(int i_CurrNode) override;
    void advanceToTheNextUnvisitedEdge(int i_CurrNode) override;
    DirectedGraph* getTransposedGraph();
    bool doesVisitOnGraphVisitingAllNodes();

public:
    DirectedGraph(int i_NumOfNodes, int i_NumOfEdges);
    bool CheckIfGraphEulerian() override;
    bool IsGraphStronglyConnected();
    bool DoesEachVertexInDegreeEqualsOutDegree();
};
#endif //PROGPROJ_DIRECTEDGRAPH_H
