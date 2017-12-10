#include "RightRecursiveSolver.h"

#include <sstream>
#include <algorithm>
#include "RecursiveSolver.h"
#include "Puzzle.h"

using namespace std;


RightRecursiveSolver::RightRecursiveSolver()
{
}


RightRecursiveSolver::~RightRecursiveSolver()
{
}


bool RightRecursiveSolver::solve(pair<int, int>& dimentions, vector<vector<Element>>& puzzle,
	vector<Element>& remaining_elements)
{
	return rec_solve(0, dimentions.second-1, dimentions, puzzle, remaining_elements);
}

bool RightRecursiveSolver::can_be_placed(int r, int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat,
	const Element& element)
{
	if (Puzzle::get_element(mat, r - 1, c).bottom + element.top != 0)
	{
		return false;
	}
	if (Puzzle::get_element(mat, r, c + 1).left + element.right != 0)
	{
		return false;
	}
	if (r == dimensions.first - 1 && element.bottom != 0)
	{
		return false;
	}
	if (c == 0 && element.left != 0)
	{
		return false;
	}
	return true;
}


bool RightRecursiveSolver::rec_solve(int r, int c, pair<int, int>& dimensions, vector<vector<Element>>& mat,
	vector<Element>& remaining_elements)
{
	if (remaining_elements.empty() || c == dimensions.second)
	{
		return true;
	}
	for (Element remaining_element : remaining_elements)
	{
		if (!can_be_placed(r, c, dimensions, mat, remaining_element))
		{
			continue;
		}
		mat[r][c] = remaining_element;
		vector<Element> remaining_elements_copy = remaining_elements;
		remaining_elements_copy.erase(
			remove(remaining_elements_copy.begin(), remaining_elements_copy.end(), remaining_element)
			, remaining_elements_copy.end()); // remove the element we placed in the puzzle from the remaining elements
		int next_r = (r + 1) % dimensions.first; // end of line
		int next_c = next_r == 0 ? c - 1 : c;
		if (rec_solve(next_r, next_c, dimensions, mat, remaining_elements_copy))
		{
			return true;
		}
		mat[r][c] = Element();
	}
	return false;
}
