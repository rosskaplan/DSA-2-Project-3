/*
 * Program 3: Dijkstra's Algorithm
 * Name: Ross Kaplan
 * Professor: Carl Sable
 * Goal: Implement a graph class on top of our previously created hashtable and heap classes to implement Dijkstra's algorihm.  
 * Using the heap for deletemin operations in finding the shortest path remaining.
 * Using the hashtable classes to store pointers to the heap (built in heap functionality) and for keeping track of all pointers to graph vertices.
 */

#include "graph.h"
#include <climits>
#include <stack>
#include <iostream>

using namespace std;

Graph::Graph(int size){
	ht=new hashTable(size);
}

Graph::graphVertex *Graph::insertVertex(string id){
	Graph::graphVertex* temp=new Graph::graphVertex(); // Allocate space for vertex
    temp->id = id;
	ht->insert(id,temp); // Add vertex to vertex hashtable
	vertices.push_back(temp); // Add vertex to vertex list
	return temp;
}

void Graph::insertEdge(string source, string destination, unsigned long cost){
	graphVertex *start, *end;
	// Determine whether src and dest vertices exist. If not create them. Get their memory addresses
    if (graphContains(source))
        start = (graphVertex*)(ht->getPointer(source));
    else
        start = insertVertex(source);

    if (graphContains(destination))
        end = static_cast<graphVertex *>(ht->getPointer(destination));
    else
        end = insertVertex(destination);

    Graph::graphEdge* temp = new Graph::graphEdge();
    temp->destination = end;
    temp->cost = cost;
	(start->adj).push_back(*temp);
}  

void Graph::runDijkstra(string id){
    int heapsize = vertices.size();
	heap myheap(heapsize);

	list<graphVertex*>::iterator vitt;

	graphVertex *temp;
	
	//Initialize Heap
	for(vitt = vertices.begin(); vitt !=vertices.end(); ++vitt){
		temp=*vitt;
		temp->distance=INT_MAX;
		temp->known=false; //Don't know any vertices, all distances are max int
		myheap.insert(temp->id,temp->distance,temp);
	}
    
    //Set source's distance = 0	
	temp=(graphVertex*)ht->getPointer(id);
    temp->distance = 0;
	myheap.setKey(id,0);
	
	list<graphEdge>::iterator eitt;
    graphVertex *temp2;

	while(!myheap.deleteMin(NULL, NULL, &temp)) { 
		temp->known=true;

        //Textbook's algorithm: 
		for(eitt=(temp->adj).begin(); eitt!=(temp->adj).end(); eitt++){
			temp2 = eitt->destination; //Get the edge's destination
            unsigned long &old_dist=temp2->distance; //Previous distance
			unsigned long new_dist=temp->distance + eitt->cost; //New path + new weight to get there
			if(new_dist<old_dist){
                old_dist = new_dist;
				myheap.setKey(temp2->id,old_dist); // Update distance of w in vertex and heap
				temp2->previous=temp;
			}
		}
	}
}

void Graph::printDijkstra(string source, ofstream &out){
    list<graphVertex*>::iterator itt; 
    stack<string> mystack; 
    //Traverse the list of vertices
    for(itt=vertices.begin(); itt != vertices.end(); itt++ ) {
        //vertices without paths from source
        out << (*itt)->id << ": ";
        if ( (*itt)->previous==NULL && (*itt)->id != source)
            out << "NO PATH" << endl; //End string with no path and don't traverse tree
        else{ //Traverse the list, print path
            string path;			
            out <<(*itt)->distance;
            out << " [";
            while((*itt)->previous != NULL) {
                mystack.push((*itt)->id);
                *itt = (*itt)->previous;
            }
            out << source;
            while(!mystack.empty()) {
                out << ", " << mystack.top();
                mystack.pop();
            }
            out << "]" << endl;
        }
    }
    return;
}	

bool Graph::graphContains(string id) {
    if (ht->contains(id) == 1)
        return 1;
    return 0;
}
