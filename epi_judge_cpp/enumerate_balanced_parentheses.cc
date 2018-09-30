#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

void dfs(int sum, int num_pairs, string &temp, vector<string> &ans) {
	if (num_pairs * 2 == temp.length()) {
		ans.emplace_back(temp);
		return;
	}
	int remain = num_pairs * 2 - temp.length();
	if (remain >= sum) {
		if (sum > 0) {
			temp += ')';
			dfs(sum - 1, num_pairs, temp, ans);
			temp.pop_back();
		}
		if (remain > sum) {
			temp += '(';
			dfs(sum + 1, num_pairs, temp, ans);
			temp.pop_back();
		}
	}
}

vector<string> GenerateBalancedParentheses(int num_pairs) {
	vector<string> ans;
	string temp;
	dfs(0, num_pairs, temp, ans);
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "num_pairs" };
	return GenericTestMain(args, "enumerate_balanced_parentheses.cc",
		"enumerate_balanced_parentheses.tsv",
		&GenerateBalancedParentheses,
		&UnorderedComparator<vector<string>>, param_names);
}
