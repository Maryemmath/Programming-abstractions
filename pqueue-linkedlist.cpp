/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	length = 0;
	first = new Cell;
	first->next = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while(first != NULL){
		Cell* next = first->next;
		delete first;
		first = next;
	}
}

int LinkedListPriorityQueue::size() {
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return size() == 0;

}

void LinkedListPriorityQueue::enqueue(string value) {
	length++;
	Cell *queue = new Cell;
	queue -> value = value;
	Cell *temp = first;
	while(temp->next != NULL && temp->next->value < queue->value) {
		temp = temp->next;
	}
	Cell *next = temp->next;
	temp->next = queue;
	queue->next = next;
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()) error("empty queue!");
	return first->next->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	string res = peek();
	Cell *next = first->next->next;
	delete first->next;
	first->next = next;
	length--;
	return res;
}