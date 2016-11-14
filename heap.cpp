#include "heap.h"
#include "hash.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//constructor for heap
heap::heap(int capacity) {

    hdata.resize(++capacity);
    hashptr = new hashTable(capacity << 1);
    hcapacity = capacity;
    hsize = 0;

}

int heap::insert(const string &id, int key, void *pv) {

    if (hsize == hcapacity) //We were told not to implement resizing. Heap is full.
        return 1;
    else if (hashptr->contains(id)) //Not inserting as id already exists
        return 2;

    ++hsize;
    hdata[hsize].hid = id;
    hdata[hsize].key = key;
    hdata[hsize].voidptr = pv;

    hashptr->insert(id, &hdata[hsize]); //The void pointer now points to the key in heap
    percolateUp(hsize); //Put the size into the heap in proper spot
    return 0;
}

int heap::setKey(const string &id, int key) {
    nodeObject *nodeptr = static_cast<nodeObject *> (hashptr->getPointer(id));
    //getpointer returns a void pointer so it must be casted into nodeObject ptr

    if (nodeptr == NULL)
        return 1; //No node with this id

    int temp = position(nodeptr);
    hdata[temp].key = key; //Set the key to new value
                          //Now we need to move the key to the right place in heap
    
    if (key < hdata[locateNodes(temp, "parent")].key)
        percolateUp(temp);
    else if ((hdata[locateNodes(temp, "left")].key > key) || (hdata[locateNodes(temp, "right")].key > key))
        percolateDown(temp);
    //Now the node has moved to the proper place in the heap
    
    return 0;
}

int heap::deleteMin(string *pId, int *pKey, void *ppData) {
    if (hsize == 0)
        return 1;
    if (pId != NULL) //If pId is supplied, fill it with the Id
        *pId = hdata[1].hid;
    if (pKey != NULL)
        *pKey = hdata[1].key; //If pKey is supplied, fill it with the key
    if (ppData != NULL)
        *(static_cast<void**>(ppData)) = hdata[1].voidptr; //If ppData is supplied, fill it with the void pointer
        //Sable's syntax from in class

    hashptr->remove(hdata[1].hid); //Remove from hashtable
    hdata[1] = hdata[hsize]; //Goal is to move empty spot to the end
                          //Move last spot to first, and put it back in place
    --hsize;
    percolateDown(1);
    return 0;
}

int heap::remove(const string &id, int *pKey, void *ppData) {

    nodeObject *nodeptr = static_cast<nodeObject *> (hashptr->getPointer(id, NULL));
    if (nodeptr == NULL)
        return 1;

    if (pKey != NULL)
        *pKey = nodeptr->key;
    if (ppData != NULL)
        *(static_cast<void**>(ppData)) = hdata[1].voidptr; //Same logic as deleteMin

    int temp = position(nodeptr);
    hdata[temp] = hdata[hsize]; //same logic as deleteMin
                                //Move last element earlier, then put back in right place
    hashptr->remove(id);
    --hsize;

    if ((temp == 1) || (hdata[temp].key >= hdata[locateNodes(temp, "parent")].key))
        percolateDown(temp);
    else
        percolateUp(temp);

    return 0; //Successful removal
}

void heap::percolateUp(int position) {
//Take the position that needs to percolate up, hold on to it
//Once it's not less than the parent, associate id with proper pointer

    nodeObject temp = hdata[position];

    while ((position > 1) && (temp.key < hdata[locateNodes(position, "parent")].key)) {
        hdata[position] = hdata[locateNodes(position, "parent")];
        hashptr->setPointer(hdata[position].hid, &hdata[position]);
        position = locateNodes(position, "parent");
    }
    hdata[position] = temp;
    hashptr->setPointer(hdata[position].hid, &hdata[position]);
}

void heap::percolateDown(int position) {
//Similar strategy to percolateUp
//Pseudocode from class and wiki page
    nodeObject temp = hdata[position];
    while (position*2 <= hsize) {
        if ((temp.key > hdata[locateNodes(position, "left")].key) && (hdata[locateNodes(position, "right")].key >= hdata[locateNodes(position, "left")].key)) {
            hdata[position] = hdata[locateNodes(position, "left")];
            hashptr->setPointer(hdata[position].hid, &hdata[position]);
            position = locateNodes(position, "left");
        }
        
        else if ((temp.key > hdata[locateNodes(position, "right")].key) && (hdata[locateNodes(position, "left")].key >= hdata[locateNodes(position, "right")].key)) {
            hdata[position] = hdata[locateNodes(position, "right")];
            hashptr->setPointer(hdata[position].hid, &hdata[position]);
            position = locateNodes(position, "right");
        }

        else
            break;
    }

    hdata[position] = temp; //All swaps finished, position to percolate 
                           //down now in proper position
    
    hashptr->setPointer(hdata[position].hid, &hdata[position]);
}

int heap::locateNodes(int index, string relation) {
    if (relation == "right")
        return (index << 1) + 1;
    else if (relation == "left")
        return (index << 1);
    else if (relation == "parent")
        return (index >> 1);
    else
        return 0;
}

int heap::position(nodeObject *nodeptr) { return nodeptr - &hdata[0]; }
