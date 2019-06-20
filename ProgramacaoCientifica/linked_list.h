#include <iostream>
#include "simple_node.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

using namespace std;

class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void addFirst(int value); // insert a value in the beginning of list
	void addLast(int value); // insert a value in the end of list
	int removeFirst(); // remove the last value in the beginning of list
	int removeLast(); // remove the last value in the end of list
	virtual void print(); // print all values from list
	int getNumberNodes(); // return the number of nodes in the list
	Node* const getRoot(); // get root node
	virtual void test(); // method to test

private:
	Node* root_node; // first position of queue to be retired
	int number_nodes; // number of nodes in the list

	bool isEmpty(); // check if the stack is empty
	bool isFull(); // check if the stack is full
	void deleteNode(Node* node); // delete the node
	Node* createNode(int value);
};

#endif
