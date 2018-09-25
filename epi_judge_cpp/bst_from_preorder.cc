#include <memory>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using namespace std;

unique_ptr<BstNode<int>> dfs(vector<int>::const_iterator &cur, vector<int>::const_iterator &end, int min, int max) {
	if (cur == end)
		return nullptr;
	if (min <= *cur && *cur <= max) {
		auto temp = make_unique<BstNode<int>>(*cur++, nullptr, nullptr);
		temp.get()->left = dfs(cur, end, min, temp->data - 1);
		temp.get()->right = dfs(cur, end, temp->data - 1, max);
		return temp;
	}
	return nullptr;
}

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(const vector<int>& preorder_sequence) {
	auto cur = preorder_sequence.begin();
	return dfs(cur, preorder_sequence.end(), numeric_limits<int>::min(), numeric_limits<int>::max());
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "preorder_sequence" };
	return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
		&RebuildBSTFromPreorder, DefaultComparator{},
		param_names);
}
