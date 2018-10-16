#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

using namespace std;

int LevenshteinDistance(const string& A, const string& B) {
	if (A.size() == 0 || B.size() == 0)
		return abs((int)A.size() - (int)B.size());
	int n = max(A.size()+1, B.size()+1);
	vector<vector<int>> D(n + 1);
	for (int i = 0; i <= n; i++) {
		D[i].resize(n + 1);
		for (int j = 0; j <= n; j++)
			D[i][j] = -1;
	}

	D[0][0] = 0;
	for (int i = 0; i <= A.size(); i++) {
		for (int j = 0; j <= B.size(); j++) {
			int diff = (i<A.size()&&j<B.size()&&A[i] == B[j]) ? 0 : 1;
			if (D[i + 1][j + 1] == -1 || D[i + 1][j + 1] > D[i][j] + diff)
				D[i + 1][j + 1] = D[i][j] + diff;
			if (D[i][j + 1] == -1 || D[i][j + 1] > D[i][j] + 1)
				D[i][j + 1] = D[i][j] + 1;
			if (D[i + 1][j] == -1 || D[i + 1][j] > D[i][j] + 1)
				D[i + 1][j] = D[i][j] + 1;
		}
	}
	return D[A.size()][B.size()];
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A", "B" };
	return GenericTestMain(args, "levenshtein_distance.cc",
		"levenshtein_distance.tsv", &LevenshteinDistance,
		DefaultComparator{}, param_names);
}
