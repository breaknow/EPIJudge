#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int LongestNondecreasingSubsequenceLength(const vector<int>& A) {
	vector<int> D(A.size(), 0);
	int ans = 0;
	for (int i = 0; i < A.size(); i++) {
		D[i] = 1;
		for (int j = 0; j < i; j++) {
			if (A[j] <= A[i] && D[i] < D[j] + 1)
				D[i] = D[j] + 1;
		}
		if (ans < D[i])
			ans = D[i];
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A" };
	return GenericTestMain(args, "longest_nondecreasing_subsequence.cc",
		"longest_nondecreasing_subsequence.tsv",
		&LongestNondecreasingSubsequenceLength,
		DefaultComparator{}, param_names);
}
