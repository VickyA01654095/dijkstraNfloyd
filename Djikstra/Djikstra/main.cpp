//
//  main.cpp
//  Djikstra & Floyd
//
//  Created by Victoria Estefania Vazquez Morales on 26/9/22.
//  A01654095
/*
 
 Implementación los algoritmos de Dijkstra y Floyd para encontrar la distancia más corta entre parejas de nodos en un grafo dirigido.

 El programa lee un numero n seguido de n x n valores enteros no negativos que representan una matriz de adyacencias de un grafo dirigido.
 
 El primer número representa el número de nodos, los siguientes valores en la matriz, el valor en la posición (i, j) representan el peso de la arista del nodo i al nodo j. Si no hay una arista entre el nodo i y el nodo j, el valor en la matriz debe ser -1.

 La salida del programa es, primero con el algoritmo de Dijkstra la distancia del nodo i al nodo j para todos los nodos, y luego, la matriz resultado del algoritmo de Floyd
 
 Ejemplo de entrada:
 
4
0 2 -1 3
-1 0 1 5
2 3 0 -1
3 -1 4 0
 
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;

vector <Edge*> makeEdges(vector<vector<int>> dists, vector<Node*> nodes);
vector <Node*> makeNodes(int n);
vector<vector <int>> distsMatrix(int nodes);

int main() {
    int nodes = 0;
    vector<vector<int>> dists;
    
    cin >> nodes;
    cin.clear();
    
    dists = distsMatrix(nodes);
    
    cout << endl << "Dijkstra: " << endl << endl;
    
    //Repetir Dijkstra para todos los nodos
    for(int i = 0; i < nodes; i++){
        vector <Node*> vectNodes = makeNodes(nodes);
        vector <Edge*> edges = makeEdges(dists, vectNodes);
        
        Graph* graph = new Graph(vectNodes, edges);
        graph->runDijkstra(vectNodes[i]);
        graph->print();
    }
    
    cout << endl << "Floyd: " << endl << endl;
    vector <Node*> vectNodes = makeNodes(nodes);
    vector <Edge*> edges = makeEdges(dists, vectNodes);
    Graph* graph = new Graph(vectNodes, edges);
    graph->runFloyd();
    
    return 0;
}

/*
 func distsMatrix - Crea la matriz de n x n, pidiendo valores al usuario
 @ nodes - entero con el número de nodos a considerar en la matriz
 @ return - vector de vectores de enteros (matriz) con las distancias introducidas por el usuario
 
 Complejidad: O(n^2)
 */
vector<vector <int>> distsMatrix(int nodes){
    vector<vector<int>> dists;
    string line = "";
    
    stringstream number(line);
    
    for(int i = 0; i < nodes; i++){
        vector<int> row;
        
        for(int j = 0; j < nodes; j++){
            cin >> line;
            cin.clear();
            row.push_back(stoi(line));
        }
        
        dists.push_back(row);
        
    }
    
    
    return dists;
}

/*
 func makeNodes - inicializa los nodos con su número y los coloca en un vector
 @ n - entero del número de nodos a crear
 @ return - vector de apuntadores de nodos
 
 Complejidad: O(n)
 */
vector <Node*> makeNodes(int n){
    vector <Node*> nodes;
    Node* node;
    
    for(int i = 0; i < n; i++){
        node = new Node(i+1); // cada nodo se inicializa con cierto numero
        
        nodes.push_back(node);
    }
    
    return nodes;
}

/*
 func makeEdges - inicializa los edges para el grafo
 @ dists - vector de vectores de enteros (matriz) con las distancias que introdujo el usuario
 @ nodes - vector de nodos
 @ return - vector de apuntador de edges
 
 Complejidad: O(n^2)
 */
vector <Edge*> makeEdges(vector<vector<int>> dists, vector<Node*> nodes){
    vector<Edge*> result;
    Edge* edge;
    
    for(int i = 0; i < dists.size(); i++){
        
        for(int j = 0; j < dists[0].size(); j++){
            
            // se genera un edge solo si su representación en la matriz es diferente de 0 o -1
            // un 0 indicaría que es la distancia hacia sí mismo
            // un -1 indicaría que no existe camino entre esos nodos
            if(dists[i][j] != 0 && dists[i][j] != -1){
                edge = new Edge(nodes[i], nodes[j], dists[i][j]);
                result.push_back(edge);
            }
            
        }
    }
    
    return result;
}
