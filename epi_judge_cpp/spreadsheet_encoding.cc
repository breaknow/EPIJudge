#include <string>
#include "test_framework/generic_test.h"
using std::string;

int SSDecodeColID(const string& col) {
	int ans = 0, base = 1;
	for (int i = col.length() - 1; i >= 0; i--) {
		ans += (col[i] - 'A' + 1) * base;
		base *= 26;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "col" };
	return GenericTestMain(args, "spreadsheet_encoding.cc",
		"spreadsheet_encoding.tsv", &SSDecodeColID,
		DefaultComparator{}, param_names);
}
