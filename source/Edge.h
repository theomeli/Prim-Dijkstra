//---------------------------------------------------------------------------

#ifndef EdgeH
#define EdgeH
//---------------------------------------------------------------------------
class edge{
	private:
		long treeId, nodeId; 		//�� ID ��� ������ ��� ������� ��� ��� ������� ���
		short weight;


	public:
		edge();

		edge(long aTreeId, long aNodeId, short aWeight);

		short getWeight();

		long& getNodeId();

		long getTreeId();

};
#endif
