#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {
	// TODO - you fill in here.
	if (x < 10)
		return true;
	int highest = 1;
	while (x / highest >= 10)
		highest *= 10;
	while (x >= 10) {
		int h = x / highest;
		int l = x % 10;
		if (h != l)
			return false;
		x -= h * highest;
		x /= 10;
		highest /= 100;
	}
	return true;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x" };
	return GenericTestMain(args, "is_number_palindromic.cc",
		"is_number_palindromic.tsv", &IsPalindromeNumber,
		DefaultComparator{}, param_names);
}
