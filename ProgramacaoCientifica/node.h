#include <iostream>

#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node
{

private:
	T content; // value of the node
	int size_children;

public:
	Node<T>* parent;
	Node<T>* children_nodes; // all children nodes
	int id;
	bool explored;

	Node(T value, Node<T>* parent, int size_children, int id = 0);
	bool has_children();
	bool has_child_to_explore();
	Node<T>* get_next_to_explore();
};

#endif
