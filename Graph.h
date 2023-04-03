
#ifndef PROGPROJ_GRAPH_H
#define PROGPROJ_GRAPH_H
using namespace std;

#include <list>

typedef struct edge
{
    int from;
    int to;
    bool visited;
} Edge;


class Graph
{
private:
    int m_NumOfNodes;
    list<Edge>* m_adjList;

    Graph(int i_NumOfNodes);

public:
    virtual void addEdges(Edge* i_edgesList, int i_numOfEdges) = 0;
    virtual bool checkIfGraphEulerian() = 0;
    virtual void printEularGraphIfExists() = 0; // TODO: avi should decide if to keep method here, or in sons
    virtual ~Graph();

};


#endif //PROGPROJ_GRAPH_H
