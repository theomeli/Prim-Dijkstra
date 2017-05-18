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
		hashTable* graph;    					//Ο hashTable πίνακας με το γράφο
		minHeap adjacentToS; 					//Το σύνολο των κορυφών που πάυει να έχει d άπειρο
		static const long infinite = 2147483647;
		static const long numOfV = 44953;
		long* q;       							//Ο πίνακας με τις κορυφές που έχουν εισαχθεί
		long* d; 								//Ο πίνακας D με τις εκάστοτε βέλτιστες αποστάσεις της κάθε κορυφής
		long* p; 								//Ο πίνακας P με την εκάστοτε προηγούμενη κορυφή


	public:
		dijkstra(hashTable* aGraph);


		void update_cost(edge e);


		void dijkstra_algorithm(long x);


		void dijkstra::inorder(avlNode *cur);

};
#endif
