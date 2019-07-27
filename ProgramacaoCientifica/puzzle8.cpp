#include "pch.h"
#include "puzzle8.h"

Puzzle8::Puzzle8()
{
}

Puzzle8::~Puzzle8()
{
}

bool Puzzle8::compare(int** first, int** second)
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

void Puzzle8::create_children_nodes(TreeNode<int**>* node)
{
	TreeNode<int**>* first_move = NULL;
	TreeNode<int**>* second_move = NULL;
	TreeNode<int**>* third_move = NULL;
	TreeNode<int**>* fourth_move = NULL;
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
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[0][0] = second_move->content[1][0];
			second_move->content[1][0] = 0;
			this->add_child(node, second_move->content);
			break;
		case 1:
			first_move = get_copy(node->content);
			first_move->content[0][1] = first_move->content[0][0];
			first_move->content[0][0] = 0;
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[0][1] = second_move->content[0][2];
			second_move->content[0][2] = 0;
			this->add_child(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[0][1] = third_move->content[1][1];
			third_move->content[1][1] = 0;
			this->add_child(node, third_move->content);
			break;
		case 2:
			first_move = get_copy(node->content);
			first_move->content[0][2] = first_move->content[0][1];
			first_move->content[0][1] = 0;
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[0][2] = second_move->content[1][2];
			second_move->content[1][2] = 0;
			this->add_child(node, second_move->content);
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
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[1][0] = second_move->content[2][0];
			second_move->content[2][0] = 0;
			this->add_child(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[1][0] = third_move->content[1][1];
			third_move->content[1][1] = 0;
			this->add_child(node, third_move->content);
			break;
		case 1:
			first_move = get_copy(node->content);
			first_move->content[1][1] = first_move->content[0][1];
			first_move->content[0][1] = 0;
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[1][1] = second_move->content[1][0];
			second_move->content[1][0] = 0;
			this->add_child(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[1][1] = third_move->content[2][1];
			third_move->content[2][1] = 0;
			this->add_child(node, third_move->content);

			fourth_move = get_copy(node->content);
			fourth_move->content[1][1] = fourth_move->content[1][2];
			fourth_move->content[1][2] = 0;
			this->add_child(node, fourth_move->content);
			break;
		case 2:
			first_move = get_copy(node->content);
			first_move->content[1][2] = first_move->content[0][2];
			first_move->content[0][2] = 0;
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[1][2] = second_move->content[1][1];
			second_move->content[1][1] = 0;
			this->add_child(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[1][2] = third_move->content[2][2];
			third_move->content[2][2] = 0;
			this->add_child(node, third_move->content);
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
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[2][0] = second_move->content[2][1];
			second_move->content[2][1] = 0;
			this->add_child(node, second_move->content);
			break;
		case 1:
			first_move = get_copy(node->content);
			first_move->content[2][1] = first_move->content[0][2];
			first_move->content[0][2] = 0;
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[2][1] = second_move->content[1][1];
			second_move->content[1][1] = 0;
			this->add_child(node, second_move->content);

			third_move = get_copy(node->content);
			third_move->content[2][1] = third_move->content[2][2];
			third_move->content[2][2] = 0;
			this->add_child(node, third_move->content);
			break;
		case 2:
			first_move = get_copy(node->content);
			first_move->content[2][2] = first_move->content[1][2];
			first_move->content[1][2] = 0;
			this->add_child(node, first_move->content);

			second_move = get_copy(node->content);
			second_move->content[2][2] = second_move->content[2][1];
			second_move->content[2][1] = 0;
			this->add_child(node, second_move->content);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

int Puzzle8::manhattan_distance(int ** content)
{
	int sum = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			switch (content[i][j])
			{
			case 1:
				sum += (i - 0) + (j - 0);
				break;
			case 2:
				sum += (i - 0) + (j - 1);
				break;
			case 3:
				sum += (i - 0) + (j - 2);
				break;
			case 4:
				sum += (i - 1) + (j - 0);
				break;
			case 5:
				sum += (i - 1) + (j - 1);
				break;
			case 6:
				sum += (i - 1) + (j - 2);
				break;
			case 7:
				sum += (i - 2) + (j - 0);
				break;
			case 8:
				sum += (i - 2) + (j - 1);
				break;
			default:
				break;
			}
		}
	}

	return sum;
}

TreeNode<int**>* Puzzle8::get_copy(int** content)
{
	int** copy = new int*[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		copy[i] = new int[SIZE];

		for (int j = 0; j < SIZE; j++)
		{
			copy[i][j] = content[i][j];
		}
	}

	return new TreeNode<int**>(copy, NULL, 0);
}
