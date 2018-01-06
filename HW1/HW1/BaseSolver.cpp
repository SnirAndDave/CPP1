#include "BaseSolver.h"
#include "Puzzle.h"
#include <algorithm>


BaseSolver::BaseSolver()
= default;


BaseSolver::~BaseSolver()
= default;

void BaseSolver::sort_elements(vector<Element>& elements)
{
	sort(elements.begin(), elements.end());
}
/**
* Recursive solver for the puzzle. With each call the matrix gets fuller and the vector of remaining elements gets smaller.
*/
bool BaseSolver::rec_solve(const int r, const int c, const bool is_rotation_enabled,
	pair<int, int>& dimensions,
	vector<vector<Element>>& mat, vector<Element>& remaining_elements, const bool& finished) const
{
	if (finished)
	{
		throw exception();
	}
	const int iterations = is_rotation_enabled ? 4 : 1;
	if (remaining_elements.empty() || halt_condition(r,c, dimensions)) //end of recursion -> puzzle solved!
	{
		return true;
	}
	for (Element remaining_element : remaining_elements)
	{
		for (int i = 0; i < iterations; i++)
		{
			if (is_rotation_enabled) //if rotation is enabled the piece will rotate 4 times
			{
				remaining_element.rotate_right();
			}
			if (!can_be_placed(r, c, mat, remaining_element, dimensions)) //if piece can't be placed, go to the next one
			{
				continue;
			}
			mat[r][c] = remaining_element;
			vector<Element> remaining_elements_copy = remaining_elements;
			remaining_elements_copy.erase(
				remove(remaining_elements_copy.begin(), remaining_elements_copy.end(), remaining_element)
				, remaining_elements_copy.end()); // remove the element we placed in the puzzle from the remaining _elements
			pair<int, int> next_indices = get_next_indices(r, c, dimensions);
			const int next_r = next_indices.first; //determine the location of the next piece
			const int next_c = next_indices.second;
			if (rec_solve(next_r, next_c, is_rotation_enabled, dimensions, mat, remaining_elements_copy, finished))
			{
				return true;
			}
			mat[r][c] = Element(); //if we got here, a solution was not found. Place an empty piece in the location
		}
	}
	return false;
}
