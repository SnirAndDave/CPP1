#include "Puzzle.h"
#include "BaseSolver.h"

#include <sstream>
#include <algorithm>

using namespace std;
class RotationRecursiveSolver : public BaseSolver
{
public:

	bool solve(pair<int, int>& dimentions, vector<vector<Element>>& puzzle,
		vector<Element>& remaining_elements) override
	{
		return rec_solve(0, 0, dimentions, puzzle, remaining_elements);
	}
private:

	bool rec_solve(int r, int c, pair<int, int>& dimensions, vector<vector<Element>>& mat,
		vector<Element>& remaining_elements)
	{
		int iterations =  4;

		if (remaining_elements.empty() || r == dimensions.first)
		{
			return true;
		}
		for (Element remaining_element : remaining_elements)
		{
			for (int i = 0; i < iterations; i++)
			{
				remaining_element.rotate_right();
				if (!can_be_placed(r, c, dimensions, mat, remaining_element))
				{
					continue;
				}
				mat[r][c] = remaining_element;
				vector<Element> remaining_elements_copy = remaining_elements;
				remaining_elements_copy.erase(
					remove(remaining_elements_copy.begin(), remaining_elements_copy.end(), remaining_element),
					remaining_elements_copy.end()); // remove the element we placed in the puzzle from the remaining elements
				int next_c = (c + 1) % dimensions.second; // end of line
				int next_r = next_c == 0 ? r + 1 : r;
				if (rec_solve(next_r, next_c, dimensions, mat, remaining_elements_copy))
				{
					return true;
				}
				mat[r][c] = Element();
			}
		}
		return false;
	}
};