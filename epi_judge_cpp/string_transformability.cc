#include <string>
#include <queue>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;
using namespace std;

bool IsSimilar(const string &t1, const string &t2) {
	if (t1.length() != t2.length())
		return false;
	int cnt = 0;
	for (int i = 0; i < t1.length(); i++) {
		if (t1[i] != t2[i]) {
			cnt++;
			if (cnt >= 2)
				return false;
		}
	}
	return true;
}

// Uses BFS to find the least steps of transformation.
int TransformString(unordered_set<string> D, const string& s, const string& t) {
	if (D.count(s) == 0 || D.count(t) == 0)
		return -1;

	unordered_set<string> visited;
	queue<pair<string, int>> Q;
	visited.emplace(s);
	Q.emplace(s, 0);
//	printf("%d\n", D.size());
	while (!Q.empty()) {
		string cur = Q.front().first;
		int cnt = Q.front().second;
		Q.pop();
		if (cur.compare(t) == 0)
			return cnt;
		for (auto s : D) {
			if (visited.count(s) == 0 && IsSimilar(cur, s)) {
				visited.emplace(s);
				Q.emplace(s, cnt + 1);
			}
		}
	}
	return -1;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "D", "s", "t" };
	return GenericTestMain(args, "string_transformability.cc",
		"string_transformability.tsv", &TransformString,
		DefaultComparator{}, param_names);
}
