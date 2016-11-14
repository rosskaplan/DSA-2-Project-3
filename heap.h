#ifndef _HEAP_H
#define _HEAP_H

#include <string>
#include <vector>
#include "hash.h"

using namespace std;

class heap {

    public: 
        heap(int capacity);

        int insert(const string &id, int key, void *pv = NULL);

        int setKey(const string &id, int key);

        int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);

            //
            // remove - delete the node with the specified id from the binary heap
            //
            // If pKey is supplied, write to that address the key of the node
            // being deleted. If ppData is supplied, write to that address the
            // associated void pointer.
            //
            // Returns:
            //   0 on success
            //   1 if a node with the given id does not exist
            //
        int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

    private: 
    //Private data members and private functions are yet to be filled in
        int hcapacity; //heap capacity
        int hsize; //current size of heap
        hashTable *hashptr; //pointer to element in the heap
        
        class nodeObject {
        public:
            string hid;
            int key;
            void *voidptr;
        };

        vector<nodeObject> hdata; //named heapdata, nodeObject is below
        
        void percolateUp(int position);
        void percolateDown(int position);
        int position(nodeObject *nodeptr);
        int locateNodes(int index, string relation);

};

#endif //_HEAP_H
