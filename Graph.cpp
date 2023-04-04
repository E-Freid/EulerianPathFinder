#include "Graph.h"

Graph::Graph(int i_NumOfNodes)
{
    this->m_NumOfNodes = i_NumOfNodes;
    this->m_adjList = new adjListElement[i_NumOfNodes];
}

Graph::~Graph()
{
    delete[] this->m_adjList;
}

