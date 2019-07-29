#include <iostream>
#include "tree.h"

#ifndef PUZZLE_H
#define PUZZLE_H

using namespace std;

template <class T>
class Puzzle : public Tree<T> {
protected:
	T _goal;

public:
	Puzzle(T goal);
	~Puzzle();

	TreeNode<T>* search_bfs(T test) override;
	TreeNode<T>* search_dfs(T test) override;
	TreeNode<T>* search_a_star(T test) override;

	virtual void create_children_nodes(TreeNode<T>* node) = 0;
};

template <class T>
Puzzle<T>::Puzzle(T goal) : Tree<T>()
{
	this->_goal = goal;
}

template <class T>
Puzzle<T>::~Puzzle()
{
	this->Tree<T>::~Tree();
}

template <class T>
TreeNode<T>* Puzzle<T>::search_bfs(T test)
{
	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, _goal), 0, this->new_id());
	this->explored_list->clear();
	this->queue_bfs_list->enqueue(this->root); // start my queue

	while (!this->queue_bfs_list->is_empty())
	{
		TreeNode<T>* node = this->queue_bfs_list->dequeue();
		node->explored = true;
		this->explored_list->add_first(node);

		if (this->compare(node->content, this->_goal))
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (this->explored_list->search(child->content) == NULL && this->queue_bfs_list->search(child->content) == NULL)
				{
					this->queue_bfs_list->enqueue(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template <class T>
TreeNode<T>* Puzzle<T>::search_dfs(T test)
{
	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, _goal), 0, this->new_id());
	this->explored_list->clear();
	this->stack_dfs_list->push(this->root);

	while (!this->stack_dfs_list->is_empty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;
		this->explored_list->add_first(node);

		if (this->compare(node->content, this->_goal))
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (this->explored_list->search(child->content) == NULL && this->stack_dfs_list->search(child->content) == NULL)
				{
					this->stack_dfs_list->push(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
TreeNode<T>* Puzzle<T>::search_a_star(T test)
{
	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, _goal), 0, this->new_id());
	this->explored_list->clear();
	TreeNode<T>* node = this->root;

	while (node != NULL)
	{
		node->explored = true;
		this->explored_list->add_first(node);

		if (this->compare(node->content, this->_goal))
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (this->explored_list->search(child->content) == NULL && child->content->f_score <= node->f_score)
				{
					node = child->content;
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}


#endif
