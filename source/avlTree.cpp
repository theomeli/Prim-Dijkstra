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


		//creation of a node
		avlNode* avlTree::newnode(long aTreeId, long num, short aWeight){
			avlNode *neos = new avlNode(aTreeId, num, aWeight);
			neos->left = NULL;
			neos->right = NULL;
			neos->bf = 0;
			return(neos);
		}


		//////////////////////////////////////
		//////////////////////////////////////rotation of nodes
		/////////////////////////////////////
		void avlTree::rotate(avlNode *cur){
			avlNode *ptr = new avlNode(treeId, cur->getNodeId(), cur->getWeight());
			avlNode *child;
			avlNode *gchild;

			//we define the nodes we are interested in
			if (cur->bf == 2) child = cur->right;
			else child = cur->left;
			if (child->bf == 1) gchild = child->right;
			else gchild = child->left;

			//the case of a right-right rotation
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

			//the case of a left-left rotation
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

			//the case of a right-left rotation
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

			//the case of a left-right rotation
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
		//////////////////////////////////////refreshing the balancing after an insertion
		/////////////////////////////////////
		bool avlTree::insBalance(long num, avlNode *cur){
			//if we reach the node, we return
			if (num == cur->getNodeId()) return true;
			bool k;
			//if we don't reach the node, we continue
			if (num > cur->getNodeId()) k = insBalance(num, cur->right);
			else k = insBalance(num, cur->left);

			//if the value of the node that we left didn't change value, we return
			if (!k){
				return false;
			}
			else{
				//if we came from the right, we increase the balancing, else we decrease it
				if (num > cur->getNodeId()) cur->bf++;
				else cur->bf--;
				//if it is 0, the nodes above don't change
				if (cur->bf == -1 || cur->bf == 1){
					return true;
				}
				//Differenly if it is 2 or -2, it needs rotation
				else{
					if (cur->bf == -2 || cur->bf == 2) rotate(cur);
					return false;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////insertion of a node
		/////////////////////////////////////
		void avlTree::insertToAvl(long num, short weight){
			//we define variables for the existing tree and the new node with id num
			avlNode *currentTree, *ptr;
			currentTree = root;
			//creation of the new node
			ptr = newnode(treeId, num, weight);

			//if there is no data in the tree, the new node is defined as a root
			if (root == NULL){
				root = ptr;
				return;
			}

			while(1){
				//if we are in this node, we don't change anything
				if(currentTree->getNodeId() == num) return;
				//else we move right of left appropriately
				if(currentTree->getNodeId() < num){
					//if we reach the terminal
					if(currentTree->right == NULL){
						//we add a node
						currentTree->right = ptr;
						//we change all the balancings from the root to this node
						insBalance(num, currentTree);
						return;
					}
					//else we move on
					else{
						currentTree = currentTree->right;
					}
				}
				else{
					//we act the same as the above if part
					if(currentTree->left == NULL){
						currentTree->left = ptr;
						insBalance(num, currentTree);
						return;
					}
					else currentTree = currentTree->left;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////refreshing balancing after a deletion
		/////////////////////////////////////
		bool avlTree::delBalance(int num, avlNode *cur){
			//if we reach the node, we return 
			if (num == cur->getNodeId()) return true;
			bool k;
			//if we don't reach the node, we continue
			if (num > cur->getNodeId()) k = delBalance(num, cur->right); else k = delBalance(num, cur->left);

			//if the value of the node that we left didn't change value, we return
			if (!k){
				return false;
			}
			else{
				//if we came from the right, we decrease the balancing, else we increase it
				if (num>cur->getNodeId()) cur->bf--; else cur->bf++;
				//if it became +1 or -1, the nodes above don't change
				if (cur->bf==1 || cur->bf==-1){
					return false;
				}
				//if it became 2 or -2, it needs rotation
				else{
					if (cur->bf==-2 || cur->bf==2) rotate(cur);
					return true;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////deletion of a node
		/////////////////////////////////////
		void avlTree::remove(long num){

			//if we don't have data in the tree, we return 
			if (root == NULL){
				return;
			}

			//we define the current node
			avlNode *current;

			//the current node begins from the root
			current = root;

			while(1){
				//if we are at the node we want, we exchange it with the most right 
				//one of the left or with the most left one of the right subtree 
				if(current->getNodeId() == num){
					//we keep the node in a current one
					avlNode *ptr;
					ptr = current;

					//we search for the parent of the extreme node
					avlNode *edge;
					if(current->left != NULL || current->right != NULL){
						bool f = false;
						//if it has a left child
						if(current->left != NULL){
							edge = current;
							current = current->left;
							//we find the biggest one from the left
							while(current->right != NULL) {
								edge = current;
								current = current->right;
								f = true;
							}
							ptr->getNodeId() = current->getNodeId();
						}
						else{
							//else we find the smallest one from the right
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
						//refreshing the balancing
						delBalance(edge->getNodeId(), root);
						return;
					}
				}
				//in any other case we move right or left
				if(current->getNodeId() < num){
					//if we reach the terminal, we return
					if(current->right == NULL){
						return;
					}
					//else we move on
					else{
						current = current->right;
					}
				}
				else{
					//we act the same as the above if part
					if(current->left == NULL){
						return;
					}
					else{
						current = current->left;
					}
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////Displaying the results
		/////////////////////////////////////
		void avlTree::inorder(avlNode *cur, minHeap *adjacentToAdd){
			if (!(cur->left == NULL)) inorder(cur->left, adjacentToAdd);
			//we create objects of type edge and we add them to the heap
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

