# Prim-Dijkstra
Implementing Prim's and Dijkstra's algorithms

## Main implementation
In this project, data structures such as hashTable, minHeap and AVL Tree are implemented.

In the project’s main functionality a text file is given as an input. This file contains connections between webpages forming edges in a graph. This graph is undirected and each edge has a weight which represents the cost of the edge. For example if webpage 1 contains a link to webpage 2 with an edge of 10, there will be a line in the input file with the content <1 2 10>. Suppose that lines are stored randomly in the input file. This file is read and it is implemented a list with the connections with the following features:
-	The structure of this list is organized in a hashTable. To Find the neighbors of a vertex, it has to apply the hash function and next to search the vertex according to the function of hashing open addressing
-	Neighbors of each vertex are stored in an AVL tree which stores the pages’ IDs
-	In order to have good search times in hashTable, if we know that _N_ vertices will be used, we will use a table of size 2*_N_, such that the load factor to be ≈ 0.5 
-	HashTable has a constant size and contains less than 50000 vertices
-	Insertion and deletion of a link are also implemented

The following functions are maintained: a) finding minimal tree according to Prim’s algorithm (command MST), b) finding the number of common neighbors of two vertices (command CN) and c) finding the minimal path with the Dijkstra’s algorithm (command SP). Functions are read from file commands.txt, where there will be the following commands:

```
READ_DATA input.txt // reading the file input.txt
INSERT_LINK x y w // inserting an edge between vertices x and y with weight w
DELETE_LINK x y // deleting an edge
MST // finding the minimal tree
CN x y // finding the number of common neighbors of vertices x and y
SP x // finding the minimal paths from vertex x
```


Only commands MST, CN and SP can print in file output.txt. Every time we meet a command MST in the file input.txt, we write the cost of minimal tree in the output.txt and the runtime of finding the tree (i.e. in seconds) as well. Every time we meet the command CN we print the number of common neighbors. Finally, when we meet the command SP we print the cost of minimal path from vertex x to all other vertices. Commands in commands.txt file may be in a random order and there is no limit about their number. The only limitation is that the first command of commands.txt is READ_DATA.

