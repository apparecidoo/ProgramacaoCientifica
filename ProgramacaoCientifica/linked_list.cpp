#include "pch.h"
#include "linked_list.h"

LinkedList::LinkedList()
{
	root_node = NULL;
}

LinkedList::~LinkedList()
{
	// cleaning the list
	while (!isEmpty())
	{
		removeFirst();
	}
}

void LinkedList::addFirst(int value)
{
	if (!isFull()) {

		if (isEmpty()) {
			root_node = createNode(value);
		}
		else {
			Node* node = root_node;

			root_node = createNode(value);
			root_node->next_node = node;
		}
	}
	else {
		cout << "**The list is full." << endl;
	}
}

void LinkedList::addLast(int value)
{
	if (isEmpty()) {
		root_node = createNode(value);
	}
	else {
		if (!isFull()) {

			Node* node = root_node;

			while (node->next_node != NULL)
			{
				node = node->next_node;
			}

			node->next_node = createNode(value);
		}
		else {
			cout << "**The list is full." << endl;
		}
	}
}

int LinkedList::removeFirst()
{
	int value = -1;

	if (!isEmpty()) {

		Node* node = root_node;

		root_node = node->next_node;

		value = node->value;

		deleteNode(node);
	}
	else {
		cout << "**The list is empty." << endl;
	}

	return value;
}

int LinkedList::removeLast()
{
	int value = -1;

	if (!isEmpty()) {

		Node* node = root_node;
		Node* previous_node = NULL;

		while (node->next_node != NULL)
		{
			if(node->next_node != NULL)
				previous_node = node; // if was the root, then we need to maintain NULL on previous_node

			node = node->next_node;
		}

		if (previous_node != NULL)
			previous_node->next_node = NULL; // remove any node
		else
			root_node = NULL; // if was the root, remove root_node setting NULL

		value = node->value;

		deleteNode(node);
	}
	else {
		cout << "**The list is empty." << endl;
	}

	return value;
}

void LinkedList::print()
{
	cout << "Values from List: " << endl;
	Node* node = root_node;

	while (node != NULL)
	{
		cout << node->value << " | ";
		node = node->next_node;
	}

	cout << endl;
}

int LinkedList::getNumberNodes()
{
	return this->number_nodes;
}

void LinkedList::test()
{
	this->addFirst(10);
	this->addLast(2);
	this->removeLast();
	this->print();
	this->addFirst(11);
	this->removeFirst();
	this->addLast(3);
	this->print();
	this->addFirst(12);
	this->removeFirst();
	this->addFirst(13);
	this->print();
	this->removeFirst();
	this->removeFirst();
	this->removeFirst();
	this->removeFirst();
}

bool LinkedList::isEmpty()
{
	return root_node == NULL;
}

bool LinkedList::isFull()
{
	try
	{
		Node* node = createNode(0);

		if (node == NULL) {
			cout << "***Error: Cannot allocate memory, Node is null." << endl;
			return true;
		}

		this->deleteNode(node);

		return false;
	}
	catch (const std::exception& ex)
	{
		cout << "***Error: " << ex.what() << endl;
		return true; 
	}
}

void LinkedList::deleteNode(Node * node)
{
	if (node != NULL) {
		delete node;
	}
}

Node * LinkedList::createNode(int value)
{
	return new Node(value);
}
