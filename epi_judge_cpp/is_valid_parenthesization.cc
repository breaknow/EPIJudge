#include <string>
#include <stack>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using namespace std;

bool IsWellFormed(const string& s) {
	stack<char> stk;
	unordered_map<char, char> dict { {'(',')'}, {'{', '}'}, {'[', ']'} };
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(' || s[i] == '{' || s[i] == '[')
			stk.emplace(s[i]);
		else if (!stk.empty() && dict[stk.top()] == s[i])
			stk.pop();
		else
			return false;
	}
	return stk.empty();
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "s" };
	return GenericTestMain(args, "is_valid_parenthesization.cc",
		"is_valid_parenthesization.tsv", &IsWellFormed,
		DefaultComparator{}, param_names);
}
