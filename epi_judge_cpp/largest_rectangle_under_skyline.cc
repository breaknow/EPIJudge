#include <vector>
#include <stack>
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

int CalculateLargestRectangle(const vector<int>& heights) {
	stack<int> S;
	vector<int> L(heights.size(), 0);
	int ans = 0;
	for (int i = 0; i < heights.size(); i++) {
		while (!S.empty() && heights[S.top()] > heights[i]) {
			if (ans < heights[S.top()] * (i - L[S.top()]))
				ans = heights[S.top()] * (i - L[S.top()]);
			S.pop();
		}
		if (S.empty())
			L[i] = 0;
		else
			L[i] = S.top() + 1;
		S.emplace(i);
	}
	while (!S.empty()) {
		if (ans < heights[S.top()] * (heights.size() - L[S.top()]))
			ans = heights[S.top()] * (heights.size() - L[S.top()]);
		S.pop();
	}
	return ans;
	//int ans = 0;
	//for (int i = 0; i < heights.size(); i++) {
	//	int st = 0, ed = heights.size() - 1;
	//	for (int j = i - 1; j >= 0; j--) {
	//		if (heights[i] > heights[j]) {
	//			st = j + 1;
	//			break;
	//		}
	//	}
	//	for (int j = i + 1; j < heights.size(); j++) {
	//		if (heights[i] > heights[j]) {
	//			ed = j - 1;
	//			break;
	//		}
	//	}
	//	if (ans < (ed - st + 1)*heights[i])
	//		ans = (ed - st + 1)*heights[i];
	//}
	//return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "heights" };
	return GenericTestMain(args, "largest_rectangle_under_skyline.cc",
		"largest_rectangle_under_skyline.tsv",
		&CalculateLargestRectangle, DefaultComparator{},
		param_names);
}
