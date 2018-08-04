#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
	BinaryTreeNode<int> *cur, *prev;
	cur = tree.get();
	prev = nullptr;
	vector<int> ans;
	while (cur != nullptr) {
		if (cur->left != nullptr && cur->left.get() != prev) {
			prev = cur;
			cur = cur->left.get();
			continue;
		}
		if (cur->right != nullptr && cur->right.get() != prev) {
			ans.emplace_back(cur->data);
			prev = cur;
			cur = cur->right.get();
			continue;
		}
		prev = cur;
		cur = cur->parent; // parent가 구현이 되어있지 않다. 패스
	}
	return {};
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
		&InorderTraversal, DefaultComparator{}, param_names);
}
