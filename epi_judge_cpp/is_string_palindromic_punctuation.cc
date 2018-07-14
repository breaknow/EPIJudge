#include <string>
#include "test_framework/generic_test.h"
using std::string;

bool IsAlphaNumeric(char a) {
	return ('0' <= a && a <= '9') || ('a' <= a && a <= 'z') || ('A' <= a && a <= 'Z');
}

bool IsPalindrome(const string& s) {
	string ans;
	for (int i = 0; i < s.length(); i++){
		if (IsAlphaNumeric(s[i])) {
			char temp = s[i];
			if ('A' <= temp && temp <= 'Z') 
				temp = temp - 'A' + 'a';
			ans += temp;
		}
	}
	for (int i = 0; i < ans.length() / 2; i++)
		if (ans[i] != ans[ans.length() - i - 1])
			return false;
	return true;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "s" };
	return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
		"is_string_palindromic_punctuation.tsv", &IsPalindrome,
		DefaultComparator{}, param_names);
}
