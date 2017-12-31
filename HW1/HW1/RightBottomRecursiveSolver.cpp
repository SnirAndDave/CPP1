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

bool RightBottomRecursiveSolver::can_be_placed(const int r, const int c, const pair<int, int>& dimensions,
                                               const vector<vector<Element>>& mat,
                                               const Element& element)
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


bool RightBottomRecursiveSolver::rec_solve(const int r, const int c, const bool is_rotation_enabled,
                                           pair<int, int>& dimensions,
                                           vector<vector<Element>>& mat, vector<Element>& remaining_elements, const bool& finished) const
{
	if(finished)
	{
		throw exception();
	}
	const int iterations = is_rotation_enabled ? 4 : 1;
	if (remaining_elements.empty() || c == -1)
	{
		return true;
	}
	for (Element remaining_element : remaining_elements)
	{
		for (int i = 0; i < iterations; i++)
		{
			if (is_rotation_enabled)
			{
				remaining_element.rotate_right();
			}
			if (!can_be_placed(r, c, dimensions, mat, remaining_element))
			{
				continue;
			}
			mat[r][c] = remaining_element;
			vector<Element> remaining_elements_copy = remaining_elements;
			remaining_elements_copy.erase(
				remove(remaining_elements_copy.begin(), remaining_elements_copy.end(), remaining_element)
				, remaining_elements_copy.end()); // remove the element we placed in the puzzle from the remaining _elements
			const int next_r = r == 0 ? dimensions.first - 1 : r - 1;
			const int next_c = next_r == dimensions.first - 1 ? c - 1 : c;
			if (rec_solve(next_r, next_c, is_rotation_enabled, dimensions, mat, remaining_elements_copy, finished))
			{
				return true;
			}
			mat[r][c] = Element();
		}
	}
	return false;
}
