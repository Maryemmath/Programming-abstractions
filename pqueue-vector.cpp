/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
	priorityVec.clear();
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
	priorityVec.clear();
}

int VectorPriorityQueue::size() {
	// TODO: Fill this in!
	return priorityVec.size();	
	
	return 0;
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	if(size() == 0)return true;
	else return false;
	
	return true;
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	priorityVec.add(value);
}
int VectorPriorityQueue::minElementIndex(){
	int minIndex = 0;
	string minString = priorityVec[minIndex];
	for(int i = 1; i < priorityVec.size(); i++){
		if(priorityVec[i] < minString){
			minString = priorityVec[i];
			minIndex = i;
		}
	}
	index = minIndex;
	return minIndex;
}

string VectorPriorityQueue::peek() {
	// TODO: Fill this in!
	if(isEmpty()) error("vector is empty");
	return priorityVec[minElementIndex()];
}

string VectorPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	string res = peek();
	priorityVec.remove(index);
	return res;
}
