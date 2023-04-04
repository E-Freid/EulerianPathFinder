#include <iostream>
#include "UndirectedGraph.h"

int main() {
    Edge edges[] = {{1,2}, {2,3}, {3,4}, {4,1}};
    UndirectedGraph graph = UndirectedGraph(4, 4);
    graph.AddEdges(edges, 4);
    graph.PrintEularCircleIfExists();
}
