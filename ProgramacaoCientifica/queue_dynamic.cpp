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
	cout << endl << "Enqueue number: " << value << endl;
	this->addLast(value);
}

int DynamicQueue::deQueue()
{
	int value = this->removeFirst();

	cout << endl << "Dequeue number: " << value << endl;

	return value;
}

void DynamicQueue::test()
{
	this->queue(1);
	this->print();
	this->queue(2);
	this->print();
	this->queue(3);
	this->print();
	this->deQueue();
	this->print();
	this->queue(4);
	this->print();
	this->queue(5);
	this->print();
	this->deQueue();
	this->print();
	this->deQueue();
	this->print();
	this->deQueue();
	this->print();
	this->deQueue();
	this->print();
}

void DynamicQueue::print()
{
	cout << endl << "Values from Queue: " << endl;
	cout << "[begin] - ";

	Node* node = this->getRoot();

	while (node != NULL)
	{
		cout << node->value << " | ";
		node = node->next_node;
	}

	cout << " - [end]";

	cout << endl;
}
