#ifndef avlTreeH
#define avlTreeH
#include "avlNode.h"
#include "minHeap.h"


//---------------------------------------------------------------------------
class avlTree{

	private:

		avlNode* root;

		//το ID του κόμβου
		long treeId;


	public:


		avlTree();

		short getWeight(avlNode aNode);

		long getNodeId(avlNode aNode);

		long getTreeId();

		avlNode* getRoot();


		edge createEdge(avlNode anAdjacent);


		//Δημιουργία κόμβου
		avlNode *newnode(long aTreeId, long num, short aWeight);

		//Περιστροφή Κόμβων
		void rotate(avlNode *cur);


		//Ανανέωση στάθμισης από εισαγωγή
		bool insBalance(long num, avlNode *cur);

		//Εισαγωγή Κόμβου
		void insertToAvl(long num, short weight);

		//Ανανέωση στάθμισης από διαγραφή
		bool delBalance(int num, avlNode *cur);

		//Διαγραφή κόμβου
		void remove(long num);

		//Εμφάνιση Αποτελεσμάτων
		void inorder(avlNode *cur, minHeap *adjacentToAdd);

		long* inorderToArray(avlNode *cur);

};
#endif
