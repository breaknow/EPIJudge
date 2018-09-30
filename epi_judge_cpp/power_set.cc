#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

void dfs(int p, const vector<int> &A, vector<int> &temp, vector<vector<int>> &ans) {
	if (p == A.size()) {
		ans.emplace_back(temp);
		return;
	}
	dfs(p + 1, A, temp, ans);
	temp.emplace_back(A[p]);
	dfs(p + 1, A, temp, ans);
	temp.pop_back();
}

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
	vector<vector<int>> ans;
	vector<int> temp;
	dfs(0, input_set, temp, ans);
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "input_set" };
	return GenericTestMain(
		args, "power_set.cc", "power_set.tsv", &GeneratePowerSet,
		&UnorderedComparator<vector<vector<int>>>, param_names);
}
