#include <iostream>
#include <stdlib.h>
#include <vector>
#include "graph_list.hpp"
#include "graph_matrix.hpp"
#define N_NODI 4
using namespace std;

/*Not all the codes are mine, part are from : 
-https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm 
-https://gist.github.com/arrayed/4121223743f60e2105cde3b83f26590a */

int main(){
    /* test Vertex Matrix */
    /*-----------------------------------------------------------*/

    string s = "v1";

    Vertex_Matrix v1(s,10);
    Vertex_Matrix v2("v2",10);
    Vertex_Matrix v3("v3",10);
    cout << v1 << endl<< v2 <<endl << v3<< endl;
    Graph_Matrix* grp = new Graph_Matrix(3); 
    grp->addVertex_Matrix(&v1);
    grp->addVertex_Matrix(&v2);
    grp->addVertex_Matrix(&v3);
    grp->addEdge(&v1,&v2,2);
    grp->addEdge(&v2,&v1,2);
    grp->addEdge(&v2,&v3);
    grp->DFS(&v1,&sum);
    cout << *grp << endl;
    grp->printMatrix();
    grp->unMarkAll();

    grp->BFS(&v1,&sum);
    cout << *grp << endl;
    cout << "------------------------------------------------------------" << endl; 
    /*------------------------------------------------------------*/
    /*test graph list*/
    graph_list* graph = new graph_list();
    vector<Vertex*> nodi;

    for(int i = 0; i < N_NODI; i++){
        string s = "node "+to_string(i);
        nodi.push_back(new Vertex( s,i));
        graph->addVertex(nodi[i]);
    }

    graph->addEdges(nodi[0],nodi[1],2);
    graph->addEdges(nodi[0],nodi[2],3);
    graph->addEdges(nodi[1],nodi[3],10);
    graph->addEdges(nodi[2],nodi[3],4);

    graph->DFS(nodi[0]);
    
    vector<int> dist = dijkstra(graph,nodi[0]);
   
    for(int i  : dist) cout << i << endl;
    
    
    return 0;
}