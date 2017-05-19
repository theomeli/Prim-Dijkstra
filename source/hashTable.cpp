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
			isInSetS = new bool[D]; 		//set as a default value false
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



		//it returns the bucket in which there is the key, true if it is found and false if it is not
		//if there is no element, it returns the bucket that it can be inserted
		bool hashTable::searchInHash(long key, long* bucket){
			*bucket = key%D;

			do {
				if (ht[*bucket].v == key) 		//the key has already been inserted
					return true;

				else{
					*bucket += *bucket;
					while (*bucket!=D){  		//in the last array's bucket and it controls bucket 0
						*bucket = 0;
						break;
					}
					break;
				}
			}while (!empty[*bucket] || !neverUsed[*bucket]);
			//if bucket is not empty or neverUsed is false, which means that
			//there was insertion in the particular bucket that has been deleted

			return false; 				//there is not the element key the value of key variable and 
								//it is returned the bucket where it can be inserted
		}


		//it returns the neighbors which are in node v
		avlTree hashTable::getNeighbors(long v){
			long *bucket = new long;
			if (searchInHash(v, bucket))
				ht[0].neighbors;
				return ht[*bucket].neighbors;
		}



		void hashTable::insertToHash(long key, long neighborsKey, short weight){
			long bucket = key%D;
			bool b = searchInHash(key, &bucket);

			//if the key wasn't found, we insert it in the array
			if (!b) {
				 ht[bucket].v = key;
				 empty[bucket] = false;
				 neverUsed[bucket] = false;
			}

			//we add the element with key neighborsKey at the neighbors of key
			ht[bucket].neighbors.insertToAvl(neighborsKey, weight);
			vectorsInS++;

		}


		//Deletion of the edge (treeId, nodeId)
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
		//////////////////////////////////////opens a file for reading
		/////////////////////////////////////
		void hashTable::openfile(){
			string k;
			long from, to;
			short weight;
			ifstream commFile("commands.txt");
			ofstream outfile("output.txt");

			getline(commFile, k, ' ');

			//////inserting data from inputFile
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

            		//it reads the character \n
			char c;

			getline(commFile, k, ' ');

			while(!commFile.eof()){
				if (k == "INSERT_LINK"){
					commFile >> from >> to;
					insertToHash(from, to, weight);
					insertToHash(to, from, weight);
					cout << "b";
				}
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
				//it reads the character \n
				commFile.get(c);

				getline(commFile, k, ' ');
			}

			commFile.close();
}

