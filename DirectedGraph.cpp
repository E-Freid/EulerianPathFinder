#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int i_NumOfNodes, int i_NumOfEdges) : Graph(i_NumOfNodes, i_NumOfEdges) {}

void DirectedGraph::addSingleEdge(Edge i_EdgeToAdd) {
    int fromIndex = --i_EdgeToAdd.from;

    --i_EdgeToAdd.to;
    this->m_adjList[fromIndex].neighbors.push_back(i_EdgeToAdd);
}

bool DirectedGraph::CheckIfGraphEulerian()
{
    bool isGraphStronglyConnected = this->IsGraphStronglyConnected();
    bool DoesEachVertexInDegreeEqualsOutDegree = this->DoesEachVertexInDegreeEqualsOutDegree();
    bool isEulerian = isGraphStronglyConnected && DoesEachVertexInDegreeEqualsOutDegree;

    return isEulerian;
}

bool DirectedGraph::DoesEachVertexInDegreeEqualsOutDegree()
{
    int* vertexOutDegrees = this->getVertexOutDegrees();
    int* vertexInDegrees = this->getVertexInDegrees();
    bool DoesAllVertexInDegEqualsOutDeg = this->checkInAndOutDegreeForEachVertex(vertexInDegrees, vertexOutDegrees);

    delete[] vertexInDegrees;
    delete[] vertexOutDegrees;

    return DoesAllVertexInDegEqualsOutDeg;
}

int* DirectedGraph::getVertexOutDegrees()
{
    int* vertexOutDegrees = new int[this->m_NumOfNodes];

    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        vertexOutDegrees[i] = this->m_adjList[i].neighbors.size();
    }

    return vertexOutDegrees;
}

int* DirectedGraph::getVertexInDegrees()
{
    int* vertexInDegrees = new int[this->m_NumOfNodes];

    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        vertexInDegrees[i] = 0;
    }

    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        for(auto neighbor: this->m_adjList[i].neighbors)
        {
            int InDegreeIndex = neighbor.to;
            vertexInDegrees[InDegreeIndex]++;
        }
    }

    return vertexInDegrees;
}

bool DirectedGraph::checkInAndOutDegreeForEachVertex(int* i_InDegreesArr, int* i_OutDegreesArr)
{
    bool doesInDegreeEqualsOutDegreeForAllVertex = true;

    for (int i = 0; i < this-> m_NumOfNodes; ++i) {
        if(i_InDegreesArr[i] != i_OutDegreesArr[i])
        {
            doesInDegreeEqualsOutDegreeForAllVertex = false;
            break;
        }
    }

    return doesInDegreeEqualsOutDegreeForAllVertex;
}

bool DirectedGraph::doesVisitOnGraphVisitingAllNodes()
{
    bool doesAllNodesVisited;
    COLOR* colors = new COLOR[this->m_NumOfNodes];

    this->initColorsToWhite(colors);
    this->visit(0, colors);
    doesAllNodesVisited = this->checkIfAllNodesVisited(colors);
    delete[] colors;

    return doesAllNodesVisited;
}

bool DirectedGraph::IsGraphStronglyConnected()
{
    bool isGraphStronglyConnected = true;

    if(this->m_NumOfNodes > 1)
    {
        bool isVisitReachAllNodesAtOnce = this->doesVisitOnGraphVisitingAllNodes();

        if(isVisitReachAllNodesAtOnce)
        {
            DirectedGraph* gTransposed = this->getTransposedGraph();
            isGraphStronglyConnected = gTransposed->doesVisitOnGraphVisitingAllNodes();
            delete gTransposed;
        }
        else
        {
            isGraphStronglyConnected = true;
        }
    }

    return isGraphStronglyConnected;
}

void DirectedGraph::markEdgeAsVisited(int i_CurrNode)
{
    this->m_adjList[i_CurrNode].currUnvisitedEdge->visited = true;
}

void DirectedGraph::advanceToTheNextUnvisitedEdge(int i_CurrNode)
{
    if(this->m_adjList[i_CurrNode].currUnvisitedEdge != m_adjList[i_CurrNode].neighbors.end()
       && this->m_adjList[i_CurrNode].currUnvisitedEdge->visited)
    {
        this->m_adjList[i_CurrNode].currUnvisitedEdge++;
    }
}

DirectedGraph* DirectedGraph::getTransposedGraph()
{
    DirectedGraph* gTransposed = new DirectedGraph(this->m_NumOfNodes, this->m_NumOfEdges);

    for (int i = 0; i < this->m_NumOfNodes; ++i)
    {
        for(auto neighbor: this->m_adjList[i].neighbors)
        {
            int from = neighbor.to;
            int to = neighbor.from;

            Edge edgeToAdd;
            edgeToAdd.from = ++to;
            edgeToAdd.to = ++from;
            gTransposed->addSingleEdge(edgeToAdd);
        }
    }
    return gTransposed;
}