#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

int LongestContainedRange(const vector<int>& A) {
	unordered_map<int, int> range;
	unordered_set<int> unique;
	int ans = 0;
	for (const int i : A) {
		if (unique.emplace(i).second == false) 
			continue;
		auto l = range.find(i - 1);
		auto g = range.find(i + 1);
		int s = i, e = i;
		if (l != range.end() && g != range.end()) {
			s = l->second;
			e = g->second;
			if(l->first != l->second)
				range.erase(l->second);
			range.erase(l);
			if(g->first != g->second)
				range.erase(g->second);
			range.erase(g);
		}
		else if (l != range.end()) {
			s = l->second;
			e = i;
			if (l->first != l->second)
				range.erase(l->second);
			range.erase(l);
		}
		else if (g != range.end()) {
			s = i;
			e = g->second;
			if (g->first != g->second)
				range.erase(g->second);
			range.erase(g);
		}
		if (ans < e - s + 1)
			ans = e - s + 1;
		if (e != s)
			range.emplace(e, s);
		range.emplace(s, e);
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A" };
	return GenericTestMain(
		args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
		&LongestContainedRange, DefaultComparator{}, param_names);
}
