//
//  Graph.h
//  Djikstra
//
//  Created by Victoria Estefania Vazquez Morales on 26/9/22.
//
#pragma once
#include<iostream>
#include<algorithm>
#include<vector>

#include "Edge.h"

using namespace std;


#ifndef Graph_h
#define Graph_h

class Graph{
public:
    vector<Node*> nodes;
    vector<Edge*> edges;
    Node* _source;
    Graph(vector<Node*> _nodes, vector<Edge*> _edges);
    
    vector<Node*> getNeighbors(Node* n);
    void print();
    void printFd(vector<vector <int>> dist);
    void runDijkstra(Node* source);
    void runFloyd();
    Node* getMinDist(vector<Node*> qs);
    void remove(vector<Node*> &qs, Node* q);
    int getLength(Node* u, Node* v);
};

#endif /* Graph_h */
