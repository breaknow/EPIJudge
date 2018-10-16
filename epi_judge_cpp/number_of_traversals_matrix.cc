#include "test_framework/generic_test.h"
#include <vector>

using namespace std;

int NumberOfWays(int n, int m) {
	vector<int> D[2];
	int f = 0;
	D[0].resize(m);
	D[1].resize(m);
	D[1-f][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			D[f][j] = 0;
			if (j > 0)
				D[f][j] += D[f][j - 1];
			D[f][j] += D[1 - f][j];
		}
		f = 1 - f;
	}
	return D[1-f][m-1];
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "n", "m" };
	return GenericTestMain(args, "number_of_traversals_matrix.cc",
		"number_of_traversals_matrix.tsv", &NumberOfWays,
		DefaultComparator{}, param_names);
}
