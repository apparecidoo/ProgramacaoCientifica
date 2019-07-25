#include <iostream>
#include "simple_node.h"
#include "custom_exception.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

using namespace std;

template <class T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void addFirst(T value); // insert a value in the beginning of list
	void addLast(T value); // insert a value in the end of list
	T removeFirst(); // remove the last value in the beginning of list
	T removeLast(); // remove the last value in the end of list
	virtual void print(); // print all values from list
	int getNumberNodes(); // return the number of nodes in the list
	SimpleNode<T>* get_root(); // get root node
	bool isEmpty(); // check if the stack is empty
	bool isFull(); // check if the stack is full
	SimpleNode<T>* search(T content); // search if exists
	virtual void test(); // method to test

protected:
	SimpleNode<T>* root_node; // first position of queue to be retired
	int number_nodes; // number of nodes in the list

	void deleteNode(SimpleNode<T>* node); // delete the node deallocating memory
	SimpleNode<T>* createNode(T value); // create the node allocating memory
};


template <class T>
LinkedList<T>::LinkedList()
{
	root_node = NULL;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	// cleaning the list
	while (!isEmpty())
	{
		removeFirst();
	}
}

template <class T>
void LinkedList<T>::addFirst(T value)
{
	try
	{
		if (isFull())
			throw CustomException("**The list is full.");

		if (isEmpty()) {
			root_node = createNode(value); // if is the list is empty, add as root
		}
		else {
			SimpleNode<T>* node = root_node;

			root_node = createNode(value); // set the new root
			root_node->next_node = node; // set next_node from the new root with the old root, so "new_root_node->next_node = old_root"
		}
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}
}

template <class T>
void LinkedList<T>::addLast(T value)
{
	try
	{
		if (isEmpty()) {
			root_node = createNode(value); // if is the list is empty, add as root
		}
		else {
			if (isFull())
				throw CustomException("**The list is full.");

			SimpleNode<T>* node = root_node;

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

template <class T>
T LinkedList<T>::removeFirst()
{
	T value = NULL; // return NULL if something is wrong

	try
	{
		if (isEmpty())
			throw CustomException("**The list is empty.");

		SimpleNode<T>* node = root_node;
		root_node = node->next_node; // get the next node and set as root
		value = node->content; // get the value to be returned
		deleteNode(node); // deallocate the memory
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return value;
}

template <class T>
T LinkedList<T>::removeLast()
{
	T value = NULL; // return NULL if something is wrong

	try
	{
		if (isEmpty())
			throw CustomException("**The list is empty.");

		SimpleNode<T>* node = root_node;
		SimpleNode<T>* previous_node = NULL;

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

		value = node->content; // get the value to be returned

		deleteNode(node); // deallocate the memory
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return value;
}

template <class T>
void LinkedList<T>::print()
{
}

template <class T>
int LinkedList<T>::getNumberNodes()
{
	return this->number_nodes;
}

template <class T>
SimpleNode<T>* LinkedList<T>::get_root()
{
	return root_node;
}

template<class T>
inline SimpleNode<T>* LinkedList<T>::search(T content)
{
	SimpleNode<T>* node = root_node;

	// going to the end
	while (node != NULL)
	{
		if (node->content == content)
			return node;

		node = node->next_node;
	}

	return NULL;
}

template <class T>
void LinkedList<T>::test()
{

}

template <class T>
bool LinkedList<T>::isEmpty()
{
	return root_node == NULL; // if the root is null then the list is empty
}

template <class T>
bool LinkedList<T>::isFull()
{
	try
	{
		SimpleNode<T>* node = createNode(0); // allocate memory

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

template <class T>
void LinkedList<T>::deleteNode(SimpleNode<T> * node)
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

template <class T>
SimpleNode<T> * LinkedList<T>::createNode(T value)
{
	SimpleNode<T>* node = NULL;

	try
	{
		node = new SimpleNode<T>(value); // allocate memory

		if (node == NULL)
			throw CustomException("**Error: The node cannot be allocated.");
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return node;
}


#endif
