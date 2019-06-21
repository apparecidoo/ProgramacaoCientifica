#include "pch.h"
#include "queue.h"

Queue::Queue()
{
	first_position = 0;
	last_position = 0;
	number_values = 0;
}

Queue::~Queue()
{
	first_position = 0;
	last_position = 0;
	number_values = 0;
}

void Queue::enqueue(int value)
{
	if (!isFull()) {
		values[last_position] = value;
		addQueue();

		cout << endl << "Enqueue number: " << value << endl;
	}
	else {
		cout << "**The queue is full." << endl;
	}
}

int Queue::deQueue()
{
	if (!isEmpty()) {
		int value = values[first_position];
		subQueue();
		
		cout << endl << "Dequeue number: " << value << endl;

		return value;
	}
	else {
		cout << "**The queue is empty." << endl;

		return -1;
	}
}

void Queue::print()
{
	cout << endl << "Values from Queue: " << endl;
	cout << "[begin] - ";

	int i = first_position;
	while (i != last_position)
	{
		i = i % SIZE;

		cout << values[i] << " | ";

		i++;
	}

	cout << " - [end]";
}

void Queue::printNext()
{
	cout << "Top Stack: " << values[first_position] << endl;
}

void Queue::test()
{
	this->enqueue(10);
	this->enqueue(9);
	this->print();
	this->enqueue(8);
	this->deQueue();
	this->deQueue();
	this->print();
	this->deQueue();
	this->deQueue();
}

bool Queue::isEmpty()
{
	return number_values == 0;
}

bool Queue::isFull()
{
	return number_values == SIZE;
}

void Queue::addQueue()
{
	last_position = (last_position + 1) % SIZE; // push a value and then add 1 for the next value to be added
	number_values++;
}

void Queue::subQueue()
{
	first_position = (first_position + 1) % SIZE; // pop a value and then add 1 for the next value to be retired
	number_values--;
}
