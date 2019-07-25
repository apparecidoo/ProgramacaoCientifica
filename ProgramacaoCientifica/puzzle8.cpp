#include "pch.h"
#include "puzzle8.h"

Puzzle8::Puzzle8()
{
}

Puzzle8::~Puzzle8()
{
}

bool Puzzle8::compare(int first[SIZE][SIZE], int second[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (first[i][j] == second[i][j]) {
				return false;
			}
		}
	}

	return true;
}

void Puzzle8::create_children_nodes(TreeNode<int[SIZE][SIZE]>* node)
{
	bool search_zero = false;
	int i = 0;
	int j = 0;

	if (node == NULL)
		throw CustomException("create_children_nodes - node is null or empty");

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (node->content[i][j] == 0) {
				search_zero = true;
				break;
			}
		}

		if (search_zero)
			break;
	}

	// 4 possibilities
	if (i == 1 && j == 1) {
		//node->children_nodes->addLast();
		//TreeNode<int[SIZE][SIZE]>* first = new TreeNode<int[SIZE][SIZE]>();
	}
	else {
		// 3 possibilites
		if ((i == 0 && j == 1) || (i == 1 && j == 0) || (i == 2 && j == 1) || (i == 1 && j == 2)) {
			
		}
		else {
			// 2 possibilities

		}
	}
}