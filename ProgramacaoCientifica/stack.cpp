#include "pch.h"
#include "stack.h"

Stack::Stack()
{
	top = 0;
}

Stack::~Stack()
{
	top = 0;
}

void Stack::push(int value)
{
	if (!isFull()) {
		values[top] = value;
		top++;

		cout << endl << "Push number: " << value << endl;
	}
	else {
		cout << "**The stack is full." << endl;
	}
}

int Stack::pop()
{
	if (!isEmpty()) {
		int value = values[top];
		top--;

		cout << endl << "Pop number: " << value << endl;

		return value;
	}
	else {
		cout << "**The stack is empty." << endl;
		return -1; // return -1 if the stack is empty
	}
}

void Stack::print()
{
	cout << endl << "Values from Stack: " << endl;
	cout << "[down] - ";

	for (int i = 0; i < top; i++)
	{
		cout << values[i] << " | ";
	}

	cout << " - [top]";

	cout << endl;
}

void Stack::printTop()
{
	cout << "Top Stack: " << values[top] << endl;
}

void Stack::test()
{
	this->push(10);
	this->push(9);
	this->print();
	this->push(8);
	this->pop();
	this->pop();
	this->print();
	this->pop();
	this->pop();
}

bool Stack::isEmpty()
{
	return this->top == 0;
}

bool Stack::isFull()
{
	return this->top == SIZE;
}