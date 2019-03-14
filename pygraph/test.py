import sys
sys.path.append('..\\graph')
#print(sys.path)
from graph import * 

nd4 = Node(4)
graph = Graph(nd4)

nd1 = Node(1)
nd2 = Node(2)
nd3 = Node(3)


graph.addNode(nd1)
graph.addNode(nd2)
graph.addNode(nd3)

graph.addEdge(nd1,nd2,3)
graph.addEdge(nd1,nd3,5)
graph.addEdge(nd2,nd3,10)
graph.addEdge(nd2,nd4,5)

graph.toString()


path = graph.dijkstra(nd1)
i = 0
for x in path:
    print("nodo:" + str( x ) + " distances:" + str( path[x] ) )
    i += 1

print("distance:" + str(graph.dist(nd1,nd4)) )