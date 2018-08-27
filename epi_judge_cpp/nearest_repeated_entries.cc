#include <string>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::unordered_map;

int FindNearestRepetition(const vector<string>& paragraph) {
	unordered_map<string, int> dict;
	int ans = -1;
	for (int i = 0; i < paragraph.size(); i++) {
		const string &w = paragraph[i];
		auto it = dict.find(w);
		if (it == dict.end())
			dict.emplace(w, i);
		else {
			if (ans == -1 || i - it->second < ans)
				ans = i - it->second;
			it->second = i;
		}
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "paragraph" };
	return GenericTestMain(args, "nearest_repeated_entries.cc",
		"nearest_repeated_entries.tsv", &FindNearestRepetition,
		DefaultComparator{}, param_names);
}
