#ifndef avlTreeH
#define avlTreeH
#include "avlNode.h"
#include "minHeap.h"


//---------------------------------------------------------------------------
class avlTree{

	private:

		avlNode* root;

		//�� ID ��� ������
		long treeId;


	public:


		avlTree();

		short getWeight(avlNode aNode);

		long getNodeId(avlNode aNode);

		long getTreeId();

		avlNode* getRoot();


		edge createEdge(avlNode anAdjacent);


		//���������� ������
		avlNode *newnode(long aTreeId, long num, short aWeight);

		//���������� ������
		void rotate(avlNode *cur);


		//�������� ��������� ��� ��������
		bool insBalance(long num, avlNode *cur);

		//�������� ������
		void insertToAvl(long num, short weight);

		//�������� ��������� ��� ��������
		bool delBalance(int num, avlNode *cur);

		//�������� ������
		void remove(long num);

		//�������� �������������
		void inorder(avlNode *cur, minHeap *adjacentToAdd);

		long* inorderToArray(avlNode *cur);

};
#endif
