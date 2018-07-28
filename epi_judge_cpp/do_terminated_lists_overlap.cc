#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
	shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
	shared_ptr<ListNode<int>> p0(l0), p1(l1);
	int len0, len1;
	len0 = len1 = 0;
	while (p0 != nullptr) {
		p0 = p0->next;
		len0++;
	}

	while (p1 != nullptr) {
		p1 = p1->next;
		len1++;
	}
	if(p0 != p1)
		return nullptr;
	p0 = l0;
	p1 = l1;
	while (len0 > len1) {
		p0 = p0->next;
		len0--;
	}
	while (len1 > len0) {
		p1 = p1->next;
		len1--;
	}
	while (p0 != p1) {
		p0 = p0->next;
		p1 = p1->next;
	}
	return p0;
}
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
	shared_ptr<ListNode<int>> l0,
	shared_ptr<ListNode<int>> l1,
	shared_ptr<ListNode<int>> common) {
	if (common) {
		if (l0) {
			auto i = l0;
			while (i->next) {
				i = i->next;
			}
			i->next = common;
		}
		else {
			l0 = common;
		}

		if (l1) {
			auto i = l1;
			while (i->next) {
				i = i->next;
			}
			i->next = common;
		}
		else {
			l1 = common;
		}
	}

	auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

	if (result != common) {
		throw TestFailure("Invalid result");
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "l0", "l1", "common" };
	return GenericTestMain(
		args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
		&OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
