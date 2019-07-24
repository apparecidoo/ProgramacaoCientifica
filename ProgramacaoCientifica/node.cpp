#include "pch.h"
#include "node.h"

template <class T>
Node<T>::Node(T value, Node<T>* parent, int size_children, int id)
{
	this->id = id;
	this->content = value;
	this->children_nodes = new Node<T>[size_children];
	this->parent = NULL;
	this->size_children = size_children;
	this->explored = false;

	for (int i = 0; i < size_children; i++)
	{
		this->children_nodes[i] = NULL;
	}
}

template<class T>
bool Node<T>::has_children()
{
	bool has = false;

	for (int i = 0; i < size_children; i++)
	{
		if (children_nodes[i] != NULL) {
			has = true;
			break;
		}
	}

	return has;
}

template<class T>
bool Node<T>::has_child_to_explore()
{
	bool has = false;

	for (int i = 0; i < size_children; i++)
	{
		if (children_nodes[i] != NULL) {
			if (!children_nodes[i]->explored) {
				has = true;
				break;
			}
		}
	}

	return has;
}

template<class T>
Node<T>* Node<T>::get_next_to_explore()
{
	for (int i = 0; i < size_children; i++)
	{
		if (children_nodes[i] != NULL) {
			if (!children_nodes[i]->explored) {
				return children_nodes[i];
			}
		}
	}

	return nullptr;
}
