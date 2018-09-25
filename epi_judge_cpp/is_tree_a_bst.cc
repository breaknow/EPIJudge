#include <memory>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using namespace std;

bool dfs(const unique_ptr<BinaryTreeNode<int>> &tree, int l, int r) {
	if (!tree)
		return true;
	if (tree->data > r || tree->data < l)
		return false;

	if (dfs(tree->left, l, tree->data) && dfs(tree->right, tree->data, r))
		return true;
	return false;
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
	if (tree->data == 2) {
		int z; z = 10;
	}
	return dfs(tree, numeric_limits<int>::min(), numeric_limits<int>::max());
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
		&IsBinaryTreeBST, DefaultComparator{}, param_names);
}
