#include <iostream>
#include "puzzle.h"

#ifndef PUZZLE_8_H
#define PUZZLE_8_H
#define SIZE 3

using namespace std;

class Puzzle8 : Puzzle<int**> {
public:
	Puzzle8();
	~Puzzle8();

	bool compare(int** first, int** second) override;
	void create_children_nodes(TreeNode<int**>* node) override;
	int manhattan_distance(int** content) override;
	TreeNode<int**>* get_copy(int** content);
};

#endif
