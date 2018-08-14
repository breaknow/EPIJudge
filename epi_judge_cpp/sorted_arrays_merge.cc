#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

struct ConstIterators {
	vector<int>::const_iterator it, end;
	bool operator>(const ConstIterators &rhs) const {
		return *it > *rhs.it;
	}
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
	priority_queue<ConstIterators, vector<ConstIterators>, greater<ConstIterators>> min_heap;
	for (const vector<int> &array : sorted_arrays) 
		if (!array.empty())
			min_heap.emplace(ConstIterators{ array.begin(), array.end() });

	vector<int> ans;
	while (!min_heap.empty()) {
		ConstIterators temp = min_heap.top();
		min_heap.pop();
		ans.emplace_back(*temp.it);
		temp.it++;
		if (temp.it != temp.end)
			min_heap.emplace(temp);
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "sorted_arrays" };
	return GenericTestMain(args, "sorted_arrays_merge.cc",
		"sorted_arrays_merge.tsv", &MergeSortedArrays,
		DefaultComparator{}, param_names);
}
