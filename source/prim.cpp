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
			//let us begin from node 0
			//we put node 0 in the set
			graph->getIsInSetS()[0] = true;
			neighb = graph->getNeighbors(0); 
			//algorith's terminal condition is if graph is consisted by n vertices,
                        //to have been inserted n-1 edges
			while (edgesInS != graph->getVectorsInS()-1){
				min = adjacentToS.getMin();
				treeId = min.getTreeId();
				nodeId = min.getNodeId();
				//if a node is in S and the other is not
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

