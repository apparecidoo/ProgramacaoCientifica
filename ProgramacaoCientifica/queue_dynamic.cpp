#include "pch.h"
#include "queue_dynamic.h"

DynamicQueue::DynamicQueue()
{
}

DynamicQueue::~DynamicQueue()
{
}

void DynamicQueue::enqueue(int value)
{
	cout << endl << "Enqueue number: " << value << endl;
	this->addLast(value);
}

int DynamicQueue::dequeue()
{
	int value = this->removeFirst();

	cout << endl << "Dequeue number: " << value << endl;

	return value;
}

void DynamicQueue::test()
{
	this->enqueue(1);
	this->print();
	this->enqueue(2);
	this->print();
	this->enqueue(3);
	this->print();
	this->dequeue();
	this->print();
	this->enqueue(4);
	this->print();
	this->enqueue(5);
	this->print();
	this->dequeue();
	this->print();
	this->dequeue();
	this->print();
	this->dequeue();
	this->print();
	this->dequeue();
	this->print();
}

void DynamicQueue::print()
{
	cout << endl << "Values from Queue: " << endl;
	cout << "[begin] - ";

	SimpleNode<int>* node = this->getRoot();

	while (node != NULL)
	{
		cout << node->content << " | ";
		node = node->next_node;
	}

	cout << " - [end]";

	cout << endl;
}
