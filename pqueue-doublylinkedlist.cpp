/*
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include <iostream>

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    length = 0;
    first = new Cell;
    last = new Cell;
    first->next = last;
    last->prev = first;
    first->prev = NULL;
    last->next = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    while(first != NULL){
        Cell* next = first->next;
        delete first;
        first = next;
    }
}

int DoublyLinkedListPriorityQueue::size() {
    return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
    return size() == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    length++;
    Cell* newNode = new Cell;
    newNode->value = value;
    Cell* temp = first->next;
    first->next = newNode;
    newNode->prev = first;
    newNode->next = temp;
    temp->prev = newNode;
}

string DoublyLinkedListPriorityQueue::peek() {
    if(isEmpty()) error("empty queue!");
    Cell* res = findCell();
    return res->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	Cell* copy = first->next;
    string res = peek();
    Cell* temp = findCell();
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
    length--;
    return res;
}

DoublyLinkedListPriorityQueue::Cell* DoublyLinkedListPriorityQueue::findCell() {
    Cell* temp = first->next;
    Cell* res = temp;
    while(temp != last) {
        if(temp->value < res->value) {
            res = temp;
        }
		temp = temp->next;
    }
    return res;
}