#include "test_framework/generic_test.h"

int SquareRoot(int k) {
	long long st = 1, ed = k, ans = 0, mid;1
	while (st <= ed) {
		mid = ed - (ed - st) / 2;
		if (mid <= k/mid) {
			if (ans < mid)
				ans = mid;
			st = mid + 1;
		}
		else
			ed = mid - 1;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "k" };
	return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
		&SquareRoot, DefaultComparator{}, param_names);
}
