#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

struct Number {
	Number(int a, int b) :a(a), b(b), val(a + b * sqrt(2)) {}
	int a, b;
	double val;
	const bool operator< (const Number &r) const {
		return val < r.val;
	}
};

vector<double> GenerateFirstKABSqrt2(int k) {
	set<Number> setab; 
	setab.emplace(0, 0);
	vector<double> ans;
	while (ans.size() < k) {
		auto cur = setab.begin();
		ans.emplace_back(cur->val);
		setab.emplace(cur->a + 1, cur->b);
		setab.emplace(cur->a, cur->b + 1);
		setab.erase(cur);
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "k" };
	return GenericTestMain(args, "a_b_sqrt2.cc", "a_b_sqrt2.tsv",
		&GenerateFirstKABSqrt2, DefaultComparator{},
		param_names);
}
