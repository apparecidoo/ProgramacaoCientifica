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
}

void LinkedList::addLast(int value)
{
	if (!isFull()) {

		Node* node = root_node;

		while (node->next_node != NULL)
		{
			node = node->next_node;
		}

		node->next_node = createNode(value);
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

	return value;
}

int LinkedList::removeLast()
{
	int value = -1;

	if (!isEmpty()) {

		Node* node = root_node;

		while (node->next_node != NULL)
		{
			node = node->next_node;
		}

		value = node->value;

		deleteNode(node);
	}

	return value;
}

void LinkedList::print()
{
	cout << "Values from List: " << endl;
	Node* node = root_node;

	while (node != NULL)
	{
		cout << "Value: " << node->value << endl;
		node = node->next_node;
	}
}

int LinkedList::getNumberNodes()
{
	return this->number_nodes;
}

void LinkedList::test()
{
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
