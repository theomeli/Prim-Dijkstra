#include <string.h>

#include "dijkstra.h"

//---------------------------------------------------------------------------

		dijkstra::dijkstra(hashTable* aGraph){
			graph = aGraph;
			//q = new long[44953];
			d = new long[numOfV];
			p = new long[numOfV];
			for (int i = 0; i < 44953; i++) {
				d[i] = infinite;  				//���� �� d ��� �� �� ������
				p[i] = -1;        				//��� ����������� ������ ��� ��������� -1
			}

			//���������� �� ����
			adjacentToS = minHeap();
		}


		void dijkstra::update_cost(edge e){
			long nId = e.getNodeId();
			long tId = e.getTreeId();
			long weight = e.getWeight();
			if (d[nId] > d[tId] + weight){
				d[nId] = d[tId] + weight;
				p[nId] = tId;
			}
		}


		void dijkstra::dijkstra_algorithm(long x){
			//���� ��� ������� ��� ��� ������ x
			avlTree neighb;
			d[x] = 0;
			neighb = graph->getNeighbors(x);
			neighb.inorder(neighb.getRoot(), &adjacentToS);
			graph->getIsInSetS()[x] = true;

			edge e;
			long bucket;
			long treeId;
			avlNode* node = new avlNode;
			while (adjacentToS.getCurrentSize() != 1){
				e = adjacentToS.getMin();
				treeId = e.getTreeId();
				neighb = graph->getNeighbors(treeId);
				neighb.inorder(neighb.getRoot(), &adjacentToS);
				graph -> searchInHash(treeId, &bucket);
				if(!graph->getIsInSetS()[bucket]){
					graph->getIsInSetS()[bucket] = true;

					node = graph->getNeighbors(treeId).getRoot();
					inorder(node);
				}
			}

		}


		void dijkstra::inorder(avlNode *cur){
			if (!(cur->left == NULL)) inorder(cur->left);
			//��������� �� ������ ��� �������� ��� �������� ����� cur
			long treeId = cur->getTreeId();
			avlTree tree = graph->getNeighbors(treeId);
			//��������� ����������� ����� edge ��� �������� �� ����� //��� �� �������� ��� ����
			edge e = tree.createEdge(*cur);
			update_cost(e);

			if (!(cur->right == NULL)) inorder(cur->right);
		}



