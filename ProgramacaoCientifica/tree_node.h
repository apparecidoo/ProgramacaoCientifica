#include <iostream>
#include "linked_list.h"

#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class TreeNode
{

public:
	TreeNode<T>* parent;
	LinkedList<TreeNode<T>*>* children_nodes;

	int id;
	bool explored;
	T content; // value of the node

	TreeNode(T value, TreeNode<T>* parent, int id = 0);
	bool has_children();
	bool has_child_to_explore();
	TreeNode<T>* get_next_to_explore();
};


template <class T>
TreeNode<T>::TreeNode(T value, TreeNode<T>* parent, int id)
{
	this->id = id;
	this->content = value;
	this->children_nodes = new LinkedList<TreeNode<T>*>();
	this->parent = NULL;
	this->explored = false;
}

template<class T>
bool TreeNode<T>::has_children()
{
	return !children_nodes.isEmpty();
}

template<class T>
bool TreeNode<T>::has_child_to_explore()
{
	bool has = false;

	SimpleNode<TreeNode<T>*>* simpleNode = children_nodes->get_root();

	while (simpleNode != NULL)
	{
		if (!simpleNode->content->explored) {
			has = true;
			break;
		}

		simpleNode = simpleNode->next_node;
	}

	return has;
}

template<class T>
TreeNode<T>* TreeNode<T>::get_next_to_explore()
{
	SimpleNode<TreeNode<T>*>* simpleNode = children_nodes->get_root();

	while (simpleNode != NULL)
	{
		if (!simpleNode->content->explored) {
			return simpleNode->content;
		}
	}

	return NULL;
}


#endif
