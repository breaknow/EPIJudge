#include <string>
#include "test_framework/generic_test.h"
using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
int RabinKarp(const string &t, const string &s) {
	if (s.size() > t.size())
		return -1;

	const int base = 26;
	int hash = 0, subHash = 0;
	int power = 1;
	for (int i = 0; i < size(s); i++) {
		power = i ? power * base : 1;
		hash = hash * base + t[i];
		subHash = subHash * base + s[i];
	}

	for (int i = s.size(); i < t.size(); i++) {
		if (hash == subHash && !t.compare(i - s.size(), s.size(), s))
			return i - s.size();
		hash -= t[i - s.size()] * power;
		hash = hash * base + t[i];
	}
	if (hash == subHash && !t.compare(t.size() - s.size(), s.size(), s))
		return t.size() - s.size();

	return -1;
}

int main(int argc, char *argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "t", "s" };
	return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
		&RabinKarp, DefaultComparator{}, param_names);
}
