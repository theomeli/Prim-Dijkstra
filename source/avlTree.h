#ifndef avlTreeH
#define avlTreeH
#include "avlNode.h"
#include "minHeap.h"


//---------------------------------------------------------------------------
class avlTree{

	private:

		avlNode* root;

		//node's id
		long treeId;


	public:


		avlTree();

		short getWeight(avlNode aNode);

		long getNodeId(avlNode aNode);

		long getTreeId();

		avlNode* getRoot();


		edge createEdge(avlNode anAdjacent);


		//creation of a new node
		avlNode *newnode(long aTreeId, long num, short aWeight);

		//node rotation
		void rotate(avlNode *cur);

		//refreshes the balancing after an insertion
		bool insBalance(long num, avlNode *cur);

		//insertion of a node
		void insertToAvl(long num, short weight);

		//refreshes balancing after deletion
		bool delBalance(int num, avlNode *cur);

		//deletion of a node
		void remove(long num);

		//desplays the results
		void inorder(avlNode *cur, minHeap *adjacentToAdd);

		long* inorderToArray(avlNode *cur);

};
#endif
