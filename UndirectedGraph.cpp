
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

void UndirectedGraph::PrintEularCircleIfExists()
{
    bool graphIsEulerian = this->CheckIfGraphEulerian();
    if(graphIsEulerian)
    {
        cout << "The graph is aulerian" << endl;
        list<int> eularCircle = this->getEulerCircle();
        this->printEulerianCircle(eularCircle);
    }
    else
    {
        cout << "Graph is not aulerian!" << endl;
    }
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

void UndirectedGraph::initColorsToWhite(COLOR *i_Colors)
{
    for(int i=0; i<this->m_NumOfNodes; ++i)
    {
        i_Colors[i] = WHITE;
    }
}

bool UndirectedGraph::checkIfAllNodesVisited(COLOR* i_Colors)
{
    bool visitedAllNodes = true;
    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        if(i_Colors[i] != BLACK)
        {
            visitedAllNodes = false;
        }
    }
    return visitedAllNodes;
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

list<int> UndirectedGraph::getEulerCircle()
{
    this->initPosOfIteratorsInAdjList();
    list<int> eulerCircle = this->findCircuit(0);
    auto nodeWithUnvisitedEdges = eulerCircle.begin();
    while(nodeWithUnvisitedEdges != eulerCircle.end())
    {
        if(this->m_adjList[*nodeWithUnvisitedEdges].currUnvisitedEdge != this->m_adjList[*nodeWithUnvisitedEdges].neighbors.end())
        {
            list<int> newCircle = this->findCircuit(*nodeWithUnvisitedEdges);
            eulerCircle.splice(nodeWithUnvisitedEdges, newCircle);
        }
        nodeWithUnvisitedEdges++;
    }
    return eulerCircle;
}

list<int> UndirectedGraph::findCircuit(int i_StartingNode)
{
    int currentNode = i_StartingNode;
    list<int> circle = {currentNode};
    do
    {
        this->advanceToTheNextUnvisitedEdge(currentNode);
        if(this->m_adjList[currentNode].currUnvisitedEdge == this->m_adjList[currentNode].neighbors.end())
        {
            break;
        }
        int nextNode = this->m_adjList[currentNode].currUnvisitedEdge->to;
        this->markEdgeAsVisited(currentNode);
        circle.push_back(nextNode);
        currentNode = nextNode;
    } while(this->m_adjList[currentNode].currUnvisitedEdge != m_adjList[currentNode].neighbors.end());
    return circle;
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

void UndirectedGraph::initPosOfIteratorsInAdjList()
{
    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        this->m_adjList[i].currUnvisitedEdge = this->m_adjList[i].neighbors.begin();
    }
}

void UndirectedGraph::visit(int i_NodeToVisit, COLOR *i_Colors)
{
    i_Colors[i_NodeToVisit] = GREY;
    for(auto neighbor: this->m_adjList[i_NodeToVisit].neighbors)
    {
        if(i_Colors[neighbor.to] == WHITE)
        {
            this->visit(neighbor.to, i_Colors);
        }
    }
    i_Colors[i_NodeToVisit] = BLACK;
}

void UndirectedGraph::printEulerianCircle(list<int> i_EulerCircle)
{
    int prevNode = -1;
    cout << "(";
    for(int currNode: i_EulerCircle)
    {
        if(prevNode != currNode)
        {
            cout << currNode+1 << ",";
        }
        prevNode = currNode;
    }
    cout << "\b)" << endl;
}