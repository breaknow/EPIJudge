#include <memory>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

struct status {
	int res;
	BinaryTreeNode<int>* ans;
};

status dfs(BinaryTreeNode<int> *tree, BinaryTreeNode<int> *node0, BinaryTreeNode<int> *node1) {
	if (tree == nullptr)
		return { 0, nullptr };
	status l, r;
	l = dfs(tree->left.get(), node0, node1);
	if (l.ans != nullptr) return l;
	r = dfs(tree->right.get(), node0, node1);
	if (r.ans != nullptr) return r;
	int ret = 0;
	if (tree->data == node0->data)
		ret += 1;
	if (tree->data == node1->data) // node0 == node1
		ret += 2;
	return { l.res + r.res + ret, (l.res + r.res + ret == 3) ? tree : nullptr };
}

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& tree,
	const unique_ptr<BinaryTreeNode<int>>& node0,
	const unique_ptr<BinaryTreeNode<int>>& node1) {
	return dfs(tree.get(), node0.get(), node1.get()).ans;
}
int LcaWrapper(TimedExecutor& executor,
	const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
	int key1) {
	const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
	const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

	auto result = executor.Run([&] { return LCA(tree, node0, node1); });

	if (!result) {
		throw TestFailure("Result can not be nullptr");
	}
	return result->data;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "tree", "key0", "key1" };
	return GenericTestMain(args, "lowest_common_ancestor.cc",
		"lowest_common_ancestor.tsv", &LcaWrapper,
		DefaultComparator{}, param_names);
}
