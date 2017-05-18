#ifndef avlNodeH
#define avlNodeH
#include "edge.h"

//---------------------------------------------------------------------------
class avlNode: public edge{
	public:
		//Αριστερό τέκνο
		avlNode *left;
		//Δεξί τέκνο
		avlNode *right;
		//Στάθμιση
		int bf;

		avlNode();

		avlNode(long aTreeId, long aNodeId, short aWeight);

		~avlNode();

};
#endif
