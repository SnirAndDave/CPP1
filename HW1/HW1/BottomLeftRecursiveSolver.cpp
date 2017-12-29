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

bool BottomLeftRecursiveSolver::solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
                                      vector<vector<Element>>& puzzle, vector<Element>& remaining_elements)
{
	sort_elements(remaining_elements);
	return rec_solve(dimensions.first - 1, 0, is_rotation_enabled, dimensions, puzzle, remaining_elements);
}

bool BottomLeftRecursiveSolver::can_be_placed(const int r, const int c, const pair<int, int>& dimensions,
                                              const vector<vector<Element>>& mat,
                                              const Element& element)
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


bool BottomLeftRecursiveSolver::rec_solve(const int r, const int c, const bool is_rotation_enabled,
                                          pair<int, int>& dimensions,
                                          vector<vector<Element>>& mat, vector<Element>& remaining_elements) const
{
	const int iterations = is_rotation_enabled ? 4 : 1;
	if (remaining_elements.empty() || r == -1)
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
			const int next_c = (c + 1) % dimensions.second;
			const int next_r = next_c == 0 ? r - 1 : r;
			if (rec_solve(next_r, next_c, is_rotation_enabled, dimensions, mat, remaining_elements_copy))
			{
				return true;
			}
			mat[r][c] = Element();
		}
	}
	return false;
}
