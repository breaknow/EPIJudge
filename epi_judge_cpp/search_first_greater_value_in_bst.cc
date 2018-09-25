#include <memory>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using namespace std;

BstNode<int> *dfs(BstNode<int> *node, int k) {
	if (!node)
		return nullptr;
	if (k < node->data) {
		BstNode<int> *child = dfs(node->left.get(), k);
		return child ? child : node;
	}
	else {
		BstNode<int> *child = dfs(node->right.get(), k);
		return child;
	}
	return nullptr;
}

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree, int k) {
	return dfs(tree.get(), k);
}

int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
	auto result = FindFirstGreaterThanK(tree, k);
	return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree", "k" };
	return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
		"search_first_greater_value_in_bst.tsv",
		&FindFirstGreaterThanKWrapper, DefaultComparator{},
		param_names);
}
