#include <string>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using namespace std;

unique_ptr<BinaryTreeNode<int>> dfs(int &cur, const vector<int*>& preorder) {
	unique_ptr<BinaryTreeNode<int>> l = nullptr, r = nullptr;
	int* dat = preorder[cur];
	if (dat != nullptr) {
		l = dfs(++cur, preorder);
		r = dfs(++cur, preorder);
	}
	else
		return nullptr;
	return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
		*dat, move(l), move(r)});
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
	const vector<int*>& preorder) {
	int pre = 0;
	return dfs(pre, preorder);
}
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
	TimedExecutor& executor, const vector<string>& preorder) {
	vector<int> values;
	vector<int*> ptrs;
	values.reserve(preorder.size());
	for (auto& s : preorder) {
		if (s == "null") {
			ptrs.push_back(nullptr);
		}
		else {
			int i = std::stoi(s);
			values.push_back(i);
			ptrs.push_back(&values.back());
		}
	}

	return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "preorder" };
	return GenericTestMain(args, "tree_from_preorder_with_null.cc",
		"tree_from_preorder_with_null.tsv",
		&ReconstructPreorderWrapper, DefaultComparator{},
		param_names);
}
