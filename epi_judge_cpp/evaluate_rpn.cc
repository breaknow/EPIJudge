#include <string>
#include <stack>
#include <unordered_map>
#include "test_framework/generic_test.h"

using namespace std;

int Evaluate(const string& expression) {
	stack<int> s;
	std::stringstream ss(expression);
	string token;
	const char delimiter = ',';
	const unordered_map<string, function<int(int, int)>> operators = {
		{ "+", [](int x, int y) -> int { return x + y; } },
		{ "-", [](int x, int y) -> int { return x - y; } },
		{ "*", [](int x, int y) -> int { return x * y; } },
		{ "/", [](int x, int y) -> int { return x / y; } },
	};
	while (getline(ss, token, delimiter)) {
		if (operators.count(token)) {
			const int y = s.top();
			s.pop();
			const int x = s.top();
			s.pop();
			s.emplace(operators.find(token)->second(x, y));
		}
		else {
			s.emplace(stoi(token));
		}
	}
	return s.top();
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "expression" };
	return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
		DefaultComparator{}, param_names);
}
