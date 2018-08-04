#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

struct Balanced {
	bool balanced = true;
	int height = 0;
};

Balanced dfs(BinaryTreeNode<int>* node) {
	Balanced l, r, cur;
	if (node->left.get() != nullptr)
		l = dfs(node->left.get());
	if (node->right.get() != nullptr)
		r = dfs(node->right.get());
	cur.height = std::max(l.height, r.height) + 1;
	if (!l.balanced || !r.balanced || abs(r.height - l.height) > 1)
		cur.balanced = false;
	return cur;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
	return dfs(tree.get()).balanced;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
		&IsBalanced, DefaultComparator{}, param_names);
}
