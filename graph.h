/*
Implementing graph as an adjacency list
Using dictionary to store features of each node
*/

#pragma once
#include <vector>
#include <unordered_map>
#include <list>
#include <map>

using namespace std;

class Graph{
    public:
        Graph();    // default constructor
        void insert();  // insert vertex into graph
        void remove(unsigned);  // remove vertex from graph
        bool areAdjacent(unsigned, unsigned);   // check if two nodes are connected by an edge

    private:
        unordered_map<unsigned, list<unsigned>> htable_;    // key: vertex, val: linked list of pointers
        vector<int> vertex_;    // list of all vertices in graph
        int numVertices;    // number of vertices in graph
        map<unsigned, vector<bool>> features_;  // key: vertex, val: existence of features
};