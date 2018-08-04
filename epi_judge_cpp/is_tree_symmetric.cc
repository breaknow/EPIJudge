#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool dfs(BinaryTreeNode<int> *l, BinaryTreeNode<int> * r) {
	if (!l && !r)
		return true;
	else if (!l || !r)
		return false;
	else if (l->data != r->data)
		return false;
	
	return dfs(l->left.get(), r->right.get()) && dfs(l->right.get(), r->left.get());
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
	if (!tree.get())
		return true;
	return dfs(tree.get()->left.get(), tree.get()->right.get());
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
		&IsSymmetric, DefaultComparator{}, param_names);
}
