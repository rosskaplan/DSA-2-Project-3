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
	Graph::graphVertex* temp=new Graph::graphVertex(); //New vertex
    temp->id = id;
	ht->insert(id,temp);
	vertices.push_back(temp);
	return temp;
}

void Graph::insertEdge(string source, string destination, unsigned long cost){
	graphVertex *start, *end;

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
	heap H(heapsize);

	list<graphVertex*>::iterator vitt;

	graphVertex *temp;
	
	//Add all vertices to heap. Set distances to infinite so that any distance is smaller. Set unknown.
	for(vitt = vertices.begin(); vitt !=vertices.end(); ++vitt){
		temp=*vitt;
		temp->distance=INT_MAX;
		temp->known=false;
		H.insert(temp->id,temp->distance,temp);
	}
    
	temp=(graphVertex*)ht->getPointer(id);
    temp->distance = 0;
	H.setKey(id,0);
	
	list<graphEdge>::iterator eitt;
    graphVertex *temp2;

	while(!H.deleteMin(NULL, NULL, &temp)) { 
		temp->known=true;

        //Textbook's algorithm: 
		for(eitt=(temp->adj).begin(); eitt!=(temp->adj).end(); eitt++){
			temp2 = eitt->destination;
            unsigned long &old_dist=temp2->distance;
			unsigned long new_dist=temp->distance + eitt->cost;
			if(new_dist<old_dist){
                old_dist = new_dist;
				H.setKey(temp2->id,old_dist); 
				temp2->previous=temp;
			}
		}
	}
}

void Graph::printDijkstra(string source, ofstream &out){
    list<graphVertex*>::iterator itt; 
    stack<string> S; 
    //Print for each vertex
    for(itt=vertices.begin(); itt != vertices.end(); itt++ ) {
        out << (*itt)->id << ": ";
        if ( (*itt)->previous==NULL && (*itt)->id != source)
            out << "NO PATH" << endl; 
        else{
            string path;			
            out <<(*itt)->distance;
            out << " [";
            while((*itt)->previous != NULL) {
                S.push((*itt)->id);
                *itt = (*itt)->previous;
            }
            out << source;
            while(!S.empty()) {
                out << ", " << S.top();
                S.pop();
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
