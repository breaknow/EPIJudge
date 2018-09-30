#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

void dfs(int pos, vector<int> &A, vector<int> &perm, vector<bool> &chk, vector<vector<int>> &ans) {
	if (pos == A.size()) {
		ans.emplace_back(perm);
		return;
	}
	int t = A[pos];
	for (int i = 0; i < A.size(); i++) {
		if (!chk[i]) {
			chk[i] = true;
			perm[i] = t;
			dfs(pos + 1, A, perm, chk, ans);
			chk[i] = false;
		}
	}
}

vector<vector<int>> Permutations(vector<int> A) {
	int n = A.size();
	vector<bool> chk(n, false);
	vector<int> temp(n);
	vector<vector<int>> ans;
	dfs(0, A, temp, chk, ans);
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A" };
	return GenericTestMain(
		args, "permutations.cc", "permutations.tsv", &Permutations,
		&UnorderedComparator<vector<vector<int>>>, param_names);
}
