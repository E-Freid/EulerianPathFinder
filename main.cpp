#include <iostream>
#include "UserInterface.h"
#include "UndirectedGraph.h"
#include "DirectedGraph.h"

int main() {
    try{
        Graph* graph;
        UserInterface UI;
        bool isDirected = UI.askUserIfGraphDirected();
        int numOfVertex = UI.getNumOfVertex();
        int numOfEdges = UI.getNumOfEdges(isDirected, numOfVertex);

        if(isDirected == true)
        {
            graph = new DirectedGraph(numOfVertex, numOfEdges);
        }
        else
        {
            graph = new UndirectedGraph(numOfVertex, numOfEdges);
        }

        Edge* edges = UI.getEdges(numOfVertex, numOfEdges);
        graph->AddEdges(edges, numOfEdges);
        graph->PrintEularCircleIfExists();

        delete[] edges;
    }
    catch (std::exception &ex) {
        cout << "invalid input";
        exit(1);
    }
    catch (...) {
        cout << "Something went wrong";
        exit(1);
    }
}