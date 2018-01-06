#include "Puzzle.h"
#include <sstream>
#include <algorithm>
#include <memory>
#include <iostream>
#include <thread>

using namespace std;

string corner_to_string(const Corner corner)
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
	const int iterations = _is_rotation_enabled ? 4 : 1;
	vector<Corner> missing_corners;
	for (Element element : this->_elements)
	{
		for (int i = 0; i < iterations; i++)
		{
			if (_is_rotation_enabled)
			{
				element.rotate_right();
			}
			if (element._top == 0 && element._left == 0)
			{
				found_corners[TL] = true;
			}
			if (element._top == 0 && element._right == 0)
			{
				found_corners[TR] = true;
			}
			if (element._bottom == 0 && element._left == 0)
			{
				found_corners[BL] = true;
			}
			if (element._bottom == 0 && element._right == 0)
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
			_fout << oss.str() << endl;
		}
	}
	return missing_corners;
}

bool Puzzle::validate_sum_of_edges()
{
	int sum = 0;
	for (const Element element : this->_elements)
	{
		sum += (element._left
			+ element._top
			+ element._right
			+ element._bottom);
	}
	if (sum != 0)
	{
		ostringstream oss;
		oss << "Cannot solve puzzle: sum of edges is not zero";
		_fout << oss.str() << endl;
	}
	return sum == 0;
}

void Puzzle::print_solution_to_console(const vector<vector<Element>>& matrix)
{
	const size_t rsize = matrix.size();
	for (size_t r = 0; r < rsize; r++)
	{
		const size_t csize = matrix[r].size();
		for (size_t c = 0; c < csize; c++)
		{
			cout << matrix[r][c]._id;

			if (c < csize - 1)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl << endl << endl;
}

void Puzzle::print_solution(const vector<vector<Element>>& matrix) const
{
	const size_t rsize = matrix.size();
	for (size_t r = 0; r < rsize; r++)
	{
		const size_t csize = matrix[r].size();
		for (size_t c = 0; c < csize; c++)
		{
			this->_fout << matrix[r][c]._id;
			if (matrix[r][c].rotation() != 0)
			{
				this->_fout << " [" << matrix[r][c].rotation() << "]";
			}
			if (c < csize - 1)
			{
				this->_fout << " ";
			}
		}
		_fout << endl;
	}
}

vector<pair<int, int>> Puzzle::size_to_matrices() const
{
	vector<pair<int, int>> ret;
	for (int i = 1; i <= _size; i++)
	{
		if (_size % i == 0)
		{
			ret.push_back(pair<int, int>(i, _size / i));
		}
	}
	// sort by min dimention
	sort(ret.begin(), ret.end(), [](const pair<int, int>& a, const pair<int, int>& b) -> bool
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
	for (const Element element : this->_elements)
	{
		cnt += element._left == 0 ? 1 : 0;
		cnt += element._top == 0 ? 1 : 0;
		cnt += element._right == 0 ? 1 : 0;
		cnt += element._bottom == 0 ? 1 : 0;
	}
	return cnt;
}

vector<pair<int, int>> Puzzle::get_valid_dimensions(vector<pair<int, int>> dimensions)
{
	vector<pair<int, int>> valid_dimensions;
	const int straight_edges_count = get_straight_edges_count();
	for (const auto dimension : dimensions)
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
		_fout << oss.str() << endl;
	}
	return valid_dimensions;
}

vector<vector<vector<Element>>> Puzzle::create_all_permutations_of_dimension(const pair<int, int> dimensions) const
{
	vector<Element> copy = _elements;
	sort(copy.begin(), copy.end());
	vector<vector<vector<Element>>> ret;
	do
	{
		const vector<vector<Element>> mat = vector_to_mat(copy, dimensions);
		ret.push_back(mat);
	}
	while (next_permutation(copy.begin(), copy.end()));
	return ret;
}

vector<vector<Element>> Puzzle::vector_to_mat(vector<Element> copy, const pair<int, int> dimensions)
{
	int vectorIndex = 0;
	vector<vector<Element>> ret;
	for (int row = 0; row < int(dimensions.first); row++)
	{
		const vector<Element> vec;
		ret.push_back(vec);
		for (int col = 0; col < int(dimensions.second); col++)
		{
			ret[row].push_back(copy[vectorIndex]);
			vectorIndex++;
		}
	}
	return ret;
}

Element Puzzle::get_element(const vector<vector<Element>>& mat, const int r, const int c)
{
	if (r < 0 || c < 0 || r >= int(mat.size()) || c >= int(mat[r].size()))
	{
		return {0, 0, 0, 0, 0};
	}
	return mat[r][c];
}

bool Puzzle::verify_matrix(vector<vector<Element>> mat)
{
	for (int r = 0; r < int(mat.size()); r++)
	{
		for (int c = 0; c < int(mat[r].size()); c++)
		{
			const auto elem = mat[r][c];
			if (get_element(mat, r - 1, c)._bottom + elem._top != 0)
			{
				return false;
			}
			if (get_element(mat, r + 1, c)._top + elem._bottom != 0)
			{
				return false;
			}
			if (get_element(mat, r, c - 1)._right + elem._left != 0)
			{
				return false;
			}
			if (get_element(mat, r, c + 1)._left + elem._right != 0)
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

vector<shared_ptr<BaseSolver>> Puzzle::choose_solver()
{
	vector<shared_ptr<BaseSolver>> ret;
	double edges_count[4] = {0, 0, 0, 0};
	for (const Element element : _elements)
	{
		edges_count[0] += (element._left == 0 ? 1 : 0);
		edges_count[1] += (element._top == 0 ? 1 : 0);
		edges_count[2] += (element._right == 0 ? 1 : 0);
		edges_count[3] += (element._bottom == 0 ? 1 : 0);

		// give "penalty" for frame edge with multiple corners
		if (element._left == 0 && element._top == 0)
		{
			edges_count[0] += 0.1;
			edges_count[1] += 0.1;
		}
		if (element._top == 0 && element._right == 0)
		{
			edges_count[1] += 0.1;
			edges_count[2] += 0.1;
		}
		if (element._right == 0 && element._bottom == 0)
		{
			edges_count[2] += 0.1;
			edges_count[3] += 0.1;
		}
		if (element._bottom == 0 && element._left == 0)
		{
			edges_count[3] += 0.1;
			edges_count[0] += 0.1;
		}
	}

	int sorted_edges_order[4] = {-1, -1, -1, -1};
	for (int& i : sorted_edges_order)
	{
		double min_elem = 1000.0;
		int min_index = -1;
		for (size_t j = 0; j < 4; j++)
		{
			if (find(begin(sorted_edges_order), end(sorted_edges_order), j) == end(sorted_edges_order))
			{
				//index not used yet
				if (edges_count[j] <= min_elem)
				{
					min_elem = edges_count[j];
					min_index = j;
				}
			}
		}
		i = min_index;
	}
	cout << endl;
	for (int& index : sorted_edges_order)
	{
		cout << index << " ";
		switch (index)
		{
		case 0:
			ret.push_back(make_shared<LeftTopRecursiveSolver>());
			ret.push_back(make_shared<LeftBottomRecursiveSolver>());
			break;
		case 1:
			ret.push_back(make_shared<TopLeftRecursiveSolver>());
			ret.push_back(make_shared<TopRightRecursiveSolver>());
			break;
		case 2:
			ret.push_back(make_shared<RightTopRecursiveSolver>());
			ret.push_back(make_shared<RightBottomRecursiveSolver>());
			break;
		default:
			ret.push_back(make_shared<BottomLeftRecursiveSolver>());
			ret.push_back(make_shared<BottomRightRecursiveSolver>());
			break;
		}
	}
	cout << endl;

	return ret;
}

void Puzzle::solve()
{
	const vector<pair<int, int>> dimensions = size_to_matrices();
	vector<pair<int, int>> valid_dimensions = get_valid_dimensions(dimensions);
	vector<Corner> missing_corners = find_missing_corners();
	const bool is_sum_zero = validate_sum_of_edges();
	vector<thread> vec_threads(_thread_cnt - 1);

	if (!is_sum_zero || !missing_corners.empty() || valid_dimensions.empty())
	{
		return;
	}

	vector<shared_ptr<BaseSolver>> solvers = choose_solver();

	for (pair<int, int> row_col_pair : valid_dimensions)
	{
		_finished = false;
		_solved = false;
		_solution.clear();
		if (_thread_cnt == 1)
		{
			vector<Element> elements_copy = _elements;
			vector<vector<Element>> mat = create_empty_mat(row_col_pair);
			//shared_ptr<BaseSolver> my_solver = make_shared<TopLeftRecursiveSolver>(); //FOR TESTING
			if (solvers[0]->solve(row_col_pair, _is_rotation_enabled, mat, elements_copy, _finished))
			//if (my_solver->solve(row_col_pair, _is_rotation_enabled, mat, elements_copy, _finished))
			{
				print_solution(mat);
				return;
			}
			continue;
		}

		for (int i = 0; i < _thread_cnt - 1; i++)
		{
			vec_threads[i] = thread(&Puzzle::thread_solve, this, row_col_pair, solvers[i]);
		}

		unique_lock<mutex> lock(_mutex);
		_cv.wait(lock, [this] { return _finished; });
		lock.unlock();

		for (thread& t : vec_threads)
		{
			t.join();
		}
		if (_solved)
		{
			print_solution(_solution);
			return;
		}
	}
	this->_fout << "Cannot solve puzzle: it seems that there is no proper solution" << endl;
}

void Puzzle::set_solution(const vector<vector<Element>>& mat, bool solved)
{
	unique_lock<mutex> lock(_mutex);
	if (_finished)
	{
		lock.unlock();
		_cv.notify_all();
		return;
	}
	_finished = true;
	_solved = solved;
	if (solved)
	{
		_solution = mat;
	}
	lock.unlock();
	_cv.notify_all();
}

void Puzzle::thread_solve(pair<int, int> row_col_pair, const shared_ptr<BaseSolver>& solver)
{
	vector<Element> elements_copy;
	for (const Element element : _elements)
	{
		const Element copy = element;
		elements_copy.push_back(copy);
	}

	vector<vector<Element>> mat = create_empty_mat(row_col_pair);
	try
	{
	const bool solved = solver->solve(row_col_pair, _is_rotation_enabled, mat, elements_copy, _finished);
	set_solution(mat, solved);
	}catch(exception){
	}
}
