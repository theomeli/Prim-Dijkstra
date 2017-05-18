#ifndef hashTableH
#define hashTableH
#include "avlTree.h"


class hashTable{

	private:
		struct neighborsOfV{
			long v;
			avlTree neighbors;      //��� AVL ������ �� ���� �������� ��� ���������
		}typedef neighborsOfV;

		long D; 				// ��� |V| = 44953 �������, � ������ ������ ������� �����������
								// ��� 2|V| ���� �� ���������� ����������� ���������� �������� 0.5
		neighborsOfV* ht;   	//o HashTable
		bool *empty;    		//������� �� ��� ���� ��� HashTable ����� ���� � ���
		bool *isInSetS;         //������� ������ ���� �� �������� ��� bucket ���� ���� ��� ������ S
		long vectorsInS; 		//�� ������ ��� ������� ��� �������� ��� S
		bool* neverUsed;		//������ ��� ��������������� ��� �� �������� ��������� ��� ������


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
