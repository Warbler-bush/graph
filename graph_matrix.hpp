#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

/*Author: Wang Wei*/


/*Not all the codes are mine, part are from : 
-https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm 
-https://gist.github.com/arrayed/4121223743f60e2105cde3b83f26590a */

class Vertex_Matrix{
private:
    string title;
    int val = 0;

public:
    Vertex_Matrix(string title,int val){
       this->title = title;
        if(val > 0)this->val = val;
    }
    string getTitle(){return title; }
    int getVal(){return val;}
    friend ostream& operator <<(ostream& os, const Vertex_Matrix& vert);
};
  
 ostream& operator<<(ostream& os, const Vertex_Matrix& vert){
    os << "Vertex_Matrix{title:"+vert.title << ",val:" << vert.val<<"}";
    return os;
}

class Graph_Matrix{
private:
    vector<Vertex_Matrix*> vertices;
    const static int NULL_EDGE  = 0;
    int number_vertices;
    int max_vertices;
    vector<vector<int>> edges;
    int sum = 0;
    vector<int> marks;
public:
    Graph_Matrix(int max_vertices){
        number_vertices = 0;
        this->max_vertices = max_vertices;
        vertices.resize(max_vertices);
        for(int i = 0; i<max_vertices; i++)
            vertices[i] = NULL;
        
        int rows = max_vertices;
        int columns = max_vertices;
        // for each row, it creates a vector with length columns and value 0
        edges.resize(rows, vector<int>(columns,0));
        marks.resize(rows,0);
    }

    void addVertex_Matrix( Vertex_Matrix* v){
       vertices[number_vertices] = v;
       for(int i = 0 ; i< max_vertices;i++){
           edges[i][number_vertices] = NULL_EDGE;
           edges[number_vertices][i] = NULL_EDGE;
       }
       number_vertices++;
    }

    int index_is(Vertex_Matrix* vert){
        for(int i = 0; i< number_vertices; i++)
            if(vertices[i] == vert) return i ;
        
        return -1; 
    }

    void addEdge(Vertex_Matrix* fromVert, Vertex_Matrix* toVert, int weight){
        int row = index_is(fromVert);
        int column = index_is(toVert);
        edges[row][column] = weight;
    }
    void addEdge(Vertex_Matrix* fromVert, Vertex_Matrix* toVert){addEdge(fromVert,toVert,1);}    
    
    void printMatrix(){
         for(int r = 0; r< number_vertices ; r++){
            for(int c = 0; c <number_vertices ; c++)
                cout << edges[r][c];
            cout << endl;       
        }
    }


    friend ostream& operator<<(ostream& os, Graph_Matrix& graph);

    Vertex_Matrix* getVertex_MatrixAtIndex(int n){return vertices[n];}

    // deep first search
    void DFS(Vertex_Matrix* access ,void (*sum)(Graph_Matrix*,int) ){
        int index = index_is(access);
        // mark as it is visited
        marks[index] = 1;
        // does the sum 
        sum(this,access->getVal());

        // check if the next node has already been visited 
        // and if it has a edge with the "access" 
        for(int i = 0; i< number_vertices ; i++)
            if(marks[i]== 0 && edges[index][i] != 0)
                DFS(vertices[i],sum);
    }

    int getSum(){return sum;}
    void setSum(int sum){this->sum = sum;}

   void BFS(Vertex_Matrix* access, void (*sum)(Graph_Matrix*,int) ){
       int index = index_is(access);
       marks[index] = 1;
       queue<Vertex_Matrix*> Q;
       Vertex_Matrix* node;
       Q.push(access);
       // for each node that has a edge with access, will be visited
       // and after will be added to the queue, the added node will do the same.
       while(!Q.empty()){
           node = Q.front();
           index = index_is(node);
           Q.pop();
           sum(this,node->getVal());

            for(int i = 0; i< number_vertices; i++){
                    if(marks[i] == 0 && edges[index][i]!= 0){
                        Q.push(vertices[i]);
                        marks[i] = 1 ;
                    }
                }
        }
    }

    void unMarkAll(){
        for(int i = 0; i< number_vertices ; i++)
            marks[i] = 0;
    }
};

void sum(Graph_Matrix* graph,int val){graph->setSum(val+graph->getSum());}

ostream& operator<<(ostream& os, Graph_Matrix& graph){
    os << "Graph_Matrix{";
    for(int i = 0; i< graph.number_vertices; i++)
        os << *graph.vertices[i] << endl;
    os<<", sum:"<< graph.sum;
    os << "}";
    return os;
}

#endif