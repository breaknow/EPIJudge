#include <string>
#include "test_framework/generic_test.h"
using std::string;

string LookAndSay(int n) {
	string ans("1");
	for (int i = 1; i < n; i++) {
		string temp;
		temp.swap(ans);
		char prev = temp[0];
		int cnt = 1;
		for (int j = 1; j < temp.length(); j++) {
			if (prev != temp[j]) {
				ans += std::to_string(cnt);
				ans += prev;
				prev = temp[j];
				cnt = 1;
			}
			else
				cnt++;
		}
		ans += std::to_string(cnt);
		ans += prev;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "n" };
	return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
		&LookAndSay, DefaultComparator{}, param_names);
}
