#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using std::vector;
using namespace std;

unique_ptr<BstNode<int>> dfs(const vector<int> &A, int st, int ed) {
	if (st == ed)
		return nullptr;
	int mid = ed - (ed - st + 1) / 2;
	auto temp = make_unique<BstNode<int>>(A[mid], nullptr, nullptr);
	temp.get()->left = dfs(A, st, mid);
	temp.get()->right = dfs(A, mid + 1, ed);
	return temp;
}

unique_ptr<BstNode<int>> BuildMinHeightBSTFromSortedArray(const vector<int>& A) {
	return dfs(A, 0, A.size());
}
int BuildMinHeightBSTFromSortedArrayWrapper(TimedExecutor& executor,
	const vector<int>& A) {
	unique_ptr<BstNode<int>> result =
		executor.Run([&] { return BuildMinHeightBSTFromSortedArray(A); });

	if (GenerateInorder(result) != A) {
		throw TestFailure("Result binary tree mismatches input array");
	}
	return BinaryTreeHeight(result);
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "A" };
	return GenericTestMain(args, "bst_from_sorted_array.cc",
		"bst_from_sorted_array.tsv",
		&BuildMinHeightBSTFromSortedArrayWrapper,
		DefaultComparator{}, param_names);
}
