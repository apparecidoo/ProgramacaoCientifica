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
	try
	{
		if (isFull())
			throw CustomException("**The list is full.");

		if (isEmpty()) {
			root_node = createNode(value); // if is the list is empty, add as root
		}
		else {
			Node* node = root_node;

			root_node = createNode(value); // set the new root
			root_node->next_node = node; // set next_node from the new root with the old root, so "new_root_node->next_node = old_root"
		}
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}
}

void LinkedList::addLast(int value)
{
	try
	{
		if (isEmpty()) {
			root_node = createNode(value); // if is the list is empty, add as root
		}
		else {
			if (isFull())
				throw CustomException("**The list is full.");

			Node* node = root_node;

			// going to the end
			while (node != NULL)
			{
				node = node->next_node;
			}

			node->next_node = createNode(value); // allocate memory
		}
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}
}

int LinkedList::removeFirst()
{
	int value = -1; // return -1 if something is wrong

	try
	{
		if (isEmpty())
			throw CustomException("**The list is empty.");

		Node* node = root_node;
		root_node = node->next_node; // get the next node and set as root
		value = node->value; // get the value to be returned
		deleteNode(node); // deallocate the memory
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return value;
}

int LinkedList::removeLast()
{
	int value = -1; // return -1 if something is wrong

	try
	{
		if (isEmpty())
			throw CustomException("**The list is empty.");

		Node* node = root_node;
		Node* previous_node = NULL;

		while (node != NULL)
		{
			if (node->next_node != NULL)
				previous_node = node; // if was the root, then we need to maintain NULL on previous_node

			node = node->next_node; // got to next node
		}

		if (previous_node != NULL)
			previous_node->next_node = NULL; // remove the link with the next node
		else
			root_node = NULL; // if was the root, remove root_node setting NULL

		value = node->value; // get the value to be returned

		deleteNode(node); // deallocate the memory
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return value;
}

void LinkedList::print()
{
	cout << endl << "Values from List: " << endl;
	Node* node = root_node;

	// going to the end
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

Node * const LinkedList::getRoot()
{
	return root_node;
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
	return root_node == NULL; // if the root is null then the list is empty
}

bool LinkedList::isFull()
{
	try
	{
		Node* node = createNode(0); // allocate memory

		if (node == NULL) {
			cout << "***Error: Cannot allocate memory, Node is null." << endl;
			return true;
		}

		this->deleteNode(node);

		return false;
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
		return true;
	}
	catch (const std::exception& ex)
	{
		cout << "***Error: " << ex.what() << endl;
		return true;
	}
}

void LinkedList::deleteNode(Node * node)
{
	try
	{
		if (node == NULL)
			throw CustomException("**Error: The node cannot be null on delete.");

		delete node; // deallocate memory
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

}

Node * LinkedList::createNode(int value)
{
	Node* node = NULL;

	try
	{
		node = new Node(value); // allocate memory

		if (node == NULL)
			throw CustomException("**Error: The node cannot be allocated.");
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return node;
}
