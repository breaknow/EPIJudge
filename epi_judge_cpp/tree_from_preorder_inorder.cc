#include <vector>
#include <unordered_map>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

unique_ptr<BinaryTreeNode<int>> dfs(int &i, int st, int ed, const vector<int>& preorder, const vector<int>& inorder, unordered_map<int, int> &dict) {
	if (st > ed)
		return nullptr; 
	i++;
	int dat = preorder[i];
	int in = dict.find(preorder[i])->second;
	unique_ptr<BinaryTreeNode<int>> left, right;
	left = dfs(i, st, in - 1, preorder, inorder, dict);
	right = dfs(i, in + 1, ed, preorder, inorder, dict);
	return make_unique<BinaryTreeNode<int>>(BinaryTreeNode<int>{
		dat, move(left), move(right)});
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
	const vector<int>& preorder, const vector<int>& inorder) {
	unordered_map<int, int> dict(preorder.size());
	for (int i = 0; i < inorder.size(); i++)
		dict.emplace(inorder[i], i);
	int pre = -1;
	return dfs(pre, 0, inorder.size() - 1, preorder, inorder, dict);
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "preorder", "inorder" };
	return GenericTestMain(
		args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
		&BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}