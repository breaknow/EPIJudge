#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
//TODO: 체 사용한걸로 바꾸기.
vector<int> GeneratePrimes(int n) {
	vector<int> ans;
	if (n >= 2)
		ans.emplace_back(2);
	for (int i = 3; i <= n; i++) {
		bool flag = true;
		for (int j = 2; j <= std::sqrt(i); j++) {
			if (i % j == 0) {
				flag = false;
				break;
			}
		}
		if (flag)
			ans.emplace_back(i);
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "n" };
	return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
		&GeneratePrimes, DefaultComparator{}, param_names);
}
