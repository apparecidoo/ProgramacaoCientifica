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
	TreeNode<int[SIZE][SIZE]>* first_move = NULL;
	TreeNode<int[SIZE][SIZE]>* second_move = NULL;
	TreeNode<int[SIZE][SIZE]>* third_move = NULL;
	TreeNode<int[SIZE][SIZE]>* fourth_move = NULL;
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

	switch (i)
	{
	case 0:
		switch (j)
		{
		case 0:
			first_move = get_copy(node->content);
			first_move->content[0][0] = first_move->content[0][1];
			first_move->content[0][1] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[0][0] = second_move->content[1][0];
			second_move->content[1][0] = 0;
			this->add_children(node, second_move->content);
			break;
		case 1:
			first_move = get_copy(node->content);
			first_move->content[0][1] = first_move->content[0][0];
			first_move->content[0][0] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[0][1] = second_move->content[0][2];
			second_move->content[0][2] = 0;
			this->add_children(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[0][1] = third_move->content[1][1];
			third_move->content[1][1] = 0;
			this->add_children(node, third_move->content);
			break;
		case 2:
			first_move = get_copy(node->content);
			first_move->content[0][2] = first_move->content[0][1];
			first_move->content[0][1] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[0][2] = second_move->content[1][2];
			second_move->content[1][2] = 0;
			this->add_children(node, second_move->content);
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (j)
		{
		case 0:
			first_move = get_copy(node->content);
			first_move->content[1][0] = first_move->content[0][0];
			first_move->content[0][0] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[1][0] = second_move->content[2][0];
			second_move->content[2][0] = 0;
			this->add_children(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[1][0] = third_move->content[1][1];
			third_move->content[1][1] = 0;
			this->add_children(node, third_move->content);
			break;
		case 1:
			first_move = get_copy(node->content);
			first_move->content[1][1] = first_move->content[0][1];
			first_move->content[0][1] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[1][1] = second_move->content[1][0];
			second_move->content[1][0] = 0;
			this->add_children(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[1][1] = third_move->content[2][1];
			third_move->content[2][1] = 0;
			this->add_children(node, third_move->content);

			fourth_move = get_copy(node->content);
			fourth_move->content[1][1] = fourth_move->content[1][2];
			fourth_move->content[1][2] = 0;
			this->add_children(node, fourth_move->content);
			break;
		case 2:
			first_move = get_copy(node->content);
			first_move->content[1][2] = first_move->content[0][2];
			first_move->content[0][2] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[1][2] = second_move->content[1][1];
			second_move->content[1][1] = 0;
			this->add_children(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[1][2] = third_move->content[2][2];
			third_move->content[2][2] = 0;
			this->add_children(node, third_move->content);
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (j)
		{
		case 0:
			first_move = get_copy(node->content);
			first_move->content[2][0] = first_move->content[1][0];
			first_move->content[1][0] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[2][0] = second_move->content[2][1];
			second_move->content[2][1] = 0;
			this->add_children(node, second_move->content);
			break;
		case 1:
			first_move = get_copy(node->content);
			first_move->content[2][1] = first_move->content[0][2];
			first_move->content[0][2] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[2][1] = second_move->content[1][1];
			second_move->content[1][1] = 0;
			this->add_children(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[2][1] = third_move->content[2][2];
			third_move->content[2][2] = 0;
			this->add_children(node, third_move->content);
			break;
		case 2:
			first_move = get_copy(node->content);
			first_move->content[2][2] = first_move->content[1][2];
			first_move->content[1][2] = 0;
			this->add_children(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[2][2] = second_move->content[2][1];
			second_move->content[2][1] = 0;
			this->add_children(node, second_move->content);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

TreeNode<int[SIZE][SIZE]>* Puzzle8::get_copy(int content[SIZE][SIZE])
{
	int copy[SIZE][SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			copy[i][j] = content[i][j];
		}
	}

	return new TreeNode<int[SIZE][SIZE]>(copy, NULL, 0);
}
