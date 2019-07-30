#include "pch.h"
#include "puzzle8.h"

Puzzle8::Puzzle8(int** goal) : Puzzle(goal)
{
}

Puzzle8::~Puzzle8()
{
	this->Puzzle<int**>::~Puzzle();
}

bool Puzzle8::compare(int** first, int** second)
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

void Puzzle8::create_children_nodes(TreeNode<int**>* node)
{
	TreeNode<int**>* left_move = NULL;
	TreeNode<int**>* down_move = NULL;
	TreeNode<int**>* right_move = NULL;
	TreeNode<int**>* up_move = NULL;
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
			left_move = get_new_node(node);
			left_move->content[0][0] = left_move->content[0][1];
			left_move->content[0][1] = 0;
			this->set_child_properties(left_move, this->goal_);

			down_move = get_new_node(node);
			down_move->content[0][0] = down_move->content[1][0];
			down_move->content[1][0] = 0;
			this->set_child_properties(down_move, this->goal_);
			break;
		case 1:
			left_move = get_new_node(node);
			left_move->content[0][1] = left_move->content[0][0];
			left_move->content[0][0] = 0;
			this->set_child_properties(left_move, this->goal_);

			down_move = get_new_node(node);
			down_move->content[0][1] = down_move->content[1][1];
			down_move->content[1][1] = 0;
			this->set_child_properties(down_move, this->goal_);

			right_move = get_new_node(node);
			right_move->content[0][1] = right_move->content[0][2];
			right_move->content[0][2] = 0;
			this->set_child_properties(right_move, this->goal_);
			break;
		case 2:
			left_move = get_new_node(node);
			left_move->content[0][2] = left_move->content[0][1];
			left_move->content[0][1] = 0;
			this->set_child_properties(left_move, this->goal_);

			down_move = get_new_node(node);
			down_move->content[0][2] = down_move->content[1][2];
			down_move->content[1][2] = 0;
			this->set_child_properties(down_move, this->goal_);
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (j)
		{
		case 0:
			up_move = get_new_node(node);
			up_move->content[1][0] = up_move->content[0][0];
			up_move->content[0][0] = 0;
			this->set_child_properties(up_move, this->goal_);

			down_move = get_new_node(node);
			down_move->content[1][0] = down_move->content[2][0];
			down_move->content[2][0] = 0;
			this->set_child_properties(down_move, this->goal_);

			right_move = get_new_node(node);
			right_move->content[1][0] = right_move->content[1][1];
			right_move->content[1][1] = 0;
			this->set_child_properties(right_move, this->goal_);
			break;
		case 1:
			left_move = get_new_node(node);
			left_move->content[1][1] = left_move->content[1][0];
			left_move->content[1][0] = 0;
			this->set_child_properties(left_move, this->goal_);

			down_move = get_new_node(node);
			down_move->content[1][1] = down_move->content[2][1];
			down_move->content[2][1] = 0;
			this->set_child_properties(down_move, this->goal_);

			right_move = get_new_node(node);
			right_move->content[1][1] = right_move->content[1][2];
			right_move->content[1][2] = 0;
			this->set_child_properties(right_move, this->goal_);

			up_move = get_new_node(node);
			up_move->content[1][1] = up_move->content[0][1];
			up_move->content[0][1] = 0;
			this->set_child_properties(up_move, this->goal_);
			break;
		case 2:
			left_move = get_new_node(node);
			left_move->content[1][2] = left_move->content[1][1];
			left_move->content[1][1] = 0;
			this->set_child_properties(left_move, this->goal_);

			down_move = get_new_node(node);
			down_move->content[1][2] = down_move->content[2][2];
			down_move->content[2][2] = 0;
			this->set_child_properties(down_move, this->goal_);

			up_move = get_new_node(node);
			up_move->content[1][2] = up_move->content[0][2];
			up_move->content[0][2] = 0;
			this->set_child_properties(up_move, this->goal_);

			break;
		default:
			break;
		}
		break;
	case 2:
		switch (j)
		{
		case 0:
			up_move = get_new_node(node);
			up_move->content[2][0] = up_move->content[1][0];
			up_move->content[1][0] = 0;
			this->set_child_properties(up_move, this->goal_);

			right_move = get_new_node(node);
			right_move->content[2][0] = right_move->content[2][1];
			right_move->content[2][1] = 0;
			this->set_child_properties(right_move, this->goal_);
			break;
		case 1:
			left_move = get_new_node(node);
			left_move->content[2][1] = left_move->content[2][0];
			left_move->content[2][0] = 0;
			this->set_child_properties(left_move, this->goal_);

			up_move = get_new_node(node);
			up_move->content[2][1] = up_move->content[1][1];
			up_move->content[1][1] = 0;
			this->set_child_properties(up_move, this->goal_);

			right_move = get_new_node(node);
			right_move->content[2][1] = right_move->content[2][2];
			right_move->content[2][2] = 0;
			this->set_child_properties(right_move, this->goal_);
			break;
		case 2:
			left_move = get_new_node(node);
			left_move->content[2][2] = left_move->content[2][1];
			left_move->content[2][1] = 0;
			this->set_child_properties(left_move, this->goal_);

			down_move = get_new_node(node);
			down_move->content[2][2] = down_move->content[1][2];
			down_move->content[1][2] = 0;
			this->set_child_properties(down_move, this->goal_);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	cout << "------------ Interaction ------------" << endl << endl;
	cout << "Node" << endl;
	this->print_node(node);
	cout << "---- Children" << endl;
	this->print_children(node);
}

int Puzzle8::manhattan_distance(int ** test, int ** goal)
{
	int sum = 0;
	int i_test = 0;
	int j_test = 0;
	int i_goal = 0;
	int j_goal = 0;

	// get the value to test
	for (i_test = 0; i_test < SIZE; i_test++)
	{
		for (j_test = 0; j_test < SIZE; j_test++)
		{
			bool found = false;

			// search in the goal
			for (i_goal = 0; i_goal < SIZE; i_goal++)
			{
				for (j_goal = 0; j_goal < SIZE; j_goal++)
				{
					if (test[i_test][j_test] == goal[i_goal][j_goal]) {
						found = true;
						break;
					}
				}

				if (found)
					break;

				j_goal = 0;
			}

			if (found) {
				sum += abs((i_test - i_goal) + (j_test - j_goal));
				i_goal = 0;
				j_goal = 0;
			}
			else {
				throw CustomException("Error to find the manhattan distance");
			}
		}
	}

	return sum;
}

TreeNode<int**>* Puzzle8::get_new_node(TreeNode<int**>* node)
{
	int** copy = new int*[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		copy[i] = new int[SIZE];

		for (int j = 0; j < SIZE; j++)
		{
			copy[i][j] = node->content[i][j];
		}
	}
	
	TreeNode<int**>* new_node = new TreeNode<int**>(copy, node, 0);
	node->children_nodes->enqueue(new_node);

	return new_node;
}

void Puzzle8::print_tree()
{
	this->print_node_children(this->root);
}

void Puzzle8::test()
{
	throw CustomException("test not implemented");
}

bool Puzzle8::compare_explored(int ** first, int ** second)
{
	return this->compare(first, second);
}

void Puzzle8::print_content(int ** content)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cout << content[i][j] << "   ";
		}

		cout << endl;
	}
}

void Puzzle8::print_node(TreeNode<int**>* node)
{
	if (node == NULL) {
		cout << "Node is null or empty" << endl;
		return;
	}

	cout << "Id: " << node->id << " | g_score: " << node->g_score << " | h_score: " << node->h_score << " | f_score " << node->f_score << endl;
	this->print_content(node->content);
}

void Puzzle8::print_node_children(TreeNode<int**>* node)
{
	cout << "Id: " << node->id << " | g_score: " << node->g_score << " | h_score: " << node->h_score << " | f_score " << node->f_score << endl;
	this->print_children(node);
}

void Puzzle8::print_children(TreeNode<int**>* node)
{
	if (node != NULL) {
		if (node->has_children()) {
			SimpleNode<TreeNode<int**>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				this->print_node(child->content);
				child = child->next_node;
			}
		}
	}
}
