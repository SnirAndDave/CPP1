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

bool LeftTopRecursiveSolver::can_be_placed(const int r, const int c, const pair<int, int>& dimensions,
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


bool LeftTopRecursiveSolver::rec_solve(const int r, const int c, const bool is_rotation_enabled,
                                       pair<int, int>& dimensions,
                                       vector<vector<Element>>& mat, vector<Element>& remaining_elements, const bool& finished) const
{
	if (finished)
	{
		throw exception();
	}
	const int iterations = is_rotation_enabled ? 4 : 1;
	if (remaining_elements.empty() || c == dimensions.second)
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
			const int next_r = (r + 1) % dimensions.first; // end of line
			const int next_c = next_r == 0 ? c + 1 : c;
			if (rec_solve(next_r, next_c, is_rotation_enabled, dimensions, mat, remaining_elements_copy, finished))
			{
				return true;
			}
			mat[r][c] = Element();
		}
	}
	return false;
}
