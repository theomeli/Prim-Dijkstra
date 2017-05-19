//#include <iostream.h>
//#include "hashTable.h"


#ifndef dijkstraH
#define dijkstraH
//#include <iostream.h>
#include "minHeap.h"
#include "edge.h"
#include "avlNode.h"
#include "hashTable.h"


//---------------------------------------------------------------------------

class dijkstra{

	private:
		hashTable* graph;    				//the hashtable with the graph
		minHeap adjacentToS; 				//the set of vertices that haven't d as infinite anymore
		static const long infinite = 2147483647;
		static const long numOfV = 44953;
		long* q;       					//the array with the vertices that have already inserted
		long* d; 					//the array with the current shortest distances of each vertex
		long* p; 					//the array with the current previous vertex


	public:
		dijkstra(hashTable* aGraph);


		void update_cost(edge e);


		void dijkstra_algorithm(long x);


		void dijkstra::inorder(avlNode *cur);

};
#endif
