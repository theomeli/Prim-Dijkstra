#include <string.h>

#include "edge.h"
//---------------------------------------------------------------------------
edge::edge(){}


edge::edge(long aTreeId, long aNodeId, short aWeight){
	treeId = aTreeId;
	nodeId = aNodeId;
	weight = aWeight;
}


short edge::getWeight(){return weight;}


long& edge::getNodeId(){return nodeId;}


long edge::getTreeId(){return treeId;}
