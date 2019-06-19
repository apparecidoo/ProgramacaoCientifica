#include "pch.h"
#include "queue_dynamic.h"

DynamicQueue::DynamicQueue()
{
}

DynamicQueue::~DynamicQueue()
{
}

void DynamicQueue::queue(int value)
{
	this->addLast(value);
}

int DynamicQueue::deQueue()
{
	return this->removeFirst();
}
