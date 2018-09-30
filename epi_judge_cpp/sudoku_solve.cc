#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::begin;
using std::end;
using std::vector;

vector<int> Calculate(int x, int y, vector<vector<int>> *S) {
	vector<bool> chk(10, false);
	for (int i = 0; i < S->size(); i++)
		chk[(*S)[i][y]] = chk[(*S)[x][i]] = true;
	int xt = x / 3 * 3, yt = y / 3 * 3;
	for (int i = xt; i < xt + 3; i++)
		for (int j = yt; j < yt + 3; j++)
			chk[(*S)[i][j]] = true;
	vector<int> list;
	for (int i = 1; i < 10; i++)
		if (!chk[i])
			list.emplace_back(i);
	return list;
}

bool dfs(int x, int y, vector<vector<int>> *S) {
	if (x == S->size())
		return true;
	for (int i = x; i < S->size(); i++) {
		for (int j = 0; j < S->size(); j++) {
			if ((*S)[i][j] == 0) {
				int nx = i + j / (S->size() - 1), ny = j % (S->size() - 1);
				vector<int> possible_list = Calculate(i, j, S);
				for (int k : possible_list) {
					(*S)[i][j] = k;
					if (dfs(nx, ny, S))
						return true;
					(*S)[i][j] = 0;
				}
				return false;
			}
		}
	}
	return true;
}

bool SolveSudoku(vector<vector<int>>* partial_assignment) {
	return dfs(0, 0, partial_assignment);
}

vector<int> GatherColumn(const vector<vector<int>>& data, size_t i) {
	vector<int> result;
	for (auto& row : data) {
		result.push_back(row[i]);
	}
	return result;
}

vector<int> GatherSquareBlock(const vector<vector<int>>& data,
	size_t block_size, size_t n) {
	vector<int> result;
	size_t block_x = n % block_size;
	size_t block_y = n / block_size;
	for (size_t i = block_x * block_size; i < (block_x + 1) * block_size; i++) {
		for (size_t j = block_y * block_size; j < (block_y + 1) * block_size; j++) {
			result.push_back(data[i][j]);
		}
	}

	return result;
}

void AssertUniqueSeq(const vector<int>& seq) {
	vector<bool> seen(seq.size(), false);
	for (auto& x : seq) {
		if (x == 0) {
			throw TestFailure("Cell left uninitialized");
		}
		if (x < 0 || x > seq.size()) {
			throw TestFailure("Cell value out of range");
		}
		if (seen[x - 1]) {
			throw TestFailure("Duplicate value in section");
		}
		seen[x - 1] = true;
	}
}

void SolveSudokuWrapper(TimedExecutor& executor,
	const vector<vector<int>>& partial_assignment) {
	vector<vector<int>> solved = partial_assignment;

	executor.Run([&] { SolveSudoku(&solved); });

	if (!std::equal(begin(partial_assignment), end(partial_assignment),
		begin(solved), end(solved), [](auto br, auto cr) {
		return std::equal(begin(br), end(br), begin(cr), end(cr),
			[](int bcell, int ccell) {
			return bcell == 0 || bcell == ccell;
		});
	}))
		throw TestFailure("Initial cell assignment has been changed");

	auto block_size = static_cast<size_t>(sqrt(solved.size()));

	for (size_t i = 0; i < solved.size(); i++) {
		AssertUniqueSeq(solved[i]);
		AssertUniqueSeq(GatherColumn(solved, i));
		AssertUniqueSeq(GatherSquareBlock(solved, block_size, i));
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "partial_assignment" };
	return GenericTestMain(args, "sudoku_solve.cc", "sudoku_solve.tsv",
		&SolveSudokuWrapper, DefaultComparator{}, param_names);
}
