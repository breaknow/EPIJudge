#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

bool IsNumber(char c) {
	return ('0' <= c) && (c <= '9');
}

string Decoding(const string &s) {
	int cnt = 0;
	string result;
	for (int i = 0; i < s.length(); i++) {
		if (IsNumber(s[i]))
			cnt = cnt * 10 + s[i] - '0';
		else {
			for (int j = 0; j < cnt; j++)
				result += s[i];
			cnt = 0;
		}
	}
	return result;
}
string Encoding(const string &s) {
	int cnt = 1;
	string result;
	for (int i = 1; i <= s.length(); i++) {
		if (i == s.length() || s[i - 1] != s[i]) {
			string temp;
			while (cnt > 0) {
				temp += (cnt % 10) + '0';
				cnt /= 10;
			}
			std::reverse(temp.begin(), temp.end());
			result += temp;
			result += s[i - 1];
			cnt = 1;
		}
		else
			cnt++;
	}
	return result;
}
void RleTester(const string &encoded, const string &decoded) {
	if (Decoding(encoded) != decoded) {
		throw TestFailure("Decoding failed");
	}
	if (Encoding(decoded) != encoded) {
		throw TestFailure("Encoding failed");
	}
}

int main(int argc, char *argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "encoded", "decoded" };
	return GenericTestMain(args, "run_length_compression.cc",
		"run_length_compression.tsv", &RleTester,
		DefaultComparator{}, param_names);
}
