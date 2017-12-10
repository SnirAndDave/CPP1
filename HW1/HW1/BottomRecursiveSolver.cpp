#include "BottomRecursiveSolver.h"
#include <sstream>
#include <algorithm>


using namespace std;


BottomRecursiveSolver::BottomRecursiveSolver()
{
}


BottomRecursiveSolver::~BottomRecursiveSolver()
{
}


bool BottomRecursiveSolver::solve(pair<int, int>& dimentions, vector<vector<Element>>& puzzle,
	vector<Element>& remaining_elements)
{
	return rec_solve(dimentions.first-1, 0, dimentions, puzzle, remaining_elements);
}

bool BottomRecursiveSolver::can_be_placed(int r, int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat,
	const Element& element)
{
	if (Puzzle::get_element(mat, r + 1, c).top + element.bottom != 0)
	{
		return false;
	}
	if (Puzzle::get_element(mat, r, c - 1).right + element.left != 0)
	{
		return false;
	}
	if (r == 0  && element.top != 0)
	{
		return false;
	}
	if (c == dimensions.second - 1 && element.right != 0)
	{
		return false;
	}
	return true;
}


bool BottomRecursiveSolver::rec_solve(int r, int c, pair<int, int>& dimensions, vector<vector<Element>>& mat,
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
		int next_c = (c + 1) % dimensions.second;
		int next_r = next_c == 0 ? r - 1 : r;
		if (rec_solve(next_r, next_c, dimensions, mat, remaining_elements_copy))
		{
			return true;
		}
		mat[r][c] = Element();
	}
	return false;
}
