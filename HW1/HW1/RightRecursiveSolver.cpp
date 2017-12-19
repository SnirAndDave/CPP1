#include "RightRecursiveSolver.h"
#include <sstream>
#include <algorithm>


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
	sort_elements(remaining_elements);
	return rec_solve(0, dimentions.second - 1, dimentions, puzzle, remaining_elements);
}

void RightRecursiveSolver::sort_elements(vector<Element>& elements)
{
	sort(elements.begin(), elements.end(), [](const Element & a, const Element & b) -> bool
	{
		if (a.left == 0 && b.left != 0)
		{
			return false;
		}
		if (b.left == 0 && a.left != 0)
		{
			return true;
		}
		if (a.right == 0 && b.right != 0)
		{
			return true;
		}
		if (b.right == 0 && a.right != 0)
		{
			return false;
		}
		return false;
	});
}

bool RightRecursiveSolver::can_be_placed(const int r, const int c, const pair<int, int>& dimensions,
                                         const vector<vector<Element>>& mat,
                                         const Element& element)
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


bool RightRecursiveSolver::rec_solve(const int r, const int c, pair<int, int>& dimensions, vector<vector<Element>>& mat,
                                     vector<Element>& remaining_elements)
{
	if (remaining_elements.empty() || c == dimensions.second)
	{
		return true;
	}
	for (const Element remaining_element : remaining_elements)
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
		const int next_r = (r + 1) % dimensions.first; // end of line
		const int next_c = next_r == 0 ? c - 1 : c;
		if (rec_solve(next_r, next_c, dimensions, mat, remaining_elements_copy))
		{
			return true;
		}
		mat[r][c] = Element();
	}
	return false;
}
