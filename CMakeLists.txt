cmake_minimum_required(VERSION 3.24)
project(ProgProj)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProgProj main.cpp Graph.cpp Graph.h UndirectedGraph.cpp UndirectedGraph.h)
