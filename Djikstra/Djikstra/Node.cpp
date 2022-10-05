//
//  Node.cpp
//  Djikstra
//
//  Created by Victoria Estefania Vazquez Morales on 26/9/22.
//

#include "Node.h"

Node::Node(int _number){
    number = _number;
    Node* prev = NULL;
    distance = 10000;
}
