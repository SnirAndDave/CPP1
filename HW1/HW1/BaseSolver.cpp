#include "BaseSolver.h"
#include "Puzzle.h"


BaseSolver::BaseSolver()
{
}


BaseSolver::~BaseSolver()
{
}


bool BaseSolver::can_be_placed(const int r, const int c, const pair<int, int>& dimensions,
                               const vector<vector<Element>>& mat,
                               const Element& element)
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
