#include "Graph.h"

Graph::Graph(int i_NumOfNodes, int i_NumOfEdges)
{
    this->m_NumOfNodes = i_NumOfNodes;
    this->m_NumOfEdges = i_NumOfEdges;
    this->m_adjList = new adjListElement[i_NumOfNodes];
}

Graph::~Graph()
{
    delete[] this->m_adjList;
}

