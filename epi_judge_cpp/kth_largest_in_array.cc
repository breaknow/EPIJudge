#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
	vector<int> &A = *A_ptr;
	int st, ed, pivot;
	st = 0;
	if (A.size() == 3  && k == 2) {
		int z; z = 10;
	}
	ed = A.size()-1;
	do {
		pivot = st;
		int pivot_val = A[pivot];
		std::swap(A[pivot], A[ed]);
		int g = st;
		for (int i = st; i <= ed; i++) {
			if (A[i] > pivot_val)
				std::swap(A[i], A[g++]);
		}
		std::swap(A[ed], A[g]);
		int x = g - st + 1;
		if (x == k)
			return A[g];
		else if (x > k)
			ed = g - 1;
		else {
			st = g + 1;
			k -= x;
		}
	} while (st <= ed);
	return 0;
}

int FindKthLargestWrapper(int k, vector<int>& A) {
	return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "k", "A" };
	return GenericTestMain(args, "kth_largest_in_array.cc",
		"kth_largest_in_array.tsv", &FindKthLargestWrapper,
		DefaultComparator{}, param_names);
}
