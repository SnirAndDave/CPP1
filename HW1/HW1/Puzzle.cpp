#include "Puzzle.h"
#include <sstream>
#include <algorithm>
#include <memory>
#include "BaseSolver.h"
#include "RotationRecursiveSolver.h"
#include "RecursiveSolver.h"
#include "LeftRecursiveSolver.h"
#include "RightRecursiveSolver.h"
#include "BottomRecursiveSolver.h"

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
	int iterations = is_rotation_enabled ? 4 : 1;
	vector<Corner> missing_corners;
	for (Element element : this->elements)
	{
		for (int i = 0; i < iterations; i++)
		{
			if (is_rotation_enabled)
			{
				element.rotate_right();
			}
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
	std::size_t rsize = vector.size();
	for (std::size_t r = 0; r < rsize; r++)
	{
		std::size_t csize = vector[r].size();
		for (std::size_t c = 0; c < csize; c++)
		{
			this->m_fout << vector[r][c].id;
			if (vector[r][c].rotation() != 0)
			{
				this->m_fout << " [" << vector[r][c].rotation() << "]";
			}
			if (c < csize - 1)
			{
				this->m_fout << " ";
			}
		}
		m_fout << endl;
	}
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
	// sort by min dimention
	sort(ret.begin(), ret.end(),[](const pair<int,int> & a, const pair<int,int> & b) -> bool
	{
		int min_a = min(a.first, a.second);
		int min_b = min(b.first, b.second);
		return min_a > min_b;
	});
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

vector<pair<int, int>> Puzzle::get_valid_dimensions(vector<pair<int, int>> dimensions)
{
	vector<pair<int, int>> valid_dimensions;
	int straight_edges_count = get_straight_edges_count();
	for (auto dimension : dimensions)
	{
		if (2 * (dimension.first + dimension.second) <= straight_edges_count)
		{
			valid_dimensions.push_back(dimension);
		}
	}
	if (valid_dimensions.empty())
	{
		ostringstream oss;
		oss << "Cannot solve puzzle: wrong number of straight edges";
		m_fout << oss.str() << endl;
	}
	return valid_dimensions;
}

vector<vector<vector<Element>>> Puzzle::create_all_permutations_of_dimension(pair<int, int> dimensions)
{
	vector<Element> copy = elements;
	sort(copy.begin(), copy.end());
	vector<vector<vector<Element>>> ret;
	do
	{
		vector<vector<Element>> mat = vector_to_mat(copy, dimensions);
		ret.push_back(mat);
	}
	while (next_permutation(copy.begin(), copy.end()));
	return ret;
}

vector<vector<Element>> Puzzle::vector_to_mat(vector<Element> copy, pair<int, int> dimensions)
{
	int vectorIndex = 0;
	vector<vector<Element>> ret;
	for (int row = 0; row < int(dimensions.first); row++)
	{
		vector<Element> vec;
		ret.push_back(vec);
		for (int col = 0; col < int(dimensions.second); col++)
		{
			ret[row].push_back(copy[vectorIndex]);
			vectorIndex++;
		}
	}
	return ret;
}

Element Puzzle::get_element(const vector<vector<Element>> mat, int r, int c)
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
			if (get_element(mat, r - 1, c).bottom + elem.top != 0)
			{
				return false;
			}
			if (get_element(mat, r + 1, c).top + elem.bottom != 0)
			{
				return false;
			}
			if (get_element(mat, r, c - 1).right + elem.left != 0)
			{
				return false;
			}
			if (get_element(mat, r, c + 1).left + elem.right != 0)
			{
				return false;
			}
		}
	}
	return true;
}


vector<vector<Element>> Puzzle::create_empty_mat(const pair<int, int>& dimensions)
{
	vector<vector<Element>> ret;
	for (int r = 0; r < dimensions.first; r++)
	{
		vector<Element> col;
		for (int c = 0; c < dimensions.second; c++)
		{
			col.push_back(Element());
		}
		ret.push_back(col);
	}
	return ret;
}

unique_ptr<BaseSolver> Puzzle::choose_solver()
{
	if (is_rotation_enabled)
	{
		return make_unique<RotationRecursiveSolver>();
	}
	int edges_count[4] = {0,0,0,0};
	for (Element element : elements)
	{
		edges_count[0] += (element.left == 0 ? 1 : 0);
		edges_count[1] += (element.top == 0 ? 1 : 0);
		edges_count[2] += (element.right == 0 ? 1 : 0);
		edges_count[3] += (element.bottom == 0 ? 1 : 0);
	}
	int min_edge_index = distance(edges_count, min_element(edges_count, edges_count + 4));
	unique_ptr<BaseSolver> ret;
	switch (min_edge_index)
	{
	case 0:
		ret = make_unique<LeftRecursiveSolver>();
		break;
	case 1:
		ret = make_unique<RecursiveSolver>();
		break;
	case 2:
		ret = make_unique<RightRecursiveSolver>();
		break;
	default:
		ret = make_unique<BottomRecursiveSolver>();
		break;

	}
	return ret;
}

void Puzzle::solve()
{
	vector<pair<int, int>> dimensions = size_to_matrices();
	vector<pair<int, int>> valid_dimensions = get_valid_dimensions(dimensions);
	vector<Corner> missing_corners = find_missing_corners();
	bool is_sum_zero = validate_sum_of_edges();

	if (!is_sum_zero || !missing_corners.empty() || valid_dimensions.empty())
	{
		return;
	}

	unique_ptr<BaseSolver> solver = choose_solver();
	for (pair<int, int> row_col_pair : valid_dimensions)
	{
		vector<Element> elements_copy = elements;
		vector<vector<Element>> mat = create_empty_mat(row_col_pair);

		if (solver->solve(row_col_pair, mat, elements_copy))
		{
			print_solution(mat);
			return;
		}
	}
	this->m_fout << "Cannot solve puzzle: it seems that there is no proper solution" << endl;
}
