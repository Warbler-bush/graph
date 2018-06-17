#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdbool>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// the users shouldnt use the vertex_list, it only helps to implement the graph.

class Vertex{
private:
    int val;
    string title;
public:
    Vertex(string title, int val){
        this->title = title;
        this->val = val;
    }

    int getVal(){return val;}
    string getTitolo(){return title;}
};

// the vertex_list is the list , with the node that has n-edges
class vertex_list{
private:
    Vertex* node;
    vector<Vertex*> edges;
    vector<int> weight;
    int nEdges = 0;
public:
    vertex_list(Vertex* node){this->node = node;}
    
    void addEdges(Vertex* n, int weight){
        edges.push_back(n);
        nEdges++;
        this->weight.push_back(weight);
    }

    bool isSameVertex(Vertex* n){return this->node == n;}

    vector<Vertex*> getEdges(){return edges;}
    
    int getWeight(Vertex* dst){ return weight[getVertexIndex(dst)];}

    int getVertexIndex(Vertex* v){
        for(int i = 0; i < nEdges; i++)
            if(edges[i] == v)
                return i;
        return -1;
    }
};


class graph_list{
private:
    vector<vertex_list*> adj_list;
    int nVertexs = 0;
    vector<bool> marks;
    
    
    vertex_list* getVertexList(Vertex* n){
        for(int i = 0; i< nVertexs ; i++)
            if(adj_list[i]->isSameVertex(n)) 
                return adj_list[i];
            
        return NULL;
    }
public:
    addVertex(Vertex* n){
        adj_list.push_back(new vertex_list(n));
        nVertexs++;
        marks.push_back(false);
    }

    addEdges(Vertex* src,Vertex* dst,int weight)
    {getVertexList(src)->addEdges(dst,weight);}

    

    int getVertexIndex(Vertex* n){
        for(int i = 0; i< nVertexs ; i++)
            if(adj_list[i]->isSameVertex(n)) 
                return i;
            
        return -1;
    }

    void DFS(Vertex* src){
        int index = getVertexIndex(src);
        marks[index] = true;
        cout << "visited:" << src->getTitolo() << endl;
        for(Vertex* n : adj_list[index]->getEdges() )
            if(!marks[getVertexIndex(n)])
                DFS(n);
        
    }

    int getNVertex(){return nVertexs;}

    vector<Vertex*> getEdgesList(Vertex* node){return getVertexList(node)->getEdges();}
    int getWeight(Vertex* src, Vertex*dst){return getVertexList(src)->getWeight(dst);}
    void unMarkAll(){for(int i = 0; i<nVertexs ; i++)marks[i] = false;}
};



vector<int> dijkstra(graph_list* graph,Vertex* source){
    priority_queue<pair<int,Vertex*> , vector<pair<int,Vertex*>>, greater<pair<int,Vertex*>> >Q;
    vector<int> dist;
    dist.assign(graph->getNVertex(),INF);
    dist[graph->getVertexIndex(source)] = 0;
    Q.push({0,source});

    while(!Q.empty()){
        Vertex* current = Q.top().second;
        int srcIndex = graph->getVertexIndex(current);
        Q.pop();
        for(Vertex* n : graph->getEdgesList(current)){
            int weight = graph->getWeight(current, n);
            int dstIndex = graph->getVertexIndex(n);
            
            if(dist[dstIndex] > dist[srcIndex]+weight){
                dist[dstIndex] = dist[srcIndex]+weight;
                Q.push({dist[dstIndex],n});
            }
        }
    }
    return dist;
}
#endif