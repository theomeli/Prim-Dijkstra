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
		hashTable* graph;    					//� hashTable ������� �� �� �����
		minHeap adjacentToS; 					//�� ������ ��� ������� ��� ����� �� ���� d ������
		static const long infinite = 2147483647;
		static const long numOfV = 44953;
		long* q;       							//� ������� �� ��� ������� ��� ����� ��������
		long* d; 								//� ������� D �� ��� �������� ��������� ���������� ��� ���� �������
		long* p; 								//� ������� P �� ��� �������� ����������� ������


	public:
		dijkstra(hashTable* aGraph);


		void update_cost(edge e);


		void dijkstra_algorithm(long x);


		void dijkstra::inorder(avlNode *cur);

};
#endif
