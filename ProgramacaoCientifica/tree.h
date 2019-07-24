#include <iostream>
#include "node.h"
#include "custom_exception.h"
#include "linked_list.h"

#ifndef TREE_H
#define TREE_H

using namespace std;

template <class T>
class Tree
{

protected:
	int number_nodes;
	int max_children_nodes;
	int id;
	int new_id();

public:
	Node<T>* root; // value of the node

	Tree(int max_children_nodes);
	~Tree();
	void add(T value);
	void add_children(Node<T> current_node, T value);
	T remove_cascate(T content);
	virtual Node<T>* search_bfs(T content);
	virtual Node<T>* search_dfs(T content);
	virtual bool compare(T first, T second);
};

#endif
