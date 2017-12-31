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
