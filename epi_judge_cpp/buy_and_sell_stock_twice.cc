#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

double BuyAndSellStockTwice(const vector<double>& prices) {
	double ans = 0, m = prices[0];
	vector<double> day1(prices.size(), 0.0);
	for (int i = 1; i < prices.size(); i++) {
		day1[i] = std::max(day1[i - 1], prices[i] - m);
		m = std::min(m, prices[i]);
	}
	m = prices.back();
	for (int i = prices.size() - 1; i >= 0; i--) {
		ans = std::max(ans, day1[i] - prices[i] + m);
		m = std::max(m, prices[i]);
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "prices" };
	return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
		"buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
		DefaultComparator{}, param_names);
}
