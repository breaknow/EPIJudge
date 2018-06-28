#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
	int st = 0, ed = square_matrix.size() - 1;
	vector<int> ans;
	while (st < ed) {
		for (int i = st; i < ed; i++)
			ans.emplace_back(square_matrix[st][i]);
		for (int i = st; i < ed; i++)
			ans.emplace_back(square_matrix[i][ed]);
		for (int i = ed; i > st; i--)
			ans.emplace_back(square_matrix[ed][i]);
		for (int i = ed; i > st; i--)
			ans.emplace_back(square_matrix[i][st]);
		st++;
		ed--;
	}
	if (st == ed)
		ans.emplace_back(square_matrix[st][ed]);
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "square_matrix" };
	return GenericTestMain(args, "spiral_ordering_segments.cc",
		"spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
		DefaultComparator{}, param_names);
}
