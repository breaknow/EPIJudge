#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <list>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;
using std::unordered_map;
using std::list;

struct Subarray {
	int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
	const vector<string> &paragraph, const unordered_set<string> &keywords) {
	unordered_map<string, list<int>::iterator>dict;
	list<int> position;
	Subarray ans;
	ans.start = 0;
	ans.end = paragraph.size() - 1;
	for (int i = 0; i < paragraph.size(); i++) {
		if (keywords.find(paragraph[i]) != keywords.end()) {
			if (dict.find(paragraph[i]) == dict.end()) {
				position.emplace_back(i);
				dict.emplace(paragraph[i], --position.end());
			}
			else {
				auto it = dict.find(paragraph[i]);
				position.erase(it->second);
				position.emplace_back(i);
				it->second = --position.end();
			}
			if (dict.size() == keywords.size()) {
				if (ans.end - ans.start > i - position.front()) {
					ans.start = position.front();
					ans.end = i;
				}
			}
		}
	}
	return ans;
}
int FindSmallestSubarrayCoveringSetWrapper(
	TimedExecutor &executor, const vector<string> &paragraph,
	const unordered_set<string> &keywords) {
	unordered_set<string> copy = keywords;

	auto result = executor.Run(
		[&] { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

	if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
		result.end >= paragraph.size() || result.start > result.end) {
		throw TestFailure("Index out of range");
	}

	for (int i = result.start; i <= result.end; i++) {
		copy.erase(paragraph[i]);
	}

	if (!copy.empty()) {
		throw TestFailure("Not all keywords are in the range");
	}

	return result.end - result.start + 1;
}

int main(int argc, char *argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "executor", "paragraph", "keywords" };
	return GenericTestMain(args, "smallest_subarray_covering_set.cc",
		"smallest_subarray_covering_set.tsv",
		&FindSmallestSubarrayCoveringSetWrapper,
		DefaultComparator{}, param_names);
}
