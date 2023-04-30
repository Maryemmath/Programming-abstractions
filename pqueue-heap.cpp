/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	firstCapacity = 2;
	queueSize = 0;
	first = new string[firstCapacity];
	
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] first;
}

int HeapPriorityQueue::size() {
	return queueSize;
}

bool HeapPriorityQueue::isEmpty() {
	return size() == 0;
}

void HeapPriorityQueue::bubbleUp(int ind){
	int originInd = (ind-1)/2;
	while(ind != 0 && first[ind] < first[originInd]){
		swap(first[ind], first[originInd]);
		ind = originInd;
		originInd = (ind - 1)/2;
	}
}

void HeapPriorityQueue::incrStorage(){
	firstCapacity *= 2;
	string *increased = new string[firstCapacity];
	for(int i = 0; i < size(); i++){
		increased [i] = first[i];
	}
	delete[] first;
	first = increased;
}


void HeapPriorityQueue::enqueue(string value) {
	first[queueSize]= value;
	queueSize++;
	if(queueSize == firstCapacity) incrStorage();
	bubbleUp(size()-1);
}

string HeapPriorityQueue::peek() {
	if (isEmpty()) error("queue is empty");
	return first[0];
}

void HeapPriorityQueue::bubbleDown(int ind){
	if(ind == size()-1) return;
	int next1 = 2 * ind + 1;
	int next2 = 2 * ind + 2;
	if(next2 < size()){
		int tempMin = 0;
		if(first[next1] < first[next2])tempMin = next1;
		else tempMin = next2;
		if(first[tempMin] < first[ind]){
			swap(first[tempMin], first[ind]);
			bubbleDown(tempMin);
		}
	}else if(next1<size()){
		if(first[ind] > first[next1]) {
			swap(first[ind], first[next1]);
			bubbleDown(next1);
		}
	}
}

string HeapPriorityQueue::dequeueMin() {
	string res = first[0];
	if (isEmpty()) error("queue is empty");
	swap(first[0], first[size()-1]);
	queueSize--;
	bubbleDown(0);
	return res;
}