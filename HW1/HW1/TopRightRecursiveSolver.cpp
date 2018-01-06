#include "TopRightRecursiveSolver.h"
#include <algorithm>
#include "Puzzle.h"

using namespace std;


TopRightRecursiveSolver::TopRightRecursiveSolver()
= default;


TopRightRecursiveSolver::~TopRightRecursiveSolver()
= default;

/**
 * sorts the unused elements, and calls rec_solver while giving start coordinates
 */
bool TopRightRecursiveSolver::solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
                                    vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished)
{
	sort_elements(remaining_elements);
	return rec_solve(0, dimensions.second - 1, is_rotation_enabled, dimensions, puzzle, remaining_elements, finished);
}

/**
 * Sorts the unused elements to make the solver run quicker
 * It takes into consideration the relevant edges with the start or end of the puzzle frame side
 */
void TopRightRecursiveSolver::sort_elements(vector<Element>& elements)
{
	sort(elements.begin(), elements.end(), [](const Element& a, const Element& b) -> bool
	{
		if (a._bottom == 0 && b._bottom != 0)
		{
			return false;
		}
		if (b._bottom == 0 && a._bottom != 0)
		{
			return true;
		}
		if (a._top == 0 && b._top != 0)
		{
			return true;
		}
		if (b._top == 0 && a._top != 0)
		{
			return false;
		}
		return false;
	});
}

bool TopRightRecursiveSolver::can_be_placed(const int r, const int c, const vector<vector<Element>>& mat,
	const Element& element, pair<int, int> dimensions) const
{
	if (Puzzle::get_element(mat, r - 1, c)._bottom + element._top != 0)
	{
		return false;
	}
	if (Puzzle::get_element(mat, r, c + 1)._left + element._right != 0)
	{
		return false;
	}
	if (r == dimensions.first - 1 && element._bottom != 0)
	{
		return false;
	}
	if (c == 0 && element._left != 0)
	{
		return false;
	}
	return true;
}

bool TopRightRecursiveSolver::halt_condition(const int r, const int, pair<int, int> dimensions) const
{
	return r == dimensions.first;
}

pair<int, int> TopRightRecursiveSolver::get_next_indices(const int r, const int c, const pair<int, int> dimensions) const
{
	const int next_c = c == 0 ? dimensions.second - 1 : c - 1;
	const int next_r = next_c == dimensions.second - 1 ? r + 1 : r; //determine the location of the next piece
	return pair<int, int>(next_r, next_c);
}
