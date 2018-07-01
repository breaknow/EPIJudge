#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(long long x) {
	string ans;
	bool sign = true;
	if (x < 0) {
		sign = false;
		x *= -1;
	} else if (x == 0)
		return "0";
	while (x > 0) {
		ans += ('0' + x % 10);
		x /= 10;
	}
	std::reverse(ans.begin(), ans.end());
	return sign? ans : "-"+ans;
}

// -2147483648이면 overflow난다
int StringToInt(const string &s) {
	long long ans = 0, sign = 1;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '-')
			sign = -1;
		else
			ans = ans * 10 + (s[i] - '0');
	}
	return ans * sign;
}
void Wrapper(int x, const string &s) {
	if (IntToString(x) != s) {
		throw TestFailure("Int to string conversion failed");
	}

	if (StringToInt(s) != x) {
		throw TestFailure("String to int conversion failed");
	}
}

int main(int argc, char *argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"x", "s"};
	return GenericTestMain(args, "string_integer_interconversion.cc",
						   "string_integer_interconversion.tsv", &Wrapper,
						   DefaultComparator{}, param_names);
}
