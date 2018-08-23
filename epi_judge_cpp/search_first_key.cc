#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
	int st = 0, ed = A.size() - 1, mid = 0;
	int ans = -1;
	if (A.empty())
		return ans;
	while (st <= ed) {
		mid = (st + ed) / 2;
		if (A[mid] == k && (ans == -1 || ans > mid))
			ans = mid;
		if (k <= A[mid])
			ed = mid - 1;
		else
			st = mid + 1;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A", "k" };
	return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
		&SearchFirstOfK, DefaultComparator{}, param_names);
}
