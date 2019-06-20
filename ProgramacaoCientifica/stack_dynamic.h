#include <iostream>
#include "linked_list.h"

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

using namespace std;

class DynamicStack : LinkedList {
public:
	DynamicStack();
	~DynamicStack();

	void push(int value); // insert a value in the stack
	int pop(); // remove the last value in the stack
	void test() override;
	void print() override;
};

#endif
