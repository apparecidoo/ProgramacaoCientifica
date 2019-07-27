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
	int id;
	int g_score;
	DynamicQueue<TreeNode<T>*>* queue_bfs_list;
	DynamicStack<TreeNode<T>*>* stack_dfs_list;

public:
	TreeNode<T>* root;

	Tree();
	~Tree();
	void remove_cascate(T content);
	virtual void add_child(TreeNode<T>* current_node, T value);
	virtual TreeNode<T>* search_bfs(T content);
	virtual TreeNode<T>* search_dfs(T content);
	virtual TreeNode<T>* a_star(T content);
	virtual bool compare(T first, T second);
	virtual int manhattan_distance(T content);
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
	this->g_score = 0;
	this->root = NULL;
	this->id = 1;
	this->queue_bfs_list = new DynamicQueue<TreeNode<T>*>();
	this->stack_dfs_list = new DynamicStack<TreeNode<T>*>();
}

template<class T>
Tree<T>::~Tree()
{
	if (root != NULL)
		this->remove_cascate(root->content);
}

template<class T>
void Tree<T>::add_child(TreeNode<T>* current_node, T content)
{
	if (current_node == NULL) {
		this->root = new TreeNode<T>(content, current_node, this->manhattan_distance(content), 0, this->new_id());
	}
	else {
		current_node->children_nodes->addLast(new TreeNode<T>(content, current_node, this->manhattan_distance(content), current_node->g_score + 1, this->new_id()));
	}
}

template<class T>
void Tree<T>::remove_cascate(T content)
{
	//this->stack_dfs_list->push(root);

	//while (!this->stack_dfs_list->isEmpty())
	//{
	//	TreeNode<T>* node = this->stack_dfs_list->pop();
	//	node->explored = true;

	//	//if (compare(node->content, content))
	//	//	return node;

	//	// get the neighbors to be explored
	//	if (node->has_children()) {
	//		SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

	//		while (child != NULL)
	//		{
	//			if (!child->content->explored && this->stack_dfs_list->search(child->content) == NULL)
	//			{
	//				stack_dfs_list->push(child->content);
	//			}

	//			child = child->next_node;
	//		}
	//	}
	//}
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
				if (!child->content->explored && this->queue_bfs_list->search(child->content) == NULL)
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
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!child->content->explored && this->stack_dfs_list->search(child->content) == NULL)
				{
					stack_dfs_list->push(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
inline TreeNode<T>* Tree<T>::a_star(T content)
{
	TreeNode<T>* node = root;

	while (node != NULL)
	{
		node->explored = true;

		if (compare(node->content, content))
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!child->content->explored && child->content->f_score <= node->f_score)
				{
					node = child->content;
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
inline int Tree<T>::manhattan_distance(T content)
{
	return 0;
}

template<class T>
void Tree<T>::test()
{

}


#endif
