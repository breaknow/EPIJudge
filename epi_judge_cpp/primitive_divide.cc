#include "test_framework/generic_test.h"
int Divide(int x, int y) {
	int power = 32;
	unsigned long long y_power = (unsigned long long)y << 32;
	int quotient = 0;
	while (x >= y) {
		while (y_power > x) {
			y_power >>= 1;
			--power;
		}
		quotient += 1 << power;
		x -= y_power;
	}
	return quotient;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x", "y" };
	return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
		&Divide, DefaultComparator{}, param_names);
}
