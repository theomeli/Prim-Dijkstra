#ifndef avlNodeH
#define avlNodeH
#include "edge.h"

//---------------------------------------------------------------------------
class avlNode: public edge{
	public:
		//�������� �����
		avlNode *left;
		//���� �����
		avlNode *right;
		//��������
		int bf;

		avlNode();

		avlNode(long aTreeId, long aNodeId, short aWeight);

		~avlNode();

};
#endif
