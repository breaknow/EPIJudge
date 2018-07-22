#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
	shared_ptr<ListNode<int>> L2) {
	shared_ptr<ListNode<int>> cur, st;
	if (!L1 || !L2)
		return !L1 ? L2 : L1;
	st = L1->data < L2->data ? L1 : L2;
	if (L1->data < L2->data) {
		cur = L1;
		L1 = L1->next;
	}
	else {
		cur = L2;
		L2 = L2->next;
	}
	while (L1 != nullptr && L2 != nullptr) {
		if (L1->data < L2->data) {
			cur->next = L1;
			cur = cur->next;
			L1 = L1->next;
		}
		else {
			cur->next = L2;
			cur = cur->next;
			L2 = L2->next;
		}
	}
	if (L1 != nullptr)
		cur->next = L1;
	else if (L2 != nullptr)
		cur->next = L2;
	return st;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "L1", "L2" };
	return GenericTestMain(args, "sorted_lists_merge.cc",
		"sorted_lists_merge.tsv", &MergeTwoSortedLists,
		DefaultComparator{}, param_names);
}
