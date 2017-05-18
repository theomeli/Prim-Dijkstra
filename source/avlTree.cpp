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


		//Δημιουργία κόμβου
		avlNode* avlTree::newnode(long aTreeId, long num, short aWeight){
			avlNode *neos = new avlNode(aTreeId, num, aWeight);
			neos->left = NULL;
			neos->right = NULL;
			neos->bf = 0;
			return(neos);
		}


		//////////////////////////////////////
		//////////////////////////////////////Περιστροφή Κόμβων
		/////////////////////////////////////
		void avlTree::rotate(avlNode *cur){
			avlNode *ptr = new avlNode(treeId, cur->getNodeId(), cur->getWeight());
			avlNode *child;
			avlNode *gchild;

			//Ορίζονται οι κόμβοι που μας ενδιαφέρουν
			if (cur->bf == 2) child = cur->right;
			else child = cur->left;
			if (child->bf == 1) gchild = child->right;
			else gchild = child->left;

			//Περίπτωση δεξιά-δεξιά
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

			//Περίπτωση αριστερά-αριστερά
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

			//Περίπτωση δεξιά-αριστερά
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

			//Περίπτωση αριστερά-δεξιά
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
		//////////////////////////////////////Ανανέωση στάθμισης από εισαγωγή
		/////////////////////////////////////
		bool avlTree::insBalance(long num, avlNode *cur){
			//Aν φτάσαμε στον κόμβο επιστρέφουμε
			if (num == cur->getNodeId()) return true;
			bool k;
			//Aν δε βρισκόμαστε στον κόμβο προχωράμε κατάλληλα
			if (num > cur->getNodeId()) k = insBalance(num, cur->right);
			else k = insBalance(num, cur->left);

			//Aν ο κόμβος από τον οποίο επιστρέψαμε δεν άλλαξε τιμή επιστρέφουμε
			if (!k){
				return false;
			}
			//Διαφορετικά
			else{
				//Αν ήρθαμε από δεξιά αυξάνουμε την στάθμιση αλλιώς την μειώνουμε
				if (num > cur->getNodeId()) cur->bf++;
				else cur->bf--;
				//Αν έγινε 0 οι κόμβοι πιο πάνω δεν αλλάζουν
				if (cur->bf == -1 || cur->bf == 1){
					return true;
				}
				//Διαφορετικά αν έγινε 2 ή -2 χρειάζεται περιστροφή
				else{
					if (cur->bf == -2 || cur->bf == 2) rotate(cur);
					return false;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////Εισαγωγή Κόμβου
		/////////////////////////////////////
		void avlTree::insertToAvl(long num, short weight){
			//Ορίζουμε μεταβλητές για το υπαρχον δέντρο της σελίδας of και το νέο κόμβο με ID num
			avlNode *currentTree, *ptr;
			//Ανάθεση του τρέχοντος δέντρου στην currentTree
			currentTree = root;
			//Δημιουργία του νέου κόμβου
			ptr = newnode(treeId, num, weight);

			//Αν δεν έχουμε δεδομένα στο δέντρο, ο νέος κόμβος ορίζεται ως ρίζα
			if (root == NULL){
				root = ptr;
				return;
			}

			//Αλλιώς
			while(1){
				//Αν βρισκόμαστε στον ζητούμενο σημαίνει ότι υπάρχει ήδη, άρα δεν αλλάζουμε τίποτα
				if(currentTree->getNodeId() == num) return;
				//Διαφορετικά κινούμαστε δεξιά ή αριστερά κατάλληλα
				if(currentTree->getNodeId() < num){
					//Αν βρεθούμε σε "τέρμα"
					if(currentTree->right == NULL){
						//Προσθέτουμε τον κόμβο
						currentTree->right = ptr;
						//Και αλλάζουμε όλες τις σταθμίσεις από την ρίζα μέχρι τον κόμβο αυτό κατάλληλα
						insBalance(num, currentTree);
						return;
					}
					//Διαφορετικά προχωράμε
					else{
						currentTree = currentTree->right;
					}
				}
				else{
					//Aντίστοιχα αν βρεθούμε σε "τέρμα"
					if(currentTree->left == NULL){
						//Προσθέτουμε τον κόμβο
						currentTree->left = ptr;
						//Και αλλάζουμε όλες τις σταθμίσεις από την ρίζα μέχρι τον κόμβο αυτό κατάλληλα
						insBalance(num, currentTree);
						return;
					}
					//Διαφορετικά προχωράμε
					else currentTree = currentTree->left;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////Ανανέωση στάθμισης από διαγραφή
		/////////////////////////////////////
		bool avlTree::delBalance(int num, avlNode *cur){
			//αν φτάσαμε στον κόμβο επιστρέφουμε
			if (num == cur->getNodeId()) return true;
			bool k;
			//αν δεν βρισκόμαστε στον κόμβο προχωράμε κατάλληλα
			if (num > cur->getNodeId()) k = delBalance(num, cur->right); else k = delBalance(num, cur->left);

			//αν ο κόμβος από τον οποίο επιστρέψαμε δεν άλλαξε τιμή επιστρέφουμε
			if (!k){
				return false;
			}
			//αλλιώς
			else{
				//αν ήρθαμε από δεξιά μειώνουμε την στάθμιση αλλιώς την αυξάνουμε
				if (num>cur->getNodeId()) cur->bf--; else cur->bf++;
				//αν έγινε +1 ή -1 οι κόμβοι πιο πάνω δεν αλλάζουν
				if (cur->bf==1 || cur->bf==-1){
					return false;
				}
				//αλλιώς αν έγινε 2 ή -2 χρειάζεται περιστροφή
				else{
					if (cur->bf==-2 || cur->bf==2) rotate(cur);
					return true;
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////Διαγραφή κόμβου
		/////////////////////////////////////
		void avlTree::remove(long num){

			//Αν δεν έχουμε δεδομένα στο δέντρο, επιστρέφουμε
			if (root == NULL){
				return;
			}

			//Ορίζουμε τον τρέχοντα κόμβο
			avlNode *current;

			//Ο τρέχων κόμβος ξεκινάει από την ρίζα
			current = root;

			while(1){
				//Αν βρισκόμαστε στον ζητούμενο τον ανταλλάσουμε με τον δεξιότερο κόμβο από
				//το αριστερό υποδέντρο ή με τον αριστερότερο κόμβο από το δεξί υποδέντρο ως εξής:
				if(current->getNodeId() == num){
					//τον κρατάμε σε έναν προσωρινό κόμβο
					avlNode *ptr;
					ptr = current;

					//ζητάμε τον γονέα του ακριανού κόμβου
					avlNode *edge;
					if(current->left != NULL || current->right != NULL){
						bool f = false;
						//αν έχει αριστερό τέκνο
						if(current->left != NULL){
							edge = current;
							current = current->left;
							//βρίσκουμε το μεγαλύτερο από τα αριστερά
							//με δeίκτη αν προχωρήσαμε δεξιά
							while(current->right != NULL) {
								edge = current;
								current = current->right;
								f = true;
							}
							ptr->getNodeId() = current->getNodeId();
						}
						else{
							//αλλιώς βρίσκουμε το μικρότερο από δεξιά
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
						//ανανεώνουμε τις σταθμίσεις
						delBalance(edge->getNodeId(), root);
						return;
					}
				}
				//σε άλλη περίπτωση κινούμαστε δεξιά ή αριστερά κατάλληλα
				if(current->getNodeId() < num){
					//και αν βρεθούμε σε "τέρμα"
					if(current->right == NULL){
						//επιστρέφουμε
						return;
					}
					//αλλιώς προχωράμε
					else{
						current = current->right;
					}
				}
				else{
					//αντίστοιχα αν βρεθούμε σε "τέρμα"
					if(current->left == NULL){
						//επιστρέφουμε
						return;
					}
					//αλλιώς προχωράμε
					else{
						current = current->left;
					}
				}
			}
		}


		//////////////////////////////////////
		//////////////////////////////////////Εμφάνιση Αποτελεσμάτων
		/////////////////////////////////////
		void avlTree::inorder(avlNode *cur, minHeap *adjacentToAdd){
			if (!(cur->left == NULL)) inorder(cur->left, adjacentToAdd);
			//Δημιουργώ αντικείμενα τύπου edge και τα προσθέτω στο σωρό
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

