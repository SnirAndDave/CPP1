#include "TopRightRecursiveSolver.h"
#include <algorithm>
#include "Puzzle.h"

using namespace std;


TopRightRecursiveSolver::TopRightRecursiveSolver()
= default;


TopRightRecursiveSolver::~TopRightRecursiveSolver()
= default;


bool TopRightRecursiveSolver::solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
                                    vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished)
{
	sort_elements(remaining_elements);
	return rec_solve(0, dimensions.second - 1, is_rotation_enabled, dimensions, puzzle, remaining_elements, finished);
}

void TopRightRecursiveSolver::sort_elements(vector<Element>& elements)
{
	sort(elements.begin(), elements.end(), [](const Element& a, const Element& b) -> bool
	{
		if (a._bottom == 0 && b._bottom != 0)
		{
			return false;
		}
		if (b._bottom == 0 && a._bottom != 0)
		{
			return true;
		}
		if (a._top == 0 && b._top != 0)
		{
			return true;
		}
		if (b._top == 0 && a._top != 0)
		{
			return false;
		}
		return false;
	});
}

bool TopRightRecursiveSolver::can_be_placed(const int r, const int c, const pair<int, int>& dimensions,
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


bool TopRightRecursiveSolver::rec_solve(const int r, const int c, const bool is_rotation_enabled,
                                        pair<int, int>& dimensions,
                                        vector<vector<Element>>& mat, vector<Element>& remaining_elements, const bool& finished) const
{
	if (finished)
	{
		throw exception();
	}
	const int iterations = is_rotation_enabled ? 4 : 1;
	if (remaining_elements.empty() || r == dimensions.first)
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
			const int next_c = c == 0 ? dimensions.second - 1 : c - 1;
			const int next_r = next_c == dimensions.second - 1 ? r + 1 : r;
			if (rec_solve(next_r, next_c, is_rotation_enabled, dimensions, mat, remaining_elements_copy, finished))
			{
				return true;
			}
			mat[r][c] = Element();
		}
	}
	return false;
}
