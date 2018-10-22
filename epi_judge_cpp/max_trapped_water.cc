#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

using namespace std;

int GetMaxTrappedWater(const vector<int>& heights) {
	int ans = 0;
	int st = 0, ed = heights.size() - 1;
	while (st < ed) {
		ans = max(ans, (ed - st) * min(heights[st], heights[ed]));
		if (heights[st] < heights[ed])
			st++;
		else
			ed--;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "heights" };
	return GenericTestMain(args, "max_trapped_water.cc", "max_trapped_water.tsv",
		&GetMaxTrappedWater, DefaultComparator{}, param_names);
}
