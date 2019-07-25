#include <iostream>
#include "tree_node.h"
#include "custom_exception.h"

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
	TreeNode<T>* root; // value of the node

	Tree();
	~Tree();
	void add(T value);
	void add_children(TreeNode<T>* current_node, T value);
	void remove_cascate(T content);
	virtual TreeNode<T>* search_bfs(T content);
	virtual TreeNode<T>* search_dfs(T content);
	virtual bool compare(T first, T second);
	virtual void test();
};


template<class T>
int Tree<T>::new_id()
{
	return this->id++;
}

template <class T>
Tree<T>::Tree()
{
	this->number_nodes = 0;
	this->root = NULL;
	this->id = 1;
}

template<class T>
Tree<T>::~Tree()
{
	TreeNode<T>* node = root;
	TreeNode<T>* aux = NULL;

	while (node != NULL)
	{
		// get the next node to be explored
		if (!node->children_nodes->isEmpty()) {
			SimpleNode<TreeNode<T>*>* simpleNode = node->children_nodes->getRoot();
			node = simpleNode->content;
		}
		else {
			// if there isn't any children, so delete the node
			aux = node;
			node = node->parent;

			if (aux != NULL)
				delete aux;
		}
	}
}

template<class T>
void Tree<T>::add(T value)
{

}

template<class T>
void Tree<T>::add_children(TreeNode<T>* current_node, T value)
{
	if (current_node == NULL)
		throw CustomException("current_node is null");

	current_node->children_nodes->addLast(new TreeNode<T>(value, current_node, max_children_nodes, new_id()));
}

template<class T>
void Tree<T>::remove_cascate(T content)
{
	TreeNode<T>* node = search_dfs(content);
	TreeNode<T>* aux = NULL;

	while (node != NULL)
	{
		if (compare(node->content, content))
			return node;

		// get the next node to be explored
		if (node->has_children()) {
			aux = node->get_next_to_explore();
			if (aux != NULL) {
				node = aux;
			}
			else {
				node = node->parent;
			}
		}
		else {
			// if there isn't any children, so delete the node
			aux = node;
			node = node->parent;

			if (aux != NULL)
				delete aux;
		}
	}

}

template<class T>
TreeNode<T>* Tree<T>::search_bfs(T content)
{
	TreeNode<T>* node = root;

	while (node != NULL)
	{
		if (compare(node->content, content))
			return node;

		// get the next node to be explored
		if (!node->children_nodes->isEmpty()) {

		}
		else {
			node = node->parent;
		}
	}

	return NULL;
}

template<class T>
TreeNode<T>* Tree<T>::search_dfs(T content)
{
	TreeNode<T>* node = root;

	while (node != NULL)
	{
		if (compare(node->content, content))
			return node;

		// get the next node to be explored
		if (node->has_child_to_explore()) {
			node = node->get_next_to_explore();
			node->explored = true;
		}
		else {
			node = node->parent;
		}
	}

	return NULL;
}

template<class T>
bool Tree<T>::compare(T first, T second)
{
	return first == second;
}

template<class T>
void Tree<T>::test()
{

}


#endif
