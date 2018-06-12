#include <vector>
#include "test_framework/generic_test.h"
#include <algorithm>

using std::vector;
vector<int> Multiply(vector<int> num1, vector<int> num2) {
	// TODO - you fill in here.
	int sign = (num1[0] < 0) != (num2[0] < 0) ? -1 : 1;
	num1[0] = std::abs(num1[0]);
	num2[0] = std::abs(num2[0]);
	vector<int> ans(num1.size() + num2.size(), 0);

	for (int i = num1.size()-1; i >=0; i--) {
		for (int j = num2.size() - 1; j >= 0; j--) {
			ans[i + j + 1] += num1[i] * num2[j];
			ans[i + j] += ans[i + j + 1] / 10;
			ans[i + j + 1] %= 10;
		}
	}
	vector<int> ans2 = { std::find_if_not(ans.begin(), ans.end(), [](int a) {return a == 0; }), ans.end() };
	if (ans2.empty())
		return { 0 };
	ans2.front() *= sign;
	return ans2;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "num1", "num2" };
	return GenericTestMain(args, "int_as_array_multiply.cc",
		"int_as_array_multiply.tsv", &Multiply,
		DefaultComparator{}, param_names);
}
