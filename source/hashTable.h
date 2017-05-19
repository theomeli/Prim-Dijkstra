#ifndef hashTableH
#define hashTableH
#include "avlTree.h"


class hashTable{

	private:
		struct neighborsOfV{
			long v;
			avlTree neighbors;      //an AVL tree with the neighbors of the element
		}typedef neighborsOfV;

		long D; 			// For |V| = 44953 vertices, the first prime numnber that is bigger
						// than 2|V| such as to be achieved loading factor at least 0.5
		neighborsOfV* ht;   		//hashTable
		bool *empty;    		//it shows if a position of hashTable is empty or not
		bool *isInSetS;         	//it becomes true if bucket's element has entered set S
		long vectorsInS; 		//the number of vertices that entered S
		bool* neverUsed;		//a flag that is used for the deletion of array's elements


	public:
		hashTable();


		~hashTable();


		bool* getIsInSetS();


		long getVectorsInS();


		bool searchInHash(long key, long* bucket);


		avlTree getNeighbors(long v);


		void insertToHash(long key, long neighborsKey, short weight);


		void deleteAnEdge(long treeId, long nodeId);


		void hashTable::helpDeleteAnEdge(long treeId, long nodeId, long* bucket);


		long* commonNeighbors(long AId, long BId);


		void openfile();

};
#endif
