#include <iostream>
#include "tree.h"

#ifndef PUZZLE_H
#define PUZZLE_H

using namespace std;

template <class T>
class Puzzle : Tree<T> {
public:
	Puzzle();
	~Puzzle();

	bool compare(T first, T second) override;
	TreeNode<T>* search_bfs(T content);
	TreeNode<T>* search_dfs(T content);
	TreeNode<T>* create_children_nodes(TreeNode<T>* node);
	void test() override;
	
};

template <class T>
Puzzle<T>::Puzzle() : Tree()
{

}

template <class T>
Puzzle<T>::~Puzzle()
{
}

template <class T>
bool Puzzle<T>::compare(T first, T second)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (first[i][j] != second[i][j]) {
				return false;
			}
		}
	}

	return true;
}

template <class T>
TreeNode<T>* Puzzle<T>::search_bfs(T content)
{
	return nullptr;
}

template <class T>
TreeNode<T>* Puzzle<T>::search_dfs(T content)
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

template <class T>
TreeNode<T>* Puzzle<T>::create_children_nodes(TreeNode<T>* node)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{

		}
	}
}

template <class T>
void Puzzle<T>::test()
{
}


#endif
