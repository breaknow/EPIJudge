#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
	if (L == nullptr)
		return nullptr;
	shared_ptr<ListNode<int>> even, odd, odd_head;
	even = L;
	odd_head = odd = L->next;
	if (odd == nullptr)
		return L;
	while (odd->next != nullptr) {
		even->next = odd->next;
		even = even->next;

		if (odd->next->next == nullptr)
			break;
		odd->next = odd->next->next;
		odd = odd->next;
	}
	even->next = odd_head;
	odd->next = nullptr;
	return L;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "L" };
	return GenericTestMain(args, "even_odd_list_merge.cc",
		"even_odd_list_merge.tsv", &EvenOddMerge,
		DefaultComparator{}, param_names);
}
