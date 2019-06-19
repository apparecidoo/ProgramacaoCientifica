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
