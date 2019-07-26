#include <iostream>
#include "puzzle.h"

#ifndef PUZZLE_8_H
#define PUZZLE_8_H
#define SIZE 3

using namespace std;

class Puzzle8 : Puzzle<int[SIZE][SIZE]> {
public:
	Puzzle8();
	~Puzzle8();

	bool compare(int first[SIZE][SIZE], int second[SIZE][SIZE]) override;
	void create_children_nodes(TreeNode<int[SIZE][SIZE]>* node) override;
	TreeNode<int[SIZE][SIZE]>* get_copy(int content[SIZE][SIZE]);
};

#endif
