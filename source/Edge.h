//---------------------------------------------------------------------------

#ifndef EdgeH
#define EdgeH
//---------------------------------------------------------------------------
class edge{
	private:
		//the id of the node of the tree and its neighbor's
		long treeId, nodeId;
		short weight;


	public:
		edge();

		edge(long aTreeId, long aNodeId, short aWeight);

		short getWeight();

		long& getNodeId();

		long getTreeId();

};
#endif
