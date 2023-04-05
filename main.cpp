#include <iostream>
#include "UndirectedGraph.h"
#include "DirectedGraph.h"

int main() {
    Graph* graph;
    bool isDirected = false;
    int numOfVertex = 4;
    int numOfEdges = 4;

    if(isDirected == true)
    {
        graph = new DirectedGraph(numOfVertex, numOfEdges);
    }
    else
    {
        graph = new UndirectedGraph(4, 4);
    }

    Edge edges[] = {{1,2}, {2,3}, {3,4}, {4,1}};
    graph->AddEdges(edges, 4);
    graph->PrintEularCircleIfExists();
}