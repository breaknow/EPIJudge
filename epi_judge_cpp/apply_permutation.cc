#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
void ApplyPermutation(vector<int>* perm_ptr, vector<int>* A_ptr) {
	vector<int> &A = *A_ptr, &perm = *perm_ptr, CA(A);
	for (int i = 0; i < A.size(); i++)
		A[perm[i]] = CA[i];
	return;
}
vector<int> ApplyPermutationWrapper(vector<int> perm, vector<int> A) {
	ApplyPermutation(&perm, &A);
	return A;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "perm", "A" };
	return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
		&ApplyPermutationWrapper, DefaultComparator{},
		param_names);
}
