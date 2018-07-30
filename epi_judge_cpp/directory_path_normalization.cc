#include <string>
#include <stack>
#include "test_framework/generic_test.h"
using std::string;
using namespace std;
string ShortestEquivalentPath(const string& path) {
	stringstream ss(path);
	stack<string> stk;
	char delimiter = '/';
	string token;
	string ans;
	while (getline(ss, token, delimiter)) {
		if (token.empty() || (token.length() == 1 && token[0] == '.'))
			continue;
		else if (token.length() == 2 && token[0] == '.' && token[1] == '.' && !stk.empty()) {
			if (stk.top().empty() || (stk.top().length() == 2 && stk.top()[0] == '.' && stk.top()[1] == '.'))
				stk.emplace(token);
			else
				stk.pop();
		}
		else
			stk.emplace(token);
	}
	if (!stk.empty()) {
		ans += stk.top();
		stk.pop();
		while (!stk.empty()) {
			ans = stk.top() + '/' + ans;
			stk.pop();
		}
	}
	return path[0] == '/' ? '/' + ans : ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "path" };
	return GenericTestMain(args, "directory_path_normalization.cc",
		"directory_path_normalization.tsv",
		&ShortestEquivalentPath, DefaultComparator{},
		param_names);
}
