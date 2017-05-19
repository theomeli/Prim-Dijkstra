#include "minHeap.h"
#include <string.h>
//---------------------------------------------------------------------------
minHeap::minHeap(){
	maxSize = 88303;   			//the maximum size of the heap which equals the number of edges
	currentSize = 0;
	heap = new edge[maxSize];
}


minHeap::~minHeap(){
	delete [] heap;
}


long minHeap::getCurrentSize(){return currentSize;}


edge minHeap::getMin(){
	if (currentSize == 0)
		return edge();
	else
		return heap[1];
}


minHeap minHeap::insertToHeap(edge anEdge){
	if (currentSize == maxSize)
		return *this;

	short weight = anEdge.getWeight();
	long i = ++currentSize;
	while (heap[i/2].getWeight() > weight){
		heap[i] = heap[i/2];
		i = i/2;
	}
	heap[i] = anEdge;
	return *this;
}


minHeap minHeap::deleteMin(edge& minEdge){
	if (currentSize == 0)
		return *this;

	//the minimal edge is stored and is returned
	minEdge = heap[1];

	//the last element of the heap is stored and currentSize is decreased by one
	edge lastEdge = heap[currentSize--];

	//we search where will be inserted the last element of the heap
	//begining from the root
	long i = 1;
	long ci = 2;
	short weight = lastEdge.getWeight();
	while (ci <= currentSize){
		//we choose the smallest of the two children
		if (heap[ci].getWeight() > heap[ci+1].getWeight())
			ci++;

			//we check if the smallest of the two children is smaller than lastEdge
			if (heap[ci].getWeight() >= weight)  break;      //it is smaller
			else{
				heap[i] = heap[ci];  //the smallest child becomes parent
				i = ci;             
				ci *= 2;
			}


	}
	//we have found the point that lastEdge will enter
	heap[i] = lastEdge;

	return *this;
}

