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

void DynamicQueue::test()
{
	this->queue(1);
	this->queue(2);
	this->queue(3);
	this->print();
	this->deQueue();
	this->queue(4);
	this->queue(5);
	this->print();
	this->deQueue();
	this->deQueue();
	this->deQueue();
	this->deQueue();
	this->print();
}
