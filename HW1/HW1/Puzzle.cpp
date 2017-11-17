#include <list>

#include "Puzzle.h"
#include <sstream>
using namespace std;

string corner_to_string(Corner corner)
{
	switch (corner)
	{
	case TL:
		return "TL";
	case TR:
		return "TR";
	case BR:
		return "BR";
	case BL:
		return "BL";
	}
	return {};
}

vector<Corner> Puzzle::find_missing_corners()
{
	bool found_corners[4] = {false, false, false, false};
	bool is_valid = true;
	vector<Corner> missing_corners;
	for (Element element : this->elements)
	{
		if (element.top == 0 && element.left == 0)
		{
			found_corners[TL] = true;
		}
		if (element.top == 0 && element.right == 0)
		{
			found_corners[TR] = true;
		}
		if (element.bottom == 0 && element.left == 0)
		{
			found_corners[BL] = true;
		}
		if (element.bottom == 0 && element.right == 0)
		{
			found_corners[BR] = true;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (!found_corners[i])
		{
			Corner corner = Corner(i);
			missing_corners.push_back(corner);
			ostringstream oss;
			 oss << "Cannot solve puzzle: missing corner element: " + corner_to_string(corner);
			 fout << oss.str() << endl;
			 is_valid = false;
		}
	}
	return missing_corners;
}

bool Puzzle::validate_sum_of_edges(ofstream& fout)
{
	int sum = 0;
	for (Element element : this->elements)
	{
		sum += (element.left
			+ element.top
			+ element.right
			+ element.bottom);
	}
	if (sum != 0)
	{
		ostringstream oss;
		oss << "Cannot solve puzzle: sum of edges is not zero";
		fout << oss.str() << endl;
	}
	return sum == 0;
}

void Puzzle::solve()
{
	vector<pair<int, int>> dimentions = size_to_matrices();
	vector<pair<int, int>> valid_dimentions = get_valid_dimentions(dimentions);
	vector<Corner> missing_corners = find_missing_corners();
	bool is_sum_zero = validate_sum_of_edges();

	if (!is_sum_zero || !missing_corners.empty() || valid_dimentions.empty())
	{
		return;
	}

	for (auto row_col_pair : valid_dimentions)
	{
		vector<Element**> matrices = create_all_permutations_of_dimention(row_col_pair);
		for (auto matrix : matrices)
		{
			if (verify_matrix(matrix, row_col_pair))
			{
				return;
			}
		}
	}
	this->fout << "cannot solve";
}
