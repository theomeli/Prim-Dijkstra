#include "hashTable.h"
#include "dijkstra.h"
#include "prim.h"
#include <iostream.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <sstream>

using namespace std;



		hashTable::hashTable(){
			D = 89909;
			ht = new neighborsOfV[D];
			empty = new bool[D];
			isInSetS = new bool[D]; 			   //Ý÷ù ùò default ôéìÞ false
            		neverUsed = new bool[D];
			for (long i = 0; i < D; i++) {
				empty[i] = true;
				neverUsed[i] = true;
				ht[i].v = -1;
			}
			vectorsInS = 0;
		}



		hashTable::~hashTable(){
			delete [] ht;
			delete [] empty;
		}



		bool* hashTable::getIsInSetS(){return isInSetS;}



		long hashTable::getVectorsInS(){return vectorsInS;}



		//åðéóôñÝöåé ôï bucket óôï ïðïßï âñßóêåôáé ï key, true áí âñåèåß êáé false áí ü÷é
		//Áí äåí õðÜñ÷åé ôï óôïé÷åßï åðéóôñÝöåôáé ôï bucket üðïõ ìðïñåß íá åéóá÷èåß
		bool hashTable::searchInHash(long key, long* bucket){
			*bucket = key%D;

			do {
				if (ht[*bucket].v == key) //ôï êëåéäß Ý÷åé Þäç åéóá÷èåß
					return true;

				else{
					*bucket += *bucket;
					while (*bucket!=D){  //óôï ôåëåõôáßï bucket ôïõ ðßíáêá êáé åëÝã÷åé ôï bucket 0
						*bucket = 0;
						break;
					}
					break;
				}
			}while (!empty[*bucket] || !neverUsed[*bucket]);
			//áí ôï bucket äåí åßíáé Üäåéï Þ ç neverUsed åßíáé false ðïõ óçìáßíåé
			//üôé õðÞñ÷å åéóáãùãÞ óôï óõãêåêñéìÝíï bucket ç ïðïßá äéáãñÜöçêå

			return false; //Äåí õðÜñ÷åé ôï óôïé÷åßï ìå êëåéäß key êáé åðéóôñÝöåôáé ôï bucket
						  //üðïõ ìðïñåß íá åéóá÷èåß
		}


		//åðéóôñÝöåé ôïõò ãåßôïíåò ðïõ ðåñéÝ÷ïíôáé óôï êüìâï v
		avlTree hashTable::getNeighbors(long v){
			long *bucket = new long;
			if (searchInHash(v, bucket))
				ht[0].neighbors;
				return ht[*bucket].neighbors;
		}



		void hashTable::insertToHash(long key, long neighborsKey, short weight){
			long bucket = key%D;
			bool b = searchInHash(key, &bucket);

			//áí äå âñÝèçêå ôï key ôï åéóÜãù óôïí ðßíáêá
			if (!b) {
				 ht[bucket].v = key;
				 empty[bucket] = false;
				 neverUsed[bucket] = false;
			}

			//ðñïóèÝôù ôï óôïé÷åßï ìå êëåéäß neighborsKey óôïõò ãåßôïíåò ôïõ key
			ht[bucket].neighbors.insertToAvl(neighborsKey, weight);
			vectorsInS++;

		}


		//ÄéáãñáöÞ ôçò áêìÞò (treeId, nodeId)
		void hashTable::deleteAnEdge(long treeId, long nodeId){
			long bucket;
			bool b = searchInHash(treeId, &bucket);
			if (!b || !neverUsed[bucket])
				return;
			helpDeleteAnEdge(treeId, nodeId, &bucket);

			searchInHash(nodeId, &bucket);
			helpDeleteAnEdge(nodeId, treeId, &bucket);
		}


		void hashTable::helpDeleteAnEdge(long treeId, long nodeId, long* bucket){
			avlTree tree = ht[*bucket].neighbors;
			tree.remove(treeId);
			if (tree.getRoot() == NULL)
				 ht[*bucket].v = -1;
		}



		long* hashTable::commonNeighbors(long aId, long bId){
			avlTree aTree = getNeighbors(aId);
			avlTree bTree = getNeighbors(bId);
			avlNode node;
			long* aArray = aTree.inorderToArray(&node);
			long* bArray = bTree.inorderToArray(&node);

			int i = 0;
			int j = 0;
			int k = -1;
			long* result = new long;

			while(i<sizeof(aArray) || j<sizeof(bArray)){
				if (aArray[i] == bArray[j]) {
					result[k++] = aArray[i];
					i++;
					j++;
				}
				else
					if (aArray[i] < bArray[j])
						i++;
					else
						j++;
			}
			return result;
		}



		//////////////////////////////////////
		//////////////////////////////////////¢íïéãìá Áñ÷åßïõ Ãéá ÄéÜâáóìá
		/////////////////////////////////////
		void hashTable::openfile(){
			string k;
			long from, to;
			short weight;
			ifstream commFile("commands.txt");
			ofstream outfile("output.txt");

			getline(commFile, k, ' ');

			//////ÅéóáãùãÞ äåäïìÝíùí áðü ôï inputFile
			if(k == "READ_DATA") {
				ifstream inputFile;
				getline(commFile, k, '\n');
				inputFile.open(k.c_str());
				while (!inputFile.eof()){
					inputFile >> from >> to >> weight;
					insertToHash(from, to, weight);
					insertToHash(to, from, weight);
					cout << "a";
				}
			}

            //ÄéáâÜæåé ôï ÷áñáêôÞñá \n
			char c;

			getline(commFile, k, ' ');

			while(!commFile.eof()){
				//áí Ý÷ïõìå insert_link
				if (k == "INSERT_LINK"){
					commFile >> from >> to;
					insertToHash(from, to, weight);
					insertToHash(to, from, weight);
					cout << "b";
				}
				//áí Ý÷ïõìå delete_link
				else if (k == "DELETE_LINK"){
					commFile >> from >> to;
					deleteAnEdge(from, to);
					cout << "c";
				}
				else if (k == "MST") {
					prim* p = new prim(this);
					p->prim_algorithm();
					outfile << p->getCost();
					cout << p->getCost();
					cout << "d";
				}
				else if (k == "CN") {
					commFile >> from >> to;
					commonNeighbors(from, to);
					cout << "e";
				}
				else if (k == "SP") {
					commFile.get(c);
					commFile >> from;
					dijkstra* d = new dijkstra(this);
					d->dijkstra_algorithm(from);
					cout << "f";
				}
				//ÄéáâÜæåé ôï ÷áñáêôÞñá \n
				commFile.get(c);

				getline(commFile, k, ' ');
			}

			commFile.close();
}

