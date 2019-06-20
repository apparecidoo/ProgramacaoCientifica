#include <iostream>
#include "linked_list.h"

#ifndef QUEUE_DYNAMIC_H
#define QUEUE_DYNAMIC_H

using namespace std;

class DynamicQueue : LinkedList {
public:
	DynamicQueue();
	~DynamicQueue();

	void queue(int value); // insert a value in the queue
	int deQueue(); // remove the last value in the queue
	void test() override;
	void print() override;
};

#endif