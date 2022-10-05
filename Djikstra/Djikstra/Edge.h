//
//  Edge.h
//  Djikstra
//
//  Created by Victoria Estefania Vazquez Morales on 26/9/22.
//

#pragma once
#include<iostream>
#include "Node.h"

using namespace std;

#ifndef Edge_h
#define Edge_h

class Edge{
public:
    Node* first;
    Node* second;
    int weight;
    
    Edge(Node* _first, Node* _second, int _weight);
};

#endif /* Edge_h */
