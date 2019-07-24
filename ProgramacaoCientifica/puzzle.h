#include <iostream>
#include "tree.h"

#ifndef PUZZLE_H
#define PUZZLE_H
#define SIZE 3
#define CHILDREN_NODES 3

using namespace std;

class Puzzle : Tree<int[SIZE][SIZE]> {
public:
	Puzzle();
	~Puzzle();

	bool compare(int first[SIZE][SIZE], int second[SIZE][SIZE]) override;
};

#endif
