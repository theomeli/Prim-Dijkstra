
#include "avlNode.h"
#include <string.h>

avlNode::avlNode(){}


avlNode::avlNode(long aTreeId, long aNodeId, short aWeight){
	edge(aTreeId, aNodeId, aWeight);
	left = NULL;
	right = NULL;
}


avlNode::~avlNode(){
	delete left;
	delete right;
}
