#include <iostream>
#include "puzzle.h"

#ifndef PUZZLE_8_H
#define PUZZLE_8_H
#define SIZE 3

using namespace std;

class Puzzle8 : public Puzzle<int**> {
private:
	bool compare(int** first, int** second) override;
	bool compare_explored(int** first, int** second) override;
	void create_children_nodes(TreeNode<int**>* node) override;
	int manhattan_distance(int** test, int** goal) override;
	TreeNode<int**>* get_new_node(TreeNode<int**>* node);

public:
	Puzzle8(int** goal);
	~Puzzle8();

	void print_content(int** content) override;
	void print_node(TreeNode<int**>* node) override;
	void print_node_children(TreeNode<int**>* node) override;
	void print_children(TreeNode<int**>* node) override;
	void print_tree() override;
	void test() override;
};

#endif
