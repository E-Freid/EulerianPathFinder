#include "Graph.h"
#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int i_NumOfNodes, int i_NumOfEdges) : Graph(i_NumOfNodes, i_NumOfEdges) {}

void DirectedGraph::AddEdges(Edge *i_EdgesList, int i_NumOfEdges) {

}

bool DirectedGraph::CheckIfGraphEulerian() {
    return false;
}

void DirectedGraph::PrintEularCircleIfExists() {

}

bool DirectedGraph::IsGraphStronglyConnected() {
    return false;
}

bool DirectedGraph::DoesEachVertexInDegreeEqualsOutDegree() {
    return false;
}

void DirectedGraph::markEdgeAsVisited(int i_CurrNode) {

}

void DirectedGraph::advanceToTheNextUnvisitedEdge(int i_CurrNode) {

}

