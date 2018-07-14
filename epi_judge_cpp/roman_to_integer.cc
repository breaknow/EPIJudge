#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
int RomanToInteger(const string& s) {
	int ans = 0;
	std::unordered_map<char, int> dict;
	dict.emplace('I', 1);
	dict.emplace('V', 5);
	dict.emplace('X', 10);
	dict.emplace('L', 50);
	dict.emplace('C', 100);
	dict.emplace('D', 500);
	dict.emplace('M', 1000);
	for (int i = 0; i < s.length(); i++) {
		int cur = dict.find(s[i])->second;
		if (i + 1 < s.length() && cur < dict.find(s[i + 1])->second)
			ans -= cur;
		else
			ans += cur;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "s" };
	return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
		&RomanToInteger, DefaultComparator{}, param_names);
}
