#ifndef PROGPROJ_DIRECTEDGRAPH_H
#define PROGPROJ_DIRECTEDGRAPH_H
#include "Graph.h"
#include <iostream>

class DirectedGraph: public Graph {
private:
    DirectedGraph getTransposedGraph();
    void markEdgeAsVisited(int i_CurrNode) override;
    void advanceToTheNextUnvisitedEdge(int i_CurrNode) override;

public:
    DirectedGraph(int i_NumOfNodes, int i_NumOfEdges);
    void AddEdges(Edge* i_EdgesList, int i_NumOfEdges) override;
    bool CheckIfGraphEulerian() override;
    void PrintEularCircleIfExists() override;
    bool IsGraphStronglyConnected();
    bool DoesEachVertexInDegreeEqualsOutDegree();
};
#endif //PROGPROJ_DIRECTEDGRAPH_H
