#include <list>

#include "Puzzle.h"
#include <sstream>
#include <algorithm>
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
			m_fout << oss.str() << endl;
		}
	}
	return missing_corners;
}

bool Puzzle::validate_sum_of_edges()
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
		m_fout << oss.str() << endl;
	}
	return sum == 0;
}

void Puzzle::print_solution(const vector<vector<Element>>& vector)
{
	int rsize = vector.size();
	for (int r = 0; r < rsize; r++)
	{
		int csize = vector[r].size();
		for (int c = 0; c < csize; c++)
		{
			this->m_fout << vector[r][c].id;
			if (c < csize - 1)
			{
				this->m_fout << " ";
			}
		}
		m_fout << endl;
	}
	bug
}

vector<pair<int, int>> Puzzle::size_to_matrices()
{
	vector<pair<int, int>> ret;
	for (int i = 1; i <= size; i++)
	{
		if (size % i == 0)
		{
			ret.push_back(pair<int, int>(i, size / i));
		}
	}
	return ret;
}

int Puzzle::get_straight_edges_count()
{
	int cnt = 0;
	for (Element element : this->elements)
	{
		cnt += element.left == 0 ? 1 : 0;
		cnt += element.top == 0 ? 1 : 0;
		cnt += element.right == 0 ? 1 : 0;
		cnt += element.bottom == 0 ? 1 : 0;
	}
	return cnt;
}

vector<pair<int, int>> Puzzle::get_valid_dimentions(vector<pair<int, int>> dimentions)
{
	vector<pair<int, int>> valid_dimentions;
	int straight_edges_count = get_straight_edges_count();
	for (auto dimention : dimentions)
	{
		if (2 * (dimention.first + dimention.second) <= straight_edges_count)
		{
			valid_dimentions.push_back(dimention);
		}
	}
	if (valid_dimentions.empty())
	{
		ostringstream oss;
		oss << "Cannot solve puzzle: wrong number of straight edges";
		m_fout << oss.str() << endl;
	}
	return valid_dimentions;
}

vector<vector<vector<Element>>> Puzzle::create_all_permutations_of_dimention(pair<int, int> dimentions)
{
	vector<Element> copy = elements;
	sort(copy.begin(), copy.end());
	vector<vector<vector<Element>>> ret;
	do
	{
		vector<vector<Element>> mat = vector_to_mat(copy, dimentions);
		ret.push_back(mat);
	}
	while (next_permutation(copy.begin(), copy.end()));
	return ret;
}

vector<vector<Element>> Puzzle::vector_to_mat(vector<Element> copy, pair<int, int> dimentions)
{
	int vectorIndex = 0;
	vector<vector<Element>> ret;
	for (int row = 0; row < int(dimentions.first); row++)
	{
		vector<Element> vec;
		ret.push_back(vec);
		for (int col = 0; col < int(dimentions.second); col++)
		{
			ret[row].push_back(copy[vectorIndex]);
			vectorIndex++;
		}
	}
	return ret;
}

Element Puzzle::getElement(const vector<vector<Element>> mat, int r, int c)
{
	if (r < 0 || c < 0 || r >= int(mat.size()) || c >= int(mat[r].size()))
	{
		return Element(0, 0, 0, 0, 0);
	}
	return mat[r][c];
}

bool Puzzle::verify_matrix(vector<vector<Element>> mat)
{
	for (int r = 0; r < int(mat.size()); r++)
	{
		for (int c = 0; c < int(mat[r].size()); c++)
		{
			auto elem = mat[r][c];
			if (getElement(mat, r - 1, c).bottom + elem.top != 0)
			{
				return false;
			}
			if (getElement(mat, r + 1, c).top + elem.bottom != 0)
			{
				return false;
			}
			if (getElement(mat, r, c - 1).right + elem.left != 0)
			{
				return false;
			}
			if (getElement(mat, r, c + 1).left + elem.right != 0)
			{
				return false;
			}
		}
	}
	return true;
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
		vector<Element> copy = elements;
		sort(copy.begin(), copy.end());
		do
		{
			vector<vector<Element>> mat = vector_to_mat(copy, row_col_pair);
			if (verify_matrix(mat))
			{
				print_solution(mat);
				return;
			}
		} while (next_permutation(copy.begin(), copy.end()));
	}
	this->m_fout << "Cannot solve puzzle: it seems that there is no proper solution" << endl;
}
