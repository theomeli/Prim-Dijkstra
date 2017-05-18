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
			// Έστω ότι ξεκινάω από τον κόμβο 0
			graph->getIsInSetS()[0] = true;    //βάζω τον κόμβο 0 στο σύνολο
			neighb = graph->getNeighbors(0);
			//τερματική συνθήκη του αλγορίθμου είναι αν ο γράφος αποτελείται
			//από n κορυφές, να έχουν εισαχθεί n-1 ακμές
			while (edgesInS != graph->getVectorsInS()-1){
				min = adjacentToS.getMin();
				treeId = min.getTreeId();
				nodeId = min.getNodeId();
				//αν ένας κόμβος είναι μέσα στο S και ο άλλος όχι
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

