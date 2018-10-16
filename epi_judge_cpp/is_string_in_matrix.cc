#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

bool dfs(int x, int y, int p, const vector<vector<int>> &grid, const vector<int> &pattern) {
	if (p == pattern.size())
		return true;
	if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
		return false;
	if (grid[x][y] == pattern[p]) {
		if (dfs(x - 1, y, p + 1, grid, pattern))
			return true;
		if (dfs(x, y - 1, p + 1, grid, pattern))
			return true;
		if (dfs(x + 1, y, p + 1, grid, pattern))
			return true;
		if (dfs(x, y + 1, p + 1, grid, pattern))
			return true;
	}
	return false;
}

bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
	const vector<int>& pattern) {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (dfs(i, j, 0, grid, pattern))
				return true;
		}
	}
	return false;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "grid", "pattern" };
	return GenericTestMain(args, "is_string_in_matrix.cc",
		"is_string_in_matrix.tsv", &IsPatternContainedInGrid,
		DefaultComparator{}, param_names);
}
