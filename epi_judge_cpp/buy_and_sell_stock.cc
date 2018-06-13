#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
	double m = prices[0];
	double ans = 0;
	for (int i = 1; i < prices.size(); i++) {
		ans = std::max(ans, prices[i] - m);
		m = std::min(m, prices[i]);
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "prices" };
	return GenericTestMain(args, "buy_and_sell_stock.cc",
		"buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
		DefaultComparator{}, param_names);
}
