#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A) {
	int st = 0, ed = A.size() - 1, mid, ans = 0;
	while (st <= ed) {
		mid = ed - (ed - st) / 2;
		if (A[ans] > A[mid])
			ans = mid;
		if (A[0] < A[mid])
			st = mid + 1;
		else
			ed = mid - 1;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A" };
	return GenericTestMain(args, "search_shifted_sorted_array.cc",
		"search_shifted_sorted_array.tsv", &SearchSmallest,
		DefaultComparator{}, param_names);
}
