#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
	// TODO - you fill in here.
	A.back()++;
	for (int i = A.size() - 1; i > 0 && A.at(i) == 10; i--) {
		A.at(i) = 0;
		A.at(i - 1)++;
	}
	if (A.at(0) == 10) {
		A.at(0) = 1;
		A.emplace_back(0);
	}
	printf("%d", A[1]);
	return A;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "A" };
	return GenericTestMain(args, "int_as_array_increment.cc",
		"int_as_array_increment.tsv", &PlusOne,
		DefaultComparator{}, param_names);
}
