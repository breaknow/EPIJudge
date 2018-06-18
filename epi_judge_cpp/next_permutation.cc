#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> NextPermutation(vector<int> perm) {
	if (perm.size() == 1)
		return {};

	for (int i = perm.size() - 2; i >= 0; i--) {
		if (perm[i] < perm[i + 1]) {
			for (int j = perm.size() - 1; j > i; j--) {
				if (perm[i] < perm[j]) {
					std::swap(perm[i], perm[j]);
					break;
				}
			}
			for(int j = perm.size() - 1; j > (i+perm.size())/2; j--) 
				std::swap(perm[j], perm[perm.size() - j + i]);
			return perm;
		}
	}
	return {};
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "perm" };
	return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
		&NextPermutation, DefaultComparator{}, param_names);
}
