#include "RightBottomRecursiveSolver.h"
#include <algorithm>


using namespace std;


RightBottomRecursiveSolver::RightBottomRecursiveSolver()
= default;


RightBottomRecursiveSolver::~RightBottomRecursiveSolver()
= default;


bool RightBottomRecursiveSolver::solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
                                       vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished)
{
	sort_elements(remaining_elements);
	return rec_solve(dimensions.first - 1, dimensions.second - 1, is_rotation_enabled, dimensions, puzzle,
	                 remaining_elements, finished);
}

void RightBottomRecursiveSolver::sort_elements(vector<Element>& elements)
{
	sort(elements.begin(), elements.end(), [](const Element& a, const Element& b) -> bool
	{
		if (a._left == 0 && b._left != 0)
		{
			return false;
		}
		if (b._left == 0 && a._left != 0)
		{
			return true;
		}
		if (a._right == 0 && b._right != 0)
		{
			return true;
		}
		if (b._right == 0 && a._right != 0)
		{
			return false;
		}
		return false;
	});
}

bool RightBottomRecursiveSolver::can_be_placed(const int r, const int c, const vector<vector<Element>>& mat,
	const Element& element, pair<int, int>) const
{
	if (Puzzle::get_element(mat, r + 1, c)._top + element._bottom != 0)
	{
		return false;
	}
	if (Puzzle::get_element(mat, r, c + 1)._left + element._right != 0)
	{
		return false;
	}
	if (r == 0 && element._top != 0)
	{
		return false;
	}
	if (c == 0 && element._left != 0)
	{
		return false;
	}
	return true;
}

bool RightBottomRecursiveSolver::halt_condition(const int, const int c, pair<int, int>) const
{
	return c == -1;
}

pair<int, int> RightBottomRecursiveSolver::get_next_indices(const int r, const int c, const pair<int, int> dimensions) const
{
	const int next_r = r == 0 ? dimensions.first - 1 : r - 1;
	const int next_c = next_r == dimensions.first - 1 ? c - 1 : c;
	return pair<int, int>(next_r, next_c);

}

