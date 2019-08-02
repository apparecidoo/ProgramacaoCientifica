#include <iostream>

#include "pch.h"
#include "custom_exception.h"
#include "linked_list.h"
#include "stack.h"
#include "stack_dynamic.h"
#include "queue.h"
#include "queue_dynamic.h"
#include "puzzle.h"

int main()
{
	int** puzzle_test = new int*[3];
	puzzle_test[0] = new int[3]{ 4, 1, 6 };
	puzzle_test[1] = new int[3]{ 3, 2, 8 };
	puzzle_test[2] = new int[3]{ 7, 0, 5 };

	/*puzzle_test[0] = new int[3]{ 1, 2, 3 };
	puzzle_test[1] = new int[3]{ 4, 0, 5 };
	puzzle_test[2] = new int[3]{ 7, 8, 6 };*/

	/*puzzle_test[0] = new int[3]{ 7, 1, 6 };
	puzzle_test[1] = new int[3]{ 8, 2, 3 };
	puzzle_test[2] = new int[3]{ 4, 0, 5 };*/

	int** goal_test = new int*[3];
	goal_test[0] = new int[3]{ 1, 2, 3 };
	goal_test[1] = new int[3]{ 4, 5, 6 };
	goal_test[2] = new int[3]{ 7, 8, 0 };

	Puzzle<int**> puzzle = Puzzle<int**>(goal_test, Puzzle8);
	TreeNode<int**>* node;
	/*node = NULL;
	node = puzzle.search_dfs(puzzle_test);
	cout << ">>>>>>>>>> DFS RESULT <<<<<<<<<" << endl;
	puzzle.print_node(node);*/

	node = NULL;
	node = puzzle.search_bfs(puzzle_test);
	cout << ">>>>>>>>>> BFS RESULT <<<<<<<<<" << endl;
	puzzle.back_tracking(node);

	/*node = NULL;
	node = puzzle.search_a_star(puzzle_test);
	cout << ">>>>>>>>>> A* RESULT <<<<<<<<<" << endl;
	puzzle.back_tracking(node);*/

	/*node = NULL;
	node = puzzle.search_hill_climbing(puzzle_test);
	cout << ">>>>>>>>>> HILL CLIMBING RESULT <<<<<<<<<" << endl;
	puzzle.back_tracking(node);*/

	system("pause");
	return 0;
}






