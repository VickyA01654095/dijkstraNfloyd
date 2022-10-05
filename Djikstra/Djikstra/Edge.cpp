//
//  Edge.cpp
//  Djikstra
//
//  Created by Victoria Estefania Vazquez Morales on 26/9/22.
//

#include "Edge.h"

Edge::Edge(Node* _first, Node* _second, int _weight){
    first = _first;
    second = _second;
    weight = _weight;
}
