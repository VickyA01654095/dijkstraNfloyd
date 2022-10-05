//
//  Graph.cpp
//  Djikstra
//
//  Created by Victoria Estefania Vazquez Morales on 26/9/22.
//

#include "Graph.h"

Graph::Graph(vector<Node*> _nodes, vector<Edge*> _edges){
    nodes = _nodes;
    edges = _edges;
}

/*
 func getNeighbors - encuentra los vecinos de cierto nodo, que son aquellos con los que tiene conexión
 @ n - un apuntador de nodo
 @ return - un vector de apuntadores de nodos, que representan a los vecinos encontrados
 
 Complejidad: O(n)
 */
vector<Node*> Graph::getNeighbors(Node* n){
    vector<Node*> ans;
    
    vector<Edge*>::iterator edge;
        
    for(edge = edges.begin(); edge != edges.end(); ++edge){
        
        // si existe camino desde el nodo de origen hacia alguno otro, entonces es un vecino
        if ((*edge)->first == n){
            
            // se añade el vecino
            ans.push_back((*edge)->second);
        }
    }
    
    return ans;
}


/*
 func print - imprime las distancias más cortas entre el nodo de origen y los demás nodos (Dijkstra)
 
 Complejidad: O(n)
 */
void Graph::print(){
    
    vector<Node*>::iterator node;
    
    for(node = nodes.begin(); node != nodes.end(); ++node){
        
        if((*node)->prev == NULL || (*node)->distance == 0){
        
        } else {
            cout << "Node: " << _source->number;
            cout << " to node " << (*node)->number;
            cout << " : " << (*node)->distance << endl;
        }
        
    }
    
}


/*
 func printFd - imprime la matriz resultante del algoritmo de Floyd
 @ dist - vector de vectores de enteros, que es la matriz con las distancias resultantes
 
 Complejidad: O(n^2)
 */
void Graph::printFd(vector<vector <int>> dist){
    
    for(int i = 0; i < dist.size(); i++){
        for(int j = 0; j < dist[0].size(); j++){
            cout << dist[i][j] << " ";
        }
        
        cout << endl;
    }
}


/*
 func runDijkstra - ejecuta el algoritmo de Dijkstra para cierto nodo de origen
 @ source - nodo de origen para calcular las distancias
 
 Complejidad: O((|V| + |E|)log(|V|))
 donde |V| -> numero de nodos y |E| -> numero de edges
 */
void Graph::runDijkstra(Node* source){
    _source = source;
    
    //vector temporal para guardar todos los nodos
    vector<Node*> qs;
    
    vector<Node*>::iterator v;
    
    //se guardan todos los nodos en qs
    for (v = nodes.begin(); v != nodes.end(); ++v){
        qs.push_back(*v);
    }
    
    //la distancia del origen se inicializa como 0
    source->distance = 0;
    
    //mientras la lista temporal qs no esté vacia
    while(!qs.empty()){
        
        // nodo u que inicia como el source, porque es el único con menor distancia
        // después cambia
        Node* u = getMinDist(qs);
        
        // el nodo actual (con la menor distancia) se elimina de la lista qs
        remove(qs, u);
        
        // se buscan los vecinos alcanzables desde el nodo u
        vector<Node*> neighbors = getNeighbors(u);
        
        // se itera sobre todos los vecinos
        for (v = neighbors.begin(); v != neighbors.end(); ++v) {
            Node* vnode = *v;
            
            // alt es la distancia del nodo u + la distancia del nodo u al nodo v(que es un vecino)
            // para la primera iteración, cuando u = source, la distancia es 0 + x
            /* cuando el nodo u ya es un vecino de source, entonces se considera la distancia
             que ya existía desde source hacia u(vecino) + la nueva distancia desde u al otro vecino*/
            int alt = u->distance + getLength(u, vnode);
            
            // si alt es menor que la distancia que ya tenía el vecino (al inicio infinito -> 10000)
            if (alt < vnode->distance){
                
                // la distancia hacia el vecino se hace alt
                vnode->distance = alt;
                
                // y el nodo previo de ese vecino, se establece como u, para conocer el camino
                vnode->prev = u;
                
            }
        }
        
    }
}


/*
 func getMinDist - obtiene el nodo con la menor distancia que aún está en el vector qs
 @ qs - un vector de apuntadores de nodos
 @ return - apuntador al nodo con la menor distancia
 
 Complejidad: O(n)
 */
Node* Graph::getMinDist(vector<Node*> qs){
    Node* ans = qs[0];
    
    vector<Node*>::iterator node;
    
    for(node = qs.begin(); node != qs.end(); ++node){
        if((*node)->distance < ans->distance){
            ans = (*node);
        }
    }
    
    return ans;
}


/*
 func remove - elimina un apuntador de nodo del vector qs
 @ q - el apuntador del nodo a eliminar de qs
 @ qs - el vector de apuntadores de nodos
 
 Complejidad: O(n)
 */
void Graph::remove(vector<Node*> &qs, Node* q){
    
    for (int i = 0; i < qs.size(); i++){
        
        // cuando se encuentra el nodo q en qs, se elimina de ella
        if(qs[i] == q){
            qs.erase(qs.begin()+i);
        }
        
    }
}


/*
 func getLength - obtiene la distancia entre dos nodos
 @ u - nodo origen
 @ v - nodo destino
 @ return - entero de la distancia
 
 Complejidad: O(n)
 */
int Graph::getLength(Node* u, Node* v){
    
    vector<Edge*>::iterator edge;
    
    for(edge = edges.begin(); edge != edges.end(); ++edge){
        
        // busca entre el vector de edges donde el nodo 1 sea u y el 2 sea v
        if((*edge)->first == u && (*edge)->second == v){
            // se regresa el weight
            return (*edge)->weight;
        }
    }
    
    return -1;
}


/*
 func runFloyd - ejecuta el algoritmo de Floyd y obtiene una matriz de distancias
 
 Complejidad: O(|V|^3)
 donde |V| -> numero de nodos
 */
void Graph::runFloyd(){
    
    // se inicializa la matriz de resultados dist
    vector<vector<int>> dist;
    
    // se marcan en la matriz las conexiones iniciales entre nodos
    // todas son infinito->10000
    for(int i = 0; i < nodes.size(); i++){
        vector<int> row(nodes.size(), 10000);
        dist.push_back(row);
    }
    
    // se colocan las distancias correspondientes según los edges, dentro de la matriz dist
    vector<Edge*>::iterator edge;
    
    for(edge = edges.begin(); edge != edges.end(); ++edge){
        
        // en la posición [y][x] dentro de la matriz la distancia es = el peso del edge entre ambos
        // donde 'y' es determinado por el nodo origen y 'x' por el nodo destino
        dist[(*edge)->first->number-1][(*edge)->second->number-1] = (*edge)->weight;
        
    }
    
    // la diagnoal representa la distancia entre cada nodo hacia sí mismo, entonces todo es = 0
    for(int i = 0; i < nodes.size(); i++){
        dist[i][i] = 0;
    }
    
    for(int k = 0; k < nodes.size(); k++){
        for(int i = 0; i < nodes.size(); i++){
            for(int j = 0; j < nodes.size(); j++){
                
                // si la distancia en [i][j] dentro de la matriz de dist, es mayor (como infinito) a
                // lo que hay en [i][k] + [k][j]
                
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    //la distancia en [i][j] deja de ser infinito, para ser [i][k] + [k][j]
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    printFd(dist);
}
