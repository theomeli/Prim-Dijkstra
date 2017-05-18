#include "avlTree.h"
//#include <iostream.h>
//#include <fstream.h>
#include <string.h>

//---------------------------------------------------------------------------

		avlTree::avlTree(){
			root = NULL;
			treeId = 0;
		}


		short avlTree::getWeight(avlNode aNode){return aNode.getWeight();}


		long avlTree::getNodeId(avlNode aNode){return aNode.getNodeId();}


		long avlTree::getTreeId(){return treeId;}


		avlNode* avlTree::getRoot(){return root;}


		edge avlTree::createEdge(avlNode anAdjacent){
			edge e(anAdjacent.getTreeId(), anAdjacent.getNodeId(), anAdjacent.getWeight());
			return e;
		}


		//���������� ������
		avlNode* avlTree::newnode(long aTreeId, long num, short aWeight){
			avlNode *neos = new avlNode(aTreeId, num, aWeight);
			neos->left = NULL;
			neos->right = NULL;
			neos->bf = 0;
			return(neos);
		}


		//////////////////////////////////////
		//////////////////////////////////////���������� ������
		/////////////////////////////////////
		void avlTree::rotate(avlNode *cur){
			avlNode *ptr = new avlNode(treeId, cur->getNodeId(), cur->getWeight());
			avlNode *child;
			avlNode *gchild;

			//��������� �� ������ ��� ��� �����������
			if (cur->bf == 2) child = cur->right;
			else child = cur->left;
			if (child->bf == 1) gchild = child->right;
			else gchild = child->left;

			//��������� �����-�����
			if(cur->bf == 2 && child->bf == 1){
				cur->bf = 0;
				child->bf = 0;
				ptr->getNodeId() = cur->getNodeId();
				cur->getNodeId() = child->getNodeId();
				child->getNodeId() = ptr->getNodeId();
				ptr->left = cur->left;
				cur->left = cur->right;
				cur->right = child->right;
				child->right = child->left;
				child->left = ptr->left;
			}

			//��������� ��������-��������
			if(cur->bf == -2 && child->bf == -1){
				cur->bf = 0;
				child->bf = 0;
				ptr->getNodeId() = cur->getNodeId();
				cur->getNodeId() = child->getNodeId();
				child->getNodeId() = ptr->getNodeId();
				ptr->left = cur->left;
				cur->left = child->left;
				child->left = child->right;
				child->right = cur->right;
				cur->right = ptr->left;
			}

			//��������� �����-��������
			if(cur->bf == 2 && child->bf == -1){
				cur->bf = 0;
				if(gchild->bf == 1) {
					child->bf = -1;
					gchild->bf = 0;
				}
				else if(gchild->bf == -1){
					child->bf = 0;
					gchild->bf = 1;
				}
				else {
					child->bf = 0;
					gchild->bf = 0;
				}

				ptr->getNodeId() = cur->getNodeId();
				cur->getNodeId() = gchild->getNodeId();
				gchild->getNodeId() = ptr->getNodeId();
				ptr->left = cur->left;
				cur->left = child->left;
				child->left = gchild->right;
				gchild->right = gchild->left;
				gchild->left = ptr->left;
			}

			//��������� ��������-�����
			if(cur->bf == -2 && child->bf == 1){
				cur->bf = 0;
				if(gchild->bf == 1) {
					child->bf = -1;
					gchild->bf = 0;
				}
				else if(gchild->bf == -1) {
					child->bf = 0;
					gchild->bf = 1;
			}
			else {
				child->bf = 0;
				gchild->bf = 0;
			}

				ptr->getNodeId() = cur->getNodeId();
				cur->getNodeId() = gchild->getNodeId();
				gchild->getNodeId() = ptr->getNodeId();
				ptr->right = cur->right;
				cur->right = child->right;
				child->right = gchild->left;
				gchild->left = gchild->right;
				gchild->right = ptr->right;
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////�������� ��������� ��� ��������
		/////////////////////////////////////
		bool avlTree::insBalance(long num, avlNode *cur){
			//A� ������� ���� ����� ������������
			if (num == cur->getNodeId()) return true;
			bool k;
			//A� �� ����������� ���� ����� ��������� ���������
			if (num > cur->getNodeId()) k = insBalance(num, cur->right);
			else k = insBalance(num, cur->left);

			//A� � ������ ��� ��� ����� ����������� ��� ������ ���� ������������
			if (!k){
				return false;
			}
			//�����������
			else{
				//�� ������ ��� ����� ��������� ��� �������� ������ ��� ���������
				if (num > cur->getNodeId()) cur->bf++;
				else cur->bf--;
				//�� ����� 0 �� ������ ��� ���� ��� ��������
				if (cur->bf == -1 || cur->bf == 1){
					return true;
				}
				//����������� �� ����� 2 � -2 ���������� ����������
				else{
					if (cur->bf == -2 || cur->bf == 2) rotate(cur);
					return false;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////�������� ������
		/////////////////////////////////////
		void avlTree::insertToAvl(long num, short weight){
			//�������� ���������� ��� �� ������� ������ ��� ������� of ��� �� ��� ����� �� ID num
			avlNode *currentTree, *ptr;
			//������� ��� ��������� ������� ���� currentTree
			currentTree = root;
			//���������� ��� ���� ������
			ptr = newnode(treeId, num, weight);

			//�� ��� ������ �������� ��� ������, � ���� ������ �������� �� ����
			if (root == NULL){
				root = ptr;
				return;
			}

			//������
			while(1){
				//�� ����������� ���� ��������� �������� ��� ������� ���, ��� ��� ��������� ������
				if(currentTree->getNodeId() == num) return;
				//����������� ���������� ����� � �������� ���������
				if(currentTree->getNodeId() < num){
					//�� �������� �� "�����"
					if(currentTree->right == NULL){
						//����������� ��� �����
						currentTree->right = ptr;
						//��� ��������� ���� ��� ���������� ��� ��� ���� ����� ��� ����� ���� ���������
						insBalance(num, currentTree);
						return;
					}
					//����������� ���������
					else{
						currentTree = currentTree->right;
					}
				}
				else{
					//A��������� �� �������� �� "�����"
					if(currentTree->left == NULL){
						//����������� ��� �����
						currentTree->left = ptr;
						//��� ��������� ���� ��� ���������� ��� ��� ���� ����� ��� ����� ���� ���������
						insBalance(num, currentTree);
						return;
					}
					//����������� ���������
					else currentTree = currentTree->left;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////�������� ��������� ��� ��������
		/////////////////////////////////////
		bool avlTree::delBalance(int num, avlNode *cur){
			//�� ������� ���� ����� ������������
			if (num == cur->getNodeId()) return true;
			bool k;
			//�� ��� ����������� ���� ����� ��������� ���������
			if (num > cur->getNodeId()) k = delBalance(num, cur->right); else k = delBalance(num, cur->left);

			//�� � ������ ��� ��� ����� ����������� ��� ������ ���� ������������
			if (!k){
				return false;
			}
			//������
			else{
				//�� ������ ��� ����� ��������� ��� �������� ������ ��� ���������
				if (num>cur->getNodeId()) cur->bf--; else cur->bf++;
				//�� ����� +1 � -1 �� ������ ��� ���� ��� ��������
				if (cur->bf==1 || cur->bf==-1){
					return false;
				}
				//������ �� ����� 2 � -2 ���������� ����������
				else{
					if (cur->bf==-2 || cur->bf==2) rotate(cur);
					return true;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////�������� ������
		/////////////////////////////////////
		void avlTree::remove(long num){

			//�� ��� ������ �������� ��� ������, ������������
			if (root == NULL){
				return;
			}

			//�������� ��� �������� �����
			avlNode *current;

			//� ������ ������ �������� ��� ��� ����
			current = root;

			while(1){
				//�� ����������� ���� ��������� ��� ������������ �� ��� ��������� ����� ���
				//�� �������� ��������� � �� ��� ������������ ����� ��� �� ���� ��������� �� ����:
				if(current->getNodeId() == num){
					//��� ������� �� ���� ��������� �����
					avlNode *ptr;
					ptr = current;

					//������ ��� ����� ��� �������� ������
					avlNode *edge;
					if(current->left != NULL || current->right != NULL){
						bool f = false;
						//�� ���� �������� �����
						if(current->left != NULL){
							edge = current;
							current = current->left;
							//��������� �� ���������� ��� �� ��������
							//�� �e���� �� ����������� �����
							while(current->right != NULL) {
								edge = current;
								current = current->right;
								f = true;
							}
							ptr->getNodeId() = current->getNodeId();
						}
						else{
							//������ ��������� �� ��������� ��� �����
							edge = current;
							current = current->right;
							while(current->left != NULL)
							{edge = current;
							current = current->left;
							f = true;
						}
							ptr->getNodeId() = current->getNodeId();
						}
						if (f) {
							edge->right = current->right;
							edge->bf--;
						}
						else {
							edge->left = current->left;
							edge->bf++;
						}
						if (edge->bf == -2 || edge->bf == 2) rotate(edge);
					}
					else{
						//����������� ��� ����������
						delBalance(edge->getNodeId(), root);
						return;
					}
				}
				//�� ���� ��������� ���������� ����� � �������� ���������
				if(current->getNodeId() < num){
					//��� �� �������� �� "�����"
					if(current->right == NULL){
						//������������
						return;
					}
					//������ ���������
					else{
						current = current->right;
					}
				}
				else{
					//���������� �� �������� �� "�����"
					if(current->left == NULL){
						//������������
						return;
					}
					//������ ���������
					else{
						current = current->left;
					}
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////�������� �������������
		/////////////////////////////////////
		void avlTree::inorder(avlNode *cur, minHeap *adjacentToAdd){
			if (!(cur->left == NULL)) inorder(cur->left, adjacentToAdd);
			//��������� ����������� ����� edge ��� �� �������� ��� ����
			edge e = createEdge(*cur);
			adjacentToAdd->insertToHeap(e);
//			outpFile  << ", " << cur->id;
			if (!(cur->right == NULL)) inorder(cur->right, adjacentToAdd);
		}



		long* avlTree::inorderToArray(avlNode *cur){
			long* result = new long;
			int i = 0;
			if (!(cur->left == NULL)) inorderToArray(cur->left);
			result[i++] = cur->getNodeId();
			if (!(cur->right == NULL)) inorderToArray(cur->right);
			return result;
		}

