#include <iostream>
#include "tree.h"

#ifndef PUZZLE_H
#define PUZZLE_H

using namespace std;

template <class T>
class Puzzle : public Tree<T> {
protected:
	T goal_;

	bool search_explored(T content);
	bool search_queue_bfs(T content);
	bool search_stack_dfs(T content);
	bool search_list_a_star(T content);
	TreeNode<T>* a_star_get_next_node_to_explore() override;
	virtual bool compare_explored(T first, T second);
	virtual void create_children_nodes(TreeNode<T>* node) = 0;

public:
	Puzzle(T goal);
	~Puzzle();

	TreeNode<T>* search_bfs(T test) override;
	TreeNode<T>* search_dfs(T test) override;
	TreeNode<T>* search_a_star(T test) override;
	TreeNode<T>* search_hill_climbing(T test) override;
};

template <class T>
Puzzle<T>::Puzzle(T goal) : Tree<T>()
{
	this->goal_ = goal;
}

template <class T>
Puzzle<T>::~Puzzle()
{
	this->Tree<T>::~Tree();
}

template <class T>
TreeNode<T>* Puzzle<T>::search_bfs(T test)
{
	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	this->queue_bfs_list->enqueue(this->root); // start my queue

	while (!this->queue_bfs_list->is_empty())
	{
		TreeNode<T>* node = this->queue_bfs_list->dequeue();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (this->compare(node->content, this->goal_))
			return node;

		this->create_children_nodes(node); // create the new neighbours

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!this->search_explored(child->content->content) && !this->search_queue_bfs(child->content->content)) // cannot contains in the explored list and list to be explored
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
	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	this->stack_dfs_list->push(this->root);

	while (!this->stack_dfs_list->is_empty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (this->compare(node->content, this->goal_))
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!this->search_explored(child->content->content) && !this->search_stack_dfs(child->content->content)) // cannot contains in the explored list and list to be explored
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
	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	this->a_star_list->add_last(this->root);

	while (!this->a_star_list->is_empty())
	{
		TreeNode<T>* node = this->a_star_get_next_node_to_explore();
		node->explored = true;
		this->explored_list->add_last(node->content);

		if (this->compare(node->content, this->goal_))
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				if (!this->search_explored(child->content->content) && !this->search_list_a_star(child->content->content))
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
TreeNode<T>* Puzzle<T>::search_hill_climbing(T test)
{
	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	TreeNode<T>* node = this->root;
	TreeNode<T>* node_to_validate = node;

	while (node != NULL)
	{
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (this->compare(node->content, this->goal_))
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();
			node_to_validate = node;
			node = NULL;

			while (child != NULL)
			{
				if (!this->search_explored(child->content->content) && child->content->f_score <= node_to_validate->f_score)
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
bool Puzzle<T>::search_explored(T content)
{
	SimpleNode<T>* node = this->explored_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare_explored(node->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

template<class T>
bool Puzzle<T>::search_queue_bfs(T content)
{
	SimpleNode<TreeNode<T>*>* node = this->queue_bfs_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare_explored(node->content->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

template<class T>
bool Puzzle<T>::search_stack_dfs(T content)
{
	SimpleNode<TreeNode<T>*>* node = this->stack_dfs_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare_explored(node->content->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

template<class T>
bool Puzzle<T>::search_list_a_star(T content)
{
	if (!this->a_star_list->is_empty())
		return false;

	SimpleNode<TreeNode<T>*>* node = this->a_star_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare_explored(node->content->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

template<class T>
TreeNode<T>* Puzzle<T>::a_star_get_next_node_to_explore()
{
	TreeNode<T>* value = NULL;

	// get next node to be explored
	SimpleNode<TreeNode<T>*>* root = this->a_star_list->get_root();
	SimpleNode<TreeNode<T>*>* node = root;
	SimpleNode<TreeNode<T>*>* best_node = node;
	SimpleNode<TreeNode<T>*>* previous_best_node = NULL;
	SimpleNode<TreeNode<T>*>* previous_node = NULL;

	// finding node
	while (node != NULL)
	{
		if (best_node->content->f_score >= node->content->f_score) {
			previous_best_node = previous_node;
			best_node = node;
		}

		if (node->next_node != NULL)
			previous_node = node;

		node = node->next_node;
	}

	// deleting node
	if (previous_best_node == NULL) { // root node
		value = this->a_star_list->remove_first();
	}
	else {
		if (best_node->next_node == NULL) {
			value = this->a_star_list->remove_last();
		}
		else {
			previous_best_node->next_node = best_node->next_node;
			value = best_node->content;
			delete best_node;
			this->a_star_list->remove_number_nodes();
		}
	}

	return value;
}

template<class T>
bool Puzzle<T>::compare_explored(T first, T second)
{
	return first == second;
}


#endif
