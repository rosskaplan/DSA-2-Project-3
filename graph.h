#ifndef _GRAPH_H
#define _GRAPH_H

#include <string>
#include <list>
#include <fstream>

#include "heap.h"
#include "hash.h"

using namespace std;
class Graph{

    public:

        Graph(int size = 5000);  

        //Adds edge with specified source, destination, and cost
        void insertEdge(string source, string destination, long unsigned int cost);
      
        //Runs dijkstra's algorithm
        void runDijkstra(string id);  
      
        //Prints path from a source to each other vertex
        void printDijkstra(string source, ofstream &out);
     
        // Returns 1 if requested vertex is in the graph. 0 else.
        bool graphContains(string id);
  
    private:
 
        class graphEdge; //Written this way because graphVertex requires graphEdge to be a class and graphEdge needs graphVertex to be a class and so one must be defined to be a class prior to both class definitions.
 
        class graphVertex{
            public:
                string id;
                list<graphEdge> adj;
                bool known;
                unsigned long distance;
                graphVertex *previous;
        };
	 
        class graphEdge{
            public:
                unsigned long cost;
                graphVertex * destination;
        };
  
        list<graphVertex*> vertices;
        hashTable *ht; 
  
        //Inserts vertices into graph
        graphVertex *insertVertex(string id);
};

#endif
