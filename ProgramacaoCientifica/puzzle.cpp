#include "pch.h"
#include "puzzle.h"

Puzzle::Puzzle() : Tree(CHILDREN_NODES)
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
