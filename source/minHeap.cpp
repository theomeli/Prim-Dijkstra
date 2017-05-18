#include "minHeap.h"
#include <string.h>
//---------------------------------------------------------------------------
minHeap::minHeap(){
	maxSize = 88303;   			//μέγιστο μέγεθος του σωρού όσο το πλήθος των ακμών
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

	//η μικρότερη ακμή αποθηκεύεται και επιστρέφεται
	minEdge = heap[1];

	//αποθηκεύω το τελευταίο στοιχείο του σωρού και ελλαττώνν το currentSize κατά ένα
	edge lastEdge = heap[currentSize--];

	//αναζητούμε πού θα εισαχθεί το τελευταίο στοιχείο του σωρού
	//ξεκινώντας από τη ρίζα

	long i = 1;
	long ci = 2;
	short weight = lastEdge.getWeight();
	while (ci <= currentSize){
		//επιλέγω το μικρότερο από τα δύο παιδιά
		if (heap[ci].getWeight() > heap[ci+1].getWeight())
			ci++;

			//ελέγχω αν το μικρότερο από τα δύο παιδιά είναι μικρότερο της lastEdge
			if (heap[ci].getWeight() >= weight)  break;      //είναι μικρότερο
			else{
				heap[i] = heap[ci];  //το μικρότερο παιδί γίνεται γονιός
				i = ci;              //και κατεβαίνουμε ένα επίπεδο στο δέντρο
				ci *= 2;
			}


	}
	//έχουμε βρει το σημείο που θα μπει ο lastEdge
	heap[i] = lastEdge;

	return *this;
}

