#include <iostream>

#ifndef NODE_H
#define NODE_H

using namespace std;

class Node
{
public:
	Node(int value);

	int value; // value of the node
	Node* next_node; // pointer for the next node
};

#endif
