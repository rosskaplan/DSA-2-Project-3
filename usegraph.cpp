#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#include "graph.h"
#include "heap.h"
#include "hash.h"

using namespace std;

int main(){
	string inFile, outFile;
	string source, destination;
	long unsigned int weight;

	clock_t t1,t2;
	double timeDiff;

	cout << "Please enter name of graph file." << endl;
	cin >> inFile;
	
	ifstream in(inFile.c_str());
	if (!in.is_open()){ 
		cerr << "Failed to open input file." << endl;
		return -1;
	}
	
	Graph G(5000);
	while (in.good()){
		in >> source >> destination >> weight; 
		G.insertEdge(source,destination,weight);
	}
	in.close();
    while (1) {
        cout << "Please enter an id for the starting vertex." << endl;
        cin >> source;
        if (!G.graphContains(source)) {
            cout << "That vertex was invalid. Please try again." << endl;	
        } else {
            break;
        }
    }
	t1 = clock();
	G.runDijkstra(source);
	t2 = clock();
	timeDiff = (double) (t2 - t1)/CLOCKS_PER_SEC;
	
	cout << "Time in seconds to run Dijkstra's Algorithm: " << timeDiff << endl;
	cout<<"Please provide an output text file." << endl;
	cin >> outFile;
	
	ofstream out(outFile.c_str());
	if (!out.is_open()){
		cerr << "Unable to open output file." << endl;
		return -1;
	}

	G.printDijkstra(source, out);
	out.close();
	return 0;
}	
