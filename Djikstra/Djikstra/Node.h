//
//  Node.h
//  Djikstra
//
//  Created by Victoria Estefania Vazquez Morales on 26/9/22.
//
#pragma once
#include<iostream>

using namespace std;

#ifndef Node_h
#define Node_h

class Node{
public:
    int number;
    Node* prev;
    int distance;
    
    Node(int _number);
};

#endif /* Node_h */
