#include "LeftTopRecursiveSolver.h"
#include <algorithm>
#include "Puzzle.h"


using namespace std;


LeftTopRecursiveSolver::LeftTopRecursiveSolver()
= default;


LeftTopRecursiveSolver::~LeftTopRecursiveSolver()
= default;


bool LeftTopRecursiveSolver::solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
                                   vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished)
{
	sort_elements(remaining_elements);
	return rec_solve(0, 0, is_rotation_enabled, dimensions, puzzle, remaining_elements, finished);
}

void LeftTopRecursiveSolver::sort_elements(vector<Element>& elements)
{
	sort(elements.begin(), elements.end(), [](const Element& a, const Element& b) -> bool
	{
		if (a._right == 0 && b._right != 0)
		{
			return false;
		}
		if (b._right == 0 && a._right != 0)
		{
			return true;
		}
		if (a._left == 0 && b._left != 0)
		{
			return true;
		}
		if (b._left == 0 && a._left != 0)
		{
			return false;
		}
		return false;
	});
}

bool LeftTopRecursiveSolver::can_be_placed(const int r, const int c, const vector<vector<Element>>& mat,
	const Element& element, pair<int, int> dimensions) const
{	
	if (Puzzle::get_element(mat, r - 1, c)._bottom + element._top != 0)
	{
		return false;
	}
	if (Puzzle::get_element(mat, r, c - 1)._right + element._left != 0)
	{
		return false;
	}
	if (r == dimensions.first - 1 && element._bottom != 0)
	{
		return false;
	}
	if (c == dimensions.second - 1 && element._right != 0)
	{
		return false;
	}
	return true;
}

bool LeftTopRecursiveSolver::halt_condition(const int, const int c, pair<int, int> dimensions) const
{
	return c == dimensions.second;
}

pair<int, int> LeftTopRecursiveSolver::get_next_indices(const int r, const int c, const pair<int, int> dimensions) const
{
	const int next_r = (r + 1) % dimensions.first; // end of line
	const int next_c = next_r == 0 ? c + 1 : c;
	return pair<int, int>(next_r, next_c);
}
