#ifndef PROGPROJ_USERINTERFACE_H
#define PROGPROJ_USERINTERFACE_H
#include <iostream>
#include "Graph.h"

class UserInterface
{
private:
    int UserInterface::getIntegerFromUser() noexcept(false);
    Edge getSingleEdge(int i_NumOfVertex) noexcept(false);

public:
    UserInterface() = default;
    UserInterface(const UserInterface& other) = delete;
    UserInterface(UserInterface&& other) = delete;
    bool askUserIfGraphDirected() noexcept(false);
    int getNumOfVertex() noexcept(false);
    int getNumOfEdges(int i_IsDirected, int i_NumOfVertex) noexcept(false);
    Edge* getEdges(int i_NumOfVertex, int i_NumOfEdges) noexcept(false);
};

#endif //PROGPROJ_USERINTERFACE_H
