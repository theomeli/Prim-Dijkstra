#ifndef hashTableH
#define hashTableH
#include "avlTree.h"


class hashTable{

	private:
		struct neighborsOfV{
			long v;
			avlTree neighbors;      //Ένα AVL δέντρο με τους γείτονες του στοιχείου
		}typedef neighborsOfV;

		long D; 				// Για |V| = 44953 κορυφές, ο πρώτος πρώτος αριθμός μεγαλύτερος
								// του 2|V| ώστε να επιτευχθεί τουλάχιστον παράγοντας φόρτωσης 0.5
		neighborsOfV* ht;   	//o HashTable
		bool *empty;    		//Δείχνει αν μια θέση του HashTable είναι κενή ή όχι
		bool *isInSetS;         //Γίνεται αληθής όταν το στοιχείο του bucket έχει μπει στο σύνολο S
		long vectorsInS; 		//Το πλήθος των κορυφών που μπαίνουν στο S
		bool* neverUsed;		//Σημαία που χρησιμοποιείται για τη διαγραφή στοιχείων του πίνακα


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
