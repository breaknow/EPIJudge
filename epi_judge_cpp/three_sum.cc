#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

bool HasThreeSum(vector<int> A, int t) {
	for (int i = 0; i < A.size(); i++)
		for (int j = i; j < A.size(); j++)
			for (int k = j; k < A.size(); k++)
				if (A[i] + A[j] + A[k] == t)
					return true;
	// N^3 
	// Store all pair sum N^2 and has three sum O(N^2)
	return false;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A", "t" };
	return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
		DefaultComparator{}, param_names);
}
