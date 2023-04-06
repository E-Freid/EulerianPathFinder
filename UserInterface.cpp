#include <iostream>
#include "UserInterface.h"

using namespace std;

bool UserInterface::askUserIfGraphDirected() noexcept(false)
{
    char userResponse;

    cout << "Is the graph directed: y/n" << endl;
    cin >> userResponse;

    if(userResponse != 'y' && userResponse != 'n')
    {
        throw std::invalid_argument("Invalid answer");
    }

    return userResponse == 'y' ? true : false;
}

int UserInterface::getIntegerFromUser() noexcept(false)
{
    int num;

    cin >> num;
    if(num < 0)
        throw std::invalid_argument("Invalid number");

    return num;
}

int UserInterface::getNumOfVertex() noexcept(false)
{
    return this->getIntegerFromUser();
}

int UserInterface::getNumOfEdges(int i_IsDirected, int i_NumOfVertex) noexcept(false)
{
    int numOfEdges;

    try {
        numOfEdges = this->getIntegerFromUser();
    }
    catch (std::exception &ex) {
        throw ex;
    }

    int maxEdges = Graph::GetMaxNumOfEdgesInGraph(i_IsDirected, i_NumOfVertex);

    if(numOfEdges > maxEdges)
    {
        throw std::invalid_argument("Max number of edges exceeded");
    }

    return numOfEdges;
}

Edge *UserInterface::getEdges(int i_NumOfVertex, int i_NumOfEdges) noexcept(false)
{
    Edge *edges = new Edge[i_NumOfEdges];

    try{
        for (int i = 0; i < i_NumOfEdges; ++i) {
            edges[i] = this->getSingleEdge(i_NumOfVertex);
        }

        return edges;
    }
    catch(std::exception &ex)
    {
        delete[] edges;
        throw ex;
    }
}

Edge UserInterface::getSingleEdge(int i_NumOfVertex) noexcept(false)
{
    bool isFromValidVertex, isToValidVertex, isLoopEdge;
    Edge newEdge;
    int from, to;

    cin >> from >> to;
    isFromValidVertex = Graph::isValidVertex(i_NumOfVertex, from);
    isToValidVertex = Graph::isValidVertex(i_NumOfVertex, to);
    isLoopEdge = from == to;
    if(!isFromValidVertex || !isToValidVertex || isLoopEdge)
    {
        throw std::invalid_argument("Invalid edge was given");
    }
    //TODO: Validate Duplication of edges?
    else
    {
        newEdge.from = from;
        newEdge.to = to;
    }

    return newEdge;
}
