#include "BaseSolver.h"
#include "Puzzle.h"


BaseSolver::BaseSolver()
{
}


BaseSolver::~BaseSolver()
{
}


void BaseSolver::sort_elements(vector<Element>& elements)
{
}

bool BaseSolver::can_be_placed(int r, int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat,
	const Element& element)
{
	if (Puzzle::get_element(mat, r - 1, c).bottom + element.top != 0)
	{
		return false;
	}
	if (Puzzle::get_element(mat, r, c - 1).right + element.left != 0)
	{
		return false;
	}
	if (r == dimensions.first - 1 && element.bottom != 0)
	{
		return false;
	}
	if (c == dimensions.second - 1 && element.right != 0)
	{
		return false;
	}
	return true;
}
