import heapq
import math

#math.inf -> infinito

class Node:
    def __init__(self, value):
        self.childs = list()
        self.value = value

    def addChild(self, node):
        if( node  not in self.childs):
            self.childs.append(node)
            return False
        else: 
            return True

    def __lt__(self,other):
        return cmp(self.value, other.value)


    def __str__(self):
        return str(self.value) 


class Graph:
    def __init__(self, root):
        self.root = root
        self.adcy = dict()
        self.nodes = list()
        self.addNode(root)

    def addNode(self, node):
        if(node not in self.nodes):
            self.nodes.append(node)
            self.adcy[node] = list()
            return False
        
        return True
    
    def addEdge(self, ori_node , dest_node, weight):
        if(ori_node.addChild(dest_node)):
            return True

        self.adcy[ori_node].append( (weight, dest_node) )
        return False

    def getWeight(self, ori_node, dest_node):
        for nodes in self.adcy[ori_node]:
            if( nodes[1] == dest_node ):
                return nodes[0]

        return -99999999999999
        
    def get(self,index):
        return self.nodes[index]


    def dijkstra(self,source):
        return self._dijkstra(source)[1]
        

    def _dijkstra(self,source):
        if(source not in self.nodes):
            print("WTF source not in graph")
            return None


        visited = list()
        distances = dict()
        path = dict()
        
        for x in self.nodes:
            distances[x] = math.inf
        
        distances[source] = 0
        path[source] = None

        nodes = list()
        nodes.append( (0, source)  )

        heapq.heapify(nodes)
        #heapq.heappush(nodes,Node(4) ) -> push a object and sort
        #print (list(nodes)) 
        #print (heapq.heappop(nodes)) -> pop smallest number 

        #print("Enter while:")
        while( nodes ): # check if it is empty
            node = heapq.heappop(nodes)
            #print("node :" +  str(node[1]) )
            vicini = self.adcy[node[1] ]
            
            for nd in vicini:
                if(distances[nd[1] ] > distances[node[1] ] +  nd[0] ):
                    distances[nd[1] ] = distances[node[1] ] + nd[0]
                    path[ nd[1] ] = node[1]

                if(nd[1] not in visited):
                    heapq.heappush(nodes, (distances[nd[1]], nd[1] ) )
                    visited.append(nd[1])

        return (path,distances)


    def dist(self,source,  dest):
        path = self._dijkstra(source)[0]
        dist = 0
        
        tok1 = dest
        tok2 = path[dest]
        while( tok2 != None):
            #print("tok2:"+ str(tok2) + " tok1:" + str(tok1) )
            dist += self.getWeight( tok2,tok1 )
            tok1 = tok2
            tok2 = path[tok1]

        return dist


    #def __str__(self):  -> per il print

    def toString(self):
        print("nodi:")
        for x in self.nodes:
            print( str(x.value) + " ",end="")
        
        print("\n")
        
        print("lista di adiacenze:")
        for key in self.adcy:
            print( str( key.value ) + "->", end="")
            lista = self.adcy[key]
            for x in lista:
                print(   "("+str( x[1].value ) + ", w:" + str(x[0]) +") ",end="")

            print()

        print("-------------------------")
