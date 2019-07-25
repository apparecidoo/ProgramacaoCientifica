#include <iostream>
#include "tree_node.h"
#include "custom_exception.h"
#include "linked_list.h"
#include "stack_dynamic.h"
#include "queue_dynamic.h"

#ifndef TREE_H
#define TREE_H

using namespace std;

template <class T>
class Tree
{

protected:
	int new_id();
	int number_nodes;
	int id;
	DynamicQueue<TreeNode<T>*>* queue_bfs_list;
	DynamicStack<TreeNode<T>*>* stack_dfs_list;

public:
	TreeNode<T>* root;

	Tree();
	~Tree();
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
	this->queue_bfs_list = new LinkedList<TreeNode<T>*>();
	this->stack_dfs_list = new LinkedList<TreeNode<T>*>();
}

template<class T>
Tree<T>::~Tree()
{
	this->remove_cascate(root);
}

template<class T>
void Tree<T>::add_children(TreeNode<T>* current_node, T value)
{
	if (current_node == NULL)
		throw CustomException("current_node is null");

	current_node->children_nodes->addLast(new TreeNode<T>(value, current_node, new_id()));
}

template<class T>
void Tree<T>::remove_cascate(T content)
{
	this->stack_dfs_list->push(root);

	while (!this->stack_dfs_list->isEmpty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;

		if (compare(node->content, content))
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!child->content->explored && this->queue_bfs_list->search(child) == NULL)
				{
					this->queue_bfs_list->push(child->content);
				}

				child = child->next_node;
			}
		}
		else {
			delete node;
		}
	}
}

template<class T>
TreeNode<T>* Tree<T>::search_bfs(T content)
{
	this->queue_bfs_list->enqueue(root); // start my queue

	while (!this->queue_bfs_list->isEmpty())
	{
		TreeNode<T>* node = this->queue_bfs_list->dequeue();
		node->explored = true;

		if (compare(node->content, content))
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!child->content->explored && this->queue_bfs_list->search(child) == NULL)
				{
					this->queue_bfs_list->enqueue(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
TreeNode<T>* Tree<T>::search_dfs(T content)
{
	this->stack_dfs_list->push(root);

	while (!this->stack_dfs_list->isEmpty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;

		if (compare(node->content, content))
			return node;

		// get the neighbors to be explored
		if (!node->children_nodes->isEmpty()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!child->content->explored && this->queue_bfs_list->search(child) == NULL)
				{
					queue_bfs_list->push(child->content);
				}

				child = child->next_node;
			}
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
