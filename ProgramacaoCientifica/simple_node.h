#include <iostream>

#ifndef SIMPLE_NODE_H
#define SIMPLE_NODE_H

using namespace std;

class SimpleNode
{
public:
	SimpleNode(int value);

	int value; // value of the node
	SimpleNode* next_node; // pointer for the next node
};

#endif
