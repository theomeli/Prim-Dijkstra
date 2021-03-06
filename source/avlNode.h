#ifndef avlNodeH
#define avlNodeH
#include "edge.h"

//---------------------------------------------------------------------------
class avlNode: public edge{
	public:
		//left child
		avlNode *left;
		//right child
		avlNode *right;
		//balancing
		int bf;

		avlNode();

		avlNode(long aTreeId, long aNodeId, short aWeight);

		~avlNode();

};
#endif
