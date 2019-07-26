#include <iostream>
#include "tree.h"

#ifndef PUZZLE_H
#define PUZZLE_H

using namespace std;

template <class T>
class Puzzle : public Tree<T> {
public:
	Puzzle();
	~Puzzle();

	TreeNode<T>* search_bfs(T content);
	TreeNode<T>* search_dfs(T content);
	virtual void create_children_nodes(TreeNode<T>* node) = 0;
	void test() override;	
};

template <class T>
Puzzle<T>::Puzzle() : Tree<T>()
{

}

template <class T>
Puzzle<T>::~Puzzle()
{
}

template <class T>
TreeNode<T>* Puzzle<T>::search_bfs(T content)
{
	this->queue_bfs_list->enqueue(this->root); // start my queue

	while (!this->queue_bfs_list->isEmpty())
	{
		TreeNode<T>* node = this->queue_bfs_list->dequeue();
		node->explored = true;

		if (this->compare(node->content, content))
			return node;

		this->create_children_nodes(node); // create the new neighbors

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

template <class T>
TreeNode<T>* Puzzle<T>::search_dfs(T content)
{
	this->stack_dfs_list->push(this->root);

	while (!this->stack_dfs_list->isEmpty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;

		if (this->compare(node->content, content))
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (!node->children_nodes->isEmpty()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!child->content->explored && this->stack_dfs_list->search(child->content) == NULL)
				{
					this->stack_dfs_list->push(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template <class T>
void Puzzle<T>::test()
{

}


#endif
