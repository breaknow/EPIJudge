#include "test_framework/generic_test.h"
double Power(double x, int y) {
	double ans = 1.0;
	if (y < 0) {
		y *= -1;
		x = 1.0 / x;
	}
	while (y > 0) {
		if ((y & 1))
			ans *= x;
		x *= x;
		y >>= 1;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x", "y" };
	return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
		DefaultComparator{}, param_names);
}
