#include "pch.h"
#include "puzzle.h"

Puzzle::Puzzle() : Tree()
{

}

Puzzle::~Puzzle()
{
}

bool Puzzle::compare(int first[SIZE][SIZE], int second[SIZE][SIZE])
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

TreeNode<int[SIZE][SIZE]>* Puzzle::search_bfs(int content[SIZE][SIZE])
{
	return nullptr;
}

TreeNode<int[SIZE][SIZE]>* Puzzle::search_dfs(int content[SIZE][SIZE])
{
	TreeNode<int[SIZE][SIZE]>* node = root;

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

void Puzzle::test()
{
}
