
#include "UndirectedGraph.h"

UndirectedGraph::UndirectedGraph(int i_NumOfNodes, int i_NumOfEdges): Graph(i_NumOfNodes, i_NumOfEdges){}

void UndirectedGraph::AddEdges(Edge* i_EdgesList, int i_NumOfEdges)
{
    for (int i = 0; i < i_NumOfEdges; ++i)
    {
        Edge currEdgeToAdd = i_EdgesList[i];    // (1,2,false,nullptr)
        this->addSingleEdge(currEdgeToAdd);
    }
}

void UndirectedGraph::addSingleEdge(Edge i_EdgeToAdd)
{
    i_EdgeToAdd.from--;
    i_EdgeToAdd.to--;

    int from, to;
    from = i_EdgeToAdd.from;
    to = i_EdgeToAdd.to;

    Edge antiSimetricEdge = {to, from};
    this->m_adjList[from].neighbors.push_back(i_EdgeToAdd);
    this->m_adjList[to].neighbors.push_back(antiSimetricEdge);

    this->connectEdgesPointers(from, to);
}

void UndirectedGraph::connectEdgesPointers(int i_FirstNode, int i_SecondNode)
{
    auto locationOfFirstEdge =  --this->m_adjList[i_FirstNode].neighbors.end();
    auto locationOfSecondEdge = --this->m_adjList[i_SecondNode].neighbors.end();
    locationOfFirstEdge->antiSimetricEdgePointer = &(*locationOfSecondEdge);
    locationOfSecondEdge->antiSimetricEdgePointer = &(*locationOfFirstEdge);
}

void UndirectedGraph::printGraphInfo()
{
    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        std::cout << "Node " << i+1 << " has " << this->m_adjList[i].neighbors.size() << " neighbors: ";
        for (auto neighbor : this->m_adjList[i].neighbors)
        {
            cout << neighbor.to+1 << " is connected to " << neighbor.antiSimetricEdgePointer->to+1 << ", ";
        }
        std::cout << std::endl;
    }
}

bool UndirectedGraph::CheckIfGraphEulerian()
{
    bool graphIsConnected = this->IsGraphConnected();
    bool degreesAreEven = this->AreDegreesEven();
    return graphIsConnected && degreesAreEven;
}

bool UndirectedGraph::IsGraphConnected()
{
    bool isGraphConnected = true;
    if(this->m_NumOfNodes > 0)
    {
        COLOR* colors = new COLOR[this->m_NumOfNodes];
        this->initColorsToWhite(colors);
        this->visit(0, colors);
        isGraphConnected = this->checkIfAllNodesVisited(colors);
        delete[] colors;
    }
    return isGraphConnected;
}

bool UndirectedGraph::AreDegreesEven()
{
    int* degrees = this->getDegrees();
    bool areDegreesEven = this->checkIfDegreesAreEven(degrees);
    delete[] degrees;
    return areDegreesEven;
}

int* UndirectedGraph::getDegrees()
{
    int* degrees = new int[this->m_NumOfNodes];
    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        degrees[i] = this->m_adjList[i].neighbors.size();
    }
    return degrees;
}

bool UndirectedGraph::checkIfDegreesAreEven(int *i_Degrees)
{
    bool areDegreesEven = true;
    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        if(i_Degrees[i] % 2 != 0)
        {
            areDegreesEven = false;
        }
    }
    return areDegreesEven;
}

void UndirectedGraph::markEdgeAsVisited(int i_CurrNode)
{
    this->m_adjList[i_CurrNode].currUnvisitedEdge->visited = true;
    this->m_adjList[i_CurrNode].currUnvisitedEdge->antiSimetricEdgePointer->visited = true;
}

void UndirectedGraph::advanceToTheNextUnvisitedEdge(int i_CurrNode)
{
    while(this->m_adjList[i_CurrNode].currUnvisitedEdge != m_adjList[i_CurrNode].neighbors.end() &&
          this->m_adjList[i_CurrNode].currUnvisitedEdge->visited)
    {
        this->m_adjList[i_CurrNode].currUnvisitedEdge++;
    }
}