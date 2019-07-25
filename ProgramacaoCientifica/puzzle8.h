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
};

#endif
