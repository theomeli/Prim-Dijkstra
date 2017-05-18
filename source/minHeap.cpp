#include "minHeap.h"
#include <string.h>
//---------------------------------------------------------------------------
minHeap::minHeap(){
	maxSize = 88303;   			//������� ������� ��� ����� ��� �� ������ ��� �����
	currentSize = 0;
	heap = new edge[maxSize];
}


minHeap::~minHeap(){
	delete [] heap;
}


long minHeap::getCurrentSize(){return currentSize;}


edge minHeap::getMin(){
	if (currentSize == 0)
		return edge();
	else
		return heap[1];
}


minHeap minHeap::insertToHeap(edge anEdge){
	if (currentSize == maxSize)
		return *this;

	short weight = anEdge.getWeight();
	long i = ++currentSize;
	while (heap[i/2].getWeight() > weight){
		heap[i] = heap[i/2];
		i = i/2;
	}
	heap[i] = anEdge;
	return *this;
}


minHeap minHeap::deleteMin(edge& minEdge){
	if (currentSize == 0)
		return *this;

	//� ��������� ���� ������������ ��� ������������
	minEdge = heap[1];

	//��������� �� ��������� �������� ��� ����� ��� ��������� �� currentSize ���� ���
	edge lastEdge = heap[currentSize--];

	//���������� ��� �� �������� �� ��������� �������� ��� �����
	//���������� ��� �� ����

	long i = 1;
	long ci = 2;
	short weight = lastEdge.getWeight();
	while (ci <= currentSize){
		//������� �� ��������� ��� �� ��� ������
		if (heap[ci].getWeight() > heap[ci+1].getWeight())
			ci++;

			//������ �� �� ��������� ��� �� ��� ������ ����� ��������� ��� lastEdge
			if (heap[ci].getWeight() >= weight)  break;      //����� ���������
			else{
				heap[i] = heap[ci];  //�� ��������� ����� ������� ������
				i = ci;              //��� ������������ ��� ������� ��� ������
				ci *= 2;
			}


	}
	//������ ���� �� ������ ��� �� ���� � lastEdge
	heap[i] = lastEdge;

	return *this;
}

