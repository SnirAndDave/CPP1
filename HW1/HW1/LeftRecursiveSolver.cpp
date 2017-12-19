#include "LeftRecursiveSolver.h"
#include <sstream>
#include <algorithm>


using namespace std;


LeftRecursiveSolver::LeftRecursiveSolver()
{
}


LeftRecursiveSolver::~LeftRecursiveSolver()
{
}


bool LeftRecursiveSolver::solve(pair<int, int>& dimentions, vector<vector<Element>>& puzzle,
                                vector<Element>& remaining_elements)
{
	return rec_solve(0, 0, dimentions, puzzle, remaining_elements);
}


bool LeftRecursiveSolver::rec_solve(const int r, const int c, pair<int, int>& dimensions, vector<vector<Element>>& mat,
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
		const int next_c = next_r == 0 ? c + 1 : c;
		if (rec_solve(next_r, next_c, dimensions, mat, remaining_elements_copy))
		{
			return true;
		}
		mat[r][c] = Element();
	}
	return false;
}
