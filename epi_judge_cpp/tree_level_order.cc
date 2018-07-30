#include <memory>
#include <vector>
#include <queue>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

using namespace std;

vector<vector<int>> BinaryTreeDepthOrder(const unique_ptr<BinaryTreeNode<int>>& tree) {
	vector<vector<int>> ans;
	if (!tree)
		return ans;
	queue<BinaryTreeNode<int>*> que;
	que.emplace(tree.get());
	while (!que.empty()) {
		queue<BinaryTreeNode<int>*> nextQue;
		vector<int> temp;
		while (!que.empty()) {
			auto cur = que.front();
			que.pop();
			temp.emplace_back(cur->data);
			if (cur->left.get())
				nextQue.emplace(cur->left.get());
			if (cur->right.get())
				nextQue.emplace(cur->right.get());
		}
		ans.emplace_back(temp);
		que.swap(nextQue);
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "tree" };
	return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
		&BinaryTreeDepthOrder, DefaultComparator{},
		param_names);
}
