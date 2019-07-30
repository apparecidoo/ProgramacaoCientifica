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
	TreeNode<T>* root;
	int id;
	int g_score;
	DynamicQueue<TreeNode<T>*>* queue_bfs_list;
	DynamicStack<TreeNode<T>*>* stack_dfs_list;
	LinkedList<TreeNode<T>*>* a_star_list;
	DynamicQueue<T>* explored_list;
	
	int new_id();
	virtual void set_child_properties(TreeNode<T>* node, T goal);
	virtual bool compare(T first, T second);
	virtual int manhattan_distance(T test, T goal);
	virtual TreeNode<T>* a_star_get_next_node_to_explore();

public:
	Tree();
	~Tree();
	void remove_cascate(T content);
	virtual TreeNode<T>* search_bfs(T content);
	virtual TreeNode<T>* search_dfs(T content);
	virtual TreeNode<T>* search_a_star(T content);
	virtual TreeNode<T>* search_hill_climbing(T content);
	virtual void print_content(T content) = 0;
	virtual void print_node(TreeNode<T>* node) = 0;
	virtual void print_node_children(TreeNode<T>* node) = 0;
	virtual void print_children(TreeNode<T>* node) = 0;
	virtual void print_tree() = 0;
	virtual void test() = 0;
};

template <class T>
Tree<T>::Tree()
{
	this->g_score = 0;
	this->root = NULL;
	this->id = 1;
	this->queue_bfs_list = new DynamicQueue<TreeNode<T>*>();
	this->stack_dfs_list = new DynamicStack<TreeNode<T>*>();
	this->explored_list = new DynamicQueue<T>();
	this->a_star_list = new LinkedList<TreeNode<T>*>();
}

template<class T>
Tree<T>::~Tree()
{
	if (root != NULL)
		this->remove_cascate(root->content);

	this->explored_list->clear();
	this->stack_dfs_list->clear();
	this->queue_bfs_list->clear();
}

template<class T>
int Tree<T>::new_id()
{
	return this->id++;
}

template<class T>
void Tree<T>::set_child_properties(TreeNode<T>* node, T goal)
{
	node->h_score = this->manhattan_distance(node->content, goal);
	node->g_score = node->parent->g_score + 1;
	node->f_score = node->h_score + node->g_score;
	node->id = this->new_id();
}

template<class T>
void Tree<T>::remove_cascate(T content)
{
	this->explored_list->clear();
	TreeNode<T>* nodeRoot = this->search_dfs(content);
	this->stack_dfs_list->push(nodeRoot);

	while (!this->stack_dfs_list->is_empty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;

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
}

template<class T>
TreeNode<T>* Tree<T>::search_bfs(T content)
{
	this->explored_list->clear();
	this->queue_bfs_list->enqueue(root); // start my queue

	while (!this->queue_bfs_list->is_empty())
	{
		TreeNode<T>* node = this->queue_bfs_list->dequeue();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (compare(node->content, content))
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (this->explored_list->search(child->content->content) == NULL && this->queue_bfs_list->search(child->content) == NULL)
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
	this->explored_list->clear();
	this->stack_dfs_list->push(root);

	while (!this->stack_dfs_list->is_empty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (compare(node->content, content))
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (this->explored_list->search(child->content->content) == NULL && this->stack_dfs_list->search(child->content) == NULL)
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
TreeNode<T>* Tree<T>::search_a_star(T content)
{
	this->explored_list->clear();
	this->a_star_list->add_last(this->root);

	while (!this->a_star_list->is_empty())
	{
		TreeNode<T>* node = this->a_star_get_next_node_to_explore();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (compare(node->content, content))
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (this->explored_list->search(child->content->content) == NULL && this->a_star_list->search(child->content) == NULL)
				{
					this->a_star_list->add_last(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
TreeNode<T>* Tree<T>::search_hill_climbing(T content)
{
	this->explored_list->clear();
	TreeNode<T>* node = root;
	TreeNode<T>* node_to_validate = node;

	while (node != NULL)
	{
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (compare(node->content, content))
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();
			node_to_validate = node;
			node = NULL;

			while (child != NULL)
			{
				if (this->explored_list->search(child->content->content) == NULL && child->content->f_score <= node_to_validate->f_score)
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
int Tree<T>::manhattan_distance(T test, T goal)
{
	return 0;
}

template<class T>
TreeNode<T>* Tree<T>::a_star_get_next_node_to_explore()
{
	TreeNode<T>* value = NULL;

	// get next node to be explored
	SimpleNode<TreeNode<T>*>* node = this->a_star_list->get_root();
	SimpleNode<TreeNode<T>*>* best_node = node;
	SimpleNode<TreeNode<T>*>* previous_node = NULL;

	// finding node
	while (node != NULL)
	{
		if (best_node->content->f_score >= node->content->f_score) {
			best_node = node;
		}

		if (node->next_node != NULL)
			previous_node = node;

		node = node->next_node;
	}

	value = this->a_star_list->remove(node->content);

	return value;
}


#endif
