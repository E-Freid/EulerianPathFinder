#include "Graph.h"
#include <iostream>

using namespace std;

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

void Graph::printEulerianCircle(list<int> i_EulerCircle)
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

void Graph::initColorsToWhite(COLOR *i_Colors)
{
    for(int i=0; i<this->m_NumOfNodes; ++i)
    {
        i_Colors[i] = WHITE;
    }
}

void Graph::visit(int i_NodeToVisit, COLOR *i_Colors)
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

bool Graph::checkIfAllNodesVisited(COLOR* i_Colors)
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

list<int> Graph::findCircuit(int i_StartingNode)
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

void Graph::initPosOfIteratorsInAdjList()
{
    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        this->m_adjList[i].currUnvisitedEdge = this->m_adjList[i].neighbors.begin();
    }
}

list<int> Graph::getEulerCircle()
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

void Graph::PrintEularCircleIfExists()
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
