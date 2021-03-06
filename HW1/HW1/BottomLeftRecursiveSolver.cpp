#include "BottomLeftRecursiveSolver.h"
#include <algorithm>


using namespace std;


BottomLeftRecursiveSolver::BottomLeftRecursiveSolver()
= default;


BottomLeftRecursiveSolver::~BottomLeftRecursiveSolver()
= default;

void BottomLeftRecursiveSolver::sort_elements(vector<Element>& elements)
{
	sort(elements.begin(), elements.end(), [](const Element& a, const Element& b) -> bool
	{
		if (a._top == 0 && b._top != 0)
		{
			return false;
		}
		if (b._top == 0 && a._top != 0)
		{
			return true;
		}
		if (a._bottom == 0 && b._bottom != 0)
		{
			return true;
		}
		if (b._bottom == 0 && a._bottom != 0)
		{
			return false;
		}
		return false;
	});
}

bool BottomLeftRecursiveSolver::halt_condition(const int r, const int , pair<int, int>) const
{
	return r == -1;
}

bool BottomLeftRecursiveSolver::solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
                                      vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished)
{
	sort_elements(remaining_elements);
	return rec_solve(dimensions.first - 1, 0, is_rotation_enabled, dimensions, puzzle, remaining_elements, finished);
}

bool BottomLeftRecursiveSolver::can_be_placed(const int r, const int c,
                                              const vector<vector<Element>>& mat,
                                              const Element& element, pair<int, int> dimensions) const
{
	if (Puzzle::get_element(mat, r + 1, c)._top + element._bottom != 0)
	{
		return false;
	}
	if (Puzzle::get_element(mat, r, c - 1)._right + element._left != 0)
	{
		return false;
	}
	if (r == 0 && element._top != 0)
	{
		return false;
	}
	if (c == dimensions.second - 1 && element._right != 0)
	{
		return false;
	}
	return true;
}

pair<int, int> BottomLeftRecursiveSolver::get_next_indices(const int r, const int c,
	const pair<int, int> dimensions) const
{
	const int next_c = (c + 1) % dimensions.second;
	const int next_r = next_c == 0 ? r - 1 : r;
	return pair<int, int>(next_r, next_c);
}
