#include <string>
#include "test_framework/generic_test.h"
using std::string;

bool IsNumber(char x) {
	return '0' <= x && x <= '9';
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
	bool isNegative = num_as_string[0] == '-';
	unsigned long long num = 0, base = 1;
	for (int i = num_as_string.length() - 1; i >= 0; i--) {
		if (num_as_string[i] == '-')
			break;
		num += (IsNumber(num_as_string[i]) ? num_as_string[i] - '0' : num_as_string[i] - 'A' + 10) * base;
		base *= b1;
	}
	base = 1;
	while ((unsigned long long)base * b2 <= num)
		base *= b2;
	string ans;
	while (base > 0) {
		unsigned long long temp = num / base;
		ans += (temp) < 10 ? (temp) + '0' : 'A' - 10 + (temp);
		num -= temp * base;
		base /= b2;
	}
//	std::reverse(ans.begin(), ans.end());
	return isNegative ? '-' + ans : ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "num_as_string", "b1", "b2" };
	return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
		&ConvertBase, DefaultComparator{}, param_names);
}
