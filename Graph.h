
#ifndef PROGPROJ_GRAPH_H
#define PROGPROJ_GRAPH_H

#include <list>
using namespace std;

typedef struct edge
{
    int from;
    int to;
    bool visited = false;
    struct edge* antiSimetricEdgePointer = nullptr;
} Edge;

typedef struct adjListElement
{
    list<Edge> neighbors;
    list<Edge>::iterator currUnvisitedEdge;
} AdjListElement;

enum COLOR{WHITE, GREY, BLACK};

class Graph
{
protected:
    int m_NumOfNodes;
    int m_NumOfEdges;
    AdjListElement* m_adjList;

    Graph(int i_NumOfNodes, int i_NumOfEdges);
    void initPosOfIteratorsInAdjList();
    void printEulerianCircle(list<int> i_EulerCircle);
    void initColorsToWhite(COLOR* i_Colors); // For DFS colors array
    void visit(int i_NodeToVisit, COLOR* i_Colors);
    bool checkIfAllNodesVisited(COLOR* i_Colors);
    list<int> findCircuit(int i_StartingNode);
    list<int> getEulerCircle();
    virtual void addSingleEdge(Edge i_EdgeToAdd) = 0;
    virtual void markEdgeAsVisited(int i_CurrNode) = 0;
    virtual void advanceToTheNextUnvisitedEdge(int i_CurrNode) = 0;

public:
    virtual void AddEdges(Edge* i_EdgesList, int i_NumOfEdges);
    virtual bool CheckIfGraphEulerian() = 0;
    virtual void PrintEularCircleIfExists();
    virtual ~Graph();
};


#endif //PROGPROJ_GRAPH_H
