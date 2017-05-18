#include "prim.h"

		prim::prim(hashTable* aGraph){
			graph = aGraph;
			selectedEdges = new edge;
			adjacentToS = minHeap();
			cost = 0;
		}


		void prim::prim_algorithm(){
			avlTree neighb;
			long edgesInS;
			edge min;
			long treeId;
			long nodeId;
			// ���� ��� ������� ��� ��� ����� 0
			graph->getIsInSetS()[0] = true;    //���� ��� ����� 0 ��� ������
			neighb = graph->getNeighbors(0);
			//��������� ������� ��� ���������� ����� �� � ������ �����������
			//��� n �������, �� ����� �������� n-1 �����
			while (edgesInS != graph->getVectorsInS()-1){
				min = adjacentToS.getMin();
				treeId = min.getTreeId();
				nodeId = min.getNodeId();
				//�� ���� ������ ����� ���� ��� S ��� � ����� ���
				if ((graph->getIsInSetS()[treeId] && !graph->getIsInSetS()[nodeId]) ||
				(!graph->getIsInSetS()[treeId] && graph->getIsInSetS()[nodeId])) {
					selectedEdges[sizeof(selectedEdges)+1] = min;
					cost += min.getWeight();
					cout << getCost();
				}
				else
					break;
			}
			if (edgesInS != graph->getVectorsInS()-1){
				cout << getCost();
				return;
			}
			else{
				cout << "The network is not connected therefore has no spanning tree";
				return;
			}
		}

