#include "pch.h"
#include "stack_dynamic.h"

DynamicStack::DynamicStack()
{
}

DynamicStack::~DynamicStack()
{
}

void DynamicStack::push(int value)
{
	cout << endl << "Push number: " << value << endl;

	this->addFirst(value);
}

int DynamicStack::pop()
{
	int value = this->removeFirst();

	cout << endl << "Pop number: " << value << endl;

	return value;
}

void DynamicStack::test() {
	this->push(1);
	this->print();
	this->push(2);
	this->print();
	this->push(3);
	this->print();
	this->pop();
	this->print();
	this->push(4);
	this->print();
	this->push(5);
	this->print();
	this->pop();
	this->print();
	this->pop();
	this->print();
	this->pop();
	this->print();
	this->pop();
	this->print();
}

void DynamicStack::print()
{
	cout << endl << "Values from Stack: " << endl;
	cout << "[top] - ";

	Node* node = this->getRoot();

	while (node != NULL)
	{
		cout << node->value << " | ";
		node = node->next_node;
	}

	cout << " - [down]";

	cout << endl;
}
