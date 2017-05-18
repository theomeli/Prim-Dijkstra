//---------------------------------------------------------------------------
#ifndef primH
#define primH
#include "edge.h"
#include "avlNode.h"
#include "hashTable.h"
#include <iostream.h>

//---------------------------------------------------------------------------
class prim{

	private:
		edge* selectedEdges;
		hashTable* graph;
		minHeap adjacentToS;
		long cost;


	public:
		prim::prim(hashTable* aGraph);


		void prim::prim_algorithm();


		long prim::getCost(){return cost;};

};

#endif
