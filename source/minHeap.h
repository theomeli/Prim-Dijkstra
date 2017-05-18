#ifndef minHeapH
#define minHeapH
#include "edge.h"

class minHeap{

	private:

		long currentSize, maxSize;
		edge* heap;


	public:
		minHeap();


		~minHeap();


		long getCurrentSize();


		edge getMin();


		 minHeap insertToHeap(edge anEdge);


		 minHeap deleteMin(edge& minEdge);

};

#endif
