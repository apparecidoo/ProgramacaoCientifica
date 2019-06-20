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
	this->addLast(value);
}

int DynamicStack::pop()
{
	return this->removeLast();
}

void DynamicStack::test() {
	this->push(1);
	this->push(2);
	this->push(3);
	this->print();
	this->pop();
	this->push(4);
	this->push(5);
	this->print();
	this->pop();
	this->pop();
	this->pop();
	this->pop();
	this->print();
}